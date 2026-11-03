#include "crypto_original_abi.h"
#include "network/crypto_state.h"
#include "crypto/transport.h"

// Bridge the original void(void) caller to the recovered explicit-state API.
// This uses the same context as the real A101, send and receive paths.
extern "C" void client_crypto_reconnect_original_abi() {
    reset_transport_streams_from_nonce(&client_crypto_state);
}
