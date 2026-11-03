#include "bigint_fft_helpers.h"

namespace {
struct SignedDivision {
    int32_t quotient, remainder;
};

SignedDivision divide_signed(int32_t numerator, int32_t denominator) {
    SignedDivision result;
    // Original CDQ/IDIV keeps hardware divide faults, including zero divisors.
    __asm__ __volatile__("cltd\n\tidivl %3"
                         : "=a"(result.quotient), "=&d"(result.remainder)
                         : "0"(numerator), "rm"(denominator)
                         : "cc");
    return result;
}

void copy_forward(uint32_t* output, const uint32_t* input, uint32_t words) {
    while (words != 0) {
        *output++ = *input++;
        --words;
    }
}
} // namespace

// Original 0x589e50..0x58a043. Signed exponent reduction, shifts, complemented
// wrapped words, borrow correction and the final odd-quotient complement follow
// the original instructions; this does not substitute a modular arithmetic API.
extern "C" void fun_00589e50(uint32_t* value, int32_t exponent, int32_t limb_words,
                             uint32_t* scratch) {
    const int32_t span = int32_t(uint32_t(limb_words) << 5);
    const int32_t remainder = divide_signed(exponent, span).remainder;
    uint32_t bits = uint32_t(remainder) & 0x8000001fu;
    if (int32_t(bits) < 0)
        bits = ((bits - 1) | 0xffffffe0u) + 1;
    if (bits == 0) {
        copy_forward(scratch, value, uint32_t(limb_words) + 1);
    } else {
        fun_00587480(scratch, value, uint32_t(limb_words) + 1, bits);
    }
    const int32_t word_shift = remainder / 32;
    if (word_shift == 0) {
        const uint32_t borrow = fun_00587350(value, scratch, limb_words, scratch[limb_words]);
        value[limb_words] = borrow;
        if (borrow != 0)
            value[limb_words] = fun_005873f0(value, value, limb_words, 1);
    } else {
        for (int32_t index = word_shift - 1; index >= 0; --index)
            value[index] = ~scratch[limb_words - word_shift + index];
        const uint32_t carry = fun_005873f0(value, value, word_shift, 1);
        const int32_t remaining = int32_t(uint32_t(limb_words) - uint32_t(word_shift));
        uint32_t first_borrow;
        if (carry == 1) {
            first_borrow = 0;
            copy_forward(value + word_shift, scratch, uint32_t(remaining));
        } else {
            first_borrow = fun_00587350(value + word_shift, scratch, remaining, 1);
        }
        const uint32_t second_borrow =
            fun_00587350(value + word_shift, value + word_shift, remaining, scratch[limb_words]);
        const uint32_t correction = first_borrow + second_borrow;
        value[limb_words] =
            correction == 0 ? 0 : fun_005873f0(value, value, limb_words, correction);
    }
    if ((uint32_t(divide_signed(exponent, span).quotient) & 1u) != 0) {
        uint32_t* cursor = value;
        uint32_t remaining = uint32_t(limb_words);
        do {
            *cursor = ~*cursor;
            ++cursor;
        } while (--remaining != 0);
        const uint32_t adjustment = value[limb_words] + 2;
        value[limb_words] = 0;
        const uint32_t sum = value[0] + adjustment;
        value[0] = sum;
        if (sum < adjustment) {
            cursor = value + 1;
            do {
                ++*cursor;
            } while (*cursor++ == 0);
        }
    }
}

// Original 0x58a700..0x58a763, including its unbounded borrow propagation.
extern "C" void fun_0058a700(uint32_t* value, const uint32_t* addend, int32_t limb_words) {
    const uint32_t carry = fun_0058b2a0(value, value, addend, uint32_t(limb_words));
    const uint32_t high = carry + addend[limb_words] + value[limb_words];
    if (high < 2) {
        value[limb_words] = high;
    } else {
        value[limb_words] = high - 1;
        uint32_t* cursor = value;
        uint32_t before;
        do {
            before = *cursor;
            *cursor++ = before - 1;
        } while (before == 0);
    }
}

// Original 0x58ad50..0x58ad89.
extern "C" void fun_0058ad50(uint32_t* value, int32_t limb_words) {
    if (value[limb_words] != 0) {
        const uint32_t borrow = fun_00587350(value, value, limb_words, 1);
        value[limb_words] = borrow;
        if (borrow != 0) {
            for (uint32_t index = 0; index != uint32_t(limb_words); ++index)
                value[index] = 0;
        }
    }
}

// Original 0x58af20..0x58af54: wrap the inverse exponent, then normalize.
extern "C" void fun_0058af20(uint32_t* value, int32_t exponent, int32_t limb_words,
                             uint32_t* scratch) {
    const int32_t span = int32_t(uint32_t(limb_words) << 6);
    const int32_t wrapped = int32_t(uint32_t(span) - uint32_t(exponent));
    const int32_t remainder = divide_signed(wrapped, span).remainder;
    fun_00589e50(value, remainder, limb_words, scratch);
    fun_0058ad50(value, limb_words);
}

// Original 0x58af60..0x58b02f. The original callers supply the reduction domain;
// no input clipping, alias restrictions or extra zero initialization is added.
extern "C" void fun_0058af60(uint32_t* output, const uint32_t* input, int32_t limb_words,
                             int32_t input_words) {
    int32_t sub_words;
    if (input_words > int32_t(uint32_t(limb_words) * 2)) {
        const int32_t leading = int32_t(uint32_t(input_words) - uint32_t(limb_words) * 2);
        const uint32_t carry =
            fun_0058b2a0(output, input, input + limb_words * 2, uint32_t(leading));
        output[limb_words] =
            fun_005873f0(output + leading, input + leading,
                         int32_t(uint32_t(limb_words) * 3 - uint32_t(input_words)), carry);
        sub_words = limb_words;
    } else {
        sub_words = int32_t(uint32_t(input_words) - uint32_t(limb_words));
        copy_forward(output, input, uint32_t(limb_words));
        output[limb_words] = 0;
    }
    if (fun_00587610(output, output, input + limb_words, uint32_t(sub_words)) != 0 &&
        fun_00587350(output + sub_words, output + sub_words,
                     int32_t(uint32_t(limb_words) - uint32_t(sub_words) + 1), 1) != 0) {
        output[limb_words] = fun_005873f0(output, output, limb_words, 1);
    }
}
