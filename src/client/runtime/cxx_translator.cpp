#include "cxx_dispatch.h"

// The original translator installs a40-byte registration containing its exact
// savedESP/EBP, and its guard can resume inside that still-active registration.
// These architecture-specific bridges preserve that nonlocal ABI with textual
// instructions and relocated symbols; no original image/code bytes are used.
extern "C" __attribute__((naked)) int32_t fun_005cca75(OriginalExceptionRecord*, CxxRegistration*,
                                                       void*, void*, CxxFuncInfo*, int32_t, void*) {
    __asm__ __volatile__(
        "pushl %ebp\n\tmovl %esp, %ebp\n\tsubl $0x34, %esp\n\tpushl %ebx\n\t"
        "cmpl $0x123, 8(%ebp)\n\tjne 1f\n\tmovl $2f, %eax\n\tmovl 12(%ebp), %ecx\n\t"
        "movl %eax, (%ecx)\n\txorl %eax, %eax\n\tincl %eax\n\tjmp 5f\n\t"
        "1:\n\tandl $0, -0x28(%ebp)\n\tmovl $_fun_005ccb3c, -0x24(%ebp)\n\t"
        "movl _dat_0070e4ec, %eax\n\tmovl %eax, -0x20(%ebp)\n\tmovl 24(%ebp), %eax\n\t"
        "movl %eax, -0x1c(%ebp)\n\tmovl 12(%ebp), %eax\n\tmovl %eax, -0x18(%ebp)\n\t"
        "movl 28(%ebp), %eax\n\tmovl %eax, -0x14(%ebp)\n\tmovl 32(%ebp), %eax\n\t"
        "movl %eax, -0x10(%ebp)\n\tandl $0, -0xc(%ebp)\n\tandl $0, -8(%ebp)\n\t"
        "andl $0, -4(%ebp)\n\tmovl %esp, -0xc(%ebp)\n\tmovl %ebp, -8(%ebp)\n\t"
        "movl %fs:0, %eax\n\tmovl %eax, -0x28(%ebp)\n\tleal -0x28(%ebp), %eax\n\t"
        "movl %eax, %fs:0\n\tmovl $1, -0x34(%ebp)\n\tmovl 8(%ebp), %eax\n\t"
        "movl %eax, -0x30(%ebp)\n\tmovl 16(%ebp), %eax\n\tmovl %eax, -0x2c(%ebp)\n\t"
        "leal -0x30(%ebp), %eax\n\tpushl %eax\n\tmovl 8(%ebp), %eax\n\tpushl (%eax)\n\t"
        "calll _fun_005d2659\n\tcalll *0x74(%eax)\n\tpopl %ecx\n\tpopl %ecx\n\tandl $0, -0x34(%ebp)\n\t"
        "2:\n\tcmpl $0, -4(%ebp)\n\tje 3f\n\tmovl %fs:0, %ebx\n\tmovl (%ebx), %eax\n\t"
        "movl -0x28(%ebp), %ebx\n\tmovl %eax, (%ebx)\n\tmovl %ebx, %fs:0\n\tjmp 4f\n\t"
        "3:\n\tmovl -0x28(%ebp), %eax\n\tmovl %eax, %fs:0\n\t4:\n\tmovl -0x34(%ebp), %eax\n\t"
        "5:\n\tpopl %ebx\n\tleave\n\tretl\n\t");
}

// A C++ statement of the original guard's dispatch decisions. Its outer bridge
// keepsESI/EDI untouched and supplies the original translator-resume operation.
extern "C" int32_t recovered_cxx_translator_guard(OriginalExceptionRecord* exception,
                                                  CxxTranslatorGuard* guard, void* context, void*) {
    if (guard->cookie != dat_0070e4ec) {
        exception->flags |= 8;
        return 1;
    }
    if ((exception->flags & 0x66) != 0) {
        guard->unwinding = 1;
        return 1;
    }
    fun_005d257e(exception, guard->frame, context, nullptr, guard->information, guard->catch_depth,
                 guard->guard_frame, 1);
    if (guard->unwinding == 0)
        fun_005cc9b2(guard, exception);
    return 0;
}

extern "C" __attribute__((naked)) int32_t fun_005ccb3c(OriginalExceptionRecord*,
                                                       CxxTranslatorGuard*, void*, void*) {
    __asm__ __volatile__(
        "pushl %ebp\n\tmovl %esp, %ebp\n\tpushl %ecx\n\tpushl %ebx\n\tcld\n\t"
        "pushl 20(%ebp)\n\tpushl 16(%ebp)\n\tpushl 12(%ebp)\n\tpushl 8(%ebp)\n\t"
        "calll _recovered_cxx_translator_guard\n\taddl $16, %esp\n\ttestl %eax, %eax\n\tjne 1f\n\t"
        "pushl $0\n\tpushl $0\n\tpushl $0\n\tpushl $0\n\tpushl $0\n\tleal -4(%ebp), %eax\n\t"
        "pushl %eax\n\tpushl $0x123\n\tcalll _fun_005cca75\n\taddl $28, %esp\n\t"
        "movl -4(%ebp), %eax\n\tmovl 12(%ebp), %ebx\n\tmovl 0x1c(%ebx), %esp\n\t"
        "movl 0x20(%ebx), %ebp\n\tjmpl *%eax\n\t1:\n\tpopl %ebx\n\tleave\n\tretl\n\t");
}
