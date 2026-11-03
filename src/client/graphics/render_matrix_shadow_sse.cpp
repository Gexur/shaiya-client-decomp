#include "graphics/render_matrix_shadow_sse.h"
#include "graphics/render_simd_norm.h"
#include "startup/math_dispatch_state.h"
extern "C" {
alignas(16) uint32_t dat_007176d0[20] = {0x80000000u, 0x80000000u, 0x80000000u, 0x80000000u, 0x0u,
                                         0xffffffffu, 0x0u,        0x0u,        0x0u,        0x0u,
                                         0xffffffffu, 0x0u,        0x0u,        0x0u,        0x0u,
                                         0xffffffffu, 0xffffffffu, 0xffffffffu, 0xffffffffu, 0x0u};
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
SIMD V block(uint32_t p) {
    V v;
    __asm__ volatile("movups %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SIMD V aligned(uint32_t p) {
    V v;
    __asm__ volatile("movaps %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SIMD V zero() {
    V v;
    __asm__ volatile("xorps %0,%0" : "=x"(v));
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
SIMD V root_guess(V a, V b) {
    __asm__ volatile("rsqrtss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V and_bits(V a, V b) {
    __asm__ volatile("andps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V xor_bits(V a, V b) {
    __asm__ volatile("xorps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD bool equal(V a, V b) {
    unsigned char r;
    __asm__ volatile("comiss %2,%1\n\tsete %0" : "=qm"(r) : "x"(a), "x"(b) : "cc");
    return r != 0;
}
SIMD void store_low(uint32_t p, V a) {
    __asm__ volatile("movlps %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(a) : "memory");
}
SIMD void store_high(uint32_t p, V a) {
    __asm__ volatile("movhps %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(a) : "memory");
}
} // namespace
extern "C" __attribute__((target("sse"))) void*
recovered_sse_matrix_shadow(const uint32_t* arguments, const unsigned char* incoming) {
    const V incoming_three = block(reinterpret_cast<uint32_t>(incoming));
    const V plane = block(word(arguments + 2));
    const V masked = and_bits(plane, aligned(reinterpret_cast<uint32_t>(dat_007176d0 + 16)));
    const V squares = mul(masked, masked);
    const V upper = high_to_low(incoming_three, squares);
    const V paired = add(upper, squares);
    const V other = shuffle<1>(paired, paired);
    const V length = add_low(other, paired); // original destXMM2=shuffle then adds originalXMM3
    V chosen = length, partial_for_dot = paired;
    if (!equal(length, zero())) {
        const V guess = root_guess(length, length);
        const V product = mul_low(length, guess);
        const V twice_product = mul_low(product, guess);
        const V half_guess = mul_low(guess, scalar(reinterpret_cast<uint32_t>(dat_006f3930)));
        const V correction =
            sub_low(scalar(reinterpret_cast<uint32_t>(dat_006f3920)), twice_product);
        const V factor_low = mul_low(half_guess, correction);
        const V factor = shuffle<0>(factor_low, factor_low);
        chosen = mul(factor, plane);
        partial_for_dot = correction;
    }
    const V light = block(word(arguments + 1));
    const V products = mul(light, chosen);
    const V high_products = high_to_low(partial_for_dot, products);
    const V paired_products = add(products, high_products);
    const V other_product = shuffle<1>(paired_products, paired_products);
    const V dot_low = add_low(paired_products, other_product);
    const V dot = shuffle<0>(dot_low, dot_low);
    const V signed_plane = xor_bits(chosen, aligned(reinterpret_cast<uint32_t>(dat_007176d0)));
    const V x = shuffle<0>(signed_plane, signed_plane);
    const V y = shuffle<0x55>(signed_plane, signed_plane);
    const V z = shuffle<0xaa>(signed_plane, signed_plane);
    const V w = shuffle<0xff>(signed_plane, signed_plane);
    const V x_product = mul(x, light), y_product = mul(y, light), z_product = mul(z, light),
            w_product = mul(w, light);
    const V row_zero = add_low(x_product, dot);
    const V y_diagonal = and_bits(dot, aligned(reinterpret_cast<uint32_t>(dat_007176d0 + 4)));
    const V z_diagonal = and_bits(dot, aligned(reinterpret_cast<uint32_t>(dat_007176d0 + 8)));
    const V w_diagonal = and_bits(dot, aligned(reinterpret_cast<uint32_t>(dat_007176d0 + 12)));
    const V row_one = add(y_product, y_diagonal), row_two = add(z_product, z_diagonal),
            row_three = add(w_product, w_diagonal);
    const uint32_t output = word(arguments);
    store_low(output, row_zero);
    store_high(output + 8, row_zero);
    store_low(output + 16, row_one);
    store_high(output + 24, row_one);
    store_low(output + 32, row_two);
    store_high(output + 40, row_two);
    store_low(output + 48, row_three);
    store_high(output + 56, row_three);
    return reinterpret_cast<void*>(word(arguments));
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall)) FUN_00681161(void*, const void*,
                                                                              const void*) {
    __asm__ volatile(
        "subl $16,%esp\n\tmovups %xmm3,0(%esp)\n\tmovl %esp,%edx\n\tleal 20(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_sse_matrix_shadow\n\taddl $24,%esp\n\tretl $12");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e66ff(void*, const void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmp _FUN_005e670c@12");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e670c(void*, const void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+112");
}
