#include "bigint.h"

// Original mutually recursive normalized division helpers0058C040/0058C190.
// Numerator workspaces are modified in place; multiplication uses the actual
// recovered dispatcher and retains its real unresolved large-count branches.
extern "C" uint32_t fun_0058c040(uint32_t* quotient, uint32_t* numerator,
                                 const uint32_t* denominator, int32_t denominator_count) {
    if (denominator_count % 2 != 0) {
        const int32_t tail_count = denominator_count - 1;
        uint32_t* tail_quotient = quotient + 1;
        uint32_t high = fun_0058c040(tail_quotient, numerator + 2, denominator + 1, tail_count);
        uint32_t* lower_window = numerator + 1;
        const uint32_t carry =
            fun_0058b350(lower_window, tail_quotient, uint32_t(tail_count), denominator[0]);
        uint32_t borrow =
            fun_00587350(numerator + denominator_count, numerator + denominator_count, 1, carry);
        if (high != 0)
            borrow += fun_00587350(numerator + denominator_count, numerator + denominator_count, 1,
                                   denominator[0]);
        while (borrow != 0) {
            high -= fun_00587350(tail_quotient, tail_quotient, tail_count, 1);
            borrow -=
                fun_0058b2a0(lower_window, lower_window, denominator, uint32_t(denominator_count));
        }
        const uint32_t low_carry = fun_0058bd70(quotient, numerator, denominator_count + 1,
                                                denominator, denominator_count);
        return high + fun_005873f0(tail_quotient, tail_quotient, tail_count, low_carry);
    }
    const int32_t half = denominator_count / 2;
    uint32_t* upper_quotient = quotient + half;
    const uint32_t high = fun_0058c190(upper_quotient, numerator + half, denominator, half);
    const uint32_t carry = fun_0058c190(quotient, numerator, denominator, half);
    return high + fun_005873f0(upper_quotient, upper_quotient, half, carry);
}

extern "C" uint32_t fun_0058c190(uint32_t* quotient, uint32_t* numerator,
                                 const uint32_t* denominator, int32_t half_denominator_count) {
    const int32_t count = half_denominator_count;
    uint32_t high;
    if (count < 92)
        high = fun_0058bd70(quotient, numerator + count, count * 2, denominator + count, count);
    else
        high = fun_0058c040(quotient, numerator + count, denominator + count, count);
    uint32_t* product = static_cast<uint32_t*>(__builtin_alloca(uint32_t(count) * 8));
    fun_00588b40(product, quotient, denominator, count);
    uint32_t borrow = fun_00587610(numerator, numerator, product, uint32_t(count * 2));
    if (high != 0)
        borrow += fun_00587610(numerator + count, numerator + count, denominator, uint32_t(count));
    while (borrow != 0) {
        high -= fun_00587350(quotient, quotient, count, 1);
        borrow -= fun_0058b2a0(numerator, numerator, denominator, uint32_t(count * 2));
    }
    return high;
}
