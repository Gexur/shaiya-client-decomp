#include "graphics/render_quaternion_amd.h"
#include "graphics/render_amd_inverse.h"
#include "graphics/render_3dnow_norm.h"
namespace {
using u32 = uint32_t;
using Packed = long long __attribute__((vector_size(8)));
struct B4 {
    unsigned char bytes[4];
};
struct B8 {
    unsigned char bytes[8];
};
#define AMD __attribute__((target("mmx,sse"), always_inline)) inline
u32 word(const u32* p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
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
AMD u32 low(Packed p) {
    u32 v;
    __asm__ volatile("movd %1,%0" : "=r"(v) : "y"(p));
    return v;
}
AMD u32 sign_mask(Packed p) {
    u32 v;
    __asm__ volatile("pmovmskb %1,%0" : "=r"(v) : "y"(p));
    return v;
}
AMD Packed estimate(Packed p) {
    Packed v;
    __asm__ volatile("pfrsqrt %1,%0" : "=y"(v) : "y"(p));
    return v;
}
AMD void store(u32 p, Packed v) {
    __asm__ volatile("movq %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "y"(v) : "memory");
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
AMD Packed pfsub(Packed a, Packed b) {
    __asm__ volatile("pfsub %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfsubr(Packed a, Packed b) {
    __asm__ volatile("pfsubr %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfacc(Packed a, Packed b) {
    __asm__ volatile("pfacc %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed punpckhdq(Packed a, Packed b) {
    __asm__ volatile("punpckhdq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed punpckldq(Packed a, Packed b) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pxor(Packed a, Packed b) {
    __asm__ volatile("pxor %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pand(Packed a, Packed b) {
    __asm__ volatile("pand %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfcmpgt(Packed a, Packed b) {
    __asm__ volatile("pfcmpgt %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfcmpge(Packed a, Packed b) {
    __asm__ volatile("pfcmpge %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed packssdw(Packed a, Packed b) {
    __asm__ volatile("packssdw %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed packsswb(Packed a, Packed b) {
    __asm__ volatile("packsswb %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfrsqit1(Packed a, Packed b) {
    __asm__ volatile("pfrsqit1 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfrcpit2(Packed a, Packed b) {
    __asm__ volatile("pfrcpit2 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
// Keep the actual memory instruction: PUNPCKLDQ's observed memory
// access width must not be widened by a separate MOVQ load.
AMD Packed unpack_memory(Packed a, u32 p) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return a;
}
} // namespace
extern "C" alignas(8) const u32 dat_006f0178[2] = {0x80000000u, 0x00000000u};
extern "C" alignas(8) const u32 dat_006f0180[2] = {0x00000000u, 0x80000000u};
extern "C" alignas(8) const u32 dat_006f01c8[2] = {0x3f000000u, 0x3f000000u};

// Complete original00684f3c..00684fd5; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_00684f3c(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    edx = word(arguments + 2); // original00684f3c mov edx, dword ptr [esp + 0xc]
    eax = word(arguments + 1); // original00684f40 mov eax, dword ptr [esp + 8]
    mm2 = pair(edx);           // original00684f44 movq mm2, qword ptr [edx]
    mm3 = pair(edx + 0x8u);    // original00684f47 movq mm3, qword ptr [edx + 8]
    mm4 = mm2;                 // original00684f4b movq mm4, mm2
    mm5 = mm3;                 // original00684f4e movq mm5, mm3
    mm0 = pair(eax);           // original00684f51 movq mm0, qword ptr [eax]
    mm4 = punpckhdq(mm4, mm2); // original00684f54 punpckhdq mm4, mm2
    mm5 = punpckhdq(mm5, mm3); // original00684f57 punpckhdq mm5, mm3
    mm1 = pair(eax + 0x8u);    // original00684f5a movq mm1, qword ptr [eax + 8]
    mm4 = punpckldq(mm4, mm2); // original00684f5e punpckldq mm4, mm2
    mm5 = punpckldq(mm5, mm3); // original00684f61 punpckldq mm5, mm3
    eax = word(arguments + 0); // original00684f64 mov eax, dword ptr [esp + 4]
    mm6 = mm4;                 // original00684f68 movq mm6, mm4
    mm7 = mm5;                 // original00684f6b movq mm7, mm5
    mm2 = pfmul(mm2, mm1);     // original00684f6e pfmul mm2, mm1
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00684f72 pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original00684f79 pfmul mm3, mm0
    mm2 = pxor(mm2, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00684f7d pxor mm2, qword ptr [0x6f0178]
    mm5 = pfmul(mm5, mm0);               // original00684f84 pfmul mm5, mm0
    mm4 = pfmul(mm4, mm1);               // original00684f88 pfmul mm4, mm1
    mm2 = pfadd(mm2, mm3);               // original00684f8c pfadd mm2, mm3
    mm3 = pair(edx);                     // original00684f90 movq mm3, qword ptr [edx]
    mm4 = pfsub(mm4, mm5);               // original00684f93 pfsub mm4, mm5
    mm5 = pair(edx + 0x8u);              // original00684f97 movq mm5, qword ptr [edx + 8]
    mm7 = pfmul(mm7, mm1);               // original00684f9b pfmul mm7, mm1
    mm6 = pxor(mm6, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00684f9f pxor mm6, qword ptr [0x6f0178]
    mm4 = pfacc(mm4, mm2);               // original00684fa6 pfacc mm4, mm2
    mm6 = pfmul(mm6, mm0);               // original00684faa pfmul mm6, mm0
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00684fae pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original00684fb5 pfmul mm3, mm0
    store(eax, mm4);                     // original00684fb9 movq qword ptr [eax], mm4
    mm5 = pfmul(mm5, mm1);               // original00684fbc pfmul mm5, mm1
    mm6 = pfadd(mm6, mm7);               // original00684fc0 pfadd mm6, mm7
    mm5 = pfsub(mm5, mm3);               // original00684fc4 pfsub mm5, mm3
    mm6 = pfacc(mm6, mm5);               // original00684fc8 pfacc mm6, mm5
    store(eax + 0x8u, mm6);              // original00684fcc movq qword ptr [eax + 8], mm6
    empty();                             // original00684fd0 femms
    return eax;                          // original00684fd2 ret 0xc
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00684f3c(void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00684f3c\n\taddl $4,%esp\n\tretl $12");
}

// Complete original00684fd5..00685032; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_00684fd5(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    edx = word(arguments + 1); // original00684fd5 mov edx, dword ptr [esp + 8]
    mm0 = pair(edx);           // original00684fd9 movq mm0, qword ptr [edx]
    mm2 = pair(edx + 0x8u);    // original00684fdc movq mm2, qword ptr [edx + 8]
    mm1 = mm0;                 // original00684fe0 movq mm1, mm0
    mm0 = pfmul(mm0, mm0);     // original00684fe3 pfmul mm0, mm0
    mm3 = mm2;                 // original00684fe7 movq mm3, mm2
    mm2 = pfmul(mm2, mm2);     // original00684fea pfmul mm2, mm2
    mm0 = pfadd(mm0, mm2);     // original00684fee pfadd mm0, mm2
    eax = word(arguments + 0); // original00684ff2 mov eax, dword ptr [esp + 4]
    mm0 = pfacc(mm0, mm0);     // original00684ff6 pfacc mm0, mm0
    mm5 = mm0;                 // original00684ffa movq mm5, mm0
    mm4 = estimate(mm0);       // original00684ffd pfrsqrt mm4, mm0
    mm5 = pfcmpgt(mm5, pair(reinterpret_cast<u32>(
                           dat_006f01d0))); // original00685001 pfcmpgt mm5, qword ptr [0x6f01d0]
    mm2 = mm4;                              // original00685009 movq mm2, mm4
    mm2 = pfmul(mm2, mm4);                  // original0068500c pfmul mm2, mm4
    mm0 = pfrsqit1(mm0, mm2);               // original00685010 pfrsqit1 mm0, mm2
    mm1 = pand(mm1, mm5);                   // original00685014 pand mm1, mm5
    mm3 = pand(mm3, mm5);                   // original00685017 pand mm3, mm5
    mm0 = pfrcpit2(mm0, mm4);               // original0068501a pfrcpit2 mm0, mm4
    mm1 = pfmul(mm1, mm0);                  // original0068501e pfmul mm1, mm0
    mm3 = pfmul(mm3, mm0);                  // original00685022 pfmul mm3, mm0
    store(eax, mm1);                        // original00685026 movq qword ptr [eax], mm1
    store(eax + 0x8u, mm3);                 // original00685029 movq qword ptr [eax + 8], mm3
    empty();                                // original0068502d femms
    return eax;                             // original0068502f ret 8
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00684fd5(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00684fd5\n\taddl $4,%esp\n\tretl $8");
}

// Complete original00685076..00685292; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_00685076(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    edx = word(arguments + 1);                  // original00685076 mov edx, dword ptr [esp + 8]
    mm0 = pair(edx);                            // original0068507a movq mm0, qword ptr [edx]
    __asm__ volatile("pxor %0,%0" : "=y"(mm6)); // original0068507d pxor mm6, mm6
    mm4 = single(edx + 0x14u);                  // original00685080 movd mm4, dword ptr [edx + 0x14]
    mm1 = mm0;                                  // original00685084 movq mm1, mm0
    mm2 = mm0;                                  // original00685087 movq mm2, mm0
    mm3 = mm0;                                  // original0068508a movq mm3, mm0
    mm0 = pfadd(mm0, mm4);                      // original0068508d pfadd mm0, mm4
    mm5 = single(edx + 0x28u);                  // original00685091 movd mm5, dword ptr [edx + 0x28]
    mm1 = pfsub(mm1, mm4);                      // original00685095 pfsub mm1, mm4
    mm2 = pfsubr(mm2, mm4);                     // original00685099 pfsubr mm2, mm4
    mm3 = pfsubr(mm3, mm5);                     // original0068509d pfsubr mm3, mm5
    mm0 = pfadd(mm0, mm5);                      // original006850a1 pfadd mm0, mm5
    mm1 = pfsub(mm1, mm5);                      // original006850a5 pfsub mm1, mm5
    mm2 = pfsub(mm2, mm5);                      // original006850a9 pfsub mm2, mm5
    mm5 = pair(edx + 0x20u);                    // original006850ad movq mm5, qword ptr [edx + 0x20]
    mm3 = pfsub(mm3, mm4);                      // original006850b1 pfsub mm3, mm4
    mm0 = punpckldq(mm0, mm2);                  // original006850b5 punpckldq mm0, mm2
    mm7 = mm2;                                  // original006850b8 movq mm7, mm2
    mm6 = punpckldq(mm6, mm1);                  // original006850bb punpckldq mm6, mm1
    mm7 = punpckldq(mm7, mm1);                  // original006850be punpckldq mm7, mm1
    mm3 = punpckldq(mm3, mm3);                  // original006850c1 punpckldq mm3, mm3
    mm6 = pfcmpge(mm6, mm0);                    // original006850c4 pfcmpge mm6, mm0
    mm7 = pfcmpge(mm7, mm3);                    // original006850c8 pfcmpge mm7, mm3
    mm6 = packssdw(mm6, mm7);                   // original006850cc packssdw mm6, mm7
    mm6 = packsswb(mm6, mm6);                   // original006850cf packsswb mm6, mm6
    ecx = low(mm6);                             // original006850d2 movd ecx, mm6
    zero = ((ecx & 0x1u) == 0);                 // original006850d5 test ecx, 1
    mm6 = mm5;                                  // original006850db movq mm6, mm5
    eax = ecx;                                  // original006850de mov eax, ecx
    if (!zero)
        goto L_00685147; // original006850e0 jne 0x685147
    mm0 = pfadd(mm0, pair(reinterpret_cast<u32>(
                         dat_006f0150))); // original006850e2 pfadd mm0, qword ptr [0x6f0150]
    mm3 = single(edx + 0x18u);            // original006850ea movd mm3, dword ptr [edx + 0x18]
    mm7 = single(edx + 0x8u);             // original006850ee movd mm7, dword ptr [edx + 8]
    mm4 = estimate(mm0);                  // original006850f2 pfrsqrt mm4, mm0
    mm3 = punpckldq(mm3, mm5);            // original006850f6 punpckldq mm3, mm5
    mm7 = punpckldq(mm7, mm7);            // original006850f9 punpckldq mm7, mm7
    mm2 = mm4;                            // original006850fc movq mm2, mm4
    mm0 = punpckldq(mm0, mm0);            // original006850ff punpckldq mm0, mm0
    mm4 = pfmul(mm4, mm4);                // original00685102 pfmul mm4, mm4
    mm5 = punpckhdq(mm5, mm7);            // original00685106 punpckhdq mm5, mm7
    mm6 = single(edx + 0x10u);            // original00685109 movd mm6, dword ptr [edx + 0x10]
    mm4 = pfrsqit1(mm4, mm0);             // original0068510d pfrsqit1 mm4, mm0
    mm1 = punpckhdq(mm1, mm1);            // original00685111 punpckhdq mm1, mm1
    mm3 = pfsub(mm3, mm5);                // original00685114 pfsub mm3, mm5
    mm4 = pfrcpit2(mm4, mm2);             // original00685118 pfrcpit2 mm4, mm2
    mm1 = pfsub(mm1, mm6);                // original0068511c pfsub mm1, mm6
    mm4 = pfmul(mm4, pair(reinterpret_cast<u32>(
                         dat_006f01c8))); // original00685120 pfmul mm4, qword ptr [0x6f01c8]
    eax = word(arguments + 0);            // original00685128 mov eax, dword ptr [esp + 4]
    mm0 = pfmul(mm0, mm4);                // original0068512c pfmul mm0, mm4
    mm1 = pfmul(mm1, mm4);                // original00685130 pfmul mm1, mm4
    mm3 = pfmul(mm3, mm4);                // original00685134 pfmul mm3, mm4
    mm1 = punpckldq(mm1, mm0);            // original00685138 punpckldq mm1, mm0
    store(eax, mm3);                      // original0068513b movq qword ptr [eax], mm3
    store(eax + 0x8u, mm1);               // original0068513e movq qword ptr [eax + 8], mm1
    empty();                              // original00685142 femms
    return eax;                           // original00685144 ret 8
L_00685147:;
    eax &= 0xff00ff00u;          // original00685147 and eax, 0xff00ff00
    zero = (eax == 0xff00ff00u); // original0068514c cmp eax, 0xff00ff00
    eax = word(arguments + 0);   // original00685151 mov eax, dword ptr [esp + 4]
    if (!zero)
        goto L_006851c0; // original00685155 jne 0x6851c0
    mm1 = pfadd(mm1, pair(reinterpret_cast<u32>(
                         dat_006f0150)));  // original00685157 pfadd mm1, qword ptr [0x6f0150]
    mm2 = punpckhdq(mm2, mm2);             // original0068515f punpckhdq mm2, mm2
    mm4 = estimate(mm1);                   // original00685162 pfrsqrt mm4, mm1
    mm3 = single(edx + 0x10u);             // original00685166 movd mm3, dword ptr [edx + 0x10]
    mm0 = mm4;                             // original0068516a movq mm0, mm4
    mm4 = pfmul(mm4, mm4);                 // original0068516d pfmul mm4, mm4
    mm1 = punpckldq(mm1, mm1);             // original00685171 punpckldq mm1, mm1
    mm5 = unpack_memory(mm5, edx + 0x18u); // original00685174 punpckldq mm5, dword ptr [edx + 0x18]
    mm3 = pfsub(mm3, mm2);                 // original00685178 pfsub mm3, mm2
    mm4 = pfrsqit1(mm4, mm1);              // original0068517c pfrsqit1 mm4, mm1
    mm7 = single(edx + 0x8u);              // original00685180 movd mm7, dword ptr [edx + 8]
    mm6 = punpckhdq(mm6, mm6);             // original00685184 punpckhdq mm6, mm6
    mm4 = pfrcpit2(mm4, mm0);              // original00685187 pfrcpit2 mm4, mm0
    mm7 = punpckldq(mm7, mm6);             // original0068518b punpckldq mm7, mm6
    mm4 = pfmul(mm4, pair(reinterpret_cast<u32>(
                         dat_006f01c8))); // original0068518e pfmul mm4, qword ptr [0x6f01c8]
    mm7 = pxor(mm7, pair(reinterpret_cast<u32>(
                        dat_006f0180))); // original00685196 pxor mm7, qword ptr [0x6f0180]
    mm1 = pfmul(mm1, mm4);               // original0068519d pfmul mm1, mm4
    mm5 = pfadd(mm5, mm7);               // original006851a1 pfadd mm5, mm7
    mm3 = pfmul(mm3, mm4);               // original006851a5 pfmul mm3, mm4
    eax = word(arguments + 0);           // original006851a9 mov eax, dword ptr [esp + 4]
    mm5 = pfmul(mm5, mm4);               // original006851ad pfmul mm5, mm4
    mm1 = punpckldq(mm1, mm3);           // original006851b1 punpckldq mm1, mm3
    store(eax + 0x8u, mm5);              // original006851b4 movq qword ptr [eax + 8], mm5
    store(eax, mm1);                     // original006851b8 movq qword ptr [eax], mm1
    empty();                             // original006851bb femms
    return eax;                          // original006851bd ret 8
L_006851c0:;
    zero = ((ecx & 0x10000u) == 0); // original006851c0 test ecx, 0x10000
    eax = word(arguments + 0);      // original006851c6 mov eax, dword ptr [esp + 4]
    if (zero)
        goto L_00685234; // original006851ca je 0x685234
    mm2 = pfadd(mm2, pair(reinterpret_cast<u32>(
                         dat_006f0150))); // original006851cc pfadd mm2, qword ptr [0x6f0150]
    mm1 = punpckhdq(mm1, mm1);            // original006851d4 punpckhdq mm1, mm1
    mm6 = mm5;                            // original006851d7 movq mm6, mm5
    mm4 = estimate(mm2);                  // original006851da pfrsqrt mm4, mm2
    mm3 = single(edx + 0x18u);            // original006851de movd mm3, dword ptr [edx + 0x18]
    mm6 = punpckhdq(mm6, mm6);            // original006851e2 punpckhdq mm6, mm6
    mm0 = mm4;                            // original006851e5 movq mm0, mm4
    mm4 = pfmul(mm4, mm4);                // original006851e8 pfmul mm4, mm4
    mm2 = punpckldq(mm2, mm2);            // original006851ec punpckldq mm2, mm2
    mm6 = unpack_memory(mm6, edx + 0x8u); // original006851ef punpckldq mm6, dword ptr [edx + 8]
    mm3 = punpckldq(mm3, mm5);            // original006851f3 punpckldq mm3, mm5
    mm4 = pfrsqit1(mm4, mm2);             // original006851f6 pfrsqit1 mm4, mm2
    mm7 = single(edx + 0x10u);            // original006851fa movd mm7, dword ptr [edx + 0x10]
    mm4 = pfrcpit2(mm4, mm0);             // original006851fe pfrcpit2 mm4, mm0
    mm6 = pxor(mm6, pair(reinterpret_cast<u32>(
                        dat_006f0180))); // original00685202 pxor mm6, qword ptr [0x6f0180]
    mm1 = pfadd(mm1, mm7);               // original00685209 pfadd mm1, mm7
    mm4 = pfmul(mm4, pair(reinterpret_cast<u32>(
                         dat_006f01c8))); // original0068520d pfmul mm4, qword ptr [0x6f01c8]
    mm3 = pfadd(mm3, mm6);                // original00685215 pfadd mm3, mm6
    mm1 = pfmul(mm1, mm4);                // original00685219 pfmul mm1, mm4
    mm2 = pfmul(mm2, mm4);                // original0068521d pfmul mm2, mm4
    mm3 = pfmul(mm3, mm4);                // original00685221 pfmul mm3, mm4
    mm1 = punpckldq(mm1, mm2);            // original00685225 punpckldq mm1, mm2
    store(eax + 0x8u, mm3);               // original00685228 movq qword ptr [eax + 8], mm3
    store(eax, mm1);                      // original0068522c movq qword ptr [eax], mm1
    empty();                              // original0068522f femms
    return eax;                           // original00685231 ret 8
L_00685234:;
    mm3 = pfadd(mm3, pair(reinterpret_cast<u32>(
                         dat_006f0150)));  // original00685234 pfadd mm3, qword ptr [0x6f0150]
    mm1 = punpckhdq(mm1, mm1);             // original0068523c punpckhdq mm1, mm1
    mm2 = estimate(mm3);                   // original0068523f pfrsqrt mm2, mm3
    mm4 = single(edx + 0x8u);              // original00685243 movd mm4, dword ptr [edx + 8]
    mm6 = punpckhdq(mm6, mm6);             // original00685247 punpckhdq mm6, mm6
    mm0 = mm2;                             // original0068524a movq mm0, mm2
    mm2 = pfmul(mm2, mm2);                 // original0068524d pfmul mm2, mm2
    mm3 = punpckldq(mm3, mm3);             // original00685251 punpckldq mm3, mm3
    mm5 = unpack_memory(mm5, edx + 0x18u); // original00685254 punpckldq mm5, dword ptr [edx + 0x18]
    mm4 = punpckldq(mm4, mm6);             // original00685258 punpckldq mm4, mm6
    mm2 = pfrsqit1(mm2, mm3);              // original0068525b pfrsqit1 mm2, mm3
    mm7 = single(edx + 0x10u);             // original0068525f movd mm7, dword ptr [edx + 0x10]
    mm2 = pfrcpit2(mm2, mm0);              // original00685263 pfrcpit2 mm2, mm0
    mm1 = pfsub(mm1, mm7);                 // original00685267 pfsub mm1, mm7
    mm5 = pfadd(mm5, mm4);                 // original0068526b pfadd mm5, mm4
    mm2 = pfmul(mm2, pair(reinterpret_cast<u32>(
                         dat_006f01c8))); // original0068526f pfmul mm2, qword ptr [0x6f01c8]
    mm3 = pfmul(mm3, mm2);                // original00685277 pfmul mm3, mm2
    mm1 = pfmul(mm1, mm2);                // original0068527b pfmul mm1, mm2
    mm5 = pfmul(mm5, mm2);                // original0068527f pfmul mm5, mm2
    mm3 = punpckldq(mm3, mm1);            // original00685283 punpckldq mm3, mm1
    store(eax, mm5);                      // original00685286 movq qword ptr [eax], mm5
    store(eax + 0x8u, mm3);               // original00685289 movq qword ptr [eax + 8], mm3
    empty();                              // original0068528d femms
    return eax;                           // original0068528f ret 8
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00685076(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00685076\n\taddl $4,%esp\n\tretl $8");
}

// Complete original00685292..006854a7; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_00685292(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    edx = word(arguments + 1);                  // original00685292 mov edx, dword ptr [esp + 8]
    mm0 = pair(edx);                            // original00685296 movq mm0, qword ptr [edx]
    __asm__ volatile("pxor %0,%0" : "=y"(mm6)); // original00685299 pxor mm6, mm6
    mm4 = single(edx + 0x14u);                  // original0068529c movd mm4, dword ptr [edx + 0x14]
    mm1 = mm0;                                  // original006852a0 movq mm1, mm0
    mm2 = mm0;                                  // original006852a3 movq mm2, mm0
    mm3 = mm0;                                  // original006852a6 movq mm3, mm0
    mm0 = pfadd(mm0, mm4);                      // original006852a9 pfadd mm0, mm4
    mm5 = single(edx + 0x28u);                  // original006852ad movd mm5, dword ptr [edx + 0x28]
    mm1 = pfsub(mm1, mm4);                      // original006852b1 pfsub mm1, mm4
    mm2 = pfsubr(mm2, mm4);                     // original006852b5 pfsubr mm2, mm4
    mm3 = pfsubr(mm3, mm5);                     // original006852b9 pfsubr mm3, mm5
    mm0 = pfadd(mm0, mm5);                      // original006852bd pfadd mm0, mm5
    mm1 = pfsub(mm1, mm5);                      // original006852c1 pfsub mm1, mm5
    mm2 = pfsub(mm2, mm5);                      // original006852c5 pfsub mm2, mm5
    mm5 = pair(edx + 0x20u);                    // original006852c9 movq mm5, qword ptr [edx + 0x20]
    mm3 = pfsub(mm3, mm4);                      // original006852cd pfsub mm3, mm4
    mm0 = punpckldq(mm0, mm2);                  // original006852d1 punpckldq mm0, mm2
    mm7 = mm2;                                  // original006852d4 movq mm7, mm2
    mm6 = punpckldq(mm6, mm1);                  // original006852d7 punpckldq mm6, mm1
    mm7 = punpckldq(mm7, mm1);                  // original006852da punpckldq mm7, mm1
    mm3 = punpckldq(mm3, mm3);                  // original006852dd punpckldq mm3, mm3
    mm6 = pfcmpge(mm6, mm0);                    // original006852e0 pfcmpge mm6, mm0
    mm7 = pfcmpge(mm7, mm3);                    // original006852e4 pfcmpge mm7, mm3
    mm6 = packssdw(mm6, mm7);                   // original006852e8 packssdw mm6, mm7
    ecx = sign_mask(mm6);                       // original006852eb pmovmskb ecx, mm6
    zero = ((ecx & 0x1u) == 0);                 // original006852ee test ecx, 1
    mm6 = mm5;                                  // original006852f4 movq mm6, mm5
    eax = ecx;                                  // original006852f7 mov eax, ecx
    if (!zero)
        goto L_00685360; // original006852f9 jne 0x685360
    mm0 = pfadd(mm0, pair(reinterpret_cast<u32>(
                         dat_006f0150))); // original006852fb pfadd mm0, qword ptr [0x6f0150]
    mm3 = single(edx + 0x18u);            // original00685303 movd mm3, dword ptr [edx + 0x18]
    mm7 = single(edx + 0x8u);             // original00685307 movd mm7, dword ptr [edx + 8]
    mm4 = estimate(mm0);                  // original0068530b pfrsqrt mm4, mm0
    mm3 = punpckldq(mm3, mm5);            // original0068530f punpckldq mm3, mm5
    mm7 = punpckldq(mm7, mm7);            // original00685312 punpckldq mm7, mm7
    mm2 = mm4;                            // original00685315 movq mm2, mm4
    mm0 = punpckldq(mm0, mm0);            // original00685318 punpckldq mm0, mm0
    mm4 = pfmul(mm4, mm4);                // original0068531b pfmul mm4, mm4
    mm5 = punpckhdq(mm5, mm7);            // original0068531f punpckhdq mm5, mm7
    mm6 = single(edx + 0x10u);            // original00685322 movd mm6, dword ptr [edx + 0x10]
    mm4 = pfrsqit1(mm4, mm0);             // original00685326 pfrsqit1 mm4, mm0
    mm1 = punpckhdq(mm1, mm1);            // original0068532a punpckhdq mm1, mm1
    mm3 = pfsub(mm3, mm5);                // original0068532d pfsub mm3, mm5
    mm4 = pfrcpit2(mm4, mm2);             // original00685331 pfrcpit2 mm4, mm2
    mm1 = pfsub(mm1, mm6);                // original00685335 pfsub mm1, mm6
    mm4 = pfmul(mm4, pair(reinterpret_cast<u32>(
                         dat_006f01c8))); // original00685339 pfmul mm4, qword ptr [0x6f01c8]
    eax = word(arguments + 0);            // original00685341 mov eax, dword ptr [esp + 4]
    mm0 = pfmul(mm0, mm4);                // original00685345 pfmul mm0, mm4
    mm1 = pfmul(mm1, mm4);                // original00685349 pfmul mm1, mm4
    mm3 = pfmul(mm3, mm4);                // original0068534d pfmul mm3, mm4
    mm1 = punpckldq(mm1, mm0);            // original00685351 punpckldq mm1, mm0
    store(eax, mm3);                      // original00685354 movq qword ptr [eax], mm3
    store(eax + 0x8u, mm1);               // original00685357 movq qword ptr [eax + 8], mm1
    empty();                              // original0068535b femms
    return eax;                           // original0068535d ret 8
L_00685360:;
    eax &= 0xccu;          // original00685360 and eax, 0xcc
    zero = (eax == 0xccu); // original00685365 cmp eax, 0xcc
    if (!zero)
        goto L_006853d5; // original0068536a jne 0x6853d5
    mm1 = pfadd(mm1, pair(reinterpret_cast<u32>(
                         dat_006f0150)));  // original0068536c pfadd mm1, qword ptr [0x6f0150]
    mm2 = punpckhdq(mm2, mm2);             // original00685374 punpckhdq mm2, mm2
    mm4 = estimate(mm1);                   // original00685377 pfrsqrt mm4, mm1
    mm3 = single(edx + 0x10u);             // original0068537b movd mm3, dword ptr [edx + 0x10]
    mm0 = mm4;                             // original0068537f movq mm0, mm4
    mm4 = pfmul(mm4, mm4);                 // original00685382 pfmul mm4, mm4
    mm1 = punpckldq(mm1, mm1);             // original00685386 punpckldq mm1, mm1
    mm5 = unpack_memory(mm5, edx + 0x18u); // original00685389 punpckldq mm5, dword ptr [edx + 0x18]
    mm3 = pfsub(mm3, mm2);                 // original0068538d pfsub mm3, mm2
    mm4 = pfrsqit1(mm4, mm1);              // original00685391 pfrsqit1 mm4, mm1
    mm7 = single(edx + 0x8u);              // original00685395 movd mm7, dword ptr [edx + 8]
    mm6 = punpckhdq(mm6, mm6);             // original00685399 punpckhdq mm6, mm6
    mm4 = pfrcpit2(mm4, mm0);              // original0068539c pfrcpit2 mm4, mm0
    mm7 = punpckldq(mm7, mm6);             // original006853a0 punpckldq mm7, mm6
    mm4 = pfmul(mm4, pair(reinterpret_cast<u32>(
                         dat_006f01c8))); // original006853a3 pfmul mm4, qword ptr [0x6f01c8]
    mm7 = pxor(mm7, pair(reinterpret_cast<u32>(
                        dat_006f0180))); // original006853ab pxor mm7, qword ptr [0x6f0180]
    mm1 = pfmul(mm1, mm4);               // original006853b2 pfmul mm1, mm4
    mm5 = pfadd(mm5, mm7);               // original006853b6 pfadd mm5, mm7
    mm3 = pfmul(mm3, mm4);               // original006853ba pfmul mm3, mm4
    eax = word(arguments + 0);           // original006853be mov eax, dword ptr [esp + 4]
    mm5 = pfmul(mm5, mm4);               // original006853c2 pfmul mm5, mm4
    mm1 = punpckldq(mm1, mm3);           // original006853c6 punpckldq mm1, mm3
    store(eax + 0x8u, mm5);              // original006853c9 movq qword ptr [eax + 8], mm5
    store(eax, mm1);                     // original006853cd movq qword ptr [eax], mm1
    empty();                             // original006853d0 femms
    return eax;                          // original006853d2 ret 8
L_006853d5:;
    zero = ((ecx & 0x10u) == 0); // original006853d5 test ecx, 0x10
    eax = word(arguments + 0);   // original006853db mov eax, dword ptr [esp + 4]
    if (zero)
        goto L_00685449; // original006853df je 0x685449
    mm2 = pfadd(mm2, pair(reinterpret_cast<u32>(
                         dat_006f0150))); // original006853e1 pfadd mm2, qword ptr [0x6f0150]
    mm1 = punpckhdq(mm1, mm1);            // original006853e9 punpckhdq mm1, mm1
    mm6 = mm5;                            // original006853ec movq mm6, mm5
    mm4 = estimate(mm2);                  // original006853ef pfrsqrt mm4, mm2
    mm3 = single(edx + 0x18u);            // original006853f3 movd mm3, dword ptr [edx + 0x18]
    mm6 = punpckhdq(mm6, mm6);            // original006853f7 punpckhdq mm6, mm6
    mm0 = mm4;                            // original006853fa movq mm0, mm4
    mm4 = pfmul(mm4, mm4);                // original006853fd pfmul mm4, mm4
    mm2 = punpckldq(mm2, mm2);            // original00685401 punpckldq mm2, mm2
    mm6 = unpack_memory(mm6, edx + 0x8u); // original00685404 punpckldq mm6, dword ptr [edx + 8]
    mm3 = punpckldq(mm3, mm5);            // original00685408 punpckldq mm3, mm5
    mm4 = pfrsqit1(mm4, mm2);             // original0068540b pfrsqit1 mm4, mm2
    mm7 = single(edx + 0x10u);            // original0068540f movd mm7, dword ptr [edx + 0x10]
    mm4 = pfrcpit2(mm4, mm0);             // original00685413 pfrcpit2 mm4, mm0
    mm6 = pxor(mm6, pair(reinterpret_cast<u32>(
                        dat_006f0180))); // original00685417 pxor mm6, qword ptr [0x6f0180]
    mm1 = pfadd(mm1, mm7);               // original0068541e pfadd mm1, mm7
    mm4 = pfmul(mm4, pair(reinterpret_cast<u32>(
                         dat_006f01c8))); // original00685422 pfmul mm4, qword ptr [0x6f01c8]
    mm3 = pfadd(mm3, mm6);                // original0068542a pfadd mm3, mm6
    mm1 = pfmul(mm1, mm4);                // original0068542e pfmul mm1, mm4
    mm2 = pfmul(mm2, mm4);                // original00685432 pfmul mm2, mm4
    mm3 = pfmul(mm3, mm4);                // original00685436 pfmul mm3, mm4
    mm1 = punpckldq(mm1, mm2);            // original0068543a punpckldq mm1, mm2
    store(eax + 0x8u, mm3);               // original0068543d movq qword ptr [eax + 8], mm3
    store(eax, mm1);                      // original00685441 movq qword ptr [eax], mm1
    empty();                              // original00685444 femms
    return eax;                           // original00685446 ret 8
L_00685449:;
    mm3 = pfadd(mm3, pair(reinterpret_cast<u32>(
                         dat_006f0150)));  // original00685449 pfadd mm3, qword ptr [0x6f0150]
    mm1 = punpckhdq(mm1, mm1);             // original00685451 punpckhdq mm1, mm1
    mm2 = estimate(mm3);                   // original00685454 pfrsqrt mm2, mm3
    mm4 = single(edx + 0x8u);              // original00685458 movd mm4, dword ptr [edx + 8]
    mm6 = punpckhdq(mm6, mm6);             // original0068545c punpckhdq mm6, mm6
    mm0 = mm2;                             // original0068545f movq mm0, mm2
    mm2 = pfmul(mm2, mm2);                 // original00685462 pfmul mm2, mm2
    mm3 = punpckldq(mm3, mm3);             // original00685466 punpckldq mm3, mm3
    mm5 = unpack_memory(mm5, edx + 0x18u); // original00685469 punpckldq mm5, dword ptr [edx + 0x18]
    mm4 = punpckldq(mm4, mm6);             // original0068546d punpckldq mm4, mm6
    mm2 = pfrsqit1(mm2, mm3);              // original00685470 pfrsqit1 mm2, mm3
    mm7 = single(edx + 0x10u);             // original00685474 movd mm7, dword ptr [edx + 0x10]
    mm2 = pfrcpit2(mm2, mm0);              // original00685478 pfrcpit2 mm2, mm0
    mm1 = pfsub(mm1, mm7);                 // original0068547c pfsub mm1, mm7
    mm5 = pfadd(mm5, mm4);                 // original00685480 pfadd mm5, mm4
    mm2 = pfmul(mm2, pair(reinterpret_cast<u32>(
                         dat_006f01c8))); // original00685484 pfmul mm2, qword ptr [0x6f01c8]
    mm3 = pfmul(mm3, mm2);                // original0068548c pfmul mm3, mm2
    mm1 = pfmul(mm1, mm2);                // original00685490 pfmul mm1, mm2
    mm5 = pfmul(mm5, mm2);                // original00685494 pfmul mm5, mm2
    mm3 = punpckldq(mm3, mm1);            // original00685498 punpckldq mm3, mm1
    store(eax, mm5);                      // original0068549b movq qword ptr [eax], mm5
    store(eax + 0x8u, mm3);               // original0068549e movq qword ptr [eax + 8], mm3
    empty();                              // original006854a2 femms
    return eax;                           // original006854a4 ret 8
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00685292(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00685292\n\taddl $4,%esp\n\tretl $8");
}
