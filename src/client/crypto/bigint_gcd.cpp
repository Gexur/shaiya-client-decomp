#include "bigint.h"

namespace {
#include "bigint_powmod_tables.inc"
uint32_t leading_zeros(uint32_t value) {
    uint32_t shift = value < 0x10000 ? (value < 0x100 ? 1u : 9u) : (value < 0x1000000 ? 17u : 25u);
    return 33u - leading_zero_table[value >> shift] - shift;
}
void copy_words(uint32_t* output, const uint32_t* input, int32_t count) {
    if (count != 0)
        do {
            *output++ = *input++;
        } while (--count != 0);
}
void zero_words(uint32_t* output, int32_t count) {
    if (count != 0)
        do {
            *output++ = 0;
        } while (--count != 0);
}
int32_t normalized_size(const uint32_t* words, int32_t count) {
    while (count > 0 && words[count - 1] == 0)
        --count;
    return count;
}
// The original double-word Lehmer estimate forms each product from 16-bit
// partials. Retain its intermediate wrap/carry and two-word subtraction.
void subtract_product(uint32_t& high, uint32_t& low, uint32_t other_high, uint32_t other_low,
                      uint32_t multiplier) {
    uint32_t low_product = (other_low & 0xffff) * (multiplier & 0xffff);
    uint32_t cross = (other_low & 0xffff) * (multiplier >> 16);
    uint32_t upper = (other_low >> 16) * (multiplier >> 16);
    uint32_t middle = (low_product >> 16) + cross + (other_low >> 16) * (multiplier & 0xffff);
    if (middle < cross)
        upper += 0x10000;
    uint32_t difference = low - (middle * 0x10000 + (low_product & 0xffff));
    high = high - uint32_t(low < difference) - ((middle >> 16) + upper + multiplier * other_high);
    low = difference;
}
} // namespace

