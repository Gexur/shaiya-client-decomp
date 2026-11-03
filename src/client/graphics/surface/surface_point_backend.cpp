#include "graphics/surface/surface_point_backend.h"
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
unsigned char byte(u32 p) {
    unsigned char v;
    __asm__ volatile("movb (%1),%0" : "=q"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
u32 divide(u32 numerator, u32 denominator) {
    // Actual unsigned DIV with zero high word, including its divide-by-zero
    // behavior. No C++ zero-divisor UB or conventional resampling math fallback.
    u32 remainder = 0;
    __asm__ volatile("divl %2" : "+a"(numerator), "+d"(remainder) : "r"(denominator) : "cc");
    return numerator;
}
void pixel(u32 destination, u32 source) {
    __asm__ volatile("movsl\n\tmovsl\n\tmovsl\n\tmovsl"
                     : "+D"(destination), "+S"(source)::"memory");
}
void row_call(u32 receiver, u32 row, u32 slice, u32 buffer, u32 offset) {
    u32 table = word(receiver);
    const u32 code = word(table + offset), words[3] = {row, slice, buffer};
    __asm__ volatile("pushl 8(%3)\n\tpushl 4(%3)\n\tpushl (%3)\n\tcalll *%2"
                     : "+a"(table), "+c"(receiver)
                     : "r"(code), "r"(words)
                     : "edx", "memory", "cc");
}
constexpr int32_t failure = static_cast<int32_t>(0x80004005u),
                  out_of_memory = static_cast<int32_t>(0x8007000eu);
} // namespace
// Complete5ee074..5ee24a. All step numerators wrap at32 bits before unsigned
// division; cached16.16 increments and live receiver bounds are distinct.
extern "C" int32_t __attribute__((thiscall)) FUN_005ee074(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    if (byte(self + 8) != 2)
        return failure;
    u32 source = word(self);
    const u32 initial_source_width = word(source + 0x68);
    void* first = fun_005cc96d(initial_source_width << 4);
    if (first)
        FUN_00405c90(first, 16, initial_source_width, reinterpret_cast<uintptr_t>(&FUN_004441b0));
    if (!first)
        return out_of_memory;
    u32 destination = word(self + 4);
    const u32 initial_destination_width = word(destination + 0x68);
    void* second = fun_005cc96d(initial_destination_width << 4);
    if (second)
        FUN_00405c90(second, 16, initial_destination_width,
                     reinterpret_cast<uintptr_t>(&FUN_004441b0));
    if (!second) {
        fun_005cc620(first);
        return out_of_memory;
    }
    destination = word(self + 4);
    if (word(destination + 0x10)) {
        source = word(self);
        if (word(source + 0x10)) {
            put(destination + 0x10, 0);
            source = word(self);
            put(source + 0x10, 0);
        }
    }
    source = word(self);
    destination = word(self + 4);
    const u32 source_width = word(source + 0x68), destination_width = word(destination + 0x68);
    const u32 x_step = divide(source_width << 16, destination_width);
    const u32 source_height = word(source + 0x6c), destination_height = word(destination + 0x6c);
    const u32 y_step = divide(source_height << 16, destination_height);
    const u32 source_depth = word(source + 0x70), destination_depth = word(destination + 0x70);
    const u32 z_step = divide(source_depth << 16, destination_depth);
    u32 source_slice = 0, destination_slice = 0;
    if (word(destination + 0x70))
        do {
            u32 cached_source_row = 0xffffffffu, source_row = 0, destination_row = 0;
            if (word(destination + 0x6c))
                do {
                    u32 source_x = 0, destination_x = 0;
                    if ((cached_source_row ^ source_row) & 0xffff0000u) {
                        source = word(self);
                        row_call(source, source_row >> 16, source_slice >> 16,
                                 reinterpret_cast<uintptr_t>(first), 4);
                        cached_source_row = source_row;
                    }
                    destination = word(self + 4);
                    u32 output = reinterpret_cast<uintptr_t>(second);
                    if (word(destination + 0x68))
                        do {
                            const u32 input =
                                (source_x >> 16) * 16 + reinterpret_cast<uintptr_t>(first);
                            source_x += x_step;
                            ++destination_x;
                            pixel(output, input);
                            destination = word(self + 4);
                            output += 16;
                        } while (destination_x < word(destination + 0x68));
                    destination = word(self + 4);
                    row_call(destination, destination_row, destination_slice,
                             reinterpret_cast<uintptr_t>(second), 8);
                    source_row += y_step;
                    ++destination_row;
                    destination = word(self + 4);
                } while (destination_row < word(destination + 0x6c));
            source_slice += z_step;
            ++destination_slice;
            destination = word(self + 4);
        } while (destination_slice < word(destination + 0x70));
    fun_005cc620(first);
    fun_005cc620(second);
    return 0;
}
