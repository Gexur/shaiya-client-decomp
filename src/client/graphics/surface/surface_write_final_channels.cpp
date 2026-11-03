#include "graphics/surface/surface_write_final_channels.h"
#include "graphics/surface/surface_write_transform.h"
#include "graphics/surface/surface_write_color.h"
#include "graphics/surface/surface_error_row.h"
extern "C" {
extern const uint32_t dat_006bbc78;
extern const uint32_t dat_006bc894;
extern const uint32_t dat_006bc8c4;
extern const uint32_t dat_006bca1c;
extern const uint32_t dat_006be1d0;
extern const uint32_t dat_006be980;
extern const uint32_t dat_006c0c2c;
extern const uint32_t dat_006c2bb4;
extern const uint32_t dat_006dc574;
extern const uint32_t dat_006dc578;
extern const uint32_t dat_006dc57c;
extern const uint32_t dat_006de5ac;
extern const uint32_t dat_006df404;
extern const uint32_t dat_006df408;
extern const uint32_t dat_006df410;
extern const uint32_t dat_006df418;
extern const uint32_t dat_006df41c;
extern const uint32_t dat_006df42c;
extern const uint32_t dat_006df430;
extern const uint32_t dat_006df434;
extern const uint32_t dat_006df5d8;
extern const uint32_t dat_006df62c;
extern const uint32_t dat_006df630;
}

#include "graphics/render_dispatch.h"
extern "C" const uint32_t dat_006df434 = 0x42fe0000u;
extern "C" const uint32_t dat_006df5d8 = 0x46fffe00u;
extern "C" const uint32_t dat_006df630 = 0x43ff8000u;
namespace {
using u32 = uint32_t;
u32 load32(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 load16(u32 p) {
    u32 v;
    __asm__ volatile("movzwl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 load8(u32 p) {
    u32 v;
    __asm__ volatile("movzbl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void store32(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void store16(u32 p, u32 v) {
    __asm__ volatile("movw %w1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void store8(u32 p, u32 v) {
    __asm__ volatile("movb %b1,(%0)" ::"r"(p), "q"(v) : "memory");
}
} // namespace
// Complete original 005f5959..005f5d10: A16B16G16R16; original access widths/order retained.
extern "C" u32 recovered_005f5959(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x80];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x80u;
    ;          // C++ frame and ABI save ownership. // original 005f5959 mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f595b push ebp
    ;          // C++ frame and ABI save ownership. // original 005f595c mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f595e sub esp, 0x5c
    ;          // C++ frame and ABI save ownership. // original 005f5961 push ebx
    ;          // C++ frame and ABI save ownership. // original 005f5962 push esi
    esi = ecx; // original 005f5963 mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f5965 cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f5969 push edi
    if (left == right)
        goto L_005f5977;         // original 005f596a je 0x5f5977
    pending = load32(args + 8u); // original 005f596c push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f596f call 0x5f0da1
    store32(args + 8u, eax); // original 005f5974 mov dword ptr [ebp + 0x10], eax
L_005f5977:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f5977 cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f598a;         // original 005f597b je 0x5f598a
    pending = load32(args + 8u); // original 005f597d push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f5980 mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f5982 call 0x5f22d6
    store32(args + 8u, eax); // original 005f5987 mov dword ptr [ebp + 0x10], eax
L_005f598a:;
    eax = load32(args + 0u);                     // original 005f598a mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f598d fldz
    edi = load32(esi + 0x68u); // original 005f598f mov edi, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x5cu)
                     : "st", "memory"); // original 005f5992 fstp dword ptr [ebp - 0x5c]
    edx = load32(esi + 0x60u);          // original 005f5995 mov edx, dword ptr [esi + 0x60]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f5998 fldz
    ebx = load32(esi + 0x64u); // original 005f599a mov ebx, dword ptr [esi + 0x64]
    edx = (edx) * (eax);       // original 005f599d imul edx, eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x58u)
                     : "st", "memory");          // original 005f59a0 fstp dword ptr [ebp - 0x58]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f59a3 fldz
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory");          // original 005f59a5 fstp dword ptr [ebp - 0x54]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f59a8 fldz
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f59aa fstp dword ptr [ebp - 0x50]
    store32(args + 0u, eax);            // original 005f59ad mov dword ptr [ebp + 8], eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f59b0 and dword ptr [ebp + 8], 1
    ecx = edi + 0xffffffffu;               // original 005f59b4 lea ecx, [edi - 1]
    ecx = (ecx) * (load32(args + 0u));     // original 005f59b7 imul ecx, dword ptr [ebp + 8]
    ecx = edx + ecx * 8u;                  // original 005f59bb lea ecx, [edx + ecx*8]
    edx = load32(args + 4u);               // original 005f59be mov edx, dword ptr [ebp + 0xc]
    ebx = (ebx) * (edx);                   // original 005f59c1 imul ebx, edx
    ecx = (ecx) + (ebx);                   // original 005f59c4 add ecx, ebx
    ecx = (ecx) + (load32(esi + 0x20u));   // original 005f59c6 add ecx, dword ptr [esi + 0x20]
    eax = (eax) & (0x3u);                  // original 005f59c9 and eax, 3
    edx = (edx) & (0x3u);                  // original 005f59cc and edx, 3
    left = load32(args + 0u);
    right = 0x0u;                // original 005f59cf cmp dword ptr [ebp + 8], 0
    store32(frame - 0x4u, ecx);  // original 005f59d3 mov dword ptr [ebp - 4], ecx
    ecx = load32(esi + 0x34u);   // original 005f59d6 mov ecx, dword ptr [esi + 0x34]
    eax = edx + eax * 8u;        // original 005f59d9 lea eax, [edx + eax*8]
    eax = ecx + eax * 4u;        // original 005f59dc lea eax, [ecx + eax*4]
    store32(frame - 0x10u, eax); // original 005f59df mov dword ptr [ebp - 0x10], eax
    if (left != right)
        goto L_005f59eb; // original 005f59e2 jne 0x5f59eb
    ebx = 0u;            // original 005f59e4 xor ebx, ebx
    edi = 0u;            // original 005f59e6 xor edi, edi
    ebx = ebx + 1u;      // original 005f59e8 inc ebx
    goto L_005f59ef;     // original 005f59e9 jmp 0x5f59ef
L_005f59eb:;
    edi = edi - 1u;              // original 005f59eb dec edi
    ebx = (ebx) | (0xffffffffu); // original 005f59ec or ebx, 0xffffffff
L_005f59ef:;
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 0u)
                     : "st", "memory"); // original 005f59ef fnstcw word ptr [ebp + 8]
    eax = load32(args + 0u);            // original 005f59f2 mov eax, dword ptr [ebp + 8]
    eax = (eax) | (0xc00u);             // original 005f59f5 or eax, 0xc00
    store32(args + 4u, eax);            // original 005f59fa mov dword ptr [ebp + 0xc], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f59fd fldcw word ptr [ebp + 0xc]
    eax = load32(args + 0u);            // original 005f5a00 mov eax, dword ptr [ebp + 8]
    store32(esi + 0x7cu, eax);          // original 005f5a03 mov dword ptr [esi + 0x7c], eax
    left = load32(esi + 0x5cu);
    right = 0x0u; // original 005f5a06 cmp dword ptr [esi + 0x5c], 0
    if (left == right)
        goto L_005f5a16;         // original 005f5a0a je 0x5f5a16
    pending = load32(args + 8u); // original 005f5a0c push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f5a0f mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f5a11 call 0x5f25f2
L_005f5a16:;
    store32(args + 0u,
            (load32(args + 0u)) & (0x0u)); // original 005f5a16 and dword ptr [ebp + 8], 0
    left = load32(esi + 0x68u);
    right = 0x0u; // original 005f5a1a cmp dword ptr [esi + 0x68], 0
    if (left <= right)
        goto L_005f5d00;         // original 005f5a1e jbe 0x5f5d00
    eax = ebx;                   // original 005f5a24 mov eax, ebx
    eax = (eax) << (0x3u);       // original 005f5a26 shl eax, 3
    store32(frame - 0x28u, eax); // original 005f5a29 mov dword ptr [ebp - 0x28], eax
    eax = ebx;                   // original 005f5a2c mov eax, ebx
    eax = (eax) << (0x4u);       // original 005f5a2e shl eax, 4
    ecx = edi;                   // original 005f5a31 mov ecx, edi
    edx = ebx + edi;             // original 005f5a33 lea edx, [ebx + edi]
    store32(frame - 0x2cu, eax); // original 005f5a36 mov dword ptr [ebp - 0x2c], eax
    eax = load32(args + 8u);     // original 005f5a39 mov eax, dword ptr [ebp + 0x10]
    ecx = (ecx) << (0x4u);       // original 005f5a3c shl ecx, 4
    edx = (edx) << (0x4u);       // original 005f5a3f shl edx, 4
    edi = (edi) - (ebx);         // original 005f5a42 sub edi, ebx
    edi = (edi) << (0x4u);       // original 005f5a44 shl edi, 4
    eax = ecx + eax + 0x8u;      // original 005f5a47 lea eax, [ecx + eax + 8]
    store32(frame - 0xcu, edx);  // original 005f5a4b mov dword ptr [ebp - 0xc], edx
    store32(frame - 0x8u, edi);  // original 005f5a4e mov dword ptr [ebp - 8], edi
    store32(args + 4u, eax);     // original 005f5a51 mov dword ptr [ebp + 0xc], eax
L_005f5a54:;
    eax = load32(args + 0u); // original 005f5a54 mov eax, dword ptr [ebp + 8]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006de5ac))
                     : "st", "memory"); // original 005f5a57 fld dword ptr [0x6de5ac]
    ebx = load32(frame - 0x10u);        // original 005f5a5d mov ebx, dword ptr [ebp - 0x10]
    eax = (eax) & (0x3u);               // original 005f5a60 and eax, 3
    __asm__ volatile("flds (%0)" ::"r"(ebx + eax * 4u)
                     : "st", "memory"); // original 005f5a63 fld dword ptr [ebx + eax*4]
    eax = load32(args + 4u);            // original 005f5a66 mov eax, dword ptr [ebp + 0xc]
    __asm__ volatile("fsts (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f5a69 fst dword ptr [ebp + 0x10]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x5cu)
                     : "st", "memory"); // original 005f5a6c fld dword ptr [ebp - 0x5c]
    __asm__ volatile("fadds (%0)" ::"r"(eax + 0xfffffff8u)
                     : "st", "memory"); // original 005f5a6f fadd dword ptr [eax - 8]
    __asm__ volatile("fmul %%st(2)" ::: "st", "memory"); // original 005f5a72 fmul st(2)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f5a74 fstp dword ptr [ebp - 0x4c]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x58u)
                     : "st", "memory"); // original 005f5a77 fld dword ptr [ebp - 0x58]
    __asm__ volatile("fadds (%0)" ::"r"(eax + 0xfffffffcu)
                     : "st", "memory"); // original 005f5a7a fadd dword ptr [eax - 4]
    __asm__ volatile("fmul %%st(2)" ::: "st", "memory"); // original 005f5a7d fmul st(2)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f5a7f fstp dword ptr [ebp - 0x48]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f5a82 fld dword ptr [ebp - 0x54]
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory");                  // original 005f5a85 fadd dword ptr [eax]
    __asm__ volatile("fmul %%st(2)" ::: "st", "memory"); // original 005f5a87 fmul st(2)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f5a89 fstp dword ptr [ebp - 0x44]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f5a8c fld dword ptr [ebp - 0x50]
    __asm__ volatile("fadds (%0)" ::"r"(eax + 0x4u)
                     : "st", "memory"); // original 005f5a8f fadd dword ptr [eax + 4]
    __asm__ volatile("fmul %%st(2)" ::: "st", "memory"); // original 005f5a92 fmul st(2)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f5a94 fstp dword ptr [ebp - 0x40]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f5a97 fld dword ptr [ebp - 0x4c]
    __asm__ volatile("fadd %%st(1)" ::: "st", "memory"); // original 005f5a9a fadd st(1)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f5a9c fstp dword ptr [ebp - 0x14]
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f5a9f fstp st(0)
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f5aa1 fstp st(0)
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f5aa3 fld dword ptr [ebp - 0x14]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f5aa6 fistp dword ptr [ebp - 0x18]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f5aa9 fld dword ptr [ebp - 0x48]
    ebx = load32(frame - 0x18u);        // original 005f5aac mov ebx, dword ptr [ebp - 0x18]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f5aaf fadd dword ptr [ebp + 0x10]
    store32(frame - 0x3cu, ebx);        // original 005f5ab2 mov dword ptr [ebp - 0x3c], ebx
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f5ab5 fstp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f5ab8 fld dword ptr [ebp - 0x14]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x1cu)
                     : "st", "memory"); // original 005f5abb fistp dword ptr [ebp - 0x1c]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f5abe fld dword ptr [ebp - 0x44]
    eax = load32(frame - 0x1cu);        // original 005f5ac1 mov eax, dword ptr [ebp - 0x1c]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f5ac4 fadd dword ptr [ebp + 0x10]
    store32(frame - 0x38u, eax);        // original 005f5ac7 mov dword ptr [ebp - 0x38], eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f5aca fstp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f5acd fld dword ptr [ebp - 0x14]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x20u)
                     : "st", "memory"); // original 005f5ad0 fistp dword ptr [ebp - 0x20]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f5ad3 fld dword ptr [ebp - 0x40]
    eax = load32(frame - 0x20u);        // original 005f5ad6 mov eax, dword ptr [ebp - 0x20]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f5ad9 fadd dword ptr [ebp + 0x10]
    store32(frame - 0x34u, eax);        // original 005f5adc mov dword ptr [ebp - 0x34], eax
    __asm__ volatile("fstps (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f5adf fstp dword ptr [ebp + 0x10]
    __asm__ volatile("flds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f5ae2 fld dword ptr [ebp + 0x10]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x24u)
                     : "st", "memory"); // original 005f5ae5 fistp dword ptr [ebp - 0x24]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f5ae8 cmp dword ptr [esi + 0x5c], 0
    eax = load32(frame - 0x24u); // original 005f5aec mov eax, dword ptr [ebp - 0x24]
    store32(frame - 0x30u, eax); // original 005f5aef mov dword ptr [ebp - 0x30], eax
    if (left == right)
        goto L_005f5c26; // original 005f5af2 je 0x5f5c26
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df42c))
                     : "st", "memory"); // original 005f5af8 fld dword ptr [0x6df42c]
    eax = load32(esi + 0x5cu);          // original 005f5afe mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f5b01 fild dword ptr [ebp - 0x3c]
    eax = eax + edi + 0x10u;            // original 005f5b04 lea eax, [eax + edi + 0x10]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f5b08 fsubr dword ptr [ebp - 0x4c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5b0b fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f5b0d fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5b13 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5b15 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5b17 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f5b19 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f5b1c fld dword ptr [0x6df418]
    eax = eax + ecx + 0x10u;            // original 005f5b22 lea eax, [eax + ecx + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5b26 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5b28 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5b2a fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f5b2c mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f5b2f fld dword ptr [0x6be980]
    eax = eax + edx + 0x10u;            // original 005f5b35 lea eax, [eax + edx + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5b39 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5b3b fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5b3d fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f5b3f mov eax, dword ptr [esi + 0x5c]
    eax = eax + edi + 0x14u;            // original 005f5b42 lea eax, [eax + edi + 0x14]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f5b46 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x5cu)
                     : "st", "memory"); // original 005f5b4c fstp dword ptr [ebp - 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f5b4f fild dword ptr [ebp - 0x38]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f5b52 fsubr dword ptr [ebp - 0x48]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5b55 fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f5b57 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5b5d fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5b5f fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5b61 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f5b63 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f5b66 fld dword ptr [0x6df418]
    eax = eax + ecx + 0x14u;            // original 005f5b6c lea eax, [eax + ecx + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5b70 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5b72 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5b74 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f5b76 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f5b79 fld dword ptr [0x6be980]
    eax = eax + edx + 0x14u;            // original 005f5b7f lea eax, [eax + edx + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5b83 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5b85 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5b87 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f5b89 mov eax, dword ptr [esi + 0x5c]
    eax = eax + edi + 0x18u;            // original 005f5b8c lea eax, [eax + edi + 0x18]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f5b90 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x58u)
                     : "st", "memory"); // original 005f5b96 fstp dword ptr [ebp - 0x58]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f5b99 fild dword ptr [ebp - 0x34]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f5b9c fsubr dword ptr [ebp - 0x44]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5b9f fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f5ba1 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5ba7 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5ba9 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5bab fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f5bad mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f5bb0 fld dword ptr [0x6df418]
    eax = eax + ecx + 0x18u;            // original 005f5bb6 lea eax, [eax + ecx + 0x18]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5bba fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5bbc fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5bbe fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f5bc0 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f5bc3 fld dword ptr [0x6be980]
    eax = eax + edx + 0x18u;            // original 005f5bc9 lea eax, [eax + edx + 0x18]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5bcd fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5bcf fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5bd1 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f5bd3 mov eax, dword ptr [esi + 0x5c]
    edi = eax + edi + 0x1cu;            // original 005f5bd6 lea edi, [eax + edi + 0x1c]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f5bda fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f5be0 fstp dword ptr [ebp - 0x54]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f5be3 fild dword ptr [ebp - 0x30]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f5be6 fsubr dword ptr [ebp - 0x40]
    __asm__ volatile("fmulp %%st(1)" ::: "st", "memory"); // original 005f5be9 fmulp st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f5beb fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5bf1 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f5bf3 fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f5bf5 fstp dword ptr [edi]
    eax = load32(esi + 0x5cu);          // original 005f5bf7 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f5bfa fld dword ptr [0x6df418]
    eax = eax + ecx + 0x1cu;            // original 005f5c00 lea eax, [eax + ecx + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5c04 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5c06 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5c08 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f5c0a mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f5c0d fld dword ptr [0x6be980]
    edx = eax + edx + 0x1cu;            // original 005f5c13 lea edx, [eax + edx + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5c17 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f5c19 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f5c1b fstp dword ptr [edx]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f5c1d fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f5c23 fstp dword ptr [ebp - 0x50]
L_005f5c26:;
    eax = 0xffffu; // original 005f5c26 mov eax, 0xffff
    left = ebx;
    right = eax; // original 005f5c2b cmp ebx, eax
    edx = ebx;   // original 005f5c2d mov edx, ebx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f5c33; // original 005f5c2f jl 0x5f5c33
    edx = eax;           // original 005f5c31 mov edx, eax
L_005f5c33:;
    edi = 0u; // original 005f5c33 xor edi, edi
    left = edx;
    right = edi; // original 005f5c35 cmp edx, edi
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f5c42; // original 005f5c37 jle 0x5f5c42
    left = ebx;
    right = eax; // original 005f5c39 cmp ebx, eax
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f5c45;         // original 005f5c3b jl 0x5f5c45
    store32(frame - 0x3cu, eax); // original 005f5c3d mov dword ptr [ebp - 0x3c], eax
    goto L_005f5c45;             // original 005f5c40 jmp 0x5f5c45
L_005f5c42:;
    store32(frame - 0x3cu, edi); // original 005f5c42 mov dword ptr [ebp - 0x3c], edi
L_005f5c45:;
    left = load32(frame - 0x38u);
    right = eax;                 // original 005f5c45 cmp dword ptr [ebp - 0x38], eax
    edx = load32(frame - 0x38u); // original 005f5c48 mov edx, dword ptr [ebp - 0x38]
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f5c4f; // original 005f5c4b jl 0x5f5c4f
    edx = eax;           // original 005f5c4d mov edx, eax
L_005f5c4f:;
    left = edx;
    right = edi; // original 005f5c4f cmp edx, edi
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f5c5d; // original 005f5c51 jle 0x5f5c5d
    left = load32(frame - 0x38u);
    right = eax; // original 005f5c53 cmp dword ptr [ebp - 0x38], eax
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f5c60;         // original 005f5c56 jl 0x5f5c60
    store32(frame - 0x38u, eax); // original 005f5c58 mov dword ptr [ebp - 0x38], eax
    goto L_005f5c60;             // original 005f5c5b jmp 0x5f5c60
L_005f5c5d:;
    store32(frame - 0x38u, edi); // original 005f5c5d mov dword ptr [ebp - 0x38], edi
L_005f5c60:;
    left = load32(frame - 0x34u);
    right = eax;                 // original 005f5c60 cmp dword ptr [ebp - 0x34], eax
    edx = load32(frame - 0x34u); // original 005f5c63 mov edx, dword ptr [ebp - 0x34]
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f5c6a; // original 005f5c66 jl 0x5f5c6a
    edx = eax;           // original 005f5c68 mov edx, eax
L_005f5c6a:;
    left = edx;
    right = edi; // original 005f5c6a cmp edx, edi
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f5c78; // original 005f5c6c jle 0x5f5c78
    left = load32(frame - 0x34u);
    right = eax; // original 005f5c6e cmp dword ptr [ebp - 0x34], eax
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f5c7b;         // original 005f5c71 jl 0x5f5c7b
    store32(frame - 0x34u, eax); // original 005f5c73 mov dword ptr [ebp - 0x34], eax
    goto L_005f5c7b;             // original 005f5c76 jmp 0x5f5c7b
L_005f5c78:;
    store32(frame - 0x34u, edi); // original 005f5c78 mov dword ptr [ebp - 0x34], edi
L_005f5c7b:;
    left = load32(frame - 0x30u);
    right = eax;                 // original 005f5c7b cmp dword ptr [ebp - 0x30], eax
    edx = load32(frame - 0x30u); // original 005f5c7e mov edx, dword ptr [ebp - 0x30]
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f5c85; // original 005f5c81 jl 0x5f5c85
    edx = eax;           // original 005f5c83 mov edx, eax
L_005f5c85:;
    left = edx;
    right = edi; // original 005f5c85 cmp edx, edi
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f5c93; // original 005f5c87 jle 0x5f5c93
    left = load32(frame - 0x30u);
    right = eax; // original 005f5c89 cmp dword ptr [ebp - 0x30], eax
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f5c96;         // original 005f5c8c jl 0x5f5c96
    store32(frame - 0x30u, eax); // original 005f5c8e mov dword ptr [ebp - 0x30], eax
    goto L_005f5c96;             // original 005f5c91 jmp 0x5f5c96
L_005f5c93:;
    store32(frame - 0x30u, edi); // original 005f5c93 mov dword ptr [ebp - 0x30], edi
L_005f5c96:;
    eax = load32(frame - 0x30u); // original 005f5c96 mov eax, dword ptr [ebp - 0x30]
    edx = static_cast<int32_t>(eax) < 0 ? 0xffffffffu : 0u; // original 005f5c99 cdq
    edx = (edx << (0x10u & 31u)) |
          (eax >> (32u - (0x10u & 31u))); // original 005f5c9a shld edx, eax, 0x10
    eax = (eax) << (0x10u);               // original 005f5c9e shl eax, 0x10
    edi = eax;                            // original 005f5ca1 mov edi, eax
    eax = load32(frame - 0x34u);          // original 005f5ca3 mov eax, dword ptr [ebp - 0x34]
    ebx = edx;                            // original 005f5ca6 mov ebx, edx
    edx = static_cast<int32_t>(eax) < 0 ? 0xffffffffu : 0u; // original 005f5ca8 cdq
    edi = (edi) | (eax);                                    // original 005f5ca9 or edi, eax
    eax = load32(frame - 0x38u); // original 005f5cab mov eax, dword ptr [ebp - 0x38]
    ebx = (ebx) | (edx);         // original 005f5cae or ebx, edx
    ebx = (ebx << (0x10u & 31u)) |
          (edi >> (32u - (0x10u & 31u)));                   // original 005f5cb0 shld ebx, edi, 0x10
    edx = static_cast<int32_t>(eax) < 0 ? 0xffffffffu : 0u; // original 005f5cb4 cdq
    edi = (edi) << (0x10u);                                 // original 005f5cb5 shl edi, 0x10
    edi = (edi) | (eax);                                    // original 005f5cb8 or edi, eax
    eax = load32(frame - 0x3cu); // original 005f5cba mov eax, dword ptr [ebp - 0x3c]
    ebx = (ebx) | (edx);         // original 005f5cbd or ebx, edx
    ebx = (ebx << (0x10u & 31u)) |
          (edi >> (32u - (0x10u & 31u)));                   // original 005f5cbf shld ebx, edi, 0x10
    edx = static_cast<int32_t>(eax) < 0 ? 0xffffffffu : 0u; // original 005f5cc3 cdq
    edi = (edi) << (0x10u);                                 // original 005f5cc4 shl edi, 0x10
    edi = (edi) | (eax);                                    // original 005f5cc7 or edi, eax
    eax = load32(frame - 0x4u);            // original 005f5cc9 mov eax, dword ptr [ebp - 4]
    ebx = (ebx) | (edx);                   // original 005f5ccc or ebx, edx
    edx = load32(frame - 0xcu);            // original 005f5cce mov edx, dword ptr [ebp - 0xc]
    store32(eax, edi);                     // original 005f5cd1 mov dword ptr [eax], edi
    edi = load32(frame - 0x8u);            // original 005f5cd3 mov edi, dword ptr [ebp - 8]
    store32(eax + 0x4u, ebx);              // original 005f5cd6 mov dword ptr [eax + 4], ebx
    eax = (eax) + (load32(frame - 0x28u)); // original 005f5cd9 add eax, dword ptr [ebp - 0x28]
    store32(frame - 0x4u, eax);            // original 005f5cdc mov dword ptr [ebp - 4], eax
    eax = load32(frame - 0x2cu);           // original 005f5cdf mov eax, dword ptr [ebp - 0x2c]
    store32(args + 4u,
            (load32(args + 4u)) + (eax));       // original 005f5ce2 add dword ptr [ebp + 0xc], eax
    edi = (edi) + (eax);                        // original 005f5ce5 add edi, eax
    edx = (edx) + (eax);                        // original 005f5ce7 add edx, eax
    ecx = (ecx) + (eax);                        // original 005f5ce9 add ecx, eax
    store32(args + 0u, load32(args + 0u) + 1u); // original 005f5ceb inc dword ptr [ebp + 8]
    eax = load32(args + 0u);                    // original 005f5cee mov eax, dword ptr [ebp + 8]
    left = eax;
    right = load32(esi + 0x68u); // original 005f5cf1 cmp eax, dword ptr [esi + 0x68]
    store32(frame - 0x8u, edi);  // original 005f5cf4 mov dword ptr [ebp - 8], edi
    store32(frame - 0xcu, edx);  // original 005f5cf7 mov dword ptr [ebp - 0xc], edx
    if (left < right)
        goto L_005f5a54; // original 005f5cfa jb 0x5f5a54
L_005f5d00:;
    eax = load32(esi + 0x7cu); // original 005f5d00 mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f5d03 mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f5d06 fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f5d09 pop edi
    ;                                   // C++ ABI restore ownership. // original 005f5d0a pop esi
    ;                                   // C++ ABI restore ownership. // original 005f5d0b pop ebx
    ;                                   // C++ frame ownership. // original 005f5d0c leave
    return eax;                         // original 005f5d0d ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f5959(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f5959\n\taddl $8,%esp\n\tretl $12");
}

// Complete original 005f5d10..005f5f58: A1; original access widths/order retained.
extern "C" u32 recovered_005f5d10(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x80];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x80u;
    ;          // C++ frame and ABI save ownership. // original 005f5d10 mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f5d12 push ebp
    ;          // C++ frame and ABI save ownership. // original 005f5d13 mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f5d15 sub esp, 0x54
    ;          // C++ frame and ABI save ownership. // original 005f5d18 push ebx
    ;          // C++ frame and ABI save ownership. // original 005f5d19 push esi
    esi = ecx; // original 005f5d1a mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f5d1c cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f5d20 push edi
    if (left == right)
        goto L_005f5d2e;         // original 005f5d21 je 0x5f5d2e
    pending = load32(args + 8u); // original 005f5d23 push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f5d26 call 0x5f0da1
    store32(args + 8u, eax); // original 005f5d2b mov dword ptr [ebp + 0x10], eax
