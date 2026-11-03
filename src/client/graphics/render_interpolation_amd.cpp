#include "graphics/render_interpolation_amd.h"
#include "graphics/render_matrix_leaves_amd.h"
#include "graphics/render_quaternion_amd.h"
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
// Keep the actual memory instruction: PUNPCKLDQ's observed memory
// access width must not be widened by a separate MOVQ load.
AMD Packed unpack_memory(Packed a, u32 p) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return a;
}
} // namespace
extern "C" alignas(8) const u32 dat_006f0170[2] = {0x40400000u, 0x40000000u};
extern "C" alignas(8) const u32 dat_006f01e8[2] = {0x3f800000u, 0x3f800000u};
extern "C" alignas(8) const u32 dat_006f01f8[2] = {0x40000000u, 0x40000000u};
extern "C" alignas(8) const u32 dat_006f0200[2] = {0x40400000u, 0x40400000u};

// Complete original0068b1cb..0068b214; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068b1cb(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    edx = word(arguments + 2); // original0068b1cb mov edx, dword ptr [esp + 0xc]
    ecx = word(arguments + 3); // original0068b1cf mov ecx, dword ptr [esp + 0x10]
    eax = word(arguments + 1); // original0068b1d3 mov eax, dword ptr [esp + 8]
    mm6 = single(reinterpret_cast<u32>(arguments) +
                 16u);         // original0068b1d7 movd mm6, dword ptr [esp + 0x14]
    mm0 = pair(edx);           // original0068b1dc movq mm0, qword ptr [edx]
    mm2 = pair(ecx);           // original0068b1df movq mm2, qword ptr [ecx]
    mm4 = pair(eax);           // original0068b1e2 movq mm4, qword ptr [eax]
    mm6 = punpckldq(mm6, mm6); // original0068b1e5 punpckldq mm6, mm6
    mm7 = single(reinterpret_cast<u32>(arguments) +
                 20u);         // original0068b1e8 movd mm7, dword ptr [esp + 0x18]
    mm0 = pfsub(mm0, mm4);     // original0068b1ed pfsub mm0, mm4
    eax = word(arguments + 0); // original0068b1f1 mov eax, dword ptr [esp + 4]
    mm7 = punpckldq(mm7, mm7); // original0068b1f5 punpckldq mm7, mm7
    mm0 = pfmul(mm0, mm6);     // original0068b1f8 pfmul mm0, mm6
    mm2 = pfsub(mm2, mm4);     // original0068b1fc pfsub mm2, mm4
    mm4 = pfadd(mm4, mm0);     // original0068b200 pfadd mm4, mm0
    mm2 = pfmul(mm2, mm7);     // original0068b204 pfmul mm2, mm7
    mm4 = pfadd(mm4, mm2);     // original0068b208 pfadd mm4, mm2
    store(eax, mm4);           // original0068b20c movq qword ptr [eax], mm4
    empty();                   // original0068b20f femms
    return eax;                // original0068b211 ret 0x18
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068b1cb(void*, const void*, const void*,
                                                              const void*, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068b1cb\n\taddl $4,%esp\n\tretl $24");
}

