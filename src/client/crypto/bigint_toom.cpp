#include "bigint_toom.h"

namespace {
// Factored repeated original branch sequences, not additional original
// procedures or replacement algorithms. Every leaf remains an address-named
// implementation recovered from the same executable.
void multiply_part(uint32_t* output, const uint32_t* left, const uint32_t* right, int32_t count,
                   uint32_t* scratch) {
    if (count < 22)
        fun_0058b2f0(output, left, count, right, count);
    else if (count < 278)
        fun_00587720(output, left, right, count, scratch);
    else
        fun_00587e90(output, left, right, count, scratch);
}

void square_part(uint32_t* output, const uint32_t* input, int32_t count, uint32_t* scratch) {
    if (count < 58)
        fun_0058b0e0(output, input, count);
    else if (count < 226)
        fun_00587bb0(output, input, uint32_t(count), scratch);
    else
        fun_00588790(output, input, count, scratch);
}

void copy_words(uint32_t* output, const uint32_t* input, int32_t count) {
    if (count != 0)
        do {
            *output++ = *input++;
        } while (--count != 0);
}

void add_high_word(uint32_t* word, uint32_t value) {
    *word += value;
    if (*word < value) {
        do {
            ++word;
            ++*word;
        } while (*word == 0);
    }
}
} // namespace

extern "C" void fun_00588320(uint32_t* scaled_half, uint32_t* at_one, uint32_t* at_two,
                             uint32_t* scaled_half_high, uint32_t* at_one_high,
                             uint32_t* at_two_high, const uint32_t* a0, const uint32_t* a1,
                             const uint32_t* a2, int32_t count, int32_t top_count) {
    const uint32_t a1_high = fun_00587480(at_one, a1, uint32_t(count), 1);
    const uint32_t a0_high = fun_00587480(scaled_half, a0, uint32_t(count), 2);
    const uint32_t sum_high = fun_0058b2a0(scaled_half, scaled_half, at_one, uint32_t(count));
    uint32_t top_high = fun_0058b2a0(scaled_half, scaled_half, a2, uint32_t(top_count));
    if (top_count != count)
        top_high = fun_005873f0(scaled_half + top_count, scaled_half + top_count, count - top_count,
                                top_high);
    *scaled_half_high = a0_high + sum_high + a1_high + top_high;

    uint32_t a2_high = fun_00587480(at_two, a2, uint32_t(top_count), 2);
    if (top_count != count) {
        at_two[count - 1] = 0;
        at_two[top_count] = a2_high;
        a2_high = 0;
    }
    const uint32_t first_high = fun_0058b2a0(at_two, at_two, at_one, uint32_t(count));
    const uint32_t second_high = fun_0058b2a0(at_two, at_two, a0, uint32_t(count));
    *at_two_high = second_high + a2_high + first_high + a1_high;

    const uint32_t one_high = fun_0058b2a0(at_one, a0, a1, uint32_t(count));
    uint32_t one_top_high = fun_0058b2a0(at_one, at_one, a2, uint32_t(top_count));
    if (top_count != count)
        one_top_high =
            fun_005873f0(at_one + top_count, at_one + top_count, count - top_count, one_top_high);
    *at_one_high = one_high + one_top_high;
}

