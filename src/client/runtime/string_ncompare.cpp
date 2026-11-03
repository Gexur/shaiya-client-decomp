#include "string_ncompare.h"
#include "character_case.h"
#include "thread_data.h"
#include "nls.h"
namespace {
uint8_t read_byte(const char* pointer) {
    uint32_t value;
    __asm__ __volatile__("movzbl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return uint8_t(value);
}
uint8_t lower_ascii(uint8_t value) {
    return value > 0x40 && value < 0x5b ? uint8_t(value + 0x20) : value;
}
} // namespace
extern "C" int32_t fun_005e11e0(const char* left, const char* right, uint32_t count) {
    while (count != 0) {
        uint8_t a = read_byte(left), b = read_byte(right);
        // Both original byte loads precede either NUL test.
        if (a == 0 || b == 0)
            return a == b ? 0 : a < b ? -1 : 1;
        ++left;
        ++right;
        a = lower_ascii(a);
        b = lower_ascii(b);
        if (a != b)
            return a < b ? -1 : 1;
        --count;
    }
    return 0;
}
extern "C" int32_t fun_005e0a1f(const char* left, const char* right, uint32_t count) {
    auto* const data = static_cast<OriginalPerThreadData*>(fun_005d2659());
    auto* locale = static_cast<OriginalLocaleStorage*>(data->locale_64);
    if (locale != dat_0070e67c)
        locale = fun_005d505a();
    if (count == 0)
        return 0;
    if (locale->undecoded_004[4] == 0)
        return fun_005e11e0(left, right, count);
    uint32_t a, b;
    do {
        a = fun_005d08a1(locale, read_byte(left));
        ++left;
        b = fun_005d08a1(locale, read_byte(right));
        ++right;
        --count;
    } while (count != 0 && a != 0 && a == b);
    return int32_t(a - b);
}
extern "C" int32_t _strnicmp(const char*, const char*, uint32_t)
    __attribute__((alias("fun_005e0a1f")));
