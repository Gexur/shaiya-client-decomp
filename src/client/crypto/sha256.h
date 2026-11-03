#pragma once

#include <stdint.h>
#include <stddef.h>

// Context offsets recovered from 00401820, 004041C0, and 00404270.
// Counts are bytes, not bits. No pointer or original image address is stored.
struct Sha256State {
    uint32_t byte_count_low;
    uint32_t byte_count_high;
    uint32_t words[8];
    uint8_t pending[64];
};
static_assert(sizeof(Sha256State) == 0x68, "original SHA context size");
static_assert(offsetof(Sha256State, words) == 8, "original chaining state offset");
static_assert(offsetof(Sha256State, pending) == 0x28, "original pending block offset");

#if defined(_WIN32)
#define SHAIYA_HASH_EXPORT __declspec(dllexport)
#else
#define SHAIYA_HASH_EXPORT
#endif

extern "C" {
// The named initialize helper is the repeated initialization sequence inside
// 00404410 and 004044A0; it is not a separate original procedure.
/// Initialize @p context's chaining words and byte counters; retain its pending bytes.
SHAIYA_HASH_EXPORT void sha256_initialize(Sha256State* context);

// Normalized C interfaces. Original private x86 register conventions:
// 00401820: block in EAX, context on stack.
// 004041C0: context in EBX, input and byte_count on stack.
// 00404270: context in ECX, output in ESI.
// 00404410: output in ECX, input and byte_count on stack.
// 004044A0: key length in ECX, key in EDX; output/message/byte_count on stack.
/// Compress the 64 readable @p block bytes into @p context without updating its byte count.
SHAIYA_HASH_EXPORT void sha256_compress_block(Sha256State* context, const uint8_t block[64]);
/// Append @p byte_count bytes from @p input to @p context; zero byte_count accesses neither pointer.
SHAIYA_HASH_EXPORT void sha256_update(Sha256State* context, const void* input, uint32_t byte_count);
/// Pad and modify @p context, then write the 32-byte big-endian digest to @p output.
SHAIYA_HASH_EXPORT void sha256_finalize(Sha256State* context, uint8_t output[32]);
/// Hash @p byte_count bytes from @p input into the 32 writable bytes at @p output.
SHAIYA_HASH_EXPORT void sha256_digest(uint8_t output[32], const void* input, uint32_t byte_count);
/**
 * Write the recovered HMAC-SHA-256 result to the 32-byte @p output buffer.
 * Uses @p key_byte_count bytes of @p key and @p message_byte_count bytes of @p message;
 * retains the original signed key-length test and fixed-buffer copying behavior.
 */
SHAIYA_HASH_EXPORT void hmac_sha256(uint8_t output[32], const void* key, uint32_t key_byte_count,
                                    const void* message, uint32_t message_byte_count);
}
