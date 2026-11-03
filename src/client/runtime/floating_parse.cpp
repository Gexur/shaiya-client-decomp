#include "floating_parse.h"
#include "character_case.h"
#include "floating_text.h"

namespace {
void put16(void* p, uint32_t value) {
    __asm__ __volatile__("movw %w1,(%0)" ::"r"(p), "r"(value) : "memory");
}
void put32(void* p, uint32_t value) {
    __asm__ __volatile__("movl %1,(%0)" ::"r"(p), "r"(value) : "memory");
}
uint32_t get32(const void* p) {
    uint32_t v;
    __asm__ __volatile__("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
bool nonzero_digit(uint8_t c) {
    return int8_t(c) >= '1' && int8_t(c) <= '9';
}
bool digit(uint8_t c) {
    return fun_005d9235(c) != 0;
}
} // namespace

extern "C" void fun_005e056b(const int8_t* digits, uint32_t count, OriginalExtended96* output) {
    uint16_t exponent = 0x404e;
    output->words[0] = 0;
    output->words[1] = 0;
    output->words[2] = 0;
    if (count)
        do {
            OriginalExtended96 saved = *output;
            fun_005e0510(output);
            fun_005e0510(output);
            fun_005e04b2(output, &saved);
            fun_005e0510(output);
            saved.words[0] = uint32_t(int32_t(*digits));
            saved.words[1] = 0;
            saved.words[2] = 0;
            fun_005e04b2(output, &saved);
            ++digits;
        } while (--count);
    if (!output->words[2]) {
        uint32_t high;
        do {
            exponent = uint16_t(exponent - 16);
            high = output->words[1] >> 16;
            output->words[1] = (output->words[0] >> 16) | (output->words[1] << 16);
            output->words[0] <<= 16;
        } while (!high);
        output->words[2] = high;
    }
    while (!(output->words[2] & 0x8000)) {
        fun_005e0510(output);
        --exponent;
    }
    put16(reinterpret_cast<uint8_t*>(output) + 10, exponent);
}

extern "C" uint32_t fun_005decd2(OriginalExtended96* output, const char** end, const char* input,
                                 int32_t keep_guard, int32_t default_power,
                                 int32_t implicit_fraction, int32_t bare_exponent) {
    int32_t state = 0, exponent_sign = 1;
    uint32_t count = 0, status = 0, decimal_shift = 0, exponent = 0;
    uint16_t sign = 0;
    bool seen = false, decimal_seen = false, explicit_exponent = false;
    int8_t digits[25];
    int8_t* cursor = digits;
    const char* fallback = input;
    const char* current = input;
    while (*current == ' ' || *current == '\t' || *current == '\n' || *current == '\r')
        ++current;
    for (;;) {
        const uint8_t c = uint8_t(*current++);
        switch (state) {
        case 0:
            if (nonzero_digit(c)) {
                state = 3;
                --current;
                continue;
            }
            if (c == uint8_t(dat_0070e4e4[0])) {
                state = 5;
                continue;
            }
            state = 2;
            if (c == '+') {
                sign = 0;
                continue;
            }
            if (c == '-') {
                sign = 0x8000;
                continue;
            }
            if (c == '0') {
                state = 1;
                continue;
            }
            --current;
            goto finish;
        case 1:
            seen = true;
            if (nonzero_digit(c)) {
                state = 3;
                --current;
                continue;
            }
            if (c == uint8_t(dat_0070e4e4[0])) {
                state = 4;
                continue;
            }
            if (c == '+' || c == '-') {
                state = 11;
                --current;
                continue;
            }
            if (c == '0')
                continue;
            if ((int8_t(c) >= 'D' && int8_t(c) <= 'E') || (int8_t(c) >= 'd' && int8_t(c) <= 'e')) {
                state = 6;
                continue;
            }
            --current;
            goto finish;
        case 2:
            if (nonzero_digit(c)) {
                state = 3;
                --current;
                continue;
            }
            if (c == uint8_t(dat_0070e4e4[0])) {
                state = 5;
                continue;
            }
            if (c == '0') {
                state = 1;
                continue;
            }
            current = fallback;
            goto finish;
        case 3: {
            seen = true;
            uint8_t value = c;
            while (digit(value)) {
                if (count < 25) {
                    ++count;
                    *cursor++ = int8_t(value - '0');
                } else
                    ++decimal_shift;
                value = uint8_t(*current++);
            }
            if (value == uint8_t(dat_0070e4e4[0])) {
                state = 4;
                continue;
            }
            if (value == '+' || value == '-') {
                state = 11;
                --current;
                continue;
            }
            if ((int8_t(value) >= 'D' && int8_t(value) <= 'E') ||
                (int8_t(value) >= 'd' && int8_t(value) <= 'e')) {
                state = 6;
                continue;
            }
            --current;
            goto finish;
        }
        case 4: {
            seen = true;
            decimal_seen = true;
            uint8_t value = c;
            if (!count)
                while (value == '0') {
                    --decimal_shift;
                    value = uint8_t(*current++);
                }
            while (digit(value)) {
                if (count < 25) {
                    ++count;
                    *cursor++ = int8_t(value - '0');
                    --decimal_shift;
                }
                value = uint8_t(*current++);
            }
            if (value == '+' || value == '-') {
                state = 11;
                --current;
                continue;
            }
            if ((int8_t(value) >= 'D' && int8_t(value) <= 'E') ||
                (int8_t(value) >= 'd' && int8_t(value) <= 'e')) {
                state = 6;
                continue;
            }
            --current;
            goto finish;
        }
        case 5:
            decimal_seen = true;
            if (digit(c)) {
                state = 4;
                --current;
                continue;
            }
            current = fallback;
            goto finish;
        case 6:
            fallback = current - 2;
            if (nonzero_digit(c)) {
                state = 9;
                --current;
                continue;
            }
            if (c == '+') {
                state = 7;
                continue;
            }
            if (c == '-') {
                exponent_sign = -1;
                state = 7;
                continue;
            }
            if (c == '0') {
                state = 8;
                continue;
            }
            current = fallback;
            goto finish;
        case 7:
            if (nonzero_digit(c)) {
                state = 9;
                --current;
                continue;
            }
            if (c == '0') {
                state = 8;
                continue;
            }
            current = fallback;
            goto finish;
        case 8: {
            explicit_exponent = true;
            uint8_t value = c;
            while (value == '0')
                value = uint8_t(*current++);
            if (nonzero_digit(value)) {
                state = 9;
                --current;
                continue;
            }
            --current;
            goto finish;
        }
        case 9: {
            explicit_exponent = true;
            exponent = 0;
            uint8_t value = c;
            while (digit(value)) {
                exponent = exponent * 10 + uint32_t(int32_t(int8_t(value)) - '0');
                if (int32_t(exponent) > 5200) {
                    exponent = 5201;
                    break;
                }
                value = uint8_t(*current++);
            }
            while (digit(value))
                value = uint8_t(*current++);
            --current;
            goto finish;
        }
        case 11:
            if (bare_exponent) {
                fallback = current - 1;
                if (c == '+') {
                    state = 7;
                    continue;
                }
                if (c == '-') {
                    exponent_sign = -1;
                    state = 7;
                    continue;
                }
                current = fallback;
                goto finish;
            }
            --current;
            goto finish;
        default:
            if (state == 10)
                goto finish;
        }
    }
finish:
    *end = current;
    OriginalExtended96 value;
    if (!seen)
        status = 4;
    else {
        if (count > 24) {
            // Original5def46 tests/increments the24th stored byte, not the25th.
            if (digits[23] >= 5)
                ++digits[23];
            --cursor;
            ++decimal_shift;
            count = 24;
        }
        if (count) {
            while (*--cursor == 0) {
                --count;
                ++decimal_shift;
            }
            fun_005e056b(digits, count, &value);
            if (exponent_sign < 0)
                exponent = 0 - exponent;
            exponent += decimal_shift;
            if (!explicit_exponent)
                exponent += uint32_t(default_power);
            if (!decimal_seen)
                exponent -= uint32_t(implicit_fraction);
            if (int32_t(exponent) > 5200) {
                value.words[0] = 0;
                value.words[1] = 0;
                value.words[2] = 0x7fff8000;
                status = 2;
                goto store;
            }
            if (int32_t(exponent) >= -5200) {
                fun_005e0eda(&value, int32_t(exponent), keep_guard);
                goto store;
            }
            status = 1;
        }
    }
    value.words[0] = 0;
    value.words[1] = 0;
    value.words[2] = 0;
store:
    auto* bytes = reinterpret_cast<uint8_t*>(output);
    const uint32_t middle = get32(reinterpret_cast<const uint8_t*>(&value) + 2);
    const uint32_t high = get32(reinterpret_cast<const uint8_t*>(&value) + 6);
    const uint16_t top = uint16_t(value.words[2] >> 16) | sign;
    put16(bytes, value.words[0]);
    put32(bytes + 2, middle);
    put16(bytes + 10, top);
    put32(bytes + 6, high);
    return status;
}
