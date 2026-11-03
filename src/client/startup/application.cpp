#include "startup/application.h"
#include "core/string.h"
#include "startup/timing.h"
#include "config/initialization.hpp"
#include "platform/support.hpp"
#include "ui/constructors.hpp"
#include "graphics/native_renderer.h"
#include "graphics/native_animation_timing.h"

#include <shlobj.h>
#include <mmsystem.h>

using shaiya::config::dat_00708598;
using shaiya::config::DAT_0070859c;
using shaiya::config::DAT_007085a0;
using shaiya::config::DAT_007191e0;
using shaiya::config::DAT_007198b0;
using shaiya::config::DAT_00719a40;
using shaiya::config::DAT_00719a44;
using shaiya::config::FUN_005cd489;
using shaiya::config::initialize_client_configuration;
using shaiya::startup::Pair_0040abc0;
using shaiya::startup::String_00405710;
using shaiya::ui::FUN_005cc96d;

extern "C" {
// Global data definitions are in application_storage.cpp.

// Actual unresolved object storage; only their addresses are passed here. No
// object size, constructor or replacement vtable is fabricated.
extern unsigned char dat_0071cff0[];
extern unsigned char dat_02209408[];

// Actual client/CRT dependencies, with observed argument cleanup and ECX/ST0
// contracts. In particular 0x405840 is RET4 and returns its value in x87 ST0.
uint32_t __cdecl FUN_005c08d0(uint8_t);
uint32_t __attribute__((thiscall)) FUN_005c0ee0(Pair_0040abc0*, const String_00405710*);
uint32_t __attribute__((thiscall)) read_profile_string(Pair_0040abc0*, const String_00405710*,
                                                       String_00405710*, const String_00405710*);
void __cdecl FUN_005cc620(void*);
char* __cdecl FUN_005ce160(char*, const char*);
[[noreturn]] void __cdecl FUN_005ce120(int32_t);
int32_t __cdecl FUN_005cdf60(const char*, const char*, uint32_t);
int32_t __cdecl FUN_005cdf2a(const char*);
int32_t __cdecl FUN_005cdee4(const char*, int32_t);
int32_t __cdecl FUN_005cdeb6(const char*, const char*);
int32_t __cdecl FUN_005cd26b(const char*, const char*, ...);
void __cdecl FUN_005cdac0(uint32_t);
void __cdecl load_sah_archive_index();
void __attribute__((thiscall)) FUN_0040bb10(void*, const char*);
void* __attribute__((thiscall)) FUN_0041f570(void*);
void __cdecl destroy_archive_index();
const char* __cdecl FUN_0041d4a0(uint32_t);
const wchar_t* __cdecl FUN_0054bd80(const char*);
int32_t __cdecl classify_startup_physical_memory();
void __cdecl detect_windows_nt_platform();
int32_t __cdecl ensure_startup_timing_marker();
void __cdecl create_game_window_for_locale(uint32_t, int32_t, int32_t, int32_t, int32_t);
int32_t __cdecl FUN_0040b2d0();
void __cdecl FUN_0040aa20();
void __cdecl unregister_game_window_class_for_locale();
long double __attribute__((stdcall)) FUN_00405840(int32_t);
int32_t __attribute__((thiscall)) FUN_00543a00(void*);
int32_t __cdecl FUN_0042caf0();
void __cdecl FUN_005c0790();
}

