#include "bootstrap.h"
#include "bigint.h"

/**
 * Initialize A101 transport material and produce its RSA public-operation reply.
 * @param state Explicit client context receiving algorithm, PRNG and stream state updates.
 * @param reply Writable reply storage large enough for the resulting whole-limb byte sequence.
 * @param reply_bytes Receives the output byte count; its incoming value is unused.
 * @param algorithm Zero selects AES; every other value selects the LCG stream setup.
 * @param exponent Readable little-endian public-exponent bytes.
 * @param exponent_bytes Public-exponent byte count passed to the recovered integer importer.
 * @param modulus Readable little-endian modulus bytes, also used in material derivation.
 * @param modulus_bytes Modulus byte count passed unchanged to derivation and import.
 * Generates a 128-byte local value, imports both public-key integers, computes the
 * reply, then releases exponent and modulus storage in the original order.
 * Original entry 0x401160 uses cdecl stack arguments; this C API adds explicit state.
 */
extern "C" void build_a101_crypto_reply(ClientCryptoState* state, void* reply,
                                        uint32_t* reply_bytes, uint32_t algorithm,
                                        const void* exponent, uint32_t exponent_bytes,
                                        const void* modulus, uint32_t modulus_bytes) {
    uint8_t random128[128];
    client_crypto_initialize_a101(state, algorithm, modulus, modulus_bytes, random128);
    RsaPublicKey public_key;
    fun_00585dc0(&public_key.exponent);
    fun_00585dc0(&public_key.modulus);
    fun_00405370(&public_key.exponent, exponent, exponent_bytes);
    fun_00405370(&public_key.modulus, modulus, modulus_bytes);
    fun_004053e0(&public_key, reply, reply_bytes, random128, 128);
    fun_00586000(&public_key.exponent);
    fun_00586000(&public_key.modulus);
}
