#include "bigint.h"

namespace {
// The original inlined comparisons scan from the highest word and stop at the
// first mismatch. The verified dispatcher domain has a nonzero half count;
// no new zero-size policy is introduced here.
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

// Original 0x587720: cdecl (output, left, right, count, scratch). All products,
// differences and carries use the original recovered limb callees. This is
// the recursive routine selected by 0x588b40 for 22 <= count < 278, rather than
// a replacement multiplication algorithm. Its mutable scratch contents and
// even/odd split order are retained, including the original carry propagation.
extern "C" void fun_00587720(uint32_t* output, const uint32_t* left, const uint32_t* right,
                             int32_t count, uint32_t* scratch) {
    const int32_t half = count >> 1;
    if ((count & 1) == 0) {
        const uint32_t* left_high = left + half;
        const uint32_t* right_high = right + half;
        bool opposite = lower_words_less(left, left_high, half);
        if (opposite)
            fun_00587610(output, left_high, left, half);
        else
            fun_00587610(output, left, left_high, half);

        if (lower_words_less(right, right_high, half)) {
            opposite = !opposite;
            fun_00587610(output + half, right_high, right, half);
        } else {
            fun_00587610(output + half, right, right_high, half);
        }
        if (half < 22) {
            fun_0058b2f0(scratch, output, half, output + half, half);
            fun_0058b2f0(output, left, half, right, half);
            fun_0058b2f0(output + count, left_high, half, right_high, half);
        } else {
            uint32_t* extra = scratch + count;
            fun_00587720(scratch, output, output + half, half, extra);
            fun_00587720(output, left, right, half, extra);
            fun_00587720(output + count, left_high, right_high, half, extra);
        }
        uint32_t carry;
        if (!opposite)
            carry = 0u - fun_00587610(scratch, output, scratch, count);
        else
            carry = fun_0058b2a0(scratch, output, scratch, count);
        carry += fun_0058b2a0(scratch, output + count, scratch, count);
        carry += fun_0058b2a0(output + half, output + half, scratch, count);
        uint32_t* top = output + half + count;
        *top += carry;
        if (*top < carry)
            increment_chain(top + 1);
        return;
    }

    const int32_t larger = count - half;
    const uint32_t* left_high = left + larger;
    const uint32_t* right_high = right + larger;
    bool opposite = false;
    uint32_t upper = left[half];
    if (upper == 0) {
        if (lower_words_less(left, left_high, half)) {
            opposite = true;
            fun_00587610(output, left_high, left, half);
        } else {
            fun_00587610(output, left, left_high, half);
        }
    } else {
        upper -= fun_00587610(output, left, left_high, half);
    }
    output[half] = upper;

    upper = right[half];
    if (upper == 0) {
        if (lower_words_less(right, right_high, half)) {
            opposite = !opposite;
            fun_00587610(output + larger, right_high, right, half);
        } else {
            fun_00587610(output + larger, right, right_high, half);
        }
    } else {
        upper -= fun_00587610(output + larger, right, right_high, half);
    }
    output[count] = upper;

    const int32_t extended = count + 1;
    if (half < 22) {
        if (larger < 22) {
            fun_0058b2f0(scratch, output, larger, output + larger, larger);
            fun_0058b2f0(output, left, larger, right, larger);
        } else {
            fun_00587720(scratch, output, output + larger, larger, scratch + extended);
            fun_00587720(output, left, right, larger, scratch + extended);
        }
        fun_0058b2f0(output + extended, left_high, half, right_high, half);
    } else {
        fun_00587720(scratch, output, output + larger, larger, scratch + extended);
        fun_00587720(output, left, right, larger, scratch + extended);
        fun_00587720(output + extended, left_high, right_high, half, scratch + extended);
    }
    if (!opposite)
        fun_00587610(scratch, output, scratch, extended);
    else
        fun_0058b2a0(scratch, output, scratch, extended);

    const int32_t high_words = count - 1;
    if (fun_0058b2a0(scratch, output + extended, scratch, high_words) != 0) {
        scratch[high_words] += 1;
        if (scratch[high_words] == 0)
            scratch[count] += 1;
    }
    if (fun_0058b2a0(output + larger, output + larger, scratch, extended) != 0)
        increment_chain(output + extended + larger);
}
