#pragma once
#include "extended96.h"
extern "C" {
// Original12-byte record to binary64/binary32, status in EAX; cdecl.
int32_t fun_005dcc4f(const OriginalExtended96* source, void* binary64);
int32_t fun_005dcc65(const OriginalExtended96* source, void* binary32);
}
