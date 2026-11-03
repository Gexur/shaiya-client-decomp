#include "graphics/render_amd_trig_rotation.h"
#include "graphics/render_scale_amd.h"
#include "graphics/render_normalize_amd.h"
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
} // namespace
extern "C" alignas(8) uint32_t dat_00717d98[2] = {0x3f800000u, 0x3f800000u};
extern "C" alignas(8) uint32_t dat_00717de0[2] = {0xbf490000u, 0xb97daa22u};
extern "C" alignas(8) uint32_t dat_00717de8[2] = {0xbc924925u, 0xbcc30c31u};
extern "C" alignas(8) uint32_t dat_00717df0[2] = {0x3f490fdbu, 0x3f490fdbu};
extern "C" alignas(8) uint32_t dat_00717df8[2] = {0xbd088889u, 0xbd4ccccdu};
extern "C" alignas(8) uint32_t dat_00717e00[2] = {0xbdaaaaabu, 0xbe2aaaabu};
extern "C" alignas(8) uint32_t dat_00717e08[2] = {0xbf000000u, 0xbf000000u};
extern "C" alignas(4) uint32_t dat_00717e1c[1] = {0x7fffffffu};
extern "C" alignas(4) uint32_t dat_00717ed0[1] = {0x3fa2f983u};
extern "C" alignas(8) const uint32_t dat_006f01d8[2] = {0x80000000u, 0x00000000u};
extern "C" alignas(8) const uint32_t dat_006f0228[2] = {0x3f800000u, 0x00000000u};
// Complete original006a6f20..006a701c.
extern "C" __attribute__((target("mmx"))) void recovered_006a6f20(u32 state) {
    [[maybe_unused]] u32 eax, ebx, ecx, edx, esi;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    mm0 = pair(state + 24);
    eax = low(mm0); // original006a6f20 movd eax, mm0
    mm3 = single(
        reinterpret_cast<u32>(dat_00717e1c)); // original006a6f23 movd mm3, dword ptr [0x717e1c]
    ebx = eax;                                // original006a6f2a mov ebx, eax
    edx = eax;                                // original006a6f2c mov edx, eax
    mm0 = pand(mm0, mm3);                     // original006a6f2e pand mm0, mm3
    ebx &= 0x80000000u;                       // original006a6f31 and ebx, 0x80000000
    edx >>= 0x1fu;                            // original006a6f37 shr edx, 0x1f
    eax ^= ebx;                               // original006a6f3a xor eax, ebx
    mm2 = single(
        reinterpret_cast<u32>(dat_00717ed0)); // original006a6f3c movd mm2, dword ptr [0x717ed0]
    mm1 = mm0;                                // original006a6f43 movq mm1, mm0
    mm0 = pfmul(mm0, mm2);                    // original006a6f46 pfmul mm0, mm2
    mm3 = pair(
        reinterpret_cast<u32>(dat_00717de0)); // original006a6f4a movq mm3, qword ptr [0x717de0]
    mm0 = to_int(mm0);                        // original006a6f51 pf2id mm0, mm0
    mm7 = pair(
        reinterpret_cast<u32>(dat_00717de8)); // original006a6f55 movq mm7, qword ptr [0x717de8]
    ecx = low(mm0);                           // original006a6f5c movd ecx, mm0
    mm0 = to_float(mm0);                      // original006a6f5f pi2fd mm0, mm0
    esi = ecx;                                // original006a6f63 mov esi, ecx
    mm6 = pair(
        reinterpret_cast<u32>(dat_00717df8)); // original006a6f65 movq mm6, qword ptr [0x717df8]
    mm0 = punpckldq(mm0, mm0);                // original006a6f6c punpckldq mm0, mm0
    mm5 = pair(
        reinterpret_cast<u32>(dat_00717d98)); // original006a6f6f movq mm5, qword ptr [0x717d98]
    mm0 = pfmul(mm0, mm3);                    // original006a6f76 pfmul mm0, mm3
    mm3 = pair(
        reinterpret_cast<u32>(dat_00717df0)); // original006a6f7a movq mm3, qword ptr [0x717df0]
    mm1 = pfadd(mm1, mm0);                    // original006a6f81 pfadd mm1, mm0
    esi >>= 0x2u;                             // original006a6f85 shr esi, 2
    mm0 = punpckhdq(mm0, mm0);                // original006a6f88 punpckhdq mm0, mm0
    edx ^= esi;                               // original006a6f8b xor edx, esi
    mm1 = pfadd(mm1, mm0);                    // original006a6f8d pfadd mm1, mm0
    zero = (ecx & 1u) == 0;                   // original006a6f91 test ecx, 1
    mm1 = punpckldq(mm1, mm1);                // original006a6f97 punpckldq mm1, mm1
    if (zero)
        goto L_006a6fa0;    // original006a6f9a je 0x6a6fa0
    mm1 = pfsubr(mm1, mm3); // original006a6f9c pfsubr mm1, mm3
L_006a6fa0:;
    mm2 = mm5;                 // original006a6fa0 movq mm2, mm5
    edx <<= 0x1fu;             // original006a6fa3 shl edx, 0x1f
    mm2 = punpckldq(mm2, mm1); // original006a6fa6 punpckldq mm2, mm1
    mm1 = pfmul(mm1, mm1);     // original006a6fa9 pfmul mm1, mm1
    esi = ecx;                 // original006a6fad mov esi, ecx
    mm4 = pair(
        reinterpret_cast<u32>(dat_00717e00)); // original006a6faf movq mm4, qword ptr [0x717e00]
    esi >>= 0x1u;                             // original006a6fb6 shr esi, 1
    mm7 = pfmul(mm7, mm1);                    // original006a6fb8 pfmul mm7, mm1
    ecx ^= esi;                               // original006a6fbc xor ecx, esi
    mm6 = pfmul(mm6, mm1);                    // original006a6fbe pfmul mm6, mm1
    esi <<= 0x1fu;                            // original006a6fc2 shl esi, 0x1f
    mm7 = pfadd(mm7, mm5);                    // original006a6fc5 pfadd mm7, mm5
    ebx ^= esi;                               // original006a6fc9 xor ebx, esi
    mm4 = pfmul(mm4, mm1);                    // original006a6fcb pfmul mm4, mm1
    mm7 = pfmul(mm7, mm6);                    // original006a6fcf pfmul mm7, mm6
    mm6 = pair(
        reinterpret_cast<u32>(dat_00717e08)); // original006a6fd3 movq mm6, qword ptr [0x717e08]
    mm7 = pfadd(mm7, mm5);                    // original006a6fda pfadd mm7, mm5
    mm6 = pfmul(mm6, mm1);                    // original006a6fde pfmul mm6, mm1
    mm4 = pfmul(mm4, mm7);                    // original006a6fe2 pfmul mm4, mm7
    mm0 = packed_word(edx);                   // original006a6fe6 movd mm0, edx
    mm4 = pfadd(mm4, mm5);                    // original006a6fe9 pfadd mm4, mm5
    mm6 = punpckldq(mm6, mm5);                // original006a6fed punpckldq mm6, mm5
    mm5 = shift32(mm5);                       // original006a6ff0 psrlq mm5, 0x20
    mm4 = pfmul(mm4, mm6);                    // original006a6ff4 pfmul mm4, mm6
    mm0 = punpckldq(mm0, mm0);                // original006a6ff8 punpckldq mm0, mm0
    mm1 = packed_word(ebx);                   // original006a6ffb movd mm1, ebx
    mm4 = pfadd(mm4, mm5);                    // original006a6ffe pfadd mm4, mm5
    zero = (ecx & 1u) == 0;                   // original006a7002 test ecx, 1
    mm4 = pfmul(mm4, mm2);                    // original006a7008 pfmul mm4, mm2
    if (zero)
        goto L_006a7014;       // original006a700c je 0x6a7014
    mm5 = punpckldq(mm5, mm4); // original006a700e punpckldq mm5, mm4
    mm4 = punpckhdq(mm4, mm5); // original006a7011 punpckhdq mm4, mm5
L_006a7014:;
    mm4 = pxor(mm4, mm1); // original006a7014 pxor mm4, mm1
    mm0 = pxor(mm0, mm4); // original006a7017 pxor mm0, mm4
    ;                     // original006a701a nop
    put(state, eax);
    put(state + 4, ebx);
    put(state + 8, ecx);
    put(state + 12, edx);
    put(state + 16, esi);
    store(state + 24, mm0);
    return; // original006a701b ret
}
extern "C" __attribute__((naked)) void FUN_006a6f20() {
    __asm__ volatile(
        "subl $40,%esp\n\tmovq %mm0,24(%esp)\n\tpushl %esp\n\tcalll _recovered_006a6f20\n\taddl $4,%esp\n\tmovq 24(%esp),%mm0\n\tmovl (%esp),%eax\n\tmovl 4(%esp),%ebx\n\tmovl 8(%esp),%ecx\n\tmovl 12(%esp),%edx\n\tmovl 16(%esp),%esi\n\taddl $40,%esp\n\tretl");
}
// Complete original00686931..00686996.
extern "C" __attribute__((target("mmx"))) u32 recovered_00686931(u32 arguments) {
    [[maybe_unused]] u32 eax, ebx, ecx, edx, esi;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ;                                           // original00686931 mov edi, edi
    ;                                           // original00686933 push ebx
    ;                                           // original00686934 push esi
    empty();                                    // original00686935 femms
    mm0 = single(arguments + 4);                // original00686937 movd mm0, dword ptr [esp + 0x10]
    mm0 = trig(mm0);                            // original0068693c call 0x6a6f20
    eax = word(arguments + 0);                  // original00686941 mov eax, dword ptr [esp + 0xc]
    mm4 = mm0;                                  // original00686945 movq mm4, mm0
    __asm__ volatile("pxor %0,%0" : "=y"(mm1)); // original00686948 pxor mm1, mm1
    mm2 = pair(
        reinterpret_cast<u32>(dat_006f0228)); // original0068694b movq mm2, qword ptr [0x6f0228]
    mm3 = pair(
        reinterpret_cast<u32>(dat_006f0220)); // original00686952 movq mm3, qword ptr [0x6f0220]
    mm4 = shift32(mm4);                       // original00686959 psrlq mm4, 0x20
    store(eax, mm2);                          // original0068695d movq qword ptr [eax], mm2
    store(eax + 0x8u, mm1);                   // original00686960 movq qword ptr [eax + 8], mm1
    store_single(eax + 0x10u, mm1);           // original00686964 movd dword ptr [eax + 0x10], mm1
    store_single(eax + 0x14u, mm0);           // original00686968 movd dword ptr [eax + 0x14], mm0
    store(eax + 0x18u, mm4);                  // original0068696c movq qword ptr [eax + 0x18], mm4
    mm4 = pxor(mm4, pair(reinterpret_cast<u32>(
                        dat_006f01d8))); // original00686970 pxor mm4, qword ptr [0x6f01d8]
    store(eax + 0x30u, mm1);             // original00686977 movq qword ptr [eax + 0x30], mm1
    store(eax + 0x38u, mm3);             // original0068697b movq qword ptr [eax + 0x38], mm3
    store_single(eax + 0x20u, mm1);      // original0068697f movd dword ptr [eax + 0x20], mm1
    store_single(eax + 0x24u, mm4);      // original00686983 movd dword ptr [eax + 0x24], mm4
    store_single(eax + 0x28u, mm0);      // original00686987 movd dword ptr [eax + 0x28], mm0
    store_single(eax + 0x2cu, mm1);      // original0068698b movd dword ptr [eax + 0x2c], mm1
    empty();                             // original0068698f femms
    ;                                    // original00686991 pop esi
    ;                                    // original00686992 pop ebx
    return eax;                          // original00686993 ret 8
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00686931(void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00686931\n\taddl $4,%esp\n\tretl $8");
}
// Complete original00686996..006869f6.
extern "C" __attribute__((target("mmx"))) u32 recovered_00686996(u32 arguments) {
    [[maybe_unused]] u32 eax, ebx, ecx, edx, esi;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ;                            // original00686996 mov edi, edi
    ;                            // original00686998 push ebx
    ;                            // original00686999 push esi
    empty();                     // original0068699a femms
    mm0 = single(arguments + 4); // original0068699c movd mm0, dword ptr [esp + 0x10]
    mm0 = trig(mm0);             // original006869a1 call 0x6a6f20
    eax = word(arguments + 0);   // original006869a6 mov eax, dword ptr [esp + 0xc]
    mm4 = mm0;                   // original006869aa movq mm4, mm0
    mm0 = pand(mm0, pair(reinterpret_cast<u32>(
                        dat_006f01b0)));        // original006869ad pand mm0, qword ptr [0x6f01b0]
    __asm__ volatile("pxor %0,%0" : "=y"(mm1)); // original006869b4 pxor mm1, mm1
    mm2 = pair(
        reinterpret_cast<u32>(dat_006f0228)); // original006869b7 movq mm2, qword ptr [0x6f0228]
    mm3 = pair(
        reinterpret_cast<u32>(dat_006f0220)); // original006869be movq mm3, qword ptr [0x6f0220]
    mm4 = shift32(mm4);                       // original006869c5 psrlq mm4, 0x20
    store(eax + 0x10u, mm3);                  // original006869c9 movq qword ptr [eax + 0x10], mm3
    store(eax + 0x18u, mm1);                  // original006869cd movq qword ptr [eax + 0x18], mm1
    store(eax + 0x30u, mm1);                  // original006869d1 movq qword ptr [eax + 0x30], mm1
    store(eax + 0x38u, mm3);                  // original006869d5 movq qword ptr [eax + 0x38], mm3
    store(eax + 0x20u, mm4);                  // original006869d9 movq qword ptr [eax + 0x20], mm4
    mm4 = pxor(mm4, pair(reinterpret_cast<u32>(
                        dat_006f01d8))); // original006869dd pxor mm4, qword ptr [0x6f01d8]
    store(eax, mm0);                     // original006869e4 movq qword ptr [eax], mm0
    store(eax + 0x28u, mm0);             // original006869e7 movq qword ptr [eax + 0x28], mm0
    store(eax + 0x8u, mm4);              // original006869eb movq qword ptr [eax + 8], mm4
    empty();                             // original006869ef femms
    ;                                    // original006869f1 pop esi
    ;                                    // original006869f2 pop ebx
    return eax;                          // original006869f3 ret 8
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00686996(void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00686996\n\taddl $4,%esp\n\tretl $8");
}
// Complete original006869f6..00686a51.
extern "C" __attribute__((target("mmx"))) u32 recovered_006869f6(u32 arguments) {
    [[maybe_unused]] u32 eax, ebx, ecx, edx, esi;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ;                                           // original006869f6 mov edi, edi
    ;                                           // original006869f8 push ebx
    ;                                           // original006869f9 push esi
    empty();                                    // original006869fa femms
    mm0 = single(arguments + 4);                // original006869fc movd mm0, dword ptr [esp + 0x10]
    mm0 = trig(mm0);                            // original00686a01 call 0x6a6f20
    eax = word(arguments + 0);                  // original00686a06 mov eax, dword ptr [esp + 0xc]
    mm4 = mm0;                                  // original00686a0a movq mm4, mm0
    mm4 = punpckhdq(mm4, mm4);                  // original00686a0d punpckhdq mm4, mm4
    __asm__ volatile("pxor %0,%0" : "=y"(mm1)); // original00686a10 pxor mm1, mm1
    mm2 = pair(
        reinterpret_cast<u32>(dat_006f0228)); // original00686a13 movq mm2, qword ptr [0x6f0228]
    mm3 = pair(
        reinterpret_cast<u32>(dat_006f0220)); // original00686a1a movq mm3, qword ptr [0x6f0220]
    mm4 = punpckldq(mm4, mm0);                // original00686a21 punpckldq mm4, mm0
    mm4 = pxor(mm4, pair(reinterpret_cast<u32>(
                        dat_006f01d8))); // original00686a24 pxor mm4, qword ptr [0x6f01d8]
    store(eax, mm0);                     // original00686a2b movq qword ptr [eax], mm0
    store(eax + 0x8u, mm1);              // original00686a2e movq qword ptr [eax + 8], mm1
    store(eax + 0x18u, mm1);             // original00686a32 movq qword ptr [eax + 0x18], mm1
    store(eax + 0x20u, mm1);             // original00686a36 movq qword ptr [eax + 0x20], mm1
    store(eax + 0x28u, mm2);             // original00686a3a movq qword ptr [eax + 0x28], mm2
    store(eax + 0x30u, mm1);             // original00686a3e movq qword ptr [eax + 0x30], mm1
    store(eax + 0x38u, mm3);             // original00686a42 movq qword ptr [eax + 0x38], mm3
    store(eax + 0x10u, mm4);             // original00686a46 movq qword ptr [eax + 0x10], mm4
    empty();                             // original00686a4a femms
    ;                                    // original00686a4c pop esi
    ;                                    // original00686a4d pop ebx
    return eax;                          // original00686a4e ret 8
}
extern "C" __attribute__((naked, stdcall)) void* FUN_006869f6(void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_006869f6\n\taddl $4,%esp\n\tretl $8");
}
