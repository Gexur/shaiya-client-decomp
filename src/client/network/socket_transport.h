#pragma once

#include <winsock2.h>
#include <windows.h>
#include "packets.h"

// These are individual, binary-evidenced storage locations. Unknown neighboring
// fields are not supplied by this module. Socket and flag storage is originally
// in the zero-filled tail of .data, not initialized to INVALID_SOCKET.
extern "C" {
extern SOCKET dat_0224e340;
extern HWND dat_0224a330;
extern void* dat_0224a32c;
extern uint16_t dat_02246320;
extern uint8_t dat_02242320[0x4000];
extern uint32_t dat_0224e348;
extern uint8_t dat_02252fe8;
extern uint8_t dat_02252fe9;

// Original cdecl. Only AL is a result of 0x58d3f0; the upper EAX bytes on its
// early exits are residual Winsock results, not an additional return value.
PACKET_EXPORT uint8_t PACKET_CDECL fun_0058d3f0(const char*, uint16_t);
PACKET_EXPORT void PACKET_CDECL fun_0058d4b0(void*);
PACKET_EXPORT void PACKET_CDECL fun_0058d4c0(SessionPrefix*);
PACKET_EXPORT void PACKET_CDECL fun_0058d4d0();
PACKET_EXPORT void PACKET_CDECL fun_0058d560();
PACKET_EXPORT void PACKET_CDECL fun_0058d580(int32_t);
PACKET_EXPORT void PACKET_CDECL fun_004014f0();
PACKET_EXPORT void PACKET_CDECL fun_00401510();
PACKET_EXPORT void PACKET_CDECL fun_00401570();
PACKET_EXPORT void PACKET_CDECL fun_004015a0();
}
