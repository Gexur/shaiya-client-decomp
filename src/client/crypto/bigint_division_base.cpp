#include "bigint.h"

// Recovered from 0058BD70 and 0058C270 in the unchanged original x86 image.
// These operate on a normalized divisor (its highest word has bit 31 set).
// The 16-bit quotient estimates and corrections follow the original operation
// order; no host wide-integer division or substitute bigint implementation is used.
extern "C" uint32_t fun_0058bd70(uint32_t* quotient, uint32_t* numerator, int32_t numerator_count,
                                 const uint32_t* denominator, int32_t denominator_count) {
    int32_t remaining = numerator_count - denominator_count;
    uint32_t high_quotient = 0;
    const uint32_t next = denominator[denominator_count - 2];
    const uint32_t top = denominator[denominator_count - 1];
    uint32_t* window = numerator + remaining;
    uint32_t high = window[denominator_count - 1];
    if (top <= high &&
        (high != top || fun_00587660(window, denominator, denominator_count - 1) >= 0)) {
        fun_00587610(window, window, denominator, denominator_count);
        high_quotient = 1;
    }
    if (remaining - 1 >= 0) {
        quotient += remaining - 1;
        do {
            high = window[denominator_count - 1];
            uint32_t* lower_window = window - 1;
            if (high == top) {
                const uint32_t carry =
                    fun_0058b350(lower_window, denominator, denominator_count, 0xffffffffu);
                if (high == carry)
                    *quotient = 0xffffffffu;
                else {
                    fun_0058b2a0(lower_window, lower_window, denominator, denominator_count);
                    *quotient = 0xfffffffeu;
                }
            } else {
                const uint32_t low = window[denominator_count - 2];
                const uint32_t top_half = top >> 16;
                uint32_t estimate = high / top_half;
                const uint32_t product = estimate * (top & 0xffff);
                uint32_t remainder = (estimate * top_half * 0xffff + high) * 0x10000 | low >> 16;
                uint32_t quotient_high = estimate;
                if (remainder < product) {
                    quotient_high = estimate - 1;
                    remainder += top;
                    if (top <= remainder && remainder < product) {
                        quotient_high = estimate - 2;
                        remainder += top;
                    }
                }
                estimate = (remainder - product) / top_half;
                const uint32_t product_low = estimate * (top & 0xffff);
                remainder = (estimate * top_half * 0xffff + (remainder - product)) * 0x10000 |
                            (low & 0xffff);
                uint32_t quotient_low = estimate;
                if (remainder < product_low) {
                    quotient_low = estimate - 1;
                    remainder += top;
                    if (top <= remainder && remainder < product_low) {
                        quotient_low = estimate - 2;
                        remainder += top;
                    }
                }
                remainder -= product_low;
                uint32_t word = quotient_high << 16 | quotient_low;
                const uint32_t partial = (quotient_low & 0xffff) * (next >> 16);
                uint32_t product_high = (word >> 16) * (next >> 16);
                const uint32_t partial_low = (quotient_low & 0xffff) * (next & 0xffff);
                const uint32_t middle =
                    (partial_low >> 16) + partial + (word >> 16) * (next & 0xffff);
                if (middle < partial)
                    product_high += 0x10000;
                product_high += middle >> 16;
                uint32_t product_word = middle * 0x10000 + (partial_low & 0xffff);
                uint32_t correction_carry = 0;
                const uint32_t next_numerator = window[denominator_count - 3];
                bool borrow;
                if (remainder < product_high ||
                    (remainder == product_high && next_numerator < product_word)) {
                    product_high -= uint32_t(product_word < next);
                    product_word -= next;
                    remainder += top;
                    --word;
                    correction_carry = uint32_t(remainder < top);
                    borrow = next_numerator < product_word;
                } else {
                    borrow = remainder == product_high ? false : next_numerator < product_word;
                }
                const uint32_t upper_remainder = remainder - (product_high + uint32_t(borrow));
                const uint32_t carry =
                    fun_0058b350(lower_window, denominator, denominator_count - 2, word);
                const uint32_t next_borrow = uint32_t(next_numerator - product_word < carry);
                window[denominator_count - 2] = upper_remainder - next_borrow;
                window[denominator_count - 3] = (next_numerator - product_word) - carry;
                if (uint32_t(upper_remainder < next_borrow) !=
                    correction_carry - uint32_t(remainder < product_high + uint32_t(borrow))) {
                    fun_0058b2a0(lower_window, lower_window, denominator, denominator_count);
                    --word;
                }
                *quotient = word;
            }
            --quotient;
            --remaining;
            window = lower_window;
        } while (remaining != 0);
    }
    return high_quotient;
}

