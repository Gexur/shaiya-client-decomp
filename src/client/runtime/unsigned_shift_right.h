#pragma once
#include <stdint.h>
// Original compiler-helper ABI: EDX:EAX is the value and CL is the count.
// RET0 returns EDX:EAX and preserves/updates ECX exactly as the original.
// Invoke through an explicit register bridge, not an ordinary C++ call.
extern "C" void FUN_006aa840();
