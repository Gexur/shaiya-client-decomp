#include "core/float_classify.h"
extern "C" int32_t __cdecl FUN_005ced05(double value) {
    uint32_t words[2];
    __builtin_memcpy(words, &value, 8);
    return (words[1] & 0x7ff00000u) != 0x7ff00000u;
}
