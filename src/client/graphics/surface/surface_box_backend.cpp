#include "graphics/surface/surface_box_backend.h"
#include "graphics/surface/surface_format_configure.h"
#include "runtime/allocations.h"
#include "core/untouched_lifetime.h"
extern "C" const float dat_006bfe14 = 0.25f;
extern "C" {
#define LEAF(n) int32_t __attribute__((thiscall)) FUN_##n(void*)
LEAF(005ecf49);
LEAF(005ed1dc);
LEAF(005ed1fe);
LEAF(005ed332);
LEAF(005ed437);
LEAF(005ed560);
LEAF(005ed697);
LEAF(005ed7b5);
LEAF(005ed841);
LEAF(005ed96f);
LEAF(005eda78);
LEAF(005edba6);
#undef LEAF
}
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
unsigned char byte(u32 p) {
    unsigned char v;
    __asm__ volatile("movb (%1),%0" : "=q"(v) : "r"(p) : "memory");
    return v;
}
void and_even(u32 p) {
    __asm__ volatile("andl $-2,(%0)" ::"r"(p) : "memory", "cc");
}
void subtract(u32 p, u32 amount) {
    __asm__ volatile("subl %1,(%0)" ::"r"(p), "r"(amount) : "memory", "cc");
}
struct __attribute__((packed, may_alias)) FloatWord {
    float value;
};
volatile float& f32(u32 p) {
    return reinterpret_cast<volatile FloatWord*>(p)->value;
}
void row_call(u32 receiver, u32 row, u32 buffer, u32 offset) {
    u32 table = word(receiver);
    const u32 code = word(table + offset), words[3] = {row, 0, buffer};
    __asm__ volatile("pushl 8(%3)\n\tpushl 4(%3)\n\tpushl (%3)\n\tcalll *%2"
                     : "+a"(table), "+c"(receiver)
                     : "r"(code), "r"(words)
                     : "edx", "memory", "cc");
}
void four_words(u32 output, const volatile float* source) {
    u32 input = reinterpret_cast<uintptr_t>(source);
    __asm__ volatile("movsl\n\tmovsl\n\tmovsl\n\tmovsl" : "+D"(output), "+S"(input)::"memory");
}
// Original5ee510..5ee59a arithmetic dependencies and each evidenced F32
// private spill. Channels have different intermediate rounding lifetimes.
void average(u32 output, u32 a, u32 b, u32 c, u32 d, const volatile long double& q) {
    const volatile long double x0 =
        static_cast<long double>(f32(b)) + static_cast<long double>(f32(a));
    const volatile long double y0 =
        static_cast<long double>(f32(b + 4)) + static_cast<long double>(f32(a + 4));
    const volatile long double z0 =
        static_cast<long double>(f32(b + 8)) + static_cast<long double>(f32(a + 8));
    const volatile float zs = static_cast<float>(z0);
    const volatile long double w0 =
        static_cast<long double>(f32(b + 12)) + static_cast<long double>(f32(a + 12));
    const volatile float ws = static_cast<float>(w0);
    const volatile long double x1 = x0 + static_cast<long double>(f32(c));
    const volatile float xs1 = static_cast<float>(x1);
    const volatile long double y1 = y0 + static_cast<long double>(f32(c + 4));
    const volatile long double z1 =
        static_cast<long double>(zs) + static_cast<long double>(f32(c + 8));
    const volatile long double w1 =
        static_cast<long double>(ws) + static_cast<long double>(f32(c + 12));
    const volatile float ws1 = static_cast<float>(w1);
    const volatile long double x2 =
        static_cast<long double>(xs1) + static_cast<long double>(f32(d));
    const volatile float xs2 = static_cast<float>(x2);
    const volatile long double y2 = y1 + static_cast<long double>(f32(d + 4));
    const volatile float ys2 = static_cast<float>(y2);
    const volatile long double z2 = z1 + static_cast<long double>(f32(d + 8));
    const volatile long double w2 =
        static_cast<long double>(ws1) + static_cast<long double>(f32(d + 12));
    volatile float result[4];
    result[0] = static_cast<float>(static_cast<long double>(xs2) * q);
    result[1] = static_cast<float>(static_cast<long double>(ys2) * q);
    result[2] = static_cast<float>(z2 * q);
    result[3] = static_cast<float>(w2 * q);
    four_words(output, result);
}
int32_t packed(void* self, u32 format) {
    switch (format) {
    case 21:
    case 32:
        return FUN_005ecf49(self);
    case 22:
    case 33:
        return FUN_005ed1dc(self);
    case 23:
        return FUN_005ed1fe(self);
    case 24:
        return FUN_005ed332(self);
    case 25:
        return FUN_005ed437(self);
    case 26:
        return FUN_005ed560(self);
    case 27:
        return FUN_005ed697(self);
    case 28:
    case 50:
        return FUN_005ed7b5(self);
    case 29:
        return FUN_005ed841(self);
    case 30:
        return FUN_005ed96f(self);
    case 51:
        return FUN_005eda78(self);
    case 52:
        return FUN_005edba6(self);
    default:
        return static_cast<int32_t>(0x80004005u);
    }
}
constexpr int32_t failure = static_cast<int32_t>(0x80004005u),
                  out_of_memory = static_cast<int32_t>(0x8007000eu);
} // namespace
// Complete5ee24a..5ee5ee instruction body. The adjacent9DWORD original switch
// table5ee5ee..5ee612 is represented by evidenced cases in packed(), not code.
extern "C" int32_t __attribute__((thiscall)) FUN_005ee24a(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    if (byte(self + 8) != 5)
        return failure;
    u32 source = word(self);
    const u32 source_width = word(source + 0x68);
    u32 destination = word(self + 4);
    const u32 destination_width = word(destination + 0x68);
    if (destination_width != (source_width >> 1) &&
        (destination_width != 1 || source_width != destination_width))
        return failure;
    const u32 source_height = word(source + 0x6c), destination_height = word(destination + 0x6c);
    if (destination_height != (source_height >> 1) &&
        (destination_height != 1 || word(source + 0x6c) != destination_height))
        return failure;
    if (word(destination + 0x70) != 1 || word(source + 0x70) != 1)
        return failure;
    if (source_width > 1 && (source_width & 1)) {
        and_even(source + 0x68);
        source = word(self);
        const u32 bytes_per_pixel = word(source + 0x78);
        subtract(source + 0x74, bytes_per_pixel);
    }
    source = word(self);
    if (word(source + 0x6c) > 1)
        and_even(source + 0x6c);
    if (!(byte(self + 10) & 8)) {
        source = word(self);
        destination = word(self + 4);
        const u32 format = word(source + 4);
        if (format == word(destination + 4) && word(source + 0x68) >= 2 &&
            word(source + 0x6c) >= 2 && !word(destination + 0x10) && !word(source + 0x10)) {
            if (packed(object, format) >= 0)
                return 0;
        }
    }
    destination = word(self + 4);
    const u32 output_width = word(destination + 0x68);
    void* output = fun_005cc96d(output_width << 4);
    if (output)
        FUN_00405c90(output, 16, output_width, reinterpret_cast<uintptr_t>(&FUN_004441b0));
    if (!output)
        return out_of_memory;
    source = word(self);
    const u32 input_height = word(source + 0x6c), input_width = word(source + 0x68);
    void* input;
    u32 second_row;
    if (input_height == 1) {
        input = fun_005cc96d(input_width << 4);
        if (input)
            FUN_00405c90(input, 16, input_width, reinterpret_cast<uintptr_t>(&FUN_004441b0));
        second_row = reinterpret_cast<uintptr_t>(input);
    } else {
        const u32 count = input_width << 1;
        input = fun_005cc96d(count << 4);
        if (input)
            FUN_00405c90(input, 16, count, reinterpret_cast<uintptr_t>(&FUN_004441b0));
        source = word(self);
        second_row = (word(source + 0x68) << 4) + reinterpret_cast<uintptr_t>(input);
    }
    if (!input) {
        fun_005cc620(output);
        return out_of_memory;
    }
    const u32 first_row = reinterpret_cast<uintptr_t>(input);
    source = word(self);
    u32 first_right = first_row, second_right = second_row;
    if (word(source + 0x68) != 1) {
        first_right += 16;
        second_right += 16;
    }
    u32 row = 0;
    destination = word(self + 4);
    if (word(destination + 0x6c))
        do {
            source = word(self);
            row_call(source, row * 2, first_row, 4);
            if (second_row != first_row) {
                source = word(self);
                row_call(source, row * 2 + 1, second_row, 4);
            }
            destination = word(self + 4);
            u32 x = 0;
            if (word(destination + 0x68)) {
                const volatile long double quarter =
                    static_cast<long double>(f32(reinterpret_cast<uintptr_t>(&dat_006bfe14)));
                u32 to = reinterpret_cast<uintptr_t>(output);
                do {
                    const u32 offset = (x + x) << 4;
                    average(to, first_row + offset, first_right + offset, second_row + offset,
                            second_right + offset, quarter);
                    to += 16;
                    ++x;
                    destination = word(self + 4);
                } while (x < word(destination + 0x68));
            }
            destination = word(self + 4);
            row_call(destination, row, reinterpret_cast<uintptr_t>(output), 8);
            ++row;
            destination = word(self + 4);
        } while (row < word(destination + 0x6c));
    fun_005cc620(input);
    fun_005cc620(output);
    return 0;
}
