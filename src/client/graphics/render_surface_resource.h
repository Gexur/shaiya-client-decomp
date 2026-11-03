#pragma once
#include <stdint.h>
extern "C" {
// Only original offsets and the original 0x54-byte allocation are recovered;
// no complete C++ class layout is inferred from them.
void* __attribute__((thiscall)) FUN_00602c51(void*);
int32_t __attribute__((thiscall)) FUN_0060269a(void*, void*, uint32_t, uint32_t, uint32_t, uint32_t,
                                               uint32_t);
uint32_t __attribute__((stdcall)) FUN_00602b70(void*);
uint32_t __attribute__((thiscall)) FUN_00602be4(void*);
void* __attribute__((thiscall)) FUN_005e8bdf(void*, uint32_t);
int32_t __attribute__((stdcall)) FUN_005e8d2b(void*, uint32_t, uint32_t, uint32_t, uint32_t,
                                              uint32_t, void**);
int32_t __attribute__((stdcall)) FUN_00602c08(void*, const void*, void**);
uint32_t __attribute__((stdcall)) FUN_00620553(void*);
uint32_t __attribute__((stdcall)) FUN_00602c78(void*);
int32_t __attribute__((stdcall)) FUN_006026eb(void*, void**);
int32_t __attribute__((stdcall)) FUN_00602715(void*, void*);
uint32_t __attribute__((stdcall)) FUN_0063830d(void*);
// Two original table targets remain unresolved, with their actual RET12/RET8.
int32_t __attribute__((stdcall)) FUN_0060273d(void*, uint32_t, uint32_t);
int32_t __attribute__((stdcall)) FUN_006029f3(void*, uint32_t);
using OriginalCodeAddress_006df9f4 = void (*)();
extern const OriginalCodeAddress_006df9f4 dat_006df9f4[9];
extern const uint32_t dat_006f73f8[4], dat_006effd4[4];
}
