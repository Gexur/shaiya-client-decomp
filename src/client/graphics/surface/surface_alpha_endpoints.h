#pragma once
#include <stdint.h>
extern "C" {
// Original four DWORDs/RET16; EAX is the actual second output pointer.
void* __attribute__((stdcall)) FUN_0064f879(void* lower, void* upper, const void* values,
                                            uint32_t levels);
// Exact112B storage view of the four observed adjacent weight spans.
extern const uint32_t dat_006f0034[28];
extern const uint32_t dat_006c127c;
extern const uint32_t dat_006dfa1c;
}
