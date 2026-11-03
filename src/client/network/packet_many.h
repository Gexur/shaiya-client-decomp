#pragma once
#include "network/packets.h"

extern "C" {
/**
 * @brief Read 12 fields (48 wire bytes) and call session vtable byte offset 0x0fc.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_12_dwords_to_session_slot_0fc(PacketReader* reader);
/**
 * @brief Read 11 fields (24 wire bytes) and call session vtable byte offset 0x150.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1, 4, 4, 2, 1, 2, 2, 2, 2, 2, 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_11_mixed_fields_to_session_slot_150(PacketReader* reader);
/**
 * @brief Read 11 fields (24 wire bytes) and call session vtable byte offset 0x168.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1, 4, 4, 2, 1, 2, 2, 2, 2, 2, 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_11_mixed_fields_to_session_slot_168(PacketReader* reader);
/**
 * @brief Read 9 fields (19 wire bytes) and call session vtable byte offset 0x17c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1, 4, 4, 1, 2, 1, 2, 2, 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_9_mixed_fields_to_session_slot_17c(PacketReader* reader);
/**
 * @brief Read 12 fields (25 wire bytes) and call session vtable byte offset 0x180.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1, 4, 4, 1, 2, 1, 2, 2, 2, 2, 2, 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_12_mixed_fields_to_session_slot_180(PacketReader* reader);
/**
 * @brief Read 13 fields (16 wire bytes) and call session vtable byte offset 0x1c8.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_13_mixed_fields_to_session_slot_1c8(PacketReader* reader);
/**
 * @brief Read 10 fields (20 wire bytes) and call session vtable byte offset 0x200.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4, 2, 1, 1, 4, 4, 1, 1, 1, 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_10_mixed_fields_to_session_slot_200(PacketReader* reader);
}
