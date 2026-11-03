#include "graphics/render_quaternion_angles_amd.h"
#include "graphics/render_3dnow_norm.h"
#include "graphics/render_amd_trig_rotation.h"
#include "graphics/render_geometry_amd.h"
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
} // namespace
extern "C" alignas(8) const uint32_t dat_006f01f0[2] = {0x3f000000u, 0x3f000000u};

// Complete original006854a7..0068556c.
extern "C" __attribute__((target("mmx"))) u32 recovered_006854a7(u32 arguments) {
    [[maybe_unused]] u32 eax;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    Packed saved_angles, saved_roll, saved_pitch;
    empty(); // original006854a7 femms
    mm0 = pair(
        reinterpret_cast<u32>(dat_006f01f0)); // original006854a9 movq mm0, qword ptr [0x6f01f0]
    ; // Original private frame/save/argument setup; no private-address identity claim. // original006854b0 push ebx
    ; // Original private frame/save/argument setup; no private-address identity claim. // original006854b1 push esi
    ; // Original private frame/save/argument setup; no private-address identity claim. // original006854b2 sub esp, 0x18
    mm1 = mm0;                               // original006854b5 movq mm1, mm0
    mm0 = pfmul(mm0, pair(arguments + 12u)); // original006854b8 pfmul mm0, qword ptr [esp + 0x30]
    mm1 = pfmul(mm1, pair(arguments + 4u));  // original006854be pfmul mm1, qword ptr [esp + 0x28]
    saved_angles = mm1;                      // original006854c4 movq qword ptr [esp + 0x10], mm1
    mm0 = trig(mm0);                         // original006854c9 call 0x6a6f20
    saved_roll = mm0;                        // original006854ce movq qword ptr [esp], mm0
    mm0 = saved_angles;                      // original006854d2 movq mm0, qword ptr [esp + 0x10]
    mm0 = punpckhdq(mm0, mm0);               // original006854d7 punpckhdq mm0, mm0
    mm0 = trig(mm0);                         // original006854da call 0x6a6f20
    saved_pitch = mm0;                       // original006854df movq qword ptr [esp + 8], mm0
    mm0 = saved_angles;                      // original006854e4 movq mm0, qword ptr [esp + 0x10]
    mm0 = trig(mm0);                         // original006854e9 call 0x6a6f20
    mm1 = saved_roll;                        // original006854ee movq mm1, qword ptr [esp]
    mm2 = saved_pitch;                       // original006854f2 movq mm2, qword ptr [esp + 8]
    eax = word(arguments);                   // original006854f7 mov eax, dword ptr [esp + 0x24]
    mm7 = pair(
        reinterpret_cast<u32>(dat_006f01e0)); // original006854fb movq mm7, qword ptr [0x6f01e0]
    mm3 = mm0;                                // original00685502 movq mm3, mm0
    mm4 = mm0;                                // original00685505 movq mm4, mm0
    mm5 = mm0;                                // original00685508 movq mm5, mm0
    mm0 = punpckldq(mm0, mm0);                // original0068550b punpckldq mm0, mm0
    mm3 = punpckldq(mm3, mm3);                // original0068550e punpckldq mm3, mm3
    mm4 = punpckhdq(mm4, mm4);                // original00685511 punpckhdq mm4, mm4
    mm5 = punpckhdq(mm5, mm5);                // original00685514 punpckhdq mm5, mm5
    mm0 = pxor(mm0, mm7);                     // original00685517 pxor mm0, mm7
    mm7 = shift32(mm7);                       // original0068551a psrlq mm7, 0x20
    mm6 = mm2;                                // original0068551e movq mm6, mm2
    mm2 = punpckldq(mm2, mm2);                // original00685521 punpckldq mm2, mm2
    mm6 = punpckhdq(mm6, mm6);                // original00685524 punpckhdq mm6, mm6
    mm5 = pxor(mm5, mm7);                     // original00685527 pxor mm5, mm7
    mm0 = pfmul(mm0, mm6);                    // original0068552a pfmul mm0, mm6
    mm3 = pfmul(mm3, mm2);                    // original0068552e pfmul mm3, mm2
    mm4 = pfmul(mm4, mm2);                    // original00685532 pfmul mm4, mm2
    mm5 = pfmul(mm5, mm6);                    // original00685536 pfmul mm5, mm6
    mm7 = mm1;                                // original0068553a movq mm7, mm1
    mm7 = punpckhdq(mm7, mm7);                // original0068553d punpckhdq mm7, mm7
    mm7 = punpckldq(mm7, mm1);                // original00685540 punpckldq mm7, mm1
    mm0 = pfmul(mm0, mm1);                    // original00685543 pfmul mm0, mm1
    mm3 = pfmul(mm3, mm7);                    // original00685547 pfmul mm3, mm7
    mm4 = pfmul(mm4, mm7);                    // original0068554b pfmul mm4, mm7
    mm5 = pfmul(mm5, mm1);                    // original0068554f pfmul mm5, mm1
    mm0 = pfadd(mm0, mm4);                    // original00685553 pfadd mm0, mm4
    mm3 = pfadd(mm3, mm5);                    // original00685557 pfadd mm3, mm5
    store(eax, mm0);                          // original0068555b movq qword ptr [eax], mm0
    store(eax + 0x8u, mm3);                   // original0068555e movq qword ptr [eax + 8], mm3
    empty();                                  // original00685562 femms
    ; // Original private frame/save/argument setup; no private-address identity claim. // original00685564 add esp, 0x18
    ; // Original private frame/save/argument setup; no private-address identity claim. // original00685567 pop esi
    ; // Original private frame/save/argument setup; no private-address identity claim. // original00685568 pop ebx
    return eax; // original00685569 ret 0x10
}
extern "C" __attribute__((naked, stdcall)) void* FUN_006854a7(void*, uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_006854a7\n\taddl $4,%esp\n\tretl $16");
}

