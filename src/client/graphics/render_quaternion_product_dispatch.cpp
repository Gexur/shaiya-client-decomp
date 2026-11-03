#include "graphics/render_quaternion_product_dispatch.h"
#include "startup/math_dispatch_state.h"
// Original5e6a51..5e6a64 initializes before any incoming word is read, then
// tail-jumps through actual slot20. All three actual caller slots survive.
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6a51(void*, const void*, const void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+80");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6a64(void*, const void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+80");
}
