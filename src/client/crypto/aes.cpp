#include "aes.h"

// Recovered from the key expansion, block transform, and retained counter stream
// procedures in game.exe. The tables below are named semantic data, not serialized
// image sections. Their original data locations and rotation equivalences are
// checked by tools/verify_cpp_aes.py against all original entries.
namespace {
#include "aes_tables.inc"

/**
 * Rotate one AES table word right by a nonzero byte rotation.
 * @param value Table word to rotate.
 * @param rotation_bits Rotation count of eight, sixteen or twenty-four bits.
 * @return Rotated 32-bit word.
 */
uint32_t rotate_word_right(uint32_t value, unsigned rotation_bits) {
    return value >> rotation_bits | value << (32 - rotation_bits);
}

/**
 * Decode one big-endian AES key or block word.
 * @param bytes Four readable bytes with no alignment requirement.
 * @return The decoded word.
 */
uint32_t load_big_endian_word(const uint8_t* bytes) {
    return uint32_t(bytes[0]) << 24 | uint32_t(bytes[1]) << 16 | uint32_t(bytes[2]) << 8 |
           uint32_t(bytes[3]);
}

/**
 * Encode one encrypted AES word in big-endian order.
 * @param bytes Four writable bytes with no alignment requirement.
 * @param value Word to store, most significant byte first.
 */
void store_big_endian_word(uint8_t* bytes, uint32_t value) {
    bytes[0] = uint8_t(value >> 24);
    bytes[1] = uint8_t(value >> 16);
    bytes[2] = uint8_t(value >> 8);
    bytes[3] = uint8_t(value);
}

/**
 * Read one little-endian word for the recovered DWORD-grouped stream XOR.
 * @param bytes Four readable bytes with no alignment requirement.
 * @return The decoded word.
 */
uint32_t load_little_endian_word(const uint8_t* bytes) {
    return uint32_t(bytes[0]) | uint32_t(bytes[1]) << 8 | uint32_t(bytes[2]) << 16 |
           uint32_t(bytes[3]) << 24;
}

/**
 * Write one little-endian word after the recovered stream XOR.
 * @param bytes Four writable bytes with no alignment requirement.
 * @param value Word to store, least significant byte first.
 */
void store_little_endian_word(uint8_t* bytes, uint32_t value) {
    bytes[0] = uint8_t(value);
    bytes[1] = uint8_t(value >> 8);
    bytes[2] = uint8_t(value >> 16);
    bytes[3] = uint8_t(value >> 24);
}

/**
 * Apply the recovered AES substitution table to each byte independently.
 * @param value Key-schedule word to substitute.
 * @return Substituted word in the same byte positions.
 */
uint32_t substitute_word(uint32_t value) {
    return uint32_t(substitution[value >> 24]) << 24 |
           uint32_t(substitution[value >> 16 & 255]) << 16 |
           uint32_t(substitution[value >> 8 & 255]) << 8 | uint32_t(substitution[value & 255]);
}

/**
 * Apply one AES table round and its four-word round key.
 * @param state Four AES state words, replaced after all next-state words are computed.
 * @param key Four readable expanded-key words for this round.
 */
void apply_aes_round(uint32_t state[4], const uint32_t* key) {
    uint32_t next[4];
    for (unsigned i = 0; i < 4; ++i) {
        next[i] = forward_table[state[i] >> 24] ^
                  rotate_word_right(forward_table[state[(i + 1) & 3] >> 16 & 255], 8) ^
                  rotate_word_right(forward_table[state[(i + 2) & 3] >> 8 & 255], 16) ^
                  rotate_word_right(forward_table[state[(i + 3) & 3] & 255], 24) ^ key[i];
    }
    for (unsigned i = 0; i < 4; ++i)
        state[i] = next[i];
}

/**
 * Encrypt the current counter into the retained stream block, then increment it.
 * @param context Initialized schedule, four-word counter and writable stream storage.
 * Carry propagates from counter[0] through counter[3] in the original little-endian
 * DWORD order. The fragment position is controlled by the caller.
 */
void generate_counter_stream_block(AesCtrState* context) {
    aes_encrypt_block(&context->schedule, reinterpret_cast<const uint8_t*>(context->counter),
                      context->stream);
    // Original ADD/JNE carry chain at 0040529D..004052B5.
    if (++context->counter[0] == 0)
        if (++context->counter[1] == 0)
            if (++context->counter[2] == 0)
                ++context->counter[3];
}
} // namespace

