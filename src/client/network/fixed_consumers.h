#pragma once
#include "network/packets.h"

// Original cdecl packet consumers. The virtual callees are supplied by the
// actual session; these declarations do not recover those callback bodies.
extern "C" {
void PACKET_CDECL fun_0058d5c0(PacketReader*);
void PACKET_CDECL fun_0058d5f0(PacketReader*);
void PACKET_CDECL fun_0058d640(PacketReader*);
void PACKET_CDECL fun_0058d690(PacketReader*);
void PACKET_CDECL fun_0058d6c0(PacketReader*);
void PACKET_CDECL fun_0058d6f0(PacketReader*);
void PACKET_CDECL fun_0058d710(PacketReader*);
void PACKET_CDECL fun_0058d830(PacketReader*);
void PACKET_CDECL fun_0058db20(PacketReader*);
void PACKET_CDECL fun_0058db50(PacketReader*);
void PACKET_CDECL fun_0058db90(PacketReader*);
}
