#include "floating_decimal.h"
#include "floating_binary.h"
#include "floating_text.h"
#include "strings.h"
#include "security.h"
#include "../core/memory.h"
extern "C" char* fun_005dcd05(char* output, int32_t digits, OriginalDecimalFloat* value) {
    char* source = value->digits;
    char* cursor = output + 1;
    *output = '0';
    int32_t rounding = digits;
    if (digits > 0) {
        rounding = 0;
        do {
            const char digit = *source;
            if (digit)
                ++source;
            *cursor++ = digit ? digit : '0';
        } while (--digits);
    }
    *cursor = 0;
    if (rounding >= 0 && static_cast<int8_t>(*source) >= int8_t('5')) {
        while (*--cursor == '9')
            *cursor = '0';
        *cursor = static_cast<char>(uint8_t(*cursor) + 1);
    }
    if (*output == '1')
        value->point = int32_t(uint32_t(value->point) + 1);
    else
        fun_005cc630(output, output + 1, fun_005d4cf0(output + 1) + 1);
    return output;
}
extern "C" OriginalDecimalFloat* fun_005dce36(uint32_t low, uint32_t high,
                                              OriginalDecimalFloat* value, char* digits) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    const uint32_t binary[] = {low, high};
    uint32_t extended[3];
    OriginalDecimalDigits result;
    fun_005dcd7c(extended, binary);
    uint32_t exponent;
    // The original conversion writes only ten bytes; read the written WORD
    // without promoting the two untouched bytes of its stack allocation.
    __asm__ volatile("movzwl 8(%1),%0" : "=r"(exponent) : "r"(extended) : "memory");
    value->status = int32_t(fun_005e0653(extended[0], extended[1], exponent, 17, 0, &result));
    value->sign = result.sign;
    value->point = result.point;
    fun_005d6350(digits, result.digits);
    value->digits = digits;
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return value;
}
extern "C" char* fun_005d2bfb(char* buffer, int32_t distance) {
    if (!distance)
        return buffer;
    char* shifted =
        reinterpret_cast<char*>(reinterpret_cast<uint32_t>(buffer) + uint32_t(distance));
    return static_cast<char*>(fun_005cc630(shifted, buffer, fun_005d4cf0(buffer) + 1));
}
extern "C" char* fun_005d2c18(OriginalDecimalFloat* value, char* output, int32_t precision,
                              int32_t uppercase, uint32_t general) {
    general = uint8_t(general);
    if (general)
        fun_005d2bfb(output + uint32_t(value->sign == '-'), precision > 0 ? 1 : 0);
    char* cursor = output;
    if (value->sign == '-')
        *cursor++ = '-';
    if (precision > 0) {
        *cursor = cursor[1];
        *++cursor = dat_0070e4e4[0];
    }
    char* exponent = fun_005d6350(reinterpret_cast<char*>(reinterpret_cast<uint32_t>(cursor) +
                                                          uint32_t(precision) + uint32_t(!general)),
                                  "e+000");
    if (uppercase)
        *exponent = 'E';
    ++exponent;
    if (*value->digits != '0') {
        int32_t power = int32_t(uint32_t(value->point) - 1);
        if (power < 0) {
            power = int32_t(0u - uint32_t(power));
            *exponent = '-';
        }
        ++exponent;
        if (power >= 100) {
            const int32_t quotient = power / 100;
            power %= 100;
            *exponent = static_cast<char>(uint8_t(*exponent) + quotient);
        }
        ++exponent;
        if (power >= 10) {
            const int32_t quotient = power / 10;
            power %= 10;
            *exponent = static_cast<char>(uint8_t(*exponent) + quotient);
        }
        exponent[1] = static_cast<char>(uint8_t(exponent[1]) + power);
    }
    return output;
}
extern "C" char* fun_005d2d36(OriginalDecimalFloat* value, char* output, int32_t precision,
                              uint32_t general) {
    general = uint8_t(general);
    const uint32_t before = uint32_t(value->point) - 1;
    if (general && before == uint32_t(precision)) {
        char* end = reinterpret_cast<char*>(reinterpret_cast<uint32_t>(output) +
                                            uint32_t(value->sign == '-') + before);
        end[0] = '0';
        end[1] = 0;
    }
    char* cursor = output;
    if (value->sign == '-')
        *cursor++ = '-';
    if (value->point <= 0) {
        fun_005d2bfb(cursor, 1);
        *cursor++ = '0';
    } else
        cursor =
            reinterpret_cast<char*>(reinterpret_cast<uint32_t>(cursor) + uint32_t(value->point));
    if (precision > 0) {
        fun_005d2bfb(cursor, 1);
        *cursor++ = dat_0070e4e4[0];
        if (value->point < 0) {
            const uint32_t leading = 0u - uint32_t(value->point);
            if (general || precision >= int32_t(leading))
                precision = int32_t(leading);
            fun_005d2bfb(cursor, precision);
            fun_005dceb0(cursor, '0', uint32_t(precision));
        }
    }
    return output;
}
extern "C" char* fun_005d2cc6(const uint32_t* binary64, char* output, int32_t precision,
                              int32_t uppercase) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    OriginalDecimalFloat value;
    char digits[24];
    fun_005dce36(binary64[0], binary64[1], &value, digits);
    fun_005dcd05(output + uint32_t(value.sign == '-') + uint32_t(precision > 0),
                 int32_t(uint32_t(precision) + 1), &value);
    fun_005d2c18(&value, output, precision, uppercase, 0);
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return output;
}
extern "C" char* fun_005d2dd2(const uint32_t* binary64, char* output, int32_t precision) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    OriginalDecimalFloat value;
    char digits[24];
    fun_005dce36(binary64[0], binary64[1], &value, digits);
    fun_005dcd05(output + uint32_t(value.sign == '-'),
                 int32_t(uint32_t(value.point) + uint32_t(precision)), &value);
    fun_005d2d36(&value, output, precision, 0);
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return output;
}
extern "C" char* fun_005d2e39(const uint32_t* binary64, char* output, int32_t precision,
                              int32_t uppercase) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    OriginalDecimalFloat value;
    char digits[24];
    fun_005dce36(binary64[0], binary64[1], &value, digits);
    const int32_t old_point = int32_t(uint32_t(value.point) - 1);
    char* first = output + uint32_t(value.sign == '-');
    fun_005dcd05(first, precision, &value);
    const int32_t new_point = int32_t(uint32_t(value.point) - 1);
    if (new_point < -4 || precision <= new_point)
        fun_005d2c18(&value, output, precision, uppercase, 1);
    else {
        if (old_point < new_point) {
            char* end = first;
            while (*end++) {
            }
            end[-2] = 0;
        }
        fun_005d2d36(&value, output, precision, 1);
    }
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return output;
}
extern "C" char* fun_005d2ed8(const uint32_t* binary64, char* output, int32_t format,
                              int32_t precision, int32_t uppercase) {
    if (format == 'e' || format == 'E')
        return fun_005d2cc6(binary64, output, precision, uppercase);
    if (format == 'f')
        return fun_005d2dd2(binary64, output, precision);
    return fun_005d2e39(binary64, output, precision, uppercase);
}
