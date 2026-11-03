#include "strftime.h"
#include "runtime/nls.h"
#include "runtime/heap.h"
struct OriginalTimeFormatSystemTime {
    uint16_t year, month, wday, mday, hour, min, sec, milliseconds;
};
using OriginalDateFormat = int32_t(__attribute__((stdcall)) *)(uint32_t, uint32_t,
                                                               const OriginalTimeFormatSystemTime*,
                                                               const char*, char*, int32_t);
extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall))
GetDateFormatA(uint32_t, uint32_t, const OriginalTimeFormatSystemTime*, const char*, char*,
               int32_t);
__declspec(dllimport) int32_t __attribute__((stdcall))
GetTimeFormatA(uint32_t, uint32_t, const OriginalTimeFormatSystemTime*, const char*, char*,
               int32_t);
}
namespace {
uint32_t word(const void* p) {
    uint32_t v;
    __asm__ __volatile__("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
uint8_t byte(const void* p) {
    uint32_t v;
    __asm__ __volatile__("movzbl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return uint8_t(v);
}
void store(void* p, uint32_t v) {
    __asm__ __volatile__("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void store8(void* p, uint8_t v) {
    __asm__ __volatile__("movb %1,(%0)" ::"r"(p), "q"(v) : "memory");
}
void emit(char** output, uint32_t* remaining, uint8_t value) {
    store8(reinterpret_cast<void*>(uintptr_t(word(output))), value);
    store(output, word(output) + 1);
    store(remaining, word(remaining) - 1);
}
bool lead(const OriginalLocaleStorage* locale, uint8_t v) {
    return (byte(reinterpret_cast<const uint8_t*>(locale->table_048) + uint32_t(v) * 2 + 1) &
            0x80) != 0;
}
bool copy_character(OriginalLocaleStorage* locale, const char*& input, char** output,
                    uint32_t* remaining) {
    const uint8_t value = byte(input);
    if (lead(locale, value) && *remaining > 1) {
        ++input;
        if (byte(input) == 0)
            return false;
        emit(output, remaining, value);
    }
    void* const target = reinterpret_cast<void*>(uintptr_t(word(output)));
    store8(target, byte(input));
    store(output, word(output) + 1);
    ++input;
    store(remaining, word(remaining) - 1);
    return true;
}
} // namespace
extern "C" int32_t fun_005cf2f8(OriginalLocaleStorage* locale, int32_t mode, const OriginalTm* time,
                                char** output, uint32_t* remaining,
                                OriginalLocaleCategory* category) {
    // Original caches these pointers in EBP-relative memory across its stack
    // allocation handler; preserve those exact memory-backed operands.
    const char* volatile saved_pattern = category->strings[mode == 0 ? 40 : mode == 1 ? 41 : 42];
    if (category->flag != 1) {
        OriginalDateFormat volatile api = mode == 2 ? GetTimeFormatA : GetDateFormatA;
        OriginalTimeFormatSystemTime fields;
        fields.year = uint16_t(uint16_t(time->year) + 1900);
        fields.month = uint16_t(uint16_t(time->mon) + 1);
        // Original does not initialize SYSTEMTIME.wDayOfWeek.
        fields.mday = uint16_t(time->mday);
        fields.hour = uint16_t(time->hour);
        fields.min = uint16_t(time->min);
        fields.sec = uint16_t(time->sec);
        fields.milliseconds = 0;
        const int32_t needed = api(category->language, 0, &fields, saved_pattern, nullptr, 0);
        if (needed != 0) {
            bool heap = false;
            char* temporary;
            __try {
                temporary = static_cast<char*>(__builtin_alloca((uint32_t(needed) + 3u) & ~3u));
            } __except (1) {
                fun_005cfb61();
                temporary = nullptr;
            }
            if (temporary == nullptr) {
                temporary = static_cast<char*>(fun_005cfade(uint32_t(needed)));
                heap = temporary != nullptr;
            }
            if (temporary != nullptr) {
                int32_t count =
                    api(category->language, 0, &fields, saved_pattern, temporary, needed);
                const char* cursor = temporary;
                for (count = int32_t(uint32_t(count) - 1); count > 0 && word(remaining) != 0;
                     --count) {
                    void* const target = reinterpret_cast<void*>(uintptr_t(word(output)));
                    store8(target, byte(cursor));
                    store(output, word(output) + 1);
                    ++cursor;
                    store(remaining, word(remaining) - 1);
                }
                if (heap)
                    fun_005cfaf0(temporary);
                return 1;
            }
        }
    }
    const char* pattern = saved_pattern;
    for (;;) {
        const uint8_t value = byte(pattern);
        if (value == 0 || *remaining == 0)
            return 1;
        const char* end = pattern;
        uint32_t repeat = 0;
        do {
            ++end;
            ++repeat;
        } while (byte(end) == value);
        uint8_t conversion = 0;
        int32_t alternate = 0;
        switch (int8_t(value)) {
        case 'd':
            if (repeat == 1) {
                alternate = 1;
                conversion = 'd';
            } else if (repeat == 2)
                conversion = 'd';
            else if (repeat == 3)
                conversion = 'a';
            else if (repeat == 4)
                conversion = 'A';
            break;
        case 'M':
            if (repeat == 1) {
                alternate = 1;
                conversion = 'm';
            } else if (repeat == 2)
                conversion = 'm';
            else if (repeat == 3)
                conversion = 'b';
            else if (repeat == 4)
                conversion = 'B';
            break;
        case 'H':
        case 'h':
        case 'm':
        case 's':
            if (repeat == 1)
                alternate = 1;
            if (repeat <= 2)
                conversion = value == 'h' ? 'I' : value == 'm' ? 'M' : value == 's' ? 'S' : 'H';
            break;
        case 'y':
            if (repeat == 2)
                conversion = 'y';
            else if (repeat == 4)
                conversion = 'Y';
            break;
        case 'A':
        case 'a':
            if (fun_005d9070(pattern, "am/pm") == 0)
                end = pattern + 5;
            else if (fun_005d9070(pattern, "a/p") == 0)
                end = pattern + 3;
            conversion = 'p';
            break;
        case '\'':
            pattern = end;
            if (repeat & 1) {
                for (;;) {
                    const uint8_t quoted = byte(pattern);
                    if (quoted == 0 || *remaining == 0)
                        break;
                    if (quoted == '\'') {
                        ++pattern;
                        break;
                    }
                    if (!copy_character(locale, pattern, output, remaining))
                        return 0;
                }
            }
            continue;
        case 't': {
            const char* marker = category->strings[time->hour <= 11 ? 38 : 39];
            if (repeat == 1 && *remaining != 0) {
                if (!copy_character(locale, marker, output, remaining))
                    return 0;
            } else {
                while (byte(marker) != 0 && *remaining != 0)
                    if (!copy_character(locale, marker, output, remaining))
                        return 0;
            }
            pattern = end;
            continue;
        }
        default:
            break;
        }
        if (conversion != 0) {
            if (!fun_005cf092(conversion, locale, time, category, alternate, output, remaining))
                return 0;
            pattern = end;
        } else if (!copy_character(locale, pattern, output, remaining))
            return 0;
    }
}
