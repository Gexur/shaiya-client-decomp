#include "graphics/render_plane_points_sse2.h"
#include "graphics/render_simd_norm.h"
extern "C" {
alignas(16) uint32_t dat_00717800[4] = {0x80000000u, 0x80000000u, 0x80000000u, 0x80000000u};
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
SIMD V aligned(uint32_t p) {
    V v;
    __asm__ volatile("movaps %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SIMD V high(V a, uint32_t p) {
    __asm__ volatile("movhps %1,%0" : "+x"(a) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
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
SIMD V mul(V a, V b) {
    __asm__ volatile("mulps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V add(V a, V b) {
    __asm__ volatile("addps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V sub(V a, V b) {
    __asm__ volatile("subps %1,%0" : "+x"(a) : "x"(b));
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
SIMD V xor_bits(V a, V b) {
    __asm__ volatile("xorps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD void store_block(uint32_t p, V a) {
    __asm__ volatile("movups %1,%0" : "=m"(*reinterpret_cast<B16*>(p)) : "x"(a) : "memory");
}
SIMD void store_low(uint32_t p, V a) {
    __asm__ volatile("movss %1,%0" : "=m"(*reinterpret_cast<B4*>(p)) : "x"(a) : "memory");
}
} // namespace
extern "C" __attribute__((target("sse"))) void*
recovered_sse2_plane_points(const uint32_t* arguments) {
    const uint32_t first_pointer = word(arguments + 1), third_pointer = word(arguments + 3);
    const V first_z = scalar(first_pointer + 8), third_z = scalar(third_pointer + 8);
    const V first = high(first_z, first_pointer), third = high(third_z, third_pointer);
    const uint32_t second_pointer = word(arguments + 2), output = word(arguments);
    const V second_z = scalar(second_pointer + 8), second = high(second_z, second_pointer);
    const V first_minus_third = sub(first, third);
    const V first_rotated = shuffle<0x78>(first_minus_third, first_minus_third);
    const V first_alternate = shuffle<0x63>(first_minus_third, first_minus_third);
    const V first_minus_second = sub(first, second);
    const V three = aligned(reinterpret_cast<uint32_t>(dat_006f3950));
    const V second_alternate = shuffle<0x63>(first_minus_second, first_minus_second);
    const V second_rotated = shuffle<0x78>(first_minus_second, first_minus_second);
    const V left_product = mul(first_rotated, second_alternate);
    const V right_product = mul(second_rotated, first_alternate);
    const V half = aligned(reinterpret_cast<uint32_t>(dat_006f3960));
    const V cross = sub(left_product, right_product);
    const V first_for_dot = shuffle<0x0e>(first, first);
    const V squares = mul(cross, cross);
    const V upper = high_to_low(squares, squares);
    const V paired = add(squares, upper);
    const V second_square = shuffle<1>(paired, paired);
    const V squared_norm = add_low(paired, second_square);
    const V guess = root_guess(squared_norm);
    const V half_guess = mul_low(half, guess);
    const V first_correction = mul_low(squared_norm, guess);
    const V second_correction = mul_low(first_correction, guess);
    const V correction = sub_low(three, second_correction);
    const V factor_low = mul_low(half_guess, correction);
    const V factor = shuffle<0>(factor_low, factor_low);
    const V normal = mul(cross, factor);
    const V dot_products = mul(first_for_dot, normal);
    store_block(output, normal); // actual sixteen-byte write before final dot/mask
    const V high_products = high_to_low(squared_norm, dot_products);
    const V y_product = shuffle<0x55>(dot_products, dot_products);
    const V zy = add_low(high_products, y_product);
    const V dot = add_low(dot_products, zy);
    const V mask = aligned(reinterpret_cast<uint32_t>(dat_00717800));
    store_low(output + 12, xor_bits(dot, mask));
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_00683b5d(void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse2_plane_points\n\taddl $4,%esp\n\tretl $16");
}
