#pragma once
#include "packets.h"

extern "C" {
// Original session callback at vtable offset0x228: thiscall, five stack
// arguments, RET20. The concrete full vtable is still a separate dependency.
PACKET_EXPORT void PACKET_THISCALL fun_00570a60(SessionPrefix*, uint8_t algorithm,
                                                uint8_t exponent_bytes, uint8_t modulus_bytes,
                                                const uint8_t* exponent, const uint8_t* modulus);
}