L_005f5d2e:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f5d2e cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f5d41;         // original 005f5d32 je 0x5f5d41
    pending = load32(args + 8u); // original 005f5d34 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f5d37 mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f5d39 call 0x5f22d6
    store32(args + 8u, eax); // original 005f5d3e mov dword ptr [ebp + 0x10], eax
L_005f5d41:;
    eax = load32(args + 0u);                     // original 005f5d41 mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f5d44 fldz
    edi = load32(esi + 0x68u); // original 005f5d46 mov edi, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f5d49 fstp dword ptr [ebp - 0x38]
    edx = load32(esi + 0x60u);          // original 005f5d4c mov edx, dword ptr [esi + 0x60]
    store32(args + 0u, eax);            // original 005f5d4f mov dword ptr [ebp + 8], eax
    edx = (edx) * (eax);                // original 005f5d52 imul edx, eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f5d55 and dword ptr [ebp + 8], 1
    ecx = edi + 0xffffffffu;               // original 005f5d59 lea ecx, [edi - 1]
    ecx = (ecx) * (load32(args + 0u));     // original 005f5d5c imul ecx, dword ptr [ebp + 8]
    ebx = edx + ecx * 2u;                  // original 005f5d60 lea ebx, [edx + ecx*2]
    ecx = load32(args + 4u);               // original 005f5d63 mov ecx, dword ptr [ebp + 0xc]
    edx = load32(esi + 0x64u);             // original 005f5d66 mov edx, dword ptr [esi + 0x64]
    edx = (edx) * (ecx);                   // original 005f5d69 imul edx, ecx
    eax = (eax) & (0x3u);                  // original 005f5d6c and eax, 3
    ecx = (ecx) & (0x3u);                  // original 005f5d6f and ecx, 3
    eax = ecx + eax * 8u;                  // original 005f5d72 lea eax, [ecx + eax*8]
    ecx = load32(esi + 0x34u);             // original 005f5d75 mov ecx, dword ptr [esi + 0x34]
    ebx = (ebx) + (edx);                   // original 005f5d78 add ebx, edx
    ebx = (ebx) + (load32(esi + 0x20u));   // original 005f5d7a add ebx, dword ptr [esi + 0x20]
    left = load32(args + 0u);
    right = 0x0u;                // original 005f5d7d cmp dword ptr [ebp + 8], 0
    eax = ecx + eax * 4u;        // original 005f5d81 lea eax, [ecx + eax*4]
    store32(frame - 0x1cu, eax); // original 005f5d84 mov dword ptr [ebp - 0x1c], eax
    if (left != right)
        goto L_005f5d94;      // original 005f5d87 jne 0x5f5d94
    edi = 0u;                 // original 005f5d89 xor edi, edi
    store32(args + 0u, 0x1u); // original 005f5d8b mov dword ptr [ebp + 8], 1
    goto L_005f5d99;          // original 005f5d92 jmp 0x5f5d99
L_005f5d94:;
    edi = edi - 1u; // original 005f5d94 dec edi
    store32(args + 0u, (load32(args + 0u)) |
                           (0xffffffffu)); // original 005f5d95 or dword ptr [ebp + 8], 0xffffffff
L_005f5d99:;
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f5d99 fnstcw word ptr [ebp + 0xc]
    eax = load32(args + 4u);            // original 005f5d9c mov eax, dword ptr [ebp + 0xc]
    eax = (eax) | (0xc00u);             // original 005f5d9f or eax, 0xc00
    store32(frame - 0x18u, eax);        // original 005f5da4 mov dword ptr [ebp - 0x18], eax
    __asm__ volatile("fldcw (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f5da7 fldcw word ptr [ebp - 0x18]
    eax = load32(args + 4u);            // original 005f5daa mov eax, dword ptr [ebp + 0xc]
    store32(esi + 0x7cu, eax);          // original 005f5dad mov dword ptr [esi + 0x7c], eax
    left = load32(esi + 0x5cu);
    right = 0x0u; // original 005f5db0 cmp dword ptr [esi + 0x5c], 0
    if (left == right)
        goto L_005f5dc0;         // original 005f5db4 je 0x5f5dc0
    pending = load32(args + 8u); // original 005f5db6 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f5db9 mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f5dbb call 0x5f25f2
L_005f5dc0:;
    store32(args + 4u,
            (load32(args + 4u)) & (0x0u)); // original 005f5dc0 and dword ptr [ebp + 0xc], 0
    left = load32(esi + 0x68u);
    right = 0x0u; // original 005f5dc4 cmp dword ptr [esi + 0x68], 0
    if (left <= right)
        goto L_005f5f48;                // original 005f5dc8 jbe 0x5f5f48
    ecx = load32(args + 0u);            // original 005f5dce mov ecx, dword ptr [ebp + 8]
    eax = ecx + ecx;                    // original 005f5dd1 lea eax, [ecx + ecx]
    store32(frame - 0x24u, eax);        // original 005f5dd4 mov dword ptr [ebp - 0x24], eax
    eax = ecx;                          // original 005f5dd7 mov eax, ecx
    eax = (eax) << (0x4u);              // original 005f5dd9 shl eax, 4
    edx = edi;                          // original 005f5ddc mov edx, edi
    edx = (edx) - (load32(args + 0u));  // original 005f5dde sub edx, dword ptr [ebp + 8]
    ecx = (ecx) + (edi);                // original 005f5de1 add ecx, edi
    store32(frame - 0xcu, eax);         // original 005f5de3 mov dword ptr [ebp - 0xc], eax
    eax = load32(args + 8u);            // original 005f5de6 mov eax, dword ptr [ebp + 0x10]
    edi = (edi) << (0x4u);              // original 005f5de9 shl edi, 4
    edx = (edx) << (0x4u);              // original 005f5dec shl edx, 4
    edi = edi + eax + 0x8u;             // original 005f5def lea edi, [edi + eax + 8]
    store32(frame - 0x8u, 0xfffffff8u); // original 005f5df3 mov dword ptr [ebp - 8], 0xfffffff8
    ecx = (ecx) << (0x4u);              // original 005f5dfa shl ecx, 4
    store32(frame - 0x8u,
            (load32(frame - 0x8u)) - (eax)); // original 005f5dfd sub dword ptr [ebp - 8], eax
    store32(frame - 0x18u, edx);             // original 005f5e00 mov dword ptr [ebp - 0x18], edx
    store32(args + 0u, edi);                 // original 005f5e03 mov dword ptr [ebp + 8], edi
L_005f5e06:;
    eax = load32(esi + 0x38u); // original 005f5e06 mov eax, dword ptr [esi + 0x38]
    store32(frame - 0x14u,
            (load32(frame - 0x14u)) & (0x0u)); // original 005f5e09 and dword ptr [ebp - 0x14], 0
    store32(args + 8u,
            (load32(args + 8u)) & (0x0u)); // original 005f5e0d and dword ptr [ebp + 0x10], 0
    store32(frame - 0x10u, 0x7f7fffffu); // original 005f5e11 mov dword ptr [ebp - 0x10], 0x7f7fffff
    store32(frame - 0x4u, eax);          // original 005f5e18 mov dword ptr [ebp - 4], eax
    goto L_005f5e20;                     // original 005f5e1b jmp 0x5f5e20
L_005f5e1d:;
    eax = load32(frame - 0x4u); // original 005f5e1d mov eax, dword ptr [ebp - 4]
L_005f5e20:;
    __asm__ volatile("flds (%0)" ::"r"(edi + 0xfffffff8u)
                     : "st", "memory"); // original 005f5e20 fld dword ptr [edi - 8]
    __asm__ volatile("fsubs (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f5e23 fsub dword ptr [eax]
    __asm__ volatile("flds (%0)" ::"r"(edi + 0xfffffffcu)
                     : "st", "memory"); // original 005f5e25 fld dword ptr [edi - 4]
    __asm__ volatile("fsubs (%0)" ::"r"(eax + 0x4u)
                     : "st", "memory"); // original 005f5e28 fsub dword ptr [eax + 4]
    __asm__ volatile("flds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f5e2b fld dword ptr [edi]
    __asm__ volatile("fsubs (%0)" ::"r"(eax + 0x8u)
                     : "st", "memory"); // original 005f5e2d fsub dword ptr [eax + 8]
    __asm__ volatile("fld %%st(0)" ::: "st", "memory");   // original 005f5e30 fld st(0)
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory");  // original 005f5e32 fmul st(1)
    __asm__ volatile("fld %%st(2)" ::: "st", "memory");   // original 005f5e34 fld st(2)
    __asm__ volatile("fmul %%st(3)" ::: "st", "memory");  // original 005f5e36 fmul st(3)
    __asm__ volatile("faddp %%st(1)" ::: "st", "memory"); // original 005f5e38 faddp st(1)
    __asm__ volatile("fld %%st(3)" ::: "st", "memory");   // original 005f5e3a fld st(3)
    __asm__ volatile("fmul %%st(4)" ::: "st", "memory");  // original 005f5e3c fmul st(4)
    __asm__ volatile("faddp %%st(1)" ::: "st", "memory"); // original 005f5e3e faddp st(1)
    __asm__ volatile("fstp %%st(3)" ::: "st", "memory");  // original 005f5e40 fstp st(3)
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory");  // original 005f5e42 fstp st(0)
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory");  // original 005f5e44 fstp st(0)
    __asm__ volatile("fcoms (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f5e46 fcom dword ptr [ebp - 0x10]
    uint16_t status;
    __asm__ volatile("fnstsw %%ax" : "=a"(status));
    eax = (eax & 0xffff0000u) | status; // original 005f5e49 fnstsw ax
    left = (eax >> 8 & 255u);
    right = 0x5u;
    left &= right;
    right = 0; // original 005f5e4b test ah, 5
    if ((__builtin_parity(left & 255u) == 0))
        goto L_005f5e5b;     // original 005f5e4e jp 0x5f5e5b
    eax = load32(args + 8u); // original 005f5e50 mov eax, dword ptr [ebp + 0x10]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f5e53 fstp dword ptr [ebp - 0x10]
    store32(frame - 0x14u, eax);        // original 005f5e56 mov dword ptr [ebp - 0x14], eax
    goto L_005f5e5d;                    // original 005f5e59 jmp 0x5f5e5d
L_005f5e5b:;
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f5e5b fstp st(0)
L_005f5e5d:;
    store32(args + 8u, load32(args + 8u) + 1u); // original 005f5e5d inc dword ptr [ebp + 0x10]
    store32(frame - 0x4u,
            (load32(frame - 0x4u)) + (0x10u)); // original 005f5e60 add dword ptr [ebp - 4], 0x10
    left = load32(args + 8u);
    right = 0x100u; // original 005f5e64 cmp dword ptr [ebp + 0x10], 0x100
    if (left < right)
        goto L_005f5e1d; // original 005f5e6b jb 0x5f5e1d
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f5e6d fld dword ptr [ebp - 0x38]
    eax = load32(args + 4u);            // original 005f5e70 mov eax, dword ptr [ebp + 0xc]
    __asm__ volatile("fadds (%0)" ::"r"(edi + 0x4u)
                     : "st", "memory"); // original 005f5e73 fadd dword ptr [edi + 4]
    edi = load32(frame - 0x1cu);        // original 005f5e76 mov edi, dword ptr [ebp - 0x1c]
    eax = (eax) & (0x3u);               // original 005f5e79 and eax, 3
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bc8c4))
                     : "st", "memory"); // original 005f5e7c fmul dword ptr [0x6bc8c4]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x28u)
                     : "st", "memory"); // original 005f5e82 fstp dword ptr [ebp - 0x28]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x28u)
                     : "st", "memory"); // original 005f5e85 fld dword ptr [ebp - 0x28]
    __asm__ volatile("fadds (%0)" ::"r"(edi + eax * 4u)
                     : "st", "memory"); // original 005f5e88 fadd dword ptr [edi + eax*4]
    __asm__ volatile("fstps (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f5e8b fstp dword ptr [ebp + 0x10]
    __asm__ volatile("flds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f5e8e fld dword ptr [ebp + 0x10]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x20u)
                     : "st", "memory"); // original 005f5e91 fistp dword ptr [ebp - 0x20]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f5e94 cmp dword ptr [esi + 0x5c], 0
    eax = load32(frame - 0x20u); // original 005f5e98 mov eax, dword ptr [ebp - 0x20]
    store32(frame - 0x48u, eax); // original 005f5e9b mov dword ptr [ebp - 0x48], eax
    if (left == right)
        goto L_005f5ef6; // original 005f5e9e je 0x5f5ef6
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f5ea0 fild dword ptr [ebp - 0x48]
    edi = load32(esi + 0x5cu);          // original 005f5ea3 mov edi, dword ptr [esi + 0x5c]
    edx = edi + edx + 0x1cu;            // original 005f5ea6 lea edx, [edi + edx + 0x1c]
    edi = load32(args + 0u);            // original 005f5eaa mov edi, dword ptr [ebp + 8]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x28u)
                     : "st", "memory"); // original 005f5ead fsubr dword ptr [ebp - 0x28]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be1d0))
                     : "st", "memory"); // original 005f5eb0 fmul dword ptr [0x6be1d0]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f5eb6 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5ebc fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f5ebe fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory");   // original 005f5ec0 fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);            // original 005f5ec2 mov edx, dword ptr [esi + 0x5c]
    edx = (edx) + (load32(frame - 0x8u)); // original 005f5ec5 add edx, dword ptr [ebp - 8]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f5ec8 fld dword ptr [0x6df418]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5ece fmul st(1)
    edx = edx + edi + 0x1cu; // original 005f5ed0 lea edx, [edx + edi + 0x1c]
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f5ed4 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f5ed6 fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f5ed8 mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f5edb fld dword ptr [0x6be980]
    edx = edx + ecx + 0x1cu;            // original 005f5ee1 lea edx, [edx + ecx + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f5ee5 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f5ee7 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f5ee9 fstp dword ptr [edx]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f5eeb fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f5ef1 fstp dword ptr [ebp - 0x38]
    goto L_005f5ef9;                    // original 005f5ef4 jmp 0x5f5ef9
L_005f5ef6:;
    edi = load32(args + 0u); // original 005f5ef6 mov edi, dword ptr [ebp + 8]
L_005f5ef9:;
    left = eax;
    right = 0xffu; // original 005f5ef9 cmp eax, 0xff
    edx = eax;     // original 005f5efe mov edx, eax
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f5f07; // original 005f5f00 jl 0x5f5f07
    edx = 0xffu;         // original 005f5f02 mov edx, 0xff
L_005f5f07:;
    left = edx;
    right = edx;
    left &= right;
    right = 0; // original 005f5f07 test edx, edx
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f5f18; // original 005f5f09 jle 0x5f5f18
    edx = 0xffu;         // original 005f5f0b mov edx, 0xff
    left = eax;
    right = edx; // original 005f5f10 cmp eax, edx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f5f1a; // original 005f5f12 jl 0x5f5f1a
    eax = edx;           // original 005f5f14 mov eax, edx
    goto L_005f5f1a;     // original 005f5f16 jmp 0x5f5f1a
L_005f5f18:;
    eax = 0u; // original 005f5f18 xor eax, eax
L_005f5f1a:;
    edi = (edi) + (load32(frame - 0xcu)); // original 005f5f1a add edi, dword ptr [ebp - 0xc]
    ecx = (ecx) + (load32(frame - 0xcu)); // original 005f5f1d add ecx, dword ptr [ebp - 0xc]
    edx = 0u;                             // original 005f5f20 xor edx, edx
    edx = (edx & 0xffff00ffu) | ((((eax & 0xffu)) & 255u) << 8); // original 005f5f22 mov dh, al
    store32(args + 0u, edi);                    // original 005f5f24 mov dword ptr [ebp + 8], edi
    edx = (edx) | (load32(frame - 0x14u));      // original 005f5f27 or edx, dword ptr [ebp - 0x14]
    store16(ebx, (edx & 0xffffu));              // original 005f5f2a mov word ptr [ebx], dx
    edx = load32(frame - 0x18u);                // original 005f5f2d mov edx, dword ptr [ebp - 0x18]
    edx = (edx) + (load32(frame - 0xcu));       // original 005f5f30 add edx, dword ptr [ebp - 0xc]
    ebx = (ebx) + (load32(frame - 0x24u));      // original 005f5f33 add ebx, dword ptr [ebp - 0x24]
    store32(args + 4u, load32(args + 4u) + 1u); // original 005f5f36 inc dword ptr [ebp + 0xc]
    eax = load32(args + 4u);                    // original 005f5f39 mov eax, dword ptr [ebp + 0xc]
    left = eax;
    right = load32(esi + 0x68u); // original 005f5f3c cmp eax, dword ptr [esi + 0x68]
    store32(frame - 0x18u, edx); // original 005f5f3f mov dword ptr [ebp - 0x18], edx
    if (left < right)
        goto L_005f5e06; // original 005f5f42 jb 0x5f5e06
L_005f5f48:;
    eax = load32(esi + 0x7cu); // original 005f5f48 mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f5f4b mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f5f4e fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f5f51 pop edi
    ;                                   // C++ ABI restore ownership. // original 005f5f52 pop esi
    ;                                   // C++ ABI restore ownership. // original 005f5f53 pop ebx
    ;                                   // C++ frame ownership. // original 005f5f54 leave
    return eax;                         // original 005f5f55 ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f5d10(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f5d10\n\taddl $8,%esp\n\tretl $12");
}

// Complete original 005f6496..005f6737: signed L6V5U5; original access widths/order retained.
extern "C" u32 recovered_005f6496(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x80];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x80u;
    ;          // C++ frame and ABI save ownership. // original 005f6496 mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f6498 push ebp
    ;          // C++ frame and ABI save ownership. // original 005f6499 mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f649b sub esp, 0x50
    ;          // C++ frame and ABI save ownership. // original 005f649e push ebx
    ;          // C++ frame and ABI save ownership. // original 005f649f push esi
    esi = ecx; // original 005f64a0 mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f64a2 cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f64a6 push edi
    if (left == right)
        goto L_005f64b4;         // original 005f64a7 je 0x5f64b4
    pending = load32(args + 8u); // original 005f64a9 push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f64ac call 0x5f0da1
    store32(args + 8u, eax); // original 005f64b1 mov dword ptr [ebp + 0x10], eax
L_005f64b4:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f64b4 cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f64c7;         // original 005f64b8 je 0x5f64c7
    pending = load32(args + 8u); // original 005f64ba push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f64bd mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f64bf call 0x5f22d6
    store32(args + 8u, eax); // original 005f64c4 mov dword ptr [ebp + 0x10], eax
L_005f64c7:;
    eax = load32(args + 0u);                     // original 005f64c7 mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f64ca fldz
    edx = load32(esi + 0x68u); // original 005f64cc mov edx, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f64cf fstp dword ptr [ebp - 0x50]
    ecx = load32(esi + 0x60u);          // original 005f64d2 mov ecx, dword ptr [esi + 0x60]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f64d5 fldz
    ebx = load32(esi + 0x64u); // original 005f64d7 mov ebx, dword ptr [esi + 0x64]
    ecx = (ecx) * (eax);       // original 005f64da imul ecx, eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f64dd fstp dword ptr [ebp - 0x44]
    store32(args + 0u, eax);            // original 005f64e0 mov dword ptr [ebp + 8], eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f64e3 and dword ptr [ebp + 8], 1
    edi = edx + 0xffffffffu;               // original 005f64e7 lea edi, [edx - 1]
    edi = (edi) * (load32(args + 0u));     // original 005f64ea imul edi, dword ptr [ebp + 8]
    edi = (edi) + (ecx);                   // original 005f64ee add edi, ecx
    ecx = load32(args + 4u);               // original 005f64f0 mov ecx, dword ptr [ebp + 0xc]
    ebx = (ebx) * (ecx);                   // original 005f64f3 imul ebx, ecx
    eax = (eax) & (0x3u);                  // original 005f64f6 and eax, 3
    ecx = (ecx) & (0x3u);                  // original 005f64f9 and ecx, 3
    edi = (edi) + (ebx);                   // original 005f64fc add edi, ebx
    edi = (edi) + (load32(esi + 0x20u));   // original 005f64fe add edi, dword ptr [esi + 0x20]
    eax = ecx + eax * 8u;                  // original 005f6501 lea eax, [ecx + eax*8]
    ecx = load32(esi + 0x34u);             // original 005f6504 mov ecx, dword ptr [esi + 0x34]
    ebx = 0u;                              // original 005f6507 xor ebx, ebx
    left = load32(args + 0u);
    right = ebx;                // original 005f6509 cmp dword ptr [ebp + 8], ebx
    eax = ecx + eax * 4u;       // original 005f650c lea eax, [ecx + eax*4]
    store32(frame - 0xcu, eax); // original 005f650f mov dword ptr [ebp - 0xc], eax
    if (left != right)
        goto L_005f6520;      // original 005f6512 jne 0x5f6520
    store32(args + 4u, ebx);  // original 005f6514 mov dword ptr [ebp + 0xc], ebx
    store32(args + 0u, 0x1u); // original 005f6517 mov dword ptr [ebp + 8], 1
    goto L_005f6528;          // original 005f651e jmp 0x5f6528
L_005f6520:;
    edx = edx - 1u; // original 005f6520 dec edx
    store32(args + 0u, (load32(args + 0u)) |
                           (0xffffffffu)); // original 005f6521 or dword ptr [ebp + 8], 0xffffffff
    store32(args + 4u, edx);               // original 005f6525 mov dword ptr [ebp + 0xc], edx
L_005f6528:;
    __asm__ volatile("fnstcw (%0)" ::"r"(frame - 0x8u)
                     : "st", "memory"); // original 005f6528 fnstcw word ptr [ebp - 8]
    eax = load32(frame - 0x8u);         // original 005f652b mov eax, dword ptr [ebp - 8]
    eax = (eax) | (0xc00u);             // original 005f652e or eax, 0xc00
    store32(frame - 0x4u, eax);         // original 005f6533 mov dword ptr [ebp - 4], eax
    __asm__ volatile("fldcw (%0)" ::"r"(frame - 0x4u)
                     : "st", "memory"); // original 005f6536 fldcw word ptr [ebp - 4]
    eax = load32(frame - 0x8u);         // original 005f6539 mov eax, dword ptr [ebp - 8]
    store32(esi + 0x7cu, eax);          // original 005f653c mov dword ptr [esi + 0x7c], eax
    ecx = 0u;                           // original 005f653f xor ecx, ecx
    left = load32(esi + 0x68u);
    right = ebx; // original 005f6541 cmp dword ptr [esi + 0x68], ebx
    if (left <= right)
        goto L_005f6572;     // original 005f6544 jbe 0x5f6572
    eax = load32(args + 8u); // original 005f6546 mov eax, dword ptr [ebp + 0x10]
L_005f6549:;
    __asm__ volatile("flds (%0)" ::"r"(eax + 0x8u)
                     : "st", "memory"); // original 005f6549 fld dword ptr [eax + 8]
    ecx = ecx + 1u;                     // original 005f654c inc ecx
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006dc57c))
                     : "st", "memory"); // original 005f654d fmul dword ptr [0x6dc57c]
    __asm__ volatile("flds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f6553 fld dword ptr [eax]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006dc574))
                     : "st", "memory"); // original 005f6555 fmul dword ptr [0x6dc574]
    __asm__ volatile("faddp %%st(1)" ::: "st", "memory"); // original 005f655b faddp st(1)
    __asm__ volatile("flds (%0)" ::"r"(eax + 0x4u)
                     : "st", "memory"); // original 005f655d fld dword ptr [eax + 4]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006dc578))
                     : "st", "memory"); // original 005f6560 fmul dword ptr [0x6dc578]
    __asm__ volatile("faddp %%st(1)" ::: "st", "memory"); // original 005f6566 faddp st(1)
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f6568 fstp dword ptr [eax]
    eax = (eax) + (0x10u);              // original 005f656a add eax, 0x10
    left = ecx;
    right = load32(esi + 0x68u); // original 005f656d cmp ecx, dword ptr [esi + 0x68]
    if (left < right)
        goto L_005f6549; // original 005f6570 jb 0x5f6549
L_005f6572:;
    left = load32(esi + 0x5cu);
    right = ebx; // original 005f6572 cmp dword ptr [esi + 0x5c], ebx
    if (left == right)
        goto L_005f6581;         // original 005f6575 je 0x5f6581
    pending = load32(args + 8u); // original 005f6577 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f657a mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f657c call 0x5f25f2
L_005f6581:;
    left = load32(esi + 0x68u);
    right = ebx;                // original 005f6581 cmp dword ptr [esi + 0x68], ebx
    store32(frame - 0x4u, ebx); // original 005f6584 mov dword ptr [ebp - 4], ebx
    if (left <= right)
        goto L_005f6727;               // original 005f6587 jbe 0x5f6727
    ebx = load32(args + 0u);           // original 005f658d mov ebx, dword ptr [ebp + 8]
    edx = load32(args + 4u);           // original 005f6590 mov edx, dword ptr [ebp + 0xc]
    ecx = ebx;                         // original 005f6593 mov ecx, ebx
    ecx = (ecx) << (0x4u);             // original 005f6595 shl ecx, 4
    store32(frame - 0x20u, ecx);       // original 005f6598 mov dword ptr [ebp - 0x20], ecx
    ecx = edx;                         // original 005f659b mov ecx, edx
    ecx = (ecx) - (load32(args + 0u)); // original 005f659d sub ecx, dword ptr [ebp + 8]
    ebx = (ebx) + (edx);               // original 005f65a0 add ebx, edx
    eax = edx;                         // original 005f65a2 mov eax, edx
    ebx = (ebx) << (0x4u);             // original 005f65a4 shl ebx, 4
    eax = (eax) << (0x4u);             // original 005f65a7 shl eax, 4
    ecx = (ecx) << (0x4u);             // original 005f65aa shl ecx, 4
    store32(frame - 0x8u, ebx);        // original 005f65ad mov dword ptr [ebp - 8], ebx
    store32(args + 4u, ecx);           // original 005f65b0 mov dword ptr [ebp + 0xc], ecx
