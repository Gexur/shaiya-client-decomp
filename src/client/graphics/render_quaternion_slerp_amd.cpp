#include "graphics/render_quaternion_slerp_amd.h"
namespace {
using u32 = uint32_t;
using Packed = long long __attribute__((vector_size(8)));
struct B4 {
    unsigned char b[4];
};
struct B8 {
    unsigned char b[8];
};
#define AMD __attribute__((target("mmx"), always_inline)) inline
u32 word(const u32* p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
AMD Packed pair(u32 p) {
    Packed v;
    __asm__ volatile("movq %1,%0" : "=y"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
AMD Packed single(u32 p) {
    Packed v;
    __asm__ volatile("movd %1,%0" : "=y"(v) : "m"(*reinterpret_cast<const B4*>(p)) : "memory");
    return v;
}
AMD void store(u32 p, Packed v) {
    __asm__ volatile("movq %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "y"(v) : "memory");
}
AMD void store_single(u32 p, Packed v) {
    __asm__ volatile("movd %1,%0" : "=m"(*reinterpret_cast<B4*>(p)) : "y"(v) : "memory");
}
AMD Packed root(Packed p) {
    Packed v;
    __asm__ volatile("pfrsqrt %1,%0" : "=y"(v) : "y"(p));
    return v;
}
AMD Packed reciprocal(Packed p) {
    Packed v;
    __asm__ volatile("pfrcp %1,%0" : "=y"(v) : "y"(p));
    return v;
}
AMD Packed sign_shift(Packed p) {
    __asm__ volatile("pslld $31,%0" : "+y"(p));
    return p;
}
AMD void empty() {
    __asm__ volatile("femms" ::
                         : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st", "st(1)",
                           "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory");
}
AMD Packed pand(Packed a, Packed b) {
    __asm__ volatile("pand %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pandn(Packed a, Packed b) {
    __asm__ volatile("pandn %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed por(Packed a, Packed b) {
    __asm__ volatile("por %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pxor(Packed a, Packed b) {
    __asm__ volatile("pxor %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pcmpgtd(Packed a, Packed b) {
    __asm__ volatile("pcmpgtd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfmul(Packed a, Packed b) {
    __asm__ volatile("pfmul %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfadd(Packed a, Packed b) {
    __asm__ volatile("pfadd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfsubr(Packed a, Packed b) {
    __asm__ volatile("pfsubr %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfrsqit1(Packed a, Packed b) {
    __asm__ volatile("pfrsqit1 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfrcpit1(Packed a, Packed b) {
    __asm__ volatile("pfrcpit1 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfrcpit2(Packed a, Packed b) {
    __asm__ volatile("pfrcpit2 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed punpckhdq(Packed a, Packed b) {
    __asm__ volatile("punpckhdq %1,%0" : "+y"(a) : "y"(b));
    return a;
}

AMD Packed pfmin(Packed a, Packed b) {
    __asm__ volatile("pfmin %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfmax(Packed a, Packed b) {
    __asm__ volatile("pfmax %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfsub(Packed a, Packed b) {
    __asm__ volatile("pfsub %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfcmpge(Packed a, Packed b) {
    __asm__ volatile("pfcmpge %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfacc(Packed a, Packed b) {
    __asm__ volatile("pfacc %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed punpckldq(Packed a, Packed b) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed left1(Packed a) {
    __asm__ volatile("pslld $1,%0" : "+y"(a));
    return a;
}
AMD Packed right1(Packed a) {
    __asm__ volatile("psrld $1,%0" : "+y"(a));
    return a;
}
AMD Packed arithmetic31(Packed a) {
    __asm__ volatile("psrad $31,%0" : "+y"(a));
    return a;
}
AMD Packed zero() {
    Packed a;
    __asm__ volatile("pxor %0,%0" : "=y"(a));
    return a;
}
AMD u32 low(Packed a) {
    u32 v;
    __asm__ volatile("movd %1,%0" : "=r"(v) : "y"(a));
    return v;
}
AMD Packed packed_word(u32 value) {
    Packed a;
    __asm__ volatile("movd %1,%0" : "=y"(a) : "r"(value));
    return a;
}
AMD Packed angle(Packed x, Packed y) {
    Packed result;
    __asm__ volatile("movq %1,%%mm0\n\tmovq %2,%%mm1\n\tcalll _FUN_006a6840\n\tmovq %%mm0,%0"
                     : "=m"(result)
                     : "m"(x), "m"(y)
                     : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "memory", "cc");
    return result;
}
AMD Packed sine(Packed input) {
    Packed result;
    __asm__ volatile("movq %1,%%mm0\n\tcalll _FUN_006a7020\n\tmovq %%mm0,%0"
                     : "=m"(result)
                     : "m"(input)
                     : "eax", "ebx", "ecx", "edx", "esi", "mm0", "mm1", "mm2", "mm3", "mm4", "mm5",
                       "mm6", "mm7", "memory", "cc");
    return result;
}
} // namespace

extern "C" alignas(8) const u32 dat_006f0248[2] = {0x3f7fff58u, 0x3f7fff58u};
extern "C" alignas(4) u32 dat_00717e48[1] = {0x419d92c8u};
extern "C" alignas(4) u32 dat_00717e4c[1] = {0x41e6bd60u};
extern "C" alignas(4) u32 dat_00717e50[1] = {0x41355dc0u};
extern "C" alignas(4) u32 dat_00717e54[1] = {0xc0d21907u};
extern "C" alignas(4) u32 dat_00717e58[1] = {0xc0b59883u};
extern "C" alignas(4) u32 dat_00717e5c[1] = {0xbf52c7eau};
extern "C" __attribute__((target("mmx"))) void recovered_006a6840(u32 state) {
    Packed mm0 = pair(state), mm1 = pair(state + 8), mm2, mm3, mm4, mm5, mm6, mm7;
    mm7 = single(
        reinterpret_cast<u32>(dat_00717e18)); // original006a6840 movd mm7, dword ptr [0x717e18]
    mm6 = single(
        reinterpret_cast<u32>(dat_00717e18)); // original006a6847 movd mm6, dword ptr [0x717e18]
    mm5 = single(
        reinterpret_cast<u32>(dat_00717e1c)); // original006a684e movd mm5, dword ptr [0x717e1c]
    mm7 = pand(mm7, mm0);                     // original006a6855 pand mm7, mm0
    mm6 = pand(mm6, mm1);                     // original006a6858 pand mm6, mm1
    mm7 = right1(mm7);                        // original006a685b psrld mm7, 1
    mm7 = por(mm7, mm6);                      // original006a685f por mm7, mm6
    mm1 = pand(mm1, mm5);                     // original006a6862 pand mm1, mm5
    mm0 = pand(mm0, mm5);                     // original006a6865 pand mm0, mm5
    mm6 = mm1;                                // original006a6868 movq mm6, mm1
    mm2 = mm0;                                // original006a686b movq mm2, mm0
    mm6 = pcmpgtd(mm6, mm0);                  // original006a686e pcmpgtd mm6, mm0
    mm0 = pfmax(mm0, mm1);                    // original006a6871 pfmax mm0, mm1
    mm6 = sign_shift(mm6);                    // original006a6875 pslld mm6, 0x1f
    mm1 = pfmin(mm1, mm2);                    // original006a6879 pfmin mm1, mm2
    mm2 = reciprocal(mm0);                    // original006a687d pfrcp mm2, mm0
    mm5 = single(
        reinterpret_cast<u32>(dat_00717e58)); // original006a6881 movd mm5, dword ptr [0x717e58]
    mm0 = pfrcpit1(mm0, mm2);                 // original006a6888 pfrcpit1 mm0, mm2
    mm4 = single(
        reinterpret_cast<u32>(dat_00717e5c)); // original006a688c movd mm4, dword ptr [0x717e5c]
    mm0 = pfrcpit2(mm0, mm2);                 // original006a6893 pfrcpit2 mm0, mm2
    mm3 = single(
        reinterpret_cast<u32>(dat_00717e50)); // original006a6897 movd mm3, dword ptr [0x717e50]
    mm0 = pfmul(mm0, mm1);                    // original006a689e pfmul mm0, mm1
    mm1 = mm0;                                // original006a68a2 movq mm1, mm0
    mm0 = pfmul(mm0, mm0);                    // original006a68a5 pfmul mm0, mm0
    mm3 = pfadd(mm3, mm0);                    // original006a68a9 pfadd mm3, mm0
    mm4 = pfmul(mm4, mm0);                    // original006a68ad pfmul mm4, mm0
    mm2 = single(
        reinterpret_cast<u32>(dat_00717e4c)); // original006a68b1 movd mm2, dword ptr [0x717e4c]
    mm3 = pfmul(mm3, mm0);                    // original006a68b8 pfmul mm3, mm0
    mm4 = pfadd(mm4, mm5);                    // original006a68bc pfadd mm4, mm5
    mm5 = single(
        reinterpret_cast<u32>(dat_00717e54)); // original006a68c0 movd mm5, dword ptr [0x717e54]
    mm3 = pfadd(mm3, mm2);                    // original006a68c7 pfadd mm3, mm2
    mm4 = pfmul(mm4, mm0);                    // original006a68cb pfmul mm4, mm0
    mm2 = single(
        reinterpret_cast<u32>(dat_00717e48)); // original006a68cf movd mm2, dword ptr [0x717e48]
    mm3 = pfmul(mm3, mm0);                    // original006a68d6 pfmul mm3, mm0
    mm4 = pfadd(mm4, mm5);                    // original006a68da pfadd mm4, mm5
    mm3 = pfadd(mm3, mm2);                    // original006a68de pfadd mm3, mm2
    mm0 = pfmul(mm0, mm4);                    // original006a68e2 pfmul mm0, mm4
    mm4 = mm7;                                // original006a68e6 movq mm4, mm7
    mm0 = pfmul(mm0, mm1);                    // original006a68e9 pfmul mm0, mm1
    mm5 = reciprocal(mm3);                    // original006a68ed pfrcp mm5, mm3
    mm7 = left1(mm7);                         // original006a68f1 pslld mm7, 1
    mm3 = pfrcpit1(mm3, mm5);                 // original006a68f5 pfrcpit1 mm3, mm5
    mm3 = pfrcpit2(mm3, mm5);                 // original006a68f9 pfrcpit2 mm3, mm5
    mm5 = mm7;                                // original006a68fd movq mm5, mm7
    mm7 = pxor(mm7, mm6);                     // original006a6900 pxor mm7, mm6
    mm0 = pfmul(mm0, mm3);                    // original006a6903 pfmul mm0, mm3
    mm3 = single(
        reinterpret_cast<u32>(dat_00717e78)); // original006a6907 movd mm3, dword ptr [0x717e78]
    mm5 = pxor(mm5, mm3);                     // original006a690e pxor mm5, mm3
    mm6 = arithmetic31(mm6);                  // original006a6911 psrad mm6, 0x1f
    mm0 = pfadd(mm0, mm1);                    // original006a6915 pfadd mm0, mm1
    mm6 = pandn(mm6, mm5);                    // original006a6919 pandn mm6, mm5
    mm1 = single(
        reinterpret_cast<u32>(dat_00717e18)); // original006a691c movd mm1, dword ptr [0x717e18]
    mm6 = pfsub(mm6, mm3);                    // original006a6923 pfsub mm6, mm3
    mm0 = por(mm0, mm7);                      // original006a6927 por mm0, mm7
    mm1 = pand(mm1, mm4);                     // original006a692a pand mm1, mm4
    mm0 = pfadd(mm0, mm6);                    // original006a692d pfadd mm0, mm6
    mm0 = por(mm0, mm1);                      // original006a6931 por mm0, mm1
    store(state, mm0);
    return; // original006a6934 ret
}
extern "C" __attribute__((naked)) void FUN_006a6840() {
    __asm__ volatile(
        "pushfl\n\tsubl $16,%esp\n\tmovq %mm0,(%esp)\n\tmovq %mm1,8(%esp)\n\tpushal\n\tleal 32(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_006a6840\n\taddl $4,%esp\n\tpopal\n\tmovq (%esp),%mm0\n\taddl $16,%esp\n\tpopfl\n\tretl");
}

// Complete006855d8..0068570f. The four original private DWORDs are written
// on precisely the branch on which they are subsequently read. Saved-register
// words are not read as arithmetic inputs. Actual argument3 is overwritten.
extern "C" __attribute__((target("mmx"))) u32 recovered_006855d8(u32 args) {
    empty();
    u32 ecx = word(reinterpret_cast<const u32*>(args + 4));
    u32 edx = word(reinterpret_cast<const u32*>(args + 8));
    u32 scratch_words[4];
    const u32 scratch = reinterpret_cast<u32>(scratch_words);
    Packed mm0 = single(reinterpret_cast<u32>(dat_006f01e8));
    Packed mm1 = pair(ecx);
    mm1 = pfmul(mm1, pair(edx));
    Packed mm2 = pair(ecx + 8);
    mm2 = pfmul(mm2, pair(edx + 8));
    mm1 = pfadd(mm1, mm2);
    Packed mm7 = zero();
    Packed mm4 = single(args + 12);
    mm0 = pfsub(mm0, mm4);
    mm1 = pfacc(mm1, mm1);
    mm7 = pfcmpge(mm7, mm1);
    Packed mm6 = pair(reinterpret_cast<u32>(dat_006f0248));
    mm7 = pand(mm7, pair(reinterpret_cast<u32>(dat_006f0230)));
    mm1 = pxor(mm1, mm7);
    mm6 = pfcmpge(mm6, mm1);
    const u32 condition = low(mm6);
    Packed mm3 = mm1;
    mm3 = pfmul(mm3, mm3);
    mm3 = pfsubr(mm3, pair(reinterpret_cast<u32>(dat_006f01e8)));
    if (condition) {
        mm4 = root(mm3);
        mm2 = mm4;
        store_single(scratch + 12, mm7);
        mm2 = pfmul(mm2, mm4);
        mm3 = pfrsqit1(mm3, mm2);
        mm3 = pfrcpit2(mm3, mm4);
        mm2 = reciprocal(mm3);
        mm4 = mm3;
        mm4 = pfrcpit1(mm4, mm2);
        mm4 = pfrcpit2(mm4, mm2);
        store_single(scratch, mm0);
        store_single(scratch + 4, mm3);
        mm0 = mm1;
        mm1 = mm4;
        mm0 = angle(mm0, mm1);
        mm1 = single(args + 12);
        store_single(scratch + 8, mm0);
        mm0 = pfmul(mm0, mm1);
        mm0 = sine(mm0);
        store_single(args + 12, mm0);
        mm1 = single(scratch);
        mm0 = single(scratch + 8);
        mm0 = pfmul(mm0, mm1);
        mm0 = sine(mm0);
        mm4 = single(args + 12);
        mm1 = single(scratch + 4);
        mm7 = single(scratch + 12);
        mm0 = pfmul(mm0, mm1);
        mm4 = pfmul(mm4, mm1);
    }
    ecx = word(reinterpret_cast<const u32*>(args + 4));
    edx = word(reinterpret_cast<const u32*>(args + 8));
    const u32 eax = word(reinterpret_cast<const u32*>(args));
    mm4 = pxor(mm4, mm7);
    mm0 = punpckldq(mm0, mm0);
    mm4 = punpckldq(mm4, mm4);
    Packed mm5 = mm0;
    mm6 = mm4;
    mm0 = pfmul(mm0, pair(ecx));
    mm4 = pfmul(mm4, pair(edx));
    mm5 = pfmul(mm5, pair(ecx + 8));
    mm6 = pfmul(mm6, pair(edx + 8));
    mm0 = pfadd(mm0, mm4);
    mm5 = pfadd(mm5, mm6);
    store(eax, mm0);
    store(eax + 8, mm5);
    empty();
    return eax;
}
extern "C" __attribute__((naked, stdcall)) void* FUN_006855d8(void*, const void*, const void*,
                                                              u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_006855d8\n\taddl $4,%esp\n\tretl $16");
}
// Complete0068570f..0068579c. The initial sum becomes the actual root
// argument4. Nested outgoing frames and the two initialized16B buffers have
// their own identities; finalEAX is a fresh read of actual root argument0.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068570f(u32 args) {
    u32 temporary[8];
    const u32 a = reinterpret_cast<u32>(temporary), b = a + 16;
    empty();
    Packed mm0 = single(args + 16), mm1 = single(args + 20);
    mm0 = pfadd(mm0, mm1);
    store_single(args + 16, mm0);
    const u32 first_t = low(mm0);
    const u32 first_q2 = word(reinterpret_cast<const u32*>(args + 8));
    const u32 first_q1 = word(reinterpret_cast<const u32*>(args + 4));
    FUN_006855d8(reinterpret_cast<void*>(a), reinterpret_cast<const void*>(first_q1),
                 reinterpret_cast<const void*>(first_q2), first_t);
    const u32 second_t = word(reinterpret_cast<const u32*>(args + 16));
    const u32 second_q3 = word(reinterpret_cast<const u32*>(args + 12));
    const u32 second_q1 = word(reinterpret_cast<const u32*>(args + 4));
    FUN_006855d8(reinterpret_cast<void*>(b), reinterpret_cast<const void*>(second_q1),
                 reinterpret_cast<const void*>(second_q3), second_t);
    mm0 = single(args + 16);
    mm1 = single(args + 20);
    Packed mm2 = reciprocal(mm0);
    mm0 = pfrcpit1(mm0, mm2);
    mm0 = pfrcpit2(mm0, mm2);
    mm0 = pfmul(mm0, mm1);
    const u32 third_t = low(mm0);
    const u32 output = word(reinterpret_cast<const u32*>(args));
    FUN_006855d8(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(a),
                 reinterpret_cast<const void*>(b), third_t);
    const u32 result = word(reinterpret_cast<const u32*>(args));
    empty();
    return result;
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068570f(void*, const void*, const void*,
                                                              const void*, u32, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068570f\n\taddl $4,%esp\n\tretl $24");
}
// Complete0068579c..0068582e. Three genuine core calls; the outer argument5
// is read separately for every call. The final returned pointer is cached by
// the final core, with no subsequent outer argument0 reload.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068579c(u32 args) {
    u32 temporary[8];
    const u32 a = reinterpret_cast<u32>(temporary), b = a + 16;
    const u32 first_t = word(reinterpret_cast<const u32*>(args + 20));
    const u32 first_q4 = word(reinterpret_cast<const u32*>(args + 16));
    const u32 first_q1 = word(reinterpret_cast<const u32*>(args + 4));
    FUN_006855d8(reinterpret_cast<void*>(a), reinterpret_cast<const void*>(first_q1),
                 reinterpret_cast<const void*>(first_q4), first_t);
    const u32 second_t = word(reinterpret_cast<const u32*>(args + 20));
    const u32 second_q3 = word(reinterpret_cast<const u32*>(args + 12));
    const u32 second_q2 = word(reinterpret_cast<const u32*>(args + 8));
    FUN_006855d8(reinterpret_cast<void*>(b), reinterpret_cast<const void*>(second_q2),
                 reinterpret_cast<const void*>(second_q3), second_t);
    Packed mm0 = single(args + 20);
    const u32 output = word(reinterpret_cast<const u32*>(args));
    Packed mm1 = mm0;
    mm0 = pfmul(mm0, mm0);
    mm1 = pfsub(mm1, mm0);
    mm1 = pfmul(mm1, pair(reinterpret_cast<u32>(dat_006f0168)));
    void* result = FUN_006855d8(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(a),
                                reinterpret_cast<const void*>(b), low(mm1));
    empty();
    return reinterpret_cast<u32>(result);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068579c(void*, const void*, const void*,
                                                              const void*, const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068579c\n\taddl $4,%esp\n\tretl $24");
}
