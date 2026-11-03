#pragma once
#include <stdint.h>
#include "graphics/render_amd_trig_rotation.h"
#include "graphics/render_acos_amd.h"
#include "graphics/render_normalize_amd.h"
#include "graphics/render_interpolation_amd.h"
extern "C" {
extern const uint32_t dat_006f0198[2], dat_006f01a0[2], dat_006f01a8[2];
void FUN_006a7020();
void* __attribute__((stdcall)) FUN_00685892(void*, const void*);
void* __attribute__((stdcall)) FUN_00685939(void*, const void*);
}
