#include "cxx_exception.h"
#include "thread_data.h"

extern "C" void* _exception_info();
extern "C" [[noreturn]] void fun_005d0ba9();
extern "C" void (*dat_0070e4f8)() = fun_005d292f;

namespace {
uint32_t& unwind_counter(void* data) {
    return *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(data) + 0x84);
}
using TerminateCallback = void (*)();
TerminateCallback& terminate_callback(void* data) {
    return *reinterpret_cast<TerminateCallback*>(static_cast<uint8_t*>(data) + 0x6c);
}
} // namespace

extern "C" void fun_005d1de3(CxxRegistration* frame, void* /*dispatcher_context*/,
                             CxxFuncInfo* information, int32_t target_state) {
    int32_t current = frame->state;
    ++unwind_counter(fun_005d2659());
    __try {
        while (current != target_state) {
            if (current <= -1 || current >= information->maximum_state)
                fun_005d2964();
            const int32_t previous = current;
            CxxUnwindEntry* entry = information->unwind_map + previous;
            current = entry->enclosing_state;
            __try {
                if (entry->action != nullptr) {
                    frame->state = current;
                    fun_005d29a0(information->unwind_map[previous].action, frame, 0x103);
                }
            } __except (fun_005d1dc5(static_cast<OriginalExceptionPointers*>(_exception_info()))) {
                // The original filter terminates for C++ exceptions and returns
                // CONTINUE_SEARCH otherwise; its retained handler rejoins here.
            }
        }
    } __finally {
        fun_005d1e96();
    }
    if (current != target_state)
        fun_005d2964();
    frame->state = current;
}

extern "C" void fun_005d1eb1(OriginalExceptionRecord* exception, uint32_t terminate_on_exception) {
    if (exception != nullptr) {
        CxxThrowInfo* thrown = reinterpret_cast<CxxThrowInfo*>(exception->parameters[2]);
        if (thrown->unwind_function != nullptr) {
            __try {
                fun_005cc9ab(reinterpret_cast<void*>(exception->parameters[1]),
                             thrown->unwind_function);
            } __except (uint8_t(terminate_on_exception) != 0) {
                fun_005d292f();
            }
        }
    }
}

extern "C" [[noreturn]] void fun_005d292f() {
    if (terminate_callback(fun_005d2659()) != nullptr) {
        __try {
            terminate_callback(fun_005d2659())();
        } __except (1) {
        }
    }
    fun_005d0ba9();
}

extern "C" [[noreturn]] void fun_005d2964() {
    if (dat_0070e4f8 != nullptr) {
        __try {
            dat_0070e4f8();
        } __except (1) {
        }
    }
    fun_005d292f();
}
