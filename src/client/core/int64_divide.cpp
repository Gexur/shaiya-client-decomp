#include "int64_divide.h"
namespace {
struct DivisionWords {
    uint32_t quotient, remainder;
};
DivisionWords divide(uint32_t high, uint32_t low, uint32_t divisor) {
    DivisionWords result;
    __asm__ volatile("divl %4"
                     : "=a"(result.quotient), "=d"(result.remainder)
                     : "0"(low), "1"(high), "rm"(divisor)
                     : "cc");
    return result;
}
uint32_t word(const uint32_t* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void store(uint32_t* p, uint32_t v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
} // namespace
// Original 0x005ccfd0..0x005cd07a. In-place sign normalization of the actual
// four incoming words precedes the original two-word shift/DIV/correction.
extern "C" __attribute__((noinline)) uint64_t aligned_005ccfd0(uint32_t* arguments) {
    uint32_t negatives = 0;
    uint32_t dividend_high = word(arguments + 1);
    if (dividend_high & 0x80000000u) {
        ++negatives;
        const uint32_t low = word(arguments);
        dividend_high = 0u - dividend_high - (low != 0);
        store(arguments + 1, dividend_high);
        store(arguments, 0u - low);
    }
    uint32_t divisor_high = word(arguments + 3);
    if (divisor_high & 0x80000000u) {
        ++negatives;
        const uint32_t low = word(arguments + 2);
        divisor_high = 0u - divisor_high - (low != 0);
        store(arguments + 3, divisor_high);
        store(arguments + 2, 0u - low);
    }
    uint64_t quotient;
    if (divisor_high == 0) {
        const uint32_t divisor_low = word(arguments + 2);
        const DivisionWords upper = divide(0, word(arguments + 1), divisor_low);
        const DivisionWords lower = divide(upper.remainder, word(arguments), divisor_low);
        quotient = (uint64_t(upper.quotient) << 32) | lower.quotient;
    } else {
        uint32_t upper_divisor = divisor_high, lower_divisor = word(arguments + 2);
        uint32_t upper_dividend = word(arguments + 1), lower_dividend = word(arguments);
        do {
            lower_divisor = (lower_divisor >> 1) | (upper_divisor << 31);
            upper_divisor >>= 1;
            lower_dividend = (lower_dividend >> 1) | (upper_dividend << 31);
            upper_dividend >>= 1;
        } while (upper_divisor != 0);
        uint32_t q = divide(upper_dividend, lower_dividend, lower_divisor).quotient;
        const uint32_t upper_product = q * word(arguments + 3);
        const uint64_t lower_product = uint64_t(word(arguments + 2)) * q;
        const uint32_t combined = uint32_t(lower_product >> 32) + upper_product;
        const uint32_t original_high = word(arguments + 1);
        if (combined < upper_product || combined > original_high ||
            (combined == original_high && uint32_t(lower_product) > word(arguments)))
            --q;
        quotient = q;
    }
    if (negatives == 1)
        quotient = uint64_t(0) - quotient;
    return quotient;
}
// Capturing the original argument storage is necessary: negative operands are
// actually overwritten even though the original routine removes their words.
extern "C" __attribute__((naked, stdcall)) uint64_t fun_005ccfd0(uint32_t, uint32_t, uint32_t,
                                                                 uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcall _aligned_005ccfd0\n\taddl $4,%esp\n\tretl $16");
}
