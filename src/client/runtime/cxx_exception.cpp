#include "cxx_exception.h"
#include "thread_data.h"

namespace {
CxxFrameInfo*& active_frames(void* per_thread_data) {
    return *reinterpret_cast<CxxFrameInfo**>(static_cast<uint8_t*>(per_thread_data) + 0x88);
}
const char* type_name(const void* header) {
    return static_cast<const char*>(header) + 8;
}
void* exception_chain() {
    void* result;
    __asm__ __volatile__("movl %%fs:0, %0" : "=r"(result) : : "memory");
    return result;
}
void set_exception_chain(void* value) {
    __asm__ __volatile__("movl %0, %%fs:0" : : "r"(value) : "memory");
}
} // namespace

extern "C" int32_t fun_005d1d76(const CxxHandlerType* handler, const CxxCatchableType* catchable,
                                const CxxThrowInfo* thrown) {
    if (handler->type_header != nullptr && *type_name(handler->type_header) != '\0') {
        if (handler->type_header != catchable->type_header &&
            fun_005d65d0(type_name(handler->type_header), type_name(catchable->type_header)) != 0)
            return 0;
        if ((catchable->properties & 2) != 0 && (handler->adjectives & 8) == 0)
            return 0;
        if ((thrown->attributes & 1) != 0 && (handler->adjectives & 1) == 0)
            return 0;
        if ((thrown->attributes & 2) != 0 && (handler->adjectives & 2) == 0)
            return 0;
    }
    return 1;
}

extern "C" CxxTryBlock* fun_005ccbee(const CxxFuncInfo* information, int32_t catch_depth,
                                     int32_t state, uint32_t* first, uint32_t* end) {
    uint32_t index = information->try_count;
    uint32_t checkpoint = index;
    uint32_t upper = index;
    while (catch_depth >= 0) {
        if (index == 0xffffffffu)
            fun_005d2964();
        --index;
        const volatile CxxTryBlock* candidate = information->try_map + int32_t(index);
        if ((candidate->try_high < state && state <= candidate->catch_high) ||
            index == 0xffffffffu) {
            --catch_depth;
            upper = checkpoint;
            checkpoint = index;
        }
    }
    ++index;
    *first = index;
    *end = upper;
    if (upper > information->try_count || index > upper)
        fun_005d2964();
    return information->try_map + index;
}

extern "C" CxxFrameInfo* fun_005ccc68(CxxFrameInfo* frame, void* object) {
    frame->object = object;
    frame->next = active_frames(fun_005d2659());
    active_frames(fun_005d2659()) = frame;
    return frame;
}
extern "C" int32_t fun_005ccc90(void* object) {
    CxxFrameInfo* frame = active_frames(fun_005d2659());
    for (;;) {
        if (frame == nullptr)
            return 1;
        if (frame->object == object)
            return 0;
        frame = frame->next;
    }
}
extern "C" void fun_005cccb1(CxxFrameInfo* frame) {
    if (frame == active_frames(fun_005d2659())) {
        active_frames(fun_005d2659()) = frame->next;
        return;
    }
    CxxFrameInfo* previous = active_frames(fun_005d2659());
    for (;;) {
        if (previous->next == nullptr)
            fun_005d2964();
        if (previous->next == frame)
            break;
        previous = previous->next;
    }
    previous->next = frame->next;
}

extern "C" void fun_005d1e96() {
    if (*reinterpret_cast<int32_t*>(static_cast<uint8_t*>(fun_005d2659()) + 0x84) > 0)
        --*reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(fun_005d2659()) + 0x84);
}

extern "C" void* fun_005d1ef6(void* object, const CxxPointerDisplacement* displacement) {
    const uint32_t base = reinterpret_cast<uint32_t>(object);
    uint32_t result = base + uint32_t(displacement->member);
    if (displacement->vbtable >= 0) {
        const uint32_t table =
            *reinterpret_cast<const uint32_t*>(base + uint32_t(displacement->vbtable));
        const uint32_t delta =
            *reinterpret_cast<const uint32_t*>(table + uint32_t(displacement->vbase));
        result += delta + uint32_t(displacement->vbtable);
    }
    return reinterpret_cast<void*>(result);
}

extern "C" int32_t fun_005d1dc5(OriginalExceptionPointers* pointers) {
    if (pointers->record->code != 0xe06d7363u)
        return 0;
    *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(fun_005d2659()) + 0x84) = 0;
    fun_005d292f();
}