namespace {
// The original updater requests the Windows XP PROCESS_ALL_ACCESS value.
// Modern SDKs add access bits, so retaining its numeric mask is intentional.
constexpr DWORD kLegacyProcessAllAccess = 0x001f0fff;

/**
 * Zero exactly @p byte_count bytes without assuming a typed object layout.
 * @param destination Writable storage; may be null only when byte_count is zero.
 * @param byte_count Number of consecutive bytes to clear.
 */
void clear_bytes(void* destination, uint32_t byte_count) {
    auto* next_byte = static_cast<unsigned char*>(destination);
    while (byte_count-- != 0)
        *next_byte++ = 0;
}
/**
 * Copy a C string including its terminator using the original unbounded loop.
 * @param destination Storage large enough for all source bytes and the terminator.
 * @param source Null-terminated source string; no overlap handling is added.
 */
void copy_null_terminated_string(char* destination, const char* source) {
    char next_character;
    do {
        next_character = *source++;
        *destination++ = next_character;
    } while (next_character != 0);
}
/**
 * Count the non-null bytes preceding a C string's terminator.
 * @param text Readable, null-terminated byte string.
 * @return Its byte length, excluding the terminator.
 */
uint32_t null_terminated_string_length(const char* text) {
    uint32_t byte_count = 0;
    while (text[byte_count] != 0)
        ++byte_count;
    return byte_count;
}
/**
 * Compare a fixed byte prefix without stopping at null characters.
 * @param left First readable byte range.
 * @param right Second readable byte range.
 * @param byte_count Number of bytes to compare, including terminators when requested.
 * @return True when all requested bytes match.
 */
bool equal_byte_prefix(const char* left, const char* right, uint32_t byte_count) {
    while (byte_count-- != 0)
        if (*left++ != *right++)
            return false;
    return true;
}
/**
 * Set the evidenced size, capacity and inline terminator of an empty client string.
 * @param value String storage to initialize; owned heap storage must first be released.
 * @note Other storage bytes and the unknown leading DWORD are left untouched.
 */
void initialize_empty_string(String_00405710& value) {
    value.capacity_018 = 15;
    value.size_014 = 0;
    value.storage_004[0] = 0;
}
/**
 * Resolve writable character storage from the client's small-string representation.
 * @param value Initialized client string with either inline bytes or a four-byte pointer.
 * @return Inline storage for capacity below sixteen, otherwise the stored x86 pointer.
 */
char* mutable_string_data(String_00405710& value) {
    if (value.capacity_018 < 16)
        return reinterpret_cast<char*>(value.storage_004);
    const auto* pointer_bytes = value.storage_004;
    const uint32_t pointer = uint32_t(pointer_bytes[0]) | uint32_t(pointer_bytes[1]) << 8 |
                             uint32_t(pointer_bytes[2]) << 16 | uint32_t(pointer_bytes[3]) << 24;
    return reinterpret_cast<char*>(pointer);
}
/**
 * Free a client string's heap storage when its capacity selects the heap representation.
 * @param value Initialized string whose storage may be released once.
 * @note The string's fields are not reset; callers retain the original reset order.
 */
void release_string_storage(String_00405710& value) {
    if (value.capacity_018 >= 16)
        FUN_005cc620(mutable_string_data(value));
}
/**
 * Display a localized startup error using the current locale's ANSI or Unicode API.
 * @param use_window Whether the main game window owns the message box.
 * @param caption Null-terminated byte caption passed to the locale converter when needed.
 * @param message_id Localization table entry to resolve for the message body.
 * @param flags Win32 MessageBox flags passed unchanged to the selected API.
 * @note Unicode caption conversion precedes body conversion despite their shared storage.
 */
void show_localized_error(bool use_window, const char* caption, uint32_t message_id, UINT flags) {
    if (dat_00708598 == 3) {
        // Conversion order matters: the real converter returns shared storage.
        const wchar_t* wide_caption = FUN_0054bd80(caption);
        const char* text = FUN_0041d4a0(message_id);
        const wchar_t* wide_text = FUN_0054bd80(text);
        MessageBoxW(use_window ? dat_00719a3c : nullptr, wide_text, wide_caption, flags);
    } else {
        const char* text = FUN_0041d4a0(message_id);
        MessageBoxA(use_window ? dat_00719a3c : nullptr, text, caption, flags);
    }
}
/**
 * Format localized updater error 0x2748 and display an unowned ANSI message box.
 * @param destination Writable formatting buffer large enough for the original CRT formatter.
 * @param format Format containing the localized text placeholder and retry-stage suffix.
 */
void show_updater_error(char* destination, const char* format) {
    const char* message = FUN_0041d4a0(0x2748);
    FUN_005cd489(destination, format, message);
    MessageBoxA(nullptr, destination, nullptr, MB_OK);
}
/** @return The low 32 bits of @p left + @p right, preserving signed x86 wraparound. */
int32_t add_wrapped(int32_t left, int32_t right) {
    return static_cast<int32_t>(uint32_t(left) + uint32_t(right));
}
/** @return The low 32 bits of @p left - @p right, preserving signed x86 wraparound. */
int32_t subtract_wrapped(int32_t left, int32_t right) {
    return static_cast<int32_t>(uint32_t(left) - uint32_t(right));
}

/**
 * Replace Updater.exe with new_updater.exe and attempt to start the replacement.
 * @param format_buffer Writable 2048-byte startup scratch buffer for localized errors.
 * @param startup_info Receives the cleared and initialized CreateProcess startup fields.
 * @param process_info Receives process information if CreateProcessA succeeds.
 * @param find_window ANSI window lookup used to wait for or terminate updater dialogs.
 * Performs the original retry loops, process termination, deletion and rename in order.
 * Stage failures display e01 through e04 and return without launching the updater;
 * the final CreateProcessA result and returned process handles are left as originally handled.
 */
void replace_updater(char* format_buffer, STARTUPINFOA& startup_info,
                     PROCESS_INFORMATION& process_info, decltype(&FindWindowA) find_window) {
    destroy_archive_index();
    int32_t retry_count = 0;
    int32_t updater_access_result = FUN_005cdee4("new_updater.exe", 0);
    const auto sleep = &Sleep;
    while (updater_access_result == -1) {
        if (++retry_count > 10) {
            show_updater_error(format_buffer, "%s e01");
            return;
        }
        sleep(1000);
        updater_access_result = FUN_005cdee4("new_updater.exe", 0);
    }
    retry_count = 0;
    HWND updater_window = find_window("#32770", "Shaiya Updater");
    while (updater_window != nullptr) {
        if (++retry_count > 10)
            break;
        sleep(1000);
        updater_window = find_window("#32770", "Shaiya Updater");
    }
    if (find_window("#32770", "Shaiya Updater") != nullptr) {
        updater_window = find_window("#32770", "Shaiya Updater");
        while (updater_window != nullptr) {
            updater_window = find_window("#32770", "Shaiya Updater");
            DWORD process_id;
            GetWindowThreadProcessId(updater_window, &process_id);
            HANDLE process_handle = OpenProcess(kLegacyProcessAllAccess, FALSE, process_id);
            TerminateProcess(process_handle, 0);
            CloseHandle(process_handle);
            updater_window = find_window("#32770", "Shaiya Updater");
        }
        sleep(1000);
        retry_count = 0;
        updater_window = find_window("#32770", "Shaiya Updater");
        while (updater_window != nullptr) {
            if (++retry_count > 10) {
                show_updater_error(format_buffer, "%s e02");
                return;
            }
            sleep(1000);
            updater_window = find_window("#32770", "Shaiya Updater");
        }
    }
    const auto delete_file = &DeleteFileA;
    retry_count = 0;
    BOOL updater_deleted = delete_file("Updater.exe");
    while (updater_deleted == FALSE) {
        if (++retry_count > 10) {
            show_updater_error(format_buffer, "%s e03");
            return;
        }
        sleep(1000);
        updater_deleted = delete_file("Updater.exe");
    }
    retry_count = 0;
    int32_t rename_result = FUN_005cdeb6("new_updater.exe", "Updater.exe");
    while (rename_result != 0) {
        if (++retry_count > 10) {
            show_updater_error(format_buffer, "%s e04");
            return;
        }
        sleep(1000);
        rename_result = FUN_005cdeb6("new_updater.exe", "Updater.exe");
    }
    sleep(500);
    clear_bytes(&startup_info, 0x44);
    startup_info.cb = 0x44;
    CreateProcessA(nullptr, const_cast<char*>("Updater.exe "), nullptr, nullptr, TRUE, 0, nullptr,
                   nullptr, &startup_info, &process_info);
    return;
}

} // namespace

