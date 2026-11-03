#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>
#include "startup/application.h"

struct FontDescription_005e8da9 {
    int32_t height;
    uint32_t width, weight, mip_levels, italic;
    uint8_t charset, output_precision, quality, pitch_family;
    char face[32];
};
static_assert(sizeof(FontDescription_005e8da9) == 0x38);
static_assert(__builtin_offsetof(FontDescription_005e8da9, face) == 0x18);
extern "C" {
__declspec(dllexport) int32_t __attribute__((thiscall)) FUN_00544620(void*);
__declspec(dllexport) int32_t __attribute__((thiscall)) FUN_005416b0(void*);
__declspec(dllexport) int32_t __attribute__((thiscall)) FUN_00541490(void*);
__declspec(dllexport) void* __attribute__((thiscall)) FUN_00541f30(void*);
__declspec(dllexport) int32_t __cdecl FUN_0054bdf0(void**, void**, int32_t, uint32_t, const char*);
__declspec(dllexport) shaiya::startup::String_00405710* __attribute__((thiscall))
FUN_00405800(shaiya::startup::String_00405710*, const char*);
__declspec(dllexport) uint32_t __attribute__((thiscall))
FUN_00529db0(shaiya::startup::String_00405710*);
__declspec(dllexport) HRESULT __attribute__((stdcall)) FUN_005e8da9(void*, int32_t, uint32_t,
                                                                    uint32_t, uint32_t, uint32_t,
                                                                    uint32_t, uint32_t, uint32_t,
                                                                    uint32_t, const char*, void**);
}
