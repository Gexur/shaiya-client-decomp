#include "graphics/render_half_decode_mmx.h"
namespace {
using u32 = uint32_t;
using M = long long __attribute__((vector_size(8)));
using V = float __attribute__((vector_size(16)));
struct B8 {
    unsigned char bytes[8];
};
#define SIMD __attribute__((target("sse,mmx"), always_inline)) inline
SIMD M load(const u32* p) {
    M v;
    __asm__ volatile("movq %1,%0" : "=y"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
SIMD M zero() {
    M v;
    __asm__ volatile("pxor %0,%0" : "=y"(v));
    return v;
}
SIMD M and_bits(M a, M b) {
    __asm__ volatile("pand %1,%0" : "+y"(a) : "y"(b));
    return a;
}
SIMD M or_bits(M a, M b) {
    __asm__ volatile("por %1,%0" : "+y"(a) : "y"(b));
    return a;
}
SIMD M and_not(M a, M b) {
    __asm__ volatile("pandn %1,%0" : "+y"(a) : "y"(b));
    return a;
}
SIMD M equal_words(M a, M b) {
    __asm__ volatile("pcmpeqw %1,%0" : "+y"(a) : "y"(b));
    return a;
}
SIMD M max_signed_words(M a, M b) {
    __asm__ volatile("pmaxsw %1,%0" : "+y"(a) : "y"(b));
    return a;
}
SIMD M unpack_low_words(M a, M b) {
    __asm__ volatile("punpcklwd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
SIMD M unpack_high_words(M a, M b) {
    __asm__ volatile("punpckhwd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
SIMD M add_dwords(M a, M b) {
    __asm__ volatile("paddd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
SIMD M shift_thirteen(M a) {
    __asm__ volatile("pslld $13,%0" : "+y"(a));
    return a;
}
SIMD V low_mmx(M a) {
    V v{};
    __asm__ volatile("movlps %1,%0" : "+x"(v) : "m"(a));
    return v;
}
SIMD V high_mmx(V a, M b) {
    __asm__ volatile("movhps %1,%0" : "+x"(a) : "m"(b));
    return a;
}
SIMD V converted(M a) {
    V v{};
    __asm__ volatile("cvtpi2ps %1,%0" : "+x"(v) : "y"(a));
    return v;
}
SIMD V combine(V a, V b) {
    __asm__ volatile("movlhps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V multiply(V a, V b) {
    __asm__ volatile("mulps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
struct Result {
    V low, high;
    M mm[8];
};
} // namespace
extern "C" __attribute__((target("sse,mmx"), force_align_arg_pointer)) void
recovered_mmx_half_unpack(const M* input, Result* output) {
    const M incoming_mm0 = load(reinterpret_cast<const u32*>(input)),
            incoming_mm1 = load(reinterpret_cast<const u32*>(input + 1));
    const M v000 = zero();                       // original0068274a pxor mm7, mm7
    const M v001 = load(dat_00717740);           // original0068274d movq mm6, qword ptr [0x717740]
    const M v002 = load(dat_00717750);           // original00682754 movq mm2, qword ptr [0x717750]
    const M v003 = and_bits(v001, incoming_mm0); // original0068275b pand mm6, mm0
    const M v004 = v003;                         // original0068275e movq mm3, mm6
    const M v005 = and_bits(v002, incoming_mm0); // original00682761 pand mm2, mm0
    const M v006 = and_bits(incoming_mm0,
                            load(dat_00717730)); // original00682764 pand mm0, qword ptr [0x717730]
    const M v007 = equal_words(v004, v000);      // original0068276b pcmpeqw mm3, mm7
    const M v008 =
        and_not(v007, load(dat_00717720)); // original0068276e pandn mm3, qword ptr [0x717720]
    const M v009 = or_bits(v005, v008);    // original00682775 por mm2, mm3
    const M v010 = v000;                   // original00682778 movq mm3, mm7
    const M v011 = max_signed_words(
        v003, load(dat_00717760));     // original0068277b pmaxsw mm6, qword ptr [0x717760]
    const M v012 = load(dat_00717770); // original00682782 movq mm4, qword ptr [0x717770]
    const M v013 = v011;               // original00682789 movq mm3, mm6
    const M v014 = unpack_low_words(v011, v000);  // original0068278c punpcklwd mm6, mm7
    const M v015 = unpack_high_words(v013, v000); // original0068278f punpckhwd mm3, mm7
    const M v016 = v000;                          // original00682792 movq mm5, mm7
    const M v017 = unpack_low_words(v016, v006);  // original00682795 punpcklwd mm5, mm0
    const M v018 = unpack_high_words(v000, v006); // original00682798 punpckhwd mm7, mm0
    const M v019 = add_dwords(v014, v012);        // original0068279b paddd mm6, mm4
    const M v020 = add_dwords(v015, v012);        // original0068279e paddd mm3, mm4
    const M v021 = shift_thirteen(v019);          // original006827a1 pslld mm6, 0xd
    const M v022 = shift_thirteen(v020);          // original006827a5 pslld mm3, 0xd
    const M v023 = or_bits(v021, v017);           // original006827a9 por mm6, mm5
    const M v024 = or_bits(v022, v018);           // original006827ac por mm3, mm7
    const V v025 = low_mmx(v023);                 // original006827b8 movlps xmm1, qword ptr [esp]
    const V v026 = high_mmx(v025, v024); // original006827bc movhps xmm1, qword ptr [esp + 8]
    const M v027 = zero();               // original006827c1 pxor mm3, mm3
    const M v028 = v009;                 // original006827c4 movq mm7, mm2
    const M v029 = unpack_low_words(v009, v027);  // original006827c7 punpcklwd mm2, mm3
    const M v030 = unpack_high_words(v028, v027); // original006827ca punpckhwd mm7, mm3
    const V v031 = converted(v029);               // original006827cd cvtpi2ps xmm0, mm2
    const V v032 = converted(v030);               // original006827d0 cvtpi2ps xmm2, mm7
    const V v033 = combine(v031, v032);           // original006827d3 movlhps xmm0, xmm2
    const V v034 = multiply(v033, v026);          // original006827d6 mulps xmm0, xmm1
    const M v035 = incoming_mm1;                  // original006827d9 movq mm0, mm1
    const M v036 = v027;                          // original006827dc movq mm7, mm3
    const M v037 = load(dat_00717740);            // original006827df movq mm6, qword ptr [0x717740]
    const M v038 = load(dat_00717750);            // original006827e6 movq mm2, qword ptr [0x717750]
    const M v039 = and_bits(v037, v035);          // original006827ed pand mm6, mm0
    const M v040 = v039;                          // original006827f0 movq mm3, mm6
    const M v041 = and_bits(v038, v035);          // original006827f3 pand mm2, mm0
    const M v042 =
        and_bits(v035, load(dat_00717730)); // original006827f6 pand mm0, qword ptr [0x717730]
    const M v043 = equal_words(v040, v036); // original006827fd pcmpeqw mm3, mm7
    const M v044 =
        and_not(v043, load(dat_00717720)); // original00682800 pandn mm3, qword ptr [0x717720]
    const M v045 = or_bits(v041, v044);    // original00682807 por mm2, mm3
    const M v046 = v036;                   // original0068280a movq mm3, mm7
    const M v047 = max_signed_words(
        v039, load(dat_00717760));     // original0068280d pmaxsw mm6, qword ptr [0x717760]
    const M v048 = load(dat_00717770); // original00682814 movq mm4, qword ptr [0x717770]
    const M v049 = v047;               // original0068281b movq mm3, mm6
    const M v050 = unpack_low_words(v047, v036);  // original0068281e punpcklwd mm6, mm7
    const M v051 = unpack_high_words(v049, v036); // original00682821 punpckhwd mm3, mm7
    const M v052 = v036;                          // original00682824 movq mm5, mm7
    const M v053 = unpack_low_words(v052, v042);  // original00682827 punpcklwd mm5, mm0
    const M v054 = unpack_high_words(v036, v042); // original0068282a punpckhwd mm7, mm0
    const M v055 = add_dwords(v050, v048);        // original0068282d paddd mm6, mm4
    const M v056 = add_dwords(v051, v048);        // original00682830 paddd mm3, mm4
    const M v057 = shift_thirteen(v055);          // original00682833 pslld mm6, 0xd
    const M v058 = shift_thirteen(v056);          // original00682837 pslld mm3, 0xd
    const M v059 = or_bits(v057, v053);           // original0068283b por mm6, mm5
    const M v060 = or_bits(v058, v054);           // original0068283e por mm3, mm7
    const V v061 = low_mmx(v059);                 // original0068284a movlps xmm1, qword ptr [esp]
    const V v062 = high_mmx(v061, v060); // original0068284e movhps xmm1, qword ptr [esp + 8]
    const M v063 = zero();               // original00682853 pxor mm3, mm3
    const M v064 = v045;                 // original00682856 movq mm7, mm2
    const M v065 = unpack_low_words(v045, v063);  // original00682859 punpcklwd mm2, mm3
    const M v066 = unpack_high_words(v064, v063); // original0068285c punpckhwd mm7, mm3
    const V v067 = converted(v065);               // original0068285f cvtpi2ps xmm3, mm2
    const V v068 = converted(v066);               // original00682862 cvtpi2ps xmm2, mm7
    const V v069 = combine(v067, v068);           // original00682865 movlhps xmm3, xmm2
    const V v070 = multiply(v069, v062);          // original00682868 mulps xmm3, xmm1
    output->mm[0] = v042;
    output->mm[1] = incoming_mm1;
    output->mm[2] = v065;
    output->mm[3] = v063;
    output->mm[4] = v048;
    output->mm[5] = v053;
    output->mm[6] = v059;
    output->mm[7] = v066;
    output->low = v034;
    output->high = v070;
}
// Private original682747 ABI: MM0/MM1 input, XMM0/XMM3 output, all GPRs preserved.
// Restore every physical MMX payload before actual EMMS: x87 aliases are observable.
extern "C" __attribute__((naked)) void FUN_00682747() {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl %eax\n\tpushl %edx\n\tpushl %ecx\n\tandl $-16,%esp\n\tsubl $144,%esp\n\tmovq %mm0,16(%esp)\n\tmovq %mm1,24(%esp)\n\tleal 16(%esp),%eax\n\tmovl %eax,(%esp)\n\tleal 32(%esp),%eax\n\tmovl %eax,4(%esp)\n\tcalll _recovered_mmx_half_unpack\n\tmovups 32(%esp),%xmm0\n\tmovups 48(%esp),%xmm3\n\tmovq 64(%esp),%mm0\n\tmovq 72(%esp),%mm1\n\tmovq 80(%esp),%mm2\n\tmovq 88(%esp),%mm3\n\tmovq 96(%esp),%mm4\n\tmovq 104(%esp),%mm5\n\tmovq 112(%esp),%mm6\n\tmovq 120(%esp),%mm7\n\temms\n\tmovl -12(%ebp),%ecx\n\tmovl -8(%ebp),%edx\n\tmovl -4(%ebp),%eax\n\tleal (%ebp),%esp\n\tpopl %ebp\n\tretl");
}
namespace {
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
SIMD void low_store(u32 p, V v) {
    __asm__ volatile("movlps %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(v) : "memory");
}
SIMD void high_store(u32 p, V v) {
    __asm__ volatile("movhps %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(v) : "memory");
}
struct Pair {
    V low, high;
};
SIMD Pair invoke(M first, M second) {
    register M low __asm__("mm0") = first, high __asm__("mm1") = second;
    register V a __asm__("xmm0"), b __asm__("xmm3");
    __asm__ volatile("calll _FUN_00682747"
                     : "+y"(low), "+y"(high), "=x"(a), "=x"(b)::"cc", "memory", "xmm1", "xmm2",
                       "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st", "st(1)", "st(2)", "st(3)",
                       "st(4)", "st(5)", "st(6)", "st(7)");
    return {a, b};
}
SIMD void empty() {
    __asm__ volatile("emms" ::
                         : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st", "st(1)",
                           "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory");
}
} // namespace
extern "C" __attribute__((target("sse,mmx"), force_align_arg_pointer)) void*
recovered_mmx_half_array(const u32* arguments) {
    const u32 first_count = word(arguments + 2), initial = word(arguments);
    if (first_count >= 8) {
        const u32 grouped = word(arguments + 2) & ~7u;
        u32 remaining = grouped, input = word(arguments + 1), output = word(arguments);
        do {
            const M a = load(reinterpret_cast<const u32*>(input)),
                    b = load(reinterpret_cast<const u32*>(input + 8));
            input += 16;
            const Pair result = invoke(a, b);
            low_store(output, result.low);
            high_store(output + 8, result.low);
            low_store(output + 16, result.high);
            high_store(output + 24, result.high);
            output += 32;
            remaining -= 8;
        } while (remaining);
        empty();
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
extern "C" __attribute__((naked, stdcall)) void* FUN_00682871(void*, const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_mmx_half_array\n\taddl $4,%esp\n\tretl $12");
}
extern "C" {
alignas(8) uint32_t dat_00717720[2] = {0x04000400u, 0x04000400u};
alignas(8) uint32_t dat_00717730[2] = {0x80008000u, 0x80008000u};
alignas(8) uint32_t dat_00717740[2] = {0x7c007c00u, 0x7c007c00u};
alignas(8) uint32_t dat_00717750[2] = {0x03ff03ffu, 0x03ff03ffu};
alignas(8) uint32_t dat_00717760[2] = {0x04000400u, 0x04000400u};
alignas(8) uint32_t dat_00717770[2] = {0x00019800u, 0x00019800u};
}
