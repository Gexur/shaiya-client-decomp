#pragma once
#include <stdint.h>
extern "C" {
// Original four raw words; last word is the actual constructor code address.
uint32_t __attribute__((stdcall)) FUN_00405c90(void*, uint32_t, uint32_t, uint32_t);
int32_t __attribute__((thiscall)) FUN_005f2032(void*, void*);
}
