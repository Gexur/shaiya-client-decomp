#include "sha256.h"

// Recovered from game.exe SHA256
// 796af141fd13451bab67ae0bae02d2177b1fe60af51775f296bec7b0eff752da.
// The original compression procedure is unrolled. Here its repeated unsigned
// word recurrence is expressed as a loop, using the 64 original round immediates.
// No external cryptographic implementation is used. See evidence/cpp-hashing*.
namespace {
constexpr uint32_t round_immediates[64] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
};

/**
 * Rotate a 32-bit word right by the nonzero SHA schedule or round rotation.
 * @param value Word whose rotation_bits are rotated.
 * @param rotation_bits Rotation count in the range one through thirty-one.
 * @return The rotated word with all arithmetic confined to 32 rotation_bits.
 */
uint32_t rotate_word_right(uint32_t value, unsigned rotation_bits) {
    return (value >> rotation_bits) | (value << (32 - rotation_bits));
}

/**
 * Load one big-endian SHA word without requiring aligned input.
 * @param input Four readable bytes, most significant byte first.
 * @return The decoded 32-bit word.
 */
uint32_t load_big_endian_word(const uint8_t* input) {
    return (uint32_t(input[0]) << 24) | (uint32_t(input[1]) << 16) | (uint32_t(input[2]) << 8) |
           uint32_t(input[3]);
}

/**
 * Store one word in the SHA digest's big-endian byte order.
 * @param output Four writable bytes, with no alignment requirement.
 * @param value Word to encode, most significant byte first.
 */
void store_big_endian_word(uint8_t* output, uint32_t value) {
    output[0] = uint8_t(value >> 24);
    output[1] = uint8_t(value >> 16);
    output[2] = uint8_t(value >> 8);
    output[3] = uint8_t(value);
}

/**
 * Copy bytes in the original REP MOVSD then REP MOVSB grouping.
 * @param destination Writable range of byte_count bytes.
 * @param source Readable range of byte_count bytes.
 * @param byte_count Number of bytes to copy forward.
 * Each complete DWORD is read before its four bytes are written, retaining the
 * original overlap behavior rather than introducing memmove semantics.
 */
void copy_dword_grouped_bytes(uint8_t* destination, const uint8_t* source, uint32_t byte_count) {
    while (byte_count >= 4) {
        uint32_t word = uint32_t(source[0]) | uint32_t(source[1]) << 8 | uint32_t(source[2]) << 16 |
                        uint32_t(source[3]) << 24;
        destination[0] = uint8_t(word);
        destination[1] = uint8_t(word >> 8);
        destination[2] = uint8_t(word >> 16);
        destination[3] = uint8_t(word >> 24);
        destination += 4;
        source += 4;
        byte_count -= 4;
    }
    while (byte_count != 0) {
        *destination++ = *source++;
        --byte_count;
    }
}
} // namespace

/**
 * Initialize SHA-256 chaining words and the two-word byte counter.
 * @param context Writable SHA context; its pending buffer is left untouched.
 * This factors the initialization repeated within original entries 0x404410 and
 * 0x4044a0; it has no separate original entry or private register convention.
 */
extern "C" void sha256_initialize(Sha256State* context) {
    context->byte_count_low = 0;
    context->byte_count_high = 0;
    context->words[0] = 0x6a09e667;
    context->words[1] = 0xbb67ae85;
    context->words[2] = 0x3c6ef372;
    context->words[3] = 0xa54ff53a;
    context->words[4] = 0x510e527f;
    context->words[5] = 0x9b05688c;
    context->words[6] = 0x1f83d9ab;
    context->words[7] = 0x5be0cd19;
}

/**
 * Compress one 64-byte SHA-256 block into the context's chaining words.
 * @param context Initialized context whose eight chaining words are updated.
 * @param block Complete readable block in message byte order.
 * The byte counter and pending buffer retain their current values. This C API
 * normalizes original entry 0x401820's block-in-EAX/context-on-stack convention.
 */
extern "C" void sha256_compress_block(Sha256State* context, const uint8_t block[64]) {
    uint32_t schedule[64];
    for (unsigned i = 0; i < 16; ++i)
        schedule[i] = load_big_endian_word(block + i * 4);
    // 00401820's unrolled schedule first repeats this recurrence after round 15.
    for (unsigned i = 16; i < 64; ++i) {
        uint32_t x = schedule[i - 2], y = schedule[i - 15];
        schedule[i] = (rotate_word_right(x, 19) ^ rotate_word_right(x, 17) ^ (x >> 10)) +
                      (rotate_word_right(y, 18) ^ rotate_word_right(y, 7) ^ (y >> 3)) +
                      schedule[i - 7] + schedule[i - 16];
    }
    uint32_t a = context->words[0], b = context->words[1];
    uint32_t c = context->words[2], d = context->words[3];
    uint32_t e = context->words[4], f = context->words[5];
    uint32_t g = context->words[6], h = context->words[7];
    for (unsigned i = 0; i < 64; ++i) {
        uint32_t first =
            (((g ^ f) & e) ^ g) +
            (rotate_word_right(e, 25) ^ rotate_word_right(e, 11) ^ rotate_word_right(e, 6)) + h +
            round_immediates[i] + schedule[i];
        uint32_t second =
            (((b | a) & c) | (b & a)) +
            (rotate_word_right(a, 22) ^ rotate_word_right(a, 13) ^ rotate_word_right(a, 2));
        h = g;
        g = f;
        f = e;
        e = d + first;
        d = c;
        c = b;
        b = a;
        a = first + second;
    }
    context->words[0] += a;
    context->words[1] += b;
    context->words[2] += c;
    context->words[3] += d;
    context->words[4] += e;
    context->words[5] += f;
    context->words[6] += g;
    context->words[7] += h;
}

