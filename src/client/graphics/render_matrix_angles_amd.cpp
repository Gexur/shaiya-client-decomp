#include "graphics/render_matrix_angles_amd.h"
#include "graphics/render_quaternion_angles_amd.h"
#include "graphics/render_quaternion_amd.h"
#include "graphics/render_matrix_leaves_amd.h"
#include "graphics/render_3dnow_norm.h"
#include "graphics/render_amd_trig_rotation.h"
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
AMD Packed shift32(Packed p) {
    __asm__ volatile("psrlq $32,%0" : "+y"(p));
    return p;
}
AMD void empty() {
    __asm__ volatile("femms" ::
                         : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st", "st(1)",
                           "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory");
}
AMD Packed trig(Packed input) {
    Packed output;
    __asm__ volatile("movq %1,%%mm0\n\tcalll _FUN_006a6f20\n\tmovq %%mm0,%0"
                     : "=m"(output)
                     : "m"(input)
                     : "eax", "ebx", "ecx", "edx", "esi", "mm0", "mm1", "mm2", "mm3", "mm4", "mm5",
                       "mm6", "mm7", "memory", "cc");
    return output;
}
AMD Packed pfmul(Packed a, Packed b) {
    __asm__ volatile("pfmul %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfadd(Packed a, Packed b) {
    __asm__ volatile("pfadd %1,%0" : "+y"(a) : "y"(b));
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
AMD void store_single(u32 p, Packed v) {
    __asm__ volatile("movd %1,%0" : "=m"(*reinterpret_cast<B4*>(p)) : "y"(v) : "memory");
}
AMD Packed unpack_low_memory(Packed a, u32 p) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return a;
}
} // namespace