extern "C" void* fun_005cccfd(CxxRegistration* frame, CxxFuncInfo* information, void* handler,
                              int32_t catch_depth, uint32_t code) {
    CxxCatchGuard guard = {
        exception_chain(), reinterpret_cast<void*>(fun_005cca3a), dat_0070e4ec, information, frame,
        catch_depth + 1};
    set_exception_chain(&guard);
    void* result = fun_005d29a0(handler, frame, code);
    set_exception_chain(guard.previous);
    return result;
}

extern "C" __attribute__((naked, stdcall)) void fun_005cc9ab(void*, void*) {
    __asm__ __volatile__("popl %eax\n\tpopl %ecx\n\txchgl %eax, (%esp)\n\tjmpl *%eax\n\t");
}

extern "C" int32_t fun_005d257e(OriginalExceptionRecord* exception, CxxRegistration* frame,
                                void* context, void* dispatcher_context, CxxFuncInfo* information,
                                int32_t catch_depth, void* guard_frame, uint32_t recursive) {
    if ((information->magic_and_flags & 0x1fffffffu) != 0x19930520u)
        fun_005d2964();
    if ((exception->flags & 0x66) != 0) {
        if (information->maximum_state != 0 && catch_depth == 0)
            fun_005d1de3(frame, dispatcher_context, information, -1);
    } else if (information->try_count != 0) {
        if (exception->code == 0xe06d7363u && exception->parameters[0] > 0x19930520u) {
            CxxThrowInfo* thrown = reinterpret_cast<CxxThrowInfo*>(exception->parameters[2]);
            if (thrown->forward_handler != nullptr)
                return thrown->forward_handler(exception, frame, context, dispatcher_context,
                                               information, catch_depth, guard_frame,
                                               uint8_t(recursive));
        }
        fun_005d237a(exception, frame, context, dispatcher_context, information, recursive,
                     catch_depth, guard_frame);
    }
    return 1;
}

extern "C" __attribute__((naked)) int32_t fun_005cca04(OriginalExceptionRecord*, CxxRegistration*,
                                                       void*, void*) {
    __asm__ __volatile__("pushl %ebp\n\tmovl %esp, %ebp\n\tcld\n\t"
                         "pushl $0\n\tpushl $0\n\tpushl $0\n\tpushl %eax\n\t"
                         "pushl 20(%ebp)\n\tpushl 16(%ebp)\n\tpushl 12(%ebp)\n\tpushl 8(%ebp)\n\t"
                         "calll _fun_005d257e\n\taddl $32, %esp\n\tleave\n\tretl\n\t");
}

extern "C" int32_t fun_005cca3a(OriginalExceptionRecord* exception, CxxCatchGuard* guard,
                                void* context, void*) {
    if (guard->cookie != dat_0070e4ec) {
        exception->flags |= 8;
        return 1;
    }
    return fun_005d257e(exception, guard->frame, context, nullptr, guard->information,
                        guard->catch_depth, guard, 0);
}

// This original bridge sets a funclet's enclosing EBP, preserves the original
// callee-save convention, issues both real NLG notifications and returnsRET12.
extern "C" __attribute__((naked, stdcall)) void* fun_005d29a0(void*, CxxRegistration*, uint32_t) {
    __asm__ __volatile__(
        "pushl %ebp\n\tmovl %esp, %ebp\n\tsubl $4, %esp\n\tpushl %ebx\n\tpushl %ecx\n\t"
        "movl 12(%ebp), %eax\n\taddl $12, %eax\n\tmovl %eax, -4(%ebp)\n\t"
        "movl 8(%ebp), %eax\n\tpushl %ebp\n\tpushl 16(%ebp)\n\tmovl 16(%ebp), %ecx\n\t"
        "movl -4(%ebp), %ebp\n\tcalll _fun_005cce25\n\tpushl %esi\n\tpushl %edi\n\t"
        "calll *%eax\n\tpopl %edi\n\tpopl %esi\n\tmovl %ebp, %ebx\n\tpopl %ebp\n\t"
        "movl 16(%ebp), %ecx\n\tpushl %ebp\n\tmovl %ebx, %ebp\n\t"
        "cmpl $0x100, %ecx\n\tjne 1f\n\tmovl $2, %ecx\n\t1:\n\tpushl %ecx\n\t"
        "calll _fun_005cce25\n\tpopl %ebp\n\tpopl %ecx\n\tpopl %ebx\n\tleave\n\tretl $12\n\t");
}
