#include "graphics/surface/surface_read_transform.h"
#include "graphics/surface/surface_transfer_lut.h"
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
void square(u32 p) {
    __asm__ volatile(
        "flds (%0)\n\tfld %%st(0)\n\tfmul %%st(1),%%st(0)\n\tfstps (%0)\n\tfstp %%st(0)" ::"r"(p)
        : "st", "st(1)", "memory");
}
void convert(u32 p) {
    __asm__ volatile(
        "flds (%0)\n\tsubl $4,%%esp\n\tfstps (%%esp)\n\tcalll _FUN_005f1dfc@4\n\tfstps (%0)" ::"r"(
            p)
        : "eax", "ecx", "edx", "st", "memory", "cc");
}
} // namespace
// Complete5f24c9..5f25f2. Empty square paths keep incoming physical EAX;
// nonlinear paths overwrite low16 of the actual incoming pixel word with CW.
extern "C" u32 recovered_005f24c9(u32 self, u32 argument, u32 incoming_eax) {
    u32 pixels = word(argument);
    const u32 end = pixels + (word(self + 0x68) << 4);
    if (word(self + 0x14)) {
        const u32 kind = word(self + 8);
        if (pixels >= end)
            return incoming_eax;
        u32 count = ((end - pixels - 1) >> 4) + 1;
        if (kind == 1 || kind == 4) {
            u32 p = pixels + 8;
            do {
                square(p - 8);
                square(p - 4);
                square(p);
                p += 16;
            } while (--count);
            return p;
        }
        u32 p = pixels + 12;
        do {
            square(p);
            p += 16;
        } while (--count);
        return p;
    }
    __asm__ volatile("fnstcw (%0)" ::"r"(argument) : "memory");
    const u32 current = word(argument);
    u32 truncated = current | 0x0c00u;
    __asm__ volatile("fldcw %0" ::"m"(truncated) : "memory");
    put(self + 0x7c, word(argument));
    const u32 kind = word(self + 8);
    if (pixels < end) {
        u32 count = ((end - pixels - 1) >> 4) + 1;
        if (kind == 1 || kind == 4) {
            u32 p = pixels + 8;
            do {
                convert(p - 8);
                convert(p - 4);
                convert(p);
                p += 16;
            } while (--count);
        } else {
            u32 p = pixels + 12;
            do {
                convert(p);
                p += 16;
            } while (--count);
        }
    }
    const u32 saved = word(self + 0x7c);
    put(argument, saved);
    __asm__ volatile("fldcw (%0)" ::"r"(argument) : "memory");
    return saved;
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f24c9(void*, void*) {
    __asm__ volatile(
        "pushl %eax\n\tleal 8(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f24c9\n\taddl $12,%esp\n\tretl $4");
}
