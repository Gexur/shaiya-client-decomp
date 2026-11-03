#include "x87_convert64.h"
// Complete original5d0bc4..5d0beb. Hardware FISTP retains real masked-invalid
// and overflow behavior; C++ floating-to-integer UB is never used.
extern "C" __attribute__((naked)) uint64_t FUN_005d0bc4() {
    __asm__ volatile("pushl %ebp\n\tmovl %esp,%ebp\n\taddl $-12,%esp\n\t"
                     "fwait\n\tfnstcw -2(%ebp)\n\tfwait\n\t"
                     "movw -2(%ebp),%ax\n\torb $12,%ah\n\tmovw %ax,-4(%ebp)\n\t"
                     "fldcw -4(%ebp)\n\tfistpq -12(%ebp)\n\tfldcw -2(%ebp)\n\t"
                     "movl -12(%ebp),%eax\n\tmovl -8(%ebp),%edx\n\tleave\n\tretl");
}
