#include "graphics/surface/surface_packed16.h"
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
void put_half(u32 p, u32 v) {
    __asm__ volatile("movw %w1,(%0)" ::"r"(p), "r"(v) : "memory");
}
} // namespace
// Complete5ed1fe..5ed332. Raw masks/XOR order and four WORD read order come
// from the instructions, without assigning a guessed pixel-format formula.
extern "C" int32_t __attribute__((thiscall)) FUN_005ed1fe(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    u32 source = word(self), destination = word(self + 4), output_row = word(destination + 0x20),
        input_row = word(source + 0x20);
    const u32 height = word(source + 0x6c), pitch = word(source + 0x60),
              end = input_row + height * pitch;
    if (input_row < end)
        do {
            const u32 row_pitch = word(source + 0x60), width = word(source + 0x68),
                      row_end = input_row + width * 2;
            u32 second = input_row + row_pitch, first = input_row, output = output_row;
            if (first < row_end)
                do {
                    const u32 c = half(second), d = half(second + 2), b = half(first + 2),
                              a = half(first);
                    const u32 combined1 =
                        ((a & 0xf81fu) + (d & 0xf81fu) + (c & 0xf81fu) + (b & 0xf81fu) + 0x1002u) >>
                        2;
                    const u32 combined2 = ((a & 0xffff07e0u) + (d & 0xffff07e0u) +
                                           (c & 0xffff07e0u) + (b & 0xffff07e0u) + 0x40u) >>
                                          2;
                    const u32 different = combined1 ^ combined2;
                    const u32 combined3 =
                        ((a & 0xf81fu) + (d & 0xf81fu) + (c & 0xf81fu) + (b & 0xf81fu) + 0x1002u) >>
                        2;
                    put_half(output, (different & 0xffff07e0u) ^ combined3);
                    output += 2;
                    first += 4;
                    second += 4;
                } while (first < row_end);
            destination = word(self + 4);
            output_row += word(destination + 0x60);
            source = word(self);
            const u32 current_pitch = word(source + 0x60);
            input_row += current_pitch * 2;
        } while (input_row < end);
    return 0;
}
// Complete5ed332..5ed437, including its distinct initial four-WORD load order.
extern "C" int32_t __attribute__((thiscall)) FUN_005ed332(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    u32 source = word(self), destination = word(self + 4), output_row = word(destination + 0x20),
        input_row = word(source + 0x20);
    const u32 height = word(source + 0x6c), pitch = word(source + 0x60),
              end = input_row + height * pitch;
    if (input_row < end)
        do {
            const u32 row_pitch = word(source + 0x60), width = word(source + 0x68),
                      row_end = input_row + width * 2;
            u32 second = input_row + row_pitch, first = input_row, output = output_row;
            if (first < row_end)
                do {
                    const u32 b = half(first + 2), c = half(second), d = half(second + 2),
                              a = half(first);
                    const u32 combined1 = ((a & 0xffff03e0u) + (d & 0xffff03e0u) +
                                           (c & 0xffff03e0u) + (b & 0xffff03e0u) + 0x40u) >>
                                          2;
                    const u32 combined2 =
                        ((a & 0x7c1fu) + (d & 0x7c1fu) + (c & 0x7c1fu) + (b & 0x7c1fu) + 0x802u) >>
                        2;
                    put_half(output, (combined1 & 0xffff03e0u) | (combined2 & 0x7c1fu));
                    output += 2;
                    first += 4;
                    second += 4;
                } while (first < row_end);
            destination = word(self + 4);
            output_row += word(destination + 0x60);
            source = word(self);
            const u32 current_pitch = word(source + 0x60);
            input_row += current_pitch * 2;
        } while (input_row < end);
    return 0;
}
