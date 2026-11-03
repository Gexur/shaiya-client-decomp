#pragma once
#include <stdint.h>
extern "C" {
using DebugMuteCodeAddress = void(__cdecl*)();
extern DebugMuteCodeAddress dat_0224f358, dat_0224f354;
extern int32_t dat_0070f5c0;
extern const char dat_006de95c[9], dat_006de940[10], dat_006de94c[13], dat_006de930[14];
// Original callers ignore the result. The entry adapter separately retains
// residual physical EAX, including cache-skip paths that inherit incoming EAX.
void __attribute__((stdcall)) FUN_005e9b1d(uint32_t);
}
