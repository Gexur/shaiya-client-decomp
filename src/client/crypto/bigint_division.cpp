#include "bigint.h"

// Complete source control flow of00588C30; actual recursive-division/assertion
// callees remain explicit dependencies until recovered. No missing branch is
// replaced by host division, a success stub, or a call into the mapped image.
namespace {
#include "bigint_powmod_tables.inc"

uint32_t leading_zeros(uint32_t value) {
    const uint32_t shift =
        value < 0x10000 ? (value < 0x100 ? 1u : 9u) : (value < 0x1000000 ? 17u : 25u);
    return 33u - leading_zero_table[value >> shift] - shift;
}
void copy_words(uint32_t* output, const uint32_t* input, uint32_t count) {
    if (count != 0)
        do {
            *output++ = *input++;
        } while (--count != 0);
}
void decrement(uint32_t* value) {
    uint32_t before = *value;
    *value = before - 1;
    while (before == 0) {
        before = *++value;
        *value = before - 1;
    }
}
// Original immutable strings at0070C144/0070C18C, used solely by the original
// assertion call. The path is evidence text and is never opened by this code.
constexpr char assertion_file[] =
    "C:\\cygwin\\home\\D6VAA1\\dev\\new\\corelib2\\win32\\gmp\\mpn\\generic\\tdiv_qr.c";
constexpr char assertion_expression[] = "c == 0";
} // namespace

#define ALLOCA_WORDS(count) static_cast<uint32_t*>(__builtin_alloca(uint32_t(count) * 4))

