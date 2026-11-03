#include "unsigned_shift_right.h"
extern "C" uint64_t recovered_006aa840(uint32_t low, uint32_t high, uint32_t* actual_count) {
    const uint32_t count = *actual_count & 0xffu;
    if (count >= 64u)
        return 0;
    if (count >= 32u) {
        const uint32_t reduced = count & 31u;
        *actual_count = (*actual_count & 0xffffff00u) | reduced;
        return static_cast<uint64_t>(high >> reduced);
    }
    const uint32_t result_low = count ? ((low >> count) | (high << (32u - count))) : low;
    const uint32_t result_high = high >> count;
    return (static_cast<uint64_t>(result_high) << 32) | result_low;
}
extern "C" __attribute__((naked)) void FUN_006aa840() {
    // The saved ECX word is a genuine private bridge input/output. PUSH ESP
    // passes its address without consuming the original EDX:EAX operands.
    __asm__ volatile(
        "pushl %ecx\n\tpushl %esp\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_006aa840\n\taddl $12,%esp\n\tpopl %ecx\n\tretl");
}
