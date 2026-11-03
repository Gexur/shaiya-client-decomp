#include "graphics/surface/surface_format_owner.h"
#include "graphics/surface/surface_format_palette.h"
#include "runtime/allocations.h"
#include "graphics/surface/surface_format_configure.h"
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
void add_word(u32 p, u32 v) {
    __asm__ volatile("addl %1,(%0)" ::"r"(p), "r"(v) : "memory", "cc");
}
void copy6(u32 output, u32 input) {
    u32 count = 6;
    __asm__ volatile("rep movsl" : "+D"(output), "+S"(input), "+c"(count)::"memory");
}
void scaled(u32 argument, u32 output) {
    __asm__ volatile("fildl (%0)\n\tfmul %%st(1),%%st(0)\n\tfstps (%1)" ::"r"(argument), "r"(output)
                     : "st", "memory");
}
void zero_bytes(u32 output, u32 bytes) {
    u32 count = bytes >> 2;
    __asm__ volatile("rep stosl" : "+D"(output), "+c"(count) : "a"(0) : "memory");
    count = bytes & 3;
    __asm__ volatile("rep stosb" : "+D"(output), "+c"(count) : "a"(0) : "memory");
}
} // namespace
// Complete original5f1e45..5f2011. The descriptor and bit-count incoming words
// are original writable state, so the entry passes their actual addresses.
extern "C" u32 recovered_005f1e45(u32 self, u32 arguments) {
    const u32 descriptor = word(arguments);
    put(self, reinterpret_cast<uintptr_t>(dat_006df3b0));
    put(self + 0x20, word(descriptor));
    put(self + 4, word(descriptor + 4));
    put(self + 0x60, word(descriptor + 8));
    put(self + 0x64, word(descriptor + 12));
    copy6(self + 0x3c, descriptor + 0x28);
    const u32 dither = word(descriptor + 0x40) ? reinterpret_cast<uintptr_t>(dat_0070fe80)
                                               : reinterpret_cast<uintptr_t>(dat_0070fe00);
    put(self + 0x34, dither);
    const u32 bytes = word(arguments + 4) >> 3;
    put(arguments, bytes);
    put(self + 0x78, bytes);
    const bool packed = word(arguments + 4) != 0;
    put(self + 0x54, 0);
    put(self + 0x58, 0);
    put(self + 12, packed ? 1 : 0);
    put(self + 8, word(arguments + 8));
    put(self + 0x18, word(descriptor + 0x4c));
    const u32 format = word(self + 4);
    const u32 indexed = (format == 0x29 || format == 0x28) ? 1 : 0;
    const bool color = word(self + 0x18) != 0;
    put(self + 0x1c, indexed);
    put(self + 0x38, 0);
    put(self + 0x10, word(descriptor + 0x48));
    put(self + 0x14, 0);
    put(self + 0x5c, 0);
    if (color) {
        const u32 argb = word(descriptor + 0x4c);
        u32 temporary[4];
        __asm__ volatile("flds %0" ::"m"(dat_006be1d0) : "st", "memory");
        put(arguments + 4, (argb >> 16) & 255);
        scaled(arguments + 4, reinterpret_cast<uintptr_t>(&temporary[0]));
        put(arguments + 4, (argb >> 8) & 255);
        scaled(arguments + 4, reinterpret_cast<uintptr_t>(&temporary[1]));
        put(arguments + 4, argb & 255);
        scaled(arguments + 4, reinterpret_cast<uintptr_t>(&temporary[2]));
        put(arguments + 4, argb >> 24);
        scaled(arguments + 4, reinterpret_cast<uintptr_t>(&temporary[3]));
        put(self + 0x24, word(reinterpret_cast<uintptr_t>(&temporary[0])));
        put(self + 0x28, word(reinterpret_cast<uintptr_t>(&temporary[1])));
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
        put(self + 0x2c, word(reinterpret_cast<uintptr_t>(&temporary[2])));
        put(self + 0x30, word(reinterpret_cast<uintptr_t>(&temporary[3])));
    }
    if (word(arguments + 8) == 2) {
        if (word(self + 4) == 0x3d)
            goto geometry;
        put(self + 0x10, 0);
    }
    if (word(arguments + 8) == 3)
        put(self + 0x10, 0);
geometry:
    const u32 left = word(self + 0x3c), right = word(self + 0x44);
    const u32 top = word(self + 0x40);
    u32 bottom = word(self + 0x48);
    const u32 width = right - left;
    put(self + 0x68, width);
    const u32 row_bytes = width * word(arguments);
    bottom -= top;
    const u32 front = word(self + 0x4c);
    put(self + 0x6c, bottom);
    u32 back = word(self + 0x50);
    put(self + 0x74, row_bytes);
    back -= front;
    put(self + 0x70, back);
    if (packed) {
        const u32 x = left * word(arguments);
        const u32 pitch = word(self + 0x60);
        const u32 actual_top = word(self + 0x40);
        const u32 y = pitch * actual_top;
        const u32 slice_pitch = word(self + 0x64);
        const u32 z = slice_pitch * front;
        add_word(self + 0x20, x + y + z);
        put(self + 0x44, word(self + 0x68));
        put(self + 0x48, word(self + 0x6c));
        const u32 depth = word(self + 0x70);
        put(self + 0x3c, 0);
        put(self + 0x40, 0);
        put(self + 0x4c, 0);
        put(self + 0x50, depth);
    }
    if (word(descriptor + 0x44)) {
        const u32 count = word(self + 0x68) + 2;
        void* const allocation = fun_005cc96d(count << 4);
        if (allocation)
            FUN_00405c90(allocation, 16, count, reinterpret_cast<uintptr_t>(&FUN_004441b0));
        put(self + 0x5c, reinterpret_cast<uintptr_t>(allocation));
        if (allocation)
            zero_bytes(reinterpret_cast<uintptr_t>(allocation), (word(self + 0x68) + 2) << 4);
    }
    return self;
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f1e45(void*, void*, uint32_t,
                                                                  uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f1e45\n\taddl $8,%esp\n\tretl $12");
}
