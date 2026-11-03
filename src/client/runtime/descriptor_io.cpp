#include "descriptor_io.h"
#include "thread_data.h"
#include "security.h"

extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) SetStdHandle(int32_t, void*);
__declspec(dllimport) uint32_t __attribute__((stdcall)) SetFilePointer(void*, int32_t, int32_t*,
                                                                       uint32_t);
__declspec(dllimport) int32_t __attribute__((stdcall)) CloseHandle(void*);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetLastError();
__declspec(dllimport) int32_t __attribute__((stdcall)) WriteFile(void*, const void*, uint32_t,
                                                                 uint32_t*, void*);
__declspec(dllimport) void __attribute__((stdcall)) LeaveCriticalSection(OriginalCriticalSection*);
uint32_t dat_0070e4d4 = 2;
const OriginalDosError dat_0070e800[45] = {
    {1, 22},   {2, 2},    {3, 2},    {4, 24},   {5, 13},   {6, 9},    {7, 12},  {8, 12},
    {9, 12},   {10, 7},   {11, 8},   {12, 22},  {13, 22},  {15, 2},   {16, 13}, {17, 18},
    {18, 2},   {33, 13},  {53, 2},   {65, 13},  {67, 2},   {80, 17},  {82, 13}, {83, 13},
    {87, 22},  {89, 11},  {108, 13}, {109, 32}, {112, 28}, {114, 9},  {6, 22},  {128, 10},
    {129, 10}, {130, 9},  {131, 22}, {132, 13}, {145, 41}, {158, 13}, {161, 2}, {164, 11},
    {167, 13}, {183, 17}, {206, 2},  {215, 11}, {1816, 12}};
}

extern "C" uint32_t* fun_005d58a3() {
    return reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(fun_005d2659()) + 12);
}
extern "C" void fun_005d58ac(uint32_t error) {
    auto* data = static_cast<OriginalPerThreadData*>(fun_005d2659());
    *reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(data) + 12) = error;
    uint32_t index = 0;
    for (; index < 45; ++index)
        if (dat_0070e800[index].system_error == error)
            break;
    int32_t value;
    if (index < 45)
        value = dat_0070e800[index].c_error;
    else if (error >= 19 && error <= 36)
        value = 13;
    else if (error >= 188 && error <= 202)
        value = 8;
    else
        value = 22;
    static_cast<OriginalPerThreadData*>(fun_005d2659())->error_number = value;
}

static int32_t bad_descriptor() {
    *fun_005d589a() = 9;
    *fun_005d58a3() = 0;
    return -1;
}
extern "C" int32_t fun_005d5c18(int32_t descriptor) {
    if (uint32_t(descriptor) < uint32_t(dat_022532d4)) {
        auto* entry = original_io_entry(descriptor);
        if (entry->flags & 1u)
            return int32_t(reinterpret_cast<uint32_t>(entry->handle));
    }
    return bad_descriptor();
}
extern "C" int32_t fun_005d5b99(int32_t descriptor) {
    if (uint32_t(descriptor) < uint32_t(dat_022532d4)) {
        auto* entry = original_io_entry(descriptor);
        if ((entry->flags & 1u) && entry->handle != reinterpret_cast<void*>(0xffffffffu)) {
            if (dat_0070e4d4 == 1 && descriptor >= 0 && descriptor <= 2)
                SetStdHandle(-10 - descriptor, nullptr);
            original_io_entry(descriptor)->handle = reinterpret_cast<void*>(0xffffffffu);
            return 0;
        }
    }
    return bad_descriptor();
}
extern "C" void fun_005d5cf9(int32_t descriptor) {
    LeaveCriticalSection(&original_io_entry(descriptor)->section);
}
extern "C" void fun_005d5cf0() {
    fun_005d64e6(10);
}

extern "C" int64_t fun_005ce21f(int32_t descriptor, int32_t low, int32_t high, uint32_t origin) {
    const int32_t handle = fun_005d5c18(descriptor);
    uint32_t result;
    if (handle == -1) {
        *fun_005d589a() = 9;
        result = 0xffffffffu;
        high = -1;
    } else {
        result = SetFilePointer(reinterpret_cast<void*>(handle), low, &high, origin);
        uint32_t error = 0;
        if (result == 0xffffffffu)
            error = GetLastError();
        if (error) {
            fun_005d58ac(error);
            result = 0xffffffffu;
            high = -1;
        } else
            original_io_entry(descriptor)->flags &= 0xfdu;
    }
    return int64_t((uint64_t(uint32_t(high)) << 32) | result);
}

extern "C" int32_t fun_005cd4e1(int32_t descriptor) {
    uint32_t error = 0;
    if (fun_005d5c18(descriptor) != -1) {
        bool close = true;
        if (descriptor == 1 || descriptor == 2) {
            const int32_t second = fun_005d5c18(2);
            close = fun_005d5c18(1) != second;
        }
        if (close && !CloseHandle(reinterpret_cast<void*>(fun_005d5c18(descriptor))))
            error = GetLastError();
    }
    fun_005d5b99(descriptor);
    original_io_entry(descriptor)->flags = 0;
    if (error) {
        fun_005d58ac(error);
        return -1;
    }
    return 0;
}

extern "C" int32_t fun_005d0c62(int32_t descriptor, const char* buffer, uint32_t count) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    uint32_t written = 0, extra = 0, error = 0;
    if (!count) {
        fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
        return 0;
    }
    if (original_io_entry(descriptor)->flags & 0x20u)
        fun_005ce21f(descriptor, 0, 0, 2);
    if (original_io_entry(descriptor)->flags & 0x80u) {
        // Original checks the limit after adding both bytes of a translated LF,
        // so a chunk can contain1025bytes. No extra rejection is introduced.
        char temporary[1025];
        uint32_t consumed = 0;
        do {
            uint32_t output = 0;
            do {
                if (consumed >= count)
                    break;
                const char value = buffer[consumed++];
                if (value == '\n') {
                    ++extra;
                    temporary[output++] = '\r';
                }
                temporary[output++] = value;
            } while (int32_t(output) < 1024);
            uint32_t actual;
            if (!WriteFile(original_io_entry(descriptor)->handle, temporary, output, &actual,
                           nullptr)) {
                error = GetLastError();
                break;
            }
            written += actual;
            if (int32_t(actual) < int32_t(output))
                break;
        } while (consumed < count);
    } else {
        uint32_t actual;
        if (!WriteFile(original_io_entry(descriptor)->handle, buffer, count, &actual, nullptr))
            error = GetLastError();
        else
            written = actual;
    }
    int32_t result;
    if (written)
        result = int32_t(written - extra);
    else if (error) {
        if (error == 5) {
            *fun_005d589a() = 9;
            *fun_005d58a3() = 5;
        } else
            fun_005d58ac(error);
        result = -1;
    } else if ((original_io_entry(descriptor)->flags & 0x40u) && uint8_t(*buffer) == 0x1a)
        result = 0;
    else {
        *fun_005d589a() = 28;
        *fun_005d58a3() = 0;
        result = -1;
    }
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return result;
}
