#pragma once
#include <stdint.h>
extern "C" {
// Original shader owner: six COM slots, release EAX from the last loaded slot.
uint32_t __attribute__((thiscall)) FUN_00543560(void*);
// Original scalar deleting destructor: low flag byte tested after releases.
void* __attribute__((thiscall)) FUN_00543530(void*, uint32_t);
extern const uintptr_t dat_006c8398[1];
}
