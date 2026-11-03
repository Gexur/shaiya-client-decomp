#include "graphics/surface/surface_format_palette.h"
#include "runtime/allocations.h"
#include "graphics/surface/surface_format_configure.h"
#include "core/untouched_lifetime.h"
extern "C" const uint32_t dat_006be1d0 = 0x3b808081u;
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
} // namespace
// Complete original5f20b5..5f21aa. The actual descriptor argument DWORD is
// rewritten with each source BYTE; the cached descriptor itself stays live.
extern "C" int32_t recovered_005f20b5(u32 self, u32 argument) {
    void* const allocated = fun_005cc96d(0x1000);
    if (allocated)
        FUN_00405c90(allocated, 16, 256, reinterpret_cast<uintptr_t>(&FUN_004441b0));
    put(self + 0x38, reinterpret_cast<uintptr_t>(allocated));
    if (!allocated)
        return static_cast<int32_t>(0x8007000eu);
    const u32 descriptor = word(argument);
    if (word(descriptor + 0x50)) {
        __asm__ volatile("flds %0" ::"m"(dat_006be1d0) : "st", "memory");
        u32 input = 0, output = 0;
        do {
            put(argument, byte(word(descriptor + 0x50) + input));
            u32 buffer = word(self + 0x38);
            input += 4;
            scaled(argument, buffer + output);
            put(argument, byte(word(descriptor + 0x50) + input - 3));
            buffer = word(self + 0x38);
            output += 16;
            scaled(argument, buffer + output - 12);
            put(argument, byte(word(descriptor + 0x50) + input - 2));
            buffer = word(self + 0x38);
            scaled(argument, buffer + output - 8);
            put(argument, byte(word(descriptor + 0x50) + input - 1));
            buffer = word(self + 0x38);
            scaled(argument, buffer + output - 4);
        } while (input < 1024);
        __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
    } else {
        u32 output = 0;
        do {
            one(word(self + 0x38) + output + 12);
            one(word(self + 0x38) + output + 8);
            one(word(self + 0x38) + output + 4);
            one(word(self + 0x38) + output);
            output += 16;
        } while (output < 4096);
    }
    return 0;
}
extern "C" __attribute__((naked, thiscall)) int32_t FUN_005f20b5(void*, void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f20b5\n\taddl $8,%esp\n\tretl $4");
}
