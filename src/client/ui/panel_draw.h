#pragma once
#include <stdint.h>

extern "C" {
// Observed ECX receivers are opaque. No unrecovered concrete class is assumed.
uint32_t __attribute__((thiscall)) FUN_00529040(void*);
uint32_t __attribute__((thiscall)) FUN_0052d390(void*);
uint32_t __attribute__((thiscall)) FUN_00528b00(void*, uint32_t, uint32_t);

// Original dependent bodies; their source closure is still pending here.
uint32_t __attribute__((thiscall)) FUN_00549ff0(void*, uint32_t, uint32_t, uint32_t);
uint32_t __attribute__((thiscall)) FUN_0052d030(void*, uint32_t, uint32_t, uint32_t, uint32_t);
uint32_t __attribute__((thiscall)) FUN_005277a0(void*);
}
