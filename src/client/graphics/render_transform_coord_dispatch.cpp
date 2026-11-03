#include "graphics/render_transform_coord_dispatch.h"
#include "startup/math_dispatch_state.h"
extern "C" __attribute__((naked, stdcall)) void* FUN_005e3fec(void*, const void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+36");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e3fff(void*, const void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+36");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e44be(void*, const void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+40");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e44d1(void*, const void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+40");
}
