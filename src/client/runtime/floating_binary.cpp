#include "floating_binary.h"
extern "C" void fun_005dcd7c(void* extended80, const void* binary64) {
    auto* output = static_cast<uint32_t*>(extended80);
    auto* input = static_cast<const uint32_t*>(binary64);
    const uint16_t upper = uint16_t(input[1] >> 16);
    uint16_t exponent = (upper >> 4) & 0x7ff;
    uint32_t hidden = 0x80000000u;
    const uint32_t low = input[0];
    if (!exponent) {
        if (!(input[1] & 0xfffffu) && !low) {
            output[1] = 0;
            output[0] = 0;
            *reinterpret_cast<uint16_t*>(output + 2) = 0;
            return;
        }
        exponent = uint16_t(exponent + 0x3c01);
        hidden = 0;
    } else if (exponent == 0x7ff)
        exponent = 0x7fff;
    else
        exponent = uint16_t(exponent + 0x3c00);
    output[1] = (low >> 21) | ((input[1] & 0xfffffu) << 11) | hidden;
    output[0] = low << 11;
    while (!hidden) {
        const uint32_t high = output[1];
        --exponent;
        output[1] = (high << 1) | (output[0] >> 31);
        output[0] <<= 1;
        hidden = (high << 1) & 0x80000000u;
    }
    *reinterpret_cast<uint16_t*>(output + 2) = (upper & 0x8000) | exponent;
}
