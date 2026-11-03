#include "graphics/surface/surface_signed_vector_readers.h"
#include "graphics/surface/surface_broadcast_signed_readers.h"
#include "graphics/render_project_unproject.h"
#include "graphics/render_packed_trig_quaternions.h"
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
void put_byte(u32 p, u32 v) {
    __asm__ volatile("movb %b1,(%0)" ::"r"(p), "q"(v) : "memory");
}
void begin_scaled(u32 argument) {
    __asm__ volatile("fildl (%0)\n\tfmul %%st(1),%%st(0)" ::"r"(argument) : "st", "memory");
}
void pending(u32 output) {
    __asm__ volatile("fstps (%0)" ::"r"(output) : "st", "memory");
}
u32 signed_byte(u32 value, u32 adjust) {
    value = (value + adjust) & 255u;
    return value & 128u ? value | 0xffffff00u : value;
}
u32 adjusted_byte(u32 value) {
    value &= 255u;
    return signed_byte(value, value == 128u);
}
u32 signed_word(u32 value, u32 adjust) {
    value = (value + adjust) & 65535u;
    return value & 32768u ? value | 0xffff0000u : value;
}
u32 adjusted_word(u32 value) {
    value &= 65535u;
    return signed_word(value, value == 32768u);
}
u32 ten_in_word(u32 value) {
    value &= 1023u;
    return value & 512u ? value | 0xfc00u : value;
}
uint16_t normal_remainder(u32 argument, u32 output) {
    uint16_t status;
    __asm__ volatile(
        "fsts (%2)\n\tfildl (%1)\n\tfmul %%st(2),%%st(0)\n\tfsts 4(%2)\n\tfld %%st(1)\n\tfmul %%st(2),%%st(0)\n\tfsubrs %3\n\tfld %%st(1)\n\tfmul %%st(2),%%st(0)\n\tfsubrp %%st(0),%%st(1)\n\tfstp %%st(2)\n\tfstp %%st(0)\n\tfcoms %4\n\tfnstsw %%ax\n\ttestb $0x41,%%ah\n\tjp 1f\n\tfstp %%st(0)\n\tfldz\n\tjmp 2f\n1:\tfsqrt\n2:\tfstps 8(%2)"
        : "=a"(status)
        : "r"(argument), "r"(output), "m"(dat_006bc4dc[0]), "m"(dat_006bb5fc[0])
        : "st", "cc", "memory");
    return status;
}
} // namespace
extern "C" u32 recovered_005f9eed(u32 self, u32 a) {
    u32 output = word(a + 8), input = start(self, a);
    const u32 end = input + (word(self + 0x68) << 2);
    put(a, end);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006df430) : "st", "memory");
        bool repeat;
        do {
            const u32 red = byte(input), green = word(input) >> 8;
            put(a + 8, adjusted_byte(red));
            begin_scaled(a + 8);
            put(a + 8, adjusted_byte(green));
            input += 4;
            pending(output);
            output += 16;
            repeat = input < word(a);
            scaled(a + 8, output - 12);
            one(output - 8);
            put(a + 8, byte(input - 2));
            __asm__ volatile("fildl (%0)\n\tfmuls %2\n\tfstps (%1)" ::"r"(a + 8), "r"(output - 4),
                             "m"(dat_006be1d0)
                             : "st", "memory");
        } while (repeat);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005f9fac(u32 self, u32 a) {
    u32 output = word(a + 8), input = start(self, a);
    const u32 end = input + (word(self + 0x68) << 2);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006df430) : "st", "memory");
        do {
            const u32 pixel = word(input);
            put_byte(a + 11, pixel >> 16);
            put_byte(a + 3, pixel >> 24);
            put(a + 4, adjusted_byte(pixel));
            __asm__ volatile("fildl (%0)" ::"r"(a + 4) : "st", "memory");
            const u32 blue_adjust = byte(a + 11) == 128u;
            __asm__ volatile("fmul %%st(1),%%st(0)" ::: "st", "memory");
            put(a + 4, adjusted_byte(pixel >> 8));
            const u32 blue = byte(a + 11);
            pending(output);
            __asm__ volatile("fildl (%0)" ::"r"(a + 4) : "st", "memory");
            const u32 alpha_adjust = byte(a + 3) == 128u;
            __asm__ volatile("fmul %%st(1),%%st(0)" ::: "st", "memory");
            put(a + 8, signed_byte(blue, blue_adjust));
            const u32 alpha = byte(a + 3);
            pending(output + 4);
            begin_scaled(a + 8);
            input += 4;
            put(a + 8, signed_byte(alpha, alpha_adjust));
            output += 16;
            pending(output - 8);
            scaled(a + 8, output - 4);
        } while (input < end);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005fa09a(u32 self, u32 a) {
    u32 input = start(self, a);
    const u32 end = input + (word(self + 0x68) << 2);
    u32 output = word(a + 8);
    put(a, end);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006bbc78) : "st", "memory");
        bool repeat;
        do {
            const u32 green = half(input + 2), red = half(input);
            put(a + 8, adjusted_word(red));
            input += 4;
            scaled(a + 8, output);
            put(a + 8, adjusted_word(green));
            output += 16;
            repeat = input < word(a);
            scaled(a + 8, output - 12);
            one(output - 8);
            one(output - 4);
        } while (repeat);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005fa14f(u32 self, u32 a) {
    u32 input = start(self, a);
    const u32 end = input + (word(self + 0x68) << 2);
    u32 output = word(a + 8);
    put(a + 4, end);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006df62c) : "st", "memory");
        bool repeat;
        do {
            const u32 pixel = word(input), red = half(input), green = ten_in_word(pixel >> 10),
                      blue = ten_in_word(pixel >> 20);
            put(a + 8, blue);
            const u32 red_word = ten_in_word(red);
            put(a, signed_word(red_word, red_word == 0xfe00u));
            scaled(a, output);
            put(a, signed_word(green, green == 0xfe00u));
            const u32 adjust = half(a + 8) == 0xfe00u;
            __asm__ volatile("fildl (%0)" ::"r"(a) : "st", "memory");
            __asm__ volatile("fmul %%st(1),%%st(0)" ::: "st", "memory");
            pending(output + 4);
            put(a + 8, signed_word(word(a + 8), adjust));
            scaled(a + 8, output + 8);
            const u32 alpha = word(input) >> 30;
            put(a + 8, alpha);
            __asm__ volatile(
                "fildl (%0)\n\ttestl %1,%1\n\tjns 1f\n\tfadds %2\n1:\tfmuls %3" ::"r"(a + 8),
                "r"(alpha), "m"(dat_006bb60c[0]), "m"(dat_006c2bb4)
                : "st", "cc", "memory");
            input += 4;
            output += 16;
            repeat = input < word(a + 4);
            pending(output - 4);
        } while (repeat);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005fa25b(u32 self, u32 a) {
    u32 input = start(self, a);
    const u32 end = input + (word(self + 0x68) << 3);
    u32 output = word(a + 8);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006bbc78) : "st", "memory");
        do {
            const u32 high = word(input + 4), low = word(input);
            put(a + 8, (low >> 16) | (high << 16));
            const u32 red = half(input), blue = high & 65535u;
            put(a, high >> 16);
            put(a + 4, adjusted_word(red));
            const u32 green_adjust = half(a + 8) == 32768u;
            __asm__ volatile("fildl (%0)" ::"r"(a + 4) : "st", "memory");
            __asm__ volatile("fmul %%st(1),%%st(0)" ::: "st", "memory");
            pending(output);
            put(a + 8, signed_word(word(a + 8), green_adjust));
            const u32 blue_adjust = blue == 32768u;
            __asm__ volatile("fildl (%0)" ::"r"(a + 8) : "st", "memory");
            __asm__ volatile("fmul %%st(1),%%st(0)" ::: "st", "memory");
            pending(output + 4);
            put(a + 8, signed_word(blue, blue_adjust));
            const u32 alpha_adjust = half(a) == 32768u;
            __asm__ volatile("fildl (%0)" ::"r"(a + 8) : "st", "memory");
            __asm__ volatile("fmul %%st(1),%%st(0)" ::: "st", "memory");
            input += 8;
            output += 16;
            pending(output - 8);
            put(a + 8, signed_word(word(a), alpha_adjust));
            scaled(a + 8, output - 4);
        } while (input < end);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, input);
}
extern "C" u32 recovered_005fa365(u32 self, u32 a) {
    u32 output = word(a + 8), input = start(self, a);
    u32 result = input + (word(self + 0x68) << 1);
    put(a, result);
    if (input < result) {
        __asm__ volatile("flds %0" ::"m"(dat_006df430) : "st", "memory");
        bool repeat;
        do {
            const u32 red = byte(input), green = byte(input + 1);
            put(a + 8, adjusted_byte(red));
            begin_scaled(a + 8);
            const u32 signed_green = adjusted_byte(green);
            put(a + 8, signed_green);
            const uint16_t status = normal_remainder(a + 8, output);
            result = (signed_green & 0xffff0000u) | status;
            ++input;
            one(output + 12);
            ++input;
            output += 16;
            repeat = input < word(a);
        } while (repeat);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    return finish(self, output, result);
}
#define ENTRY(n)                                                                                   \
    extern "C" __attribute__((naked, thiscall)) u32 FUN_##n(void*, u32, u32, void*) {              \
        __asm__ volatile("leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_" #n   \
                         "\n\taddl $8,%esp\n\tretl $12");                                          \
    }
ENTRY(005f9eed)
ENTRY(005f9fac)
ENTRY(005fa09a)
ENTRY(005fa14f)
ENTRY(005fa25b)
ENTRY(005fa365)
#undef ENTRY
extern "C" const uint32_t dat_006bbc78 = 0x38000100u;
extern "C" const uint32_t dat_006df62c = 0x3b004020u;