extern "C" uint32_t fun_0058c270(uint32_t* quotient, int32_t extra_quotient_words,
                                 uint32_t* numerator, int32_t numerator_count,
                                 const uint32_t* denominator) {
    const uint32_t top = denominator[1];
    const uint32_t low = denominator[0];
    uint32_t high_quotient = 0;
    uint32_t high = numerator[numerator_count - 1];
    const uint32_t initial_low = numerator[numerator_count - 2];
    numerator += numerator_count - 2;
    uint32_t remainder_low = initial_low;
    if (top <= high && (high != top || low <= initial_low)) {
        high_quotient = 1;
        remainder_low = initial_low - low;
        high -= uint32_t(initial_low < remainder_low) + top;
    }
    int32_t index = extra_quotient_words - 3 + numerator_count;
    if (index >= 0) {
        quotient += index;
        do {
            if (index < extra_quotient_words)
                *numerator = 0;
            else
                --numerator;
            uint32_t word, product_high, product_low;
            bool perform_correction = true;
            if (high == top) {
                high = remainder_low + top;
                word = 0xffffffffu;
                if (top <= high) {
                    product_high = low - uint32_t(low != 0);
                    product_low = 0u - low;
                } else {
                    const uint32_t next = *numerator;
                    remainder_low = next + low;
                    *quotient = 0xffffffffu;
                    high = (uint32_t(remainder_low < next) - low) + high;
                    perform_correction = false;
                }
            } else {
                const uint32_t top_half = top >> 16;
                uint32_t estimate = high / top_half;
                const uint32_t first_product = estimate * (top & 0xffff);
                high = (estimate * top_half * 0xffff + high) * 0x10000 | remainder_low >> 16;
                uint32_t quotient_high = estimate;
                if (high < first_product) {
                    high += top;
                    quotient_high = estimate - 1;
                    if (top <= high && high < first_product) {
                        quotient_high = estimate - 2;
                        high += top;
                    }
                }
                estimate = (high - first_product) / top_half;
                const uint32_t second_product = estimate * (top & 0xffff);
                high = (estimate * top_half * 0xffff + (high - first_product)) * 0x10000 |
                       (remainder_low & 0xffff);
                uint32_t quotient_low = estimate;
                if (high < second_product) {
                    high += top;
                    quotient_low = estimate - 1;
                    if (top <= high && high < second_product) {
                        quotient_low = estimate - 2;
                        high += top;
                    }
                }
                high -= second_product;
                word = quotient_high << 16 | quotient_low;
                const uint32_t partial = (quotient_low & 0xffff) * (low >> 16);
                const uint32_t partial_low = (quotient_low & 0xffff) * (low & 0xffff);
                uint32_t upper = (word >> 16) * (low >> 16);
                const uint32_t middle =
                    (partial_low >> 16) + partial + (word >> 16) * (low & 0xffff);
                if (middle < partial)
                    upper += 0x10000;
                product_high = (middle >> 16) + upper;
                product_low = middle * 0x10000 + (partial_low & 0xffff);
            }
            if (perform_correction) {
                const uint32_t next = *numerator;
                uint32_t corrected_low;
                do {
                    corrected_low = product_low;
                    if (product_high <= high && (product_high != high || product_low <= next))
                        break;
                    corrected_low = product_low - low;
                    --word;
                    high += top;
                    product_high -= uint32_t(product_low < corrected_low);
                    product_low = corrected_low;
                } while (top <= high);
                *quotient = word;
                remainder_low = next - corrected_low;
                high = (high - uint32_t(next < remainder_low)) - product_high;
            }
            --index;
            --quotient;
        } while (index >= 0);
    }
    *numerator = remainder_low;
    numerator[1] = high;
    return high_quotient;
}