extern "C" void fun_00588460(const uint32_t* low_product, uint32_t* scaled_half_product,
                             uint32_t* at_one_product, uint32_t* at_two_product,
                             const uint32_t* high_product, uint32_t* scaled_half_high,
                             uint32_t* at_one_high, uint32_t* at_two_high, int32_t product_count,
                             int32_t top_product_count) {
    uint32_t* temporary = static_cast<uint32_t*>(__builtin_alloca(uint32_t(product_count) * 4));
    const uint32_t half_high = *scaled_half_high;
    const uint32_t one_high = *at_one_high;
    const uint32_t two_high = *at_two_high;
    uint32_t shift = fun_00587480(temporary, low_product, uint32_t(product_count), 4);
    uint32_t borrow =
        fun_00587610(scaled_half_product, scaled_half_product, temporary, uint32_t(product_count));
    uint32_t top_borrow = fun_00587610(scaled_half_product, scaled_half_product, high_product,
                                       uint32_t(top_product_count));
    if (top_product_count != product_count)
        top_borrow = fun_00587350(scaled_half_product + top_product_count,
                                  scaled_half_product + top_product_count,
                                  product_count - top_product_count, top_borrow);
    const uint32_t half_remaining_high = (half_high - (borrow + shift)) - top_borrow;

    borrow = fun_00587610(at_one_product, at_one_product, low_product, uint32_t(product_count));
    top_borrow =
        fun_00587610(at_one_product, at_one_product, high_product, uint32_t(top_product_count));
    if (top_product_count != product_count)
        top_borrow =
            fun_00587350(at_one_product + top_product_count, at_one_product + top_product_count,
                         product_count - top_product_count, top_borrow);
    const uint32_t one_remaining_high = (one_high - borrow) - top_borrow;

    uint32_t high = fun_00587480(temporary, high_product, uint32_t(top_product_count), 4);
    high += fun_0058b2a0(temporary, temporary, low_product, uint32_t(top_product_count));
    if (top_product_count != product_count)
        high = fun_005873f0(temporary + top_product_count, low_product + top_product_count,
                            product_count - top_product_count, high);
    borrow = fun_00587610(at_two_product, at_two_product, temporary, uint32_t(product_count));
    const uint32_t two_remaining_high = two_high - (borrow + high);
    const uint32_t sum_carry =
        fun_0058b2a0(temporary, scaled_half_product, at_two_product, uint32_t(product_count));
    const uint32_t difference_borrow =
        fun_00587610(at_two_product, scaled_half_product, at_two_product, uint32_t(product_count));
    copy_words(scaled_half_product, temporary, product_count);

    shift = fun_00587480(temporary, at_one_product, uint32_t(product_count), 3);
    borrow =
        fun_00587610(scaled_half_product, scaled_half_product, temporary, uint32_t(product_count));
    const uint32_t combined_high = (sum_carry + two_remaining_high + half_remaining_high) -
                                   (borrow + shift + one_remaining_high * 8);
    shift = fun_00587480(at_one_product, at_one_product, uint32_t(product_count), 1);
    borrow =
        fun_00587610(at_one_product, at_one_product, scaled_half_product, uint32_t(product_count));
    const uint32_t middle_high = (shift + one_remaining_high * 2) - (borrow + combined_high);

    const uint32_t divide_carry = fun_0058b480(at_two_product, at_two_product, product_count, 0);
    const uint32_t divided_high =
        divide_carry * 0x55555555u +
        ((half_remaining_high - two_remaining_high) - difference_borrow) * 0xaaaaaaabu;
    const uint32_t carry =
        fun_0058b2a0(temporary, scaled_half_product, at_two_product, uint32_t(product_count));
    const uint32_t first_high = carry + divided_high + combined_high;
    borrow =
        fun_00587610(at_two_product, scaled_half_product, at_two_product, uint32_t(product_count));
    const uint32_t last_high = (combined_high - divided_high) - borrow;
    copy_words(scaled_half_product, temporary, product_count);

    fun_00587510(scaled_half_product, scaled_half_product, uint32_t(product_count), 2);
    scaled_half_product[product_count - 1] |= first_high * 0x40000000u;
    fun_00587510(at_one_product, at_one_product, uint32_t(product_count), 1);
    at_one_product[product_count - 1] |= middle_high * 0x80000000u;
    fun_00587510(at_two_product, at_two_product, uint32_t(product_count), 2);
    at_two_product[product_count - 1] |= last_high * 0x40000000u;
    *scaled_half_high = first_high >> 2;
    *at_one_high = middle_high >> 1;
    *at_two_high = last_high >> 2;
}

