#include "runtime/nls.h"
#include "runtime/thread_data.h"
#include "runtime/security.h"

extern "C" __declspec(dllimport) int32_t __attribute__((stdcall)) GetLocaleInfoA(uint32_t, uint32_t,
                                                                                 char*, int32_t);

extern "C" uint32_t dat_0224f238 = 0;
extern "C" uint32_t dat_0224f0b0 = 0;
// Original LCID category storage is six contiguousDWORDs. The historical
// independentLC_CTYPE symbol now aliases its genuine thirdentry.
extern "C" uint32_t dat_0224f240[6] = {};
__asm__(".globl _dat_0224f248\n.set _dat_0224f248,_dat_0224f240+8\n");

extern "C" uint32_t fun_005d0beb(const OriginalLocaleStorage* locale, int32_t character,
                                 uint32_t mask) {
    uint16_t type;
    if (uint32_t(character) + 1u <= 0x100u) {
        type = locale->table_048[character];
    } else {
        // The original output pointer addresses the high WORD of character,
        // immediately followed by its mask argument. Two returned type WORDs
        // therefore overwrite the low mask WORD; retain that concrete layout.
        struct ArgumentWords {
            uint16_t low, high;
            uint32_t mask;
        };
        volatile ArgumentWords arguments = {uint16_t(character),
                                            uint16_t(uint32_t(character) >> 16), mask};
        char text[3];
        uint32_t count;
        const uint32_t high = (uint32_t(character) >> 8) & 255u;
        if (locale->table_048[high] & 0x8000u) {
            text[0] = char(high);
            text[1] = char(character);
            text[2] = 0;
            count = 2;
        } else {
            text[0] = char(character);
            text[1] = 0;
            count = 1;
        }
        // Original writes the returned WORD over the high half of its argument.
        if (!fun_005dc003(1, text, count, const_cast<uint16_t*>(&arguments.high),
                          locale->undecoded_004[0], locale->undecoded_004[4], 1))
            return 0;
        return arguments.high & arguments.mask;
    }
    return type & mask;
}

extern "C" int32_t fun_005cd2dd(const char* source) {
    auto* data = static_cast<OriginalPerThreadData*>(fun_005d2659());
    auto* locale = static_cast<OriginalLocaleStorage*>(data->locale_64);
    if (locale != dat_0070e67c)
        locale = fun_005d505a();
    uint32_t character;
    for (;;) {
        character = uint8_t(*source);
        const uint32_t space = int32_t(locale->invariant_028) <= 1
                                   ? locale->table_048[character] & 8u
                                   : fun_005d0beb(locale, character, 8);
        if (!space)
            break;
        ++source;
    }
    const uint32_t sign = character;
    ++source;
    if (sign == '-' || sign == '+')
        character = uint8_t(*source++);
    uint32_t result = 0;
    while (character >= '0' && character <= '9') {
        result = result * 10u + character - '0';
        character = uint8_t(*source++);
    }
    return int32_t(sign == '-' ? 0u - result : result);
}

extern "C" int32_t fun_005cd365(const char* source) {
    return fun_005cd2dd(source);
}
extern "C" int32_t FUN_005cd365(const char*) __attribute__((alias("fun_005cd365")));

extern "C" int32_t fun_005df112(uint32_t locale) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    char buffer[7];
    buffer[6] = 0;
    const int32_t result = GetLocaleInfoA(locale, 0x1004, buffer, 6) ? fun_005cd2dd(buffer) : -1;
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return result;
}
