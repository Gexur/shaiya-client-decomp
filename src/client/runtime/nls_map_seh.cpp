#include "nls.h"
#include "multibyte.h"
#include "heap.h"
#include "../core/memory.h"

extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) GetLastError();
__declspec(dllimport) int32_t __attribute__((stdcall))
LCMapStringW(uint32_t, uint32_t, const uint16_t*, int32_t, uint16_t*, int32_t);
__declspec(dllimport) int32_t __attribute__((stdcall)) LCMapStringA(uint32_t, uint32_t, const char*,
                                                                    int32_t, char*, int32_t);
__declspec(dllimport) int32_t __attribute__((stdcall))
MultiByteToWideChar(uint32_t, uint32_t, const char*, int32_t, uint16_t*, int32_t);
__declspec(dllimport) int32_t __attribute__((stdcall)) WideCharToMultiByte(uint32_t, uint32_t,
                                                                           const uint16_t*, int32_t,
                                                                           char*, int32_t,
                                                                           const char*, int32_t*);
}

extern "C" uint32_t fun_005d9327(uint32_t locale, uint32_t flags, const char* source,
                                 int32_t length, char* output, int32_t capacity, uint32_t code_page,
                                 int32_t strict) {
    if (!dat_0224f0b0) {
        const uint16_t empty = 0;
        if (LCMapStringW(0, 0x100, &empty, 1, nullptr, 0))
            dat_0224f0b0 = 1;
        else if (GetLastError() == 120)
            dat_0224f0b0 = 2;
    }
    if (length > 0) {
        int32_t remaining = length;
        const char* cursor = source;
        do {
            --remaining;
            if (!*cursor)
                break;
            ++cursor;
        } while (remaining);
        if (!remaining && cursor == source + length)
            remaining = -1;
        length = int32_t(uint32_t(length) - 1u - uint32_t(remaining));
    }
    if (dat_0224f0b0 == 1) {
        uint32_t result = 0;
        bool input_heap = false, output_heap = false;
        if (!code_page)
            code_page = dat_0224f258;
        const int32_t count =
            MultiByteToWideChar(code_page, strict ? 9 : 1, source, length, nullptr, 0);
        if (!count)
            return 0;
        uint16_t* wide_input;
        __try {
            wide_input =
                static_cast<uint16_t*>(__builtin_alloca((uint32_t(count) * 2u + 3u) & ~3u));
        } __except (1) {
            fun_005cfb61();
            wide_input = nullptr;
        }
        if (!wide_input) {
            wide_input = static_cast<uint16_t*>(fun_005cfade(uint32_t(count) * 2u));
            if (!wide_input)
                return 0;
            input_heap = true;
        }
        uint16_t* wide_output;
        if (MultiByteToWideChar(code_page, 1, source, length, wide_input, count)) {
            result = LCMapStringW(locale, flags, wide_input, count, nullptr, 0);
            if (result) {
                if (flags & 0x400u) {
                    if (capacity && int32_t(result) <= capacity)
                        LCMapStringW(locale, flags, wide_input, count,
                                     reinterpret_cast<uint16_t*>(output), capacity);
                } else {
                    __try {
                        wide_output =
                            static_cast<uint16_t*>(__builtin_alloca((result * 2u + 3u) & ~3u));
                    } __except (1) {
                        fun_005cfb61();
                        wide_output = nullptr;
                    }
                    if (!wide_output) {
                        wide_output = static_cast<uint16_t*>(fun_005cfade(result * 2u));
                        if (wide_output)
                            output_heap = true;
                    }
                    if (wide_output &&
                        LCMapStringW(locale, flags, wide_input, count, wide_output, result))
                        result = WideCharToMultiByte(code_page, 0, wide_output, result,
                                                     capacity ? output : nullptr,
                                                     capacity ? capacity : 0, nullptr, nullptr);
                }
            }
        }
        if (output_heap)
            fun_005cfaf0(wide_output);
        if (input_heap)
            fun_005cfaf0(wide_input);
        return result;
    }
    if (dat_0224f0b0 && dat_0224f0b0 != 2)
        return 0;
    if (!locale)
        locale = dat_0224f248;
    if (!code_page)
        code_page = dat_0224f258;
    const uint32_t locale_page = uint32_t(fun_005df112(locale));
    if (locale_page == 0xffffffffu)
        return 0;
    if (locale_page == code_page)
        return LCMapStringA(locale, flags, source, length, output, capacity);
    char* converted_input = fun_005df159(code_page, locale_page, source, &length, nullptr, 0);
    if (!converted_input)
        return 0;
    int32_t size = LCMapStringA(locale, flags, converted_input, length, nullptr, 0);
    // Original5d96a6 loads an unwritten stack DWORD if measurement returns zero.
    // Its value is indeterminate, not a fabricated deterministic error code.
    unsigned char unwritten_result[4];
    uint32_t result;
    char* converted_output = nullptr;
    char* temporary;
    bool heap = false;
    if (size) {
        __try {
            temporary = static_cast<char*>(__builtin_alloca((uint32_t(size) + 3u) & ~3u));
            fun_005dceb0(temporary, 0, size);
        } __except (1) {
            fun_005cfb61();
            temporary = nullptr;
        }
        if (!temporary) {
            temporary = static_cast<char*>(fun_005cfade(size));
            if (temporary) {
                fun_005dceb0(temporary, 0, size);
                heap = true;
            }
        }
        result = 0;
        if (temporary) {
            size = LCMapStringA(locale, flags, converted_input, length, temporary, size);
            if (size) {
                converted_output =
                    fun_005df159(locale_page, code_page, temporary, &size, output, capacity);
                if (converted_output)
                    result = size;
            }
        }
        if (heap)
            fun_005cfaf0(temporary);
    } else {
        // A machine-level read of unwritten storage, without a C++ promotion
        // of an indeterminate integer. Its initial contents remain a boundary.
        __asm__ volatile("movl %1, %0" : "=r"(result) : "m"(unwritten_result) : "memory");
    }
    fun_005cfaf0(converted_input);
    if (converted_output && converted_output != output)
        fun_005cfaf0(converted_output);
    return result;
}
