#pragma once
#include <stdint.h>
extern "C" {
// Original543d30 receives eight DWORD stack arguments and returns RET32.
uint32_t __attribute__((thiscall)) FUN_00543d30(void*, uint32_t, uint32_t, uint32_t, uint32_t,
                                                uint32_t, uint32_t, int32_t, char*);
uint32_t recovered_00543d30(void*, uint32_t* original_argument_words);
}
