#include "graphics/render_geometry_amd.h"
#include "graphics/render_amd_trig_rotation.h"
#include "graphics/render_3dnow_norm.h"
#include "graphics/render_amd_inverse.h"
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
AMD Packed reciprocal(Packed p) {
    Packed v;
    __asm__ volatile("pfrcp %1,%0" : "=y"(v) : "y"(p));
    return v;
}
template <int N> AMD Packed psllq(Packed p) {
    __asm__ volatile("psllq %1,%0" : "+y"(p) : "i"(N));
    return p;
}
template <int N> AMD Packed psrlq(Packed p) {
    __asm__ volatile("psrlq %1,%0" : "+y"(p) : "i"(N));
    return p;
}
AMD Packed estimate(Packed p) {
    Packed v;
    __asm__ volatile("pfrsqrt %1,%0" : "=y"(v) : "y"(p));
    return v;
}
AMD void store(u32 p, Packed v) {
    __asm__ volatile("movq %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "y"(v) : "memory");
}
AMD void store_single(u32 p, Packed v) {
    __asm__ volatile("movd %1,%0" : "=m"(*reinterpret_cast<B4*>(p)) : "y"(v) : "memory");
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
AMD Packed pfrcpit1(Packed a, Packed b) {
    __asm__ volatile("pfrcpit1 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfcmpeq(Packed a, Packed b) {
    __asm__ volatile("pfcmpeq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
// Keep the actual memory instruction: PUNPCKLDQ's observed memory
// access width must not be widened by a separate MOVQ load.
AMD Packed unpack_memory(Packed a, u32 p) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return a;
}
} // namespace
extern "C" alignas(8) const u32 dat_006f01e0[2] = {0x00000000u, 0x80000000u};

// Complete original0068b3e5..0068b519; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068b3e5(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx, ebx, edi;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    // Original same-register no-op. // original0068b3e5 mov edi, edi
    // Original private EBX save/restore; the typed entry preserves EBX. // original0068b3e7 push ebx
    empty();                   // original0068b3e8 femms
    ebx = word(arguments + 1); // original0068b3ea mov ebx, dword ptr [esp + 0xc]
    ecx = word(arguments + 2); // original0068b3ee mov ecx, dword ptr [esp + 0x10]
    edx = word(arguments + 3); // original0068b3f2 mov edx, dword ptr [esp + 0x14]
    eax = word(arguments + 0); // original0068b3f6 mov eax, dword ptr [esp + 8]
    mm0 = pair(ecx);           // original0068b3fa movq mm0, qword ptr [ecx]
    mm1 = pair(edx);           // original0068b3fd movq mm1, qword ptr [edx]
    mm2 = pair(ecx + 0x8u);    // original0068b400 movq mm2, qword ptr [ecx + 8]
    mm3 = pair(edx + 0x8u);    // original0068b404 movq mm3, qword ptr [edx + 8]
    mm4 = mm3;                 // original0068b408 movq mm4, mm3
    mm6 = mm2;                 // original0068b40b movq mm6, mm2
    mm4 = punpckhdq(mm4, mm4); // original0068b40e punpckhdq mm4, mm4
    mm6 = punpckhdq(mm6, mm6); // original0068b411 punpckhdq mm6, mm6
    mm5 = mm2;                 // original0068b414 movq mm5, mm2
    mm7 = mm3;                 // original0068b417 movq mm7, mm3
    mm5 = punpckldq(mm5, mm5); // original0068b41a punpckldq mm5, mm5
    mm7 = punpckldq(mm7, mm7); // original0068b41d punpckldq mm7, mm7
    mm5 = punpckhdq(mm5, mm0); // original0068b420 punpckhdq mm5, mm0
    mm7 = punpckhdq(mm7, mm1); // original0068b423 punpckhdq mm7, mm1
    mm4 = pfmul(mm4, mm5);     // original0068b426 pfmul mm4, mm5
    mm6 = pfmul(mm6, mm7);     // original0068b42a pfmul mm6, mm7
    mm4 = pfsub(mm4, mm6);     // original0068b42e pfsub mm4, mm6
    mm5 = mm0;                 // original0068b432 movq mm5, mm0
    mm5 = punpckhdq(mm5, mm2); // original0068b435 punpckhdq mm5, mm2
    mm6 = mm3;                 // original0068b438 movq mm6, mm3
    mm6 = punpckldq(mm6, mm1); // original0068b43b punpckldq mm6, mm1
    mm5 = pfmul(mm5, mm6);     // original0068b43e pfmul mm5, mm6
    mm6 = mm1;                 // original0068b442 movq mm6, mm1
    mm6 = punpckhdq(mm6, mm3); // original0068b445 punpckhdq mm6, mm3
    mm7 = mm2;                 // original0068b448 movq mm7, mm2
    mm7 = punpckldq(mm7, mm0); // original0068b44b punpckldq mm7, mm0
    mm6 = pfmul(mm6, mm7);     // original0068b44e pfmul mm6, mm7
    mm5 = pfsub(mm5, mm6);     // original0068b452 pfsub mm5, mm6
    mm6 = mm1;                 // original0068b456 movq mm6, mm1
    mm6 = punpckldq(mm6, mm6); // original0068b459 punpckldq mm6, mm6
    mm2 = punpckldq(mm2, mm2); // original0068b45c punpckldq mm2, mm2
    mm2 = punpckhdq(mm2, mm0); // original0068b45f punpckhdq mm2, mm0
    mm3 = punpckldq(mm3, mm3); // original0068b462 punpckldq mm3, mm3
    mm0 = punpckldq(mm0, mm0); // original0068b465 punpckldq mm0, mm0
    mm6 = pfmul(mm6, mm2);     // original0068b468 pfmul mm6, mm2
    mm3 = punpckhdq(mm3, mm1); // original0068b46c punpckhdq mm3, mm1
    mm0 = pfmul(mm0, mm3);     // original0068b46f pfmul mm0, mm3
    mm6 = pfsub(mm6, mm0);     // original0068b473 pfsub mm6, mm0
    mm0 = pair(ebx);           // original0068b477 movq mm0, qword ptr [ebx]
    mm1 = pair(ebx + 0x8u);    // original0068b47a movq mm1, qword ptr [ebx + 8]
    mm7 = pair(
        reinterpret_cast<u32>(dat_006f01e0)); // original0068b47e movq mm7, qword ptr [0x6f01e0]
    mm2 = mm4;                                // original0068b485 movq mm2, mm4
    mm3 = mm0;                                // original0068b488 movq mm3, mm0
    mm2 = punpckldq(mm2, mm2);                // original0068b48b punpckldq mm2, mm2
    mm3 = punpckldq(mm3, mm3);                // original0068b48e punpckldq mm3, mm3
    mm2 = pxor(mm2, mm7);                     // original0068b491 pxor mm2, mm7
    mm0 = punpckhdq(mm0, mm3);                // original0068b494 punpckhdq mm0, mm3
    mm2 = pfmul(mm2, mm0);                    // original0068b497 pfmul mm2, mm0
    mm0 = mm7;                                // original0068b49b movq mm0, mm7
    mm3 = mm4;                                // original0068b49e movq mm3, mm4
    mm7 = mm5;                                // original0068b4a1 movq mm7, mm5
    mm3 = punpckhdq(mm3, mm3);                // original0068b4a4 punpckhdq mm3, mm3
    mm7 = punpckhdq(mm7, mm7);                // original0068b4a7 punpckhdq mm7, mm7
    mm3 = punpckldq(mm3, mm5);                // original0068b4aa punpckldq mm3, mm5
    mm7 = punpckldq(mm7, mm6);                // original0068b4ad punpckldq mm7, mm6
    mm3 = pfmul(mm3, mm1);                    // original0068b4b0 pfmul mm3, mm1
    mm7 = pfmul(mm7, mm1);                    // original0068b4b4 pfmul mm7, mm1
    mm3 = pxor(mm3, mm0);                     // original0068b4b8 pxor mm3, mm0
    mm7 = pxor(mm7, mm0);                     // original0068b4bb pxor mm7, mm0
    mm3 = pfacc(mm3, mm7);                    // original0068b4be pfacc mm3, mm7
    mm7 = mm0;                                // original0068b4c2 movq mm7, mm0
    mm0 = pair(ebx);                          // original0068b4c5 movq mm0, qword ptr [ebx]
    mm2 = pfsub(mm2, mm3);                    // original0068b4c8 pfsub mm2, mm3
    store(eax, mm2);                          // original0068b4cc movq qword ptr [eax], mm2
    mm4 = punpckhdq(mm4, mm5);                // original0068b4cf punpckhdq mm4, mm5
    mm4 = pxor(mm4, mm7);                     // original0068b4d2 pxor mm4, mm7
    mm2 = mm5;                                // original0068b4d5 movq mm2, mm5
    mm7 = psrlq<32>(mm7);                     // original0068b4d8 psrlq mm7, 0x20
    mm2 = punpckldq(mm2, mm6);                // original0068b4dc punpckldq mm2, mm6
    mm2 = pxor(mm2, mm7);                     // original0068b4df pxor mm2, mm7
    mm6 = punpckhdq(mm6, mm6);                // original0068b4e2 punpckhdq mm6, mm6
    mm3 = mm1;                                // original0068b4e5 movq mm3, mm1
    mm3 = punpckldq(mm3, mm3);                // original0068b4e8 punpckldq mm3, mm3
    mm6 = pxor(mm6, mm7);                     // original0068b4eb pxor mm6, mm7
    mm1 = punpckhdq(mm1, mm3);                // original0068b4ee punpckhdq mm1, mm3
    mm7 = psllq<32>(mm7);                     // original0068b4f1 psllq mm7, 0x20
    mm4 = pfmul(mm4, mm0);                    // original0068b4f5 pfmul mm4, mm0
    mm2 = pfmul(mm2, mm0);                    // original0068b4f9 pfmul mm2, mm0
    mm1 = pfmul(mm1, mm6);                    // original0068b4fd pfmul mm1, mm6
    mm4 = pxor(mm4, mm7);                     // original0068b501 pxor mm4, mm7
    mm2 = pxor(mm2, mm7);                     // original0068b504 pxor mm2, mm7
    mm4 = pfacc(mm4, mm2);                    // original0068b507 pfacc mm4, mm2
    mm1 = pfadd(mm1, mm4);                    // original0068b50b pfadd mm1, mm4
    store(eax + 0x8u, mm1);                   // original0068b50f movq qword ptr [eax + 8], mm1
    empty();                                  // original0068b513 femms
    // Original private EBX save/restore; the typed entry preserves EBX. // original0068b515 pop ebx
    return eax; // original0068b516 ret 0x10
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068b3e5(void*, const void*, const void*,
                                                              const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068b3e5\n\taddl $4,%esp\n\tretl $16");
}

// Complete original0068b730..0068b773; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068b730(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx, ebx, edi;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    empty();                   // original0068b730 femms
    eax = word(arguments + 0); // original0068b732 mov eax, dword ptr [esp + 4]
    edx = word(arguments + 2); // original0068b736 mov edx, dword ptr [esp + 0xc]
    ecx = word(arguments + 1); // original0068b73a mov ecx, dword ptr [esp + 8]
    mm0 = pair(edx);           // original0068b73e movq mm0, qword ptr [edx]
    mm1 = single(edx + 0x8u);  // original0068b741 movd mm1, dword ptr [edx + 8]
    mm2 = pair(ecx);           // original0068b745 movq mm2, qword ptr [ecx]
    mm3 = single(ecx + 0x8u);  // original0068b748 movd mm3, dword ptr [ecx + 8]
    mm2 = pfmul(mm2, mm0);     // original0068b74c pfmul mm2, mm0
    mm3 = pfmul(mm3, mm1);     // original0068b750 pfmul mm3, mm1
    mm2 = pfacc(mm2, mm2);     // original0068b754 pfacc mm2, mm2
    mm2 = pfadd(mm2, mm3);     // original0068b758 pfadd mm2, mm3
    store(eax, mm0);           // original0068b75c movq qword ptr [eax], mm0
    mm2 = pxor(mm2, pair(reinterpret_cast<u32>(
                        dat_006f01d8))); // original0068b75f pxor mm2, qword ptr [0x6f01d8]
    store_single(eax + 0x8u, mm1);       // original0068b766 movd dword ptr [eax + 8], mm1
    store_single(eax + 0xcu, mm2);       // original0068b76a movd dword ptr [eax + 0xc], mm2
    empty();                             // original0068b76e femms
    return eax;                          // original0068b770 ret 0xc
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068b730(void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068b730\n\taddl $4,%esp\n\tretl $12");
}

// Complete original0068b773..0068b857; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068b773(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx, ebx, edi;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    empty();                   // original0068b773 femms
    eax = word(arguments + 2); // original0068b775 mov eax, dword ptr [esp + 0xc]
    ecx = word(arguments + 3); // original0068b779 mov ecx, dword ptr [esp + 0x10]
    edx = word(arguments + 1); // original0068b77d mov edx, dword ptr [esp + 8]
    mm3 = pair(
        reinterpret_cast<u32>(dat_006f01e0)); // original0068b781 movq mm3, qword ptr [0x6f01e0]
    mm0 = pair(edx);                          // original0068b788 movq mm0, qword ptr [edx]
    mm1 = single(edx + 0x8u);                 // original0068b78b movd mm1, dword ptr [edx + 8]
    mm2 = mm1;                                // original0068b78f movq mm2, mm1
    mm4 = mm0;                                // original0068b792 movq mm4, mm0
    mm6 = single(ecx + 0x8u);                 // original0068b795 movd mm6, dword ptr [ecx + 8]
    mm1 = punpckldq(mm1, mm1);                // original0068b799 punpckldq mm1, mm1
    mm6 = unpack_memory(mm6, eax + 0x8u);     // original0068b79c punpckldq mm6, dword ptr [eax + 8]
    mm0 = pfsub(mm0, pair(eax));              // original0068b7a0 pfsub mm0, qword ptr [eax]
    mm1 = pfsub(mm1, mm6);                    // original0068b7a4 pfsub mm1, mm6
    mm4 = pfsub(mm4, pair(ecx));              // original0068b7a8 pfsub mm4, qword ptr [ecx]
    __asm__ volatile("pxor %0,%0" : "=y"(mm7)); // original0068b7ac pxor mm7, mm7
    mm7 = pfsub(mm7, mm4);                      // original0068b7af pfsub mm7, mm4
    mm5 = mm0;                                  // original0068b7b3 movq mm5, mm0
    mm0 = punpckhdq(mm0, mm7);                  // original0068b7b6 punpckhdq mm0, mm7
    mm0 = pfmul(mm0, mm1);                      // original0068b7b9 pfmul mm0, mm1
    mm6 = mm7;                                  // original0068b7bd movq mm6, mm7
    mm6 = punpckldq(mm6, mm1);                  // original0068b7c0 punpckldq mm6, mm1
    mm1 = punpckhdq(mm1, mm3);                  // original0068b7c3 punpckhdq mm1, mm3
    mm1 = punpckldq(mm1, mm5);                  // original0068b7c6 punpckldq mm1, mm5
    mm1 = pfmul(mm1, mm6);                      // original0068b7c9 pfmul mm1, mm6
    mm0 = pfacc(mm0, mm1);                      // original0068b7cd pfacc mm0, mm1
    mm0 = pxor(mm0, mm3);                       // original0068b7d1 pxor mm0, mm3
    mm1 = mm4;                                  // original0068b7d4 movq mm1, mm4
    mm4 = punpckldq(mm4, mm7);                  // original0068b7d7 punpckldq mm4, mm7
    mm1 = punpckhdq(mm1, mm4);                  // original0068b7da punpckhdq mm1, mm4
    mm1 = pfmul(mm1, mm5);                      // original0068b7dd pfmul mm1, mm5
    mm1 = pfacc(mm1, mm1);                      // original0068b7e1 pfacc mm1, mm1
    mm6 = mm0;                                  // original0068b7e5 movq mm6, mm0
    mm7 = mm1;                                  // original0068b7e8 movq mm7, mm1
    mm7 = psllq<32>(mm7);                       // original0068b7eb psllq mm7, 0x20
    mm6 = pfmul(mm6, mm6);                      // original0068b7ef pfmul mm6, mm6
    mm7 = pfmul(mm7, mm7);                      // original0068b7f3 pfmul mm7, mm7
    mm6 = pfadd(mm6, mm7);                      // original0068b7f7 pfadd mm6, mm7
    mm6 = pfacc(mm6, mm6);                      // original0068b7fb pfacc mm6, mm6
    mm5 = mm6;                                  // original0068b7ff movq mm5, mm6
    mm4 = estimate(mm6);                        // original0068b802 pfrsqrt mm4, mm6
    mm5 = pfcmpgt(mm5, pair(reinterpret_cast<u32>(
                           dat_006f01d0))); // original0068b806 pfcmpgt mm5, qword ptr [0x6f01d0]
    mm7 = mm4;                              // original0068b80e movq mm7, mm4
    mm7 = pfmul(mm7, mm4);                  // original0068b811 pfmul mm7, mm4
    mm6 = pfrsqit1(mm6, mm7);               // original0068b815 pfrsqit1 mm6, mm7
    mm0 = pand(mm0, mm5);                   // original0068b819 pand mm0, mm5
    mm1 = pand(mm1, mm5);                   // original0068b81c pand mm1, mm5
    mm6 = pfrcpit2(mm6, mm4);               // original0068b81f pfrcpit2 mm6, mm4
    mm0 = pfmul(mm0, mm6);                  // original0068b823 pfmul mm0, mm6
    mm1 = pfmul(mm1, mm6);                  // original0068b827 pfmul mm1, mm6
    eax = word(arguments + 0);              // original0068b82b mov eax, dword ptr [esp + 4]
    mm4 = mm0;                              // original0068b82f movq mm4, mm0
    mm5 = mm1;                              // original0068b832 movq mm5, mm1
    mm0 = pfmul(mm0, pair(edx));            // original0068b835 pfmul mm0, qword ptr [edx]
    mm1 = pfmul(mm1, mm2);                  // original0068b839 pfmul mm1, mm2
    mm0 = pfacc(mm0, mm0);                  // original0068b83d pfacc mm0, mm0
    mm0 = pfadd(mm0, mm1);                  // original0068b841 pfadd mm0, mm1
    mm5 = punpckldq(mm5, mm0);              // original0068b845 punpckldq mm5, mm0
    mm5 = pxor(mm5, mm3);                   // original0068b848 pxor mm5, mm3
    store(eax, mm4);                        // original0068b84b movq qword ptr [eax], mm4
    store(eax + 0x8u, mm5);                 // original0068b84e movq qword ptr [eax + 8], mm5
    empty();                                // original0068b852 femms
    return eax;                             // original0068b854 ret 0x10
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068b773(void*, const void*, const void*,
                                                              const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068b773\n\taddl $4,%esp\n\tretl $16");
}

// Complete original0068b857..0068b915; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068b857(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx, ebx, edi;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    eax = word(arguments + 1);                  // original0068b857 mov eax, dword ptr [esp + 8]
    edx = word(arguments + 3);                  // original0068b85b mov edx, dword ptr [esp + 0x10]
    mm0 = pair(eax);                            // original0068b85f movq mm0, qword ptr [eax]
    mm1 = pair(eax + 0x8u);                     // original0068b862 movq mm1, qword ptr [eax + 8]
    ecx = word(arguments + 2);                  // original0068b866 mov ecx, dword ptr [esp + 0xc]
    mm4 = pair(edx);                            // original0068b86a movq mm4, qword ptr [edx]
    mm5 = single(edx + 0x8u);                   // original0068b86d movd mm5, dword ptr [edx + 8]
    mm3 = mm1;                                  // original0068b871 movq mm3, mm1
    mm2 = mm0;                                  // original0068b874 movq mm2, mm0
    mm6 = pair(ecx);                            // original0068b877 movq mm6, qword ptr [ecx]
    mm2 = pfmul(mm2, mm4);                      // original0068b87a pfmul mm2, mm4
    mm3 = pfmul(mm3, mm5);                      // original0068b87e pfmul mm3, mm5
    mm7 = single(ecx + 0x8u);                   // original0068b882 movd mm7, dword ptr [ecx + 8]
    mm4 = mm0;                                  // original0068b886 movq mm4, mm0
    mm2 = pfadd(mm2, mm3);                      // original0068b889 pfadd mm2, mm3
    mm5 = mm1;                                  // original0068b88d movq mm5, mm1
    mm4 = pfmul(mm4, mm6);                      // original0068b890 pfmul mm4, mm6
    mm5 = pfmul(mm5, mm7);                      // original0068b894 pfmul mm5, mm7
    mm4 = pfadd(mm4, mm5);                      // original0068b898 pfadd mm4, mm5
    __asm__ volatile("pxor %0,%0" : "=y"(mm3)); // original0068b89c pxor mm3, mm3
    mm4 = pfsub(mm4, mm2);                      // original0068b89f pfsub mm4, mm2
    mm7 = unpack_memory(mm7,
                        reinterpret_cast<u32>(
                            dat_006f0150)); // original0068b8a3 punpckldq mm7, dword ptr [0x6f0150]
    mm2 = mm0;                              // original0068b8aa movq mm2, mm0
    mm4 = pfacc(mm4, mm4);                  // original0068b8ad pfacc mm4, mm4
    mm3 = pfcmpeq(mm3, mm4);                // original0068b8b1 pfcmpeq mm3, mm4
    eax = low(mm3);                         // original0068b8b5 movd eax, mm3
    zero = ((eax & eax) == 0);              // original0068b8b8 test eax, eax
    mm5 = reciprocal(mm4);                  // original0068b8ba pfrcp mm5, mm4
    eax = word(arguments + 0);              // original0068b8be mov eax, dword ptr [esp + 4]
    mm3 = mm1;                              // original0068b8c2 movq mm3, mm1
    mm2 = pfmul(mm2, mm6);                  // original0068b8c5 pfmul mm2, mm6
    if (zero)
        goto L_0068b8d2; // original0068b8c9 je 0x68b8d2
    eax = 0u;            // original0068b8cb xor eax, eax
    empty();             // original0068b8cd femms
    return eax;          // original0068b8cf ret 0x10
L_0068b8d2:;
    mm3 = pfmul(mm3, mm7);         // original0068b8d2 pfmul mm3, mm7
    mm4 = pfrcpit1(mm4, mm5);      // original0068b8d6 pfrcpit1 mm4, mm5
    mm2 = pfadd(mm2, mm3);         // original0068b8da pfadd mm2, mm3
    mm3 = pair(edx);               // original0068b8de movq mm3, qword ptr [edx]
    mm4 = pfrcpit2(mm4, mm5);      // original0068b8e1 pfrcpit2 mm4, mm5
    mm2 = pfacc(mm2, mm2);         // original0068b8e5 pfacc mm2, mm2
    mm5 = single(edx + 0x8u);      // original0068b8e9 movd mm5, dword ptr [edx + 8]
    mm3 = pfsub(mm3, mm6);         // original0068b8ed pfsub mm3, mm6
    mm2 = pfmul(mm2, mm4);         // original0068b8f1 pfmul mm2, mm4
    mm5 = pfsub(mm5, mm7);         // original0068b8f5 pfsub mm5, mm7
    mm3 = pfmul(mm3, mm2);         // original0068b8f9 pfmul mm3, mm2
    mm5 = pfmul(mm5, mm2);         // original0068b8fd pfmul mm5, mm2
    mm3 = pfadd(mm3, mm6);         // original0068b901 pfadd mm3, mm6
    mm5 = pfadd(mm5, mm7);         // original0068b905 pfadd mm5, mm7
    store(eax, mm3);               // original0068b909 movq qword ptr [eax], mm3
    store_single(eax + 0x8u, mm5); // original0068b90c movd dword ptr [eax + 8], mm5
    empty();                       // original0068b910 femms
    return eax;                    // original0068b912 ret 0x10
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068b857(void*, const void*, const void*,
                                                              const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068b857\n\taddl $4,%esp\n\tretl $16");
}
