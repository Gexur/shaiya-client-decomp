#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include <windows.h>
#include "config/development_version.h"
#include "network/outbound.h"
#include "network/crypto_state.h"

extern "C" {
void __cdecl FUN_00599440(uint8_t server, uint32_t version);

SOCKET dat_0224e340 = INVALID_SOCKET;
HWND dat_0224a330 = nullptr;
void* dat_0224a32c = nullptr;
uint16_t dat_02246320 = 0;
uint8_t dat_02242320[0x4000] = {};
uint32_t dat_0224e348 = 0;
uint32_t dat_0070c3c4 = 1;
uint32_t dat_0224e6fc = 0;
uint8_t dat_02251fe0[4096] = {};
uint32_t dat_02252fe4 = 0;
uint8_t dat_02252fe8 = 0;
uint8_t dat_02252fe9 = 0;
uint8_t dat_02252fea = 0;
ClientCryptoState client_crypto_state = {};
}

// Execute the production A202 builder and original stack-allocation contract.
// Its seven bytes then pass through real outbound framing, crypto dispatch
// (disabled by the canonical flag above), and Winsock to the local receiver.
__asm__(".text\n.intel_syntax noprefix\n"
#include "network/server_selection_packet.inc"
        ".att_syntax prefix\n");

namespace {
constexpr uint32_t recovered_version = 0x11122200;
int failure = 0;
SOCKET receiver = INVALID_SOCKET;

void require(bool condition, int code) {
    if (!condition && failure == 0)
        failure = code;
}
bool connect_loopback() {
    WSADATA data;
    if (WSAStartup(MAKEWORD(2, 2), &data) != 0) {
        require(false, 1);
        return false;
    }
    const SOCKET listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listener == INVALID_SOCKET) {
        require(false, 2);
        return false;
    }
    sockaddr_in address = {};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
    int address_bytes = sizeof(address);
    if (bind(listener, reinterpret_cast<const sockaddr*>(&address), sizeof(address)) != 0 ||
        listen(listener, 1) != 0 ||
        getsockname(listener, reinterpret_cast<sockaddr*>(&address), &address_bytes) != 0) {
        require(false, 3);
        closesocket(listener);
        return false;
    }
    dat_0224e340 = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (dat_0224e340 == INVALID_SOCKET ||
        connect(dat_0224e340, reinterpret_cast<const sockaddr*>(&address), sizeof(address)) != 0) {
        require(false, 4);
        closesocket(listener);
        return false;
    }
    receiver = accept(listener, nullptr, nullptr);
    closesocket(listener);
    if (receiver == INVALID_SOCKET) {
        require(false, 5);
        return false;
    }
    const DWORD timeout = 2000;
    require(setsockopt(receiver, SOL_SOCKET, SO_RCVTIMEO,
                       reinterpret_cast<const char*>(&timeout), sizeof(timeout)) == 0,
            6);
    require(setsockopt(dat_0224e340, SOL_SOCKET, SO_SNDTIMEO,
                       reinterpret_cast<const char*>(&timeout), sizeof(timeout)) == 0,
            7);
    return failure == 0;
}
void verify_wire(uint8_t server, uint32_t version) {
    FUN_00599440(server, shaiya_client_version);
    uint8_t packet[9] = {};
    uint32_t received = 0;
    while (received < sizeof(packet)) {
        const int count = recv(receiver, reinterpret_cast<char*>(packet + received),
                               sizeof(packet) - received, 0);
        if (count <= 0) {
            require(false, 8);
            return;
        }
        received += static_cast<uint32_t>(count);
    }
    require(packet[0] == 9 && packet[1] == 0, 9);
    require(packet[2] == 0x02 && packet[3] == 0xa2, 10);
    require(packet[4] == server, 11);
    for (uint32_t byte = 0; byte < 4; ++byte)
        require(packet[5 + byte] == uint8_t(version >> (byte * 8)), 12);
    require(dat_0224e348 == 0, 13);
}
void configure(const char* value) {
    require(SetEnvironmentVariableA("SHAIYA_CLIENT_VERSION", value) != FALSE, 14);
    shaiya_apply_development_client_version();
}
void test_default() {
    // Start with a non-default value so missing configuration must reset it.
    configure("42");
    require(shaiya_client_version == 42, 15);
    configure(nullptr);
    require(shaiya_client_version == recovered_version, 16);
    verify_wire(0x5a, recovered_version);
}
void test_valid_values() {
    struct Case {
        const char* text;
        uint32_t expected;
    };
    static const Case cases[] = {
        {"0", 0},
        {"1", 1},
        {"286401024", recovered_version},
        {"00042", 42},
        {"010", 10},
        {"4294967295", 0xffffffff},
        {"0x0", 0},
        {"0X0", 0},
        {"0x11122200", recovered_version},
        {"0XABCDEF01", 0xabcdef01},
        {"0xffffffff", 0xffffffff},
        {"0XFFFFFFFF", 0xffffffff},
        {"0x00000000", 0},
        {"0x0000002a", 42},
    };
    uint8_t server = 0;
    for (const Case& test : cases) {
        configure(test.text);
        require(shaiya_client_version == test.expected, 17);
        verify_wire(server++, test.expected);
        if (failure != 0)
            return;
    }
}
void test_invalid_values() {
    static const char* cases[] = {
        nullptr, "", "+1", "-1", " 1", "1 ", "1\t", "1\n", "1.0", "1e3", "0b1",
        "0x", "0X", "0xG1", "0x1z", "0x-1", "0x+1", "0x 1", "0x1 ",
        "4294967296", "9999999999", "0x100000000", "0XFFFFFFFFF",
        "0000000000000000000000000000000000000000000000000000000000000000000000000000000000",
    };
    for (const char* text : cases) {
        configure("0xabcdef01");
        require(shaiya_client_version == 0xabcdef01, 18);
        configure(text);
        require(shaiya_client_version == recovered_version, 19);
        verify_wire(0xff, recovered_version);
        if (failure != 0)
            return;
    }
}
} // namespace

extern "C" void __cdecl fun_0044cd20(const PacketDumpSite*, uint32_t, const char*, ...) {
    // Logging is disabled in this fixture; a call would indicate a bad flag.
    require(false, 20);
}

extern "C" void __cdecl client_version_test_entry() {
    if (connect_loopback()) {
        test_default();
        if (failure == 0)
            test_valid_values();
        if (failure == 0)
            test_invalid_values();
    }
    if (receiver != INVALID_SOCKET)
        closesocket(receiver);
    if (dat_0224e340 != INVALID_SOCKET)
        closesocket(dat_0224e340);
    WSACleanup();
    static const char passed[] =
        "Client version: decimal/hex configuration, fallback and A202 wire bytes passed.\n";
    static const char failed[] = "Client version regression failed.\n";
    DWORD written = 0;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), failure ? failed : passed,
              failure ? sizeof(failed) - 1 : sizeof(passed) - 1, &written, nullptr);
    ExitProcess(static_cast<UINT>(failure));
}
