#include "file_open.h"
#include "heap.h"
#include "security.h"
#include "../core/memory.h"

struct OriginalSecurityAttributes {
    uint32_t size;
    void* descriptor;
    int32_t inherit;
};
static_assert(sizeof(OriginalSecurityAttributes) == 12);
extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) SetStdHandle(int32_t, void*);
__declspec(dllimport) void* __attribute__((stdcall)) CreateFileA(const char*, uint32_t, uint32_t,
                                                                 OriginalSecurityAttributes*,
                                                                 uint32_t, uint32_t, void*);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetFileType(void*);
__declspec(dllimport) int32_t __attribute__((stdcall)) CloseHandle(void*);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetLastError();
__declspec(dllimport) int32_t __attribute__((stdcall)) SetEndOfFile(void*);
uint32_t dat_0224ee74 = 0, dat_0224ede4 = 0;
}
extern "C" int32_t fun_005d5b1d(int32_t descriptor, int32_t handle) {
    if (uint32_t(descriptor) < uint32_t(dat_022532d4) &&
        file_io_entry(descriptor)->handle == reinterpret_cast<void*>(0xffffffffu)) {
        if (dat_0070e4d4 == 1 && descriptor >= 0 && descriptor <= 2)
            SetStdHandle(-10 - descriptor, reinterpret_cast<void*>(handle));
        file_io_entry(descriptor)->handle = reinterpret_cast<void*>(handle);
        return 0;
    }
    *fun_005d589a() = 9;
    *fun_005d58a3() = 0;
    return -1;
}
extern "C" int32_t fun_005de9fb(int32_t descriptor, int32_t mode) {
    const uint8_t old = file_io_entry(descriptor)->flags;
    if (mode == 0x8000)
        file_io_entry(descriptor)->flags &= 0x7fu;
    else if (mode == 0x4000)
        file_io_entry(descriptor)->flags |= 0x80u;
    else {
        *fun_005d589a() = 22;
        return -1;
    }
    return old & 0x80u ? 0x4000 : 0x8000;
}
extern "C" int32_t fun_005d5e97(int32_t descriptor, int32_t size) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    int32_t result = 0;
    const int32_t position = fun_005cd610(descriptor, 0, 1);
    int32_t end;
    if (position == -1 || (end = fun_005cd610(descriptor, 0, 2)) == -1)
        result = -1;
    else {
        int32_t difference = int32_t(uint32_t(size) - uint32_t(end));
        if (difference > 0) {
            char zeroes[4096];
            fun_005dceb0(zeroes, 0, 4096);
            const int32_t old_mode = fun_005de9fb(descriptor, 0x8000);
            do {
                const int32_t chunk = difference < 4096 ? difference : 4096;
                const int32_t actual = fun_005d0c62(descriptor, zeroes, chunk);
                if (actual == -1) {
                    if (*fun_005d58a3() == 5)
                        *fun_005d589a() = 13;
                    result = -1;
                    break;
                }
                difference = int32_t(uint32_t(difference) - uint32_t(actual));
            } while (difference > 0);
            fun_005de9fb(descriptor, old_mode);
        } else if (difference < 0) {
            fun_005cd610(descriptor, size, 0);
            const int32_t handle = fun_005d5c18(descriptor);
            result = SetEndOfFile(reinterpret_cast<void*>(handle)) ? 0 : -1;
            if (result == -1) {
                *fun_005d589a() = 13;
                uint32_t* const os_error = fun_005d58a3();
                const uint32_t error = GetLastError();
                *os_error = error;
            }
        }
        fun_005cd610(descriptor, position, 0);
    }
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return result;
}

