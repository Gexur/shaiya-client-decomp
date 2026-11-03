#pragma once
#include "graphics/render_math.h"
#include "graphics/render_vector.h"
#include "startup/math_dispatch_state.h"
using NormalizeDispatch_0070f38c = float*(__attribute__((stdcall)) *)(float*, const float*);
using InverseDispatch_0070f3bc = D3DMATRIX*(__attribute__((stdcall)) *)(D3DMATRIX*, float*,
                                                                        const D3DMATRIX*);
extern "C" {
// Actual slots7/19 are fields of canonical dat0070f370. They are not separately
// allocated globals: original addresses70f38c/70f3bc share this table storage.
float* __attribute__((stdcall)) FUN_005e40d8(float*, const float*);
float* __attribute__((stdcall)) FUN_005e40eb(float*, const float*);
D3DMATRIX* __attribute__((stdcall)) FUN_005e52cb(D3DMATRIX*, float*, const D3DMATRIX*);
D3DMATRIX* __attribute__((stdcall)) FUN_005e52de(D3DMATRIX*, float*, const D3DMATRIX*);
}
