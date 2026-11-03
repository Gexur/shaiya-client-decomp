#include "strings.h"

namespace {
uint32_t read_word(const char* pointer) {
    return *reinterpret_cast<const volatile uint32_t*>(pointer);
}
bool possible_zero(uint32_t value) {
    return (((value ^ 0xffffffffu) ^ (value + 0x7efefeffu)) & 0x81010100u) != 0;
}
void copy_tail(char* destination, const char* source) {
    while ((reinterpret_cast<uintptr_t>(source) & 3) != 0) {
        uint8_t value = static_cast<uint8_t>(*source++);
        if (value == 0) {
            *destination = 0;
            return;
        }
        *destination++ = static_cast<char>(value);
    }
    for (;;) {
        uint32_t value = read_word(source);
        bool candidate = possible_zero(value);
        value = read_word(source);
        source += 4;
        if (candidate) {
            if ((value & 0xffu) == 0) {
                *destination = static_cast<char>(value);
                return;
            }
            if ((value & 0xff00u) == 0) {
                *reinterpret_cast<uint16_t*>(destination) = static_cast<uint16_t>(value);
                return;
            }
            if ((value & 0xff0000u) == 0) {
                *reinterpret_cast<uint16_t*>(destination) = static_cast<uint16_t>(value);
                destination[2] = 0;
                return;
            }
            if ((value & 0xff000000u) == 0) {
                *reinterpret_cast<uint32_t*>(destination) = value;
                return;
            }
        }
        *reinterpret_cast<uint32_t*>(destination) = value;
        destination += 4;
    }
}
} // namespace

extern "C" uint32_t fun_005d4cf0(const char* string) {
    const char* cursor = string;
    while ((reinterpret_cast<uintptr_t>(cursor) & 3) != 0) {
        if (*cursor++ == 0)
            return static_cast<uint32_t>(cursor - string - 1);
    }
    for (;;) {
        uint32_t value = read_word(cursor);
        cursor += 4;
        if (!possible_zero(value))
            continue;
        value = read_word(cursor - 4);
        if ((value & 0xffu) == 0)
            return static_cast<uint32_t>(cursor - string - 4);
        if ((value & 0xff00u) == 0)
            return static_cast<uint32_t>(cursor - string - 3);
        if ((value & 0xff0000u) == 0)
            return static_cast<uint32_t>(cursor - string - 2);
        if ((value & 0xff000000u) == 0)
            return static_cast<uint32_t>(cursor - string - 1);
    }
}
extern "C" char* fun_005d6350(char* destination, const char* source) {
    copy_tail(destination, source);
    return destination;
}
extern "C" char* fun_005d6360(char* destination, const char* source) {
    copy_tail(destination + fun_005d4cf0(destination), source);
    return destination;
}
