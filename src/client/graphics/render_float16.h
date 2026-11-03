#pragma once
#include <stdint.h>
// Original array loops operate on raw DWORD/WORD storage, not host half types.
extern "C" {
void* __attribute__((stdcall)) FUN_005e3c36(void*, const void*, uint32_t);
void* __attribute__((stdcall)) FUN_005e3cf1(void*, const void*, uint32_t);
}
