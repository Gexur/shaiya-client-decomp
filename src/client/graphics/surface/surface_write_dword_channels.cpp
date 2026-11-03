#include "graphics/surface/surface_write_dword_channels.h"
#include "graphics/surface/surface_write_transform.h"
#include "graphics/surface/surface_write_color.h"
#include "graphics/surface/surface_error_row.h"
#include "graphics/surface/surface_write_rgb24.h"
extern "C" {
extern const uint32_t dat_006bc8c4, dat_006de5ac, dat_006df42c, dat_006be1d0, dat_006df424,
    dat_006bca1c, dat_006c2bb4;
extern const uint32_t dat_006df428 = 0x447fc000u;
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
void zero(u32& v) {
    __asm__ volatile("fldz\n\tfstps %0" : "=m"(v)::"st", "memory");
}
void scaled(u32 carry, u32 input, u32 coefficient, u32& v) {
    __asm__ volatile("flds %1\n\tfadds (%2)\n\tfmuls (%3)\n\tfstps %0"
                     : "=m"(v)
                     : "m"(carry), "r"(input), "r"(coefficient)
                     : "st", "memory");
}
void rounded(u32 value, u32 bias, u32& result) {
    u32 temp;
    __asm__ volatile("flds %1\n\tfadds (%2)\n\tfstps %0"
                     : "=m"(temp)
                     : "m"(value), "r"(bias)
                     : "st", "memory");
    __asm__ volatile("flds %1\n\tfistpl %0" : "=m"(result) : "m"(temp) : "st", "memory");
}
void first_integer(u32 value, u32& result) {
    u32 temp;
    __asm__ volatile("flds %1\n\tfadd %%st(1),%%st\n\tfstps %0\n\tfstp %%st(0)"
                     : "=m"(temp)
                     : "m"(value)
                     : "st", "memory");
    __asm__ volatile("flds %1\n\tfistpl %0" : "=m"(result) : "m"(temp) : "st", "memory");
}
void neighbor(u32 p, u32 coefficient) {
    __asm__ volatile("flds (%1)\n\tfmul %%st(1),%%st\n\tfadds (%0)\n\tfstps (%0)" ::"r"(p),
                     "r"(coefficient)
                     : "st", "memory");
}
void carry(u32& v) {
    __asm__ volatile("fmull _dat_006df410\n\tfstps %0" : "=m"(v)::"st", "memory");
}
u32 clamp(u32 v, u32 high) {
    if (static_cast<int32_t>(v) <= 0)
        return 0;
    return static_cast<int32_t>(v) >= static_cast<int32_t>(high) ? high : v;
}
u32 addr(const u32& v) {
    return reinterpret_cast<uintptr_t>(&v);
}
void prepare(u32 self, u32 args) {
    if (word(self + 0x54))
        put(args + 8, FUN_005f0da1(reinterpret_cast<void*>(self),
                                   reinterpret_cast<const void*>(word(args + 8))));
    if (word(self + 0x10))
        put(args + 8, FUN_005f22d6(reinterpret_cast<void*>(self),
                                   reinterpret_cast<const void*>(word(args + 8))));
}
void neighbors(u32 self, u32 current, u32 after, u32 channel, u32 first) {
    neighbor(first, addr(dat_006df41c));
    u32 p = word(self + 0x5c);
    neighbor(p + current + channel, addr(dat_006df418));
    p = word(self + 0x5c);
    neighbor(p + after + channel, addr(dat_006be980));
}
} // namespace
//005f5019..005f532f: R8G8B8 in a32-bit word, with the actual second word holding dither/last rounding.
extern "C" uint32_t recovered_005f5019(uint32_t self, uint32_t args) {
    prepare(self, args);
    const u32 row = word(args);
    u32 cr, cg, cb;
    __asm__ volatile("fldz" ::: "st", "memory");
    const u32 width = word(self + 0x68);
    __asm__ volatile("fstps %0" : "=m"(cr)::"st", "memory");
    const u32 rowPitch = word(self + 0x60);
    __asm__ volatile("fldz" ::: "st", "memory");
    const u32 slicePitch = word(self + 0x64);
    __asm__ volatile("fstps %0" : "=m"(cg)::"st", "memory");
    zero(cb);
    put(args, row);
    put(args, word(args) & 1u);
    u32 destination = rowPitch * row + (width - 1u) * word(args) * 4u;
    const u32 slice = word(args + 4);
    destination += slicePitch * slice;
    destination += word(self + 0x20);
    const u32 dither = word(self + 0x34) + ((slice & 3u) + (row & 3u) * 8u) * 4u;
    const bool odd = word(args) != 0;
    const u32 index = odd ? width - 1u : 0u, step = odd ? 0xffffffffu : 1u;
    __asm__ volatile("fnstcw (%0)" ::"r"(args) : "memory");
    put(args + 4, word(args) | 0xc00u);
    __asm__ volatile("fldcw (%0)" ::"r"(args + 4) : "memory");
    put(self + 0x7c, word(args));
    if (word(self + 0x5c))
        FUN_005f25f2(reinterpret_cast<void*>(self), reinterpret_cast<void*>(word(args + 8)));
    put(args, word(args) & 0u);
    if (word(self + 0x68) != 0) {
        const u32 pixelStep = step << 4, destinationStep = step << 2;
        u32 current = index << 4, after = (step + index) << 4, before = (index - step) << 4;
        put(args + 8, word(args + 8) + current + 8u);
        do {
            __asm__ volatile("flds (%0)" ::"r"(dither + (word(args) & 3u) * 4u) : "st", "memory");
            const u32 pixel = word(args + 8);
            __asm__ volatile("fsts (%0)" ::"r"(args + 4) : "memory");
            u32 r, g, b, ri, gi, bi, temp;
            scaled(cr, pixel - 8, addr(dat_006bc8c4), r);
            scaled(cg, pixel - 4, addr(dat_006bc8c4), g);
            scaled(cb, pixel, addr(dat_006bc8c4), b);
            first_integer(r, ri);
            rounded(g, args + 4, gi);
            __asm__ volatile("flds %0\n\tfadds (%1)\n\tfstps (%1)" ::"m"(b), "r"(args + 4)
                             : "st", "memory");
            temp = word(args + 4);
            __asm__ volatile("flds %1\n\tfistpl %0" : "=m"(bi) : "m"(temp) : "st", "memory");
            if (word(self + 0x5c)) {
                __asm__ volatile("flds _dat_006be1d0" ::: "st", "memory");
                u32 first = word(self + 0x5c) + before + 16;
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmul %%st(1),%%st" ::"m"(ri), "m"(r)
                                 : "st", "memory");
                neighbors(self, current, after, 16, first);
                first = word(self + 0x5c) + before + 20;
                carry(cr);
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmul %%st(1),%%st" ::"m"(gi), "m"(g)
                                 : "st", "memory");
                neighbors(self, current, after, 20, first);
                first = word(self + 0x5c) + before + 24;
                carry(cg);
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmulp %%st,%%st(1)" ::"m"(bi), "m"(b)
                                 : "st", "memory");
                neighbors(self, current, after, 24, first);
                carry(cb);
            }
            put(destination, ((clamp(bi, 255) << 8) | clamp(gi, 255)) << 8 | clamp(ri, 255));
            destination += destinationStep;
            put(args + 8, word(args + 8) + pixelStep);
            current += pixelStep;
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
//005f532f..005f55a4: two16-bit channels, with the actual second word changing from step to error offset.
extern "C" uint32_t recovered_005f532f(uint32_t self, uint32_t args) {
    prepare(self, args);
    const u32 row = word(args);
    u32 cr, cg;
    __asm__ volatile("fldz" ::: "st", "memory");
    const u32 width = word(self + 0x68);
    __asm__ volatile("fstps %0" : "=m"(cr)::"st", "memory");
    const u32 rowPitch = word(self + 0x60);
    zero(cg);
    put(args, row);
    put(args, word(args) & 1u);
    u32 destination = rowPitch * row + (width - 1u) * word(args) * 4u;
    const u32 slice = word(args + 4), slicePitch = word(self + 0x64);
    destination += slicePitch * slice;
    destination += word(self + 0x20);
    const bool odd = word(args) != 0;
    const u32 dither = word(self + 0x34) + ((slice & 3u) + (row & 3u) * 8u) * 4u,
              index = odd ? width - 1u : 0u;
    if (odd)
        put(args + 4, word(args + 4) | 0xffffffffu);
    else
        put(args + 4, 1);
    __asm__ volatile("fnstcw (%0)" ::"r"(args) : "memory");
    const u32 forced = word(args) | 0xc00u;
    __asm__ volatile("fldcw %0" ::"m"(forced) : "memory");
    put(self + 0x7c, word(args));
    if (word(self + 0x5c))
        FUN_005f25f2(reinterpret_cast<void*>(self), reinterpret_cast<void*>(word(args + 8)));
    put(args, word(args) & 0u);
    if (word(self + 0x68) != 0) {
        const u32 step = word(args + 4), pixelStep = step << 4, destinationStep = step << 2;
        u32 current = index << 4, after = (step + index) << 4;
        put(args + 4, (index - step) << 4);
        do {
            u32 bias, r, g, ri, gi;
            __asm__ volatile("flds (%1)\n\tfsts %0"
                             : "=m"(bias)
                             : "r"(dither + (word(args) & 3u) * 4u)
                             : "st", "memory");
            const u32 pixel = word(args + 8) + current;
            scaled(cr, pixel, addr(dat_006de5ac), r);
            scaled(cg, pixel + 4, addr(dat_006de5ac), g);
            first_integer(r, ri);
            rounded(g, addr(bias), gi);
            if (word(self + 0x5c)) {
                __asm__ volatile("flds _dat_006df42c" ::: "st", "memory");
                u32 first = word(self + 0x5c);
                const u32 before = word(args + 4);
                first += before + 16;
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmul %%st(1),%%st" ::"m"(ri), "m"(r)
                                 : "st", "memory");
                neighbors(self, current, after, 16, first);
                first = word(self + 0x5c) + before + 20;
                carry(cr);
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmulp %%st,%%st(1)" ::"m"(gi), "m"(g)
                                 : "st", "memory");
                neighbors(self, current, after, 20, first);
                carry(cg);
            }
            put(destination, (clamp(gi, 65535) << 16) | clamp(ri, 65535));
            destination += destinationStep;
            put(args + 4, word(args + 4) + pixelStep);
            current += pixelStep;
            after += pixelStep;
            put(args, word(args) + 1u);
        } while (word(args) < word(self + 0x68));
    }
    const u32 result = word(self + 0x7c);
    put(args + 8, result);
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8) : "memory");
    return result;
}
//005f55a4..005f5959: A2R10G10B10. Dither is stored in the actual third word, moving input in second.
extern "C" uint32_t recovered_005f55a4(uint32_t self, uint32_t args) {
    prepare(self, args);
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
    u32 destination = rowPitch * row + (width - 1u) * word(args) * 4u;
    const u32 slice = word(args + 4);
    destination += slicePitch * slice;
    destination += word(self + 0x20);
    const bool odd = word(args) != 0;
    const u32 dither = word(self + 0x34) + ((slice & 3u) + (row & 3u) * 8u) * 4u,
              index = odd ? width - 1u : 0u, step = odd ? 0xffffffffu : 1u;
    __asm__ volatile("fnstcw (%0)" ::"r"(args) : "memory");
    put(args + 4, word(args) | 0xc00u);
    __asm__ volatile("fldcw (%0)" ::"r"(args + 4) : "memory");
    put(self + 0x7c, word(args));
    if (word(self + 0x5c))
        FUN_005f25f2(reinterpret_cast<void*>(self), reinterpret_cast<void*>(word(args + 8)));
    put(args, word(args) & 0u);
    if (word(self + 0x68) != 0) {
        const u32 pixelStep = step << 4, destinationStep = step << 2;
        u32 current = index << 4, after = (step + index) << 4, before = (index - step) << 4;
        put(args + 4, word(args + 8) + current + 8u);
        do {
            __asm__ volatile("flds (%0)" ::"r"(dither + (word(args) & 3u) * 4u) : "st", "memory");
            const u32 pixel = word(args + 4);
            __asm__ volatile("fsts (%0)" ::"r"(args + 8) : "memory");
            u32 r, g, b, a, ri, gi, bi, ai, temp;
            scaled(cr, pixel - 8, addr(dat_006df428), r);
            scaled(cg, pixel - 4, addr(dat_006df428), g);
            scaled(cb, pixel, addr(dat_006df428), b);
            scaled(ca, pixel + 4, addr(dat_006bca1c), a);
            first_integer(r, ri);
            rounded(g, args + 8, gi);
            rounded(b, args + 8, bi);
            __asm__ volatile("flds %0\n\tfadds (%1)\n\tfstps (%1)" ::"m"(a), "r"(args + 8)
                             : "st", "memory");
            temp = word(args + 8);
            __asm__ volatile("flds %1\n\tfistpl %0" : "=m"(ai) : "m"(temp) : "st", "memory");
            if (word(self + 0x5c)) {
                __asm__ volatile("flds _dat_006df424" ::: "st", "memory");
                u32 first = word(self + 0x5c) + before + 16;
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmul %%st(1),%%st" ::"m"(ri), "m"(r)
                                 : "st", "memory");
                neighbors(self, current, after, 16, first);
                first = word(self + 0x5c) + before + 20;
                carry(cr);
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmul %%st(1),%%st" ::"m"(gi), "m"(g)
                                 : "st", "memory");
                neighbors(self, current, after, 20, first);
                first = word(self + 0x5c) + before + 24;
                carry(cg);
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmulp %%st,%%st(1)" ::"m"(bi), "m"(b)
                                 : "st", "memory");
                neighbors(self, current, after, 24, first);
                first = word(self + 0x5c) + before + 28;
                carry(cb);
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmuls _dat_006c2bb4" ::"m"(ai), "m"(a)
                                 : "st", "memory");
                neighbors(self, current, after, 28, first);
                carry(ca);
            }
            put(destination,
                (((((clamp(ai, 3) << 10) | clamp(ri, 1023)) << 10) | clamp(gi, 1023)) << 10) |
                    clamp(bi, 1023));
            destination += destinationStep;
            put(args + 4, word(args + 4) + pixelStep);
            current += pixelStep;
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
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f5019(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f5019\n\taddl $8,%esp\n\tretl $12");
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f532f(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f532f\n\taddl $8,%esp\n\tretl $12");
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f55a4(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f55a4\n\taddl $8,%esp\n\tretl $12");
}
