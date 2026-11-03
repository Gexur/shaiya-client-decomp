#include "lcg_stream.h"

// Recovered directly from 004015C0..00401812. The eight independent 31-bit
// recurrences are paired into four output words in reverse order. Division is
// by FFFF, rather than a bit shift or the familiar CRT rand() output mask.
namespace {
/**
 * Read one little-endian word for the original DWORD-grouped stream XOR.
 * @param bytes Four readable bytes with no alignment requirement.
 * @return The decoded word.
 */
uint32_t load_little_endian_word(const uint8_t* bytes) {
    return uint32_t(bytes[0]) | uint32_t(bytes[1]) << 8 | uint32_t(bytes[2]) << 16 |
           uint32_t(bytes[3]) << 24;
}

/**
 * Store one little-endian generated or transformed word.
 * @param bytes Four writable bytes with no alignment requirement.
 * @param value Word to encode, least significant byte first.
 */
void store_little_endian_word(uint8_t* bytes, uint32_t value) {
    bytes[0] = uint8_t(value);
    bytes[1] = uint8_t(value >> 8);
    bytes[2] = uint8_t(value >> 16);
    bytes[3] = uint8_t(value >> 24);
}
} // namespace

/**
 * Advance eight independent 31-bit LCG seeds and produce one sixteen-byte block.
 * @param seeds Eight writable seed words, advanced once each in ascending index order.
 * @param output Sixteen writable bytes receiving four seed pairs in reverse pair order.
 * @return Low 32 bits of the last updated seed multiplied by 0x80008001, preserving EAX.
 * Output components use division by 0xffff. The normalized C API replaces original
 * entry 0x4015c0's ECX seed array and ESI output convention.
 */
extern "C" uint32_t lcg_generate_block(uint32_t seeds[8], uint8_t output[16]) {
    uint32_t last = 0;
    for (unsigned pair = 0; pair < 4; ++pair) {
        const unsigned i = pair * 2;
        uint32_t first = (seeds[i] * 0x343fd + 0x269ec3) & 0x7fffffff;
        seeds[i] = first;
        last = (seeds[i + 1] * 0x343fd + 0x269ec3) & 0x7fffffff;
        seeds[i + 1] = last;
        store_little_endian_word(output + (3 - pair) * 4, (last / 0xffff) << 16 | (first / 0xffff));
    }
    return last * 0x80008001;
}

/**
 * XOR bytes with the retained eight-seed LCG stream and preserve its partial block.
 * @param context Initialized seed/stream state with a retained position from zero to fifteen.
 * @param input Readable input range of byte_count bytes.
 * @param output Writable range of byte_count bytes; input and output may be identical.
 * @param byte_count Byte count, preserving the original signed branch comparisons.
 * Pending bytes are consumed before generating another block. Whole blocks preserve
 * the four-DWORD forward read/write grouping. The normalized C API replaces original
 * entry 0x401700's ECX context, EAX input, EDX output and RET4 stack byte_count.
 */
extern "C" void lcg_transform_stream(LcgStreamState* context, const void* input, void* output,
                                     uint32_t byte_count) {
    const uint8_t* source = static_cast<const uint8_t*>(input);
    uint8_t* destination = static_cast<uint8_t*>(output);
    if (context->position > 0) {
        int32_t available = 16 - context->position;
        if (int32_t(byte_count) <= available) {
            while (byte_count != 0) {
                *destination++ = context->stream[context->position] ^ *source++;
                ++context->position;
                --byte_count;
            }
            if (context->position >= 16)
                context->position = 0;
            return;
        }
        byte_count -= uint32_t(available);
        while (context->position < 16) {
            *destination++ = context->stream[context->position] ^ *source++;
            ++context->position;
        }
        context->position = 0;
    }
    if (int32_t(byte_count) >= 16) {
        uint32_t blocks = byte_count >> 4;
        byte_count -= blocks * 16;
        do {
            lcg_generate_block(context->seeds, context->stream);
            for (unsigned i = 0; i < 4; ++i) {
                uint32_t value = load_little_endian_word(source + i * 4) ^
                                 load_little_endian_word(context->stream + i * 4);
                store_little_endian_word(destination + i * 4, value);
            }
            source += 16;
            destination += 16;
        } while (--blocks != 0);
    }
    if (int32_t(byte_count) > 0) {
        lcg_generate_block(context->seeds, context->stream);
        while (context->position < int32_t(byte_count)) {
            *destination++ = context->stream[context->position] ^ *source++;
            ++context->position;
        }
    }
}

/**
 * Fill bytes from the single-seed LCG using the original word and leftover paths.
 * @param seed Writable seed, made explicit from original global 0x225328c.
 * @param output Output address used by both the complete-word and leftover-byte paths.
 * @param byte_count Requested byte count; the whole-word count retains its signed shift.
 * @return Low 32 bits of the original output pointer for a multiple of four bytes;
 * otherwise the last updated seed multiplied by 0x80008001 modulo 2^32.
 * @note A nonzero remainder starts writing at output + (byte_count & ~3) - 1. This
 * overwrites the final complete-word byte, or writes output[-1] for lengths one
 * through three; callers supply storage for that original behavior. This C API
 * normalizes original entry 0x4046a0's stacked output and byte_count plus global seed.
 */
extern "C" uint32_t lcg_fill_bytes(uint32_t* seed, void* output, uint32_t byte_count) {
    uint8_t* destination = static_cast<uint8_t*>(output);
    const uint32_t remainder = byte_count & 3;
    // Original SAR EAX,2 followed by a decrement-until-zero counter.
    uint32_t word_count = uint32_t(int32_t(byte_count) >> 2);
    if (word_count != 0) {
        do {
            uint32_t first = (*seed * 0x343fd + 0x269ec3) & 0x7fffffff;
            uint32_t second = (first * 0x343fd + 0x269ec3) & 0x7fffffff;
            *seed = second;
            store_little_endian_word(destination, (second / 0xffff) << 16 | (first / 0xffff));
            destination += 4;
        } while (--word_count != 0);
    }
    // 00404717 reloads the original output argument into EAX, even after a
    // nonempty whole-word loop. The trailing-byte MUL replaces EAX only when
    // there is a remainder. Preserve both observable return values.
    uint32_t result = uint32_t(reinterpret_cast<uintptr_t>(output));
    if (remainder != 0) {
        destination = static_cast<uint8_t*>(output) + (byte_count - remainder) - 1;
        for (uint32_t i = 0; i < remainder; ++i) {
            *seed = (*seed * 0x343fd + 0x269ec3) & 0x7fffffff;
            result = *seed * 0x80008001;
            *destination++ = uint8_t(*seed / 0xffff);
        }
    }
    return result;
}
