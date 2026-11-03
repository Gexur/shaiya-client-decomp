#include "graphics/render_matrix_leaves_amd.h"
namespace {
using u32 = uint32_t;
using Packed = long long __attribute__((vector_size(8)));
struct B4 {
    unsigned char bytes[4];
};
struct B8 {
    unsigned char bytes[8];
};
#define AMD __attribute__((target("mmx,3dnowa"), always_inline)) inline
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
AMD void store(u32 p, Packed v) {
    __asm__ volatile("movq %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "y"(v) : "memory");
}
AMD Packed swap(Packed a) {
    Packed b;
    __asm__ volatile("pswapd %1,%0" : "=y"(b) : "y"(a));
    return b;
}
// The two actual PUNPCKLDQ memory operands read exactly4bytes. Other
// PF operations in the same routines separately read the complete8B pool.
AMD Packed unpack_memory(Packed a, u32 p) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "m"(*reinterpret_cast<const B4*>(p)) : "memory");
    return a;
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
AMD Packed punpckldq(Packed a, Packed b) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed punpckhdq(Packed a, Packed b) {
    __asm__ volatile("punpckhdq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pxor(Packed a, Packed b) {
    __asm__ volatile("pxor %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfpnacc(Packed a, Packed b) {
    __asm__ volatile("pfpnacc %1,%0" : "+y"(a) : "y"(b));
    return a;
}
} // namespace
extern "C" alignas(8) const uint32_t dat_006f0160[2] = {0x3f800000u, 0x3f800000u};
// Complete original00686a98..00686b07; ordered raw reads/stores and packed dataflow.
extern "C" __attribute__((target("mmx,3dnowa"))) u32 recovered_00686a98(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    edx = word(arguments + 1); // original00686a98 mov edx, dword ptr [esp + 8]
    mm0 = pair(edx);           // original00686a9c movq mm0, qword ptr [edx]
    mm1 = pair(edx + 0x10u);   // original00686a9f movq mm1, qword ptr [edx + 0x10]
    mm3 = pair(edx + 0x28u);   // original00686aa3 movq mm3, qword ptr [edx + 0x28]
    mm4 = pair(edx + 0x38u);   // original00686aa7 movq mm4, qword ptr [edx + 0x38]
    mm2 = mm0;                 // original00686aab movq mm2, mm0
    eax = word(arguments + 0); // original00686aae mov eax, dword ptr [esp + 4]
    mm0 = punpckldq(mm0, mm1); // original00686ab2 punpckldq mm0, mm1
    mm2 = punpckhdq(mm2, mm1); // original00686ab5 punpckhdq mm2, mm1
    mm5 = mm3;                 // original00686ab8 movq mm5, mm3
    store(eax, mm0);           // original00686abb movq qword ptr [eax], mm0
    store(eax + 0x10u, mm2);   // original00686abe movq qword ptr [eax + 0x10], mm2
    mm6 = pair(edx + 0x8u);    // original00686ac2 movq mm6, qword ptr [edx + 8]
    mm3 = punpckldq(mm3, mm4); // original00686ac6 punpckldq mm3, mm4
    mm7 = pair(edx + 0x18u);   // original00686ac9 movq mm7, qword ptr [edx + 0x18]
    mm0 = pair(edx + 0x20u);   // original00686acd movq mm0, qword ptr [edx + 0x20]
    mm5 = punpckhdq(mm5, mm4); // original00686ad1 punpckhdq mm5, mm4
    mm1 = mm6;                 // original00686ad4 movq mm1, mm6
    store(eax + 0x28u, mm3);   // original00686ad7 movq qword ptr [eax + 0x28], mm3
    store(eax + 0x38u, mm5);   // original00686adb movq qword ptr [eax + 0x38], mm5
    mm6 = punpckldq(mm6, mm7); // original00686adf punpckldq mm6, mm7
    mm4 = pair(edx + 0x30u);   // original00686ae2 movq mm4, qword ptr [edx + 0x30]
    mm2 = mm0;                 // original00686ae6 movq mm2, mm0
    mm1 = punpckhdq(mm1, mm7); // original00686ae9 punpckhdq mm1, mm7
    store(eax + 0x20u, mm6);   // original00686aec movq qword ptr [eax + 0x20], mm6
    mm0 = punpckhdq(mm0, mm4); // original00686af0 punpckhdq mm0, mm4
    mm2 = punpckldq(mm2, mm4); // original00686af3 punpckldq mm2, mm4
    store(eax + 0x30u, mm1);   // original00686af6 movq qword ptr [eax + 0x30], mm1
    store(eax + 0x18u, mm0);   // original00686afa movq qword ptr [eax + 0x18], mm0
    store(eax + 0x8u, mm2);    // original00686afe movq qword ptr [eax + 8], mm2
    empty();                   // original00686b02 femms
    return eax;                // original00686b04 ret 8
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00686a98(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00686a98\n\taddl $4,%esp\n\tretl $8");
}
// Complete original00686b07..00686bd9; ordered raw reads/stores and packed dataflow.
extern "C" __attribute__((target("mmx,3dnowa"))) u32 recovered_00686b07(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    eax = word(arguments + 0);                  // original00686b07 mov eax, dword ptr [esp + 4]
    ecx = word(arguments + 1);                  // original00686b0b mov ecx, dword ptr [esp + 8]
    mm0 = pair(ecx);                            // original00686b0f movq mm0, qword ptr [ecx]
    mm1 = pair(ecx + 0x8u);                     // original00686b12 movq mm1, qword ptr [ecx + 8]
    mm2 = mm0;                                  // original00686b16 movq mm2, mm0
    mm3 = mm0;                                  // original00686b19 movq mm3, mm0
    mm0 = pfadd(mm0, mm0);                      // original00686b1c pfadd mm0, mm0
    mm4 = mm1;                                  // original00686b20 movq mm4, mm1
    mm7 = mm1;                                  // original00686b23 movq mm7, mm1
    mm1 = pfadd(mm1, mm1);                      // original00686b26 pfadd mm1, mm1
    mm2 = punpckhdq(mm2, mm2);                  // original00686b2a punpckhdq mm2, mm2
    mm5 = mm0;                                  // original00686b2d movq mm5, mm0
    mm4 = punpckhdq(mm4, mm4);                  // original00686b30 punpckhdq mm4, mm4
    mm3 = pfmul(mm3, mm0);                      // original00686b33 pfmul mm3, mm0
    mm1 = punpckldq(mm1, mm0);                  // original00686b37 punpckldq mm1, mm0
    mm7 = punpckldq(mm7, mm7);                  // original00686b3a punpckldq mm7, mm7
    mm5 = pfmul(mm5, mm4);                      // original00686b3d pfmul mm5, mm4
    mm6 = mm1;                                  // original00686b41 movq mm6, mm1
    mm7 = pfmul(mm7, mm1);                      // original00686b44 pfmul mm7, mm1
    mm1 = pfmul(mm1, mm2);                      // original00686b48 pfmul mm1, mm2
    __asm__ volatile("pxor %0,%0" : "=y"(mm0)); // original00686b4c pxor mm0, mm0
    mm6 = pfmul(mm6, mm4);                      // original00686b4f pfmul mm6, mm4
    mm2 = mm1;                                  // original00686b53 movq mm2, mm1
    mm1 = punpckhdq(mm1, mm7);                  // original00686b56 punpckhdq mm1, mm7
    mm7 = punpckldq(mm7, mm7);                  // original00686b59 punpckldq mm7, mm7
    mm6 = punpckldq(mm6, mm6);                  // original00686b5c punpckldq mm6, mm6
    store(eax + 0x30u, mm0);                    // original00686b5f movq qword ptr [eax + 0x30], mm0
    mm7 = pfadd(mm7, mm3);                      // original00686b63 pfadd mm7, mm3
    mm3 = pfacc(mm3, mm3);                      // original00686b67 pfacc mm3, mm3
    mm4 = mm1;                                  // original00686b6b movq mm4, mm1
    mm6 = punpckhdq(mm6, mm5);                  // original00686b6e punpckhdq mm6, mm5
    mm3 = pfsubr(mm3, pair(reinterpret_cast<u32>(
                          dat_006f0160))); // original00686b71 pfsubr mm3, qword ptr [0x6f0160]
    mm7 = pfsubr(mm7, pair(reinterpret_cast<u32>(
                          dat_006f0160))); // original00686b79 pfsubr mm7, qword ptr [0x6f0160]
    mm3 = punpckldq(mm3, mm0);             // original00686b81 punpckldq mm3, mm0
    mm1 = pfadd(mm1, mm6);                 // original00686b84 pfadd mm1, mm6
    store(eax + 0x28u, mm3);               // original00686b88 movq qword ptr [eax + 0x28], mm3
    mm4 = pfsub(mm4, mm6);                 // original00686b8c pfsub mm4, mm6
    mm3 = mm2;                             // original00686b90 movq mm3, mm2
    mm2 = pfadd(mm2, mm5);                 // original00686b93 pfadd mm2, mm5
    mm3 = pfsub(mm3, mm5);                 // original00686b97 pfsub mm3, mm5
    mm5 = mm4;                             // original00686b9b movq mm5, mm4
    mm2 = punpckldq(mm2, mm0);             // original00686b9e punpckldq mm2, mm0
    mm6 = mm1;                             // original00686ba1 movq mm6, mm1
    mm4 = punpckldq(mm4, mm7);             // original00686ba4 punpckldq mm4, mm7
    mm1 = punpckldq(mm1, mm1);             // original00686ba7 punpckldq mm1, mm1
    store(eax + 0x18u, mm2);               // original00686baa movq qword ptr [eax + 0x18], mm2
    mm5 = punpckhdq(mm5, mm0);             // original00686bae punpckhdq mm5, mm0
    mm0 = unpack_memory(mm0,
                        reinterpret_cast<u32>(
                            dat_006f0160)); // original00686bb1 punpckldq mm0, dword ptr [0x6f0160]
    store(eax + 0x8u, mm5);                 // original00686bb8 movq qword ptr [eax + 8], mm5
    mm6 = punpckhdq(mm6, mm6);              // original00686bbc punpckhdq mm6, mm6
    store(eax + 0x10u, mm4);                // original00686bbf movq qword ptr [eax + 0x10], mm4
    mm7 = punpckhdq(mm7, mm1);              // original00686bc3 punpckhdq mm7, mm1
    mm6 = punpckldq(mm6, mm3);              // original00686bc6 punpckldq mm6, mm3
    store(eax, mm7);                        // original00686bc9 movq qword ptr [eax], mm7
    store(eax + 0x20u, mm6);                // original00686bcc movq qword ptr [eax + 0x20], mm6
    store(eax + 0x38u, mm0);                // original00686bd0 movq qword ptr [eax + 0x38], mm0
    empty();                                // original00686bd4 femms
    return eax;                             // original00686bd6 ret 8
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00686b07(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00686b07\n\taddl $4,%esp\n\tretl $8");
}
// Complete original00686bd9..00686c8e; ordered raw reads/stores and packed dataflow.
extern "C" __attribute__((target("mmx,3dnowa"))) u32 recovered_00686bd9(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    eax = word(arguments + 0); // original00686bd9 mov eax, dword ptr [esp + 4]
    ecx = word(arguments + 1); // original00686bdd mov ecx, dword ptr [esp + 8]
    mm0 = pair(ecx);           // original00686be1 movq mm0, qword ptr [ecx]
    mm1 = pair(ecx + 0x8u);    // original00686be4 movq mm1, qword ptr [ecx + 8]
    mm3 = swap(mm0);           // original00686be8 pswapd mm3, mm0
    mm6 = mm0;                 // original00686bec movq mm6, mm0
    mm2 = mm0;                 // original00686bef movq mm2, mm0
    mm0 = pfadd(mm0, mm0);     // original00686bf2 pfadd mm0, mm0
    mm4 = mm1;                 // original00686bf6 movq mm4, mm1
    mm6 = punpckhdq(mm6, mm1); // original00686bf9 punpckhdq mm6, mm1
    mm1 = pfadd(mm1, mm1);     // original00686bfc pfadd mm1, mm1
    mm5 = mm0;                 // original00686c00 movq mm5, mm0
    mm0 = pfmul(mm0, mm2);     // original00686c03 pfmul mm0, mm2
    mm5 = punpckldq(mm5, mm1); // original00686c07 punpckldq mm5, mm1
    mm2 = pfmul(mm2, mm1);     // original00686c0a pfmul mm2, mm1
    mm3 = pfmul(mm3, mm1);     // original00686c0e pfmul mm3, mm1
    mm1 = pfmul(mm1, mm4);     // original00686c12 pfmul mm1, mm4
    mm6 = pfmul(mm6, mm5);     // original00686c16 pfmul mm6, mm5
    mm4 = mm0;                 // original00686c1a movq mm4, mm0
    mm0 = pfsubr(mm0, pair(reinterpret_cast<u32>(
                          dat_006f0160))); // original00686c1d pfsubr mm0, qword ptr [0x6f0160]
    mm5 = mm1;                             // original00686c25 movq mm5, mm1
    mm1 = punpckldq(mm1, mm1);             // original00686c28 punpckldq mm1, mm1
    mm3 = pfpnacc(mm3, mm3);               // original00686c2b pfpnacc mm3, mm3
    mm4 = pfacc(mm4, mm4);                 // original00686c2f pfacc mm4, mm4
    mm6 = pfpnacc(mm6, mm6);               // original00686c33 pfpnacc mm6, mm6
    mm2 = pfpnacc(mm2, mm2);               // original00686c37 pfpnacc mm2, mm2
    mm0 = pfsub(mm0, mm1);                 // original00686c3b pfsub mm0, mm1
    mm5 = swap(mm2);                       // original00686c3f pswapd mm5, mm2
    mm4 = pfsubr(mm4, pair(reinterpret_cast<u32>(
                          dat_006f0160)));      // original00686c43 pfsubr mm4, qword ptr [0x6f0160]
    __asm__ volatile("pxor %0,%0" : "=y"(mm7)); // original00686c4b pxor mm7, mm7
    mm1 = mm0;                                  // original00686c4e movq mm1, mm0
    store(eax + 0x30u, mm7);                    // original00686c51 movq qword ptr [eax + 0x30], mm7
    mm5 = punpckldq(mm5, mm3);                  // original00686c55 punpckldq mm5, mm3
    mm2 = punpckldq(mm2, mm7);                  // original00686c58 punpckldq mm2, mm7
    mm4 = punpckhdq(mm4, mm7);                  // original00686c5b punpckhdq mm4, mm7
    mm0 = punpckhdq(mm0, mm6);                  // original00686c5e punpckhdq mm0, mm6
    store(eax + 0x20u, mm5);                    // original00686c61 movq qword ptr [eax + 0x20], mm5
    mm3 = punpckhdq(mm3, mm7);                  // original00686c65 punpckhdq mm3, mm7
    store(eax + 0x8u, mm2);                     // original00686c68 movq qword ptr [eax + 8], mm2
    mm6 = punpckldq(mm6, mm1);                  // original00686c6c punpckldq mm6, mm1
    store(eax + 0x28u, mm4);                    // original00686c6f movq qword ptr [eax + 0x28], mm4
    mm7 = unpack_memory(mm7,
                        reinterpret_cast<u32>(
                            dat_006f0160)); // original00686c73 punpckldq mm7, dword ptr [0x6f0160]
    store(eax, mm0);                        // original00686c7a movq qword ptr [eax], mm0
    store(eax + 0x10u, mm6);                // original00686c7d movq qword ptr [eax + 0x10], mm6
    store(eax + 0x18u, mm3);                // original00686c81 movq qword ptr [eax + 0x18], mm3
    store(eax + 0x38u, mm7);                // original00686c85 movq qword ptr [eax + 0x38], mm7
    empty();                                // original00686c89 femms
    return eax;                             // original00686c8b ret 8
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00686bd9(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00686bd9\n\taddl $4,%esp\n\tretl $8");
}
