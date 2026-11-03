#pragma once
#include <stdint.h>
using OriginalPackedRowKernel = uint32_t(__attribute__((stdcall)) *)(uint32_t, uint32_t, uint32_t,
                                                                     uint32_t, uint32_t, uint32_t);
extern "C" {
uint32_t __attribute__((thiscall)) FUN_005ecf49(void*);
uint32_t __attribute__((thiscall)) FUN_005ed1dc(void*);
uint32_t __attribute__((stdcall)) FUN_005ed171(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                                               uint32_t);
uint32_t __attribute__((stdcall)) FUN_005ed1ab(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                                               uint32_t);
extern OriginalPackedRowKernel volatile dat_0070fdf4;
extern OriginalPackedRowKernel volatile dat_0070fdf8;
}
