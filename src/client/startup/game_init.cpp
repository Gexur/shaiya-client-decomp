#include "game_init.h"
#include "logger_format.h"
#include "application.h"
#include "../network/packets.h"
#include "../network/window_transport.h"
#include "../config/initialization.hpp"
#include "../config/development_endpoint.h"
#include "../platform/support.hpp"
#include "../ui/constructors.hpp"
#include <mmsystem.h>

using shaiya::config::DAT_0071987c;
using shaiya::config::DAT_007198b0;
using shaiya::config::DAT_00719a40;
using shaiya::config::DAT_00719a44;
using shaiya::config::DAT_022071e0;
using shaiya::startup::CallbackObject_00405cc0;
using shaiya::ui::FUN_005cc96d;

extern "C" {
CallbackObject_00405cc0* dat_007191d4 = nullptr;
void* dat_00719318 = nullptr;
void* dat_0071931c = nullptr;

// Actual opaque globals, not made-up replacement objects. The audio global's
// original identity is shared with existing config/audio recovery above.
extern unsigned char dat_0224ead0[], dat_02209408[], dat_02203678[];
int32_t __cdecl open_archive_or_loose_file(const char*, const char*);
void* __cdecl FUN_005cde20(uint32_t);
int32_t __cdecl FUN_005a26c0(int32_t);
void __attribute__((thiscall)) FUN_005c0050(void*);
uint32_t __attribute__((thiscall)) FUN_005c0110(void*, void*, uint32_t, uint32_t);
void __cdecl FUN_005cdc59(void*);
CallbackObject_00405cc0* __attribute__((thiscall)) FUN_00405cc0(void*);
void __cdecl FUN_0052ccf0(uint32_t);
int32_t __attribute__((thiscall)) FUN_00541400(void*);
int32_t __attribute__((thiscall)) FUN_00531680(void*);
int32_t __attribute__((thiscall)) FUN_00541410(void*);
int32_t __attribute__((thiscall)) FUN_00544620(void*);
void __attribute__((thiscall)) FUN_00539f40(void*);
uint32_t __attribute__((thiscall)) FUN_0053b990(void*, uint32_t, uint32_t, const char*, int32_t,
                                                uint32_t);
void* __attribute__((thiscall)) FUN_0053e530(void*);
void* __attribute__((thiscall)) FUN_0054e330(void*);
void __cdecl FUN_0040a5d0();
const char* __cdecl FUN_0041d4a0(uint32_t);
const wchar_t* __cdecl FUN_0054bd80(const char*);
}

namespace {
void copy_string(char* destination, const char* source) {
    char value;
    do {
        value = *source++;
        *destination++ = value;
    } while (value != 0);
}
uint32_t field_004(SessionPrefix* session) {
    const auto* p =
        reinterpret_cast<const unsigned char*>(reinterpret_cast<uintptr_t>(session) + 4);
    return uint32_t(p[0]) | uint32_t(p[1]) << 8 | uint32_t(p[2]) << 16 | uint32_t(p[3]) << 24;
}
void write_field_49c(SessionPrefix* session, uint32_t value) {
    auto* p = reinterpret_cast<unsigned char*>(reinterpret_cast<uintptr_t>(session) + 0x49c);
    p[0] = uint8_t(value);
    p[1] = uint8_t(value >> 8);
    p[2] = uint8_t(value >> 16);
    p[3] = uint8_t(value >> 24);
}
void error_with_caption(const char* caption, uint32_t text_id) {
    if (dat_00708598 == 3) {
        const wchar_t* wide_caption = FUN_0054bd80(caption);
        const char* text = FUN_0041d4a0(text_id);
        const wchar_t* wide_text = FUN_0054bd80(text);
        MessageBoxW(dat_00719a3c, wide_text, wide_caption, 0x10);
    } else {
        const char* text = FUN_0041d4a0(text_id);
        MessageBoxA(dat_00719a3c, text, caption, 0x10);
    }
}
void error_with_copied_caption(uint32_t caption_id, uint32_t text_id) {
    char caption[260];
    copy_string(caption, FUN_0041d4a0(caption_id));
    error_with_caption(caption, text_id);
}
void fullscreen_error() {
    const char* caption = FUN_0041d4a0(0x2750);
    if (dat_00708598 == 3) {
        const wchar_t* wide_caption = FUN_0054bd80(caption);
        const wchar_t* wide_text = FUN_0054bd80("Full Screen Error!!!");
        MessageBoxW(dat_00719a3c, wide_text, wide_caption, 0x10);
    } else {
        MessageBoxA(dat_00719a3c, "Full Screen Error!!!", caption, 0x10);
    }
}
} // namespace

