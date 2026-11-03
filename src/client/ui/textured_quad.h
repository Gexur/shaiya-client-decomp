#pragma once
#include <stdint.h>
extern "C" {
// ECX points to the observed texture/width/height prefix. Stack operands are
// packed color and signed integer x,y; original RET12 and EAX are preserved.
uint32_t __attribute__((thiscall)) FUN_00549ff0(void*, uint32_t, uint32_t, uint32_t);
}
