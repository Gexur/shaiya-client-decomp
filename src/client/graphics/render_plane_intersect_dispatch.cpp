#include "graphics/render_plane_intersect_dispatch.h"
#include "startup/math_dispatch_state.h"
extern "C" __attribute__((naked, stdcall)) void* FUN_005e704a(void*, const void*, const void*,
                                                              const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmp _FUN_005e7057@16");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e7057(void*, const void*, const void*,
                                                              const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+92");
}
