#include "graphics/render_half_decode_sse2.h"
namespace {
using u32 = uint32_t;
using I = uint32_t __attribute__((vector_size(16)));
using V = float __attribute__((vector_size(16)));
struct B8 {
    unsigned char bytes[8];
};
struct B16 {
    unsigned char bytes[16];
};
#define SIMD __attribute__((target("sse2"), always_inline)) inline
u32 word(const u32* p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 half(u32 p) {
    u32 v;
    __asm__ volatile("movzwl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(const u32* p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
SIMD I zero() {
    I v;
    __asm__ volatile("pxor %0,%0" : "=x"(v));
    return v;
}
SIMD I load(const u32* p) {
    I v;
    __asm__ volatile("movdqa %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SIMD I input_load(const void* p) {
    I v;
    __asm__ volatile("movdqu %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SIMD I and_bits(I a, I b) {
    __asm__ volatile("pand %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD I or_bits(I a, I b) {
    __asm__ volatile("por %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD I and_not(I a, I b) {
    __asm__ volatile("pandn %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD I equal_words(I a, I b) {
    __asm__ volatile("pcmpeqw %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD I max_signed_words(I a, I b) {
    __asm__ volatile("pmaxsw %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD u32 mask_bytes(I a) {
    u32 result;
    __asm__ volatile("pmovmskb %1,%0" : "=r"(result) : "x"(a));
    return result;
}
SIMD I unpack_low_words(I a, I b) {
    __asm__ volatile("punpcklwd %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD I unpack_high_words(I a, I b) {
    __asm__ volatile("punpckhwd %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD I add_dwords(I a, I b) {
    __asm__ volatile("paddd %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD I shift_thirteen(I a) {
    __asm__ volatile("pslld $13,%0" : "+x"(a));
    return a;
}
SIMD V converted(I a) {
    V v;
    __asm__ volatile("cvtdq2ps %1,%0" : "=x"(v) : "x"(a));
    return v;
}
SIMD V floating_bits(I a) {
    V v;
    __builtin_memcpy(&v, &a, 16);
    return v;
}
SIMD V multiply(V a, V b) {
    __asm__ volatile("mulps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD void vector_store(void* p, V v) {
    __asm__ volatile("movups %1,%0" : "=m"(*reinterpret_cast<B16*>(p)) : "x"(v) : "memory");
}
SIMD V low_pair(u32 p) {
    V v{};
    __asm__ volatile("movlps %1,%0" : "+x"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
SIMD V high_pair(V v, u32 p) {
    __asm__ volatile("movhps %1,%0" : "+x"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
SIMD void low_store(u32 p, V v) {
    __asm__ volatile("movlps %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(v) : "memory");
}
SIMD void high_store(u32 p, V v) {
    __asm__ volatile("movhps %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(v) : "memory");
}
struct Pair {
    V low, high;
};
SIMD Pair invoke(V input) {
    register V low __asm__("xmm0") = input;
    register V high __asm__("xmm3");
    __asm__ volatile("calll _FUN_006834bf"
                     : "+x"(low), "=x"(high)::"cc", "memory", "xmm1", "xmm2", "xmm4", "xmm5",
                       "xmm6", "xmm7");
    return {low, high};
}
} // namespace
extern "C" __attribute__((target("sse2"), force_align_arg_pointer)) u32
recovered_sse2_half_unpack(const void* incoming, void* output) {
    const I input = input_load(incoming), z = zero(), exponent_mask = load(dat_007177b0),
            fraction_mask = load(dat_007177c0);
    const I exponent = and_bits(exponent_mask, input), fraction = and_bits(fraction_mask, input),
            sign = and_bits(input, load(dat_007177a0)), equal = equal_words(exponent, z);
    const u32 mask = mask_bytes(equal);
    V low, high;
    if (mask) {
        const I implicit = and_not(equal, load(dat_00717790)),
                significand = or_bits(fraction, implicit),
                clamped = max_signed_words(exponent, load(dat_007177d0)), bias = load(dat_007177e0);
        const I exponent_low = unpack_low_words(clamped, z),
                exponent_high = unpack_high_words(clamped, z), sign_low = unpack_low_words(z, sign),
                sign_high = unpack_high_words(z, sign);
        const I biased_low = add_dwords(exponent_low, bias),
                biased_high = add_dwords(exponent_high, bias),
                shifted_low = shift_thirteen(biased_low),
                shifted_high = shift_thirteen(biased_high),
                scale_low = or_bits(shifted_low, sign_low),
                scale_high = or_bits(shifted_high, sign_high);
        const I z2 = zero(), integer_low = unpack_low_words(significand, z2),
                integer_high = unpack_high_words(significand, z2);
        const V value_low = converted(integer_low), value_high = converted(integer_high);
        low = multiply(value_low, floating_bits(scale_low));
        high = multiply(floating_bits(scale_high), value_high);
    } else {
        const I bias = load(dat_007177f0), sign_low = unpack_low_words(z, sign),
                sign_high = unpack_high_words(z, sign);
        // The original uses the overwritten XMM7 sign-high words in these unpacks.
        const I exponent_low = unpack_low_words(exponent, sign_high),
                exponent_high = unpack_high_words(exponent, sign_high),
                biased_low = add_dwords(exponent_low, bias),
                biased_high = add_dwords(exponent_high, bias);
        const I fraction_low = unpack_low_words(fraction, sign_high),
                fraction_high = unpack_high_words(fraction, sign_high),
                combined_low = or_bits(fraction_low, biased_low),
                combined_high = or_bits(biased_high, fraction_high);
        low = floating_bits(or_bits(shift_thirteen(combined_low), sign_low));
        high = floating_bits(or_bits(shift_thirteen(combined_high), sign_high));
    }
    vector_store(output, low);
    vector_store(static_cast<unsigned char*>(output) + 16, high);
    return mask;
}
// Private original6834bf ABI: XMM0 in, XMM0/XMM3 out, all GPRs preserved.
// A private aligned adapter is needed for the ordinary C++ helper call.
extern "C" __attribute__((naked)) void FUN_006834bf() {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl %eax\n\tpushl %edx\n\tpushl %ecx\n\tandl $-16,%esp\n\tsubl $80,%esp\n\tmovups %xmm0,16(%esp)\n\tleal 16(%esp),%eax\n\tmovl %eax,(%esp)\n\tleal 32(%esp),%eax\n\tmovl %eax,4(%esp)\n\tcalll _recovered_sse2_half_unpack\n\tmovups 32(%esp),%xmm0\n\tmovups 48(%esp),%xmm3\n\ttestl %eax,%eax\n\tmovl -12(%ebp),%ecx\n\tmovl -8(%ebp),%edx\n\tmovl -4(%ebp),%eax\n\tleal (%ebp),%esp\n\tpopl %ebp\n\tretl");
}
extern "C" __attribute__((target("sse2"), force_align_arg_pointer)) void*
recovered_sse2_half_array(const u32* arguments) {
    const u32 first_count = word(arguments + 2), initial = word(arguments);
    if (first_count >= 8) {
        const u32 grouped = word(arguments + 2) & ~7u;
        u32 remaining = grouped, input = word(arguments + 1), output = word(arguments);
        do {
            const V a = low_pair(input), b = high_pair(a, input + 8);
            input += 16;
            const Pair result = invoke(b);
            low_store(output, result.low);
            high_store(output + 8, result.low);
            low_store(output + 16, result.high);
            high_store(output + 24, result.high);
            output += 32;
            remaining -= 8;
        } while (remaining);
        const u32 fresh_input = word(arguments + 1);
        put(arguments + 2, word(arguments + 2) - grouped);
        put(arguments + 1, fresh_input + grouped * 2);
        put(arguments, initial + grouped * 4);
    }
    u32 index = 0;
    if (word(arguments + 2) > index)
        do {
            const u32 input = word(arguments + 1), raw = half(input + index * 2),
                      exponent = raw & 0x7c00u, sign = (raw & 0x8000u) << 16,
                      significand = (exponent ? 0x400u : 0u) | (raw & 0x3ffu),
                      clamped = exponent > 0x400u ? exponent : 0x400u,
                      scale = ((clamped + 0x19800u) << 13) | sign;
            __asm__ volatile("fildl %0" ::"m"(significand) : "st", "memory");
            if (static_cast<int32_t>(significand) < 0)
                __asm__ volatile("fadds %0" ::"m"(dat_006bb60c) : "st", "memory");
            const u32 output = word(arguments);
            __asm__ volatile("fmuls %1\n\tfstps %0"
                             : "=m"(*reinterpret_cast<u32*>(output + index * 4))
                             : "m"(scale)
                             : "st", "memory");
            ++index;
        } while (index < word(arguments + 2));
    return reinterpret_cast<void*>(initial);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_006835b2(void*, const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse2_half_array\n\taddl $4,%esp\n\tretl $12");
}
extern "C" {
alignas(16) uint32_t dat_00717790[4] = {0x04000400u, 0x04000400u, 0x04000400u, 0x04000400u};
alignas(16) uint32_t dat_007177a0[4] = {0x80008000u, 0x80008000u, 0x80008000u, 0x80008000u};
alignas(16) uint32_t dat_007177b0[4] = {0x7c007c00u, 0x7c007c00u, 0x7c007c00u, 0x7c007c00u};
alignas(16) uint32_t dat_007177c0[4] = {0x03ff03ffu, 0x03ff03ffu, 0x03ff03ffu, 0x03ff03ffu};
alignas(16) uint32_t dat_007177d0[4] = {0x04000400u, 0x04000400u, 0x04000400u, 0x04000400u};
alignas(16) uint32_t dat_007177e0[4] = {0x00019800u, 0x00019800u, 0x00019800u, 0x00019800u};
alignas(16) uint32_t dat_007177f0[4] = {0x0001c000u, 0x0001c000u, 0x0001c000u, 0x0001c000u};
alignas(4) extern const uint32_t dat_006bb60c[1] = {0x4f800000u};
}
