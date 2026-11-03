#include "runtime_error.h"
namespace {
uint32_t load_word(const char* p) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
void store_word(char* p, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(value) : "memory");
}
void pad(char* destination, uint32_t count) {
    while (count && (reinterpret_cast<uint32_t>(destination) & 3)) {
        *(volatile char*)destination++ = 0;
        --count;
    }
    while (count >= 4) {
        store_word(destination, 0);
        destination += 4;
        count -= 4;
    }
    while (count) {
        *(volatile char*)destination++ = 0;
        --count;
    }
}
} // namespace
// Original005CD0F0..005CD213. Aligned DWORD reads/stores and the prefix/tail
// byte order remain explicit, including the original behavior for overlap.
extern "C" char* fun_005cd0f0(char* destination, const char* source, uint32_t count) {
    char* const result = destination;
    while (count && (reinterpret_cast<uint32_t>(source) & 3)) {
        const char value = *(const volatile char*)source++;
        *(volatile char*)destination++ = value;
        --count;
        if (value == 0) {
            pad(destination, count);
            return result;
        }
    }
    while (count >= 4) {
        const uint32_t probe = load_word(source);
        const uint32_t flags = (probe + 0x7efefeffu) ^ ~probe;
        uint32_t word = load_word(source);
        source += 4;
        bool zero = false;
        if ((flags & 0x81010100u) != 0) {
            if ((word & 0xff) == 0) {
                word = 0;
                zero = true;
            } else if ((word & 0xff00) == 0) {
                word &= 0xff;
                zero = true;
            } else if ((word & 0xff0000) == 0) {
                word &= 0xffff;
                zero = true;
            } else if ((word & 0xff000000) == 0)
                zero = true;
        }
        store_word(destination, word);
        destination += 4;
        count -= 4;
        if (zero) {
            pad(destination, count);
            return result;
        }
    }
    while (count) {
        const char value = *(const volatile char*)source++;
        *(volatile char*)destination++ = value;
        --count;
        if (value == 0) {
            pad(destination, count);
            return result;
        }
    }
    return result;
}
extern "C" char* FUN_005cd0f0(char*, const char*, uint32_t) __attribute__((alias("fun_005cd0f0")));
