#include "bigint.h"

namespace {
uint32_t magnitude(uint32_t encoded_size) {
    return int32_t(encoded_size) < 0 ? 0u - encoded_size : encoded_size;
}

// The two original procedures differ at the right size's initial NEG. All
// later branch structure, growth timing, carry-word store and sign handling
// are identical. Factor that repeated source operation without replacing any
// limb arithmetic, callback, or alias path with a separate math implementation.
void add_with_encoded_sign(BigInt* output, const BigInt* left, const BigInt* right,
                           uint32_t right_sign) {
    uint32_t left_sign = uint32_t(left->signed_size);
    uint32_t left_count = magnitude(left_sign), right_count = magnitude(right_sign);
    const BigInt* larger = left;
    const BigInt* smaller = right;
    if (int32_t(left_count) < int32_t(right_count)) {
        larger = right;
        smaller = left;
        uint32_t temporary = left_count;
        left_count = right_count;
        right_count = temporary;
        temporary = left_sign;
        left_sign = right_sign;
        right_sign = temporary;
    }
    if (output->capacity < int32_t(left_count + 1))
        fun_00587300(output, int32_t(left_count + 1));
    // Original reloads these pointers after reallocation. This matters when the
    // result aliases either input object and the callback moved its limb buffer.
    const uint32_t* first = larger->limbs;
    const uint32_t* second = smaller->limbs;
    uint32_t* destination = output->limbs;
    if (int32_t(left_sign ^ right_sign) >= 0) {
        uint32_t carry =
            fun_00587590(destination, first, int32_t(left_count), second, int32_t(right_count));
        destination[left_count] = carry;
        uint32_t result_count = left_count + carry;
        output->signed_size = int32_t(int32_t(left_sign) < 0 ? 0u - result_count : result_count);
        return;
    }
    bool reverse_sign = false;
    if (left_count == right_count) {
        if (fun_00587660(first, second, int32_t(left_count)) < 0) {
            fun_00587610(destination, second, first, left_count);
            reverse_sign = true;
        } else {
            fun_00587610(destination, first, second, left_count);
        }
    } else {
        fun_005876a0(destination, first, int32_t(left_count), second, int32_t(right_count));
    }
    while (int32_t(left_count) > 0 && destination[left_count - 1] == 0)
        --left_count;
    bool negative = int32_t(left_sign) < 0;
    if (reverse_sign)
        negative = !negative;
    output->signed_size = int32_t(negative ? 0u - left_count : left_count);
}
} // namespace

extern "C" void fun_00586020(BigInt* output, const BigInt* left, const BigInt* right) {
    add_with_encoded_sign(output, left, right, uint32_t(right->signed_size));
}

extern "C" void fun_00586be0(BigInt* output, const BigInt* left, const BigInt* right) {
    add_with_encoded_sign(output, left, right, 0u - uint32_t(right->signed_size));
}
