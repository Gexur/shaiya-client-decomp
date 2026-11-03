#include "graphics/surface/surface_write_color.h"
#include "graphics/render_rsqrt_scalar.h"
#include "graphics/surface/surface_inverse_transfer_lut.h"
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
void load(u32 p) {
    __asm__ volatile("flds (%0)" ::"r"(p) : "st", "memory");
}
void store(u32 p) {
    __asm__ volatile("fstps (%0)" ::"r"(p) : "st", "memory");
}
void root(u32 p) {
    __asm__ volatile(
        "flds (%0)\n\tsubl $4,%%esp\n\tfstps (%%esp)\n\tcalll _FUN_0064f3a4@4\n\tfmuls (%0)" ::"r"(
            p)
        : "eax", "ecx", "edx", "st", "memory", "cc");
}
void convert(u32 p) {
    __asm__ volatile("flds (%0)\n\tsubl $4,%%esp\n\tfstps (%%esp)\n\tcalll _FUN_005f1daa@4" ::"r"(p)
                     : "eax", "ecx", "edx", "st", "memory", "cc");
}
} // namespace
// Complete original005f22d6..005f24c9. This preserves the real caller word
// rewrites and fresh output/width reads; all numeric work is the actual helpers.
extern "C" uint32_t recovered_005f22d6(uint32_t self, uint32_t argument) {
    u32 count = 0;
    if (word(self + 0x14)) {
        const u32 kind = word(self + 8);
        if (word(self + 0x68) == 0)
            return word(self + 0x58);
        const u32 base = word(argument);
        if (kind == 1 || kind == 4) {
            put(argument, 0xfffffff8u);
            put(argument, word(argument) - base);
            u32 p = base + 8;
            do {
                const u32 offset = word(argument) + p;
                root(p - 8);
                u32 output = word(self + 0x58);
                store(output + offset);
                root(p - 4);
                output = word(self + 0x58);
                store(output + offset + 4);
                root(p);
                output = word(self + 0x58);
                ++count;
                p += 16;
                store(output + offset + 8);
                output = word(self + 0x58);
                load(p - 12);
                store(output + offset + 12);
            } while (count < word(self + 0x68));
        } else {
            put(argument, 0xfffffff4u);
            put(argument, word(argument) - base);
            u32 p = base + 12;
            do {
                const u32 offset = word(argument) + p;
                load(p - 12);
                u32 output = word(self + 0x58);
                store(output + offset);
                output = word(self + 0x58);
                load(p - 8);
                store(output + offset + 4);
                output = word(self + 0x58);
                load(p - 4);
                store(output + offset + 8);
                root(p);
                output = word(self + 0x58);
                ++count;
                p += 16;
                store(output + offset + 12);
            } while (count < word(self + 0x68));
        }
    } else {
        // Original PUSH ECX supplies the upper16 bits left untouched by FNSTCW.
        u32 saved = self;
        __asm__ volatile("fnstcw %0" : "+m"(saved)::"memory");
        const u32 truncated = saved | 0x0c00u;
        __asm__ volatile("fldcw %0" ::"m"(truncated) : "memory");
        put(self + 0x7c, saved);
        const u32 kind = word(self + 8);
        if (word(self + 0x68) != 0) {
            u32 p = word(argument) + 8, offset = 0;
            if (kind == 1 || kind == 4) {
                do {
                    convert(p - 8);
                    u32 output = word(self + 0x58);
                    store(output + offset);
                    convert(p - 4);
                    output = word(self + 0x58);
                    store(output + offset + 4);
                    convert(p);
                    output = word(self + 0x58);
                    ++count;
                    store(output + offset + 8);
                    output = word(self + 0x58);
                    load(p + 4);
                    store(output + offset + 12);
                    offset += 16;
                    p += 16;
                } while (count < word(self + 0x68));
            } else {
                do {
                    u32 output = word(self + 0x58);
                    load(p - 8);
                    store(output + offset);
                    output = word(self + 0x58);
                    load(p - 4);
                    store(output + offset + 4);
                    output = word(self + 0x58);
                    load(p);
                    store(output + offset + 8);
                    convert(p + 4);
                    output = word(self + 0x58);
                    ++count;
                    store(output + offset + 12);
                    offset += 16;
                    p += 16;
                } while (count < word(self + 0x68));
            }
        }
        put(argument, word(self + 0x7c));
        __asm__ volatile("fldcw (%0)" ::"r"(argument) : "memory");
    }
    return word(self + 0x58);
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f22d6(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f22d6\n\taddl $8,%esp\n\tretl $4");
}
