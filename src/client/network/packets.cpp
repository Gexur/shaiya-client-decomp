#include "network/packets.h"

extern "C" {
PACKET_EXPORT SessionPrefix* dat_0224a328 = nullptr;
PACKET_EXPORT SessionPrefix* dat_0223f100 = nullptr;
}

namespace {
uint32_t load_le32(const uint8_t* p) {
    return uint32_t(p[0]) | uint32_t(p[1]) << 8 | uint32_t(p[2]) << 16 | uint32_t(p[3]) << 24;
}
void store_le32(uint8_t* p, uint32_t value) {
    p[0] = uint8_t(value);
    p[1] = uint8_t(value >> 8);
    p[2] = uint8_t(value >> 16);
    p[3] = uint8_t(value >> 24);
}
// Preserve the forward DWORD-then-byte ordering of REP MOVSD / REP MOVSB.
// memcpy/memmove would give different semantics for some overlapping regions.
void copy_forward(uint8_t* out, const uint8_t* in, uint32_t length) {
    for (uint32_t words = length >> 2; words != 0; --words, out += 4, in += 4)
        store_le32(out, load_le32(in));
    for (uint32_t tail = length & 3; tail != 0; --tail)
        *out++ = *in++;
}
} // namespace

extern "C" PacketReader* PACKET_THISCALL initialize_packet_reader(PacketReader* reader,
                                                                  const void* input,
                                                                  uint32_t length) {
    for (uint32_t i = 0; i != 0x2000; ++i)
        reader->bytes[i] = 0;
    reader->end = reader->bytes;
    reader->cursor = reader->bytes;
    if (length > 0x2000)
        length = 0x2000;
    copy_forward(reader->bytes, static_cast<const uint8_t*>(input), length);
    uint8_t* end = reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(reader->end) + length);
    reader->length = length;
    reader->end = end;
    return reader;
}

extern "C" void PACKET_CDECL report_packet_read_diagnostic() {
    dat_0224a328->callbacks->read_diagnostic(dat_0224a328, nullptr);
}

extern "C" uint32_t PACKET_THISCALL read_packet_bytes_with_diagnostic(PacketReader* reader,
                                                                      void* output,
                                                                      uint32_t length) {
    uint8_t* source = reader->cursor;
    const uintptr_t reader_address = reinterpret_cast<uintptr_t>(reader);
    if (reinterpret_cast<uintptr_t>(source) + length > reader_address + reader->length) {
        uint8_t* destination = static_cast<uint8_t*>(output);
        for (uint32_t i = 0; i != length; ++i)
            destination[i] = 0;
        dat_0224a328->callbacks->read_diagnostic(dat_0224a328, reader);
        // The original reloads both fields after the virtual call. In particular,
        // this path copies the new remaining length, not min(remaining, request).
        source = reader->cursor;
        length = reader_address - reinterpret_cast<uintptr_t>(source) + reader->length;
        if (length == 0)
            return 0;
    }
    copy_forward(static_cast<uint8_t*>(output), source, length);
    reader->cursor =
        reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(reader->cursor) + length);
    return length;
}

extern "C" uint32_t PACKET_THISCALL read_available_packet_bytes(PacketReader* reader, void* output,
                                                                uint32_t length) {
    uint8_t* source = reader->cursor;
    const uintptr_t reader_address = reinterpret_cast<uintptr_t>(reader);
    if (reinterpret_cast<uintptr_t>(source) + length > reader_address + reader->length) {
        const uint32_t remaining =
            reader_address + reader->length - reinterpret_cast<uintptr_t>(source);
        if (remaining == 0) {
            uint8_t* destination = static_cast<uint8_t*>(output);
            for (uint32_t i = 0; i != length; ++i)
                destination[i] = 0;
            dat_0224a328->callbacks->read_diagnostic(dat_0224a328, reader);
            return 0;
        }
        length = remaining;
    }
    copy_forward(static_cast<uint8_t*>(output), source, length);
    reader->cursor =
        reinterpret_cast<uint8_t*>(reinterpret_cast<uintptr_t>(reader->cursor) + length);
    return length;
}

