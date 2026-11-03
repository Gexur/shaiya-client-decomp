#include "graphics/render_matrix_reflect_sse.h"
#include "graphics/render_simd_norm.h"
#include "startup/math_dispatch_state.h"
extern "C" {
alignas(16) uint32_t dat_007175e0[24] = {0xffffffffu, 0xffffffffu, 0xffffffffu, 0x0u, 0xc0000000u,
                                         0xc0000000u, 0xc0000000u, 0x0u,        0x0u, 0x0u,
                                         0x0u,        0x3f800000u, 0x0u,        0x0u, 0x3f800000u,
                                         0x0u,        0x0u,        0x3f800000u, 0x0u, 0x0u,
                                         0x3f800000u, 0x0u,        0x0u,        0x0u};
}
namespace {
using V = float __attribute__((vector_size(16)));
struct B4 {
    unsigned char b[4];
};
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
SIMD V scalar(uint32_t p) {
    V v;
    __asm__ volatile("movss %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B4*>(p)) : "memory");
    return v;
}
SIMD V load(uint32_t p) {
    V v{};
    __asm__ volatile("movhps %1,%0"
                     : "+x"(v)
                     : "m"(*reinterpret_cast<const B8*>(p + 8))
                     : "memory");
    __asm__ volatile("movlps %1,%0" : "+x"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
SIMD V aligned(uint32_t p) {
    V v;
    __asm__ volatile("movaps %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SIMD V high_to_low(V a, V b) {
    __asm__ volatile("movhlps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
template <int mask> SIMD V shuffle(V a, V b) {
    __asm__ volatile("shufps %2,%1,%0" : "+x"(a) : "x"(b), "i"(mask));
    return a;
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
SIMD V root_guess(V a) {
    __asm__ volatile("rsqrtss %0,%0" : "+x"(a));
    return a;
}
SIMD V and_bits(V a, V b) {
    __asm__ volatile("andps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD void store(uint32_t p, V a) {
    __asm__ volatile("movups %1,%0" : "=m"(*reinterpret_cast<B16*>(p)) : "x"(a) : "memory");
}
} // namespace
extern "C" __attribute__((target("sse"))) void*
recovered_sse_matrix_reflect(const uint32_t* arguments) {
    const uint32_t input = word(arguments + 1), output = word(arguments);
    const V plane = load(input); // original high8 before low8, both before arithmetic
    const V mask = aligned(reinterpret_cast<uint32_t>(dat_007175e0));
    const V masked = and_bits(mask, plane);
    const V squares = mul(masked, masked);
    const V three = scalar(reinterpret_cast<uint32_t>(dat_006f3920));
    const V half = scalar(reinterpret_cast<uint32_t>(dat_006f3930));
    const V upper = high_to_low(squares, squares);
    const V paired = add(squares, upper);
    const V other = shuffle<1>(paired, paired);
    const V length = add_low(paired, other);
    const V scale = aligned(reinterpret_cast<uint32_t>(dat_007175e0 + 4));
    const V guess = root_guess(length);
    const V product = mul_low(length, guess);
    const V second_product = mul_low(product, guess);
    const V correction = sub_low(three, second_product);
    const V half_guess = mul_low(half, guess);
    const V factor_low = mul_low(half_guess, correction);
    const V factor = shuffle<0>(factor_low, factor_low);
    const V normal = mul(plane, factor);
    const V scaled = mul(scale, normal);
    const V x = shuffle<0>(normal, normal);
    const V x_product = mul(x, scaled);
    const V row_zero = add(x_product, aligned(reinterpret_cast<uint32_t>(dat_007175e0 + 20)));
    const V w = shuffle<0xff>(normal, normal);
    const V w_product = mul(w, scaled);
    const V row_three = add(w_product, aligned(reinterpret_cast<uint32_t>(dat_007175e0 + 8)));
    const V z = shuffle<0xaa>(normal, normal);
    const V z_product = mul(z, scaled);
    const V row_two = add(z_product, aligned(reinterpret_cast<uint32_t>(dat_007175e0 + 12)));
    const V y = shuffle<0x55>(normal, normal);
    const V y_product = mul(scaled, y); // original operand order differs from other three rows
    const V row_one = add(y_product, aligned(reinterpret_cast<uint32_t>(dat_007175e0 + 16)));
    store(output, row_zero);
    store(output + 16, row_one);
    store(output + 32, row_two);
    store(output + 48, row_three);
    return reinterpret_cast<void*>(output); // original cached EAX, no final argument reload
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall)) FUN_00681259(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_matrix_reflect\n\taddl $4,%esp\n\tretl $8");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6712(void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmp _FUN_005e671f@8");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e671f(void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+116");
}
