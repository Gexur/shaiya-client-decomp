#include "graphics/render_quaternion_from_matrix_dispatch.h"
#include "startup/math_dispatch_state.h"
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6770(void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+100");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6783(void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+100");
}
