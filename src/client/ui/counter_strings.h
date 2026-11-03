#pragma once
#include <stdint.h>
extern "C" {
int32_t FUN_00531a80(uint32_t, const uint16_t*, int32_t, char*, int32_t);
int32_t __attribute__((thiscall)) FUN_00532bc0(void*, char*, int32_t);
uint32_t __attribute__((thiscall)) FUN_00532dc0(void*);
uint32_t __attribute__((thiscall)) FUN_00532eb0(void*);
int32_t recovered_00531a80(const uint32_t* original_arguments);
int32_t recovered_00532bc0(void*, const uint32_t* original_arguments);
}
