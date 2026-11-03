#pragma once
#include <stdint.h>
static_assert(sizeof(void*) == 4);
extern "C" {
// Original005D90C0: RET16; quotient EDX:EAX, remainder EBX:ECX.
// Its unusual output registers are intentionally not an ordinary C++ return.
void __attribute__((stdcall)) fun_005d90c0(uint32_t, uint32_t, uint32_t, uint32_t);
// Explicit source normalization of those same four input words and two outputs.
uint64_t recovered_u64_divrem(uint32_t dividend_low, uint32_t dividend_high, uint32_t divisor_low,
                              uint32_t divisor_high, uint64_t* remainder);
}
