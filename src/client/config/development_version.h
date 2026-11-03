#pragma once
#include <stdint.h>

extern "C" {
// Version sent in the game-server selection packet and its connection log.
extern uint32_t shaiya_client_version;

// Read SHAIYA_CLIENT_VERSION as an unsigned 32-bit decimal or 0x-prefixed
// hexadecimal integer. Missing, empty, invalid or oversized values restore
// the recovered default, 0x11122200. Signs and whitespace are not accepted.
void shaiya_apply_development_client_version();
}
