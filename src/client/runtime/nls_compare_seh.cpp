#include "environment_compare.h"
#include "runtime/nls.h"
#include "runtime/multibyte.h"
#include "runtime/heap.h"
#include "runtime/security.h"
extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall))
CompareStringW(uint32_t, uint32_t, const uint16_t*, int32_t, const uint16_t*, int32_t);
__declspec(dllimport) int32_t __attribute__((stdcall))
CompareStringA(uint32_t, uint32_t, const char*, int32_t, const char*, int32_t);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetLastError();
__declspec(dllimport) int32_t __attribute__((stdcall)) GetCPInfo(uint32_t, OriginalCodePageInfo*);
__declspec(dllimport) int32_t __attribute__((stdcall))
MultiByteToWideChar(uint32_t, uint32_t, const char*, int32_t, uint16_t*, int32_t);
uint32_t dat_0224f2e4 = 0;
}

extern "C" uint32_t fun_005e1241(const char* source, uint32_t count) {
    uint32_t remaining = count;
    if (remaining) {
        do {
            --remaining;
            if (!*source)
                return count - remaining - 1u;
            ++source;
        } while (remaining);
    }
    --remaining;
    return count - remaining - 1u;
}

namespace {
int32_t compare(uint32_t locale, uint32_t flags, const char* left, int32_t left_length,
                const char* right, int32_t right_length, uint32_t code_page) {
    if (!dat_0224f2e4) {
        static const uint16_t empty = 0; // original readonly UTF16 terminator6d6dbc
        if (CompareStringW(0, 0, &empty, 1, &empty, 1))
            dat_0224f2e4 = 1;
        else if (GetLastError() == 120)
            dat_0224f2e4 = 2;
    }
    if (left_length > 0)
        left_length = static_cast<int32_t>(fun_005e1241(left, static_cast<uint32_t>(left_length)));
    if (right_length > 0)
        right_length =
            static_cast<int32_t>(fun_005e1241(right, static_cast<uint32_t>(right_length)));
    if (dat_0224f2e4 == 1) {
        int32_t result = 0;
        bool first_heap = false, second_heap = false;
        if (!code_page)
            code_page = dat_0224f258;
        if (!left_length || !right_length) {
            if (left_length == right_length)
                return 2;
            if (right_length > 1)
                return 1;
            if (left_length > 1)
                return 3;
            OriginalCodePageInfo info;
            if (!GetCPInfo(code_page, &info))
                return 0;
            if (left_length > 0) {
                if (info.maximum_character_bytes < 2)
                    return 3;
                for (const uint8_t* p = info.lead_bytes; p[0] && p[1]; p += 2)
                    if (p[0] <= static_cast<uint8_t>(*left) && static_cast<uint8_t>(*left) <= p[1])
                        return 2;
                return 3;
            }
            if (right_length > 0) {
                if (info.maximum_character_bytes > 1)
                    for (const uint8_t* p = info.lead_bytes; p[0] && p[1]; p += 2)
                        if (p[0] <= static_cast<uint8_t>(*right) &&
                            static_cast<uint8_t>(*right) <= p[1])
                            return 2;
                return 1;
            }
        }
        int32_t first_count = MultiByteToWideChar(code_page, 9, left, left_length, nullptr, 0);
        if (!first_count)
            return 0;
        uint16_t* first;
        __try {
            first = static_cast<uint16_t*>(
                __builtin_alloca((static_cast<uint32_t>(first_count) * 2u + 3u) & ~3u));
        } __except (1) {
            fun_005cfb61();
            first = nullptr;
        }
        if (!first) {
            first = static_cast<uint16_t*>(fun_005cfade(static_cast<uint32_t>(first_count) * 2u));
            if (!first)
                return 0;
            first_heap = true;
        }
        if (MultiByteToWideChar(code_page, 1, left, left_length, first, first_count)) {
            int32_t second_count =
                MultiByteToWideChar(code_page, 9, right, right_length, nullptr, 0);
            if (second_count) {
                uint16_t* second;
                __try {
                    second = static_cast<uint16_t*>(
                        __builtin_alloca((static_cast<uint32_t>(second_count) * 2u + 3u) & ~3u));
                } __except (1) {
                    fun_005cfb61();
                    second = nullptr;
                }
                if (!second) {
                    second = static_cast<uint16_t*>(
                        fun_005cfade(static_cast<uint32_t>(second_count) * 2u));
                    if (second)
                        second_heap = true;
                }
                if (second) {
                    if (MultiByteToWideChar(code_page, 1, right, right_length, second,
                                            second_count))
                        result =
                            CompareStringW(locale, flags, first, first_count, second, second_count);
                    if (second_heap)
                        fun_005cfaf0(second);
                }
            }
        }
        if (first_heap)
            fun_005cfaf0(first);
        return result;
    }
    if (dat_0224f2e4 != 0 && dat_0224f2e4 != 2)
        return 0;
    if (!locale)
        locale = dat_0224f248;
    if (!code_page)
        code_page = dat_0224f258;
    uint32_t locale_page = static_cast<uint32_t>(fun_005df112(locale));
    if (locale_page == 0xffffffffu)
        return 0;
    char* first = nullptr;
    char* second = nullptr;
    if (locale_page != code_page) {
        first = fun_005df159(code_page, locale_page, left, &left_length, nullptr, 0);
        if (!first)
            return 0;
        second = fun_005df159(code_page, locale_page, right, &right_length, nullptr, 0);
        if (!second) {
            fun_005cfaf0(first);
            return 0;
        }
        left = first;
        right = second;
    }
    int32_t result = CompareStringA(locale, flags, left, left_length, right, right_length);
    if (first) {
        fun_005cfaf0(first);
        fun_005cfaf0(second);
    }
    return result;
}
} // namespace

extern "C" int32_t fun_005e125d(uint32_t locale, uint32_t flags, const char* left,
                                int32_t left_length, const char* right, int32_t right_length,
                                uint32_t code_page) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    int32_t result = compare(locale, flags, left, left_length, right, right_length, code_page);
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return result;
}
