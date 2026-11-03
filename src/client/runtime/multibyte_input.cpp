#include "multibyte_input.h"
#include "thread_data.h"
#include "nls.h"
#include "locks.h"
extern "C" __declspec(dllimport) int32_t __attribute__((stdcall))
MultiByteToWideChar(uint32_t, uint32_t, const char*, int32_t, uint16_t*, int32_t);
extern "C" int32_t fun_005dd1e2(OriginalLocaleStorage* locale, uint16_t* output, const char* input,
                                uint32_t size) {
    if (!input || !size)
        return 0;
    const uint8_t first = uint8_t(*input);
    if (!first) {
        if (output)
            *output = 0;
        return 0;
    }
    if (!locale->undecoded_004[4]) {
        if (output)
            *output = first;
        return 1;
    }
    if (!(locale->table_048[first] & 0x8000)) {
        if (MultiByteToWideChar(locale->undecoded_004[0], 9, input, 1, output, output ? 1 : 0))
            return 1;
    } else {
        const uint32_t maximum = locale->invariant_028;
        if ((int32_t(maximum) > 1 && int32_t(size) >= int32_t(maximum) &&
             MultiByteToWideChar(locale->undecoded_004[0], 9, input, int32_t(maximum), output,
                                 output ? 1 : 0)) ||
            (size >= maximum && input[1] != 0))
            return int32_t(maximum);
    }
    *fun_005d589a() = 42;
    return -1;
}
extern "C" int32_t fun_005dd2a2(uint16_t* output, const char* input, uint32_t size) {
    auto* data = static_cast<OriginalPerThreadData*>(fun_005d2659());
    auto* locale = static_cast<OriginalLocaleStorage*>(data->locale_64);
    if (locale != dat_0070e67c)
        locale = fun_005d505a();
    return fun_005dd1e2(locale, output, input, size);
}
