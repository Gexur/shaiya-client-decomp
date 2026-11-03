#include "wide_output.h"
#include "thread_data.h"
#include "nls.h"
#include "locks.h"
extern "C" __declspec(dllimport) int32_t __attribute__((stdcall))
WideCharToMultiByte(uint32_t, uint32_t, const uint16_t*, int32_t, char*, int32_t, const char*,
                    int32_t*);
extern "C" int32_t fun_005dd0ef(OriginalLocaleStorage* locale, char* output, uint32_t character) {
    if (!output)
        return 0;
    if (!locale->undecoded_004[4]) {
        if (uint16_t(character) <= 255) {
            *output = static_cast<char>(character);
            return 1;
        }
    } else {
        int32_t used_default = 0;
        const int32_t result = WideCharToMultiByte(
            locale->undecoded_004[0], 0, reinterpret_cast<const uint16_t*>(&character), 1, output,
            int32_t(locale->invariant_028), nullptr, &used_default);
        if (result && !used_default)
            return result;
    }
    *fun_005d589a() = 42;
    return -1;
}
extern "C" int32_t fun_005dd14f(char* output, uint32_t character) {
    auto* data = static_cast<OriginalPerThreadData*>(fun_005d2659());
    auto* locale = static_cast<OriginalLocaleStorage*>(data->locale_64);
    if (locale != dat_0070e67c)
        locale = static_cast<OriginalLocaleStorage*>(fun_005d505a());
    return fun_005dd0ef(locale, output, character);
}
