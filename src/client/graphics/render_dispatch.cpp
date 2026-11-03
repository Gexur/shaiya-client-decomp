#include "graphics/render_dispatch.h"
extern "C" int32_t __attribute__((stdcall)) FUN_005fd1f8(int32_t);

extern "C" float* __attribute__((stdcall)) FUN_005e40d8(float* output, const float* input) {
    FUN_005fd1f8(1);
    return reinterpret_cast<NormalizeDispatch_0070f38c>(dat_0070f370.entries[7])(output, input);
}
extern "C" float* __attribute__((stdcall)) FUN_005e40eb(float* output, const float* input) {
    return reinterpret_cast<NormalizeDispatch_0070f38c>(dat_0070f370.entries[7])(output, input);
}
extern "C" D3DMATRIX* __attribute__((stdcall)) FUN_005e52cb(D3DMATRIX* output, float* determinant,
                                                            const D3DMATRIX* input) {
    FUN_005fd1f8(1);
    return reinterpret_cast<InverseDispatch_0070f3bc>(dat_0070f370.entries[19])(output, determinant,
                                                                                input);
}
extern "C" D3DMATRIX* __attribute__((stdcall)) FUN_005e52de(D3DMATRIX* output, float* determinant,
                                                            const D3DMATRIX* input) {
    return reinterpret_cast<InverseDispatch_0070f3bc>(dat_0070f370.entries[19])(output, determinant,
                                                                                input);
}