// Complete original0068b257..0068b302; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068b257(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    mm0 = single(reinterpret_cast<u32>(arguments) +
                 20u);         // original0068b257 movd mm0, dword ptr [esp + 0x18]
    mm1 = mm0;                 // original0068b25c movq mm1, mm0
    mm0 = punpckldq(mm0, mm0); // original0068b25f punpckldq mm0, mm0
    mm0 = pfmul(mm0, mm0);     // original0068b262 pfmul mm0, mm0
    mm1 = unpack_memory(mm1,
                        reinterpret_cast<u32>(
                            dat_006f0160)); // original0068b266 punpckldq mm1, dword ptr [0x6f0160]
    mm0 = pfmul(mm0, mm1);                  // original0068b26d pfmul mm0, mm1
    mm3 = mm1;                              // original0068b271 movq mm3, mm1
    mm1 = pfmul(mm1, mm1);                  // original0068b274 pfmul mm1, mm1
    edx = word(arguments + 1);              // original0068b278 mov edx, dword ptr [esp + 8]
    __asm__ volatile("pxor %0,%0" : "=y"(mm7)); // original0068b27c pxor mm7, mm7
    mm0 = pfsub(mm0, mm1);                      // original0068b27f pfsub mm0, mm1
    mm1 = punpckldq(mm1, mm1);                  // original0068b283 punpckldq mm1, mm1
    mm4 = mm0;                                  // original0068b286 movq mm4, mm0
    mm3 = punpckldq(mm3, mm3);                  // original0068b289 punpckldq mm3, mm3
    mm0 = pfmul(mm0, pair(reinterpret_cast<u32>(
                         dat_006f0170))); // original0068b28c pfmul mm0, qword ptr [0x6f0170]
    mm5 = mm0;                            // original0068b294 movq mm5, mm0
    mm0 = punpckldq(mm0, mm4);            // original0068b297 punpckldq mm0, mm4
    mm3 = pxor(mm3, pair(reinterpret_cast<u32>(
                        dat_006f0180))); // original0068b29a pxor mm3, qword ptr [0x6f0180]
    mm5 = punpckhdq(mm5, mm7);           // original0068b2a1 punpckhdq mm5, mm7
    mm1 = pfadd(mm1, mm3);               // original0068b2a4 pfadd mm1, mm3
    ecx = word(arguments + 2);           // original0068b2a8 mov ecx, dword ptr [esp + 0xc]
    mm1 = pfsub(mm1, mm0);               // original0068b2ac pfsub mm1, mm0
    mm0 = pfsub(mm0, mm5);               // original0068b2b0 pfsub mm0, mm5
    mm2 = mm1;                           // original0068b2b4 movq mm2, mm1
    mm1 = punpckhdq(mm1, mm1);           // original0068b2b7 punpckhdq mm1, mm1
    mm3 = mm0;                           // original0068b2ba movq mm3, mm0
    mm0 = punpckldq(mm0, mm0);           // original0068b2bd punpckldq mm0, mm0
    eax = word(arguments + 3);           // original0068b2c0 mov eax, dword ptr [esp + 0x10]
    mm2 = punpckldq(mm2, mm2);           // original0068b2c4 punpckldq mm2, mm2
    mm1 = pfmul(mm1, pair(edx));         // original0068b2c7 pfmul mm1, qword ptr [edx]
    mm3 = punpckhdq(mm3, mm3);           // original0068b2cb punpckhdq mm3, mm3
    mm0 = pfmul(mm0, pair(ecx));         // original0068b2ce pfmul mm0, qword ptr [ecx]
    mm2 = pfmul(mm2, pair(eax));         // original0068b2d2 pfmul mm2, qword ptr [eax]
    mm0 = pfadd(mm0, mm1);               // original0068b2d6 pfadd mm0, mm1
    edx = word(arguments + 4);           // original0068b2da mov edx, dword ptr [esp + 0x14]
    mm4 = pfadd(mm4, mm5);               // original0068b2de pfadd mm4, mm5
    eax = word(arguments + 0);           // original0068b2e2 mov eax, dword ptr [esp + 4]
    mm0 = pfadd(mm0, mm2);               // original0068b2e6 pfadd mm0, mm2
    mm3 = pfmul(mm3, pair(edx));         // original0068b2ea pfmul mm3, qword ptr [edx]
    mm0 = pfadd(mm0, mm3);               // original0068b2ee pfadd mm0, mm3
    mm0 = pfmul(mm0, pair(reinterpret_cast<u32>(
                         dat_006f01c8))); // original0068b2f2 pfmul mm0, qword ptr [0x6f01c8]
    store(eax, mm0);                      // original0068b2fa movq qword ptr [eax], mm0
    empty();                              // original0068b2fd femms
    return eax;                           // original0068b2ff ret 0x18
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068b257(void*, const void*, const void*,
                                                              const void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068b257\n\taddl $4,%esp\n\tretl $24");
}

