#include "challenge.h"
#include "crypto_state.h"
#include "outbound.h"

// Original0x570a60..0x570ac7. This is the concrete A101 session callback,
// connecting the recovered bootstrap to the original fixed-size reply builder.
// The original leaves unused reply bytes uninitialized when RSA output is
// shorter than128 bytes; no zero-fill or reply-length policy is invented here.
// Full128-byte fixture replies are the first intended verification domain.
extern "C" void PACKET_THISCALL fun_00570a60(SessionPrefix* session, uint8_t algorithm,
                                             uint8_t exponent_bytes, uint8_t modulus_bytes,
                                             const uint8_t* exponent, const uint8_t* modulus) {
    uint8_t reply[128];
    uint32_t reply_bytes;
    build_a101_crypto_reply(&client_crypto_state, reply, &reply_bytes, algorithm, exponent,
                            exponent_bytes, modulus, modulus_bytes);
    fun_005992a0(uint8_t(reply_bytes), reply);
    fun_00401510();
    session->state = 1;
}
