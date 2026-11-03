#include "bigint_allocator.h"

// Original 0x589550/0x589580 and 0x58b410/0x58b450: fatal arithmetic
// and assertion helpers. Underlying CRT formatting and abort remain external.
extern "C" {
uint32_t dat_02242318 = 0;
int32_t dat_02253290 = 0;
extern const volatile int32_t dat_006cd65c = 0;
}

// Original00589550 computes this OR before its signed divide, but stores both
// globals only after the divide. The immutable original divisor is zero, causing
// x86 divide exception0 before either store. C++ division by zero has undefined
// behavior; these two original mnemonics preserve the actual architecture event.
// No machine-code bytes or fixed-address access is embedded here.
extern "C" [[noreturn]] void fun_00589550(uint32_t flags) {
    const uint32_t combined = dat_02242318 | flags;
    int32_t quotient = 10;
    int32_t remainder;
    __asm__ __volatile__("cltd\n\tidivl %2"
                         : "+a"(quotient), "=&d"(remainder)
                         : "m"(dat_006cd65c)
                         : "cc", "memory");
    dat_02242318 = combined;
    dat_02253290 = quotient;
    fun_005d0ba9();
}

extern "C" [[noreturn]] void fun_00589580() {
    fun_00589550(2);
}

extern "C" void fun_0058b410(const char* file, int32_t line) {
    if (file != nullptr && file[0] != '\0') {
        fun_005cdb8c(&dat_0070e280, "%s:", file);
        if (line != -1)
            fun_005cdb8c(&dat_0070e280, "%d: ", line);
    }
}

extern "C" void fun_0058b450(const char* file, int32_t line, const char* expression) {
    fun_0058b410(file, line);
    fun_005cdb8c(&dat_0070e280, "GNU MP assertion failed: %s\n", expression);
    fun_005d0ba9();
}
