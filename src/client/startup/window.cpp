#include "startup/window.h"
#include "startup/application.h"
#include "startup/timing.h"
#include "network/packets.h"
#include "network/outbound.h"
#include "config/initialization.hpp"
#include "ui/constructors.hpp"

using shaiya::config::DAT_00719a40;
using shaiya::config::DAT_00719a44;
using shaiya::ui::FUN_005cc96d;
extern "C" {
// Original data definitions are in window_storage.cpp.
extern unsigned char dat_02203adc[];
/**
 * Forward a Win32 message to the recovered input/message context before window dispatch.
 * @param message_context Existing opaque message context; its complete layout is unresolved.
 * @param window Window receiving the original message.
 * @param message Original Win32 message identifier.
 * @param wparam Original word-sized message argument.
 * @param lparam Original long-sized message argument.
 * @return Zero suppresses this window procedure's remaining dispatch; nonzero permits it.
 * @note This declaration describes the caller-observed contract of entry 0x00535bc0.
 */
int32_t __attribute__((thiscall)) FUN_00535bc0(void* message_context, HWND window, UINT message,
                                               WPARAM wparam, LPARAM lparam);
}

namespace {
constexpr uintptr_t kManagerChildOffset = 0x26d8;
constexpr uintptr_t kOuterWindowOffset = 0x04;
constexpr uintptr_t kContentWindowOffset = 0x08;
constexpr uintptr_t kVisibilityFlagOffset = 0x14;
constexpr uintptr_t kPreviousGameLeftOffset = 0x20;
constexpr uintptr_t kPreviousGameTopOffset = 0x24;

/**
 * Read a little-endian DWORD from an opaque x86 object without requiring alignment.
 * @param object Non-null base of the recovered object storage.
 * @param offset Byte displacement of a readable four-byte field.
 * @return The field's original 32-bit bit pattern.
 */
uint32_t read_unaligned_uint32(const void* object, uintptr_t offset) {
    const auto* bytes =
        reinterpret_cast<const unsigned char*>(reinterpret_cast<uintptr_t>(object) + offset);
    return uint32_t(bytes[0]) | uint32_t(bytes[1]) << 8 | uint32_t(bytes[2]) << 16 |
           uint32_t(bytes[3]) << 24;
}
/**
 * Write a little-endian DWORD without imposing an alignment or complete-type contract.
 * @param object Non-null base of writable object storage.
 * @param offset Byte displacement of the four-byte field.
 * @param value Bit pattern to store; no neighboring bytes are changed.
 */
void write_unaligned_uint32(void* object, uintptr_t offset, uint32_t value) {
    auto* bytes = reinterpret_cast<unsigned char*>(reinterpret_cast<uintptr_t>(object) + offset);
    bytes[0] = uint8_t(value);
    bytes[1] = uint8_t(value >> 8);
    bytes[2] = uint8_t(value >> 16);
    bytes[3] = uint8_t(value >> 24);
}
/**
 * Read a four-byte x86 pointer field from opaque storage.
 * @param object Non-null base of the recovered object.
 * @param offset Byte displacement of the pointer field.
 * @return The stored pointer, including null when that is the field value.
 */
void* read_x86_pointer(const void* object, uintptr_t offset) {
    return reinterpret_cast<void*>(read_unaligned_uint32(object, offset));
}
/**
 * Follow the recovered manager indirection to its auxiliary-window child.
 * @pre The global holder and the manager pointer it contains are non-null.
 * @return The child pointer stored at the evidenced 0x26d8 offset.
 */
void* auxiliary_window_child() {
    return read_x86_pointer(read_x86_pointer(dat_0071cfb0, 0), kManagerChildOffset);
}
/**
 * Find the auxiliary-window child while allowing either manager link to be null.
 * @return The child pointer, or null when the holder or manager is absent.
 */
void* checked_auxiliary_window_child() {
    if (dat_0071cfb0 == nullptr)
        return nullptr;
    void* manager = read_x86_pointer(dat_0071cfb0, 0);
    return manager != nullptr ? read_x86_pointer(manager, kManagerChildOffset) : nullptr;
}
/** @return The low 32 bits of @p left + @p right, interpreted as signed x86 arithmetic. */
int32_t add_wrapped(int32_t left, int32_t right) {
    return int32_t(uint32_t(left) + uint32_t(right));
}
/** @return The low 32 bits of @p left - @p right, interpreted as signed x86 arithmetic. */
int32_t subtract_wrapped(int32_t left, int32_t right) {
    return int32_t(uint32_t(left) - uint32_t(right));
}
} // namespace

