#include "uint64_divide.h"

namespace {
struct DivisionWords {
    uint32_t quotient, remainder;
};

DivisionWords divide_words(uint32_t high, uint32_t low, uint32_t divisor) {
    DivisionWords result;
    // Original DIV ECX / DIV EBX. An explicit DIV keeps the original #DE on
    // zero instead of expressing C++ division-by-zero undefined behavior.
    __asm__ __volatile__("divl %4"
                         : "=a"(result.quotient), "=d"(result.remainder)
                         : "0"(low), "1"(high), "rm"(divisor)
                         : "cc");
    return result;
}
} // namespace

// Original 0x5d7b70..0x5d7bd7 (__aulldiv). Two-word normalization, tentative
// quotient, multiply/check and one-word correction are taken from its original
// instructions. No uint64 division expression or replacement math is used.
extern "C" uint64_t __attribute__((stdcall, noinline)) fun_005d7b70(uint32_t dividend_low,
                                                                    uint32_t dividend_high,
                                                                    uint32_t divisor_low,
                                                                    uint32_t divisor_high) {
    if (divisor_high == 0) {
        const DivisionWords upper = divide_words(0, dividend_high, divisor_low);
        const DivisionWords lower = divide_words(upper.remainder, dividend_low, divisor_low);
        return (uint64_t(upper.quotient) << 32) | lower.quotient;
    }

    uint32_t shifted_divisor_high = divisor_high;
    uint32_t shifted_divisor_low = divisor_low;
    uint32_t shifted_dividend_high = dividend_high;
    uint32_t shifted_dividend_low = dividend_low;
    do {
        shifted_divisor_low = (shifted_divisor_low >> 1) | (shifted_divisor_high << 31);
        shifted_divisor_high >>= 1;
        shifted_dividend_low = (shifted_dividend_low >> 1) | (shifted_dividend_high << 31);
        shifted_dividend_high >>= 1;
    } while (shifted_divisor_high != 0);

    uint32_t quotient =
        divide_words(shifted_dividend_high, shifted_dividend_low, shifted_divisor_low).quotient;
    const uint32_t upper_product = quotient * divisor_high;
    const uint64_t lower_product = uint64_t(divisor_low) * quotient;
    const uint32_t lower_product_high = uint32_t(lower_product >> 32);
    const uint32_t combined_high = lower_product_high + upper_product;
    if (combined_high < upper_product || combined_high > dividend_high ||
        (combined_high == dividend_high && uint32_t(lower_product) > dividend_low)) {
        --quotient;
    }
    return uint64_t(quotient);
}

extern "C" uint64_t __attribute__((cdecl)) __udivdi3(uint64_t dividend, uint64_t divisor) {
    return fun_005d7b70(uint32_t(dividend), uint32_t(dividend >> 32), uint32_t(divisor),
                        uint32_t(divisor >> 32));
}
