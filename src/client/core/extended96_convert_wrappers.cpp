#include "extended96_convert.h"
#include "extended96_mantissa.h"
#include "../runtime/runtime_error.h"
extern "C" int32_t fun_005dcc4f(const OriginalExtended96* source, void* destination) {
    return fun_005dcaf7(source, destination, &dat_0070ee30.conversion_formats[0]);
}
extern "C" int32_t fun_005dcc65(const OriginalExtended96* source, void* destination) {
    return fun_005dcaf7(source, destination, &dat_0070ee30.conversion_formats[1]);
}
