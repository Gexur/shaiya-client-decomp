#include "fp_exception_support.h"
#include "core/math_error.h"
#include "runtime/locks.h"
#include "runtime/security.h"

extern "C" {
uint32_t dat_0070ef40 = 0x2694; // Exact original file-backed DWORD0070ef40.
}
namespace {
struct WordBytes {
    unsigned char bytes[4];
};
inline uint32_t original_private_word(const unsigned char* pointer) {
    uint32_t value;
    __asm__ __volatile__("movl %1,%0"
                         : "=r"(value)
                         : "m"(*reinterpret_cast<const WordBytes*>(pointer)));
    return value;
}
inline void write_private_word(unsigned char* pointer, uint32_t value) {
    __asm__ __volatile__("movl %1,%0"
                         : "=m"(*reinterpret_cast<WordBytes*>(pointer))
                         : "r"(value)
                         : "memory");
}
} // namespace

// Original005d8633..005d865b, exact supported mathematical error kinds.
extern "C" __attribute__((noinline)) uint32_t __cdecl FUN_005d8633(int32_t kind) {
    if (kind == 1 || kind == 2 || kind == 3) {
        auto* error = fun_005d589a();
        *error = kind == 1 ? 0x21 : 0x22;
        return reinterpret_cast<uint32_t>(error);
    }
    return static_cast<uint32_t>(kind);
}

// Original005dea67..005deb63, normal-return control/data flow. The opaque
// IEEE record keeps original private bytes, with explicit machine loads for
// the two read/modify/write flags fields; no C++ indeterminate-value promotion.
extern "C" uint32_t __cdecl FUN_005dea67(uint32_t operation, PowerMathException* exception,
                                         uint16_t* saved_word) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    uint32_t control = *saved_word;
    alignas(16) unsigned char ieee_record[124];
    uint32_t flags = 0;
    bool handle = true;
    switch (exception->kind) {
    case 1:
    case 5:
        flags = 8;
        break;
    case 2:
        flags = 4;
        break;
    case 3:
        flags = 0x11;
        break;
    case 4:
        flags = 0x12;
        break;
    case 7:
        exception->kind = 1;
        handle = false;
        break;
    case 8:
        flags = 0x10;
        break;
    default:
        handle = false;
        break;
    }
    if (handle && FUN_005d840f(flags, &exception->result, control) == 0) {
        uint32_t bits = original_private_word(ieee_record + 64);
        if (operation == 0x10 || operation == 0x16 || operation == 0x1d) {
            __asm__ __volatile__("fldl %1\n\tfstpl %0"
                                 : "=m"(*reinterpret_cast<double*>(ieee_record + 48))
                                 : "m"(exception->argument1)
                                 : "st", "memory");
            bits = (bits & 0xffffffe3u) | 3u;
        } else
            bits &= 0xfffffffeu;
        write_private_word(ieee_record + 64, bits);
        FUN_005d816a(ieee_record, &control, flags, operation, &exception->argument0,
                     &exception->result);
    }
    FUN_005d8978(control, 0xffff);
    if (exception->kind != 8 && dat_0070ef40 == 0) {
        const uint32_t handled = static_cast<uint32_t>(FUN_005decbe(exception));
        if (handled != 0) {
            fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
            return handled;
        }
    }
    const uint32_t result = FUN_005d8633(static_cast<int32_t>(exception->kind));
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return result;
}
