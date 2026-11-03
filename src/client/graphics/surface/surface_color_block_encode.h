#pragma once
#include <stdint.h>
extern "C" {
// Actual custom ABI: EAX=16 RGBA records; three actual stack DWORDs below.
// Use an explicit assembly call. Callee pops12; EAX=0 and NVs preserved.
uint32_t __attribute__((stdcall)) FUN_00650120(void* output, uint32_t alpha_mode, uint32_t dither);
extern const uint32_t dat_006f00e8[4];
extern const uint32_t dat_006f00f8[3];
extern const uint32_t dat_006f0104;
extern uint32_t dat_00716920[3];
}
