#include "bigint.h"

namespace {
uint32_t magnitude(int32_t size) {
    return size < 0 ? 0u - uint32_t(size) : uint32_t(size);
}
void copy_words(uint32_t* output, const uint32_t* input, uint32_t count) {
    if (count != 0)
        do {
            *output++ = *input++;
        } while (--count != 0);
}
} // namespace

extern "C" uint32_t fun_00586d80(BigInt* output, const BigInt* input, const BigInt* modulus) {
    const uint32_t input_count = magnitude(input->signed_size);
    const uint32_t modulus_count = magnitude(modulus->signed_size);
    uint32_t capacity = int32_t(input_count) > int32_t(modulus_count) ? input_count : modulus_count;
    ++capacity;
    if (input_count == 0 || (modulus_count == 1 && modulus->limbs[0] == 1))
        return 0;
    BigInt gcd, coefficient;
    gcd.capacity = int32_t(capacity);
    gcd.limbs = static_cast<uint32_t*>(__builtin_alloca(capacity * 4));
    coefficient.capacity = int32_t(capacity);
    coefficient.limbs = static_cast<uint32_t*>(__builtin_alloca(capacity * 4));
    fun_00589640(&gcd, &coefficient, nullptr, input, modulus);
    if (gcd.signed_size != 1 || gcd.limbs[0] != 1)
        return 0;
    if (coefficient.signed_size < 0) {
        if (modulus->signed_size < 0)
            fun_00586be0(output, &coefficient, modulus);
        else
            fun_00586020(output, &coefficient, modulus);
    } else {
        fun_00586f20(output, &coefficient);
    }
    return 1;
}

extern "C" void fun_00589640(BigInt* gcd, BigInt* first_coefficient, BigInt* second_coefficient,
                             const BigInt* left, const BigInt* right) {
    uint32_t left_count = magnitude(left->signed_size), right_count = magnitude(right->signed_size);
    const BigInt* larger;
    const BigInt* smaller;
    BigInt* larger_coefficient;
    BigInt* smaller_coefficient;
    uint32_t larger_count, smaller_count;
    if (int32_t(left_count) > int32_t(right_count) ||
        (left_count == right_count &&
         fun_00587660(left->limbs, right->limbs, int32_t(left_count)) > 0)) {
        larger = left;
        smaller = right;
        larger_count = left_count;
        smaller_count = right_count;
        larger_coefficient = first_coefficient;
        smaller_coefficient = second_coefficient;
    } else {
        larger = right;
        smaller = left;
        larger_count = right_count;
        smaller_count = left_count;
        larger_coefficient = second_coefficient;
        smaller_coefficient = first_coefficient;
    }
    auto* u = static_cast<uint32_t*>(__builtin_alloca(larger_count * 4 + 4));
    auto* v = static_cast<uint32_t*>(__builtin_alloca(smaller_count * 4 + 4));
    copy_words(u, larger->limbs, larger_count);
    copy_words(v, smaller->limbs, smaller_count);
    auto* gcd_words = static_cast<uint32_t*>(__builtin_alloca(larger_count * 4 + 4));
    auto* coefficient_words = static_cast<uint32_t*>(__builtin_alloca(larger_count * 4 + 4));
    int32_t coefficient_size;
    int32_t gcd_size;
    if (smaller_count == 0) {
        coefficient_words[0] = 1;
        coefficient_size = 1;
        copy_words(gcd_words, u, larger_count);
        gcd_size = int32_t(larger_count);
    } else {
        gcd_size = fun_0058c630(gcd_words, coefficient_words, &coefficient_size, u,
                                int32_t(larger_count), v, int32_t(smaller_count));
    }
    const uint32_t coefficient_count = magnitude(coefficient_size);
    // The original only initializes the size and limb fields of these two
    // stack objects; their unused input capacity words are not fabricated.
    BigInt gcd_value, coefficient_value;
    gcd_value.signed_size = gcd_size;
    gcd_value.limbs = gcd_words;
    coefficient_value.signed_size = int32_t(larger->signed_size ^ coefficient_size) < 0
                                        ? int32_t(0u - coefficient_count)
                                        : int32_t(coefficient_count);
    coefficient_value.limbs = coefficient_words;
    if (smaller_coefficient != nullptr) {
        if (smaller->signed_size == 0) {
            smaller_coefficient->signed_size = 0;
        } else {
            BigInt temporary;
            temporary.capacity = int32_t(coefficient_count + 1 + larger_count);
            temporary.limbs =
                static_cast<uint32_t*>(__builtin_alloca(uint32_t(temporary.capacity) * 4));
            fun_00585df0(&temporary, &coefficient_value, larger);
            fun_00586be0(&temporary, &gcd_value, &temporary);
            fun_0058c4d0(smaller_coefficient, &temporary, smaller);
        }
    }
    if (larger_coefficient != nullptr) {
        if (larger_coefficient->capacity < int32_t(coefficient_count))
            fun_00587300(larger_coefficient, int32_t(coefficient_count));
        copy_words(larger_coefficient->limbs, coefficient_words, coefficient_count);
        larger_coefficient->signed_size = coefficient_value.signed_size;
    }
    if (gcd->capacity < gcd_size)
        fun_00587300(gcd, gcd_size);
    copy_words(gcd->limbs, gcd_words, uint32_t(gcd_size));
    gcd->signed_size = gcd_size;
}

