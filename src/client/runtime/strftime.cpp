#include "strftime.h"
#include "runtime/nls.h"
#include "runtime/thread_data.h"
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
char* pointer(char** p) {
    return reinterpret_cast<char*>(uintptr_t(word(p)));
}
void emit(char** output, uint32_t* remaining, uint8_t v) {
    store8(pointer(output), v);
    store(output, word(output) + 1);
    store(remaining, word(remaining) - 1);
}
bool lead(const OriginalLocaleStorage* locale, uint8_t v) {
    return (byte(reinterpret_cast<const uint8_t*>(locale->table_048) + uint32_t(v) * 2 + 1) &
            0x80) != 0;
}
int32_t add(int32_t a, int32_t b) {
    return int32_t(uint32_t(a) + uint32_t(b));
}
} // namespace
extern "C" int32_t fun_005d9070(const char* left, const char* right) {
    uint8_t previous = 0xff;
    while (previous != 0) {
        const uint8_t b = byte(right++);
        const uint8_t a = byte(left++);
        previous = b;
        if (a == b)
            continue;
        const uint8_t folded_b = uint8_t(b - 'A') < 26 ? uint8_t(b + 32) : b;
        const uint8_t folded_a = uint8_t(a - 'A') < 26 ? uint8_t(a + 32) : a;
        previous = folded_a;
        if (folded_a != folded_b)
            return folded_a < folded_b ? -1 : 1;
    }
    return 0;
}
extern "C" void fun_005ceff9(char** output, uint32_t* remaining, const char* source) {
    while (word(remaining) != 0) {
        const uint8_t value = byte(source);
        if (value == 0)
            return;
        emit(output, remaining, value);
        ++source;
    }
}
extern "C" void fun_005cf019(char** output, uint32_t* remaining, int32_t value, uint32_t width,
                             int32_t alternate) {
    if (alternate != 0) {
        char* next = pointer(output);
        while (word(remaining) > 1) {
            const int32_t remainder = value % 10;
            value /= 10;
            store8(next++, uint8_t(remainder + 48));
            store(remaining, word(remaining) - 1);
            if (value <= 0)
                break;
        }
        char* left = pointer(output);
        store(output, uint32_t(uintptr_t(next)));
        char* right = next - 1;
        // The original swaps once even when the digit loop wrote no byte.
        do {
            const uint8_t a = byte(left), b = byte(right);
            store8(right, a);
            --right;
            store8(left, b);
            ++left;
        } while (uintptr_t(left) < uintptr_t(right));
    } else {
        if (width >= word(remaining)) {
            store(remaining, 0);
            return;
        }
        uint32_t written = 0;
        for (uint32_t index = width; index != 0;) {
            --index;
            const int32_t remainder = value % 10;
            value /= 10;
            store8(reinterpret_cast<char*>(uintptr_t(word(output) + index)),
                   uint8_t(remainder + 48));
            ++written;
        }
        store(output, word(output) + written);
        store(remaining, word(remaining) - written);
    }
}
extern "C" int32_t fun_005cf092(uint8_t code, OriginalLocaleStorage* locale, const OriginalTm* time,
                                OriginalLocaleCategory* category, int32_t alternate, char** output,
                                uint32_t* remaining) {
    const char* text = nullptr;
    bool string_value = false;
    int32_t number = 0;
    uint32_t width = 2;
    switch (int8_t(code)) {
    case '%':
        emit(output, remaining, '%');
        return 1;
    case 'A':
        text = category->strings[int32_t(word(&time->wday)) + 7];
        string_value = true;
        break;
    case 'B':
        text = category->strings[int32_t(word(&time->mon)) + 26];
        string_value = true;
        break;
    case 'a':
        text = category->strings[int32_t(word(&time->wday))];
        string_value = true;
        break;
    case 'b':
        text = category->strings[int32_t(word(&time->mon)) + 14];
        string_value = true;
        break;
    case 'p':
        text = category->strings[int32_t(word(&time->hour)) <= 11 ? 38 : 39];
        string_value = true;
        break;
    case 'Z':
    case 'z':
        fun_005d7add();
        text = dat_0070eb70[word(&time->isdst) != 0];
        string_value = true;
        break;
    case 'H':
        number = int32_t(word(&time->hour));
        break;
    case 'I':
        number = int32_t(word(&time->hour)) % 12;
        if (number == 0)
            number = 12;
        break;
    case 'M':
        number = int32_t(word(&time->min));
        break;
    case 'S':
        number = int32_t(word(&time->sec));
        break;
    case 'U':
    case 'W': {
        int32_t start = int32_t(word(&time->wday));
        if (code == 'W')
            start = start == 0 ? 6 : add(start, -1);
        const int32_t day = int32_t(word(&time->yday));
        if (day < start)
            number = 0;
        else {
            number = day / 7;
            if (day % 7 >= start)
                number = add(number, 1);
        }
        break;
    }
    case 'Y':
        number = add(int32_t(word(&time->year)), 1900);
        width = 4;
        break;
    case 'y':
        number = int32_t(word(&time->year)) % 100;
        break;
    case 'm':
        number = add(int32_t(word(&time->mon)), 1);
        break;
    case 'w':
        number = int32_t(word(&time->wday));
        width = 1;
        break;
    case 'd':
        number = int32_t(word(&time->mday));
        break;
    case 'j':
        number = add(int32_t(word(&time->yday)), 1);
        width = 3;
        break;
    case 'x':
        return fun_005cf2f8(locale, alternate != 0 ? 1 : 0, time, output, remaining, category) != 0;
    case 'c':
        if (!fun_005cf2f8(locale, alternate != 0 ? 1 : 0, time, output, remaining, category) ||
            word(remaining) == 0)
            return 0;
        emit(output, remaining, ' ');
        [[fallthrough]];
    case 'X':
        return fun_005cf2f8(locale, 2, time, output, remaining, category) != 0;
    default:
        return 1;
    }
    if (string_value)
        fun_005ceff9(output, remaining, text);
    else
        fun_005cf019(output, remaining, number, width, alternate);
    return 1;
}
extern "C" uint32_t fun_005cf782(OriginalLocaleStorage* locale, char* output, uint32_t capacity,
                                 const char* format, const OriginalTm* time,
                                 OriginalLocaleCategory* category) {
    if (category == nullptr)
        category = locale->category_04c;
    if (capacity == 0)
        return 0;
    char* cursor = output;
    uint32_t remaining = capacity;
    while (remaining != 0) {
        const uint8_t value = byte(format);
        if (value == 0)
            break;
        if (value == '%') {
            ++format;
            int32_t alternate = 0;
            if (byte(format) == '#') {
                alternate = 1;
                ++format;
            }
            if (!fun_005cf092(byte(format), locale, time, category, alternate, &cursor,
                              &remaining)) {
                *output = 0;
                return 0;
            }
            ++format;
        } else {
            if (lead(locale, value) && remaining > 1) {
                ++format;
                if (byte(format) == 0) {
                    *output = 0;
                    return 0;
                }
                *cursor++ = char(value);
                --remaining;
            }
            *cursor++ = char(byte(format++));
            --remaining;
        }
    }
    if (remaining == 0) {
        *output = 0;
        return 0;
    }
    *cursor = 0;
    return capacity - remaining;
}
extern "C" uint32_t fun_005cf845(char* output, uint32_t capacity, const char* format,
                                 const OriginalTm* time, OriginalLocaleCategory* category) {
    auto* locale = static_cast<OriginalLocaleStorage*>(
        static_cast<OriginalPerThreadData*>(fun_005d2659())->locale_64);
    if (locale != dat_0070e67c)
        locale = fun_005d505a();
    return fun_005cf782(locale, output, capacity, format, time, category);
}
extern "C" uint32_t fun_005cf877(char* output, uint32_t capacity, const char* format,
                                 const OriginalTm* time) {
    return fun_005cf845(output, capacity, format, time, nullptr);
}
