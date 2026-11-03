#include "graphics/surface/surface_write_rgb332.h"
#include "graphics/surface/surface_write_transform.h"
#include "graphics/surface/surface_write_color.h"
#include "graphics/surface/surface_error_row.h"
extern "C" {
extern const uint32_t dat_006bc8c4;
extern const uint32_t dat_006bca1c;
extern const uint32_t dat_006be1d0;
extern const uint32_t dat_006be980;
extern const uint32_t dat_006c2bb4;
extern const uint32_t dat_006df410;
extern const uint32_t dat_006df418;
extern const uint32_t dat_006df41c;
extern const uint32_t dat_006df420;
}

extern "C" const uint32_t dat_006bc9dc = 0x40e00000u;
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
// Complete original 005f3d48..005f405d: R3G3B2; original access widths/order retained.
extern "C" u32 recovered_005f3d48(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x58];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x58u;
    ;          // C++ frame and ABI save ownership. // original 005f3d48 mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f3d4a push ebp
    ;          // C++ frame and ABI save ownership. // original 005f3d4b mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f3d4d sub esp, 0x54
    ;          // C++ frame and ABI save ownership. // original 005f3d50 push ebx
    ;          // C++ frame and ABI save ownership. // original 005f3d51 push esi
    esi = ecx; // original 005f3d52 mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f3d54 cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f3d58 push edi
    if (left == right)
        goto L_005f3d66;         // original 005f3d59 je 0x5f3d66
    pending = load32(args + 8u); // original 005f3d5b push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f3d5e call 0x5f0da1
    store32(args + 8u, eax); // original 005f3d63 mov dword ptr [ebp + 0x10], eax
L_005f3d66:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f3d66 cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f3d79;         // original 005f3d6a je 0x5f3d79
    pending = load32(args + 8u); // original 005f3d6c push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f3d6f mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f3d71 call 0x5f22d6
    store32(args + 8u, eax); // original 005f3d76 mov dword ptr [ebp + 0x10], eax
L_005f3d79:;
    eax = load32(args + 0u);                     // original 005f3d79 mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f3d7c fldz
    edx = load32(esi + 0x68u); // original 005f3d7e mov edx, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f3d81 fstp dword ptr [ebp - 0x54]
    ecx = load32(esi + 0x60u);          // original 005f3d84 mov ecx, dword ptr [esi + 0x60]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f3d87 fldz
    edi = load32(esi + 0x64u); // original 005f3d89 mov edi, dword ptr [esi + 0x64]
    ecx = (ecx) * (eax);       // original 005f3d8c imul ecx, eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory");          // original 005f3d8f fstp dword ptr [ebp - 0x50]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f3d92 fldz
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f3d94 fstp dword ptr [ebp - 0x4c]
    store32(args + 0u, eax);            // original 005f3d97 mov dword ptr [ebp + 8], eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f3d9a and dword ptr [ebp + 8], 1
    ebx = edx + 0xffffffffu;               // original 005f3d9e lea ebx, [edx - 1]
    ebx = (ebx) * (load32(args + 0u));     // original 005f3da1 imul ebx, dword ptr [ebp + 8]
    ebx = (ebx) + (ecx);                   // original 005f3da5 add ebx, ecx
    ecx = load32(args + 4u);               // original 005f3da7 mov ecx, dword ptr [ebp + 0xc]
    edi = (edi) * (ecx);                   // original 005f3daa imul edi, ecx
    eax = (eax) & (0x3u);                  // original 005f3dad and eax, 3
    ecx = (ecx) & (0x3u);                  // original 005f3db0 and ecx, 3
    ebx = (ebx) + (edi);                   // original 005f3db3 add ebx, edi
    ebx = (ebx) + (load32(esi + 0x20u));   // original 005f3db5 add ebx, dword ptr [esi + 0x20]
    eax = ecx + eax * 8u;                  // original 005f3db8 lea eax, [ecx + eax*8]
    ecx = load32(esi + 0x34u);             // original 005f3dbb mov ecx, dword ptr [esi + 0x34]
    edi = 0u;                              // original 005f3dbe xor edi, edi
    left = load32(args + 0u);
    right = edi;                 // original 005f3dc0 cmp dword ptr [ebp + 8], edi
    eax = ecx + eax * 4u;        // original 005f3dc3 lea eax, [ecx + eax*4]
    store32(frame - 0xcu, ebx);  // original 005f3dc6 mov dword ptr [ebp - 0xc], ebx
    store32(frame - 0x10u, eax); // original 005f3dc9 mov dword ptr [ebp - 0x10], eax
    if (left != right)
        goto L_005f3dda;        // original 005f3dcc jne 0x5f3dda
    store32(frame - 0x4u, edi); // original 005f3dce mov dword ptr [ebp - 4], edi
    store32(args + 0u, 0x1u);   // original 005f3dd1 mov dword ptr [ebp + 8], 1
    goto L_005f3de2;            // original 005f3dd8 jmp 0x5f3de2
L_005f3dda:;
    edx = edx - 1u; // original 005f3dda dec edx
    store32(args + 0u, (load32(args + 0u)) |
                           (0xffffffffu)); // original 005f3ddb or dword ptr [ebp + 8], 0xffffffff
    store32(frame - 0x4u, edx);            // original 005f3ddf mov dword ptr [ebp - 4], edx
L_005f3de2:;
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f3de2 fnstcw word ptr [ebp + 0xc]
    eax = load32(args + 4u);            // original 005f3de5 mov eax, dword ptr [ebp + 0xc]
    eax = (eax) | (0xc00u);             // original 005f3de8 or eax, 0xc00
    store32(frame - 0x8u, eax);         // original 005f3ded mov dword ptr [ebp - 8], eax
    __asm__ volatile("fldcw (%0)" ::"r"(frame - 0x8u)
                     : "st", "memory"); // original 005f3df0 fldcw word ptr [ebp - 8]
    eax = load32(args + 4u);            // original 005f3df3 mov eax, dword ptr [ebp + 0xc]
    store32(esi + 0x7cu, eax);          // original 005f3df6 mov dword ptr [esi + 0x7c], eax
    left = load32(esi + 0x5cu);
    right = edi; // original 005f3df9 cmp dword ptr [esi + 0x5c], edi
    if (left == right)
        goto L_005f3e08;         // original 005f3dfc je 0x5f3e08
    pending = load32(args + 8u); // original 005f3dfe push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f3e01 mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f3e03 call 0x5f25f2
L_005f3e08:;
    left = load32(esi + 0x68u);
    right = edi;             // original 005f3e08 cmp dword ptr [esi + 0x68], edi
    store32(args + 4u, edi); // original 005f3e0b mov dword ptr [ebp + 0xc], edi
    if (left <= right)
        goto L_005f404d;               // original 005f3e0e jbe 0x5f404d
    edi = load32(args + 0u);           // original 005f3e14 mov edi, dword ptr [ebp + 8]
    edx = load32(frame - 0x4u);        // original 005f3e17 mov edx, dword ptr [ebp - 4]
    ecx = edi;                         // original 005f3e1a mov ecx, edi
    ecx = (ecx) << (0x4u);             // original 005f3e1c shl ecx, 4
    store32(frame - 0x24u, ecx);       // original 005f3e1f mov dword ptr [ebp - 0x24], ecx
    ecx = edx;                         // original 005f3e22 mov ecx, edx
    ecx = (ecx) - (load32(args + 0u)); // original 005f3e24 sub ecx, dword ptr [ebp + 8]
    edi = (edi) + (edx);               // original 005f3e27 add edi, edx
    eax = edx;                         // original 005f3e29 mov eax, edx
    eax = (eax) << (0x4u);             // original 005f3e2b shl eax, 4
    edi = (edi) << (0x4u);             // original 005f3e2e shl edi, 4
    ecx = (ecx) << (0x4u);             // original 005f3e31 shl ecx, 4
    store32(frame - 0x4u, ecx);        // original 005f3e34 mov dword ptr [ebp - 4], ecx
    ecx = load32(args + 8u);           // original 005f3e37 mov ecx, dword ptr [ebp + 0x10]
    ecx = eax + ecx + 0x8u;            // original 005f3e3a lea ecx, [eax + ecx + 8]
    store32(args + 8u, ecx);           // original 005f3e3e mov dword ptr [ebp + 0x10], ecx
