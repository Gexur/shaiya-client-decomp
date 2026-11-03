#include "extended96_mantissa.h"
namespace {
uint16_t load16(const void* p) {
    uint32_t x;
    __asm__ volatile("movzwl (%1),%0" : "=r"(x) : "r"(p) : "memory");
    return uint16_t(x);
}
uint32_t load32(const void* p) {
    uint32_t x;
    __asm__ volatile("movl (%1),%0" : "=r"(x) : "r"(p) : "memory");
    return x;
}
void store32(void* p, uint32_t x) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(x) : "memory");
}
void* word(void* p, int32_t index) {
    return reinterpret_cast<void*>(reinterpret_cast<uint32_t>(p) + uint32_t(index) * 4);
}
const void* word(const void* p, int32_t index) {
    return reinterpret_cast<const void*>(reinterpret_cast<uint32_t>(p) + uint32_t(index) * 4);
}
uint32_t field(const OriginalExtended96Format* p, uint32_t index) {
    return load32(word(p, int32_t(index)));
}
} // namespace
extern "C" int32_t fun_005dc957(const void* mantissa, int32_t bit) {
    int32_t index = bit / 32;
    const uint32_t mask = ~(0xffffffffu << ((31 - (bit % 32)) & 31));
    if ((load32(word(mantissa, index)) & mask) != 0)
        return 0;
    while (++index < 3)
        if (load32(word(mantissa, index)) != 0)
            return 0;
    return 1;
}
extern "C" int32_t fun_005dc989(void* mantissa, int32_t bit) {
    int32_t index = bit / 32;
    int32_t carry = fun_005e0491(load32(word(mantissa, index)), 1u << ((31 - (bit % 32)) & 31),
                                 static_cast<uint32_t*>(word(mantissa, index)));
    while (--index >= 0) {
        if (carry == 0)
            break;
        carry = fun_005e0491(load32(word(mantissa, index)), 1,
                             static_cast<uint32_t*>(word(mantissa, index)));
    }
    return carry;
}
extern "C" int32_t fun_005dc9d6(void* mantissa, int32_t bit) {
    int32_t carry = 0;
    int32_t index = bit / 32;
    const uint32_t shift = (31 - (bit % 32)) & 31;
    if ((load32(word(mantissa, index)) & (1u << shift)) != 0 && fun_005dc957(mantissa, bit) == 0)
        carry = fun_005dc989(mantissa, bit - 1);
    store32(word(mantissa, index), load32(word(mantissa, index)) & (0xffffffffu << shift));
    while (++index < 3)
        store32(word(mantissa, index), 0);
    return carry;
}
extern "C" void fun_005dca48(void* destination, const void* source) {
    for (int32_t index = 0; index < 3; ++index)
        store32(word(destination, index), load32(word(source, index)));
}
extern "C" int32_t fun_005dca63(const void* mantissa) {
    for (int32_t index = 0; index < 3; ++index)
        if (load32(word(mantissa, index)) != 0)
            return 0;
    return 1;
}
extern "C" void fun_005dca7c(void* mantissa, int32_t shift) {
    const int32_t whole = shift / 32, remainder = shift % 32;
    const uint32_t mask = ~(0xffffffffu << (remainder & 31));
    uint32_t carry = 0;
    for (int32_t index = 0; index < 3; ++index) {
        const uint32_t current = load32(word(mantissa, index));
        store32(word(mantissa, index), (current >> (remainder & 31)) | carry);
        carry = (current & mask) << ((32 - remainder) & 31);
    }
    for (int32_t index = 2; index >= 0; --index)
        store32(word(mantissa, index), index < whole ? 0 : load32(word(mantissa, index - whole)));
}
extern "C" int32_t fun_005dcaf7(const OriginalExtended96* source, void* destination,
                                const OriginalExtended96Format* format) {
    const auto* bytes = reinterpret_cast<const uint8_t*>(source);
    const uint16_t tag = load16(bytes + 10);
    uint32_t mantissa[3] = {load32(bytes + 6), load32(bytes + 2), uint32_t(load16(bytes)) << 16};
    int32_t exponent = int32_t(tag & 0x7fff) - 0x3fff;
    int32_t result = 0;
    uint32_t binary_exponent = 0;
    if (exponent == -0x3fff) {
        if (fun_005dca63(mantissa) == 0) {
            mantissa[0] = 0;
            mantissa[1] = 0;
            mantissa[2] = 0;
            result = 2;
        }
    } else {
        uint32_t backup[3];
        fun_005dca48(backup, mantissa);
        if (fun_005dc9d6(mantissa, int32_t(field(format, 2))) != 0)
            ++exponent;
        const int32_t minimum = int32_t(field(format, 1));
        if (exponent < int32_t(uint32_t(minimum) - field(format, 2))) {
            mantissa[0] = 0;
            mantissa[1] = 0;
            mantissa[2] = 0;
            result = 2;
        } else if (exponent <= minimum) {
            fun_005dca48(mantissa, backup);
            fun_005dca7c(mantissa, int32_t(uint32_t(minimum) - uint32_t(exponent)));
            (void)fun_005dc9d6(mantissa, int32_t(field(format, 2)));
            fun_005dca7c(mantissa, int32_t(field(format, 3) + 1));
            result = 2;
        } else if (exponent >= int32_t(field(format, 0))) {
            mantissa[0] = 0x80000000u;
            mantissa[1] = 0;
            mantissa[2] = 0;
            fun_005dca7c(mantissa, int32_t(field(format, 3)));
            binary_exponent = field(format, 5) + field(format, 0);
            result = 1;
        } else {
            mantissa[0] &= 0x7fffffffu;
            binary_exponent = field(format, 5) + uint32_t(exponent);
            fun_005dca7c(mantissa, int32_t(field(format, 3)));
        }
    }
    const uint32_t high = (binary_exponent << ((31 - field(format, 3)) & 31)) |
                          ((tag & 0x8000) ? 0x80000000u : 0) | mantissa[0];
    const uint32_t width = field(format, 4);
    if (width == 64) {
        auto* output = reinterpret_cast<uint8_t*>(destination);
        store32(output + 4, high);
        store32(output, mantissa[1]);
    } else if (width == 32)
        store32(destination, high);
    return result;
}
