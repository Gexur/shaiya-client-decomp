#pragma once
#include <stdint.h>
extern "C" {
// Original four actual DWORD arguments; callee pops 16 bytes and returns upper.
void* __attribute__((stdcall)) FUN_0064fba0(void* lower, void* upper, const void* rgba,
                                            uint32_t levels);
// The original minimum vector belongs to writable PE .data.
extern uint32_t dat_00716910[4];
// Exact observed scalar and adjacent weight storage; no interpolation formula.
extern const uint32_t dat_006de5a4;
extern const uint32_t dat_006f00a4[16];
}