L_005f3e41:;
    ecx = load32(args + 4u);     // original 005f3e41 mov ecx, dword ptr [ebp + 0xc]
    edx = load32(frame - 0x10u); // original 005f3e44 mov edx, dword ptr [ebp - 0x10]
    ecx = (ecx) & (0x3u);        // original 005f3e47 and ecx, 3
    __asm__ volatile("flds (%0)" ::"r"(edx + ecx * 4u)
                     : "st", "memory"); // original 005f3e4a fld dword ptr [edx + ecx*4]
    ecx = load32(args + 8u);            // original 005f3e4d mov ecx, dword ptr [ebp + 0x10]
    __asm__ volatile("fsts (%0)" ::"r"(frame - 0x8u)
                     : "st", "memory"); // original 005f3e50 fst dword ptr [ebp - 8]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f3e53 fld dword ptr [ebp - 0x54]
    __asm__ volatile("fadds (%0)" ::"r"(ecx + 0xfffffff8u)
                     : "st", "memory"); // original 005f3e56 fadd dword ptr [ecx - 8]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bc9dc))
                     : "st", "memory"); // original 005f3e59 fmul dword ptr [0x6bc9dc]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f3e5f fstp dword ptr [ebp - 0x44]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f3e62 fld dword ptr [ebp - 0x50]
    __asm__ volatile("fadds (%0)" ::"r"(ecx + 0xfffffffcu)
                     : "st", "memory"); // original 005f3e65 fadd dword ptr [ecx - 4]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bc9dc))
                     : "st", "memory"); // original 005f3e68 fmul dword ptr [0x6bc9dc]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f3e6e fstp dword ptr [ebp - 0x40]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f3e71 fld dword ptr [ebp - 0x4c]
    __asm__ volatile("fadds (%0)" ::"r"(ecx)
                     : "st", "memory"); // original 005f3e74 fadd dword ptr [ecx]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bca1c))
                     : "st", "memory"); // original 005f3e76 fmul dword ptr [0x6bca1c]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f3e7c fstp dword ptr [ebp - 0x3c]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f3e7f fld dword ptr [ebp - 0x44]
    __asm__ volatile("fadd %%st(1)" ::: "st", "memory"); // original 005f3e82 fadd st(1)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f3e84 fstp dword ptr [ebp - 0x14]
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f3e87 fstp st(0)
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f3e89 fld dword ptr [ebp - 0x14]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f3e8c fistp dword ptr [ebp - 0x18]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f3e8f fld dword ptr [ebp - 0x40]
    ecx = load32(frame - 0x18u);        // original 005f3e92 mov ecx, dword ptr [ebp - 0x18]
    __asm__ volatile("fadds (%0)" ::"r"(frame - 0x8u)
                     : "st", "memory"); // original 005f3e95 fadd dword ptr [ebp - 8]
    store32(frame - 0x34u, ecx);        // original 005f3e98 mov dword ptr [ebp - 0x34], ecx
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f3e9b fstp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f3e9e fld dword ptr [ebp - 0x14]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x1cu)
                     : "st", "memory"); // original 005f3ea1 fistp dword ptr [ebp - 0x1c]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f3ea4 fld dword ptr [ebp - 0x3c]
    edx = load32(frame - 0x1cu);        // original 005f3ea7 mov edx, dword ptr [ebp - 0x1c]
    __asm__ volatile("fadds (%0)" ::"r"(frame - 0x8u)
                     : "st", "memory"); // original 005f3eaa fadd dword ptr [ebp - 8]
    store32(frame - 0x30u, edx);        // original 005f3ead mov dword ptr [ebp - 0x30], edx
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f3eb0 fstp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f3eb3 fld dword ptr [ebp - 0x14]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x20u)
                     : "st", "memory"); // original 005f3eb6 fistp dword ptr [ebp - 0x20]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f3eb9 cmp dword ptr [esi + 0x5c], 0
    edx = load32(frame - 0x20u); // original 005f3ebd mov edx, dword ptr [ebp - 0x20]
    store32(frame - 0x2cu, edx); // original 005f3ec0 mov dword ptr [ebp - 0x2c], edx
    if (left == right)
        goto L_005f3fb7; // original 005f3ec3 je 0x5f3fb7
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df420))
                     : "st", "memory"); // original 005f3ec9 fld dword ptr [0x6df420]
    ebx = load32(esi + 0x5cu);          // original 005f3ecf mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f3ed2 fild dword ptr [ebp - 0x34]
    edx = load32(frame - 0x4u);         // original 005f3ed5 mov edx, dword ptr [ebp - 4]
    ebx = ebx + edx + 0x10u;            // original 005f3ed8 lea ebx, [ebx + edx + 0x10]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f3edc fsubr dword ptr [ebp - 0x44]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f3edf fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f3ee1 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f3ee7 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f3ee9 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f3eeb fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f3eed mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f3ef0 fld dword ptr [0x6df418]
    ebx = ebx + eax + 0x10u;            // original 005f3ef6 lea ebx, [ebx + eax + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f3efa fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f3efc fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f3efe fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f3f00 mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f3f03 fld dword ptr [0x6be980]
    ebx = ebx + edi + 0x10u;            // original 005f3f09 lea ebx, [ebx + edi + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f3f0d fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f3f0f fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f3f11 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f3f13 mov ebx, dword ptr [esi + 0x5c]
    ebx = ebx + edx + 0x14u;            // original 005f3f16 lea ebx, [ebx + edx + 0x14]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f3f1a fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f3f20 fstp dword ptr [ebp - 0x54]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f3f23 fild dword ptr [ebp - 0x30]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f3f26 fsubr dword ptr [ebp - 0x40]
    __asm__ volatile("fmulp %%st(1)" ::: "st", "memory"); // original 005f3f29 fmulp st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f3f2b fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f3f31 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f3f33 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f3f35 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f3f37 mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f3f3a fld dword ptr [0x6df418]
    ebx = ebx + eax + 0x14u;            // original 005f3f40 lea ebx, [ebx + eax + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f3f44 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f3f46 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f3f48 fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f3f4a mov ebx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f3f4d fld dword ptr [0x6be980]
    ebx = ebx + edi + 0x14u;            // original 005f3f53 lea ebx, [ebx + edi + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f3f57 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f3f59 fadd dword ptr [ebx]
    __asm__ volatile("fstps (%0)" ::"r"(ebx)
                     : "st", "memory"); // original 005f3f5b fstp dword ptr [ebx]
    ebx = load32(esi + 0x5cu);          // original 005f3f5d mov ebx, dword ptr [esi + 0x5c]
    edx = ebx + edx + 0x18u;            // original 005f3f60 lea edx, [ebx + edx + 0x18]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f3f64 fmul qword ptr [0x6df410]
    ebx = load32(frame - 0xcu);         // original 005f3f6a mov ebx, dword ptr [ebp - 0xc]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f3f6d fstp dword ptr [ebp - 0x50]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x2cu)
                     : "st", "memory"); // original 005f3f70 fild dword ptr [ebp - 0x2c]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f3f73 fsubr dword ptr [ebp - 0x3c]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006c2bb4))
                     : "st", "memory"); // original 005f3f76 fmul dword ptr [0x6c2bb4]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f3f7c fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f3f82 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f3f84 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f3f86 fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f3f88 mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f3f8b fld dword ptr [0x6df418]
    edx = edx + eax + 0x18u;            // original 005f3f91 lea edx, [edx + eax + 0x18]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f3f95 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f3f97 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f3f99 fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f3f9b mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f3f9e fld dword ptr [0x6be980]
    edx = edx + edi + 0x18u;            // original 005f3fa4 lea edx, [edx + edi + 0x18]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f3fa8 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f3faa fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f3fac fstp dword ptr [edx]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f3fae fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f3fb4 fstp dword ptr [ebp - 0x4c]
