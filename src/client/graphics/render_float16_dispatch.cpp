#include "graphics/render_float16_dispatch.h"
#include "startup/math_dispatch_state.h"

// Original5e3c1d..5e3c30 and5e3cd8..5e3ceb. The initializer runs before
// any argument is read. The final jump retains the actual caller slots: both
// integer conversion loops reread those slots during their iterations.
extern "C" __attribute__((naked, stdcall)) void* FUN_005e3c1d(void*, const void*, uint32_t) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+232");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e3cd8(void*, const void*, uint32_t) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+236");
}
// The two adjacent original six-byte fast entries contain only these jumps.
extern "C" __attribute__((naked, stdcall)) void* FUN_005e3c30(void*, const void*, uint32_t) {
    __asm__ volatile("jmpl *_dat_0070f370+232");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e3ceb(void*, const void*, uint32_t) {
    __asm__ volatile("jmpl *_dat_0070f370+236");
}
