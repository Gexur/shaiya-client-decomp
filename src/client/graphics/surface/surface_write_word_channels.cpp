#include "graphics/surface/surface_write_word_channels.h"
#include "graphics/surface/surface_write_transform.h"
#include "graphics/surface/surface_write_color.h"
#include "graphics/surface/surface_error_row.h"
#include "graphics/surface/surface_write_rgb24.h"
#include "graphics/surface/surface_byte_word_readers.h"
extern "C" const uint32_t dat_006dc574 = 0x3e59999au;
extern "C" const uint32_t dat_006dc578 = 0x3f372474u;
extern "C" const uint32_t dat_006dc57c = 0x3d93a92au;
extern "C" const uint32_t dat_006de5ac = 0x477fff00u;
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
void half(u32 p, u32 v) {
    __asm__ volatile("movw %w1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void zero(u32& v) {
    __asm__ volatile("fldz\n\tfstps %0" : "=m"(v)::"st", "memory");
}
void luminance(u32 p) {
    __asm__ volatile(
        "flds 8(%0)\n\tfmuls _dat_006dc57c\n\tflds 4(%0)\n\tfmuls _dat_006dc578\n\tfaddp %%st,%%st(1)\n\tflds (%0)\n\tfmuls _dat_006dc574\n\tfaddp %%st,%%st(1)\n\tfstps (%0)" ::
            "r"(p)
        : "st", "memory");
}
void scaled(u32 carry, u32 input, u32& v) {
    __asm__ volatile("flds %1\n\tfadds (%2)\n\tfmuls _dat_006de5ac\n\tfstps %0"
                     : "=m"(v)
                     : "m"(carry), "r"(input)
                     : "st", "memory");
}
void biased(u32 value, u32 bias, u32& rounded) {
    __asm__ volatile("flds %1\n\tfadds %2\n\tfstps %0"
                     : "=m"(rounded)
                     : "m"(value), "m"(bias)
                     : "st", "memory");
}
void integer(u32 value, u32& result) {
    __asm__ volatile("flds %1\n\tfistpl %0" : "=m"(result) : "m"(value) : "st", "memory");
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
    return static_cast<int32_t>(v) >= 65535 ? 65535u : v;
}
void prepare(u32 self, u32 args) {
    if (word(self + 0x54))
        put(args + 8, FUN_005f0da1(reinterpret_cast<void*>(self),
                                   reinterpret_cast<const void*>(word(args + 8))));
    if (word(self + 0x10))
        put(args + 8, FUN_005f22d6(reinterpret_cast<void*>(self),
                                   reinterpret_cast<const void*>(word(args + 8))));
}
void error_neighbor_set(u32 self, u32 current, u32 after, u32 channel, u32 first) {
    neighbor(first, reinterpret_cast<uintptr_t>(&dat_006df41c));
    u32 p = word(self + 0x5c);
    neighbor(p + current + channel, reinterpret_cast<uintptr_t>(&dat_006df418));
    p = word(self + 0x5c);
    neighbor(p + after + channel, reinterpret_cast<uintptr_t>(&dat_006be980));
}
} // namespace
//005f8560..005f8751: L16. FNSTCW overwrites the low half of the
//actual first word; the actual second word becomes the moving error offset.
extern "C" uint32_t recovered_005f8560(uint32_t self, uint32_t args) {
    prepare(self, args);
    const u32 row = word(args);
    u32 gray;
    zero(gray);
    const u32 slice = word(args + 4), rowPitch = word(self + 0x60), slicePitch = word(self + 0x64),
              width = word(self + 0x68);
    put(args, row);
    put(args, word(args) & 1u);
    u32 destination = rowPitch * row + slicePitch * slice + (width - 1u) * word(args) * 2u;
    const u32 dither = word(self + 0x34) + ((slice & 3u) + (row & 3u) * 8u) * 4u;
    destination += word(self + 0x20);
    const bool odd = word(args) != 0;
    const u32 index = odd ? word(self + 0x68) - 1u : 0u;
    put(args + 4, odd ? 0xffffffffu : 1u);
    __asm__ volatile("fnstcw (%0)" ::"r"(args) : "memory");
    const u32 forced = word(args) | 0xc00u;
    __asm__ volatile("fldcw %0" ::"m"(forced) : "memory");
    put(self + 0x7c, word(args));
    u32 n = 0;
    if (word(self + 0x68) != 0) {
        u32 p = word(args + 8);
        do {
            ++n;
            luminance(p);
            p += 16;
        } while (n < word(self + 0x68));
    }
    if (word(self + 0x5c))
        FUN_005f25f2(reinterpret_cast<void*>(self), reinterpret_cast<void*>(word(args + 8)));
    put(args, 0);
    if (word(self + 0x68) != 0) {
        const u32 step = word(args + 4), pixelStep = step << 4, destinationStep = step << 1;
        u32 current = index << 4, after = (step + index) << 4;
        put(args + 4, (index - step) << 4);
        do {
            u32 value, rounded, result;
            scaled(gray, word(args + 8) + current, value);
            __asm__ volatile("flds %1\n\tfadds (%2)\n\tfstps %0"
                             : "=m"(rounded)
                             : "m"(value), "r"(dither + (word(args) & 3u) * 4u)
                             : "st", "memory");
            integer(rounded, result);
            if (word(self + 0x5c)) {
                u32 p = word(self + 0x5c) + word(args + 4) + 16;
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmuls _dat_006df42c" ::"m"(result),
                                 "m"(value)
                                 : "st", "memory");
                error_neighbor_set(self, current, after, 16, p);
                carry(gray);
            }
            half(destination, clamp(result));
            put(args + 4, word(args + 4) + pixelStep);
            destination += destinationStep;
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
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f8560(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f8560\n\taddl $8,%esp\n\tretl $12");
}
//005f892f..005f8bd7: A16L16. Dither remains live across both scaled
//loads, and the reciprocal stays live across both error channels.
extern "C" uint32_t recovered_005f892f(uint32_t self, uint32_t args) {
    prepare(self, args);
    const u32 row = word(args);
    u32 gray, alpha;
    zero(gray);
    const u32 width = word(self + 0x68), rowPitch = word(self + 0x60);
    zero(alpha);
    put(args, row);
    put(args, word(args) & 1u);
    u32 destination = rowPitch * row + (width - 1u) * word(args) * 4u;
    const u32 slice = word(args + 4), slicePitch = word(self + 0x64);
    destination += slicePitch * slice;
    destination += word(self + 0x20);
    const bool odd = word(args) != 0;
    const u32 dither = word(self + 0x34) + ((slice & 3u) + (row & 3u) * 8u) * 4u;
    const u32 index = odd ? width - 1u : 0u;
    put(args + 4, odd ? 0xffffffffu : 1u);
    __asm__ volatile("fnstcw (%0)" ::"r"(args) : "memory");
    const u32 forced = word(args) | 0xc00u;
    __asm__ volatile("fldcw %0" ::"m"(forced) : "memory");
    put(self + 0x7c, word(args));
    u32 n = 0;
    if (word(self + 0x68) != 0) {
        u32 p = word(args + 8);
        do {
            ++n;
            luminance(p);
            p += 16;
        } while (n < word(self + 0x68));
    }
    if (word(self + 0x5c))
        FUN_005f25f2(reinterpret_cast<void*>(self), reinterpret_cast<void*>(word(args + 8)));
    put(args, word(args) & 0u);
    if (word(self + 0x68) != 0) {
        const u32 step = word(args + 4), destinationStep = step << 2, pixelStep = step << 4;
        u32 current = index << 4, after = (step + index) << 4;
        put(args + 4, (index - step) << 4);
        do {
            u32 bias, gv, av, rounded, gi, ai;
            __asm__ volatile("flds (%1)\n\tfsts %0"
                             : "=m"(bias)
                             : "r"(dither + (word(args) & 3u) * 4u)
                             : "st", "memory");
            const u32 p = word(args + 8) + current;
            scaled(gray, p, gv);
            scaled(alpha, p + 12, av);
            __asm__ volatile("flds %1\n\tfadd %%st(1),%%st\n\tfstps %0\n\tfstp %%st(0)"
                             : "=m"(rounded)
                             : "m"(gv)
                             : "st", "memory");
            integer(rounded, gi);
            biased(av, bias, rounded);
            integer(rounded, ai);
            if (word(self + 0x5c)) {
                __asm__ volatile("flds _dat_006df42c" ::: "st", "memory");
                u32 first = word(self + 0x5c) + word(args + 4) + 16;
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmul %%st(1),%%st" ::"m"(gi), "m"(gv)
                                 : "st", "memory");
                error_neighbor_set(self, current, after, 16, first);
                first = word(self + 0x5c) + word(args + 4) + 28;
                carry(gray);
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmulp %%st,%%st(1)" ::"m"(ai), "m"(av)
                                 : "st", "memory");
                error_neighbor_set(self, current, after, 28, first);
                carry(alpha);
            }
            put(destination, (clamp(ai) << 16) | clamp(gi));
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
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f892f(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f892f\n\taddl $8,%esp\n\tretl $12");
}
//005f8bd7..005f8eda: B16G16R16. The second actual word receives
//FNSTCW without clearing its high half; G/R stores precede the B store.
extern "C" uint32_t recovered_005f8bd7(uint32_t self, uint32_t args) {
    prepare(self, args);
    const u32 row = word(args);
    u32 cr, cg, cb;
    zero(cr);
    const u32 width = word(self + 0x68), rowPitch = word(self + 0x60);
    __asm__ volatile("fldz" ::: "st", "memory");
    put(args, row);
    __asm__ volatile("fstps %0" : "=m"(cg)::"st", "memory");
    zero(cb);
    put(args, word(args) & 1u);
    u32 destination = rowPitch * row + (width - 1u) * word(args) * 6u;
    const u32 slice = word(args + 4), slicePitch = word(self + 0x64);
    const u32 dither = word(self + 0x34) + ((slice & 3u) + (row & 3u) * 8u) * 4u;
    destination += slicePitch * slice;
    destination += word(self + 0x20);
    const bool odd = word(args) != 0;
    const u32 index = odd ? width - 1u : 0u;
    put(args, odd ? 0xffffffffu : 1u);
    u32 step = word(args);
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 4) : "memory");
    const u32 forced = word(args + 4) | 0xc00u;
    __asm__ volatile("fldcw %0" ::"m"(forced) : "memory");
    put(self + 0x7c, word(args + 4));
    if (word(self + 0x5c)) {
        FUN_005f25f2(reinterpret_cast<void*>(self), reinterpret_cast<void*>(word(args + 8)));
        step = word(args);
    }
    put(args, word(args) & 0u);
    if (word(self + 0x68) != 0) {
        const u32 destinationStep = step * 6u, pixelStep = step << 4;
        u32 current = index << 4, after = (step + index) << 4;
        const u32 input = word(args + 8);
        put(args + 4, (index - step) << 4);
        put(args + 8, input + current + 8u);
        do {
            u32 bias, rv, gv, bv, rounded, ri, gi, bi;
            __asm__ volatile("flds (%1)\n\tfsts %0"
                             : "=m"(bias)
                             : "r"(dither + (word(args) & 3u) * 4u)
                             : "st", "memory");
            const u32 p = word(args + 8);
            scaled(cr, p - 8, rv);
            scaled(cg, p - 4, gv);
            scaled(cb, p, bv);
            __asm__ volatile("flds %1\n\tfadd %%st(1),%%st\n\tfstps %0\n\tfstp %%st(0)"
                             : "=m"(rounded)
                             : "m"(rv)
                             : "st", "memory");
            integer(rounded, ri);
            biased(gv, bias, rounded);
            integer(rounded, gi);
            biased(bv, bias, rounded);
            integer(rounded, bi);
            if (word(self + 0x5c)) {
                __asm__ volatile("flds _dat_006df42c" ::: "st", "memory");
                u32 first = word(self + 0x5c) + word(args + 4) + 16;
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmul %%st(1),%%st" ::"m"(ri), "m"(rv)
                                 : "st", "memory");
                error_neighbor_set(self, current, after, 16, first);
                first = word(self + 0x5c) + word(args + 4) + 20;
                carry(cr);
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmul %%st(1),%%st" ::"m"(gi), "m"(gv)
                                 : "st", "memory");
                error_neighbor_set(self, current, after, 20, first);
                first = word(self + 0x5c) + word(args + 4) + 24;
                carry(cg);
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmulp %%st,%%st(1)" ::"m"(bi), "m"(bv)
                                 : "st", "memory");
                error_neighbor_set(self, current, after, 24, first);
                carry(cb);
            }
            half(destination + 2, clamp(gi));
            half(destination + 4, clamp(ri));
            put(args + 8, word(args + 8) + pixelStep);
            put(args + 4, word(args + 4) + pixelStep);
            half(destination, clamp(bi));
            destination += destinationStep;
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
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f8bd7(void*, uint32_t, uint32_t,
                                                                  const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f8bd7\n\taddl $8,%esp\n\tretl $12");
}
