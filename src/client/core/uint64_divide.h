#pragma once

#include <stdint.h>

static_assert(sizeof(void*) == 4, "Original unsigned division ABI requires x86");

extern "C" {
// Original 0x5d7b70: four stack words, RET16, result in EDX:EAX.
uint64_t __attribute__((stdcall)) fun_005d7b70(uint32_t dividend_low, uint32_t dividend_high,
                                               uint32_t divisor_low, uint32_t divisor_high);

// Clang/GNU x86 compiler-runtime boundary: caller pops its two uint64 arguments.
// Delegates to the real recovered original routine, not replacement division.
uint64_t __attribute__((cdecl)) __udivdi3(uint64_t dividend, uint64_t divisor);
}