L_005f3fb7:;
    left = ecx;
    right = 0x7u; // original 005f3fb7 cmp ecx, 7
    if (static_cast<int32_t>(left) >= static_cast<int32_t>(right))
        goto L_005f3fc0; // original 005f3fba jge 0x5f3fc0
    edx = ecx;           // original 005f3fbc mov edx, ecx
    goto L_005f3fc3;     // original 005f3fbe jmp 0x5f3fc3
L_005f3fc0:;
    pending = 0x7u; // original 005f3fc0 push 7
    edx = pending;  // original 005f3fc2 pop edx
L_005f3fc3:;
    left = edx;
    right = edx;
    left &= right;
    right = 0; // original 005f3fc3 test edx, edx
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f3fd1; // original 005f3fc5 jle 0x5f3fd1
    left = ecx;
    right = 0x7u; // original 005f3fc7 cmp ecx, 7
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f3fd3; // original 005f3fca jl 0x5f3fd3
    pending = 0x7u;      // original 005f3fcc push 7
    ecx = pending;       // original 005f3fce pop ecx
    goto L_005f3fd3;     // original 005f3fcf jmp 0x5f3fd3
L_005f3fd1:;
    ecx = 0u; // original 005f3fd1 xor ecx, ecx
L_005f3fd3:;
    left = load32(frame - 0x30u);
    right = 0x7u; // original 005f3fd3 cmp dword ptr [ebp - 0x30], 7
    if (static_cast<int32_t>(left) >= static_cast<int32_t>(right))
        goto L_005f3fde;         // original 005f3fd7 jge 0x5f3fde
    edx = load32(frame - 0x30u); // original 005f3fd9 mov edx, dword ptr [ebp - 0x30]
    goto L_005f3fe1;             // original 005f3fdc jmp 0x5f3fe1
L_005f3fde:;
    pending = 0x7u; // original 005f3fde push 7
    edx = pending;  // original 005f3fe0 pop edx
L_005f3fe1:;
    left = edx;
    right = edx;
    left &= right;
    right = 0; // original 005f3fe1 test edx, edx
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f3ff4; // original 005f3fe3 jle 0x5f3ff4
    left = load32(frame - 0x30u);
    right = 0x7u; // original 005f3fe5 cmp dword ptr [ebp - 0x30], 7
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f3ff8;          // original 005f3fe9 jl 0x5f3ff8
    store32(frame - 0x30u, 0x7u); // original 005f3feb mov dword ptr [ebp - 0x30], 7
    goto L_005f3ff8;              // original 005f3ff2 jmp 0x5f3ff8
L_005f3ff4:;
    store32(frame - 0x30u,
            (load32(frame - 0x30u)) & (0x0u)); // original 005f3ff4 and dword ptr [ebp - 0x30], 0
L_005f3ff8:;
    left = load32(frame - 0x2cu);
    right = 0x3u; // original 005f3ff8 cmp dword ptr [ebp - 0x2c], 3
    if (static_cast<int32_t>(left) >= static_cast<int32_t>(right))
        goto L_005f4003;         // original 005f3ffc jge 0x5f4003
    edx = load32(frame - 0x2cu); // original 005f3ffe mov edx, dword ptr [ebp - 0x2c]
    goto L_005f4006;             // original 005f4001 jmp 0x5f4006
L_005f4003:;
    pending = 0x3u; // original 005f4003 push 3
    edx = pending;  // original 005f4005 pop edx
L_005f4006:;
    left = edx;
    right = edx;
    left &= right;
    right = 0; // original 005f4006 test edx, edx
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f4019; // original 005f4008 jle 0x5f4019
    left = load32(frame - 0x2cu);
    right = 0x3u; // original 005f400a cmp dword ptr [ebp - 0x2c], 3
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f401d;          // original 005f400e jl 0x5f401d
    store32(frame - 0x2cu, 0x3u); // original 005f4010 mov dword ptr [ebp - 0x2c], 3
    goto L_005f401d;              // original 005f4017 jmp 0x5f401d
L_005f4019:;
    store32(frame - 0x2cu,
            (load32(frame - 0x2cu)) & (0x0u)); // original 005f4019 and dword ptr [ebp - 0x2c], 0
L_005f401d:;
    ecx =
        (ecx & 0xffffff00u) | ((((ecx & 0xffu)) << (0x3u)) & 0xffu); // original 005f401d shl cl, 3
    ecx = (ecx & 0xffffff00u) | ((((ecx & 0xffu)) | (load8(frame - 0x30u))) &
                                 0xffu); // original 005f4020 or cl, byte ptr [ebp - 0x30]
    ecx =
        (ecx & 0xffffff00u) | ((((ecx & 0xffu)) << (0x2u)) & 0xffu); // original 005f4023 shl cl, 2
    ecx = (ecx & 0xffffff00u) | ((((ecx & 0xffu)) | (load8(frame - 0x2cu))) &
                                 0xffu); // original 005f4026 or cl, byte ptr [ebp - 0x2c]
    store8(ebx, (ecx & 0xffu));          // original 005f4029 mov byte ptr [ebx], cl
    ecx = load32(frame - 0x24u);         // original 005f402b mov ecx, dword ptr [ebp - 0x24]
    ebx = (ebx) + (load32(args + 0u));   // original 005f402e add ebx, dword ptr [ebp + 8]
    store32(args + 8u,
            (load32(args + 8u)) + (ecx)); // original 005f4031 add dword ptr [ebp + 0x10], ecx
    store32(frame - 0x4u,
            (load32(frame - 0x4u)) + (ecx));    // original 005f4034 add dword ptr [ebp - 4], ecx
    eax = (eax) + (ecx);                        // original 005f4037 add eax, ecx
    edi = (edi) + (ecx);                        // original 005f4039 add edi, ecx
    store32(args + 4u, load32(args + 4u) + 1u); // original 005f403b inc dword ptr [ebp + 0xc]
    ecx = load32(args + 4u);                    // original 005f403e mov ecx, dword ptr [ebp + 0xc]
    left = ecx;
    right = load32(esi + 0x68u); // original 005f4041 cmp ecx, dword ptr [esi + 0x68]
    store32(frame - 0xcu, ebx);  // original 005f4044 mov dword ptr [ebp - 0xc], ebx
    if (left < right)
        goto L_005f3e41; // original 005f4047 jb 0x5f3e41
L_005f404d:;
    eax = load32(esi + 0x7cu); // original 005f404d mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f4050 mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f4053 fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f4056 pop edi
    ;                                   // C++ ABI restore ownership. // original 005f4057 pop esi
    ;                                   // C++ ABI restore ownership. // original 005f4058 pop ebx
    ;                                   // C++ frame ownership. // original 005f4059 leave
    return eax;                         // original 005f405a ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f3d48(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f3d48\n\taddl $8,%esp\n\tretl $12");
}

