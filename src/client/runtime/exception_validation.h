#pragma once
#include <stdint.h>

extern "C" {
// Canonical zero-filled image locations shared by the recovered EH3 validator.
extern int32_t dat_0224f0c0;
extern uint32_t dat_0224f0c8[16];
extern volatile int32_t dat_0224f108;
int32_t fun_005da2a6(const void* frame);
}
