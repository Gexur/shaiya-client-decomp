#pragma once
#include <stdint.h>
extern "C" {
extern uint8_t dat_02209408[];
using OriginalScrollCallback = uint32_t(__attribute__((cdecl)) *)(uint32_t, uint32_t);
// Original checks signed kind<5; negative indices read before this address.
// No extent or neighboring storage definition is invented by this declaration.
extern OriginalScrollCallback dat_02203660[];
uint32_t __attribute__((thiscall)) FUN_0052d030(void*, uint32_t, uint32_t, uint32_t, uint32_t);
uint32_t recovered_0052d030(void*, const uint32_t* original_arguments);
}