/**
 * Initialize the configuration file and section strings in caller-owned storage.
 * @param profile_context Non-null storage for the recovered two-string profile context.
 * @return The same context pointer, following the original thiscall constructor ABI.
 * Only the evidenced empty-string fields are written. Original entry: 0x40abc0.
 */
extern "C" Pair_0040abc0* __attribute__((thiscall))
initialize_profile_context(Pair_0040abc0* profile_context) {
    initialize_empty_string(profile_context->first_000);
    initialize_empty_string(profile_context->second_01c);
    return profile_context;
}
/**
 * Release the profile context's section string, then its file string, and reset both.
 * @param profile_context Non-null initialized profile context; its enclosing storage is not freed.
 * Uses the original CRT free boundary and preserves field-reset order.
 * Original entry: 0x4c1760; the object pointer is passed in ECX.
 */
extern "C" void __attribute__((thiscall)) destroy_profile_context(Pair_0040abc0* profile_context) {
    release_string_storage(profile_context->second_01c);
    initialize_empty_string(profile_context->second_01c);
    release_string_storage(profile_context->first_000);
    profile_context->first_000.size_014 = 0;
    profile_context->first_000.capacity_018 = 15;
    profile_context->first_000.storage_004[0] = 0;
}

/**
 * Run the recovered EP5.4 WinMain startup, updater handoff, frame loop and shutdown.
 * @param instance Application module stored for window/resource creation.
 * @param previous_instance Unused legacy WinMain argument, preserved for the RET16 ABI.
 * @param command_line Writable ANSI argument string used by the original launch parser.
 * @param show_command Unused WinMain show argument; the original uses SW_SHOWDEFAULT.
 * @return Zero after startup rejection, updater launch, or normal frame-loop termination.
 * Selects locale-specific configuration, checks resources and memory, creates the
 * main window, updates frame timing, and executes the original shutdown sequence.
 * Retry counts, unbounded token copies, aliased scan destinations, unchecked API
 * results and uninitialized legacy fields intentionally retain their original behavior.
 * The original entry 0x40bdd0 uses stack alignment/probing and stdcall RET16 without
 * a local SEH frame; unrecovered callees retain their external exception boundaries.
 */
