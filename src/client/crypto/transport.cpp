#include "transport.h"
#include "sha256.h"

namespace {
/**
 * Copy sixteen bytes in four forward DWORD-sized groups without requiring alignment.
 * @param destination Sixteen writable bytes.
 * @param source Sixteen readable bytes; each DWORD is loaded before its bytes are stored.
 * Retains the original grouping when the ranges overlap.
 */
void copy_four_dword_bytes(void* destination, const uint8_t* source) {
    uint8_t* output = static_cast<uint8_t*>(destination);
    for (unsigned i = 0; i < 4; ++i) {
        uint32_t value = uint32_t(source[0]) | uint32_t(source[1]) << 8 |
                         uint32_t(source[2]) << 16 | uint32_t(source[3]) << 24;
        output[0] = uint8_t(value);
        output[1] = uint8_t(value >> 8);
        output[2] = uint8_t(value >> 16);
        output[3] = uint8_t(value >> 24);
        source += 4;
        output += 4;
    }
}
} // namespace

/**
 * Install matching inbound/outbound AES-128 schedules and counter bytes.
 * @param state Explicit context receiving schedules, counters and zero fragment positions.
 * @param material Thirty-two readable bytes: sixteen key bytes followed by sixteen counter bytes.
 * Sets the canonical inbound/outbound transform flags to one after both schedules
 * are initialized; retains the current algorithm selector. The C API makes the
 * original scattered state explicit for original cdecl entry 0x401000.
 */
extern "C" void initialize_transport_aes_material(ClientCryptoState* state,
                                                  const uint8_t material[32]) {
    aes_expand_key(&state->inbound_aes.schedule, material, 128);
    copy_four_dword_bytes(state->inbound_aes.counter, material + 16);
    state->inbound_aes.position = 0;
    aes_expand_key(&state->outbound_aes.schedule, material, 128);
    copy_four_dword_bytes(state->outbound_aes.counter, material + 16);
    state->outbound_aes.position = 0;
    dat_02252fea = 1;
    dat_02252fe9 = 1;
}

/**
 * Transform an outbound payload in place when its canonical enable flag is set.
 * @param state Explicit context; algorithm zero selects AES, every other value selects LCG.
 * @param data Writable/readable payload buffer, unchanged when dat_02252fe9 is zero.
 * @param byte_count Payload length in bytes, passed unchanged to the selected stream routine.
 * Advances only the selected outbound stream state. Original entry 0x4010a0 is
 * cdecl; this normalized C API adds the originally implicit state argument.
 */
extern "C" void transform_outbound_payload(ClientCryptoState* state, void* data,
                                           uint32_t byte_count) {
    if (dat_02252fe9 != 0) {
        if (state->algorithm == 0)
            aes_transform_ctr(&state->outbound_aes, data, data, byte_count);
        else
            lcg_transform_stream(&state->outbound_lcg, data, data, byte_count);
    }
}

/**
 * Transform inbound bytes using the original flag, mode and algorithm dispatch.
 * @param state Explicit inbound AES/LCG state selected when dat_02252fe8 is zero.
 * @param data Writable/readable payload transformed in place on an enabled path.
 * @param byte_count Byte count passed to the stream transform or signed-tested table-XOR path.
 * With the alternate flag clear, dat_02252fea enables the selected inbound stream.
 * With that flag set, only mode two and a positive signed byte_count perform table XOR.
 * The latter reads dat_02251fe0[byte_count + i] without a modulo or bounds adjustment;
 * lengths above 2048 depend on storage beyond the known 4096-byte table.
 * Original cdecl entry: 0x4010e0; the context argument is normalized explicitly.
 */
extern "C" void transform_inbound_payload(ClientCryptoState* state, void* data,
                                          uint32_t byte_count) {
    if (dat_02252fe8 == 0) {
        if (dat_02252fea != 0) {
            if (state->algorithm == 0)
                aes_transform_ctr(&state->inbound_aes, data, data, byte_count);
            else
                lcg_transform_stream(&state->inbound_lcg, data, data, byte_count);
        }
    } else if (dat_02252fe4 == 2 && int32_t(byte_count) > 0) {
        uint8_t* bytes = static_cast<uint8_t*>(data);
        // Original 004010FD starts at table+byte_count, then reads byte_count bytes.
        // For byte_count>2048 this reaches outside the known 4096-byte table. No
        // bounds check or invented modulo is added: that original neighboring
        // storage layout remains an explicit incomplete integration boundary.
        for (uint32_t i = 0; i < byte_count; ++i)
            bytes[i] ^= dat_02251fe0[byte_count + i];
    }
}

/**
 * Reset both transport streams using the SHA-256 digest of the reconnect nonce.
 * @param state Explicit context containing the current algorithm, nonce and retained LCG key.
 * AES replaces both counters with the first sixteen digest bytes while retaining
 * schedules. LCG seeds combine the retained key with those digest bytes, advance
 * once to prefill each stream, then set both fragment positions to zero. Finally
 * clears all sixteen bytes of both reconnect_nonce and lcg_key.
 * Original cdecl entry: 0x4013a0; scattered original state is explicit in this API.
 */
extern "C" void reset_transport_streams_from_nonce(ClientCryptoState* state) {
    uint8_t digest[32];
    sha256_digest(digest, state->reconnect_nonce, 16);
    if (state->algorithm == 0) {
        copy_four_dword_bytes(state->outbound_aes.counter, digest);
        state->outbound_aes.position = 0;
        copy_four_dword_bytes(state->inbound_aes.counter, digest);
        state->inbound_aes.position = 0;
    } else {
        uint8_t material[32];
        copy_four_dword_bytes(material, state->lcg_key);
        copy_four_dword_bytes(material + 16, digest);
        copy_four_dword_bytes(state->outbound_lcg.seeds, material);
        copy_four_dword_bytes(state->outbound_lcg.seeds + 4, material + 16);
        lcg_generate_block(state->outbound_lcg.seeds, state->outbound_lcg.stream);
        copy_four_dword_bytes(state->inbound_lcg.seeds, material);
        copy_four_dword_bytes(state->inbound_lcg.seeds + 4, material + 16);
        state->outbound_lcg.position = 0;
        lcg_generate_block(state->inbound_lcg.seeds, state->inbound_lcg.stream);
        state->inbound_lcg.position = 0;
    }
    for (unsigned i = 0; i < 16; ++i) {
        state->reconnect_nonce[i] = 0;
        state->lcg_key[i] = 0;
    }
}
