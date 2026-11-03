#pragma once
#include <stdint.h>
extern "C" {
// Actual three-stack-DWORD stdcall ABI/RET12. Explicit asm labels satisfy the
// existing undecorated format-owner references without changing that ABI.
uint32_t __attribute__((stdcall)) FUN_00650d78(void* output, const void* rgba,
                                               uint32_t dither) __asm__("_FUN_00650d78");
uint32_t __attribute__((stdcall)) FUN_00650e9c(void* output, const void* rgba,
                                               uint32_t dither) __asm__("_FUN_00650e9c");
// Existing canonical owner startup/surface_write_argb16.cpp defines this
// scalar; its current header does not declare it. This is a declaration only.
extern const uint32_t dat_006bc894;
}