L_005f65b3:;
    ecx = load32(frame - 0x4u); // original 005f65b3 mov ecx, dword ptr [ebp - 4]
    edx = load32(frame - 0xcu); // original 005f65b6 mov edx, dword ptr [ebp - 0xc]
    ecx = (ecx) & (0x3u);       // original 005f65b9 and ecx, 3
    __asm__ volatile("flds (%0)" ::"r"(edx + ecx * 4u)
                     : "st", "memory"); // original 005f65bc fld dword ptr [edx + ecx*4]
    ecx = load32(args + 8u);            // original 005f65bf mov ecx, dword ptr [ebp + 0x10]
    __asm__ volatile("fsts (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f65c2 fst dword ptr [ebp - 0x18]
    ecx = (ecx) + (eax);                // original 005f65c5 add ecx, eax
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f65c7 fld dword ptr [ebp - 0x50]
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f65ca fadd dword ptr [ecx]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bc894))
                     : "st", "memory"); // original 005f65cc fmul dword ptr [0x6bc894]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f65d2 fstp dword ptr [ebp - 0x40]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f65d5 fld dword ptr [ebp - 0x44]
    __asm__ volatile("fadds (%0)" ::"r"(ecx + 0xcu)
                     : "st", "memory"); // original 005f65d8 fadd dword ptr [ecx + 0xc]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bc894))
                     : "st", "memory"); // original 005f65db fmul dword ptr [0x6bc894]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f65e1 fstp dword ptr [ebp - 0x34]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f65e4 fld dword ptr [ebp - 0x40]
    __asm__ volatile("fadd %%st(1)" ::: "st", "memory"); // original 005f65e7 fadd st(1)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f65e9 fstp dword ptr [ebp - 0x10]
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f65ec fstp st(0)
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f65ee fld dword ptr [ebp - 0x10]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f65f1 fistp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f65f4 fld dword ptr [ebp - 0x34]
    ecx = load32(frame - 0x14u);        // original 005f65f7 mov ecx, dword ptr [ebp - 0x14]
    __asm__ volatile("fadds (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f65fa fadd dword ptr [ebp - 0x18]
    store32(frame - 0x30u, ecx);        // original 005f65fd mov dword ptr [ebp - 0x30], ecx
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f6600 fstp dword ptr [ebp - 0x18]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f6603 fld dword ptr [ebp - 0x18]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x1cu)
                     : "st", "memory"); // original 005f6606 fistp dword ptr [ebp - 0x1c]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f6609 cmp dword ptr [esi + 0x5c], 0
    ecx = load32(frame - 0x1cu); // original 005f660d mov ecx, dword ptr [ebp - 0x1c]
    store32(frame - 0x24u, ecx); // original 005f6610 mov dword ptr [ebp - 0x24], ecx
    if (left == right)
        goto L_005f66bf; // original 005f6613 je 0x5f66bf
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006c0c2c))
                     : "st", "memory"); // original 005f6619 fld dword ptr [0x6c0c2c]
    edx = load32(esi + 0x5cu);          // original 005f661f mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f6622 fild dword ptr [ebp - 0x30]
    ebx = load32(args + 4u);            // original 005f6625 mov ebx, dword ptr [ebp + 0xc]
    edx = edx + ebx + 0x10u;            // original 005f6628 lea edx, [edx + ebx + 0x10]
    ebx = load32(frame - 0x8u);         // original 005f662c mov ebx, dword ptr [ebp - 8]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f662f fsubr dword ptr [ebp - 0x40]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6632 fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f6634 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f663a fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f663c fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f663e fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f6640 mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f6643 fld dword ptr [0x6df418]
    edx = edx + eax + 0x10u;            // original 005f6649 lea edx, [edx + eax + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f664d fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f664f fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6651 fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f6653 mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f6656 fld dword ptr [0x6be980]
    edx = edx + ebx + 0x10u;            // original 005f665c lea edx, [edx + ebx + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6660 fmul st(1)
    ebx = load32(args + 4u); // original 005f6662 mov ebx, dword ptr [ebp + 0xc]
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6665 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6667 fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f6669 mov edx, dword ptr [esi + 0x5c]
    edx = edx + ebx + 0x1cu;            // original 005f666c lea edx, [edx + ebx + 0x1c]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f6670 fmul qword ptr [0x6df410]
    ebx = load32(frame - 0x8u);         // original 005f6676 mov ebx, dword ptr [ebp - 8]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f6679 fstp dword ptr [ebp - 0x50]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x24u)
                     : "st", "memory"); // original 005f667c fild dword ptr [ebp - 0x24]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f667f fsubr dword ptr [ebp - 0x34]
    __asm__ volatile("fmulp %%st(1)" ::: "st", "memory"); // original 005f6682 fmulp st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f6684 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f668a fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f668c fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f668e fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f6690 mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f6693 fld dword ptr [0x6df418]
    edx = edx + eax + 0x1cu;            // original 005f6699 lea edx, [edx + eax + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f669d fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f669f fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f66a1 fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f66a3 mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f66a6 fld dword ptr [0x6be980]
    edx = edx + ebx + 0x1cu;            // original 005f66ac lea edx, [edx + ebx + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f66b0 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f66b2 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f66b4 fstp dword ptr [edx]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f66b6 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f66bc fstp dword ptr [ebp - 0x44]
L_005f66bf:;
    left = load32(frame - 0x30u);
    right = 0xfu; // original 005f66bf cmp dword ptr [ebp - 0x30], 0xf
    if (static_cast<int32_t>(left) >= static_cast<int32_t>(right))
        goto L_005f66ca;         // original 005f66c3 jge 0x5f66ca
    edx = load32(frame - 0x30u); // original 005f66c5 mov edx, dword ptr [ebp - 0x30]
    goto L_005f66cd;             // original 005f66c8 jmp 0x5f66cd
L_005f66ca:;
    pending = 0xfu; // original 005f66ca push 0xf
    edx = pending;  // original 005f66cc pop edx
L_005f66cd:;
    left = edx;
    right = edx;
    left &= right;
    right = 0; // original 005f66cd test edx, edx
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f66e0; // original 005f66cf jle 0x5f66e0
    left = load32(frame - 0x30u);
    right = 0xfu; // original 005f66d1 cmp dword ptr [ebp - 0x30], 0xf
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f66e4;          // original 005f66d5 jl 0x5f66e4
    store32(frame - 0x30u, 0xfu); // original 005f66d7 mov dword ptr [ebp - 0x30], 0xf
    goto L_005f66e4;              // original 005f66de jmp 0x5f66e4
L_005f66e0:;
    store32(frame - 0x30u,
            (load32(frame - 0x30u)) & (0x0u)); // original 005f66e0 and dword ptr [ebp - 0x30], 0
L_005f66e4:;
    left = ecx;
    right = 0xfu; // original 005f66e4 cmp ecx, 0xf
    if (static_cast<int32_t>(left) >= static_cast<int32_t>(right))
        goto L_005f66ed; // original 005f66e7 jge 0x5f66ed
    edx = ecx;           // original 005f66e9 mov edx, ecx
    goto L_005f66f0;     // original 005f66eb jmp 0x5f66f0
L_005f66ed:;
    pending = 0xfu; // original 005f66ed push 0xf
    edx = pending;  // original 005f66ef pop edx
L_005f66f0:;
    left = edx;
    right = edx;
    left &= right;
    right = 0; // original 005f66f0 test edx, edx
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f66fe; // original 005f66f2 jle 0x5f66fe
    left = ecx;
    right = 0xfu; // original 005f66f4 cmp ecx, 0xf
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f6700; // original 005f66f7 jl 0x5f6700
    pending = 0xfu;      // original 005f66f9 push 0xf
    ecx = pending;       // original 005f66fb pop ecx
    goto L_005f6700;     // original 005f66fc jmp 0x5f6700
L_005f66fe:;
    ecx = 0u; // original 005f66fe xor ecx, ecx
L_005f6700:;
    ecx =
        (ecx & 0xffffff00u) | ((((ecx & 0xffu)) << (0x4u)) & 0xffu); // original 005f6700 shl cl, 4
    ecx = (ecx & 0xffffff00u) | ((((ecx & 0xffu)) | (load8(frame - 0x30u))) &
                                 0xffu); // original 005f6703 or cl, byte ptr [ebp - 0x30]
    store8(edi, (ecx & 0xffu));          // original 005f6706 mov byte ptr [edi], cl
    ecx = load32(frame - 0x20u);         // original 005f6708 mov ecx, dword ptr [ebp - 0x20]
    store32(args + 4u,
            (load32(args + 4u)) + (ecx)); // original 005f670b add dword ptr [ebp + 0xc], ecx
    edi = (edi) + (load32(args + 0u));    // original 005f670e add edi, dword ptr [ebp + 8]
    ebx = (ebx) + (ecx);                  // original 005f6711 add ebx, ecx
    eax = (eax) + (ecx);                  // original 005f6713 add eax, ecx
    store32(frame - 0x4u, load32(frame - 0x4u) + 1u); // original 005f6715 inc dword ptr [ebp - 4]
    ecx = load32(frame - 0x4u); // original 005f6718 mov ecx, dword ptr [ebp - 4]
    left = ecx;
    right = load32(esi + 0x68u); // original 005f671b cmp ecx, dword ptr [esi + 0x68]
    store32(frame - 0x8u, ebx);  // original 005f671e mov dword ptr [ebp - 8], ebx
    if (left < right)
        goto L_005f65b3; // original 005f6721 jb 0x5f65b3
L_005f6727:;
    eax = load32(esi + 0x7cu); // original 005f6727 mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f672a mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f672d fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f6730 pop edi
    ;                                   // C++ ABI restore ownership. // original 005f6731 pop esi
    ;                                   // C++ ABI restore ownership. // original 005f6732 pop ebx
    ;                                   // C++ frame ownership. // original 005f6733 leave
    return eax;                         // original 005f6734 ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f6496(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f6496\n\taddl $8,%esp\n\tretl $12");
}

// Complete original 005f6737..005f699e: signed V8U8; original access widths/order retained.
extern "C" u32 recovered_005f6737(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x80];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x80u;
    ;          // C++ frame and ABI save ownership. // original 005f6737 mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f6739 push ebp
    ;          // C++ frame and ABI save ownership. // original 005f673a mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f673c sub esp, 0x4c
    ;          // C++ frame and ABI save ownership. // original 005f673f push ebx
    ;          // C++ frame and ABI save ownership. // original 005f6740 push esi
    esi = ecx; // original 005f6741 mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f6743 cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f6747 push edi
    if (left == right)
        goto L_005f6755;         // original 005f6748 je 0x5f6755
    pending = load32(args + 8u); // original 005f674a push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f674d call 0x5f0da1
    store32(args + 8u, eax); // original 005f6752 mov dword ptr [ebp + 0x10], eax
L_005f6755:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f6755 cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f6768;         // original 005f6759 je 0x5f6768
    pending = load32(args + 8u); // original 005f675b push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f675e mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f6760 call 0x5f22d6
    store32(args + 8u, eax); // original 005f6765 mov dword ptr [ebp + 0x10], eax
L_005f6768:;
    eax = load32(args + 0u);                     // original 005f6768 mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f676b fldz
    ebx = load32(esi + 0x68u); // original 005f676d mov ebx, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f6770 fstp dword ptr [ebp - 0x4c]
    edx = load32(esi + 0x60u);          // original 005f6773 mov edx, dword ptr [esi + 0x60]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f6776 fldz
    edi = load32(esi + 0x64u); // original 005f6778 mov edi, dword ptr [esi + 0x64]
    edx = (edx) * (eax);       // original 005f677b imul edx, eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f677e fstp dword ptr [ebp - 0x48]
    store32(args + 0u, eax);            // original 005f6781 mov dword ptr [ebp + 8], eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f6784 and dword ptr [ebp + 8], 1
    ecx = ebx + 0xffffffffu;               // original 005f6788 lea ecx, [ebx - 1]
    ecx = (ecx) * (load32(args + 0u));     // original 005f678b imul ecx, dword ptr [ebp + 8]
    edx = edx + ecx * 2u;                  // original 005f678f lea edx, [edx + ecx*2]
    ecx = load32(args + 4u);               // original 005f6792 mov ecx, dword ptr [ebp + 0xc]
    edi = (edi) * (ecx);                   // original 005f6795 imul edi, ecx
    eax = (eax) & (0x3u);                  // original 005f6798 and eax, 3
    ecx = (ecx) & (0x3u);                  // original 005f679b and ecx, 3
    edx = (edx) + (edi);                   // original 005f679e add edx, edi
    edx = (edx) + (load32(esi + 0x20u));   // original 005f67a0 add edx, dword ptr [esi + 0x20]
    left = load32(args + 0u);
    right = 0x0u;               // original 005f67a3 cmp dword ptr [ebp + 8], 0
    eax = ecx + eax * 8u;       // original 005f67a7 lea eax, [ecx + eax*8]
    ecx = load32(esi + 0x34u);  // original 005f67aa mov ecx, dword ptr [esi + 0x34]
    eax = ecx + eax * 4u;       // original 005f67ad lea eax, [ecx + eax*4]
    store32(frame - 0x4u, edx); // original 005f67b0 mov dword ptr [ebp - 4], edx
    store32(frame - 0xcu, eax); // original 005f67b3 mov dword ptr [ebp - 0xc], eax
    if (left != right)
        goto L_005f67c2;     // original 005f67b6 jne 0x5f67c2
    edi = 0u;                // original 005f67b8 xor edi, edi
    ebx = 0u;                // original 005f67ba xor ebx, ebx
    edi = edi + 1u;          // original 005f67bc inc edi
    store32(args + 4u, edi); // original 005f67bd mov dword ptr [ebp + 0xc], edi
    goto L_005f67ca;         // original 005f67c0 jmp 0x5f67ca
L_005f67c2:;
    ebx = ebx - 1u; // original 005f67c2 dec ebx
    store32(args + 4u, (load32(args + 4u)) |
                           (0xffffffffu)); // original 005f67c3 or dword ptr [ebp + 0xc], 0xffffffff
    edi = load32(args + 4u);               // original 005f67c7 mov edi, dword ptr [ebp + 0xc]
L_005f67ca:;
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 0u)
                     : "st", "memory"); // original 005f67ca fnstcw word ptr [ebp + 8]
    eax = load32(args + 0u);            // original 005f67cd mov eax, dword ptr [ebp + 8]
    eax = (eax) | (0xc00u);             // original 005f67d0 or eax, 0xc00
    store32(frame - 0x8u, eax);         // original 005f67d5 mov dword ptr [ebp - 8], eax
    __asm__ volatile("fldcw (%0)" ::"r"(frame - 0x8u)
                     : "st", "memory"); // original 005f67d8 fldcw word ptr [ebp - 8]
    eax = load32(args + 0u);            // original 005f67db mov eax, dword ptr [ebp + 8]
    store32(esi + 0x7cu, eax);          // original 005f67de mov dword ptr [esi + 0x7c], eax
    left = load32(esi + 0x5cu);
    right = 0x0u; // original 005f67e1 cmp dword ptr [esi + 0x5c], 0
    if (left == right)
        goto L_005f67f1;         // original 005f67e5 je 0x5f67f1
    pending = load32(args + 8u); // original 005f67e7 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f67ea mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f67ec call 0x5f25f2
L_005f67f1:;
    store32(args + 0u,
            (load32(args + 0u)) & (0x0u)); // original 005f67f1 and dword ptr [ebp + 8], 0
    left = load32(esi + 0x68u);
    right = 0x0u; // original 005f67f5 cmp dword ptr [esi + 0x68], 0
    if (left <= right)
        goto L_005f698e;               // original 005f67f9 jbe 0x5f698e
    eax = edi + edi;                   // original 005f67ff lea eax, [edi + edi]
    ecx = edi;                         // original 005f6802 mov ecx, edi
    store32(frame - 0x1cu, eax);       // original 005f6804 mov dword ptr [ebp - 0x1c], eax
    eax = ebx;                         // original 005f6807 mov eax, ebx
    edi = (edi) + (ebx);               // original 005f6809 add edi, ebx
    ebx = (ebx) - (load32(args + 4u)); // original 005f680b sub ebx, dword ptr [ebp + 0xc]
    ecx = (ecx) << (0x4u);             // original 005f680e shl ecx, 4
    eax = (eax) << (0x4u);             // original 005f6811 shl eax, 4
    edi = (edi) << (0x4u);             // original 005f6814 shl edi, 4
    store32(frame - 0x8u, ecx);        // original 005f6817 mov dword ptr [ebp - 8], ecx
    ebx = (ebx) << (0x4u);             // original 005f681a shl ebx, 4
L_005f681d:;
    ecx = load32(args + 0u);    // original 005f681d mov ecx, dword ptr [ebp + 8]
    edx = load32(frame - 0xcu); // original 005f6820 mov edx, dword ptr [ebp - 0xc]
    ecx = (ecx) & (0x3u);       // original 005f6823 and ecx, 3
    __asm__ volatile("flds (%0)" ::"r"(edx + ecx * 4u)
                     : "st", "memory"); // original 005f6826 fld dword ptr [edx + ecx*4]
    ecx = load32(args + 8u);            // original 005f6829 mov ecx, dword ptr [ebp + 0x10]
    __asm__ volatile("fsts (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f682c fst dword ptr [ebp - 0x14]
    ecx = (ecx) + (eax);                // original 005f682f add ecx, eax
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f6831 fld dword ptr [ebp - 0x4c]
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f6834 fadd dword ptr [ecx]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df434))
                     : "st", "memory"); // original 005f6836 fmul dword ptr [0x6df434]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f683c fstp dword ptr [ebp - 0x3c]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f683f fld dword ptr [ebp - 0x48]
    __asm__ volatile("fadds (%0)" ::"r"(ecx + 0x4u)
                     : "st", "memory"); // original 005f6842 fadd dword ptr [ecx + 4]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df434))
                     : "st", "memory"); // original 005f6845 fmul dword ptr [0x6df434]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f684b fstp dword ptr [ebp - 0x38]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f684e fld dword ptr [ebp - 0x3c]
    __asm__ volatile("fadd %%st(1)" ::: "st", "memory"); // original 005f6851 fadd st(1)
    __asm__ volatile("fstps (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f6853 fstp dword ptr [ebp + 0xc]
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f6856 fstp st(0)
    __asm__ volatile("flds (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f6858 fld dword ptr [ebp + 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f685b fistp dword ptr [ebp - 0x10]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f685e fld dword ptr [ebp - 0x38]
    ecx = load32(frame - 0x10u);        // original 005f6861 mov ecx, dword ptr [ebp - 0x10]
    __asm__ volatile("fadds (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f6864 fadd dword ptr [ebp - 0x14]
    store32(frame - 0x2cu, ecx);        // original 005f6867 mov dword ptr [ebp - 0x2c], ecx
    __asm__ volatile("fstps (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f686a fstp dword ptr [ebp + 0xc]
    __asm__ volatile("flds (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f686d fld dword ptr [ebp + 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f6870 fistp dword ptr [ebp - 0x18]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f6873 cmp dword ptr [esi + 0x5c], 0
    edx = load32(frame - 0x18u); // original 005f6877 mov edx, dword ptr [ebp - 0x18]
    store32(frame - 0x28u, edx); // original 005f687a mov dword ptr [ebp - 0x28], edx
    if (left == right)
        goto L_005f691d; // original 005f687d je 0x5f691d
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df430))
                     : "st", "memory"); // original 005f6883 fld dword ptr [0x6df430]
    ecx = load32(esi + 0x5cu);          // original 005f6889 mov ecx, dword ptr [esi + 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x2cu)
                     : "st", "memory"); // original 005f688c fild dword ptr [ebp - 0x2c]
    ecx = ecx + ebx + 0x10u;            // original 005f688f lea ecx, [ecx + ebx + 0x10]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f6893 fsubr dword ptr [ebp - 0x3c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6896 fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f6898 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f689e fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f68a0 fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f68a2 fstp dword ptr [ecx]
    ecx = load32(esi + 0x5cu);          // original 005f68a4 mov ecx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f68a7 fld dword ptr [0x6df418]
    ecx = eax + ecx + 0x10u;            // original 005f68ad lea ecx, [eax + ecx + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f68b1 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f68b3 fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f68b5 fstp dword ptr [ecx]
    ecx = load32(esi + 0x5cu);          // original 005f68b7 mov ecx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f68ba fld dword ptr [0x6be980]
    ecx = ecx + edi + 0x10u;            // original 005f68c0 lea ecx, [ecx + edi + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f68c4 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f68c6 fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f68c8 fstp dword ptr [ecx]
    ecx = load32(esi + 0x5cu);          // original 005f68ca mov ecx, dword ptr [esi + 0x5c]
    ecx = ecx + ebx + 0x14u;            // original 005f68cd lea ecx, [ecx + ebx + 0x14]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f68d1 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f68d7 fstp dword ptr [ebp - 0x4c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x28u)
                     : "st", "memory"); // original 005f68da fild dword ptr [ebp - 0x28]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f68dd fsubr dword ptr [ebp - 0x38]
    __asm__ volatile("fmulp %%st(1)" ::: "st", "memory"); // original 005f68e0 fmulp st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f68e2 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f68e8 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f68ea fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f68ec fstp dword ptr [ecx]
    ecx = load32(esi + 0x5cu);          // original 005f68ee mov ecx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f68f1 fld dword ptr [0x6df418]
    ecx = eax + ecx + 0x14u;            // original 005f68f7 lea ecx, [eax + ecx + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f68fb fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f68fd fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f68ff fstp dword ptr [ecx]
    ecx = load32(esi + 0x5cu);          // original 005f6901 mov ecx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f6904 fld dword ptr [0x6be980]
    ecx = ecx + edi + 0x14u;            // original 005f690a lea ecx, [ecx + edi + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f690e fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f6910 fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f6912 fstp dword ptr [ecx]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f6914 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f691a fstp dword ptr [ebp - 0x48]
L_005f691d:;
    left = load32(frame - 0x2cu);
    right = 0x7fu; // original 005f691d cmp dword ptr [ebp - 0x2c], 0x7f
    if (static_cast<int32_t>(left) >= static_cast<int32_t>(right))
        goto L_005f6928;         // original 005f6921 jge 0x5f6928
    ecx = load32(frame - 0x2cu); // original 005f6923 mov ecx, dword ptr [ebp - 0x2c]
    goto L_005f692b;             // original 005f6926 jmp 0x5f692b
L_005f6928:;
    pending = 0x7fu; // original 005f6928 push 0x7f
    ecx = pending;   // original 005f692a pop ecx
L_005f692b:;
    left = ecx;
    right = 0xffffff81u; // original 005f692b cmp ecx, -0x7f
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f693f; // original 005f692e jle 0x5f693f
    left = load32(frame - 0x2cu);
    right = 0x7fu; // original 005f6930 cmp dword ptr [ebp - 0x2c], 0x7f
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f6946;           // original 005f6934 jl 0x5f6946
    store32(frame - 0x2cu, 0x7fu); // original 005f6936 mov dword ptr [ebp - 0x2c], 0x7f
    goto L_005f6946;               // original 005f693d jmp 0x5f6946
L_005f693f:;
    store32(frame - 0x2cu, 0xffffff81u); // original 005f693f mov dword ptr [ebp - 0x2c], 0xffffff81
L_005f6946:;
    left = edx;
    right = 0x7fu; // original 005f6946 cmp edx, 0x7f
    if (static_cast<int32_t>(left) >= static_cast<int32_t>(right))
        goto L_005f694f; // original 005f6949 jge 0x5f694f
    ecx = edx;           // original 005f694b mov ecx, edx
    goto L_005f6952;     // original 005f694d jmp 0x5f6952
L_005f694f:;
    pending = 0x7fu; // original 005f694f push 0x7f
    ecx = pending;   // original 005f6951 pop ecx
L_005f6952:;
    left = ecx;
    right = 0xffffff81u; // original 005f6952 cmp ecx, -0x7f
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f6960; // original 005f6955 jle 0x5f6960
    left = edx;
    right = 0x7fu; // original 005f6957 cmp edx, 0x7f
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f6963; // original 005f695a jl 0x5f6963
    pending = 0x7fu;     // original 005f695c push 0x7f
    goto L_005f6962;     // original 005f695e jmp 0x5f6962
L_005f6960:;
    pending = 0xffffff81u; // original 005f6960 push -0x7f
L_005f6962:;
    edx = pending; // original 005f6962 pop edx
L_005f6963:;
    ecx = (ecx & 0xffff0000u) |
          ((load8(frame - 0x2cu)) & 0xffffu); // original 005f6963 movzx cx, byte ptr [ebp - 0x2c]
    eax = (eax) + (load32(frame - 0x8u));     // original 005f6968 add eax, dword ptr [ebp - 8]
    ebx = (ebx) + (load32(frame - 0x8u));     // original 005f696b add ebx, dword ptr [ebp - 8]
    edi = (edi) + (load32(frame - 0x8u));     // original 005f696e add edi, dword ptr [ebp - 8]
    ecx = (ecx & 0xffff00ffu) | ((((edx & 0xffu)) & 255u) << 8); // original 005f6971 mov ch, dl
    edx = load32(frame - 0x4u);    // original 005f6973 mov edx, dword ptr [ebp - 4]
    store16(edx, (ecx & 0xffffu)); // original 005f6976 mov word ptr [edx], cx
    ecx = load32(frame - 0x1cu);   // original 005f6979 mov ecx, dword ptr [ebp - 0x1c]
    store32(frame - 0x4u,
            (load32(frame - 0x4u)) + (ecx));    // original 005f697c add dword ptr [ebp - 4], ecx
    store32(args + 0u, load32(args + 0u) + 1u); // original 005f697f inc dword ptr [ebp + 8]
    ecx = load32(args + 0u);                    // original 005f6982 mov ecx, dword ptr [ebp + 8]
    left = ecx;
    right = load32(esi + 0x68u); // original 005f6985 cmp ecx, dword ptr [esi + 0x68]
    if (left < right)
        goto L_005f681d; // original 005f6988 jb 0x5f681d
L_005f698e:;
    eax = load32(esi + 0x7cu); // original 005f698e mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f6991 mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f6994 fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f6997 pop edi
    ;                                   // C++ ABI restore ownership. // original 005f6998 pop esi
    ;                                   // C++ ABI restore ownership. // original 005f6999 pop ebx
    ;                                   // C++ frame ownership. // original 005f699a leave
    return eax;                         // original 005f699b ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f6737(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f6737\n\taddl $8,%esp\n\tretl $12");
}

// Complete original 005f6a01..005f6d1c: signed X8L8V8U8; original access widths/order retained.
extern "C" u32 recovered_005f6a01(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x80];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x80u;
    ;          // C++ frame and ABI save ownership. // original 005f6a01 mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f6a03 push ebp
    ;          // C++ frame and ABI save ownership. // original 005f6a04 mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f6a06 sub esp, 0x54
    ;          // C++ frame and ABI save ownership. // original 005f6a09 push ebx
    ;          // C++ frame and ABI save ownership. // original 005f6a0a push esi
    esi = ecx; // original 005f6a0b mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f6a0d cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f6a11 push edi
    if (left == right)
        goto L_005f6a1f;         // original 005f6a12 je 0x5f6a1f
    pending = load32(args + 8u); // original 005f6a14 push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f6a17 call 0x5f0da1
    store32(args + 8u, eax); // original 005f6a1c mov dword ptr [ebp + 0x10], eax
L_005f6a1f:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f6a1f cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f6a32;         // original 005f6a23 je 0x5f6a32
    pending = load32(args + 8u); // original 005f6a25 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f6a28 mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f6a2a call 0x5f22d6
    store32(args + 8u, eax); // original 005f6a2f mov dword ptr [ebp + 0x10], eax
L_005f6a32:;
    eax = load32(args + 0u);                     // original 005f6a32 mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f6a35 fldz
    ebx = load32(esi + 0x68u); // original 005f6a37 mov ebx, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f6a3a fstp dword ptr [ebp - 0x54]
    edx = load32(esi + 0x60u);          // original 005f6a3d mov edx, dword ptr [esi + 0x60]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f6a40 fldz
    edi = load32(esi + 0x64u); // original 005f6a42 mov edi, dword ptr [esi + 0x64]
    edx = (edx) * (eax);       // original 005f6a45 imul edx, eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory");          // original 005f6a48 fstp dword ptr [ebp - 0x50]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f6a4b fldz
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f6a4d fstp dword ptr [ebp - 0x48]
    store32(args + 0u, eax);            // original 005f6a50 mov dword ptr [ebp + 8], eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f6a53 and dword ptr [ebp + 8], 1
    ecx = ebx + 0xffffffffu;               // original 005f6a57 lea ecx, [ebx - 1]
    ecx = (ecx) * (load32(args + 0u));     // original 005f6a5a imul ecx, dword ptr [ebp + 8]
    ecx = edx + ecx * 2u;                  // original 005f6a5e lea ecx, [edx + ecx*2]
    edx = load32(args + 4u);               // original 005f6a61 mov edx, dword ptr [ebp + 0xc]
    edi = (edi) * (edx);                   // original 005f6a64 imul edi, edx
    ecx = (ecx) + (edi);                   // original 005f6a67 add ecx, edi
    ecx = (ecx) + (load32(esi + 0x20u));   // original 005f6a69 add ecx, dword ptr [esi + 0x20]
    eax = (eax) & (0x3u);                  // original 005f6a6c and eax, 3
    edx = (edx) & (0x3u);                  // original 005f6a6f and edx, 3
    left = load32(args + 0u);
    right = 0x0u;               // original 005f6a72 cmp dword ptr [ebp + 8], 0
    store32(frame - 0x4u, ecx); // original 005f6a76 mov dword ptr [ebp - 4], ecx
    ecx = load32(esi + 0x34u);  // original 005f6a79 mov ecx, dword ptr [esi + 0x34]
    eax = edx + eax * 8u;       // original 005f6a7c lea eax, [edx + eax*8]
    eax = ecx + eax * 4u;       // original 005f6a7f lea eax, [ecx + eax*4]
    store32(frame - 0xcu, eax); // original 005f6a82 mov dword ptr [ebp - 0xc], eax
    if (left != right)
        goto L_005f6a91;     // original 005f6a85 jne 0x5f6a91
    edi = 0u;                // original 005f6a87 xor edi, edi
    ebx = 0u;                // original 005f6a89 xor ebx, ebx
    edi = edi + 1u;          // original 005f6a8b inc edi
    store32(args + 4u, edi); // original 005f6a8c mov dword ptr [ebp + 0xc], edi
    goto L_005f6a99;         // original 005f6a8f jmp 0x5f6a99
