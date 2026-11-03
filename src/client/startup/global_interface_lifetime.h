#pragma once
#include <stdint.h>
using OriginalInterfaceDeleting = void*(__attribute__((thiscall)) *)(void*, uint32_t);
extern "C" {
extern const OriginalInterfaceDeleting dat_006cd2a8[1];
// Only this actual4-byte global prefix is accessed by the recovered callbacks;
// no larger object layout or constructor is inferred from it.
extern const OriginalInterfaceDeleting* dat_0070c0ac;
void* __attribute__((thiscall)) FUN_00584d30(void*, uint32_t flags);
void fun_006b7670();
void fun_006ba730();
}
