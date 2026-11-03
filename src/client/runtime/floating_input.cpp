#include "floating_parse.h"
#include "../core/extended96_convert.h"
extern "C" int32_t fun_005dcc7b(void* binary64, const char* input) {
    OriginalExtended96 value;
    const char* end;
    fun_005decd2(&value, &end, input, 0, 0, 0, 0);
    return fun_005dcc4f(&value, binary64);
}
extern "C" int32_t fun_005dccc0(void* binary32, const char* input) {
    OriginalExtended96 value;
    const char* end;
    fun_005decd2(&value, &end, input, 0, 0, 0, 0);
    return fun_005dcc65(&value, binary32);
}
extern "C" void* fun_005d2bbd(int32_t binary64, void* output, const char* input) {
    if (binary64) {
        uint32_t value[2];
        fun_005dcc7b(value, input);
        auto* result = static_cast<uint32_t*>(output);
        result[0] = value[0];
        result[1] = value[1];
    } else {
        fun_005dccc0(&binary64, input);
        *static_cast<uint32_t*>(output) = uint32_t(binary64);
    }
    return output;
}
