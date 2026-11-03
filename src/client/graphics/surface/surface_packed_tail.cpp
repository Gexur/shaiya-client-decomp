#include "graphics/surface/surface_packed_tail.h"
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
void put_half(u32 p, u32 v) {
    __asm__ volatile("movw %w1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void put_byte(u32 p, u32 v) {
    __asm__ volatile("movb %b1,(%0)" ::"r"(p), "q"(v) : "memory");
}
// Original841 andA78 have identical control/load/store structure. Parameters
// below are the literal four mask/bias operands of their original streams.
template <u32 low_mask, u32 high_mask, u32 low_bias, u32 high_bias> int32_t word_xor(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    u32 destination = word(self + 4), output_row = word(destination + 0x20), source = word(self),
        input_row = word(source + 0x20);
    const u32 height = word(source + 0x6c), pitch = word(source + 0x60),
              end = input_row + height * pitch;
    if (input_row < end)
        do {
            const u32 row_pitch = word(source + 0x60), width = word(source + 0x68),
                      row_end = input_row + width * 2;
            u32 first = input_row, second = input_row + row_pitch, output = output_row;
            if (first < row_end)
                do {
                    const u32 d = half(second + 2), c = half(second), a = half(first),
                              b = half(first + 2);
                    const u32 low = ((d & low_mask) + (a & low_mask) + (c & low_mask) +
                                     (b & low_mask) + low_bias) >>
                                    2;
                    const u32 high = ((d & high_mask) + (a & high_mask) + (c & high_mask) +
                                      (b & high_mask) + high_bias) >>
                                     2;
                    // Actual XOR DL,CL preserves the remaining24bits before the full AND.
                    const u32 partial = (low & 0xffffff00u) | ((low ^ high) & 0xffu);
                    const u32 masked = partial & (0xffff0000u | low_mask);
                    const u32 high_again = ((d & high_mask) + (a & high_mask) + (c & high_mask) +
                                            (b & high_mask) + high_bias) >>
                                           2;
                    put_half(output, masked ^ high_again);
                    output += 2;
                    first += 4;
                    second += 4;
                } while (first < row_end);
            destination = word(self + 4);
            output_row += word(destination + 0x60);
            source = word(self);
            input_row += word(source + 0x60) * 2;
        } while (input_row < end);
    return 0;
}
} // namespace
// Complete original5ed841..5ed96f and5eda78..5edba6 respectively.
extern "C" int32_t __attribute__((thiscall)) FUN_005ed841(void* p) {
    return word_xor<0xe3u, 0xff1cu, 0x42u, 0x208u>(p);
}
extern "C" int32_t __attribute__((thiscall)) FUN_005eda78(void* p) {
    return word_xor<0xffu, 0xff00u, 2u, 0x200u>(p);
}
// Complete original5ed96f..5eda78, with top0/top1/bottom1/bottom0 reads.
extern "C" int32_t __attribute__((thiscall)) FUN_005ed96f(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    u32 destination = word(self + 4), output_row = word(destination + 0x20), source = word(self);
    const u32 height = word(source + 0x6c), pitch = word(source + 0x60);
    u32 input_row = word(source + 0x20);
    const u32 end = input_row + height * pitch;
    if (input_row < end)
        do {
            const u32 row_pitch = word(source + 0x60), width = word(source + 0x68),
                      row_end = input_row + width * 2;
            u32 first = input_row, second = input_row + row_pitch, output = output_row;
            if (first < row_end)
                do {
                    const u32 a = half(first), b = half(first + 2), d = half(second + 2),
                              c = half(second);
                    const u32 narrow = ((d & 0xffff00f0u) + (a & 0xffff00f0u) + (c & 0xffff00f0u) +
                                        (b & 0xffff00f0u) + 0x20u) >>
                                       2;
                    const u32 wide = ((d & 0xffff0f0fu) + (a & 0xffff0f0fu) + (c & 0xf0fu) +
                                      (b & 0xf0fu) + 0x202u) >>
                                     2;
                    const u32 partial = (wide & 0xffff0000u) | (wide & 0xf0fu);
                    put_half(output, (narrow & 0xffff00f0u) | partial);
                    second += 4;
                    output += 2;
                    first += 4;
                } while (first < row_end);
            destination = word(self + 4);
            output_row += word(destination + 0x60);
            source = word(self);
            input_row += word(source + 0x60) * 2;
        } while (input_row < end);
    return 0;
}
// Complete original5edba6..5edcc4. One-BYTE elements and distinct width units.
extern "C" int32_t __attribute__((thiscall)) FUN_005edba6(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    u32 destination = word(self + 4), output_row = word(destination + 0x20), source = word(self);
    const u32 height = word(source + 0x6c), pitch = word(source + 0x60);
    u32 input_row = word(source + 0x20);
    const u32 end = input_row + height * pitch;
    if (input_row < end)
        do {
            const u32 row_pitch = word(source + 0x60), width = word(source + 0x68),
                      row_end = input_row + width;
            u32 first = input_row, second = input_row + row_pitch, output = output_row;
            if (first < row_end)
                do {
                    const u32 c = byte(second), d = byte(second + 1), b = byte(first + 1),
                              a = byte(first);
                    const u32 low = ((a & 0xfu) + (d & 0xfu) + (c & 0xfu) + (b & 0xfu) + 2) >> 2;
                    const u32 high =
                        ((d & 0xf0u) + (a & 0xf0u) + (c & 0xf0u) + (b & 0xf0u) + 0x20u) >> 2;
                    const u32 high_again =
                        ((d & 0xf0u) + (a & 0xf0u) + (c & 0xf0u) + (b & 0xf0u) + 0x20u) >> 2;
                    put_byte(output, ((low ^ high) & 0xfu) ^ high_again);
                    ++output;
                    first += 2;
                    second += 2;
                } while (first < row_end);
            destination = word(self + 4);
            output_row += word(destination + 0x60);
            source = word(self);
            input_row += word(source + 0x60) * 2;
        } while (input_row < end);
    return 0;
}
