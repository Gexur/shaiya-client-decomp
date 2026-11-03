#include "core/fp_raise.h"
#include "core/fp_exception_support.h"
#include <windows.h>

namespace {
// Several fields deliberately retain original private scratch bits. A real
// MOVL reads those bytes without a C++ indeterminate-value promotion.
inline uint32_t read_word(const unsigned char* record, uint32_t offset) {
    uint32_t result;
    __asm__ __volatile__("movl (%1),%0" : "=r"(result) : "r"(record + offset) : "memory");
    return result;
}
inline void write_word(unsigned char* record, uint32_t offset, uint32_t value) {
    __asm__ __volatile__("movl %1,(%0)" ::"r"(record + offset), "r"(value) : "memory");
}
inline void replace_bits(unsigned char* record, uint32_t offset, uint32_t value, uint32_t mask) {
    const uint32_t previous = read_word(record, offset);
    write_word(record, offset, previous ^ ((value ^ previous) & mask));
}
inline void copy_double(void* destination, const void* source) {
    __asm__ __volatile__("fldl (%1)\n\tfstpl (%0)" ::"r"(destination), "r"(source)
                         : "st", "memory");
}
} // namespace

// Original005d816a..005d840f. Offsets below are actual byte offsets in the
// caller's IEEE scratch record, not a guessed host CRT structure layout.
extern "C" void __cdecl FUN_005d816a(void* opaque, uint32_t* control, uint32_t flags,
                                     uint32_t operation, double* argument, double* result) {
    auto* record = static_cast<unsigned char*>(opaque);
    write_word(record, 4, 0);
    write_word(record, 8, 0);
    write_word(record, 12, 0);
    uint32_t exception_code = flags;
    if (flags & 0x10u) {
        write_word(record, 4, read_word(record, 4) | 1u);
        exception_code = 0xc000008fu;
    }
    if (flags & 2u) {
        write_word(record, 4, read_word(record, 4) | 2u);
        exception_code = 0xc0000093u;
    }
    if (flags & 1u) {
        write_word(record, 4, read_word(record, 4) | 4u);
        exception_code = 0xc0000091u;
    }
    if (flags & 4u) {
        write_word(record, 4, read_word(record, 4) | 8u);
        exception_code = 0xc000008eu;
    }
    if (flags & 8u) {
        write_word(record, 4, read_word(record, 4) | 0x10u);
        exception_code = 0xc0000090u;
    }
    replace_bits(record, 8, ~(*control << 4), 0x10);
    replace_bits(record, 8, ~(*control << 1), 8);
    replace_bits(record, 8, ~(*control >> 1), 4);
    replace_bits(record, 8, ~(*control >> 3), 2);
    replace_bits(record, 8, ~(*control >> 5), 1);
    const uint32_t status = static_cast<uint32_t>(FUN_005d8961());
    if (status & 1u)
        write_word(record, 12, read_word(record, 12) | 0x10u);
    if (status & 4u)
        write_word(record, 12, read_word(record, 12) | 8u);
    if (status & 8u)
        write_word(record, 12, read_word(record, 12) | 4u);
    if (status & 0x10u)
        write_word(record, 12, read_word(record, 12) | 2u);
    if (status & 0x20u)
        write_word(record, 12, read_word(record, 12) | 1u);
    switch (*control & 0xc00u) {
    case 0:
        write_word(record, 0, read_word(record, 0) & ~3u);
        break;
    case 0x400:
        write_word(record, 0, (read_word(record, 0) & ~2u) | 1u);
        break;
    case 0x800:
        write_word(record, 0, (read_word(record, 0) & ~1u) | 2u);
        break;
    case 0xc00:
        write_word(record, 0, read_word(record, 0) | 3u);
        break;
    }
    switch (*control & 0x300u) {
    case 0:
        write_word(record, 0, (read_word(record, 0) & 0xffffffebu) | 8u);
        break;
    case 0x200:
        write_word(record, 0, (read_word(record, 0) & 0xffffffe7u) | 4u);
        break;
    case 0x300:
        write_word(record, 0, read_word(record, 0) & 0xffffffe3u);
        break;
    }
    replace_bits(record, 0, operation << 5, 0x1ffe0);
    write_word(record, 32, read_word(record, 32) | 1u);
    write_word(record, 32, (read_word(record, 32) & 0xffffffe3u) | 2u);
    copy_double(record + 16, argument);
    write_word(record, 96, read_word(record, 96) | 1u);
    write_word(record, 96, (read_word(record, 96) & 0xffffffe3u) | 2u);
    copy_double(record + 80, result);
    FUN_005d896c();
    ULONG_PTR exception_argument = reinterpret_cast<ULONG_PTR>(record);
    RaiseException(exception_code, 0, 1, &exception_argument);
    // The original passes &param_1, so a resumed exception handler can also
    // change the record pointer itself. Reload that exact pointer afterward.
    record = reinterpret_cast<unsigned char*>(exception_argument);
    if (read_word(record, 8) & 0x10u)
        *control &= ~1u;
    if (read_word(record, 8) & 8u)
        *control &= ~4u;
    if (read_word(record, 8) & 4u)
        *control &= ~8u;
    if (read_word(record, 8) & 2u)
        *control &= ~0x10u;
    if (read_word(record, 8) & 1u)
        *control &= ~0x20u;
    switch (read_word(record, 0) & 3u) {
    case 0:
        *control &= 0xfffff3ffu;
        break;
    case 1:
        *control = (*control & 0xfffff7ffu) | 0x400u;
        break;
    case 2:
        *control = (*control & 0xfffffbffu) | 0x800u;
        break;
    case 3:
        reinterpret_cast<unsigned char*>(control)[1] |= 0x0c;
        break;
    }
    switch ((read_word(record, 0) >> 2) & 7u) {
    case 0:
        *control = (*control & 0xfffff3ffu) | 0x300u;
        break;
    case 1:
        *control = (*control & 0xfffff3ffu) | 0x200u;
        break;
    case 2:
        *control &= 0xfffff3ffu;
        break;
    }
    copy_double(result, record + 80);
}
