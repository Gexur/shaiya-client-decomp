#include "nls.h"
#include "thread_data.h"
#include "locks.h"

// These increments deliberately follow the observed order, including aliases.
static void change_references(OriginalLocaleStorage* locale, uint32_t change) {
    locale->references = int32_t(uint32_t(locale->references) + change);
    if (locale->reference_02c)
        *locale->reference_02c = int32_t(uint32_t(*locale->reference_02c) + change);
    if (locale->reference_034)
        *locale->reference_034 = int32_t(uint32_t(*locale->reference_034) + change);
    if (locale->reference_030)
        *locale->reference_030 = int32_t(uint32_t(*locale->reference_030) + change);
    if (locale->reference_040)
        *locale->reference_040 = int32_t(uint32_t(*locale->reference_040) + change);
    locale->category_04c->references = int32_t(uint32_t(locale->category_04c->references) + change);
}

extern "C" OriginalLocaleStorage* fun_005d4e4b() {
    auto* data = static_cast<OriginalPerThreadData*>(fun_005d2659());
    auto* old = static_cast<OriginalLocaleStorage*>(data->locale_64);
    if (old != dat_0070e67c) {
        if (old)
            change_references(old, 0xffffffffu);
        auto* current = static_cast<OriginalLocaleStorage*>(dat_0070e67c);
        data->locale_64 = current;
        change_references(current, 1);
        if (old && !old->references && old != &dat_0070e628)
            fun_005d4d7b(old);
    }
    return static_cast<OriginalLocaleStorage*>(data->locale_64);
}

extern "C" void fun_005d508c() {
    fun_005d64e6(12);
}

extern "C" OriginalLocaleStorage* fun_005d505a() {
    fun_005d659b(12);
    OriginalLocaleStorage* result;
    __try {
        result = fun_005d4e4b();
    } __finally {
        fun_005d508c();
    }
    return result;
}
