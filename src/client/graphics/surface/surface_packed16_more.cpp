#include "graphics/surface/surface_packed16_more.h"
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
void store_half(u32 p, u32 v) {
    __asm__ volatile("movw %w1,(%0)" ::"r"(p), "r"(v) : "memory");
}
} // namespace
// Complete original5ed437..5ed560. No format semantics are inferred: masks,
// biases, four input load order and XOR sequence are the original arithmetic.
extern "C" int32_t __attribute__((thiscall)) FUN_005ed437(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    u32 destination = word(self + 4), source = word(self), input_row = word(source + 0x20),
        output_row = word(destination + 0x20);
    const u32 height = word(source + 0x6c), pitch = word(source + 0x60),
              end = input_row + height * pitch;
    if (input_row < end)
        do {
            const u32 row_pitch = word(source + 0x60), width = word(source + 0x68),
                      row_end = input_row + width * 2;
            u32 first = input_row, second = input_row + row_pitch, output = output_row;
            if (first < row_end)
                do {
                    const u32 b = half(first + 2), d = half(second + 2), c = half(second),
                              a = half(first);
                    const u32 group1 = ((a & 0x83e0u) + (d & 0x83e0u) + (c & 0x83e0u) +
                                        (b & 0x83e0u) + 0x10040u) >>
                                       2;
                    const u32 group2 =
                        ((a & 0x7c1fu) + (d & 0x7c1fu) + (c & 0x7c1fu) + (b & 0x7c1fu) + 0x802u) >>
                        2;
                    const u32 group3 = ((a & 0x83e0u) + (d & 0x83e0u) + (c & 0x83e0u) +
                                        (b & 0x83e0u) + 0x10040u) >>
                                       2;
                    store_half(output, ((group1 ^ group2) & 0xffff7c1fu) ^ group3);
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
// Complete original5ed560..5ed697, including bottom0/bottom1/top1/top0 reads.
extern "C" int32_t __attribute__((thiscall)) FUN_005ed560(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    u32 source = word(self), destination = word(self + 4), output_row = word(destination + 0x20),
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
                    const u32 c = half(second), d = half(second + 2), b = half(first + 2),
                              a = half(first);
                    const u32 group1 =
                        ((a & 0xf0f0u) + (d & 0xf0f0u) + (c & 0xf0f0u) + (b & 0xf0f0u) + 0x2020u) >>
                        2;
                    const u32 group2 = ((a & 0xffff0f0fu) + (d & 0xffff0f0fu) + (c & 0xffff0f0fu) +
                                        (b & 0xffff0f0fu) + 0x202u) >>
                                       2;
                    const u32 group3 =
                        ((a & 0xf0f0u) + (d & 0xf0f0u) + (c & 0xf0f0u) + (b & 0xf0f0u) + 0x2020u) >>
                        2;
                    store_half(output, ((group1 ^ group2) & 0xffff0f0fu) ^ group3);
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
