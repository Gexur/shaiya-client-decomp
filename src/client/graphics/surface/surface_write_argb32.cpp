#include "graphics/surface/surface_write_argb32.h"
#include "graphics/surface/surface_write_rgb24.h"
#include "graphics/surface/surface_write_transform.h"
#include "graphics/surface/surface_write_color.h"
#include "graphics/surface/surface_error_row.h"
extern "C" const uint32_t dat_006be1d0;
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void zero(u32& v) {
    __asm__ volatile("fldz\n\tfstps %0" : "=m"(v)::"st", "memory");
}
void scaled(u32 carry, u32 input, u32& v) {
    __asm__ volatile("flds %1\n\tfadds (%2)\n\tfmul %%st(2),%%st\n\tfstps %0"
                     : "=m"(v)
                     : "m"(carry), "r"(input)
                     : "st", "memory");
}
void neighbor(u32 p, u32 coefficient) {
    __asm__ volatile("flds (%1)\n\tfmul %%st(1),%%st\n\tfadds (%0)\n\tfstps (%0)" ::"r"(p),
                     "r"(coefficient)
                     : "st", "memory");
}
void carry(u32& v) {
    __asm__ volatile("fmull _dat_006df410\n\tfstps %0" : "=m"(v)::"st", "memory");
}
u32 clamp(u32 v) {
    if (static_cast<int32_t>(v) <= 0)
        return 0;
    return static_cast<int32_t>(v) >= 255 ? 255 : v;
}
} // namespace
// Complete005f2961..005f2d10. Bias and alpha spills target the actual third
// incoming word, while the second incoming word becomes the pixel cursor.
extern "C" uint32_t recovered_005f2961(uint32_t self, uint32_t args) {
    if (word(self + 0x54))
        put(args + 8, FUN_005f0da1(reinterpret_cast<void*>(self),
                                   reinterpret_cast<const void*>(word(args + 8))));
    if (word(self + 0x10))
        put(args + 8, FUN_005f22d6(reinterpret_cast<void*>(self),
                                   reinterpret_cast<const void*>(word(args + 8))));
    const u32 row = word(args);
    u32 cr, cg, cb, ca;
    __asm__ volatile("fldz" ::: "st", "memory");
    const u32 width = word(self + 0x68);
    __asm__ volatile("fstps %0" : "=m"(cr)::"st", "memory");
    const u32 rowPitch = word(self + 0x60);
    __asm__ volatile("fldz" ::: "st", "memory");
    const u32 slicePitch = word(self + 0x64);
    __asm__ volatile("fstps %0" : "=m"(cg)::"st", "memory");
    zero(cb);
    zero(ca);
    put(args, row);
    put(args, word(args) & 1u);
    const u32 first = (width - 1u) * word(args);
    u32 destination = rowPitch * row + first * 4u;
    const u32 slice = word(args + 4);
    destination += slicePitch * slice;
    destination += word(self + 0x20);
    const u32 odd = word(args);
    const u32 dither = word(self + 0x34) + ((slice & 3u) + (row & 3u) * 8u) * 4u;
    const u32 step = odd ? 0xffffffffu : 1u, index = odd ? width - 1u : 0u;
    __asm__ volatile("fnstcw (%0)" ::"r"(args) : "memory");
    put(args + 4, word(args) | 0x0c00u);
    __asm__ volatile("fldcw (%0)" ::"r"(args + 4) : "memory");
    put(self + 0x7c, word(args));
    if (word(self + 0x5c))
        FUN_005f25f2(reinterpret_cast<void*>(self), reinterpret_cast<void*>(word(args + 8)));
    put(args, word(args) & 0u);
    if (word(self + 0x68) != 0) {
        const u32 input = word(args + 8), destinationStep = step << 2, pixelStep = step << 4;
        u32 before = index << 4, after = (index + step) << 4, past = (index - step) << 4;
        put(args + 4, input + before + 8u);
        do {
            const u32 which = word(args);
            __asm__ volatile("flds _dat_006bc8c4" ::: "st", "memory");
            __asm__ volatile("flds (%0)" ::"r"(dither + (which & 3u) * 4u) : "st", "memory");
            const u32 pixel = word(args + 4);
            u32 r, g, b, a, ri, gi, bi, ai, rounded;
            __asm__ volatile("fsts (%0)" ::"r"(args + 8) : "memory");
            scaled(cr, pixel - 8, r);
            scaled(cg, pixel - 4, g);
            scaled(cb, pixel, b);
            scaled(ca, pixel + 4, a);
            __asm__ volatile(
                "flds %1\n\tfadd %%st(1),%%st\n\tfstps %0\n\tfstp %%st(0)\n\tfstp %%st(0)"
                : "=m"(rounded)
                : "m"(r)
                : "st", "memory");
            __asm__ volatile("flds %1\n\tfistpl %0" : "=m"(ri) : "m"(rounded) : "st", "memory");
            __asm__ volatile("flds %1\n\tfadds (%2)\n\tfstps %0"
                             : "=m"(rounded)
                             : "m"(g), "r"(args + 8)
                             : "st", "memory");
            __asm__ volatile("flds %1\n\tfistpl %0" : "=m"(gi) : "m"(rounded) : "st", "memory");
            __asm__ volatile("flds %1\n\tfadds (%2)\n\tfstps %0"
                             : "=m"(rounded)
                             : "m"(b), "r"(args + 8)
                             : "st", "memory");
            __asm__ volatile("flds %1\n\tfistpl %0" : "=m"(bi) : "m"(rounded) : "st", "memory");
            __asm__ volatile("flds %0\n\tfadds (%1)\n\tfstps (%1)" ::"m"(a), "r"(args + 8)
                             : "st", "memory");
            __asm__ volatile("flds (%1)\n\tfistpl %0" : "=m"(ai) : "r"(args + 8) : "st", "memory");
            if (word(self + 0x5c)) {
                __asm__ volatile("flds _dat_006be1d0" ::: "st", "memory");
                u32 current = word(self + 0x5c) + past + 16;
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmul %%st(1),%%st" ::"m"(ri), "m"(r)
                                 : "st", "memory");
                neighbor(current, reinterpret_cast<uintptr_t>(&dat_006df41c));
                current = word(self + 0x5c);
                neighbor(current + before + 16, reinterpret_cast<uintptr_t>(&dat_006df418));
                current = word(self + 0x5c);
                neighbor(current + after + 16, reinterpret_cast<uintptr_t>(&dat_006be980));
                current = word(self + 0x5c) + past + 20;
                carry(cr);
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmul %%st(1),%%st" ::"m"(gi), "m"(g)
                                 : "st", "memory");
                neighbor(current, reinterpret_cast<uintptr_t>(&dat_006df41c));
                current = word(self + 0x5c);
                neighbor(current + before + 20, reinterpret_cast<uintptr_t>(&dat_006df418));
                current = word(self + 0x5c);
                neighbor(current + after + 20, reinterpret_cast<uintptr_t>(&dat_006be980));
                current = word(self + 0x5c) + past + 24;
                carry(cg);
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmul %%st(1),%%st" ::"m"(bi), "m"(b)
                                 : "st", "memory");
                neighbor(current, reinterpret_cast<uintptr_t>(&dat_006df41c));
                current = word(self + 0x5c);
                neighbor(current + before + 24, reinterpret_cast<uintptr_t>(&dat_006df418));
                current = word(self + 0x5c);
                neighbor(current + after + 24, reinterpret_cast<uintptr_t>(&dat_006be980));
                current = word(self + 0x5c) + past + 28;
                carry(cb);
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmulp %%st,%%st(1)" ::"m"(ai), "m"(a)
                                 : "st", "memory");
                neighbor(current, reinterpret_cast<uintptr_t>(&dat_006df41c));
                current = word(self + 0x5c);
                neighbor(current + before + 28, reinterpret_cast<uintptr_t>(&dat_006df418));
                current = word(self + 0x5c);
                neighbor(current + after + 28, reinterpret_cast<uintptr_t>(&dat_006be980));
                carry(ca);
            }
            put(destination, (((clamp(ai) << 8) | clamp(ri)) << 8 | clamp(gi)) << 8 | clamp(bi));
            destination += destinationStep;
            put(args + 4, word(args + 4) + pixelStep);
            before += pixelStep;
            past += pixelStep;
            after += pixelStep;
            put(args, word(args) + 1u);
        } while (word(args) < word(self + 0x68));
    }
    const u32 result = word(self + 0x7c);
    put(args + 8, result);
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8) : "memory");
    return result;
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f2961(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f2961\n\taddl $8,%esp\n\tretl $12");
}
