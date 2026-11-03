#include "graphics/surface/surface_alpha_palette_readers.h"
#include "graphics/surface/surface_nibble_readers.h"
#include "graphics/surface/surface_word_packed_readers.h"
#include "core/item_stat_cost.h"
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
    // literal ANDff limits its ordinary value to0..255.
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
namespace {
void zero(u32 output) {
    __asm__ volatile("fldz\n\tfstps (%0)" ::"r"(output) : "st", "memory");
}
void byte_alpha(u32 arguments, u32 output) {
    __asm__ volatile("fildl (%0)\n\tfmuls %2\n\tfstps (%1)" ::"r"(arguments), "r"(output),
                     "m"(dat_006be1d0)
                     : "st", "memory");
}
void copy_three(u32& source, u32& target) {
    __asm__ volatile("movsl\n\tmovsl\n\tmovsl" : "+S"(source), "+D"(target)::"memory");
}
void copy_one(u32& source, u32& target) {
    __asm__ volatile("movsl" : "+S"(source), "+D"(target)::"memory");
}
} // namespace
extern "C" u32 recovered_005f98f2(u32 self, u32 arguments) {
    u32 input = start(self, arguments);
    const u32 end = input + word(self + 0x68);
    u32 output = word(arguments + 8);
    while (input < end) {
        zero(output);
        output += 16;
        zero(output - 12);
        zero(output - 8);
        put(arguments + 8, byte(input));
        ++input;
        byte_alpha(arguments + 8, output - 4);
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005f9970(u32 self, u32 arguments) {
    u32 input = start(self, arguments);
    const u32 width = word(self + 0x68);
    u32 output = word(arguments + 8);
    const u32 end = input + (width << 1);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006df420) : "st", "memory");
        do {
            put(arguments + 8, (byte(input) >> 5) & 7);
            scaled(arguments + 8, output);
            put(arguments + 8, (byte(input) >> 2) & 7);
            output += 16;
            scaled(arguments + 8, output - 12);
            put(arguments + 8, byte(input) & 3);
            input += 2;
            __asm__ volatile("fildl (%0)\n\tfmuls %2\n\tfstps (%1)" ::"r"(arguments + 8),
                             "r"(output - 8), "m"(dat_006c2bb4)
                             : "st", "memory");
            put(arguments + 8, byte(input - 1));
            byte_alpha(arguments + 8, output - 4);
        } while (input < end);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005f9a2a(u32 self, u32 arguments) {
    u32 input = start(self, arguments);
    const u32 width = word(self + 0x68);
    u32 output = word(arguments + 8);
    const u32 end = input + (width << 1);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006c0c2c) : "st", "memory");
        do {
            put(arguments + 8, byte(input + 1) & 15);
            scaled(arguments + 8, output);
            put(arguments + 8, (byte(input) >> 4) & 15);
            output += 16;
            scaled(arguments + 8, output - 12);
            put(arguments + 8, byte(input) & 15);
            input += 2;
            scaled(arguments + 8, output - 8);
            one(output - 4);
        } while (input < end);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005f9ad1(u32 self, u32 arguments) {
    u32 input = start(self, arguments);
    const u32 end = input + (word(self + 0x68) << 1);
    u32 output = word(arguments + 8);
    put(arguments, end);
    if (input < end) {
        bool repeat;
        do {
            const u32 index = byte(input);
            u32 target = output;
            output += 16;
            u32 palette = index * 16 + word(self + 0x38);
            ++input;
            copy_three(palette, target);
            copy_one(palette, target);
            put(arguments + 8, byte(input));
            ++input;
            repeat = input < word(arguments);
            byte_alpha(arguments + 8, output - 4);
        } while (repeat);
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005f9b61(u32 self, u32 arguments) {
    u32 input = start(self, arguments);
    const u32 end = input + word(self + 0x68);
    u32 output = word(arguments + 8);
    while (input < end) {
        u32 palette = byte(input) * 16 + word(self + 0x38), target = output;
        copy_three(palette, target);
        ++input;
        output += 16;
        const bool repeat = input < end;
        copy_one(palette, target);
        if (!repeat)
            break;
    }
    return finish(self, output, input);
}
#define ENTRY(n)                                                                                   \
    extern "C" __attribute__((naked, thiscall)) u32 FUN_##n(void*, u32, u32, void*) {              \
        __asm__ volatile("leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_" #n   \
                         "\n\taddl $8,%esp\n\tretl $12");                                          \
    }
ENTRY(005f98f2)
ENTRY(005f9970)
ENTRY(005f9a2a)
ENTRY(005f9ad1)
ENTRY(005f9b61)
#undef ENTRY