L_005f6a91:;
    ebx = ebx - 1u; // original 005f6a91 dec ebx
    store32(args + 4u, (load32(args + 4u)) |
                           (0xffffffffu)); // original 005f6a92 or dword ptr [ebp + 0xc], 0xffffffff
    edi = load32(args + 4u);               // original 005f6a96 mov edi, dword ptr [ebp + 0xc]
L_005f6a99:;
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 0u)
                     : "st", "memory"); // original 005f6a99 fnstcw word ptr [ebp + 8]
    eax = load32(args + 0u);            // original 005f6a9c mov eax, dword ptr [ebp + 8]
    eax = (eax) | (0xc00u);             // original 005f6a9f or eax, 0xc00
    store32(frame - 0x8u, eax);         // original 005f6aa4 mov dword ptr [ebp - 8], eax
    __asm__ volatile("fldcw (%0)" ::"r"(frame - 0x8u)
                     : "st", "memory"); // original 005f6aa7 fldcw word ptr [ebp - 8]
    eax = load32(args + 0u);            // original 005f6aaa mov eax, dword ptr [ebp + 8]
    store32(esi + 0x7cu, eax);          // original 005f6aad mov dword ptr [esi + 0x7c], eax
    left = load32(esi + 0x5cu);
    right = 0x0u; // original 005f6ab0 cmp dword ptr [esi + 0x5c], 0
    if (left == right)
        goto L_005f6ac0;         // original 005f6ab4 je 0x5f6ac0
    pending = load32(args + 8u); // original 005f6ab6 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f6ab9 mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f6abb call 0x5f25f2
L_005f6ac0:;
    store32(args + 0u,
            (load32(args + 0u)) & (0x0u)); // original 005f6ac0 and dword ptr [ebp + 8], 0
    left = load32(esi + 0x68u);
    right = 0x0u; // original 005f6ac4 cmp dword ptr [esi + 0x68], 0
    if (left <= right)
        goto L_005f6d0c;               // original 005f6ac8 jbe 0x5f6d0c
    eax = edi + edi;                   // original 005f6ace lea eax, [edi + edi]
    ecx = edi;                         // original 005f6ad1 mov ecx, edi
    ecx = (ecx) << (0x4u);             // original 005f6ad3 shl ecx, 4
    store32(frame - 0x20u, eax);       // original 005f6ad6 mov dword ptr [ebp - 0x20], eax
    eax = ebx;                         // original 005f6ad9 mov eax, ebx
    edi = (edi) + (ebx);               // original 005f6adb add edi, ebx
    ebx = (ebx) - (load32(args + 4u)); // original 005f6add sub ebx, dword ptr [ebp + 0xc]
    store32(frame - 0x24u, ecx);       // original 005f6ae0 mov dword ptr [ebp - 0x24], ecx
    ecx = load32(args + 8u);           // original 005f6ae3 mov ecx, dword ptr [ebp + 0x10]
    eax = (eax) << (0x4u);             // original 005f6ae6 shl eax, 4
    edi = (edi) << (0x4u);             // original 005f6ae9 shl edi, 4
    ebx = (ebx) << (0x4u);             // original 005f6aec shl ebx, 4
    ecx = eax + ecx + 0xcu;            // original 005f6aef lea ecx, [eax + ecx + 0xc]
    store32(frame - 0x8u, ebx);        // original 005f6af3 mov dword ptr [ebp - 8], ebx
    store32(args + 8u, ecx);           // original 005f6af6 mov dword ptr [ebp + 0x10], ecx
L_005f6af9:;
    ecx = load32(args + 0u);    // original 005f6af9 mov ecx, dword ptr [ebp + 8]
    edx = load32(frame - 0xcu); // original 005f6afc mov edx, dword ptr [ebp - 0xc]
    ecx = (ecx) & (0x3u);       // original 005f6aff and ecx, 3
    __asm__ volatile("flds (%0)" ::"r"(edx + ecx * 4u)
                     : "st", "memory"); // original 005f6b02 fld dword ptr [edx + ecx*4]
    ecx = load32(args + 8u);            // original 005f6b05 mov ecx, dword ptr [ebp + 0x10]
    __asm__ volatile("fsts (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f6b08 fst dword ptr [ebp + 0xc]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f6b0b fld dword ptr [ebp - 0x54]
    __asm__ volatile("fadds (%0)" ::"r"(ecx + 0xfffffff4u)
                     : "st", "memory"); // original 005f6b0e fadd dword ptr [ecx - 0xc]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bc894))
                     : "st", "memory"); // original 005f6b11 fmul dword ptr [0x6bc894]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f6b17 fstp dword ptr [ebp - 0x44]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f6b1a fld dword ptr [ebp - 0x50]
    __asm__ volatile("fadds (%0)" ::"r"(ecx + 0xfffffff8u)
                     : "st", "memory"); // original 005f6b1d fadd dword ptr [ecx - 8]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bc894))
                     : "st", "memory"); // original 005f6b20 fmul dword ptr [0x6bc894]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f6b26 fstp dword ptr [ebp - 0x40]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f6b29 fld dword ptr [ebp - 0x48]
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f6b2c fadd dword ptr [ecx]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df408))
                     : "st", "memory"); // original 005f6b2e fmul dword ptr [0x6df408]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f6b34 fstp dword ptr [ebp - 0x38]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f6b37 fld dword ptr [ebp - 0x44]
    __asm__ volatile("fadd %%st(1)" ::: "st", "memory"); // original 005f6b3a fadd st(1)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f6b3c fstp dword ptr [ebp - 0x10]
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f6b3f fstp st(0)
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f6b41 fld dword ptr [ebp - 0x10]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f6b44 fistp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f6b47 fld dword ptr [ebp - 0x40]
    ecx = load32(frame - 0x14u);        // original 005f6b4a mov ecx, dword ptr [ebp - 0x14]
    __asm__ volatile("fadds (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f6b4d fadd dword ptr [ebp + 0xc]
    store32(frame - 0x34u, ecx);        // original 005f6b50 mov dword ptr [ebp - 0x34], ecx
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f6b53 fstp dword ptr [ebp - 0x10]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f6b56 fld dword ptr [ebp - 0x10]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f6b59 fistp dword ptr [ebp - 0x18]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f6b5c fld dword ptr [ebp - 0x38]
    ecx = load32(frame - 0x18u);        // original 005f6b5f mov ecx, dword ptr [ebp - 0x18]
    __asm__ volatile("fadds (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f6b62 fadd dword ptr [ebp + 0xc]
    store32(frame - 0x30u, ecx);        // original 005f6b65 mov dword ptr [ebp - 0x30], ecx
    __asm__ volatile("fstps (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f6b68 fstp dword ptr [ebp + 0xc]
    __asm__ volatile("flds (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f6b6b fld dword ptr [ebp + 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x1cu)
                     : "st", "memory"); // original 005f6b6e fistp dword ptr [ebp - 0x1c]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f6b71 cmp dword ptr [esi + 0x5c], 0
    edx = load32(frame - 0x1cu); // original 005f6b75 mov edx, dword ptr [ebp - 0x1c]
    store32(frame - 0x28u, edx); // original 005f6b78 mov dword ptr [ebp - 0x28], edx
    if (left == right)
        goto L_005f6c6c; // original 005f6b7b je 0x5f6c6c
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006c0c2c))
                     : "st", "memory"); // original 005f6b81 fld dword ptr [0x6c0c2c]
    edx = load32(esi + 0x5cu);          // original 005f6b87 mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f6b8a fild dword ptr [ebp - 0x34]
    edx = edx + ebx + 0x10u;            // original 005f6b8d lea edx, [edx + ebx + 0x10]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f6b91 fsubr dword ptr [ebp - 0x44]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6b94 fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f6b96 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6b9c fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6b9e fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6ba0 fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f6ba2 mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f6ba5 fld dword ptr [0x6df418]
    edx = edx + eax + 0x10u;            // original 005f6bab lea edx, [edx + eax + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6baf fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6bb1 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6bb3 fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f6bb5 mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f6bb8 fld dword ptr [0x6be980]
    edx = edx + edi + 0x10u;            // original 005f6bbe lea edx, [edx + edi + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6bc2 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6bc4 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6bc6 fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f6bc8 mov edx, dword ptr [esi + 0x5c]
    edx = edx + ebx + 0x14u;            // original 005f6bcb lea edx, [edx + ebx + 0x14]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f6bcf fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f6bd5 fstp dword ptr [ebp - 0x54]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f6bd8 fild dword ptr [ebp - 0x30]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f6bdb fsubr dword ptr [ebp - 0x40]
    __asm__ volatile("fmulp %%st(1)" ::: "st", "memory"); // original 005f6bde fmulp st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f6be0 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6be6 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6be8 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6bea fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f6bec mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f6bef fld dword ptr [0x6df418]
    edx = edx + eax + 0x14u;            // original 005f6bf5 lea edx, [edx + eax + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6bf9 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6bfb fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6bfd fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f6bff mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f6c02 fld dword ptr [0x6be980]
    edx = edx + edi + 0x14u;            // original 005f6c08 lea edx, [edx + edi + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6c0c fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6c0e fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6c10 fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f6c12 mov edx, dword ptr [esi + 0x5c]
    edx = edx + ebx + 0x1cu;            // original 005f6c15 lea edx, [edx + ebx + 0x1c]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f6c19 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f6c1f fstp dword ptr [ebp - 0x50]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x28u)
                     : "st", "memory"); // original 005f6c22 fild dword ptr [ebp - 0x28]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f6c25 fsubr dword ptr [ebp - 0x38]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df404))
                     : "st", "memory"); // original 005f6c28 fmul dword ptr [0x6df404]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f6c2e fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6c34 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6c36 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6c38 fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f6c3a mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f6c3d fld dword ptr [0x6df418]
    edx = edx + eax + 0x1cu;            // original 005f6c43 lea edx, [edx + eax + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6c47 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6c49 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6c4b fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f6c4d mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f6c50 fld dword ptr [0x6be980]
    edx = edx + edi + 0x1cu;            // original 005f6c56 lea edx, [edx + edi + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6c5a fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6c5c fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f6c5e fstp dword ptr [edx]
    edx = load32(frame - 0x28u);        // original 005f6c60 mov edx, dword ptr [ebp - 0x28]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f6c63 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f6c69 fstp dword ptr [ebp - 0x48]
L_005f6c6c:;
    ebx = load32(frame - 0x34u); // original 005f6c6c mov ebx, dword ptr [ebp - 0x34]
    left = ebx;
    right = 0xfu; // original 005f6c6f cmp ebx, 0xf
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f6c77; // original 005f6c72 jl 0x5f6c77
    pending = 0xfu;      // original 005f6c74 push 0xf
    ebx = pending;       // original 005f6c76 pop ebx
L_005f6c77:;
    left = ebx;
    right = 0xfffffff1u; // original 005f6c77 cmp ebx, -0xf
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f6c8b; // original 005f6c7a jle 0x5f6c8b
    left = load32(frame - 0x34u);
    right = 0xfu; // original 005f6c7c cmp dword ptr [ebp - 0x34], 0xf
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f6c92;          // original 005f6c80 jl 0x5f6c92
    store32(frame - 0x34u, 0xfu); // original 005f6c82 mov dword ptr [ebp - 0x34], 0xf
    goto L_005f6c92;              // original 005f6c89 jmp 0x5f6c92
L_005f6c8b:;
    store32(frame - 0x34u, 0xfffffff1u); // original 005f6c8b mov dword ptr [ebp - 0x34], 0xfffffff1
L_005f6c92:;
    left = ecx;
    right = 0xfu; // original 005f6c92 cmp ecx, 0xf
    if (static_cast<int32_t>(left) >= static_cast<int32_t>(right))
        goto L_005f6c9b; // original 005f6c95 jge 0x5f6c9b
    ebx = ecx;           // original 005f6c97 mov ebx, ecx
    goto L_005f6c9e;     // original 005f6c99 jmp 0x5f6c9e
L_005f6c9b:;
    pending = 0xfu; // original 005f6c9b push 0xf
    ebx = pending;  // original 005f6c9d pop ebx
L_005f6c9e:;
    left = ebx;
    right = 0xfffffff1u; // original 005f6c9e cmp ebx, -0xf
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f6cac; // original 005f6ca1 jle 0x5f6cac
    left = ecx;
    right = 0xfu; // original 005f6ca3 cmp ecx, 0xf
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f6caf; // original 005f6ca6 jl 0x5f6caf
    pending = 0xfu;      // original 005f6ca8 push 0xf
    goto L_005f6cae;     // original 005f6caa jmp 0x5f6cae
L_005f6cac:;
    pending = 0xfffffff1u; // original 005f6cac push -0xf
L_005f6cae:;
    ecx = pending; // original 005f6cae pop ecx
L_005f6caf:;
    left = edx;
    right = 0x3fu; // original 005f6caf cmp edx, 0x3f
    if (static_cast<int32_t>(left) >= static_cast<int32_t>(right))
        goto L_005f6cb8; // original 005f6cb2 jge 0x5f6cb8
    ebx = edx;           // original 005f6cb4 mov ebx, edx
    goto L_005f6cbb;     // original 005f6cb6 jmp 0x5f6cbb
L_005f6cb8:;
    pending = 0x3fu; // original 005f6cb8 push 0x3f
    ebx = pending;   // original 005f6cba pop ebx
L_005f6cbb:;
    left = ebx;
    right = 0xffffffc1u; // original 005f6cbb cmp ebx, -0x3f
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f6cc9; // original 005f6cbe jle 0x5f6cc9
    left = edx;
    right = 0x3fu; // original 005f6cc0 cmp edx, 0x3f
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f6ccc; // original 005f6cc3 jl 0x5f6ccc
    pending = 0x3fu;     // original 005f6cc5 push 0x3f
    goto L_005f6ccb;     // original 005f6cc7 jmp 0x5f6ccb
L_005f6cc9:;
    pending = 0xffffffc1u; // original 005f6cc9 push -0x3f
L_005f6ccb:;
    edx = pending; // original 005f6ccb pop edx
L_005f6ccc:;
    ebx = load32(frame - 0x8u);    // original 005f6ccc mov ebx, dword ptr [ebp - 8]
    ecx = (ecx) & (0x1fu);         // original 005f6ccf and ecx, 0x1f
    edx = (edx) << (0x5u);         // original 005f6cd2 shl edx, 5
    ecx = (ecx) | (edx);           // original 005f6cd5 or ecx, edx
    edx = load32(frame - 0x34u);   // original 005f6cd7 mov edx, dword ptr [ebp - 0x34]
    ecx = (ecx) << (0x5u);         // original 005f6cda shl ecx, 5
    edx = (edx) & (0x1fu);         // original 005f6cdd and edx, 0x1f
    ecx = (ecx) | (edx);           // original 005f6ce0 or ecx, edx
    edx = load32(frame - 0x4u);    // original 005f6ce2 mov edx, dword ptr [ebp - 4]
    store16(edx, (ecx & 0xffffu)); // original 005f6ce5 mov word ptr [edx], cx
    ecx = load32(frame - 0x20u);   // original 005f6ce8 mov ecx, dword ptr [ebp - 0x20]
    store32(frame - 0x4u,
            (load32(frame - 0x4u)) + (ecx)); // original 005f6ceb add dword ptr [ebp - 4], ecx
    ecx = load32(frame - 0x24u);             // original 005f6cee mov ecx, dword ptr [ebp - 0x24]
    store32(args + 8u,
            (load32(args + 8u)) + (ecx));       // original 005f6cf1 add dword ptr [ebp + 0x10], ecx
    ebx = (ebx) + (ecx);                        // original 005f6cf4 add ebx, ecx
    eax = (eax) + (ecx);                        // original 005f6cf6 add eax, ecx
    edi = (edi) + (ecx);                        // original 005f6cf8 add edi, ecx
    store32(args + 0u, load32(args + 0u) + 1u); // original 005f6cfa inc dword ptr [ebp + 8]
    ecx = load32(args + 0u);                    // original 005f6cfd mov ecx, dword ptr [ebp + 8]
    left = ecx;
    right = load32(esi + 0x68u); // original 005f6d00 cmp ecx, dword ptr [esi + 0x68]
    store32(frame - 0x8u, ebx);  // original 005f6d03 mov dword ptr [ebp - 8], ebx
    if (left < right)
        goto L_005f6af9; // original 005f6d06 jb 0x5f6af9
L_005f6d0c:;
    eax = load32(esi + 0x7cu); // original 005f6d0c mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f6d0f mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f6d12 fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f6d15 pop edi
    ;                                   // C++ ABI restore ownership. // original 005f6d16 pop esi
    ;                                   // C++ ABI restore ownership. // original 005f6d17 pop ebx
    ;                                   // C++ frame ownership. // original 005f6d18 leave
    return eax;                         // original 005f6d19 ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f6a01(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f6a01\n\taddl $8,%esp\n\tretl $12");
}

// Complete original 005f6e24..005f713d: signed Q8W8V8U8; original access widths/order retained.
extern "C" u32 recovered_005f6e24(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x80];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x80u;
    ;          // C++ frame and ABI save ownership. // original 005f6e24 mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f6e26 push ebp
    ;          // C++ frame and ABI save ownership. // original 005f6e27 mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f6e29 sub esp, 0x50
    ;          // C++ frame and ABI save ownership. // original 005f6e2c push ebx
    ;          // C++ frame and ABI save ownership. // original 005f6e2d push esi
    esi = ecx; // original 005f6e2e mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f6e30 cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f6e34 push edi
    if (left == right)
        goto L_005f6e42;         // original 005f6e35 je 0x5f6e42
    pending = load32(args + 8u); // original 005f6e37 push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f6e3a call 0x5f0da1
    store32(args + 8u, eax); // original 005f6e3f mov dword ptr [ebp + 0x10], eax
L_005f6e42:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f6e42 cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f6e55;         // original 005f6e46 je 0x5f6e55
    pending = load32(args + 8u); // original 005f6e48 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f6e4b mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f6e4d call 0x5f22d6
    store32(args + 8u, eax); // original 005f6e52 mov dword ptr [ebp + 0x10], eax
L_005f6e55:;
    eax = load32(args + 0u);                     // original 005f6e55 mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f6e58 fldz
    ebx = load32(esi + 0x68u); // original 005f6e5a mov ebx, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f6e5d fstp dword ptr [ebp - 0x50]
    edx = load32(esi + 0x60u);          // original 005f6e60 mov edx, dword ptr [esi + 0x60]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f6e63 fldz
    edi = load32(esi + 0x64u); // original 005f6e65 mov edi, dword ptr [esi + 0x64]
    edx = (edx) * (eax);       // original 005f6e68 imul edx, eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory");          // original 005f6e6b fstp dword ptr [ebp - 0x4c]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f6e6e fldz
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f6e70 fstp dword ptr [ebp - 0x44]
    store32(args + 0u, eax);            // original 005f6e73 mov dword ptr [ebp + 8], eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f6e76 and dword ptr [ebp + 8], 1
    ecx = ebx + 0xffffffffu;               // original 005f6e7a lea ecx, [ebx - 1]
    ecx = (ecx) * (load32(args + 0u));     // original 005f6e7d imul ecx, dword ptr [ebp + 8]
    edx = edx + ecx * 4u;                  // original 005f6e81 lea edx, [edx + ecx*4]
    ecx = load32(args + 4u);               // original 005f6e84 mov ecx, dword ptr [ebp + 0xc]
    edi = (edi) * (ecx);                   // original 005f6e87 imul edi, ecx
    eax = (eax) & (0x3u);                  // original 005f6e8a and eax, 3
    ecx = (ecx) & (0x3u);                  // original 005f6e8d and ecx, 3
    edx = (edx) + (edi);                   // original 005f6e90 add edx, edi
    edx = (edx) + (load32(esi + 0x20u));   // original 005f6e92 add edx, dword ptr [esi + 0x20]
    left = load32(args + 0u);
    right = 0x0u;               // original 005f6e95 cmp dword ptr [ebp + 8], 0
    eax = ecx + eax * 8u;       // original 005f6e99 lea eax, [ecx + eax*8]
    ecx = load32(esi + 0x34u);  // original 005f6e9c mov ecx, dword ptr [esi + 0x34]
    eax = ecx + eax * 4u;       // original 005f6e9f lea eax, [ecx + eax*4]
    store32(frame - 0x4u, edx); // original 005f6ea2 mov dword ptr [ebp - 4], edx
    store32(frame - 0xcu, eax); // original 005f6ea5 mov dword ptr [ebp - 0xc], eax
    if (left != right)
        goto L_005f6eb4;     // original 005f6ea8 jne 0x5f6eb4
    edi = 0u;                // original 005f6eaa xor edi, edi
    ebx = 0u;                // original 005f6eac xor ebx, ebx
    edi = edi + 1u;          // original 005f6eae inc edi
    store32(args + 4u, edi); // original 005f6eaf mov dword ptr [ebp + 0xc], edi
    goto L_005f6ebc;         // original 005f6eb2 jmp 0x5f6ebc
L_005f6eb4:;
    ebx = ebx - 1u; // original 005f6eb4 dec ebx
    store32(args + 4u, (load32(args + 4u)) |
                           (0xffffffffu)); // original 005f6eb5 or dword ptr [ebp + 0xc], 0xffffffff
    edi = load32(args + 4u);               // original 005f6eb9 mov edi, dword ptr [ebp + 0xc]
L_005f6ebc:;
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 0u)
                     : "st", "memory"); // original 005f6ebc fnstcw word ptr [ebp + 8]
    eax = load32(args + 0u);            // original 005f6ebf mov eax, dword ptr [ebp + 8]
    eax = (eax) | (0xc00u);             // original 005f6ec2 or eax, 0xc00
    store32(frame - 0x8u, eax);         // original 005f6ec7 mov dword ptr [ebp - 8], eax
    __asm__ volatile("fldcw (%0)" ::"r"(frame - 0x8u)
                     : "st", "memory"); // original 005f6eca fldcw word ptr [ebp - 8]
    eax = load32(args + 0u);            // original 005f6ecd mov eax, dword ptr [ebp + 8]
    store32(esi + 0x7cu, eax);          // original 005f6ed0 mov dword ptr [esi + 0x7c], eax
    left = load32(esi + 0x5cu);
    right = 0x0u; // original 005f6ed3 cmp dword ptr [esi + 0x5c], 0
    if (left == right)
        goto L_005f6ee3;         // original 005f6ed7 je 0x5f6ee3
    pending = load32(args + 8u); // original 005f6ed9 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f6edc mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f6ede call 0x5f25f2
L_005f6ee3:;
    store32(args + 0u,
            (load32(args + 0u)) & (0x0u)); // original 005f6ee3 and dword ptr [ebp + 8], 0
    left = load32(esi + 0x68u);
    right = 0x0u; // original 005f6ee7 cmp dword ptr [esi + 0x68], 0
    if (left <= right)
        goto L_005f712d;               // original 005f6eeb jbe 0x5f712d
    eax = edi;                         // original 005f6ef1 mov eax, edi
    eax = (eax) << (0x2u);             // original 005f6ef3 shl eax, 2
    ecx = edi;                         // original 005f6ef6 mov ecx, edi
    ecx = (ecx) << (0x4u);             // original 005f6ef8 shl ecx, 4
    store32(frame - 0x1cu, eax);       // original 005f6efb mov dword ptr [ebp - 0x1c], eax
    eax = ebx;                         // original 005f6efe mov eax, ebx
    store32(frame - 0x20u, ecx);       // original 005f6f00 mov dword ptr [ebp - 0x20], ecx
    ecx = load32(args + 8u);           // original 005f6f03 mov ecx, dword ptr [ebp + 0x10]
    edi = (edi) + (ebx);               // original 005f6f06 add edi, ebx
    ebx = (ebx) - (load32(args + 4u)); // original 005f6f08 sub ebx, dword ptr [ebp + 0xc]
    eax = (eax) << (0x4u);             // original 005f6f0b shl eax, 4
    ecx = eax + ecx + 0xcu;            // original 005f6f0e lea ecx, [eax + ecx + 0xc]
    edi = (edi) << (0x4u);             // original 005f6f12 shl edi, 4
    ebx = (ebx) << (0x4u);             // original 005f6f15 shl ebx, 4
    store32(args + 8u, ecx);           // original 005f6f18 mov dword ptr [ebp + 0x10], ecx
