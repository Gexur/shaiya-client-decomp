#include "graphics/render_geometry_dispatch.h"
#include "startup/math_dispatch_state.h"

// Original005e7611..005e7637: both wrappers initialize the actual shared
// selector, restore the caller EBP and tail-dispatch through canonical table
// slots70/71. No argument is captured before the selector. The caller words,
// return address, volatile registers and selected callee return stay intact.
// Assembly expresses only the evidenced private forwarding ABI.
extern "C" __attribute__((naked, stdcall)) void FUN_005e7611(uint32_t, uint32_t, uint32_t, uint32_t,
                                                             uint32_t, uint32_t, uint32_t, uint32_t,
                                                             uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+280");
}
extern "C" __attribute__((naked, stdcall)) void
FUN_005e7624(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+284");
}
