#include "graphics/render_quaternion_setup_amd.h"
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
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
AMD Packed call_acos(Packed input) {
    Packed output;
    __asm__ volatile("movq %1,%%mm0\n\tcalll _FUN_006a6940\n\tmovq %%mm0,%0"
                     : "=m"(output)
                     : "m"(input)
                     : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "memory", "cc");
    return output;
}
AMD Packed call_sine(Packed input) {
    Packed output;
    __asm__ volatile("movq %1,%%mm0\n\tcalll _FUN_006a7020\n\tmovq %%mm0,%0"
                     : "=m"(output)
                     : "m"(input)
                     : "eax", "ebx", "ecx", "edx", "esi", "mm0", "mm1", "mm2", "mm3", "mm4", "mm5",
                       "mm6", "mm7", "memory", "cc");
    return output;
}
AMD Packed call_trig(Packed input) {
    Packed output;
    __asm__ volatile("movq %1,%%mm0\n\tcalll _FUN_006a6f20\n\tmovq %%mm0,%0"
                     : "=m"(output)
                     : "m"(input)
                     : "eax", "ebx", "ecx", "edx", "esi", "mm0", "mm1", "mm2", "mm3", "mm4", "mm5",
                       "mm6", "mm7", "memory", "cc");
    return output;
}
} // namespace

