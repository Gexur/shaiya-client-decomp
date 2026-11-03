#include "graphics/surface/surface_float_copy_readers.h"
#include "graphics/surface/surface_byte_word_readers.h"
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
void gray_word(u32 argument, u32 output) {
    __asm__ volatile(
        "fildl (%0)\n\tfmuls %2\n\tfsts 8(%1)\n\tfsts 4(%1)\n\tfstps (%1)" ::"r"(argument),
        "r"(output), "m"(dat_006df42c)
        : "st", "memory");
}
void gray_resident_unsigned(u32 argument, u32 value, u32 output) {
    __asm__ volatile(
        "fildl (%0)\n\ttestl %1,%1\n\tjns 1f\n\tfadds %3\n1:\tfmul %%st(1),%%st(0)\n\tfsts 8(%2)\n\tfsts 4(%2)\n\tfstps (%2)" ::
            "r"(argument),
        "r"(value), "r"(output), "m"(dat_006bb60c)
        : "st", "cc", "memory");
}
void copy_words_bytes(u32 output, u32 input, u32 bytes) {
    u32 count = bytes >> 2;
    __asm__ volatile("rep movsl" : "+S"(input), "+D"(output), "+c"(count)::"memory");
    count = bytes & 3u;
    __asm__ volatile("rep movsb" : "+S"(input), "+D"(output), "+c"(count)::"memory");
}
u32 finish_actual_output_word(u32 self, u32 arguments, u32 result) {
    if (word(self + 0x18)) {
        const u32 pixels = word(arguments + 8);
        u32 receiver = self, edx;
        __asm__ volatile("pushl %3\n\tcalll _FUN_005f225c"
                         : "+a"(result), "+c"(receiver), "=d"(edx)
                         : "r"(pixels)
                         : "memory", "cc");
    }
    if (word(self + 0x10)) {
        const u32 pixels = word(arguments + 8);
        u32 receiver = self, edx;
        __asm__ volatile("pushl %3\n\tcalll _FUN_005f24c9"
                         : "+a"(result), "+c"(receiver), "=d"(edx)
                         : "r"(pixels)
                         : "memory", "cc");
    }
    return result;
}
} // namespace
extern "C" u32 recovered_005fa439(u32 self, u32 a) {
    u32 input = start(self, a);
    const u32 end = input + (word(self + 0x68) << 1);
    u32 output = word(a + 8);
    while (input < end) {
        put(a + 8, half(input));
        ++input;
        ++input;
        gray_word(a + 8, output);
        output += 16;
        one(output - 4);
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005fa4b5(u32 self, u32 a) {
    u32 input = start(self, a);
    const u32 end = input + (word(self + 0x68) << 2);
    u32 output = word(a + 8);
    while (input < end) {
        const u32 red = word(input);
        one(output + 12);
        put(output, red);
        one(output + 8);
        input += 4;
        output += 16;
        one(output - 12);
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005fa67d(u32 self, u32 a) {
    u32 input = start(self, a);
    const u32 end = input + (word(self + 0x68) << 3);
    u32 output = word(a + 8);
    while (input < end) {
        const u32 red = word(input);
        __asm__ volatile("fld1" ::: "st", "memory");
        put(output, red);
        const u32 green = word(input + 4);
        __asm__ volatile("fstps (%0)\n\tfld1" ::"r"(output + 12) : "st", "memory");
        put(output + 4, green);
        __asm__ volatile("fstps (%0)" ::"r"(output + 8) : "st", "memory");
        input += 8;
        output += 16;
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005fa6f2(u32 self, u32 a) {
    const u32 slice = word(self + 0x64) * word(a + 4), bytes = word(self + 0x68) << 4;
    u32 input = word(self + 0x60) * word(a);
    input += slice;
    input += word(self + 0x20);
    const u32 output = word(a + 8);
    copy_words_bytes(output, input, bytes);
    return finish_actual_output_word(self, a, bytes);
}
extern "C" u32 recovered_005fa74d(u32 self, u32 a) {
    u32 input = start(self, a);
    const u32 end = input + (word(self + 0x68) << 2);
    u32 output = word(a + 8);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006df42c) : "st", "memory");
        do {
            const u32 gray = word(input) & 65535u;
            put(a + 8, gray);
            gray_resident_unsigned(a + 8, gray, output);
            input += 4;
            put(a + 8, half(input - 2));
            output += 16;
            scaled(a + 8, output - 4);
        } while (input < end);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005fa7e7(u32 self, u32 a) {
    u32 input = start(self, a);
    const u32 end = input + word(self + 0x74);
    u32 output = word(a + 8);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006df42c) : "st", "memory");
        do {
            put(a + 8, half(input + 4));
            scaled(a + 8, output);
            put(a + 8, half(input + 2));
            output += 16;
            scaled(a + 8, output - 12);
            put(a + 8, half(input));
            input += 6;
            scaled(a + 8, output - 8);
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
ENTRY(005fa439)
ENTRY(005fa4b5)
ENTRY(005fa67d)
ENTRY(005fa6f2)
ENTRY(005fa74d)
ENTRY(005fa7e7)
#undef ENTRY
