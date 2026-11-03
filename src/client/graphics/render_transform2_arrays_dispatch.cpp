#include "graphics/render_transform2_arrays_dispatch.h"
#include "startup/math_dispatch_state.h"
extern "C" __attribute__((naked, stdcall)) void* FUN_005e3fd9(void*, uint32_t, const void*,
                                                              uint32_t, const void*, uint32_t) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmp _FUN_005e3fe6@24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e3fe6(void*, uint32_t, const void*,
                                                              uint32_t, const void*, uint32_t) {
    __asm__ volatile("jmpl *_dat_0070f370+240");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e4005(void*, uint32_t, const void*,
                                                              uint32_t, const void*, uint32_t) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmp _FUN_005e4012@24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e4012(void*, uint32_t, const void*,
                                                              uint32_t, const void*, uint32_t) {
    __asm__ volatile("jmpl *_dat_0070f370+244");
}
