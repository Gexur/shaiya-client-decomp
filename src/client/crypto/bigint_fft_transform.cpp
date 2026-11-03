#include "bigint_fft.h"

namespace {
void copy_words(uint32_t* output, const uint32_t* input, int32_t count) {
    if (count != 0)
        do {
            *output++ = *input++;
        } while (--count != 0);
}
// Literal repeated base case of 58A540,58A770,58AD90. The leading carry
// word belongs to the residue and is included in both original limb calls.
void base_pair(uint32_t* first, uint32_t* second, int32_t words, uint32_t* scratch) {
    copy_words(scratch, first, words + 1);
    fun_0058b2a0(first, first, second, uint32_t(words + 1));
    if (fun_00587610(second, scratch, second, uint32_t(words + 1)) != 0)
        second[words] = fun_005873f0(second, second, words, 1);
}
} // namespace

extern "C" void fun_0058a540(uint32_t** blocks, int32_t points, uint32_t** level_slot,
                             int32_t twiddle_step, int32_t limb_words, int32_t stride,
                             uint32_t* scratch) {
    if (points == 2) {
        base_pair(blocks[0], blocks[stride], limb_words, scratch);
        return;
    }
    uint32_t* permutation = *level_slot;
    auto* temporary = static_cast<uint32_t*>(__builtin_alloca(uint32_t(limb_words + 1) * 4));
    const int32_t half = points / 2;
    fun_0058a540(blocks, half, level_slot - 1, twiddle_step * 2, limb_words, stride * 2, scratch);
    fun_0058a540(blocks + stride, half, level_slot - 1, twiddle_step * 2, limb_words, stride * 2,
                 scratch);
    for (int32_t index = 0; index < half; ++index, blocks += stride * 2, permutation += 2) {
        copy_words(scratch, blocks[stride], limb_words + 1);
        fun_00589e50(blocks[stride], int32_t(permutation[1] * uint32_t(twiddle_step)), limb_words,
                     temporary);
        fun_0058a700(blocks[stride], blocks[0], limb_words);
        fun_00589e50(scratch, int32_t(permutation[0] * uint32_t(twiddle_step)), limb_words,
                     temporary);
        fun_0058a700(blocks[0], scratch, limb_words);
    }
}

extern "C" void fun_0058a770(uint32_t** left, uint32_t** right, int32_t points,
                             uint32_t** level_slot, int32_t twiddle_step, int32_t limb_words,
                             int32_t stride, uint32_t* scratch) {
    if (points == 2) {
        base_pair(left[0], left[stride], limb_words, scratch);
        base_pair(right[0], right[stride], limb_words, scratch);
        return;
    }
    uint32_t* permutation = *level_slot;
    auto* temporary = static_cast<uint32_t*>(__builtin_alloca(uint32_t(limb_words + 1) * 4));
    const int32_t half = points / 2;
    fun_0058a770(left, right, half, level_slot - 1, twiddle_step * 2, limb_words, stride * 2,
                 scratch);
    fun_0058a770(left + stride, right + stride, half, level_slot - 1, twiddle_step * 2, limb_words,
                 stride * 2, scratch);
    for (int32_t index = 0; index < half;
         ++index, left += stride * 2, right += stride * 2, permutation += 2) {
        copy_words(scratch, left[stride], limb_words + 1);
        fun_00589e50(left[stride], int32_t(permutation[1] * uint32_t(twiddle_step)), limb_words,
                     temporary);
        fun_0058a700(left[stride], left[0], limb_words);
        fun_00589e50(scratch, int32_t(permutation[0] * uint32_t(twiddle_step)), limb_words,
                     temporary);
        fun_0058a700(left[0], scratch, limb_words);
        copy_words(scratch, right[stride], limb_words + 1);
        fun_00589e50(right[stride], int32_t(permutation[1] * uint32_t(twiddle_step)), limb_words,
                     temporary);
        fun_0058a700(right[stride], right[0], limb_words);
        fun_00589e50(scratch, int32_t(permutation[0] * uint32_t(twiddle_step)), limb_words,
                     temporary);
        fun_0058a700(right[0], scratch, limb_words);
    }
}

extern "C" void fun_0058ad90(uint32_t** blocks, int32_t points, int32_t twiddle_step,
                             int32_t limb_words, uint32_t* scratch) {
    if (points == 2) {
        base_pair(blocks[0], blocks[1], limb_words, scratch);
        return;
    }
    const int32_t half = points / 2;
    uint32_t** second = blocks + half;
    auto* temporary = static_cast<uint32_t*>(__builtin_alloca(uint32_t(limb_words + 1) * 4));
    fun_0058ad90(blocks, half, twiddle_step * 2, limb_words, scratch);
    fun_0058ad90(second, half, twiddle_step * 2, limb_words, scratch);
    int32_t first_exponent = 0, second_exponent = half * twiddle_step;
    for (int32_t index = 0; index < half; ++index, ++blocks, ++second) {
        copy_words(scratch, second[0], limb_words + 1);
        fun_00589e50(second[0], second_exponent, limb_words, temporary);
        fun_0058a700(second[0], blocks[0], limb_words);
        fun_00589e50(scratch, first_exponent, limb_words, temporary);
        fun_0058a700(blocks[0], scratch, limb_words);
        first_exponent += twiddle_step;
        second_exponent += twiddle_step;
    }
}
