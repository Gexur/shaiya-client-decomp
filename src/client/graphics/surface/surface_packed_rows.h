#pragma once
#include <stdint.h>
// Original six DWORD stack operands are raw bits/addresses. Both entries RET24
// and mutate their actual incoming argument words; these are not const values.
extern "C" uint32_t __attribute__((stdcall)) FUN_005ece1f(uint32_t, uint32_t, uint32_t, uint32_t,
                                                          uint32_t, uint32_t);
extern "C" uint32_t __attribute__((stdcall)) FUN_005ecf6b(uint32_t, uint32_t, uint32_t, uint32_t,
                                                          uint32_t, uint32_t);
