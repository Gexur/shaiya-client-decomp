#include "nls.h"
#include "multibyte.h"
#include "heap.h"
#include "allocations.h"
#include "strings.h"
#include "security.h"
#include "../core/memory.h"

extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) GetLastError();
__declspec(dllimport) int32_t __attribute__((stdcall)) GetStringTypeW(uint32_t, const uint16_t*,
                                                                      int32_t, uint16_t*);
__declspec(dllimport) int32_t __attribute__((stdcall))
GetStringTypeA(uint32_t, uint32_t, const char*, int32_t, uint16_t*);
__declspec(dllimport) int32_t __attribute__((stdcall))
MultiByteToWideChar(uint32_t, uint32_t, const char*, int32_t, uint16_t*, int32_t);
__declspec(dllimport) int32_t __attribute__((stdcall)) WideCharToMultiByte(uint32_t, uint32_t,
                                                                           const uint16_t*, int32_t,
                                                                           char*, int32_t,
                                                                           const char*, int32_t*);
__declspec(dllimport) int32_t __attribute__((stdcall)) GetCPInfo(uint32_t, OriginalCodePageInfo*);
}

extern "C" int32_t fun_005dc003(uint32_t information, const char* source, int32_t length,
                                uint16_t* types, uint32_t code_page, uint32_t locale,
                                int32_t strict) {
    if (!dat_0224f238) {
        uint16_t type[2];
        const uint16_t empty = 0;
        if (GetStringTypeW(1, &empty, 1, type))
            dat_0224f238 = 1;
        else if (GetLastError() == 120)
            dat_0224f238 = 2;
    }
    if (!dat_0224f238 || dat_0224f238 == 2) {
        if (!locale)
            locale = dat_0224f248;
        if (!code_page)
            code_page = dat_0224f258;
        const uint32_t locale_page = uint32_t(fun_005df112(locale));
        if (locale_page == 0xffffffffu)
            return 0;
        char* converted = nullptr;
        if (locale_page != code_page) {
            converted = fun_005df159(code_page, locale_page, source, &length, nullptr, 0);
            if (!converted)
                return 0;
            source = converted;
        }
        const int32_t result = GetStringTypeA(locale, information, source, length, types);
        if (converted)
            fun_005cfaf0(converted);
        return result;
    }
    if (dat_0224f238 != 1)
        return 0;
    if (!code_page)
        code_page = dat_0224f258;
    const int32_t count =
        MultiByteToWideChar(code_page, strict ? 9 : 1, source, length, nullptr, 0);
    if (!count)
        return 0;
    const uint32_t bytes = uint32_t(count) * 2u;
    uint16_t* wide;
    bool heap = false;
    __try {
        wide = static_cast<uint16_t*>(__builtin_alloca((bytes + 3u) & ~3u));
        fun_005dceb0(wide, 0, bytes);
    } __except (1) {
        fun_005cfb61();
        wide = nullptr;
    }
    if (!wide) {
        wide = static_cast<uint16_t*>(fun_005d8c58(2, count));
        if (!wide)
            return 0;
        heap = true;
    }
    const int32_t converted = MultiByteToWideChar(code_page, 1, source, length, wide, count);
    const int32_t result = converted ? GetStringTypeW(information, wide, converted, types) : 0;
    if (heap)
        fun_005cfaf0(wide);
    return result;
}

extern "C" char* fun_005df159(uint32_t from, uint32_t to, const char* source, int32_t* length,
                              char* output, int32_t capacity) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    const int32_t input_length = *length;
    char* result = nullptr;
    if (from == to) {
        fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
        return result;
    }
    OriginalCodePageInfo information;
    bool single_byte = false;
    if (GetCPInfo(from, &information) && information.maximum_character_bytes == 1 &&
        GetCPInfo(to, &information) && information.maximum_character_bytes == 1)
        single_byte = true;
    int32_t count;
    if (single_byte)
        count = input_length == -1 ? int32_t(fun_005d4cf0(source) + 1u) : input_length;
    else {
        count = MultiByteToWideChar(from, 1, source, input_length, nullptr, 0);
        if (!count) {
            fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
            return result;
        }
    }
    uint16_t* wide;
    bool heap = false;
    const uint32_t bytes = uint32_t(count) * 2u;
    __try {
        wide = static_cast<uint16_t*>(__builtin_alloca((bytes + 3u) & ~3u));
        fun_005dceb0(wide, 0, bytes);
    } __except (1) {
        fun_005cfb61();
        wide = nullptr;
    }
    if (!wide) {
        wide = static_cast<uint16_t*>(fun_005d8c58(2, count));
        if (!wide) {
            fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
            return result;
        }
        heap = true;
    }
    if (MultiByteToWideChar(from, 1, source, input_length, wide, count)) {
        if (output) {
            if (WideCharToMultiByte(to, 0, wide, count, output, capacity, nullptr, nullptr))
                result = output;
        } else {
            if (!single_byte)
                count = WideCharToMultiByte(to, 0, wide, count, nullptr, 0, nullptr, nullptr);
            if (single_byte || count) {
                result = static_cast<char*>(fun_005d8c58(1, count));
                if (result) {
                    // Original reuses output-byte count as the wide-input count.
                    const int32_t converted =
                        WideCharToMultiByte(to, 0, wide, count, result, count, nullptr, nullptr);
                    if (!converted) {
                        fun_005cfaf0(result);
                        result = nullptr;
                    } else if (input_length != -1)
                        *length = converted;
                }
            }
        }
    }
    if (heap)
        fun_005cfaf0(wide);
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return result;
}
