#pragma once
#include "network/packets.h"

// Original cdecl consumers; downstream virtual bodies remain unresolved.
extern "C" {
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x040.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_040(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x050.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_050(PacketReader* reader);
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x058.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u16_to_session_slot_058(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x064.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_064(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x08c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_08c(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x098.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_098(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x0d0.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_0d0(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x0d8.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_0d8(PacketReader* reader);
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x128.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u16_to_session_slot_128(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x13c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_13c(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x194.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_194(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x19c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_19c(PacketReader* reader);
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x208.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u16_to_session_slot_208(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x218.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_218(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x260.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_260(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x264.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_264(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x268.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_268(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x29c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_29c(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x2a4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_2a4(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x2cc.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_2cc(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x2d4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_2d4(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x2dc.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_2dc(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x2f0.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_2f0(PacketReader* reader);
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x314.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u16_to_session_slot_314(PacketReader* reader);
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x318.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u16_to_session_slot_318(PacketReader* reader);
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x380.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u16_to_session_slot_380(PacketReader* reader);
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x384.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u16_to_session_slot_384(PacketReader* reader);
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x388.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u16_to_session_slot_388(PacketReader* reader);
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x38c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u16_to_session_slot_38c(PacketReader* reader);
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x390.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u16_to_session_slot_390(PacketReader* reader);
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x39c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u16_to_session_slot_39c(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x3a0.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_3a0(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x3a4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_3a4(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x3b8.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_3b8(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x3bc.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_3bc(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x3c0.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_3c0(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x3c8.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_3c8(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x3d0.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_3d0(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x3f0.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_3f0(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x404.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_404(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x410.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_410(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x428.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_428(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x434.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_434(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x43c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_43c(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x444.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_444(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x460.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_460(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x468.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_468(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x47c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_47c(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x484.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_484(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x488.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_488(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x4b4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_4b4(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x4dc.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_4dc(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x4e4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_4e4(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x4e8.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_4e8(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x4fc.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_4fc(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x514.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_514(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x524.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_524(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x530.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_530(PacketReader* reader);
/**
 * @brief Read one 2-byte field and call session vtable byte offset 0x538.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 2 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u16_to_session_slot_538(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x544.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_544(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x54c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_54c(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x550.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_550(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x558.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_558(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x55c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_55c(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x560.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_560(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x564.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_564(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x568.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_568(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x584.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_584(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x588.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_588(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x2c4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_2c4(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x5b4.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_5b4(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x604.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_604(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x5ec.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_5ec(PacketReader* reader);
/**
 * @brief Read one 4-byte field and call session vtable byte offset 0x60c.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 4 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u32_to_session_slot_60c(PacketReader* reader);
/**
 * @brief Read one 1-byte field and call session vtable byte offset 0x618.
 * @param reader Packet reader whose cursor is advanced by the original read procedure.
 * @note Wire field widths: 1 byte(s), in that order.
 *       The callback's game meaning is unresolved. Its DWORD arguments retain
 *       original scratch padding; short reads are not rejected by this adapter.
 */
void PACKET_CDECL dispatch_packet_u8_to_session_slot_618(PacketReader* reader);
}
