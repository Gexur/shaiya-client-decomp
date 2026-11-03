#pragma once
#include <stdint.h>
extern "C" {
// Three original binary32 argument slots are explicit DWORD bits. The bridge
// calls the selected machine ABI without a mismatched C++ function pointer.
void* __attribute__((stdcall)) FUN_005e568b(void*, uint32_t, uint32_t, uint32_t);
void* __attribute__((stdcall)) FUN_005e56bb(void*, uint32_t, uint32_t, uint32_t);
}
