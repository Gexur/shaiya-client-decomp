#include "bigint.h"

namespace {
void square_word(uint32_t* output, uint32_t input) {
    uint32_t low = input & 0xffff, high = input >> 16;
    uint32_t high_product = high * high;
    uint32_t cross = low * high;
    uint32_t middle = (low * low >> 16) + cross + high * low;
    if (middle < cross)
        high_product += 0x10000;
    output[1] = (middle >> 16) + high_product;
    output[0] = (middle << 16) + (low * low & 0xffff);
}
} // namespace

extern "C" void fun_0058b2f0(uint32_t* output, const uint32_t* left, int32_t left_count,
                             const uint32_t* right, int32_t right_count) {
    output[left_count] = fun_00587260(output, left, uint32_t(left_count), *right);
    if (right_count > 1) {
        for (int32_t i = 1; i < right_count; ++i) {
            ++right;
            ++output;
            output[left_count] = fun_00589590(output, left, uint32_t(left_count), *right);
        }
    }
}

extern "C" void fun_0058b0e0(uint32_t* output, const uint32_t* input, int32_t count) {
    // Original local_1D0[2] and immediately following local_1C8[456] form the
    // cross-product workspace. The observed square dispatcher selects count<58.
    uint32_t cross_products[116];
    square_word(output, input[0]);
    if (count > 1) {
        cross_products[count - 1] =
            fun_00587260(cross_products, input + 1, uint32_t(count - 1), input[0]);
        for (int32_t i = 0; i < count - 2; ++i) {
            cross_products[count + i] = fun_00589590(cross_products + 2 + 2 * i, input + 2 + i,
                                                     uint32_t(count - 2 - i), input[1 + i]);
        }
        for (int32_t i = 1; i < count; ++i)
            square_word(output + 2 * i, input[i]);
        uint32_t words = uint32_t(count) * 2 - 2;
        uint32_t high = fun_00587480(cross_products, cross_products, words, 1);
        uint32_t carry = fun_0058b2a0(output + 1, output + 1, cross_products, words);
        output[uint32_t(count) * 2 - 1] += high + carry;
    }
}