// Complete original 005f405d..005f421e: A8; original access widths/order retained.
extern "C" u32 recovered_005f405d(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x58];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x58u;
    ;          // C++ frame and ABI save ownership. // original 005f405d mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f405f push ebp
    ;          // C++ frame and ABI save ownership. // original 005f4060 mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f4062 sub esp, 0x44
    ;          // C++ frame and ABI save ownership. // original 005f4065 push ebx
    ;          // C++ frame and ABI save ownership. // original 005f4066 push esi
    esi = ecx; // original 005f4067 mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f4069 cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f406d push edi
    if (left == right)
        goto L_005f407b;         // original 005f406e je 0x5f407b
    pending = load32(args + 8u); // original 005f4070 push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f4073 call 0x5f0da1
    store32(args + 8u, eax); // original 005f4078 mov dword ptr [ebp + 0x10], eax
L_005f407b:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f407b cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f408e;         // original 005f407f je 0x5f408e
    pending = load32(args + 8u); // original 005f4081 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f4084 mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f4086 call 0x5f22d6
    store32(args + 8u, eax); // original 005f408b mov dword ptr [ebp + 0x10], eax
L_005f408e:;
    eax = load32(args + 0u);                     // original 005f408e mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f4091 fldz
    ebx = load32(esi + 0x68u); // original 005f4093 mov ebx, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x28u)
                     : "st", "memory"); // original 005f4096 fstp dword ptr [ebp - 0x28]
    ecx = load32(esi + 0x60u);          // original 005f4099 mov ecx, dword ptr [esi + 0x60]
    edx = load32(esi + 0x64u);          // original 005f409c mov edx, dword ptr [esi + 0x64]
    ecx = (ecx) * (eax);                // original 005f409f imul ecx, eax
    store32(args + 0u, eax);            // original 005f40a2 mov dword ptr [ebp + 8], eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f40a5 and dword ptr [ebp + 8], 1
    edi = ebx + 0xffffffffu;               // original 005f40a9 lea edi, [ebx - 1]
    edi = (edi) * (load32(args + 0u));     // original 005f40ac imul edi, dword ptr [ebp + 8]
    edi = (edi) + (ecx);                   // original 005f40b0 add edi, ecx
    ecx = load32(args + 4u);               // original 005f40b2 mov ecx, dword ptr [ebp + 0xc]
    edx = (edx) * (ecx);                   // original 005f40b5 imul edx, ecx
    eax = (eax) & (0x3u);                  // original 005f40b8 and eax, 3
    ecx = (ecx) & (0x3u);                  // original 005f40bb and ecx, 3
    eax = ecx + eax * 8u;                  // original 005f40be lea eax, [ecx + eax*8]
    ecx = load32(esi + 0x34u);             // original 005f40c1 mov ecx, dword ptr [esi + 0x34]
    edi = (edi) + (edx);                   // original 005f40c4 add edi, edx
    edi = (edi) + (load32(esi + 0x20u));   // original 005f40c6 add edi, dword ptr [esi + 0x20]
    left = load32(args + 0u);
    right = 0x0u;               // original 005f40c9 cmp dword ptr [ebp + 8], 0
    eax = ecx + eax * 4u;       // original 005f40cd lea eax, [ecx + eax*4]
    store32(frame - 0x8u, eax); // original 005f40d0 mov dword ptr [ebp - 8], eax
    if (left != right)
        goto L_005f40e0;      // original 005f40d3 jne 0x5f40e0
    ebx = 0u;                 // original 005f40d5 xor ebx, ebx
    store32(args + 0u, 0x1u); // original 005f40d7 mov dword ptr [ebp + 8], 1
    goto L_005f40e5;          // original 005f40de jmp 0x5f40e5
L_005f40e0:;
    ebx = ebx - 1u; // original 005f40e0 dec ebx
    store32(args + 0u, (load32(args + 0u)) |
                           (0xffffffffu)); // original 005f40e1 or dword ptr [ebp + 8], 0xffffffff
L_005f40e5:;
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f40e5 fnstcw word ptr [ebp + 0xc]
    eax = load32(args + 4u);            // original 005f40e8 mov eax, dword ptr [ebp + 0xc]
    eax = (eax) | (0xc00u);             // original 005f40eb or eax, 0xc00
    store32(frame - 0x4u, eax);         // original 005f40f0 mov dword ptr [ebp - 4], eax
    __asm__ volatile("fldcw (%0)" ::"r"(frame - 0x4u)
                     : "st", "memory"); // original 005f40f3 fldcw word ptr [ebp - 4]
    eax = load32(args + 4u);            // original 005f40f6 mov eax, dword ptr [ebp + 0xc]
    store32(esi + 0x7cu, eax);          // original 005f40f9 mov dword ptr [esi + 0x7c], eax
    left = load32(esi + 0x5cu);
    right = 0x0u; // original 005f40fc cmp dword ptr [esi + 0x5c], 0
    if (left == right)
        goto L_005f410c;         // original 005f4100 je 0x5f410c
    pending = load32(args + 8u); // original 005f4102 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f4105 mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f4107 call 0x5f25f2
L_005f410c:;
    store32(args + 4u,
            (load32(args + 4u)) & (0x0u)); // original 005f410c and dword ptr [ebp + 0xc], 0
    left = load32(esi + 0x68u);
    right = 0x0u; // original 005f4110 cmp dword ptr [esi + 0x68], 0
    if (left <= right)
        goto L_005f420e;         // original 005f4114 jbe 0x5f420e
    edx = load32(args + 0u);     // original 005f411a mov edx, dword ptr [ebp + 8]
    ecx = edx;                   // original 005f411d mov ecx, edx
    ecx = (ecx) << (0x4u);       // original 005f411f shl ecx, 4
    eax = ebx;                   // original 005f4122 mov eax, ebx
    store32(frame - 0x14u, ecx); // original 005f4124 mov dword ptr [ebp - 0x14], ecx
    ecx = edx + ebx;             // original 005f4127 lea ecx, [edx + ebx]
    ebx = (ebx) - (edx);         // original 005f412a sub ebx, edx
    edx = load32(args + 8u);     // original 005f412c mov edx, dword ptr [ebp + 0x10]
    eax = (eax) << (0x4u);       // original 005f412f shl eax, 4
    ecx = (ecx) << (0x4u);       // original 005f4132 shl ecx, 4
    ebx = (ebx) << (0x4u);       // original 005f4135 shl ebx, 4
    edx = eax + edx + 0xcu;      // original 005f4138 lea edx, [eax + edx + 0xc]
    store32(frame - 0x4u, ebx);  // original 005f413c mov dword ptr [ebp - 4], ebx
    store32(args + 8u, edx);     // original 005f413f mov dword ptr [ebp + 0x10], edx
