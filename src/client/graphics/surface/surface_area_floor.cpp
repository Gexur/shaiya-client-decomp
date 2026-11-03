#include "graphics/surface/surface_area_weights.h"
// Complete24-byte original5ec9e8..5eca00. The actual6aa710 floor family is a
// genuine external dependency; this ABI-only wrapper contains no floor model.
extern "C" __attribute__((naked, stdcall)) long double FUN_005ec9e8(uint32_t) {
    __asm__ volatile("movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\t"
                     "flds 8(%ebp)\n\tpushl %ecx\n\tpushl %ecx\n\tfstpl (%esp)\n\t"
                     "calll _FUN_006aa710\n\tpopl %ecx\n\tpopl %ecx\n\tpopl %ebp\n\tretl $4");
}
