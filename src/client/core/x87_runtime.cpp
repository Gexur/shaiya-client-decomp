#include "core/x87_runtime.h"

extern "C" {
uint32_t dat_022532cc = 0;
// Actual unresolved math kernels, retaining their private x87/EAX contracts.
void __cdecl FUN_005d068d();
void __cdecl FUN_005da930();
}

// Original5cd414..5cd488. A standard C++ parameter cannot denote incoming ST0.
// These are its actual instruction mnemonics, not copied instruction bytes.
// Its FISTP/rounding correction (including exceptional values) is preserved.
extern "C" __attribute__((naked)) uint64_t __cdecl FUN_005cd414() {
    __asm__ __volatile__("pushl %ebp\n\t"
                         "movl %esp,%ebp\n\t"
                         "subl $0x20,%esp\n\t"
                         "andl $-16,%esp\n\t"
                         "fld %st(0)\n\t"
                         "fsts 0x18(%esp)\n\t"
                         "fistpq 0x10(%esp)\n\t"
                         "fildq 0x10(%esp)\n\t"
                         "movl 0x18(%esp),%edx\n\t"
                         "movl 0x10(%esp),%eax\n\t"
                         "testl %eax,%eax\n\t"
                         "jz 3f\n\t"
                         "1:\n\t"
                         // LLVM/GNU AT&T spelling is reversed here: this emits DE E9,
                         // original Intel FSUBP ST(1),ST(0), never DE E1 FSUBRP.
                         "fsubrp %st(0),%st(1)\n\t"
                         "testl %edx,%edx\n\t"
                         "jns 2f\n\t"
                         "fstps (%esp)\n\t"
                         "movl (%esp),%ecx\n\t"
                         "xorl $0x80000000,%ecx\n\t"
                         "addl $0x7fffffff,%ecx\n\t"
                         "adcl $0,%eax\n\t"
                         "movl 0x14(%esp),%edx\n\t"
                         "adcl $0,%edx\n\t"
                         "jmp 4f\n\t"
                         "2:\n\t"
                         "fstps (%esp)\n\t"
                         "movl (%esp),%ecx\n\t"
                         "addl $0x7fffffff,%ecx\n\t"
                         "sbbl $0,%eax\n\t"
                         "movl 0x14(%esp),%edx\n\t"
                         "sbbl $0,%edx\n\t"
                         "jmp 4f\n\t"
                         "3:\n\t"
                         "movl 0x14(%esp),%edx\n\t"
                         "testl $0x7fffffff,%edx\n\t"
                         "jnz 1b\n\t"
                         "fstps 0x18(%esp)\n\t"
                         "fstps 0x18(%esp)\n\t"
                         "4:\n\t"
                         "leave\n\t"
                         "retl\n\t");
}

// Original5d0630..5d0683 selector/wrapper. Actual5d068d also receives EAX as
// the exponent-high DWORD and retains exponent in ST0 after the stack stores.
extern "C" __attribute__((naked)) void __cdecl FUN_005d0630() {
    __asm__ __volatile__("cmpl $0,_dat_022532cc\n\t"
                         "je 2f\n\t"
                         "subl $8,%esp\n\t"
                         "stmxcsr 4(%esp)\n\t"
                         "movl 4(%esp),%eax\n\t"
                         "andl $0x1f80,%eax\n\t"
                         "cmpl $0x1f80,%eax\n\t"
                         "jne 1f\n\t"
                         "fnstcw (%esp)\n\t"
                         "movw (%esp),%ax\n\t"
                         "andw $0x7f,%ax\n\t"
                         "cmpw $0x7f,%ax\n\t"
                         "1:\n\t"
                         "leal 8(%esp),%esp\n\t"
                         "jne 2f\n\t"
                         "jmp _FUN_005da930\n\t"
                         "2:\n\t"
                         "subl $0x14,%esp\n\t"
                         "fxch %st(1)\n\t"
                         "fstpl (%esp)\n\t"
                         "fstl 8(%esp)\n\t"
                         "movl 0xc(%esp),%eax\n\t"
                         "call _FUN_005d068d\n\t"
                         "addl $0x14,%esp\n\t"
                         "retl\n\t");
}

extern "C" uint64_t __cdecl x87_to_integer_005cd414(long double value) {
    uint32_t low, high;
    __asm__ __volatile__("fldt %2\n\tcall _FUN_005cd414"
                         : "=a"(low), "=d"(high)
                         : "m"(value)
                         : "ecx", "st", "cc", "memory");
    return uint64_t(low) | (uint64_t(high) << 32);
}
extern "C" long double __cdecl x87_power_005d0630(long double base, long double exponent) {
    long double result;
    __asm__ __volatile__("fldt %1\n\tfldt %2\n\tcall _FUN_005d0630"
                         : "=t"(result)
                         : "m"(base), "m"(exponent)
                         : "eax", "ecx", "edx", "st(1)", "cc", "memory");
    return result;
}
