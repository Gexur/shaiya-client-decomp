#include "cxx_exception.h"

extern "C" int32_t fun_005d65d0(const char* left_chars, const char* right_chars) {
    const uint8_t* left = reinterpret_cast<const uint8_t*>(left_chars);
    const uint8_t* right = reinterpret_cast<const uint8_t*>(right_chars);
    if ((reinterpret_cast<uint32_t>(left) & 3) != 0) {
        if ((reinterpret_cast<uint32_t>(left) & 1) != 0) {
            const uint8_t a = *left++;
            const uint8_t b = *right;
            if (a != b)
                return a < b ? -1 : 1;
            ++right;
            if (a == 0)
                return 0;
            if ((reinterpret_cast<uint32_t>(left) & 2) == 0)
                goto aligned;
        }
        // Volatile records an actual original full-width load before either
        // character check; this qualifier is not inferred original C typing.
        const uint16_t value = *reinterpret_cast<const volatile uint16_t*>(left);
        left += 2;
        uint8_t a = uint8_t(value), b = right[0];
        if (a != b)
            return a < b ? -1 : 1;
        if (a == 0)
            return 0;
        a = uint8_t(value >> 8);
        b = right[1];
        if (a != b)
            return a < b ? -1 : 1;
        if (a == 0)
            return 0;
        right += 2;
    }
aligned:
    for (;;) {
        const uint32_t value = *reinterpret_cast<const volatile uint32_t*>(left);
        for (uint32_t index = 0; index != 4; ++index) {
            const uint8_t a = uint8_t(value >> (index * 8));
            const uint8_t b = right[index];
            if (a != b)
                return a < b ? -1 : 1;
            if (a == 0)
                return 0;
        }
        left += 4;
        right += 4;
    }
}
