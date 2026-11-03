#include "outbound.h"
#include "crypto_state.h"
#include "../crypto/transport.h"

extern "C" {
__attribute__((
    visibility("hidden"))) extern uint32_t dat_0224e6fc; // Same image: real logger.flags field.
}

namespace {
uint16_t load_word(const uint8_t* p) {
    return uint16_t(p[0]) | uint16_t(p[1]) << 8;
}
uint32_t load_dword(const uint8_t* p) {
    return uint32_t(p[0]) | uint32_t(p[1]) << 8 | uint32_t(p[2]) << 16 | uint32_t(p[3]) << 24;
}
void store_word(uint8_t* p, uint16_t value) {
    p[0] = uint8_t(value);
    p[1] = uint8_t(value >> 8);
}
void copy_forward(uint8_t* out, const uint8_t* in, uint32_t length) {
    for (uint32_t words = length >> 2; words != 0; --words, out += 4, in += 4) {
        const uint32_t value = load_dword(in);
        out[0] = uint8_t(value);
        out[1] = uint8_t(value >> 8);
        out[2] = uint8_t(value >> 16);
        out[3] = uint8_t(value >> 24);
    }
    for (uint32_t tail = length & 3; tail != 0; --tail)
        *out++ = *in++;
}
char hex_digit(uint8_t value) {
    if (value < 10)
        return char(value + 0x30);
    if (value < 16)
        return char(value + 0x37);
    return 'x';
}
void queue_frame(const uint8_t* frame, uint16_t frame_bytes) {
    // Original queue bounds check occurs AFTER the unchecked copy. Keep this
    // behavior and its 16-bit appended length; do not invent early rejection.
    uint32_t queued = dat_0224e348;
    copy_forward(dat_02242320 + queued, frame, frame_bytes);
    queued += frame_bytes;
    dat_0224e348 = queued;
    if (queued > 0x4000) {
        MessageBoxA(nullptr, "Send Error!!!", "Socket", 0);
        dat_0224e348 = 0;
        return;
    }
    WSAAsyncSelect(dat_0224e340, dat_0224a330, 0x2b10, 0x23);
}
void send_frame(const uint8_t* frame, uint32_t frame_bytes) {
    const int32_t sent = send(dat_0224e340, reinterpret_cast<const char*>(frame),
                              static_cast<int32_t>(frame_bytes), 0);
    // The original discards the complete frame after every non-error result,
    // including zero/short sends; it does not queue a remainder or retry.
    if (sent != SOCKET_ERROR)
        return;
    const int32_t error = WSAGetLastError();
    if (error == 0x2733 || error == 0x3e5)
        queue_frame(frame, uint16_t(frame_bytes));
}
} // namespace

extern "C" void PACKET_CDECL fun_00597d70(const char* direction, uint16_t opcode, const void* body,
                                          uint32_t body_bytes) {
    if ((dat_0224e6fc & 0x40) == 0)
        return;
    char text[0x6080];
    char* out = text + wsprintfA(text, "%s [%04X/%04X] ", direction, uint32_t(opcode), body_bytes);
    const auto* bytes = static_cast<const uint8_t*>(body);
    for (int32_t index = 0; index < static_cast<int32_t>(body_bytes); ++index) {
        *out++ = hex_digit(bytes[index] >> 4);
        *out++ = hex_digit(bytes[index] & 15);
        *out++ = ' ';
    }
    *out = 0;
    const PacketDumpSite site = {"PacketDump", "D:\\ENGLISH\\Network\\ProjectSNet.cpp", 0x4e};
    fun_0044cd20(&site, 0x40, text);
}

extern "C" void PACKET_CDECL fun_00597e40(uint32_t opcode, const void* body, uint32_t body_bytes) {
    if (dat_0070c3c4 == 0)
        return;
    fun_00597d70("SEND>>", uint16_t(opcode), body, body_bytes);
    uint8_t frame[0x1000];
    const uint32_t frame_bytes = body_bytes + 4;
    store_word(frame, uint16_t(frame_bytes));
    store_word(frame + 2, uint16_t(opcode));
    copy_forward(frame + 4, static_cast<const uint8_t*>(body), body_bytes);
    transform_outbound_payload(&client_crypto_state, frame + 2, body_bytes + 2);
    send_frame(frame, frame_bytes);
}

extern "C" void PACKET_CDECL fun_00597f60(const void* packet, uint32_t packet_bytes) {
    if (dat_0070c3c4 == 0)
        return;
    const auto* bytes = static_cast<const uint8_t*>(packet);
    // This original WORD read occurs even when packet_bytes is zero.
    fun_00597d70("SEND>>", load_word(bytes), packet, packet_bytes);
    uint8_t frame[0x1000];
    const uint32_t frame_bytes = packet_bytes + 2;
    store_word(frame, uint16_t(frame_bytes));
    copy_forward(frame + 2, bytes, packet_bytes);
    transform_outbound_payload(&client_crypto_state, frame + 2, packet_bytes);
    send_frame(frame, frame_bytes);
}

extern "C" void PACKET_CDECL fun_005992a0(uint8_t field, const void* reply128) {
    uint8_t packet[0x2000];
    store_word(packet, 0xa101);
    packet[2] = field;
    copy_forward(packet + 3, static_cast<const uint8_t*>(reply128), 128);
    fun_00597f60(packet, 0x83);
}
