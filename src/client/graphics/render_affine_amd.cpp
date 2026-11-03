#include "graphics/render_affine_amd.h"
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
AMD Packed zero_pair() {
    Packed v;
    __asm__ volatile("pxor %0,%0" : "=y"(v));
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

extern "C" alignas(8) const uint32_t dat_006f0140[2] = {0x00000000u, 0x3f800000u};
// Complete original0068802f..00688563; every packed operation and branch.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068802f(u32 arguments, u32 rotation) {
    u32 eax, ecx, edx;
    bool zero = false;
    Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    eax = word(arguments + 0u);   // original0068802f mov eax, dword ptr [esp + 4]
    mm6 = single(arguments + 4u); // original00688033 movd mm6, dword ptr [esp + 8]
    mm7 = zero_pair();            // original00688038 pxor mm7, mm7
    edx = word(arguments + 12u);  // original0068803b mov edx, dword ptr [esp + 0x10]
    mm5 = pair(
        reinterpret_cast<u32>(dat_006f0140)); // original0068803f movq mm5, qword ptr [0x6f0140]
    ecx = word(arguments + 8u);               // original00688046 mov ecx, dword ptr [esp + 0xc]
    store(eax, mm6);                          // original0068804a movq qword ptr [eax], mm6
    store(eax + 8u, mm7);                     // original0068804d movq qword ptr [eax + 8], mm7
    store_single(eax + 16u, mm7);             // original00688051 movd dword ptr [eax + 0x10], mm7
    ; // Original private64B frame allocation/release; explicit bounded bridge storage. // original00688055 sub esp, 0x40
    store_single(eax + 20u, mm6); // original00688058 movd dword ptr [eax + 0x14], mm6
    store(eax + 24u, mm7);        // original0068805c movq qword ptr [eax + 0x18], mm7
    zero = (edx == 0);            // original00688060 test edx, edx
    store(eax + 32u, mm7);        // original00688062 movq qword ptr [eax + 0x20], mm7
    store(eax + 40u, mm6);        // original00688066 movq qword ptr [eax + 0x28], mm6
    store(eax + 48u, mm7);        // original0068806a movq qword ptr [eax + 0x30], mm7
    store(eax + 56u, mm5);        // original0068806e movq qword ptr [eax + 0x38], mm5
    if (zero)
        goto L_00688534;        // original00688072 je 0x688534
    mm0 = pair(edx);            // original00688078 movq mm0, qword ptr [edx]
    mm1 = pair(edx + 8u);       // original0068807b movq mm1, qword ptr [edx + 8]
    mm2 = mm0;                  // original0068807f movq mm2, mm0
    mm3 = mm0;                  // original00688082 movq mm3, mm0
    mm0 = pfadd(mm0, mm0);      // original00688085 pfadd mm0, mm0
    mm4 = mm1;                  // original00688089 movq mm4, mm1
    mm7 = mm1;                  // original0068808c movq mm7, mm1
    mm1 = pfadd(mm1, mm1);      // original0068808f pfadd mm1, mm1
    mm2 = punpckhdq(mm2, mm2);  // original00688093 punpckhdq mm2, mm2
    mm5 = mm0;                  // original00688096 movq mm5, mm0
    mm4 = punpckhdq(mm4, mm4);  // original00688099 punpckhdq mm4, mm4
    mm3 = pfmul(mm3, mm0);      // original0068809c pfmul mm3, mm0
    mm1 = punpckldq(mm1, mm0);  // original006880a0 punpckldq mm1, mm0
    mm7 = punpckldq(mm7, mm7);  // original006880a3 punpckldq mm7, mm7
    mm5 = pfmul(mm5, mm4);      // original006880a6 pfmul mm5, mm4
    mm6 = mm1;                  // original006880aa movq mm6, mm1
    mm7 = pfmul(mm7, mm1);      // original006880ad pfmul mm7, mm1
    mm1 = pfmul(mm1, mm2);      // original006880b1 pfmul mm1, mm2
    mm0 = zero_pair();          // original006880b5 pxor mm0, mm0
    mm6 = pfmul(mm6, mm4);      // original006880b8 pfmul mm6, mm4
    mm2 = mm1;                  // original006880bc movq mm2, mm1
    mm1 = punpckhdq(mm1, mm7);  // original006880bf punpckhdq mm1, mm7
    mm7 = punpckldq(mm7, mm7);  // original006880c2 punpckldq mm7, mm7
    mm6 = punpckldq(mm6, mm6);  // original006880c5 punpckldq mm6, mm6
    store(rotation + 48u, mm0); // original006880c8 movq qword ptr [esp + 0x30], mm0
    mm7 = pfadd(mm7, mm3);      // original006880cd pfadd mm7, mm3
    mm3 = pfacc(mm3, mm3);      // original006880d1 pfacc mm3, mm3
    mm4 = mm1;                  // original006880d5 movq mm4, mm1
    mm6 = punpckhdq(mm6, mm5);  // original006880d8 punpckhdq mm6, mm5
    mm3 = pfsubr(mm3, pair(reinterpret_cast<u32>(
                          dat_006f0160))); // original006880db pfsubr mm3, qword ptr [0x6f0160]
    mm7 = pfsubr(mm7, pair(reinterpret_cast<u32>(
                          dat_006f0160))); // original006880e3 pfsubr mm7, qword ptr [0x6f0160]
    mm3 = punpckldq(mm3, mm0);             // original006880eb punpckldq mm3, mm0
    mm1 = pfadd(mm1, mm6);                 // original006880ee pfadd mm1, mm6
    store(rotation + 40u, mm3);            // original006880f2 movq qword ptr [esp + 0x28], mm3
    mm4 = pfsub(mm4, mm6);                 // original006880f7 pfsub mm4, mm6
    mm3 = mm2;                             // original006880fb movq mm3, mm2
    mm2 = pfadd(mm2, mm5);                 // original006880fe pfadd mm2, mm5
    mm3 = pfsub(mm3, mm5);                 // original00688102 pfsub mm3, mm5
    mm5 = mm4;                             // original00688106 movq mm5, mm4
    mm2 = punpckldq(mm2, mm0);             // original00688109 punpckldq mm2, mm0
    mm6 = mm1;                             // original0068810c movq mm6, mm1
    mm4 = punpckldq(mm4, mm7);             // original0068810f punpckldq mm4, mm7
    mm1 = punpckldq(mm1, mm1);             // original00688112 punpckldq mm1, mm1
    store(rotation + 24u, mm2);            // original00688115 movq qword ptr [esp + 0x18], mm2
    mm5 = punpckhdq(mm5, mm0);             // original0068811a punpckhdq mm5, mm0
    mm0 = unpack_low_memory(
        mm0, reinterpret_cast<u32>(
                 dat_006f0160)); // original0068811d punpckldq mm0, dword ptr [0x6f0160]
    store(rotation + 8u, mm5);   // original00688124 movq qword ptr [esp + 8], mm5
    mm6 = punpckhdq(mm6, mm6);   // original00688129 punpckhdq mm6, mm6
    store(rotation + 16u, mm4);  // original0068812c movq qword ptr [esp + 0x10], mm4
    mm7 = punpckhdq(mm7, mm1);   // original00688131 punpckhdq mm7, mm1
    mm6 = punpckldq(mm6, mm3);   // original00688134 punpckldq mm6, mm3
    store(rotation, mm7);        // original00688137 movq qword ptr [esp], mm7
    store(rotation + 32u, mm6);  // original0068813b movq qword ptr [esp + 0x20], mm6
    store(rotation + 56u, mm0);  // original00688140 movq qword ptr [esp + 0x38], mm0
    zero = (ecx == 0);           // original00688145 test ecx, ecx
    if (zero)
        goto L_00688362;                    // original00688147 je 0x688362
    mm0 = pair(eax + 48u);                  // original0068814d movq mm0, qword ptr [eax + 0x30]
    mm1 = single(eax + 56u);                // original00688151 movd mm1, dword ptr [eax + 0x38]
    mm2 = pair(ecx);                        // original00688155 movq mm2, qword ptr [ecx]
    mm3 = single(ecx + 8u);                 // original00688158 movd mm3, dword ptr [ecx + 8]
    mm0 = pfsub(mm0, mm2);                  // original0068815c pfsub mm0, mm2
    mm1 = pfsub(mm1, mm3);                  // original00688160 pfsub mm1, mm3
    store(eax + 48u, mm0);                  // original00688164 movq qword ptr [eax + 0x30], mm0
    store_single(eax + 56u, mm1);           // original00688168 movd dword ptr [eax + 0x38], mm1
    mm0 = pair(eax);                        // original0068816c movq mm0, qword ptr [eax]
    mm1 = pair(eax + 8u);                   // original0068816f movq mm1, qword ptr [eax + 8]
    mm4 = pair(rotation);                   // original00688173 movq mm4, qword ptr [esp]
    mm2 = punpckhdq(mm2, mm0);              // original00688177 punpckhdq mm2, mm0
    mm5 = pair(rotation + 16u);             // original0068817a movq mm5, qword ptr [esp + 0x10]
    mm3 = punpckhdq(mm3, mm1);              // original0068817f punpckhdq mm3, mm1
    mm6 = pair(rotation + 32u);             // original00688182 movq mm6, qword ptr [esp + 0x20]
    mm0 = punpckldq(mm0, mm0);              // original00688187 punpckldq mm0, mm0
    mm1 = punpckldq(mm1, mm1);              // original0068818a punpckldq mm1, mm1
    mm4 = pfmul(mm4, mm0);                  // original0068818d pfmul mm4, mm0
    mm2 = punpckhdq(mm2, mm2);              // original00688191 punpckhdq mm2, mm2
    mm0 = pfmul(mm0, pair(rotation + 8u));  // original00688194 pfmul mm0, qword ptr [esp + 8]
    mm7 = pair(rotation + 48u);             // original0068819a movq mm7, qword ptr [esp + 0x30]
    mm5 = pfmul(mm5, mm2);                  // original0068819f pfmul mm5, mm2
    mm3 = punpckhdq(mm3, mm3);              // original006881a3 punpckhdq mm3, mm3
    mm2 = pfmul(mm2, pair(rotation + 24u)); // original006881a6 pfmul mm2, qword ptr [esp + 0x18]
    mm5 = pfadd(mm5, mm4);                  // original006881ac pfadd mm5, mm4
    mm6 = pfmul(mm6, mm1);                  // original006881b0 pfmul mm6, mm1
    mm2 = pfadd(mm2, mm0);                  // original006881b4 pfadd mm2, mm0
    mm1 = pfmul(mm1, pair(rotation + 40u)); // original006881b8 pfmul mm1, qword ptr [esp + 0x28]
    mm6 = pfadd(mm6, mm5);                  // original006881be pfadd mm6, mm5
    mm7 = pfmul(mm7, mm3);                  // original006881c2 pfmul mm7, mm3
    mm2 = pfadd(mm2, mm1);                  // original006881c6 pfadd mm2, mm1
    mm3 = pfmul(mm3, pair(rotation + 56u)); // original006881ca pfmul mm3, qword ptr [esp + 0x38]
    mm7 = pfadd(mm7, mm6);                  // original006881d0 pfadd mm7, mm6
    mm0 = pair(eax + 16u);                  // original006881d4 movq mm0, qword ptr [eax + 0x10]
    mm3 = pfadd(mm3, mm2);                  // original006881d8 pfadd mm3, mm2
    mm1 = pair(eax + 24u);                  // original006881dc movq mm1, qword ptr [eax + 0x18]
    store(eax, mm7);                        // original006881e0 movq qword ptr [eax], mm7
    mm4 = pair(rotation);                   // original006881e3 movq mm4, qword ptr [esp]
    store(eax + 8u, mm3);                   // original006881e7 movq qword ptr [eax + 8], mm3
    mm2 = punpckhdq(mm2, mm0);              // original006881eb punpckhdq mm2, mm0
    mm5 = pair(rotation + 16u);             // original006881ee movq mm5, qword ptr [esp + 0x10]
    mm3 = punpckhdq(mm3, mm1);              // original006881f3 punpckhdq mm3, mm1
    mm6 = pair(rotation + 32u);             // original006881f6 movq mm6, qword ptr [esp + 0x20]
    mm0 = punpckldq(mm0, mm0);              // original006881fb punpckldq mm0, mm0
    mm1 = punpckldq(mm1, mm1);              // original006881fe punpckldq mm1, mm1
    mm4 = pfmul(mm4, mm0);                  // original00688201 pfmul mm4, mm0
    mm2 = punpckhdq(mm2, mm2);              // original00688205 punpckhdq mm2, mm2
    mm0 = pfmul(mm0, pair(rotation + 8u));  // original00688208 pfmul mm0, qword ptr [esp + 8]
    mm7 = pair(rotation + 48u);             // original0068820e movq mm7, qword ptr [esp + 0x30]
    mm5 = pfmul(mm5, mm2);                  // original00688213 pfmul mm5, mm2
    mm3 = punpckhdq(mm3, mm3);              // original00688217 punpckhdq mm3, mm3
    mm2 = pfmul(mm2, pair(rotation + 24u)); // original0068821a pfmul mm2, qword ptr [esp + 0x18]
    mm5 = pfadd(mm5, mm4);                  // original00688220 pfadd mm5, mm4
    mm6 = pfmul(mm6, mm1);                  // original00688224 pfmul mm6, mm1
    mm2 = pfadd(mm2, mm0);                  // original00688228 pfadd mm2, mm0
    mm1 = pfmul(mm1, pair(rotation + 40u)); // original0068822c pfmul mm1, qword ptr [esp + 0x28]
    mm6 = pfadd(mm6, mm5);                  // original00688232 pfadd mm6, mm5
    mm7 = pfmul(mm7, mm3);                  // original00688236 pfmul mm7, mm3
    mm2 = pfadd(mm2, mm1);                  // original0068823a pfadd mm2, mm1
    mm3 = pfmul(mm3, pair(rotation + 56u)); // original0068823e pfmul mm3, qword ptr [esp + 0x38]
    mm7 = pfadd(mm7, mm6);                  // original00688244 pfadd mm7, mm6
    mm0 = pair(eax + 32u);                  // original00688248 movq mm0, qword ptr [eax + 0x20]
    mm3 = pfadd(mm3, mm2);                  // original0068824c pfadd mm3, mm2
    mm1 = pair(eax + 40u);                  // original00688250 movq mm1, qword ptr [eax + 0x28]
    store(eax + 16u, mm7);                  // original00688254 movq qword ptr [eax + 0x10], mm7
    mm4 = pair(rotation);                   // original00688258 movq mm4, qword ptr [esp]
    store(eax + 24u, mm3);                  // original0068825c movq qword ptr [eax + 0x18], mm3
    mm2 = punpckhdq(mm2, mm0);              // original00688260 punpckhdq mm2, mm0
    mm5 = pair(rotation + 16u);             // original00688263 movq mm5, qword ptr [esp + 0x10]
    mm3 = punpckhdq(mm3, mm1);              // original00688268 punpckhdq mm3, mm1
    mm6 = pair(rotation + 32u);             // original0068826b movq mm6, qword ptr [esp + 0x20]
    mm0 = punpckldq(mm0, mm0);              // original00688270 punpckldq mm0, mm0
    mm1 = punpckldq(mm1, mm1);              // original00688273 punpckldq mm1, mm1
    mm4 = pfmul(mm4, mm0);                  // original00688276 pfmul mm4, mm0
    mm2 = punpckhdq(mm2, mm2);              // original0068827a punpckhdq mm2, mm2
    mm0 = pfmul(mm0, pair(rotation + 8u));  // original0068827d pfmul mm0, qword ptr [esp + 8]
    mm7 = pair(rotation + 48u);             // original00688283 movq mm7, qword ptr [esp + 0x30]
    mm5 = pfmul(mm5, mm2);                  // original00688288 pfmul mm5, mm2
    mm3 = punpckhdq(mm3, mm3);              // original0068828c punpckhdq mm3, mm3
    mm2 = pfmul(mm2, pair(rotation + 24u)); // original0068828f pfmul mm2, qword ptr [esp + 0x18]
    mm5 = pfadd(mm5, mm4);                  // original00688295 pfadd mm5, mm4
    mm6 = pfmul(mm6, mm1);                  // original00688299 pfmul mm6, mm1
    mm2 = pfadd(mm2, mm0);                  // original0068829d pfadd mm2, mm0
    mm1 = pfmul(mm1, pair(rotation + 40u)); // original006882a1 pfmul mm1, qword ptr [esp + 0x28]
    mm6 = pfadd(mm6, mm5);                  // original006882a7 pfadd mm6, mm5
    mm7 = pfmul(mm7, mm3);                  // original006882ab pfmul mm7, mm3
    mm2 = pfadd(mm2, mm1);                  // original006882af pfadd mm2, mm1
    mm3 = pfmul(mm3, pair(rotation + 56u)); // original006882b3 pfmul mm3, qword ptr [esp + 0x38]
    mm7 = pfadd(mm7, mm6);                  // original006882b9 pfadd mm7, mm6
    mm0 = pair(eax + 48u);                  // original006882bd movq mm0, qword ptr [eax + 0x30]
    mm3 = pfadd(mm3, mm2);                  // original006882c1 pfadd mm3, mm2
    mm1 = pair(eax + 56u);                  // original006882c5 movq mm1, qword ptr [eax + 0x38]
    store(eax + 32u, mm7);                  // original006882c9 movq qword ptr [eax + 0x20], mm7
    mm4 = pair(rotation);                   // original006882cd movq mm4, qword ptr [esp]
    store(eax + 40u, mm3);                  // original006882d1 movq qword ptr [eax + 0x28], mm3
    mm2 = punpckhdq(mm2, mm0);              // original006882d5 punpckhdq mm2, mm0
    mm5 = pair(rotation + 16u);             // original006882d8 movq mm5, qword ptr [esp + 0x10]
    mm3 = punpckhdq(mm3, mm1);              // original006882dd punpckhdq mm3, mm1
    mm6 = pair(rotation + 32u);             // original006882e0 movq mm6, qword ptr [esp + 0x20]
    mm0 = punpckldq(mm0, mm0);              // original006882e5 punpckldq mm0, mm0
    mm1 = punpckldq(mm1, mm1);              // original006882e8 punpckldq mm1, mm1
    mm4 = pfmul(mm4, mm0);                  // original006882eb pfmul mm4, mm0
    mm2 = punpckhdq(mm2, mm2);              // original006882ef punpckhdq mm2, mm2
    mm0 = pfmul(mm0, pair(rotation + 8u));  // original006882f2 pfmul mm0, qword ptr [esp + 8]
    mm7 = pair(rotation + 48u);             // original006882f8 movq mm7, qword ptr [esp + 0x30]
    mm5 = pfmul(mm5, mm2);                  // original006882fd pfmul mm5, mm2
    mm3 = punpckhdq(mm3, mm3);              // original00688301 punpckhdq mm3, mm3
    mm2 = pfmul(mm2, pair(rotation + 24u)); // original00688304 pfmul mm2, qword ptr [esp + 0x18]
    mm5 = pfadd(mm5, mm4);                  // original0068830a pfadd mm5, mm4
    mm6 = pfmul(mm6, mm1);                  // original0068830e pfmul mm6, mm1
    mm2 = pfadd(mm2, mm0);                  // original00688312 pfadd mm2, mm0
    mm1 = pfmul(mm1, pair(rotation + 40u)); // original00688316 pfmul mm1, qword ptr [esp + 0x28]
    mm6 = pfadd(mm6, mm5);                  // original0068831c pfadd mm6, mm5
    mm7 = pfmul(mm7, mm3);                  // original00688320 pfmul mm7, mm3
    mm2 = pfadd(mm2, mm1);                  // original00688324 pfadd mm2, mm1
    mm3 = pfmul(mm3, pair(rotation + 56u)); // original00688328 pfmul mm3, qword ptr [esp + 0x38]
    mm7 = pfadd(mm7, mm6);                  // original0068832e pfadd mm7, mm6
    mm3 = pfadd(mm3, mm2);                  // original00688332 pfadd mm3, mm2
    store(eax + 48u, mm7);                  // original00688336 movq qword ptr [eax + 0x30], mm7
    store(eax + 56u, mm3);                  // original0068833a movq qword ptr [eax + 0x38], mm3
    mm0 = pair(eax + 48u);                  // original0068833e movq mm0, qword ptr [eax + 0x30]
    mm1 = single(eax + 56u);                // original00688342 movd mm1, dword ptr [eax + 0x38]
    mm2 = pair(ecx);                        // original00688346 movq mm2, qword ptr [ecx]
    mm3 = single(ecx + 8u);                 // original00688349 movd mm3, dword ptr [ecx + 8]
    mm0 = pfadd(mm0, mm2);                  // original0068834d pfadd mm0, mm2
    mm1 = pfadd(mm1, mm3);                  // original00688351 pfadd mm1, mm3
    store(eax + 48u, mm0);                  // original00688355 movq qword ptr [eax + 0x30], mm0
    store_single(eax + 56u, mm1);           // original00688359 movd dword ptr [eax + 0x38], mm1
    goto L_00688534;                        // original0068835d jmp 0x688534
L_00688362:;
    mm0 = pair(eax);                        // original00688362 movq mm0, qword ptr [eax]
    mm1 = pair(eax + 8u);                   // original00688365 movq mm1, qword ptr [eax + 8]
    mm4 = pair(rotation);                   // original00688369 movq mm4, qword ptr [esp]
    mm2 = punpckhdq(mm2, mm0);              // original0068836d punpckhdq mm2, mm0
    mm5 = pair(rotation + 16u);             // original00688370 movq mm5, qword ptr [esp + 0x10]
    mm3 = punpckhdq(mm3, mm1);              // original00688375 punpckhdq mm3, mm1
    mm6 = pair(rotation + 32u);             // original00688378 movq mm6, qword ptr [esp + 0x20]
    mm0 = punpckldq(mm0, mm0);              // original0068837d punpckldq mm0, mm0
    mm1 = punpckldq(mm1, mm1);              // original00688380 punpckldq mm1, mm1
    mm4 = pfmul(mm4, mm0);                  // original00688383 pfmul mm4, mm0
    mm2 = punpckhdq(mm2, mm2);              // original00688387 punpckhdq mm2, mm2
    mm0 = pfmul(mm0, pair(rotation + 8u));  // original0068838a pfmul mm0, qword ptr [esp + 8]
    mm7 = pair(rotation + 48u);             // original00688390 movq mm7, qword ptr [esp + 0x30]
    mm5 = pfmul(mm5, mm2);                  // original00688395 pfmul mm5, mm2
    mm3 = punpckhdq(mm3, mm3);              // original00688399 punpckhdq mm3, mm3
    mm2 = pfmul(mm2, pair(rotation + 24u)); // original0068839c pfmul mm2, qword ptr [esp + 0x18]
    mm5 = pfadd(mm5, mm4);                  // original006883a2 pfadd mm5, mm4
    mm6 = pfmul(mm6, mm1);                  // original006883a6 pfmul mm6, mm1
    mm2 = pfadd(mm2, mm0);                  // original006883aa pfadd mm2, mm0
    mm1 = pfmul(mm1, pair(rotation + 40u)); // original006883ae pfmul mm1, qword ptr [esp + 0x28]
    mm6 = pfadd(mm6, mm5);                  // original006883b4 pfadd mm6, mm5
    mm7 = pfmul(mm7, mm3);                  // original006883b8 pfmul mm7, mm3
    mm2 = pfadd(mm2, mm1);                  // original006883bc pfadd mm2, mm1
    mm3 = pfmul(mm3, pair(rotation + 56u)); // original006883c0 pfmul mm3, qword ptr [esp + 0x38]
    mm7 = pfadd(mm7, mm6);                  // original006883c6 pfadd mm7, mm6
    mm0 = pair(eax + 16u);                  // original006883ca movq mm0, qword ptr [eax + 0x10]
    mm3 = pfadd(mm3, mm2);                  // original006883ce pfadd mm3, mm2
    mm1 = pair(eax + 24u);                  // original006883d2 movq mm1, qword ptr [eax + 0x18]
    store(eax, mm7);                        // original006883d6 movq qword ptr [eax], mm7
    mm4 = pair(rotation);                   // original006883d9 movq mm4, qword ptr [esp]
    store(eax + 8u, mm3);                   // original006883dd movq qword ptr [eax + 8], mm3
    mm2 = punpckhdq(mm2, mm0);              // original006883e1 punpckhdq mm2, mm0
    mm5 = pair(rotation + 16u);             // original006883e4 movq mm5, qword ptr [esp + 0x10]
    mm3 = punpckhdq(mm3, mm1);              // original006883e9 punpckhdq mm3, mm1
    mm6 = pair(rotation + 32u);             // original006883ec movq mm6, qword ptr [esp + 0x20]
    mm0 = punpckldq(mm0, mm0);              // original006883f1 punpckldq mm0, mm0
    mm1 = punpckldq(mm1, mm1);              // original006883f4 punpckldq mm1, mm1
    mm4 = pfmul(mm4, mm0);                  // original006883f7 pfmul mm4, mm0
    mm2 = punpckhdq(mm2, mm2);              // original006883fb punpckhdq mm2, mm2
    mm0 = pfmul(mm0, pair(rotation + 8u));  // original006883fe pfmul mm0, qword ptr [esp + 8]
    mm7 = pair(rotation + 48u);             // original00688404 movq mm7, qword ptr [esp + 0x30]
    mm5 = pfmul(mm5, mm2);                  // original00688409 pfmul mm5, mm2
    mm3 = punpckhdq(mm3, mm3);              // original0068840d punpckhdq mm3, mm3
    mm2 = pfmul(mm2, pair(rotation + 24u)); // original00688410 pfmul mm2, qword ptr [esp + 0x18]
    mm5 = pfadd(mm5, mm4);                  // original00688416 pfadd mm5, mm4
    mm6 = pfmul(mm6, mm1);                  // original0068841a pfmul mm6, mm1
    mm2 = pfadd(mm2, mm0);                  // original0068841e pfadd mm2, mm0
    mm1 = pfmul(mm1, pair(rotation + 40u)); // original00688422 pfmul mm1, qword ptr [esp + 0x28]
    mm6 = pfadd(mm6, mm5);                  // original00688428 pfadd mm6, mm5
    mm7 = pfmul(mm7, mm3);                  // original0068842c pfmul mm7, mm3
    mm2 = pfadd(mm2, mm1);                  // original00688430 pfadd mm2, mm1
    mm3 = pfmul(mm3, pair(rotation + 56u)); // original00688434 pfmul mm3, qword ptr [esp + 0x38]
    mm7 = pfadd(mm7, mm6);                  // original0068843a pfadd mm7, mm6
    mm0 = pair(eax + 32u);                  // original0068843e movq mm0, qword ptr [eax + 0x20]
    mm3 = pfadd(mm3, mm2);                  // original00688442 pfadd mm3, mm2
    mm1 = pair(eax + 40u);                  // original00688446 movq mm1, qword ptr [eax + 0x28]
    store(eax + 16u, mm7);                  // original0068844a movq qword ptr [eax + 0x10], mm7
    mm4 = pair(rotation);                   // original0068844e movq mm4, qword ptr [esp]
    store(eax + 24u, mm3);                  // original00688452 movq qword ptr [eax + 0x18], mm3
    mm2 = punpckhdq(mm2, mm0);              // original00688456 punpckhdq mm2, mm0
    mm5 = pair(rotation + 16u);             // original00688459 movq mm5, qword ptr [esp + 0x10]
    mm3 = punpckhdq(mm3, mm1);              // original0068845e punpckhdq mm3, mm1
    mm6 = pair(rotation + 32u);             // original00688461 movq mm6, qword ptr [esp + 0x20]
    mm0 = punpckldq(mm0, mm0);              // original00688466 punpckldq mm0, mm0
    mm1 = punpckldq(mm1, mm1);              // original00688469 punpckldq mm1, mm1
    mm4 = pfmul(mm4, mm0);                  // original0068846c pfmul mm4, mm0
    mm2 = punpckhdq(mm2, mm2);              // original00688470 punpckhdq mm2, mm2
    mm0 = pfmul(mm0, pair(rotation + 8u));  // original00688473 pfmul mm0, qword ptr [esp + 8]
    mm7 = pair(rotation + 48u);             // original00688479 movq mm7, qword ptr [esp + 0x30]
    mm5 = pfmul(mm5, mm2);                  // original0068847e pfmul mm5, mm2
    mm3 = punpckhdq(mm3, mm3);              // original00688482 punpckhdq mm3, mm3
    mm2 = pfmul(mm2, pair(rotation + 24u)); // original00688485 pfmul mm2, qword ptr [esp + 0x18]
    mm5 = pfadd(mm5, mm4);                  // original0068848b pfadd mm5, mm4
    mm6 = pfmul(mm6, mm1);                  // original0068848f pfmul mm6, mm1
    mm2 = pfadd(mm2, mm0);                  // original00688493 pfadd mm2, mm0
    mm1 = pfmul(mm1, pair(rotation + 40u)); // original00688497 pfmul mm1, qword ptr [esp + 0x28]
    mm6 = pfadd(mm6, mm5);                  // original0068849d pfadd mm6, mm5
    mm7 = pfmul(mm7, mm3);                  // original006884a1 pfmul mm7, mm3
    mm2 = pfadd(mm2, mm1);                  // original006884a5 pfadd mm2, mm1
    mm3 = pfmul(mm3, pair(rotation + 56u)); // original006884a9 pfmul mm3, qword ptr [esp + 0x38]
    mm7 = pfadd(mm7, mm6);                  // original006884af pfadd mm7, mm6
    mm0 = pair(eax + 48u);                  // original006884b3 movq mm0, qword ptr [eax + 0x30]
    mm3 = pfadd(mm3, mm2);                  // original006884b7 pfadd mm3, mm2
    mm1 = pair(eax + 56u);                  // original006884bb movq mm1, qword ptr [eax + 0x38]
    store(eax + 32u, mm7);                  // original006884bf movq qword ptr [eax + 0x20], mm7
    mm4 = pair(rotation);                   // original006884c3 movq mm4, qword ptr [esp]
    store(eax + 40u, mm3);                  // original006884c7 movq qword ptr [eax + 0x28], mm3
    mm2 = punpckhdq(mm2, mm0);              // original006884cb punpckhdq mm2, mm0
    mm5 = pair(rotation + 16u);             // original006884ce movq mm5, qword ptr [esp + 0x10]
    mm3 = punpckhdq(mm3, mm1);              // original006884d3 punpckhdq mm3, mm1
    mm6 = pair(rotation + 32u);             // original006884d6 movq mm6, qword ptr [esp + 0x20]
    mm0 = punpckldq(mm0, mm0);              // original006884db punpckldq mm0, mm0
    mm1 = punpckldq(mm1, mm1);              // original006884de punpckldq mm1, mm1
    mm4 = pfmul(mm4, mm0);                  // original006884e1 pfmul mm4, mm0
    mm2 = punpckhdq(mm2, mm2);              // original006884e5 punpckhdq mm2, mm2
    mm0 = pfmul(mm0, pair(rotation + 8u));  // original006884e8 pfmul mm0, qword ptr [esp + 8]
    mm7 = pair(rotation + 48u);             // original006884ee movq mm7, qword ptr [esp + 0x30]
    mm5 = pfmul(mm5, mm2);                  // original006884f3 pfmul mm5, mm2
    mm3 = punpckhdq(mm3, mm3);              // original006884f7 punpckhdq mm3, mm3
    mm2 = pfmul(mm2, pair(rotation + 24u)); // original006884fa pfmul mm2, qword ptr [esp + 0x18]
    mm5 = pfadd(mm5, mm4);                  // original00688500 pfadd mm5, mm4
    mm6 = pfmul(mm6, mm1);                  // original00688504 pfmul mm6, mm1
    mm2 = pfadd(mm2, mm0);                  // original00688508 pfadd mm2, mm0
    mm1 = pfmul(mm1, pair(rotation + 40u)); // original0068850c pfmul mm1, qword ptr [esp + 0x28]
    mm6 = pfadd(mm6, mm5);                  // original00688512 pfadd mm6, mm5
    mm7 = pfmul(mm7, mm3);                  // original00688516 pfmul mm7, mm3
    mm2 = pfadd(mm2, mm1);                  // original0068851a pfadd mm2, mm1
    mm3 = pfmul(mm3, pair(rotation + 56u)); // original0068851e pfmul mm3, qword ptr [esp + 0x38]
    mm7 = pfadd(mm7, mm6);                  // original00688524 pfadd mm7, mm6
    mm3 = pfadd(mm3, mm2);                  // original00688528 pfadd mm3, mm2
    store(eax + 48u, mm7);                  // original0068852c movq qword ptr [eax + 0x30], mm7
    store(eax + 56u, mm3);                  // original00688530 movq qword ptr [eax + 0x38], mm3
L_00688534:;
    edx = word(arguments + 16u); // original00688534 mov edx, dword ptr [esp + 0x54]
    zero = (edx == 0);           // original00688538 test edx, edx
    if (zero)
        goto L_0068855b;          // original0068853a je 0x68855b
    mm0 = pair(edx);              // original0068853c movq mm0, qword ptr [edx]
    mm1 = single(edx + 8u);       // original0068853f movd mm1, dword ptr [edx + 8]
    mm2 = pair(eax + 48u);        // original00688543 movq mm2, qword ptr [eax + 0x30]
    mm3 = single(eax + 56u);      // original00688547 movd mm3, dword ptr [eax + 0x38]
    mm0 = pfadd(mm0, mm2);        // original0068854b pfadd mm0, mm2
    mm1 = pfadd(mm1, mm3);        // original0068854f pfadd mm1, mm3
    store(eax + 48u, mm0);        // original00688553 movq qword ptr [eax + 0x30], mm0
    store_single(eax + 56u, mm1); // original00688557 movd dword ptr [eax + 0x38], mm1
L_0068855b:;
    ; // Original private64B frame allocation/release; explicit bounded bridge storage. // original0068855b add esp, 0x40
    empty();    // original0068855e femms
    return eax; // original00688560 ret 0x14
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068802f(void*, uint32_t, const void*,
                                                              const void*, const void*) {
    // Allocate the actual bounded64B private matrix as an explicit helper operand.
    __asm__ volatile(
        "subl $64,%esp\n\tleal 68(%esp),%eax\n\tpushl %esp\n\tpushl %eax\n\tcalll _recovered_0068802f\n\taddl $8,%esp\n\taddl $64,%esp\n\tretl $20");
}
