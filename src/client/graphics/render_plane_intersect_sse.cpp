#include "graphics/render_plane_intersect_sse.h"
extern "C" {
uint32_t dat_02251f98 = 0x0u;
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
void put(uint32_t* p, uint32_t v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
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
SIMD V high(V a, uint32_t p) {
    __asm__ volatile("movhps %1,%0" : "+x"(a) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return a;
}
SIMD V high_to_low(V a, V b) {
    __asm__ volatile("movhlps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V copy_low(V a, V b) {
    __asm__ volatile("movss %1,%0" : "+x"(a) : "x"(b));
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
SIMD V reciprocal(V a, V b) {
    __asm__ volatile("rcpss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD bool equal_operand(V a) {
    unsigned char r;
    __asm__ volatile("comiss %2,%1\n\tsete %0"
                     : "=qm"(r)
                     : "x"(a), "m"(*reinterpret_cast<const B4*>(&dat_02251f98))
                     : "cc", "memory");
    return r != 0;
}
SIMD void store_high(uint32_t p, V a) {
    __asm__ volatile("movhps %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(a) : "memory");
}
SIMD void store_low(uint32_t p, V a) {
    __asm__ volatile("movss %1,%0" : "=m"(*reinterpret_cast<B4*>(p)) : "x"(a) : "memory");
}
} // namespace
extern "C" __attribute__((target("sse"))) void*
recovered_sse_plane_intersect(uint32_t* arguments, const unsigned char* incoming) {
    const V incoming_five = block(reinterpret_cast<uint32_t>(incoming));
    const V incoming_six = block(reinterpret_cast<uint32_t>(incoming + 16));
    const uint32_t initial_output = word(arguments);
    put(arguments, initial_output);
    const V plane = block(word(arguments + 1));
    const uint32_t first_pointer = word(arguments + 2);
    const V first_z = scalar(first_pointer + 8);
    const uint32_t second_pointer = word(arguments + 3);
    const V first = high(first_z, first_pointer);
    const V second_z = scalar(second_pointer + 8);
    const V rotated_plane = shuffle<0x4e>(plane, plane);
    const V plane_w = shuffle<0xff>(plane, plane);
    const V second = high(second_z, second_pointer);
    const V first_product = mul(first, rotated_plane);
    const V second_product = mul(rotated_plane, second);
    const V first_high = high_to_low(incoming_five, first_product);
    const V second_high = high_to_low(incoming_six, second_product);
    const V first_sum = add(first_product, first_high);
    const V second_sum = add(second_product, second_high);
    const V first_reduction = shuffle<0x55>(first_high, first_sum);
    const V second_reduction = shuffle<0x55>(second_high, second_sum);
    const V first_dot = add_low(first_sum, first_reduction);
    const V second_dot = add_low(second_sum, second_reduction);
    const V denominator = sub_low(copy_low(first_reduction, first_dot), second_dot);
    const V numerator = add_low(first_dot, plane_w);
    if (equal_operand(denominator)) {
        put(arguments, 0); // unordered COMISS also takes original JE
    } else {
        const V guess = reciprocal(second_dot, denominator);
        const V saved_guess = copy_low(second_reduction, guess);
        const V twice = add_low(saved_guess, saved_guess);
        const V product = mul_low(denominator, guess);
        const V corrected_product = mul_low(product, guess);
        const V refined = sub_low(twice, corrected_product);
        const V t = mul_low(numerator, refined);
        const V broadcast = shuffle<0>(t, t);
        const V difference = sub(second, first);
        const V scaled = mul(broadcast, difference);
        const uint32_t output = word(arguments);
        const V result = add(first, scaled);
        store_high(output, result);
        store_low(output + 8, result);
    }
    return reinterpret_cast<void*>(word(arguments));
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_00680fc5(void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "subl $32,%esp\n\tmovups %xmm5,0(%esp)\n\tmovups %xmm6,16(%esp)\n\tmovl %esp,%edx\n\tleal 36(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_sse_plane_intersect\n\taddl $40,%esp\n\tretl $16");
}
