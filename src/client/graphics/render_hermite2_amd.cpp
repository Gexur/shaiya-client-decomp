#include "graphics/render_hermite2_amd.h"
#include "graphics/render_interpolation_amd.h"
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
u32 word(u32 p) {
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
AMD Packed pfsub(Packed a, Packed b) {
    __asm__ volatile("pfsub %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfadd(Packed a, Packed b) {
    __asm__ volatile("pfadd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed punpckldq(Packed a, Packed b) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
} // namespace
// Complete original0068b133..0068b1cb; zero new data.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068b133(u32 arguments) {
    u32 eax, ecx, edx;
    Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;

    empty();                       // original0068b133 femms
    mm0 = single(arguments + 20u); // original0068b135 movd mm0, dword ptr [esp + 0x18]
    mm1 = mm0;                     // original0068b13a movq mm1, mm0
    mm1 = pfmul(mm1, mm1);         // original0068b13d pfmul mm1, mm1
    mm2 = mm1;                     // original0068b141 movq mm2, mm1
    mm2 = pfmul(mm2, mm0);         // original0068b144 pfmul mm2, mm0
    mm3 = pair(
        reinterpret_cast<u32>(dat_006f01f8)); // original0068b148 movq mm3, qword ptr [0x6f01f8]
    mm4 = mm1;                                // original0068b14f movq mm4, mm1
    mm7 = mm2;                                // original0068b152 movq mm7, mm2
    mm7 = pfsub(mm7, mm1);                    // original0068b155 pfsub mm7, mm1
    mm4 = pfmul(mm4, mm3);                    // original0068b159 pfmul mm4, mm3
    mm6 = mm2;                                // original0068b15d movq mm6, mm2
    mm1 = pfmul(mm1, pair(reinterpret_cast<u32>(
                         dat_006f0200))); // original0068b160 pfmul mm1, qword ptr [0x6f0200]
    mm2 = pfmul(mm2, mm3);                // original0068b168 pfmul mm2, mm3
    mm6 = pfsub(mm6, mm4);                // original0068b16c pfsub mm6, mm4
    mm5 = mm1;                            // original0068b170 movq mm5, mm1
    mm1 = pfsub(mm1, mm2);                // original0068b173 pfsub mm1, mm2
    mm6 = pfadd(mm6, mm0);                // original0068b177 pfadd mm6, mm0
    mm2 = pfsub(mm2, mm5);                // original0068b17b pfsub mm2, mm5
    mm2 = pfadd(mm2, pair(reinterpret_cast<u32>(
                         dat_006f01e8))); // original0068b17f pfadd mm2, qword ptr [0x6f01e8]
    eax = word(arguments + 0u);           // original0068b187 mov eax, dword ptr [esp + 4]
    ecx = word(arguments + 4u);           // original0068b18b mov ecx, dword ptr [esp + 8]
    mm1 = punpckldq(mm1, mm1);            // original0068b18f punpckldq mm1, mm1
    edx = word(arguments + 8u);           // original0068b192 mov edx, dword ptr [esp + 0xc]
    mm6 = punpckldq(mm6, mm6);            // original0068b196 punpckldq mm6, mm6
    mm7 = punpckldq(mm7, mm7);            // original0068b199 punpckldq mm7, mm7
    mm2 = punpckldq(mm2, mm2);            // original0068b19c punpckldq mm2, mm2
    mm2 = pfmul(mm2, pair(ecx));          // original0068b19f pfmul mm2, qword ptr [ecx]
    ecx = word(arguments + 12u);          // original0068b1a3 mov ecx, dword ptr [esp + 0x10]
    mm6 = pfmul(mm6, pair(edx));          // original0068b1a7 pfmul mm6, qword ptr [edx]
    edx = word(arguments + 16u);          // original0068b1ab mov edx, dword ptr [esp + 0x14]
    mm2 = pfadd(mm2, mm6);                // original0068b1af pfadd mm2, mm6
    mm1 = pfmul(mm1, pair(ecx));          // original0068b1b3 pfmul mm1, qword ptr [ecx]
    mm7 = pfmul(mm7, pair(edx));          // original0068b1b7 pfmul mm7, qword ptr [edx]
    mm1 = pfadd(mm1, mm7);                // original0068b1bb pfadd mm1, mm7
    mm2 = pfadd(mm2, mm1);                // original0068b1bf pfadd mm2, mm1
    store(eax, mm2);                      // original0068b1c3 movq qword ptr [eax], mm2
    empty();                              // original0068b1c6 femms
    return eax;                           // original0068b1c8 ret 0x18
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068b133(void*, const void*, const void*,
                                                              const void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068b133\n\taddl $4,%esp\n\tretl $24");
}