L_005f4142:;
    edx = load32(args + 8u); // original 005f4142 mov edx, dword ptr [ebp + 0x10]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x28u)
                     : "st", "memory"); // original 005f4145 fld dword ptr [ebp - 0x28]
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f4148 fadd dword ptr [edx]
    edx = load32(args + 4u);            // original 005f414a mov edx, dword ptr [ebp + 0xc]
    ebx = load32(frame - 0x8u);         // original 005f414d mov ebx, dword ptr [ebp - 8]
    edx = (edx) & (0x3u);               // original 005f4150 and edx, 3
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bc8c4))
                     : "st", "memory"); // original 005f4153 fmul dword ptr [0x6bc8c4]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f4159 fstp dword ptr [ebp - 0x18]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f415c fld dword ptr [ebp - 0x18]
    __asm__ volatile("fadds (%0)" ::"r"(ebx + edx * 4u)
                     : "st", "memory"); // original 005f415f fadd dword ptr [ebx + edx*4]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f4162 fstp dword ptr [ebp - 0xc]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f4165 fld dword ptr [ebp - 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f4168 fistp dword ptr [ebp - 0x10]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f416b cmp dword ptr [esi + 0x5c], 0
    edx = load32(frame - 0x10u); // original 005f416f mov edx, dword ptr [ebp - 0x10]
    store32(frame - 0x38u, edx); // original 005f4172 mov dword ptr [ebp - 0x38], edx
    if (left == right)
        goto L_005f41cb; // original 005f4175 je 0x5f41cb
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f4177 fild dword ptr [ebp - 0x38]
    edx = load32(esi + 0x5cu);          // original 005f417a mov edx, dword ptr [esi + 0x5c]
    ebx = load32(frame - 0x4u);         // original 005f417d mov ebx, dword ptr [ebp - 4]
    edx = ebx + edx + 0x1cu;            // original 005f4180 lea edx, [ebx + edx + 0x1c]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f4184 fsubr dword ptr [ebp - 0x18]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be1d0))
                     : "st", "memory"); // original 005f4187 fmul dword ptr [0x6be1d0]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f418d fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f4193 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f4195 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f4197 fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f4199 mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f419c fld dword ptr [0x6df418]
    edx = eax + edx + 0x1cu;            // original 005f41a2 lea edx, [eax + edx + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f41a6 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f41a8 fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f41aa fstp dword ptr [edx]
    edx = load32(esi + 0x5cu);          // original 005f41ac mov edx, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f41af fld dword ptr [0x6be980]
    edx = ecx + edx + 0x1cu;            // original 005f41b5 lea edx, [ecx + edx + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f41b9 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f41bb fadd dword ptr [edx]
    __asm__ volatile("fstps (%0)" ::"r"(edx)
                     : "st", "memory"); // original 005f41bd fstp dword ptr [edx]
    edx = load32(frame - 0x38u);        // original 005f41bf mov edx, dword ptr [ebp - 0x38]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f41c2 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x28u)
                     : "st", "memory"); // original 005f41c8 fstp dword ptr [ebp - 0x28]
L_005f41cb:;
    left = edx;
    right = 0xffu; // original 005f41cb cmp edx, 0xff
    ebx = edx;     // original 005f41d1 mov ebx, edx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f41da; // original 005f41d3 jl 0x5f41da
    ebx = 0xffu;         // original 005f41d5 mov ebx, 0xff
L_005f41da:;
    left = ebx;
    right = ebx;
    left &= right;
    right = 0; // original 005f41da test ebx, ebx
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f41eb; // original 005f41dc jle 0x5f41eb
    ebx = 0xffu;         // original 005f41de mov ebx, 0xff
    left = edx;
    right = ebx; // original 005f41e3 cmp edx, ebx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f41ed; // original 005f41e5 jl 0x5f41ed
    edx = ebx;           // original 005f41e7 mov edx, ebx
    goto L_005f41ed;     // original 005f41e9 jmp 0x5f41ed
L_005f41eb:;
    edx = 0u; // original 005f41eb xor edx, edx
L_005f41ed:;
    store8(edi, (edx & 0xffu));  // original 005f41ed mov byte ptr [edi], dl
    edx = load32(frame - 0x14u); // original 005f41ef mov edx, dword ptr [ebp - 0x14]
    store32(args + 8u,
            (load32(args + 8u)) + (edx)); // original 005f41f2 add dword ptr [ebp + 0x10], edx
    store32(frame - 0x4u,
            (load32(frame - 0x4u)) + (edx));    // original 005f41f5 add dword ptr [ebp - 4], edx
    edi = (edi) + (load32(args + 0u));          // original 005f41f8 add edi, dword ptr [ebp + 8]
    eax = (eax) + (edx);                        // original 005f41fb add eax, edx
    ecx = (ecx) + (edx);                        // original 005f41fd add ecx, edx
    store32(args + 4u, load32(args + 4u) + 1u); // original 005f41ff inc dword ptr [ebp + 0xc]
    edx = load32(args + 4u);                    // original 005f4202 mov edx, dword ptr [ebp + 0xc]
    left = edx;
    right = load32(esi + 0x68u); // original 005f4205 cmp edx, dword ptr [esi + 0x68]
    if (left < right)
        goto L_005f4142; // original 005f4208 jb 0x5f4142
L_005f420e:;
    eax = load32(esi + 0x7cu); // original 005f420e mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f4211 mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f4214 fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f4217 pop edi
    ;                                   // C++ ABI restore ownership. // original 005f4218 pop esi
    ;                                   // C++ ABI restore ownership. // original 005f4219 pop ebx
    ;                                   // C++ frame ownership. // original 005f421a leave
    return eax;                         // original 005f421b ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f405d(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f405d\n\taddl $8,%esp\n\tretl $12");
}

// Complete original 005f421e..005f45b6: A8R3G3B2; original access widths/order retained.
extern "C" u32 recovered_005f421e(u32 self, u32 args) {
    u32 eax = 0, ebx = 0, ecx = self, edx = 0, esi = 0, edi = 0, pending = 0, left = 0, right = 0;
    alignas(4) unsigned char private_frame[0x58];
    const u32 frame = reinterpret_cast<u32>(private_frame) + 0x58u;
    ;          // C++ frame and ABI save ownership. // original 005f421e mov edi, edi
    ;          // C++ frame and ABI save ownership. // original 005f4220 push ebp
    ;          // C++ frame and ABI save ownership. // original 005f4221 mov ebp, esp
    ;          // C++ frame and ABI save ownership. // original 005f4223 sub esp, 0x54
    ;          // C++ frame and ABI save ownership. // original 005f4226 push ebx
    ;          // C++ frame and ABI save ownership. // original 005f4227 push esi
    esi = ecx; // original 005f4228 mov esi, ecx
    left = load32(esi + 0x54u);
    right = 0x0u; // original 005f422a cmp dword ptr [esi + 0x54], 0
    ;             // C++ ABI save ownership. // original 005f422e push edi
    if (left == right)
        goto L_005f423c;         // original 005f422f je 0x5f423c
    pending = load32(args + 8u); // original 005f4231 push dword ptr [ebp + 0x10]
    eax = FUN_005f0da1(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f4234 call 0x5f0da1
    store32(args + 8u, eax); // original 005f4239 mov dword ptr [ebp + 0x10], eax
L_005f423c:;
    left = load32(esi + 0x10u);
    right = 0x0u; // original 005f423c cmp dword ptr [esi + 0x10], 0
    if (left == right)
        goto L_005f424f;         // original 005f4240 je 0x5f424f
    pending = load32(args + 8u); // original 005f4242 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f4245 mov ecx, esi
    eax = FUN_005f22d6(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<const void*>(pending)); // original 005f4247 call 0x5f22d6
    store32(args + 8u, eax); // original 005f424c mov dword ptr [ebp + 0x10], eax
L_005f424f:;
    eax = load32(args + 0u);                     // original 005f424f mov eax, dword ptr [ebp + 8]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f4252 fldz
    edi = load32(esi + 0x68u); // original 005f4254 mov edi, dword ptr [esi + 0x68]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f4257 fstp dword ptr [ebp - 0x54]
    edx = load32(esi + 0x60u);          // original 005f425a mov edx, dword ptr [esi + 0x60]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f425d fldz
    ebx = load32(esi + 0x64u); // original 005f425f mov ebx, dword ptr [esi + 0x64]
    edx = (edx) * (eax);       // original 005f4262 imul edx, eax
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory");          // original 005f4265 fstp dword ptr [ebp - 0x50]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f4268 fldz
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory");          // original 005f426a fstp dword ptr [ebp - 0x4c]
    __asm__ volatile("fldz" ::: "st", "memory"); // original 005f426d fldz
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f426f fstp dword ptr [ebp - 0x48]
    store32(args + 0u, eax);            // original 005f4272 mov dword ptr [ebp + 8], eax
    store32(args + 0u,
            (load32(args + 0u)) & (0x1u)); // original 005f4275 and dword ptr [ebp + 8], 1
    ecx = edi + 0xffffffffu;               // original 005f4279 lea ecx, [edi - 1]
    ecx = (ecx) * (load32(args + 0u));     // original 005f427c imul ecx, dword ptr [ebp + 8]
    ecx = edx + ecx * 2u;                  // original 005f4280 lea ecx, [edx + ecx*2]
    edx = load32(args + 4u);               // original 005f4283 mov edx, dword ptr [ebp + 0xc]
    ebx = (ebx) * (edx);                   // original 005f4286 imul ebx, edx
    ecx = (ecx) + (ebx);                   // original 005f4289 add ecx, ebx
    ecx = (ecx) + (load32(esi + 0x20u));   // original 005f428b add ecx, dword ptr [esi + 0x20]
    eax = (eax) & (0x3u);                  // original 005f428e and eax, 3
    edx = (edx) & (0x3u);                  // original 005f4291 and edx, 3
    left = load32(args + 0u);
    right = 0x0u;               // original 005f4294 cmp dword ptr [ebp + 8], 0
    store32(frame - 0x4u, ecx); // original 005f4298 mov dword ptr [ebp - 4], ecx
    ecx = load32(esi + 0x34u);  // original 005f429b mov ecx, dword ptr [esi + 0x34]
    eax = edx + eax * 8u;       // original 005f429e lea eax, [edx + eax*8]
    eax = ecx + eax * 4u;       // original 005f42a1 lea eax, [ecx + eax*4]
    store32(frame - 0x8u, eax); // original 005f42a4 mov dword ptr [ebp - 8], eax
    if (left != right)
        goto L_005f42b0; // original 005f42a7 jne 0x5f42b0
    ebx = 0u;            // original 005f42a9 xor ebx, ebx
    edi = 0u;            // original 005f42ab xor edi, edi
    ebx = ebx + 1u;      // original 005f42ad inc ebx
    goto L_005f42b4;     // original 005f42ae jmp 0x5f42b4
L_005f42b0:;
    edi = edi - 1u;              // original 005f42b0 dec edi
    ebx = (ebx) | (0xffffffffu); // original 005f42b1 or ebx, 0xffffffff
L_005f42b4:;
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 0u)
                     : "st", "memory"); // original 005f42b4 fnstcw word ptr [ebp + 8]
    eax = load32(args + 0u);            // original 005f42b7 mov eax, dword ptr [ebp + 8]
    eax = (eax) | (0xc00u);             // original 005f42ba or eax, 0xc00
    store32(args + 4u, eax);            // original 005f42bf mov dword ptr [ebp + 0xc], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 4u)
                     : "st", "memory"); // original 005f42c2 fldcw word ptr [ebp + 0xc]
    eax = load32(args + 0u);            // original 005f42c5 mov eax, dword ptr [ebp + 8]
    store32(esi + 0x7cu, eax);          // original 005f42c8 mov dword ptr [esi + 0x7c], eax
    left = load32(esi + 0x5cu);
    right = 0x0u; // original 005f42cb cmp dword ptr [esi + 0x5c], 0
    if (left == right)
        goto L_005f42db;         // original 005f42cf je 0x5f42db
    pending = load32(args + 8u); // original 005f42d1 push dword ptr [ebp + 0x10]
    ecx = esi;                   // original 005f42d4 mov ecx, esi
    eax = FUN_005f25f2(reinterpret_cast<void*>(ecx),
                       reinterpret_cast<void*>(pending)); // original 005f42d6 call 0x5f25f2
