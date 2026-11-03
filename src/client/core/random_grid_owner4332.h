#pragma once
#include <stdint.h>
#include <stddef.h>
// The original initializer writes this exact span: three leading DWORDs
// followed by two interleaved-in-time 27 by 20 arrays of floats.
struct OriginalRandomGrid4332 {
    uint32_t word_00;
    uint32_t word_04;
    uint32_t word_08;
    float plane[2][27][20];
};
static_assert(offsetof(OriginalRandomGrid4332, plane) == 12);
static_assert(sizeof(OriginalRandomGrid4332) == 0x10ec);
extern "C" {
uint32_t __attribute__((thiscall)) FUN_0054f9a0(OriginalRandomGrid4332*);
OriginalRandomGrid4332* __attribute__((thiscall)) FUN_0054fb80(OriginalRandomGrid4332*);
extern OriginalRandomGrid4332 dat_0085f260;
void fun_006b5d00();
void fun_006b82e0();
}
