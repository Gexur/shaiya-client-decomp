#include "graphics/surface/surface_word_packed_readers.h"
#include "graphics/surface/surface_tenbit_reader.h"
#include "graphics/surface/surface_byte_word_readers.h"
#include "runtime/unsigned_shift_right.h"
#include "graphics/surface/surface_basic_readers.h"
#include "graphics/surface/surface_format_palette.h"
#include "graphics/surface/surface_color_match.h"
#include "graphics/surface/surface_read_transform.h"
#include "graphics/render_half_decode_sse2.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 half(u32 p) {
    u32 v;
    __asm__ volatile("movzwl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 byte(u32 p) {
    u32 v;
    __asm__ volatile("movzbl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void scaled(u32 argument, u32 output) {
    __asm__ volatile("fildl (%0)\n\tfmul %%st(1),%%st(0)\n\tfstps (%1)" ::"r"(argument), "r"(output)
                     : "st", "memory");
}
void scaled_green(u32 argument, u32 output) {
    __asm__ volatile("fildl (%0)\n\tfmuls %2\n\tfstps (%1)" ::"r"(argument), "r"(output),
                     "m"(dat_006df404)
                     : "st", "memory");
}
void scaled_unsigned(u32 argument, u32 value, u32 output) {
    // Retain the original signed-adjust branch even though this caller's
    // literal field masks constrain all values to nonnegative integers.
    __asm__ volatile(
        "fildl (%0)\n\ttestl %1,%1\n\tjns 1f\n\tfadds %3\n1:\tfmul %%st(1),%%st(0)\n\tfstps (%2)" ::
            "r"(argument),
        "r"(value), "r"(output), "m"(dat_006bb60c)
        : "st", "cc", "memory");
}
void third_unsigned(u32 argument, u32 value, u32 output) {
    __asm__ volatile(
        "fildl (%0)\n\ttestl %1,%1\n\tjns 1f\n\tfadds %3\n1:\tfmuls %4\n\tfstps (%2)" ::"r"(
            argument),
        "r"(value), "r"(output), "m"(dat_006bb60c), "m"(dat_006c2bb4)
        : "st", "cc", "memory");
}
void one(u32 output) {
    __asm__ volatile("fld1\n\tfstps (%0)" ::"r"(output) : "st", "memory");
}
u32 start(u32 self, u32 arguments) {
    u32 input = word(self + 0x60) * word(arguments);
    const u32 slice = word(self + 0x64) * word(arguments + 4);
    input += slice;
    input += word(self + 0x20);
    return input;
}
__attribute__((always_inline)) inline u32 finish(u32 self, u32 output, u32 result) {
    if (word(self + 0x18)) {
        result = word(self + 0x68) << 4;
        u32 pixels = output - result;
        __asm__ volatile("pushl %3\n\tcalll _FUN_005f225c"
                         : "+a"(result), "+c"(self), "+d"(pixels)
                         : "r"(pixels)
                         : "memory", "cc");
    }
    if (word(self + 0x10)) {
        result = word(self + 0x68) << 4;
        output -= result;
        u32 edx;
        __asm__ volatile("pushl %3\n\tcalll _FUN_005f24c9"
                         : "+a"(result), "+c"(self), "=d"(edx)
                         : "r"(output)
                         : "memory", "cc");
    }
    return result;
}
} // namespace
// Complete5f966c: reversed10-bit order, with separate fresh DWORD reads.
extern "C" u32 recovered_005f966c(u32 self, u32 arguments) {
    u32 input = start(self, arguments);
    const u32 width = word(self + 0x68);
    u32 output = word(arguments + 8);
    const u32 end = input + (width << 2);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006df424) : "st", "memory");
        do {
            const u32 red = (word(input) >> 20) & 1023;
            put(arguments + 8, red);
            scaled_unsigned(arguments + 8, red, output);
            const u32 green = (word(input) >> 10) & 1023;
            put(arguments + 8, green);
            scaled_unsigned(arguments + 8, green, output + 4);
            const u32 blue = word(input) & 1023;
            put(arguments + 8, blue);
            scaled_unsigned(arguments + 8, blue, output + 8);
            const u32 alpha = word(input) >> 30;
            put(arguments + 8, alpha);
            input += 4;
            output += 16;
            third_unsigned(arguments + 8, alpha, output - 4);
        } while (input < end);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
