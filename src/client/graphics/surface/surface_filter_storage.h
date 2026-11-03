#pragma once
#include <stdint.h>
extern "C" {
// The iterator's physical EAX is count-1 on the signed-empty route, otherwise
// the last callback's EAX. Each callback has ECX=element and no stack operands.
uint32_t __attribute__((stdcall)) FUN_005e232f(void*, uint32_t, uint32_t, uintptr_t);
// Destructor role: the existing void-free boundary's physical EAX is private
// frame dependent and is not established equivalent by the finite proof.
void __attribute__((thiscall)) FUN_005eca00(void*);
void* __attribute__((thiscall)) FUN_005ef56a(void*, uint32_t);
void* __attribute__((thiscall)) FUN_005fc891(void*);
}
