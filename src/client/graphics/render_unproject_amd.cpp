#include "graphics/render_unproject_amd.h"
#include "graphics/render_project_amd.h"
#include "graphics/render_amd_inverse.h"
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
void inverse_fast(u32 output, u32 input) {
    FUN_00689f10(reinterpret_cast<D3DMATRIX*>(output), nullptr,
                 reinterpret_cast<const D3DMATRIX*>(input));
}
void inverse_general(u32 output, u32 input) {
    FUN_00689836(reinterpret_cast<D3DMATRIX*>(output), nullptr,
                 reinterpret_cast<const D3DMATRIX*>(input));
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

// Complete original0068a9bb..0068abb8.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068a9bb(u32 arguments, u32 local) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    // Actual incoming caller-stack64 B at rootSP-68 is an explicit ABI memory operand.
    // No contents are initialized here: singular inverse routes retain actual incoming bytes.
    const u32 second = word(arguments + 16u);
    const u32 third = word(arguments + 20u);
    const bool first_present = word(arguments + 12u) != 0;
    const u32 flags = (third != 0 ? 4u : 0u) | (second != 0 ? 2u : 0u) | (first_present ? 1u : 0u);
    switch (flags) {
    case 0:
        zero(local + 56u); // original0068a9fb/0068a9fd
        zero(local + 52u); // original0068aa00/0068aa02
        zero(local + 48u); // original0068aa05/0068aa07
        zero(local + 44u); // original0068aa0a/0068aa0c
        zero(local + 36u); // original0068aa0f/0068aa11
        zero(local + 32u); // original0068aa14/0068aa16
        zero(local + 28u); // original0068aa19/0068aa1b
        zero(local + 24u); // original0068aa1e/0068aa20
        zero(local + 16u); // original0068aa23/0068aa25
        zero(local + 12u); // original0068aa28/0068aa2a
        zero(local + 8u);  // original0068aa2d/0068aa2f
        zero(local + 4u);  // original0068aa32/0068aa34
        one(local + 60u);  // original0068aa37/0068aa39
        one(local + 40u);  // original0068aa3c/0068aa3e
        one(local + 20u);  // original0068aa41/0068aa43
        one(local + 0u);   // original0068aa46/0068aa48
        break;
    case 1: {
        empty();
        const u32 fresh = word(arguments + 12u);
        inverse_fast(local, fresh);
        empty();
        break;
    }
    case 2:
        empty();
        inverse_fast(local, second);
        empty();
        break;
    case 3: {
        empty();
        const u32 fresh = word(arguments + 12u);
        multiply(local, second, fresh);
        inverse_fast(local, local);
        empty();
        break;
    }
    case 4:
        empty();
        inverse_fast(local, third);
        empty();
        break;
    case 5: {
        empty();
        const u32 fresh = word(arguments + 12u);
        multiply(local, third, fresh);
        inverse_fast(local, local);
        empty();
        break;
    }
    case 6:
        empty();
        multiply(local, third, second);
        inverse_fast(local, local);
        empty();
        break;
    case 7: {
        empty();
        multiply(local, third, second);
        const u32 fresh = word(arguments + 12u);
        multiply(local, local, fresh);
        inverse_fast(local, local);
        empty();
        break;
    }
    }
    const bool viewport_present = word(arguments + 8u) != 0;
    if (viewport_present) {
        empty();                    // original0068ab15 femms
        eax = word(arguments + 8u); // original0068ab17 mov eax, dword ptr [ebp + 0x10]
        ecx = word(arguments + 4u); // original0068ab1a mov ecx, dword ptr [ebp + 0xc]
        edx = word(arguments + 0u); // original0068ab1d mov edx, dword ptr [ebp + 8]
        mm1 = pair(eax);            // original0068ab20 movq mm1, qword ptr [eax]
        mm2 = pair(eax + 0x8u);     // original0068ab23 movq mm2, qword ptr [eax + 8]
        mm0 = pair(ecx);            // original0068ab27 movq mm0, qword ptr [ecx]
        mm1 = pi2fd(mm1);           // original0068ab2a pi2fd mm1, mm1
        mm4 = pair(eax + 0x10u);    // original0068ab2e movq mm4, qword ptr [eax + 0x10]
        mm2 = pi2fd(mm2);           // original0068ab32 pi2fd mm2, mm2
        mm3 = mm2;                  // original0068ab36 movq mm3, mm2
        mm3 = punpckhdq(mm3, mm3);  // original0068ab39 punpckhdq mm3, mm3
        mm5 = pfrcp(mm2);           // original0068ab3c pfrcp mm5, mm2
        mm3 = pfrcp(mm3);           // original0068ab40 pfrcp mm3, mm3
        mm0 = pfsub(mm0, mm1);      // original0068ab44 pfsub mm0, mm1
        mm5 = punpckldq(mm5, mm3);  // original0068ab48 punpckldq mm5, mm3
        mm2 = pfrcpit1(mm2, mm5);   // original0068ab4b pfrcpit1 mm2, mm5
        mm3 = single(ecx + 0x8u);   // original0068ab4f movd mm3, dword ptr [ecx + 8]
        mm2 = pfrcpit2(mm2, mm5);   // original0068ab53 pfrcpit2 mm2, mm5
        mm2 = pfmul(mm2, pair(reinterpret_cast<u32>(
                             dat_006f01f8))); // original0068ab57 pfmul mm2, qword ptr [0x6f01f8]
        mm5 = mm4;                            // original0068ab5f movq mm5, mm4
        mm0 = pfmul(mm0, mm2);                // original0068ab62 pfmul mm0, mm2
        mm5 = punpckhdq(mm5, mm5);            // original0068ab66 punpckhdq mm5, mm5
        mm0 = pfsub(mm0, pair(reinterpret_cast<u32>(
                             dat_006f01e8))); // original0068ab69 pfsub mm0, qword ptr [0x6f01e8]
        mm5 = pfsub(mm5, mm4);                // original0068ab71 pfsub mm5, mm4
        mm6 = pfrcp(mm5);                     // original0068ab75 pfrcp mm6, mm5
        mm0 = pxor(mm0, pair(reinterpret_cast<u32>(
                            dat_006f01e0))); // original0068ab79 pxor mm0, qword ptr [0x6f01e0]
        mm5 = pfrcpit1(mm5, mm6);            // original0068ab80 pfrcpit1 mm5, mm6
        mm5 = pfrcpit2(mm5, mm6);            // original0068ab84 pfrcpit2 mm5, mm6
        mm3 = pfsub(mm3, mm4);               // original0068ab88 pfsub mm3, mm4
        mm3 = pfmul(mm3, mm5);               // original0068ab8c pfmul mm3, mm5
        store(edx, mm0);                     // original0068ab90 movq qword ptr [edx], mm0
        store_single(edx + 0x8u, mm3);       // original0068ab93 movd dword ptr [edx + 8], mm3
        empty();                             // original0068ab97 femms
    }
    const u32 input = word(arguments + (viewport_present ? 0u : 4u));
    const u32 output = word(arguments);
    coordinate(output, input, local);
    return word(arguments);
}
extern "C" __attribute__((naked, stdcall)) void*
FUN_0068a9bb(void*, const void*, const void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "subl $68,%esp\n\tleal 72(%esp),%eax\n\tpushl %esp\n\tpushl %eax\n\tcalll _recovered_0068a9bb\n\taddl $8,%esp\n\taddl $68,%esp\n\tretl $24");
}