/**
 * Classify physical memory using the EP5.4 client's unsigned startup thresholds.
 * Updates dat_007198d0 to a tier from zero through four.
 * @return Zero when total physical memory is at most 0x09600000 bytes; one otherwise.
 * @note Preserves the original uninitialized MEMORYSTATUS::dwLength before the API call.
 * Original entry: 0x409f00.
 */
extern "C" int32_t __cdecl classify_startup_physical_memory() {
    MEMORYSTATUS status;
    GlobalMemoryStatus(&status);
    if (status.dwTotalPhys > 0x60000000u) {
        dat_007198d0 = 3;
        if (status.dwAvailPhys >= 0x2bc00000u)
            dat_007198d0 = 4;
    } else if (status.dwTotalPhys >= 0x32000000u) {
        dat_007198d0 = 2;
    } else if (status.dwTotalPhys > 0x19000000u) {
        dat_007198d0 = 1;
    } else {
        dat_007198d0 = 0;
        if (status.dwTotalPhys <= 0x09600000u)
            return 0;
    }
    return 1;
}

/**
 * Record whether Windows reports the NT platform in dat_007198d4.
 * Starts with one and preserves that value if GetVersionExA fails or reports an
 * unrecognized platform; Win32s and Windows 9x select zero. Original entry: 0x409f90.
 */
extern "C" void __cdecl detect_windows_nt_platform() {
    dat_007198d4 = 1;
    OSVERSIONINFOEXA version;
    static_assert(sizeof(version) == 0x9c,
                  "Original 409f90 allocates the complete extended version structure");
    version.dwOSVersionInfoSize = 0x9c;
    if (GetVersionExA(reinterpret_cast<OSVERSIONINFOA*>(&version)) != FALSE) {
        if (version.dwPlatformId <= VER_PLATFORM_WIN32_WINDOWS)
            dat_007198d4 = 0;
        else if (version.dwPlatformId == VER_PLATFORM_WIN32_NT)
            dat_007198d4 = 1;
    }
}

/**
 * Allocate the one-byte startup timing marker when it has not yet been allocated.
 * @return One if dat_00719a64 is non-null after the attempt; zero on allocation failure.
 * @note The allocation's original object type is unresolved. Original entry: 0x40a970.
 */
extern "C" int32_t __cdecl ensure_startup_timing_marker() {
    if (dat_00719a64 == nullptr) {
        dat_00719a64 = FUN_005cc96d(1);
        if (dat_00719a64 == nullptr)
            return 0;
    }
    return 1;
}

/**
 * Register the ANSI GAME window class and create the main client window.
 * @param window_style Win32 window style passed unchanged to CreateWindowExA.
 * @param left Outer-window left coordinate in screen pixels.
 * @param top Outer-window top coordinate in screen pixels.
 * @param window_width Outer-window width in pixels.
 * @param window_height Outer-window height in pixels.
 * Stores the returned handle, including null on failure, in dat_00719a3c.
 * Registration and creation results are otherwise unchecked. Original entry: 0x40a7f0.
 */
extern "C" void __cdecl create_game_window_ansi(uint32_t window_style, int32_t left, int32_t top,
                                                int32_t window_width, int32_t window_height) {
    WNDCLASSEXA window_class;
    static_assert(sizeof(window_class) == 0x30);
    window_class.cbSize = sizeof(window_class);
    window_class.style = CS_CLASSDC;
    window_class.lpfnWndProc = game_window_procedure;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = GetModuleHandleA(nullptr);
    window_class.hIcon =
        LoadIconA(static_cast<HINSTANCE>(DAT_00719a40), reinterpret_cast<LPCSTR>(0xb9));
    window_class.hCursor =
        LoadCursorA(static_cast<HINSTANCE>(DAT_00719a40), reinterpret_cast<LPCSTR>(0xae));
    window_class.hbrBackground = nullptr;
    window_class.lpszMenuName = nullptr;
    window_class.lpszClassName = "GAME";
    window_class.hIconSm = nullptr;
    RegisterClassExA(&window_class);
    dat_00719a3c = CreateWindowExA(0, "GAME", "Shaiya XD", window_style, left, top, window_width,
                                   window_height, nullptr, nullptr,
                                   static_cast<HINSTANCE>(DAT_00719a40), nullptr);
}

