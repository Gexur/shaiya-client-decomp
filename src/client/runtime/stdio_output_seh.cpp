#include "stdio_output.h"
extern "C" uint32_t fun_005d05a1(const void* buffer, uint32_t size, uint32_t count,
                                 OriginalFile* file) {
    fun_005d0166(file);
    uint32_t result;
    __try {
        result = fun_005d049a(buffer, size, count, file);
    } __finally {
        fun_005d05e3(file);
    }
    return result;
}
