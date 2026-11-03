#pragma once
#include <stdint.h>
extern "C" {
// Exactly the original constructor-observed prefix through the DWORD at+1624.
// This does not assign invented types or semantics to untouched bytes.
extern unsigned char dat_02209408[0x1628];
extern void* dat_0085f1f0;
void* __attribute__((thiscall)) FUN_005435d0(void*);
uint32_t __attribute__((thiscall)) FUN_00543870(void*);
void fun_006b6e60();
void fun_006b9c40();
}