L_005f6f1b:;
    ecx = load32(args + 0u);    // original 005f6f1b mov ecx, dword ptr [ebp + 8]
    edx = load32(frame - 0xcu); // original 005f6f1e mov edx, dword ptr [ebp - 0xc]
    ecx = (ecx) & (0x3u);       // original 005f6f21 and ecx, 3
    __asm__ volatile("flds (%0)" ::"r"(edx + ecx * 4u)
                     : "st", "memory"); // original 005f6f24 fld dword ptr [edx + ecx*4]
    ecx = load32(args + 8u);            // original 005f6f27 mov ecx, dword ptr [ebp + 0x10]
    __asm__ volatile("fsts (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f6f2a fst dword ptr [ebp + 0xc]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f6f2d fld dword ptr [ebp - 0x50]
    __asm__ volatile("fadds (%0)" ::"r"(ecx + 0xfffffff4u)
                     : "st", "memory"); // original 005f6f30 fadd dword ptr [ecx - 0xc]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df434))
                     : "st", "memory"); // original 005f6f33 fmul dword ptr [0x6df434]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f6f39 fstp dword ptr [ebp - 0x40]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f6f3c fld dword ptr [ebp - 0x4c]
    __asm__ volatile("fadds (%0)" ::"r"(ecx + 0xfffffff8u)
                     : "st", "memory"); // original 005f6f3f fadd dword ptr [ecx - 8]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df434))
                     : "st", "memory"); // original 005f6f42 fmul dword ptr [0x6df434]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f6f48 fstp dword ptr [ebp - 0x3c]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f6f4b fld dword ptr [ebp - 0x44]
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f6f4e fadd dword ptr [ecx]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bc8c4))
                     : "st", "memory"); // original 005f6f50 fmul dword ptr [0x6bc8c4]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f6f56 fstp dword ptr [ebp - 0x34]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f6f59 fld dword ptr [ebp - 0x40]
    __asm__ volatile("fadd %%st(1)" ::: "st", "memory"); // original 005f6f5c fadd st(1)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x8u)
                     : "st", "memory"); // original 005f6f5e fstp dword ptr [ebp - 8]
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f6f61 fstp st(0)
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x8u)
                     : "st", "memory"); // original 005f6f63 fld dword ptr [ebp - 8]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f6f66 fistp dword ptr [ebp - 0x10]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f6f69 fld dword ptr [ebp - 0x3c]
    edx = load32(frame - 0x10u);        // original 005f6f6c mov edx, dword ptr [ebp - 0x10]
    __asm__ volatile("fadds (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f6f6f fadd dword ptr [ebp + 0xc]
    store32(frame - 0x30u, edx);        // original 005f6f72 mov dword ptr [ebp - 0x30], edx
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x8u)
                     : "st", "memory"); // original 005f6f75 fstp dword ptr [ebp - 8]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x8u)
                     : "st", "memory"); // original 005f6f78 fld dword ptr [ebp - 8]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f6f7b fistp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f6f7e fld dword ptr [ebp - 0x34]
    ecx = load32(frame - 0x14u);        // original 005f6f81 mov ecx, dword ptr [ebp - 0x14]
    __asm__ volatile("fadds (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f6f84 fadd dword ptr [ebp + 0xc]
    store32(frame - 0x2cu, ecx);        // original 005f6f87 mov dword ptr [ebp - 0x2c], ecx
    __asm__ volatile("fstps (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f6f8a fstp dword ptr [ebp + 0xc]
    __asm__ volatile("flds (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f6f8d fld dword ptr [ebp + 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f6f90 fistp dword ptr [ebp - 0x18]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f6f93 cmp dword ptr [esi + 0x5c], 0
    ecx = load32(frame - 0x18u); // original 005f6f97 mov ecx, dword ptr [ebp - 0x18]
    store32(frame - 0x24u, ecx); // original 005f6f9a mov dword ptr [ebp - 0x24], ecx
    if (left == right)
        goto L_005f708b; // original 005f6f9d je 0x5f708b
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df430))
                     : "st", "memory"); // original 005f6fa3 fld dword ptr [0x6df430]
    ecx = load32(esi + 0x5cu);          // original 005f6fa9 mov ecx, dword ptr [esi + 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f6fac fild dword ptr [ebp - 0x30]
    ecx = ecx + ebx + 0x10u;            // original 005f6faf lea ecx, [ecx + ebx + 0x10]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f6fb3 fsubr dword ptr [ebp - 0x40]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6fb6 fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f6fb8 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6fbe fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f6fc0 fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f6fc2 fstp dword ptr [ecx]
    ecx = load32(esi + 0x5cu);          // original 005f6fc4 mov ecx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f6fc7 fld dword ptr [0x6df418]
    ecx = ecx + eax + 0x10u;            // original 005f6fcd lea ecx, [ecx + eax + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6fd1 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f6fd3 fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f6fd5 fstp dword ptr [ecx]
    ecx = load32(esi + 0x5cu);          // original 005f6fd7 mov ecx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f6fda fld dword ptr [0x6be980]
    ecx = ecx + edi + 0x10u;            // original 005f6fe0 lea ecx, [ecx + edi + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f6fe4 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f6fe6 fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f6fe8 fstp dword ptr [ecx]
    ecx = load32(esi + 0x5cu);          // original 005f6fea mov ecx, dword ptr [esi + 0x5c]
    ecx = ecx + ebx + 0x14u;            // original 005f6fed lea ecx, [ecx + ebx + 0x14]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f6ff1 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f6ff7 fstp dword ptr [ebp - 0x50]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x2cu)
                     : "st", "memory"); // original 005f6ffa fild dword ptr [ebp - 0x2c]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f6ffd fsubr dword ptr [ebp - 0x3c]
    __asm__ volatile("fmulp %%st(1)" ::: "st", "memory"); // original 005f7000 fmulp st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f7002 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7008 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f700a fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f700c fstp dword ptr [ecx]
    ecx = load32(esi + 0x5cu);          // original 005f700e mov ecx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f7011 fld dword ptr [0x6df418]
    ecx = ecx + eax + 0x14u;            // original 005f7017 lea ecx, [ecx + eax + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f701b fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f701d fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f701f fstp dword ptr [ecx]
    ecx = load32(esi + 0x5cu);          // original 005f7021 mov ecx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f7024 fld dword ptr [0x6be980]
    ecx = ecx + edi + 0x14u;            // original 005f702a lea ecx, [ecx + edi + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f702e fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f7030 fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f7032 fstp dword ptr [ecx]
    ecx = load32(esi + 0x5cu);          // original 005f7034 mov ecx, dword ptr [esi + 0x5c]
    ecx = ecx + ebx + 0x1cu;            // original 005f7037 lea ecx, [ecx + ebx + 0x1c]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f703b fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f7041 fstp dword ptr [ebp - 0x4c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x24u)
                     : "st", "memory"); // original 005f7044 fild dword ptr [ebp - 0x24]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f7047 fsubr dword ptr [ebp - 0x34]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be1d0))
                     : "st", "memory"); // original 005f704a fmul dword ptr [0x6be1d0]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f7050 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7056 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f7058 fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f705a fstp dword ptr [ecx]
    ecx = load32(esi + 0x5cu);          // original 005f705c mov ecx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f705f fld dword ptr [0x6df418]
    ecx = ecx + eax + 0x1cu;            // original 005f7065 lea ecx, [ecx + eax + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7069 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f706b fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f706d fstp dword ptr [ecx]
    ecx = load32(esi + 0x5cu);          // original 005f706f mov ecx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f7072 fld dword ptr [0x6be980]
    ecx = ecx + edi + 0x1cu;            // original 005f7078 lea ecx, [ecx + edi + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f707c fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f707e fadd dword ptr [ecx]
    __asm__ volatile("fstps (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f7080 fstp dword ptr [ecx]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f7082 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f7088 fstp dword ptr [ebp - 0x44]
L_005f708b:;
    pending = 0x7fu; // original 005f708b push 0x7f
    ecx = pending;   // original 005f708d pop ecx
    left = edx;
    right = ecx; // original 005f708e cmp edx, ecx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7094; // original 005f7090 jl 0x5f7094
    edx = ecx;           // original 005f7092 mov edx, ecx
L_005f7094:;
    left = edx;
    right = 0xffffff81u; // original 005f7094 cmp edx, -0x7f
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f70a3; // original 005f7097 jle 0x5f70a3
    left = load32(frame - 0x30u);
    right = ecx; // original 005f7099 cmp dword ptr [ebp - 0x30], ecx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f70aa;         // original 005f709c jl 0x5f70aa
    store32(frame - 0x30u, ecx); // original 005f709e mov dword ptr [ebp - 0x30], ecx
    goto L_005f70aa;             // original 005f70a1 jmp 0x5f70aa
L_005f70a3:;
    store32(frame - 0x30u, 0xffffff81u); // original 005f70a3 mov dword ptr [ebp - 0x30], 0xffffff81
L_005f70aa:;
    edx = load32(frame - 0x2cu); // original 005f70aa mov edx, dword ptr [ebp - 0x2c]
    left = edx;
    right = ecx; // original 005f70ad cmp edx, ecx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f70b3; // original 005f70af jl 0x5f70b3
    edx = ecx;           // original 005f70b1 mov edx, ecx
L_005f70b3:;
    left = edx;
    right = 0xffffff81u; // original 005f70b3 cmp edx, -0x7f
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f70c2; // original 005f70b6 jle 0x5f70c2
    left = load32(frame - 0x2cu);
    right = ecx; // original 005f70b8 cmp dword ptr [ebp - 0x2c], ecx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f70c9;         // original 005f70bb jl 0x5f70c9
    store32(frame - 0x2cu, ecx); // original 005f70bd mov dword ptr [ebp - 0x2c], ecx
    goto L_005f70c9;             // original 005f70c0 jmp 0x5f70c9
L_005f70c2:;
    store32(frame - 0x2cu, 0xffffff81u); // original 005f70c2 mov dword ptr [ebp - 0x2c], 0xffffff81
L_005f70c9:;
    edx = load32(frame - 0x24u); // original 005f70c9 mov edx, dword ptr [ebp - 0x24]
    ecx = 0xffu;                 // original 005f70cc mov ecx, 0xff
    left = load32(frame - 0x24u);
    right = ecx; // original 005f70d1 cmp dword ptr [ebp - 0x24], ecx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f70d8; // original 005f70d4 jl 0x5f70d8
    edx = ecx;           // original 005f70d6 mov edx, ecx
L_005f70d8:;
    left = edx;
    right = 0xffffff01u; // original 005f70d8 cmp edx, 0xffffff01
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f70ea; // original 005f70de jle 0x5f70ea
    left = load32(frame - 0x24u);
    right = ecx; // original 005f70e0 cmp dword ptr [ebp - 0x24], ecx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f70f1;         // original 005f70e3 jl 0x5f70f1
    store32(frame - 0x24u, ecx); // original 005f70e5 mov dword ptr [ebp - 0x24], ecx
    goto L_005f70f1;             // original 005f70e8 jmp 0x5f70f1
L_005f70ea:;
    store32(frame - 0x24u, 0xffffff01u); // original 005f70ea mov dword ptr [ebp - 0x24], 0xffffff01
L_005f70f1:;
    ecx = load32(frame - 0x30u); // original 005f70f1 mov ecx, dword ptr [ebp - 0x30]
    edx = 0u;                    // original 005f70f4 xor edx, edx
    edx = (edx & 0xffff00ffu) |
          (((load8(frame - 0x24u)) & 255u) << 8); // original 005f70f6 mov dh, byte ptr [ebp - 0x24]
    ecx = (ecx) & (0xffu);                        // original 005f70f9 and ecx, 0xff
    edx = (edx & 0xffffff00u) |
          ((load8(frame - 0x2cu)) & 0xffu); // original 005f70ff mov dl, byte ptr [ebp - 0x2c]
    edx = (edx) << (0x8u);                  // original 005f7102 shl edx, 8
    edx = (edx) | (ecx);                    // original 005f7105 or edx, ecx
    ecx = load32(frame - 0x4u);             // original 005f7107 mov ecx, dword ptr [ebp - 4]
    store32(ecx, edx);                      // original 005f710a mov dword ptr [ecx], edx
    ecx = load32(frame - 0x1cu);            // original 005f710c mov ecx, dword ptr [ebp - 0x1c]
    store32(frame - 0x4u,
            (load32(frame - 0x4u)) + (ecx)); // original 005f710f add dword ptr [ebp - 4], ecx
    ecx = load32(frame - 0x20u);             // original 005f7112 mov ecx, dword ptr [ebp - 0x20]
    store32(args + 8u,
            (load32(args + 8u)) + (ecx));       // original 005f7115 add dword ptr [ebp + 0x10], ecx
    eax = (eax) + (ecx);                        // original 005f7118 add eax, ecx
    ebx = (ebx) + (ecx);                        // original 005f711a add ebx, ecx
    edi = (edi) + (ecx);                        // original 005f711c add edi, ecx
    store32(args + 0u, load32(args + 0u) + 1u); // original 005f711e inc dword ptr [ebp + 8]
    ecx = load32(args + 0u);                    // original 005f7121 mov ecx, dword ptr [ebp + 8]
    left = ecx;
    right = load32(esi + 0x68u); // original 005f7124 cmp ecx, dword ptr [esi + 0x68]
    if (left < right)
        goto L_005f6f1b; // original 005f7127 jb 0x5f6f1b
L_005f712d:;
    eax = load32(esi + 0x7cu); // original 005f712d mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f7130 mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f7133 fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f7136 pop edi
    ;                                   // C++ ABI restore ownership. // original 005f7137 pop esi
    ;                                   // C++ ABI restore ownership. // original 005f7138 pop ebx
    ;                                   // C++ frame ownership. // original 005f7139 leave
    return eax;                         // original 005f713a ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f6e24(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f6e24\n\taddl $8,%esp\n\tretl $12");
}

// Complete original 005f7224..005f75d0: signed A2W10V10U10; original access widths/order retained.
extern "C" u32 recovered_005f7224(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x80];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x80u;
    ;          // C++ frame and ABI save ownership. // original 005f7224 mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f7226 push ebp
    ;          // C++ frame and ABI save ownership. // original 005f7227 mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f7229 sub esp, 0x54
    ;          // C++ frame and ABI save ownership. // original 005f722c push ebx
    ;          // C++ frame and ABI save ownership. // original 005f722d push esi
    esi = ecx; // original 005f722e mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f7230 cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f7234 push edi
    if (left == right)
        goto L_005f7242;         // original 005f7235 je 0x5f7242
    pending = load32(args + 8u); // original 005f7237 push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f723a call 0x5f0da1
    store32(args + 8u, eax); // original 005f723f mov dword ptr [ebp + 0x10], eax
L_005f7242:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f7242 cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f7255;         // original 005f7246 je 0x5f7255
    pending = load32(args + 8u); // original 005f7248 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f724b mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f724d call 0x5f22d6
    store32(args + 8u, eax); // original 005f7252 mov dword ptr [ebp + 0x10], eax
L_005f7255:;
    eax = load32(args + 0u);                     // original 005f7255 mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f7258 fldz
    edi = load32(esi + 0x68u); // original 005f725a mov edi, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f725d fstp dword ptr [ebp - 0x54]
    edx = load32(esi + 0x60u);          // original 005f7260 mov edx, dword ptr [esi + 0x60]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f7263 fldz
    ebx = load32(esi + 0x64u); // original 005f7265 mov ebx, dword ptr [esi + 0x64]
    edx = (edx) * (eax);       // original 005f7268 imul edx, eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory");          // original 005f726b fstp dword ptr [ebp - 0x50]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f726e fldz
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory");          // original 005f7270 fstp dword ptr [ebp - 0x4c]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f7273 fldz
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f7275 fstp dword ptr [ebp - 0x48]
    store32(args + 0u, eax);            // original 005f7278 mov dword ptr [ebp + 8], eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f727b and dword ptr [ebp + 8], 1
    ecx = edi + 0xffffffffu;               // original 005f727f lea ecx, [edi - 1]
    ecx = (ecx) * (load32(args + 0u));     // original 005f7282 imul ecx, dword ptr [ebp + 8]
    ecx = edx + ecx * 4u;                  // original 005f7286 lea ecx, [edx + ecx*4]
    edx = load32(args + 4u);               // original 005f7289 mov edx, dword ptr [ebp + 0xc]
    ebx = (ebx) * (edx);                   // original 005f728c imul ebx, edx
    ecx = (ecx) + (ebx);                   // original 005f728f add ecx, ebx
    ecx = (ecx) + (load32(esi + 0x20u));   // original 005f7291 add ecx, dword ptr [esi + 0x20]
    eax = (eax) & (0x3u);                  // original 005f7294 and eax, 3
    edx = (edx) & (0x3u);                  // original 005f7297 and edx, 3
    left = load32(args + 0u);
    right = 0x0u;               // original 005f729a cmp dword ptr [ebp + 8], 0
    store32(frame - 0x4u, ecx); // original 005f729e mov dword ptr [ebp - 4], ecx
    ecx = load32(esi + 0x34u);  // original 005f72a1 mov ecx, dword ptr [esi + 0x34]
    eax = edx + eax * 8u;       // original 005f72a4 lea eax, [edx + eax*8]
    eax = ecx + eax * 4u;       // original 005f72a7 lea eax, [ecx + eax*4]
    store32(frame - 0x8u, eax); // original 005f72aa mov dword ptr [ebp - 8], eax
    if (left != right)
        goto L_005f72b6; // original 005f72ad jne 0x5f72b6
    ebx = 0u;            // original 005f72af xor ebx, ebx
    edi = 0u;            // original 005f72b1 xor edi, edi
    ebx = ebx + 1u;      // original 005f72b3 inc ebx
    goto L_005f72ba;     // original 005f72b4 jmp 0x5f72ba
L_005f72b6:;
    edi = edi - 1u;              // original 005f72b6 dec edi
    ebx = (ebx) | (0xffffffffu); // original 005f72b7 or ebx, 0xffffffff
L_005f72ba:;
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 0u)
                     : "st", "memory"); // original 005f72ba fnstcw word ptr [ebp + 8]
    eax = load32(args + 0u);            // original 005f72bd mov eax, dword ptr [ebp + 8]
    eax = (eax) | (0xc00u);             // original 005f72c0 or eax, 0xc00
    store32(args + 4u, eax);            // original 005f72c5 mov dword ptr [ebp + 0xc], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f72c8 fldcw word ptr [ebp + 0xc]
    eax = load32(args + 0u);            // original 005f72cb mov eax, dword ptr [ebp + 8]
    store32(esi + 0x7cu, eax);          // original 005f72ce mov dword ptr [esi + 0x7c], eax
    left = load32(esi + 0x5cu);
    right = 0x0u; // original 005f72d1 cmp dword ptr [esi + 0x5c], 0
    if (left == right)
        goto L_005f72e1;         // original 005f72d5 je 0x5f72e1
    pending = load32(args + 8u); // original 005f72d7 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f72da mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f72dc call 0x5f25f2
L_005f72e1:;
    store32(args + 0u,
            (load32(args + 0u)) & (0x0u)); // original 005f72e1 and dword ptr [ebp + 8], 0
    left = load32(esi + 0x68u);
    right = 0x0u; // original 005f72e5 cmp dword ptr [esi + 0x68], 0
    if (left <= right)
        goto L_005f75c0;         // original 005f72e9 jbe 0x5f75c0
    edx = load32(args + 8u);     // original 005f72ef mov edx, dword ptr [ebp + 0x10]
    eax = ebx;                   // original 005f72f2 mov eax, ebx
    eax = (eax) << (0x2u);       // original 005f72f4 shl eax, 2
    store32(frame - 0x20u, eax); // original 005f72f7 mov dword ptr [ebp - 0x20], eax
    eax = edi;                   // original 005f72fa mov eax, edi
    ecx = ebx;                   // original 005f72fc mov ecx, ebx
    ecx = (ecx) << (0x4u);       // original 005f72fe shl ecx, 4
    eax = (eax) << (0x4u);       // original 005f7301 shl eax, 4
    store32(frame - 0x24u, ecx); // original 005f7304 mov dword ptr [ebp - 0x24], ecx
    ecx = ebx + edi;             // original 005f7307 lea ecx, [ebx + edi]
    edi = (edi) - (ebx);         // original 005f730a sub edi, ebx
    edx = eax + edx + 0x8u;      // original 005f730c lea edx, [eax + edx + 8]
    ecx = (ecx) << (0x4u);       // original 005f7310 shl ecx, 4
    edi = (edi) << (0x4u);       // original 005f7313 shl edi, 4
    store32(args + 4u, edx);     // original 005f7316 mov dword ptr [ebp + 0xc], edx
L_005f7319:;
    edx = load32(args + 0u); // original 005f7319 mov edx, dword ptr [ebp + 8]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df434))
                     : "st", "memory"); // original 005f731c fld dword ptr [0x6df434]
    ebx = load32(frame - 0x8u);         // original 005f7322 mov ebx, dword ptr [ebp - 8]
    edx = (edx) & (0x3u);               // original 005f7325 and edx, 3
    __asm__ volatile("flds (%0)" ::"r"(ebx + edx * 4u)
                     : "st", "memory"); // original 005f7328 fld dword ptr [ebx + edx*4]
    edx = load32(args + 4u);            // original 005f732b mov edx, dword ptr [ebp + 0xc]
    __asm__ volatile("fsts (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f732e fst dword ptr [ebp + 0x10]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f7331 fld dword ptr [ebp - 0x54]
    __asm__ volatile("fadds (%0)" ::"r"(edx + 0xfffffff8u)
                     : "st", "memory"); // original 005f7334 fadd dword ptr [edx - 8]
    __asm__ volatile("fmul %%st(2)" ::: "st", "memory"); // original 005f7337 fmul st(2)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f7339 fstp dword ptr [ebp - 0x44]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f733c fld dword ptr [ebp - 0x50]
    __asm__ volatile("fadds (%0)" ::"r"(edx + 0xfffffffcu)
                     : "st", "memory"); // original 005f733f fadd dword ptr [edx - 4]
    __asm__ volatile("fmul %%st(2)" ::: "st", "memory"); // original 005f7342 fmul st(2)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f7344 fstp dword ptr [ebp - 0x40]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f7347 fld dword ptr [ebp - 0x4c]
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory");                  // original 005f734a fadd dword ptr [edx]
    __asm__ volatile("fmul %%st(2)" ::: "st", "memory"); // original 005f734c fmul st(2)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f734e fstp dword ptr [ebp - 0x3c]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f7351 fld dword ptr [ebp - 0x48]
    __asm__ volatile("fadds (%0)" ::"r"(edx + 0x4u)
                     : "st", "memory"); // original 005f7354 fadd dword ptr [edx + 4]
    __asm__ volatile("fmul %%st(2)" ::: "st", "memory"); // original 005f7357 fmul st(2)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f7359 fstp dword ptr [ebp - 0x38]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f735c fld dword ptr [ebp - 0x44]
    __asm__ volatile("fadd %%st(1)" ::: "st", "memory"); // original 005f735f fadd st(1)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f7361 fstp dword ptr [ebp - 0xc]
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f7364 fstp st(0)
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f7366 fstp st(0)
    __asm__ volatile("flds (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f7368 fld dword ptr [ebp - 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f736b fistp dword ptr [ebp - 0x10]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f736e fld dword ptr [ebp - 0x40]
    edx = load32(frame - 0x10u);        // original 005f7371 mov edx, dword ptr [ebp - 0x10]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f7374 fadd dword ptr [ebp + 0x10]
    store32(frame - 0x34u, edx);        // original 005f7377 mov dword ptr [ebp - 0x34], edx
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f737a fstp dword ptr [ebp - 0xc]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f737d fld dword ptr [ebp - 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f7380 fistp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f7383 fld dword ptr [ebp - 0x3c]
    edx = load32(frame - 0x14u);        // original 005f7386 mov edx, dword ptr [ebp - 0x14]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f7389 fadd dword ptr [ebp + 0x10]
    store32(frame - 0x30u, edx);        // original 005f738c mov dword ptr [ebp - 0x30], edx
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f738f fstp dword ptr [ebp - 0xc]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f7392 fld dword ptr [ebp - 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f7395 fistp dword ptr [ebp - 0x18]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f7398 fld dword ptr [ebp - 0x38]
    edx = load32(frame - 0x18u);        // original 005f739b mov edx, dword ptr [ebp - 0x18]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f739e fadd dword ptr [ebp + 0x10]
    store32(frame - 0x2cu, edx);        // original 005f73a1 mov dword ptr [ebp - 0x2c], edx
    __asm__ volatile("fstps (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f73a4 fstp dword ptr [ebp + 0x10]
    __asm__ volatile("flds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f73a7 fld dword ptr [ebp + 0x10]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x1cu)
                     : "st", "memory"); // original 005f73aa fistp dword ptr [ebp - 0x1c]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f73ad cmp dword ptr [esi + 0x5c], 0
    ebx = load32(frame - 0x1cu); // original 005f73b1 mov ebx, dword ptr [ebp - 0x1c]
    store32(frame - 0x28u, ebx); // original 005f73b4 mov dword ptr [ebp - 0x28], ebx
    if (left == right)
        goto L_005f74eb; // original 005f73b7 je 0x5f74eb
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df430))
                     : "st", "memory"); // original 005f73bd fld dword ptr [0x6df430]
    ebx = load32(esi + 0x5cu);          // original 005f73c3 mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f73c6 fild dword ptr [ebp - 0x34]
    ebx = ebx + edi + 0x10u;            // original 005f73c9 lea ebx, [ebx + edi + 0x10]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f73cd fsubr dword ptr [ebp - 0x44]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f73d0 fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f73d2 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f73d8 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f73da fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f73dc fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f73de mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f73e1 fld dword ptr [0x6df418]
    ebx = ebx + eax + 0x10u;            // original 005f73e7 lea ebx, [ebx + eax + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f73eb fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f73ed fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f73ef fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f73f1 mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f73f4 fld dword ptr [0x6be980]
    ebx = ebx + ecx + 0x10u;            // original 005f73fa lea ebx, [ebx + ecx + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f73fe fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7400 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7402 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7404 mov ebx, dword ptr [esi + 0x5c]
    ebx = ebx + edi + 0x14u;            // original 005f7407 lea ebx, [ebx + edi + 0x14]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f740b fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f7411 fstp dword ptr [ebp - 0x54]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f7414 fild dword ptr [ebp - 0x30]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f7417 fsubr dword ptr [ebp - 0x40]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f741a fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f741c fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7422 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7424 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7426 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7428 mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f742b fld dword ptr [0x6df418]
    ebx = ebx + eax + 0x14u;            // original 005f7431 lea ebx, [ebx + eax + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7435 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7437 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7439 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f743b mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f743e fld dword ptr [0x6be980]
    ebx = ebx + ecx + 0x14u;            // original 005f7444 lea ebx, [ebx + ecx + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7448 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f744a fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f744c fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f744e mov ebx, dword ptr [esi + 0x5c]
    ebx = ebx + edi + 0x18u;            // original 005f7451 lea ebx, [ebx + edi + 0x18]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f7455 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f745b fstp dword ptr [ebp - 0x50]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x2cu)
                     : "st", "memory"); // original 005f745e fild dword ptr [ebp - 0x2c]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f7461 fsubr dword ptr [ebp - 0x3c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7464 fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f7466 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f746c fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f746e fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7470 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7472 mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f7475 fld dword ptr [0x6df418]
    ebx = ebx + eax + 0x18u;            // original 005f747b lea ebx, [ebx + eax + 0x18]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f747f fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7481 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7483 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7485 mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f7488 fld dword ptr [0x6be980]
    ebx = ebx + ecx + 0x18u;            // original 005f748e lea ebx, [ebx + ecx + 0x18]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7492 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7494 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7496 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7498 mov ebx, dword ptr [esi + 0x5c]
    ebx = ebx + edi + 0x1cu;            // original 005f749b lea ebx, [ebx + edi + 0x1c]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f749f fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f74a5 fstp dword ptr [ebp - 0x4c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x28u)
                     : "st", "memory"); // original 005f74a8 fild dword ptr [ebp - 0x28]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f74ab fsubr dword ptr [ebp - 0x38]
    __asm__ volatile("fmulp %%st(1)" ::: "st", "memory"); // original 005f74ae fmulp st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f74b0 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f74b6 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f74b8 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f74ba fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f74bc mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f74bf fld dword ptr [0x6df418]
    ebx = ebx + eax + 0x1cu;            // original 005f74c5 lea ebx, [ebx + eax + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f74c9 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f74cb fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f74cd fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f74cf mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f74d2 fld dword ptr [0x6be980]
    ebx = ebx + ecx + 0x1cu;            // original 005f74d8 lea ebx, [ebx + ecx + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f74dc fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f74de fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f74e0 fstp dword ptr [ebx]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f74e2 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f74e8 fstp dword ptr [ebp - 0x48]
L_005f74eb:;
    ebx = load32(frame - 0x34u); // original 005f74eb mov ebx, dword ptr [ebp - 0x34]
    left = ebx;
    right = 0x7fu; // original 005f74ee cmp ebx, 0x7f
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f74f6; // original 005f74f1 jl 0x5f74f6
    pending = 0x7fu;     // original 005f74f3 push 0x7f
    ebx = pending;       // original 005f74f5 pop ebx
L_005f74f6:;
    left = ebx;
    right = 0xffffff81u; // original 005f74f6 cmp ebx, -0x7f
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f750a; // original 005f74f9 jle 0x5f750a
    left = load32(frame - 0x34u);
    right = 0x7fu; // original 005f74fb cmp dword ptr [ebp - 0x34], 0x7f
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7511;           // original 005f74ff jl 0x5f7511
    store32(frame - 0x34u, 0x7fu); // original 005f7501 mov dword ptr [ebp - 0x34], 0x7f
    goto L_005f7511;               // original 005f7508 jmp 0x5f7511
L_005f750a:;
    store32(frame - 0x34u, 0xffffff81u); // original 005f750a mov dword ptr [ebp - 0x34], 0xffffff81
L_005f7511:;
    ebx = load32(frame - 0x30u); // original 005f7511 mov ebx, dword ptr [ebp - 0x30]
    left = ebx;
    right = 0x7fu; // original 005f7514 cmp ebx, 0x7f
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f751c; // original 005f7517 jl 0x5f751c
    pending = 0x7fu;     // original 005f7519 push 0x7f
    ebx = pending;       // original 005f751b pop ebx
L_005f751c:;
    left = ebx;
    right = 0xffffff81u; // original 005f751c cmp ebx, -0x7f
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f7530; // original 005f751f jle 0x5f7530
    left = load32(frame - 0x30u);
    right = 0x7fu; // original 005f7521 cmp dword ptr [ebp - 0x30], 0x7f
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7537;           // original 005f7525 jl 0x5f7537
    store32(frame - 0x30u, 0x7fu); // original 005f7527 mov dword ptr [ebp - 0x30], 0x7f
    goto L_005f7537;               // original 005f752e jmp 0x5f7537
L_005f7530:;
    store32(frame - 0x30u, 0xffffff81u); // original 005f7530 mov dword ptr [ebp - 0x30], 0xffffff81
L_005f7537:;
    left = edx;
    right = 0x7fu; // original 005f7537 cmp edx, 0x7f
    if (static_cast<int32_t>(left) >= static_cast<int32_t>(right))
        goto L_005f7540; // original 005f753a jge 0x5f7540
    ebx = edx;           // original 005f753c mov ebx, edx
    goto L_005f7543;     // original 005f753e jmp 0x5f7543
L_005f7540:;
    pending = 0x7fu; // original 005f7540 push 0x7f
    ebx = pending;   // original 005f7542 pop ebx
L_005f7543:;
    left = ebx;
    right = 0xffffff81u; // original 005f7543 cmp ebx, -0x7f
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f7551; // original 005f7546 jle 0x5f7551
    left = edx;
    right = 0x7fu; // original 005f7548 cmp edx, 0x7f
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7554; // original 005f754b jl 0x5f7554
    pending = 0x7fu;     // original 005f754d push 0x7f
    goto L_005f7553;     // original 005f754f jmp 0x5f7553
