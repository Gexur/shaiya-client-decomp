#include "graphics/render_quaternion_normalize_sse.h"
extern "C" {
uint32_t dat_00717520 = 0x3f000000u;
uint32_t dat_00717530 = 0x40400000u;
}
namespace {
using V = float __attribute__((vector_size(16)));
struct B4 {
    unsigned char b[4];
};
#define SIMD __attribute__((target("sse"), always_inline)) inline
uint32_t word(const uint32_t* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
SIMD V load(uint32_t p) {
    V v;
    __asm__ volatile("movss %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B4*>(p)) : "memory");
    return v;
}
SIMD V mul(V a, V b) {
    __asm__ volatile("mulss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V add(V a, V b) {
    __asm__ volatile("addss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V sub(V a, V b) {
    __asm__ volatile("subss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V root_guess(V a) {
    V result;
    __asm__ volatile("rsqrtss %1,%0" : "=x"(result) : "x"(a));
    return result;
}
SIMD void store(uint32_t p, V v) {
    __asm__ volatile("movss %1,%0" : "=m"(*reinterpret_cast<B4*>(p)) : "x"(v) : "memory");
}
} // namespace
// Complete original6800c3..68015f. No zero/threshold fallback exists in this body.
extern "C" __attribute__((target("sse"))) void*
recovered_sse_quaternion_normalize(const uint32_t* arguments) {
    const uint32_t input = word(arguments + 1); // 6800c8
    const V x = load(input), y = load(input + 4), z = load(input + 8),
            w = load(input + 12);                           // cb..d9
    const V xx = mul(x, x), yy = mul(y, y), zz = mul(z, z); // ee..f6
    const V xy = add(xx, yy);                               // fa
    const V ww = mul(w, w);                                 // fe
    const V zw = add(zz, ww);                               // 680102
    const V norm = add(xy, zw);                             // 680106
    const uint32_t output = word(arguments);                // 68010a
    const V guess = root_guess(norm);                       // 68010d; real hardware approximation
    const V square_guess = mul(guess, guess);               // 680115
    const V corrected = mul(norm, square_guess);            // 680119
    const V three = load(reinterpret_cast<uint32_t>(&dat_00717530)); // 68011d
    const V correction = sub(three, corrected);                      // 680125
    const V half = load(reinterpret_cast<uint32_t>(&dat_00717520));  // 680129
    const V half_correction = mul(correction, half);
    const V factor = mul(half_correction, guess);     // 680131
    const V nx = mul(x, factor), ny = mul(y, factor); // 680135/139
    store(output, nx);                                // 68013d
    const V nz = mul(z, factor);                      // 680141
    store(output + 4, ny);                            // 680145
    const V nw = mul(w, factor);                      // 68014a
    store(output + 8, nz);
    store(output + 12, nw);                          // 68014e/153
    return reinterpret_cast<void*>(word(arguments)); // 680158
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall)) FUN_006800c3(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_quaternion_normalize\n\taddl $4,%esp\n\tretl $8");
}
