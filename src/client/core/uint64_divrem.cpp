#include "uint64_divrem.h"
namespace {
struct DivisionWords {
    uint32_t quotient, remainder;
};
DivisionWords divide_words(uint32_t high, uint32_t low, uint32_t divisor) {
    DivisionWords result;
    __asm__ volatile("divl %4"
                     : "=a"(result.quotient), "=d"(result.remainder)
                     : "0"(low), "1"(high), "rm"(divisor)
                     : "cc");
    return result;
}
} // namespace
extern "C" __attribute__((noinline)) uint64_t recovered_u64_divrem(uint32_t dividend_low,
                                                                   uint32_t dividend_high,
                                                                   uint32_t divisor_low,
                                                                   uint32_t divisor_high,
                                                                   uint64_t* remainder) {
    uint32_t quotient_low, quotient_high, product_low, product_high;
    if (divisor_high == 0) {
        const DivisionWords upper = divide_words(0, dividend_high, divisor_low);
        const DivisionWords lower = divide_words(upper.remainder, dividend_low, divisor_low);
        quotient_high = upper.quotient;
        quotient_low = lower.quotient;
        const uint32_t upper_product = quotient_high * divisor_low;
        const uint64_t lower_product = uint64_t(quotient_low) * divisor_low;
        product_low = uint32_t(lower_product);
        product_high = uint32_t(lower_product >> 32) + upper_product;
    } else {
        uint32_t dh = divisor_high, dl = divisor_low, nh = dividend_high, nl = dividend_low;
        do {
            dl = (dl >> 1) | (dh << 31);
            dh >>= 1;
            nl = (nl >> 1) | (nh << 31);
            nh >>= 1;
        } while (dh != 0);
        quotient_low = divide_words(nh, nl, dl).quotient;
        const uint32_t upper_product = quotient_low * divisor_high;
        const uint64_t lower_product = uint64_t(divisor_low) * quotient_low;
        product_low = uint32_t(lower_product);
        product_high = uint32_t(lower_product >> 32) + upper_product;
        if (product_high < upper_product || product_high > dividend_high ||
            (product_high == dividend_high && product_low > dividend_low)) {
            --quotient_low;
            const uint32_t before = product_low;
            product_low -= divisor_low;
            product_high = product_high - divisor_high - uint32_t(before < divisor_low);
        }
        quotient_high = 0;
    }
    // Original SUB/SBB then NEG(high),NEG(low),SBB(high,0), not a second divide.
    const uint32_t difference_low = product_low - dividend_low;
    const uint32_t difference_high =
        product_high - dividend_high - uint32_t(product_low < dividend_low);
    const uint32_t remainder_low = 0u - difference_low;
    const uint32_t remainder_high = 0u - difference_high - uint32_t(difference_low != 0);
    *remainder = (uint64_t(remainder_high) << 32) | remainder_low;
    return (uint64_t(quotient_high) << 32) | quotient_low;
}
extern "C" __attribute__((naked, stdcall)) void fun_005d90c0(uint32_t, uint32_t, uint32_t,
                                                             uint32_t) {
    // Eight private output bytes normalize EBX:ECX without changing original
    // inputs or ESI/EDI/EBP. The actual recovered arithmetic is called once.
    __asm__ volatile("subl $8,%esp\n\t"
                     "leal (%esp),%eax\n\t"
                     "pushl %eax\n\t"
                     "pushl 28(%esp)\n\t"
                     "pushl 28(%esp)\n\t"
                     "pushl 28(%esp)\n\t"
                     "pushl 28(%esp)\n\t"
                     "call _recovered_u64_divrem\n\t"
                     "addl $20,%esp\n\t"
                     "movl (%esp),%ecx\n\t"
                     "movl 4(%esp),%ebx\n\t"
                     "addl $8,%esp\n\t"
                     "retl $16\n\t");
}
