#include "bigint.h"

namespace {
void copy_words_then_bytes(uint8_t* destination, const uint8_t* source, uint32_t count) {
    while (count >= 4) {
        uint32_t word = uint32_t(source[0]) | uint32_t(source[1]) << 8 | uint32_t(source[2]) << 16 |
                        uint32_t(source[3]) << 24;
        destination[0] = uint8_t(word);
        destination[1] = uint8_t(word >> 8);
        destination[2] = uint8_t(word >> 16);
        destination[3] = uint8_t(word >> 24);
        destination += 4;
        source += 4;
        count -= 4;
    }
    while (count != 0) {
        *destination++ = *source++;
        --count;
    }
}
} // namespace

extern "C" void fun_004053e0(const RsaPublicKey* key, void* output, uint32_t* output_bytes,
                             const void* input, uint32_t input_bytes) {
    BigInt result, base;
    fun_00585dc0(&result);
    fun_00585dc0(&base);
    fun_00405370(&base, input, input_bytes);
    fun_005861c0(&result, &base, &key->exponent, &key->modulus);
    *output_bytes = uint32_t(result.signed_size) * 4;
    copy_words_then_bytes(static_cast<uint8_t*>(output),
                          reinterpret_cast<const uint8_t*>(result.limbs), *output_bytes);
    fun_00586000(&result);
    fun_00586000(&base);
}
