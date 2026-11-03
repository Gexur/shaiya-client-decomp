#include "runtime/stdio_scan.h"
#include "runtime/strings.h"
extern "C" int32_t fun_005cd26b(const char* input, const char* format, ...) {
    OriginalFile file;
    file.flags = 0x49;
    file.cursor = const_cast<char*>(input);
    file.base = const_cast<char*>(input);
    file.count = int32_t(fun_005d4cf0(input));
    __builtin_va_list arguments;
    __builtin_va_start(arguments, format);
    const int32_t result = fun_005d3eb6(&file, format, arguments);
    __builtin_va_end(arguments);
    return result;
}
extern "C" int32_t FUN_005cd26b(const char*, const char*, ...)
    __attribute__((alias("fun_005cd26b")));