L_005f7551:;
    pending = 0xffffff81u; // original 005f7551 push -0x7f
L_005f7553:;
    edx = pending; // original 005f7553 pop edx
L_005f7554:;
    ebx = load32(frame - 0x28u); // original 005f7554 mov ebx, dword ptr [ebp - 0x28]
    left = ebx;
    right = 0x7fu; // original 005f7557 cmp ebx, 0x7f
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f755f; // original 005f755a jl 0x5f755f
    pending = 0x7fu;     // original 005f755c push 0x7f
    ebx = pending;       // original 005f755e pop ebx
L_005f755f:;
    left = ebx;
    right = 0xffffff81u; // original 005f755f cmp ebx, -0x7f
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f7570;         // original 005f7562 jle 0x5f7570
    ebx = load32(frame - 0x28u); // original 005f7564 mov ebx, dword ptr [ebp - 0x28]
    left = ebx;
    right = 0x7fu; // original 005f7567 cmp ebx, 0x7f
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7573; // original 005f756a jl 0x5f7573
    pending = 0x7fu;     // original 005f756c push 0x7f
    goto L_005f7572;     // original 005f756e jmp 0x5f7572
L_005f7570:;
    pending = 0xffffff81u; // original 005f7570 push -0x7f
L_005f7572:;
    ebx = pending; // original 005f7572 pop ebx
L_005f7573:;
    edx = (edx) & (0xffu);                 // original 005f7573 and edx, 0xff
    ebx = (ebx) << (0x8u);                 // original 005f7579 shl ebx, 8
    edx = (edx) | (ebx);                   // original 005f757c or edx, ebx
    ebx = load32(frame - 0x30u);           // original 005f757e mov ebx, dword ptr [ebp - 0x30]
    edx = (edx) << (0x8u);                 // original 005f7581 shl edx, 8
    ebx = (ebx) & (0xffu);                 // original 005f7584 and ebx, 0xff
    edx = (edx) | (ebx);                   // original 005f758a or edx, ebx
    ebx = load32(frame - 0x34u);           // original 005f758c mov ebx, dword ptr [ebp - 0x34]
    edx = (edx) << (0x8u);                 // original 005f758f shl edx, 8
    ebx = (ebx) & (0xffu);                 // original 005f7592 and ebx, 0xff
    edx = (edx) | (ebx);                   // original 005f7598 or edx, ebx
    ebx = load32(frame - 0x4u);            // original 005f759a mov ebx, dword ptr [ebp - 4]
    store32(ebx, edx);                     // original 005f759d mov dword ptr [ebx], edx
    edx = load32(frame - 0x24u);           // original 005f759f mov edx, dword ptr [ebp - 0x24]
    ebx = (ebx) + (load32(frame - 0x20u)); // original 005f75a2 add ebx, dword ptr [ebp - 0x20]
    store32(args + 4u,
            (load32(args + 4u)) + (edx));       // original 005f75a5 add dword ptr [ebp + 0xc], edx
    eax = (eax) + (edx);                        // original 005f75a8 add eax, edx
    edi = (edi) + (edx);                        // original 005f75aa add edi, edx
    ecx = (ecx) + (edx);                        // original 005f75ac add ecx, edx
    store32(args + 0u, load32(args + 0u) + 1u); // original 005f75ae inc dword ptr [ebp + 8]
    edx = load32(args + 0u);                    // original 005f75b1 mov edx, dword ptr [ebp + 8]
    left = edx;
    right = load32(esi + 0x68u); // original 005f75b4 cmp edx, dword ptr [esi + 0x68]
    store32(frame - 0x4u, ebx);  // original 005f75b7 mov dword ptr [ebp - 4], ebx
    if (left < right)
        goto L_005f7319; // original 005f75ba jb 0x5f7319
L_005f75c0:;
    eax = load32(esi + 0x7cu); // original 005f75c0 mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f75c3 mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f75c6 fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f75c9 pop edi
    ;                                   // C++ ABI restore ownership. // original 005f75ca pop esi
    ;                                   // C++ ABI restore ownership. // original 005f75cb pop ebx
    ;                                   // C++ frame ownership. // original 005f75cc leave
    return eax;                         // original 005f75cd ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f7224(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f7224\n\taddl $8,%esp\n\tretl $12");
}

// Complete original 005f76d8..005f794f: signed CxV8U8; original access widths/order retained.
extern "C" u32 recovered_005f76d8(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x80];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x80u;
    ;          // C++ frame and ABI save ownership. // original 005f76d8 mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f76da push ebp
    ;          // C++ frame and ABI save ownership. // original 005f76db mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f76dd sub esp, 0x50
    ;          // C++ frame and ABI save ownership. // original 005f76e0 push ebx
    ;          // C++ frame and ABI save ownership. // original 005f76e1 push esi
    esi = ecx; // original 005f76e2 mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f76e4 cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f76e8 push edi
    if (left == right)
        goto L_005f76f6;         // original 005f76e9 je 0x5f76f6
    pending = load32(args + 8u); // original 005f76eb push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f76ee call 0x5f0da1
    store32(args + 8u, eax); // original 005f76f3 mov dword ptr [ebp + 0x10], eax
L_005f76f6:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f76f6 cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f7709;         // original 005f76fa je 0x5f7709
    pending = load32(args + 8u); // original 005f76fc push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f76ff mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f7701 call 0x5f22d6
    store32(args + 8u, eax); // original 005f7706 mov dword ptr [ebp + 0x10], eax
L_005f7709:;
    eax = load32(args + 0u);                     // original 005f7709 mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f770c fldz
    edi = load32(esi + 0x68u); // original 005f770e mov edi, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f7711 fstp dword ptr [ebp - 0x40]
    edx = load32(esi + 0x60u);          // original 005f7714 mov edx, dword ptr [esi + 0x60]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f7717 fldz
    ebx = load32(esi + 0x64u); // original 005f7719 mov ebx, dword ptr [esi + 0x64]
    edx = (edx) * (eax);       // original 005f771c imul edx, eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f771f fstp dword ptr [ebp - 0x3c]
    store32(args + 0u, eax);            // original 005f7722 mov dword ptr [ebp + 8], eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f7725 and dword ptr [ebp + 8], 1
    ecx = edi + 0xffffffffu;               // original 005f7729 lea ecx, [edi - 1]
    ecx = (ecx) * (load32(args + 0u));     // original 005f772c imul ecx, dword ptr [ebp + 8]
    edx = edx + ecx * 4u;                  // original 005f7730 lea edx, [edx + ecx*4]
    ecx = load32(args + 4u);               // original 005f7733 mov ecx, dword ptr [ebp + 0xc]
    ebx = (ebx) * (ecx);                   // original 005f7736 imul ebx, ecx
    eax = (eax) & (0x3u);                  // original 005f7739 and eax, 3
    ecx = (ecx) & (0x3u);                  // original 005f773c and ecx, 3
    edx = (edx) + (ebx);                   // original 005f773f add edx, ebx
    edx = (edx) + (load32(esi + 0x20u));   // original 005f7741 add edx, dword ptr [esi + 0x20]
    left = load32(args + 0u);
    right = 0x0u;               // original 005f7744 cmp dword ptr [ebp + 8], 0
    eax = ecx + eax * 8u;       // original 005f7748 lea eax, [ecx + eax*8]
    ecx = load32(esi + 0x34u);  // original 005f774b mov ecx, dword ptr [esi + 0x34]
    eax = ecx + eax * 4u;       // original 005f774e lea eax, [ecx + eax*4]
    store32(frame - 0x4u, edx); // original 005f7751 mov dword ptr [ebp - 4], edx
    store32(frame - 0x8u, eax); // original 005f7754 mov dword ptr [ebp - 8], eax
    if (left != right)
        goto L_005f7760; // original 005f7757 jne 0x5f7760
    ebx = 0u;            // original 005f7759 xor ebx, ebx
    edi = 0u;            // original 005f775b xor edi, edi
    ebx = ebx + 1u;      // original 005f775d inc ebx
    goto L_005f7764;     // original 005f775e jmp 0x5f7764
L_005f7760:;
    edi = edi - 1u;              // original 005f7760 dec edi
    ebx = (ebx) | (0xffffffffu); // original 005f7761 or ebx, 0xffffffff
L_005f7764:;
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 0u)
                     : "st", "memory"); // original 005f7764 fnstcw word ptr [ebp + 8]
    eax = load32(args + 0u);            // original 005f7767 mov eax, dword ptr [ebp + 8]
    eax = (eax) | (0xc00u);             // original 005f776a or eax, 0xc00
    store32(args + 4u, eax);            // original 005f776f mov dword ptr [ebp + 0xc], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f7772 fldcw word ptr [ebp + 0xc]
    eax = load32(args + 0u);            // original 005f7775 mov eax, dword ptr [ebp + 8]
    store32(esi + 0x7cu, eax);          // original 005f7778 mov dword ptr [esi + 0x7c], eax
    left = load32(esi + 0x5cu);
    right = 0x0u; // original 005f777b cmp dword ptr [esi + 0x5c], 0
    if (left == right)
        goto L_005f778b;         // original 005f777f je 0x5f778b
    pending = load32(args + 8u); // original 005f7781 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f7784 mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f7786 call 0x5f25f2
L_005f778b:;
    store32(args + 0u,
            (load32(args + 0u)) & (0x0u)); // original 005f778b and dword ptr [ebp + 8], 0
    left = load32(esi + 0x68u);
    right = 0x0u; // original 005f778f cmp dword ptr [esi + 0x68], 0
    if (left <= right)
        goto L_005f793f;         // original 005f7793 jbe 0x5f793f
    eax = ebx;                   // original 005f7799 mov eax, ebx
    eax = (eax) << (0x2u);       // original 005f779b shl eax, 2
    store32(frame - 0x1cu, eax); // original 005f779e mov dword ptr [ebp - 0x1c], eax
    eax = edi;                   // original 005f77a1 mov eax, edi
    edx = ebx + edi;             // original 005f77a3 lea edx, [ebx + edi]
    ecx = ebx;                   // original 005f77a6 mov ecx, ebx
    ecx = (ecx) << (0x4u);       // original 005f77a8 shl ecx, 4
    edi = (edi) - (ebx);         // original 005f77ab sub edi, ebx
    eax = (eax) << (0x4u);       // original 005f77ad shl eax, 4
    edx = (edx) << (0x4u);       // original 005f77b0 shl edx, 4
    edi = (edi) << (0x4u);       // original 005f77b3 shl edi, 4
    store32(frame - 0x20u, ecx); // original 005f77b6 mov dword ptr [ebp - 0x20], ecx
    store32(args + 4u, edi);     // original 005f77b9 mov dword ptr [ebp + 0xc], edi
L_005f77bc:;
    ecx = load32(args + 0u);    // original 005f77bc mov ecx, dword ptr [ebp + 8]
    edi = load32(frame - 0x8u); // original 005f77bf mov edi, dword ptr [ebp - 8]
    ecx = (ecx) & (0x3u);       // original 005f77c2 and ecx, 3
    __asm__ volatile("flds (%0)" ::"r"(edi + ecx * 4u)
                     : "st", "memory"); // original 005f77c5 fld dword ptr [edi + ecx*4]
    ecx = load32(args + 8u);            // original 005f77c8 mov ecx, dword ptr [ebp + 0x10]
    __asm__ volatile("fsts (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f77cb fst dword ptr [ebp - 0x14]
    ecx = (ecx) + (eax);                // original 005f77ce add ecx, eax
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f77d0 fld dword ptr [ebp - 0x40]
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f77d3 fadd dword ptr [ecx]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df5d8))
                     : "st", "memory"); // original 005f77d5 fmul dword ptr [0x6df5d8]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f77db fstp dword ptr [ebp - 0x30]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f77de fld dword ptr [ebp - 0x3c]
    __asm__ volatile("fadds (%0)" ::"r"(ecx + 0x4u)
                     : "st", "memory"); // original 005f77e1 fadd dword ptr [ecx + 4]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df5d8))
                     : "st", "memory"); // original 005f77e4 fmul dword ptr [0x6df5d8]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x2cu)
                     : "st", "memory"); // original 005f77ea fstp dword ptr [ebp - 0x2c]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f77ed fld dword ptr [ebp - 0x30]
    __asm__ volatile("fadd %%st(1)" ::: "st", "memory"); // original 005f77f0 fadd st(1)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f77f2 fstp dword ptr [ebp - 0xc]
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f77f5 fstp st(0)
    __asm__ volatile("flds (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f77f7 fld dword ptr [ebp - 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f77fa fistp dword ptr [ebp - 0x10]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x2cu)
                     : "st", "memory"); // original 005f77fd fld dword ptr [ebp - 0x2c]
    edi = load32(frame - 0x10u);        // original 005f7800 mov edi, dword ptr [ebp - 0x10]
    __asm__ volatile("fadds (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f7803 fadd dword ptr [ebp - 0x14]
    store32(frame - 0x50u, edi);        // original 005f7806 mov dword ptr [ebp - 0x50], edi
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f7809 fstp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f780c fld dword ptr [ebp - 0x14]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f780f fistp dword ptr [ebp - 0x18]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f7812 cmp dword ptr [esi + 0x5c], 0
    ecx = load32(frame - 0x18u); // original 005f7816 mov ecx, dword ptr [ebp - 0x18]
    store32(frame - 0x4cu, ecx); // original 005f7819 mov dword ptr [ebp - 0x4c], ecx
    if (left == right)
        goto L_005f78c2; // original 005f781c je 0x5f78c2
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bbc78))
                     : "st", "memory"); // original 005f7822 fld dword ptr [0x6bbc78]
    edi = load32(esi + 0x5cu);          // original 005f7828 mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f782b fild dword ptr [ebp - 0x50]
    ebx = load32(args + 4u);            // original 005f782e mov ebx, dword ptr [ebp + 0xc]
    edi = ebx + edi + 0x10u;            // original 005f7831 lea edi, [ebx + edi + 0x10]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f7835 fsubr dword ptr [ebp - 0x30]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7838 fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f783a fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7840 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f7842 fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f7844 fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f7846 mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f7849 fld dword ptr [0x6df418]
    edi = eax + edi + 0x10u;            // original 005f784f lea edi, [eax + edi + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7853 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f7855 fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f7857 fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f7859 mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f785c fld dword ptr [0x6be980]
    edi = edx + edi + 0x10u;            // original 005f7862 lea edi, [edx + edi + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7866 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f7868 fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f786a fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f786c mov edi, dword ptr [esi + 0x5c]
    edi = ebx + edi + 0x14u;            // original 005f786f lea edi, [ebx + edi + 0x14]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f7873 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f7879 fstp dword ptr [ebp - 0x40]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f787c fild dword ptr [ebp - 0x4c]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x2cu)
                     : "st", "memory"); // original 005f787f fsubr dword ptr [ebp - 0x2c]
    __asm__ volatile("fmulp %%st(1)" ::: "st", "memory"); // original 005f7882 fmulp st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f7884 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f788a fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f788c fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f788e fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f7890 mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f7893 fld dword ptr [0x6df418]
    edi = eax + edi + 0x14u;            // original 005f7899 lea edi, [eax + edi + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f789d fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f789f fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f78a1 fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f78a3 mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f78a6 fld dword ptr [0x6be980]
    edi = edx + edi + 0x14u;            // original 005f78ac lea edi, [edx + edi + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f78b0 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f78b2 fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f78b4 fstp dword ptr [edi]
    edi = load32(frame - 0x50u);        // original 005f78b6 mov edi, dword ptr [ebp - 0x50]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f78b9 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f78bf fstp dword ptr [ebp - 0x3c]
L_005f78c2:;
    left = edi;
    right = 0x7fffu; // original 005f78c2 cmp edi, 0x7fff
    ebx = edi;       // original 005f78c8 mov ebx, edi
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f78d1; // original 005f78ca jl 0x5f78d1
    ebx = 0x7fffu;       // original 005f78cc mov ebx, 0x7fff
L_005f78d1:;
    left = ebx;
    right = 0xffff8001u; // original 005f78d1 cmp ebx, 0xffff8001
    ebx = 0x7fffu;       // original 005f78d7 mov ebx, 0x7fff
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f78e6; // original 005f78dc jle 0x5f78e6
    left = edi;
    right = ebx; // original 005f78de cmp edi, ebx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f78eb; // original 005f78e0 jl 0x5f78eb
    edi = ebx;           // original 005f78e2 mov edi, ebx
    goto L_005f78eb;     // original 005f78e4 jmp 0x5f78eb
L_005f78e6:;
    edi = 0xffff8001u; // original 005f78e6 mov edi, 0xffff8001
L_005f78eb:;
    left = ecx;
    right = ebx; // original 005f78eb cmp ecx, ebx
    ebx = ecx;   // original 005f78ed mov ebx, ecx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f78f6; // original 005f78ef jl 0x5f78f6
    ebx = 0x7fffu;       // original 005f78f1 mov ebx, 0x7fff
L_005f78f6:;
    left = ebx;
    right = 0xffff8001u; // original 005f78f6 cmp ebx, 0xffff8001
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f790b; // original 005f78fc jle 0x5f790b
    ebx = 0x7fffu;       // original 005f78fe mov ebx, 0x7fff
    left = ecx;
    right = ebx; // original 005f7903 cmp ecx, ebx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7910; // original 005f7905 jl 0x5f7910
    ecx = ebx;           // original 005f7907 mov ecx, ebx
    goto L_005f7910;     // original 005f7909 jmp 0x5f7910
L_005f790b:;
    ecx = 0xffff8001u; // original 005f790b mov ecx, 0xffff8001
L_005f7910:;
    ecx = (ecx) << (0x10u);                // original 005f7910 shl ecx, 0x10
    edi = (edi) & (0xffffu);               // original 005f7913 and edi, 0xffff
    ecx = (ecx) | (edi);                   // original 005f7919 or ecx, edi
    edi = load32(frame - 0x4u);            // original 005f791b mov edi, dword ptr [ebp - 4]
    store32(edi, ecx);                     // original 005f791e mov dword ptr [edi], ecx
    ecx = load32(frame - 0x20u);           // original 005f7920 mov ecx, dword ptr [ebp - 0x20]
    edi = (edi) + (load32(frame - 0x1cu)); // original 005f7923 add edi, dword ptr [ebp - 0x1c]
    store32(args + 4u,
            (load32(args + 4u)) + (ecx));       // original 005f7926 add dword ptr [ebp + 0xc], ecx
    eax = (eax) + (ecx);                        // original 005f7929 add eax, ecx
    edx = (edx) + (ecx);                        // original 005f792b add edx, ecx
    store32(args + 0u, load32(args + 0u) + 1u); // original 005f792d inc dword ptr [ebp + 8]
    ecx = load32(args + 0u);                    // original 005f7930 mov ecx, dword ptr [ebp + 8]
    left = ecx;
    right = load32(esi + 0x68u); // original 005f7933 cmp ecx, dword ptr [esi + 0x68]
    store32(frame - 0x4u, edi);  // original 005f7936 mov dword ptr [ebp - 4], edi
    if (left < right)
        goto L_005f77bc; // original 005f7939 jb 0x5f77bc
L_005f793f:;
    eax = load32(esi + 0x7cu); // original 005f793f mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f7942 mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f7945 fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f7948 pop edi
    ;                                   // C++ ABI restore ownership. // original 005f7949 pop esi
    ;                                   // C++ ABI restore ownership. // original 005f794a pop ebx
    ;                                   // C++ frame ownership. // original 005f794b leave
    return eax;                         // original 005f794c ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f76d8(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f76d8\n\taddl $8,%esp\n\tretl $12");
}

// Complete original 005f79f4..005f7dce: signed A2B10G10R10; original access widths/order retained.
extern "C" u32 recovered_005f79f4(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x80];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x80u;
    ;          // C++ frame and ABI save ownership. // original 005f79f4 mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f79f6 push ebp
    ;          // C++ frame and ABI save ownership. // original 005f79f7 mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f79f9 sub esp, 0x54
    ;          // C++ frame and ABI save ownership. // original 005f79fc push ebx
    ;          // C++ frame and ABI save ownership. // original 005f79fd push esi
    esi = ecx; // original 005f79fe mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f7a00 cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f7a04 push edi
    if (left == right)
        goto L_005f7a12;         // original 005f7a05 je 0x5f7a12
    pending = load32(args + 8u); // original 005f7a07 push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f7a0a call 0x5f0da1
    store32(args + 8u, eax); // original 005f7a0f mov dword ptr [ebp + 0x10], eax
L_005f7a12:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f7a12 cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f7a25;         // original 005f7a16 je 0x5f7a25
    pending = load32(args + 8u); // original 005f7a18 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f7a1b mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f7a1d call 0x5f22d6
    store32(args + 8u, eax); // original 005f7a22 mov dword ptr [ebp + 0x10], eax
L_005f7a25:;
    eax = load32(args + 0u);                     // original 005f7a25 mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f7a28 fldz
    edi = load32(esi + 0x68u); // original 005f7a2a mov edi, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f7a2d fstp dword ptr [ebp - 0x54]
    edx = load32(esi + 0x60u);          // original 005f7a30 mov edx, dword ptr [esi + 0x60]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f7a33 fldz
    ebx = load32(esi + 0x64u); // original 005f7a35 mov ebx, dword ptr [esi + 0x64]
    edx = (edx) * (eax);       // original 005f7a38 imul edx, eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory");          // original 005f7a3b fstp dword ptr [ebp - 0x50]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f7a3e fldz
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory");          // original 005f7a40 fstp dword ptr [ebp - 0x4c]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f7a43 fldz
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f7a45 fstp dword ptr [ebp - 0x48]
    store32(args + 0u, eax);            // original 005f7a48 mov dword ptr [ebp + 8], eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f7a4b and dword ptr [ebp + 8], 1
    ecx = edi + 0xffffffffu;               // original 005f7a4f lea ecx, [edi - 1]
    ecx = (ecx) * (load32(args + 0u));     // original 005f7a52 imul ecx, dword ptr [ebp + 8]
    ecx = edx + ecx * 4u;                  // original 005f7a56 lea ecx, [edx + ecx*4]
    edx = load32(args + 4u);               // original 005f7a59 mov edx, dword ptr [ebp + 0xc]
    ebx = (ebx) * (edx);                   // original 005f7a5c imul ebx, edx
    ecx = (ecx) + (ebx);                   // original 005f7a5f add ecx, ebx
    ecx = (ecx) + (load32(esi + 0x20u));   // original 005f7a61 add ecx, dword ptr [esi + 0x20]
    eax = (eax) & (0x3u);                  // original 005f7a64 and eax, 3
    edx = (edx) & (0x3u);                  // original 005f7a67 and edx, 3
    left = load32(args + 0u);
    right = 0x0u;               // original 005f7a6a cmp dword ptr [ebp + 8], 0
    store32(frame - 0x4u, ecx); // original 005f7a6e mov dword ptr [ebp - 4], ecx
    ecx = load32(esi + 0x34u);  // original 005f7a71 mov ecx, dword ptr [esi + 0x34]
    eax = edx + eax * 8u;       // original 005f7a74 lea eax, [edx + eax*8]
    eax = ecx + eax * 4u;       // original 005f7a77 lea eax, [ecx + eax*4]
    store32(frame - 0x8u, eax); // original 005f7a7a mov dword ptr [ebp - 8], eax
    if (left != right)
        goto L_005f7a86; // original 005f7a7d jne 0x5f7a86
    ebx = 0u;            // original 005f7a7f xor ebx, ebx
    edi = 0u;            // original 005f7a81 xor edi, edi
    ebx = ebx + 1u;      // original 005f7a83 inc ebx
    goto L_005f7a8a;     // original 005f7a84 jmp 0x5f7a8a
L_005f7a86:;
    edi = edi - 1u;              // original 005f7a86 dec edi
    ebx = (ebx) | (0xffffffffu); // original 005f7a87 or ebx, 0xffffffff
L_005f7a8a:;
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 0u)
                     : "st", "memory"); // original 005f7a8a fnstcw word ptr [ebp + 8]
    eax = load32(args + 0u);            // original 005f7a8d mov eax, dword ptr [ebp + 8]
    eax = (eax) | (0xc00u);             // original 005f7a90 or eax, 0xc00
    store32(args + 4u, eax);            // original 005f7a95 mov dword ptr [ebp + 0xc], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f7a98 fldcw word ptr [ebp + 0xc]
    eax = load32(args + 0u);            // original 005f7a9b mov eax, dword ptr [ebp + 8]
    store32(esi + 0x7cu, eax);          // original 005f7a9e mov dword ptr [esi + 0x7c], eax
    left = load32(esi + 0x5cu);
    right = 0x0u; // original 005f7aa1 cmp dword ptr [esi + 0x5c], 0
    if (left == right)
        goto L_005f7ab1;         // original 005f7aa5 je 0x5f7ab1
    pending = load32(args + 8u); // original 005f7aa7 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f7aaa mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f7aac call 0x5f25f2
L_005f7ab1:;
    store32(args + 0u,
            (load32(args + 0u)) & (0x0u)); // original 005f7ab1 and dword ptr [ebp + 8], 0
    left = load32(esi + 0x68u);
    right = 0x0u; // original 005f7ab5 cmp dword ptr [esi + 0x68], 0
    if (left <= right)
        goto L_005f7dbe;         // original 005f7ab9 jbe 0x5f7dbe
    edx = load32(args + 8u);     // original 005f7abf mov edx, dword ptr [ebp + 0x10]
    eax = ebx;                   // original 005f7ac2 mov eax, ebx
    eax = (eax) << (0x2u);       // original 005f7ac4 shl eax, 2
    store32(frame - 0x20u, eax); // original 005f7ac7 mov dword ptr [ebp - 0x20], eax
    eax = edi;                   // original 005f7aca mov eax, edi
    ecx = ebx;                   // original 005f7acc mov ecx, ebx
    ecx = (ecx) << (0x4u);       // original 005f7ace shl ecx, 4
    eax = (eax) << (0x4u);       // original 005f7ad1 shl eax, 4
    store32(frame - 0x24u, ecx); // original 005f7ad4 mov dword ptr [ebp - 0x24], ecx
    ecx = ebx + edi;             // original 005f7ad7 lea ecx, [ebx + edi]
    edi = (edi) - (ebx);         // original 005f7ada sub edi, ebx
    edx = eax + edx + 0x8u;      // original 005f7adc lea edx, [eax + edx + 8]
    ecx = (ecx) << (0x4u);       // original 005f7ae0 shl ecx, 4
    edi = (edi) << (0x4u);       // original 005f7ae3 shl edi, 4
    store32(args + 4u, edx);     // original 005f7ae6 mov dword ptr [ebp + 0xc], edx
