#pragma once
#include "core/x87_pow_private.h"
using OriginalMathErrorCallback = int32_t(__cdecl*)(PowerMathException*);
extern "C" {
extern OriginalMathErrorCallback dat_0070ec00;
int32_t __cdecl FUN_005decbe(PowerMathException*);
void __cdecl FUN_005d7bd8(double*, double*, double*, uint32_t);
}
