#pragma once
#include "bigint.h"
#include "bigint_fft_helpers.h"

extern "C" {
void fun_00589a20(uint32_t* output, int32_t output_words, const uint32_t* left, int32_t left_words,
                  const uint32_t* right, int32_t right_words, int32_t depth);
void fun_0058a050(uint32_t* output, const uint32_t* left, const uint32_t* right,
                  int32_t output_words, int32_t depth, int32_t points, uint32_t** left_blocks,
                  uint32_t** right_blocks, uint32_t* left_storage, uint32_t* right_storage,
                  int32_t limb_words, int32_t chunk_words, int32_t twiddle_step, uint32_t** levels,
                  uint32_t* scratch, int32_t initialize);
void fun_0058a540(uint32_t** blocks, int32_t points, uint32_t** level_slot, int32_t twiddle_step,
                  int32_t limb_words, int32_t stride, uint32_t* scratch);
void fun_0058a770(uint32_t** left, uint32_t** right, int32_t points, uint32_t** level_slot,
                  int32_t twiddle_step, int32_t limb_words, int32_t stride, uint32_t* scratch);
void fun_0058aa40(uint32_t** left, uint32_t** right, int32_t limb_words, int32_t points);
void fun_0058ad90(uint32_t** blocks, int32_t points, int32_t twiddle_step, int32_t limb_words,
                  uint32_t* scratch);
}