extern "C" int32_t fun_005cd72f(int32_t* locked, int32_t* output_descriptor, const char* path,
                                uint32_t flags, uint32_t permissions, uint32_t sharing) {
    OriginalSecurityAttributes security = {12, nullptr, int8_t(flags) >= 0 ? 1 : 0};
    uint8_t internal = int8_t(flags) >= 0 ? 0 : 0x10;
    if (!(flags & 0x8000u) && ((flags & 0x4000u) || dat_0224ee74 != 0x8000u))
        internal |= 0x80u;
    uint32_t access;
    switch (flags & 3u) {
    case 0:
        access = 0x80000000u;
        break;
    case 1:
        access = 0x40000000u;
        break;
    case 2:
        access = 0xc0000000u;
        break;
    default:
        *fun_005d589a() = 22;
        *fun_005d58a3() = 0;
        return -1;
    }
    uint32_t share;
    switch (sharing) {
    case 0x10:
        share = 0;
        break;
    case 0x20:
        share = 1;
        break;
    case 0x30:
        share = 2;
        break;
    case 0x40:
        share = 3;
        break;
    default:
        *fun_005d589a() = 22;
        *fun_005d58a3() = 0;
        return -1;
    }
    uint32_t creation;
    switch (flags & 0x700u) {
    case 0:
    case 0x400:
        creation = 3;
        break;
    case 0x100:
        creation = 4;
        break;
    case 0x200:
    case 0x600:
        creation = 5;
        break;
    case 0x300:
        creation = 2;
        break;
    case 0x500:
    case 0x700:
        creation = 1;
        break;
    default:
        *fun_005d589a() = 22;
        *fun_005d58a3() = 0;
        return -1;
    }
    uint32_t attributes = 0x80;
    if ((flags & 0x100u) && int8_t((~dat_0224ede4) & permissions) >= 0)
        attributes = 1;
    if (flags & 0x40u) {
        access |= 0x10000u;
        attributes |= 0x4000000u;
        if (dat_0224ede8 == 2)
            share |= 4;
    }
    if (flags & 0x1000u)
        attributes |= 0x100u;
    if (flags & 0x20u)
        attributes |= 0x8000000u;
    else if (flags & 0x10u)
        attributes |= 0x10000000u;
    const int32_t descriptor = fun_005d5d1b();
    if (descriptor == -1) {
        *fun_005d589a() = 24;
        *fun_005d58a3() = 0;
        return -1;
    }
    *locked = 1;
    *output_descriptor = descriptor;
    void* handle = CreateFileA(path, access, share, &security, creation, attributes, nullptr);
    if (handle != reinterpret_cast<void*>(0xffffffffu)) {
        const uint32_t type = GetFileType(handle);
        if (type) {
            if (type == 2)
                internal |= 0x40u;
            else if (type == 3)
                internal |= 8u;
            fun_005d5b1d(descriptor, int32_t(reinterpret_cast<uint32_t>(handle)));
            internal |= 1u;
            file_io_entry(descriptor)->flags = internal;
            const uint8_t special = internal & 0x48u;
            if (!special && int8_t(internal) < 0 && (flags & 2u)) {
                const int32_t position = fun_005cd610(descriptor, -1, 2);
                bool failed = false;
                if (position == -1)
                    failed = *fun_005d58a3() != 131;
                else {
                    char final = 0;
                    const int32_t amount = fun_005ce360(descriptor, &final, 1);
                    if (!amount && uint8_t(final) == 0x1a &&
                        fun_005d5e97(descriptor, position) == -1)
                        failed = true;
                    if (!failed && fun_005cd610(descriptor, 0, 0) == -1)
                        failed = true;
                }
                if (failed) {
                    fun_005cd4e1(descriptor);
                    return -1;
                }
            }
            if (!special && (flags & 8u))
                file_io_entry(descriptor)->flags |= 0x20u;
            return descriptor;
        }
        CloseHandle(handle);
    }
    fun_005d58ac(GetLastError());
    return -1;
}

// Architectural vararg adapter: original _open reads the third incoming stack
// DWORD even when O_CREAT is clear and callers supplied only two arguments.
// This raw x86 read retains that unprovided operand without C++ va_arg UB.
extern "C" int32_t _open(const char* path, int32_t flags, ...) {
    uint32_t permissions;
    const void* frame = __builtin_frame_address(0);
    __asm__ volatile("movl 16(%1), %0" : "=r"(permissions) : "r"(frame) : "memory");
    return fun_005cda16(path, uint32_t(flags), permissions);
}