extern "C" void PACKET_CDECL fun_005921b0(PacketReader* reader) {
    uint8_t status;
    uint32_t user_id;
    uint8_t flag;
    uint8_t token[16];
    read_packet_bytes_with_diagnostic(reader, &status, 1);
    read_packet_bytes_with_diagnostic(reader, &user_id, 4);
    read_packet_bytes_with_diagnostic(reader, &flag, 1);
    read_packet_bytes_with_diagnostic(reader, token, 16);
    dat_0224a328->callbacks->login_result(dat_0224a328, status, user_id, flag, token);
}

extern "C" void PACKET_CDECL fun_00592120(PacketReader* reader) {
    uint8_t byte_0, byte_1, byte_2;
    uint8_t block_64[64];
    uint8_t block_128[128];
    read_packet_bytes_with_diagnostic(reader, &byte_0, 1);
    read_packet_bytes_with_diagnostic(reader, &byte_1, 1);
    read_packet_bytes_with_diagnostic(reader, &byte_2, 1);
    read_packet_bytes_with_diagnostic(reader, block_64, 64);
    read_packet_bytes_with_diagnostic(reader, block_128, 128);
    dat_0224a328->callbacks->challenge_a101(dat_0224a328, byte_0, byte_1, byte_2, block_64,
                                            block_128);
}

extern "C" void PACKET_CDECL fun_00592220(PacketReader* reader) {
    // 0x592234 sets ECX=456 then REP STOSD: exactly 48 * 38 bytes.
    // The original does not bound the byte count to this stack array. Preserve
    // the parser rather than invent a rejection or truncate the record count.
    ServerListRecord entries[48] = {};
    uint8_t count;
    read_packet_bytes_with_diagnostic(reader, &count, 1);
    for (uint32_t index = 0; index < count; ++index)
        read_packet_bytes_with_diagnostic(reader, &entries[index], 0x26);
    dat_0224a328->callbacks->server_list(dat_0224a328, count, entries);
}

extern "C" void PACKET_CDECL fun_00592030(PacketReader* reader) {
    uint32_t dword_0;
    uint8_t byte_4;
    uint16_t word_5;
    read_packet_bytes_with_diagnostic(reader, &dword_0, 4);
    read_packet_bytes_with_diagnostic(reader, &byte_4, 1);
    read_packet_bytes_with_diagnostic(reader, &word_5, 2);
    dat_0224a328->callbacks->callback_220(dat_0224a328, dword_0, byte_4, word_5);
}

extern "C" void PACKET_CDECL fun_00592090(PacketReader* reader) {
    uint32_t dword_0, dword_5, dword_9, dword_13, dword_17;
    uint8_t byte_4;
    read_packet_bytes_with_diagnostic(reader, &dword_0, 4);
    read_packet_bytes_with_diagnostic(reader, &byte_4, 1);
    read_packet_bytes_with_diagnostic(reader, &dword_5, 4);
    read_packet_bytes_with_diagnostic(reader, &dword_9, 4);
    read_packet_bytes_with_diagnostic(reader, &dword_13, 4);
    read_packet_bytes_with_diagnostic(reader, &dword_17, 4);
    dat_0224a328->callbacks->callback_224(dat_0224a328, dword_0, byte_4, dword_5, dword_9, dword_13,
                                          dword_17);
}

extern "C" void PACKET_CDECL fun_00592620(PacketReader* reader) {
    uint32_t dword_0;
    read_packet_bytes_with_diagnostic(reader, &dword_0, 4);
    dat_0224a328->callbacks->callback_254(dat_0224a328, dword_0);
}

extern "C" void PACKET_CDECL fun_00592650(PacketReader* reader) {
    uint8_t byte_0;
    uint32_t dword_1;
    read_packet_bytes_with_diagnostic(reader, &byte_0, 1);
    read_packet_bytes_with_diagnostic(reader, &dword_1, 4);
    dat_0224a328->callbacks->callback_258(dat_0224a328, byte_0, dword_1);
}

