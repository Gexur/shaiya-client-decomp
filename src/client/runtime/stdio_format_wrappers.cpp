#include "stdio_format.h"
namespace {
int32_t format_buffer(char* output, uint32_t capacity, const char* format, const void* arguments) {
    OriginalFile file;
    file.count = int32_t(capacity);
    file.flags = 0x42;
    file.base = output;
    file.cursor = output;
    const int32_t result = fun_005d36e4(&file, format, arguments);
    if (output) {
        file.count = int32_t(uint32_t(file.count) - 1);
        if (file.count < 0)
            fun_005d353d(0, &file);
        else
            *file.cursor = 0;
    }
    return result;
}
} // namespace
extern "C" int32_t fun_005ceb39(char* output, const char* format, const void* argument_words) {
    return format_buffer(output, 0x7fffffff, format, argument_words);
}
extern "C" int32_t fun_005d139d(char* output, uint32_t capacity, const char* format,
                                const void* argument_words) {
    return format_buffer(output, capacity, format, argument_words);
}
extern "C" int32_t fun_005cd489(char* output, const char* format, ...) {
    __builtin_va_list arguments;
    __builtin_va_start(arguments, format);
    const int32_t result = format_buffer(output, 0x7fffffff, format, arguments);
    __builtin_va_end(arguments);
    return result;
}
extern "C" int32_t fun_005cd214(char* output, uint32_t capacity, const char* format, ...) {
    __builtin_va_list arguments;
    __builtin_va_start(arguments, format);
    const int32_t result = format_buffer(output, capacity, format, arguments);
    __builtin_va_end(arguments);
    return result;
}
extern "C" int32_t sprintf(char* output, const char* format, ...) {
    __builtin_va_list arguments;
    __builtin_va_start(arguments, format);
    const int32_t result = fun_005ceb39(output, format, arguments);
    __builtin_va_end(arguments);
    return result;
}
extern "C" int32_t vsprintf(char* output, const char* format, __builtin_va_list arguments) {
    return fun_005ceb39(output, format, arguments);
}
extern "C" int32_t _snprintf(char* output, uint32_t capacity, const char* format, ...) {
    __builtin_va_list arguments;
    __builtin_va_start(arguments, format);
    const int32_t result = fun_005d139d(output, capacity, format, arguments);
    __builtin_va_end(arguments);
    return result;
}
extern "C" int32_t _vsnprintf(char* output, uint32_t capacity, const char* format,
                              __builtin_va_list arguments) {
    return fun_005d139d(output, capacity, format, arguments);
}
extern "C" void fun_005cdbe0(OriginalFile* file) {
    fun_005d01b8(file);
}
extern "C" int32_t FUN_005cd489(char*, const char*, ...) __attribute__((alias("fun_005cd489")));
