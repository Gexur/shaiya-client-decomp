#pragma once
#include <stdint.h>
extern "C" {
// These are address-only declarations for the original dispatch ABI. All
// incoming words are preserved without a speculative geometry parameter type.
void __attribute__((stdcall)) FUN_005e7611(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                                           uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                                           uint32_t);
void __attribute__((stdcall)) FUN_005e7624(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                                           uint32_t, uint32_t, uint32_t);
}