extern "C" void fun_00588c30(uint32_t* quotient, uint32_t* remainder, uint32_t extra_quotient_words,
                             const uint32_t* numerator, int32_t numerator_count,
                             const uint32_t* denominator, int32_t denominator_count) {
    if (extra_quotient_words != 0)
        fun_005d0ba9();
    if (denominator_count == 0)
        fun_00589580();
    if (denominator_count == 1) {
        remainder[0] = fun_0058b4e0(quotient, 0, numerator, numerator_count, denominator[0]);
        return;
    }
    if (denominator_count == 2) {
        const uint32_t top = denominator[1];
        if ((top & 0x80000000) != 0) {
            uint32_t* work = ALLOCA_WORDS(numerator_count);
            copy_words(work, numerator, uint32_t(numerator_count));
            quotient[numerator_count - 2] =
                fun_0058c270(quotient, 0, work, numerator_count, denominator);
            remainder[0] = work[0];
            remainder[1] = work[1];
        } else {
            const uint32_t shift = leading_zeros(top);
            const uint32_t normalized[2] = {denominator[0] << (shift & 31),
                                            denominator[0] >> ((32 - shift) & 31) |
                                                top << (shift & 31)};
            uint32_t* work = ALLOCA_WORDS(numerator_count + 1);
            const uint32_t carry = fun_00587480(work, numerator, uint32_t(numerator_count), shift);
            work[numerator_count] = carry;
            const uint32_t high =
                fun_0058c270(quotient, 0, work, numerator_count + int32_t(carry != 0), normalized);
            if (carry == 0)
                quotient[numerator_count - 2] = high;
            fun_00587510(remainder, work, 2, shift);
        }
        return;
    }
    const uint32_t carry =
        uint32_t(denominator[denominator_count - 1] <= numerator[numerator_count - 1]);
    int32_t adjusted_count = numerator_count + int32_t(carry);
    if (denominator_count * 2 <= adjusted_count) {
        quotient[numerator_count - denominator_count] = 0;
        uint32_t shift = 0;
        const uint32_t* divisor = denominator;
        uint32_t* work = ALLOCA_WORDS(numerator_count + 1);
        if ((denominator[denominator_count - 1] & 0x80000000) == 0) {
            shift = leading_zeros(denominator[denominator_count - 1]);
            uint32_t* normalized = ALLOCA_WORDS(denominator_count);
            fun_00587480(normalized, denominator, uint32_t(denominator_count), shift);
            divisor = normalized;
            work[numerator_count] = fun_00587480(work, numerator, uint32_t(numerator_count), shift);
        } else {
            copy_words(work, numerator, uint32_t(numerator_count));
            work[numerator_count] = 0;
        }
        uint32_t* window = work;
        if (denominator_count > 91) {
            int32_t offset = adjusted_count - denominator_count * 2;
            window = work + offset;
            uint32_t* quotient_window = quotient + offset;
            fun_0058c040(quotient_window, window, divisor, denominator_count);
            adjusted_count -= denominator_count;
            while (denominator_count * 2 <= adjusted_count) {
                quotient_window -= denominator_count;
                window -= denominator_count;
                if (fun_0058c040(quotient_window, window, divisor, denominator_count) != 0)
                    fun_0058b450(assertion_file, 0x9c, assertion_expression);
                adjusted_count -= denominator_count;
            }
            if (adjusted_count != denominator_count) {
                window += denominator_count - adjusted_count;
                fun_0058bd70(quotient, window, adjusted_count, divisor, denominator_count);
            }
        } else {
            fun_0058bd70(quotient, window, adjusted_count, divisor, denominator_count);
        }
        if (shift != 0)
            fun_00587510(remainder, window, uint32_t(denominator_count), shift);
        else
            copy_words(remainder, window, uint32_t(denominator_count));
        return;
    }
    quotient[numerator_count - denominator_count] = 0;
    const int32_t quotient_count = numerator_count - denominator_count + int32_t(carry);
    if (quotient_count == 0) {
        copy_words(remainder, numerator, uint32_t(denominator_count));
        return;
    }
    const int32_t low_count = denominator_count - quotient_count;
    uint32_t shift = 0;
    const uint32_t* original_high_divisor = denominator + low_count;
    const uint32_t* divisor = original_high_divisor;
    uint32_t* work = ALLOCA_WORDS(quotient_count * 2 + 1);
    uint32_t* window = work;
    if ((denominator[denominator_count - 1] & 0x80000000) == 0) {
        shift = leading_zeros(denominator[denominator_count - 1]);
        uint32_t* normalized = ALLOCA_WORDS(quotient_count);
        fun_00587480(normalized, original_high_divisor, uint32_t(quotient_count), shift);
        normalized[0] |= original_high_divisor[-1] >> ((32 - shift) & 31);
        divisor = normalized;
        const uint32_t* high_numerator = numerator + numerator_count - quotient_count * 2;
        const uint32_t high =
            fun_00587480(work, high_numerator, uint32_t(quotient_count * 2), shift);
        if (carry == 0)
            work[0] |= high_numerator[-1] >> ((32 - shift) & 31);
        else {
            work[quotient_count * 2] = high;
            window = work + 1;
        }
    } else {
        copy_words(work, numerator + numerator_count - quotient_count * 2,
                   uint32_t(quotient_count * 2));
        if (carry != 0) {
            work[quotient_count * 2] = 0;
            window = work + 1;
        }
    }
    if (quotient_count == 1) {
        const uint32_t input_low = window[0];
        const uint32_t top = divisor[0];
        const uint32_t high_half = top >> 16;
        const uint32_t low_half = top & 0xffff;
        uint32_t estimate = window[1] / high_half;
        const uint32_t partial = estimate * low_half;
        uint32_t residual = (estimate * high_half * 0xffff + window[1]) * 0x10000 | input_low >> 16;
        uint32_t high = estimate;
        if (residual < partial) {
            high = estimate - 1;
            residual += top;
            if (top <= residual && residual < partial) {
                high = estimate - 2;
                residual += top;
            }
        }
        estimate = (residual - partial) / high_half;
        const uint32_t second_partial = estimate * low_half;
        residual =
            (estimate * high_half * 0xffff + (residual - partial)) * 0x10000 | (input_low & 0xffff);
        uint32_t low = estimate;
        if (residual < second_partial) {
            low = estimate - 1;
            residual += top;
            if (top <= residual && residual < second_partial) {
                low = estimate - 2;
                residual += top;
            }
        }
        window[0] = residual - second_partial;
        quotient[0] = high << 16 | low;
    } else if (quotient_count == 2)
        fun_0058c270(quotient, 0, window, 4, divisor);
    else if (quotient_count < 92)
        fun_0058bd70(quotient, window, quotient_count * 2, divisor, quotient_count);
    else
        fun_0058c040(quotient, window, divisor, quotient_count);

    const uint32_t previous = low_count >= 2 ? denominator[low_count - 2] : 0;
    const uint32_t next_divisor = (previous >> 1) >> ((~shift) & 31) | original_high_divisor[-1]
                                                                           << (shift & 31);
    const uint32_t next_high = next_divisor >> 16;
    const uint32_t next_low = next_divisor & 0xffff;
    const uint32_t quotient_low = quotient[quotient_count - 1] & 0xffff;
    const uint32_t quotient_high = quotient[quotient_count - 1] >> 16;
    const uint32_t partial = quotient_low * next_high;
    uint32_t upper = quotient_high * next_high;
    const uint32_t middle = quotient_high * next_low + partial + (quotient_low * next_low >> 16);
    if (middle < partial)
        upper += 0x10000;
    int32_t remainder_count = quotient_count;
    if (window[quotient_count - 1] < (middle >> 16) + upper) {
        decrement(quotient);
        const uint32_t high = fun_0058b2a0(window, window, divisor, uint32_t(quotient_count));
        if (high != 0) {
            remainder_count = quotient_count + 1;
            window[quotient_count] = high;
        }
    }
    uint32_t borrow = 0;
    int32_t remaining_low = low_count;
    if (shift != 0) {
        const uint32_t high = fun_00587480(window, window, uint32_t(remainder_count), 32 - shift);
        const uint32_t mask = 0xffffffffu >> (shift & 31);
        window[0] |= numerator[low_count - 1] & mask;
        const uint32_t carry_out = fun_0058b350(window, quotient, uint32_t(quotient_count),
                                                original_high_divisor[-1] & mask);
        if (quotient_count == remainder_count) {
            window[quotient_count] = high - carry_out;
            borrow = uint32_t(high < carry_out);
            ++remainder_count;
            --remaining_low;
        } else {
            if (window[quotient_count] < carry_out)
                fun_005d0ba9();
            window[quotient_count] -= carry_out;
            --remaining_low;
        }
    }
    uint32_t* product = ALLOCA_WORDS(denominator_count);
    if (remaining_low < quotient_count && remaining_low == 0) {
        copy_words(remainder, window, uint32_t(remainder_count));
        if (remainder_count != denominator_count)
            fun_005d0ba9();
    } else {
        if (remaining_low < quotient_count)
            fun_00587030(product, quotient, quotient_count, denominator, remaining_low);
        else
            fun_00587030(product, denominator, remaining_low, quotient, quotient_count);
        const uint32_t high_borrow =
            fun_005876a0(window, window, remainder_count, product + remaining_low, quotient_count);
        copy_words(remainder + remaining_low, window, uint32_t(denominator_count - remaining_low));
        const uint32_t combined_borrow = borrow | high_borrow;
        const uint32_t low_borrow =
            fun_00587610(remainder, numerator, product, uint32_t(remaining_low));
        borrow =
            combined_borrow | fun_00587350(remainder + remaining_low, remainder + remaining_low,
                                           remainder_count, low_borrow);
    }
    if (borrow != 0) {
        decrement(quotient);
        fun_0058b2a0(remainder, remainder, denominator, uint32_t(denominator_count));
    }
}

#undef ALLOCA_WORDS
