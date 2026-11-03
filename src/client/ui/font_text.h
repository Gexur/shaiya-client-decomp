#pragma once
#include <stdint.h>
extern "C" {
extern uint16_t dat_02208400[1024], dat_02208c00[1024];
uint32_t __attribute__((thiscall)) FUN_00541cb0(void*, const uint16_t*, uint32_t, uint32_t*,
                                                uint32_t);
uint32_t __attribute__((thiscall)) FUN_00542f70(void*, const char*, uint32_t, uint32_t*, uint32_t);
uint32_t __attribute__((thiscall)) FUN_005430a0(void*, const char*, uint32_t, uint32_t);
// Actual5418c0 is variadic. Original extra word before format is unread.
uint32_t FUN_005418c0(void*, uint32_t, uint32_t, uint32_t, uint32_t, const char*, ...);
// The four rectangle DWORDs live in the actual incoming argument backing.
uint32_t FUN_0054be30(void*, const char*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
}
