#include "file_ops.h"
extern "C" void fun_005cd70b(int32_t descriptor) {
    fun_005d5cf9(descriptor);
}
extern "C" int32_t fun_005cd684(int32_t descriptor, int32_t offset, int32_t origin) {
    if (uint32_t(descriptor) < uint32_t(dat_022532d4) && (file_io_entry(descriptor)->flags & 1u)) {
        fun_005d5c59(descriptor);
        int32_t result;
        __try {
            if (file_io_entry(descriptor)->flags & 1u)
                result = fun_005cd610(descriptor, offset, origin);
            else {
                *fun_005d589a() = 9;
                *fun_005d58a3() = 0;
                result = -1;
            }
        } __finally {
            fun_005cd70b(descriptor);
        }
        return result;
    }
    *fun_005d589a() = 9;
    *fun_005d58a3() = 0;
    return -1;
}
