#include "graphics/render_plane_normalize_sse2.h"
#include "graphics/render_simd_norm.h"
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
    V r;
    __asm__ volatile("rsqrtss %1,%0" : "=x"(r) : "x"(a));
    return r;
}
SIMD bool above_threshold(V a) {
    unsigned char r;
    __asm__ volatile("comiss %2,%1\n\tsetae %0"
                     : "=qm"(r)
                     : "x"(a), "m"(*reinterpret_cast<const B4*>(dat_006f3970))
                     : "cc", "memory");
    return r != 0;
}
SIMD void store(uint32_t p, V v) {
    __asm__ volatile("movss %1,%0" : "=m"(*reinterpret_cast<B4*>(p)) : "x"(v) : "memory");
}
void zero(uint32_t p) {
    __asm__ volatile("movl $0,(%0)" ::"r"(p) : "memory");
}
} // namespace
extern "C" __attribute__((target("sse"))) void*
recovered_sse2_plane_normalize(const uint32_t* arguments) {
    const uint32_t input = word(arguments + 1);
    const V x = load(input), y = load(input + 4), z = load(input + 8);
    const V xx = mul(x, x), yy = mul(y, y), zz = mul(z, z);
    const V xy = add(xx, yy), norm = add(xy, zz);
    const uint32_t output = word(arguments);
    if (!above_threshold(norm)) {
        zero(output);
        zero(output + 4);
        zero(output + 8);
        zero(output + 12);
    } else {
        const V guess = root_guess(norm);
        const V scaled_guess = mul(guess, norm);
        const V correction_product = mul(scaled_guess, guess);
        const V three = load(reinterpret_cast<uint32_t>(dat_006f3950));
        const V half_guess = mul(guess, load(reinterpret_cast<uint32_t>(dat_006f3960)));
        const V correction = sub(three, correction_product);
        const V factor = mul(correction, half_guess);
        const V nx = mul(x, factor), ny = mul(y, factor), nz = mul(z, factor);
        const V nw = mul(
            factor, load(input + 12)); // fourth input is read only after the threshold/refinement
        store(output, nx);
        store(output + 4, ny);
        store(output + 8, nz);
        store(output + 12, nw);
    }
    return reinterpret_cast<void*>(word(arguments)); // actual late reload after all stores
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall)) FUN_006837da(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse2_plane_normalize\n\taddl $4,%esp\n\tretl $8");
}
