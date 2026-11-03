#include "x87_acos.h"

extern "C" {
extern char s_0070e170[5] = "acos";
extern const uint64_t dat_006d6b90 = UINT64_C(0x3ff0000000000000);
}

// Complete original005ce5f0..005ce604; actual private machine contract.
extern "C" __attribute__((naked)) void __cdecl FUN_005ce5f0() {
    __asm__ volatile("subl $0xc, %esp\n\t"
                     "fstl (%esp)\n\t"
                     "calll _FUN_005d6a78\n\t"
                     "calll _FUN_005ce60d\n\t"
                     "addl $0xc, %esp\n\t"
                     "retl \n\t");
}

// Complete original005ce604..005ce6bb; actual private machine contract.
extern "C" __attribute__((naked)) long double __cdecl FUN_005ce604(double) {
    __asm__ volatile("leal 4(%esp), %edx\n\t"
                     "calll _FUN_005d6a35\n\t"
                     ".globl _FUN_005ce60d\n\t"
                     "_FUN_005ce60d:\n\t"
                     "acos_005ce60d:\n\t"
                     "pushl %edx\n\t"
                     "wait \n\t"
                     "fnstcw (%esp)\n\t"
                     "je acos_005ce681\n\t"
                     "cmpw $0x27f, (%esp)\n\t"
                     "je acos_005ce621\n\t"
                     "calll _FUN_005d6a05\n\t"
                     "acos_005ce621:\n\t"
                     "cmpl $0x3ff00000, %eax\n\t"
                     "jae acos_005ce655\n\t"
                     "fld1 \n\t"
                     "fadd %st(1)\n\t"
                     "fld1 \n\t"
                     "fsub %st(2)\n\t"
                     "fmulp %st(1)\n\t"
                     "fsqrt \n\t"
                     "fxch %st(1)\n\t"
                     "fpatan \n\t"
                     "acos_005ce638:\n\t"
                     "cmpl $0, _dat_0224eddc\n\t"
                     "jne _FUN_005d6a8e\n\t"
                     "movl $0xd, %edx\n\t"
                     "leal _s_0070e170, %ecx\n\t"
                     "jmp _FUN_005d6a9b\n\t"
                     "acos_005ce655:\n\t"
                     "ja acos_005ce68f\n\t"
                     "movl 0xc(%esp), %eax\n\t"
                     "movl %eax, %ecx\n\t"
                     "andl $0xfffff, %eax\n\t"
                     "orl 8(%esp), %eax\n\t"
                     "jne acos_005ce68f\n\t"
                     "andl $0x80000000, %ecx\n\t"
                     "fstp %st(0)\n\t"
                     "je acos_005ce676\n\t"
                     "fldpi \n\t"
                     "jmp acos_005ce638\n\t"
                     "acos_005ce676:\n\t"
                     "fldz \n\t"
                     "jmp acos_005ce638\n\t"
                     "acos_005ce67a:\n\t"
                     "calll _FUN_005d6a1c\n\t"
                     "jmp acos_005ce69c\n\t"
                     "acos_005ce681:\n\t"
                     "testl $0xfffff, %eax\n\t"
                     "jne acos_005ce67a\n\t"
                     "cmpl $0, 8(%esp)\n\t"
                     "jne acos_005ce67a\n\t"
                     "acos_005ce68f:\n\t"
                     "fstp %st(0)\n\t"
                     "fldt _dat_0070eab0\n\t"
                     "movl $1, %eax\n\t"
                     "acos_005ce69c:\n\t"
                     "cmpl $0, _dat_0224eddc\n\t"
                     "jne _FUN_005d6a8e\n\t"
                     "movl $0xd, %edx\n\t"
                     "leal _s_0070e170, %ecx\n\t"
                     "calll _FUN_005d69a7\n\t"
                     "popl %edx\n\t"
                     "retl \n\t");
}

// Complete original005d6a1c..005d6a35; actual private machine contract.
extern "C" __attribute__((naked)) void __cdecl FUN_005d6a1c() {
    __asm__ volatile("testl $0x80000, %eax\n\t"
                     "je acos_005d6a29\n\t"
                     "movl $7, %eax\n\t"
                     "retl \n\t"
                     "acos_005d6a29:\n\t"
                     "faddl _dat_006d6b90\n\t"
                     "movl $1, %eax\n\t"
                     "retl \n\t");
}

// Complete original005d6a78..005d6a8e; actual private machine contract.
extern "C" __attribute__((naked)) void __cdecl FUN_005d6a78() {
    __asm__ volatile("movl 8(%esp), %eax\n\t"
                     "andl $0x7ff00000, %eax\n\t"
                     "cmpl $0x7ff00000, %eax\n\t"
                     "je acos_005d6a89\n\t"
                     "retl \n\t"
                     "acos_005d6a89:\n\t"
                     "movl 8(%esp), %eax\n\t"
                     "retl \n\t");
}

// Complete original005d6a9b..005d6ac5; actual private machine contract.
extern "C" __attribute__((naked)) void __cdecl FUN_005d6a9b() {
    __asm__ volatile("movw (%esp), %ax\n\t"
                     "cmpw $0x27f, %ax\n\t"
                     "je acos_005d6ac3\n\t"
                     "andw $0x20, %ax\n\t"
                     "je acos_005d6ac0\n\t"
                     "wait \n\t"
                     "fnstsw %ax\n\t"
                     "andw $0x20, %ax\n\t"
                     "je acos_005d6ac0\n\t"
                     "movl $8, %eax\n\t"
                     "calll _FUN_005d69a7\n\t"
                     "popl %edx\n\t"
                     "retl \n\t"
                     "acos_005d6ac0:\n\t"
                     "fldcw (%esp)\n\t"
                     "acos_005d6ac3:\n\t"
                     "popl %edx\n\t"
                     "retl \n\t");
}
