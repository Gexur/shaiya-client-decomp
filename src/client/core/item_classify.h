#pragma once
#include <stdint.h>
extern "C" {
// Original entries ignore ECX, consume stack+4's low byte, preserve EAX's
// upper24bits and RET4. The thiscall view matches their original callers.
uint32_t __attribute__((thiscall)) FUN_004c8fb0(void*, uint32_t);
uint32_t __attribute__((thiscall)) FUN_004cba90(void*, uint32_t);
uint32_t recovered_004c8fb0(uint32_t argument, uint32_t incoming_eax);
uint32_t recovered_004cba90(uint32_t argument, uint32_t incoming_eax);
}
