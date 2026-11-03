#include "graphics/surface/surface_write_rgb24.h"
#include "graphics/surface/surface_write_transform.h"
#include "graphics/surface/surface_write_color.h"
#include "graphics/surface/surface_error_row.h"
extern "C" {
extern const uint32_t dat_006bc8c4 = 0x437f0000u;
extern const uint64_t dat_006df410 = 0x3fdc000000000000ull;
extern const uint32_t dat_006df418 = 0x3ea00000u;
extern const uint32_t dat_006df41c = 0x3e400000u;
extern const uint32_t dat_006be980 = 0x3d800000u;
extern const uint32_t dat_006be1d0;
}
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
void byte(u32 p, u32 v) {
    __asm__ volatile("movb %b1,(%0)" ::"r"(p), "q"(v) : "memory");
}
void zero(u32& v) {
    __asm__ volatile("fldz\n\tfstps %0" : "=m"(v)::"st", "memory");
}
void scaled(u32 carry, u32 input, u32& v) {
    __asm__ volatile("flds %1\n\tfadds (%2)\n\tfmuls _dat_006bc8c4\n\tfstps %0"
                     : "=m"(v)
                     : "m"(carry), "r"(input)
                     : "st", "memory");
}
void neighbor(u32 p, u32 coefficient) {
    __asm__ volatile("flds (%1)\n\tfmul %%st(1),%%st\n\tfadds (%0)\n\tfstps (%0)" ::"r"(p),
                     "r"(coefficient)
                     : "st", "memory");
}
void carry(u32& value) {
    __asm__ volatile("fmull _dat_006df410\n\tfstps %0" : "=m"(value)::"st", "memory");
}
u32 clamp(u32 v) {
    if (static_cast<int32_t>(v) <= 0)
        return 0;
    return static_cast<int32_t>(v) >= 255 ? 255 : v;
}
} // namespace
// Complete005f2664..005f2961, including the active post-RET blue-zero branch.
// The argument-address adapter preserves all three actual caller-word rewrites.
extern "C" uint32_t recovered_005f2664(uint32_t self, uint32_t args) {
    if (word(self + 0x54))
        put(args + 8, FUN_005f0da1(reinterpret_cast<void*>(self),
                                   reinterpret_cast<const void*>(word(args + 8))));
    if (word(self + 0x10))
        put(args + 8, FUN_005f22d6(reinterpret_cast<void*>(self),
                                   reinterpret_cast<const void*>(word(args + 8))));
    const u32 row = word(args);
    u32 cr, cg, cb;
    __asm__ volatile("fldz" ::: "st", "memory");
    const u32 width = word(self + 0x68);
    __asm__ volatile("fstps %0" : "=m"(cr)::"st", "memory");
    put(args, row);
    __asm__ volatile("fldz" ::: "st", "memory");
    put(args, word(args) & 1u);
    __asm__ volatile("fstps %0" : "=m"(cg)::"st", "memory");
    const u32 slicePitch = word(self + 0x64);
    __asm__ volatile("fldz" ::: "st", "memory");
    const u32 first = (width - 1u) * word(args);
    __asm__ volatile("fstps %0" : "=m"(cb)::"st", "memory");
    u32 destination = first * 3u + word(self + 0x60) * row;
    const u32 slice = word(args + 4);
    const u32 dither = word(self + 0x34) + ((slice & 3u) + (row & 3u) * 8u) * 4u;
    destination += slicePitch * slice;
    destination += word(self + 0x20);
    u32 index, step;
    if (word(args) == 0) {
        index = 0;
        step = 1;
        put(args, step);
    } else {
        index = width - 1u;
        put(args, word(args) | 0xffffffffu);
        step = word(args);
    }
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 4) : "memory");
    const u32 trunc = word(args + 4) | 0x0c00u;
    __asm__ volatile("fldcw %0" ::"m"(trunc) : "memory");
    put(self + 0x7c, word(args + 4));
    if (word(self + 0x5c)) {
        FUN_005f25f2(reinterpret_cast<void*>(self), reinterpret_cast<void*>(word(args + 8)));
        step = word(args);
    }
    put(args, word(args) & 0u);
    if (word(self + 0x68) != 0) {
        const u32 destinationStep = step * 3u, pixelStep = step << 4;
        u32 before = index << 4, after = (index + step) << 4, previous = (index - step) << 4;
        const u32 input = word(args + 8);
        put(args + 4, previous);
        put(args + 8, input + before + 8u);
        do {
            const u32 which = word(args) & 3u;
            __asm__ volatile("flds (%0)" ::"r"(dither + which * 4u) : "st", "memory");
            const u32 pixel = word(args + 8);
            u32 bias, r, g, b, ri, gi, bi, rounded;
            __asm__ volatile("fsts %0" : "=m"(bias)::"memory");
            scaled(cr, pixel - 8, r);
            scaled(cg, pixel - 4, g);
            scaled(cb, pixel, b);
            __asm__ volatile("flds %1\n\tfadd %%st(1),%%st\n\tfstps %0\n\tfstp %%st(0)"
                             : "=m"(rounded)
                             : "m"(r)
                             : "st", "memory");
            __asm__ volatile("flds %1\n\tfistpl %0" : "=m"(ri) : "m"(rounded) : "st", "memory");
            __asm__ volatile("flds %1\n\tfadds %2\n\tfstps %0"
                             : "=m"(rounded)
                             : "m"(g), "m"(bias)
                             : "st", "memory");
            __asm__ volatile("flds %1\n\tfistpl %0" : "=m"(gi) : "m"(rounded) : "st", "memory");
            __asm__ volatile("flds %1\n\tfadds %2\n\tfstps %0"
                             : "=m"(rounded)
                             : "m"(b), "m"(bias)
                             : "st", "memory");
            __asm__ volatile("flds %1\n\tfistpl %0" : "=m"(bi) : "m"(rounded) : "st", "memory");
            if (word(self + 0x5c)) {
                __asm__ volatile("flds _dat_006be1d0" ::: "st", "memory");
                u32 current = word(self + 0x5c);
                const u32 past = word(args + 4);
                current += past + 16;
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
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmulp %%st,%%st(1)" ::"m"(bi), "m"(b)
                                 : "st", "memory");
                neighbor(current, reinterpret_cast<uintptr_t>(&dat_006df41c));
                current = word(self + 0x5c);
                neighbor(current + before + 24, reinterpret_cast<uintptr_t>(&dat_006df418));
                current = word(self + 0x5c);
                neighbor(current + after + 24, reinterpret_cast<uintptr_t>(&dat_006be980));
                carry(cb);
            }
            ri = clamp(ri);
            gi = clamp(gi);
            bi = clamp(bi);
            byte(destination, bi);
            byte(destination + 1, gi);
            byte(destination + 2, ri);
            put(args + 8, word(args + 8) + pixelStep);
            put(args + 4, word(args + 4) + pixelStep);
            destination += destinationStep;
            before += pixelStep;
            after += pixelStep;
            put(args, word(args) + 1u);
        } while (word(args) < word(self + 0x68));
    }
    const u32 result = word(self + 0x7c);
    put(args + 8, result);
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8) : "memory");
    return result;
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f2664(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f2664\n\taddl $8,%esp\n\tretl $12");
}
