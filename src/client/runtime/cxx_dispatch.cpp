#include "cxx_dispatch.h"
#include "thread_data.h"

extern "C" {
__declspec(dllimport) void __attribute__((stdcall)) RtlUnwind(void*, void*,
                                                              OriginalExceptionRecord*, void*);
__declspec(dllimport) void __attribute__((stdcall)) RaiseException(uint32_t, uint32_t, uint32_t,
                                                                   const uint32_t*);
}

namespace {
template <class T> T& thread_field(void* data, uint32_t offset) {
    return *reinterpret_cast<T*>(static_cast<uint8_t*>(data) + offset);
}
bool is_cpp_exception(const OriginalExceptionRecord* exception) {
    return exception->code == 0xe06d7363u && exception->parameter_count == 3 &&
           (exception->parameters[0] == 0x19930520u || exception->parameters[0] == 0x19930521u);
}
const char* type_name(const void* header) {
    return static_cast<const char*>(header) + 8;
}
} // namespace

extern "C" void fun_005d237a(OriginalExceptionRecord* exception, CxxRegistration* frame,
                             void* context, void* dispatcher_context, CxxFuncInfo* information,
                             uint32_t recursive, int32_t catch_depth, void* guard_frame) {
    const int32_t state = frame->state;
    if (state < -1 || state >= information->maximum_state)
        fun_005d2964();
    if (exception->code == 0xe06d7363u) {
        if (is_cpp_exception(exception) && exception->parameters[2] == 0) {
            if (thread_field<OriginalExceptionRecord*>(fun_005d2659(), 0x7c) == nullptr)
                return;
            exception = thread_field<OriginalExceptionRecord*>(fun_005d2659(), 0x7c);
            context = thread_field<void*>(fun_005d2659(), 0x80);
            if (fun_005dc907(exception, 1) == 0)
                fun_005d2964();
            if (exception->code != 0xe06d7363u)
                goto foreign;
            if (is_cpp_exception(exception) && exception->parameters[2] == 0)
                fun_005d2964();
        }
        if (is_cpp_exception(exception)) {
            uint32_t first, end;
            CxxTryBlock* block = fun_005ccbee(information, catch_depth, state, &first, &end);
            while (first < end) {
                if (block->try_low <= state && state <= block->try_high) {
                    CxxHandlerType* handler = block->handlers;
                    for (int32_t catches = block->catch_count; catches > 0; --catches, ++handler) {
                        CxxThrowInfo* thrown =
                            reinterpret_cast<CxxThrowInfo*>(exception->parameters[2]);
                        CxxCatchableTypes* types = thrown->catchable_types;
                        CxxCatchableType** entry = &types->first;
                        for (int32_t available = types->count; available > 0;
                             --available, ++entry) {
                            CxxCatchableType* candidate = *entry;
                            if (fun_005d1d76(handler, candidate, thrown) != 0) {
                                fun_005d2255(exception, frame, context, dispatcher_context,
                                             information, handler, candidate, block, catch_depth,
                                             guard_frame);
                                goto next_try;
                            }
                        }
                    }
                }
            next_try:
                ++first;
                ++block;
            }
            if (uint8_t(recursive) != 0)
                fun_005d1eb1(exception, 1);
            return;
        }
    }
foreign:
    if (uint8_t(recursive) == 0)
        fun_005d22bc(exception, frame, context, dispatcher_context, information, state, catch_depth,
                     guard_frame);
    else
        fun_005d292f();
}

extern "C" void fun_005d22bc(OriginalExceptionRecord* exception, CxxRegistration* frame,
                             void* context, void* dispatcher_context, CxxFuncInfo* information,
                             int32_t state, int32_t catch_depth, void* guard_frame) {
    if (exception->code == 0x80000003u)
        return;
    if (thread_field<void*>(fun_005d2659(), 0x74) != nullptr &&
        fun_005cca75(exception, frame, context, dispatcher_context, information, catch_depth,
                     guard_frame) != 0)
        return;
    uint32_t first, end;
    CxxTryBlock* block = fun_005ccbee(information, catch_depth, state, &first, &end);
    while (first < end) {
        if (block->try_low <= state && state <= block->try_high) {
            CxxHandlerType* handler = block->handlers + block->catch_count - 1;
            if (handler->type_header == nullptr || *type_name(handler->type_header) == '\0')
                fun_005d2255(exception, frame, context, dispatcher_context, information, handler,
                             nullptr, block, catch_depth, guard_frame);
        }
        ++first;
        ++block;
    }
}

