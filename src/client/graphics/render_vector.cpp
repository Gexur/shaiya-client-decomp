#include "graphics/render_vector.h"

extern "C" int32_t __attribute__((stdcall)) FUN_005e3be9(float left, float right) {
    // Actual FSUB retains extended precision; both epsilon endpoints pass.
    const long double difference = static_cast<long double>(left) - static_cast<long double>(right);
    return difference >= -0x1p-23L && difference <= 0x1p-23L ? 1 : 0;
}

namespace {
void copy_word(float* output, const float* input) {
    auto* destination = reinterpret_cast<unsigned char*>(output);
    const auto* source = reinterpret_cast<const unsigned char*>(input);
    const uint32_t value = uint32_t(source[0]) | uint32_t(source[1]) << 8 |
                           uint32_t(source[2]) << 16 | uint32_t(source[3]) << 24;
    destination[0] = uint8_t(value);
    destination[1] = uint8_t(value >> 8);
    destination[2] = uint8_t(value >> 16);
    destination[3] = uint8_t(value >> 24);
}
} // namespace

extern "C" float* __attribute__((stdcall)) FUN_005e78ce(float* output, const float* input) {
    const long double x = input[0], y = input[1], z = input[2];
    const volatile float squared = static_cast<float>((x * x + y * y) + z * z);
    if (FUN_005e3be9(squared, 1.0f) != 0) {
        if (output == input)
            return output;
        copy_word(output, input);
        copy_word(output + 1, input + 1);
        copy_word(output + 2, input + 2);
        return output;
    }
    // Original branch also zeros an unordered length, unlike <= alone in C++.
    if (!(squared > 0x1p-126f)) {
        output[0] = 0;
        output[1] = 0;
        output[2] = 0;
        return output;
    }
    long double root;
    __asm__ __volatile__("fsqrt" : "=t"(root) : "0"(static_cast<long double>(squared)));
    const long double reciprocal = 1.0L / root;
    float normalized[3] = {static_cast<float>(reciprocal * static_cast<long double>(input[0])),
                           static_cast<float>(reciprocal * static_cast<long double>(input[1])),
                           static_cast<float>(reciprocal * static_cast<long double>(input[2]))};
    copy_word(output, normalized);
    copy_word(output + 1, normalized + 1);
    copy_word(output + 2, normalized + 2);
    return output;
}