L_005f7ae9:;
    edx = load32(args + 0u);    // original 005f7ae9 mov edx, dword ptr [ebp + 8]
    ebx = load32(frame - 0x8u); // original 005f7aec mov ebx, dword ptr [ebp - 8]
    edx = (edx) & (0x3u);       // original 005f7aef and edx, 3
    __asm__ volatile("flds (%0)" ::"r"(ebx + edx * 4u)
                     : "st", "memory"); // original 005f7af2 fld dword ptr [ebx + edx*4]
    edx = load32(args + 4u);            // original 005f7af5 mov edx, dword ptr [ebp + 0xc]
    __asm__ volatile("fsts (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f7af8 fst dword ptr [ebp + 0x10]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f7afb fld dword ptr [ebp - 0x54]
    __asm__ volatile("fadds (%0)" ::"r"(edx + 0xfffffff8u)
                     : "st", "memory"); // original 005f7afe fadd dword ptr [edx - 8]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df630))
                     : "st", "memory"); // original 005f7b01 fmul dword ptr [0x6df630]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f7b07 fstp dword ptr [ebp - 0x44]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f7b0a fld dword ptr [ebp - 0x50]
    __asm__ volatile("fadds (%0)" ::"r"(edx + 0xfffffffcu)
                     : "st", "memory"); // original 005f7b0d fadd dword ptr [edx - 4]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df630))
                     : "st", "memory"); // original 005f7b10 fmul dword ptr [0x6df630]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f7b16 fstp dword ptr [ebp - 0x40]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f7b19 fld dword ptr [ebp - 0x4c]
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f7b1c fadd dword ptr [edx]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df630))
                     : "st", "memory"); // original 005f7b1e fmul dword ptr [0x6df630]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f7b24 fstp dword ptr [ebp - 0x3c]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f7b27 fld dword ptr [ebp - 0x48]
    __asm__ volatile("fadds (%0)" ::"r"(edx + 0x4u)
                     : "st", "memory"); // original 005f7b2a fadd dword ptr [edx + 4]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bca1c))
                     : "st", "memory"); // original 005f7b2d fmul dword ptr [0x6bca1c]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f7b33 fstp dword ptr [ebp - 0x38]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f7b36 fld dword ptr [ebp - 0x44]
    __asm__ volatile("fadd %%st(1)" ::: "st", "memory"); // original 005f7b39 fadd st(1)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f7b3b fstp dword ptr [ebp - 0xc]
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f7b3e fstp st(0)
    __asm__ volatile("flds (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f7b40 fld dword ptr [ebp - 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f7b43 fistp dword ptr [ebp - 0x10]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f7b46 fld dword ptr [ebp - 0x40]
    edx = load32(frame - 0x10u);        // original 005f7b49 mov edx, dword ptr [ebp - 0x10]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f7b4c fadd dword ptr [ebp + 0x10]
    store32(frame - 0x34u, edx);        // original 005f7b4f mov dword ptr [ebp - 0x34], edx
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f7b52 fstp dword ptr [ebp - 0xc]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f7b55 fld dword ptr [ebp - 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f7b58 fistp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f7b5b fld dword ptr [ebp - 0x3c]
    edx = load32(frame - 0x14u);        // original 005f7b5e mov edx, dword ptr [ebp - 0x14]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f7b61 fadd dword ptr [ebp + 0x10]
    store32(frame - 0x30u, edx);        // original 005f7b64 mov dword ptr [ebp - 0x30], edx
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f7b67 fstp dword ptr [ebp - 0xc]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f7b6a fld dword ptr [ebp - 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f7b6d fistp dword ptr [ebp - 0x18]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f7b70 fld dword ptr [ebp - 0x38]
    edx = load32(frame - 0x18u);        // original 005f7b73 mov edx, dword ptr [ebp - 0x18]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f7b76 fadd dword ptr [ebp + 0x10]
    store32(frame - 0x2cu, edx);        // original 005f7b79 mov dword ptr [ebp - 0x2c], edx
    __asm__ volatile("fstps (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f7b7c fstp dword ptr [ebp + 0x10]
    __asm__ volatile("flds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f7b7f fld dword ptr [ebp + 0x10]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x1cu)
                     : "st", "memory"); // original 005f7b82 fistp dword ptr [ebp - 0x1c]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f7b85 cmp dword ptr [esi + 0x5c], 0
    ebx = load32(frame - 0x1cu); // original 005f7b89 mov ebx, dword ptr [ebp - 0x1c]
    store32(frame - 0x28u, ebx); // original 005f7b8c mov dword ptr [ebp - 0x28], ebx
    if (left == right)
        goto L_005f7cc7; // original 005f7b8f je 0x5f7cc7
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df62c))
                     : "st", "memory"); // original 005f7b95 fld dword ptr [0x6df62c]
    ebx = load32(esi + 0x5cu);          // original 005f7b9b mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f7b9e fild dword ptr [ebp - 0x34]
    ebx = ebx + edi + 0x10u;            // original 005f7ba1 lea ebx, [ebx + edi + 0x10]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f7ba5 fsubr dword ptr [ebp - 0x44]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7ba8 fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f7baa fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7bb0 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7bb2 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7bb4 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7bb6 mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f7bb9 fld dword ptr [0x6df418]
    ebx = ebx + eax + 0x10u;            // original 005f7bbf lea ebx, [ebx + eax + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7bc3 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7bc5 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7bc7 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7bc9 mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f7bcc fld dword ptr [0x6be980]
    ebx = ebx + ecx + 0x10u;            // original 005f7bd2 lea ebx, [ebx + ecx + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7bd6 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7bd8 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7bda fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7bdc mov ebx, dword ptr [esi + 0x5c]
    ebx = ebx + edi + 0x14u;            // original 005f7bdf lea ebx, [ebx + edi + 0x14]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f7be3 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f7be9 fstp dword ptr [ebp - 0x54]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f7bec fild dword ptr [ebp - 0x30]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f7bef fsubr dword ptr [ebp - 0x40]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7bf2 fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f7bf4 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7bfa fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7bfc fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7bfe fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7c00 mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f7c03 fld dword ptr [0x6df418]
    ebx = ebx + eax + 0x14u;            // original 005f7c09 lea ebx, [ebx + eax + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7c0d fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7c0f fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7c11 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7c13 mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f7c16 fld dword ptr [0x6be980]
    ebx = ebx + ecx + 0x14u;            // original 005f7c1c lea ebx, [ebx + ecx + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7c20 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7c22 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7c24 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7c26 mov ebx, dword ptr [esi + 0x5c]
    ebx = ebx + edi + 0x18u;            // original 005f7c29 lea ebx, [ebx + edi + 0x18]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f7c2d fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f7c33 fstp dword ptr [ebp - 0x50]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x2cu)
                     : "st", "memory"); // original 005f7c36 fild dword ptr [ebp - 0x2c]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f7c39 fsubr dword ptr [ebp - 0x3c]
    __asm__ volatile("fmulp %%st(1)" ::: "st", "memory"); // original 005f7c3c fmulp st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f7c3e fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7c44 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7c46 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7c48 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7c4a mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f7c4d fld dword ptr [0x6df418]
    ebx = ebx + eax + 0x18u;            // original 005f7c53 lea ebx, [ebx + eax + 0x18]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7c57 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7c59 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7c5b fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7c5d mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f7c60 fld dword ptr [0x6be980]
    ebx = ebx + ecx + 0x18u;            // original 005f7c66 lea ebx, [ebx + ecx + 0x18]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7c6a fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7c6c fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7c6e fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7c70 mov ebx, dword ptr [esi + 0x5c]
    ebx = ebx + edi + 0x1cu;            // original 005f7c73 lea ebx, [ebx + edi + 0x1c]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f7c77 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f7c7d fstp dword ptr [ebp - 0x4c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x28u)
                     : "st", "memory"); // original 005f7c80 fild dword ptr [ebp - 0x28]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f7c83 fsubr dword ptr [ebp - 0x38]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006c2bb4))
                     : "st", "memory"); // original 005f7c86 fmul dword ptr [0x6c2bb4]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f7c8c fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7c92 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7c94 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7c96 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7c98 mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f7c9b fld dword ptr [0x6df418]
    ebx = ebx + eax + 0x1cu;            // original 005f7ca1 lea ebx, [ebx + eax + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7ca5 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7ca7 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7ca9 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f7cab mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f7cae fld dword ptr [0x6be980]
    ebx = ebx + ecx + 0x1cu;            // original 005f7cb4 lea ebx, [ebx + ecx + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f7cb8 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7cba fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f7cbc fstp dword ptr [ebx]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f7cbe fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f7cc4 fstp dword ptr [ebp - 0x48]
L_005f7cc7:;
    ebx = load32(frame - 0x34u); // original 005f7cc7 mov ebx, dword ptr [ebp - 0x34]
    left = ebx;
    right = 0x1ffu; // original 005f7cca cmp ebx, 0x1ff
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7cd7; // original 005f7cd0 jl 0x5f7cd7
    ebx = 0x1ffu;        // original 005f7cd2 mov ebx, 0x1ff
L_005f7cd7:;
    left = ebx;
    right = 0xfffffe01u; // original 005f7cd7 cmp ebx, 0xfffffe01
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f7cf1; // original 005f7cdd jle 0x5f7cf1
    left = load32(frame - 0x34u);
    right = 0x1ffu; // original 005f7cdf cmp dword ptr [ebp - 0x34], 0x1ff
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7cf8;            // original 005f7ce6 jl 0x5f7cf8
    store32(frame - 0x34u, 0x1ffu); // original 005f7ce8 mov dword ptr [ebp - 0x34], 0x1ff
    goto L_005f7cf8;                // original 005f7cef jmp 0x5f7cf8
L_005f7cf1:;
    store32(frame - 0x34u, 0xfffffe01u); // original 005f7cf1 mov dword ptr [ebp - 0x34], 0xfffffe01
L_005f7cf8:;
    ebx = load32(frame - 0x30u); // original 005f7cf8 mov ebx, dword ptr [ebp - 0x30]
    left = ebx;
    right = 0x1ffu; // original 005f7cfb cmp ebx, 0x1ff
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7d08; // original 005f7d01 jl 0x5f7d08
    ebx = 0x1ffu;        // original 005f7d03 mov ebx, 0x1ff
L_005f7d08:;
    left = ebx;
    right = 0xfffffe01u; // original 005f7d08 cmp ebx, 0xfffffe01
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f7d22; // original 005f7d0e jle 0x5f7d22
    left = load32(frame - 0x30u);
    right = 0x1ffu; // original 005f7d10 cmp dword ptr [ebp - 0x30], 0x1ff
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7d29;            // original 005f7d17 jl 0x5f7d29
    store32(frame - 0x30u, 0x1ffu); // original 005f7d19 mov dword ptr [ebp - 0x30], 0x1ff
    goto L_005f7d29;                // original 005f7d20 jmp 0x5f7d29
L_005f7d22:;
    store32(frame - 0x30u, 0xfffffe01u); // original 005f7d22 mov dword ptr [ebp - 0x30], 0xfffffe01
L_005f7d29:;
    left = edx;
    right = 0x1ffu; // original 005f7d29 cmp edx, 0x1ff
    ebx = edx;      // original 005f7d2f mov ebx, edx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7d38; // original 005f7d31 jl 0x5f7d38
    ebx = 0x1ffu;        // original 005f7d33 mov ebx, 0x1ff
L_005f7d38:;
    left = ebx;
    right = 0xfffffe01u; // original 005f7d38 cmp ebx, 0xfffffe01
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f7d4d; // original 005f7d3e jle 0x5f7d4d
    ebx = 0x1ffu;        // original 005f7d40 mov ebx, 0x1ff
    left = edx;
    right = ebx; // original 005f7d45 cmp edx, ebx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7d52; // original 005f7d47 jl 0x5f7d52
    edx = ebx;           // original 005f7d49 mov edx, ebx
    goto L_005f7d52;     // original 005f7d4b jmp 0x5f7d52
L_005f7d4d:;
    edx = 0xfffffe01u; // original 005f7d4d mov edx, 0xfffffe01
L_005f7d52:;
    ebx = load32(frame - 0x28u); // original 005f7d52 mov ebx, dword ptr [ebp - 0x28]
    left = ebx;
    right = 0x3u; // original 005f7d55 cmp ebx, 3
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7d5d; // original 005f7d58 jl 0x5f7d5d
    pending = 0x3u;      // original 005f7d5a push 3
    ebx = pending;       // original 005f7d5c pop ebx
L_005f7d5d:;
    left = ebx;
    right = 0xfffffffdu; // original 005f7d5d cmp ebx, -3
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f7d6e;         // original 005f7d60 jle 0x5f7d6e
    ebx = load32(frame - 0x28u); // original 005f7d62 mov ebx, dword ptr [ebp - 0x28]
    left = ebx;
    right = 0x3u; // original 005f7d65 cmp ebx, 3
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f7d71; // original 005f7d68 jl 0x5f7d71
    pending = 0x3u;      // original 005f7d6a push 3
    goto L_005f7d70;     // original 005f7d6c jmp 0x5f7d70
L_005f7d6e:;
    pending = 0xfffffffdu; // original 005f7d6e push -3
L_005f7d70:;
    ebx = pending; // original 005f7d70 pop ebx
L_005f7d71:;
    edx = (edx) & (0x3ffu);                // original 005f7d71 and edx, 0x3ff
    ebx = (ebx) << (0xau);                 // original 005f7d77 shl ebx, 0xa
    edx = (edx) | (ebx);                   // original 005f7d7a or edx, ebx
    ebx = load32(frame - 0x30u);           // original 005f7d7c mov ebx, dword ptr [ebp - 0x30]
    edx = (edx) << (0xau);                 // original 005f7d7f shl edx, 0xa
    ebx = (ebx) & (0x3ffu);                // original 005f7d82 and ebx, 0x3ff
    edx = (edx) | (ebx);                   // original 005f7d88 or edx, ebx
    ebx = load32(frame - 0x34u);           // original 005f7d8a mov ebx, dword ptr [ebp - 0x34]
    edx = (edx) << (0xau);                 // original 005f7d8d shl edx, 0xa
    ebx = (ebx) & (0x3ffu);                // original 005f7d90 and ebx, 0x3ff
    edx = (edx) | (ebx);                   // original 005f7d96 or edx, ebx
    ebx = load32(frame - 0x4u);            // original 005f7d98 mov ebx, dword ptr [ebp - 4]
    store32(ebx, edx);                     // original 005f7d9b mov dword ptr [ebx], edx
    edx = load32(frame - 0x24u);           // original 005f7d9d mov edx, dword ptr [ebp - 0x24]
    ebx = (ebx) + (load32(frame - 0x20u)); // original 005f7da0 add ebx, dword ptr [ebp - 0x20]
    store32(args + 4u,
            (load32(args + 4u)) + (edx));       // original 005f7da3 add dword ptr [ebp + 0xc], edx
    eax = (eax) + (edx);                        // original 005f7da6 add eax, edx
    edi = (edi) + (edx);                        // original 005f7da8 add edi, edx
    ecx = (ecx) + (edx);                        // original 005f7daa add ecx, edx
    store32(args + 0u, load32(args + 0u) + 1u); // original 005f7dac inc dword ptr [ebp + 8]
    edx = load32(args + 0u);                    // original 005f7daf mov edx, dword ptr [ebp + 8]
    left = edx;
    right = load32(esi + 0x68u); // original 005f7db2 cmp edx, dword ptr [esi + 0x68]
    store32(frame - 0x4u, ebx);  // original 005f7db5 mov dword ptr [ebp - 4], ebx
    if (left < right)
        goto L_005f7ae9; // original 005f7db8 jb 0x5f7ae9
L_005f7dbe:;
    eax = load32(esi + 0x7cu); // original 005f7dbe mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f7dc1 mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f7dc4 fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f7dc7 pop edi
    ;                                   // C++ ABI restore ownership. // original 005f7dc8 pop esi
    ;                                   // C++ ABI restore ownership. // original 005f7dc9 pop ebx
    ;                                   // C++ frame ownership. // original 005f7dca leave
    return eax;                         // original 005f7dcb ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f79f4(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f79f4\n\taddl $8,%esp\n\tretl $12");
}

// Complete original 005f7ed9..005f82ae: signed Q16W16V16U16; original access widths/order retained.
extern "C" u32 recovered_005f7ed9(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x80];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x80u;
    ;          // C++ frame and ABI save ownership. // original 005f7ed9 mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f7edb push ebp
    ;          // C++ frame and ABI save ownership. // original 005f7edc mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f7ede sub esp, 0x5c
    ;          // C++ frame and ABI save ownership. // original 005f7ee1 push ebx
    ;          // C++ frame and ABI save ownership. // original 005f7ee2 push esi
    esi = ecx; // original 005f7ee3 mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f7ee5 cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f7ee9 push edi
    if (left == right)
        goto L_005f7ef7;         // original 005f7eea je 0x5f7ef7
    pending = load32(args + 8u); // original 005f7eec push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f7eef call 0x5f0da1
    store32(args + 8u, eax); // original 005f7ef4 mov dword ptr [ebp + 0x10], eax
L_005f7ef7:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f7ef7 cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f7f0a;         // original 005f7efb je 0x5f7f0a
    pending = load32(args + 8u); // original 005f7efd push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f7f00 mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f7f02 call 0x5f22d6
    store32(args + 8u, eax); // original 005f7f07 mov dword ptr [ebp + 0x10], eax
L_005f7f0a:;
    eax = load32(args + 0u);                     // original 005f7f0a mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f7f0d fldz
    edi = load32(esi + 0x68u); // original 005f7f0f mov edi, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x5cu)
                     : "st", "memory"); // original 005f7f12 fstp dword ptr [ebp - 0x5c]
    edx = load32(esi + 0x60u);          // original 005f7f15 mov edx, dword ptr [esi + 0x60]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f7f18 fldz
    ebx = load32(esi + 0x64u); // original 005f7f1a mov ebx, dword ptr [esi + 0x64]
    edx = (edx) * (eax);       // original 005f7f1d imul edx, eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x58u)
                     : "st", "memory");          // original 005f7f20 fstp dword ptr [ebp - 0x58]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f7f23 fldz
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory");          // original 005f7f25 fstp dword ptr [ebp - 0x54]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f7f28 fldz
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f7f2a fstp dword ptr [ebp - 0x50]
    store32(args + 0u, eax);            // original 005f7f2d mov dword ptr [ebp + 8], eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f7f30 and dword ptr [ebp + 8], 1
    ecx = edi + 0xffffffffu;               // original 005f7f34 lea ecx, [edi - 1]
    ecx = (ecx) * (load32(args + 0u));     // original 005f7f37 imul ecx, dword ptr [ebp + 8]
    ecx = edx + ecx * 8u;                  // original 005f7f3b lea ecx, [edx + ecx*8]
    edx = load32(args + 4u);               // original 005f7f3e mov edx, dword ptr [ebp + 0xc]
    ebx = (ebx) * (edx);                   // original 005f7f41 imul ebx, edx
    ecx = (ecx) + (ebx);                   // original 005f7f44 add ecx, ebx
    ecx = (ecx) + (load32(esi + 0x20u));   // original 005f7f46 add ecx, dword ptr [esi + 0x20]
    eax = (eax) & (0x3u);                  // original 005f7f49 and eax, 3
    edx = (edx) & (0x3u);                  // original 005f7f4c and edx, 3
    left = load32(args + 0u);
    right = 0x0u;                // original 005f7f4f cmp dword ptr [ebp + 8], 0
    store32(frame - 0x4u, ecx);  // original 005f7f53 mov dword ptr [ebp - 4], ecx
    ecx = load32(esi + 0x34u);   // original 005f7f56 mov ecx, dword ptr [esi + 0x34]
    eax = edx + eax * 8u;        // original 005f7f59 lea eax, [edx + eax*8]
    eax = ecx + eax * 4u;        // original 005f7f5c lea eax, [ecx + eax*4]
    store32(frame - 0x10u, eax); // original 005f7f5f mov dword ptr [ebp - 0x10], eax
    if (left != right)
        goto L_005f7f6b; // original 005f7f62 jne 0x5f7f6b
    ebx = 0u;            // original 005f7f64 xor ebx, ebx
    edi = 0u;            // original 005f7f66 xor edi, edi
    ebx = ebx + 1u;      // original 005f7f68 inc ebx
    goto L_005f7f6f;     // original 005f7f69 jmp 0x5f7f6f
L_005f7f6b:;
    edi = edi - 1u;              // original 005f7f6b dec edi
    ebx = (ebx) | (0xffffffffu); // original 005f7f6c or ebx, 0xffffffff
L_005f7f6f:;
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 0u)
                     : "st", "memory"); // original 005f7f6f fnstcw word ptr [ebp + 8]
    eax = load32(args + 0u);            // original 005f7f72 mov eax, dword ptr [ebp + 8]
    eax = (eax) | (0xc00u);             // original 005f7f75 or eax, 0xc00
    store32(args + 4u, eax);            // original 005f7f7a mov dword ptr [ebp + 0xc], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f7f7d fldcw word ptr [ebp + 0xc]
    eax = load32(args + 0u);            // original 005f7f80 mov eax, dword ptr [ebp + 8]
    store32(esi + 0x7cu, eax);          // original 005f7f83 mov dword ptr [esi + 0x7c], eax
    left = load32(esi + 0x5cu);
    right = 0x0u; // original 005f7f86 cmp dword ptr [esi + 0x5c], 0
    if (left == right)
        goto L_005f7f96;         // original 005f7f8a je 0x5f7f96
    pending = load32(args + 8u); // original 005f7f8c push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f7f8f mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f7f91 call 0x5f25f2
L_005f7f96:;
    store32(args + 0u,
            (load32(args + 0u)) & (0x0u)); // original 005f7f96 and dword ptr [ebp + 8], 0
    left = load32(esi + 0x68u);
    right = 0x0u; // original 005f7f9a cmp dword ptr [esi + 0x68], 0
    if (left <= right)
        goto L_005f829e;         // original 005f7f9e jbe 0x5f829e
    eax = ebx;                   // original 005f7fa4 mov eax, ebx
    eax = (eax) << (0x3u);       // original 005f7fa6 shl eax, 3
    store32(frame - 0x28u, eax); // original 005f7fa9 mov dword ptr [ebp - 0x28], eax
    eax = ebx;                   // original 005f7fac mov eax, ebx
    eax = (eax) << (0x4u);       // original 005f7fae shl eax, 4
    ecx = edi;                   // original 005f7fb1 mov ecx, edi
    edx = ebx + edi;             // original 005f7fb3 lea edx, [ebx + edi]
    store32(frame - 0x2cu, eax); // original 005f7fb6 mov dword ptr [ebp - 0x2c], eax
    eax = load32(args + 8u);     // original 005f7fb9 mov eax, dword ptr [ebp + 0x10]
    ecx = (ecx) << (0x4u);       // original 005f7fbc shl ecx, 4
    edx = (edx) << (0x4u);       // original 005f7fbf shl edx, 4
    edi = (edi) - (ebx);         // original 005f7fc2 sub edi, ebx
    edi = (edi) << (0x4u);       // original 005f7fc4 shl edi, 4
    eax = ecx + eax + 0x8u;      // original 005f7fc7 lea eax, [ecx + eax + 8]
    store32(frame - 0xcu, edx);  // original 005f7fcb mov dword ptr [ebp - 0xc], edx
    store32(frame - 0x8u, edi);  // original 005f7fce mov dword ptr [ebp - 8], edi
    store32(args + 4u, eax);     // original 005f7fd1 mov dword ptr [ebp + 0xc], eax
L_005f7fd4:;
    eax = load32(args + 0u); // original 005f7fd4 mov eax, dword ptr [ebp + 8]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df5d8))
                     : "st", "memory"); // original 005f7fd7 fld dword ptr [0x6df5d8]
    ebx = load32(frame - 0x10u);        // original 005f7fdd mov ebx, dword ptr [ebp - 0x10]
    eax = (eax) & (0x3u);               // original 005f7fe0 and eax, 3
    __asm__ volatile("flds (%0)" ::"r"(ebx + eax * 4u)
                     : "st", "memory"); // original 005f7fe3 fld dword ptr [ebx + eax*4]
    eax = load32(args + 4u);            // original 005f7fe6 mov eax, dword ptr [ebp + 0xc]
    __asm__ volatile("fsts (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f7fe9 fst dword ptr [ebp + 0x10]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x5cu)
                     : "st", "memory"); // original 005f7fec fld dword ptr [ebp - 0x5c]
    __asm__ volatile("fadds (%0)" ::"r"(eax + 0xfffffff8u)
                     : "st", "memory"); // original 005f7fef fadd dword ptr [eax - 8]
    __asm__ volatile("fmul %%st(2)" ::: "st", "memory"); // original 005f7ff2 fmul st(2)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f7ff4 fstp dword ptr [ebp - 0x4c]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x58u)
                     : "st", "memory"); // original 005f7ff7 fld dword ptr [ebp - 0x58]
    __asm__ volatile("fadds (%0)" ::"r"(eax + 0xfffffffcu)
                     : "st", "memory"); // original 005f7ffa fadd dword ptr [eax - 4]
    __asm__ volatile("fmul %%st(2)" ::: "st", "memory"); // original 005f7ffd fmul st(2)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f7fff fstp dword ptr [ebp - 0x48]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f8002 fld dword ptr [ebp - 0x54]
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory");                  // original 005f8005 fadd dword ptr [eax]
    __asm__ volatile("fmul %%st(2)" ::: "st", "memory"); // original 005f8007 fmul st(2)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f8009 fstp dword ptr [ebp - 0x44]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f800c fld dword ptr [ebp - 0x50]
    __asm__ volatile("fadds (%0)" ::"r"(eax + 0x4u)
                     : "st", "memory"); // original 005f800f fadd dword ptr [eax + 4]
    __asm__ volatile("fmul %%st(2)" ::: "st", "memory"); // original 005f8012 fmul st(2)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f8014 fstp dword ptr [ebp - 0x40]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f8017 fld dword ptr [ebp - 0x4c]
    __asm__ volatile("fadd %%st(1)" ::: "st", "memory"); // original 005f801a fadd st(1)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f801c fstp dword ptr [ebp - 0x14]
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f801f fstp st(0)
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f8021 fstp st(0)
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f8023 fld dword ptr [ebp - 0x14]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f8026 fistp dword ptr [ebp - 0x18]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f8029 fld dword ptr [ebp - 0x48]
    ebx = load32(frame - 0x18u);        // original 005f802c mov ebx, dword ptr [ebp - 0x18]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f802f fadd dword ptr [ebp + 0x10]
    store32(frame - 0x3cu, ebx);        // original 005f8032 mov dword ptr [ebp - 0x3c], ebx
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f8035 fstp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f8038 fld dword ptr [ebp - 0x14]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x1cu)
                     : "st", "memory"); // original 005f803b fistp dword ptr [ebp - 0x1c]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f803e fld dword ptr [ebp - 0x44]
    eax = load32(frame - 0x1cu);        // original 005f8041 mov eax, dword ptr [ebp - 0x1c]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f8044 fadd dword ptr [ebp + 0x10]
    store32(frame - 0x38u, eax);        // original 005f8047 mov dword ptr [ebp - 0x38], eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f804a fstp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f804d fld dword ptr [ebp - 0x14]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x20u)
                     : "st", "memory"); // original 005f8050 fistp dword ptr [ebp - 0x20]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f8053 fld dword ptr [ebp - 0x40]
    eax = load32(frame - 0x20u);        // original 005f8056 mov eax, dword ptr [ebp - 0x20]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f8059 fadd dword ptr [ebp + 0x10]
    store32(frame - 0x34u, eax);        // original 005f805c mov dword ptr [ebp - 0x34], eax
    __asm__ volatile("fstps (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f805f fstp dword ptr [ebp + 0x10]
    __asm__ volatile("flds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f8062 fld dword ptr [ebp + 0x10]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x24u)
                     : "st", "memory"); // original 005f8065 fistp dword ptr [ebp - 0x24]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f8068 cmp dword ptr [esi + 0x5c], 0
    eax = load32(frame - 0x24u); // original 005f806c mov eax, dword ptr [ebp - 0x24]
    store32(frame - 0x30u, eax); // original 005f806f mov dword ptr [ebp - 0x30], eax
    if (left == right)
        goto L_005f81a6; // original 005f8072 je 0x5f81a6
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bbc78))
                     : "st", "memory"); // original 005f8078 fld dword ptr [0x6bbc78]
    eax = load32(esi + 0x5cu);          // original 005f807e mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f8081 fild dword ptr [ebp - 0x3c]
    eax = eax + edi + 0x10u;            // original 005f8084 lea eax, [eax + edi + 0x10]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f8088 fsubr dword ptr [ebp - 0x4c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f808b fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f808d fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f8093 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8095 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8097 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f8099 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f809c fld dword ptr [0x6df418]
    eax = eax + ecx + 0x10u;            // original 005f80a2 lea eax, [eax + ecx + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f80a6 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f80a8 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f80aa fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f80ac mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f80af fld dword ptr [0x6be980]
    eax = eax + edx + 0x10u;            // original 005f80b5 lea eax, [eax + edx + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f80b9 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f80bb fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f80bd fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f80bf mov eax, dword ptr [esi + 0x5c]
    eax = eax + edi + 0x14u;            // original 005f80c2 lea eax, [eax + edi + 0x14]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f80c6 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x5cu)
                     : "st", "memory"); // original 005f80cc fstp dword ptr [ebp - 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f80cf fild dword ptr [ebp - 0x38]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f80d2 fsubr dword ptr [ebp - 0x48]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f80d5 fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f80d7 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f80dd fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f80df fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f80e1 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f80e3 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f80e6 fld dword ptr [0x6df418]
    eax = eax + ecx + 0x14u;            // original 005f80ec lea eax, [eax + ecx + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f80f0 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f80f2 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f80f4 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f80f6 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f80f9 fld dword ptr [0x6be980]
    eax = eax + edx + 0x14u;            // original 005f80ff lea eax, [eax + edx + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f8103 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8105 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8107 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f8109 mov eax, dword ptr [esi + 0x5c]
    eax = eax + edi + 0x18u;            // original 005f810c lea eax, [eax + edi + 0x18]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f8110 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x58u)
                     : "st", "memory"); // original 005f8116 fstp dword ptr [ebp - 0x58]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f8119 fild dword ptr [ebp - 0x34]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f811c fsubr dword ptr [ebp - 0x44]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f811f fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f8121 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f8127 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8129 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f812b fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f812d mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f8130 fld dword ptr [0x6df418]
    eax = eax + ecx + 0x18u;            // original 005f8136 lea eax, [eax + ecx + 0x18]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f813a fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f813c fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f813e fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f8140 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f8143 fld dword ptr [0x6be980]
    eax = eax + edx + 0x18u;            // original 005f8149 lea eax, [eax + edx + 0x18]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f814d fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f814f fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8151 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f8153 mov eax, dword ptr [esi + 0x5c]
    eax = eax + edi + 0x1cu;            // original 005f8156 lea eax, [eax + edi + 0x1c]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f815a fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f8160 fstp dword ptr [ebp - 0x54]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f8163 fild dword ptr [ebp - 0x30]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f8166 fsubr dword ptr [ebp - 0x40]
    __asm__ volatile("fmulp %%st(1)" ::: "st", "memory"); // original 005f8169 fmulp st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f816b fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f8171 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8173 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8175 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f8177 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f817a fld dword ptr [0x6df418]
    eax = eax + ecx + 0x1cu;            // original 005f8180 lea eax, [eax + ecx + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f8184 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8186 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8188 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f818a mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f818d fld dword ptr [0x6be980]
    eax = eax + edx + 0x1cu;            // original 005f8193 lea eax, [eax + edx + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f8197 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8199 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f819b fstp dword ptr [eax]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f819d fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f81a3 fstp dword ptr [ebp - 0x50]
