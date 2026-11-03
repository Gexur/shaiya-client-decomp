#include "exception.h"

extern "C" OriginalNlgInformation dat_0070e120 = {0x19930520u, nullptr, 0, nullptr};

static inline void* exception_chain() {
    void* chain;
    __asm__ __volatile__("movl %%fs:0, %0" : "=r"(chain) : : "memory");
    return chain;
}
static inline void set_exception_chain(void* chain) {
    __asm__ __volatile__("movl %0, %%fs:0" : : "r"(chain) : "memory");
}

// A filter/finally funclet addresses its enclosing function's stack through
// EBP. The dispatcher's filter path clears all five other general registers.
// This ABI adapter performs that architectural operation and returns EAX.
extern "C" __attribute__((naked)) int32_t recovered_seh_call_filter(void*, void*) {
    __asm__ __volatile__("pushl %ebp\n\tpushl %ebx\n\tpushl %esi\n\tpushl %edi\n\t"
                         "movl 20(%esp), %eax\n\tmovl 24(%esp), %ebp\n\t"
                         "xorl %ebx, %ebx\n\txorl %ecx, %ecx\n\txorl %edx, %edx\n\t"
                         "xorl %esi, %esi\n\txorl %edi, %edi\n\tcalll *%eax\n\t"
                         "popl %edi\n\tpopl %esi\n\tpopl %ebx\n\tpopl %ebp\n\tretl\n\t");
}

// The local-unwind finally path sets EBP but does not perform the dispatcher's
// explicit zeroing. Only that enclosing-frame ABI is supplied by this bridge.
extern "C" __attribute__((naked)) void recovered_seh_call_finally(void*, void*) {
    __asm__ __volatile__("pushl %ebp\n\t"
                         "movl 8(%esp), %eax\n\tmovl 12(%esp), %ebp\n\t"
                         "calll *%eax\n\tpopl %ebp\n\tretl\n\t");
}

extern "C" __attribute__((naked)) void fun_005cce25() {
    __asm__ __volatile__("pushl %ebx\n\tpushl %ecx\n\tmovl $_dat_0070e120, %ebx\n\t"
                         "movl %ecx, 8(%ebx)\n\tmovl %eax, 4(%ebx)\n\tmovl %ebp, 12(%ebx)\n\t"
                         "popl %ecx\n\tpopl %ebx\n\tretl $4\n\t");
}
extern "C" __attribute__((naked)) void fun_005cce2e() {
    __asm__ __volatile__("pushl %ebx\n\tpushl %ecx\n\tmovl $_dat_0070e120, %ebx\n\t"
                         "movl 8(%ebp), %ecx\n\tmovl %ecx, 8(%ebx)\n\t"
                         "movl %eax, 4(%ebx)\n\tmovl %ebp, 12(%ebx)\n\t"
                         "popl %ecx\n\tpopl %ebx\n\tretl $4\n\t");
}
extern "C" __attribute__((naked)) void recovered_seh_notify(void*, void*, uint32_t) {
    __asm__ __volatile__("pushl %ebp\n\tmovl 8(%esp), %eax\n\tmovl 12(%esp), %ebp\n\t"
                         "pushl 16(%esp)\n\tcalll _fun_005cce2e\n\tpopl %ebp\n\tretl\n\t");
}

extern "C" int32_t fun_005ccd78(OriginalExceptionRecord* exception,
                                OriginalUnwindRegistration* registration, void* /*context*/,
                                void** dispatcher_context) {
    if ((exception->flags & 6) != 0) {
        *dispatcher_context = registration;
        return 3; // ExceptionCollidedUnwind
    }
    return 1; // ExceptionContinueSearch
}

extern "C" void recovered_seh_local_unwind(OriginalExceptionRegistration* frame,
                                           int32_t target_level, void* parent_frame) {
    OriginalUnwindRegistration guard = {exception_chain(), reinterpret_cast<void*>(fun_005ccd78),
                                        -2, frame};
    set_exception_chain(&guard);
    for (;;) {
        OriginalScopeEntry* table = frame->scope_table;
        int32_t current = frame->scope_level;
        if (current == -1 || current == target_level) {
            break;
        }
        int32_t next = table[current].enclosing_level;
        guard.enclosing_level = next;
        frame->scope_level = next;
        if (table[current].filter == nullptr) {
            recovered_seh_notify(table[current].handler, parent_frame, 0x101);
            recovered_seh_call_finally(table[current].handler, parent_frame);
        }
    }
    set_exception_chain(guard.previous);
}