// Complete original0068a39f..0068a410; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068a39f(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    edx = word(arguments + 2); // original0068a39f mov edx, dword ptr [esp + 0xc]
    ecx = word(arguments + 3); // original0068a3a3 mov ecx, dword ptr [esp + 0x10]
    eax = word(arguments + 1); // original0068a3a7 mov eax, dword ptr [esp + 8]
    mm0 = pair(edx);           // original0068a3ab movq mm0, qword ptr [edx]
    mm4 = pair(eax);           // original0068a3ae movq mm4, qword ptr [eax]
    mm6 = single(reinterpret_cast<u32>(arguments) +
                 16u);        // original0068a3b1 movd mm6, dword ptr [esp + 0x14]
    mm1 = single(edx + 0x8u); // original0068a3b6 movd mm1, dword ptr [edx + 8]
    mm2 = pair(ecx);          // original0068a3ba movq mm2, qword ptr [ecx]
    mm3 = single(ecx + 0x8u); // original0068a3bd movd mm3, dword ptr [ecx + 8]
    mm5 = single(eax + 0x8u); // original0068a3c1 movd mm5, dword ptr [eax + 8]
    mm0 = pfsub(mm0, mm4);    // original0068a3c5 pfsub mm0, mm4
    mm7 = single(reinterpret_cast<u32>(arguments) +
                 20u);             // original0068a3c9 movd mm7, dword ptr [esp + 0x18]
    mm1 = pfsub(mm1, mm5);         // original0068a3ce pfsub mm1, mm5
    eax = word(arguments + 0);     // original0068a3d2 mov eax, dword ptr [esp + 4]
    mm2 = pfsub(mm2, mm4);         // original0068a3d6 pfsub mm2, mm4
    mm6 = punpckldq(mm6, mm6);     // original0068a3da punpckldq mm6, mm6
    mm3 = pfsub(mm3, mm5);         // original0068a3dd pfsub mm3, mm5
    mm0 = pfmul(mm0, mm6);         // original0068a3e1 pfmul mm0, mm6
    mm7 = punpckldq(mm7, mm7);     // original0068a3e5 punpckldq mm7, mm7
    mm1 = pfmul(mm1, mm6);         // original0068a3e8 pfmul mm1, mm6
    mm0 = pfadd(mm0, mm4);         // original0068a3ec pfadd mm0, mm4
    mm2 = pfmul(mm2, mm7);         // original0068a3f0 pfmul mm2, mm7
    mm1 = pfadd(mm1, mm5);         // original0068a3f4 pfadd mm1, mm5
    mm3 = pfmul(mm3, mm7);         // original0068a3f8 pfmul mm3, mm7
    mm0 = pfadd(mm0, mm2);         // original0068a3fc pfadd mm0, mm2
    mm1 = pfadd(mm1, mm3);         // original0068a400 pfadd mm1, mm3
    store(eax, mm0);               // original0068a404 movq qword ptr [eax], mm0
    store_single(eax + 0x8u, mm1); // original0068a407 movd dword ptr [eax + 8], mm1
    empty();                       // original0068a40b femms
    return eax;                    // original0068a40d ret 0x18
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068a39f(void*, const void*, const void*,
                                                              const void*, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068a39f\n\taddl $4,%esp\n\tretl $24");
}

// Complete original0068a410..0068a4e4; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068a410(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    empty(); // original0068a410 femms
    mm0 = single(reinterpret_cast<u32>(arguments) +
                 20u);     // original0068a412 movd mm0, dword ptr [esp + 0x18]
    mm1 = mm0;             // original0068a417 movq mm1, mm0
    mm1 = pfmul(mm1, mm1); // original0068a41a pfmul mm1, mm1
    mm2 = mm1;             // original0068a41e movq mm2, mm1
    mm2 = pfmul(mm2, mm0); // original0068a421 pfmul mm2, mm0
    mm3 = pair(
        reinterpret_cast<u32>(dat_006f01f8)); // original0068a425 movq mm3, qword ptr [0x6f01f8]
    mm4 = mm1;                                // original0068a42c movq mm4, mm1
    mm7 = mm2;                                // original0068a42f movq mm7, mm2
    mm7 = pfsub(mm7, mm1);                    // original0068a432 pfsub mm7, mm1
    mm4 = pfmul(mm4, mm3);                    // original0068a436 pfmul mm4, mm3
    mm6 = mm2;                                // original0068a43a movq mm6, mm2
    mm1 = pfmul(mm1, pair(reinterpret_cast<u32>(
                         dat_006f0200))); // original0068a43d pfmul mm1, qword ptr [0x6f0200]
    mm2 = pfmul(mm2, mm3);                // original0068a445 pfmul mm2, mm3
    mm6 = pfsub(mm6, mm4);                // original0068a449 pfsub mm6, mm4
    mm5 = mm1;                            // original0068a44d movq mm5, mm1
    mm1 = pfsub(mm1, mm2);                // original0068a450 pfsub mm1, mm2
    mm6 = pfadd(mm6, mm0);                // original0068a454 pfadd mm6, mm0
    mm2 = pfsub(mm2, mm5);                // original0068a458 pfsub mm2, mm5
    mm2 = pfadd(mm2, pair(reinterpret_cast<u32>(
                         dat_006f01e8))); // original0068a45c pfadd mm2, qword ptr [0x6f01e8]
    eax = word(arguments + 4);            // original0068a464 mov eax, dword ptr [esp + 0x14]
    ecx = word(arguments + 3);            // original0068a468 mov ecx, dword ptr [esp + 0x10]
    edx = word(arguments + 2);            // original0068a46c mov edx, dword ptr [esp + 0xc]
    mm7 = punpckldq(mm7, mm7);            // original0068a470 punpckldq mm7, mm7
    mm1 = punpckldq(mm1, mm1);            // original0068a473 punpckldq mm1, mm1
    mm6 = punpckldq(mm6, mm6);            // original0068a476 punpckldq mm6, mm6
    mm2 = punpckldq(mm2, mm2);            // original0068a479 punpckldq mm2, mm2
    mm5 = mm7;                            // original0068a47c movq mm5, mm7
    mm7 = pfmul(mm7, pair(eax));          // original0068a47f pfmul mm7, qword ptr [eax]
    mm0 = mm1;                            // original0068a483 movq mm0, mm1
    mm1 = pfmul(mm1, pair(ecx));          // original0068a486 pfmul mm1, qword ptr [ecx]
    mm4 = single(eax + 0x8u);             // original0068a48a movd mm4, dword ptr [eax + 8]
    mm5 = pfmul(mm5, mm4);                // original0068a48e pfmul mm5, mm4
    mm3 = single(ecx + 0x8u);             // original0068a492 movd mm3, dword ptr [ecx + 8]
    mm0 = pfmul(mm0, mm3);                // original0068a496 pfmul mm0, mm3
    ecx = word(arguments + 1);            // original0068a49a mov ecx, dword ptr [esp + 8]
    eax = word(arguments + 0);            // original0068a49e mov eax, dword ptr [esp + 4]
    mm4 = mm6;                            // original0068a4a2 movq mm4, mm6
    mm6 = pfmul(mm6, pair(edx));          // original0068a4a5 pfmul mm6, qword ptr [edx]
    mm3 = mm2;                            // original0068a4a9 movq mm3, mm2
    mm1 = pfadd(mm1, mm7);                // original0068a4ac pfadd mm1, mm7
    mm0 = pfadd(mm0, mm5);                // original0068a4b0 pfadd mm0, mm5
    mm2 = pfmul(mm2, pair(ecx));          // original0068a4b4 pfmul mm2, qword ptr [ecx]
    mm7 = single(edx + 0x8u);             // original0068a4b8 movd mm7, dword ptr [edx + 8]
    mm4 = pfmul(mm4, mm7);                // original0068a4bc pfmul mm4, mm7
    mm5 = single(ecx + 0x8u);             // original0068a4c0 movd mm5, dword ptr [ecx + 8]
    mm3 = pfmul(mm3, mm5);                // original0068a4c4 pfmul mm3, mm5
    mm2 = pfadd(mm2, mm6);                // original0068a4c8 pfadd mm2, mm6
    mm3 = pfadd(mm3, mm4);                // original0068a4cc pfadd mm3, mm4
    mm1 = pfadd(mm1, mm2);                // original0068a4d0 pfadd mm1, mm2
    mm0 = pfadd(mm0, mm3);                // original0068a4d4 pfadd mm0, mm3
    store(eax, mm1);                      // original0068a4d8 movq qword ptr [eax], mm1
    store_single(eax + 0x8u, mm0);        // original0068a4db movd dword ptr [eax + 8], mm0
    empty();                              // original0068a4df femms
    return eax;                           // original0068a4e1 ret 0x18
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068a410(void*, const void*, const void*,
                                                              const void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068a410\n\taddl $4,%esp\n\tretl $24");
}

