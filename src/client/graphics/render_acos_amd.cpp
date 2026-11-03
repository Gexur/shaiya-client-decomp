#include "graphics/render_acos_amd.h"
#include "graphics/render_amd_trig_rotation.h"
namespace {
using u32 = uint32_t;
using Packed = long long __attribute__((vector_size(8)));
struct B4 {
    unsigned char b[4];
};
struct B8 {
    unsigned char b[8];
};
#define AMD __attribute__((target("mmx"), always_inline)) inline
u32 word(const u32* p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
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
AMD Packed root(Packed p) {
    Packed v;
    __asm__ volatile("pfrsqrt %1,%0" : "=y"(v) : "y"(p));
    return v;
}
AMD Packed reciprocal(Packed p) {
    Packed v;
    __asm__ volatile("pfrcp %1,%0" : "=y"(v) : "y"(p));
    return v;
}
AMD Packed sign_shift(Packed p) {
    __asm__ volatile("pslld $31,%0" : "+y"(p));
    return p;
}
AMD void empty() {
    __asm__ volatile("femms" ::
                         : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st", "st(1)",
                           "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory");
}
AMD Packed pand(Packed a, Packed b) {
    __asm__ volatile("pand %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pandn(Packed a, Packed b) {
    __asm__ volatile("pandn %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed por(Packed a, Packed b) {
    __asm__ volatile("por %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pxor(Packed a, Packed b) {
    __asm__ volatile("pxor %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pcmpgtd(Packed a, Packed b) {
    __asm__ volatile("pcmpgtd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfmul(Packed a, Packed b) {
    __asm__ volatile("pfmul %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfadd(Packed a, Packed b) {
    __asm__ volatile("pfadd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfsubr(Packed a, Packed b) {
    __asm__ volatile("pfsubr %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfrsqit1(Packed a, Packed b) {
    __asm__ volatile("pfrsqit1 %1,%0" : "+y"(a) : "y"(b));
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
AMD Packed punpckhdq(Packed a, Packed b) {
    __asm__ volatile("punpckhdq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed inverse_trig(Packed input) {
    Packed output;
    __asm__ volatile("movq %1,%%mm0\n\tcalll _FUN_006a6940\n\tmovq %%mm0,%0"
                     : "=m"(output)
                     : "m"(input)
                     : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "cc", "memory");
    return output;
}
} // namespace

extern "C" alignas(8) const u32 dat_006f0168[2] = {0x40000000u, 0x40000000u};
extern "C" alignas(4) u32 dat_00717e18[1] = {0x80000000u};
extern "C" alignas(4) u32 dat_00717e28[1] = {0x3f800000u};
extern "C" alignas(4) u32 dat_00717e2c[1] = {0x3f000000u};
extern "C" alignas(4) u32 dat_00717e34[1] = {0x00000000u};
extern "C" alignas(4) u32 dat_00717e60[1] = {0x3f133333u};
extern "C" alignas(4) u32 dat_00717e64[1] = {0x3f6a4aa5u};
extern "C" alignas(4) u32 dat_00717e68[1] = {0xbf004c2cu};
extern "C" alignas(4) u32 dat_00717e6c[1] = {0x40afb829u};
extern "C" alignas(4) u32 dat_00717e70[1] = {0xc0af5123u};
extern "C" alignas(4) u32 dat_00717e74[1] = {0x3fc90fdbu};
extern "C" alignas(4) u32 dat_00717e78[1] = {0xbfc90fdbu};
// Complete original006a6940..006a6a37.
extern "C" __attribute__((target("mmx"))) void recovered_006a6940(u32 state) {
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    mm0 = pair(state);
    mm6 = single(
        reinterpret_cast<u32>(dat_00717e18)); // original006a6940 movd mm6, dword ptr [0x717e18]
    mm7 = single(
        reinterpret_cast<u32>(dat_00717e1c)); // original006a6947 movd mm7, dword ptr [0x717e1c]
    mm4 = single(
        reinterpret_cast<u32>(dat_00717e2c)); // original006a694e movd mm4, dword ptr [0x717e2c]
    mm6 = pand(mm6, mm0);                     // original006a6955 pand mm6, mm0
    mm5 = single(
        reinterpret_cast<u32>(dat_00717e28)); // original006a6958 movd mm5, dword ptr [0x717e28]
    mm0 = pand(mm0, mm7);                     // original006a695f pand mm0, mm7
    mm3 = mm0;                                // original006a6962 movq mm3, mm0
    mm3 = pcmpgtd(mm3, mm5);                  // original006a6965 pcmpgtd mm3, mm5
    mm5 = mm0;                                // original006a6968 movq mm5, mm0
    mm0 = pfmul(mm0, mm4);                    // original006a696b pfmul mm0, mm4
    mm2 = single(
        reinterpret_cast<u32>(dat_00717e60)); // original006a696f movd mm2, dword ptr [0x717e60]
    mm0 = pfsubr(mm0, mm4);                   // original006a6976 pfsubr mm0, mm4
    mm7 = root(mm0);                          // original006a697a pfrsqrt mm7, mm0
    mm1 = mm7;                                // original006a697e movq mm1, mm7
    mm7 = pfmul(mm7, mm7);                    // original006a6981 pfmul mm7, mm7
    mm2 = pcmpgtd(mm2, mm5);                  // original006a6985 pcmpgtd mm2, mm5
    mm7 = pfrsqit1(mm7, mm0);                 // original006a6988 pfrsqit1 mm7, mm0
    mm4 = single(
        reinterpret_cast<u32>(dat_00717e70)); // original006a698c movd mm4, dword ptr [0x717e70]
    mm7 = pfrcpit2(mm7, mm1);                 // original006a6993 pfrcpit2 mm7, mm1
    mm7 = pfmul(mm7, mm0);                    // original006a6997 pfmul mm7, mm0
    mm0 = mm2;                                // original006a699b movq mm0, mm2
    mm5 = pand(mm5, mm2);                     // original006a699e pand mm5, mm2
    mm0 = pandn(mm0, mm7);                    // original006a69a1 pandn mm0, mm7
    mm7 = single(
        reinterpret_cast<u32>(dat_00717e68)); // original006a69a4 movd mm7, dword ptr [0x717e68]
    mm0 = por(mm0, mm5);                      // original006a69ab por mm0, mm5
    mm1 = mm0;                                // original006a69ae movq mm1, mm0
    mm0 = pfmul(mm0, mm0);                    // original006a69b1 pfmul mm0, mm0
    mm5 = single(
        reinterpret_cast<u32>(dat_00717e64)); // original006a69b5 movd mm5, dword ptr [0x717e64]
    mm7 = pfmul(mm7, mm0);                    // original006a69bc pfmul mm7, mm0
    mm4 = pfadd(mm4, mm0);                    // original006a69c0 pfadd mm4, mm0
    mm7 = pfadd(mm7, mm5);                    // original006a69c4 pfadd mm7, mm5
    mm5 = single(
        reinterpret_cast<u32>(dat_00717e6c)); // original006a69c8 movd mm5, dword ptr [0x717e6c]
    mm7 = pfmul(mm7, mm0);                    // original006a69cf pfmul mm7, mm0
    mm0 = pfmul(mm0, mm4);                    // original006a69d3 pfmul mm0, mm4
    mm0 = pfadd(mm0, mm5);                    // original006a69d7 pfadd mm0, mm5
    mm7 = pfmul(mm7, mm1);                    // original006a69db pfmul mm7, mm1
    mm4 = reciprocal(mm0);                    // original006a69df pfrcp mm4, mm0
    mm0 = pfrcpit1(mm0, mm4);                 // original006a69e3 pfrcpit1 mm0, mm4
    mm5 = single(
        reinterpret_cast<u32>(dat_00717e78)); // original006a69e7 movd mm5, dword ptr [0x717e78]
    mm0 = pfrcpit2(mm0, mm4);                 // original006a69ee pfrcpit2 mm0, mm4
    mm0 = pfmul(mm0, mm7);                    // original006a69f2 pfmul mm0, mm7
    mm4 = mm2;                                // original006a69f6 movq mm4, mm2
    mm2 = pandn(mm2, mm5);                    // original006a69f9 pandn mm2, mm5
    mm5 = single(
        reinterpret_cast<u32>(dat_00717e74)); // original006a69fc movd mm5, dword ptr [0x717e74]
    mm7 = mm4;                                // original006a6a03 movq mm7, mm4
    mm2 = pxor(mm2, mm6);                     // original006a6a06 pxor mm2, mm6
    mm1 = pfadd(mm1, mm0);                    // original006a6a09 pfadd mm1, mm0
    mm0 = single(
        reinterpret_cast<u32>(dat_00717e34)); // original006a6a0d movd mm0, dword ptr [0x717e34]
    mm2 = pfadd(mm2, mm5);                    // original006a6a14 pfadd mm2, mm5
    mm7 = sign_shift(mm7);                    // original006a6a18 pslld mm7, 0x1f
    mm4 = pandn(mm4, mm1);                    // original006a6a1c pandn mm4, mm1
    mm7 = pxor(mm7, mm6);                     // original006a6a1f pxor mm7, mm6
    mm1 = pfadd(mm1, mm4);                    // original006a6a22 pfadd mm1, mm4
    mm0 = pand(mm0, mm3);                     // original006a6a26 pand mm0, mm3
    mm1 = por(mm1, mm7);                      // original006a6a29 por mm1, mm7
    mm2 = pfadd(mm2, mm1);                    // original006a6a2c pfadd mm2, mm1
    mm3 = pandn(mm3, mm2);                    // original006a6a30 pandn mm3, mm2
    mm0 = por(mm0, mm3);                      // original006a6a33 por mm0, mm3
    store(state, mm0);
    return; // original006a6a36 ret
}
extern "C" __attribute__((naked)) void FUN_006a6940() {
    // Original helper modifies only packed registers; preserve allGPRs/EFLAGS.
    __asm__ volatile(
        "pushfl\n\tsubl $8,%esp\n\tmovq %mm0,(%esp)\n\tpushal\n\tleal 32(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_006a6940\n\taddl $4,%esp\n\tpopal\n\tmovq (%esp),%mm0\n\taddl $8,%esp\n\tpopfl\n\tretl");
}
// Complete original006a6a40..006a6b22.
extern "C" __attribute__((target("mmx"))) void recovered_006a6a40(u32 state) {
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    mm0 = pair(state);
    mm6 = single(
        reinterpret_cast<u32>(dat_00717e18)); // original006a6a40 movd mm6, dword ptr [0x717e18]
    mm7 = single(
        reinterpret_cast<u32>(dat_00717e1c)); // original006a6a47 movd mm7, dword ptr [0x717e1c]
    mm4 = single(
        reinterpret_cast<u32>(dat_00717e2c)); // original006a6a4e movd mm4, dword ptr [0x717e2c]
    mm6 = pand(mm6, mm0);                     // original006a6a55 pand mm6, mm0
    mm5 = single(
        reinterpret_cast<u32>(dat_00717e28)); // original006a6a58 movd mm5, dword ptr [0x717e28]
    mm0 = pand(mm0, mm7);                     // original006a6a5f pand mm0, mm7
    mm3 = mm0;                                // original006a6a62 movq mm3, mm0
    mm3 = pcmpgtd(mm3, mm5);                  // original006a6a65 pcmpgtd mm3, mm5
    mm5 = mm0;                                // original006a6a68 movq mm5, mm0
    mm0 = pfmul(mm0, mm4);                    // original006a6a6b pfmul mm0, mm4
    mm2 = single(
        reinterpret_cast<u32>(dat_00717e60)); // original006a6a6f movd mm2, dword ptr [0x717e60]
    mm0 = pfsubr(mm0, mm4);                   // original006a6a76 pfsubr mm0, mm4
    mm7 = root(mm0);                          // original006a6a7a pfrsqrt mm7, mm0
    mm1 = mm7;                                // original006a6a7e movq mm1, mm7
    mm7 = pfmul(mm7, mm7);                    // original006a6a81 pfmul mm7, mm7
    mm2 = pcmpgtd(mm2, mm5);                  // original006a6a85 pcmpgtd mm2, mm5
    mm7 = pfrsqit1(mm7, mm0);                 // original006a6a88 pfrsqit1 mm7, mm0
    mm4 = single(
        reinterpret_cast<u32>(dat_00717e70)); // original006a6a8c movd mm4, dword ptr [0x717e70]
    mm7 = pfrcpit2(mm7, mm1);                 // original006a6a93 pfrcpit2 mm7, mm1
    mm7 = pfmul(mm7, mm0);                    // original006a6a97 pfmul mm7, mm0
    mm0 = mm2;                                // original006a6a9b movq mm0, mm2
    mm5 = pand(mm5, mm2);                     // original006a6a9e pand mm5, mm2
    mm0 = pandn(mm0, mm7);                    // original006a6aa1 pandn mm0, mm7
    mm7 = single(
        reinterpret_cast<u32>(dat_00717e68)); // original006a6aa4 movd mm7, dword ptr [0x717e68]
    mm0 = por(mm0, mm5);                      // original006a6aab por mm0, mm5
    mm1 = mm0;                                // original006a6aae movq mm1, mm0
    mm0 = pfmul(mm0, mm0);                    // original006a6ab1 pfmul mm0, mm0
    mm5 = single(
        reinterpret_cast<u32>(dat_00717e64)); // original006a6ab5 movd mm5, dword ptr [0x717e64]
    mm7 = pfmul(mm7, mm0);                    // original006a6abc pfmul mm7, mm0
    mm4 = pfadd(mm4, mm0);                    // original006a6ac0 pfadd mm4, mm0
    mm7 = pfadd(mm7, mm5);                    // original006a6ac4 pfadd mm7, mm5
    mm5 = single(
        reinterpret_cast<u32>(dat_00717e6c)); // original006a6ac8 movd mm5, dword ptr [0x717e6c]
    mm7 = pfmul(mm7, mm0);                    // original006a6acf pfmul mm7, mm0
    mm0 = pfmul(mm0, mm4);                    // original006a6ad3 pfmul mm0, mm4
    mm0 = pfadd(mm0, mm5);                    // original006a6ad7 pfadd mm0, mm5
    mm7 = pfmul(mm7, mm1);                    // original006a6adb pfmul mm7, mm1
    mm4 = reciprocal(mm0);                    // original006a6adf pfrcp mm4, mm0
    mm0 = pfrcpit1(mm0, mm4);                 // original006a6ae3 pfrcpit1 mm0, mm4
    mm0 = pfrcpit2(mm0, mm4);                 // original006a6ae7 pfrcpit2 mm0, mm4
    mm4 = single(
        reinterpret_cast<u32>(dat_00717e74)); // original006a6aeb movd mm4, dword ptr [0x717e74]
    mm7 = pfmul(mm7, mm0);                    // original006a6af2 pfmul mm7, mm0
    mm0 = single(
        reinterpret_cast<u32>(dat_00717e34)); // original006a6af6 movd mm0, dword ptr [0x717e34]
    mm1 = pfadd(mm1, mm7);                    // original006a6afd pfadd mm1, mm7
    mm5 = mm1;                                // original006a6b01 movq mm5, mm1
    mm1 = pfadd(mm1, mm1);                    // original006a6b04 pfadd mm1, mm1
    mm1 = pfsubr(mm1, mm4);                   // original006a6b08 pfsubr mm1, mm4
    mm5 = pand(mm5, mm2);                     // original006a6b0c pand mm5, mm2
    mm2 = pandn(mm2, mm1);                    // original006a6b0f pandn mm2, mm1
    mm0 = pand(mm0, mm3);                     // original006a6b12 pand mm0, mm3
    mm2 = por(mm2, mm5);                      // original006a6b15 por mm2, mm5
    mm2 = por(mm2, mm6);                      // original006a6b18 por mm2, mm6
    mm3 = pandn(mm3, mm2);                    // original006a6b1b pandn mm3, mm2
    mm0 = por(mm0, mm3);                      // original006a6b1e por mm0, mm3
    store(state, mm0);
    return; // original006a6b21 ret
}
extern "C" __attribute__((naked)) void FUN_006a6a40() {
    // Original helper modifies only packed registers; preserve allGPRs/EFLAGS.
    __asm__ volatile(
        "pushfl\n\tsubl $8,%esp\n\tmovq %mm0,(%esp)\n\tpushal\n\tleal 32(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_006a6a40\n\taddl $4,%esp\n\tpopal\n\tmovq (%esp),%mm0\n\taddl $8,%esp\n\tpopfl\n\tretl");
}
// Complete original00685032..00685076.
extern "C" __attribute__((target("mmx"))) void recovered_00685032(const u32* arguments, u32 state) {
    [[maybe_unused]] Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    u32 ecx, edx;
    bool axis, angle;
    // Original8-byte private reservation; private stack identity excluded. // original00685032 sub esp, 8
    ecx = word(arguments + 0); // original00685035 mov ecx, dword ptr [esp + 0xc]
    edx = word(arguments + 1); // original00685039 mov edx, dword ptr [esp + 0x10]
    mm5 = pair(ecx);           // original0068503d movq mm5, qword ptr [ecx]
    mm0 = pair(ecx + 0x8u);    // original00685040 movq mm0, qword ptr [ecx + 8]
    axis = (edx != 0);         // original00685044 test edx, edx
    ecx = word(arguments + 2); // original00685046 mov ecx, dword ptr [esp + 0x14]
    if (!axis)
        goto L_00685053;           // original0068504a je 0x685053
    store(edx, mm5);               // original0068504c movq qword ptr [edx], mm5
    store_single(edx + 0x8u, mm0); // original0068504f movd dword ptr [edx + 8], mm0
L_00685053:;
    angle = (ecx != 0);        // original00685053 test ecx, ecx
    mm0 = punpckhdq(mm0, mm0); // original00685055 punpckhdq mm0, mm0
    if (!angle)
        goto L_0068506e;       // original00685058 je 0x68506e
    mm0 = inverse_trig(mm0);   // original0068505a call 0x6a6940
    ecx = word(arguments + 2); // original0068505f mov ecx, dword ptr [esp + 0x14]
    mm0 = pfmul(mm0, pair(reinterpret_cast<u32>(
                         dat_006f0168))); // original00685063 pfmul mm0, qword ptr [0x6f0168]
    store_single(ecx, mm0);               // original0068506b movd dword ptr [ecx], mm0
L_0068506e:;
    // Original8-byte private reservation; private stack identity excluded. // original0068506e add esp, 8
    empty(); // original00685071 femms
    put(state + 4, ecx);
    put(state + 8, edx);
    return; // original00685073 ret 0xc
}
extern "C" __attribute__((naked, stdcall)) void FUN_00685032(const void*, void*, void*) {
    // Preserve physical incomingEAX and the actual finalECX/EDX residues.
    __asm__ volatile(
        "subl $16,%esp\n\tmovl %eax,(%esp)\n\tleal 20(%esp),%edx\n\tpushl %esp\n\tpushl %edx\n\tcalll _recovered_00685032\n\taddl $8,%esp\n\tmovl (%esp),%eax\n\tmovl 4(%esp),%ecx\n\tmovl 8(%esp),%edx\n\taddl $16,%esp\n\tretl $12");
}
