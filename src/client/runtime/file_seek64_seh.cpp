#include "file_seek64.h"
extern "C" void fun_005ce33a(int32_t descriptor) {
    fun_005d5cf9(descriptor);
}
extern "C" int64_t fun_005ce2a2(int32_t descriptor, int64_t offset, int32_t origin) {
    if (uint32_t(descriptor) < uint32_t(dat_022532d4) && (file_io_entry(descriptor)->flags & 1)) {
        fun_005d5c59(descriptor);
        int64_t result;
        __try {
            if (file_io_entry(descriptor)->flags & 1) {
                const uint64_t bits = uint64_t(offset);
                result =
                    fun_005ce21f(descriptor, int32_t(bits), int32_t(bits >> 32), uint32_t(origin));
            } else {
                *fun_005d589a() = 9;
                *fun_005d58a3() = 0;
                result = -1;
            }
        } __finally {
            fun_005ce33a(descriptor);
        }
        return result;
    }
    *fun_005d589a() = 9;
    *fun_005d58a3() = 0;
    return -1;
}
extern "C" int64_t fun_005ce731(int32_t descriptor) {
    return fun_005ce2a2(descriptor, 0, 1);
}
extern "C" int64_t _lseeki64(int32_t, int64_t, int32_t) __attribute__((alias("fun_005ce2a2")));
extern "C" int64_t _telli64(int32_t) __attribute__((alias("fun_005ce731")));
