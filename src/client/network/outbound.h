#pragma once
#include "window_transport.h"

struct PacketDumpSite {
    const char* procedure;
    const char* file;
    uint32_t line;
};
static_assert(sizeof(PacketDumpSite) == 12);

extern "C" {
extern PACKET_EXPORT uint32_t dat_0224e6fc;
PACKET_EXPORT void PACKET_CDECL fun_00597e40(uint32_t opcode, const void* body,
                                             uint32_t body_bytes);
PACKET_EXPORT void PACKET_CDECL fun_00597f60(const void* packet, uint32_t packet_bytes);
PACKET_EXPORT void PACKET_CDECL fun_005992a0(uint8_t field, const void* reply128);

// Real unresolved variadic debug backend. The packet logger supplies the exact
// original site descriptor, category bit and formatted text; no backend body
// or substitute production logging implementation is supplied.
void PACKET_CDECL fun_0044cd20(const PacketDumpSite*, uint32_t category, const char* format, ...);
}
