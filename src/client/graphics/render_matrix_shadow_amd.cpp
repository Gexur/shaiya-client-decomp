#include "graphics/render_matrix_shadow_amd.h"
#include "graphics/render_scale_amd.h"
#include "graphics/render_amd_trig_rotation.h"
#include "graphics/render_normalize_amd.h"
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
template <int N> AMD Packed psllq(Packed v) {
    __asm__ volatile("psllq %1,%0" : "+y"(v) : "i"(N));
    return v;
}
template <int N> AMD Packed psrlq(Packed v) {
    __asm__ volatile("psrlq %1,%0" : "+y"(v) : "i"(N));
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
AMD Packed pfacc(Packed a, Packed b) {
    __asm__ volatile("pfacc %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pxor(Packed a, Packed b) {
    __asm__ volatile("pxor %1,%0" : "+y"(a) : "y"(b));
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

// Complete original0068671a..0068676a.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068671a(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, plane_word;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    eax = word(arguments + 0); // original0068671a mov eax, dword ptr [esp + 4]
    empty();                   // original0068671e femms
    mm4 = single(reinterpret_cast<u32>(arguments) +
                 12u); // original00686720 movd mm4, dword ptr [esp + 0x10]
    mm1 = pair(
        reinterpret_cast<u32>(dat_006f0220));   // original00686725 movq mm1, qword ptr [0x6f0220]
    __asm__ volatile("pxor %0,%0" : "=y"(mm0)); // original0068672c pxor mm0, mm0
    mm2 = pair(
        reinterpret_cast<u32>(dat_006f0228)); // original0068672f movq mm2, qword ptr [0x6f0228]
    mm3 = single(reinterpret_cast<u32>(arguments) +
                 4u); // original00686736 movd mm3, dword ptr [esp + 8]
    mm5 = single(reinterpret_cast<u32>(arguments) +
                 8u);          // original0068673b movd mm5, dword ptr [esp + 0xc]
    mm4 = punpckldq(mm4, mm2); // original00686740 punpckldq mm4, mm2
    mm3 = punpckldq(mm3, mm5); // original00686743 punpckldq mm3, mm5
    store(eax, mm2);           // original00686746 movq qword ptr [eax], mm2
    store(eax + 0x8u, mm0);    // original00686749 movq qword ptr [eax + 8], mm0
    store(eax + 0x10u, mm1);   // original0068674d movq qword ptr [eax + 0x10], mm1
    store(eax + 0x18u, mm0);   // original00686751 movq qword ptr [eax + 0x18], mm0
    store(eax + 0x20u, mm0);   // original00686755 movq qword ptr [eax + 0x20], mm0
    store(eax + 0x28u, mm2);   // original00686759 movq qword ptr [eax + 0x28], mm2
    store(eax + 0x30u, mm3);   // original0068675d movq qword ptr [eax + 0x30], mm3
    store(eax + 0x38u, mm4);   // original00686761 movq qword ptr [eax + 0x38], mm4
    empty();                   // original00686765 femms
    return eax;                // original00686767 ret 0x10
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068671a(void*, uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068671a\n\taddl $4,%esp\n\tretl $16");
}

// Complete original0068676a..00686855.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068676a(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, plane_word;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    alignas(8) u32 normalized[4];
    // All16 bytes are initialized by the genuine normalizer before reads.
    empty(); // original0068676a femms
    // Original private frame/save operation; no private-address identity claim. // original0068676c sub esp, 0x14
    // Original private frame/save operation; no private-address identity claim. // original0068676f mov dword ptr [esp + 0x10], ebp
    // Original private frame/save operation; no private-address identity claim. // original00686773 mov ebp, esp
    // Original private frame/save operation; no private-address identity claim. // original00686775 and esp, 0xfffffff8
    ecx = reinterpret_cast<u32>(normalized); // original00686778 mov ecx, esp
    plane_word = word(arguments + 2);        // original0068677a push dword ptr [ebp + 0x20]
    // Original private frame/save operation; no private-address identity claim. // original0068677d push ecx
    FUN_0068b915(reinterpret_cast<void*>(ecx),
                 reinterpret_cast<const void*>(plane_word)); // original0068677e call 0x68b915
    eax = word(arguments + 0); // original00686783 mov eax, dword ptr [ebp + 0x18]
    ecx = word(arguments + 1); // original00686786 mov ecx, dword ptr [ebp + 0x1c]
    mm0 =
        pair(reinterpret_cast<u32>(normalized) + 0u); // original00686789 movq mm0, qword ptr [esp]
    mm1 = pair(ecx);                                  // original0068678d movq mm1, qword ptr [ecx]
    mm6 = mm1;                                        // original00686790 movq mm6, mm1
    mm1 = pfmul(mm1, mm0);                            // original00686793 pfmul mm1, mm0
    mm2 = pair(reinterpret_cast<u32>(normalized) +
               8u);         // original00686797 movq mm2, qword ptr [esp + 8]
    mm3 = pair(ecx + 0x8u); // original0068679c movq mm3, qword ptr [ecx + 8]
    mm7 = mm3;              // original006867a0 movq mm7, mm3
    mm3 = pfmul(mm3, mm2);  // original006867a3 pfmul mm3, mm2
    mm1 = pfadd(mm1, mm3);  // original006867a7 pfadd mm1, mm3
    mm0 = pxor(mm0, pair(reinterpret_cast<u32>(
                        dat_006f0230))); // original006867ab pxor mm0, qword ptr [0x6f0230]
    mm2 = pxor(mm2, pair(reinterpret_cast<u32>(
                        dat_006f0230))); // original006867b2 pxor mm2, qword ptr [0x6f0230]
    mm1 = pfacc(mm1, mm1);               // original006867b9 pfacc mm1, mm1
    mm4 = mm0;                           // original006867bd movq mm4, mm0
    mm5 = mm0;                           // original006867c0 movq mm5, mm0
    mm3 = punpckldq(mm3, mm1);           // original006867c3 punpckldq mm3, mm1
    mm1 = psllq<32>(mm1);                // original006867c6 psllq mm1, 0x20
    mm3 = psrlq<32>(mm3);                // original006867ca psrlq mm3, 0x20
    mm4 = punpckldq(mm4, mm4);           // original006867ce punpckldq mm4, mm4
    mm5 = punpckldq(mm5, mm5);           // original006867d1 punpckldq mm5, mm5
    mm4 = pfmul(mm4, mm6);               // original006867d4 pfmul mm4, mm6
    mm5 = pfmul(mm5, mm7);               // original006867d8 pfmul mm5, mm7
    mm4 = pfadd(mm4, mm3);               // original006867dc pfadd mm4, mm3
    store(eax, mm4);                     // original006867e0 movq qword ptr [eax], mm4
    store(eax + 0x8u, mm5);              // original006867e3 movq qword ptr [eax + 8], mm5
    mm4 = mm0;                           // original006867e7 movq mm4, mm0
    mm5 = mm0;                           // original006867ea movq mm5, mm0
    mm4 = punpckhdq(mm4, mm4);           // original006867ed punpckhdq mm4, mm4
    mm5 = punpckhdq(mm5, mm5);           // original006867f0 punpckhdq mm5, mm5
    mm4 = pfmul(mm4, mm6);               // original006867f3 pfmul mm4, mm6
    mm5 = pfmul(mm5, mm7);               // original006867f7 pfmul mm5, mm7
    mm4 = pfadd(mm4, mm1);               // original006867fb pfadd mm4, mm1
    store(eax + 0x10u, mm4);             // original006867ff movq qword ptr [eax + 0x10], mm4
    store(eax + 0x18u, mm5);             // original00686803 movq qword ptr [eax + 0x18], mm5
    mm4 = mm2;                           // original00686807 movq mm4, mm2
    mm5 = mm2;                           // original0068680a movq mm5, mm2
    mm4 = punpckldq(mm4, mm4);           // original0068680d punpckldq mm4, mm4
    mm5 = punpckldq(mm5, mm5);           // original00686810 punpckldq mm5, mm5
    mm4 = pfmul(mm4, mm6);               // original00686813 pfmul mm4, mm6
    mm5 = pfmul(mm5, mm7);               // original00686817 pfmul mm5, mm7
    mm5 = pfadd(mm5, mm3);               // original0068681b pfadd mm5, mm3
    store(eax + 0x20u, mm4);             // original0068681f movq qword ptr [eax + 0x20], mm4
    store(eax + 0x28u, mm5);             // original00686823 movq qword ptr [eax + 0x28], mm5
    mm4 = mm2;                           // original00686827 movq mm4, mm2
    mm5 = mm2;                           // original0068682a movq mm5, mm2
    mm4 = punpckhdq(mm4, mm4);           // original0068682d punpckhdq mm4, mm4
    mm5 = punpckhdq(mm5, mm5);           // original00686830 punpckhdq mm5, mm5
    mm4 = pfmul(mm4, mm6);               // original00686833 pfmul mm4, mm6
    mm5 = pfmul(mm5, mm7);               // original00686837 pfmul mm5, mm7
    mm5 = pfadd(mm5, mm1);               // original0068683b pfadd mm5, mm1
    store(eax + 0x30u, mm4);             // original0068683f movq qword ptr [eax + 0x30], mm4
    store(eax + 0x38u, mm5);             // original00686843 movq qword ptr [eax + 0x38], mm5
    // Original private frame/save operation; no private-address identity claim. // original00686847 mov esp, ebp
    // Original private frame/save operation; no private-address identity claim. // original00686849 mov ebp, dword ptr [esp + 0x10]
    // Original private frame/save operation; no private-address identity claim. // original0068684d add esp, 0x14
    empty();    // original00686850 femms
    return eax; // original00686852 ret 0xc
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068676a(void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068676a\n\taddl $4,%esp\n\tretl $12");
}
