#include "graphics/render_vec4_cross_sse2.h"
#include "startup/math_dispatch_state.h"
extern "C" {
alignas(16) uint32_t dat_00717870[4] = {0x0u, 0x80000000u, 0x0u, 0x80000000u};
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
SIMD V xor_bits(V a, V b) {
    __asm__ volatile("xorps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD void store(uint32_t p, V v) {
    __asm__ volatile("movups %1,%0" : "=m"(*reinterpret_cast<B16*>(p)) : "x"(v) : "memory");
}
} // namespace
extern "C" __attribute__((target("sse"))) void*
recovered_sse2_vec4_cross(const uint32_t* arguments) {
    const V first = load(word(arguments + 1));
    const V second = load(word(arguments + 2));
    const V third = load(word(arguments + 3));
    const uint32_t output = word(arguments);
    const V second_rotated = shuffle<0x39>(second, second);
    const V product_one = mul(second_rotated, third);
    const V third_half = shuffle<0x4e>(third, third);
    const V product_three = mul(second_rotated, third_half);
    const V third_rotated = shuffle<0x39>(third_half, third_half);
    const V product_zero = mul(second_rotated, third_rotated);
    const V one_half = shuffle<0x4e>(product_one, product_one);
    const V three_rotated = shuffle<0x39>(product_three, product_three);
    const V difference_five = sub(three_rotated, one_half);
    const V zero_half = shuffle<0x4e>(product_zero, product_zero);
    const V difference_two =
        sub(zero_half, product_zero); // exact private F32vector spill/reload value
    const V one_rotated = shuffle<0x39>(product_one, product_one);
    const V first_rotated = shuffle<0x39>(first, first);
    const V mask = aligned(reinterpret_cast<uint32_t>(dat_00717870));
    const V first_twice = shuffle<0x39>(first_rotated, first_rotated);
    const V first_thrice = shuffle<0x39>(first_twice, first_twice);
    const V term_zero = mul(first_rotated, difference_five);
    const V difference_seven = sub(product_three, one_rotated);
    const V term_one = mul(first_twice, difference_two);
    const V first_sum = add(term_zero, term_one);
    const V term_three = mul(first_thrice, difference_seven);
    const V sum = add(first_sum, term_three);
    store(output, xor_bits(sum, mask));
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_006839c4(void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse2_vec4_cross\n\taddl $4,%esp\n\tretl $16");
}
