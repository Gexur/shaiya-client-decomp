#include "graphics/surface/surface_linear_backend.h"
#include "graphics/surface/surface_linear_weights.h"
#include "graphics/surface/surface_format_configure.h"
#include "runtime/allocations.h"
#include "core/untouched_lifetime.h"
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
struct __attribute__((packed, may_alias)) FloatWord {
    float value;
};
volatile float& f32(u32 p) {
    return reinterpret_cast<volatile FloatWord*>(p)->value;
}
u32 weights(u32 source, u32 destination, u32 flag) {
    u32 result;
    const auto target = &FUN_005eea1a;
    __asm__ volatile("pushl %4\n\tcalll *%3"
                     : "=a"(result), "+S"(source), "+D"(destination)
                     : "r"(target), "r"(flag)
                     : "ecx", "edx", "memory", "cc");
    return result;
}
void read_row(u32 receiver, u32 row, u32 buffer) {
    u32 table = word(receiver);
    const u32 code = word(table + 4), words[3] = {row, 0, buffer};
    __asm__ volatile("pushl 8(%4)\n\tpushl 4(%4)\n\tpushl (%4)\n\tcalll *%3"
                     : "+a"(row), "+d"(table), "+c"(receiver)
                     : "r"(code), "r"(words)
                     : "memory", "cc");
}
void write_row(u32 receiver, u32 row, u32 buffer) {
    u32 table = word(receiver);
    const u32 code = word(table + 8), words[3] = {row, 0, buffer};
    __asm__ volatile("pushl 8(%3)\n\tpushl 4(%3)\n\tpushl (%3)\n\tcalll *%2"
                     : "+a"(table), "+c"(receiver)
                     : "r"(code), "r"(words)
                     : "edx", "memory", "cc");
}
#include "graphics/surface/surface_linear_mix.h"
constexpr int32_t failure = static_cast<int32_t>(0x80004005u),
                  out_of_memory = static_cast<int32_t>(0x8007000eu);
} // namespace
// Complete original5eeb06..5eeea8. The two tables execute the actual recovered
// private-register5eea1a helper; row methods remain genuine virtual boundaries.
extern "C" int32_t __attribute__((thiscall)) FUN_005eeb06(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object), flags = word(self + 8);
    if (static_cast<unsigned char>(flags) != 3)
        return failure;
    u32 destination = word(self + 4);
    if (word(destination + 0x70) != 1)
        return failure;
    u32 source = word(self);
    if (word(source + 0x70) != 1)
        return failure;
    const u32 xflag = (~(flags >> 16)) & 1, yflag = (~(flags >> 17)) & 1;
    const u32 output_width = word(destination + 0x68), input_width = word(source + 0x68);
    const u32 xtable = weights(input_width, output_width, xflag);
    source = word(self);
    const u32 input_height = word(source + 0x6c);
    destination = word(self + 4);
    const u32 output_height = word(destination + 0x6c);
    const u32 ytable = weights(input_height, output_height, yflag);
    void* output = nullptr;
    void* input = nullptr;
    int32_t result = out_of_memory;
    if (xtable && ytable) {
        destination = word(self + 4);
        const u32 count = word(destination + 0x68);
        output = fun_005cc96d(count << 4);
        if (output)
            FUN_00405c90(output, 16, count, reinterpret_cast<uintptr_t>(&FUN_004441b0));
        if (output) {
            source = word(self);
            const u32 input_count = word(source + 0x68) << 1;
            input = fun_005cc96d(input_count << 4);
            if (input)
                FUN_00405c90(input, 16, input_count, reinterpret_cast<uintptr_t>(&FUN_004441b0));
            if (input) {
                source = word(self);
                const u32 width = word(source + 0x68);
                u32 lower = reinterpret_cast<uintptr_t>(input), upper = lower + (width << 4),
                    lower_row = 0xffffffffu, upper_row = 0xffffffffu, row = 0, y = ytable + 8;
                destination = word(self + 4);
                if (word(destination + 0x6c))
                    do {
                        const u32 first = word(y - 8);
                        if (first != lower_row) {
                            if (first == upper_row) {
                                const u32 old = lower;
                                upper_row = 0xffffffffu;
                                lower = upper;
                                lower_row = first;
                                upper = old;
                            } else {
                                source = word(self);
                                lower_row = first;
                                read_row(source, first, lower);
                            }
                        }
                        const u32 second = word(y);
                        if (second != upper_row) {
                            source = word(self);
                            upper_row = second;
                            read_row(source, second, upper);
                        }
                        destination = word(self + 4);
                        u32 x = xtable + 8, pixel = 0, to = reinterpret_cast<uintptr_t>(output);
                        if (word(destination + 0x68))
                            do {
                                mix_linear(to, lower, upper, x, y);
                                ++pixel;
                                x += 16;
                                to += 16;
                                destination = word(self + 4);
                            } while (pixel < word(destination + 0x68));
                        destination = word(self + 4);
                        write_row(destination, row, reinterpret_cast<uintptr_t>(output));
                        destination = word(self + 4);
                        y += 16;
                        ++row;
                    } while (row < word(destination + 0x6c));
                result = 0;
            }
        }
    }
    fun_005cc620(reinterpret_cast<void*>(xtable));
    fun_005cc620(reinterpret_cast<void*>(ytable));
    fun_005cc620(output);
    fun_005cc620(input);
    return result;
}