/**
 * Register the Unicode GAME window class and create the main client window.
 * @param window_style Win32 window style passed unchanged to CreateWindowExW.
 * @param left Outer-window left coordinate in screen pixels.
 * @param top Outer-window top coordinate in screen pixels.
 * @param window_width Outer-window width in pixels.
 * @param window_height Outer-window height in pixels.
 * Stores the returned handle, including null on failure, in dat_00719a3c.
 * Registration and creation results are otherwise unchecked. Original entry: 0x40ce60.
 */
extern "C" void __cdecl create_game_window_unicode(uint32_t window_style, int32_t left, int32_t top,
                                                   int32_t window_width, int32_t window_height) {
    WNDCLASSEXW window_class;
    static_assert(sizeof(window_class) == 0x30);
    window_class.cbSize = sizeof(window_class);
    window_class.style = CS_CLASSDC;
    window_class.lpfnWndProc = game_window_procedure;
    window_class.cbClsExtra = 0;
    window_class.cbWndExtra = 0;
    window_class.hInstance = GetModuleHandleW(nullptr);
    window_class.hIcon =
        LoadIconW(static_cast<HINSTANCE>(DAT_00719a40), reinterpret_cast<LPCWSTR>(0xb9));
    window_class.hCursor =
        LoadCursorW(static_cast<HINSTANCE>(DAT_00719a40), reinterpret_cast<LPCWSTR>(0xae));
    window_class.hbrBackground = nullptr;
    window_class.lpszMenuName = nullptr;
    window_class.lpszClassName = L"GAME";
    window_class.hIconSm = nullptr;
    RegisterClassExW(&window_class);
    dat_00719a3c = CreateWindowExW(0, L"GAME", L"Shaiya XD", window_style, left, top, window_width,
                                   window_height, nullptr, nullptr,
                                   static_cast<HINSTANCE>(DAT_00719a40), nullptr);
}

/**
 * Create the main window with Unicode APIs for locale mode three and ANSI APIs otherwise.
 * @param window_style Win32 style passed to the selected window creator.
 * @param left Outer-window left coordinate in screen pixels.
 * @param top Outer-window top coordinate in screen pixels.
 * @param window_width Outer-window width in pixels.
 * @param window_height Outer-window height in pixels.
 * Copies the resulting dat_00719a3c handle into dat_0224ea44. Original entry: 0x40a9d0.
 */
extern "C" void __cdecl create_game_window_for_locale(uint32_t window_style, int32_t left,
                                                      int32_t top, int32_t window_width,
                                                      int32_t window_height) {
    if (dat_00708598 == 3)
        create_game_window_unicode(window_style, left, top, window_width, window_height);
    else
        create_game_window_ansi(window_style, left, top, window_width, window_height);
    dat_0224ea44 = dat_00719a3c;
}
/**
 * Unregister the Unicode GAME class for the stored application instance.
 * The Win32 result is ignored, as in original entry 0x40cf20.
 */
extern "C" void __cdecl unregister_game_window_class_unicode() {
    UnregisterClassW(L"GAME", static_cast<HINSTANCE>(DAT_00719a40));
}
/**
 * Unregister the main window class using the API selected by locale mode.
 * Locale mode three uses Unicode; all others use ANSI. Original entry: 0x40a7d0.
 */
extern "C" void __cdecl unregister_game_window_class_for_locale() {
    if (dat_00708598 == 3)
        unregister_game_window_class_unicode();
    else
        UnregisterClassA("GAME", static_cast<HINSTANCE>(DAT_00719a40));
}

/**
 * Send the two-byte 0x2605 packet used when application activation resumes.
 * Preserves the original 0x2000-byte stack buffer and two-byte send length.
 * No response or send result is inspected. Original entry: 0x59c5e0.
 */
extern "C" void __cdecl send_activation_packet_2605() {
    uint8_t packet[0x2000];
    packet[0] = 0x05;
    packet[1] = 0x26;
    fun_00597f60(packet, 2);
}

/**
 * Dispatch main-window messages after the recovered input/UI preprocessor.
 * @param window Window receiving the message.
 * @param message Win32 message identifier.
 * @param wparam Message-specific word argument, passed unchanged to default handling.
 * @param lparam Message-specific long argument; WM_SIZE uses its unsigned 16-bit halves.
 * @return Zero for consumed messages, otherwise the selected default procedure's result.
 * Updates activation, sizing and quit state, moves the auxiliary window, and sends
 * the activation packet when its cooldown permits. Child pointers are reloaded
 * after Win32 calls in the original order. System-command comparisons retain
 * their low hit-test bits. This callback uses stdcall RET16. Original entry: 0x40a080.
 */
