#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>
#include "core/string.h"

namespace shaiya::graphics::native {
struct NativeRenderer;
}

namespace shaiya::startup {
struct Pair_0040abc0 {
    // Configuration file and section strings. Their observed field order is
    // shared with the original profile reader at 0x5c0de0.
    String_00405710 first_000;
    String_00405710 second_01c;
};
static_assert(sizeof(String_00405710) == 0x1c);
static_assert(__builtin_offsetof(String_00405710, storage_004) == 4);
static_assert(__builtin_offsetof(String_00405710, size_014) == 0x14);
static_assert(__builtin_offsetof(String_00405710, capacity_018) == 0x18);
static_assert(sizeof(Pair_0040abc0) == 0x38);

using MessagePump = unsigned int(__cdecl*)();
} // namespace shaiya::startup

extern "C" {
extern char dat_007192f4[0x23], dat_007199f4[0x23], dat_00719a18[0x23];
extern void* dat_007191d8;
extern shaiya::startup::MessagePump dat_007199ec;
extern HWND dat_00719a3c;
extern uint32_t dat_00719a48, dat_00719a4c, dat_00719a60, dat_00719a68;
extern float dat_00719a50, dat_00719a54, dat_007085c0;
extern int32_t dat_007085a4, dat_007085a8, dat_007085ac, dat_007085b0;
extern shaiya::startup::String_00405710 dat_007085c4;
extern uint32_t dat_0224e9d4;
extern shaiya::graphics::native::NativeRenderer* dat_02209400;

// Four original WinMain arguments; previous-instance and show arguments are
// unused where the original never reads them. This is the real RET16 routine,
// not a substitute PE entry point. Original callee exception paths are pending.
__declspec(dllexport) int32_t __attribute__((stdcall))
run_client_application(HINSTANCE instance, HINSTANCE previous_instance, char* command_line,
                       int32_t show_command);

__declspec(dllexport) shaiya::startup::Pair_0040abc0* __attribute__((thiscall))
initialize_profile_context(shaiya::startup::Pair_0040abc0* profile_context);
__declspec(dllexport) void __attribute__((thiscall))
destroy_profile_context(shaiya::startup::Pair_0040abc0* profile_context);
}