L_005f81a6:;
    eax = 0x7fffu; // original 005f81a6 mov eax, 0x7fff
    left = ebx;
    right = eax; // original 005f81ab cmp ebx, eax
    edi = ebx;   // original 005f81ad mov edi, ebx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f81b3; // original 005f81af jl 0x5f81b3
    edi = eax;           // original 005f81b1 mov edi, eax
L_005f81b3:;
    edx = 0xffff8001u; // original 005f81b3 mov edx, 0xffff8001
    left = edi;
    right = edx; // original 005f81b8 cmp edi, edx
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f81c5; // original 005f81ba jle 0x5f81c5
    left = ebx;
    right = eax; // original 005f81bc cmp ebx, eax
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f81c8;         // original 005f81be jl 0x5f81c8
    store32(frame - 0x3cu, eax); // original 005f81c0 mov dword ptr [ebp - 0x3c], eax
    goto L_005f81c8;             // original 005f81c3 jmp 0x5f81c8
L_005f81c5:;
    store32(frame - 0x3cu, edx); // original 005f81c5 mov dword ptr [ebp - 0x3c], edx
L_005f81c8:;
    left = load32(frame - 0x38u);
    right = eax;                 // original 005f81c8 cmp dword ptr [ebp - 0x38], eax
    edi = load32(frame - 0x38u); // original 005f81cb mov edi, dword ptr [ebp - 0x38]
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f81d2; // original 005f81ce jl 0x5f81d2
    edi = eax;           // original 005f81d0 mov edi, eax
L_005f81d2:;
    left = edi;
    right = edx; // original 005f81d2 cmp edi, edx
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f81e0; // original 005f81d4 jle 0x5f81e0
    left = load32(frame - 0x38u);
    right = eax; // original 005f81d6 cmp dword ptr [ebp - 0x38], eax
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f81e3;         // original 005f81d9 jl 0x5f81e3
    store32(frame - 0x38u, eax); // original 005f81db mov dword ptr [ebp - 0x38], eax
    goto L_005f81e3;             // original 005f81de jmp 0x5f81e3
L_005f81e0:;
    store32(frame - 0x38u, edx); // original 005f81e0 mov dword ptr [ebp - 0x38], edx
L_005f81e3:;
    left = load32(frame - 0x34u);
    right = eax;                 // original 005f81e3 cmp dword ptr [ebp - 0x34], eax
    edi = load32(frame - 0x34u); // original 005f81e6 mov edi, dword ptr [ebp - 0x34]
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f81ed; // original 005f81e9 jl 0x5f81ed
    edi = eax;           // original 005f81eb mov edi, eax
L_005f81ed:;
    left = edi;
    right = edx; // original 005f81ed cmp edi, edx
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f81fb; // original 005f81ef jle 0x5f81fb
    left = load32(frame - 0x34u);
    right = eax; // original 005f81f1 cmp dword ptr [ebp - 0x34], eax
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f81fe;         // original 005f81f4 jl 0x5f81fe
    store32(frame - 0x34u, eax); // original 005f81f6 mov dword ptr [ebp - 0x34], eax
    goto L_005f81fe;             // original 005f81f9 jmp 0x5f81fe
L_005f81fb:;
    store32(frame - 0x34u, edx); // original 005f81fb mov dword ptr [ebp - 0x34], edx
L_005f81fe:;
    left = load32(frame - 0x30u);
    right = eax;                 // original 005f81fe cmp dword ptr [ebp - 0x30], eax
    edi = load32(frame - 0x30u); // original 005f8201 mov edi, dword ptr [ebp - 0x30]
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f8208; // original 005f8204 jl 0x5f8208
    edi = eax;           // original 005f8206 mov edi, eax
L_005f8208:;
    left = edi;
    right = edx; // original 005f8208 cmp edi, edx
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f8216; // original 005f820a jle 0x5f8216
    left = load32(frame - 0x30u);
    right = eax; // original 005f820c cmp dword ptr [ebp - 0x30], eax
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f8219;         // original 005f820f jl 0x5f8219
    store32(frame - 0x30u, eax); // original 005f8211 mov dword ptr [ebp - 0x30], eax
    goto L_005f8219;             // original 005f8214 jmp 0x5f8219
L_005f8216:;
    store32(frame - 0x30u, edx); // original 005f8216 mov dword ptr [ebp - 0x30], edx
L_005f8219:;
    eax = load32(frame - 0x30u); // original 005f8219 mov eax, dword ptr [ebp - 0x30]
    edi = 0xffffu;               // original 005f821c mov edi, 0xffff
    eax = (eax) & (edi);         // original 005f8221 and eax, edi
    edx = static_cast<int32_t>(eax) < 0 ? 0xffffffffu : 0u; // original 005f8223 cdq
    edx = (edx << (0x10u & 31u)) |
          (eax >> (32u - (0x10u & 31u))); // original 005f8224 shld edx, eax, 0x10
    eax = (eax) << (0x10u);               // original 005f8228 shl eax, 0x10
    ebx = eax;                            // original 005f822b mov ebx, eax
    eax = edx;                            // original 005f822d mov eax, edx
    store32(args + 8u, eax);              // original 005f822f mov dword ptr [ebp + 0x10], eax
    eax = load32(frame - 0x34u);          // original 005f8232 mov eax, dword ptr [ebp - 0x34]
    eax = (eax) & (edi);                  // original 005f8235 and eax, edi
    edx = static_cast<int32_t>(eax) < 0 ? 0xffffffffu : 0u; // original 005f8237 cdq
    ebx = (ebx) | (eax);                                    // original 005f8238 or ebx, eax
    eax = load32(args + 8u); // original 005f823a mov eax, dword ptr [ebp + 0x10]
    eax = (eax) | (edx);     // original 005f823d or eax, edx
    eax = (eax << (0x10u & 31u)) |
          (ebx >> (32u - (0x10u & 31u))); // original 005f823f shld eax, ebx, 0x10
    edi = eax;                            // original 005f8243 mov edi, eax
    eax = load32(frame - 0x38u);          // original 005f8245 mov eax, dword ptr [ebp - 0x38]
    eax = (eax) & (0xffffu);              // original 005f8248 and eax, 0xffff
    edx = static_cast<int32_t>(eax) < 0 ? 0xffffffffu : 0u; // original 005f824d cdq
    edi = (edi) | (edx);                                    // original 005f824e or edi, edx
    ebx = (ebx) << (0x10u);                                 // original 005f8250 shl ebx, 0x10
    ebx = (ebx) | (eax);                                    // original 005f8253 or ebx, eax
    eax = load32(frame - 0x3cu); // original 005f8255 mov eax, dword ptr [ebp - 0x3c]
    edi = (edi << (0x10u & 31u)) |
          (ebx >> (32u - (0x10u & 31u)));                   // original 005f8258 shld edi, ebx, 0x10
    eax = (eax) & (0xffffu);                                // original 005f825c and eax, 0xffff
    edx = static_cast<int32_t>(eax) < 0 ? 0xffffffffu : 0u; // original 005f8261 cdq
    edi = (edi) | (edx);                                    // original 005f8262 or edi, edx
    edx = load32(frame - 0xcu);            // original 005f8264 mov edx, dword ptr [ebp - 0xc]
    ebx = (ebx) << (0x10u);                // original 005f8267 shl ebx, 0x10
    ebx = (ebx) | (eax);                   // original 005f826a or ebx, eax
    eax = load32(frame - 0x4u);            // original 005f826c mov eax, dword ptr [ebp - 4]
    store32(eax + 0x4u, edi);              // original 005f826f mov dword ptr [eax + 4], edi
    edi = load32(frame - 0x8u);            // original 005f8272 mov edi, dword ptr [ebp - 8]
    store32(eax, ebx);                     // original 005f8275 mov dword ptr [eax], ebx
    eax = (eax) + (load32(frame - 0x28u)); // original 005f8277 add eax, dword ptr [ebp - 0x28]
    store32(frame - 0x4u, eax);            // original 005f827a mov dword ptr [ebp - 4], eax
    eax = load32(frame - 0x2cu);           // original 005f827d mov eax, dword ptr [ebp - 0x2c]
    store32(args + 4u,
            (load32(args + 4u)) + (eax));       // original 005f8280 add dword ptr [ebp + 0xc], eax
    edi = (edi) + (eax);                        // original 005f8283 add edi, eax
    edx = (edx) + (eax);                        // original 005f8285 add edx, eax
    ecx = (ecx) + (eax);                        // original 005f8287 add ecx, eax
    store32(args + 0u, load32(args + 0u) + 1u); // original 005f8289 inc dword ptr [ebp + 8]
    eax = load32(args + 0u);                    // original 005f828c mov eax, dword ptr [ebp + 8]
    left = eax;
    right = load32(esi + 0x68u); // original 005f828f cmp eax, dword ptr [esi + 0x68]
    store32(frame - 0x8u, edi);  // original 005f8292 mov dword ptr [ebp - 8], edi
    store32(frame - 0xcu, edx);  // original 005f8295 mov dword ptr [ebp - 0xc], edx
    if (left < right)
        goto L_005f7fd4; // original 005f8298 jb 0x5f7fd4
L_005f829e:;
    eax = load32(esi + 0x7cu); // original 005f829e mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f82a1 mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f82a4 fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f82a7 pop edi
    ;                                   // C++ ABI restore ownership. // original 005f82a8 pop esi
    ;                                   // C++ ABI restore ownership. // original 005f82a9 pop ebx
    ;                                   // C++ frame ownership. // original 005f82aa leave
    return eax;                         // original 005f82ab ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f7ed9(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f7ed9\n\taddl $8,%esp\n\tretl $12");
}

// Complete original 005f82f0..005f8560: signed V16U16; original access widths/order retained.
extern "C" u32 recovered_005f82f0(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x80];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x80u;
    ;          // C++ frame and ABI save ownership. // original 005f82f0 mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f82f2 push ebp
    ;          // C++ frame and ABI save ownership. // original 005f82f3 mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f82f5 sub esp, 0x54
    ;          // C++ frame and ABI save ownership. // original 005f82f8 push ebx
    ;          // C++ frame and ABI save ownership. // original 005f82f9 push esi
    esi = ecx; // original 005f82fa mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f82fc cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f8300 push edi
    if (left == right)
        goto L_005f830e;         // original 005f8301 je 0x5f830e
    pending = load32(args + 8u); // original 005f8303 push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f8306 call 0x5f0da1
    store32(args + 8u, eax); // original 005f830b mov dword ptr [ebp + 0x10], eax
L_005f830e:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f830e cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f8321;         // original 005f8312 je 0x5f8321
    pending = load32(args + 8u); // original 005f8314 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f8317 mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f8319 call 0x5f22d6
    store32(args + 8u, eax); // original 005f831e mov dword ptr [ebp + 0x10], eax
L_005f8321:;
    eax = load32(args + 0u);                     // original 005f8321 mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f8324 fldz
    ebx = load32(esi + 0x68u); // original 005f8326 mov ebx, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f8329 fstp dword ptr [ebp - 0x44]
    edx = load32(esi + 0x60u);          // original 005f832c mov edx, dword ptr [esi + 0x60]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f832f fldz
    edi = load32(esi + 0x64u); // original 005f8331 mov edi, dword ptr [esi + 0x64]
    edx = (edx) * (eax);       // original 005f8334 imul edx, eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f8337 fstp dword ptr [ebp - 0x40]
    store32(args + 0u, eax);            // original 005f833a mov dword ptr [ebp + 8], eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f833d and dword ptr [ebp + 8], 1
    ecx = ebx + 0xffffffffu;               // original 005f8341 lea ecx, [ebx - 1]
    ecx = (ecx) * (load32(args + 0u));     // original 005f8344 imul ecx, dword ptr [ebp + 8]
    edx = edx + ecx * 2u;                  // original 005f8348 lea edx, [edx + ecx*2]
    ecx = load32(args + 4u);               // original 005f834b mov ecx, dword ptr [ebp + 0xc]
    edi = (edi) * (ecx);                   // original 005f834e imul edi, ecx
    eax = (eax) & (0x3u);                  // original 005f8351 and eax, 3
    ecx = (ecx) & (0x3u);                  // original 005f8354 and ecx, 3
    edx = (edx) + (edi);                   // original 005f8357 add edx, edi
    edx = (edx) + (load32(esi + 0x20u));   // original 005f8359 add edx, dword ptr [esi + 0x20]
    eax = ecx + eax * 8u;                  // original 005f835c lea eax, [ecx + eax*8]
    ecx = load32(esi + 0x34u);             // original 005f835f mov ecx, dword ptr [esi + 0x34]
    edi = 0u;                              // original 005f8362 xor edi, edi
    left = load32(args + 0u);
    right = edi;                // original 005f8364 cmp dword ptr [ebp + 8], edi
    eax = ecx + eax * 4u;       // original 005f8367 lea eax, [ecx + eax*4]
    store32(frame - 0x8u, edx); // original 005f836a mov dword ptr [ebp - 8], edx
    store32(frame - 0xcu, eax); // original 005f836d mov dword ptr [ebp - 0xc], eax
    if (left != right)
        goto L_005f837d;      // original 005f8370 jne 0x5f837d
    ebx = 0u;                 // original 005f8372 xor ebx, ebx
    store32(args + 0u, 0x1u); // original 005f8374 mov dword ptr [ebp + 8], 1
    goto L_005f8382;          // original 005f837b jmp 0x5f8382
L_005f837d:;
    ebx = ebx - 1u; // original 005f837d dec ebx
    store32(args + 0u, (load32(args + 0u)) |
                           (0xffffffffu)); // original 005f837e or dword ptr [ebp + 8], 0xffffffff
L_005f8382:;
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f8382 fnstcw word ptr [ebp + 0xc]
    eax = load32(args + 4u);            // original 005f8385 mov eax, dword ptr [ebp + 0xc]
    eax = (eax) | (0xc00u);             // original 005f8388 or eax, 0xc00
    store32(frame - 0x4u, eax);         // original 005f838d mov dword ptr [ebp - 4], eax
    __asm__ volatile("fldcw (%0)" ::"r"(frame - 0x4u)
                     : "st", "memory"); // original 005f8390 fldcw word ptr [ebp - 4]
    eax = load32(args + 4u);            // original 005f8393 mov eax, dword ptr [ebp + 0xc]
    store32(esi + 0x7cu, eax);          // original 005f8396 mov dword ptr [esi + 0x7c], eax
    left = load32(esi + 0x5cu);
    right = edi; // original 005f8399 cmp dword ptr [esi + 0x5c], edi
    if (left == right)
        goto L_005f83a8;         // original 005f839c je 0x5f83a8
    pending = load32(args + 8u); // original 005f839e push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f83a1 mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f83a3 call 0x5f25f2
L_005f83a8:;
    left = load32(esi + 0x68u);
    right = edi;                // original 005f83a8 cmp dword ptr [esi + 0x68], edi
    store32(frame - 0x4u, edi); // original 005f83ab mov dword ptr [ebp - 4], edi
    if (left <= right)
        goto L_005f8550;         // original 005f83ae jbe 0x5f8550
    eax = load32(args + 0u);     // original 005f83b4 mov eax, dword ptr [ebp + 8]
    ecx = load32(args + 0u);     // original 005f83b7 mov ecx, dword ptr [ebp + 8]
    eax = (eax) + (eax);         // original 005f83ba add eax, eax
    store32(frame - 0x20u, eax); // original 005f83bc mov dword ptr [ebp - 0x20], eax
    eax = ecx;                   // original 005f83bf mov eax, ecx
    eax = (eax) << (0x4u);       // original 005f83c1 shl eax, 4
    edi = ebx;                   // original 005f83c4 mov edi, ebx
    store32(frame - 0x24u, eax); // original 005f83c6 mov dword ptr [ebp - 0x24], eax
    eax = ecx + ebx;             // original 005f83c9 lea eax, [ecx + ebx]
    eax = (eax) << (0x4u);       // original 005f83cc shl eax, 4
    ebx = (ebx) - (ecx);         // original 005f83cf sub ebx, ecx
    edi = (edi) << (0x4u);       // original 005f83d1 shl edi, 4
    ebx = (ebx) << (0x4u);       // original 005f83d4 shl ebx, 4
    store32(args + 4u, eax);     // original 005f83d7 mov dword ptr [ebp + 0xc], eax
    store32(args + 0u, ebx);     // original 005f83da mov dword ptr [ebp + 8], ebx
L_005f83dd:;
    eax = load32(args + 8u); // original 005f83dd mov eax, dword ptr [ebp + 0x10]
    ebx = edi + eax;         // original 005f83e0 lea ebx, [edi + eax]
    pending = ebx;           // original 005f83e3 push ebx
    pending = ebx;           // original 005f83e4 push ebx
    eax = reinterpret_cast<u32>(
        FUN_005e40eb(reinterpret_cast<float*>(pending),
                     reinterpret_cast<const float*>(pending))); // original 005f83e5 call 0x5e40eb
    eax = load32(frame - 0x4u); // original 005f83ea mov eax, dword ptr [ebp - 4]
    ecx = load32(frame - 0xcu); // original 005f83ed mov ecx, dword ptr [ebp - 0xc]
    eax = (eax) & (0x3u);       // original 005f83f0 and eax, 3
    __asm__ volatile("flds (%0)" ::"r"(ecx + eax * 4u)
                     : "st", "memory"); // original 005f83f3 fld dword ptr [ecx + eax*4]
    __asm__ volatile("fsts (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f83f6 fst dword ptr [ebp - 0x18]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df434))
                     : "st", "memory"); // original 005f83f9 fld dword ptr [0x6df434]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f83ff fld dword ptr [ebp - 0x44]
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory");                  // original 005f8402 fadd dword ptr [ebx]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f8404 fmul st(1)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f8406 fstp dword ptr [ebp - 0x34]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f8409 fld dword ptr [ebp - 0x40]
    __asm__ volatile("fadds (%0)" ::"r"(ebx + 0x4u)
                     : "st", "memory"); // original 005f840c fadd dword ptr [ebx + 4]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f840f fmul st(1)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f8411 fstp dword ptr [ebp - 0x30]
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f8414 fstp st(0)
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f8416 fld dword ptr [ebp - 0x34]
    __asm__ volatile("fadd %%st(1)" ::: "st", "memory"); // original 005f8419 fadd st(1)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f841b fstp dword ptr [ebp - 0x10]
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f841e fstp st(0)
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f8420 fld dword ptr [ebp - 0x10]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f8423 fistp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f8426 fld dword ptr [ebp - 0x30]
    edx = load32(frame - 0x14u);        // original 005f8429 mov edx, dword ptr [ebp - 0x14]
    __asm__ volatile("fadds (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f842c fadd dword ptr [ebp - 0x18]
    store32(frame - 0x54u, edx);        // original 005f842f mov dword ptr [ebp - 0x54], edx
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f8432 fstp dword ptr [ebp - 0x18]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f8435 fld dword ptr [ebp - 0x18]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x1cu)
                     : "st", "memory"); // original 005f8438 fistp dword ptr [ebp - 0x1c]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f843b cmp dword ptr [esi + 0x5c], 0
    ecx = load32(frame - 0x1cu); // original 005f843f mov ecx, dword ptr [ebp - 0x1c]
    store32(frame - 0x50u, ecx); // original 005f8442 mov dword ptr [ebp - 0x50], ecx
    if (left == right)
        goto L_005f84f1; // original 005f8445 je 0x5f84f1
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df430))
                     : "st", "memory"); // original 005f844b fld dword ptr [0x6df430]
    eax = load32(esi + 0x5cu);          // original 005f8451 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f8454 fild dword ptr [ebp - 0x54]
    ebx = load32(args + 0u);            // original 005f8457 mov ebx, dword ptr [ebp + 8]
    eax = eax + ebx + 0x10u;            // original 005f845a lea eax, [eax + ebx + 0x10]
    ebx = load32(args + 4u);            // original 005f845e mov ebx, dword ptr [ebp + 0xc]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f8461 fsubr dword ptr [ebp - 0x34]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f8464 fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f8466 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f846c fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f846e fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8470 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f8472 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f8475 fld dword ptr [0x6df418]
    eax = edi + eax + 0x10u;            // original 005f847b lea eax, [edi + eax + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f847f fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8481 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8483 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f8485 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f8488 fld dword ptr [0x6be980]
    eax = eax + ebx + 0x10u;            // original 005f848e lea eax, [eax + ebx + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f8492 fmul st(1)
    ebx = load32(args + 0u); // original 005f8494 mov ebx, dword ptr [ebp + 8]
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8497 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f8499 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f849b mov eax, dword ptr [esi + 0x5c]
    eax = eax + ebx + 0x14u;            // original 005f849e lea eax, [eax + ebx + 0x14]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f84a2 fmul qword ptr [0x6df410]
    ebx = load32(args + 4u);            // original 005f84a8 mov ebx, dword ptr [ebp + 0xc]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f84ab fstp dword ptr [ebp - 0x44]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f84ae fild dword ptr [ebp - 0x50]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f84b1 fsubr dword ptr [ebp - 0x30]
    __asm__ volatile("fmulp %%st(1)" ::: "st", "memory"); // original 005f84b4 fmulp st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f84b6 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f84bc fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f84be fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f84c0 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f84c2 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f84c5 fld dword ptr [0x6df418]
    eax = edi + eax + 0x14u;            // original 005f84cb lea eax, [edi + eax + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f84cf fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f84d1 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f84d3 fstp dword ptr [eax]
    eax = load32(esi + 0x5cu);          // original 005f84d5 mov eax, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f84d8 fld dword ptr [0x6be980]
    eax = eax + ebx + 0x14u;            // original 005f84de lea eax, [eax + ebx + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f84e2 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f84e4 fadd dword ptr [eax]
    __asm__ volatile("fstps (%0)" ::"r"(eax)
                     : "st", "memory"); // original 005f84e6 fstp dword ptr [eax]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f84e8 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f84ee fstp dword ptr [ebp - 0x40]
L_005f84f1:;
    pending = 0x7fu; // original 005f84f1 push 0x7f
    ebx = pending;   // original 005f84f3 pop ebx
    left = edx;
    right = ebx; // original 005f84f4 cmp edx, ebx
    eax = edx;   // original 005f84f6 mov eax, edx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f84fc; // original 005f84f8 jl 0x5f84fc
    eax = ebx;           // original 005f84fa mov eax, ebx
L_005f84fc:;
    left = eax;
    right = 0xffffff81u; // original 005f84fc cmp eax, -0x7f
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f8509; // original 005f84ff jle 0x5f8509
    left = edx;
    right = ebx; // original 005f8501 cmp edx, ebx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f850c; // original 005f8503 jl 0x5f850c
    edx = ebx;           // original 005f8505 mov edx, ebx
    goto L_005f850c;     // original 005f8507 jmp 0x5f850c
L_005f8509:;
    pending = 0xffffff81u; // original 005f8509 push -0x7f
    edx = pending;         // original 005f850b pop edx
L_005f850c:;
    left = ecx;
    right = ebx; // original 005f850c cmp ecx, ebx
    eax = ecx;   // original 005f850e mov eax, ecx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f8514; // original 005f8510 jl 0x5f8514
    eax = ebx;           // original 005f8512 mov eax, ebx
L_005f8514:;
    left = eax;
    right = 0xffffff81u; // original 005f8514 cmp eax, -0x7f
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f8521; // original 005f8517 jle 0x5f8521
    left = ecx;
    right = ebx; // original 005f8519 cmp ecx, ebx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f8524; // original 005f851b jl 0x5f8524
    ecx = ebx;           // original 005f851d mov ecx, ebx
    goto L_005f8524;     // original 005f851f jmp 0x5f8524
L_005f8521:;
    pending = 0xffffff81u; // original 005f8521 push -0x7f
    ecx = pending;         // original 005f8523 pop ecx
L_005f8524:;
    eax = load32(frame - 0x8u); // original 005f8524 mov eax, dword ptr [ebp - 8]
    edx = (edx & 0xffff0000u) | (((edx & 0xffu)) & 0xffffu);     // original 005f8527 movzx dx, dl
    edx = (edx & 0xffff00ffu) | ((((ecx & 0xffu)) & 255u) << 8); // original 005f852b mov dh, cl
    store16(eax, (edx & 0xffffu));         // original 005f852d mov word ptr [eax], dx
    eax = (eax) + (load32(frame - 0x20u)); // original 005f8530 add eax, dword ptr [ebp - 0x20]
    store32(frame - 0x8u, eax);            // original 005f8533 mov dword ptr [ebp - 8], eax
    eax = load32(frame - 0x24u);           // original 005f8536 mov eax, dword ptr [ebp - 0x24]
    store32(args + 0u,
            (load32(args + 0u)) + (eax)); // original 005f8539 add dword ptr [ebp + 8], eax
    store32(args + 4u,
            (load32(args + 4u)) + (eax)); // original 005f853c add dword ptr [ebp + 0xc], eax
    edi = (edi) + (eax);                  // original 005f853f add edi, eax
    store32(frame - 0x4u, load32(frame - 0x4u) + 1u); // original 005f8541 inc dword ptr [ebp - 4]
    eax = load32(frame - 0x4u); // original 005f8544 mov eax, dword ptr [ebp - 4]
    left = eax;
    right = load32(esi + 0x68u); // original 005f8547 cmp eax, dword ptr [esi + 0x68]
    if (left < right)
        goto L_005f83dd; // original 005f854a jb 0x5f83dd
L_005f8550:;
    eax = load32(esi + 0x7cu); // original 005f8550 mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f8553 mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f8556 fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f8559 pop edi
    ;                                   // C++ ABI restore ownership. // original 005f855a pop esi
    ;                                   // C++ ABI restore ownership. // original 005f855b pop ebx
    ;                                   // C++ frame ownership. // original 005f855c leave
    return eax;                         // original 005f855d ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f82f0(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f82f0\n\taddl $8,%esp\n\tretl $12");
}
