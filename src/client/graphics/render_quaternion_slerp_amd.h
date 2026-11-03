#pragma once
#include <stdint.h>
#include "graphics/render_acos_amd.h"
#include "graphics/render_amd_trig_rotation.h"
#include "graphics/render_quaternion_log_exp_amd.h"
#include "graphics/render_interpolation_amd.h"
#include "graphics/render_normalize_amd.h"
extern "C" {
extern uint32_t dat_00717e48[1], dat_00717e4c[1], dat_00717e50[1], dat_00717e54[1], dat_00717e58[1],
    dat_00717e5c[1];
extern const uint32_t dat_006f0248[2];
// Actual MM0/MM1 input and MM0 output. Explicit assembly call only;
// the original custom entry preserves every GPR and arithmetic flag.
void FUN_006a6840();
void* __attribute__((stdcall)) FUN_006855d8(void*, const void*, const void*, uint32_t);
void* __attribute__((stdcall)) FUN_0068570f(void*, const void*, const void*, const void*, uint32_t,
                                            uint32_t);
void* __attribute__((stdcall)) FUN_0068579c(void*, const void*, const void*, const void*,
                                            const void*, uint32_t);
}
