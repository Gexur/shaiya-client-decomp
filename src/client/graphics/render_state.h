#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>

// Prefix only: original fields at+0,+4,+50 and the camera pointer at+54. No complete class
// identity or interpretation of the untouched bytes is inferred.
struct RenderStatePrefix_005ad720 {
    void* field_000;
    void* field_004;
    unsigned char unknown_008[0x48];
    void* field_050;
    void* field_054; // Original444430 stores the address of camera state0220e060.
};
static_assert(sizeof(RenderStatePrefix_005ad720) == 0x58);
static_assert(__builtin_offsetof(RenderStatePrefix_005ad720, field_050) == 0x50);
static_assert(__builtin_offsetof(RenderStatePrefix_005ad720, field_054) == 0x54);
extern "C" {
extern float dat_007085b4;
extern uint32_t dat_0070c83c, dat_0224e3f8;
extern uint8_t dat_0070ca53;
extern RenderStatePrefix_005ad720 dat_0224e3a0;
__declspec(dllexport) void __attribute__((thiscall)) FUN_00541bf0(void*);
__declspec(dllexport) void __attribute__((thiscall)) FUN_00541c40(void*);
__declspec(dllexport) void __attribute__((thiscall)) FUN_00542400(void*);
__declspec(dllexport) void __attribute__((thiscall)) FUN_005424d0(void*);
__declspec(dllexport) void __attribute__((thiscall)) FUN_005425f0(void*);
__declspec(dllexport) void* __cdecl FUN_005ad720();
__declspec(dllexport) uint32_t __attribute__((thiscall)) FUN_005ad770(void*, void*);
__declspec(dllexport) void __cdecl FUN_006ba7c0();
}