extern "C" __attribute__((naked)) void fun_005ccd9a(OriginalExceptionRegistration*, int32_t) {
    __asm__ __volatile__("pushl %ebp\n\tpushl 12(%esp)\n\tpushl 12(%esp)\n\t"
                         "calll _recovered_seh_local_unwind\n\taddl $12, %esp\n\tretl\n\t");
}

extern "C" int32_t fun_005cce02() {
    OriginalUnwindRegistration* guard = static_cast<OriginalUnwindRegistration*>(exception_chain());
    if (guard->dispatcher == reinterpret_cast<void*>(fun_005ccd78) &&
        guard->enclosing_level == guard->frame->scope_level) {
        return 1;
    }
    return 0;
}

// RtlUnwind resumes at this routine's local label with the saved EBP still on
// the stack. The original save/restore and TargetIp contract require a naked
// bridge; replacing them with an ordinary C++ call would use the wrong stack.
extern "C" __attribute__((naked)) void fun_005ccd58(OriginalExceptionRegistration*) {
    __asm__ __volatile__(
        "pushl %ebp\n\tmovl %esp, %ebp\n\tpushl %ebx\n\tpushl %esi\n\tpushl %edi\n\tpushl %ebp\n\t"
        "pushl $0\n\tpushl $0\n\tpushl $1f\n\tpushl 8(%ebp)\n\t"
        "calll *\"__imp__RtlUnwind@16\"\n\t"
        "1:\n\tpopl %ebp\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\t"
        "movl %ebp, %esp\n\tpopl %ebp\n\tretl\n\t");
}

extern "C" int32_t fun_005cfc4c(OriginalExceptionRecord* exception,
                                OriginalExceptionRegistration* frame, void* context,
                                void* /*dispatcher_context*/) {
    __asm__ __volatile__("cld" : : : "cc");
    void* parent_frame = reinterpret_cast<uint8_t*>(frame) + 16;
    if ((exception->flags & 6) != 0) {
        recovered_seh_local_unwind(frame, -1, parent_frame);
        return 1;
    }
    OriginalExceptionPointers pointers = {exception, context};
    *reinterpret_cast<OriginalExceptionPointers**>(reinterpret_cast<uint8_t*>(frame) - 4) =
        &pointers;
    int32_t level = frame->scope_level;
    OriginalScopeEntry* table = frame->scope_table;
    if (fun_005da2a6(frame) == 0) {
        exception->flags |= 8;
        return 1;
    }
    while (level != -1) {
        if (table[level].filter != nullptr) {
            int32_t decision = recovered_seh_call_filter(table[level].filter, parent_frame);
            if (decision < 0) {
                return 0; // ExceptionContinueExecution
            }
            if (decision != 0) {
                table = frame->scope_table;
                fun_005ccd58(frame);
                recovered_seh_local_unwind(frame, level, parent_frame);
                recovered_seh_notify(table[level].handler, parent_frame, 1);
                frame->scope_level = table[level].enclosing_level;
                // A selected handler funclet transfers control back into its
                // enclosing function, restoring that function's saved ESP.
                recovered_seh_call_filter(table[level].handler, parent_frame);
            }
        }
        table = frame->scope_table;
        level = table[level].enclosing_level;
    }
    return 1;
}

// Compiler ABI names refer to the actual recovered CRT implementations.
extern "C" int32_t _except_handler3(OriginalExceptionRecord*, OriginalExceptionRegistration*, void*,
                                    void*) __attribute__((alias("fun_005cfc4c")));
extern "C" void _local_unwind2(OriginalExceptionRegistration*, int32_t)
    __attribute__((alias("fun_005ccd9a")));
extern "C" int32_t _abnormal_termination() __attribute__((alias("fun_005cce02")));