extern "C" void PACKET_CDECL fun_005923d0(PacketReader* reader) {
    uint8_t status;
    uint32_t ipv4;
    read_packet_bytes_with_diagnostic(reader, &status, 1);
    read_packet_bytes_with_diagnostic(reader, &ipv4, 4);
    dat_0224a328->callbacks->world_address(dat_0224a328, status, ipv4);
}

extern "C" void PACKET_CDECL fun_00592420(PacketReader* reader) {
    uint8_t status;
    uint8_t mode;
    uint8_t seed[16];
    read_packet_bytes_with_diagnostic(reader, &status, 1);
    read_packet_bytes_with_diagnostic(reader, &mode, 1);
    read_packet_bytes_with_diagnostic(reader, seed, 16);
    dat_0224a328->callbacks->seed_result(dat_0224a328, status, mode, seed);
}

extern "C" void PACKET_CDECL fun_005922a0(PacketReader* reader) {
    uint8_t status;
    read_packet_bytes_with_diagnostic(reader, &status, 1);
    dat_0224a328->callbacks->status_a105(dat_0224a328, status);
}

extern "C" void PACKET_CDECL fun_00592380(PacketReader* reader) {
    uint8_t status, flag;
    read_packet_bytes_with_diagnostic(reader, &status, 1);
    read_packet_bytes_with_diagnostic(reader, &flag, 1);
    dat_0224a328->callbacks->status_a108(dat_0224a328, status, flag);
}

extern "C" void PACKET_THISCALL fun_00570ad0(SessionPrefix* session, uint8_t status,
                                             uint32_t user_id, uint8_t flag, const uint8_t* token) {
    session->state = status;
    session->user_id_1f4 = user_id;
    copy_forward(session->login_token, token, 16);
    session->user_id_1f8 = user_id;
    dat_008655e8 = flag;
    dat_008655ec = flag <= 10 ? 1 : 0;
    session->field_204 = 0;
}

extern "C" void PACKET_THISCALL fun_005712d0(SessionPrefix* session, uint8_t status,
                                             uint32_t ipv4) {
    session->state = status;
    session->world_ipv4 = ipv4;
}

extern "C" void PACKET_THISCALL fun_00570b30(SessionPrefix* session, uint8_t status) {
    // Original writes target a second singleton, except field_204 in branches
    // 0 and 1, which targets ECX. Do not assume the two session pointers alias.
    if (status == 0) {
        dat_0223f100->state = 4;
        dat_0223f100->field_200 = 1;
        session->field_204 = 0;
    } else if (status == 1) {
        dat_0223f100->field_200 = 0;
        dat_0223f100->state = 0;
        session->field_204 = 0;
    } else if (status == 2) {
        dat_0223f100->field_200 = 0;
        dat_0223f100->field_204 = 1;
        dat_0223f100->state = 4;
    }
}

extern "C" void PACKET_THISCALL fun_00570c90(SessionPrefix* session, uint8_t status, uint8_t flag) {
    if (status == 0) {
        dat_0223f100->state = 4;
        dat_0223f100->field_200 = 1;
        session->field_204 = flag;
    } else if (status == 1) {
        dat_0223f100->field_200 = 0;
        dat_0223f100->state = 0;
        session->field_204 = 0;
    }
}

// Exactly XOR EAX,EAX; RET at 0x443cd0..0x443cd2 in this binary. This is a
// recovered constant function, not a replacement for an unrecovered dependency.
extern "C" uint32_t PACKET_CDECL fun_00443cd0() {
    return 0;
}

extern "C" void PACKET_THISCALL fun_005712f0(SessionPrefix* session, uint8_t status, uint8_t mode,
                                             const uint8_t* seed) {
    // The locale-2 message block at 0x5712fc..0x571326 cannot execute: its
    // condition calls 0x443cd0 and requires a nonzero result. Preserve the
    // actual locale read/call; no speculative UI implementations are supplied.
    if (dat_00708598 == 2)
        (void)fun_00443cd0();
    if (status == 0) {
        fun_00401520(mode, seed);
        ++session->state;
    }
}
