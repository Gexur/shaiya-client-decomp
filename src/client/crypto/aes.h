#pragma once

#include <stdint.h>
#include <stddef.h>

struct AesSchedule {
    uint32_t words[60];
    uint32_t round_count;
};

struct AesCtrState {
    AesSchedule schedule;
    uint32_t counter[4];
    int32_t position;
    uint8_t stream[16];
};
static_assert(sizeof(AesSchedule) == 0xf4, "original AES schedule size");
static_assert(offsetof(AesSchedule, round_count) == 0xf0, "original AES rounds offset");
static_assert(offsetof(AesCtrState, counter) == 0xf4, "original little endian counter offset");
static_assert(offsetof(AesCtrState, position) == 0x104, "original fragment position offset");
static_assert(offsetof(AesCtrState, stream) == 0x108, "original encrypted counter offset");
static_assert(sizeof(AesCtrState) == 0x118, "original AES counter state size");

#if defined(_WIN32)
#define SHAIYA_AES_EXPORT __declspec(dllexport)
#else
#define SHAIYA_AES_EXPORT
#endif

extern "C" {
// Normalized C interfaces. Original private x86 register conventions:
// 00404770: context EAX, key EDX, key bits ECX; result EAX.
// 00404C80: schedule EAX, input ECX, output on stack (caller removes it).
// 004051B0: context ESI, input EAX, output ECX, byte_count on stack (RET 4).
/**
 * Expand @p key into @p context for @p key_bit_count equal to 128, 192 or 256.
 * @return Zero on success, -1 for a null pointer, or -2 for an unsupported key size.
 */
SHAIYA_AES_EXPORT int32_t aes_expand_key(AesSchedule* context, const void* key,
                                         uint32_t key_bit_count);
/**
 * Encrypt sixteen bytes from @p input to @p output using the expanded @p schedule.
 * Input and output may be identical; the schedule and round count must be initialized.
 */
SHAIYA_AES_EXPORT void aes_encrypt_block(const AesSchedule* schedule, const uint8_t input[16],
                                         uint8_t output[16]);
/**
 * XOR @p byte_count bytes from @p input to @p output using and advancing @p context.
 * Supports identical buffers and retains counter carry, partial blocks and signed byte_count tests.
 */
SHAIYA_AES_EXPORT void aes_transform_ctr(AesCtrState* context, const void* input, void* output,
                                         uint32_t byte_count);
}