// 0x40b2d0..0x40b899: actual caller behavior, including original AL tests,
// constructor EAX results, poll timeout arithmetic, audio fallback and stores.
// The original FS:[0] frame and cleanup states0/1/2 require an MSVC-compatible
// unwind recovery; this source currently validates normal-return paths only.
extern "C" int32_t __cdecl FUN_0040b2d0() {
    FUN_005b9f30(&dat_0224e6c0, 4, "****************%s****************", "GameInit");
    const int32_t descriptor = open_archive_or_loose_file("data/Config.cfg", "rb");
    if (descriptor != 0) {
        const uint32_t length = dat_00719e80->byte_length;
        void* data = FUN_005cde20(length);
        FUN_0040d020(data, 1, length, descriptor);
        FUN_005a26c0(descriptor);
        FUN_005c0050(dat_0224ead0);
        FUN_005c0110(dat_0224ead0, data, length, 0);
        if (data != nullptr)
            FUN_005cdc59(data);
    }
    fun_004014f0();
    if (uint8_t(fun_0059fa90(dat_00719a3c, static_cast<HINSTANCE>(DAT_00719a40))) != 0) {
        error_with_caption("ERROR!!!", 0x274a);
        return 0;
    }
    FUN_005b9f30(&dat_0224e6c0, 4, "****************%s Init Network****************", "GameInit");
    void* allocated = FUN_005cc96d(0x19f8);
    dat_007191d4 = allocated != nullptr ? FUN_00405cc0(allocated) : nullptr;
    fun_0058d4b0(dat_007191d4);
    const uint8_t enabled = uint8_t(dat_007191d4->callbacks->callback_004(dat_007191d4, 0x34));
    FUN_0052ccf0(enabled != 0);
    allocated = FUN_005cc96d(0x4a0);
    dat_0223f100 = allocated != nullptr ? reinterpret_cast<SessionPrefix*>(
                                              fun_0040b0d0(static_cast<SessionStorage*>(allocated)))
                                        : nullptr;
    fun_0058d4c0(dat_0223f100);
    // Explicit development policy; the original connection/handshake still runs.
    shaiya_apply_development_login_host(DAT_007198b0, sizeof(DAT_007198b0));
    if (fun_0058d3f0(DAT_007198b0, 0x7850) != 0) {
        error_with_copied_caption(0x274c, 0x274b);
        return 0;
    }
    FUN_005b9f30(&dat_0224e6c0, 4, "****************%s Connect****************", "GameInit");
    dat_0223f100->state = 0;
    const auto get_time = &timeGetTime;
    const DWORD start = get_time();
    const auto peek_message = &PeekMessageA;
    const auto get_message = &GetMessageA;
    for (;;) {
        MSG message;
        if (peek_message(&message, nullptr, 0, 0, 0) != FALSE &&
            get_message(&message, nullptr, 0, 0) != FALSE) {
            TranslateMessage(&message);
            DispatchMessageA(&message);
        }
        auto* current = dat_0223f100;
        if (field_004(current) != 0)
            return 0;
        if (current->state != 0)
            break;
        if (DWORD(get_time() - start) > 30000u) {
            error_with_caption("ERROR!!!", 0x274d);
            return 0;
        }
    }
    FUN_005b9f30(&dat_0224e6c0, 4, "****************%s Connect OK****************", "GameInit");
    if (FUN_00541400(dat_02209408) == 0) {
        error_with_caption("ERROR!!!", 0x274e);
        return 0;
    }
    if (FUN_00531680(dat_02203678) == 0) {
        error_with_caption("ERROR!!!", 0x274f);
        return 0;
    }
    if (DAT_00719a44 != 0 && FUN_00541410(dat_02209408) == 0) {
        fullscreen_error();
        return 0;
    }
    if (FUN_00544620(dat_02209408) == 0) {
        DAT_0071987c = 0;
        if (FUN_00544620(dat_02209408) == 0) {
            error_with_copied_caption(0x2751, 0x2750);
            return 0;
        }
    }
    FUN_00539f40(DAT_022071e0);
    FUN_0053b990(DAT_022071e0, 0, 0x1e, "ui_button001.wav", 5, 1);
    FUN_0053b990(DAT_022071e0, 0, 0x20, "ui_window.wav", 5, 1);
    allocated = FUN_005cc96d(0x308);
    dat_0071931c = allocated != nullptr ? FUN_0053e530(allocated) : nullptr;
    allocated = FUN_005cc96d(0x94);
    dat_00719318 = allocated != nullptr ? FUN_0054e330(allocated) : nullptr;
    FUN_0040a5d0();
    write_field_49c(dat_0223f100, 1);
    FUN_005b9f30(&dat_0224e6c0, 4, "****************%s End****************", "GameInit");
    return 1;
}
