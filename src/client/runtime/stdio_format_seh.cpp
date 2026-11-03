#include "stdio_format.h"
extern "C" int32_t fun_005cdb8c(OriginalFile* file, const char* format, ...) {
    __builtin_va_list arguments;
    __builtin_va_start(arguments, format);
    fun_005d0166(file);
    int32_t result;
    __try {
        const int32_t temporary = fun_005d6007(file);
        result = fun_005d36e4(file, format, arguments);
        fun_005d608f(temporary, file);
    } __finally {
        fun_005cdbe0(file);
    }
    __builtin_va_end(arguments);
    return result;
}
