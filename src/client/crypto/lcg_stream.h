#pragma once

#include <stdint.h>
#include <stddef.h>

struct LcgStreamState {
    uint32_t seeds[8];
    uint8_t stream[16];
    int32_t position;
};
static_assert(offsetof(LcgStreamState, stream) == 0x20, "original LCG output offset");
static_assert(offsetof(LcgStreamState, position) == 0x30, "original LCG position offset");
static_assert(sizeof(LcgStreamState) == 0x34, "original LCG stream size");

#if defined(_WIN32)
#define SHAIYA_LCG_EXPORT __declspec(dllexport)
#else
#define SHAIYA_LCG_EXPORT
#endif

extern "C" {
// Original 004015C0: eight seed words in ECX, 16-byte output in ESI; EAX
// retains the low product of the last updated seed and 80008001.
/**
 * Advance all eight @p seeds and write sixteen bytes to @p output in reverse pair order.
 * @return The low 32 bits of the final seed multiplied by 0x80008001.
 */
SHAIYA_LCG_EXPORT uint32_t lcg_generate_block(uint32_t seeds[8], uint8_t output[16]);
// Original 00401700: context ECX, input EAX, output EDX; byte_count stack; RET 4.
/**
 * XOR @p byte_count bytes from @p input to @p output, updating @p context's seeds and fragment.
 * Supports identical buffers and preserves signed byte_count tests and DWORD access grouping.
 */
SHAIYA_LCG_EXPORT void lcg_transform_stream(LcgStreamState* context, const void* input,
                                            void* output, uint32_t byte_count);
// Original 004046A0: output/byte_count on stack, seed in global 0225328C.
// The normalized API makes that state explicit. For a nonzero remainder, the
// first leftover byte is written at output + (byte_count & ~3) - 1, including
// output[-1] for lengths 1..3. Callers must account for the original behavior.
// EAX is the output pointer when byte_count % 4 == 0; otherwise the last MUL low word.
/**
 * Generate @p byte_count bytes at @p output using and advancing the explicit @p seed.
 * Preserves the preceding-byte remainder write and the branch-dependent EAX return
 * described above; a remainder therefore requires writable storage before its rounded boundary.
 */
SHAIYA_LCG_EXPORT uint32_t lcg_fill_bytes(uint32_t* seed, void* output, uint32_t byte_count);
}
