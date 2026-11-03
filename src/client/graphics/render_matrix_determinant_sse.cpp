#include "graphics/render_matrix_determinant_sse.h"
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
SIMD V aligned(uint32_t p) {
    V v;
    __asm__ volatile("movaps %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SIMD V low(uint32_t p) {
    V v{};
    __asm__ volatile("movlps %1,%0" : "+x"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
SIMD V high(V v, uint32_t p) {
    __asm__ volatile("movhps %1,%0" : "+x"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
template <int mask> SIMD V shuffle(V a) {
    __asm__ volatile("shufps %1,%0,%0" : "+x"(a) : "i"(mask));
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
SIMD V sub_low(V a, V b) {
    __asm__ volatile("subss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V high_to_low(V a) {
    __asm__ volatile("movhlps %0,%0" : "+x"(a));
    return a;
}
SIMD uint32_t bits(V v) {
    uint32_t result;
    __asm__ volatile("movss %1,%0" : "=m"(result) : "x"(v) : "memory");
    return result;
}
} // namespace
extern "C" __attribute__((target("sse"))) uint64_t
recovered_sse_matrix_determinant(const uint32_t* arguments) {
    const uint32_t input = word(arguments);
    V a, b, c, d;
    if ((input & 15) == 0) {
        a = aligned(input);
        b = aligned(input + 16);
        c = aligned(input + 32);
        d = aligned(input + 48);
    } else {
        b = low(input + 16);
        a = low(input);
        b = high(b, input + 24);
        a = high(a, input + 8);
        c = low(input + 32);
        d = low(input + 48);
        c = high(c, input + 40);
        d = high(d, input + 56);
    }
    // Both halves of every input vector are defined before the first arithmetic.
    const V cr = shuffle<0x39>(c), br1 = shuffle<0x39>(b);
    const V p3 = mul(d, cr), dr4e = shuffle<0x4e>(d);
    const V p4 = mul(dr4e, cr), dr2 = shuffle<0x39>(dr4e);
    const V p2 = mul(cr, dr2), r2 = shuffle<0x4e>(p2);
    const V diff2 = sub(r2, p2), br2 = shuffle<0x39>(br1);
    const V weighted2 = mul(diff2, br2), br3 = shuffle<0x39>(br2);
    const V p4r39 = shuffle<0x39>(p4), p3r4e = shuffle<0x4e>(p3), p3r39 = shuffle<0x39>(p3);
    const V diff4 = sub(p4r39, p3r4e), diff5 = sub(p4, p3r39);
    const V weighted0 = mul(br1, diff4), weighted1 = mul(br3, diff5);
    const V sum = add(weighted0, weighted2), sum2 = add(sum, weighted1), terms = mul(sum2, a);
    const V upper = high_to_low(terms), paired = add(terms, upper), other = shuffle<1>(paired);
    const V result = sub_low(paired, other);
    // EDX:EAX carries the already-read pointer and actual F32 return bits.
    return (uint64_t(input) << 32) | bits(result);
}
extern "C" __attribute__((naked, stdcall)) float FUN_00683a85(const void*) {
    __asm__ volatile(
        "pushl %ecx\n\tpushl %edx\n\tleal 12(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_matrix_determinant\n\tmovl %eax,(%esp)\n\tflds (%esp)\n\tmovl %edx,%eax\n\taddl $4,%esp\n\tpopl %edx\n\tpopl %ecx\n\ttestb $15,%al\n\tretl $4");
}
