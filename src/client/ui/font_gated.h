#pragma once
#include <stdint.h>
extern "C" {
// Original541930 is cdecl variadic with eight fixed stack DWORDs.
uint32_t FUN_00541930(void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                      const char*, ...);
uint32_t recovered_00541930(uint32_t* original_argument_words);
}
