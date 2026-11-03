#include "graphics/render_simd_norm.h"
#include "graphics/render_simd_constants.h"

namespace {
using ScalarVector = float __attribute__((vector_size(16)));
#define SSE_INLINE __attribute__((target("sse"), always_inline)) inline
SSE_INLINE ScalarVector load(const float* source) {
    ScalarVector value;
    __asm__ __volatile__("movss %1,%0" : "=x"(value) : "m"(*source));
    return value;
}
SSE_INLINE void store(float* destination, ScalarVector value) {
    __asm__ __volatile__("movss %1,%0" : "=m"(*destination) : "x"(value));
}
SSE_INLINE ScalarVector mul(ScalarVector left, ScalarVector right) {
    __asm__ __volatile__("mulss %1,%0" : "+x"(left) : "x"(right));
    return left;
}
SSE_INLINE ScalarVector add(ScalarVector left, ScalarVector right) {
    __asm__ __volatile__("addss %1,%0" : "+x"(left) : "x"(right));
    return left;
}
SSE_INLINE ScalarVector sub(ScalarVector left, ScalarVector right) {
    __asm__ __volatile__("subss %1,%0" : "+x"(left) : "x"(right));
    return left;
}
SSE_INLINE ScalarVector reciprocal_root(ScalarVector value) {
    ScalarVector result;
    __asm__ __volatile__("rsqrtss %1,%0" : "=x"(result) : "x"(value));
    return result;
}
SSE_INLINE bool above_equal(ScalarVector value, const float* threshold) {
    bool result;
    __asm__ __volatile__("comiss %2,%1" : "=@ccae"(result) : "x"(value), "m"(*threshold) : "cc");
    return result;
}
SSE_INLINE float* normalize(float* output, const float* input, const float* three,
                            const float* half, const float* threshold) {
    const ScalarVector x = load(input), y = load(input + 1), z = load(input + 2);
    const ScalarVector squared = add(add(mul(x, x), mul(y, y)), mul(z, z));
    if (!above_equal(squared, threshold)) {
        output[0] = 0;
        output[1] = 0;
        output[2] = 0;
        return output;
    }
    const ScalarVector reciprocal = reciprocal_root(squared);
    const ScalarVector correction = mul(mul(reciprocal, squared), reciprocal);
    const ScalarVector scaled = mul(reciprocal, load(half));
    const ScalarVector factor = mul(sub(load(three), correction), scaled);
    // Original captures all three inputs before its first output store.
    const ScalarVector nx = mul(x, factor), ny = mul(y, factor), nz = mul(z, factor);
    store(output, nx);
    store(output + 1, ny);
    store(output + 2, nz);
    return output;
}
} // namespace

extern "C" __attribute__((target("sse"))) float* __attribute__((stdcall))
FUN_006805d6(float* output, const float* input) {
    return normalize(output, input, dat_006f3920, dat_006f3930, dat_006f3940);
}
extern "C" __attribute__((target("sse"))) float* __attribute__((stdcall))
FUN_00683746(float* output, const float* input) {
    return normalize(output, input, dat_006f3950, dat_006f3960, dat_006f3970);
}
