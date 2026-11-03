#include "graphics/render_float16_packed_amd.h"
#include "graphics/render_float16.h"
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
template <int N> AMD Packed pslld(Packed p) {
    __asm__ volatile("pslld %1,%0" : "+y"(p) : "i"(N));
    return p;
}
template <int N> AMD Packed psrld(Packed p) {
    __asm__ volatile("psrld %1,%0" : "+y"(p) : "i"(N));
    return p;
}
AMD void empty() {
    __asm__ volatile("femms" ::
                         : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st", "st(1)",
                           "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory");
}
AMD Packed punpcklwd(Packed a, Packed b) {
    __asm__ volatile("punpcklwd %1,%0" : "+y"(a) : "y"(b));
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
AMD Packed pcmpeqd(Packed a, Packed b) {
    __asm__ volatile("pcmpeqd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed paddd(Packed a, Packed b) {
    __asm__ volatile("paddd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfsub(Packed a, Packed b) {
    __asm__ volatile("pfsub %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed por(Packed a, Packed b) {
    __asm__ volatile("por %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed packssdw(Packed a, Packed b) {
    __asm__ volatile("packssdw %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfcmpge(Packed a, Packed b) {
    __asm__ volatile("pfcmpge %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfadd(Packed a, Packed b) {
    __asm__ volatile("pfadd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed psubd(Packed a, Packed b) {
    __asm__ volatile("psubd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pfcmpgt(Packed a, Packed b) {
    __asm__ volatile("pfcmpgt %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD Packed pandn(Packed a, Packed b) {
    __asm__ volatile("pandn %1,%0" : "+y"(a) : "y"(b));
    return a;
}
} // namespace
extern "C" alignas(8) uint32_t dat_00717980[2] = {0x00007c00u, 0x00007c00u};
extern "C" alignas(8) uint32_t dat_00717990[2] = {0x0001c000u, 0x0001c000u};
extern "C" alignas(8) uint32_t dat_007179a0[2] = {0x00008000u, 0x00008000u};
extern "C" alignas(8) uint32_t dat_007179b0[2] = {0x00000400u, 0x00000400u};
extern "C" alignas(8) uint32_t dat_007179c0[2] = {0x38800000u, 0x38800000u};
extern "C" alignas(8) uint32_t dat_007179d0[2] = {0x477fefffu, 0x477fefffu};
extern "C" alignas(8) uint32_t dat_007179e0[2] = {0x38800000u, 0x38800000u};
extern "C" alignas(8) uint32_t dat_007179f0[2] = {0x80000000u, 0x80000000u};
extern "C" alignas(8) uint32_t dat_00717a10[2] = {0x00000001u, 0x00000001u};
extern "C" alignas(8) uint32_t dat_00717a20[2] = {0xc8000fffu, 0xc8000fffu};
extern "C" alignas(8) uint32_t dat_00717a40[2] = {0x7fffffffu, 0x7fffffffu};
extern "C" alignas(8) uint32_t dat_00717a50[2] = {0x00800000u, 0x00800000u};
extern "C" alignas(8) uint32_t dat_00717a60[2] = {0x00007fffu, 0x00007fffu};

// Complete original0068ad80..0068aeaa; alignment padding excluded.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068ad80(u32 arguments) {
    u32 eax, ecx, edx, esi, edi;
    bool less = false, zero = false;
    Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068ad80 sub esp, 0xc
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068ad83 mov dword ptr [esp], ebp
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068ad86 mov dword ptr [esp + 4], esi
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068ad8a mov dword ptr [esp + 8], edi
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068ad8e mov ebp, esp
    ecx = word(arguments + 8u); // original0068ad90 mov ecx, dword ptr [ebp + 0x18]
    eax = word(arguments + 0u); // original0068ad93 mov eax, dword ptr [ebp + 0x10]
    edx = word(arguments + 4u); // original0068ad96 mov edx, dword ptr [ebp + 0x14]
    less = (static_cast<int32_t>(ecx) < 4);
    zero = (ecx == 4u); // original0068ad99 cmp ecx, 4
    if (!less)
        goto L_0068adbf; // original0068ad9c jge 0x68adbf
    less = (static_cast<int32_t>(ecx) < 0);
    zero = (ecx == 0u); // original0068ad9e cmp ecx, 0
    if (zero)
        goto L_0068ae92; // original0068ada1 je 0x68ae92
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068ada7 sub esp, 0xc
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068adaa mov dword ptr [esp], eax
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068adad mov dword ptr [esp + 4], edx
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068adb1 mov dword ptr [esp + 8], ecx
    FUN_005e3cf1(reinterpret_cast<void*>(eax), reinterpret_cast<const void*>(edx),
                 ecx); // original0068adb5 call 0x5e3cf1
    goto L_0068ae92;   // original0068adba jmp 0x68ae92
L_0068adbf:;
    less = (static_cast<int32_t>(ecx) < 4);
    zero = (ecx == 4u); // original0068adbf cmp ecx, 4
    if (less)
        goto L_0068ae72;                        // original0068adc2 jl 0x68ae72
    mm0 = single(edx);                          // original0068adc8 movd mm0, dword ptr [edx]
    mm1 = single(edx + 0x4u);                   // original0068adcb movd mm1, dword ptr [edx + 4]
    __asm__ volatile("pxor %0,%0" : "=y"(mm6)); // original0068adcf pxor mm6, mm6
    mm7 = pair(
        reinterpret_cast<u32>(dat_00717980)); // original0068add2 movq mm7, qword ptr [0x717980]
    mm0 = punpcklwd(mm0, mm6);                // original0068add9 punpcklwd mm0, mm6
    mm1 = punpcklwd(mm1, mm6);                // original0068addc punpcklwd mm1, mm6
    mm2 = mm0;                                // original0068addf movq mm2, mm0
    mm3 = mm0;                                // original0068ade2 movq mm3, mm0
    mm4 = mm1;                                // original0068ade5 movq mm4, mm1
    mm5 = mm1;                                // original0068ade8 movq mm5, mm1
    mm0 = pand(mm0, mm7);                     // original0068adeb pand mm0, mm7
    mm1 = pand(mm1, mm7);                     // original0068adee pand mm1, mm7
    mm7 = pair(
        reinterpret_cast<u32>(dat_00717990)); // original0068adf1 movq mm7, qword ptr [0x717990]
    mm0 = pcmpeqd(mm0, mm6);                  // original0068adf8 pcmpeqd mm0, mm6
    mm1 = pcmpeqd(mm1, mm6);                  // original0068adfb pcmpeqd mm1, mm6
    mm6 = pair(
        reinterpret_cast<u32>(dat_007179a0)); // original0068adfe movq mm6, qword ptr [0x7179a0]
    mm2 = pand(mm2, mm6);                     // original0068ae05 pand mm2, mm6
    mm4 = pand(mm4, mm6);                     // original0068ae08 pand mm4, mm6
    mm3 = pxor(mm3, mm2);                     // original0068ae0b pxor mm3, mm2
    mm5 = pxor(mm5, mm4);                     // original0068ae0e pxor mm5, mm4
    mm3 = paddd(mm3, mm7);                    // original0068ae11 paddd mm3, mm7
    mm5 = paddd(mm5, mm7);                    // original0068ae14 paddd mm5, mm7
    mm6 = mm0;                                // original0068ae17 movq mm6, mm0
    mm7 = mm1;                                // original0068ae1a movq mm7, mm1
    mm0 = pand(mm0, pair(reinterpret_cast<u32>(
                        dat_007179b0))); // original0068ae1d pand mm0, qword ptr [0x7179b0]
    mm1 = pand(mm1, pair(reinterpret_cast<u32>(
                        dat_007179b0))); // original0068ae24 pand mm1, qword ptr [0x7179b0]
    mm3 = paddd(mm3, mm0);               // original0068ae2b paddd mm3, mm0
    mm5 = paddd(mm5, mm1);               // original0068ae2e paddd mm5, mm1
    mm6 = pand(mm6, pair(reinterpret_cast<u32>(
                        dat_007179c0))); // original0068ae31 pand mm6, qword ptr [0x7179c0]
    mm7 = pand(mm7, pair(reinterpret_cast<u32>(
                        dat_007179c0))); // original0068ae38 pand mm7, qword ptr [0x7179c0]
    mm2 = pslld<16>(mm2);                // original0068ae3f pslld mm2, 0x10
    mm4 = pslld<16>(mm4);                // original0068ae43 pslld mm4, 0x10
    mm3 = pslld<13>(mm3);                // original0068ae47 pslld mm3, 0xd
    mm5 = pslld<13>(mm5);                // original0068ae4b pslld mm5, 0xd
    mm3 = pfsub(mm3, mm6);               // original0068ae4f pfsub mm3, mm6
    mm5 = pfsub(mm5, mm7);               // original0068ae53 pfsub mm5, mm7
    mm3 = por(mm3, mm2);                 // original0068ae57 por mm3, mm2
    mm5 = por(mm5, mm4);                 // original0068ae5a por mm5, mm4
    store(eax, mm3);                     // original0068ae5d movq qword ptr [eax], mm3
    store(eax + 0x8u, mm5);              // original0068ae60 movq qword ptr [eax + 8], mm5
    eax += 16u;                          // original0068ae64 lea eax, [eax + 0x10]
    edx += 8u;                           // original0068ae67 lea edx, [edx + 8]
    ecx -= 4u;                           // original0068ae6a sub ecx, 4
    goto L_0068adbf;                     // original0068ae6d jmp 0x68adbf
L_0068ae72:;
    less = (static_cast<int32_t>(ecx) < 0);
    zero = (ecx == 0u); // original0068ae72 cmp ecx, 0
    if (zero)
        goto L_0068ae92; // original0068ae75 je 0x68ae92
    ecx -= 4u;           // original0068ae77 sub ecx, 4
    edi = ecx;           // original0068ae7a mov edi, ecx
    esi = ecx;           // original0068ae7c mov esi, ecx
    edi *= 4u;           // original0068ae7e imul edi, edi, 4
    esi *= 2u;           // original0068ae81 imul esi, esi, 2
    edx += esi;          // original0068ae84 add edx, esi
    eax += edi;          // original0068ae86 add eax, edi
    ecx = 4u;            // original0068ae88 mov ecx, 4
    goto L_0068adbf;     // original0068ae8d jmp 0x68adbf
L_0068ae92:;
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068ae92 mov esp, ebp
    eax = word(arguments + 0u); // original0068ae94 mov eax, dword ptr [ebp + 0x10]
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068ae97 mov ebp, dword ptr [esp]
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068ae9a mov esi, dword ptr [esp + 4]
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068ae9e mov edi, dword ptr [esp + 8]
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068aea2 add esp, 0xc
    empty();    // original0068aea5 femms
    return eax; // original0068aea7 ret 0xc
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068ad80(void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068ad80\n\taddl $4,%esp\n\tretl $12");
}

// Complete original0068aec0..0068b03b; alignment padding excluded.
extern "C" __attribute__((target("mmx"))) u32 recovered_0068aec0(u32 arguments) {
    u32 eax, ecx, edx, esi, edi;
    bool less = false, zero = false;
    Packed mm0, mm1, mm2, mm3, mm4, mm5, mm6, mm7;
    Packed saved_sign; // Written by an actual packed computation before its only use.
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068aec0 sub esp, 0x1c
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068aec3 mov dword ptr [esp + 0x10], ebp
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068aec7 mov dword ptr [esp + 0x14], esi
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068aecb mov dword ptr [esp + 0x18], edi
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068aecf mov ebp, esp
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068aed1 and esp, 0xfffffff8
    ecx = word(arguments + 8u); // original0068aed4 mov ecx, dword ptr [ebp + 0x28]
    eax = word(arguments + 0u); // original0068aed7 mov eax, dword ptr [ebp + 0x20]
    edx = word(arguments + 4u); // original0068aeda mov edx, dword ptr [ebp + 0x24]
    less = (static_cast<int32_t>(ecx) < 4);
    zero = (ecx == 4u); // original0068aedd cmp ecx, 4
    if (!less)
        goto L_0068af03; // original0068aee0 jge 0x68af03
    less = (static_cast<int32_t>(ecx) < 0);
    zero = (ecx == 0u); // original0068aee2 cmp ecx, 0
    if (zero)
        goto L_0068b022; // original0068aee5 je 0x68b022
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068aeeb sub esp, 0xc
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068aeee mov dword ptr [esp], eax
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068aef1 mov dword ptr [esp + 4], edx
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068aef5 mov dword ptr [esp + 8], ecx
    FUN_005e3c36(reinterpret_cast<void*>(eax), reinterpret_cast<const void*>(edx),
                 ecx); // original0068aef9 call 0x5e3c36
    goto L_0068b022;   // original0068aefe jmp 0x68b022
L_0068af03:;
    less = (static_cast<int32_t>(ecx) < 4);
    zero = (ecx == 4u); // original0068af03 cmp ecx, 4
    if (less)
        goto L_0068b002;    // original0068af06 jl 0x68b002
    mm0 = pair(edx);        // original0068af0c movq mm0, qword ptr [edx]
    mm1 = pair(edx + 0x8u); // original0068af0f movq mm1, qword ptr [edx + 8]
    mm6 = pair(
        reinterpret_cast<u32>(dat_007179f0)); // original0068af13 movq mm6, qword ptr [0x7179f0]
    mm7 = mm6;                                // original0068af1a movq mm7, mm6
    mm6 = pand(mm6, mm0);                     // original0068af1d pand mm6, mm0
    mm7 = pand(mm7, mm1);                     // original0068af20 pand mm7, mm1
    mm6 = psrld<18>(mm6);                     // original0068af23 psrld mm6, 0x12
    mm7 = psrld<18>(mm7);                     // original0068af27 psrld mm7, 0x12
    mm6 = packssdw(mm6, mm7);                 // original0068af2b packssdw mm6, mm7
    mm6 = pslld<2>(mm6);                      // original0068af2e pslld mm6, 2
    saved_sign = mm6;                         // original0068af32 movq qword ptr [esp], mm6
    mm2 = pair(
        reinterpret_cast<u32>(dat_00717a40)); // original0068af36 movq mm2, qword ptr [0x717a40]
    mm0 = pand(mm0, mm2);                     // original0068af3d pand mm0, mm2
    mm1 = pand(mm1, mm2);                     // original0068af40 pand mm1, mm2
    mm6 = mm0;                                // original0068af43 movq mm6, mm0
    mm7 = mm1;                                // original0068af46 movq mm7, mm1
    mm3 = pair(
        reinterpret_cast<u32>(dat_007179e0)); // original0068af49 movq mm3, qword ptr [0x7179e0]
    mm4 = mm3;                                // original0068af50 movq mm4, mm3
    mm5 = mm3;                                // original0068af53 movq mm5, mm3
    mm3 = pfcmpge(mm3, mm0);                  // original0068af56 pfcmpge mm3, mm0
    mm2 = mm3;                                // original0068af5a movq mm2, mm3
    mm3 = pand(mm3, mm4);                     // original0068af5d pand mm3, mm4
    mm0 = pfadd(mm0, mm3);                    // original0068af60 pfadd mm0, mm3
    mm2 = pand(mm2, pair(reinterpret_cast<u32>(
                        dat_00717a50))); // original0068af64 pand mm2, qword ptr [0x717a50]
    mm0 = psubd(mm0, mm2);               // original0068af6b psubd mm0, mm2
    mm5 = pfcmpge(mm5, mm1);             // original0068af6e pfcmpge mm5, mm1
    mm3 = mm5;                           // original0068af72 movq mm3, mm5
    mm5 = pand(mm5, mm4);                // original0068af75 pand mm5, mm4
    mm1 = pfadd(mm1, mm5);               // original0068af78 pfadd mm1, mm5
    mm3 = pand(mm3, pair(reinterpret_cast<u32>(
                        dat_00717a50))); // original0068af7c pand mm3, qword ptr [0x717a50]
    mm1 = psubd(mm1, mm3);               // original0068af83 psubd mm1, mm3
    mm2 = mm0;                           // original0068af86 movq mm2, mm0
    mm3 = mm1;                           // original0068af89 movq mm3, mm1
    mm0 = psrld<13>(mm0);                // original0068af8c psrld mm0, 0xd
    mm1 = psrld<13>(mm1);                // original0068af90 psrld mm1, 0xd
    mm4 = pair(
        reinterpret_cast<u32>(dat_00717a10)); // original0068af94 movq mm4, qword ptr [0x717a10]
    mm0 = pand(mm0, mm4);                     // original0068af9b pand mm0, mm4
    mm1 = pand(mm1, mm4);                     // original0068af9e pand mm1, mm4
    mm0 = paddd(mm0, mm2);                    // original0068afa1 paddd mm0, mm2
    mm1 = paddd(mm1, mm3);                    // original0068afa4 paddd mm1, mm3
    mm4 = pair(
        reinterpret_cast<u32>(dat_007179d0)); // original0068afa7 movq mm4, qword ptr [0x7179d0]
    mm5 = mm4;                                // original0068afae movq mm5, mm4
    mm4 = pfcmpgt(mm4, mm6);                  // original0068afb1 pfcmpgt mm4, mm6
    mm5 = pfcmpgt(mm5, mm7);                  // original0068afb5 pfcmpgt mm5, mm7
    mm6 = saved_sign;                         // original0068afb9 movq mm6, qword ptr [esp]
    mm2 = pair(
        reinterpret_cast<u32>(dat_00717a20)); // original0068afbd movq mm2, qword ptr [0x717a20]
    mm0 = paddd(mm0, mm2);                    // original0068afc4 paddd mm0, mm2
    mm1 = paddd(mm1, mm2);                    // original0068afc7 paddd mm1, mm2
    mm3 = pair(
        reinterpret_cast<u32>(dat_00717a60)); // original0068afca movq mm3, qword ptr [0x717a60]
    mm0 = psrld<13>(mm0);                     // original0068afd1 psrld mm0, 0xd
    mm1 = psrld<13>(mm1);                     // original0068afd5 psrld mm1, 0xd
    mm0 = pand(mm0, mm4);                     // original0068afd9 pand mm0, mm4
    mm1 = pand(mm1, mm5);                     // original0068afdc pand mm1, mm5
    mm4 = pandn(mm4, mm3);                    // original0068afdf pandn mm4, mm3
    mm5 = pandn(mm5, mm3);                    // original0068afe2 pandn mm5, mm3
    mm0 = por(mm0, mm4);                      // original0068afe5 por mm0, mm4
    mm1 = por(mm1, mm5);                      // original0068afe8 por mm1, mm5
    mm0 = packssdw(mm0, mm1);                 // original0068afeb packssdw mm0, mm1
    mm0 = por(mm0, mm6);                      // original0068afee por mm0, mm6
    store(eax, mm0);                          // original0068aff1 movq qword ptr [eax], mm0
    eax += 8u;                                // original0068aff4 lea eax, [eax + 8]
    edx += 16u;                               // original0068aff7 lea edx, [edx + 0x10]
    ecx -= 4u;                                // original0068affa sub ecx, 4
    goto L_0068af03;                          // original0068affd jmp 0x68af03
L_0068b002:;
    less = (static_cast<int32_t>(ecx) < 0);
    zero = (ecx == 0u); // original0068b002 cmp ecx, 0
    if (zero)
        goto L_0068b022; // original0068b005 je 0x68b022
    ecx -= 4u;           // original0068b007 sub ecx, 4
    edi = ecx;           // original0068b00a mov edi, ecx
    esi = ecx;           // original0068b00c mov esi, ecx
    edi *= 2u;           // original0068b00e imul edi, edi, 2
    esi *= 4u;           // original0068b011 imul esi, esi, 4
    edx += esi;          // original0068b014 add edx, esi
    eax += edi;          // original0068b016 add eax, edi
    ecx = 4u;            // original0068b018 mov ecx, 4
    goto L_0068af03;     // original0068b01d jmp 0x68af03
L_0068b022:;
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068b022 mov esp, ebp
    eax = word(arguments + 0u); // original0068b024 mov eax, dword ptr [ebp + 0x20]
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068b027 mov ebp, dword ptr [esp + 0x10]
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068b02b mov esi, dword ptr [esp + 0x14]
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068b02f mov edi, dword ptr [esp + 0x18]
    ; // Original private frame/save/call-argument operation; private address identity excluded. // original0068b033 add esp, 0x1c
    empty();    // original0068b036 femms
    return eax; // original0068b038 ret 0xc
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068aec0(void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068aec0\n\taddl $4,%esp\n\tretl $12");
}
