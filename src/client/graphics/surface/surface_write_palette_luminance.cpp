#include "graphics/surface/surface_write_palette_luminance.h"
#include "graphics/surface/surface_write_transform.h"
#include "graphics/surface/surface_write_color.h"
#include "graphics/surface/surface_error_row.h"
#include "graphics/surface/surface_write_rgb24.h"
#include "graphics/surface/surface_write_word_channels.h"
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
void half(u32 p, u32 v) {
    __asm__ volatile("movw %w1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void zero(u32& v) {
    __asm__ volatile("fldz\n\tfstps %0" : "=m"(v)::"st", "memory");
}
u32 prepare(u32 self, u32 args, bool spill) {
    u32 input;
    if (word(self + 0x54)) {
        input = FUN_005f0da1(reinterpret_cast<void*>(self),
                             reinterpret_cast<const void*>(word(args + 8)));
        if (spill)
            put(args + 8, input);
    } else
        input = word(args + 8);
    if (word(self + 0x10)) {
        input = FUN_005f22d6(reinterpret_cast<void*>(self),
                             reinterpret_cast<const void*>(spill ? word(args + 8) : input));
        if (spill)
            put(args + 8, input);
    }
    return input;
}
void luminance(u32 p) {
    __asm__ volatile(
        "flds 8(%0)\n\tfmuls _dat_006dc57c\n\tflds 4(%0)\n\tfmuls _dat_006dc578\n\tfaddp %%st,%%st(1)\n\tflds (%0)\n\tfmuls _dat_006dc574\n\tfaddp %%st,%%st(1)\n\tfstps (%0)" ::
            "r"(p)
        : "st", "memory");
}
void scaled(u32 carry, u32 input, u32& v) {
    __asm__ volatile("flds %1\n\tfadds (%2)\n\tfmuls _dat_006bc8c4\n\tfstps %0"
                     : "=m"(v)
                     : "m"(carry), "r"(input)
                     : "st", "memory");
}
void integer(u32 p, u32& v) {
    __asm__ volatile("flds (%1)\n\tfistpl %0" : "=m"(v) : "r"(p) : "st", "memory");
}
void neighbor(u32 p, u32 coefficient) {
    __asm__ volatile("flds (%1)\n\tfmul %%st(1),%%st\n\tfadds (%0)\n\tfstps (%0)" ::"r"(p),
                     "r"(coefficient)
                     : "st", "memory");
}
void neighbors(u32 self, u32 current, u32 after, u32 channel, u32 first) {
    neighbor(first, reinterpret_cast<uintptr_t>(&dat_006df41c));
    u32 p = word(self + 0x5c);
    neighbor(p + current + channel, reinterpret_cast<uintptr_t>(&dat_006df418));
    p = word(self + 0x5c);
    neighbor(p + after + channel, reinterpret_cast<uintptr_t>(&dat_006be980));
}
void carry(u32& v) {
    __asm__ volatile("fmull _dat_006df410\n\tfstps %0" : "=m"(v)::"st", "memory");
}
u32 clamp(u32 v) {
    return static_cast<int32_t>(v) <= 0 ? 0 : static_cast<int32_t>(v) >= 255 ? 255 : v;
}
} // namespace
//005f5f58..005f601f. Compare extended four-component squared distances
//against the actual second caller word; only a strict improvement spillsF32.
extern "C" u32 recovered_005f5f58(u32 self, u32 args) {
    const u32 input = prepare(self, args, false);
    const u32 rowPitch = word(self + 0x60), row = word(args), slicePitch = word(self + 0x64),
              slice = word(args + 4);
    u32 destination = rowPitch * row + slicePitch * slice + word(self + 0x20);
    const bool active = word(self + 0x68) != 0;
    put(args, 0);
    u32 result = input;
    if (active) {
        u32 pixel = input + 8;
        do {
            u32 palette = word(self + 0x38), best = 0;
            put(args + 8, word(args + 8) & 0u);
            put(args + 4, 0x7f7fffffu);
            do {
                uint16_t status;
                __asm__ volatile(
                    "flds -8(%1)\n\tfsubs (%2)\n\tflds -4(%1)\n\tfsubs 4(%2)\n\tflds (%1)\n\tfsubs 8(%2)\n\tflds 4(%1)\n\tfsubs 12(%2)\n\tfld %%st(0)\n\tfmul %%st(1),%%st\n\tfld %%st(2)\n\tfmul %%st(3),%%st\n\tfaddp %%st,%%st(1)\n\tfld %%st(3)\n\tfmul %%st(4),%%st\n\tfaddp %%st,%%st(1)\n\tfld %%st(4)\n\tfmul %%st(5),%%st\n\tfaddp %%st,%%st(1)\n\tfstp %%st(4)\n\tfstp %%st(0)\n\tfstp %%st(0)\n\tfstp %%st(0)\n\tfcoms (%3)\n\tfnstsw %%ax"
                    : "=a"(status)
                    : "r"(pixel), "r"(palette), "r"(args + 4)
                    : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "memory");
                if ((status & 0x500u) == 0x100u) {
                    best = word(args + 8);
                    __asm__ volatile("fstps (%0)" ::"r"(args + 4) : "st", "memory");
                } else
                    __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
                put(args + 8, word(args + 8) + 1);
                palette += 16;
            } while (word(args + 8) < 256);
            byte(destination, best);
            ++destination;
            put(args, word(args) + 1);
            result = word(args);
            pixel += 16;
        } while (result < word(self + 0x68));
    }
    return result;
}
//005f601f..005f6208. L8 keeps its error offset private; the actual first
//word stays a late destination step, and the second becomes the pixel count.
extern "C" u32 recovered_005f601f(u32 self, u32 args) {
    prepare(self, args, true);
    const u32 row = word(args);
    u32 gray;
    zero(gray);
    const u32 slice = word(args + 4), rowPitch = word(self + 0x60), slicePitch = word(self + 0x64),
              width = word(self + 0x68);
    put(args, row);
    put(args, word(args) & 1u);
    u32 destination =
        rowPitch * row + slicePitch * slice + (width - 1u) * word(args) + word(self + 0x20);
    const u32 dither = word(self + 0x34) + ((slice & 3u) + (row & 3u) * 8u) * 4;
    const bool odd = word(args) != 0;
    const u32 index = odd ? word(self + 0x68) - 1u : 0;
    put(args, odd ? 0xffffffffu : 1);
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 4) : "memory");
    const u32 forced = word(args + 4) | 0xc00u;
    __asm__ volatile("fldcw %0" ::"m"(forced) : "memory");
    put(self + 0x7c, word(args + 4));
    u32 n = 0;
    if (word(self + 0x68)) {
        u32 p = word(args + 8);
        do {
            ++n;
            luminance(p);
            p += 16;
        } while (n < word(self + 0x68));
    }
    if (word(self + 0x5c))
        FUN_005f25f2(reinterpret_cast<void*>(self), reinterpret_cast<void*>(word(args + 8)));
    const bool active = word(self + 0x68) != 0;
    put(args + 4, 0);
    if (active) {
        const u32 step = word(args), pixelStep = step << 4;
        u32 current = index << 4, after = (step + index) << 4, previous = (index - word(args)) << 4;
        do {
            u32 value, rounded, result;
            const u32 input = word(args + 8);
            scaled(gray, input + current, value);
            __asm__ volatile("flds %1\n\tfadds (%2)\n\tfstps %0"
                             : "=m"(rounded)
                             : "m"(value), "r"(dither + (word(args + 4) & 3) * 4)
                             : "st", "memory");
            integer(reinterpret_cast<uintptr_t>(&rounded), result);
            if (word(self + 0x5c)) {
                const u32 first = word(self + 0x5c) + previous + 16;
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmuls _dat_006be1d0" ::"m"(result),
                                 "m"(value)
                                 : "st", "memory");
                neighbors(self, current, after, 16, first);
                carry(gray);
            }
            byte(destination, clamp(result));
            previous += pixelStep;
            destination += word(args);
            current += pixelStep;
            after += pixelStep;
            put(args + 4, word(args + 4) + 1);
        } while (word(args + 4) < word(self + 0x68));
    }
    const u32 result = word(self + 0x7c);
    put(args + 8, result);
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8) : "memory");
    return result;
}
//005f6208..005f6496. A8L8 holds its direction across preprocessing;
//the actual second caller word is reused for both biased channel values.
extern "C" u32 recovered_005f6208(u32 self, u32 args) {
    prepare(self, args, true);
    const u32 row = word(args);
    u32 gray, alpha;
    zero(gray);
    const u32 width = word(self + 0x68), rowPitch = word(self + 0x60);
    zero(alpha);
    const u32 slicePitch = word(self + 0x64);
    put(args, row);
    put(args, word(args) & 1u);
    u32 destination = rowPitch * row + (width - 1u) * word(args) * 2;
    const u32 slice = word(args + 4);
    destination += slicePitch * slice;
    destination += word(self + 0x20);
    const u32 dither = word(self + 0x34) + ((slice & 3u) + (row & 3u) * 8u) * 4;
    const bool odd = word(args) != 0;
    const u32 index = odd ? width - 1u : 0, step = odd ? 0xffffffffu : 1;
    put(args + 4, step);
    __asm__ volatile("fnstcw (%0)" ::"r"(args) : "memory");
    const u32 forced = word(args) | 0xc00u;
    __asm__ volatile("fldcw %0" ::"m"(forced) : "memory");
    put(self + 0x7c, word(args));
    u32 n = 0;
    if (word(self + 0x68)) {
        u32 p = word(args + 8);
        do {
            ++n;
            luminance(p);
            p += 16;
        } while (n < word(self + 0x68));
    }
    if (word(self + 0x5c))
        FUN_005f25f2(reinterpret_cast<void*>(self), reinterpret_cast<void*>(word(args + 8)));
    const bool active = word(self + 0x68) != 0;
    put(args, 0);
    if (active) {
        const u32 destinationStep = step * 2, pixelStep = step << 4;
        u32 current = index << 4, after = (step + index) << 4,
            previous = (index - word(args + 4)) << 4;
        do {
            u32 bias, gv, av, gi, ai;
            __asm__ volatile("flds (%1)\n\tfsts %0"
                             : "=m"(bias)
                             : "r"(dither + (word(args) & 3) * 4)
                             : "st", "memory");
            const u32 p = word(args + 8) + current;
            scaled(gray, p, gv);
            scaled(alpha, p + 12, av);
            __asm__ volatile(
                "flds %1\n\tfadd %%st(1),%%st\n\tfstps (%0)\n\tfstp %%st(0)" ::"r"(args + 4),
                "m"(gv)
                : "st", "memory");
            integer(args + 4, gi);
            __asm__ volatile("flds %1\n\tfadds %2\n\tfstps (%0)" ::"r"(args + 4), "m"(av), "m"(bias)
                             : "st", "memory");
            integer(args + 4, ai);
            if (word(self + 0x5c)) {
                __asm__ volatile("flds _dat_006be1d0" ::: "st", "memory");
                u32 first = word(self + 0x5c) + previous + 16;
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmul %%st(1),%%st" ::"m"(gi), "m"(gv)
                                 : "st", "memory");
                neighbors(self, current, after, 16, first);
                first = word(self + 0x5c) + previous + 28;
                carry(gray);
                __asm__ volatile("fildl %0\n\tfsubrs %1\n\tfmulp %%st,%%st(1)" ::"m"(ai), "m"(av)
                                 : "st", "memory");
                neighbors(self, current, after, 28, first);
                carry(alpha);
            }
            current += pixelStep;
            previous += pixelStep;
            after += pixelStep;
            half(destination, (clamp(ai) << 8) | clamp(gi));
            destination += destinationStep;
            put(args, word(args) + 1);
        } while (word(args) < word(self + 0x68));
    }
    const u32 result = word(self + 0x7c);
    put(args + 8, result);
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8) : "memory");
    return result;
}
extern "C" __attribute__((naked, thiscall)) u32 FUN_005f5f58(void*, u32, u32, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f5f58\n\taddl $8,%esp\n\tretl $12");
}
extern "C" __attribute__((naked, thiscall)) u32 FUN_005f601f(void*, u32, u32, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f601f\n\taddl $8,%esp\n\tretl $12");
}
extern "C" __attribute__((naked, thiscall)) u32 FUN_005f6208(void*, u32, u32, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f6208\n\taddl $8,%esp\n\tretl $12");
}
