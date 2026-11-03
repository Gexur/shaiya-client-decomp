#include "graphics/render_math.h"

// Actual normalization dispatch thunk5e40eb remains a real source dependency;
// its runtime-selected scalar/SSE/3DNow implementation is never guessed here.
extern "C" float* __attribute__((stdcall)) FUN_005e40eb(float*, const float*);

namespace {
long double extended(float value) {
    return static_cast<long double>(value);
}
long double negate(long double value) {
    // Original FCHS precedes its DWORD store. An explicit operation stops
    // LLVM from rounding first and then flipping the sign under non-nearest RC.
    __asm__ __volatile__("fchs" : "+t"(value));
    return value;
}
float cross(float a, float b, float c, float d) {
    const volatile float rounded =
        static_cast<float>(extended(a) * extended(b) - extended(c) * extended(d));
    return rounded;
}
long double dot(const volatile float* a, const float* b) {
    // Original adds y-product to x-product, then the z-product.
    return (extended(a[1]) * extended(b[1]) + extended(a[0]) * extended(b[0])) +
           extended(a[2]) * extended(b[2]);
}
} // namespace

extern "C" D3DMATRIX* __attribute__((stdcall))
FUN_005e65c3(D3DMATRIX* matrix, float fov, float aspect, float near_plane, float far_plane) {
    const volatile float half = static_cast<float>(extended(fov) * 0.5L);
    float cosine, sine;
    // Actual FSINCOS outputs cos at ST0 and sin at ST1, followed by two DWORD
    // stores. Separate library sin/cos calls would change the original behavior.
    __asm__ __volatile__("flds %2\n\tfsincos\n\tfstps %0\n\tfstps %1"
                         : "=m"(cosine), "=m"(sine)
                         : "m"(half)
                         : "st", "st(1)");
    auto* output = reinterpret_cast<float*>(matrix);
    const long double ratio = extended(cosine) / extended(sine);
    output[0] = static_cast<float>(ratio / extended(aspect));
    output[1] = 0;
    output[2] = 0;
    output[3] = 0;
    output[4] = 0;
    output[5] = static_cast<float>(ratio);
    output[6] = 0;
    output[7] = 0;
    output[8] = 0;
    output[9] = 0;
    const long double depth = extended(far_plane) / (extended(far_plane) - extended(near_plane));
    output[10] = static_cast<float>(depth);
    output[11] = 1;
    output[12] = 0;
    output[13] = 0;
    output[14] = static_cast<float>(negate(depth * extended(near_plane)));
    output[15] = 0;
    return matrix;
}

extern "C" D3DMATRIX* __attribute__((stdcall)) FUN_005e646b(D3DMATRIX* matrix,
                                                            const void* eye_pointer,
                                                            const void* target_pointer,
                                                            const void* up_pointer) {
    auto* output = reinterpret_cast<float*>(matrix);
    const auto* eye = static_cast<const float*>(eye_pointer);
    const auto* target = static_cast<const float*>(target_pointer);
    const auto* up = static_cast<const float*>(up_pointer);
    volatile float forward[3] = {static_cast<float>(extended(target[0]) - extended(eye[0])),
                                 static_cast<float>(extended(target[1]) - extended(eye[1])),
                                 static_cast<float>(extended(target[2]) - extended(eye[2]))};
    FUN_005e40eb(const_cast<float*>(forward), const_cast<float*>(forward));
    volatile float right[3] = {cross(forward[2], up[1], forward[1], up[2]),
                               cross(forward[0], up[2], forward[2], up[0]),
                               cross(forward[1], up[0], forward[0], up[1])};
    FUN_005e40eb(const_cast<float*>(right), const_cast<float*>(right));
    output[4] = right[1];
    output[8] = right[2];
    volatile float vertical[3] = {cross(forward[1], right[2], forward[2], right[1]),
                                  cross(forward[2], right[0], forward[0], right[2]),
                                  cross(forward[0], right[1], forward[1], right[0])};
    output[0] = right[0];
    const long double right_translation = dot(right, eye);
    output[1] = vertical[0];
    output[5] = vertical[1];
    output[9] = vertical[2];
    output[12] = static_cast<float>(negate(right_translation));
    const long double vertical_translation = dot(vertical, eye);
    output[2] = forward[0];
    output[6] = forward[1];
    output[10] = forward[2];
    output[13] = static_cast<float>(negate(vertical_translation));
    output[14] = static_cast<float>(negate(dot(forward, eye)));
    output[3] = 0;
    output[7] = 0;
    output[11] = 0;
    output[15] = 1;
    return matrix;
}