// Complete original00687e8a..0068802f.
extern "C" __attribute__((target("mmx"))) u32 recovered_00687e8a(u32 arguments) {
    [[maybe_unused]] u32 eax, edx;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    Packed saved_angles, saved_roll, saved_pitch, quaternion_low, quaternion_high;
    ; // Original private frame/save/argument setup; addresses not equated. // original00687e8a sub esp, 0x14
    ; // Original private frame/save/argument setup; addresses not equated. // original00687e8d mov dword ptr [esp + 0x10], ebp
    ; // Original private frame/save/argument setup; addresses not equated. // original00687e91 lea ebp, [esp + 0x10]
    mm0 = pair(
        reinterpret_cast<u32>(dat_006f01f0)); // original00687e95 movq mm0, qword ptr [0x6f01f0]
    ; // Original private frame/save/argument setup; addresses not equated. // original00687e9c sub esp, 0x20
    ; // Original private frame/save/argument setup; addresses not equated. // original00687e9f mov dword ptr [esp + 4], ebx
    ; // Original private frame/save/argument setup; addresses not equated. // original00687ea3 mov dword ptr [esp], esi
    mm1 = mm0;                               // original00687ea6 movq mm1, mm0
    mm0 = pfmul(mm0, pair(arguments + 12u)); // original00687ea9 pfmul mm0, qword ptr [ebp + 0x14]
    mm1 = pfmul(mm1, pair(arguments + 4u));  // original00687eae pfmul mm1, qword ptr [ebp + 0xc]
    saved_angles = mm1;                      // original00687eb3 movq qword ptr [esp + 0x18], mm1
    mm0 = trig(mm0);                         // original00687eb8 call 0x6a6f20
    saved_roll = mm0;                        // original00687ebd movq qword ptr [esp + 8], mm0
    mm0 = saved_angles;                      // original00687ec2 movq mm0, qword ptr [esp + 0x18]
    mm0 = punpckhdq(mm0, mm0);               // original00687ec7 punpckhdq mm0, mm0
    mm0 = trig(mm0);                         // original00687eca call 0x6a6f20
    saved_pitch = mm0;                       // original00687ecf movq qword ptr [esp + 0x10], mm0
    mm0 = saved_angles;                      // original00687ed4 movq mm0, qword ptr [esp + 0x18]
    mm0 = trig(mm0);                         // original00687ed9 call 0x6a6f20
    mm1 = saved_roll;                        // original00687ede movq mm1, qword ptr [esp + 8]
    mm2 = saved_pitch;                       // original00687ee3 movq mm2, qword ptr [esp + 0x10]
    mm7 = pair(
        reinterpret_cast<u32>(dat_006f0180)); // original00687ee8 movq mm7, qword ptr [0x6f0180]
    mm3 = mm0;                                // original00687eef movq mm3, mm0
    mm4 = mm0;                                // original00687ef2 movq mm4, mm0
    mm5 = mm0;                                // original00687ef5 movq mm5, mm0
    mm0 = punpckldq(mm0, mm0);                // original00687ef8 punpckldq mm0, mm0
    mm3 = punpckldq(mm3, mm3);                // original00687efb punpckldq mm3, mm3
    mm4 = punpckhdq(mm4, mm4);                // original00687efe punpckhdq mm4, mm4
    mm5 = punpckhdq(mm5, mm5);                // original00687f01 punpckhdq mm5, mm5
    mm0 = pxor(mm0, mm7);                     // original00687f04 pxor mm0, mm7
    mm7 = shift32(mm7);                       // original00687f07 psrlq mm7, 0x20
    mm6 = mm2;                                // original00687f0b movq mm6, mm2
    mm2 = punpckldq(mm2, mm2);                // original00687f0e punpckldq mm2, mm2
    mm6 = punpckhdq(mm6, mm6);                // original00687f11 punpckhdq mm6, mm6
    mm5 = pxor(mm5, mm7);                     // original00687f14 pxor mm5, mm7
    mm0 = pfmul(mm0, mm6);                    // original00687f17 pfmul mm0, mm6
    mm3 = pfmul(mm3, mm2);                    // original00687f1b pfmul mm3, mm2
    mm4 = pfmul(mm4, mm2);                    // original00687f1f pfmul mm4, mm2
    mm5 = pfmul(mm5, mm6);                    // original00687f23 pfmul mm5, mm6
    mm7 = mm1;                                // original00687f27 movq mm7, mm1
    mm7 = punpckhdq(mm7, mm7);                // original00687f2a punpckhdq mm7, mm7
    mm7 = punpckldq(mm7, mm1);                // original00687f2d punpckldq mm7, mm1
    mm0 = pfmul(mm0, mm1);                    // original00687f30 pfmul mm0, mm1
    mm3 = pfmul(mm3, mm7);                    // original00687f34 pfmul mm3, mm7
    mm4 = pfmul(mm4, mm7);                    // original00687f38 pfmul mm4, mm7
    mm5 = pfmul(mm5, mm1);                    // original00687f3c pfmul mm5, mm1
    mm0 = pfadd(mm0, mm4);                    // original00687f40 pfadd mm0, mm4
    mm3 = pfadd(mm3, mm5);                    // original00687f44 pfadd mm3, mm5
    quaternion_low = mm0;                     // original00687f48 movq qword ptr [ebp - 0x10], mm0
    quaternion_high = mm3;                    // original00687f4c movq qword ptr [ebp - 8], mm3
    ; // Original private frame/save/argument setup; addresses not equated. // original00687f50 mov esi, dword ptr [esp]
    ; // Original private frame/save/argument setup; addresses not equated. // original00687f53 mov ebx, dword ptr [esp + 4]
    ; // Original private frame/save/argument setup; addresses not equated. // original00687f57 add esp, 0x20
    eax = word(arguments + 0u); // original00687f5a mov eax, dword ptr [ebp + 8]
    mm0 = quaternion_low;       // original00687f5d movq mm0, qword ptr [esp]
    mm1 = quaternion_high;      // original00687f61 movq mm1, qword ptr [esp + 8]
    mm2 = mm0;                  // original00687f66 movq mm2, mm0
    mm3 = mm0;                  // original00687f69 movq mm3, mm0
    mm0 = pfadd(mm0, mm0);      // original00687f6c pfadd mm0, mm0
    mm4 = mm1;                  // original00687f70 movq mm4, mm1
    mm7 = mm1;                  // original00687f73 movq mm7, mm1
    mm1 = pfadd(mm1, mm1);      // original00687f76 pfadd mm1, mm1
    mm2 = punpckhdq(mm2, mm2);  // original00687f7a punpckhdq mm2, mm2
    mm5 = mm0;                  // original00687f7d movq mm5, mm0
    mm4 = punpckhdq(mm4, mm4);  // original00687f80 punpckhdq mm4, mm4
    mm3 = pfmul(mm3, mm0);      // original00687f83 pfmul mm3, mm0
    mm1 = punpckldq(mm1, mm0);  // original00687f87 punpckldq mm1, mm0
    mm7 = punpckldq(mm7, mm7);  // original00687f8a punpckldq mm7, mm7
    mm5 = pfmul(mm5, mm4);      // original00687f8d pfmul mm5, mm4
    mm6 = mm1;                  // original00687f91 movq mm6, mm1
    mm7 = pfmul(mm7, mm1);      // original00687f94 pfmul mm7, mm1
    mm1 = pfmul(mm1, mm2);      // original00687f98 pfmul mm1, mm2
    mm0 = pxor(mm0, mm0);       // original00687f9c pxor mm0, mm0
    mm6 = pfmul(mm6, mm4);      // original00687f9f pfmul mm6, mm4
    mm2 = mm1;                  // original00687fa3 movq mm2, mm1
    mm1 = punpckhdq(mm1, mm7);  // original00687fa6 punpckhdq mm1, mm7
    mm7 = punpckldq(mm7, mm7);  // original00687fa9 punpckldq mm7, mm7
    mm6 = punpckldq(mm6, mm6);  // original00687fac punpckldq mm6, mm6
    store(eax + 0x30u, mm0);    // original00687faf movq qword ptr [eax + 0x30], mm0
    mm7 = pfadd(mm7, mm3);      // original00687fb3 pfadd mm7, mm3
    mm3 = pfacc(mm3, mm3);      // original00687fb7 pfacc mm3, mm3
    mm4 = mm1;                  // original00687fbb movq mm4, mm1
    mm6 = punpckhdq(mm6, mm5);  // original00687fbe punpckhdq mm6, mm5
    mm3 = pfsubr(mm3, pair(reinterpret_cast<u32>(
                          dat_006f0160))); // original00687fc1 pfsubr mm3, qword ptr [0x6f0160]
    mm7 = pfsubr(mm7, pair(reinterpret_cast<u32>(
                          dat_006f0160))); // original00687fc9 pfsubr mm7, qword ptr [0x6f0160]
    mm3 = punpckldq(mm3, mm0);             // original00687fd1 punpckldq mm3, mm0
    mm1 = pfadd(mm1, mm6);                 // original00687fd4 pfadd mm1, mm6
    store(eax + 0x28u, mm3);               // original00687fd8 movq qword ptr [eax + 0x28], mm3
    mm4 = pfsub(mm4, mm6);                 // original00687fdc pfsub mm4, mm6
    mm3 = mm2;                             // original00687fe0 movq mm3, mm2
    mm2 = pfadd(mm2, mm5);                 // original00687fe3 pfadd mm2, mm5
    mm3 = pfsub(mm3, mm5);                 // original00687fe7 pfsub mm3, mm5
    mm5 = mm4;                             // original00687feb movq mm5, mm4
    mm2 = punpckldq(mm2, mm0);             // original00687fee punpckldq mm2, mm0
    mm6 = mm1;                             // original00687ff1 movq mm6, mm1
    mm4 = punpckldq(mm4, mm7);             // original00687ff4 punpckldq mm4, mm7
    mm1 = punpckldq(mm1, mm1);             // original00687ff7 punpckldq mm1, mm1
    store(eax + 0x18u, mm2);               // original00687ffa movq qword ptr [eax + 0x18], mm2
    mm5 = punpckhdq(mm5, mm0);             // original00687ffe punpckhdq mm5, mm0
    mm0 = unpack_low_memory(
        mm0, reinterpret_cast<u32>(
                 dat_006f0160)); // original00688001 punpckldq mm0, dword ptr [0x6f0160]
    store(eax + 0x8u, mm5);      // original00688008 movq qword ptr [eax + 8], mm5
    mm6 = punpckhdq(mm6, mm6);   // original0068800c punpckhdq mm6, mm6
    store(eax + 0x10u, mm4);     // original0068800f movq qword ptr [eax + 0x10], mm4
    mm7 = punpckhdq(mm7, mm1);   // original00688013 punpckhdq mm7, mm1
    mm6 = punpckldq(mm6, mm3);   // original00688016 punpckldq mm6, mm3
    store(eax, mm7);             // original00688019 movq qword ptr [eax], mm7
    store(eax + 0x20u, mm6);     // original0068801c movq qword ptr [eax + 0x20], mm6
    store(eax + 0x38u, mm0);     // original00688020 movq qword ptr [eax + 0x38], mm0
    ; // Original private frame/save/argument setup; addresses not equated. // original00688024 lea esp, [ebp + 4]
    ; // Original private frame/save/argument setup; addresses not equated. // original00688027 mov ebp, dword ptr [ebp]
    empty();    // original0068802a femms
    return eax; // original0068802c ret 0x10
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00687e8a(void*, uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00687e8a\n\taddl $4,%esp\n\tretl $16");
}

// Complete original00688563..0068867e.
extern "C" __attribute__((target("mmx"))) u32 recovered_00688563(u32 arguments) {
    [[maybe_unused]] u32 eax, edx;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    alignas(8) uint32_t normalized[3];
    Packed saved_sine;
    // The actual input is copied8B+4B, then genuinely normalized in place.
    ; // Original private frame/save/argument setup; addresses not equated. // original00688563 mov edi, edi
    ; // Original private frame/save/argument setup; addresses not equated. // original00688565 push ebp
    ; // Original private frame/save/argument setup; addresses not equated. // original00688566 mov ebp, esp
    ; // Original private frame/save/argument setup; addresses not equated. // original00688568 sub esp, 0x18
    edx = word(arguments + 4u); // original0068856b mov edx, dword ptr [ebp + 0xc]
    ; // Original private frame/save/argument setup; addresses not equated. // original0068856e and esp, 0xfffffff8
    ; // Original private frame/save/argument setup; addresses not equated. // original00688571 lea eax, [esp]
    mm0 = pair(edx);          // original00688574 movq mm0, qword ptr [edx]
    mm1 = single(edx + 0x8u); // original00688577 movd mm1, dword ptr [edx + 8]
    ; // Original private frame/save/argument setup; addresses not equated. // original0068857b mov dword ptr [esp + 0x10], esi
    ; // Original private frame/save/argument setup; addresses not equated. // original0068857f mov dword ptr [esp + 0x14], ebx
    store(reinterpret_cast<u32>(normalized), mm0); // original00688583 movq qword ptr [esp], mm0
    store_single(reinterpret_cast<u32>(normalized) + 8u,
                 mm1); // original00688587 movd dword ptr [esp + 8], mm1
    ; // Original private frame/save/argument setup; addresses not equated. // original0068858c push eax
    ; // Original private frame/save/argument setup; addresses not equated. // original0068858d push eax
    FUN_0068a340(reinterpret_cast<float*>(normalized),
                 reinterpret_cast<const float*>(normalized)); // original0068858e call 0x68a340
    mm0 = single(arguments + 8u); // original00688593 movd mm0, dword ptr [ebp + 0x10]
    mm0 = trig(mm0);              // original00688597 call 0x6a6f20
    mm7 = mm0;                    // original0068859c movq mm7, mm0
    mm1 = mm0;                    // original0068859f movq mm1, mm0
    mm0 = pfsubr(mm0, pair(reinterpret_cast<u32>(
                          dat_006f0160))); // original006885a2 pfsubr mm0, qword ptr [0x6f0160]
    mm7 = punpckhdq(mm7, mm7);             // original006885aa punpckhdq mm7, mm7
    mm2 = pair(reinterpret_cast<u32>(normalized)); // original006885ad movq mm2, qword ptr [esp]
    mm3 = single(reinterpret_cast<u32>(normalized) +
                 8u);          // original006885b1 movd mm3, dword ptr [esp + 8]
    mm4 = mm2;                 // original006885b6 movq mm4, mm2
    mm5 = mm3;                 // original006885b9 movq mm5, mm3
    saved_sine = mm7;          // original006885bc movd dword ptr [esp + 0xc], mm7
    mm7 = mm3;                 // original006885c1 movq mm7, mm3
    mm3 = punpckldq(mm3, mm3); // original006885c4 punpckldq mm3, mm3
    mm6 = mm2;                 // original006885c7 movq mm6, mm2
    ; // Original private frame/save/argument setup; addresses not equated. // original006885ca mov esi, dword ptr [esp + 0x10]
    mm2 = punpckhdq(mm2, mm3);  // original006885ce punpckhdq mm2, mm3
    mm3 = pfmul(mm3, mm4);      // original006885d1 pfmul mm3, mm4
    mm0 = punpckldq(mm0, mm0);  // original006885d5 punpckldq mm0, mm0
    mm2 = pfmul(mm2, mm4);      // original006885d8 pfmul mm2, mm4
    mm1 = punpckldq(mm1, mm1);  // original006885dc punpckldq mm1, mm1
    mm2 = pfmul(mm2, mm0);      // original006885df pfmul mm2, mm0
    eax = word(arguments + 0u); // original006885e3 mov eax, dword ptr [ebp + 8]
    mm3 = pfmul(mm3, mm0);      // original006885e6 pfmul mm3, mm0
    mm4 = pfmul(mm4, mm4);      // original006885ea pfmul mm4, mm4
    mm5 = pfmul(mm5, mm5);      // original006885ee pfmul mm5, mm5
    mm4 = pfmul(mm4, mm0);      // original006885f2 pfmul mm4, mm0
    ; // Original private frame/save/argument setup; addresses not equated. // original006885f6 mov ebx, dword ptr [esp + 0x14]
    mm5 = pfmul(mm5, mm0);              // original006885fa pfmul mm5, mm0
    mm4 = pfadd(mm4, mm1);              // original006885fe pfadd mm4, mm1
    mm5 = pfadd(mm5, mm1);              // original00688602 pfadd mm5, mm1
    mm1 = packed_word(low(saved_sine)); // original00688606 movd mm1, dword ptr [esp + 0xc]
    mm0 = pxor(mm0, mm0);               // original0068860b pxor mm0, mm0
    mm1 = punpckldq(mm1, mm1);          // original0068860e punpckldq mm1, mm1
    mm6 = pfmul(mm6, mm1);              // original00688611 pfmul mm6, mm1
    mm5 = punpckldq(mm5, mm0);          // original00688615 punpckldq mm5, mm0
    mm7 = pfmul(mm7, mm1);              // original00688618 pfmul mm7, mm1
    store(eax + 0x30u, mm0);            // original0068861c movq qword ptr [eax + 0x30], mm0
    mm7 = punpckldq(mm7, mm6);          // original00688620 punpckldq mm7, mm6
    mm1 = mm2;                          // original00688623 movq mm1, mm2
    mm6 = punpckhdq(mm6, mm6);          // original00688626 punpckhdq mm6, mm6
    store(eax + 0x28u, mm5);            // original00688629 movq qword ptr [eax + 0x28], mm5
    mm2 = pfsub(mm2, mm7);              // original0068862d pfsub mm2, mm7
    mm1 = pfadd(mm1, mm7);              // original00688631 pfadd mm1, mm7
    mm7 = mm3;                          // original00688635 movq mm7, mm3
    mm3 = pfsub(mm3, mm6);              // original00688638 pfsub mm3, mm6
    mm5 = mm4;                          // original0068863c movq mm5, mm4
    mm4 = punpckldq(mm4, mm1);          // original0068863f punpckldq mm4, mm1
    mm3 = punpckldq(mm3, mm0);          // original00688642 punpckldq mm3, mm0
    mm1 = punpckhdq(mm1, mm0);          // original00688645 punpckhdq mm1, mm0
    store(eax, mm4);                    // original00688648 movq qword ptr [eax], mm4
    mm7 = punpckldq(mm7, mm7);          // original0068864b punpckldq mm7, mm7
    store(eax + 0x8u, mm3);             // original0068864e movq qword ptr [eax + 8], mm3
    mm0 =
        punpckhdq(mm0, pair(reinterpret_cast<u32>(
                           dat_006f0160))); // original00688652 punpckhdq mm0, qword ptr [0x6f0160]
    mm7 = pfadd(mm7, mm6);                  // original00688659 pfadd mm7, mm6
    store(eax + 0x18u, mm1);                // original0068865d movq qword ptr [eax + 0x18], mm1
    mm5 = punpckhdq(mm5, mm5);              // original00688661 punpckhdq mm5, mm5
    store(eax + 0x38u, mm0);                // original00688664 movq qword ptr [eax + 0x38], mm0
    mm7 = punpckhdq(mm7, mm2);              // original00688668 punpckhdq mm7, mm2
    mm2 = punpckldq(mm2, mm5);              // original0068866b punpckldq mm2, mm5
    store(eax + 0x20u, mm7);                // original0068866e movq qword ptr [eax + 0x20], mm7
    store(eax + 0x10u, mm2);                // original00688672 movq qword ptr [eax + 0x10], mm2
    ; // Original private frame/save/argument setup; addresses not equated. // original00688676 mov esp, ebp
    ; // Original private frame/save/argument setup; addresses not equated. // original00688678 pop ebp
    empty();    // original00688679 femms
    return eax; // original0068867b ret 0xc
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00688563(void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00688563\n\taddl $4,%esp\n\tretl $12");
}