/**
 * Append message bytes, compressing complete blocks and retaining a partial tail.
 * @param context Initialized context; a zero byte_count returns before accessing it.
 * @param input Readable message bytes; unused when byte_count is zero.
 * @param byte_count Number of input bytes, added to the wrapping 64-bit byte counter.
 * Preserves the original DWORD-grouped copies. The normalized C interface replaces
 * original entry 0x4041c0's context-in-EBX and stack input/byte_count convention.
 */
extern "C" void sha256_update(Sha256State* context, const void* input, uint32_t byte_count) {
    if (byte_count == 0)
        return;
    const uint8_t* bytes = static_cast<const uint8_t*>(input);
    uint32_t used = context->byte_count_low & 0x3f;
    uint32_t available = 0x40 - used;
    context->byte_count_low += byte_count;
    if (context->byte_count_low < byte_count)
        ++context->byte_count_high;
    if (used != 0 && available <= byte_count) {
        copy_dword_grouped_bytes(context->pending + used, bytes, available);
        sha256_compress_block(context, context->pending);
        bytes += available;
        byte_count -= available;
        used = 0;
    }
    while (byte_count >= 0x40) {
        sha256_compress_block(context, bytes);
        bytes += 0x40;
        byte_count -= 0x40;
    }
    if (byte_count != 0)
        copy_dword_grouped_bytes(context->pending + used, bytes, byte_count);
}

/**
 * Append SHA padding and the original bit count, then serialize the 32-byte digest.
 * @param context Initialized message context, modified by the padding updates.
 * @param output Writable 32-byte digest destination in big-endian word order.
 * Retains the finalized state and padding byte count in the context. This C API
 * normalizes original entry 0x404270's context-in-ECX/output-in-ESI convention.
 */
extern "C" void sha256_finalize(Sha256State* context, uint8_t output[32]) {
    uint8_t bit_count[8];
    const uint32_t low = context->byte_count_low;
    store_big_endian_word(bit_count, (context->byte_count_high << 3) | (low >> 29));
    store_big_endian_word(bit_count + 4, low << 3);
    const uint32_t used = low & 0x3f;
    const uint32_t padding_length = (used < 0x38 ? 0x38 : 0x78) - used;
    // Original data at 00719118: 80 followed by zero bytes.
    const uint8_t padding[64] = {0x80};
    sha256_update(context, padding, padding_length);
    sha256_update(context, bit_count, 8);
    for (unsigned i = 0; i < 8; ++i)
        store_big_endian_word(output + 4 * i, context->words[i]);
}

/**
 * Compute a complete SHA-256 digest with a local context.
 * @param output Writable 32-byte digest destination.
 * @param input Readable message bytes; unused when byte_count is zero.
 * @param byte_count Number of message bytes.
 * The C API normalizes original entry 0x404410's output-in-ECX and stack arguments.
 */
extern "C" void sha256_digest(uint8_t output[32], const void* input, uint32_t byte_count) {
    Sha256State context;
    sha256_initialize(&context);
    sha256_update(&context, input, byte_count);
    sha256_finalize(&context, output);
}

/**
 * Compute the recovered HMAC-SHA-256 inner and outer digest sequence.
 * @param output Writable 32-byte result, also used to stage the inner digest.
 * @param key Readable key bytes; lengths above sixty-four are hashed when the
 * original signed key-length comparison selects that branch.
 * @param key_byte_count Key length in bytes, retaining the original signed branch test.
 * @param message Readable message bytes; unused when message_byte_count is zero.
 * @param message_byte_count Message length in bytes.
 * Retains the original fixed-buffer copies and conversion of key lengths to signed
 * values. The normalized C API replaces entry 0x4044a0's ECX key length, EDX key,
 * and stacked output/message/message-length convention.
 */
extern "C" void hmac_sha256(uint8_t output[32], const void* key, uint32_t key_byte_count,
                            const void* message, uint32_t message_byte_count) {
    const uint8_t* key_bytes = static_cast<const uint8_t*>(key);
    uint8_t shortened_key[32];
    // 004044CF is signed JLE, retained here rather than silently normalizing it.
    if (static_cast<int32_t>(key_byte_count) > 0x40) {
        sha256_digest(shortened_key, key_bytes, key_byte_count);
        key_bytes = shortened_key;
        key_byte_count = 0x20;
    }
    uint8_t inner[64], outer[64];
    for (unsigned i = 0; i < 64; ++i) {
        inner[i] = 0;
        outer[i] = 0;
    }
    copy_dword_grouped_bytes(inner, key_bytes, key_byte_count);
    copy_dword_grouped_bytes(outer, key_bytes, key_byte_count);
    for (unsigned i = 0; i < 64; ++i) {
        inner[i] ^= 0x36;
        outer[i] ^= 0x5c;
    }
    Sha256State context;
    sha256_initialize(&context);
    sha256_update(&context, inner, 64);
    sha256_update(&context, message, message_byte_count);
    sha256_finalize(&context, output);
    sha256_initialize(&context);
    sha256_update(&context, outer, 64);
    sha256_update(&context, output, 32);
    sha256_finalize(&context, output);
}
