#pragma once
#include "../core/extended96.h"
extern "C" {
// All five entries use the original cdecl stack interface.
void fun_005e056b(const int8_t* digits, uint32_t count, OriginalExtended96* output);
uint32_t fun_005decd2(OriginalExtended96* output, const char** end, const char* input,
                      int32_t keep_guard, int32_t default_power, int32_t implicit_fraction,
                      int32_t bare_exponent);
int32_t fun_005dcc7b(void* binary64, const char* input);
int32_t fun_005dccc0(void* binary32, const char* input);
void* fun_005d2bbd(int32_t binary64, void* output, const char* input);
}
