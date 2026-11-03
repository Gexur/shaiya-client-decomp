#pragma once
#include <stdint.h>
extern "C" {
// Actual F32 argument is promoted to an outgoing double for original floor;
// returned physical80-bit ST0 is retained, with stdcall RET4.
long double __attribute__((stdcall)) FUN_005ec9e8(uint32_t);
void* __attribute__((stdcall)) FUN_005eca09(uint32_t, uint32_t, uint32_t);
}
