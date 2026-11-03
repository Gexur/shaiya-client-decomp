#pragma once

#include "bigint.h"

extern "C" {
// Original00588320: eleven ordinary x86 cdecl arguments. The first three
// arrays hold (4*a0+2*a1+a2), (a0+a1+a2), (a0+2*a1+4*a2) moduloB^count;
// the following three pointers receive their separate high words. The original
// callers supply top_count=count,count-1 orcount-2; no padding policy is invented.
SHAIYA_BIGINT_EXPORT void fun_00588320(uint32_t* scaled_half, uint32_t* at_one, uint32_t* at_two,
                                       uint32_t* scaled_half_high, uint32_t* at_one_high,
                                       uint32_t* at_two_high, const uint32_t* a0,
                                       const uint32_t* a1, const uint32_t* a2, int32_t count,
                                       int32_t top_count);

// Original00588460: ten ordinary x86 cdecl arguments. It rewrites the three
// middle product arrays and their high words using the original interpolation
// sequence. low_product/high_product remain input arrays; top_product_count may
// be smaller thanproduct_count by2 or4 words in the original Toom callers.
SHAIYA_BIGINT_EXPORT void fun_00588460(const uint32_t* low_product, uint32_t* scaled_half_product,
                                       uint32_t* at_one_product, uint32_t* at_two_product,
                                       const uint32_t* high_product, uint32_t* scaled_half_high,
                                       uint32_t* at_one_high, uint32_t* at_two_high,
                                       int32_t product_count, int32_t top_product_count);
}