// Complete original0068abd8..0068ad5b.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068abd8(u32 arguments, u32 local) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    // Actual incoming caller-stack64 B at rootSP-68 is an explicit ABI memory operand.
    // No contents are initialized here: singular inverse routes retain actual incoming bytes.
    const u32 second = word(arguments + 16u);
    const u32 third = word(arguments + 20u);
    const bool first_present = word(arguments + 12u) != 0;
    const u32 flags = (third != 0 ? 4u : 0u) | (second != 0 ? 2u : 0u) | (first_present ? 1u : 0u);
    switch (flags) {
    case 0:
        zero(local + 56u); // original0068ac18/0068ac1a
        zero(local + 52u); // original0068ac1d/0068ac1f
        zero(local + 48u); // original0068ac22/0068ac24
        zero(local + 44u); // original0068ac27/0068ac29
        zero(local + 36u); // original0068ac2c/0068ac2e
        zero(local + 32u); // original0068ac31/0068ac33
        zero(local + 28u); // original0068ac36/0068ac38
        zero(local + 24u); // original0068ac3b/0068ac3d
        zero(local + 16u); // original0068ac40/0068ac42
        zero(local + 12u); // original0068ac45/0068ac47
        zero(local + 8u);  // original0068ac4a/0068ac4c
        zero(local + 4u);  // original0068ac4f/0068ac51
        one(local + 60u);  // original0068ac54/0068ac56
        one(local + 40u);  // original0068ac59/0068ac5b
        one(local + 20u);  // original0068ac5e/0068ac60
        one(local + 0u);   // original0068ac63/0068ac65
        break;
    case 1: {
        const u32 fresh = word(arguments + 12u);
        inverse_general(local, fresh);
        break;
    }
    case 2:
        inverse_general(local, second);
        break;
    case 3: {
        const u32 fresh = word(arguments + 12u);
        multiply(local, second, fresh);
        inverse_general(local, local);
        break;
    }
    case 4:
        inverse_general(local, third);
        break;
    case 5: {
        const u32 fresh = word(arguments + 12u);
        multiply(local, third, fresh);
        inverse_general(local, local);
        break;
    }
    case 6:
        multiply(local, third, second);
        inverse_general(local, local);
        break;
    case 7: {
        multiply(local, third, second);
        const u32 fresh = word(arguments + 12u);
        multiply(local, local, fresh);
        inverse_general(local, local);
        break;
    }
    }
    const bool viewport_present = word(arguments + 8u) != 0;
    if (viewport_present) {
        empty();                    // original0068acb8 femms
        eax = word(arguments + 8u); // original0068acba mov eax, dword ptr [ebp + 0x10]
        ecx = word(arguments + 4u); // original0068acbd mov ecx, dword ptr [ebp + 0xc]
        edx = word(arguments + 0u); // original0068acc0 mov edx, dword ptr [ebp + 8]
        mm1 = pair(eax);            // original0068acc3 movq mm1, qword ptr [eax]
        mm2 = pair(eax + 0x8u);     // original0068acc6 movq mm2, qword ptr [eax + 8]
        mm0 = pair(ecx);            // original0068acca movq mm0, qword ptr [ecx]
        mm1 = pi2fd(mm1);           // original0068accd pi2fd mm1, mm1
        mm4 = pair(eax + 0x10u);    // original0068acd1 movq mm4, qword ptr [eax + 0x10]
        mm2 = pi2fd(mm2);           // original0068acd5 pi2fd mm2, mm2
        mm3 = mm2;                  // original0068acd9 movq mm3, mm2
        mm3 = punpckhdq(mm3, mm3);  // original0068acdc punpckhdq mm3, mm3
        mm5 = pfrcp(mm2);           // original0068acdf pfrcp mm5, mm2
        mm3 = pfrcp(mm3);           // original0068ace3 pfrcp mm3, mm3
        mm0 = pfsub(mm0, mm1);      // original0068ace7 pfsub mm0, mm1
        mm5 = punpckldq(mm5, mm3);  // original0068aceb punpckldq mm5, mm3
        mm2 = pfrcpit1(mm2, mm5);   // original0068acee pfrcpit1 mm2, mm5
        mm3 = single(ecx + 0x8u);   // original0068acf2 movd mm3, dword ptr [ecx + 8]
        mm2 = pfrcpit2(mm2, mm5);   // original0068acf6 pfrcpit2 mm2, mm5
        mm2 = pfmul(mm2, pair(reinterpret_cast<u32>(
                             dat_006f01f8))); // original0068acfa pfmul mm2, qword ptr [0x6f01f8]
        mm5 = mm4;                            // original0068ad02 movq mm5, mm4
        mm0 = pfmul(mm0, mm2);                // original0068ad05 pfmul mm0, mm2
        mm5 = punpckhdq(mm5, mm5);            // original0068ad09 punpckhdq mm5, mm5
        mm0 = pfsub(mm0, pair(reinterpret_cast<u32>(
                             dat_006f01e8))); // original0068ad0c pfsub mm0, qword ptr [0x6f01e8]
        mm5 = pfsub(mm5, mm4);                // original0068ad14 pfsub mm5, mm4
        mm6 = pfrcp(mm5);                     // original0068ad18 pfrcp mm6, mm5
        mm0 = pxor(mm0, pair(reinterpret_cast<u32>(
                            dat_006f01e0))); // original0068ad1c pxor mm0, qword ptr [0x6f01e0]
        mm5 = pfrcpit1(mm5, mm6);            // original0068ad23 pfrcpit1 mm5, mm6
        mm5 = pfrcpit2(mm5, mm6);            // original0068ad27 pfrcpit2 mm5, mm6
        mm3 = pfsub(mm3, mm4);               // original0068ad2b pfsub mm3, mm4
        mm3 = pfmul(mm3, mm5);               // original0068ad2f pfmul mm3, mm5
        store(edx, mm0);                     // original0068ad33 movq qword ptr [edx], mm0
        store_single(edx + 0x8u, mm3);       // original0068ad36 movd dword ptr [edx + 8], mm3
        empty();                             // original0068ad3a femms
    }
    const u32 input = word(arguments + (viewport_present ? 0u : 4u));
    const u32 output = word(arguments);
    coordinate(output, input, local);
    return word(arguments);
}
extern "C" __attribute__((naked, stdcall)) void*
FUN_0068abd8(void*, const void*, const void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "subl $68,%esp\n\tleal 72(%esp),%eax\n\tpushl %esp\n\tpushl %eax\n\tcalll _recovered_0068abd8\n\taddl $8,%esp\n\taddl $68,%esp\n\tretl $24");
}
