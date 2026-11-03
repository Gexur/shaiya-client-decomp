#include "bootstrap.h"
#include "sha256.h"

namespace {
/**
 * Copy a byte range forward with the recovered bootstrap's byte-at-a-time accesses.
 * @param destination Writable range of byte_count bytes.
 * @param source Readable range of byte_count bytes.
 * @param byte_count Number of bytes to copy, preserving forward overlap behavior.
 */
void copy_forward_bytes(uint8_t* destination, const uint8_t* source, uint32_t byte_count) {
    for (uint32_t i = 0; i < byte_count; ++i)
        destination[i] = source[i];
}
} // namespace

/**
 * Factor the A101 bootstrap's random-value generation and transport-state setup.
 * @param state Explicit context whose PRNG seed, algorithm and selected streams are updated.
 * @param algorithm Zero selects AES; every other value selects LCG initialization.
 * @param modulus Readable modulus bytes used as the HMAC-SHA-256 message.
 * @param modulus_bytes Modulus length in bytes, passed unchanged to HMAC.
 * @param random128 Receives 128 LCG bytes with the high bit of the last byte cleared.
 * Derives thirty-two bytes using random128 as the HMAC key. AES uses the first
 * half as its key and the second as counter/nonce bytes. LCG uses all derived
 * bytes as seeds, prefills each stream with one seed advance, and stores the
 * first half as its retained key and the second as reconnect nonce.
 * This helper factors inline instructions 0x4011ad..0x401314 and has no separate
 * original procedure or private register convention.
 */
extern "C" void client_crypto_initialize_a101(ClientCryptoState* state, uint32_t algorithm,
                                              const void* modulus, uint32_t modulus_bytes,
                                              uint8_t random128[128]) {
    state->algorithm = algorithm;
    lcg_fill_bytes(&state->prng_seed, random128, 128);
    random128[127] &= 0x7f;
    uint8_t derived[32];
    hmac_sha256(derived, random128, 128, modulus, modulus_bytes);
    if (algorithm == 0) {
        aes_expand_key(&state->outbound_aes.schedule, derived, 128);
        aes_expand_key(&state->inbound_aes.schedule, derived, 128);
        copy_forward_bytes(state->reconnect_nonce, derived + 16, 16);
        copy_forward_bytes(reinterpret_cast<uint8_t*>(state->outbound_aes.counter), derived + 16,
                           16);
        state->outbound_aes.position = 0;
        copy_forward_bytes(reinterpret_cast<uint8_t*>(state->inbound_aes.counter), derived + 16,
                           16);
        state->inbound_aes.position = 0;
    } else {
        copy_forward_bytes(state->reconnect_nonce, derived + 16, 16);
        copy_forward_bytes(state->lcg_key, derived, 16);
        copy_forward_bytes(reinterpret_cast<uint8_t*>(state->outbound_lcg.seeds), derived, 32);
        lcg_generate_block(state->outbound_lcg.seeds, state->outbound_lcg.stream);
        copy_forward_bytes(reinterpret_cast<uint8_t*>(state->inbound_lcg.seeds), derived, 32);
        state->outbound_lcg.position = 0;
        lcg_generate_block(state->inbound_lcg.seeds, state->inbound_lcg.stream);
        state->inbound_lcg.position = 0;
    }
}
