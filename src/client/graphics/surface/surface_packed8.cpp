#include "graphics/surface/surface_packed8.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 byte(u32 p) {
    u32 v;
    __asm__ volatile("movzbl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void store_byte(u32 p, u32 v) {
    __asm__ volatile("movb %b1,(%0)" ::"r"(p), "q"(v) : "memory");
}
} // namespace
// Complete original5ed697..5ed7b5, preserving raw masks and BYTE operations.
extern "C" int32_t __attribute__((thiscall)) FUN_005ed697(void* object) {
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
                    const u32 group1 =
                        ((a & 0x1cu) + (d & 0x1cu) + (c & 0x1cu) + (b & 0x1cu) + 8) >> 2;
                    const u32 group2 =
                        ((a & 0xe3u) + (d & 0xe3u) + (c & 0xe3u) + (b & 0xe3u) + 0x42u) >> 2;
                    const u32 group3 =
                        ((a & 0xe3u) + (d & 0xe3u) + (c & 0xe3u) + (b & 0xe3u) + 0x42u) >> 2;
                    store_byte(output, ((group1 ^ group2) & 0x1cu) ^ group3);
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
// Complete original5ed7b5..5ed841, including its distinct initial/read order.
extern "C" int32_t __attribute__((thiscall)) FUN_005ed7b5(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    u32 destination = word(self + 4), output_row = word(destination + 0x20), source = word(self),
        input_row = word(source + 0x20);
    const u32 height = word(source + 0x6c), pitch = word(source + 0x60),
              end = input_row + height * pitch;
    if (input_row < end)
        do {
            const u32 row_pitch = word(source + 0x60), width = word(source + 0x68),
                      row_end = input_row + width;
            u32 first = input_row, second = input_row + row_pitch, output = output_row;
            if (first < row_end)
                do {
                    const u32 d = byte(second + 1), b = byte(first + 1), c = byte(second),
                              a = byte(first);
                    store_byte(output, (d + b + c + a + 2) >> 2);
                    first += 2;
                    ++output;
                    second += 2;
                } while (first < row_end);
            destination = word(self + 4);
            output_row += word(destination + 0x60);
            source = word(self);
            input_row += word(source + 0x60) * 2;
        } while (input_row < end);
    return 0;
}
