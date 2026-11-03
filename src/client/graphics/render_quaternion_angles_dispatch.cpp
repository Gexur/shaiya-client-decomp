#include "graphics/render_quaternion_angles_dispatch.h"
#include "startup/math_dispatch_state.h"
// Original6940..6970 copies all three F32angles after initialization, reading
// actual incoming roll,pitch,yaw then output pointer before the mutable call.
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6940(void*, uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tflds 20(%ebp)\n\tsubl $12,%esp\n\tfstps 8(%esp)\n\tflds 16(%ebp)\n\tfstps 4(%esp)\n\tflds 12(%ebp)\n\tfstps (%esp)\n\tpushl 8(%ebp)\n\tcalll *_dat_0070f370+104\n\tpopl %ebp\n\tretl $16");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6970(void*, uint32_t, uint32_t, uint32_t) {
    __asm__ volatile("jmpl *_dat_0070f370+104");
}
