#include "graphics/surface/surface_rgb24_read.h"
#include "graphics/surface/surface_color_match.h"
#include "graphics/surface/surface_format_palette.h"
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
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void scaled(u32 argument, u32 output) {
    __asm__ volatile("fildl (%0)\n\tfmul %%st(1),%%st(0)\n\tfstps (%1)" ::"r"(argument), "r"(output)
                     : "st", "memory");
}
void one(u32 output) {
    __asm__ volatile("fld1\n\tfstps (%0)" ::"r"(output) : "st", "memory");
}
__attribute__((always_inline)) inline u32 color(u32& self, u32 eax, u32 input) {
    u32 edx = input;
    __asm__ volatile("pushl %3\n\tcalll _FUN_005f225c"
                     : "+a"(eax), "+c"(self), "+d"(edx)
                     : "r"(input)
                     : "memory", "cc");
    return eax;
}
__attribute__((always_inline)) inline u32 transform(u32 self, u32 eax, u32 input) {
    u32 edx;
    __asm__ volatile("pushl %3\n\tcalll _FUN_005f24c9"
                     : "+a"(eax), "+c"(self), "=d"(edx)
                     : "r"(input)
                     : "memory", "cc");
    return eax;
}
} // namespace
// Complete original5f8eda..5f8f72. The incoming output word is repeatedly
// overwritten by each MOVZX byte before its actual FILD, so pass its address.
extern "C" u32 recovered_005f8eda(u32 self, u32 arguments) {
    u32 input = word(self + 0x60) * word(arguments);
    const u32 slice = word(self + 0x64) * word(arguments + 4);
    input += slice;
    input += word(self + 0x20);
    const u32 end = input + word(self + 0x74);
    u32 output = word(arguments + 8);
    if (input < end) {
        __asm__ volatile("flds %0" ::"m"(dat_006be1d0) : "st", "memory");
        do {
            put(arguments + 8, byte(input + 2));
            scaled(arguments + 8, output);
            put(arguments + 8, byte(input + 1));
            output += 16;
            scaled(arguments + 8, output - 12);
            put(arguments + 8, byte(input));
            input += 3;
            scaled(arguments + 8, output - 8);
            one(output - 4);
        } while (input < end);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    }
    u32 result = input;
    if (word(self + 0x18)) {
        result = word(self + 0x68) << 4;
        const u32 pixels = output - result;
        result = color(self, result, pixels);
    }
    if (word(self + 0x10)) {
        result = word(self + 0x68) << 4;
        output -= result;
        result = transform(self, result, output);
    }
    return result;
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f8eda(void*, uint32_t, uint32_t,
                                                                  void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f8eda\n\taddl $8,%esp\n\tretl $12");
}
