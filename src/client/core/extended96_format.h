#pragma once
#include <stdint.h>
// Six original DWORDs consumed by005DCAF7, in their actual order.
struct OriginalExtended96Format {
    int32_t maximum_exponent;
    int32_t minimum_exponent;
    int32_t precision;
    int32_t shift;
    int32_t storage_bits;
    int32_t bias;
};
static_assert(sizeof(OriginalExtended96Format) == 24);
