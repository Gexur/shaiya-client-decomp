#pragma once
#include <stdint.h>
#include "graphics/render_quaternion_log_exp_amd.h"
#include "graphics/render_quaternion_amd.h"
#include "graphics/render_normalize_amd.h"
#include "graphics/render_interpolation_amd.h"
#include "graphics/render_3dnow_norm.h"
extern "C" {
extern const uint32_t dat_006f0188[2], dat_006f39b0[2];
void* __attribute__((stdcall)) FUN_006859de(void*, void*, void*, const void*, const void*,
                                            const void*, const void*);
}
