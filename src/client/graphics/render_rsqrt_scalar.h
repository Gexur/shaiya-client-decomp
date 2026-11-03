#pragma once
#include <stdint.h>

// One actual DWORD stack argument, returned as the original 80-bit ST0.
// The normalized argument type preserves every incoming float bit pattern.
extern "C" long double __attribute__((stdcall)) FUN_0064f3a4(uint32_t value_bits);