extern "C" int32_t __attribute__((stdcall)) run_client_application(HINSTANCE instance,
                                                                   HINSTANCE previous_instance,
                                                                   char* command_line,
                                                                   int32_t show_command) {
    (void)previous_instance;
    (void)show_command;
    char path_buffer[264];
    char desktop_path[264];
    char working_buffer[4096];
    char command_tokens[5][4096];
    char format_buffer[2048];
    STARTUPINFOA startup_info;
    PROCESS_INFORMATION process_info;

    FUN_005c08d0(1);
    if (dat_00708598 == 5) {
        clear_bytes(dat_00719a18, 0x23);
        clear_bytes(dat_007199f4, 0x23);
        clear_bytes(dat_007192f4, 0x23);
        clear_bytes(working_buffer, 4096);
        copy_null_terminated_string(working_buffer, command_line);
        clear_bytes(command_tokens, 0x5000);
        char* token = FUN_005ce160(working_buffer, " ");
        uint32_t token_count = 0;
        while (token != nullptr) {
            copy_null_terminated_string(command_tokens[token_count], token);
            token = FUN_005ce160(nullptr, " ");
            ++token_count;
        }
        if (token_count >= 4) {
            copy_null_terminated_string(dat_00719a18, command_tokens[2]);
            copy_null_terminated_string(dat_007199f4, command_tokens[3]);
            copy_null_terminated_string(dat_007192f4, command_tokens[4]);
        } else {
            Pair_0040abc0 config_strings;
            String_00405710 config_key, config_value;
            initialize_profile_context(&config_strings);
            initialize_empty_string(config_key);
            FUN_00405710(&config_key, "CONFIG.INI", 10);
            FUN_005c0ee0(&config_strings, &config_key);
            release_string_storage(config_key);
            initialize_empty_string(config_key);
            FUN_00405710(&config_key, "LOGIN", 5);
            FUN_00405620(&config_strings.second_01c, &config_key, 0, 0xffffffffu);
            release_string_storage(config_key);
            initialize_empty_string(config_value);
            initialize_empty_string(config_key);
            FUN_00405710(&config_key, "INTERNAL_TEST_IP", 16);
            const uint8_t has_internal_test_ip = uint8_t(
                read_profile_string(&config_strings, &config_key, &config_value, &dat_007085c4));
            release_string_storage(config_key);
            if (has_internal_test_ip == 0)
                FUN_005ce120(0);
            if (equal_byte_prefix(mutable_string_data(config_value), "TAIWAN", 7))
                MessageBoxA(nullptr, "INTERNAL TEST VERSION", "TAIWAN", MB_OK);
            release_string_storage(config_value);
            initialize_empty_string(config_value);
            destroy_profile_context(&config_strings);
        }
    }

    if (dat_00708598 == 1 &&
        SHGetSpecialFolderPathA(nullptr, desktop_path, CSIDL_DESKTOPDIRECTORY, FALSE)) {
        clear_bytes(path_buffer, 0x104);
        int32_t index = int32_t(null_terminated_string_length(desktop_path)) - 1;
        while (index >= 0 && desktop_path[index] != '\\')
            --index;
        copy_null_terminated_string(path_buffer, desktop_path + index + 1);
        if (FUN_005cdf60(path_buffer, "\xd7\xc0\xc3\xe6", 4) == 0) {
            MessageBoxA(nullptr, "Korea Version", "Error!!!", MB_OK);
            return 0;
        }
    }

    const auto delete_file_initial = &DeleteFileA;
    if (dat_00708598 == 4) {
        clear_bytes(working_buffer, 0x800);
        GetCurrentDirectoryA(0x800, working_buffer);
        const char* const remove_files[] = {"%s\\Data\\Item\\Item.SData",
                                            "%s\\Data\\Npc\\NpcQuest.SData",
                                            "%s\\Server\\SequenceItemCreate.ini",
                                            "%s\\Server\\ItemDataExport_UNICODE.txt",
                                            "%s\\Server\\GuildHouse.ini",
                                            "%s\\Server\\Version.txt",
                                            "%s\\Server.zip"};
        for (const char* format : remove_files) {
            FUN_005cd489(format_buffer, format, working_buffer);
            delete_file_initial(format_buffer);
        }
        const char* const remove_directories[] = {"%s\\Server", "%s\\Data\\Item", "%s\\Data\\Npc",
                                                  "%s\\Data"};
        for (const char* format : remove_directories) {
            FUN_005cd489(format_buffer, format, working_buffer);
            FUN_005cdf2a(format_buffer);
        }
    }
    load_sah_archive_index();
    FUN_0040bb10(dat_0071cff0, "data/filter.txt");
    void* startup_object_storage = FUN_005cc96d(0x4c);
    dat_007191d8 =
        startup_object_storage != nullptr ? FUN_0041f570(startup_object_storage) : nullptr;

    char mutex_name[20] = {};
    if (dat_0224e9d4 >= 5)
        copy_null_terminated_string(mutex_name, "Global\\");
    copy_null_terminated_string(mutex_name + null_terminated_string_length(mutex_name), "Shaiya");
    CreateMutexA(nullptr, FALSE, mutex_name);
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        destroy_archive_index();
        MessageBoxA(nullptr, FUN_0041d4a0(0x2746), "ERROR!!!", MB_ICONWARNING);
        PostQuitMessage(0);
        return 0;
    }
    const auto find_window = &FindWindowA;
    if (find_window("GAME", "Shaiya") != nullptr) {
        MessageBoxA(nullptr, FUN_0041d4a0(0x2746), "ERROR!", MB_ICONWARNING);
        PostQuitMessage(0);
        return 0;
    }

    if (FUN_005cdf60(command_line, "new updater", 11) == 0) {
        replace_updater(format_buffer, startup_info, process_info, find_window);
        return 0;
    }
    if (FUN_005cdf60(command_line, "start game", 10) != 0) {
        destroy_archive_index();
        clear_bytes(&startup_info, 0x44);
        startup_info.cb = 0x44;
        if (dat_00708598 == 5 && null_terminated_string_length(dat_00719a18) != 0) {
            FUN_005cd489(format_buffer, "Updater.exe %s %s %s", dat_00719a18, dat_007199f4,
                         dat_007192f4);
            CreateProcessA(nullptr, format_buffer, nullptr, nullptr, TRUE, 0, nullptr, nullptr,
                           &startup_info, &process_info);
        } else {
            CreateProcessA(nullptr, const_cast<char*>("Updater.exe"), nullptr, nullptr, TRUE, 0,
                           nullptr, nullptr, &startup_info, &process_info);
        }
        return 0;
    }
    if (FUN_0040a040("ijl15.dll") != 0x5b000) {
        show_localized_error(false, "nProtect GameGuard", 0x2736, MB_OK);
        return 0;
    }
    initialize_client_configuration();
    if (dat_00708598 == 2) {
        if (GetPrivateProfileStringA("LOGIN", "TEST_IP", "", path_buffer, 0x104, DAT_007191e0) ==
            0) {
            // The first two destinations intentionally alias in the original.
            FUN_005cd26b(command_line, "%s %s %s", &startup_info, &startup_info, DAT_007198b0);
        } else if (GetPrivateProfileStringA("LOGIN", "INTERNAL_TEST_IP", "", path_buffer, 0x104,
                                            DAT_007191e0) != 0 &&
                   equal_byte_prefix(path_buffer, "CHINA", 6)) {
            copy_null_terminated_string(DAT_007198b0, "172.17.10.210");
        }
    }
    if (classify_startup_physical_memory() == 0) {
        show_localized_error(true, "ERROR!!!", 0x2736, MB_ICONERROR);
        return 0;
    }
    detect_windows_nt_platform();
    if (dat_00708598 == 2) {
        clear_bytes(format_buffer, 0x400);
        HKEY opened_key = nullptr, created_key = nullptr;
        GetCurrentDirectoryA(0x400, format_buffer);
        if (RegOpenKeyExA(HKEY_LOCAL_MACHINE, "SOFTWARE\\SONOV\\Shaiya", 0, KEY_ALL_ACCESS,
                          &opened_key) == ERROR_SUCCESS) {
            DWORD value_type = 0;
            DWORD value_bytes; // Original passes this private stack word uninitialized.
            RegQueryValueExA(opened_key, "path", nullptr, &value_type,
                             reinterpret_cast<BYTE*>(format_buffer), &value_bytes);
            if (null_terminated_string_length(format_buffer) == 0 && opened_key != nullptr)
                RegSetValueExA(opened_key, "path", 0, REG_SZ,
                               reinterpret_cast<BYTE*>(format_buffer),
                               null_terminated_string_length(format_buffer));
        } else {
            RegCreateKeyA(HKEY_LOCAL_MACHINE, "SOFTWARE\\SONOV\\Shaiya", &created_key);
            RegSetValueA(created_key, "path", REG_SZ, format_buffer,
                         null_terminated_string_length(format_buffer));
            RegSetValueExA(created_key, "path", 0, REG_SZ, reinterpret_cast<BYTE*>(format_buffer),
                           null_terminated_string_length(format_buffer));
            RegCloseKey(created_key);
        }
        if (opened_key != nullptr)
            RegCloseKey(opened_key);
    }
    if (ensure_startup_timing_marker() == 0)
        return 0;
    dat_007085a4 = DAT_0070859c;
    dat_007085ac = DAT_0070859c;
    dat_007085a8 = DAT_007085a0;
    dat_007085b0 = DAT_007085a0;
    DAT_00719a40 = instance;
    int32_t left = 0, top = 0, width = DAT_0070859c, height = DAT_007085a0;
    uint32_t style;
    if (DAT_00719a44 == 0) {
        style = WS_VISIBLE | WS_OVERLAPPEDWINDOW;
        const int32_t screen_width = GetSystemMetrics(SM_CXSCREEN);
        left = subtract_wrapped(screen_width / 2, DAT_0070859c / 2);
        const int32_t screen_height = GetSystemMetrics(SM_CYSCREEN);
        top = subtract_wrapped(screen_height / 2, DAT_007085a0 / 2);
        const int32_t half_caption_height = GetSystemMetrics(SM_CYCAPTION) / 2;
        top = subtract_wrapped(top, half_caption_height);
        const int32_t frame_width = GetSystemMetrics(SM_CXFRAME);
        width = add_wrapped(DAT_0070859c, add_wrapped(frame_width, frame_width));
        const int32_t frame_height = GetSystemMetrics(SM_CYFRAME);
        const int32_t caption_height = GetSystemMetrics(SM_CYCAPTION);
        height = add_wrapped(add_wrapped(caption_height, DAT_007085a0),
                             add_wrapped(frame_height, frame_height));
        if (left < 0) {
            left = 0;
            width = GetSystemMetrics(SM_CXSCREEN);
        }
        if (top < 0) {
            top = 0;
            height = GetSystemMetrics(SM_CYSCREEN);
        }
    } else {
        style = WS_POPUP | WS_VISIBLE;
    }
    create_game_window_for_locale(style, left, top, width, height);
    FUN_005cdac0(timeGetTime());
    if (FUN_0040b2d0() == 0) {
        FUN_0040aa20();
        unregister_game_window_class_for_locale();
        return 0;
    }
    ShowWindow(dat_00719a3c, SW_SHOWDEFAULT);
    UpdateWindow(dat_00719a3c);
    SetFocus(dat_00719a3c);
    (void)FUN_00405840(1);
    SetCursor(nullptr);
    dat_007199ec = FUN_0040cf40;
    if (dat_00708598 != 3)
        dat_007199ec = FUN_00409ff0;
    for (;;) {
        while (dat_007199ec() != 0) {
        }
        dat_00719a50 = static_cast<float>(FUN_00405840(5));
        volatile float& frame_delta = dat_00719a54;
        if (dat_00719a60 != 0) {
            frame_delta = static_cast<float>(FUN_00405840(1));
            dat_00719a60 = 0;
        }
        const long double elapsed_seconds = FUN_00405840(6);
        frame_delta = static_cast<float>(elapsed_seconds);
        if (elapsed_seconds <= 0.0L)
            frame_delta = 0.05f;
        if ((dat_00708598 == 2 || dat_00708598 == 5 || dat_00708598 == 9) && frame_delta > 1.0f)
            frame_delta = 0.1f;
        native_world_animation_begin_frame(frame_delta);
        const long double activation_cooldown_remaining =
            static_cast<long double>(dat_007085c0) - static_cast<long double>(frame_delta);
        dat_007085c0 = static_cast<float>(activation_cooldown_remaining);
        if (activation_cooldown_remaining < 0.0L)
            dat_007085c0 = 0.0f;
        if (dat_02209400 != nullptr && (dat_02209400->device_removed || dat_00719a4c != 0)) {
            if (FUN_00543a00(dat_02209408) == 0)
                break;
            dat_00719a4c = 0;
            continue;
        }
        if (refresh_startup_tick() == 0)
            break;
        if (dat_00719a68 == 0 && FUN_0042caf0() == 0)
            break;
    }
    FUN_0040aa20();
    unregister_game_window_class_for_locale();
    destroy_archive_index();
    FUN_005c0790();
    WinExec("Ending.exe", SW_SHOW);
    return 0;
}
