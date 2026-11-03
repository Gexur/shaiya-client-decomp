#pragma once
#include <stdint.h>
extern "C" {
// Original shader resource setup, hidden ECX self, RET; no extra arguments.
__declspec(dllexport) int32_t __attribute__((thiscall)) FUN_00547cd0(void*);
}
