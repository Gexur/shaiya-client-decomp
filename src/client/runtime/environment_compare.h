#pragma once
#include <stdint.h>
extern "C" {
extern uint32_t dat_0224f2e4;
// Original5e1241 receives source in EAX and count on the stack.
uint32_t fun_005e1241(const char* source, uint32_t count);
int32_t fun_005e125d(uint32_t locale, uint32_t flags, const char* left, int32_t left_length,
                     const char* right, int32_t right_length, uint32_t code_page);
}
