#include "graphics/render_matrix_rotations.h"
#include "startup/math_dispatch_state.h"
// Original599c..59bf; distinct shared fast599bf..59c5,slot43@70f41c.
extern "C" __attribute__((naked, stdcall)) void* FUN_005e599c(void*, const void*, uint32_t) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tflds 16(%ebp)\n\tpushl %ecx\n\tfstps (%esp)\n\tpushl 12(%ebp)\n\tpushl 8(%ebp)\n\tcalll *_dat_0070f370+172\n\tpopl %ebp\n\tretl $12");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e59bf(void*, const void*, uint32_t) {
    __asm__ volatile("jmp *_dat_0070f370+172");
}
// Original5ac6..5ad9 performs real selection then tails with original arguments.
extern "C" __attribute__((naked, stdcall)) void* FUN_005e5ac6(void*, const void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmp *_dat_0070f370+156");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e5ad9(void*, const void*) {
    __asm__ volatile("jmp *_dat_0070f370+156");
}
// Original5bc3..5bf3 has one entry only; its final5bef bytes are epilogue,
// not another callable fast entry. Copies retain actual roll/pitch/yaw order.
extern "C" __attribute__((naked, stdcall)) void* FUN_005e5bc3(void*, uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tflds 20(%ebp)\n\tsubl $12,%esp\n\tfstps 8(%esp)\n\tflds 16(%ebp)\n\tfstps 4(%esp)\n\tflds 12(%ebp)\n\tfstps (%esp)\n\tpushl 8(%ebp)\n\tcalll *_dat_0070f370+164\n\tpopl %ebp\n\tretl $16");
}
