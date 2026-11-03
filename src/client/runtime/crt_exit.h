#pragma once
#include <stdint.h>
extern "C" {
extern uint8_t dat_0224ee20;
extern uint32_t dat_0224ee24, dat_0224ee28;
void fun_005ce05d(uint32_t status, int32_t quick, int32_t return_to_caller);
// The original finally entry additionally consumes its enclosing EBP andEDI=0.
// This explicit source operand is the original third argument at[EBP+10].
void fun_005ce10c(int32_t return_to_caller);
void fun_005ce120(int32_t status);
void fun_005ce131(int32_t status);
void fun_005ce142();
void fun_005ce151();
[[noreturn]] void fun_005cdf99(int32_t status);
}
