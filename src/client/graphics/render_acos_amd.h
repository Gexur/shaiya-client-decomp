#pragma once
#include <stdint.h>
extern "C" {
extern const uint32_t dat_006f0168[2];
extern uint32_t dat_00717e18[1];
extern uint32_t dat_00717e28[1];
extern uint32_t dat_00717e2c[1];
extern uint32_t dat_00717e34[1];
extern uint32_t dat_00717e60[1];
extern uint32_t dat_00717e64[1];
extern uint32_t dat_00717e68[1];
extern uint32_t dat_00717e6c[1];
extern uint32_t dat_00717e70[1];
extern uint32_t dat_00717e74[1];
extern uint32_t dat_00717e78[1];
// CustomMM0 entries preserve allgeneral registers/EFLAGS; explicitasm calls only.
void FUN_006a6940();
void FUN_006a6a40();
void __attribute__((stdcall)) FUN_00685032(const void*, void*, void*);
}
