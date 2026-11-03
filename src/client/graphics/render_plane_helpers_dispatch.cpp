#include "graphics/render_plane_helpers_dispatch.h"
#include "startup/math_dispatch_state.h"
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6f8e(void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+88");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6fa1(void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+88");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e7161(void*, const void*, const void*,
                                                              const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+56");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e7174(void*, const void*, const void*,
                                                              const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+56");
}
