#include "bigint_fft.h"

namespace {
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
constexpr char assertion_file[] =
    "C:\\cygwin\\home\\D6VAA1\\dev\\new\\corelib2\\win32\\gmp\\mpn\\generic\\mul_fft.c";
constexpr char assertion_expression[] = "__gmpn_fft_next_size (pl, k) == pl";
} // namespace

extern "C" void fun_00589a20(uint32_t* output, int32_t output_words, const uint32_t* left,
                             int32_t left_words, const uint32_t* right, int32_t right_words,
                             int32_t depth) {
    const bool square = left == right && left_words == right_words;
    if (fun_005899c0(output_words, uint32_t(depth)) != output_words)
        fun_0058b450(assertion_file, 0x267, assertion_expression);
    auto** levels = static_cast<uint32_t**>(__builtin_alloca(uint32_t(depth + 1) * 4));
    for (int32_t index = 0; index <= depth; ++index)
        levels[index] =
            static_cast<uint32_t*>(__builtin_alloca((1u << (uint32_t(index) & 31)) * 4));
    fun_00589de0(levels, depth);
    const int32_t points = int32_t(1u << (uint32_t(depth) & 31));
    const int32_t chunk_bits = int32_t(uint32_t(output_words) << 5) / points;
    const int32_t chunk_words = chunk_bits / 32;
    const int32_t quantum = points < 33 ? 32 : points;
    int32_t modulus_bits = ((quantum + 2 + chunk_bits * 2 + depth) / quantum) * quantum;
    int32_t limb_words = modulus_bits / 32;
    if ((square ? 678 : 834) <= limb_words) {
        const int32_t recursive_depth = fun_00589960(limb_words, left == right);
        const int32_t alignment = int32_t((1u << (uint32_t(recursive_depth) & 31)) * 32);
        if (modulus_bits % alignment != 0) {
            modulus_bits = (modulus_bits / alignment + 1) * alignment;
            limb_words = modulus_bits / 32;
        }
    }
    const int32_t block_words = limb_words + 1;
    auto* scratch = static_cast<uint32_t*>(__builtin_alloca(uint32_t(block_words) * 4));
    const uint32_t allocation_bytes = uint32_t(block_words) * uint32_t(points) * 8;
    auto* left_storage = static_cast<uint32_t*>(dat_0070c0d0(allocation_bytes));
    uint32_t* right_storage = left_storage + block_words * points;
    auto** left_blocks = static_cast<uint32_t**>(__builtin_alloca(uint32_t(points) * 4));
    auto** right_blocks = static_cast<uint32_t**>(__builtin_alloca(uint32_t(points) * 4));
    int32_t exponent = 0;
    const int32_t twiddle_step = modulus_bits / points;
    for (int32_t index = 0; index < points; ++index) {
        left_blocks[index] = left_storage + index * block_words;
        right_blocks[index] = right_storage + index * block_words;
        if (left_words < 1)
            zero_words(left_blocks[index], block_words);
        else {
            const int32_t copied = left_words < chunk_words ? left_words : chunk_words;
            copy_words(left_blocks[index], left, copied);
            left += chunk_words;
            zero_words(left_blocks[index] + copied, block_words - copied);
            fun_00589e50(left_blocks[index], exponent, limb_words, scratch);
        }
        left_words -= chunk_words;
        // The original compares the already advanced current pointers here,
        // not the original square flag, and advances right only for live input.
        if (left != right) {
            if (right_words < 1)
                zero_words(right_blocks[index], block_words);
            else {
                const int32_t copied = right_words < chunk_words ? right_words : chunk_words;
                copy_words(right_blocks[index], right, copied);
                right += chunk_words;
                zero_words(right_blocks[index] + copied, block_words - copied);
                fun_00589e50(right_blocks[index], exponent, limb_words, scratch);
            }
        }
        right_words -= chunk_words;
        exponent += twiddle_step;
    }
    fun_0058a050(output, left, right, output_words, depth, points, left_blocks, right_blocks,
                 left_storage, right_storage, limb_words, chunk_words, twiddle_step, levels,
                 scratch, 0);
    dat_0070c0d8(left_storage, allocation_bytes);
}

