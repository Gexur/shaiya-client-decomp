#include "graphics/surface/surface_packed_rows.h"
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
void add_word(u32 p, u32 v) {
    __asm__ volatile("addl %1,(%0)" ::"r"(p), "r"(v) : "memory", "cc");
}
} // namespace
// Original5ece1f..5ecf49. The adapter supplies the actual six incoming words,
// including the publicly overwritten width, height, destination and source.
extern "C" uint32_t recovered_005ece1f(uint32_t args) {
    const u32 height = word(args + 12);
    u32 source = word(args + 4), stride = word(args + 16);
    const u32 end = source + height * stride;
    if (source >= end)
        return 0;
    put(args + 12, source + word(args + 8) * 4);
    do {
        const u32 right = word(args + 12);
        u32 output = word(args);
        if (source < right) {
            u32 count = ((word(args + 12) - source - 1) >> 3) + 1, p = source + 4;
            do {
                const u32 b1 = word(p + stride), b0 = word(p + stride - 4);
                put(args + 8, b1);
                const u32 t1 = word(p), t0 = word(p - 4);
                u32 a = ((t0 >> 2) & 0xffc03fc0u) + ((b0 >> 2) & 0xffc03fc0u);
                a += ((word(args + 8) >> 2) & 0xffc03fc0u);
                a += ((t1 >> 2) & 0xffc03fc0u) + 0xff800080u;
                u32 b = (t0 & 0x00ff00ffu) + (b0 & 0x00ff00ffu);
                b += (word(args + 8) & 0x00ff00ffu);
                b += ((t1 & 0x00ff00ffu) + 0x00020002u);
                b >>= 2;
                u32 c = ((t0 >> 2) & 0x3fc03fc0u) + ((b0 >> 2) & 0x3fc03fc0u);
                c += ((word(args + 8) >> 2) & 0x3fc03fc0u);
                stride = word(args + 16);
                c += ((t1 >> 2) & 0x3fc03fc0u) + 0x00800080u;
                put(output, ((a ^ b) & 0x00ff00ffu) ^ c);
                output += 4;
                p += 8;
            } while (--count);
            source = word(args + 4);
        }
        const u32 output_stride = word(args + 20);
        add_word(args, output_stride);
        const u32 step = stride * 2;
        add_word(args + 12, step);
        source += step;
        put(args + 4, source);
    } while (source < end);
    return 0;
}
// Original5ecf6b..5ed057 has different initial reads and overwrites its actual
// width word with each output cursor before committing each output DWORD.
extern "C" uint32_t recovered_005ecf6b(uint32_t args) {
    const u32 height = word(args + 12);
    u32 stride = word(args + 16), source = word(args + 4);
    const u32 end = source + height * stride;
    if (source >= end)
        return 0;
    put(args + 12, source + word(args + 8) * 4);
    do {
        const u32 right = word(args + 12);
        const u32 output = word(args);
        put(args + 8, output);
        if (source < right) {
            u32 count = ((word(args + 12) - source - 1) >> 3) + 1, p = source + 4;
            do {
                const u32 b1 = word(p + stride), t1 = word(p), b0 = word(p + stride - 4),
                          t0 = word(p - 4);
                u32 low = (t0 & 0x00ff00ffu) + (b0 & 0x00ff00ffu);
                low += (b1 & 0x00ff00ffu);
                low += ((t1 & 0x00ff00ffu) + 0x00020002u);
                u32 middle = (t0 & 0x0000ff00u) + (b0 & 0x0000ff00u);
                middle += (b1 & 0x0000ff00u);
                middle += ((t1 & 0x0000ff00u) + 0x00000200u);
                const u32 target = word(args + 8);
                add_word(args + 8, 4);
                p += 8;
                --count;
                put(target, ((low & 0x03fc03fcu) | (middle & 0x0003fc00u)) >> 2);
                stride = word(args + 16);
            } while (count);
            source = word(args + 4);
        }
        const u32 output_stride = word(args + 20);
        add_word(args, output_stride);
        const u32 step = stride * 2;
        add_word(args + 12, step);
        source += step;
        put(args + 4, source);
    } while (source < end);
    return 0;
}
extern "C" __attribute__((naked, stdcall)) uint32_t FUN_005ece1f(uint32_t, uint32_t, uint32_t,
                                                                 uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005ece1f\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) uint32_t FUN_005ecf6b(uint32_t, uint32_t, uint32_t,
                                                                 uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005ecf6b\n\taddl $4,%esp\n\tretl $24");
}
