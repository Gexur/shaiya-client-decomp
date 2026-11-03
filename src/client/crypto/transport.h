#pragma once

#include "bootstrap.h"

extern "C" {
// Canonical definitions belong to network/transport_seed.cpp and network socket
// globals. Crypto adds no second copy of these original storage locations.
extern uint8_t dat_02251fe0[4096];
extern uint32_t dat_02252fe4;
extern uint8_t dat_02252fe8;
extern uint8_t dat_02252fe9;
extern uint8_t dat_02252fea;

// Original procedures are cdecl with the input arguments on the stack; the
// normalized interface makes scattered original crypto state explicit.
/**
 * Install @p material's sixteen key bytes and sixteen counter bytes into both AES streams
 * in @p state, reset fragment positions, and enable the canonical transform flags.
 */
SHAIYA_BOOTSTRAP_EXPORT void initialize_transport_aes_material(ClientCryptoState* state,
                                                               const uint8_t material[32]);
/// Transform @p byte_count outbound bytes at @p data in place using enabled @p state stream selection.
SHAIYA_BOOTSTRAP_EXPORT void transform_outbound_payload(ClientCryptoState* state, void* data,
                                                        uint32_t byte_count);
/**
 * Transform @p byte_count inbound bytes at @p data using @p state or the mode-two XOR table.
 * The table path starts at table + byte_count and retains its original adjacent-storage dependency.
 */
SHAIYA_BOOTSTRAP_EXPORT void transform_inbound_payload(ClientCryptoState* state, void* data,
                                                       uint32_t byte_count);
/// Reset both streams in @p state from its reconnect nonce, then clear its nonce and retained LCG key.
SHAIYA_BOOTSTRAP_EXPORT void reset_transport_streams_from_nonce(ClientCryptoState* state);
}
