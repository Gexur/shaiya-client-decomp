#pragma once
#include "stdio.h"
extern "C" {
extern uint32_t dat_0070e4e0;
// Original5d3ea0 consumes FILE in EDX; this explicit C++ interface normalizes it.
int32_t fun_005d3ea0(OriginalFile* file);
int32_t fun_005d8a13(OriginalFile* file);
int32_t fun_005dd176(int32_t character, OriginalFile* file);
}
