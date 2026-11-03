#include "graphics/render_vec4_normalize_sse.h"
#include "startup/math_dispatch_state.h"
extern "C" {
uint32_t dat_007176b0 = 0x3f000000u;
uint32_t dat_007176c0 = 0x40400000u;
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
// original instruction order retained
extern "C" __attribute__((target("sse"))) void*
recovered_sse_vec4_normalize(const uint32_t* arguments) {
    const uint32_t input = word(arguments + 1); // original instruction order retained
    const V x = load(input), y = load(input + 4), z = load(input + 8),
            w = load(input + 12);                           // cb..d9
    const V xx = mul(x, x), yy = mul(y, y), zz = mul(z, z); // ee..f6
    const V xy = add(xx, yy);                               // fa
    const V ww = mul(w, w);                                 // fe
    const V zw = add(zz, ww);                               // original instruction order retained
    const V norm = add(xy, zw);                             // original instruction order retained
    const V guess = root_guess(norm);                       // original instruction order retained
    const V square_guess = mul(guess, guess);               // original instruction order retained
    const V corrected = mul(norm, square_guess);            // original instruction order retained
    const V three =
        load(reinterpret_cast<uint32_t>(&dat_007176c0)); // original instruction order retained
    const V correction = sub(three, corrected);          // original instruction order retained
    const V half =
        load(reinterpret_cast<uint32_t>(&dat_007176b0)); // original instruction order retained
    const V half_correction = mul(correction, half);
    const V factor = mul(half_correction, guess);     // original instruction order retained
    const uint32_t output = word(arguments);          // original instruction order retained
    const V nx = mul(x, factor), ny = mul(y, factor); // original instruction order retained
    store(output, nx);                                // original instruction order retained
    const V nz = mul(z, factor);                      // original instruction order retained
    store(output + 4, ny);                            // original instruction order retained
    const V nw = mul(w, factor);                      // original instruction order retained
    store(output + 8, nz);
    store(output + 12, nw);                          // original instruction order retained
    return reinterpret_cast<void*>(word(arguments)); // original instruction order retained
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall)) FUN_00680a79(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_vec4_normalize\n\taddl $4,%esp\n\tretl $8");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e483c(void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+32");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e484f(void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+32");
}
