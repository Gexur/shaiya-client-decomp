#include "floating_decimal.h"
#include "../core/extended96.h"
#include "strings.h"
#include "security.h"
namespace {
char* address(char* pointer, int32_t distance) {
    return reinterpret_cast<char*>(reinterpret_cast<uint32_t>(pointer) + uint32_t(distance));
}
int8_t raw_byte(const void* pointer) {
    int32_t value;
    __asm__ volatile("movsbl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return int8_t(value);
}
} // namespace
extern "C" uint32_t fun_005e0653(uint32_t low, uint32_t high, uint32_t exponent_word,
                                 int32_t digits, uint32_t flags, OriginalDecimalDigits* output) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    auto finish = [&](uint32_t result) {
        fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
        return result;
    };
    auto zero = [&]() {
        output->point = 0;
        output->sign = ' ';
        output->count = 1;
        output->digits[1] = 0;
        return finish(1);
    };
    const uint16_t exponent = uint16_t(exponent_word);
    const uint32_t magnitude = exponent & 0x7fffu;
    output->sign = exponent & 0x8000 ? '-' : ' ';
    if (!magnitude && !high && !low) {
        output->digits[0] = '0';
        return zero();
    }
    if (magnitude == 0x7fff) {
        output->point = 1;
        if ((high == 0x80000000u && !low) || (high & 0x40000000u)) {
            const char* special;
            if ((exponent & 0x8000) && high == 0xc0000000u && !low)
                special = "1#IND";
            else if (high == 0x80000000u && !low)
                special = "1#INF";
            else {
                fun_005d6350(output->digits, "1#QNAN");
                output->count = 6;
                return finish(0);
            }
            fun_005d6350(output->digits, special);
            output->count = 5;
        } else {
            fun_005d6350(output->digits, "1#SNAN");
            output->count = 6;
        }
        return finish(0);
    }
    const uint32_t approximate =
        ((magnitude >> 8) + (high >> 24) * 2u) * 0x4du + magnitude * 0x4d10u - 0x134312f4u;
    int32_t decimal = int16_t(int32_t(approximate) >> 16);
    OriginalExtended96 working = {
        {low << 16, (low >> 16) | (high << 16), (high >> 16) | (magnitude << 16)}};
    fun_005e0eda(&working, -decimal, 1);
    if ((working.words[2] >> 16) >= 0x3fff) {
        ++decimal;
        const OriginalExtended96 tenth = {{0xccccccccu, 0xccccccccu, 0x3ffbccccu}};
        fun_005e0ca4(&working, &tenth);
    }
    output->point = int16_t(decimal);
    if (flags & 1) {
        digits = int32_t(uint32_t(digits) + uint32_t(decimal));
        if (digits < 1) {
            output->digits[0] = '0';
            return zero();
        }
    }
    if (digits > 21)
        digits = 21;
    const int32_t shift = int32_t(working.words[2] >> 16) - 0x3ffe;
    working.words[2] &= 0xffffu;
    for (uint32_t count = 8; count; --count)
        fun_005e0510(&working);
    if (shift < 0)
        for (uint32_t count = (0u - uint32_t(shift)) & 255u; count; --count)
            fun_005e053e(&working);
    char* cursor = output->digits;
    int32_t remaining = int32_t(uint32_t(digits) + 1);
    if (remaining > 0)
        do {
            const OriginalExtended96 previous = working;
            fun_005e0510(&working);
            fun_005e0510(&working);
            fun_005e04b2(&working, &previous);
            fun_005e0510(&working);
            *cursor++ = static_cast<char>(uint8_t(working.words[2] >> 24) + 48u);
            working.words[2] &= 0x00ffffffu;
        } while (--remaining);
    cursor = address(cursor, -1);
    const int8_t rounding = raw_byte(cursor);
    cursor = address(cursor, -1);
    const uint32_t first = reinterpret_cast<uint32_t>(output->digits);
    if (rounding >= int8_t('5')) {
        while (reinterpret_cast<uint32_t>(cursor) >= first && *cursor == '9') {
            *cursor = '0';
            cursor = address(cursor, -1);
        }
        if (reinterpret_cast<uint32_t>(cursor) < first) {
            cursor = address(cursor, 1);
            output->point = int16_t(uint16_t(output->point) + 1u);
        }
        *cursor = static_cast<char>(uint8_t(*cursor) + 1u);
    } else {
        while (reinterpret_cast<uint32_t>(cursor) >= first && *cursor == '0')
            cursor = address(cursor, -1);
        if (reinterpret_cast<uint32_t>(cursor) < first) {
            output->digits[0] = '0';
            return zero();
        }
    }
    output->count =
        uint8_t(reinterpret_cast<uint32_t>(cursor) - reinterpret_cast<uint32_t>(output) - 3u);
    char* terminator = reinterpret_cast<char*>(reinterpret_cast<uint32_t>(output) + 4u +
                                               uint32_t(int32_t(int8_t(output->count))));
    *terminator = 0;
    return finish(1);
}
