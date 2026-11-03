#include "string_compare.h"
extern "C" int32_t fun_005cdf60(const char* left, const char* right, uint32_t count) {
    if (!count)
        return 0;
    const auto* first = reinterpret_cast<const volatile uint8_t*>(left);
    const auto* scan = first;
    uint32_t remaining = count;
    // Original REPNE SCASB scans the left string before touching the right.
    do {
        --remaining;
        if (*scan++ == 0)
            break;
    } while (remaining);
    uint32_t compare = count - remaining;
    const auto* second = reinterpret_cast<const volatile uint8_t*>(right);
    do {
        const uint8_t left_byte = *first++;
        const uint8_t right_byte = *second++;
        if (right_byte != left_byte)
            break;
    } while (--compare);
    // Original MOV/CMP explicitly reread the two last compared bytes.
    const uint8_t right_byte = second[-1];
    const uint8_t left_byte = first[-1];
    if (right_byte > left_byte)
        return -1;
    if (right_byte == left_byte)
        return 0;
    return 1;
}
extern "C" int32_t FUN_005cdf60(const char*, const char*, uint32_t)
    __attribute__((alias("fun_005cdf60")));