extern "C" void fun_005d2255(OriginalExceptionRecord* exception, CxxRegistration* frame,
                             void* context, void* dispatcher_context, CxxFuncInfo* information,
                             CxxHandlerType* handler, CxxCatchableType* catchable,
                             CxxTryBlock* block, int32_t catch_depth, void* guard_frame) {
    if (catchable != nullptr)
        fun_005d20d9(exception, frame, handler, catchable);
    fun_005cc9b2(guard_frame == nullptr ? static_cast<void*>(frame) : guard_frame, exception);
    fun_005d1de3(frame, dispatcher_context, information, block->try_low);
    frame->state = block->try_high + 1;
    void* continuation =
        fun_005d1f15(exception, frame, context, information, handler->handler, catch_depth, 0x100);
    if (continuation != nullptr)
        fun_005cc97b(continuation, frame);
}

extern "C" __attribute__((naked, stdcall)) void fun_005cc9b2(void*, OriginalExceptionRecord*) {
    __asm__ __volatile__(
        "pushl %ebp\n\tmovl %esp, %ebp\n\tpushl %ecx\n\tpushl %ecx\n\tpushl %ebx\n\tpushl %esi\n\tpushl %edi\n\t"
        "movl %fs:0, %esi\n\tmovl %esi, -4(%ebp)\n\tmovl $1f, -8(%ebp)\n\t"
        "pushl $0\n\tpushl 12(%ebp)\n\tpushl -8(%ebp)\n\tpushl 8(%ebp)\n\tcalll *__imp__RtlUnwind@16\n\t"
        "1:\n\tmovl 12(%ebp), %eax\n\tmovl 4(%eax), %eax\n\tandl $0xfffffffd, %eax\n\t"
        "movl 12(%ebp), %ecx\n\tmovl %eax, 4(%ecx)\n\tmovl %fs:0, %edi\n\tmovl -4(%ebp), %ebx\n\t"
        "movl %edi, (%ebx)\n\tmovl %ebx, %fs:0\n\tpopl %edi\n\tpopl %esi\n\tpopl %ebx\n\tleave\n\tretl $8\n\t");
}

extern "C" __attribute__((naked, stdcall, noreturn)) void fun_005cc97b(void*, CxxRegistration*) {
    __asm__ __volatile__(
        "pushl %ebp\n\tmovl %esp, %ebp\n\tpushl %ecx\n\tpushl %ebx\n\tmovl 12(%ebp), %eax\n\t"
        "addl $12, %eax\n\tmovl %eax, -4(%ebp)\n\tmovl %fs:0, %ebx\n\tmovl (%ebx), %eax\n\t"
        "movl %eax, %fs:0\n\tmovl 8(%ebp), %eax\n\tmovl 12(%ebp), %ebx\n\tmovl -4(%ebx), %esp\n\t"
        "movl -4(%ebp), %ebp\n\tjmpl *%eax\n\t");
}

//005CC9AB's same original pop/thiscall/tail-jump operation supports targets
// with additional callee-popped arguments. These typed ABI adapters are not
// additional recovered original procedures.
extern "C" __attribute__((naked, stdcall)) void recovered_cxx_member1(void*, void*, void*) {
    __asm__ __volatile__("popl %eax\n\tpopl %ecx\n\txchgl %eax, (%esp)\n\tjmpl *%eax\n\t");
}
extern "C" __attribute__((naked, stdcall)) void recovered_cxx_member2(void*, void*, void*,
                                                                      uint32_t) {
    __asm__ __volatile__("popl %eax\n\tpopl %ecx\n\txchgl %eax, (%esp)\n\tjmpl *%eax\n\t");
}

extern "C" __attribute__((stdcall)) void fun_005cce46(void* object, CxxThrowInfo* information) {
    const uint32_t arguments[3] = {0x19930520u, reinterpret_cast<uint32_t>(object),
                                   reinterpret_cast<uint32_t>(information)};
    RaiseException(0xe06d7363u, 1, 3, arguments);
}
