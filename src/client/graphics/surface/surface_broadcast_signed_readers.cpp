#include "graphics/surface/surface_broadcast_signed_readers.h"
#include "graphics/surface/surface_tenbit_reader.h"
#include "graphics/surface/surface_nibble_readers.h"
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
void broadcast_memory(u32 argument, u32 output) {
    __asm__ volatile(
        "fildl (%0)\n\tfmuls %2\n\tfsts 8(%1)\n\tfsts 4(%1)\n\tfstps (%1)" ::"r"(argument),
        "r"(output), "m"(dat_006be1d0)
        : "st", "memory");
}
void broadcast_resident(u32 argument, u32 output) {
    __asm__ volatile(
        "fildl (%0)\n\tfmul %%st(1),%%st(0)\n\tfsts 8(%1)\n\tfsts 4(%1)\n\tfstps (%1)" ::"r"(
            argument),
        "r"(output)
        : "st", "memory");
}
void begin_resident(u32 argument) {
    __asm__ volatile("fildl (%0)\n\tfmul %%st(1),%%st(0)" ::"r"(argument) : "st", "memory");
}
void store_pending(u32 output) {
    __asm__ volatile("fstps (%0)" ::"r"(output) : "st", "memory");
}
u32 adjusted_signed_byte(u32 value) {
    value = (value + (value == 128u)) & 255u;
    return value & 128u ? value | 0xffffff00u : value;
}
u32 adjusted_signed_five(u32 value) {
    value &= 31u;
    value += value == 16u;
    return value & 16u ? value | 0xffffffe0u : value;
}
} // namespace
extern "C" u32 recovered_005f9bd0(u32 self, u32 arguments) {
    u32 input = start(self, arguments);
    const u32 end = input + word(self + 0x68);
    u32 output = word(arguments + 8);
    while (input < end) {
        put(arguments + 8, byte(input));
        ++input;
        broadcast_memory(arguments + 8, output);
        output += 16;
        one(output - 4);
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005f9c4a(u32 self, u32 arguments) {
    u32 input = start(self, arguments);
    const u32 width = word(self + 0x68);
    u32 output = word(arguments + 8);
    const u32 end = input + (width << 1);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006be1d0) : "st", "memory");
        do {
            put(arguments + 8, byte(input));
            input += 2;
            broadcast_resident(arguments + 8, output);
            put(arguments + 8, byte(input - 1));
            output += 16;
            scaled(arguments + 8, output - 4);
        } while (input < end);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005f9cdb(u32 self, u32 arguments) {
    u32 input = word(self + 0x60) * word(arguments);
    const u32 slice = word(self + 0x64) * word(arguments + 4);
    u32 output = word(arguments + 8);
    input += slice;
    input += word(self + 0x20);
    const u32 end = input + word(self + 0x68);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006c0c2c) : "st", "memory");
        do {
            put(arguments + 8, byte(input) & 15);
            broadcast_resident(arguments + 8, output);
            put(arguments + 8, byte(input) >> 4);
            ++input;
            output += 16;
            scaled(arguments + 8, output - 4);
        } while (input < end);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005f9d6c(u32 self, u32 arguments) {
    u32 output = word(arguments + 8), input = start(self, arguments);
    const u32 end = input + (word(self + 0x68) << 1);
    put(arguments, end);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006df430) : "st", "memory");
        bool repeat;
        do {
            const u32 red = byte(input), green = byte(input + 1);
            put(arguments + 8, adjusted_signed_byte(red));
            begin_resident(arguments + 8);
            put(arguments + 8, adjusted_signed_byte(green));
            ++input;
            store_pending(output);
            ++input;
            __asm__ volatile("fildl (%0)" ::"r"(arguments + 8) : "st", "memory");
            output += 16;
            repeat = input < word(arguments);
            __asm__ volatile("fmul %%st(1),%%st(0)\n\tfstps (%0)" ::"r"(output - 12)
                             : "st", "memory");
            one(output - 8);
            one(output - 4);
        } while (repeat);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005f9e1a(u32 self, u32 arguments) {
    u32 output = word(arguments + 8), input = start(self, arguments);
    const u32 end = input + (word(self + 0x68) << 1);
    put(arguments, end);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006c0c2c) : "st", "memory");
        bool repeat;
        do {
            const u32 red = byte(input), both = half(input);
            put(arguments + 8, adjusted_signed_five(red));
            begin_resident(arguments + 8);
            put(arguments + 8, adjusted_signed_five(both >> 5));
            store_pending(output);
            output += 16;
            scaled(arguments + 8, output - 12);
            one(output - 8);
            put(arguments + 8, half(input) >> 10);
            input += 2;
            repeat = input < word(arguments);
            __asm__ volatile("fildl (%0)\n\tfmuls %2\n\tfstps (%1)" ::"r"(arguments + 8),
                             "r"(output - 4), "m"(dat_006df404)
                             : "st", "memory");
        } while (repeat);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
#define ENTRY(n)                                                                                   \
    extern "C" __attribute__((naked, thiscall)) u32 FUN_##n(void*, u32, u32, void*) {              \
        __asm__ volatile("leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_" #n   \
                         "\n\taddl $8,%esp\n\tretl $12");                                          \
    }
ENTRY(005f9bd0)
ENTRY(005f9c4a)
ENTRY(005f9cdb)
ENTRY(005f9d6c)
ENTRY(005f9e1a)
#undef ENTRY
extern "C" const uint32_t dat_006df430 = 0x3c010204u;