extern "C" void fun_00587e90(uint32_t* output, const uint32_t* left, const uint32_t* right,
                             int32_t count, uint32_t* scratch) {
    int32_t top_count = count / 3;
    int32_t third = top_count;
    if (count != top_count * 3)
        ++third;
    if (count % 3 == 1)
        --top_count;
    const int32_t product_count = third * 2;
    uint32_t* one_product = output + third * 2;
    uint32_t* two_product = scratch + third * 2;
    uint32_t* high_product = output + third * 4;
    uint32_t* extra = scratch + third * 4;
    uint32_t* right_half = output + third;
    uint32_t* right_one = scratch + third;
    uint32_t* right_two = output + third * 3;
    uint32_t left_half_high, left_one_high, left_two_high;
    uint32_t right_half_high, right_one_high, right_two_high;
    fun_00588320(output, scratch, one_product, &left_half_high, &left_one_high, &left_two_high,
                 left, left + third, left + third * 2, third, top_count);
    fun_00588320(right_half, right_one, right_two, &right_half_high, &right_one_high,
                 &right_two_high, right, right + third, right + third * 2, third, top_count);

    multiply_part(two_product, one_product, right_two, third, extra);
    uint32_t two_high = right_two_high * left_two_high;
    if (left_two_high != 0)
        two_high += fun_00589590(two_product + third, right_two, uint32_t(third), left_two_high);
    if (right_two_high != 0)
        two_high += fun_00589590(two_product + third, one_product, uint32_t(third), right_two_high);

    multiply_part(one_product, scratch, right_one, third, extra);
    uint32_t one_high = right_one_high * left_one_high;
    uint32_t* shifted = nullptr;
    if (left_one_high != 0) {
        if (left_one_high == 1)
            one_high += fun_0058b2a0(right_two, right_two, right_one, uint32_t(third));
        else {
            shifted = static_cast<uint32_t*>(__builtin_alloca(uint32_t(third) * 4));
            const uint32_t shift_carry = fun_00587480(shifted, right_one, uint32_t(third), 1);
            one_high += shift_carry + fun_0058b2a0(right_two, right_two, shifted, uint32_t(third));
        }
    }
    if (right_one_high != 0) {
        if (right_one_high == 1)
            one_high += fun_0058b2a0(right_two, right_two, scratch, uint32_t(third));
        else {
            if (shifted == nullptr)
                shifted = static_cast<uint32_t*>(__builtin_alloca(uint32_t(third) * 4));
            const uint32_t shift_carry = fun_00587480(shifted, scratch, uint32_t(third), 1);
            one_high += shift_carry + fun_0058b2a0(right_two, right_two, shifted, uint32_t(third));
        }
    }

    multiply_part(scratch, output, right_half, third, extra);
    uint32_t half_high = right_half_high * left_half_high;
    if (left_half_high != 0)
        half_high += fun_00589590(right_one, right_half, uint32_t(third), left_half_high);
    if (right_half_high != 0)
        half_high += fun_00589590(right_one, output, uint32_t(third), right_half_high);

    multiply_part(output, left, right, third, extra);
    multiply_part(high_product, left + third * 2, right + third * 2, top_count, extra);
    fun_00588460(output, scratch, one_product, two_product, high_product, &half_high, &one_high,
                 &two_high, product_count, top_count * 2);
    half_high += fun_0058b2a0(output + third, output + third, scratch, uint32_t(product_count));
    const uint32_t carry =
        fun_0058b2a0(output + third * 3, output + third * 3, two_product, uint32_t(product_count));
    add_high_word(output + third * 3, half_high);
    add_high_word(high_product, one_high);
    add_high_word(output + third * 5, two_high + carry);
}

extern "C" void fun_00588790(uint32_t* output, const uint32_t* input, int32_t count,
                             uint32_t* scratch) {
    int32_t top_count = count / 3;
    int32_t third = top_count;
    if (count % 3 != 0)
        ++third;
    if (count % 3 == 1)
        --top_count;
    const int32_t product_count = third * 2;
    uint32_t* one_product = output + third * 2;
    uint32_t* two_product = scratch + third * 2;
    uint32_t* high_product = output + third * 4;
    uint32_t* extra = scratch + third * 4;
    uint32_t half_high, one_high, two_high;
    fun_00588320(output, scratch, one_product, &half_high, &one_high, &two_high, input,
                 input + third, input + third * 2, third, top_count);

    square_part(two_product, one_product, third, extra);
    uint32_t two_product_high = two_high * two_high;
    if (two_high != 0)
        two_product_high +=
            fun_00589590(two_product + third, one_product, uint32_t(third), two_high * 2);

    square_part(one_product, scratch, third, extra);
    uint32_t one_product_high = one_high * one_high;
    if (one_high != 0) {
        uint32_t* shifted = static_cast<uint32_t*>(__builtin_alloca(uint32_t(third) * 4));
        uint32_t shift_carry = fun_00587480(shifted, scratch, uint32_t(third), 1);
        one_product_high += shift_carry + fun_0058b2a0(one_product + third, one_product + third,
                                                       shifted, uint32_t(third));
        if (one_high == 2) {
            shift_carry = fun_00587480(shifted, scratch, uint32_t(third), 1);
            one_product_high += shift_carry + fun_0058b2a0(one_product + third, one_product + third,
                                                           shifted, uint32_t(third));
        }
    }

    square_part(scratch, output, third, extra);
    uint32_t half_product_high = half_high * half_high;
    if (half_high != 0)
        half_product_high += fun_00589590(scratch + third, output, uint32_t(third), half_high * 2);
    square_part(output, input, third, extra);
    square_part(high_product, input + third * 2, top_count, extra);
    fun_00588460(output, scratch, one_product, two_product, high_product, &half_product_high,
                 &one_product_high, &two_product_high, product_count, top_count * 2);
    half_product_high +=
        fun_0058b2a0(output + third, output + third, scratch, uint32_t(product_count));
    const uint32_t carry =
        fun_0058b2a0(output + third * 3, output + third * 3, two_product, uint32_t(product_count));
    add_high_word(output + third * 3, half_product_high);
    add_high_word(high_product, one_product_high);
    add_high_word(output + third * 5, two_product_high + carry);
}
