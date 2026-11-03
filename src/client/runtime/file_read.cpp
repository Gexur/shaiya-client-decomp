#include "file_ops.h"
extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) ReadFile(void*, void*, uint32_t, uint32_t*,
                                                                void*);
__declspec(dllimport) uint32_t __attribute__((stdcall)) GetLastError();
}
extern "C" int32_t fun_005ce360(int32_t descriptor, char* buffer, uint32_t count) {
    if (!count || (file_io_entry(descriptor)->flags & 2u))
        return 0;
    uint32_t prefix = 0;
    char* destination = buffer;
    if ((file_io_entry(descriptor)->flags & 0x48u) && file_io_entry(descriptor)->lookahead != 10) {
        --count;
        *destination++ = char(file_io_entry(descriptor)->lookahead);
        prefix = 1;
        file_io_entry(descriptor)->lookahead = 10;
    }
    uint32_t amount;
    if (!ReadFile(file_io_entry(descriptor)->handle, destination, count, &amount, nullptr)) {
        const uint32_t error = GetLastError();
        if (error == 5) {
            *fun_005d589a() = 9;
            *fun_005d58a3() = 5;
        } else if (error == 109)
            return 0;
        else
            fun_005d58ac(error);
        return -1;
    }
    if (!(file_io_entry(descriptor)->flags & 0x80u))
        return int32_t(prefix + amount);
    if (amount && *buffer == '\n')
        file_io_entry(descriptor)->flags |= 4u;
    else
        file_io_entry(descriptor)->flags &= 0xfbu;
    char* const end = buffer + prefix + amount;
    char* input = buffer;
    char* output = buffer;
    while (input < end) {
        const char value = *input;
        if (uint8_t(value) == 0x1a) {
            if (!(file_io_entry(descriptor)->flags & 0x40u))
                file_io_entry(descriptor)->flags |= 2u;
            break;
        }
        if (value != '\r') {
            *output++ = value;
            ++input;
            continue;
        }
        ++input;
        if (input < end) {
            if (*input == '\n') {
                ++input;
                *output++ = '\n';
            } else
                *output++ = '\r';
            continue;
        }
        unsigned char peek_storage[1];
        const int32_t success =
            ReadFile(file_io_entry(descriptor)->handle, peek_storage, 1, &amount, nullptr);
        if ((!success && GetLastError() != 0) || !amount) {
            *output++ = '\r';
            continue;
        }
        // The original can read an unwritten stack byte when ReadFile fails but
        // LastError is zero and its prior byte count remains nonzero. A raw
        // byte read preserves that boundary without promoting indeterminate C++.
        uint32_t next;
        __asm__ volatile("movzbl %1, %0" : "=r"(next) : "m"(peek_storage[0]) : "memory");
        if (file_io_entry(descriptor)->flags & 0x48u) {
            if (next == 10)
                *output++ = '\n';
            else {
                *output++ = '\r';
                file_io_entry(descriptor)->lookahead = uint8_t(next);
            }
        } else if (output == buffer && next == 10)
            *output++ = '\n';
        else {
            fun_005ce21f(descriptor, -1, -1, 1);
            if (next != 10)
                *output++ = '\r';
        }
    }
    return int32_t(output - buffer);
}
extern "C" int32_t _read(int32_t descriptor, void* buffer, uint32_t count) {
    return fun_005ce53d(descriptor, buffer, count);
}
