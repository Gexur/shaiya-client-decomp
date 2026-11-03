#include "graphics/render_matrix_determinant_dispatch.h"
#include "startup/math_dispatch_state.h"
extern "C" __attribute__((naked, stdcall)) float FUN_005e4cad(const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+44");
}
extern "C" __attribute__((naked, stdcall)) float FUN_005e4cc0(const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+44");
}
