#include "graphics/render_normalize_amd.h"
#include "graphics/render_quaternion_amd.h"
#include "graphics/render_3dnow_norm.h"
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
AMD Packed reciprocal_estimate(Packed p) {
    Packed v;
    __asm__ volatile("pfrcp %1,%0" : "=y"(v) : "y"(p));
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
// Keep the actual memory instruction: PUNPCKLDQ's observed memory
// access width must not be widened by a separate MOVQ load.
AMD Packed unpack_memory(Packed a, u32 p) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return a;
}
} // namespace
extern "C" alignas(8) const u32 dat_006f01b0[2] = {0xffffffffu, 0x00000000u};
extern "C" alignas(8) const u32 dat_006f0230[2] = {0x80000000u, 0x80000000u};

// Complete original0068b214..0068b257; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068b214(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    edx = word(arguments + 1); // original0068b214 mov edx, dword ptr [esp + 8]
    mm0 = pair(edx);           // original0068b218 movq mm0, qword ptr [edx]
    mm1 = mm0;                 // original0068b21b movq mm1, mm0
    mm0 = pfmul(mm0, mm0);     // original0068b21e pfmul mm0, mm0
    eax = word(arguments + 0); // original0068b222 mov eax, dword ptr [esp + 4]
    mm0 = pfacc(mm0, mm0);     // original0068b226 pfacc mm0, mm0
    mm2 = mm0;                 // original0068b22a movq mm2, mm0
    mm4 = estimate(mm0);       // original0068b22d pfrsqrt mm4, mm0
    mm2 = pfcmpgt(mm2, pair(reinterpret_cast<u32>(
                           dat_006f01d0))); // original0068b231 pfcmpgt mm2, qword ptr [0x6f01d0]
    mm5 = mm4;                              // original0068b239 movq mm5, mm4
    mm4 = pfmul(mm4, mm4);                  // original0068b23c pfmul mm4, mm4
    mm4 = pfrsqit1(mm4, mm0);               // original0068b240 pfrsqit1 mm4, mm0
    mm1 = pand(mm1, mm2);                   // original0068b244 pand mm1, mm2
    mm4 = pfrcpit2(mm4, mm5);               // original0068b247 pfrcpit2 mm4, mm5
    mm1 = pfmul(mm1, mm4);                  // original0068b24b pfmul mm1, mm4
    store(eax, mm1);                        // original0068b24f movq qword ptr [eax], mm1
    empty();                                // original0068b252 femms
    return eax;                             // original0068b254 ret 8
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068b214(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068b214\n\taddl $4,%esp\n\tretl $8");
}

// Complete original0068b386..0068b3e5; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068b386(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    empty();                   // original0068b386 femms
    ecx = word(arguments + 1); // original0068b388 mov ecx, dword ptr [esp + 8]
    mm0 = pair(ecx);           // original0068b38c movq mm0, qword ptr [ecx]
    mm1 = mm0;                 // original0068b38f movq mm1, mm0
    mm2 = pair(ecx + 0x8u);    // original0068b392 movq mm2, qword ptr [ecx + 8]
    mm3 = mm2;                 // original0068b396 movq mm3, mm2
    mm0 = pfmul(mm0, mm0);     // original0068b399 pfmul mm0, mm0
    mm2 = pfmul(mm2, mm2);     // original0068b39d pfmul mm2, mm2
    mm0 = pfadd(mm0, mm2);     // original0068b3a1 pfadd mm0, mm2
    mm0 = pfacc(mm0, mm0);     // original0068b3a5 pfacc mm0, mm0
    eax = word(arguments + 0); // original0068b3a9 mov eax, dword ptr [esp + 4]
    mm5 = mm0;                 // original0068b3ad movq mm5, mm0
    mm4 = estimate(mm0);       // original0068b3b0 pfrsqrt mm4, mm0
    mm5 = pfcmpgt(mm5, pair(reinterpret_cast<u32>(
                           dat_006f01d0))); // original0068b3b4 pfcmpgt mm5, qword ptr [0x6f01d0]
    mm2 = mm4;                              // original0068b3bc movq mm2, mm4
    mm2 = pfmul(mm2, mm4);                  // original0068b3bf pfmul mm2, mm4
    mm0 = pfrsqit1(mm0, mm2);               // original0068b3c3 pfrsqit1 mm0, mm2
    mm1 = pand(mm1, mm5);                   // original0068b3c7 pand mm1, mm5
    mm3 = pand(mm3, mm5);                   // original0068b3ca pand mm3, mm5
    mm0 = pfrcpit2(mm0, mm4);               // original0068b3cd pfrcpit2 mm0, mm4
    mm1 = pfmul(mm1, mm0);                  // original0068b3d1 pfmul mm1, mm0
    mm3 = pfmul(mm3, mm0);                  // original0068b3d5 pfmul mm3, mm0
    store(eax, mm1);                        // original0068b3d9 movq qword ptr [eax], mm1
    store(eax + 0x8u, mm3);                 // original0068b3dc movq qword ptr [eax + 8], mm3
    empty();                                // original0068b3e0 femms
    return eax;                             // original0068b3e2 ret 8
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068b386(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068b386\n\taddl $4,%esp\n\tretl $8");
}

