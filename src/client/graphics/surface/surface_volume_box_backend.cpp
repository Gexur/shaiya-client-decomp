#include "graphics/surface/surface_volume_box_backend.h"
#include "graphics/surface/surface_format_configure.h"
#include "runtime/allocations.h"
#include "core/untouched_lifetime.h"
extern "C" const float dat_006bfde0 = 0.125f;
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
void and_even(u32 p) {
    __asm__ volatile("andl $-2,(%0)" ::"r"(p) : "memory", "cc");
}
void subtract(u32 p, u32 n) {
    __asm__ volatile("subl %1,(%0)" ::"r"(p), "r"(n) : "memory", "cc");
}
struct __attribute__((packed, may_alias)) FloatWord {
    float value;
};
volatile float& f32(u32 p) {
    return reinterpret_cast<volatile FloatWord*>(p)->value;
}
void read_row(u32 receiver, u32 row, u32 slice, u32 buffer) {
    u32 table = word(receiver);
    const u32 code = word(table + 4), words[3] = {row, slice, buffer};
    // Original612 read call uses EAX=row and EDX=table, in addition to thiscall
    // ECX/three stack words. Preserve those two observed volatile inputs.
    __asm__ volatile("pushl 8(%4)\n\tpushl 4(%4)\n\tpushl (%4)\n\tcalll *%3"
                     : "+a"(row), "+d"(table), "+c"(receiver)
                     : "r"(code), "r"(words)
                     : "memory", "cc");
}
void write_row(u32 receiver, u32 row, u32 slice, u32 buffer) {
    u32 table = word(receiver);
    const u32 code = word(table + 8), words[3] = {row, slice, buffer};
    __asm__ volatile("pushl 8(%3)\n\tpushl 4(%3)\n\tpushl (%3)\n\tcalll *%2"
                     : "+a"(table), "+c"(receiver)
                     : "r"(code), "r"(words)
                     : "edx", "memory", "cc");
}
#include "graphics/surface/surface_volume_box_average.h"
constexpr int32_t failure = static_cast<int32_t>(0x80004005u),
                  out_of_memory = static_cast<int32_t>(0x8007000eu);
} // namespace
// Complete5ee612..5eea1a. No adjacent5eea1a private-register helper bytes are
// included in this function or supplied as a replacement conversion routine.
extern "C" int32_t __attribute__((thiscall)) FUN_005ee612(void* object) {
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
    const u32 source_depth = word(source + 0x70);
    if (word(destination + 0x70) != (source_depth >> 1))
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
    source = word(self);
    if (word(source + 0x70) > 1)
        and_even(source + 0x70);
    destination = word(self + 4);
    const u32 output_width = word(destination + 0x68);
    void* output = fun_005cc96d(output_width << 4);
    if (output)
        FUN_00405c90(output, 16, output_width, reinterpret_cast<uintptr_t>(&FUN_004441b0));
    if (!output)
        return out_of_memory;
    source = word(self);
    const u32 input_height = word(source + 0x6c), input_width = word(source + 0x68);
    const u32 count = input_width << (input_height == 1 ? 1 : 2);
    void* input = fun_005cc96d(count << 4);
    if (input)
        FUN_00405c90(input, 16, count, reinterpret_cast<uintptr_t>(&FUN_004441b0));
    source = word(self);
    const u32 width_address = source + 0x68, current_width = word(width_address);
    const u32 first = reinterpret_cast<uintptr_t>(input);
    u32 second, third, fourth;
    if (input_height == 1) {
        second = (current_width << 4) + first;
        third = first;
        fourth = second;
    } else {
        second = (current_width << 4) + first;
        third = (current_width << 5) + first;
        fourth = ((current_width + current_width * 2) << 4) + first;
    }
    if (!input) {
        fun_005cc620(output);
        return out_of_memory;
    }
    u32 first_right = first, second_right = second, third_right = third, fourth_right = fourth;
    if (word(width_address) != 1) {
        first_right += 16;
        second_right += 16;
        third_right += 16;
        fourth_right += 16;
    }
    u32 slice = 0;
    destination = word(self + 4);
    if (word(destination + 0x70))
        do {
            u32 row = 0;
            if (word(destination + 0x6c))
                do {
                    source = word(self);
                    read_row(source, row * 2, slice * 2, first);
                    if (second != first) {
                        source = word(self);
                        read_row(source, row * 2, slice * 2 + 1, second);
                    }
                    if (third != first) {
                        source = word(self);
                        read_row(source, row * 2 + 1, slice * 2, third);
                    }
                    if (fourth != second && fourth != third) {
                        source = word(self);
                        read_row(source, row * 2 + 1, slice * 2 + 1, fourth);
                    }
                    destination = word(self + 4);
                    u32 x = 0;
                    if (word(destination + 0x68)) {
                        const volatile long double eighth = static_cast<long double>(
                            f32(reinterpret_cast<uintptr_t>(&dat_006bfde0)));
                        u32 to = reinterpret_cast<uintptr_t>(output);
                        do {
                            const u32 offset = (x + x) << 4;
                            average8(to, first + offset, first_right + offset, second + offset,
                                     second_right + offset, third + offset, third_right + offset,
                                     fourth + offset, fourth_right + offset, eighth);
                            ++x;
                            to += 16;
                            destination = word(self + 4);
                        } while (x < word(destination + 0x68));
                    }
                    destination = word(self + 4);
                    write_row(destination, row, slice, reinterpret_cast<uintptr_t>(output));
                    ++row;
                    destination = word(self + 4);
                } while (row < word(destination + 0x6c));
            ++slice;
            destination = word(self + 4);
        } while (slice < word(destination + 0x70));
    fun_005cc620(input);
    fun_005cc620(output);
    return 0;
}
