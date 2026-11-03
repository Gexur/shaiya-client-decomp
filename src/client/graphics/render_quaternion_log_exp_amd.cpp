#include "graphics/render_quaternion_log_exp_amd.h"
namespace {
using u32 = uint32_t;
using Packed = long long __attribute__((vector_size(8)));
struct B4 {
    unsigned char bytes[4];
};
struct B8 {
    unsigned char bytes[8];
};
#define AMD __attribute__((target("mmx"), always_inline)) inline
u32 word(u32 p) {
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
AMD Packed packed_word(u32 v) {
    Packed p;
    __asm__ volatile("movd %1,%0" : "=y"(p) : "r"(v));
    return p;
}
AMD u32 low(Packed p) {
    u32 v;
    __asm__ volatile("movd %1,%0" : "=r"(v) : "y"(p));
    return v;
}
AMD void store(u32 p, Packed v) {
    __asm__ volatile("movq %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "y"(v) : "memory");
}
AMD void store_single(u32 p, Packed v) {
    __asm__ volatile("movd %1,%0" : "=m"(*reinterpret_cast<B4*>(p)) : "y"(v) : "memory");
}
AMD Packed shift32(Packed p) {
    __asm__ volatile("psrlq $32,%0" : "+y"(p));
    return p;
}
AMD Packed to_int(Packed p) {
    Packed v;
    __asm__ volatile("pf2id %1,%0" : "=y"(v) : "y"(p));
    return v;
}
AMD Packed to_float(Packed p) {
    Packed v;
    __asm__ volatile("pi2fd %1,%0" : "=y"(v) : "y"(p));
    return v;
}
AMD void empty() {
    __asm__ volatile("femms" ::
                         : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st", "st(1)",
                           "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory");
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
AMD Packed punpckldq(Packed a, Packed b) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed punpckhdq(Packed a, Packed b) {
    __asm__ volatile("punpckhdq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pand(Packed a, Packed b) {
    __asm__ volatile("pand %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pxor(Packed a, Packed b) {
    __asm__ volatile("pxor %1,%0" : "+y"(a) : "y"(b));
    return a;
}
// Actual custom input/output is MM0. The genuine entry deliberately
// clobbers EAX/EBX/ECX/EDX/ESI; EBP/EDI and the caller stack remain intact.
AMD Packed trig(Packed input) {
    Packed output;
    __asm__ volatile("movq %1,%%mm0\n\tcalll _FUN_006a6f20\n\tmovq %%mm0,%0"
                     : "=m"(output)
                     : "m"(input)
                     : "eax", "ebx", "ecx", "edx", "esi", "mm0", "mm1", "mm2", "mm3", "mm4", "mm5",
                       "mm6", "mm7", "memory", "cc");
    return output;
}
AMD Packed pfmul_reciprocal_refine1(Packed a, Packed b) {
    __asm__ volatile("pfrcpit1 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfmul_reciprocal_refine2(Packed a, Packed b) {
    __asm__ volatile("pfrcpit2 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfmul_rsqrt_refine1(Packed a, Packed b) {
    __asm__ volatile("pfrsqit1 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfcmpge(Packed a, Packed b) {
    __asm__ volatile("pfcmpge %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed reciprocal(Packed b) {
    Packed a;
    __asm__ volatile("pfrcp %1,%0" : "=y"(a) : "y"(b));
    return a;
}
AMD Packed reciprocal_sqrt(Packed b) {
    Packed a;
    __asm__ volatile("pfrsqrt %1,%0" : "=y"(a) : "y"(b));
    return a;
}
AMD Packed pfacc(Packed a, Packed b) {
    __asm__ volatile("pfacc %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed inverse_trig(Packed input) {
    Packed output;
    __asm__ volatile("movq %1,%%mm0\n\tcalll _FUN_006a6940\n\tmovq %%mm0,%0"
                     : "=m"(output)
                     : "m"(input)
                     : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "memory", "cc");
    return output;
}
AMD Packed sine(Packed input) {
    Packed output;
    __asm__ volatile("movq %1,%%mm0\n\tcalll _FUN_006a7020\n\tmovq %%mm0,%0"
                     : "=m"(output)
                     : "m"(input)
                     : "eax", "ebx", "ecx", "edx", "esi", "mm0", "mm1", "mm2", "mm3", "mm4", "mm5",
                       "mm6", "mm7", "memory", "cc");
    return output;
}
} // namespace

extern "C" alignas(8) const uint32_t dat_006f0198[2] = {0xffffffffu, 0x7fffffffu};
extern "C" alignas(8) const uint32_t dat_006f01a0[2] = {0x7fffffffu, 0x7fffffffu};
extern "C" alignas(8) const uint32_t dat_006f01a8[2] = {0x34000000u, 0x34000000u};
// Complete original006a7020..006a711e.
extern "C" __attribute__((target("mmx"))) void recovered_006a7020(u32 state) {
    [[maybe_unused]] u32 eax, ebx, ecx, edx, esi;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    mm0 = pair(state + 24);
    eax = low(mm0); // original006a7020 movd eax, mm0
    mm3 = single(
        reinterpret_cast<u32>(dat_00717e1c)); // original006a7023 movd mm3, dword ptr [0x717e1c]
    ebx = eax;                                // original006a702a mov ebx, eax
    edx = eax;                                // original006a702c mov edx, eax
    mm0 = pand(mm0, mm3);                     // original006a702e pand mm0, mm3
    ebx &= 0x80000000u;                       // original006a7031 and ebx, 0x80000000
    edx >>= 0x1fu;                            // original006a7037 shr edx, 0x1f
    eax ^= ebx;                               // original006a703a xor eax, ebx
    mm2 = single(
        reinterpret_cast<u32>(dat_00717ed0)); // original006a703c movd mm2, dword ptr [0x717ed0]
    mm1 = mm0;                                // original006a7043 movq mm1, mm0
    mm0 = pfmul(mm0, mm2);                    // original006a7046 pfmul mm0, mm2
    mm3 = pair(
        reinterpret_cast<u32>(dat_00717de0)); // original006a704a movq mm3, qword ptr [0x717de0]
    mm0 = to_int(mm0);                        // original006a7051 pf2id mm0, mm0
    mm7 = pair(
        reinterpret_cast<u32>(dat_00717de8)); // original006a7055 movq mm7, qword ptr [0x717de8]
    ecx = low(mm0);                           // original006a705c movd ecx, mm0
    mm0 = to_float(mm0);                      // original006a705f pi2fd mm0, mm0
    esi = ecx;                                // original006a7063 mov esi, ecx
    mm6 = pair(
        reinterpret_cast<u32>(dat_00717df8)); // original006a7065 movq mm6, qword ptr [0x717df8]
    mm0 = punpckldq(mm0, mm0);                // original006a706c punpckldq mm0, mm0
    mm5 = pair(
        reinterpret_cast<u32>(dat_00717d98)); // original006a706f movq mm5, qword ptr [0x717d98]
    mm0 = pfmul(mm0, mm3);                    // original006a7076 pfmul mm0, mm3
    mm3 = pair(
        reinterpret_cast<u32>(dat_00717df0)); // original006a707a movq mm3, qword ptr [0x717df0]
    mm1 = pfadd(mm1, mm0);                    // original006a7081 pfadd mm1, mm0
    esi >>= 0x2u;                             // original006a7085 shr esi, 2
    mm0 = punpckhdq(mm0, mm0);                // original006a7088 punpckhdq mm0, mm0
    edx ^= esi;                               // original006a708b xor edx, esi
    mm1 = pfadd(mm1, mm0);                    // original006a708d pfadd mm1, mm0
    zero = (ecx & 1u) == 0;                   // original006a7091 test ecx, 1
    mm1 = punpckldq(mm1, mm1);                // original006a7097 punpckldq mm1, mm1
    if (zero)
        goto L_006a70a0;    // original006a709a je 0x6a6fa0
    mm1 = pfsubr(mm1, mm3); // original006a709c pfsubr mm1, mm3
L_006a70a0:;
    mm2 = mm5;                 // original006a70a0 movq mm2, mm5
    edx <<= 0x1fu;             // original006a70a3 shl edx, 0x1f
    mm2 = punpckldq(mm2, mm1); // original006a70a6 punpckldq mm2, mm1
    mm1 = pfmul(mm1, mm1);     // original006a70a9 pfmul mm1, mm1
    esi = ecx;                 // original006a70ad mov esi, ecx
    mm4 = pair(
        reinterpret_cast<u32>(dat_00717e00)); // original006a70af movq mm4, qword ptr [0x717e00]
    esi >>= 0x1u;                             // original006a70b6 shr esi, 1
    mm7 = pfmul(mm7, mm1);                    // original006a70b8 pfmul mm7, mm1
    ecx ^= esi;                               // original006a70bc xor ecx, esi
    mm6 = pfmul(mm6, mm1);                    // original006a70be pfmul mm6, mm1
    esi <<= 0x1fu;                            // original006a70c2 shl esi, 0x1f
    mm7 = pfadd(mm7, mm5);                    // original006a70c5 pfadd mm7, mm5
    ebx ^= esi;                               // original006a70c9 xor ebx, esi
    mm4 = pfmul(mm4, mm1);                    // original006a70cb pfmul mm4, mm1
    mm7 = pfmul(mm7, mm6);                    // original006a70cf pfmul mm7, mm6
    mm6 = pair(
        reinterpret_cast<u32>(dat_00717e08)); // original006a70d3 movq mm6, qword ptr [0x717e08]
    mm7 = pfadd(mm7, mm5);                    // original006a70da pfadd mm7, mm5
    mm6 = pfmul(mm6, mm1);                    // original006a70de pfmul mm6, mm1
    mm4 = pfmul(mm4, mm7);                    // original006a70e2 pfmul mm4, mm7
    mm0 = packed_word(edx);                   // original006a70e6 movd mm0, edx
    mm4 = pfadd(mm4, mm5);                    // original006a70e9 pfadd mm4, mm5
    mm6 = punpckldq(mm6, mm5);                // original006a70ed punpckldq mm6, mm5
    mm5 = shift32(mm5);                       // original006a70f0 psrlq mm5, 0x20
    mm4 = pfmul(mm4, mm6);                    // original006a70f4 pfmul mm4, mm6
    mm0 = punpckldq(mm0, mm0);                // original006a70f8 punpckldq mm0, mm0
    mm1 = packed_word(ebx);                   // original006a70fb movd mm1, ebx
    mm4 = pfadd(mm4, mm5);                    // original006a70fe pfadd mm4, mm5
    zero = (ecx & 1u) == 0;                   // original006a7102 test ecx, 1
    mm4 = pfmul(mm4, mm2);                    // original006a7108 pfmul mm4, mm2
    if (zero)
        goto L_006a7114;       // original006a710c je 0x6a7014
    mm5 = punpckldq(mm5, mm4); // original006a710e punpckldq mm5, mm4
    mm4 = punpckhdq(mm4, mm5); // original006a7111 punpckhdq mm4, mm5
L_006a7114:;
    mm4 = pxor(mm4, mm1);      // original006a7114 pxor mm4, mm1
    mm0 = pxor(mm0, mm4);      // original006a7117 pxor mm0, mm4
    mm0 = punpckhdq(mm0, mm0); // original006a711a punpckhdq mm0, mm0
    put(state, eax);
    put(state + 4, ebx);
    put(state + 8, ecx);
    put(state + 12, edx);
    put(state + 16, esi);
    store(state + 24, mm0);
    return; // original006a711d ret
}
extern "C" __attribute__((naked)) void FUN_006a7020() {
    __asm__ volatile(
        "subl $40,%esp\n\tmovq %mm0,24(%esp)\n\tpushl %esp\n\tcalll _recovered_006a7020\n\taddl $4,%esp\n\tmovq 24(%esp),%mm0\n\tmovl (%esp),%eax\n\tmovl 4(%esp),%ebx\n\tmovl 8(%esp),%ecx\n\tmovl 12(%esp),%edx\n\tmovl 16(%esp),%esi\n\taddl $40,%esp\n\tretl");
}

// Complete00685892..00685939. Real private angle word, two genuine helpers,
// fresh argument reloads and both original packed comparison branches.
extern "C" __attribute__((target("mmx"))) void recovered_00685892(u32 args, u32 result) {
    empty();
    u32 eax = word(args), edx = word(args + 4), ecx;
    Packed mm0, mm1 = pair(edx), mm2 = pair(edx + 8), mm3, mm4;
    mm3 = punpckhdq(mm2, mm2);
    mm0 = mm3;
    mm3 = pfcmpge(mm3, pair(reinterpret_cast<u32>(dat_006f01e8)));
    ecx = low(mm3);
    if (!ecx) {
        mm0 = inverse_trig(mm0);
        const u32 angle = low(mm0);
        mm0 = sine(mm0);
        mm3 = mm0;
        edx = word(args + 4);
        mm3 = pand(mm3, pair(reinterpret_cast<u32>(dat_006f01a0)));
        eax = word(args);
        mm3 = pfcmpge(mm3, pair(reinterpret_cast<u32>(dat_006f01a8)));
        ecx = low(mm3);
        mm1 = pair(edx);
        mm2 = pair(edx + 8);
        if (ecx) {
            mm3 = packed_word(angle);
            mm4 = reciprocal(mm0);
            mm3 = punpckldq(mm3, mm3);
            mm0 = pfmul_reciprocal_refine1(mm0, mm4);
            mm0 = pfmul_reciprocal_refine2(mm0, mm4);
            mm3 = pfmul(mm3, mm0);
            mm1 = pfmul(mm1, mm3);
            mm2 = pfmul(mm2, mm3);
        }
    }
    mm2 = pand(mm2, pair(reinterpret_cast<u32>(dat_006f01b0)));
    store(eax, mm1);
    store(eax + 8, mm2);
    empty();
    put(result, eax);
    put(result + 4, ecx);
    put(result + 8, edx);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00685892(void*, const void*) {
    __asm__ volatile(
        "subl $12,%esp\n\tleal 16(%esp),%eax\n\tpushl %esp\n\tpushl %eax\n\tcalll _recovered_00685892\n\taddl $8,%esp\n\tmovl (%esp),%eax\n\tmovl 4(%esp),%ecx\n\tmovl 8(%esp),%edx\n\taddl $12,%esp\n\tretl $8");
}
// Complete00685939..006859de. The original8B operand at its privateSP spans
// the initialized reciprocalDWORD and the explicitly saved incomingESI word.
extern "C" __attribute__((target("mmx"))) void recovered_00685939(u32 args, u32 saved_esi,
                                                                  u32 saved_ebx, u32 result) {
    u32 original_private[3];
    const u32 scratch = reinterpret_cast<u32>(original_private);
    u32 edx = word(args + 4), eax, ecx;
    Packed mm0 = pair(edx), mm1 = single(edx + 8), mm2, mm3;
    mm0 = pfmul(mm0, mm0);
    mm1 = pfmul(mm1, mm1);
    mm0 = pfadd(mm0, mm1);
    mm0 = pfacc(mm0, mm0);
    mm1 = reciprocal_sqrt(mm0);
    mm2 = mm1;
    mm1 = pfmul(mm1, mm1);
    put(scratch + 4, saved_esi);
    mm1 = pfmul_rsqrt_refine1(mm1, mm0);
    put(scratch + 8, saved_ebx);
    mm1 = pfmul_reciprocal_refine2(mm1, mm2);
    store_single(scratch, mm1);
    mm0 = pfmul(mm0, mm1);
    mm0 = trig(mm0);
    mm1 = mm0;
    mm0 = pand(mm0, pair(reinterpret_cast<u32>(dat_006f0198)));
    edx = word(args + 4);
    mm0 = pfcmpge(mm0, pair(reinterpret_cast<u32>(dat_006f01a8)));
    eax = word(args);
    mm0 = punpckhdq(mm0, mm0);
    ecx = low(mm0);
    mm2 = pair(edx);
    mm0 = mm1;
    mm1 = punpckhdq(mm1, mm1);
    const bool multiply = (ecx & 1u) != 0;
    mm1 = pfmul(mm1, pair(scratch));
    mm3 = single(edx + 8);
    if (multiply) {
        mm1 = punpckldq(mm1, mm1);
        mm3 = pfmul(mm3, mm1);
        mm2 = pfmul(mm2, mm1);
    }
    mm3 = punpckldq(mm3, mm0);
    store(eax, mm2);
    store(eax + 8, mm3);
    empty();
    put(result, eax);
    put(result + 4, ecx);
    put(result + 8, edx);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00685939(void*, const void*) {
    __asm__ volatile(
        "subl $12,%esp\n\tleal 16(%esp),%eax\n\tpushl %esp\n\tpushl %ebx\n\tpushl %esi\n\tpushl %eax\n\tcalll _recovered_00685939\n\taddl $16,%esp\n\tmovl (%esp),%eax\n\tmovl 4(%esp),%ecx\n\tmovl 8(%esp),%edx\n\taddl $12,%esp\n\tretl $8");
}
