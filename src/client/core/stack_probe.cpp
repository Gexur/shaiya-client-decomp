// 0x5cd2a0..0x5cd2dc: original x86 stack-allocation/probe ABI.
// EAX supplies the byte count. This routine changes its caller's ESP, preserves
// ECX, touches each stack page, and returns with EAX containing its return PC.
// A naked ABI routine is necessary: ordinary C++ cannot assign the caller's ESP.
// These are explicit instruction mnemonics from the original, not byte arrays.
extern "C" __attribute__((naked)) void fun_005cd2a0() {
    __asm__ __volatile__("cmpl $0x1000, %eax\n\t"
                         "jae 1f\n\t"
                         "negl %eax\n\t"
                         "addl %esp, %eax\n\t"
                         "addl $4, %eax\n\t"
                         "testl %eax, (%eax)\n\t"
                         "xchgl %eax, %esp\n\t"
                         "movl (%eax), %eax\n\t"
                         "pushl %eax\n\t"
                         "retl\n\t"
                         "1:\n\t"
                         "pushl %ecx\n\t"
                         "leal 8(%esp), %ecx\n\t"
                         "2:\n\t"
                         "subl $0x1000, %ecx\n\t"
                         "subl $0x1000, %eax\n\t"
                         "testl %eax, (%ecx)\n\t"
                         "cmpl $0x1000, %eax\n\t"
                         "jae 2b\n\t"
                         "subl %eax, %ecx\n\t"
                         "movl %esp, %eax\n\t"
                         "testl %eax, (%ecx)\n\t"
                         "movl %ecx, %esp\n\t"
                         "movl (%eax), %ecx\n\t"
                         "movl 4(%eax), %eax\n\t"
                         "pushl %eax\n\t"
                         "retl\n\t");
}

// Clang's x86 Windows __alloca helper uses the same EAX/ESP contract. This
// source alias supplies that compiler ABI using the recovered routine.
extern "C" void _alloca() __attribute__((alias("fun_005cd2a0")));
// The MSVC x86 target spells that same probe contract __chkstk. Its emitted
// reference is the C-decorated form of _chkstk, not the x64 probe-only ABI.
extern "C" void _chkstk() __attribute__((alias("fun_005cd2a0")));