/**
 * Expand a 128-, 192- or 256-bit AES key into the recovered encryption schedule.
 * @param context Writable schedule receiving used key words and the round count.
 * @param key Readable key bytes in their original order.
 * @param key_bit_count Key size in bits; only 128, 192 and 256 are accepted.
 * @return Zero on success, minus one for a null context/key, or minus two for an
 * unsupported key size. Error paths leave the schedule untouched.
 * Unused trailing schedule words retain their previous contents. The normalized
 * C API replaces entry 0x404770's EAX context, EDX key and ECX key-size convention.
 */
extern "C" int32_t aes_expand_key(AesSchedule* context, const void* key, uint32_t key_bit_count) {
    if (context == nullptr || key == nullptr)
        return -1;
    if (key_bit_count != 128 && key_bit_count != 192 && key_bit_count != 256)
        return -2;
    context->round_count = key_bit_count == 128 ? 10 : (key_bit_count == 192 ? 12 : 14);
    const uint32_t key_words = key_bit_count >> 5;
    const uint8_t* bytes = static_cast<const uint8_t*>(key);
    for (uint32_t i = 0; i < key_words; ++i)
        context->words[i] = load_big_endian_word(bytes + i * 4);
    // The original three specialized branches share this recurrence. Unused tail
    // words in 128/192-bit schedules are intentionally left untouched.
    const uint32_t end = (context->round_count + 1) * 4;
    for (uint32_t i = key_words; i < end; ++i) {
        uint32_t previous = context->words[i - 1];
        if (i % key_words == 0) {
            previous = substitute_word((previous << 8) | (previous >> 24)) ^
                       round_constants[i / key_words - 1];
        } else if (key_words == 8 && i % key_words == 4) {
            previous = substitute_word(previous);
        }
        context->words[i] = context->words[i - key_words] ^ previous;
    }
    return 0;
}

/**
 * Encrypt one sixteen-byte block with an expanded AES schedule.
 * @param schedule Schedule produced by the recovered key-expansion routine.
 * @param input Sixteen readable input bytes, all loaded before output is written.
 * @param output Sixteen writable output bytes; the same buffer may serve as input.
 * Retains the signed-halved round count and two-round loop. This C API normalizes
 * entry 0x404c80's EAX schedule, ECX input and caller-cleaned stack output argument.
 */
extern "C" void aes_encrypt_block(const AesSchedule* schedule, const uint8_t input[16],
                                  uint8_t output[16]) {
    uint32_t state[4];
    for (unsigned i = 0; i < 4; ++i)
        state[i] = load_big_endian_word(input + i * 4) ^ schedule->words[i];
    apply_aes_round(state, schedule->words + 4);
    uint32_t pairs = uint32_t(int32_t(schedule->round_count) >> 1);
    const uint32_t* key = schedule->words + 8;
    // Keep the original two-round loop and signed-halved round count.
    while (--pairs != 0) {
        apply_aes_round(state, key);
        apply_aes_round(state, key + 4);
        key += 8;
    }
    for (unsigned i = 0; i < 4; ++i) {
        uint32_t last = uint32_t(substitution[state[i] >> 24]) << 24 |
                        uint32_t(substitution[state[(i + 1) & 3] >> 16 & 255]) << 16 |
                        uint32_t(substitution[state[(i + 2) & 3] >> 8 & 255]) << 8 |
                        uint32_t(substitution[state[(i + 3) & 3] & 255]);
        store_big_endian_word(output + i * 4, last ^ key[i]);
    }
}

/**
 * XOR bytes with the retained AES counter stream, updating counter and fragment state.
 * @param context Initialized AES schedule/counter with a retained position from zero to fifteen.
 * @param input Readable input range of byte_count bytes.
 * @param output Writable range of byte_count bytes; input and output may be identical.
 * @param byte_count Byte count, retaining the original signed branch comparisons.
 * Consumes a pending fragment before generating blocks, increments the little-endian
 * counter after each generation, and retains a partial block for the next call.
 * Whole blocks retain the four-DWORD forward read/write grouping. The normalized C
 * API replaces entry 0x4051b0's ESI context, EAX input, ECX output and RET4 byte_count.
 */
extern "C" void aes_transform_ctr(AesCtrState* context, const void* input, void* output,
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
            generate_counter_stream_block(context);
            // Match the original four DWORD reads/writes, supporting in-place
            // operation and preserving its forward-copy grouping.
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
        generate_counter_stream_block(context);
        while (context->position < int32_t(byte_count)) {
            *destination++ = context->stream[context->position] ^ *source++;
            ++context->position;
        }
    }
}