extern "C" int32_t fun_0058c630(uint32_t* gcd, uint32_t* coefficient,
                                int32_t* signed_coefficient_size, uint32_t* u, int32_t count,
                                uint32_t* v, int32_t v_count) {
    uint32_t* const original_coefficient = coefficient;
    auto* q = static_cast<uint32_t*>(__builtin_alloca(uint32_t(count) * 4 + 4));
    auto* t = static_cast<uint32_t*>(__builtin_alloca(uint32_t(count) * 4 + 4));
    auto* previous = static_cast<uint32_t*>(__builtin_alloca(uint32_t(count) * 4 + 4));
    zero_words(coefficient, count);
    zero_words(previous, count);
    coefficient[0] = 1;
    previous[0] = 0;
    int32_t coefficient_count = 1;
    int32_t sign = 1;
    if (v_count < count) {
        fun_00588c30(q, u, 0, u, count, v, v_count);
        coefficient[0] = 0;
        previous[0] = 1;
        sign = -1;
        uint32_t* old_u = u;
        count = v_count;
        u = v;
        v = old_u;
    }
    // This selector is calculated once before the original loop; it is not
    // recomputed as the working limb count falls below the 70-word threshold.
    const bool double_word_estimate = count >= 70;
    for (;;) {
        uint32_t* const old_previous = previous;
        uint32_t* const old_q = q;
        uint32_t* const old_t = t;
        uint32_t* const old_u = u;
        v_count = normalized_size(v, count);
        if (v_count < 2)
            break;
        uint32_t ma = 1, mb = 0, mc = 0, md = 1;
        int32_t parity = 0;
        bool estimate_available = true;
        if (!double_word_estimate) {
            uint32_t a = 1;
            uint32_t first = u[count - 1], second = v[count - 1];
            const uint32_t shift = leading_zeros(first);
            if (shift != 0) {
                first = first << (shift & 31) | u[count - 2] >> ((32 - shift) & 31);
                second = second << (shift & 31) | v[count - 2] >> ((32 - shift) & 31);
            }
            if (second == 0)
                estimate_available = false;
            else
                for (;;) {
                    ma = a;
                    uint32_t final_c = mc, final_d = md;
                    if (md + second == 0)
                        break;
                    uint32_t quotient = (first + a) / (second - mc);
                    if (quotient != (first - mb) / (md + second))
                        break;
                    a = quotient * mc + a;
                    uint32_t next_b = quotient * md + mb;
                    mb = md;
                    first -= quotient * second;
                    parity = -1;
                    ma = mc;
                    final_c = a;
                    final_d = next_b;
                    if (first - next_b == 0) {
                        mc = final_c;
                        md = final_d;
                        break;
                    }
                    quotient = (second - mc) / (first + a);
                    if (quotient != (md + second) / (first - next_b)) {
                        mc = final_c;
                        md = final_d;
                        break;
                    }
                    mc = quotient * a + mc;
                    md = quotient * next_b + md;
                    second -= quotient * first;
                    parity = 0;
                    ma = a;
                    mb = next_b;
                    if (second == mc)
                        break;
                }
        } else {
            uint32_t first_high = u[count - 1], first_low = u[count - 2];
            uint32_t second_high = v[count - 1], second_low = v[count - 2];
            const uint32_t shift = leading_zeros(first_high);
            if (shift != 0) {
                first_high = first_high << (shift & 31) | first_low >> ((32 - shift) & 31);
                first_low <<= shift & 31;
                second_high = second_high << (shift & 31) | second_low >> ((32 - shift) & 31);
                second_low <<= shift & 31;
                if (count > 2) {
                    first_low |= u[count - 3] >> ((32 - shift) & 31);
                    second_low |= v[count - 3] >> ((32 - shift) & 31);
                }
            }
            uint32_t a = 1;
            for (;;) {
                ma = a;
                uint32_t high = second_high - uint32_t(second_low < second_low - mc);
                if (high == 0)
                    break;
                uint32_t quotient = fun_0058d320(first_high + uint32_t(first_low + a < first_low),
                                                 first_low + a, high, second_low - mc);
                high = second_high + uint32_t(second_low + md < second_low);
                if (high == 0)
                    break;
                if (quotient != fun_0058d320(first_high - uint32_t(first_low < first_low - mb),
                                             first_low - mb, high, second_low + md))
                    break;
                a = quotient * mc + a;
                const uint32_t next_b = quotient * md + mb;
                mb = md;
                subtract_product(first_high, first_low, second_high, second_low, quotient);
                quotient = fun_0058d320(
                    second_high - uint32_t(second_low < second_low - mc), second_low - mc,
                    first_high + uint32_t(first_low + a < first_low), first_low + a);
                high = first_high - uint32_t(first_low < first_low - next_b);
                ma = mc;
                const uint32_t old_c = mc, old_d = md;
                mc = a;
                md = next_b;
                parity = -1;
                if (high == 0)
                    break;
                if (quotient !=
                    fun_0058d320(second_high + uint32_t(second_low + old_d < second_low),
                                 second_low + old_d, high, first_low - next_b))
                    break;
                mc = a * quotient + old_c;
                md = next_b * quotient + old_d;
                subtract_product(second_high, second_low, first_high, first_low, quotient);
                mb = next_b;
                parity = 0;
            }
        }
        if (estimate_available && parity != 0)
            sign = -sign;
        if (estimate_available && mb != 0) {
            if (ma == 0) {
                copy_words(q, v, count);
                copy_words(t, u, count);
                fun_0058b350(t, v, uint32_t(count), md);
                copy_words(u, previous, coefficient_count);
                u[coefficient_count] = 0;
                copy_words(v, coefficient, coefficient_count);
                const uint32_t carry = fun_00589590(v, previous, uint32_t(coefficient_count), md);
                v[coefficient_count] = carry;
                coefficient_count += carry != 0;
            } else {
                if (parity == 0) {
                    fun_00587260(q, u, uint32_t(count), ma);
                    fun_0058b350(q, v, uint32_t(count), mb);
                    fun_00587260(t, v, uint32_t(count), md);
                    fun_0058b350(t, u, uint32_t(count), mc);
                } else {
                    fun_00587260(q, v, uint32_t(count), mb);
                    fun_0058b350(q, u, uint32_t(count), ma);
                    fun_00587260(t, u, uint32_t(count), mc);
                    fun_0058b350(t, v, uint32_t(count), md);
                }
                uint32_t carry = fun_00587260(u, coefficient, uint32_t(coefficient_count), ma);
                uint32_t high = fun_00589590(u, previous, uint32_t(coefficient_count), mb) + carry;
                u[coefficient_count] = high;
                int32_t first_count = coefficient_count + int32_t(high != 0);
                if (high < carry) {
                    u[first_count] = 1;
                    v[first_count] = 0;
                    ++first_count;
                }
                carry = fun_00587260(v, previous, uint32_t(coefficient_count), md);
                high = fun_00589590(v, coefficient, uint32_t(coefficient_count), mc) + carry;
                v[coefficient_count] = high;
                int32_t second_count = coefficient_count + int32_t(high != 0);
                if (high < carry) {
                    v[second_count] = 1;
                    if (first_count <= second_count)
                        u[second_count] = 0;
                    ++second_count;
                }
                coefficient_count = first_count < second_count ? second_count : first_count;
            }
            previous = v;
            q = coefficient;
            t = old_previous;
            v = old_t;
            u = old_q;
            coefficient = old_u;
            count -= old_q[count - 1] == 0;
            continue;
        }
        fun_00588c30(t, u, 0, u, count, v, v_count);
        copy_words(q, coefficient, coefficient_count);
        const int32_t quotient_count = count - v_count + 1;
        zero_words(previous + coefficient_count, quotient_count);
        for (int32_t index = 0; index < quotient_count; ++index)
            q[coefficient_count + index] =
                fun_00589590(q + index, previous, uint32_t(coefficient_count), t[index]);
        coefficient_count += quotient_count;
        coefficient_count -= q[coefficient_count - 1] == 0;
        q = coefficient;
        coefficient = previous;
        sign = -sign;
        u = v;
        previous = old_q;
        v = old_u;
        count = v_count;
    }
    if (v_count != 0) {
        uint32_t divisor = v[0];
        uint32_t remainder = fun_0058b4e0(t, 0, u, count, divisor);
        copy_words(q, coefficient, coefficient_count);
        const int32_t quotient_count = count - int32_t(t[count - 1] == 0);
        if (coefficient_count < quotient_count) {
            zero_words(q + coefficient_count, quotient_count - coefficient_count);
            zero_words(previous + coefficient_count, quotient_count);
            for (int32_t index = 0; index < coefficient_count; ++index)
                q[quotient_count + index] =
                    fun_00589590(q + index, t, uint32_t(quotient_count), previous[index]);
        } else if (quotient_count != 0) {
            zero_words(previous + coefficient_count, quotient_count);
            for (int32_t index = 0; index < quotient_count; ++index)
                q[coefficient_count + index] =
                    fun_00589590(q + index, previous, uint32_t(coefficient_count), t[index]);
        }
        coefficient_count += quotient_count;
        coefficient_count -= q[coefficient_count - 1] == 0;
        for (;;) {
            sign = -sign;
            if (remainder == 0)
                break;
            const uint32_t next_remainder = divisor % remainder;
            copy_words(coefficient, previous, coefficient_count);
            q[coefficient_count] = 0;
            coefficient[coefficient_count] =
                fun_00589590(coefficient, q, uint32_t(coefficient_count), divisor / remainder);
            coefficient_count += int32_t(coefficient[coefficient_count] != 0);
            divisor = remainder;
            remainder = next_remainder;
            uint32_t* old_q = q;
            q = coefficient;
            coefficient = previous;
            previous = old_q;
        }
        if (gcd != nullptr)
            gcd[0] = divisor;
        coefficient_count = normalized_size(previous, coefficient_count);
        if (original_coefficient != previous)
            copy_words(original_coefficient, previous, coefficient_count);
        *signed_coefficient_size = sign < 0 ? -coefficient_count : coefficient_count;
        return 1;
    }
    if (gcd != u && gcd != nullptr)
        copy_words(gcd, u, count);
    coefficient_count = normalized_size(coefficient, coefficient_count);
    if (original_coefficient != coefficient)
        copy_words(original_coefficient, coefficient, coefficient_count);
    *signed_coefficient_size = sign < 0 ? -coefficient_count : coefficient_count;
    return count;
}
