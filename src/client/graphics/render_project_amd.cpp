#include "graphics/render_project_amd.h"
#include "graphics/render_sse_vec3_arrays.h"
#include "graphics/render_geometry_amd.h"
#include "graphics/render_interpolation_amd.h"
#include "graphics/render_quaternion_angles_amd.h"
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
AMD void empty() {
    __asm__ volatile("femms" ::
                         : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st", "st(1)",
                           "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory");
}
void zero(u32 p) {
    __asm__ volatile("fldz\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void one(u32 p) {
    __asm__ volatile("fld1\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void multiply(u32 output, u32 left, u32 right) {
    FUN_0068a65b(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(left),
                 reinterpret_cast<const void*>(right));
}
void coordinate(u32 output, u32 input, u32 matrix) {
    FUN_0068a5ce(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(input),
                 reinterpret_cast<const void*>(matrix));
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
AMD Packed pfrcpit1(Packed a, Packed b) {
    __asm__ volatile("pfrcpit1 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfrcpit2(Packed a, Packed b) {
    __asm__ volatile("pfrcpit2 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pi2fd(Packed a) {
    Packed v;
    __asm__ volatile("pi2fd %1,%0" : "=y"(v) : "y"(a));
    return v;
}
AMD Packed pfrcp(Packed a) {
    Packed v;
    __asm__ volatile("pfrcp %1,%0" : "=y"(v) : "y"(a));
    return v;
}
} // namespace

// Complete original0068a65b..0068a824.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068a65b(u32 arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    Packed dead_low2_source, dead_low3_source;
    // The first two PUNPCKHDQ low destination lanes are dead. Retain only their known source until self-dup; no original physical low-lane value is assumed.
    ; // Original frame/save setup; private addresses not equated. // original0068a65b mov edi, edi
    ; // Original frame/save setup; private addresses not equated. // original0068a65d push ebp
    ; // Original frame/save setup; private addresses not equated. // original0068a65e mov ebp, esp
    ecx = word(arguments + 4u); // original0068a660 mov ecx, dword ptr [ebp + 0xc]
    edx = word(arguments + 8u); // original0068a663 mov edx, dword ptr [ebp + 0x10]
    eax = word(arguments + 0u); // original0068a666 mov eax, dword ptr [ebp + 8]
    mm0 = pair(ecx);            // original0068a669 movq mm0, qword ptr [ecx]
    mm1 = pair(ecx + 0x8u);     // original0068a66c movq mm1, qword ptr [ecx + 8]
    mm4 = pair(edx);            // original0068a670 movq mm4, qword ptr [edx]
    dead_low2_source = mm0;     // original0068a673 punpckhdq mm2, mm0
    mm5 = pair(edx + 0x10u);    // original0068a676 movq mm5, qword ptr [edx + 0x10]
    dead_low3_source = mm1;     // original0068a67a punpckhdq mm3, mm1
    mm6 = pair(edx + 0x20u);    // original0068a67d movq mm6, qword ptr [edx + 0x20]
    mm0 = punpckldq(mm0, mm0);  // original0068a681 punpckldq mm0, mm0
    mm1 = punpckldq(mm1, mm1);  // original0068a684 punpckldq mm1, mm1
    mm4 = pfmul(mm4, mm0);      // original0068a687 pfmul mm4, mm0
    mm2 = punpckhdq(dead_low2_source, dead_low2_source); // original0068a68b punpckhdq mm2, mm2
    mm0 = pfmul(mm0, pair(edx + 0x8u)); // original0068a68e pfmul mm0, qword ptr [edx + 8]
    mm7 = pair(edx + 0x30u);            // original0068a693 movq mm7, qword ptr [edx + 0x30]
    mm5 = pfmul(mm5, mm2);              // original0068a697 pfmul mm5, mm2
    mm3 = punpckhdq(dead_low3_source, dead_low3_source); // original0068a69b punpckhdq mm3, mm3
    mm2 = pfmul(mm2, pair(edx + 0x18u)); // original0068a69e pfmul mm2, qword ptr [edx + 0x18]
    mm5 = pfadd(mm5, mm4);               // original0068a6a3 pfadd mm5, mm4
    mm6 = pfmul(mm6, mm1);               // original0068a6a7 pfmul mm6, mm1
    mm2 = pfadd(mm2, mm0);               // original0068a6ab pfadd mm2, mm0
    mm1 = pfmul(mm1, pair(edx + 0x28u)); // original0068a6af pfmul mm1, qword ptr [edx + 0x28]
    mm6 = pfadd(mm6, mm5);               // original0068a6b4 pfadd mm6, mm5
    mm7 = pfmul(mm7, mm3);               // original0068a6b8 pfmul mm7, mm3
    mm2 = pfadd(mm2, mm1);               // original0068a6bc pfadd mm2, mm1
    mm3 = pfmul(mm3, pair(edx + 0x38u)); // original0068a6c0 pfmul mm3, qword ptr [edx + 0x38]
    mm7 = pfadd(mm7, mm6);               // original0068a6c5 pfadd mm7, mm6
    mm0 = pair(ecx + 0x10u);             // original0068a6c9 movq mm0, qword ptr [ecx + 0x10]
    mm3 = pfadd(mm3, mm2);               // original0068a6cd pfadd mm3, mm2
    mm1 = pair(ecx + 0x18u);             // original0068a6d1 movq mm1, qword ptr [ecx + 0x18]
    store(eax, mm7);                     // original0068a6d5 movq qword ptr [eax], mm7
    mm4 = pair(edx);                     // original0068a6d8 movq mm4, qword ptr [edx]
    store(eax + 0x8u, mm3);              // original0068a6db movq qword ptr [eax + 8], mm3
    mm2 = punpckhdq(mm2, mm0);           // original0068a6df punpckhdq mm2, mm0
    mm5 = pair(edx + 0x10u);             // original0068a6e2 movq mm5, qword ptr [edx + 0x10]
    mm3 = punpckhdq(mm3, mm1);           // original0068a6e6 punpckhdq mm3, mm1
    mm6 = pair(edx + 0x20u);             // original0068a6e9 movq mm6, qword ptr [edx + 0x20]
    mm0 = punpckldq(mm0, mm0);           // original0068a6ed punpckldq mm0, mm0
    mm1 = punpckldq(mm1, mm1);           // original0068a6f0 punpckldq mm1, mm1
    mm4 = pfmul(mm4, mm0);               // original0068a6f3 pfmul mm4, mm0
    mm2 = punpckhdq(mm2, mm2);           // original0068a6f7 punpckhdq mm2, mm2
    mm0 = pfmul(mm0, pair(edx + 0x8u));  // original0068a6fa pfmul mm0, qword ptr [edx + 8]
    mm7 = pair(edx + 0x30u);             // original0068a6ff movq mm7, qword ptr [edx + 0x30]
    mm5 = pfmul(mm5, mm2);               // original0068a703 pfmul mm5, mm2
    mm3 = punpckhdq(mm3, mm3);           // original0068a707 punpckhdq mm3, mm3
    mm2 = pfmul(mm2, pair(edx + 0x18u)); // original0068a70a pfmul mm2, qword ptr [edx + 0x18]
    mm5 = pfadd(mm5, mm4);               // original0068a70f pfadd mm5, mm4
    mm6 = pfmul(mm6, mm1);               // original0068a713 pfmul mm6, mm1
    mm2 = pfadd(mm2, mm0);               // original0068a717 pfadd mm2, mm0
    mm1 = pfmul(mm1, pair(edx + 0x28u)); // original0068a71b pfmul mm1, qword ptr [edx + 0x28]
    mm6 = pfadd(mm6, mm5);               // original0068a720 pfadd mm6, mm5
    mm7 = pfmul(mm7, mm3);               // original0068a724 pfmul mm7, mm3
    mm2 = pfadd(mm2, mm1);               // original0068a728 pfadd mm2, mm1
    mm3 = pfmul(mm3, pair(edx + 0x38u)); // original0068a72c pfmul mm3, qword ptr [edx + 0x38]
    mm7 = pfadd(mm7, mm6);               // original0068a731 pfadd mm7, mm6
    mm0 = pair(ecx + 0x20u);             // original0068a735 movq mm0, qword ptr [ecx + 0x20]
    mm3 = pfadd(mm3, mm2);               // original0068a739 pfadd mm3, mm2
    mm1 = pair(ecx + 0x28u);             // original0068a73d movq mm1, qword ptr [ecx + 0x28]
    store(eax + 0x10u, mm7);             // original0068a741 movq qword ptr [eax + 0x10], mm7
    mm4 = pair(edx);                     // original0068a745 movq mm4, qword ptr [edx]
    store(eax + 0x18u, mm3);             // original0068a748 movq qword ptr [eax + 0x18], mm3
    mm2 = punpckhdq(mm2, mm0);           // original0068a74c punpckhdq mm2, mm0
    mm5 = pair(edx + 0x10u);             // original0068a74f movq mm5, qword ptr [edx + 0x10]
    mm3 = punpckhdq(mm3, mm1);           // original0068a753 punpckhdq mm3, mm1
    mm6 = pair(edx + 0x20u);             // original0068a756 movq mm6, qword ptr [edx + 0x20]
    mm0 = punpckldq(mm0, mm0);           // original0068a75a punpckldq mm0, mm0
    mm1 = punpckldq(mm1, mm1);           // original0068a75d punpckldq mm1, mm1
    mm4 = pfmul(mm4, mm0);               // original0068a760 pfmul mm4, mm0
    mm2 = punpckhdq(mm2, mm2);           // original0068a764 punpckhdq mm2, mm2
    mm0 = pfmul(mm0, pair(edx + 0x8u));  // original0068a767 pfmul mm0, qword ptr [edx + 8]
    mm7 = pair(edx + 0x30u);             // original0068a76c movq mm7, qword ptr [edx + 0x30]
    mm5 = pfmul(mm5, mm2);               // original0068a770 pfmul mm5, mm2
    mm3 = punpckhdq(mm3, mm3);           // original0068a774 punpckhdq mm3, mm3
    mm2 = pfmul(mm2, pair(edx + 0x18u)); // original0068a777 pfmul mm2, qword ptr [edx + 0x18]
    mm5 = pfadd(mm5, mm4);               // original0068a77c pfadd mm5, mm4
    mm6 = pfmul(mm6, mm1);               // original0068a780 pfmul mm6, mm1
    mm2 = pfadd(mm2, mm0);               // original0068a784 pfadd mm2, mm0
    mm1 = pfmul(mm1, pair(edx + 0x28u)); // original0068a788 pfmul mm1, qword ptr [edx + 0x28]
    mm6 = pfadd(mm6, mm5);               // original0068a78d pfadd mm6, mm5
    mm7 = pfmul(mm7, mm3);               // original0068a791 pfmul mm7, mm3
    mm2 = pfadd(mm2, mm1);               // original0068a795 pfadd mm2, mm1
    mm3 = pfmul(mm3, pair(edx + 0x38u)); // original0068a799 pfmul mm3, qword ptr [edx + 0x38]
    mm7 = pfadd(mm7, mm6);               // original0068a79e pfadd mm7, mm6
    mm0 = pair(ecx + 0x30u);             // original0068a7a2 movq mm0, qword ptr [ecx + 0x30]
    mm3 = pfadd(mm3, mm2);               // original0068a7a6 pfadd mm3, mm2
    mm1 = pair(ecx + 0x38u);             // original0068a7aa movq mm1, qword ptr [ecx + 0x38]
    store(eax + 0x20u, mm7);             // original0068a7ae movq qword ptr [eax + 0x20], mm7
    mm4 = pair(edx);                     // original0068a7b2 movq mm4, qword ptr [edx]
    store(eax + 0x28u, mm3);             // original0068a7b5 movq qword ptr [eax + 0x28], mm3
    mm2 = punpckhdq(mm2, mm0);           // original0068a7b9 punpckhdq mm2, mm0
    mm5 = pair(edx + 0x10u);             // original0068a7bc movq mm5, qword ptr [edx + 0x10]
    mm3 = punpckhdq(mm3, mm1);           // original0068a7c0 punpckhdq mm3, mm1
    mm6 = pair(edx + 0x20u);             // original0068a7c3 movq mm6, qword ptr [edx + 0x20]
    mm0 = punpckldq(mm0, mm0);           // original0068a7c7 punpckldq mm0, mm0
    mm1 = punpckldq(mm1, mm1);           // original0068a7ca punpckldq mm1, mm1
    mm4 = pfmul(mm4, mm0);               // original0068a7cd pfmul mm4, mm0
    mm2 = punpckhdq(mm2, mm2);           // original0068a7d1 punpckhdq mm2, mm2
    mm0 = pfmul(mm0, pair(edx + 0x8u));  // original0068a7d4 pfmul mm0, qword ptr [edx + 8]
    mm7 = pair(edx + 0x30u);             // original0068a7d9 movq mm7, qword ptr [edx + 0x30]
    mm5 = pfmul(mm5, mm2);               // original0068a7dd pfmul mm5, mm2
    mm3 = punpckhdq(mm3, mm3);           // original0068a7e1 punpckhdq mm3, mm3
    mm2 = pfmul(mm2, pair(edx + 0x18u)); // original0068a7e4 pfmul mm2, qword ptr [edx + 0x18]
    mm5 = pfadd(mm5, mm4);               // original0068a7e9 pfadd mm5, mm4
    mm6 = pfmul(mm6, mm1);               // original0068a7ed pfmul mm6, mm1
    mm2 = pfadd(mm2, mm0);               // original0068a7f1 pfadd mm2, mm0
    mm1 = pfmul(mm1, pair(edx + 0x28u)); // original0068a7f5 pfmul mm1, qword ptr [edx + 0x28]
    mm6 = pfadd(mm6, mm5);               // original0068a7fa pfadd mm6, mm5
    mm7 = pfmul(mm7, mm3);               // original0068a7fe pfmul mm7, mm3
    mm2 = pfadd(mm2, mm1);               // original0068a802 pfadd mm2, mm1
    mm3 = pfmul(mm3, pair(edx + 0x38u)); // original0068a806 pfmul mm3, qword ptr [edx + 0x38]
    mm7 = pfadd(mm7, mm6);               // original0068a80b pfadd mm7, mm6
    mm3 = pfadd(mm3, mm2);               // original0068a80f pfadd mm3, mm2
    store(eax + 0x30u, mm7);             // original0068a813 movq qword ptr [eax + 0x30], mm7
    store(eax + 0x38u, mm3);             // original0068a817 movq qword ptr [eax + 0x38], mm3
    empty();                             // original0068a81b femms
    eax = word(arguments + 0u);          // original0068a81d mov eax, dword ptr [ebp + 8]
    ; // Original frame/save setup; private addresses not equated. // original0068a820 pop ebp
    return eax; // original0068a821 ret 0xc
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068a65b(void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068a65b\n\taddl $4,%esp\n\tretl $12");
}

// Complete original0068a82f..0068a99b.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068a82f(u32 arguments, u32 local) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    // Actual bounded private64 B is supplied as the ABI bridge operand, without initialized contents.
    const u32 third = word(arguments + 20u);
    const bool second_present = word(arguments + 16u) != 0;
    const u32 first = word(arguments + 12u);
    const u32 flags = (third != 0 ? 4u : 0u) | (second_present ? 2u : 0u) | (first != 0 ? 1u : 0u);
    u32 matrix = local;
    switch (flags) {
    case 0:
        zero(local + 56u); // original0068a870/0068a872
        zero(local + 52u); // original0068a875/0068a877
        zero(local + 48u); // original0068a87a/0068a87c
        zero(local + 44u); // original0068a87f/0068a881
        zero(local + 36u); // original0068a884/0068a886
        zero(local + 32u); // original0068a889/0068a88b
        zero(local + 28u); // original0068a88e/0068a890
        zero(local + 24u); // original0068a893/0068a895
        zero(local + 16u); // original0068a898/0068a89a
        zero(local + 12u); // original0068a89d/0068a89f
        zero(local + 8u);  // original0068a8a2/0068a8a4
        zero(local + 4u);  // original0068a8a7/0068a8a9
        one(local + 60u);  // original0068a8ac/0068a8ae
        one(local + 40u);  // original0068a8b1/0068a8b3
        one(local + 20u);  // original0068a8b6/0068a8b8
        one(local + 0u);   // original0068a8bb/0068a8bd
        break;
    case 1:
        matrix = first;
        break;
    case 2:
        matrix = word(arguments + 16u);
        break;
    case 3: {
        empty();
        const u32 again = word(arguments + 16u);
        multiply(local, again, first);
        empty();
        break;
    }
    case 4:
        matrix = third;
        break;
    case 5:
        empty();
        multiply(local, third, first);
        empty();
        break;
    case 6: {
        empty();
        const u32 again = word(arguments + 16u);
        multiply(local, third, again);
        empty();
        break;
    }
    case 7: {
        empty();
        const u32 again = word(arguments + 16u);
        multiply(local, third, again);
        const u32 fresh = word(arguments + 12u);
        multiply(local, local, fresh);
        empty();
        break;
    }
    }
    const u32 input = word(arguments + 4u);
    const u32 output = word(arguments);
    coordinate(output, input, matrix);
    const bool viewport_present = word(arguments + 8u) != 0;
    if (viewport_present) {
        empty();                    // original0068a938 femms
        eax = word(arguments + 0u); // original0068a93a mov eax, dword ptr [ebp + 8]
        ecx = word(arguments + 8u); // original0068a93d mov ecx, dword ptr [ebp + 0x10]
        mm0 = pair(eax);            // original0068a940 movq mm0, qword ptr [eax]
        mm1 = single(eax + 0x8u);   // original0068a943 movd mm1, dword ptr [eax + 8]
        mm2 = pair(ecx);            // original0068a947 movq mm2, qword ptr [ecx]
        mm0 = pxor(mm0, pair(reinterpret_cast<u32>(
                            dat_006f01e0))); // original0068a94a pxor mm0, qword ptr [0x6f01e0]
        mm3 = pair(ecx + 0x8u);              // original0068a951 movq mm3, qword ptr [ecx + 8]
        mm4 = pair(ecx + 0x10u);             // original0068a955 movq mm4, qword ptr [ecx + 0x10]
        mm2 = pi2fd(mm2);                    // original0068a959 pi2fd mm2, mm2
        mm3 = pi2fd(mm3);                    // original0068a95d pi2fd mm3, mm3
        mm0 = pfadd(mm0, pair(reinterpret_cast<u32>(
                             dat_006f01e8))); // original0068a961 pfadd mm0, qword ptr [0x6f01e8]
        mm3 = pfmul(mm3, pair(reinterpret_cast<u32>(
                             dat_006f01f0))); // original0068a969 pfmul mm3, qword ptr [0x6f01f0]
        mm5 = mm4;                            // original0068a971 movq mm5, mm4
        mm5 = punpckhdq(mm5, mm5);            // original0068a974 punpckhdq mm5, mm5
        mm5 = pfsub(mm5, mm4);                // original0068a977 pfsub mm5, mm4
        mm0 = pfmul(mm0, mm3);                // original0068a97b pfmul mm0, mm3
        mm1 = pfmul(mm1, mm5);                // original0068a97f pfmul mm1, mm5
        mm1 = pfadd(mm1, mm4);                // original0068a983 pfadd mm1, mm4
        mm0 = pfadd(mm0, mm2);                // original0068a987 pfadd mm0, mm2
        store(eax, mm0);                      // original0068a98b movq qword ptr [eax], mm0
        store_single(eax + 0x8u, mm1);        // original0068a98e movd dword ptr [eax + 8], mm1
        empty();                              // original0068a992 femms
    }
    return word(arguments);
}
extern "C" __attribute__((naked, stdcall)) void*
FUN_0068a82f(void*, const void*, const void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "subl $64,%esp\n\tleal 68(%esp),%eax\n\tpushl %esp\n\tpushl %eax\n\tcalll _recovered_0068a82f\n\taddl $8,%esp\n\taddl $64,%esp\n\tretl $24");
}
