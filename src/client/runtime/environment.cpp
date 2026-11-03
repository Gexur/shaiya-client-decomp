#include "environment.h"
#include "startup_args.h"
#include "strings.h"
#include "heap.h"
#include "../core/memory.h"

extern "C" {
__declspec(dllimport) uint16_t* __attribute__((stdcall)) GetEnvironmentStringsW();
__declspec(dllimport) char* __attribute__((stdcall)) GetEnvironmentStrings();
__declspec(dllimport) int32_t __attribute__((stdcall)) FreeEnvironmentStringsW(uint16_t*);
__declspec(dllimport) int32_t __attribute__((stdcall)) FreeEnvironmentStringsA(char*);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetLastError();
__declspec(dllimport) int32_t __attribute__((stdcall)) WideCharToMultiByte(uint32_t, uint32_t,
                                                                           const uint16_t*, int32_t,
                                                                           char*, int32_t,
                                                                           const char*, int32_t*);
char** dat_0224ee08 = nullptr;
uint32_t dat_02254644 = 0;
uint32_t dat_0224f220 = 0;
}

extern "C" int32_t fun_005dba65() {
    if (dat_02254650 == 0)
        fun_005d34ea();
    const char* cursor = static_cast<const char*>(dat_0224ee38);
    if (cursor == nullptr)
        return -1;
    uint32_t count = 0;
    while (*cursor != 0) {
        if (*cursor != '=')
            ++count;
        cursor += fun_005d4cf0(cursor) + 1;
    }
    dat_0224ee08 = static_cast<char**>(fun_005cfade(count * 4 + 4));
    if (dat_0224ee08 == nullptr)
        return -1;
    char** next = dat_0224ee08;
    cursor = static_cast<const char*>(dat_0224ee38);
    while (*cursor != 0) {
        uint32_t size = fun_005d4cf0(cursor) + 1;
        if (*cursor != '=') {
            char* allocation = static_cast<char*>(fun_005cfade(size));
            *next = allocation;
            if (allocation == nullptr) {
                fun_005cfaf0(dat_0224ee08);
                dat_0224ee08 = nullptr;
                return -1;
            }
            fun_005d6350(allocation, cursor);
            ++next;
        }
        cursor += size;
    }
    fun_005cfaf0(dat_0224ee38);
    dat_0224ee38 = nullptr;
    *next = nullptr;
    dat_02254644 = 1;
    return 0;
}

extern "C" void* fun_005dbd3a() {
    uint16_t* wide = nullptr;
    uint32_t selected = dat_0224f220;
    if (selected == 0) {
        wide = GetEnvironmentStringsW();
        if (wide != nullptr)
            dat_0224f220 = selected = 1;
        else {
            if (GetLastError() == 120)
                dat_0224f220 = 2;
            selected = dat_0224f220;
        }
    }
    if (selected == 1) {
        if (wide == nullptr)
            wide = GetEnvironmentStringsW();
        if (wide == nullptr)
            return nullptr;
        uint16_t* cursor = wide;
        while (*cursor != 0) {
            do {
                ++cursor;
            } while (*cursor != 0);
            ++cursor;
        }
        int32_t characters = static_cast<int32_t>(cursor - wide + 1);
        int32_t bytes = WideCharToMultiByte(0, 0, wide, characters, nullptr, 0, nullptr, nullptr);
        char* result = nullptr;
        if (bytes != 0) {
            result = static_cast<char*>(fun_005cfade(static_cast<uint32_t>(bytes)));
            if (result != nullptr &&
                WideCharToMultiByte(0, 0, wide, characters, result, bytes, nullptr, nullptr) == 0) {
                fun_005cfaf0(result);
                result = nullptr;
            }
        }
        FreeEnvironmentStringsW(wide);
        return result;
    }
    if (selected != 0 && selected != 2)
        return nullptr;
    char* ansi = GetEnvironmentStrings();
    if (ansi == nullptr)
        return nullptr;
    char* cursor = ansi;
    while (*cursor != 0) {
        do {
            ++cursor;
        } while (*cursor != 0);
        ++cursor;
    }
    uint32_t bytes = static_cast<uint32_t>(cursor - ansi + 1);
    void* result = fun_005cfade(bytes);
    if (result != nullptr)
        fun_005d8d30(result, ansi, bytes);
    FreeEnvironmentStringsA(ansi);
    return result;
}
