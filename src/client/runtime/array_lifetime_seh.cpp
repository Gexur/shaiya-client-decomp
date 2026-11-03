#include "array_lifetime.h"
#include "cxx_exception.h"
#include <windows.h>

namespace {
// Original005CDC8D is the parent-frame SEH filter of005CDC5E, not a
// separately counted procedure. It tests only the exception-code DWORD.
int array_unwind_filter(uint32_t code) {
    if (code == 0xe06d7363u)
        fun_005d292f();
    return EXCEPTION_CONTINUE_SEARCH;
}
} // namespace

extern "C" void __attribute__((stdcall)) fun_005cdc5e(void* current, uint32_t element_size,
                                                      int32_t remaining,
                                                      OriginalElementCallback destructor) {
    uint32_t cursor = reinterpret_cast<uint32_t>(current);
    __try {
        for (;;) {
            remaining = static_cast<int32_t>(static_cast<uint32_t>(remaining) - 1u);
            if (remaining < 0)
                break;
            cursor -= element_size;
            destructor(reinterpret_cast<void*>(cursor));
        }
    } __except (array_unwind_filter(GetExceptionCode())) {
        // The original handler is unreachable for the shipped filter:
        // foreign exceptions continue search and C++ exceptions terminate.
    }
}

extern "C" void __attribute__((stdcall)) fun_005cdcbc(void* first, uint32_t element_size,
                                                      int32_t count,
                                                      OriginalElementCallback destructor) {
    uint32_t cursor =
        reinterpret_cast<uint32_t>(first) + element_size * static_cast<uint32_t>(count);
    bool complete = false;
    __try {
        for (;;) {
            count = static_cast<int32_t>(static_cast<uint32_t>(count) - 1u);
            if (count < 0)
                break;
            cursor -= element_size;
            destructor(reinterpret_cast<void*>(cursor));
        }
        complete = true;
    } __finally {
        if (!complete)
            fun_005cdc5e(reinterpret_cast<void*>(cursor), element_size, count, destructor);
    }
}

extern "C" void __attribute__((stdcall)) fun_005ce6bb(void* first, uint32_t element_size,
                                                      int32_t count,
                                                      OriginalElementCallback constructor,
                                                      OriginalElementCallback destructor) {
    uint32_t cursor = reinterpret_cast<uint32_t>(first);
    int32_t constructed = 0;
    bool complete = false;
    __try {
        while (constructed < count) {
            constructor(reinterpret_cast<void*>(cursor));
            cursor += element_size;
            constructed = static_cast<int32_t>(static_cast<uint32_t>(constructed) + 1u);
        }
        complete = true;
    } __finally {
        if (!complete)
            fun_005cdc5e(reinterpret_cast<void*>(cursor), element_size, constructed, destructor);
    }
}
