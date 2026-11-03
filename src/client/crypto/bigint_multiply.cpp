#include "bigint.h"

// Original 0x587030, cdecl: output, left, left_count, right, right_count.
// The original callers supply left_count >= right_count. The equal-input,
// base, repeated equal-block and final unequal-block paths below retain their
// original thresholds, add-with-carry order and highest-output-word return.
extern "C" SHAIYA_BIGINT_EXPORT uint32_t fun_00587030(uint32_t* output, const uint32_t* left,
                                                      int32_t left_count, const uint32_t* right,
                                                      int32_t right_count) {
    uint32_t* const original_output = output;
    const int32_t total = left_count + right_count;
    if (left == right && left_count == right_count) {
        fun_00586f70(output, left, left_count);
        return original_output[total - 1];
    }
    if (right_count < 22) {
        fun_0058b2f0(output, left, left_count, right, right_count);
        return original_output[total - 1];
    }
    fun_00588b40(output, left, right, right_count);
    if (left_count == right_count)
        return original_output[total - 1];

    int32_t existing = right_count;
    output += right_count;
    left += right_count;
    left_count -= right_count;
    int32_t small = right_count;
    if (left_count < small) {
        const uint32_t* remaining = left;
        left = right;
        right = remaining;
        small = left_count;
        left_count = right_count;
    }
    const int32_t temporary_words = (small > 21 ? small : left_count) + small;
    uint32_t* temporary = static_cast<uint32_t*>(__builtin_alloca(uint32_t(temporary_words) * 4));
    uint32_t carry = 0;
    while (small > 21) {
        fun_00588b40(temporary, left, right, small);
        const int32_t product_words = small * 2;
        if (product_words < existing) {
            const uint32_t low_carry = fun_0058b2a0(output, output, temporary, product_words);
            carry += fun_005873f0(output + product_words, output + product_words,
                                  existing - product_words, low_carry);
        } else {
            carry += fun_0058b2a0(output, output, temporary, existing);
            if (existing != product_words) {
                carry = fun_005873f0(output + existing, temporary + existing,
                                     product_words - existing, carry);
                existing = product_words;
            }
        }
        output += small;
        left += small;
        existing -= small;
        left_count -= small;
        if (left_count < small) {
            const uint32_t* remaining = left;
            left = right;
            right = remaining;
            const int32_t previous = small;
            small = left_count;
            left_count = previous;
        }
    }
    if (small != 0) {
        fun_0058b2f0(temporary, left, left_count, right, small);
        const int32_t product_words = left_count + small;
        if (product_words < existing) {
            const uint32_t low_carry = fun_0058b2a0(output, output, temporary, product_words);
            fun_005873f0(output + product_words, output + product_words, existing - product_words,
                         low_carry);
        } else {
            const uint32_t low_carry = fun_0058b2a0(output, output, temporary, existing);
            if (existing != product_words)
                fun_005873f0(output + existing, temporary + existing, product_words - existing,
                             carry + low_carry);
        }
    }
    return original_output[total - 1];
}

// Original 0x585df0: signed BigInt multiplication. In particular, growth of an
// aliased output retains the old limb allocation until multiplication completes;
// growth of a distinct output frees it first. Sufficient-capacity aliases use a
// copied stack input. These are original ownership paths, not a new alias rule.
extern "C" SHAIYA_BIGINT_EXPORT void fun_00585df0(BigInt* output, const BigInt* left,
                                                  const BigInt* right) {
    const uint32_t sign = uint32_t(left->signed_size) ^ uint32_t(right->signed_size);
    uint32_t large = uint32_t(left->signed_size);
    uint32_t small = uint32_t(right->signed_size);
    if (int32_t(large) < 0)
        large = 0u - large;
    if (int32_t(small) < 0)
        small = 0u - small;
    if (int32_t(large) < int32_t(small)) {
        const BigInt* previous = left;
        left = right;
        right = previous;
        const uint32_t size = large;
        large = small;
        small = size;
    }
    if (small == 0) {
        output->signed_size = 0;
        return;
    }
    if (small == 1) {
        if (output->capacity < int32_t(large + 1))
            fun_00587300(output, int32_t(large + 1));
        uint32_t* destination = output->limbs;
        const uint32_t carry = fun_00587260(destination, left->limbs, large, right->limbs[0]);
        destination[large] = carry;
        const uint32_t size = large + (carry != 0);
        output->signed_size = int32_t(int32_t(sign) < 0 ? 0u - size : size);
        return;
    }
    const uint32_t* left_limbs = left->limbs;
    const uint32_t* right_limbs = right->limbs;
    uint32_t* destination = output->limbs;
    uint32_t* deferred_free = nullptr;
    uint32_t deferred_words = 0;
    const uint32_t total = large + small;
    if (output->capacity < int32_t(total)) {
        if (destination != left_limbs && destination != right_limbs) {
            dat_0070c0d8(destination, uint32_t(output->capacity) * 4);
        } else {
            deferred_free = destination;
            deferred_words = uint32_t(output->capacity);
        }
        output->capacity = int32_t(total);
        destination = static_cast<uint32_t*>(dat_0070c0d0(total * 4));
        output->limbs = destination;
    } else if (destination == left_limbs) {
        uint32_t* copy = static_cast<uint32_t*>(__builtin_alloca(large * 4));
        for (uint32_t index = 0; index != large; ++index)
            copy[index] = destination[index];
        left_limbs = copy;
        if (destination == right_limbs)
            right_limbs = copy;
    } else if (destination == right_limbs) {
        uint32_t* copy = static_cast<uint32_t*>(__builtin_alloca(small * 4));
        for (uint32_t index = 0; index != small; ++index)
            copy[index] = destination[index];
        right_limbs = copy;
    }
    const uint32_t highest =
        fun_00587030(destination, left_limbs, int32_t(large), right_limbs, int32_t(small));
    const uint32_t size = total - (highest == 0);
    output->signed_size = int32_t(int32_t(sign) < 0 ? 0u - size : size);
    if (deferred_free != nullptr)
        dat_0070c0d8(deferred_free, deferred_words * 4);
}
