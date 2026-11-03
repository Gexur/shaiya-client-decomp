#pragma once
#include <stdint.h>
/**
 * @brief Multiply two split 64-bit unsigned integers, retaining the low 64 bits.
 * @param left_low Low word of the left operand.
 * @param left_high High word of the left operand.
 * @param right_low Low word of the right operand.
 * @param right_high High word of the right operand.
 * @return Product modulo 2^64 in EDX:EAX.
 * @note The four-word stdcall entry removes 16 argument bytes from the stack.
 */
extern "C" uint64_t __attribute__((stdcall)) multiply_uint64_words(uint32_t left_low,
                                                                   uint32_t left_high,
                                                                   uint32_t right_low,
                                                                   uint32_t right_high);
