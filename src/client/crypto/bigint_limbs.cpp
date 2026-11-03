#include "bigint.h"

namespace {
struct WordProduct {
    uint32_t low, high;
};

// Original 16-bit partial-product sequence shared by 00587260, 00589590 and
// 0058B350. All operations wrap as the observed unsigned x86 instructions do.
WordProduct multiply_words(uint32_t input, uint32_t multiplier) {
    uint32_t low_input = input & 0xffff, high_input = input >> 16;
    uint32_t low_multiplier = multiplier & 0xffff, high_multiplier = multiplier >> 16;
    uint32_t low = low_multiplier * low_input;
    uint32_t cross = low_multiplier * high_input;
    uint32_t high = high_multiplier * high_input;
    uint32_t middle = (low >> 16) + cross + high_multiplier * low_input;
    if (middle < cross)
        high += 0x10000;
    return {(middle << 16) + (low & 0xffff), high + (middle >> 16)};
}

void copy_tail(uint32_t* output, const uint32_t* input, int32_t first, int32_t count) {
    if (output != input)
        for (int32_t i = first; i < count; ++i)
            output[i] = input[i];
}
} // namespace

extern "C" int32_t fun_00587660(const uint32_t* left, const uint32_t* right, int32_t count) {
    int32_t index = count - 1;
    while (index >= 0) {
        uint32_t value = left[index], other = right[index];
        if (value != other)
            return value > other ? 1 : -1;
        --index;
    }
    return 0;
}

extern "C" uint32_t fun_0058b2a0(uint32_t* output, const uint32_t* left, const uint32_t* right,
                                 uint32_t count) {
    uint32_t carry = 0;
    do {
        uint32_t value = *left++, partial = *right++ + value;
        uint32_t result = partial + carry;
        *output++ = result;
        carry = uint32_t(result < partial || partial < value);
    } while (--count != 0);
    return carry;
}

extern "C" uint32_t fun_00587610(uint32_t* output, const uint32_t* left, const uint32_t* right,
                                 uint32_t count) {
    uint32_t borrow = 0;
    do {
        uint32_t value = *left++, partial = value - *right++;
        uint32_t result = partial - borrow;
        *output++ = result;
        borrow = uint32_t(partial < result || value < partial);
    } while (--count != 0);
    return borrow;
}

extern "C" uint32_t fun_005873f0(uint32_t* output, const uint32_t* input, int32_t count,
                                 uint32_t addend) {
    uint32_t first = input[0];
    output[0] = first + addend;
    if (first + addend < addend) {
        int32_t index = 1;
        if (count < 2)
            return 1;
        do {
            uint32_t value = input[index] + 1;
            output[index++] = value;
            if (value != 0) {
                copy_tail(output, input, index, count);
                return 0;
            }
        } while (index < count);
        return 1;
    }
    copy_tail(output, input, 1, count);
    return 0;
}

extern "C" uint32_t fun_00587350(uint32_t* output, const uint32_t* input, int32_t count,
                                 uint32_t subtrahend) {
    uint32_t first = input[0];
    output[0] = first - subtrahend;
    if (first < subtrahend) {
        int32_t index = 1;
        if (count < 2)
            return 1;
        do {
            uint32_t value = input[index];
            output[index++] = value - 1;
            if (value != 0) {
                copy_tail(output, input, index, count);
                return 0;
            }
        } while (index < count);
        return 1;
    }
    copy_tail(output, input, 1, count);
    return 0;
}

extern "C" uint32_t fun_00587480(uint32_t* output, const uint32_t* input, uint32_t count,
                                 uint32_t shift) {
    uint32_t bits = shift & 31, complement = (32 - shift) & 31;
    uint32_t index = count - 1, current = input[index];
    uint32_t carry = current >> complement;
    uint32_t value = current << bits;
    while (index != 0) {
        current = input[index - 1];
        output[index--] = (current >> complement) | value;
        value = current << bits;
    }
    output[0] = value;
    return carry;
}

extern "C" uint32_t fun_00587510(uint32_t* output, const uint32_t* input, uint32_t count,
                                 uint32_t shift) {
    uint32_t bits = shift & 31, complement = (32 - shift) & 31;
    uint32_t current = input[0], carry = current << complement;
    uint32_t value = current >> bits;
    for (uint32_t i = 1; i < count; ++i) {
        current = input[i];
        output[i - 1] = (current << complement) | value;
        value = current >> bits;
    }
    output[count - 1] = value;
    return carry;
}

extern "C" uint32_t fun_00587260(uint32_t* output, const uint32_t* input, uint32_t count,
                                 uint32_t multiplier) {
    uint32_t carry = 0;
    do {
        WordProduct product = multiply_words(*input++, multiplier);
        uint32_t value = product.low + carry;
        *output++ = value;
        carry = uint32_t(value < carry) + product.high;
    } while (--count != 0);
    return carry;
}

extern "C" uint32_t fun_00589590(uint32_t* output, const uint32_t* input, uint32_t count,
                                 uint32_t multiplier) {
    uint32_t carry = 0;
    do {
        WordProduct product = multiply_words(*input++, multiplier);
        uint32_t value = product.low + carry, before = *output;
        uint32_t result = value + before;
        *output++ = result;
        carry = uint32_t(value < carry) + product.high + uint32_t(result < before);
    } while (--count != 0);
    return carry;
}

extern "C" uint32_t fun_0058b350(uint32_t* output, const uint32_t* input, uint32_t count,
                                 uint32_t multiplier) {
    uint32_t carry = 0;
    do {
        WordProduct product = multiply_words(*input++, multiplier);
        uint32_t value = product.low + carry, before = *output;
        uint32_t result = before - value;
        *output++ = result;
        carry = uint32_t(value < carry) + product.high + uint32_t(before < result);
    } while (--count != 0);
    return carry;
}

extern "C" uint32_t fun_0058b480(uint32_t* output, const uint32_t* input, int32_t count,
                                 uint32_t carry) {
    int32_t i = 0;
    do {
        uint32_t before = input[i], difference = before - carry;
        uint32_t value = difference * 0xaaaaaaab;
        output[i++] = value;
        carry = uint32_t(value > 0x55555555) + uint32_t(before < difference) +
                uint32_t(value > 0xaaaaaaaa);
    } while (i < count);
    return carry;
}

extern "C" uint32_t fun_00587590(uint32_t* output, const uint32_t* left, int32_t left_count,
                                 const uint32_t* right, int32_t right_count) {
    if (right_count != 0 && fun_0058b2a0(output, left, right, uint32_t(right_count)) != 0) {
        while (right_count < left_count) {
            uint32_t value = left[right_count] + 1;
            output[right_count++] = value;
            if (value != 0) {
                copy_tail(output, left, right_count, left_count);
                return 0;
            }
        }
        return 1;
    }
    copy_tail(output, left, right_count, left_count);
    return 0;
}

extern "C" uint32_t fun_005876a0(uint32_t* output, const uint32_t* left, int32_t left_count,
                                 const uint32_t* right, int32_t right_count) {
    if (right_count != 0 && fun_00587610(output, left, right, uint32_t(right_count)) != 0) {
        while (right_count < left_count) {
            uint32_t value = left[right_count];
            output[right_count++] = value - 1;
            if (value != 0) {
                copy_tail(output, left, right_count, left_count);
                return 0;
            }
        }
        return 1;
    }
    copy_tail(output, left, right_count, left_count);
    return 0;
}