extern "C" void fun_0058a050(uint32_t* output, const uint32_t* left, const uint32_t* right,
                             int32_t output_words, int32_t depth, int32_t points,
                             uint32_t** left_blocks, uint32_t** right_blocks,
                             uint32_t* left_storage, uint32_t* right_storage, int32_t limb_words,
                             int32_t chunk_words, int32_t twiddle_step, uint32_t** levels,
                             uint32_t* scratch, int32_t initialize) {
    const bool different = left != right;
    if (initialize != 0) {
        int32_t exponent = 0;
        for (int32_t index = 0; index < points; ++index, exponent += twiddle_step) {
            left_blocks[index] = left_storage + index * (limb_words + 1);
            right_blocks[index] = right_storage + index * (limb_words + 1);
            copy_words(left_blocks[index], left, chunk_words);
            left += chunk_words;
            zero_words(left_blocks[index] + chunk_words, limb_words - chunk_words + 1);
            if (index == points - 1)
                left_blocks[index][chunk_words] = *left;
            fun_00589e50(left_blocks[index], exponent, limb_words, scratch);
            if (different) {
                copy_words(right_blocks[index], right, chunk_words);
                right += chunk_words;
                zero_words(right_blocks[index] + chunk_words, limb_words - chunk_words + 1);
                if (index == points - 1)
                    right_blocks[index][chunk_words] = *right;
                fun_00589e50(right_blocks[index], exponent, limb_words, scratch);
            }
        }
    }
    if (different)
        fun_0058a770(left_blocks, right_blocks, points, levels + depth, twiddle_step * 2,
                     limb_words, 1, scratch);
    else {
        fun_0058a540(left_blocks, points, levels + depth, twiddle_step * 2, limb_words, 1, scratch);
        right_blocks = left_blocks;
    }
    fun_0058aa40(left_blocks, right_blocks, limb_words, points);
    fun_0058ad90(left_blocks, points, twiddle_step * 2, limb_words, scratch);
    for (int32_t index = 0; index < points; ++index)
        fun_0058af20(left_blocks[index], ((points - index) % points) * twiddle_step + depth,
                     limb_words, scratch);
    zero_words(scratch, limb_words + 1);
    const int32_t total_words = (points - 1) * chunk_words + 1 + limb_words;
    zero_words(right_storage, total_words);
    int32_t accumulated = 0;
    for (int32_t index = points - 1; index >= 0; --index) {
        const int32_t offset = index * chunk_words;
        uint32_t* destination = right_storage + offset;
        uint32_t* block = left_blocks[(points - index) % points];
        const int32_t remaining = total_words - offset;
        if (fun_0058b2a0(destination, destination, block, uint32_t(limb_words + 1)) != 0)
            accumulated +=
                int32_t(fun_005873f0(destination + limb_words + 1, destination + limb_words + 1,
                                     remaining - limb_words - 1, 1));
        scratch[chunk_words * 2] = uint32_t(index + 1);
        if (fun_00587660(block, scratch, limb_words + 1) > 0) {
            accumulated -= int32_t(fun_00587350(destination, destination, remaining, 1));
            accumulated -= int32_t(fun_00587350(destination + limb_words, destination + limb_words,
                                                remaining - limb_words, 1));
        }
    }
    if (accumulated == -1) {
        uint32_t* high = right_storage + total_words - output_words;
        if (fun_005873f0(high, high, output_words, 1) != 0) {
            fun_00587350(high - 1, high - 1, output_words + 1, 1);
            fun_00587350(right_storage + total_words - 1, right_storage + total_words - 1, 1, 1);
        }
    } else if (accumulated == 1) {
        const int32_t doubled = output_words * 2;
        if (total_words < doubled) {
            uint32_t* high = right_storage + total_words - output_words;
            fun_00587350(high, high, output_words, 1);
        } else {
            uint32_t* high = right_storage + total_words - doubled;
            uint32_t carry = fun_005873f0(high, high, doubled, 1);
            while (carry != 0)
                carry = fun_005873f0(high, high, doubled, carry);
        }
    }
    fun_0058af60(output, right_storage, output_words, total_words);
}