// Complete original0068b915..0068b979; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068b915(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    edx = word(arguments + 1); // original0068b915 mov edx, dword ptr [esp + 8]
    mm0 = pair(edx);           // original0068b919 movq mm0, qword ptr [edx]
    mm2 = pair(edx + 0x8u);    // original0068b91c movq mm2, qword ptr [edx + 8]
    mm1 = mm0;                 // original0068b920 movq mm1, mm0
    mm3 = mm2;                 // original0068b923 movq mm3, mm2
    mm2 = pand(mm2, pair(reinterpret_cast<u32>(
                        dat_006f01b0))); // original0068b926 pand mm2, qword ptr [0x6f01b0]
    mm0 = pfmul(mm0, mm0);               // original0068b92d pfmul mm0, mm0
    mm2 = pfmul(mm2, mm2);               // original0068b931 pfmul mm2, mm2
    mm0 = pfadd(mm0, mm2);               // original0068b935 pfadd mm0, mm2
    mm0 = pfacc(mm0, mm0);               // original0068b939 pfacc mm0, mm0
    mm5 = mm0;                           // original0068b93d movq mm5, mm0
    mm4 = estimate(mm0);                 // original0068b940 pfrsqrt mm4, mm0
    mm5 = pfcmpgt(mm5, pair(reinterpret_cast<u32>(
                           dat_006f01d0))); // original0068b944 pfcmpgt mm5, qword ptr [0x6f01d0]
    mm2 = mm4;                              // original0068b94c movq mm2, mm4
    mm2 = pfmul(mm2, mm4);                  // original0068b94f pfmul mm2, mm4
    mm0 = pfrsqit1(mm0, mm2);               // original0068b953 pfrsqit1 mm0, mm2
    eax = word(arguments + 0);              // original0068b957 mov eax, dword ptr [esp + 4]
    mm1 = pand(mm1, mm5);                   // original0068b95b pand mm1, mm5
    mm3 = pand(mm3, mm5);                   // original0068b95e pand mm3, mm5
    mm0 = pfrcpit2(mm0, mm4);               // original0068b961 pfrcpit2 mm0, mm4
    mm1 = pfmul(mm1, mm0);                  // original0068b965 pfmul mm1, mm0
    mm3 = pfmul(mm3, mm0);                  // original0068b969 pfmul mm3, mm0
    store(eax, mm1);                        // original0068b96d movq qword ptr [eax], mm1
    store(eax + 0x8u, mm3);                 // original0068b970 movq qword ptr [eax + 8], mm3
    empty();                                // original0068b974 femms
    return eax;                             // original0068b976 ret 8
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068b915(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068b915\n\taddl $4,%esp\n\tretl $8");
}

// Complete original0068582e..00685892; all branches and actual argument reads retained.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068582e(const u32* arguments) {
    [[maybe_unused]] u32 eax, ecx, edx;
    [[maybe_unused]] bool zero = false;
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    edx = word(arguments + 1);      // original0068582e mov edx, dword ptr [esp + 8]
    mm0 = pair(edx);                // original00685832 movq mm0, qword ptr [edx]
    mm1 = mm0;                      // original00685835 movq mm1, mm0
    mm2 = pair(edx + 0x8u);         // original00685838 movq mm2, qword ptr [edx + 8]
    mm3 = mm2;                      // original0068583c movq mm3, mm2
    mm0 = pfmul(mm0, mm0);          // original0068583f pfmul mm0, mm0
    mm2 = pfmul(mm2, mm2);          // original00685843 pfmul mm2, mm2
    mm0 = pfadd(mm0, mm2);          // original00685847 pfadd mm0, mm2
    mm0 = pfacc(mm0, mm0);          // original0068584b pfacc mm0, mm0
    eax = word(arguments + 0);      // original0068584f mov eax, dword ptr [esp + 4]
    mm5 = mm0;                      // original00685853 movq mm5, mm0
    mm4 = reciprocal_estimate(mm0); // original00685856 pfrcp mm4, mm0
    mm5 = pfcmpgt(mm5, pair(reinterpret_cast<u32>(
                           dat_006f01d0))); // original0068585a pfcmpgt mm5, qword ptr [0x6f01d0]
    mm1 = pxor(mm1, pair(reinterpret_cast<u32>(
                        dat_006f0230))); // original00685862 pxor mm1, qword ptr [0x6f0230]
    mm3 = pxor(mm3, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685869 pxor mm3, qword ptr [0x6f0178]
    mm0 = pfrcpit1(mm0, mm4);            // original00685870 pfrcpit1 mm0, mm4
    mm1 = pand(mm1, mm5);                // original00685874 pand mm1, mm5
    mm3 = pand(mm3, mm5);                // original00685877 pand mm3, mm5
    mm0 = pfrcpit2(mm0, mm4);            // original0068587a pfrcpit2 mm0, mm4
    mm1 = pfmul(mm1, mm0);               // original0068587e pfmul mm1, mm0
    mm3 = pfmul(mm3, mm0);               // original00685882 pfmul mm3, mm0
    store(eax, mm1);                     // original00685886 movq qword ptr [eax], mm1
    store(eax + 0x8u, mm3);              // original00685889 movq qword ptr [eax + 8], mm3
    empty();                             // original0068588d femms
    return eax;                          // original0068588f ret 8
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068582e(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068582e\n\taddl $4,%esp\n\tretl $8");
}
