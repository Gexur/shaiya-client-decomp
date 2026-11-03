#pragma once
#include "core/x87_pow_private.h"
extern "C" {
extern uint32_t dat_0070ef40;
int32_t __cdecl FUN_005d8961();
int32_t __cdecl FUN_005d896c();
int32_t __cdecl FUN_005d8978(uint32_t, uint32_t);
void __cdecl FUN_005d899c(uint32_t);
uint32_t __cdecl FUN_005d8633(int32_t);
uint32_t __cdecl FUN_005dea67(uint32_t, PowerMathException*, uint16_t*);
// Actual remaining callees, not fabricated error handlers.
int32_t __cdecl FUN_005d840f(uint32_t, double*, uint32_t);
void __cdecl FUN_005d816a(void*, uint32_t*, uint32_t, uint32_t, double*, double*);
}
