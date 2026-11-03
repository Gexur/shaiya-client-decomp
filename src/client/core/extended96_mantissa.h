#pragma once
#include "extended96.h"
#include "extended96_format.h"
extern "C" {
int32_t fun_005dc957(const void* mantissa, int32_t bit);
int32_t fun_005dc989(void* mantissa, int32_t bit);
int32_t fun_005dc9d6(void* mantissa, int32_t bit);
void fun_005dca48(void* destination, const void* source);
int32_t fun_005dca63(const void* mantissa);
void fun_005dca7c(void* mantissa, int32_t shift);
int32_t fun_005dcaf7(const OriginalExtended96*, void* destination, const OriginalExtended96Format*);
}
