#include "cxx_dispatch.h"
#include "thread_data.h"
#include "../core/memory.h"

extern "C" void* _exception_info();

namespace {
template <class T> T& thread_field(void* data, uint32_t offset) {
    return *reinterpret_cast<T*>(static_cast<uint8_t*>(data) + offset);
}
bool is_cpp_exception(const OriginalExceptionRecord* exception) {
    return exception->code == 0xe06d7363u && exception->parameter_count == 3 &&
           (exception->parameters[0] == 0x19930520u || exception->parameters[0] == 0x19930521u);
}
bool is_rethrow(OriginalExceptionPointers* pointers) {
    return is_cpp_exception(pointers->record) && pointers->record->parameters[2] == 0;
}
} // namespace

extern "C" void fun_005d20d9(OriginalExceptionRecord* exception, void* frame_or_destination,
                             const CxxHandlerType* handler, const CxxCatchableType* catchable) {
    if (handler->type_header == nullptr ||
        *(static_cast<const char*>(handler->type_header) + 8) == '\0')
        return;
    if (handler->catch_object_displacement == 0 && (handler->adjectives & 0x80000000u) == 0)
        return;
    uint8_t* destination = static_cast<uint8_t*>(frame_or_destination);
    if (int32_t(handler->adjectives) >= 0)
        destination += handler->catch_object_displacement + 12;
    void* object = reinterpret_cast<void*>(exception->parameters[1]);
    __try {
        if ((handler->adjectives & 8) != 0) {
            if (fun_005dc907(object, 1) == 0 || fun_005dc923(destination, 1) == 0)
                fun_005d2964();
            *reinterpret_cast<void**>(destination) = object;
            *reinterpret_cast<void**>(destination) = fun_005d1ef6(object, &catchable->displacement);
        } else if ((catchable->properties & 1) != 0) {
            if (fun_005dc907(object, 1) == 0 || fun_005dc923(destination, 1) == 0)
                fun_005d2964();
            fun_005cc630(destination, object, uint32_t(catchable->size_or_offset));
            if (catchable->size_or_offset == 4 && *reinterpret_cast<void**>(destination) != nullptr)
                *reinterpret_cast<void**>(destination) =
                    fun_005d1ef6(*reinterpret_cast<void**>(destination), &catchable->displacement);
        } else if (catchable->copy_function == nullptr) {
            if (fun_005dc907(object, 1) == 0 || fun_005dc923(destination, 1) == 0)
                fun_005d2964();
            fun_005cc630(destination, fun_005d1ef6(object, &catchable->displacement),
                         uint32_t(catchable->size_or_offset));
        } else {
            if (fun_005dc907(object, 1) == 0 || fun_005dc923(destination, 1) == 0 ||
                fun_005dc93f(catchable->copy_function) == 0)
                fun_005d2964();
            if ((catchable->properties & 4) != 0)
                recovered_cxx_member2(destination, catchable->copy_function,
                                      fun_005d1ef6(object, &catchable->displacement), 1);
            else
                recovered_cxx_member1(destination, catchable->copy_function,
                                      fun_005d1ef6(object, &catchable->displacement));
        }
    } __except (1) {
        fun_005d292f();
    }
}

extern "C" void fun_005d206a(CxxCatchCleanup* cleanup) {
    *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(cleanup->frame) - 4) =
        cleanup->saved_stack;
    fun_005cccb1(cleanup->active_frame);
    thread_field<OriginalExceptionRecord*>(fun_005d2659(), 0x7c) = cleanup->saved_exception;
    thread_field<void*>(fun_005d2659(), 0x80) = cleanup->saved_context;
    if (is_cpp_exception(cleanup->exception) && cleanup->suppress_destruction == 0 &&
        cleanup->result != nullptr &&
        fun_005ccc90(reinterpret_cast<void*>(cleanup->exception->parameters[1])) != 0)
        fun_005d1eb1(cleanup->exception, uint32_t(fun_005cce02()));
}

extern "C" void* fun_005d1f15(OriginalExceptionRecord* exception, CxxRegistration* frame,
                              void* context, CxxFuncInfo* information, void* handler,
                              int32_t catch_depth, uint32_t code) {
    CxxFrameInfo active;
    CxxCatchCleanup cleanup = {
        frame,   exception, *reinterpret_cast<void**>(reinterpret_cast<uint8_t*>(frame) - 4),
        nullptr, nullptr,   nullptr,
        handler, 0};
    cleanup.active_frame = fun_005ccc68(&active, reinterpret_cast<void*>(exception->parameters[1]));
    cleanup.saved_exception = thread_field<OriginalExceptionRecord*>(fun_005d2659(), 0x7c);
    cleanup.saved_context = thread_field<void*>(fun_005d2659(), 0x80);
    thread_field<OriginalExceptionRecord*>(fun_005d2659(), 0x7c) = exception;
    thread_field<void*>(fun_005d2659(), 0x80) = context;
    __try {
        __try {
            cleanup.result = fun_005cccfd(frame, information, handler, catch_depth, code);
        } __except (is_rethrow(static_cast<OriginalExceptionPointers*>(_exception_info()))) {
            int32_t target = frame->state;
            for (uint32_t index = 0; index < information->try_count; ++index) {
                CxxTryBlock* entry = information->try_map + index;
                if (entry->try_high < target && target <= entry->catch_high) {
                    target = information->unwind_map[entry->try_high + 1].enclosing_state;
                    break;
                }
            }
            fun_005d1de3(frame, nullptr, information, target);
            cleanup.result = nullptr;
        }
    } __finally {
        fun_005d206a(&cleanup);
    }
    return cleanup.result;
}
