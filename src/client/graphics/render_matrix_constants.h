#pragma once
#include <stdint.h>
extern "C" {
// Normalize the three original float stack slots to their exact DWORD bits;
// these routines copy those bits without performing floating arithmetic on them.
void* __attribute__((stdcall)) FUN_005e56c1(void*, uint32_t x_bits, uint32_t y_bits,
                                            uint32_t z_bits);
void* __attribute__((stdcall)) FUN_005e5755(void*, uint32_t x_bits, uint32_t y_bits,
                                            uint32_t z_bits);
}
