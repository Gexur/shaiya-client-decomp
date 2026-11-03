#include "descriptor_io.h"
#include "thread_data.h"

extern "C" {
__declspec(dllimport) void __attribute__((stdcall)) EnterCriticalSection(OriginalCriticalSection*);
__declspec(dllimport) int32_t __attribute__((stdcall)) FlushFileBuffers(void*);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetLastError();
}

extern "C" int32_t fun_005d5c59(int32_t descriptor) {
    auto* entry = original_io_entry(descriptor);
    if (!entry->section_initialized) {
        fun_005d659b(10);
        bool ready = true;
        __try {
            if (!entry->section_initialized) {
                if (!fun_005de970(&entry->section, 4000))
                    ready = false;
                else
                    ++entry->section_initialized;
            }
        } __finally {
            fun_005d5cf0();
        }
        if (!ready)
            return 0;
    }
    EnterCriticalSection(&original_io_entry(descriptor)->section);
    return 1;
}
extern "C" void fun_005cd5db(int32_t descriptor) {
    fun_005d5cf9(descriptor);
}
extern "C" void fun_005d0ea5(int32_t descriptor) {
    fun_005d5cf9(descriptor);
}
extern "C" void fun_005da56f(int32_t descriptor) {
    fun_005d5cf9(descriptor);
}

extern "C" int32_t fun_005cd564(int32_t descriptor) {
    if (uint32_t(descriptor) < uint32_t(dat_022532d4) &&
        (original_io_entry(descriptor)->flags & 1u)) {
        // The original ignores a zero return from this lazy lock initializer.
        fun_005d5c59(descriptor);
        int32_t result;
        __try {
            if (original_io_entry(descriptor)->flags & 1u)
                result = fun_005cd4e1(descriptor);
            else {
                *fun_005d589a() = 9;
                result = -1;
            }
        } __finally {
            fun_005cd5db(descriptor);
        }
        return result;
    }
    *fun_005d589a() = 9;
    *fun_005d58a3() = 0;
    return -1;
}
extern "C" int32_t fun_005d0e1e(int32_t descriptor, const void* buffer, uint32_t count) {
    if (uint32_t(descriptor) < uint32_t(dat_022532d4) &&
        (original_io_entry(descriptor)->flags & 1u)) {
        fun_005d5c59(descriptor);
        int32_t result;
        __try {
            if (original_io_entry(descriptor)->flags & 1u)
                result = fun_005d0c62(descriptor, static_cast<const char*>(buffer), count);
            else {
                *fun_005d589a() = 9;
                *fun_005d58a3() = 0;
                result = -1;
            }
        } __finally {
            fun_005d0ea5(descriptor);
        }
        return result;
    }
    *fun_005d589a() = 9;
    *fun_005d58a3() = 0;
    return -1;
}
extern "C" int32_t fun_005da4cf(int32_t descriptor) {
    if (uint32_t(descriptor) >= uint32_t(dat_022532d4) ||
        !(original_io_entry(descriptor)->flags & 1u)) {
        *fun_005d589a() = 9;
        return -1;
    }
    fun_005d5c59(descriptor);
    int32_t result;
    __try {
        result = 0;
        bool failed = !(original_io_entry(descriptor)->flags & 1u);
        if (!failed) {
            const int32_t handle = fun_005d5c18(descriptor);
            if (!FlushFileBuffers(reinterpret_cast<void*>(handle)))
                result = int32_t(GetLastError());
            if (result) {
                *fun_005d58a3() = uint32_t(result);
                failed = true;
            }
        }
        if (failed) {
            *fun_005d589a() = 9;
            result = -1;
        }
    } __finally {
        fun_005da56f(descriptor);
    }
    return result;
}
