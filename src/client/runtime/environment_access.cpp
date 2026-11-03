#include "environment_access.h"
#include "runtime/heap.h"
#include "runtime/strings.h"
#include "runtime/thread_data.h"
#include "runtime/multibyte.h"
#include "runtime/locale.h"
#include "runtime/runtime_error.h"
#include "environment_compare.h"

extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) WideCharToMultiByte(uint32_t, uint32_t,
                                                                           const uint16_t*, int32_t,
                                                                           char*, int32_t,
                                                                           const char*, int32_t*);
__declspec(dllimport) int32_t __attribute__((stdcall)) SetEnvironmentVariableA(const char*,
                                                                               const char*);
// Original BSS DWORDs; initial saved narrow environ and wide environ.
char** dat_0224ee0c = nullptr;
uint16_t** dat_0224ee10 = nullptr;
}

extern "C" char* fun_005dec3d(const char* name) {
    char** cursor = dat_0224ee08;
    if (!dat_02254644)
        return nullptr;
    if (!cursor) {
        if (!dat_0224ee10 || fun_005e0c14() != 0)
            return nullptr;
        cursor = dat_0224ee08;
        if (!cursor)
            return nullptr;
    }
    if (!name)
        return nullptr;
    uint32_t count = fun_005d4cf0(name);
    while (*cursor) {
        if (fun_005d4cf0(*cursor) > count && (*cursor)[count] == '=' &&
            fun_005e0bc6(*cursor, name, count) == 0)
            return *cursor + count + 1;
        ++cursor;
    }
    return nullptr;
}

extern "C" int32_t fun_005e0bc6(const char* left, const char* right, uint32_t count) {
    auto* data = static_cast<OriginalPerThreadData*>(fun_005d2659())->reference_counted_60;
    if (data != dat_022533e4)
        data = fun_005d3197();
    if (count == 0)
        return 0;
    auto* info = reinterpret_cast<OriginalMultibyteData*>(data);
    int32_t result = fun_005e125d(info->locale, 1, left, static_cast<int32_t>(count), right,
                                  static_cast<int32_t>(count), info->code_page);
    return result == 0 ? 0x7fffffff : static_cast<int32_t>(static_cast<uint32_t>(result) - 2u);
}

extern "C" int32_t fun_005e0c14() {
    char* local = nullptr;
    uint16_t** cursor = dat_0224ee10;
    // Original caches the WideCharToMultiByte IAT target before the loop.
    auto convert = &WideCharToMultiByte;
    while (*cursor) {
        int32_t bytes = convert(0, 0, *cursor, -1, nullptr, 0, nullptr, nullptr);
        if (!bytes)
            return -1;
        local = static_cast<char*>(fun_005cfade(static_cast<uint32_t>(bytes)));
        if (!local)
            return -1;
        if (!convert(0, 0, *cursor, -1, local, bytes, nullptr, nullptr)) {
            fun_005cfaf0(local);
            return -1;
        }
        // A failed update is skipped after freeing an unconsumed buffer.
        // It does not abort the conversion loop (5e0c75..5e0c8d).
        if (fun_005e1695(&local, 0) < 0 && local) {
            fun_005cfaf0(local);
            local = nullptr;
        }
        ++cursor;
    }
    return 0;
}

extern "C" int32_t fun_005e15e7(const char* name, uint32_t name_length) {
    char** cursor = dat_0224ee08;
    while (*cursor) {
        if (fun_005e0bc6(name, *cursor, name_length) == 0 &&
            ((*cursor)[name_length] == '=' || (*cursor)[name_length] == 0))
            return static_cast<int32_t>(cursor - dat_0224ee08);
        ++cursor;
    }
    return -static_cast<int32_t>(cursor - dat_0224ee08);
}

extern "C" char** fun_005e1634(char* const* source) {
    if (!source)
        return nullptr;
    uint32_t count = 0;
    while (source[count])
        ++count;
    auto* result = static_cast<char**>(fun_005cfade(count * 4u + 4u));
    if (!result)
        fun_005d098b(9);
    char** out = result;
    while (*source) {
        *out = fun_005e186b(*source);
        ++out;
        ++source;
    }
    *out = nullptr;
    return result;
}