// Complete original0068a4e4..0068a5ce; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068a4e4(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    mm0 = single(reinterpret_cast<u32>(arguments) +
                 20u);         // original0068a4e4 movd mm0, dword ptr [esp + 0x18]
    edx = word(arguments + 1); // original0068a4e9 mov edx, dword ptr [esp + 8]
    mm1 = mm0;                 // original0068a4ed movq mm1, mm0
    mm0 = punpckldq(mm0, mm0); // original0068a4f0 punpckldq mm0, mm0
    mm0 = pfmul(mm0, mm0);     // original0068a4f3 pfmul mm0, mm0
    mm1 = unpack_memory(mm1,
                        reinterpret_cast<u32>(
                            dat_006f0160)); // original0068a4f7 punpckldq mm1, dword ptr [0x6f0160]
    mm0 = pfmul(mm0, mm1);                  // original0068a4fe pfmul mm0, mm1
    mm3 = mm1;                              // original0068a502 movq mm3, mm1
    mm1 = pfmul(mm1, mm1);                  // original0068a505 pfmul mm1, mm1
    __asm__ volatile("pxor %0,%0" : "=y"(mm7)); // original0068a509 pxor mm7, mm7
    mm0 = pfsub(mm0, mm1);                      // original0068a50c pfsub mm0, mm1
    mm1 = punpckldq(mm1, mm1);                  // original0068a510 punpckldq mm1, mm1
    mm4 = mm0;                                  // original0068a513 movq mm4, mm0
    mm3 = punpckldq(mm3, mm3);                  // original0068a516 punpckldq mm3, mm3
    mm0 = pfmul(mm0, pair(reinterpret_cast<u32>(
                         dat_006f0170))); // original0068a519 pfmul mm0, qword ptr [0x6f0170]
    mm5 = mm0;                            // original0068a521 movq mm5, mm0
    mm0 = punpckldq(mm0, mm4);            // original0068a524 punpckldq mm0, mm4
    mm3 = pxor(mm3, pair(reinterpret_cast<u32>(
                        dat_006f0180))); // original0068a527 pxor mm3, qword ptr [0x6f0180]
    mm5 = punpckhdq(mm5, mm7);           // original0068a52e punpckhdq mm5, mm7
    mm1 = pfadd(mm1, mm3);               // original0068a531 pfadd mm1, mm3
    mm1 = pfsub(mm1, mm0);               // original0068a535 pfsub mm1, mm0
    ecx = word(arguments + 2);           // original0068a539 mov ecx, dword ptr [esp + 0xc]
    mm0 = pfsub(mm0, mm5);               // original0068a53d pfsub mm0, mm5
    mm2 = mm1;                           // original0068a541 movq mm2, mm1
    mm1 = punpckhdq(mm1, mm1);           // original0068a544 punpckhdq mm1, mm1
    mm3 = mm0;                           // original0068a547 movq mm3, mm0
    mm0 = punpckldq(mm0, mm0);           // original0068a54a punpckldq mm0, mm0
    eax = word(arguments + 3);           // original0068a54d mov eax, dword ptr [esp + 0x10]
    mm2 = punpckldq(mm2, mm2);           // original0068a551 punpckldq mm2, mm2
    mm7 = single(edx + 0x8u);            // original0068a554 movd mm7, dword ptr [edx + 8]
    mm4 = mm1;                           // original0068a558 movq mm4, mm1
    mm1 = pfmul(mm1, pair(edx));         // original0068a55b pfmul mm1, qword ptr [edx]
    mm3 = punpckhdq(mm3, mm3);           // original0068a55f punpckhdq mm3, mm3
    mm5 = mm0;                           // original0068a562 movq mm5, mm0
    mm0 = pfmul(mm0, pair(ecx));         // original0068a565 pfmul mm0, qword ptr [ecx]
    mm6 = mm2;                           // original0068a569 movq mm6, mm2
    mm2 = pfmul(mm2, pair(eax));         // original0068a56c pfmul mm2, qword ptr [eax]
    mm4 = pfmul(mm4, mm7);               // original0068a570 pfmul mm4, mm7
    edx = word(arguments + 4);           // original0068a574 mov edx, dword ptr [esp + 0x14]
    mm7 = single(ecx + 0x8u);            // original0068a578 movd mm7, dword ptr [ecx + 8]
    mm5 = pfmul(mm5, mm7);               // original0068a57c pfmul mm5, mm7
    mm0 = pfadd(mm0, mm1);               // original0068a580 pfadd mm0, mm1
    mm7 = single(eax + 0x8u);            // original0068a584 movd mm7, dword ptr [eax + 8]
    mm6 = pfmul(mm6, mm7);               // original0068a588 pfmul mm6, mm7
    eax = word(arguments + 0);           // original0068a58c mov eax, dword ptr [esp + 4]
    mm4 = pfadd(mm4, mm5);               // original0068a590 pfadd mm4, mm5
    mm7 = mm3;                           // original0068a594 movq mm7, mm3
    mm5 = single(edx + 0x8u);            // original0068a597 movd mm5, dword ptr [edx + 8]
    mm0 = pfadd(mm0, mm2);               // original0068a59b pfadd mm0, mm2
    mm3 = pfmul(mm3, pair(edx));         // original0068a59f pfmul mm3, qword ptr [edx]
    mm1 = pair(
        reinterpret_cast<u32>(dat_006f01c8)); // original0068a5a3 movq mm1, qword ptr [0x6f01c8]
    mm0 = pfadd(mm0, mm3);                    // original0068a5aa pfadd mm0, mm3
    mm7 = pfmul(mm7, mm5);                    // original0068a5ae pfmul mm7, mm5
    mm4 = pfadd(mm4, mm6);                    // original0068a5b2 pfadd mm4, mm6
    mm0 = pfmul(mm0, mm1);                    // original0068a5b6 pfmul mm0, mm1
    mm4 = pfadd(mm4, mm7);                    // original0068a5ba pfadd mm4, mm7
    store(eax, mm0);                          // original0068a5be movq qword ptr [eax], mm0
    mm4 = pfmul(mm4, mm1);                    // original0068a5c1 pfmul mm4, mm1
    store_single(eax + 0x8u, mm4);            // original0068a5c5 movd dword ptr [eax + 8], mm4
    empty();                                  // original0068a5c9 femms
    return eax;                               // original0068a5cb ret 0x18
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068a4e4(void*, const void*, const void*,
                                                              const void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068a4e4\n\taddl $4,%esp\n\tretl $24");
}

