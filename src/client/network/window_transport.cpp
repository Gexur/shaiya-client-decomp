#include "window_transport.h"
#include "crypto_state.h"
#include "../crypto/transport.h"

namespace {
uint16_t read_word(const uint8_t* p) {
    return uint16_t(p[0]) | uint16_t(p[1]) << 8;
}
uint32_t read_dword(const uint8_t* p) {
    return uint32_t(p[0]) | uint32_t(p[1]) << 8 | uint32_t(p[2]) << 16 | uint32_t(p[3]) << 24;
}
uint32_t read_opcode_scratch(const unsigned char (&storage)[4]) {
    uint32_t value;
    // 0x59fa0f loads the complete DWORD after the reader wrote only its low
    // WORD. Read the four-byte storage through an explicit x86 instruction:
    // a C++ integer read/promotion of indeterminate high bytes is not valid.
    // The high WORD remains the actual previous stack contents, not zero.
    __asm__ __volatile__("movl %1, %0" : "=r"(value) : "m"(storage));
    return value;
}
void copy_forward(uint8_t* out, const uint8_t* in, uint32_t count) {
    // Preserve REP MOVSD's read-before-write of each DWORD on overlapping
    // receive-buffer compaction, followed by REP MOVSB's byte tail.
    for (uint32_t words = count >> 2; words != 0; --words, in += 4, out += 4) {
        const uint32_t value = read_dword(in);
        out[0] = uint8_t(value);
        out[1] = uint8_t(value >> 8);
        out[2] = uint8_t(value >> 16);
        out[3] = uint8_t(value >> 24);
    }
    for (uint32_t tail = count & 3; tail != 0; --tail)
        *out++ = *in++;
}

using SocketError = void(PACKET_THISCALL*)(SessionPrefix*, int32_t);
using SocketClose = void(PACKET_THISCALL*)(SessionPrefix*);
} // namespace

extern "C" LRESULT PACKET_CDECL fun_0059f860(HWND window, UINT message, SOCKET source_socket,
                                             uint32_t event) {
    if (message == 0x2b10) {
        if ((event >> 16) != 0) {
            // The original captures the vtable BEFORE WSAGetLastError and
            // reloads the singleton afterwards, even if the API changes it.
            SessionCallbacks* callbacks = dat_0224a328->callbacks;
            const int32_t error = WSAGetLastError();
            reinterpret_cast<SocketError>(callbacks->unknown_000[2])(dat_0224a328, error);
            closesocket(source_socket);
        } else {
            switch (event & 0xffff) {
            case 0x20:
                reinterpret_cast<SocketClose>(dat_0224a328->callbacks->unknown_000[3])(
                    dat_0224a328);
                break;
            case 2:
                if (dat_0070c3c4 != 0)
                    fun_0058d4d0();
                break;
            case 1:
                if (dat_0070c3c4 != 0) {
                    uint8_t received[0x2000];
                    const int32_t count =
                        recv(source_socket, reinterpret_cast<char*>(received), 0x2000, 0);
                    if (count == SOCKET_ERROR) {
                        closesocket(source_socket);
                        break;
                    }
                    copy_forward(dat_02246328 + dat_02246320, received,
                                 static_cast<uint32_t>(count));
                    dat_02246320 = uint16_t(dat_02246320 + count);
                    while (dat_02246320 >= 4) {
                        const uint16_t packet_bytes = read_word(dat_02246328);
                        if (packet_bytes > dat_02246320)
                            break;
                        const uint32_t body_bytes = uint32_t(packet_bytes) - 2;
                        PacketReader reader;
                        initialize_packet_reader(&reader, dat_02246328 + 2, body_bytes);
                        transform_inbound_payload(&client_crypto_state, reader.bytes, body_bytes);
                        const uint16_t remainder = uint16_t(dat_02246320 - packet_bytes);
                        copy_forward(dat_02246328, dat_02246328 + packet_bytes, remainder);
                        dat_02246320 = remainder;
                        alignas(uint32_t) unsigned char opcode_scratch[4];
                        read_packet_bytes_with_diagnostic(&reader, opcode_scratch, 2);
                        fun_00597d70("RECV>>", read_word(opcode_scratch), reader.bytes,
                                     reader.length);
                        // Default routing can forward the full scratch DWORD.
                        // Retain its stack-dependent high WORD exactly as a
                        // hardware memory load, without inventing its value.
                        fun_0059cf70(read_opcode_scratch(opcode_scratch), &reader);
                        report_packet_read_diagnostic();
                    }
                }
                break;
            }
        }
    }
    return DefWindowProcA(window, message, source_socket, static_cast<LPARAM>(event));
}

extern "C" uint32_t PACKET_CDECL fun_0059fa90(HWND parent, HINSTANCE instance) {
    dat_0224a334 = parent;
    dat_0224a338 = instance;
    const HWND window = CreateWindowExA(0, "BUTTON", "", 0xc0000000, 0, 0, 0, 0, parent, nullptr,
                                        instance, nullptr);
    SetWindowLongA(window, -4, static_cast<LONG>(reinterpret_cast<uintptr_t>(&fun_0059f860)));
    dat_0224a330 = window;
    WSADATA data;
    return static_cast<uint32_t>(WSAStartup(0x202, &data)) & 0xffffff00;
}
