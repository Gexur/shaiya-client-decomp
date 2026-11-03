#pragma once
#include <stdint.h>
extern "C" {
// Original005101f0..00510249, three cdecl DWORD arguments, RET0.
uint32_t FUN_005101f0(uint32_t, uint32_t, uint32_t);
uint32_t recovered_005101f0(const uint32_t* original_argument_words);
}