extern "C" void fun_0058c4d0(BigInt* quotient, const BigInt* numerator, const BigInt* denominator) {
    const uint32_t numerator_size = uint32_t(numerator->signed_size),
                   denominator_size = uint32_t(denominator->signed_size);
    const uint32_t numerator_count = magnitude(int32_t(numerator_size)),
                   denominator_count = magnitude(int32_t(denominator_size));
    int32_t quotient_count = int32_t(numerator_count - denominator_count + 1);
    if (denominator_count == 0)
        fun_00589580();
    if (quotient_count < 1) {
        quotient->signed_size = 0;
        return;
    }
    if (quotient->capacity < quotient_count)
        fun_00587300(quotient, quotient_count);
    uint32_t* output = quotient->limbs;
    auto* remainder = static_cast<uint32_t*>(__builtin_alloca(denominator_count * 4));
    const uint32_t* divisor = denominator->limbs;
    const uint32_t* dividend = numerator->limbs;
    if (divisor == output) {
        auto* saved = static_cast<uint32_t*>(__builtin_alloca(denominator_count * 4));
        copy_words(saved, divisor, denominator_count);
        divisor = saved;
    }
    if (dividend == output) {
        auto* saved = static_cast<uint32_t*>(__builtin_alloca(numerator_count * 4));
        copy_words(saved, dividend, numerator_count);
        dividend = saved;
    }
    fun_00588c30(output, remainder, 0, dividend, int32_t(numerator_count), divisor,
                 int32_t(denominator_count));
    quotient_count -= output[quotient_count - 1] == 0;
    if (int32_t(numerator_size ^ denominator_size) < 0)
        quotient_count = int32_t(0u - uint32_t(quotient_count));
    quotient->signed_size = quotient_count;
}

extern "C" uint32_t fun_0058d320(uint32_t numerator_high, uint32_t numerator_low,
                                 uint32_t denominator_high, uint32_t denominator_low) {
    uint32_t quotient = 0;
    uint32_t steps = 0;
    if (int32_t(numerator_high) < 0) {
        steps = 1;
        while (int32_t(denominator_high) >= 0) {
            denominator_high = denominator_high * 2 | denominator_low >> 31;
            denominator_low <<= 1;
            ++steps;
        }
        do {
            quotient <<= 1;
            if (denominator_high < numerator_high ||
                (denominator_high == numerator_high && denominator_low <= numerator_low)) {
                const uint32_t difference = numerator_low - denominator_low;
                numerator_high -= denominator_high + uint32_t(numerator_low < difference);
                numerator_low = difference;
                quotient |= 1;
            }
            denominator_low = denominator_low >> 1 | denominator_high << 31;
            denominator_high >>= 1;
        } while (--steps != 0);
    } else {
        while (denominator_high < numerator_high ||
               (denominator_high == numerator_high && denominator_low <= numerator_low)) {
            denominator_high = denominator_high * 2 | denominator_low >> 31;
            denominator_low <<= 1;
            ++steps;
        }
        while (steps != 0) {
            denominator_low = denominator_low >> 1 | denominator_high << 31;
            denominator_high >>= 1;
            quotient <<= 1;
            if (denominator_high < numerator_high ||
                (denominator_high == numerator_high && denominator_low <= numerator_low)) {
                const uint32_t difference = numerator_low - denominator_low;
                numerator_high -= denominator_high + uint32_t(numerator_low < difference);
                numerator_low = difference;
                quotient |= 1;
            }
            --steps;
        }
    }
    return quotient;
}
