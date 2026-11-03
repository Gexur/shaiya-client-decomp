#pragma once

#include "socket_transport.h"

extern "C" {
extern uint8_t dat_02246328[0x4000];
extern uint32_t dat_0070c3c4;
extern HWND dat_0224a334;
extern HINSTANCE dat_0224a338;

// The original installs 0x59f860 as a WNDPROC but uses plain RET, not RET 16.
// Preserve its observed cdecl ABI and EAX from DefWindowProcA. Normal-return
// paths only: its original SEH registration and unwind cleanup remain pending.
// The original dispatcher can forward a scratch DWORD after a WORD read. An
// explicit x86 MOVL preserves the remaining private-stack bytes; their values
// are unspecified by the original, not reconstructed constants or zero padding.
PACKET_EXPORT LRESULT PACKET_CDECL fun_0059f860(HWND, UINT, SOCKET, uint32_t);
PACKET_EXPORT uint32_t PACKET_CDECL fun_0059fa90(HWND, HINSTANCE);

// Real client dependencies. The logger consumes a WORD opcode. Named dispatcher
// routes mask the DWORD to a WORD; unknown/default routes can forward it whole.
void PACKET_CDECL fun_00597d70(const char*, uint16_t, const void*, uint32_t);
void PACKET_CDECL fun_0059cf70(uint32_t, PacketReader*);
}
