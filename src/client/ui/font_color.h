#pragma once
#include <stdint.h>
extern "C" {
// Original cdecl variadic541820 consumes low bytes of the three channels;
// its word before format is unused, and its format word is overwritten.
uint32_t FUN_00541820(void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                      const char*, ...);
uint32_t recovered_00541820(uint32_t* original_argument_words);
}