L_005f42db:;
    store32(args + 0u,
            (load32(args + 0u)) & (0x0u)); // original 005f42db and dword ptr [ebp + 8], 0
    left = load32(esi + 0x68u);
    right = 0x0u; // original 005f42df cmp dword ptr [esi + 0x68], 0
    if (left <= right)
        goto L_005f45a6;         // original 005f42e3 jbe 0x5f45a6
    ecx = ebx;                   // original 005f42e9 mov ecx, ebx
    ecx = (ecx) << (0x4u);       // original 005f42eb shl ecx, 4
    eax = ebx + ebx;             // original 005f42ee lea eax, [ebx + ebx]
    store32(frame - 0x20u, eax); // original 005f42f1 mov dword ptr [ebp - 0x20], eax
    eax = edi;                   // original 005f42f4 mov eax, edi
    store32(frame - 0x24u, ecx); // original 005f42f6 mov dword ptr [ebp - 0x24], ecx
    ecx = ebx + edi;             // original 005f42f9 lea ecx, [ebx + edi]
    edi = (edi) - (ebx);         // original 005f42fc sub edi, ebx
    eax = (eax) << (0x4u);       // original 005f42fe shl eax, 4
    ecx = (ecx) << (0x4u);       // original 005f4301 shl ecx, 4
    edi = (edi) << (0x4u);       // original 005f4304 shl edi, 4
    edx = edi;                   // original 005f4307 mov edx, edi
    edi = load32(args + 8u);     // original 005f4309 mov edi, dword ptr [ebp + 0x10]
    edi = eax + edi + 0x8u;      // original 005f430c lea edi, [eax + edi + 8]
    store32(args + 4u, edi);     // original 005f4310 mov dword ptr [ebp + 0xc], edi
