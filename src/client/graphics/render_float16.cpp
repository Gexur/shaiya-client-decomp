#include "graphics/render_float16.h"
namespace {
inline uint32_t word(uint32_t address) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(address) : "memory");
    return v;
}
inline uint32_t half(uint32_t address) {
    uint32_t v;
    __asm__ volatile("movzwl (%1),%0" : "=r"(v) : "r"(address) : "memory");
    return v;
}
inline void put_word(uint32_t address, uint32_t v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(address), "r"(v) : "memory");
}
inline void put_half(uint32_t address, uint32_t v) {
    __asm__ volatile("movw %w1,(%0)" ::"r"(address), "r"(v) : "memory");
}
} // namespace

// Full original005e3c36..005e3cd8. Saturation to signed7fff is intentional.
extern "C" void* recovered_005e3c36(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    const uint32_t output = word(slots);
    uint32_t index = 0;
    if (word(slots + 8) > index) {
        do {
            const uint32_t input = word(slots + 4);
            const uint32_t raw = word(input + index * 4);
            const uint32_t sign = (raw >> 16) & 0x8000u;
            const uint32_t magnitude = raw & 0x7fffffffu;
            uint32_t encoded;
            if (magnitude > 0x47ffefffu)
                encoded = sign | 0x7fffu;
            else {
                uint32_t rounded;
                if (magnitude < 0x38800000u) {
                    uint32_t significand = (magnitude & 0x7fffffu) | 0x800000u;
                    const uint32_t shift = 0x71u - (magnitude >> 23);
                    if (shift > 31)
                        significand = 0;
                    else
                        significand >>= shift;
                    rounded = significand + ((significand >> 13) & 1u) + 0xfffu;
                } else
                    rounded = magnitude + ((magnitude >> 13) & 1u) - 0x37fff001u;
                encoded = (rounded >> 13) | sign;
            }
            put_half(output + index * 2, encoded);
            ++index;
        } while (index < word(slots + 8));
    }
    return reinterpret_cast<void*>(output);
}

// Full original005e3cf1..005e3d98. Exponent31 follows the original finite
// exponent path; an IEEE-half library conversion would change the client.
extern "C" void* recovered_005e3cf1(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    uint32_t index = 0;
    if (word(slots + 8) > index) {
        do {
            const uint32_t input = word(slots + 4);
            const uint32_t raw = half(input + index * 2);
            uint32_t encoded;
            if ((raw & 0xffff7c00u) == 0) {
                if ((raw & 0x3ffu) == 0)
                    encoded = (raw & 0xffff8000u) << 16;
                else {
                    int32_t exponent = -14;
                    uint32_t significand = raw & 0x3ffu;
                    while ((significand & 0x400u) == 0) {
                        --exponent;
                        significand <<= 1;
                    }
                    uint32_t value = ((raw & 0xffff8080u) << 3) | significand;
                    value &= 0xfffffbffu;
                    encoded = (value << 13) | (uint32_t(exponent + 0x7f) << 23);
                }
            } else {
                uint32_t value = ((raw & 0xffff8000u) << 3) | (raw & 0x3ffu);
                const uint32_t exponent = ((raw >> 10) & 0x1fu) + 0x70u;
                encoded = (value << 13) | (exponent << 23);
            }
            const uint32_t output = word(slots);
            put_word(output + index * 4, encoded);
            ++index;
        } while (index < word(slots + 8));
    }
    return reinterpret_cast<void*>(word(slots));
}

extern "C" __attribute__((naked)) void* __attribute__((stdcall)) FUN_005e3c36(void*, const void*,
                                                                              uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e3c36\n\taddl $4,%esp\n\tretl $12");
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall)) FUN_005e3cf1(void*, const void*,
                                                                              uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e3cf1\n\taddl $4,%esp\n\tretl $12");
}
