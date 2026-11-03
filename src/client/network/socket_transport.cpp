#include "socket_transport.h"

extern "C" uint8_t PACKET_CDECL fun_0058d3f0(const char* address, uint16_t port) {
    dat_0224e340 = socket(AF_INET, SOCK_STREAM, 0);
    if (dat_0224e340 == INVALID_SOCKET)
        return 1;

    // 0x58d414, 0x58d426, 0x58d43d write only these first eight bytes. The
    // original leaves sockaddr_in::sin_zero uninitialized; do not zero it here.
    sockaddr_in peer;
    peer.sin_family = AF_INET;
    peer.sin_port = htons(port);
    peer.sin_addr.s_addr = inet_addr(address);
    const int option = 0;
    setsockopt(dat_0224e340, 0xffff, -0x81, reinterpret_cast<const char*>(&option), 4);
    if (connect(dat_0224e340, reinterpret_cast<const sockaddr*>(&peer), 16) == SOCKET_ERROR)
        return 2;

    dat_02246320 = 0; // Precisely a WORD store, not a receive-buffer clear.
    return WSAAsyncSelect(dat_0224e340, dat_0224a330, 0x2b10, 0x21) == SOCKET_ERROR ? 3 : 0;
}

extern "C" void PACKET_CDECL fun_0058d4b0(void* callback_object) {
    dat_0224a32c = callback_object;
}

extern "C" void PACKET_CDECL fun_0058d4c0(SessionPrefix* session) {
    dat_0224a328 = session;
}

extern "C" void PACKET_CDECL fun_0058d4d0() {
    const int result = send(dat_0224e340, reinterpret_cast<const char*>(dat_02242320),
                            static_cast<int32_t>(dat_0224e348), 0);
    if (result == SOCKET_ERROR) {
        MessageBoxA(nullptr, "Send Error!!!----OnWrite()", "Socket", 0);
        WSAAsyncSelect(dat_0224e340, dat_0224a330, 0x2b10, 0x23);
        return;
    }

    // The original drops the complete queue after ANY non-error send, including
    // zero and short sends. Preserve that behavior rather than adding retries.
    const SOCKET current_socket = dat_0224e340;
    for (uint32_t index = 0; index != sizeof(dat_02242320); ++index)
        dat_02242320[index] = 0;
    dat_0224e348 = 0;
    WSAAsyncSelect(current_socket, dat_0224a330, 0x2b10, 0x21);
}

extern "C" void PACKET_CDECL fun_004014f0() {
    dat_02252fe9 = 0;
    dat_02252fea = 0;
    dat_02252fe8 = 0;
}

extern "C" void PACKET_CDECL fun_00401510() {
    dat_02252fe9 = 1;
    dat_02252fea = 1;
}

extern "C" void PACKET_CDECL fun_00401570() {
    // The original uses signed comparisons: precisely 0/1 disable the main
    // inbound flag; 3 leaves it alone; all other values set alternate mode.
    if (dat_02252fe4 <= 1) {
        dat_02252fea = 0;
        return;
    }
    if (dat_02252fe4 != 3)
        dat_02252fe8 = 1;
}

extern "C" void PACKET_CDECL fun_004015a0() {
    dat_02252fe8 = 0;
    dat_02252fea = dat_02252fe4 != 0;
}

extern "C" void PACKET_CDECL fun_0058d560() {
    closesocket(dat_0224e340);
    fun_004015a0();
    fun_004014f0();
}

extern "C" void PACKET_CDECL fun_0058d580(int32_t reason) {
    closesocket(dat_0224e340);
    if (reason == 6) {
        dat_0224e340 = INVALID_SOCKET;
        return;
    }
    fun_004015a0();
    fun_004014f0();
}