extern "C" alignas(8) const u32 dat_006f0188[2] = {0x80000000u, 0x80000000u};
extern "C" alignas(8) const u32 dat_006f39b0[2] = {0xbe800000u, 0xbe800000u};
// Complete006859de..00686419. The adapter owns the exact original160B
// aligned main frame plus its initialized temporary12B. C++ arguments/spills
// are placed below those spans; saved incomingESI/EBX are explicit inputs.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_006859de(u32 arguments, u32 frame,
                                                                     u32 incoming_esi,
                                                                     u32 incoming_ebx) {
    u32 eax, ecx, edx, esi = incoming_esi, ebx = incoming_ebx;
    bool zero = false;
    Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    // Original adapter-owned frame/save/alignment operation. // original006859de mov edi, edi
    // Original adapter-owned frame/save/alignment operation. // original006859e0 push ebp
    // Original adapter-owned frame/save/alignment operation. // original006859e1 mov ebp, esp
    // Original adapter-owned frame/save/alignment operation. // original006859e3 sub esp, 0xa0
    // Original adapter-owned frame/save/alignment operation. // original006859e9 and esp, 0xfffffff8
    edx = word(reinterpret_cast<const u32*>(
        arguments + 12u)); // original006859ec mov edx, dword ptr [ebp + 0x14]
    ecx = word(reinterpret_cast<const u32*>(
        arguments + 16u));   // original006859ef mov ecx, dword ptr [ebp + 0x18]
    mm0 = pair(edx);         // original006859f2 movq mm0, qword ptr [edx]
    mm1 = pair(edx + 0x8u);  // original006859f5 movq mm1, qword ptr [edx + 8]
    mm2 = mm0;               // original006859f9 movq mm2, mm0
    mm3 = mm1;               // original006859fc movq mm3, mm1
    store(frame + 0u, mm0);  // original006859ff movq qword ptr [esp], mm0
    store(frame + 8u, mm1);  // original00685a03 movq qword ptr [esp + 8], mm1
    mm4 = pair(ecx);         // original00685a08 movq mm4, qword ptr [ecx]
    mm5 = pair(ecx + 0x8u);  // original00685a0b movq mm5, qword ptr [ecx + 8]
    store(frame + 16u, mm4); // original00685a0f movq qword ptr [esp + 0x10], mm4
    mm0 = pfadd(mm0, mm4);   // original00685a14 pfadd mm0, mm4
    store(frame + 24u, mm5); // original00685a18 movq qword ptr [esp + 0x18], mm5
    mm1 = pfadd(mm1, mm5);   // original00685a1d pfadd mm1, mm5
    mm2 = pfsub(mm2, mm4);   // original00685a21 pfsub mm2, mm4
    mm0 = pfmul(mm0, mm0);   // original00685a25 pfmul mm0, mm0
    mm3 = pfsub(mm3, mm5);   // original00685a29 pfsub mm3, mm5
    mm1 = pfmul(mm1, mm1);   // original00685a2d pfmul mm1, mm1
    edx = word(reinterpret_cast<const u32*>(
        arguments + 20u));      // original00685a31 mov edx, dword ptr [ebp + 0x1c]
    mm2 = pfmul(mm2, mm2);      // original00685a34 pfmul mm2, mm2
    mm3 = pfmul(mm3, mm3);      // original00685a38 pfmul mm3, mm3
    mm0 = pfadd(mm0, mm1);      // original00685a3c pfadd mm0, mm1
    mm2 = pfadd(mm2, mm3);      // original00685a40 pfadd mm2, mm3
    mm6 = pair(edx);            // original00685a44 movq mm6, qword ptr [edx]
    mm7 = pair(edx + 0x8u);     // original00685a47 movq mm7, qword ptr [edx + 8]
    store(frame + 32u, mm6);    // original00685a4b movq qword ptr [esp + 0x20], mm6
    store(frame + 40u, mm7);    // original00685a50 movq qword ptr [esp + 0x28], mm7
    mm1 = mm4;                  // original00685a55 movq mm1, mm4
    mm3 = mm5;                  // original00685a58 movq mm3, mm5
    mm4 = pfadd(mm4, mm6);      // original00685a5b pfadd mm4, mm6
    mm5 = pfadd(mm5, mm7);      // original00685a5f pfadd mm5, mm7
    mm1 = pfsub(mm1, mm6);      // original00685a63 pfsub mm1, mm6
    mm3 = pfsub(mm3, mm7);      // original00685a67 pfsub mm3, mm7
    mm4 = pfmul(mm4, mm4);      // original00685a6b pfmul mm4, mm4
    mm5 = pfmul(mm5, mm5);      // original00685a6f pfmul mm5, mm5
    mm1 = pfmul(mm1, mm1);      // original00685a73 pfmul mm1, mm1
    mm3 = pfmul(mm3, mm3);      // original00685a77 pfmul mm3, mm3
    mm4 = pfadd(mm4, mm5);      // original00685a7b pfadd mm4, mm5
    mm1 = pfadd(mm1, mm3);      // original00685a7f pfadd mm1, mm3
    mm0 = pfacc(mm0, mm4);      // original00685a83 pfacc mm0, mm4
    mm2 = pfacc(mm2, mm1);      // original00685a87 pfacc mm2, mm1
    mm2 = pfcmpgt(mm2, mm0);    // original00685a8b pfcmpgt mm2, mm0
    mm2 = packsswb(mm2, mm2);   // original00685a8f packsswb mm2, mm2
    eax = low(mm2);             // original00685a92 movd eax, mm2
    zero = ((eax & 0x1u) == 0); // original00685a95 test eax, 1
    mm0 = pair(
        reinterpret_cast<u32>(dat_006f0188)); // original00685a9a movq mm0, qword ptr [0x6f0188]
    if (zero)
        goto L_00685abc; // original00685aa1 je 0x685abc
    edx = word(reinterpret_cast<const u32*>(
        arguments + 12u));             // original00685aa3 mov edx, dword ptr [ebp + 0x14]
    mm1 = mm0;                         // original00685aa6 movq mm1, mm0
    mm2 = mm0;                         // original00685aa9 movq mm2, mm0
    mm1 = pxor(mm1, pair(edx));        // original00685aac pxor mm1, qword ptr [edx]
    mm2 = pxor(mm2, pair(edx + 0x8u)); // original00685aaf pxor mm2, qword ptr [edx + 8]
    store(frame + 0u, mm1);            // original00685ab3 movq qword ptr [esp], mm1
    store(frame + 8u, mm2);            // original00685ab7 movq qword ptr [esp + 8], mm2
L_00685abc:;
    zero = ((eax & 0x10000u) == 0); // original00685abc test eax, 0x10000
    if (zero)
        goto L_00685add; // original00685ac1 je 0x685add
    ecx = word(reinterpret_cast<const u32*>(
        arguments + 20u));             // original00685ac3 mov ecx, dword ptr [ebp + 0x1c]
    mm1 = mm0;                         // original00685ac6 movq mm1, mm0
    mm2 = mm0;                         // original00685ac9 movq mm2, mm0
    mm1 = pxor(mm1, pair(ecx));        // original00685acc pxor mm1, qword ptr [ecx]
    mm2 = pxor(mm2, pair(ecx + 0x8u)); // original00685acf pxor mm2, qword ptr [ecx + 8]
    store(frame + 32u, mm1);           // original00685ad3 movq qword ptr [esp + 0x20], mm1
    store(frame + 40u, mm2);           // original00685ad8 movq qword ptr [esp + 0x28], mm2
L_00685add:;
    ecx = word(reinterpret_cast<const u32*>(
        arguments + 24u));      // original00685add mov ecx, dword ptr [ebp + 0x20]
    mm6 = pair(frame + 32u);    // original00685ae0 movq mm6, qword ptr [esp + 0x20]
    mm7 = pair(frame + 40u);    // original00685ae5 movq mm7, qword ptr [esp + 0x28]
    mm1 = pair(ecx);            // original00685aea movq mm1, qword ptr [ecx]
    mm4 = pair(ecx + 0x8u);     // original00685aed movq mm4, qword ptr [ecx + 8]
    mm3 = mm6;                  // original00685af1 movq mm3, mm6
    mm5 = mm7;                  // original00685af4 movq mm5, mm7
    mm6 = pfadd(mm6, mm1);      // original00685af7 pfadd mm6, mm1
    store(frame + 48u, mm1);    // original00685afb movq qword ptr [esp + 0x30], mm1
    mm7 = pfadd(mm7, mm4);      // original00685b00 pfadd mm7, mm4
    store(frame + 56u, mm4);    // original00685b04 movq qword ptr [esp + 0x38], mm4
    mm3 = pfsub(mm3, mm1);      // original00685b09 pfsub mm3, mm1
    mm5 = pfsub(mm5, mm4);      // original00685b0d pfsub mm5, mm4
    mm6 = pfmul(mm6, mm6);      // original00685b11 pfmul mm6, mm6
    mm7 = pfmul(mm7, mm7);      // original00685b15 pfmul mm7, mm7
    mm3 = pfmul(mm3, mm3);      // original00685b19 pfmul mm3, mm3
    mm5 = pfmul(mm5, mm5);      // original00685b1d pfmul mm5, mm5
    mm6 = pfadd(mm6, mm7);      // original00685b21 pfadd mm6, mm7
    mm3 = pfadd(mm3, mm5);      // original00685b25 pfadd mm3, mm5
    mm6 = pfacc(mm6, mm6);      // original00685b29 pfacc mm6, mm6
    mm3 = pfacc(mm3, mm3);      // original00685b2d pfacc mm3, mm3
    mm3 = pfcmpgt(mm3, mm6);    // original00685b31 pfcmpgt mm3, mm6
    eax = low(mm3);             // original00685b35 movd eax, mm3
    zero = ((eax & 0x1u) == 0); // original00685b38 test eax, 1
    if (zero)
        goto L_00685b56; // original00685b3d je 0x685b56
    edx = word(reinterpret_cast<const u32*>(
        arguments + 24u));             // original00685b3f mov edx, dword ptr [ebp + 0x20]
    mm2 = mm0;                         // original00685b42 movq mm2, mm0
    mm0 = pxor(mm0, pair(edx));        // original00685b45 pxor mm0, qword ptr [edx]
    mm2 = pxor(mm2, pair(edx + 0x8u)); // original00685b48 pxor mm2, qword ptr [edx + 8]
    store(frame + 48u, mm0);           // original00685b4c movq qword ptr [esp + 0x30], mm0
    store(frame + 56u, mm2);           // original00685b51 movq qword ptr [esp + 0x38], mm2
L_00685b56:;
    mm0 = pair(frame + 16u); // original00685b56 movq mm0, qword ptr [esp + 0x10]
    mm1 = mm0;               // original00685b5b movq mm1, mm0
    mm2 = pair(frame + 24u); // original00685b5e movq mm2, qword ptr [esp + 0x18]
    mm3 = mm2;               // original00685b63 movq mm3, mm2
    mm0 = pfmul(mm0, mm0);   // original00685b66 pfmul mm0, mm0
    mm2 = pfmul(mm2, mm2);   // original00685b6a pfmul mm2, mm2
    mm0 = pfadd(mm0, mm2);   // original00685b6e pfadd mm0, mm2
    mm0 = pfacc(mm0, mm0);   // original00685b72 pfacc mm0, mm0
    mm5 = mm0;               // original00685b76 movq mm5, mm0
    mm4 = reciprocal(mm0);   // original00685b79 pfrcp mm4, mm0
    mm5 = pfcmpgt(mm5, pair(reinterpret_cast<u32>(
                           dat_006f01d0))); // original00685b7d pfcmpgt mm5, qword ptr [0x6f01d0]
    mm1 = pxor(mm1, pair(reinterpret_cast<u32>(
                        dat_006f0230))); // original00685b85 pxor mm1, qword ptr [0x6f0230]
    mm3 = pxor(mm3, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685b8c pxor mm3, qword ptr [0x6f0178]
    mm0 = pfrcpit1(mm0, mm4);            // original00685b93 pfrcpit1 mm0, mm4
    mm1 = pand(mm1, mm5);                // original00685b97 pand mm1, mm5
    mm3 = pand(mm3, mm5);                // original00685b9a pand mm3, mm5
    mm0 = pfrcpit2(mm0, mm4);            // original00685b9d pfrcpit2 mm0, mm4
    mm1 = pfmul(mm1, mm0);               // original00685ba1 pfmul mm1, mm0
    mm3 = pfmul(mm3, mm0);               // original00685ba5 pfmul mm3, mm0
    store(frame + 64u, mm1);             // original00685ba9 movq qword ptr [esp + 0x40], mm1
    store(frame + 72u, mm3);             // original00685bae movq qword ptr [esp + 0x48], mm3
    mm2 = pair(frame + 0u);              // original00685bb3 movq mm2, qword ptr [esp]
    mm3 = pair(frame + 8u);              // original00685bb7 movq mm3, qword ptr [esp + 8]
    mm4 = mm2;                           // original00685bbc movq mm4, mm2
    mm5 = mm3;                           // original00685bbf movq mm5, mm3
    mm0 = pair(frame + 64u);             // original00685bc2 movq mm0, qword ptr [esp + 0x40]
    mm4 = punpckhdq(mm4, mm2);           // original00685bc7 punpckhdq mm4, mm2
    mm5 = punpckhdq(mm5, mm3);           // original00685bca punpckhdq mm5, mm3
    mm1 = pair(frame + 72u);             // original00685bcd movq mm1, qword ptr [esp + 0x48]
    mm4 = punpckldq(mm4, mm2);           // original00685bd2 punpckldq mm4, mm2
    mm5 = punpckldq(mm5, mm3);           // original00685bd5 punpckldq mm5, mm3
    mm6 = mm4;                           // original00685bd8 movq mm6, mm4
    mm7 = mm5;                           // original00685bdb movq mm7, mm5
    mm2 = pfmul(mm2, mm1);               // original00685bde pfmul mm2, mm1
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685be2 pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original00685be9 pfmul mm3, mm0
    mm2 = pxor(mm2, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685bed pxor mm2, qword ptr [0x6f0178]
    mm5 = pfmul(mm5, mm0);               // original00685bf4 pfmul mm5, mm0
    mm4 = pfmul(mm4, mm1);               // original00685bf8 pfmul mm4, mm1
    mm2 = pfadd(mm2, mm3);               // original00685bfc pfadd mm2, mm3
    mm3 = pair(frame + 0u);              // original00685c00 movq mm3, qword ptr [esp]
    mm4 = pfsub(mm4, mm5);               // original00685c04 pfsub mm4, mm5
    mm5 = pair(frame + 8u);              // original00685c08 movq mm5, qword ptr [esp + 8]
    mm7 = pfmul(mm7, mm1);               // original00685c0d pfmul mm7, mm1
    mm6 = pxor(mm6, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685c11 pxor mm6, qword ptr [0x6f0178]
    mm4 = pfacc(mm4, mm2);               // original00685c18 pfacc mm4, mm2
    mm6 = pfmul(mm6, mm0);               // original00685c1c pfmul mm6, mm0
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685c20 pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original00685c27 pfmul mm3, mm0
    store(frame + 128u, mm4);            // original00685c2b movq qword ptr [esp + 0x80], mm4
    mm5 = pfmul(mm5, mm1);               // original00685c33 pfmul mm5, mm1
    mm6 = pfadd(mm6, mm7);               // original00685c37 pfadd mm6, mm7
    mm5 = pfsub(mm5, mm3);               // original00685c3b pfsub mm5, mm3
    mm6 = pfacc(mm6, mm5);               // original00685c3f pfacc mm6, mm5
    store(frame + 136u, mm6);            // original00685c43 movq qword ptr [esp + 0x88], mm6
    mm2 = pair(frame + 32u);             // original00685c4b movq mm2, qword ptr [esp + 0x20]
    mm3 = pair(frame + 40u);             // original00685c50 movq mm3, qword ptr [esp + 0x28]
    mm4 = mm2;                           // original00685c55 movq mm4, mm2
    mm5 = mm3;                           // original00685c58 movq mm5, mm3
    mm0 = pair(frame + 64u);             // original00685c5b movq mm0, qword ptr [esp + 0x40]
    mm4 = punpckhdq(mm4, mm2);           // original00685c60 punpckhdq mm4, mm2
    mm5 = punpckhdq(mm5, mm3);           // original00685c63 punpckhdq mm5, mm3
    mm1 = pair(frame + 72u);             // original00685c66 movq mm1, qword ptr [esp + 0x48]
    mm4 = punpckldq(mm4, mm2);           // original00685c6b punpckldq mm4, mm2
    mm5 = punpckldq(mm5, mm3);           // original00685c6e punpckldq mm5, mm3
    mm6 = mm4;                           // original00685c71 movq mm6, mm4
    mm7 = mm5;                           // original00685c74 movq mm7, mm5
    mm2 = pfmul(mm2, mm1);               // original00685c77 pfmul mm2, mm1
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685c7b pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original00685c82 pfmul mm3, mm0
    mm2 = pxor(mm2, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685c86 pxor mm2, qword ptr [0x6f0178]
    mm5 = pfmul(mm5, mm0);               // original00685c8d pfmul mm5, mm0
    mm4 = pfmul(mm4, mm1);               // original00685c91 pfmul mm4, mm1
    mm2 = pfadd(mm2, mm3);               // original00685c95 pfadd mm2, mm3
    mm3 = pair(frame + 32u);             // original00685c99 movq mm3, qword ptr [esp + 0x20]
    mm4 = pfsub(mm4, mm5);               // original00685c9e pfsub mm4, mm5
    mm5 = pair(frame + 40u);             // original00685ca2 movq mm5, qword ptr [esp + 0x28]
    mm7 = pfmul(mm7, mm1);               // original00685ca7 pfmul mm7, mm1
    mm6 = pxor(mm6, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685cab pxor mm6, qword ptr [0x6f0178]
    mm4 = pfacc(mm4, mm2);               // original00685cb2 pfacc mm4, mm2
    mm6 = pfmul(mm6, mm0);               // original00685cb6 pfmul mm6, mm0
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685cba pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original00685cc1 pfmul mm3, mm0
    store(frame + 144u, mm4);            // original00685cc5 movq qword ptr [esp + 0x90], mm4
    mm5 = pfmul(mm5, mm1);               // original00685ccd pfmul mm5, mm1
    mm6 = pfadd(mm6, mm7);               // original00685cd1 pfadd mm6, mm7
    mm5 = pfsub(mm5, mm3);               // original00685cd5 pfsub mm5, mm3
    mm6 = pfacc(mm6, mm5);               // original00685cd9 pfacc mm6, mm5
    store(frame + 152u, mm6);            // original00685cdd movq qword ptr [esp + 0x98], mm6
    // Adapter already reserves this original temporary12B; its actual words remain explicit. // original00685ce5 sub esp, 0xc
    mm1 = pair(frame + 128u);  // original00685ce8 movq mm1, qword ptr [esp + 0x8c]
    mm2 = pair(frame + 136u);  // original00685cf0 movq mm2, qword ptr [esp + 0x94]
    mm3 = mm2;                 // original00685cf8 movq mm3, mm2
    mm3 = punpckhdq(mm3, mm3); // original00685cfb punpckhdq mm3, mm3
    mm0 = mm3;                 // original00685cfe movq mm0, mm3
    mm3 = pfcmpge(mm3, pair(reinterpret_cast<u32>(
                           dat_006f01e8))); // original00685d01 pfcmpge mm3, qword ptr [0x6f01e8]
    ecx = low(mm3);                         // original00685d09 movd ecx, mm3
    zero = ((ecx & ecx) == 0);              // original00685d0c test ecx, ecx
    if (!zero)
        goto L_00685d76;            // original00685d0e jne 0x685d76
    mm0 = call_acos(mm0);           // original00685d10 call 0x6a6940
    store_single(frame - 12u, mm0); // original00685d15 movd dword ptr [esp], mm0
    put(frame - 8u, esi);           // original00685d19 mov dword ptr [esp + 4], esi
    put(frame - 4u, ebx);           // original00685d1d mov dword ptr [esp + 8], ebx
    mm0 = call_sine(mm0);           // original00685d21 call 0x6a7020
    mm3 = mm0;                      // original00685d26 movq mm3, mm0
    esi = word(
        reinterpret_cast<const u32*>(frame - 8u)); // original00685d29 mov esi, dword ptr [esp + 4]
    mm3 = pand(mm3, pair(reinterpret_cast<u32>(
                        dat_006f01a0))); // original00685d2d pand mm3, qword ptr [0x6f01a0]
    ebx = word(
        reinterpret_cast<const u32*>(frame - 4u)); // original00685d34 mov ebx, dword ptr [esp + 8]
    mm3 = pfcmpge(mm3, pair(reinterpret_cast<u32>(
                           dat_006f01a8))); // original00685d38 pfcmpge mm3, qword ptr [0x6f01a8]
    ecx = low(mm3);                         // original00685d40 movd ecx, mm3
    mm1 = pair(frame + 128u);               // original00685d43 movq mm1, qword ptr [esp + 0x8c]
    mm2 = pair(frame + 136u);               // original00685d4b movq mm2, qword ptr [esp + 0x94]
    zero = ((ecx & ecx) == 0);              // original00685d53 test ecx, ecx
    if (zero)
        goto L_00685d76;       // original00685d55 je 0x685d76
    mm3 = single(frame - 12u); // original00685d57 movd mm3, dword ptr [esp]
    mm4 = reciprocal(mm0);     // original00685d5b pfrcp mm4, mm0
    mm3 = punpckldq(mm3, mm3); // original00685d5f punpckldq mm3, mm3
    mm0 = pfrcpit1(mm0, mm4);  // original00685d62 pfrcpit1 mm0, mm4
    mm0 = pfrcpit2(mm0, mm4);  // original00685d66 pfrcpit2 mm0, mm4
    mm3 = pfmul(mm3, mm0);     // original00685d6a pfmul mm3, mm0
    mm1 = pfmul(mm1, mm3);     // original00685d6e pfmul mm1, mm3
    mm2 = pfmul(mm2, mm3);     // original00685d72 pfmul mm2, mm3
L_00685d76:;
    mm2 = pand(mm2, pair(reinterpret_cast<u32>(
                        dat_006f01b0))); // original00685d76 pand mm2, qword ptr [0x6f01b0]
    store(frame + 80u, mm1);             // original00685d7d movq qword ptr [esp + 0x5c], mm1
    store(frame + 88u, mm2);             // original00685d82 movq qword ptr [esp + 0x64], mm2
    // Adapter already reserves this original temporary12B; its actual words remain explicit. // original00685d87 add esp, 0xc
    // Adapter already reserves this original temporary12B; its actual words remain explicit. // original00685d8a sub esp, 0xc
    mm1 = pair(frame + 144u);  // original00685d8d movq mm1, qword ptr [esp + 0x9c]
    mm2 = pair(frame + 152u);  // original00685d95 movq mm2, qword ptr [esp + 0xa4]
    mm3 = mm2;                 // original00685d9d movq mm3, mm2
    mm3 = punpckhdq(mm3, mm3); // original00685da0 punpckhdq mm3, mm3
    mm0 = mm3;                 // original00685da3 movq mm0, mm3
    mm3 = pfcmpge(mm3, pair(reinterpret_cast<u32>(
                           dat_006f01e8))); // original00685da6 pfcmpge mm3, qword ptr [0x6f01e8]
    ecx = low(mm3);                         // original00685dae movd ecx, mm3
    zero = ((ecx & ecx) == 0);              // original00685db1 test ecx, ecx
    if (!zero)
        goto L_00685e1b;            // original00685db3 jne 0x685e1b
    mm0 = call_acos(mm0);           // original00685db5 call 0x6a6940
    store_single(frame - 12u, mm0); // original00685dba movd dword ptr [esp], mm0
    put(frame - 8u, esi);           // original00685dbe mov dword ptr [esp + 4], esi
    put(frame - 4u, ebx);           // original00685dc2 mov dword ptr [esp + 8], ebx
    mm0 = call_sine(mm0);           // original00685dc6 call 0x6a7020
    mm3 = mm0;                      // original00685dcb movq mm3, mm0
    esi = word(
        reinterpret_cast<const u32*>(frame - 8u)); // original00685dce mov esi, dword ptr [esp + 4]
    mm3 = pand(mm3, pair(reinterpret_cast<u32>(
                        dat_006f01a0))); // original00685dd2 pand mm3, qword ptr [0x6f01a0]
    ebx = word(
        reinterpret_cast<const u32*>(frame - 4u)); // original00685dd9 mov ebx, dword ptr [esp + 8]
    mm3 = pfcmpge(mm3, pair(reinterpret_cast<u32>(
                           dat_006f01a8))); // original00685ddd pfcmpge mm3, qword ptr [0x6f01a8]
    ecx = low(mm3);                         // original00685de5 movd ecx, mm3
    mm1 = pair(frame + 144u);               // original00685de8 movq mm1, qword ptr [esp + 0x9c]
    mm2 = pair(frame + 152u);               // original00685df0 movq mm2, qword ptr [esp + 0xa4]
    zero = ((ecx & ecx) == 0);              // original00685df8 test ecx, ecx
    if (zero)
        goto L_00685e1b;       // original00685dfa je 0x685e1b
    mm3 = single(frame - 12u); // original00685dfc movd mm3, dword ptr [esp]
    mm4 = reciprocal(mm0);     // original00685e00 pfrcp mm4, mm0
    mm3 = punpckldq(mm3, mm3); // original00685e04 punpckldq mm3, mm3
    mm0 = pfrcpit1(mm0, mm4);  // original00685e07 pfrcpit1 mm0, mm4
    mm0 = pfrcpit2(mm0, mm4);  // original00685e0b pfrcpit2 mm0, mm4
    mm3 = pfmul(mm3, mm0);     // original00685e0f pfmul mm3, mm0
    mm1 = pfmul(mm1, mm3);     // original00685e13 pfmul mm1, mm3
    mm2 = pfmul(mm2, mm3);     // original00685e17 pfmul mm2, mm3
L_00685e1b:;
    mm2 = pand(mm2, pair(reinterpret_cast<u32>(
                        dat_006f01b0))); // original00685e1b pand mm2, qword ptr [0x6f01b0]
    store(frame + 96u, mm1);             // original00685e22 movq qword ptr [esp + 0x6c], mm1
    store(frame + 104u, mm2);            // original00685e27 movq qword ptr [esp + 0x74], mm2
    // Adapter already reserves this original temporary12B; its actual words remain explicit. // original00685e2c add esp, 0xc
    mm0 = pair(frame + 80u);              // original00685e2f movq mm0, qword ptr [esp + 0x50]
    mm1 = pair(frame + 88u);              // original00685e34 movq mm1, qword ptr [esp + 0x58]
    mm0 = pfadd(mm0, pair(frame + 96u));  // original00685e39 pfadd mm0, qword ptr [esp + 0x60]
    mm1 = pfadd(mm1, pair(frame + 104u)); // original00685e3f pfadd mm1, qword ptr [esp + 0x68]
    mm0 = pfmul(mm0, pair(reinterpret_cast<u32>(
                         dat_006f39b0))); // original00685e45 pfmul mm0, qword ptr [0x6f39b0]
    mm1 = pfmul(mm1, pair(reinterpret_cast<u32>(
                         dat_006f39b0))); // original00685e4d pfmul mm1, qword ptr [0x6f39b0]
    store(frame + 128u, mm0);             // original00685e55 movq qword ptr [esp + 0x80], mm0
    store(frame + 136u, mm1);             // original00685e5d movq qword ptr [esp + 0x88], mm1
    mm7 = pair(
        reinterpret_cast<u32>(dat_006f01a8)); // original00685e65 movq mm7, qword ptr [0x6f01a8]
    // Adapter already reserves this original temporary12B; its actual words remain explicit. // original00685e6c sub esp, 0xc
    mm0 = pair(frame + 128u);       // original00685e6f movq mm0, qword ptr [esp + 0x8c]
    mm1 = single(frame + 136u);     // original00685e77 movd mm1, dword ptr [esp + 0x94]
    mm0 = pfmul(mm0, mm0);          // original00685e7f pfmul mm0, mm0
    mm1 = pfmul(mm1, mm1);          // original00685e83 pfmul mm1, mm1
    mm0 = pfadd(mm0, mm1);          // original00685e87 pfadd mm0, mm1
    mm0 = pfacc(mm0, mm0);          // original00685e8b pfacc mm0, mm0
    mm1 = estimate(mm0);            // original00685e8f pfrsqrt mm1, mm0
    mm2 = mm1;                      // original00685e93 movq mm2, mm1
    mm1 = pfmul(mm1, mm1);          // original00685e96 pfmul mm1, mm1
    put(frame - 8u, esi);           // original00685e9a mov dword ptr [esp + 4], esi
    mm1 = pfrsqit1(mm1, mm0);       // original00685e9e pfrsqit1 mm1, mm0
    put(frame - 4u, ebx);           // original00685ea2 mov dword ptr [esp + 8], ebx
    mm1 = pfrcpit2(mm1, mm2);       // original00685ea6 pfrcpit2 mm1, mm2
    store_single(frame - 12u, mm1); // original00685eaa movd dword ptr [esp], mm1
    mm0 = pfmul(mm0, mm1);          // original00685eae pfmul mm0, mm1
    mm0 = call_trig(mm0);           // original00685eb2 call 0x6a6f20
    mm1 = mm0;                      // original00685eb7 movq mm1, mm0
    mm0 = pand(mm0, pair(reinterpret_cast<u32>(
                        dat_006f0198))); // original00685eba pand mm0, qword ptr [0x6f0198]
    mm0 = pfcmpge(mm0, pair(reinterpret_cast<u32>(
                           dat_006f01a8))); // original00685ec1 pfcmpge mm0, qword ptr [0x6f01a8]
    mm0 = punpckhdq(mm0, mm0);              // original00685ec9 punpckhdq mm0, mm0
    ecx = low(mm0);                         // original00685ecc movd ecx, mm0
    mm2 = pair(frame + 128u);               // original00685ecf movq mm2, qword ptr [esp + 0x8c]
    mm0 = mm1;                              // original00685ed7 movq mm0, mm1
    mm1 = punpckhdq(mm1, mm1);              // original00685eda punpckhdq mm1, mm1
    zero = ((ecx & 0x1u) == 0);             // original00685edd test ecx, 1
    mm1 = pfmul(mm1, pair(frame - 12u));    // original00685ee3 pfmul mm1, qword ptr [esp]
    mm3 = single(frame + 136u);             // original00685ee8 movd mm3, dword ptr [esp + 0x94]
    if (zero)
        goto L_00685efd;       // original00685ef0 je 0x685efd
    mm1 = punpckldq(mm1, mm1); // original00685ef2 punpckldq mm1, mm1
    mm3 = pfmul(mm3, mm1);     // original00685ef5 pfmul mm3, mm1
    mm2 = pfmul(mm2, mm1);     // original00685ef9 pfmul mm2, mm1
L_00685efd:;
    mm3 = punpckldq(mm3, mm0); // original00685efd punpckldq mm3, mm0
    store(frame + 112u, mm2);  // original00685f00 movq qword ptr [esp + 0x7c], mm2
    store(frame + 120u, mm3);  // original00685f05 movq qword ptr [esp + 0x84], mm3
    esi = word(
        reinterpret_cast<const u32*>(frame - 8u)); // original00685f0d mov esi, dword ptr [esp + 4]
    ebx = word(
        reinterpret_cast<const u32*>(frame - 4u)); // original00685f11 mov ebx, dword ptr [esp + 8]
    // Adapter already reserves this original temporary12B; its actual words remain explicit. // original00685f15 add esp, 0xc
    eax = word(reinterpret_cast<const u32*>(arguments +
                                            0u)); // original00685f18 mov eax, dword ptr [ebp + 8]
    mm2 = pair(frame + 112u);  // original00685f1b movq mm2, qword ptr [esp + 0x70]
    mm3 = pair(frame + 120u);  // original00685f20 movq mm3, qword ptr [esp + 0x78]
    mm4 = mm2;                 // original00685f25 movq mm4, mm2
    mm5 = mm3;                 // original00685f28 movq mm5, mm3
    mm0 = pair(frame + 16u);   // original00685f2b movq mm0, qword ptr [esp + 0x10]
    mm4 = punpckhdq(mm4, mm2); // original00685f30 punpckhdq mm4, mm2
    mm5 = punpckhdq(mm5, mm3); // original00685f33 punpckhdq mm5, mm3
    mm1 = pair(frame + 24u);   // original00685f36 movq mm1, qword ptr [esp + 0x18]
    mm4 = punpckldq(mm4, mm2); // original00685f3b punpckldq mm4, mm2
    mm5 = punpckldq(mm5, mm3); // original00685f3e punpckldq mm5, mm3
    mm6 = mm4;                 // original00685f41 movq mm6, mm4
    mm7 = mm5;                 // original00685f44 movq mm7, mm5
    mm2 = pfmul(mm2, mm1);     // original00685f47 pfmul mm2, mm1
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685f4b pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original00685f52 pfmul mm3, mm0
    mm2 = pxor(mm2, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685f56 pxor mm2, qword ptr [0x6f0178]
    mm5 = pfmul(mm5, mm0);               // original00685f5d pfmul mm5, mm0
    mm4 = pfmul(mm4, mm1);               // original00685f61 pfmul mm4, mm1
    mm2 = pfadd(mm2, mm3);               // original00685f65 pfadd mm2, mm3
    mm3 = pair(frame + 112u);            // original00685f69 movq mm3, qword ptr [esp + 0x70]
    mm4 = pfsub(mm4, mm5);               // original00685f6e pfsub mm4, mm5
    mm5 = pair(frame + 120u);            // original00685f72 movq mm5, qword ptr [esp + 0x78]
    mm7 = pfmul(mm7, mm1);               // original00685f77 pfmul mm7, mm1
    mm6 = pxor(mm6, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685f7b pxor mm6, qword ptr [0x6f0178]
    mm4 = pfacc(mm4, mm2);               // original00685f82 pfacc mm4, mm2
    mm6 = pfmul(mm6, mm0);               // original00685f86 pfmul mm6, mm0
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685f8a pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original00685f91 pfmul mm3, mm0
    store(eax, mm4);                     // original00685f95 movq qword ptr [eax], mm4
    mm5 = pfmul(mm5, mm1);               // original00685f98 pfmul mm5, mm1
    mm6 = pfadd(mm6, mm7);               // original00685f9c pfadd mm6, mm7
    mm5 = pfsub(mm5, mm3);               // original00685fa0 pfsub mm5, mm3
    mm6 = pfacc(mm6, mm5);               // original00685fa4 pfacc mm6, mm5
    store(eax + 0x8u, mm6);              // original00685fa8 movq qword ptr [eax + 8], mm6
    mm0 = pair(frame + 32u);             // original00685fac movq mm0, qword ptr [esp + 0x20]
    mm1 = mm0;                           // original00685fb1 movq mm1, mm0
    mm2 = pair(frame + 40u);             // original00685fb4 movq mm2, qword ptr [esp + 0x28]
    mm3 = mm2;                           // original00685fb9 movq mm3, mm2
    mm0 = pfmul(mm0, mm0);               // original00685fbc pfmul mm0, mm0
    mm2 = pfmul(mm2, mm2);               // original00685fc0 pfmul mm2, mm2
    mm0 = pfadd(mm0, mm2);               // original00685fc4 pfadd mm0, mm2
    mm0 = pfacc(mm0, mm0);               // original00685fc8 pfacc mm0, mm0
    mm5 = mm0;                           // original00685fcc movq mm5, mm0
    mm4 = reciprocal(mm0);               // original00685fcf pfrcp mm4, mm0
    mm5 = pfcmpgt(mm5, pair(reinterpret_cast<u32>(
                           dat_006f01d0))); // original00685fd3 pfcmpgt mm5, qword ptr [0x6f01d0]
    mm1 = pxor(mm1, pair(reinterpret_cast<u32>(
                        dat_006f0230))); // original00685fdb pxor mm1, qword ptr [0x6f0230]
    mm3 = pxor(mm3, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00685fe2 pxor mm3, qword ptr [0x6f0178]
    mm0 = pfrcpit1(mm0, mm4);            // original00685fe9 pfrcpit1 mm0, mm4
    mm1 = pand(mm1, mm5);                // original00685fed pand mm1, mm5
    mm3 = pand(mm3, mm5);                // original00685ff0 pand mm3, mm5
    mm0 = pfrcpit2(mm0, mm4);            // original00685ff3 pfrcpit2 mm0, mm4
    mm1 = pfmul(mm1, mm0);               // original00685ff7 pfmul mm1, mm0
    mm3 = pfmul(mm3, mm0);               // original00685ffb pfmul mm3, mm0
    store(frame + 64u, mm1);             // original00685fff movq qword ptr [esp + 0x40], mm1
    store(frame + 72u, mm3);             // original00686004 movq qword ptr [esp + 0x48], mm3
    mm2 = pair(frame + 16u);             // original00686009 movq mm2, qword ptr [esp + 0x10]
    mm3 = pair(frame + 24u);             // original0068600e movq mm3, qword ptr [esp + 0x18]
    mm4 = mm2;                           // original00686013 movq mm4, mm2
    mm5 = mm3;                           // original00686016 movq mm5, mm3
    mm0 = pair(frame + 64u);             // original00686019 movq mm0, qword ptr [esp + 0x40]
    mm4 = punpckhdq(mm4, mm2);           // original0068601e punpckhdq mm4, mm2
    mm5 = punpckhdq(mm5, mm3);           // original00686021 punpckhdq mm5, mm3
    mm1 = pair(frame + 72u);             // original00686024 movq mm1, qword ptr [esp + 0x48]
    mm4 = punpckldq(mm4, mm2);           // original00686029 punpckldq mm4, mm2
    mm5 = punpckldq(mm5, mm3);           // original0068602c punpckldq mm5, mm3
    mm6 = mm4;                           // original0068602f movq mm6, mm4
    mm7 = mm5;                           // original00686032 movq mm7, mm5
    mm2 = pfmul(mm2, mm1);               // original00686035 pfmul mm2, mm1
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00686039 pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original00686040 pfmul mm3, mm0
    mm2 = pxor(mm2, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00686044 pxor mm2, qword ptr [0x6f0178]
    mm5 = pfmul(mm5, mm0);               // original0068604b pfmul mm5, mm0
    mm4 = pfmul(mm4, mm1);               // original0068604f pfmul mm4, mm1
    mm2 = pfadd(mm2, mm3);               // original00686053 pfadd mm2, mm3
    mm3 = pair(frame + 16u);             // original00686057 movq mm3, qword ptr [esp + 0x10]
    mm4 = pfsub(mm4, mm5);               // original0068605c pfsub mm4, mm5
    mm5 = pair(frame + 24u);             // original00686060 movq mm5, qword ptr [esp + 0x18]
    mm7 = pfmul(mm7, mm1);               // original00686065 pfmul mm7, mm1
    mm6 = pxor(mm6, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00686069 pxor mm6, qword ptr [0x6f0178]
    mm4 = pfacc(mm4, mm2);               // original00686070 pfacc mm4, mm2
    mm6 = pfmul(mm6, mm0);               // original00686074 pfmul mm6, mm0
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00686078 pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original0068607f pfmul mm3, mm0
    store(frame + 128u, mm4);            // original00686083 movq qword ptr [esp + 0x80], mm4
    mm5 = pfmul(mm5, mm1);               // original0068608b pfmul mm5, mm1
    mm6 = pfadd(mm6, mm7);               // original0068608f pfadd mm6, mm7
    mm5 = pfsub(mm5, mm3);               // original00686093 pfsub mm5, mm3
    mm6 = pfacc(mm6, mm5);               // original00686097 pfacc mm6, mm5
    store(frame + 136u, mm6);            // original0068609b movq qword ptr [esp + 0x88], mm6
    mm2 = pair(frame + 48u);             // original006860a3 movq mm2, qword ptr [esp + 0x30]
    mm3 = pair(frame + 56u);             // original006860a8 movq mm3, qword ptr [esp + 0x38]
    mm4 = mm2;                           // original006860ad movq mm4, mm2
    mm5 = mm3;                           // original006860b0 movq mm5, mm3
    mm0 = pair(frame + 64u);             // original006860b3 movq mm0, qword ptr [esp + 0x40]
    mm4 = punpckhdq(mm4, mm2);           // original006860b8 punpckhdq mm4, mm2
    mm5 = punpckhdq(mm5, mm3);           // original006860bb punpckhdq mm5, mm3
    mm1 = pair(frame + 72u);             // original006860be movq mm1, qword ptr [esp + 0x48]
    mm4 = punpckldq(mm4, mm2);           // original006860c3 punpckldq mm4, mm2
    mm5 = punpckldq(mm5, mm3);           // original006860c6 punpckldq mm5, mm3
    mm6 = mm4;                           // original006860c9 movq mm6, mm4
    mm7 = mm5;                           // original006860cc movq mm7, mm5
    mm2 = pfmul(mm2, mm1);               // original006860cf pfmul mm2, mm1
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original006860d3 pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original006860da pfmul mm3, mm0
    mm2 = pxor(mm2, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original006860de pxor mm2, qword ptr [0x6f0178]
    mm5 = pfmul(mm5, mm0);               // original006860e5 pfmul mm5, mm0
    mm4 = pfmul(mm4, mm1);               // original006860e9 pfmul mm4, mm1
    mm2 = pfadd(mm2, mm3);               // original006860ed pfadd mm2, mm3
    mm3 = pair(frame + 48u);             // original006860f1 movq mm3, qword ptr [esp + 0x30]
    mm4 = pfsub(mm4, mm5);               // original006860f6 pfsub mm4, mm5
    mm5 = pair(frame + 56u);             // original006860fa movq mm5, qword ptr [esp + 0x38]
    mm7 = pfmul(mm7, mm1);               // original006860ff pfmul mm7, mm1
    mm6 = pxor(mm6, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00686103 pxor mm6, qword ptr [0x6f0178]
    mm4 = pfacc(mm4, mm2);               // original0068610a pfacc mm4, mm2
    mm6 = pfmul(mm6, mm0);               // original0068610e pfmul mm6, mm0
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original00686112 pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original00686119 pfmul mm3, mm0
    store(frame + 144u, mm4);            // original0068611d movq qword ptr [esp + 0x90], mm4
    mm5 = pfmul(mm5, mm1);               // original00686125 pfmul mm5, mm1
    mm6 = pfadd(mm6, mm7);               // original00686129 pfadd mm6, mm7
    mm5 = pfsub(mm5, mm3);               // original0068612d pfsub mm5, mm3
    mm6 = pfacc(mm6, mm5);               // original00686131 pfacc mm6, mm5
    store(frame + 152u, mm6);            // original00686135 movq qword ptr [esp + 0x98], mm6
    // Adapter already reserves this original temporary12B; its actual words remain explicit. // original0068613d sub esp, 0xc
    mm1 = pair(frame + 128u);  // original00686140 movq mm1, qword ptr [esp + 0x8c]
    mm2 = pair(frame + 136u);  // original00686148 movq mm2, qword ptr [esp + 0x94]
    mm3 = mm2;                 // original00686150 movq mm3, mm2
    mm3 = punpckhdq(mm3, mm3); // original00686153 punpckhdq mm3, mm3
    mm0 = mm3;                 // original00686156 movq mm0, mm3
    mm3 = pfcmpge(mm3, pair(reinterpret_cast<u32>(
                           dat_006f01e8))); // original00686159 pfcmpge mm3, qword ptr [0x6f01e8]
    ecx = low(mm3);                         // original00686161 movd ecx, mm3
    zero = ((ecx & ecx) == 0);              // original00686164 test ecx, ecx
    if (!zero)
        goto L_006861ce;            // original00686166 jne 0x6861ce
    mm0 = call_acos(mm0);           // original00686168 call 0x6a6940
    store_single(frame - 12u, mm0); // original0068616d movd dword ptr [esp], mm0
    put(frame - 8u, esi);           // original00686171 mov dword ptr [esp + 4], esi
    put(frame - 4u, ebx);           // original00686175 mov dword ptr [esp + 8], ebx
    mm0 = call_sine(mm0);           // original00686179 call 0x6a7020
    mm3 = mm0;                      // original0068617e movq mm3, mm0
    esi = word(
        reinterpret_cast<const u32*>(frame - 8u)); // original00686181 mov esi, dword ptr [esp + 4]
    mm3 = pand(mm3, pair(reinterpret_cast<u32>(
                        dat_006f01a0))); // original00686185 pand mm3, qword ptr [0x6f01a0]
    ebx = word(
        reinterpret_cast<const u32*>(frame - 4u)); // original0068618c mov ebx, dword ptr [esp + 8]
    mm3 = pfcmpge(mm3, pair(reinterpret_cast<u32>(
                           dat_006f01a8))); // original00686190 pfcmpge mm3, qword ptr [0x6f01a8]
    ecx = low(mm3);                         // original00686198 movd ecx, mm3
    mm1 = pair(frame + 128u);               // original0068619b movq mm1, qword ptr [esp + 0x8c]
    mm2 = pair(frame + 136u);               // original006861a3 movq mm2, qword ptr [esp + 0x94]
    zero = ((ecx & ecx) == 0);              // original006861ab test ecx, ecx
    if (zero)
        goto L_006861ce;       // original006861ad je 0x6861ce
    mm3 = single(frame - 12u); // original006861af movd mm3, dword ptr [esp]
    mm4 = reciprocal(mm0);     // original006861b3 pfrcp mm4, mm0
    mm3 = punpckldq(mm3, mm3); // original006861b7 punpckldq mm3, mm3
    mm0 = pfrcpit1(mm0, mm4);  // original006861ba pfrcpit1 mm0, mm4
    mm0 = pfrcpit2(mm0, mm4);  // original006861be pfrcpit2 mm0, mm4
    mm3 = pfmul(mm3, mm0);     // original006861c2 pfmul mm3, mm0
    mm1 = pfmul(mm1, mm3);     // original006861c6 pfmul mm1, mm3
    mm2 = pfmul(mm2, mm3);     // original006861ca pfmul mm2, mm3
L_006861ce:;
    mm2 = pand(mm2, pair(reinterpret_cast<u32>(
                        dat_006f01b0))); // original006861ce pand mm2, qword ptr [0x6f01b0]
    store(frame + 80u, mm1);             // original006861d5 movq qword ptr [esp + 0x5c], mm1
    store(frame + 88u, mm2);             // original006861da movq qword ptr [esp + 0x64], mm2
    // Adapter already reserves this original temporary12B; its actual words remain explicit. // original006861df add esp, 0xc
    // Adapter already reserves this original temporary12B; its actual words remain explicit. // original006861e2 sub esp, 0xc
    mm1 = pair(frame + 144u);  // original006861e5 movq mm1, qword ptr [esp + 0x9c]
    mm2 = pair(frame + 152u);  // original006861ed movq mm2, qword ptr [esp + 0xa4]
    mm3 = mm2;                 // original006861f5 movq mm3, mm2
    mm3 = punpckhdq(mm3, mm3); // original006861f8 punpckhdq mm3, mm3
    mm0 = mm3;                 // original006861fb movq mm0, mm3
    mm3 = pfcmpge(mm3, pair(reinterpret_cast<u32>(
                           dat_006f01e8))); // original006861fe pfcmpge mm3, qword ptr [0x6f01e8]
    ecx = low(mm3);                         // original00686206 movd ecx, mm3
    zero = ((ecx & ecx) == 0);              // original00686209 test ecx, ecx
    if (!zero)
        goto L_00686273;            // original0068620b jne 0x686273
    mm0 = call_acos(mm0);           // original0068620d call 0x6a6940
    store_single(frame - 12u, mm0); // original00686212 movd dword ptr [esp], mm0
    put(frame - 8u, esi);           // original00686216 mov dword ptr [esp + 4], esi
    put(frame - 4u, ebx);           // original0068621a mov dword ptr [esp + 8], ebx
    mm0 = call_sine(mm0);           // original0068621e call 0x6a7020
    mm3 = mm0;                      // original00686223 movq mm3, mm0
    esi = word(
        reinterpret_cast<const u32*>(frame - 8u)); // original00686226 mov esi, dword ptr [esp + 4]
    mm3 = pand(mm3, pair(reinterpret_cast<u32>(
                        dat_006f01a0))); // original0068622a pand mm3, qword ptr [0x6f01a0]
    ebx = word(
        reinterpret_cast<const u32*>(frame - 4u)); // original00686231 mov ebx, dword ptr [esp + 8]
    mm3 = pfcmpge(mm3, pair(reinterpret_cast<u32>(
                           dat_006f01a8))); // original00686235 pfcmpge mm3, qword ptr [0x6f01a8]
    ecx = low(mm3);                         // original0068623d movd ecx, mm3
    mm1 = pair(frame + 144u);               // original00686240 movq mm1, qword ptr [esp + 0x9c]
    mm2 = pair(frame + 152u);               // original00686248 movq mm2, qword ptr [esp + 0xa4]
    zero = ((ecx & ecx) == 0);              // original00686250 test ecx, ecx
    if (zero)
        goto L_00686273;       // original00686252 je 0x686273
    mm3 = single(frame - 12u); // original00686254 movd mm3, dword ptr [esp]
    mm4 = reciprocal(mm0);     // original00686258 pfrcp mm4, mm0
    mm3 = punpckldq(mm3, mm3); // original0068625c punpckldq mm3, mm3
    mm0 = pfrcpit1(mm0, mm4);  // original0068625f pfrcpit1 mm0, mm4
    mm0 = pfrcpit2(mm0, mm4);  // original00686263 pfrcpit2 mm0, mm4
    mm3 = pfmul(mm3, mm0);     // original00686267 pfmul mm3, mm0
    mm1 = pfmul(mm1, mm3);     // original0068626b pfmul mm1, mm3
    mm2 = pfmul(mm2, mm3);     // original0068626f pfmul mm2, mm3
L_00686273:;
    mm2 = pand(mm2, pair(reinterpret_cast<u32>(
                        dat_006f01b0))); // original00686273 pand mm2, qword ptr [0x6f01b0]
    store(frame + 96u, mm1);             // original0068627a movq qword ptr [esp + 0x6c], mm1
    store(frame + 104u, mm2);            // original0068627f movq qword ptr [esp + 0x74], mm2
    // Adapter already reserves this original temporary12B; its actual words remain explicit. // original00686284 add esp, 0xc
    mm0 = pair(frame + 80u);              // original00686287 movq mm0, qword ptr [esp + 0x50]
    mm1 = pair(frame + 88u);              // original0068628c movq mm1, qword ptr [esp + 0x58]
    mm0 = pfadd(mm0, pair(frame + 96u));  // original00686291 pfadd mm0, qword ptr [esp + 0x60]
    mm1 = pfadd(mm1, pair(frame + 104u)); // original00686297 pfadd mm1, qword ptr [esp + 0x68]
    mm0 = pfmul(mm0, pair(reinterpret_cast<u32>(
                         dat_006f39b0))); // original0068629d pfmul mm0, qword ptr [0x6f39b0]
    mm1 = pfmul(mm1, pair(reinterpret_cast<u32>(
                         dat_006f39b0))); // original006862a5 pfmul mm1, qword ptr [0x6f39b0]
    store(frame + 128u, mm0);             // original006862ad movq qword ptr [esp + 0x80], mm0
    store(frame + 136u, mm1);             // original006862b5 movq qword ptr [esp + 0x88], mm1
    // Adapter already reserves this original temporary12B; its actual words remain explicit. // original006862bd sub esp, 0xc
    mm0 = pair(frame + 128u);       // original006862c0 movq mm0, qword ptr [esp + 0x8c]
    mm1 = single(frame + 136u);     // original006862c8 movd mm1, dword ptr [esp + 0x94]
    mm0 = pfmul(mm0, mm0);          // original006862d0 pfmul mm0, mm0
    mm1 = pfmul(mm1, mm1);          // original006862d4 pfmul mm1, mm1
    mm0 = pfadd(mm0, mm1);          // original006862d8 pfadd mm0, mm1
    mm0 = pfacc(mm0, mm0);          // original006862dc pfacc mm0, mm0
    mm1 = estimate(mm0);            // original006862e0 pfrsqrt mm1, mm0
    mm2 = mm1;                      // original006862e4 movq mm2, mm1
    mm1 = pfmul(mm1, mm1);          // original006862e7 pfmul mm1, mm1
    put(frame - 8u, esi);           // original006862eb mov dword ptr [esp + 4], esi
    mm1 = pfrsqit1(mm1, mm0);       // original006862ef pfrsqit1 mm1, mm0
    put(frame - 4u, ebx);           // original006862f3 mov dword ptr [esp + 8], ebx
    mm1 = pfrcpit2(mm1, mm2);       // original006862f7 pfrcpit2 mm1, mm2
    store_single(frame - 12u, mm1); // original006862fb movd dword ptr [esp], mm1
    mm0 = pfmul(mm0, mm1);          // original006862ff pfmul mm0, mm1
    mm0 = call_trig(mm0);           // original00686303 call 0x6a6f20
    mm1 = mm0;                      // original00686308 movq mm1, mm0
    mm0 = pand(mm0, pair(reinterpret_cast<u32>(
                        dat_006f0198))); // original0068630b pand mm0, qword ptr [0x6f0198]
    mm0 = pfcmpge(mm0, pair(reinterpret_cast<u32>(
                           dat_006f01a8))); // original00686312 pfcmpge mm0, qword ptr [0x6f01a8]
    mm0 = punpckhdq(mm0, mm0);              // original0068631a punpckhdq mm0, mm0
    ecx = low(mm0);                         // original0068631d movd ecx, mm0
    mm2 = pair(frame + 128u);               // original00686320 movq mm2, qword ptr [esp + 0x8c]
    mm0 = mm1;                              // original00686328 movq mm0, mm1
    mm1 = punpckhdq(mm1, mm1);              // original0068632b punpckhdq mm1, mm1
    zero = ((ecx & 0x1u) == 0);             // original0068632e test ecx, 1
    mm1 = pfmul(mm1, pair(frame - 12u));    // original00686334 pfmul mm1, qword ptr [esp]
    mm3 = single(frame + 136u);             // original00686339 movd mm3, dword ptr [esp + 0x94]
    if (zero)
        goto L_0068634e;       // original00686341 je 0x68634e
    mm1 = punpckldq(mm1, mm1); // original00686343 punpckldq mm1, mm1
    mm3 = pfmul(mm3, mm1);     // original00686346 pfmul mm3, mm1
    mm2 = pfmul(mm2, mm1);     // original0068634a pfmul mm2, mm1
L_0068634e:;
    mm3 = punpckldq(mm3, mm0); // original0068634e punpckldq mm3, mm0
    store(frame + 112u, mm2);  // original00686351 movq qword ptr [esp + 0x7c], mm2
    store(frame + 120u, mm3);  // original00686356 movq qword ptr [esp + 0x84], mm3
    esi = word(
        reinterpret_cast<const u32*>(frame - 8u)); // original0068635e mov esi, dword ptr [esp + 4]
    ebx = word(
        reinterpret_cast<const u32*>(frame - 4u)); // original00686362 mov ebx, dword ptr [esp + 8]
    // Adapter already reserves this original temporary12B; its actual words remain explicit. // original00686366 add esp, 0xc
    eax = word(reinterpret_cast<const u32*>(arguments +
                                            4u)); // original00686369 mov eax, dword ptr [ebp + 0xc]
    mm2 = pair(frame + 112u);  // original0068636c movq mm2, qword ptr [esp + 0x70]
    mm3 = pair(frame + 120u);  // original00686371 movq mm3, qword ptr [esp + 0x78]
    mm4 = mm2;                 // original00686376 movq mm4, mm2
    mm5 = mm3;                 // original00686379 movq mm5, mm3
    mm0 = pair(frame + 32u);   // original0068637c movq mm0, qword ptr [esp + 0x20]
    mm4 = punpckhdq(mm4, mm2); // original00686381 punpckhdq mm4, mm2
    mm5 = punpckhdq(mm5, mm3); // original00686384 punpckhdq mm5, mm3
    mm1 = pair(frame + 40u);   // original00686387 movq mm1, qword ptr [esp + 0x28]
    mm4 = punpckldq(mm4, mm2); // original0068638c punpckldq mm4, mm2
    mm5 = punpckldq(mm5, mm3); // original0068638f punpckldq mm5, mm3
    mm6 = mm4;                 // original00686392 movq mm6, mm4
    mm7 = mm5;                 // original00686395 movq mm7, mm5
    mm2 = pfmul(mm2, mm1);     // original00686398 pfmul mm2, mm1
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original0068639c pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original006863a3 pfmul mm3, mm0
    mm2 = pxor(mm2, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original006863a7 pxor mm2, qword ptr [0x6f0178]
    mm5 = pfmul(mm5, mm0);               // original006863ae pfmul mm5, mm0
    mm4 = pfmul(mm4, mm1);               // original006863b2 pfmul mm4, mm1
    mm2 = pfadd(mm2, mm3);               // original006863b6 pfadd mm2, mm3
    mm3 = pair(frame + 112u);            // original006863ba movq mm3, qword ptr [esp + 0x70]
    mm4 = pfsub(mm4, mm5);               // original006863bf pfsub mm4, mm5
    mm5 = pair(frame + 120u);            // original006863c3 movq mm5, qword ptr [esp + 0x78]
    mm7 = pfmul(mm7, mm1);               // original006863c8 pfmul mm7, mm1
    mm6 = pxor(mm6, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original006863cc pxor mm6, qword ptr [0x6f0178]
    mm4 = pfacc(mm4, mm2);               // original006863d3 pfacc mm4, mm2
    mm6 = pfmul(mm6, mm0);               // original006863d7 pfmul mm6, mm0
    mm5 = pxor(mm5, pair(reinterpret_cast<u32>(
                        dat_006f0178))); // original006863db pxor mm5, qword ptr [0x6f0178]
    mm3 = pfmul(mm3, mm0);               // original006863e2 pfmul mm3, mm0
    store(eax, mm4);                     // original006863e6 movq qword ptr [eax], mm4
    mm5 = pfmul(mm5, mm1);               // original006863e9 pfmul mm5, mm1
    mm6 = pfadd(mm6, mm7);               // original006863ed pfadd mm6, mm7
    mm5 = pfsub(mm5, mm3);               // original006863f1 pfsub mm5, mm3
    mm6 = pfacc(mm6, mm5);               // original006863f5 pfacc mm6, mm5
    store(eax + 0x8u, mm6);              // original006863f9 movq qword ptr [eax + 8], mm6
    eax = word(reinterpret_cast<const u32*>(
        arguments + 8u));    // original006863fd mov eax, dword ptr [ebp + 0x10]
    mm0 = pair(frame + 32u); // original00686400 movq mm0, qword ptr [esp + 0x20]
    mm1 = pair(frame + 40u); // original00686405 movq mm1, qword ptr [esp + 0x28]
    store(eax, mm0);         // original0068640a movq qword ptr [eax], mm0
    store(eax + 0x8u, mm1);  // original0068640d movq qword ptr [eax + 8], mm1
    // Original adapter-owned frame/save/alignment operation. // original00686411 mov esp, ebp
    // Original adapter-owned frame/save/alignment operation. // original00686413 pop ebp
    empty();    // original00686414 femms
    return eax; // original00686416 ret 0x1c
}
extern "C" __attribute__((naked, stdcall)) void*
FUN_006859de(void*, void*, void*, const void*, const void*, const void*, const void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $160,%esp\n\tandl $-8,%esp\n\tsubl $12,%esp\n\tleal 12(%esp),%edx\n\tleal 8(%ebp),%eax\n\tpushl %ebx\n\tpushl %esi\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_006859de\n\taddl $16,%esp\n\tmovl %ebp,%esp\n\tpopl %ebp\n\tretl $28");
}
