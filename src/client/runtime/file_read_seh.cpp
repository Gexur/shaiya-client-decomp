#include "file_ops.h"
extern "C" void fun_005ce5c4(int32_t descriptor) {
    fun_005d5cf9(descriptor);
}
extern "C" int32_t fun_005ce53d(int32_t descriptor, void* buffer, uint32_t count) {
    if (uint32_t(descriptor) < uint32_t(dat_022532d4) && (file_io_entry(descriptor)->flags & 1u)) {
        fun_005d5c59(descriptor);
        int32_t result;
        __try {
            if (file_io_entry(descriptor)->flags & 1u)
                result = fun_005ce360(descriptor, static_cast<char*>(buffer), count);
            else {
                *fun_005d589a() = 9;
                *fun_005d58a3() = 0;
                result = -1;
            }
        } __finally {
            fun_005ce5c4(descriptor);
        }
        return result;
    }
    *fun_005d589a() = 9;
    *fun_005d58a3() = 0;
    return -1;
}