// Complete original0068b519..0068b58a; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068b519(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    edx = word(arguments + 2); // original0068b519 mov edx, dword ptr [esp + 0xc]
    ecx = word(arguments + 3); // original0068b51d mov ecx, dword ptr [esp + 0x10]
    eax = word(arguments + 1); // original0068b521 mov eax, dword ptr [esp + 8]
    mm0 = pair(edx);           // original0068b525 movq mm0, qword ptr [edx]
    mm1 = pair(edx + 0x8u);    // original0068b528 movq mm1, qword ptr [edx + 8]
    mm2 = pair(ecx);           // original0068b52c movq mm2, qword ptr [ecx]
    mm3 = pair(ecx + 0x8u);    // original0068b52f movq mm3, qword ptr [ecx + 8]
    mm4 = pair(eax);           // original0068b533 movq mm4, qword ptr [eax]
    mm5 = pair(eax + 0x8u);    // original0068b536 movq mm5, qword ptr [eax + 8]
    mm6 = single(reinterpret_cast<u32>(arguments) +
                 16u); // original0068b53a movd mm6, dword ptr [esp + 0x14]
    mm7 = single(reinterpret_cast<u32>(arguments) +
                 20u);         // original0068b53f movd mm7, dword ptr [esp + 0x18]
    mm0 = pfsub(mm0, mm4);     // original0068b544 pfsub mm0, mm4
    mm1 = pfsub(mm1, mm5);     // original0068b548 pfsub mm1, mm5
    eax = word(arguments + 0); // original0068b54c mov eax, dword ptr [esp + 4]
    mm2 = pfsub(mm2, mm4);     // original0068b550 pfsub mm2, mm4
    mm3 = pfsub(mm3, mm5);     // original0068b554 pfsub mm3, mm5
    mm6 = punpckldq(mm6, mm6); // original0068b558 punpckldq mm6, mm6
    mm7 = punpckldq(mm7, mm7); // original0068b55b punpckldq mm7, mm7
    mm0 = pfmul(mm0, mm6);     // original0068b55e pfmul mm0, mm6
    mm1 = pfmul(mm1, mm6);     // original0068b562 pfmul mm1, mm6
    mm2 = pfmul(mm2, mm7);     // original0068b566 pfmul mm2, mm7
    mm0 = pfadd(mm0, mm4);     // original0068b56a pfadd mm0, mm4
    mm3 = pfmul(mm3, mm7);     // original0068b56e pfmul mm3, mm7
    mm1 = pfadd(mm1, mm5);     // original0068b572 pfadd mm1, mm5
    mm0 = pfadd(mm0, mm2);     // original0068b576 pfadd mm0, mm2
    mm1 = pfadd(mm1, mm3);     // original0068b57a pfadd mm1, mm3
    store(eax, mm0);           // original0068b57e movq qword ptr [eax], mm0
    store(eax + 0x8u, mm1);    // original0068b581 movq qword ptr [eax + 8], mm1
    empty();                   // original0068b585 femms
    return eax;                // original0068b587 ret 0x18
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068b519(void*, const void*, const void*,
                                                              const void*, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068b519\n\taddl $4,%esp\n\tretl $24");
}

