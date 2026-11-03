#pragma once
#include <stdint.h>
extern "C" {
// Original5277a0 has no explicit stack operands. Its old private DWORDs are
// observable inputs on one original path; the adapter retains that backing.
uint32_t __attribute__((thiscall)) FUN_005277a0(void*);
}