// Complete5f974e: the real unsigned-shift helper consumes low/high/dirtyECX.
extern "C" u32 recovered_005f974e(u32 self, u32 arguments) {
    u32 input = start(self, arguments);
    u32 result = input + (word(self + 0x68) << 3);
    u32 output = word(arguments + 8);
    put(arguments, result);
    if (input < result) {
        __asm__ volatile("flds %0" ::"m"(dat_006df42c) : "st", "memory");
        bool repeat;
        do {
            const u32 red = word(input) & 65535;
            put(arguments + 8, red);
            scaled_unsigned(arguments + 8, red, output);
            const u32 green_low = word(input);
            const u32 green_high = word(input + 4);
            (void)green_high;
            const u32 green = green_low >> 16;
            put(arguments + 8, green);
            scaled_unsigned(arguments + 8, green, output + 4);
            u32 low = word(input), high = word(input + 4), count = (green & 0xffffff00u) | 32u;
            __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
            __asm__ volatile("calll _FUN_006aa840"
                             : "+a"(low), "+d"(high), "+c"(count)::"memory", "cc");
            __asm__ volatile("flds %0" ::"m"(dat_006df42c) : "st", "memory");
            const u32 blue = low & 65535;
            put(arguments + 8, blue);
            __asm__ volatile(
                "fildl (%0)\n\ttestl %1,%1\n\tjns 1f\n\tfadds %2\n1:\tfmul %%st(1),%%st(0)" ::"r"(
                    arguments + 8),
                "r"(blue), "m"(dat_006bb60c)
                : "st", "cc", "memory");
            input += 8;
            output += 16;
            repeat = input < word(arguments);
            __asm__ volatile("fstps (%0)" ::"r"(output - 8) : "st", "memory");
            result = half(input - 2);
            put(arguments + 8, result);
            scaled(arguments + 8, output - 4);
        } while (repeat);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, result);
}
// Complete5f9848: actual3/3/2 byte fields, not normalized eight-bit channels.
extern "C" u32 recovered_005f9848(u32 self, u32 arguments) {
    u32 input = word(self + 0x60) * word(arguments);
    const u32 slice = word(self + 0x64) * word(arguments + 4);
    u32 output = word(arguments + 8);
    input += slice;
    input += word(self + 0x20);
    const u32 end = input + word(self + 0x68);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006df420) : "st", "memory");
        do {
            const u32 red = byte(input) >> 5;
            put(arguments + 8, red);
            scaled(arguments + 8, output);
            const u32 green = (byte(input) >> 2) & 7;
            put(arguments + 8, green);
            output += 16;
            scaled(arguments + 8, output - 12);
            const u32 blue = byte(input) & 3;
            put(arguments + 8, blue);
            ++input;
            __asm__ volatile("fildl (%0)\n\tfmuls %2\n\tfstps (%1)" ::"r"(arguments + 8),
                             "r"(output - 8), "m"(dat_006c2bb4)
                             : "st", "memory");
            one(output - 4);
        } while (input < end);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
#define ENTRY(n)                                                                                   \
    extern "C" __attribute__((naked, thiscall)) u32 FUN_##n(void*, u32, u32, void*) {              \
        __asm__ volatile("leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_" #n   \
                         "\n\taddl $8,%esp\n\tretl $12");                                          \
    }
ENTRY(005f966c)
ENTRY(005f974e)
ENTRY(005f9848)
#undef ENTRY
extern "C" const uint32_t dat_006df420 = 0x3e124925u;