// Complete original0068b58a..0068b652; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068b58a(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    empty(); // original0068b58a femms
    mm0 = single(reinterpret_cast<u32>(arguments) +
                 20u);     // original0068b58c movd mm0, dword ptr [esp + 0x18]
    mm1 = mm0;             // original0068b591 movq mm1, mm0
    mm1 = pfmul(mm1, mm1); // original0068b594 pfmul mm1, mm1
    mm2 = mm1;             // original0068b598 movq mm2, mm1
    mm2 = pfmul(mm2, mm0); // original0068b59b pfmul mm2, mm0
    mm3 = pair(
        reinterpret_cast<u32>(dat_006f01f8)); // original0068b59f movq mm3, qword ptr [0x6f01f8]
    mm4 = mm1;                                // original0068b5a6 movq mm4, mm1
    mm7 = mm2;                                // original0068b5a9 movq mm7, mm2
    mm7 = pfsub(mm7, mm1);                    // original0068b5ac pfsub mm7, mm1
    mm4 = pfmul(mm4, mm3);                    // original0068b5b0 pfmul mm4, mm3
    mm6 = mm2;                                // original0068b5b4 movq mm6, mm2
    mm1 = pfmul(mm1, pair(reinterpret_cast<u32>(
                         dat_006f0200))); // original0068b5b7 pfmul mm1, qword ptr [0x6f0200]
    mm2 = pfmul(mm2, mm3);                // original0068b5bf pfmul mm2, mm3
    mm6 = pfsub(mm6, mm4);                // original0068b5c3 pfsub mm6, mm4
    mm5 = mm1;                            // original0068b5c7 movq mm5, mm1
    mm1 = pfsub(mm1, mm2);                // original0068b5ca pfsub mm1, mm2
    mm6 = pfadd(mm6, mm0);                // original0068b5ce pfadd mm6, mm0
    mm2 = pfsub(mm2, mm5);                // original0068b5d2 pfsub mm2, mm5
    mm2 = pfadd(mm2, pair(reinterpret_cast<u32>(
                         dat_006f01e8))); // original0068b5d6 pfadd mm2, qword ptr [0x6f01e8]
    eax = word(arguments + 4);            // original0068b5de mov eax, dword ptr [esp + 0x14]
    ecx = word(arguments + 3);            // original0068b5e2 mov ecx, dword ptr [esp + 0x10]
    edx = word(arguments + 2);            // original0068b5e6 mov edx, dword ptr [esp + 0xc]
    mm7 = punpckldq(mm7, mm7);            // original0068b5ea punpckldq mm7, mm7
    mm1 = punpckldq(mm1, mm1);            // original0068b5ed punpckldq mm1, mm1
    mm6 = punpckldq(mm6, mm6);            // original0068b5f0 punpckldq mm6, mm6
    mm2 = punpckldq(mm2, mm2);            // original0068b5f3 punpckldq mm2, mm2
    mm5 = mm7;                            // original0068b5f6 movq mm5, mm7
    mm7 = pfmul(mm7, pair(eax));          // original0068b5f9 pfmul mm7, qword ptr [eax]
    mm0 = mm1;                            // original0068b5fd movq mm0, mm1
    mm1 = pfmul(mm1, pair(ecx));          // original0068b600 pfmul mm1, qword ptr [ecx]
    mm5 = pfmul(mm5, pair(eax + 0x8u));   // original0068b604 pfmul mm5, qword ptr [eax + 8]
    mm0 = pfmul(mm0, pair(ecx + 0x8u));   // original0068b609 pfmul mm0, qword ptr [ecx + 8]
    ecx = word(arguments + 1);            // original0068b60e mov ecx, dword ptr [esp + 8]
    eax = word(arguments + 0);            // original0068b612 mov eax, dword ptr [esp + 4]
    mm4 = mm6;                            // original0068b616 movq mm4, mm6
    mm6 = pfmul(mm6, pair(edx));          // original0068b619 pfmul mm6, qword ptr [edx]
    mm3 = mm2;                            // original0068b61d movq mm3, mm2
    mm2 = pfmul(mm2, pair(ecx));          // original0068b620 pfmul mm2, qword ptr [ecx]
    mm4 = pfmul(mm4, pair(edx + 0x8u));   // original0068b624 pfmul mm4, qword ptr [edx + 8]
    mm3 = pfmul(mm3, pair(ecx + 0x8u));   // original0068b629 pfmul mm3, qword ptr [ecx + 8]
    mm1 = pfadd(mm1, mm7);                // original0068b62e pfadd mm1, mm7
    mm0 = pfadd(mm0, mm5);                // original0068b632 pfadd mm0, mm5
    mm2 = pfadd(mm2, mm6);                // original0068b636 pfadd mm2, mm6
    mm3 = pfadd(mm3, mm4);                // original0068b63a pfadd mm3, mm4
    mm1 = pfadd(mm1, mm2);                // original0068b63e pfadd mm1, mm2
    mm0 = pfadd(mm0, mm3);                // original0068b642 pfadd mm0, mm3
    store(eax, mm1);                      // original0068b646 movq qword ptr [eax], mm1
    store(eax + 0x8u, mm0);               // original0068b649 movq qword ptr [eax + 8], mm0
    empty();                              // original0068b64d femms
    return eax;                           // original0068b64f ret 0x18
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068b58a(void*, const void*, const void*,
                                                              const void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068b58a\n\taddl $4,%esp\n\tretl $24");
}

