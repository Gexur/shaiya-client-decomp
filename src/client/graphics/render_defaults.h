#pragma once
#include <stdint.h>

extern "C" {
// Actual hidden-this routines at541fe0 and54a4e0; both end with RET.
__declspec(dllexport) void __attribute__((thiscall)) FUN_00541fe0(void*);
__declspec(dllexport) int32_t __attribute__((thiscall)) FUN_0054a4e0(void*);
}
