#include "core/fp_normalize.h"
#include "runtime/floating_text.h"
namespace {
inline uint64_t words(double value) {
    uint64_t result;
    __builtin_memcpy(&result, &value, 8);
    return result;
}
inline double from_words(uint64_t value) {
    double result;
    __builtin_memcpy(&result, &value, 8);
    return result;
}
inline double round_copy(double value) {
    double result;
    __asm__ __volatile__("fldl %1\n\tfstpl %0" : "=m"(result) : "m"(value) : "st", "memory");
    return result;
}
inline double store_double(long double value) {
    double result;
    __asm__ __volatile__("fstpl %0" : "=m"(result) : "t"(value) : "st");
    return result;
}
inline long double load_double(double value) {
    long double result;
    __asm__ __volatile__("fldl %1" : "=t"(result) : "m"(value));
    return result;
}
inline bool even_parity(uint8_t value) {
    return __builtin_parity(static_cast<unsigned>(value)) == 0;
}
inline uint16_t unordered_zero(double value) {
    uint16_t status;
    __asm__ __volatile__("fldl %1\n\tfldl %2\n\tfucompp\n\tfnstsw %%ax"
                         : "=a"(status)
                         : "m"(dat_006bb5f0), "m"(value)
                         : "st", "st(1)", "cc");
    return status;
}
inline uint16_t ordered_zero(double value) {
    uint16_t status;
    __asm__ __volatile__("fldl %1\n\tfcompl %2\n\tfnstsw %%ax"
                         : "=a"(status)
                         : "m"(value), "m"(dat_006bb5f0)
                         : "st", "cc");
    return status;
}
} // namespace

// Original005d8029..005d8053: the input high WORD is read from the original
// argument, while the other words come from the actual FLD/FSTP-rounded copy.
// This distinction remains observable for signaling NaN inputs.
extern "C" long double __cdecl FUN_005d8029(double value, int32_t exponent) {
    const uint16_t original_top = static_cast<uint16_t>(words(value) >> 48);
    uint64_t rounded = words(round_copy(value));
    const uint32_t encoded = (static_cast<uint32_t>(exponent) + 0x3feu) << 4;
    const uint16_t top = static_cast<uint16_t>(encoded | (original_top & 0x800fu));
    rounded = (rounded & UINT64_C(0x0000ffffffffffff)) | (uint64_t(top) << 48);
    return load_double(from_words(rounded));
}

// Original005d80ae..005d816a, including the exact subnormal shift loop and
// actual special/zero behavior. No standard-library frexp substitute.
extern "C" long double __cdecl FUN_005d80ae(double value, int32_t* output) {
    uint64_t raw = words(value);
    int32_t exponent;
    long double mantissa;
    if (!even_parity(static_cast<uint8_t>(unordered_zero(value) >> 8) & 0x44)) {
        exponent = 0;
        __asm__ __volatile__("fldz" : "=t"(mantissa));
    } else if ((raw & UINT64_C(0x7ff0000000000000)) == 0 &&
               (raw & UINT64_C(0x000fffffffffffff)) != 0) {
        const bool negative = !even_parity(static_cast<uint8_t>(ordered_zero(value) >> 8) & 5);
        exponent = -1021;
        while ((raw & UINT64_C(0x0010000000000000)) == 0) {
            raw <<= 1;
            --exponent;
        }
        raw &= ~UINT64_C(0x0010000000000000);
        if (negative)
            raw |= UINT64_C(0x8000000000000000);
        mantissa = FUN_005d8029(round_copy(from_words(raw)), 0);
    } else {
        mantissa = FUN_005d8029(round_copy(value), 0);
        exponent = static_cast<int32_t>((raw >> 52) & 0x7ff) - 0x3fe;
    }
    const double rounded = store_double(mantissa);
    long double result;
    // Original005d8160/005d8163/005d8166: store rounded value, reload ST0,
    // then write exponent. Keep the real output-pointer write after the FLD.
    __asm__ __volatile__("fldl %1\n\tmovl %2,(%3)"
                         : "=t"(result)
                         : "m"(rounded), "r"(exponent), "r"(output)
                         : "memory");
    return result;
}