L_005f4313:;
    edi = load32(args + 0u);    // original 005f4313 mov edi, dword ptr [ebp + 8]
    ebx = load32(frame - 0x8u); // original 005f4316 mov ebx, dword ptr [ebp - 8]
    edi = (edi) & (0x3u);       // original 005f4319 and edi, 3
    __asm__ volatile("flds (%0)" ::"r"(ebx + edi * 4u)
                     : "st", "memory"); // original 005f431c fld dword ptr [ebx + edi*4]
    edi = load32(args + 4u);            // original 005f431f mov edi, dword ptr [ebp + 0xc]
    __asm__ volatile("fsts (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f4322 fst dword ptr [ebp + 0x10]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f4325 fld dword ptr [ebp - 0x54]
    __asm__ volatile("fadds (%0)" ::"r"(edi + 0xfffffff8u)
                     : "st", "memory"); // original 005f4328 fadd dword ptr [edi - 8]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bc9dc))
                     : "st", "memory"); // original 005f432b fmul dword ptr [0x6bc9dc]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f4331 fstp dword ptr [ebp - 0x44]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f4334 fld dword ptr [ebp - 0x50]
    __asm__ volatile("fadds (%0)" ::"r"(edi + 0xfffffffcu)
                     : "st", "memory"); // original 005f4337 fadd dword ptr [edi - 4]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bc9dc))
                     : "st", "memory"); // original 005f433a fmul dword ptr [0x6bc9dc]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f4340 fstp dword ptr [ebp - 0x40]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f4343 fld dword ptr [ebp - 0x4c]
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f4346 fadd dword ptr [edi]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bca1c))
                     : "st", "memory"); // original 005f4348 fmul dword ptr [0x6bca1c]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f434e fstp dword ptr [ebp - 0x3c]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f4351 fld dword ptr [ebp - 0x48]
    __asm__ volatile("fadds (%0)" ::"r"(edi + 0x4u)
                     : "st", "memory"); // original 005f4354 fadd dword ptr [edi + 4]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006bc8c4))
                     : "st", "memory"); // original 005f4357 fmul dword ptr [0x6bc8c4]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f435d fstp dword ptr [ebp - 0x38]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f4360 fld dword ptr [ebp - 0x44]
    __asm__ volatile("fadd %%st(1)" ::: "st", "memory"); // original 005f4363 fadd st(1)
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f4365 fstp dword ptr [ebp - 0xc]
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory"); // original 005f4368 fstp st(0)
    __asm__ volatile("flds (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f436a fld dword ptr [ebp - 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x10u)
                     : "st", "memory"); // original 005f436d fistp dword ptr [ebp - 0x10]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f4370 fld dword ptr [ebp - 0x40]
    ebx = load32(frame - 0x10u);        // original 005f4373 mov ebx, dword ptr [ebp - 0x10]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f4376 fadd dword ptr [ebp + 0x10]
    store32(frame - 0x34u, ebx);        // original 005f4379 mov dword ptr [ebp - 0x34], ebx
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f437c fstp dword ptr [ebp - 0xc]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f437f fld dword ptr [ebp - 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x14u)
                     : "st", "memory"); // original 005f4382 fistp dword ptr [ebp - 0x14]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f4385 fld dword ptr [ebp - 0x3c]
    edi = load32(frame - 0x14u);        // original 005f4388 mov edi, dword ptr [ebp - 0x14]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f438b fadd dword ptr [ebp + 0x10]
    store32(frame - 0x30u, edi);        // original 005f438e mov dword ptr [ebp - 0x30], edi
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f4391 fstp dword ptr [ebp - 0xc]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0xcu)
                     : "st", "memory"); // original 005f4394 fld dword ptr [ebp - 0xc]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x18u)
                     : "st", "memory"); // original 005f4397 fistp dword ptr [ebp - 0x18]
    __asm__ volatile("flds (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f439a fld dword ptr [ebp - 0x38]
    edi = load32(frame - 0x18u);        // original 005f439d mov edi, dword ptr [ebp - 0x18]
    __asm__ volatile("fadds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f43a0 fadd dword ptr [ebp + 0x10]
    store32(frame - 0x2cu, edi);        // original 005f43a3 mov dword ptr [ebp - 0x2c], edi
    __asm__ volatile("fstps (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f43a6 fstp dword ptr [ebp + 0x10]
    __asm__ volatile("flds (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f43a9 fld dword ptr [ebp + 0x10]
    __asm__ volatile("fistpl (%0)" ::"r"(frame - 0x1cu)
                     : "st", "memory"); // original 005f43ac fistp dword ptr [ebp - 0x1c]
    left = load32(esi + 0x5cu);
    right = 0x0u;                // original 005f43af cmp dword ptr [esi + 0x5c], 0
    edi = load32(frame - 0x1cu); // original 005f43b3 mov edi, dword ptr [ebp - 0x1c]
    store32(frame - 0x28u, edi); // original 005f43b6 mov dword ptr [ebp - 0x28], edi
    if (left == right)
        goto L_005f44f5; // original 005f43b9 je 0x5f44f5
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df420))
                     : "st", "memory"); // original 005f43bf fld dword ptr [0x6df420]
    edi = load32(esi + 0x5cu);          // original 005f43c5 mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x34u)
                     : "st", "memory"); // original 005f43c8 fild dword ptr [ebp - 0x34]
    edi = edi + edx + 0x10u;            // original 005f43cb lea edi, [edi + edx + 0x10]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x44u)
                     : "st", "memory"); // original 005f43cf fsubr dword ptr [ebp - 0x44]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f43d2 fmul st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f43d4 fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f43da fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f43dc fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f43de fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f43e0 mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f43e3 fld dword ptr [0x6df418]
    edi = edi + eax + 0x10u;            // original 005f43e9 lea edi, [edi + eax + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f43ed fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f43ef fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f43f1 fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f43f3 mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f43f6 fld dword ptr [0x6be980]
    edi = edi + ecx + 0x10u;            // original 005f43fc lea edi, [edi + ecx + 0x10]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f4400 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f4402 fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f4404 fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f4406 mov edi, dword ptr [esi + 0x5c]
    edi = edi + edx + 0x14u;            // original 005f4409 lea edi, [edi + edx + 0x14]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f440d fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x54u)
                     : "st", "memory"); // original 005f4413 fstp dword ptr [ebp - 0x54]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x30u)
                     : "st", "memory"); // original 005f4416 fild dword ptr [ebp - 0x30]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x40u)
                     : "st", "memory"); // original 005f4419 fsubr dword ptr [ebp - 0x40]
    __asm__ volatile("fmulp %%st(1)" ::: "st", "memory"); // original 005f441c fmulp st(1)
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f441e fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f4424 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f4426 fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f4428 fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f442a mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f442d fld dword ptr [0x6df418]
    edi = edi + eax + 0x14u;            // original 005f4433 lea edi, [edi + eax + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f4437 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f4439 fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f443b fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f443d mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f4440 fld dword ptr [0x6be980]
    edi = edi + ecx + 0x14u;            // original 005f4446 lea edi, [edi + ecx + 0x14]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f444a fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f444c fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f444e fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f4450 mov edi, dword ptr [esi + 0x5c]
    edi = edi + edx + 0x18u;            // original 005f4453 lea edi, [edi + edx + 0x18]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f4457 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x50u)
                     : "st", "memory"); // original 005f445d fstp dword ptr [ebp - 0x50]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x2cu)
                     : "st", "memory"); // original 005f4460 fild dword ptr [ebp - 0x2c]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x3cu)
                     : "st", "memory"); // original 005f4463 fsubr dword ptr [ebp - 0x3c]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006c2bb4))
                     : "st", "memory"); // original 005f4466 fmul dword ptr [0x6c2bb4]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f446c fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f4472 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f4474 fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f4476 fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f4478 mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f447b fld dword ptr [0x6df418]
    edi = edi + eax + 0x18u;            // original 005f4481 lea edi, [edi + eax + 0x18]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f4485 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f4487 fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f4489 fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f448b mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f448e fld dword ptr [0x6be980]
    edi = edi + ecx + 0x18u;            // original 005f4494 lea edi, [edi + ecx + 0x18]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f4498 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f449a fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f449c fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f449e mov edi, dword ptr [esi + 0x5c]
    edi = edi + edx + 0x1cu;            // original 005f44a1 lea edi, [edi + edx + 0x1c]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f44a5 fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x4cu)
                     : "st", "memory"); // original 005f44ab fstp dword ptr [ebp - 0x4c]
    __asm__ volatile("fildl (%0)" ::"r"(frame - 0x28u)
                     : "st", "memory"); // original 005f44ae fild dword ptr [ebp - 0x28]
    __asm__ volatile("fsubrs (%0)" ::"r"(frame - 0x38u)
                     : "st", "memory"); // original 005f44b1 fsubr dword ptr [ebp - 0x38]
    __asm__ volatile("fmuls (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be1d0))
                     : "st", "memory"); // original 005f44b4 fmul dword ptr [0x6be1d0]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df41c))
                     : "st", "memory"); // original 005f44ba fld dword ptr [0x6df41c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f44c0 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f44c2 fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f44c4 fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f44c6 mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df418))
                     : "st", "memory"); // original 005f44c9 fld dword ptr [0x6df418]
    edi = edi + eax + 0x1cu;            // original 005f44cf lea edi, [edi + eax + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f44d3 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f44d5 fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f44d7 fstp dword ptr [edi]
    edi = load32(esi + 0x5cu);          // original 005f44d9 mov edi, dword ptr [esi + 0x5c]
    __asm__ volatile("flds (%0)" ::"r"(reinterpret_cast<u32>(&dat_006be980))
                     : "st", "memory"); // original 005f44dc fld dword ptr [0x6be980]
    edi = edi + ecx + 0x1cu;            // original 005f44e2 lea edi, [edi + ecx + 0x1c]
    __asm__ volatile("fmul %%st(1)" ::: "st", "memory"); // original 005f44e6 fmul st(1)
    __asm__ volatile("fadds (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f44e8 fadd dword ptr [edi]
    __asm__ volatile("fstps (%0)" ::"r"(edi)
                     : "st", "memory"); // original 005f44ea fstp dword ptr [edi]
    __asm__ volatile("fmull (%0)" ::"r"(reinterpret_cast<u32>(&dat_006df410))
                     : "st", "memory"); // original 005f44ec fmul qword ptr [0x6df410]
    __asm__ volatile("fstps (%0)" ::"r"(frame - 0x48u)
                     : "st", "memory"); // original 005f44f2 fstp dword ptr [ebp - 0x48]
L_005f44f5:;
    left = ebx;
    right = 0x7u; // original 005f44f5 cmp ebx, 7
    if (static_cast<int32_t>(left) >= static_cast<int32_t>(right))
        goto L_005f44fe; // original 005f44f8 jge 0x5f44fe
    edi = ebx;           // original 005f44fa mov edi, ebx
    goto L_005f4501;     // original 005f44fc jmp 0x5f4501
L_005f44fe:;
    pending = 0x7u; // original 005f44fe push 7
    edi = pending;  // original 005f4500 pop edi
L_005f4501:;
    pending = 0x7u; // original 005f4501 push 7
    left = edi;
    right = edi;
    left &= right;
    right = 0;     // original 005f4503 test edi, edi
    edi = pending; // original 005f4505 pop edi
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f4511; // original 005f4506 jle 0x5f4511
    left = ebx;
    right = edi; // original 005f4508 cmp ebx, edi
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f4515;         // original 005f450a jl 0x5f4515
    store32(frame - 0x34u, edi); // original 005f450c mov dword ptr [ebp - 0x34], edi
    goto L_005f4515;             // original 005f450f jmp 0x5f4515
L_005f4511:;
    store32(frame - 0x34u,
            (load32(frame - 0x34u)) & (0x0u)); // original 005f4511 and dword ptr [ebp - 0x34], 0
L_005f4515:;
    ebx = load32(frame - 0x30u); // original 005f4515 mov ebx, dword ptr [ebp - 0x30]
    left = ebx;
    right = edi; // original 005f4518 cmp ebx, edi
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f451e; // original 005f451a jl 0x5f451e
    ebx = edi;           // original 005f451c mov ebx, edi
L_005f451e:;
    left = ebx;
    right = ebx;
    left &= right;
    right = 0; // original 005f451e test ebx, ebx
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f452c; // original 005f4520 jle 0x5f452c
    left = load32(frame - 0x30u);
    right = edi; // original 005f4522 cmp dword ptr [ebp - 0x30], edi
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f4530;         // original 005f4525 jl 0x5f4530
    store32(frame - 0x30u, edi); // original 005f4527 mov dword ptr [ebp - 0x30], edi
    goto L_005f4530;             // original 005f452a jmp 0x5f4530
L_005f452c:;
    store32(frame - 0x30u,
            (load32(frame - 0x30u)) & (0x0u)); // original 005f452c and dword ptr [ebp - 0x30], 0
L_005f4530:;
    edi = load32(frame - 0x2cu); // original 005f4530 mov edi, dword ptr [ebp - 0x2c]
    pending = 0x3u;              // original 005f4533 push 3
    ebx = pending;               // original 005f4535 pop ebx
    left = edi;
    right = ebx; // original 005f4536 cmp edi, ebx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f453c; // original 005f4538 jl 0x5f453c
    edi = ebx;           // original 005f453a mov edi, ebx
L_005f453c:;
    left = edi;
    right = edi;
    left &= right;
    right = 0; // original 005f453c test edi, edi
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f454a; // original 005f453e jle 0x5f454a
    left = load32(frame - 0x2cu);
    right = ebx; // original 005f4540 cmp dword ptr [ebp - 0x2c], ebx
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f454e;         // original 005f4543 jl 0x5f454e
    store32(frame - 0x2cu, ebx); // original 005f4545 mov dword ptr [ebp - 0x2c], ebx
    goto L_005f454e;             // original 005f4548 jmp 0x5f454e
L_005f454a:;
    store32(frame - 0x2cu,
            (load32(frame - 0x2cu)) & (0x0u)); // original 005f454a and dword ptr [ebp - 0x2c], 0
L_005f454e:;
    ebx = load32(frame - 0x28u); // original 005f454e mov ebx, dword ptr [ebp - 0x28]
    edi = 0xffu;                 // original 005f4551 mov edi, 0xff
    left = ebx;
    right = edi; // original 005f4556 cmp ebx, edi
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f455c; // original 005f4558 jl 0x5f455c
    ebx = edi;           // original 005f455a mov ebx, edi
L_005f455c:;
    left = ebx;
    right = ebx;
    left &= right;
    right = 0; // original 005f455c test ebx, ebx
    if (static_cast<int32_t>(left) <= static_cast<int32_t>(right))
        goto L_005f456b;         // original 005f455e jle 0x5f456b
    ebx = load32(frame - 0x28u); // original 005f4560 mov ebx, dword ptr [ebp - 0x28]
    left = ebx;
    right = edi; // original 005f4563 cmp ebx, edi
    if (static_cast<int32_t>(left) < static_cast<int32_t>(right))
        goto L_005f456d; // original 005f4565 jl 0x5f456d
    ebx = edi;           // original 005f4567 mov ebx, edi
    goto L_005f456d;     // original 005f4569 jmp 0x5f456d
L_005f456b:;
    ebx = 0u; // original 005f456b xor ebx, ebx
L_005f456d:;
    edi = load32(frame - 0x4u);            // original 005f456d mov edi, dword ptr [ebp - 4]
    ebx = (ebx) << (0x3u);                 // original 005f4570 shl ebx, 3
    ebx = (ebx) | (load32(frame - 0x34u)); // original 005f4573 or ebx, dword ptr [ebp - 0x34]
    ebx = (ebx) << (0x3u);                 // original 005f4576 shl ebx, 3
    ebx = (ebx) | (load32(frame - 0x30u)); // original 005f4579 or ebx, dword ptr [ebp - 0x30]
    ebx = (ebx) << (0x2u);                 // original 005f457c shl ebx, 2
    ebx = (ebx) | (load32(frame - 0x2cu)); // original 005f457f or ebx, dword ptr [ebp - 0x2c]
    store16(edi, (ebx & 0xffffu));         // original 005f4582 mov word ptr [edi], bx
    edi = (edi) + (load32(frame - 0x20u)); // original 005f4585 add edi, dword ptr [ebp - 0x20]
    store32(frame - 0x4u, edi);            // original 005f4588 mov dword ptr [ebp - 4], edi
    edi = load32(frame - 0x24u);           // original 005f458b mov edi, dword ptr [ebp - 0x24]
    store32(args + 4u,
            (load32(args + 4u)) + (edi));       // original 005f458e add dword ptr [ebp + 0xc], edi
    eax = (eax) + (edi);                        // original 005f4591 add eax, edi
    edx = (edx) + (edi);                        // original 005f4593 add edx, edi
    ecx = (ecx) + (edi);                        // original 005f4595 add ecx, edi
    store32(args + 0u, load32(args + 0u) + 1u); // original 005f4597 inc dword ptr [ebp + 8]
    edi = load32(args + 0u);                    // original 005f459a mov edi, dword ptr [ebp + 8]
    left = edi;
    right = load32(esi + 0x68u); // original 005f459d cmp edi, dword ptr [esi + 0x68]
    if (left < right)
        goto L_005f4313; // original 005f45a0 jb 0x5f4313
L_005f45a6:;
    eax = load32(esi + 0x7cu); // original 005f45a6 mov eax, dword ptr [esi + 0x7c]
    store32(args + 8u, eax);   // original 005f45a9 mov dword ptr [ebp + 0x10], eax
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8u)
                     : "st", "memory"); // original 005f45ac fldcw word ptr [ebp + 0x10]
    ;                                   // C++ ABI restore ownership. // original 005f45af pop edi
    ;                                   // C++ ABI restore ownership. // original 005f45b0 pop esi
    ;                                   // C++ ABI restore ownership. // original 005f45b1 pop ebx
    ;                                   // C++ frame ownership. // original 005f45b2 leave
    return eax;                         // original 005f45b3 ret 0xc
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f421e(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f421e\n\taddl $8,%esp\n\tretl $12");
}
