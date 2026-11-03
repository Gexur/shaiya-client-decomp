#pragma once
#include <stdint.h>
#include <stddef.h>

extern "C" {
__declspec(dllexport) void* fun_005dceb0(void* destination, int32_t value, uint32_t size);
__declspec(dllexport) void* fun_005cc630(void* destination, const void* source, uint32_t size);
__declspec(dllexport) void* fun_005d8d30(void* destination, const void* source, uint32_t size);

// Standard compiler-runtime spellings delegate to the recovered implementations.
// These names are build integration wrappers, not additional original routines.
void* memset(void* destination, int value, size_t size);
void* memcpy(void* destination, const void* source, size_t size);
void* memmove(void* destination, const void* source, size_t size);
}
