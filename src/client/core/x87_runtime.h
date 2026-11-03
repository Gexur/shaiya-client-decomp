#pragma once
#include <stdint.h>
static_assert(sizeof(void*) == 4, "Original x87 ABI requires x86");
static_assert(sizeof(long double) >= 10, "Original extended-precision values require x87 storage");
extern "C" {
extern uint32_t dat_022532cc;
// Actual hardware entry contracts:5cd414 consumes ST0, returns EDX:EAX;
// 5d0630 consumes base ST1/exponent ST0 and returns its result in ST0.
uint64_t __cdecl FUN_005cd414();
void __cdecl FUN_005d0630();
// Source integration adapters, not additional original procedures.
uint64_t __cdecl x87_to_integer_005cd414(long double);
long double __cdecl x87_power_005d0630(long double base, long double exponent);
}
