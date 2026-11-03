#pragma once
#include "bigint.h"

extern "C" {
// Original cdecl FFT residue operations. Each residue has limb_words+1 words;
// the final word and the supplied scratch retain their original write order.
SHAIYA_BIGINT_EXPORT void fun_00589e50(uint32_t* value, int32_t exponent, int32_t limb_words,
                                       uint32_t* scratch);
SHAIYA_BIGINT_EXPORT void fun_0058a700(uint32_t* value, const uint32_t* addend, int32_t limb_words);
SHAIYA_BIGINT_EXPORT void fun_0058ad50(uint32_t* value, int32_t limb_words);
SHAIYA_BIGINT_EXPORT void fun_0058af20(uint32_t* value, int32_t exponent, int32_t limb_words,
                                       uint32_t* scratch);
SHAIYA_BIGINT_EXPORT void fun_0058af60(uint32_t* output, const uint32_t* input, int32_t limb_words,
                                       int32_t input_words);
}
