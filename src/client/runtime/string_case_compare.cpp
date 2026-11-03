#include "string_case_compare.h"
#include "runtime/character_case.h"
#include "runtime/thread_data.h"
#include "runtime/nls.h"
#include "runtime/strftime.h"
namespace {
uint8_t byte(const char* p) {
    uint32_t v;
    __asm__ volatile("movzbl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return uint8_t(v);
}
} // namespace
// Complete original 0x005e0428..0x005e0491. Locale lookup/update precede
// either input read. Invariant locale uses the genuine ASCII comparator;
// other locales retain the genuine per-character mapping and full difference.
extern "C" int32_t fun_005e0428(const char* left, const char* right) {
    auto* data = static_cast<OriginalPerThreadData*>(fun_005d2659());
    auto* locale = static_cast<OriginalLocaleStorage*>(data->locale_64);
    if (locale != dat_0070e67c)
        locale = fun_005d505a();
    if (locale->undecoded_004[4] == 0)
        return fun_005d9070(left, right);
    uint32_t a, b;
    do {
        a = fun_005d08a1(locale, byte(left));
        ++left;
        b = fun_005d08a1(locale, byte(right));
        ++right;
    } while (a != 0 && a == b);
    return int32_t(a - b);
}
extern "C" int32_t _stricmp(const char*, const char*) __attribute__((alias("fun_005e0428")));
