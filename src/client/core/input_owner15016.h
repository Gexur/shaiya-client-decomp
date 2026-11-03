#pragma once
#include <stdint.h>
using OriginalInputDeleting = void*(__attribute__((thiscall)) *)(void*, uint32_t);
extern "C" {
extern const OriginalInputDeleting dat_006c58c8[1], dat_006cf228[1];
void* __attribute__((thiscall)) FUN_00557200(void*);
void __attribute__((thiscall)) FUN_005aa030(void*);
void __attribute__((thiscall)) FUN_005aa190(void*);
void __attribute__((thiscall)) FUN_005aa540(void*);
void __attribute__((thiscall)) FUN_005aa2d0(void*);
void __attribute__((thiscall)) FUN_005aa300(void*);
void* __attribute__((thiscall)) FUN_005aa390(void*);
void* __attribute__((thiscall)) FUN_005aa3d0(void*, uint32_t);
void* __attribute__((thiscall)) FUN_00535200(void*);
void __attribute__((thiscall)) FUN_005340e0(void*);
void* __attribute__((thiscall)) FUN_00531580(void*);
void __attribute__((thiscall)) FUN_005315f0(void*);
void* __attribute__((thiscall)) FUN_00531660(void*, uint32_t);
}
