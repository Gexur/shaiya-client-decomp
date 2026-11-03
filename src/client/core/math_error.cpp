#include "core/math_error.h"
#include "runtime/locks.h"
#include "runtime/security.h"

extern "C" {
OriginalMathErrorCallback dat_0070ec00 = FUN_005decbe; // Original .data005decbe pointer.
extern const char s_006d6cb0[8] = "atan";
extern const char s_006d6cb8[8] = "ceil";
extern const char s_006d6cc0[8] = "floor";
extern const char s_006d6cc8[8] = "modf";
extern const char s_006d6cd0[8] = "exp2";
extern const char s_006d6cd8[8] = "exp10";
extern const char s_006d6ce0[8] = "log2";
extern const char s_006d6ce8[4] = "pow";
extern const char s_006d6cec[4] = "log";
extern const char s_006d6cf0[8] = "log10";
extern const char s_006d6cf8[4] = "exp";
}
namespace {
inline void copy_double(double* destination, const double* source) {
    // Original FLD/FSTP can quiet signaling NaNs and set x87 exceptions;
    // a byte memcpy would lose those actual semantics.
    __asm__ __volatile__("fldl %1\n\tfstpl %0"
                         : "=m"(*destination)
                         : "m"(*source)
                         : "st", "memory");
}
} // namespace

// Original005decbe..005decc1 is exactly XOR EAX,EAX; RET. This is the genuine
// default callback body from the binary, not a fabricated error handler.
extern "C" int32_t __cdecl FUN_005decbe(PowerMathException*) {
    return 0;
}

// Original005d7bd8..005d7e4f, all observed code selectors including unknowns.
extern "C" void __cdecl FUN_005d7bd8(double* first, double* second, double* output, uint32_t code) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    const char* name;
    uint32_t kind;
    uint32_t error = 0;
    bool first_to_output = false;
    switch (code) {
    case 2:
        name = s_006d6cec;
        kind = 2;
        error = 0x22;
        break;
    case 3:
        name = s_006d6cec;
        kind = 1;
        error = 0x21;
        break;
    case 8:
        name = s_006d6cf0;
        kind = 2;
        error = 0x22;
        break;
    case 9:
        name = s_006d6cf0;
        kind = 1;
        error = 0x21;
        break;
    case 14:
        name = s_006d6cf8;
        kind = 3;
        error = 0x22;
        break;
    case 15:
        name = s_006d6cf8;
        kind = 4;
        break;
    case 24:
        name = s_006d6ce8;
        kind = 3;
        error = 0x22;
        break;
    case 25:
        name = s_006d6ce8;
        kind = 4;
        break;
    case 26:
        __asm__ __volatile__("fld1\n\tfstpl %0" : "=m"(*output)::"st", "memory");
        fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
        return;
    case 27:
        name = s_006d6ce8;
        kind = 2;
        error = 0x22;
        break;
    case 28:
        name = s_006d6ce8;
        kind = 1;
        error = 0x21;
        break;
    case 29:
        name = s_006d6ce8;
        kind = 1;
        error = 0x21;
        first_to_output = true;
        break;
    case 161:
        name = s_006d6cd0;
        kind = 3;
        error = 0x22;
        break;
    case 162:
        name = s_006d6cd0;
        kind = 4;
        error = 0x22;
        break;
    case 166:
        name = s_006d6cd8;
        kind = 3;
        error = 0x22;
        break;
    case 170:
        name = s_006d6ce0;
        kind = 2;
        error = 0x22;
        break;
    case 171:
        name = s_006d6ce0;
        kind = 1;
        error = 0x21;
        break;
    case 1000:
        name = s_006d6cec;
        kind = 1;
        error = 0x21;
        first_to_output = true;
        break;
    case 1001:
        name = s_006d6cf0;
        kind = 1;
        error = 0x21;
        first_to_output = true;
        break;
    case 1002:
        name = s_006d6cf8;
        kind = 1;
        error = 0x21;
        first_to_output = true;
        break;
    case 1003:
        name = s_006d6cb0;
        kind = 1;
        error = 0x21;
        first_to_output = true;
        break;
    case 1004:
        name = s_006d6cb8;
        kind = 1;
        error = 0x21;
        first_to_output = true;
        break;
    case 1005:
        name = s_006d6cc0;
        kind = 1;
        error = 0x21;
        first_to_output = true;
        break;
    case 1006:
        name = s_006d6ce8;
        kind = 1;
        error = 0x21;
        break;
    case 1007:
        name = s_006d6cc8;
        kind = 1;
        error = 0x21;
        first_to_output = true;
        break;
    default:
        fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
        return;
    }
    // The initial output write must precede both argument loads: output may
    // alias either caller input, just as in original005d7e08/005d7e0c.
    if (first_to_output)
        copy_double(output, first);
    PowerMathException record;
    record.kind = kind;
    record.name = name;
    copy_double(&record.argument0, first);
    copy_double(&record.argument1, second);
    copy_double(&record.result, output);
    const int32_t handled = dat_0070ec00(&record);
    if (error != 0 && handled == 0)
        *fun_005d589a() = static_cast<int32_t>(error);
    copy_double(output, &record.result);
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
}
