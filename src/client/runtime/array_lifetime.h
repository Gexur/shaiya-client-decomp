#pragma once
#include <stdint.h>

using OriginalElementCallback = void(__attribute__((thiscall)) *)(void*);
extern "C" {
void __attribute__((stdcall)) fun_005cdc5e(void* current, uint32_t element_size, int32_t remaining,
                                           OriginalElementCallback destructor);
void __attribute__((stdcall)) fun_005cdcbc(void* first, uint32_t element_size, int32_t count,
                                           OriginalElementCallback destructor);
void __attribute__((stdcall)) fun_005ce6bb(void* first, uint32_t element_size, int32_t count,
                                           OriginalElementCallback constructor,
                                           OriginalElementCallback destructor);
}
