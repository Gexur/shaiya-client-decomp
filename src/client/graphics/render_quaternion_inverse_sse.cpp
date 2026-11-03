#include "graphics/render_quaternion_inverse_sse.h"
extern "C" {
alignas(16) uint32_t dat_00717540[4] = {0xbf800000u, 0xbf800000u, 0xbf800000u, 0x3f800000u};
}
namespace {
using V = float __attribute__((vector_size(16)));
struct B8 {
    unsigned char b[8];
};
struct B16 {
    unsigned char b[16];
};
#define SIMD __attribute__((target("sse"), always_inline)) inline
uint32_t word(const uint32_t* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
SIMD V load(uint32_t p) {
    V v{};
    __asm__ volatile("movlps %1,%0" : "+x"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    __asm__ volatile("movhps %1,%0"
                     : "+x"(v)
                     : "m"(*reinterpret_cast<const B8*>(p + 8))
                     : "memory");
    return v;
}
SIMD V aligned(uint32_t p) {
    V v;
    __asm__ volatile("movaps %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SIMD V mul(V a, V b) {
    __asm__ volatile("mulps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V add(V a, V b) {
    __asm__ volatile("addps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V mul_low(V a, V b) {
    __asm__ volatile("mulss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V add_low(V a, V b) {
    __asm__ volatile("addss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V sub_low(V a, V b) {
    __asm__ volatile("subss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V high_to_low(V a, V b) {
    __asm__ volatile("movhlps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
template <int mask> SIMD V shuffle(V a, V b) {
    __asm__ volatile("shufps %2,%1,%0" : "+x"(a) : "x"(b), "i"(mask));
    return a;
}
SIMD V reciprocal(V a) {
    V r;
    __asm__ volatile("rcpss %1,%0" : "=x"(r) : "x"(a));
    return r;
}
SIMD V replace_low(V a, V b) {
    __asm__ volatile("movss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD void store(uint32_t p, V v) {
    __asm__ volatile("movups %1,%0" : "=m"(*reinterpret_cast<B16*>(p)) : "x"(v) : "memory");
}
} // namespace
extern "C" __attribute__((target("sse"))) void*
recovered_sse_quaternion_inverse(const uint32_t* arguments) {
    const uint32_t input = word(arguments + 1); // 680171
    const V vector = load(input); // both input halves overwrite original unused private vector
    const uint32_t output = word(arguments); // 68017f, cached through output store
    const V squares = mul(vector, vector);
    const V upper = high_to_low(squares, squares);
    const V paired = add(squares, upper); // all four lanes execute, including two doubled squares
    const V second = shuffle<0x55>(paired, paired);
    const V norm = add_low(paired, second);
    const V estimate = reciprocal(norm); // real RCPSS; no host divide or zero branch
    const V private_value =
        replace_low(norm, estimate); // exact original private store/low overwrite/load
    const V first_product = mul_low(private_value, norm);
    const V twice = add_low(private_value, private_value);
    const V correction = mul_low(first_product, private_value);
    const V refined = sub_low(twice, correction);
    const V factor = shuffle<0>(refined, refined);
    const V signs = aligned(reinterpret_cast<uint32_t>(dat_00717540));
    const V conjugated = mul(vector, signs);
    const V result = mul(conjugated, factor);
    store(output, result);
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall)) FUN_0068015f(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_quaternion_inverse\n\taddl $4,%esp\n\tretl $8");
}
