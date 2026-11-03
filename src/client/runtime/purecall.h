#pragma once
#include <stdint.h>
using OriginalPureCallHandler = void(__attribute__((cdecl)) *)();
extern "C" {
extern OriginalPureCallHandler dat_0224ee2c;
// The original fatal backend can be replaced by its real runtime-exit
// callback. If it returns, this function retains that call's residual EAX.
uint32_t fun_005ce71d();
uint32_t _purecall();
}