extern "C" LRESULT __attribute__((stdcall)) game_window_procedure(HWND window, UINT message,
                                                                  WPARAM wparam, LPARAM lparam) {
    if (FUN_00535bc0(dat_02203adc, window, message, wparam, lparam) == 0)
        return 0;
    const uint32_t raw_lparam = uint32_t(lparam);
    switch (message) {
    case WM_CREATE:
        SetCursor(nullptr);
        return 0;
    case WM_DESTROY: {
        auto* session = dat_0223f100;
        dat_00719a5c = 0;
        if (session != nullptr)
            write_unaligned_uint32(session, 4, 1);
        PostQuitMessage(0);
        return 0;
    }
    case WM_SIZE:
        dat_007085a8 = int32_t(raw_lparam >> 16);
        dat_007085a4 = int32_t(raw_lparam & 0xffffu);
        return 0;
    case WM_CLOSE:
        DestroyWindow(window);
        return 0;
    case WM_ACTIVATEAPP: {
        dat_00719a48 = uint32_t(wparam);
        if (dat_00708598 == 4 && wparam != 0) {
            void* child = checked_auxiliary_window_child();
            if (child != nullptr &&
                *reinterpret_cast<const unsigned char*>(reinterpret_cast<uintptr_t>(child) +
                                                        kVisibilityFlagOffset) != 0)
                ShowWindow(reinterpret_cast<HWND>(read_x86_pointer(child, kOuterWindowOffset)),
                           SW_SHOW);
        }
        if (dat_0085cfbc != 0 && dat_00719a48 != 0 && dat_007085c0 == 0.0f) {
            send_activation_packet_2605();
            dat_007085c0 = 60.0f;
        }
        return 0;
    }
    case WM_WINDOWPOSCHANGING: {
        if (dat_00708598 != 4 || checked_auxiliary_window_child() == nullptr || DAT_00719a44 != 0)
            return 0;
        RECT game_rect, content_rect, outer_rect;
        const auto get_rect = &GetWindowRect;
        get_rect(dat_00719a3c, &game_rect);
        get_rect(reinterpret_cast<HWND>(
                     read_x86_pointer(auxiliary_window_child(), kContentWindowOffset)),
                 &content_rect);
        const int32_t width = subtract_wrapped(content_rect.right, content_rect.left);
        const int32_t height = subtract_wrapped(content_rect.bottom, content_rect.top);
        get_rect(
            reinterpret_cast<HWND>(read_x86_pointer(auxiliary_window_child(), kOuterWindowOffset)),
            &outer_rect);
        // Reload the opaque child after API calls, as the original does.
        void* child = auxiliary_window_child();
        if (int32_t(read_unaligned_uint32(child, kPreviousGameLeftOffset)) != game_rect.left ||
            int32_t(read_unaligned_uint32(child, kPreviousGameTopOffset)) != game_rect.top) {
            child = auxiliary_window_child();
            const int32_t x = add_wrapped(
                subtract_wrapped(outer_rect.left,
                                 int32_t(read_unaligned_uint32(child, kPreviousGameLeftOffset))),
                game_rect.left);
            const int32_t y = add_wrapped(
                subtract_wrapped(outer_rect.top,
                                 int32_t(read_unaligned_uint32(child, kPreviousGameTopOffset))),
                game_rect.top);
            MoveWindow(reinterpret_cast<HWND>(read_x86_pointer(child, kOuterWindowOffset)), x, y,
                       width, height, TRUE);
        }
        write_unaligned_uint32(auxiliary_window_child(), kPreviousGameLeftOffset,
                               uint32_t(game_rect.left));
        write_unaligned_uint32(auxiliary_window_child(), kPreviousGameTopOffset,
                               uint32_t(game_rect.top));
        return 0;
    }
    case WM_COMMAND:
        return 0;
    case WM_SYSCOMMAND:
        // Preserve the low hit-test bits: the original compares the complete
        // command, rather than applying the usual 0xfff0 command mask.
        if (wparam == (SC_MOUSEMENU | HTSYSMENU))
            return 0;
        if (wparam == SC_RESTORE || wparam == (SC_MOVE | HTCAPTION) || wparam == SC_PREVWINDOW ||
            wparam == SC_MINIMIZE || wparam == SC_MAXIMIZE)
            dat_00719a60 = 1;
        break;
    case WM_CAPTURECHANGED:
        dat_00719a60 = 1;
        return DefWindowProcW(window, message, wparam, lparam);
    }
    if (dat_00708598 == 3)
        return DefWindowProcW(window, message, wparam, lparam);
    return DefWindowProcA(window, message, wparam, lparam);
}