extern "C" int32_t fun_005e1695(char** input, int32_t update_os) {
    int32_t result = 0;
    if (!input || !*input)
        return -1;
    char* entry = *input;
    char* separator = fun_005e1896(entry, '=');
    if (!separator || entry == separator)
        return -1;
    const bool remove = separator[1] == 0;
    if (dat_0224ee08 == dat_0224ee0c)
        dat_0224ee08 = fun_005e1634(dat_0224ee08);
    if (!dat_0224ee08) {
        if (update_os && dat_0224ee10) {
            if (fun_005e0c14() != 0)
                return -1;
        } else {
            if (remove)
                return 0;
            dat_0224ee08 = static_cast<char**>(fun_005cfade(4));
            if (!dat_0224ee08)
                return -1;
            *dat_0224ee08 = nullptr;
            if (!dat_0224ee10) {
                dat_0224ee10 = static_cast<uint16_t**>(fun_005cfade(4));
                if (!dat_0224ee10)
                    return -1;
                *dat_0224ee10 = nullptr;
            }
        }
    }
    char** array = dat_0224ee08;
    int32_t index = fun_005e15e7(entry, static_cast<uint32_t>(separator - entry));
    if (index >= 0 && *array) {
        char** position = array + index;
        fun_005cfaf0(*position);
        if (!remove) {
            *position = entry;
            *input = nullptr;
        } else {
            while (*position) {
                *position = position[1];
                ++index;
                position = array + index;
            }
            auto* resized =
                static_cast<char**>(fun_005d020a(dat_0224ee08, static_cast<uint32_t>(index) * 4u));
            if (resized)
                dat_0224ee08 = resized;
        }
    } else {
        if (remove) {
            fun_005cfaf0(entry);
            *input = nullptr;
            return 0;
        }
        if (index < 0)
            index = static_cast<int32_t>(0u - static_cast<uint32_t>(index));
        auto* resized =
            static_cast<char**>(fun_005d020a(dat_0224ee08, static_cast<uint32_t>(index) * 4u + 8u));
        if (!resized)
            return -1;
        resized[index + 1] = nullptr;
        resized[index] = entry;
        *input = nullptr;
        dat_0224ee08 = resized;
    }
    if (update_os) {
        char* copy = static_cast<char*>(fun_005cfade(fun_005d4cf0(entry) + 2u));
        if (copy) {
            fun_005d6350(copy, entry);
            char* value = copy + (separator - entry);
            *value = 0;
            ++value;
            if (!SetEnvironmentVariableA(copy, remove ? nullptr : value))
                result = -1;
            fun_005cfaf0(copy);
        }
    }
    // Original found-entry removal leaves *input dangling; only a missing-entry
    // removal clears it. Preserve that observed ownership behavior.
    if (remove)
        fun_005cfaf0(entry);
    return result;
}

extern "C" char* fun_005e186b(const char* source) {
    if (!source)
        return nullptr;
    auto* result = static_cast<char*>(fun_005cfade(fun_005d4cf0(source) + 1u));
    return result ? fun_005d6350(result, source) : nullptr;
}

extern "C" char* fun_005e1896(const char* source, uint32_t character) {
    auto* data = static_cast<OriginalPerThreadData*>(fun_005d2659())->reference_counted_60;
    if (data != dat_022533e4)
        data = fun_005d3197();
    auto* info = reinterpret_cast<OriginalMultibyteData*>(data);
    if (!info->multibyte)
        return fun_005d6670(source, character);
    const auto* cursor = reinterpret_cast<const uint8_t*>(source);
    while (*cursor) {
        uint32_t current = *cursor;
        if (info->classification[current + 1] & 4) {
            uint8_t second = cursor[1];
            if (!second)
                return nullptr;
            if (character == ((current << 8) | second))
                return const_cast<char*>(reinterpret_cast<const char*>(cursor));
            cursor += 2;
        } else {
            if (character == current)
                return const_cast<char*>(reinterpret_cast<const char*>(cursor));
            ++cursor;
        }
    }
    return character == 0 ? const_cast<char*>(reinterpret_cast<const char*>(cursor)) : nullptr;
}
