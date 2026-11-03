#include "graphics/render_normalization_dispatch.h"
#include "startup/math_dispatch_state.h"
extern "C" __attribute__((naked, stdcall)) void* FUN_005e3d98(void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+188");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e3dab(void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+188");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6b02(void*, const void*) {
    // Original6b0f is this lazy entry's actual final instruction.
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmp _FUN_005e6b0f@8");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6b0f(void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+84");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6b15(void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+180");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6b28(void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+180");
}
