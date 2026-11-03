#pragma once
#include <stdint.h>
struct OriginalDecimalFloat {
    int32_t sign;
    int32_t point;
    int32_t status;
    char* digits;
};
struct OriginalDecimalDigits {
    int16_t point;
    int8_t sign;
    uint8_t count;
    char digits[24];
};
static_assert(sizeof(OriginalDecimalFloat) == 16);
static_assert(sizeof(OriginalDecimalDigits) == 28);
extern "C" {
char* fun_005dcd05(char* output, int32_t digits, OriginalDecimalFloat* value);
OriginalDecimalFloat* fun_005dce36(uint32_t low, uint32_t high, OriginalDecimalFloat* value,
                                   char* digits);
uint32_t fun_005e0653(uint32_t low, uint32_t high, uint32_t exponent, int32_t digits,
                      uint32_t flags, OriginalDecimalDigits* output);
// The original shift uses EAX=buffer and EDI=distance.
char* fun_005d2bfb(char* buffer, int32_t distance);
// Original EAX=value,EBX=output,three stack precision/uppercase/mode operands.
char* fun_005d2c18(OriginalDecimalFloat* value, char* output, int32_t precision, int32_t uppercase,
                   uint32_t general);
// Original EAX=value plus stack output,precision,mode operands.
char* fun_005d2d36(OriginalDecimalFloat* value, char* output, int32_t precision, uint32_t general);
char* fun_005d2cc6(const uint32_t* binary64, char* output, int32_t precision, int32_t uppercase);
char* fun_005d2dd2(const uint32_t* binary64, char* output, int32_t precision);
char* fun_005d2e39(const uint32_t* binary64, char* output, int32_t precision, int32_t uppercase);
char* fun_005d2ed8(const uint32_t* binary64, char* output, int32_t format, int32_t precision,
                   int32_t uppercase);
}
