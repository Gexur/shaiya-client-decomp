#pragma once
#include <stdint.h>
using OriginalModuleArrayDeleting = void*(__attribute__((thiscall)) *)(void*, uint32_t);
extern "C" {
extern const OriginalModuleArrayDeleting dat_006c977c[1];
void* __attribute__((thiscall)) FUN_00548bc0(void*);
void __attribute__((thiscall)) FUN_00548c00(void*);
void* __attribute__((thiscall)) FUN_00548c10(void*);
void __attribute__((thiscall)) FUN_00434d20(void*);
void __attribute__((thiscall)) FUN_00434cc0(void*);
void __attribute__((thiscall)) FUN_00549710(void*);
void* __attribute__((thiscall)) FUN_00549780(void*, uint32_t);
}
