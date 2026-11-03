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

extern "C" void fun_00585dc0(BigInt* value) {
    value->capacity = 1;
    value->limbs = static_cast<uint32_t*>(dat_0070c0d0(4));
    value->signed_size = 0;
}

extern "C" void fun_00586000(BigInt* value) {
    dat_0070c0d8(value->limbs, uint32_t(value->capacity) << 2);
}

extern "C" void fun_00587300(BigInt* value, int32_t limb_capacity) {
    if (limb_capacity < 2)
        limb_capacity = 1;
    uint32_t* resized = static_cast<uint32_t*>(
        dat_0070c0d4(value->limbs, uint32_t(value->capacity) << 2, uint32_t(limb_capacity) * 4));
    int32_t size = value->signed_size;
    value->limbs = resized;
    value->capacity = limb_capacity;
    int32_t magnitude = size < 0 ? int32_t(0u - uint32_t(size)) : size;
    if (limb_capacity < magnitude)
        value->signed_size = 0;
}

extern "C" void fun_00586f20(BigInt* output, const BigInt* input) {
    int32_t size = input->signed_size;
    int32_t count = size < 0 ? int32_t(0u - uint32_t(size)) : size;
    if (output->capacity < count)
        fun_00587300(output, count);
    uint32_t* destination = output->limbs;
    const uint32_t* source = input->limbs;
    uint32_t remaining = uint32_t(count);
    if (remaining != 0)
        do {
            *destination++ = *source++;
        } while (--remaining != 0);
    output->signed_size = size;
}

extern "C" void fun_00405370(BigInt* value, const void* input, uint32_t bytes) {
    int32_t count = int32_t(bytes) >> 2;
    if (bytes != uint32_t(count) * 4)
        ++count;
    if (value->signed_size < count) {
        value->limbs = static_cast<uint32_t*>(fun_005d020a(value->limbs, uint32_t(count) * 4));
        value->capacity = count + 1;
    }
    value->signed_size = count;
    // These stores are an observed property of the original import wrapper,
    // including count 0/1. Do not replace them with a safe generalized import.
    value->limbs[count - 1] = 0;
    value->limbs[count - 2] = 0;
    copy_words_then_bytes(reinterpret_cast<uint8_t*>(value->limbs),
                          static_cast<const uint8_t*>(input), bytes);
}
