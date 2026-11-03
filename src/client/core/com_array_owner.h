#pragma once
#include <stdint.h>
// Opaque original owners expose only binary-proven byte offsets; this API
// does not invent a full class layout/size from gaps between global symbols.
extern "C" {
void* __attribute__((thiscall)) FUN_005b0c30(void*);
void __attribute__((thiscall)) FUN_005b00e0(void*);
void __attribute__((thiscall)) FUN_005b0d10(void*);
void __attribute__((thiscall)) FUN_005b15a0(void*);
void __attribute__((thiscall)) FUN_005b2870(void*);
}