// Complete original0068556c..006855d8.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068556c(u32 arguments) {
    [[maybe_unused]] u32 eax;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    alignas(8) uint32_t normalized[3];
    // Genuine68a340 writes all12 bytes before the first read.
    ; // Original private frame/save/argument setup; no private-address identity claim. // original0068556c sub esp, 0x18
    ; // Original private frame/save/argument setup; no private-address identity claim. // original0068556f mov dword ptr [esp + 0x10], ebx
    ; // Original private frame/save/argument setup; no private-address identity claim. // original00685573 mov dword ptr [esp + 0xc], esi
    ; // Original private frame/save/argument setup; no private-address identity claim. // original00685577 mov dword ptr [esp + 0x14], ebp
    ; // Original private frame/save/argument setup; no private-address identity claim. // original0068557b mov ebp, esp
    ; // Original private frame/save/argument setup; no private-address identity claim. // original0068557d and esp, 0xfffffff8
    ; // Original private frame/save/argument setup; no private-address identity claim. // original00685580 mov edx, esp
    empty(); // original00685582 femms
    ; // Original private frame/save/argument setup; no private-address identity claim. // original00685584 push dword ptr [ebp + 0x20]
    ; // Original private frame/save/argument setup; no private-address identity claim. // original00685587 push edx
    FUN_0068a340(
        reinterpret_cast<float*>(normalized),
        reinterpret_cast<const float*>(word(arguments + 4))); // original00685588 call 0x68a340
    mm0 = single(arguments + 8u); // original0068558d movd mm0, dword ptr [ebp + 0x24]
    mm0 = pfmul(mm0, pair(reinterpret_cast<u32>(
                         dat_006f01f0))); // original00685591 pfmul mm0, qword ptr [0x6f01f0]
    mm0 = trig(mm0);                      // original00685599 call 0x6a6f20
    eax = word(arguments);                // original0068559e mov eax, dword ptr [ebp + 0x1c]
    mm1 = pair(reinterpret_cast<u32>(normalized)); // original006855a1 movq mm1, qword ptr [esp]
    mm2 = single(reinterpret_cast<u32>(normalized) +
                 8u);          // original006855a5 movd mm2, dword ptr [esp + 8]
    mm3 = mm0;                 // original006855aa movq mm3, mm0
    mm3 = punpckhdq(mm3, mm3); // original006855ad punpckhdq mm3, mm3
    mm1 = pfmul(mm1, mm3);     // original006855b0 pfmul mm1, mm3
    mm2 = pfmul(mm2, mm3);     // original006855b4 pfmul mm2, mm3
    mm2 = punpckldq(mm2, mm0); // original006855b8 punpckldq mm2, mm0
    store(eax, mm1);           // original006855bb movq qword ptr [eax], mm1
    store(eax + 0x8u, mm2);    // original006855be movq qword ptr [eax + 8], mm2
    empty();                   // original006855c2 femms
    ; // Original private frame/save/argument setup; no private-address identity claim. // original006855c4 mov esp, ebp
    ; // Original private frame/save/argument setup; no private-address identity claim. // original006855c6 mov ebx, dword ptr [esp + 0x10]
    ; // Original private frame/save/argument setup; no private-address identity claim. // original006855ca mov esi, dword ptr [esp + 0xc]
    ; // Original private frame/save/argument setup; no private-address identity claim. // original006855ce mov ebp, dword ptr [esp + 0x14]
    ; // Original private frame/save/argument setup; no private-address identity claim. // original006855d2 add esp, 0x18
    return eax; // original006855d5 ret 0xc
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068556c(void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068556c\n\taddl $4,%esp\n\tretl $12");
}
