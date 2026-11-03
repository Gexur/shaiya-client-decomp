#include "graphics/render_determinant_amd.h"
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
AMD Packed unpack_low_memory(Packed a, u32 p) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "m"(*reinterpret_cast<const B4*>(p)) : "memory");
    return a;
}
AMD void put_low(u32 p, Packed a) {
    __asm__ volatile("movd %1,%0" : "=m"(*reinterpret_cast<B4*>(p)) : "y"(a) : "memory");
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
AMD Packed pfacc(Packed a, Packed b) {
    __asm__ volatile("pfacc %1,%0" : "+y"(a) : "y"(b));
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
} // namespace
// Complete original0068664b..0068671a, including real caller-word writeback.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068664b(u32* arguments) {
    u32 eax;
    Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    eax = word(arguments);               // original0068664b mov eax, dword ptr [esp + 4]
    mm2 = pair(eax + 0x20u);             // original0068664f movq mm2, qword ptr [eax + 0x20]
    mm1 = pair(eax + 0x28u);             // original00686653 movq mm1, qword ptr [eax + 0x28]
    mm0 = pair(eax + 0x24u);             // original00686657 movq mm0, qword ptr [eax + 0x24]
    mm1 = punpckhdq(mm1, mm1);           // original0068665b punpckhdq mm1, mm1
    mm2 = punpckldq(mm2, mm2);           // original0068665e punpckldq mm2, mm2
    mm5 = pair(eax + 0x30u);             // original00686661 movq mm5, qword ptr [eax + 0x30]
    mm4 = pair(eax + 0x38u);             // original00686665 movq mm4, qword ptr [eax + 0x38]
    mm3 = pair(eax + 0x34u);             // original00686669 movq mm3, qword ptr [eax + 0x34]
    mm4 = punpckhdq(mm4, mm4);           // original0068666d punpckhdq mm4, mm4
    mm5 = punpckldq(mm5, mm5);           // original00686670 punpckldq mm5, mm5
    mm4 = pfmul(mm4, mm0);               // original00686673 pfmul mm4, mm0
    mm1 = pfmul(mm1, mm3);               // original00686677 pfmul mm1, mm3
    mm4 = pfsub(mm4, mm1);               // original0068667b pfsub mm4, mm1
    mm2 = pfmul(mm2, pair(eax + 0x38u)); // original0068667f pfmul mm2, qword ptr [eax + 0x38]
    mm5 = pfmul(mm5, pair(eax + 0x28u)); // original00686684 pfmul mm5, qword ptr [eax + 0x28]
    mm2 = pfsub(mm2, mm5);               // original00686689 pfsub mm2, mm5
    mm3 = pfmul(mm3, pair(eax + 0x20u)); // original0068668d pfmul mm3, qword ptr [eax + 0x20]
    mm0 = pfmul(mm0, pair(eax + 0x30u)); // original00686692 pfmul mm0, qword ptr [eax + 0x30]
    mm3 = pfsub(mm3, mm0);               // original00686697 pfsub mm3, mm0
    mm0 = mm2;                           // original0068669b movq mm0, mm2
    mm0 = punpckhdq(mm0, mm0);           // original0068669e punpckhdq mm0, mm0
    mm0 = punpckldq(mm0, mm4);           // original006866a1 punpckldq mm0, mm4
    mm1 = mm3;                           // original006866a4 movq mm1, mm3
    mm1 = punpckhdq(mm1, mm4);           // original006866a7 punpckhdq mm1, mm4
    mm5 = mm3;                           // original006866aa movq mm5, mm3
    mm5 = punpckldq(mm5, mm2);           // original006866ad punpckldq mm5, mm2
    mm6 = pair(eax + 0x18u);             // original006866b0 movq mm6, qword ptr [eax + 0x18]
    mm7 = mm6;                           // original006866b4 movq mm7, mm6
    mm6 = punpckhdq(mm6, mm6);           // original006866b7 punpckhdq mm6, mm6
    mm4 = pfmul(mm4, pair(eax + 0x10u)); // original006866ba pfmul mm4, qword ptr [eax + 0x10]
    mm3 = pfmul(mm3, mm6);               // original006866bf pfmul mm3, mm6
    mm4 = pfadd(mm4, mm3);               // original006866c3 pfadd mm4, mm3
    mm3 = pair(eax + 0x14u);             // original006866c7 movq mm3, qword ptr [eax + 0x14]
    mm0 = pfmul(mm0, mm3);               // original006866cb pfmul mm0, mm3
    mm4 = pfsub(mm4, mm0);               // original006866cf pfsub mm4, mm0
    mm0 = pair(eax + 0x10u);             // original006866d3 movq mm0, qword ptr [eax + 0x10]
    mm0 = punpckldq(mm0, mm0);           // original006866d7 punpckldq mm0, mm0
    mm6 = pair(eax + 0x8u);              // original006866da movq mm6, qword ptr [eax + 8]
    mm6 = unpack_low_memory(mm6, eax);   // original006866de punpckldq mm6, dword ptr [eax]
    mm4 = pfmul(mm4, mm6);               // original006866e1 pfmul mm4, mm6
    mm6 = pair(eax + 0x8u);              // original006866e5 movq mm6, qword ptr [eax + 8]
    mm6 = punpckhdq(mm6, pair(eax));     // original006866e9 punpckhdq mm6, qword ptr [eax]
    mm5 = pfmul(mm5, mm7);               // original006866ec pfmul mm5, mm7
    mm2 = pfmul(mm2, mm3);               // original006866f0 pfmul mm2, mm3
    mm1 = pfmul(mm1, mm0);               // original006866f4 pfmul mm1, mm0
    mm1 = pfadd(mm1, mm5);               // original006866f8 pfadd mm1, mm5
    mm1 = pfsub(mm1, mm2);               // original006866fc pfsub mm1, mm2
    mm1 = pfmul(mm1, mm6);               // original00686700 pfmul mm1, mm6
    mm4 = pfsub(mm4, mm1);               // original00686704 pfsub mm4, mm1
    mm4 = pfacc(mm4, mm4);               // original00686708 pfacc mm4, mm4
    put_low(reinterpret_cast<u32>(arguments),
            mm4); // original0068670c movd dword ptr [esp + 4], mm4
    empty();      // original00686711 femms
    __asm__ volatile("flds (%0)" ::"r"(arguments)
                     : "st", "memory"); // original00686713 fld dword ptr [esp + 4]
    return eax;                         // original00686717 ret 4
}
extern "C" __attribute__((naked, stdcall)) float FUN_0068664b(const void*) {
    __asm__ volatile(
        "pushl %edx\n\tpushl %ecx\n\tleal 12(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068664b\n\taddl $4,%esp\n\tpopl %ecx\n\tpopl %edx\n\tretl $4");
}
