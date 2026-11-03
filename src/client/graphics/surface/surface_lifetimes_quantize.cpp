#include "graphics/surface/surface_lifetimes.h"
#include "graphics/render_project_unproject.h"
#include "graphics/surface/surface_block_quantize.h"
#include "graphics/surface/surface_basic_readers.h"
#include "graphics/surface/surface_write_rgb24.h"
extern "C" const uint32_t dat_006bc894;
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
u32 quantize(u32 component, u32 scale, u32 inverse, u32 temporary, u32 integer, u32 copy,
             bool scale_first = false) {
    const u32 first = scale_first ? scale : component, second = scale_first ? component : scale;
    __asm__ volatile(
        "flds (%0)\n\tfmuls (%1)\n\tfadds %4\n\tfstps (%2)\n\tflds (%2)\n\tfistpl (%3)" ::"r"(
            first),
        "r"(second), "r"(temporary), "r"(integer), "m"(dat_006bc860[0])
        : "st", "memory");
    const u32 result = word(integer);
    put(copy, result);
    __asm__ volatile("fildl (%0)\n\tfmuls (%1)\n\tfstps (%2)" ::"r"(copy), "r"(inverse),
                     "r"(component)
                     : "st", "memory");
    return result;
}
} // namespace
// Complete005f1cc8..005f1daa. Preserve the actual F32 spill before each
// FISTP and each copied integer in the original8B private region. Rounding
// follows incoming x87 control; no C++ float-to-int conversion is substituted.
extern "C" u32 recovered_005f1cc8(u32 self, u32 frame) {
    const u32 format = word(self + 4);
    if (format == 0x32545844u || format == 0x33545844u)
        __asm__ volatile("flds %0" ::"m"(dat_006bc894) : "st", "memory");
    else
        __asm__ volatile("flds %0" ::"m"(dat_006bc8c4) : "st", "memory");
    __asm__ volatile(
        "fsts 128(%0)\n\tfld1\n\tfdiv %%st(1),%%st(0)\n\tfstps 132(%0)\n\tfstp %%st(0)" ::"r"(self)
        : "st", "st(1)", "memory");
    quantize(self + 0x24, reinterpret_cast<uintptr_t>(&dat_006c651c),
             reinterpret_cast<uintptr_t>(&dat_006c4be8), frame + 4, frame, frame);
    quantize(self + 0x28, reinterpret_cast<uintptr_t>(&dat_006df408),
             reinterpret_cast<uintptr_t>(&dat_006df404), frame, frame + 4, frame);
    quantize(self + 0x2c, reinterpret_cast<uintptr_t>(&dat_006c651c),
             reinterpret_cast<uintptr_t>(&dat_006c4be8), frame, frame + 4, frame);
    return quantize(self + 0x30, self + 0x80, self + 0x84, frame, frame + 4, frame, true);
}
extern "C" __attribute__((naked, thiscall)) void FUN_005f1cc8(void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl %ecx\n\tpushl %ecx\n\tleal -8(%ebp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f1cc8\n\taddl $8,%esp\n\tleave\n\tretl");
}
