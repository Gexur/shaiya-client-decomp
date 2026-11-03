#include "packets.h"
#include "../crypto/sha256.h"

extern "C" {
PACKET_EXPORT uint8_t dat_02251fe0[4096] = {};
PACKET_EXPORT uint32_t dat_02252fe4 = 0;
PACKET_EXPORT uint8_t dat_02252fea = 0;
}

// 0x401520..0x40156c. SHA-256 output ECX in the original is an explicit output
// argument in the recovered C++ SHA interface. No hash implementation is faked.
extern "C" void PACKET_CDECL fun_00401520(uint32_t mode, const void* seed) {
    sha256_digest(dat_02251fe0, seed, 16);
    for (uint32_t offset = 32; offset != 4096; offset += 32)
        sha256_digest(dat_02251fe0 + offset, dat_02251fe0 + offset - 16, 16);
    dat_02252fe4 = mode;
    if (mode == 0)
        dat_02252fea = 0;
}
