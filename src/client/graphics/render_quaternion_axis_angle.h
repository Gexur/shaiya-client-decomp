#pragma once
#include <stdint.h>
extern "C" {
// Original logical operation has optional axis/angle outputs. The normalized
// return exposes actual residual EAX for instruction-derived caller checks.
uint32_t __attribute__((stdcall)) FUN_005e6725(const void*, void*, float*);
uint32_t __attribute__((stdcall)) FUN_005e6738(const void*, void*, float*);
}
