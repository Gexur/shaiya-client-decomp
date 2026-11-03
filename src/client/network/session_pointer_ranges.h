#pragma once
#include <stdint.h>
extern "C" {
// Original DWORD pointer-range helpers. Stack words are deliberately retained
// as raw DWORDs; each entry adapter passes their actual addresses to C++.
__attribute__((stdcall)) uint32_t fun_004ce990(uint32_t output, uint32_t count,
                                               uint32_t value_pointer);
uint32_t fun_0048cad0(uint32_t first, uint32_t last, uint32_t value_pointer);
__attribute__((stdcall)) uint32_t fun_00585260(uint32_t first, uint32_t last, uint32_t output);
uint32_t fun_004ce760(uint32_t first, uint32_t last, uint32_t output_end);
}