extern "C" void fun_0058aa40(uint32_t** left, uint32_t** right, int32_t limb_words,
                             int32_t points) {
    const bool square = left == right;
    if (limb_words < (square ? 678 : 834)) {
        auto* product = static_cast<uint32_t*>(__builtin_alloca(uint32_t(limb_words) * 8));
        for (int32_t index = 0; index < points; ++index) {
            uint32_t* first = left[index];
            uint32_t* second = right[index];
            if (square)
                fun_00586f70(product, first, limb_words);
            else
                fun_00588b40(product, first, second, limb_words);
            uint32_t carry = first[limb_words] == 0
                                 ? 0
                                 : fun_0058b2a0(product + limb_words, product + limb_words, second,
                                                uint32_t(limb_words));
            if (second[limb_words] != 0)
                carry += fun_0058b2a0(product + limb_words, product + limb_words, first,
                                      uint32_t(limb_words)) +
                         first[limb_words];
            if (carry != 0) {
                carry = fun_005873f0(product, product, limb_words * 2, carry);
                fun_005873f0(product, product, limb_words * 2, carry);
            }
            uint32_t high = 0;
            if (fun_00587610(first, product, product + limb_words, uint32_t(limb_words)) != 0)
                high = fun_005873f0(first, first, limb_words, 1) != 0;
            first[limb_words] = high;
        }
        return;
    }
    const int32_t depth = fun_00589960(limb_words, square);
    const int32_t count = int32_t(1u << (uint32_t(depth) & 31));
    const int32_t quantum = count < 33 ? 32 : count;
    const int32_t modulus_bits =
        ((quantum + 2 + (int32_t(uint32_t(limb_words) << 5) / count) * 2 + depth) / quantum) *
        quantum;
    const int32_t inner_words = modulus_bits / 32;
    auto** left_blocks = static_cast<uint32_t**>(__builtin_alloca(uint32_t(count) * 4));
    auto** right_blocks = static_cast<uint32_t**>(__builtin_alloca(uint32_t(count) * 4));
    const int32_t storage_words = (inner_words + 1) * count;
    auto* storage = static_cast<uint32_t*>(__builtin_alloca(uint32_t(storage_words) * 8));
    auto* scratch = static_cast<uint32_t*>(__builtin_alloca(uint32_t(inner_words + 1) * 4));
    auto** levels = static_cast<uint32_t**>(__builtin_alloca(uint32_t(depth + 1) * 4));
    for (int32_t index = 0; index <= depth; ++index)
        levels[index] =
            static_cast<uint32_t*>(__builtin_alloca((1u << (uint32_t(index) & 31)) * 4));
    fun_00589de0(levels, depth);
    for (int32_t index = 0; index < points; ++index) {
        fun_0058ad50(left[index], limb_words);
        if (!square)
            fun_0058ad50(right[index], limb_words);
        fun_0058a050(left[index], left[index], right[index], limb_words, depth, count, left_blocks,
                     right_blocks, storage, storage + storage_words, inner_words,
                     limb_words / count, modulus_bits / count, levels, scratch, 1);
    }
}

extern "C" void fun_0058b030(uint32_t* output, const uint32_t* left, int32_t left_words,
                             const uint32_t* right, int32_t right_words) {
    const int32_t total = left_words + right_words;
    const int32_t depth = fun_00589960(total, left == right && left_words == right_words);
    const int32_t rounded = fun_005899c0(total, uint32_t(depth));
    const uint32_t bytes = uint32_t(rounded) * 4 + 4;
    auto* temporary = static_cast<uint32_t*>(dat_0070c0d0(bytes));
    fun_00589a20(temporary, rounded, left, left_words, right, right_words, depth);
    copy_words(output, temporary, total);
    dat_0070c0d8(temporary, bytes);
}
