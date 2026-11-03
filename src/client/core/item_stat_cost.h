#pragma once
#include <stdint.h>
extern "C" {
// Callee pops4 bytes and overwrites that actual input word with each rounded
// single-precision ratio. EAX is the wrapped original integer accumulator.
uint32_t __attribute__((stdcall)) FUN_004cbf50(uint32_t);
extern const uint32_t dat_006c2bb4;
// Existing1.0 declaration is in startup/render_project_unproject.h.
}
