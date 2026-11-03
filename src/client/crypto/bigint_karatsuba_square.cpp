#include "bigint.h"

namespace {
// Literal high-to-low comparison from 0x587bfd/0x587d70. The recovered
// dispatcher enters with count >= 58; recursive halves are nonzero.
bool lower_words_less(const uint32_t* left, const uint32_t* right, int32_t count) {
    do {
        --count;
        if (left[count] != right[count])
            return left[count] < right[count];
    } while (count != 0);
    return false;
}

void increment_chain(uint32_t* word) {
    do {
        *word += 1;
    } while (*word++ == 0);
}
} // namespace

// Original 0x587bb0..0x587e83, selected by 0x586f70 for 58 <= count < 226.
// Retains the original difference, square and merge order, including every
// mutable scratch word and odd-count carry. All arithmetic dependencies are
// genuine recovered limb/base-square procedures; no replacement math is used.
extern "C" SHAIYA_BIGINT_EXPORT void fun_00587bb0(uint32_t* output, const uint32_t* input,
                                                  uint32_t count, uint32_t* scratch) {
    const int32_t half = int32_t(count) >> 1;
    if ((count & 1) == 0) {
        const uint32_t* high = input + half;
        if (lower_words_less(input, high, half))
            fun_00587610(output, high, input, uint32_t(half));
        else
            fun_00587610(output, input, high, uint32_t(half));

        uint32_t* high_output = output + count;
        if (half < 58) {
            fun_0058b0e0(scratch, output, half);
            fun_0058b0e0(output, input, half);
            fun_0058b0e0(high_output, high, half);
        } else {
            uint32_t* extra = scratch + count;
            fun_00587bb0(scratch, output, uint32_t(half), extra);
            fun_00587bb0(output, input, uint32_t(half), extra);
            fun_00587bb0(high_output, high, uint32_t(half), extra);
        }
        uint32_t carry = 0u - fun_00587610(scratch, output, scratch, count);
        carry += fun_0058b2a0(scratch, high_output, scratch, count);
        carry += fun_0058b2a0(output + half, output + half, scratch, count);
        uint32_t* top = output + half + count;
        *top += carry;
        if (*top < carry)
            increment_chain(top + 1);
        return;
    }

    const uint32_t larger = count - uint32_t(half);
    const uint32_t* high = input + larger;
    uint32_t upper = input[half];
    if (upper == 0) {
        if (lower_words_less(input, high, half))
            fun_00587610(output, high, input, uint32_t(half));
        else
            fun_00587610(output, input, high, uint32_t(half));
    } else {
        upper -= fun_00587610(output, input, high, uint32_t(half));
    }
    output[half] = upper;

    const uint32_t extended = count + 1;
    if (int32_t(larger) < 58) {
        fun_0058b0e0(scratch, output, int32_t(larger));
        fun_0058b0e0(output, input, int32_t(larger));
    } else {
        fun_00587bb0(scratch, output, larger, scratch + extended);
        fun_00587bb0(output, input, larger, scratch + extended);
    }
    uint32_t* high_output = output + extended;
    if (half < 58)
        fun_0058b0e0(high_output, high, half);
    else
        fun_00587bb0(high_output, high, uint32_t(half), scratch + extended);

    fun_00587610(scratch, output, scratch, extended);
    const uint32_t high_words = count - 1;
    if (fun_0058b2a0(scratch, high_output, scratch, high_words) != 0) {
        scratch[high_words] += 1;
        if (scratch[high_words] == 0)
            scratch[count] += 1;
    }
    if (fun_0058b2a0(output + larger, output + larger, scratch, extended) != 0)
        increment_chain(output + extended + larger);
}