// Complete original0068b652..0068b730; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068b652(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    mm0 = single(reinterpret_cast<u32>(arguments) +
                 20u);         // original0068b652 movd mm0, dword ptr [esp + 0x18]
    edx = word(arguments + 1); // original0068b657 mov edx, dword ptr [esp + 8]
    mm1 = mm0;                 // original0068b65b movq mm1, mm0
    mm0 = punpckldq(mm0, mm0); // original0068b65e punpckldq mm0, mm0
    mm0 = pfmul(mm0, mm0);     // original0068b661 pfmul mm0, mm0
    mm1 = unpack_memory(mm1,
                        reinterpret_cast<u32>(
                            dat_006f0160)); // original0068b665 punpckldq mm1, dword ptr [0x6f0160]
    mm0 = pfmul(mm0, mm1);                  // original0068b66c pfmul mm0, mm1
    mm3 = mm1;                              // original0068b670 movq mm3, mm1
    mm1 = pfmul(mm1, mm1);                  // original0068b673 pfmul mm1, mm1
    __asm__ volatile("pxor %0,%0" : "=y"(mm7)); // original0068b677 pxor mm7, mm7
    mm0 = pfsub(mm0, mm1);                      // original0068b67a pfsub mm0, mm1
    mm1 = punpckldq(mm1, mm1);                  // original0068b67e punpckldq mm1, mm1
    mm4 = mm0;                                  // original0068b681 movq mm4, mm0
    mm3 = punpckldq(mm3, mm3);                  // original0068b684 punpckldq mm3, mm3
    mm0 = pfmul(mm0, pair(reinterpret_cast<u32>(
                         dat_006f0170))); // original0068b687 pfmul mm0, qword ptr [0x6f0170]
    mm5 = mm0;                            // original0068b68f movq mm5, mm0
    mm0 = punpckldq(mm0, mm4);            // original0068b692 punpckldq mm0, mm4
    mm3 = pxor(mm3, pair(reinterpret_cast<u32>(
                        dat_006f0180))); // original0068b695 pxor mm3, qword ptr [0x6f0180]
    mm5 = punpckhdq(mm5, mm7);           // original0068b69c punpckhdq mm5, mm7
    mm1 = pfadd(mm1, mm3);               // original0068b69f pfadd mm1, mm3
    mm1 = pfsub(mm1, mm0);               // original0068b6a3 pfsub mm1, mm0
    ecx = word(arguments + 2);           // original0068b6a7 mov ecx, dword ptr [esp + 0xc]
    mm0 = pfsub(mm0, mm5);               // original0068b6ab pfsub mm0, mm5
    mm2 = mm1;                           // original0068b6af movq mm2, mm1
    mm1 = punpckhdq(mm1, mm1);           // original0068b6b2 punpckhdq mm1, mm1
    mm3 = mm0;                           // original0068b6b5 movq mm3, mm0
    mm0 = punpckldq(mm0, mm0);           // original0068b6b8 punpckldq mm0, mm0
    eax = word(arguments + 3);           // original0068b6bb mov eax, dword ptr [esp + 0x10]
    mm2 = punpckldq(mm2, mm2);           // original0068b6bf punpckldq mm2, mm2
    mm4 = mm1;                           // original0068b6c2 movq mm4, mm1
    mm1 = pfmul(mm1, pair(edx));         // original0068b6c5 pfmul mm1, qword ptr [edx]
    mm3 = punpckhdq(mm3, mm3);           // original0068b6c9 punpckhdq mm3, mm3
    mm5 = mm0;                           // original0068b6cc movq mm5, mm0
    mm0 = pfmul(mm0, pair(ecx));         // original0068b6cf pfmul mm0, qword ptr [ecx]
    mm6 = mm2;                           // original0068b6d3 movq mm6, mm2
    mm2 = pfmul(mm2, pair(eax));         // original0068b6d6 pfmul mm2, qword ptr [eax]
    mm7 = mm3;                           // original0068b6da movq mm7, mm3
    mm4 = pfmul(mm4, pair(edx + 0x8u));  // original0068b6dd pfmul mm4, qword ptr [edx + 8]
    edx = word(arguments + 4);           // original0068b6e2 mov edx, dword ptr [esp + 0x14]
    mm5 = pfmul(mm5, pair(ecx + 0x8u));  // original0068b6e6 pfmul mm5, qword ptr [ecx + 8]
    mm0 = pfadd(mm0, mm1);               // original0068b6eb pfadd mm0, mm1
    mm6 = pfmul(mm6, pair(eax + 0x8u));  // original0068b6ef pfmul mm6, qword ptr [eax + 8]
    eax = word(arguments + 0);           // original0068b6f4 mov eax, dword ptr [esp + 4]
    mm4 = pfadd(mm4, mm5);               // original0068b6f8 pfadd mm4, mm5
    mm0 = pfadd(mm0, mm2);               // original0068b6fc pfadd mm0, mm2
    mm3 = pfmul(mm3, pair(edx));         // original0068b700 pfmul mm3, qword ptr [edx]
    mm1 = pair(
        reinterpret_cast<u32>(dat_006f01c8)); // original0068b704 movq mm1, qword ptr [0x6f01c8]
    mm0 = pfadd(mm0, mm3);                    // original0068b70b pfadd mm0, mm3
    mm7 = pfmul(mm7, pair(edx + 0x8u));       // original0068b70f pfmul mm7, qword ptr [edx + 8]
    mm4 = pfadd(mm4, mm6);                    // original0068b714 pfadd mm4, mm6
    mm0 = pfmul(mm0, mm1);                    // original0068b718 pfmul mm0, mm1
    mm4 = pfadd(mm4, mm7);                    // original0068b71c pfadd mm4, mm7
    store(eax, mm0);                          // original0068b720 movq qword ptr [eax], mm0
    mm4 = pfmul(mm4, mm1);                    // original0068b723 pfmul mm4, mm1
    store(eax + 0x8u, mm4);                   // original0068b727 movq qword ptr [eax + 8], mm4
    empty();                                  // original0068b72b femms
    return eax;                               // original0068b72d ret 0x18
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068b652(void*, const void*, const void*,
                                                              const void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068b652\n\taddl $4,%esp\n\tretl $24");
}
