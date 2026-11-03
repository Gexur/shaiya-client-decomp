#include "bigint.h"

namespace {
#include "bigint_powmod_tables.inc"

struct Product {
    uint32_t low, high;
};
Product product(uint32_t left, uint32_t right) {
    const uint32_t cross = (left & 0xffff) * (right >> 16);
    const uint32_t low = (left & 0xffff) * (right & 0xffff);
    uint32_t high = (left >> 16) * (right >> 16);
    const uint32_t middle = (left >> 16) * (right & 0xffff) + cross + (low >> 16);
    if (middle < cross)
        high += 0x10000;
    return {middle * 0x10000 + (low & 0xffff), (middle >> 16) + high};
}

uint32_t reciprocal(uint32_t divisor) {
    if ((divisor & 0x7fffffff) == 0)
        return 0xffffffff;
    const uint32_t high_half = divisor >> 16;
    const uint32_t low_half = divisor & 0xffff;
    uint32_t estimate = (0u - divisor) / high_half;
    const uint32_t partial = estimate * low_half;
    uint32_t remainder = (estimate * high_half + divisor) * 0xffff0000;
    uint32_t quotient_high = estimate;
    if (remainder < partial) {
        remainder += divisor;
        quotient_high = estimate - 1;
        if (divisor <= remainder && remainder < partial) {
            quotient_high = estimate - 2;
            remainder += divisor;
        }
    }
    estimate = (remainder - partial) / high_half;
    const uint32_t second_partial = estimate * low_half;
    remainder = (estimate * high_half * 0xffff + (remainder - partial)) * 0x10000;
    uint32_t quotient_low = estimate;
    if (remainder < second_partial) {
        remainder += divisor;
        quotient_low = estimate - 1;
        if (divisor <= remainder && remainder < second_partial)
            quotient_low = estimate - 2;
    }
    return quotient_high << 16 | quotient_low;
}

// Factored repeated instruction sequence inside0058B4E0, not an additional
// recovered original procedure. Products retain the original16-bit pieces.
uint32_t divide_word(uint32_t& remainder, uint32_t next, uint32_t divisor, uint32_t inverse) {
    uint32_t quotient = product(inverse, remainder).high + remainder;
    const Product multiple = product(divisor, quotient);
    const uint32_t difference = next - multiple.low;
    const uint32_t high_difference = remainder - uint32_t(next < difference);
    remainder = difference;
    if (high_difference != multiple.high) {
        remainder = difference - divisor;
        ++quotient;
        if (high_difference - multiple.high != uint32_t(difference < remainder)) {
            remainder -= divisor;
            ++quotient;
        }
    }
    if (divisor <= remainder) {
        remainder -= divisor;
        ++quotient;
    }
    return quotient;
}
} // namespace

// Original0058B4E0: ordinary x86 cdecl. The extra quotient words correspond to
// zero words appended below the numerator. The numerator and quotient may alias.
extern "C" uint32_t fun_0058b4e0(uint32_t* quotient, int32_t extra_quotient_words,
                                 const uint32_t* numerator, int32_t numerator_count,
                                 uint32_t denominator) {
    const int32_t output_count = extra_quotient_words + numerator_count;
    uint32_t remainder = 0;
    if (output_count == 0)
        return 0;
    quotient += output_count - 1;
    if ((denominator & 0x80000000) == 0) {
        if (numerator_count != 0 && numerator[numerator_count - 1] < denominator) {
            remainder = numerator[numerator_count - 1];
            *quotient-- = 0;
            if (output_count == 1)
                return remainder;
            --numerator_count;
        }
        uint32_t table_shift = denominator < 0x10000 ? (denominator < 0x100 ? 1u : 9u)
                                                     : (denominator < 0x1000000 ? 17u : 25u);
        const uint32_t shift =
            (33u - leading_zero_table[denominator >> table_shift] - table_shift) & 31;
        denominator <<= shift;
        remainder <<= shift;
        const uint32_t inverse = reciprocal(denominator);
        if (numerator_count != 0) {
            uint32_t current = numerator[numerator_count - 1];
            remainder |= current >> ((32 - shift) & 31);
            int32_t index = numerator_count - 2;
            while (index >= 0) {
                const uint32_t following = numerator[index];
                const uint32_t next = following >> ((32 - shift) & 31) | current << shift;
                *quotient-- = divide_word(remainder, next, denominator, inverse);
                current = following;
                --index;
            }
            *quotient-- = divide_word(remainder, current << shift, denominator, inverse);
        }
        for (int32_t index = extra_quotient_words; index > 0; --index)
            *quotient-- = divide_word(remainder, 0, denominator, inverse);
        return remainder >> shift;
    }
    if (numerator_count != 0) {
        remainder = numerator[numerator_count - 1];
        const uint32_t word = uint32_t(denominator <= remainder);
        *quotient-- = word;
        remainder -= (0u - word) & denominator;
        --numerator_count;
    }
    const uint32_t inverse = reciprocal(denominator);
    for (int32_t index = numerator_count - 1; index >= 0; --index)
        *quotient-- = divide_word(remainder, numerator[index], denominator, inverse);
    for (int32_t index = extra_quotient_words; index > 0; --index)
        *quotient-- = divide_word(remainder, 0, denominator, inverse);
    return remainder;
}
