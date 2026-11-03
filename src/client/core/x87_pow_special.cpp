#include "core/x87_pow_special.h"
#include "runtime/floating_text.h"

extern "C" {
extern const uint64_t dat_006cf0a0 = UINT64_C(0x3ff0000000000000);
extern const uint64_t dat_006cf4a0 = UINT64_C(0x4000000000000000);
extern const uint64_t dat_0070ec08 = UINT64_C(0x7ff0000000000000);
extern const uint64_t dat_0070ec10 = UINT64_C(0xfff8000000000000);
extern const uint64_t dat_0070ec28 = UINT64_C(0x8000000000000000);
}
namespace {
inline uint64_t words(double value) {
    uint64_t bits;
    __builtin_memcpy(&bits, &value, 8);
    return bits;
}
inline double rounded_store(double value) {
    double result;
    __asm__ __volatile__("fldl %1\n\tfstpl %0" : "=m"(result) : "m"(value) : "st");
    return result;
}
inline uint16_t compare_zero(double value) {
    uint16_t status;
    __asm__ __volatile__("fldl %1\n\tfldl %2\n\tfucompp\n\tfnstsw %%ax"
                         : "=a"(status)
                         : "m"(dat_006bb5f0), "m"(value)
                         : "st", "st(1)", "cc");
    return status;
}
inline uint16_t compare_one(double value) {
    uint16_t status;
    __asm__ __volatile__("fldl %1\n\tfcompl %2\n\tfnstsw %%ax"
                         : "=a"(status)
                         : "m"(value), "m"(dat_006cf0a0)
                         : "st", "cc");
    return status;
}
inline uint16_t compare_zero_ordered(double value) {
    uint16_t status;
    __asm__ __volatile__("fldl %1\n\tfcompl %2\n\tfnstsw %%ax"
                         : "=a"(status)
                         : "m"(value), "m"(dat_006bb5f0)
                         : "st", "cc");
    return status;
}
inline uint16_t compare_original(double value, double other) {
    uint16_t status;
    // Original5db6b0/5db6b4: value below other, then FUCOMPP compares other.
    __asm__ __volatile__("fldl %1\n\tfldl %2\n\tfucompp\n\tfnstsw %%ax"
                         : "=a"(status)
                         : "m"(value), "m"(other)
                         : "st", "st(1)", "cc");
    return status;
}
inline bool parity_even(uint8_t value) {
    return __builtin_parity(static_cast<unsigned>(value)) == 0;
}
inline long double load_words(const uint64_t& value) {
    long double result;
    __asm__ __volatile__("fldl %1" : "=t"(result) : "m"(value));
    return result;
}
inline long double zero() {
    long double result;
    __asm__ __volatile__("fldz" : "=t"(result));
    return result;
}
inline long double one() {
    long double result;
    __asm__ __volatile__("fld1" : "=t"(result));
    return result;
}
inline void store(double* target, long double value) {
    __asm__ __volatile__("fstpl %0" : "=m"(*target) : "t"(value) : "st");
}
inline double store_local(long double value) {
    double result;
    store(&result, value);
    return result;
}
inline long double divide_two(double value) {
    long double result;
    __asm__ __volatile__("fldl %1\n\tfdivl %2" : "=t"(result) : "m"(value), "m"(dat_006cf4a0));
    return result;
}
inline long double negate(long double value) {
    __asm__ __volatile__("fchs" : "+t"(value));
    return value;
}
} // namespace

// Original005d8053..005d80ae. Entire classification is integer bit inspection.
extern "C" uint32_t __cdecl FUN_005d8053(double value) {
    const uint64_t raw = words(value);
    const uint32_t low = raw, high = raw >> 32;
    if (high == 0x7ff00000u && low == 0)
        return 1;
    if (high == 0xfff00000u && low == 0)
        return 2;
    const uint32_t top = static_cast<uint32_t>(raw >> 48) & 0x7ff8u;
    if (top == 0x7ff8u)
        return 3;
    if (top == 0x7ff0u && ((high & 0x7ffffu) != 0 || low != 0))
        return 4;
    return 0;
}

// Original005ced48..005cede4. Preserve the real FLD/FSTP before subtype call.
extern "C" uint32_t __cdecl FUN_005ced48(double value) {
    const uint64_t raw = words(value);
    const uint32_t top = raw >> 48;
    if ((top & 0x7ff0u) == 0x7ff0u) {
        const uint32_t subtype = FUN_005d8053(rounded_store(value));
        if (subtype == 1)
            return 0x200;
        if (subtype == 2)
            return 4;
        if (subtype == 3)
            return 2;
        return 1;
    }
    const bool negative = (top & 0x8000u) != 0;
    if ((top & 0x7ff0u) == 0 && (raw & UINT64_C(0xfffffffffffff)) != 0)
        return negative ? 0x10 : 0x80;
    const uint8_t status = compare_zero(value) >> 8;
    if (!parity_even(status & 0x44))
        return negative ? 0x20 : 0x40;
    return negative ? 8 : 0x100;
}

// Original005decc1..005decd2. FRNDINT follows the incoming FPCW, with an actual
// double store/reload boundary before returning ST0; no C/C++ rounding API.
extern "C" long double __cdecl FUN_005decc1(double value) {
    double rounded;
    long double result;
    __asm__ __volatile__("fldl %2\n\tfrndint\n\tfstpl %1\n\tfldl %1"
                         : "=t"(result), "=m"(rounded)
                         : "m"(value));
    return result;
}

// Original005db687..005db6f5. Returns0(noninteger),1(odd),2(even), using real
// classifier/FRNDINT callees and original float-store/comparison boundaries.
extern "C" uint32_t __cdecl FUN_005db687(double value) {
    if ((FUN_005ced48(rounded_store(value)) & 0x90u) != 0)
        return 0;
    const double rounded = store_local(FUN_005decc1(rounded_store(value)));
    if (parity_even(static_cast<uint8_t>(compare_original(value, rounded) >> 8) & 0x44))
        return 0;
    const double half = store_local(divide_two(value));
    const long double integral_half = FUN_005decc1(rounded_store(half));
    // Original5db6d4 returns integral-half in ST0, then FLD half/FUCOMPP.
    uint16_t status;
    __asm__ __volatile__("fldl %2\n\tfucompp\n\tfnstsw %%ax"
                         : "=a"(status)
                         : "t"(integral_half), "m"(half)
                         : "st", "st(1)", "cc");
    return parity_even(static_cast<uint8_t>(status >> 8) & 0x44) ? 1 : 2;
}

// Original005db6f5..005db857. Exceptional original base/exponent handling.
extern "C" int32_t __cdecl FUN_005db6f5(double base, double exponent, double* output) {
    double absolute;
    uint16_t status;
    // Original FCOM/FCHS/FSTP sequence (FCOM is intentionally not FUCOM).
    __asm__ __volatile__(
        "fldl %2\n\tfcoml %3\n\tfnstsw %%ax\n\ttestb $5,%%ah\n\tjp 1f\n\tfchs\n1:\n\tfstpl %1"
        : "=a"(status), "=m"(absolute)
        : "m"(base), "m"(dat_006bb5f0)
        : "st", "cc");
    const uint64_t base_words = words(base), exponent_words = words(exponent);
    const uint32_t exponent_high = exponent_words >> 32;
    uint32_t fallback = 0;
    long double result;
    if (exponent_high == 0x7ff00000u && static_cast<uint32_t>(exponent_words) == 0) {
        status = compare_one(absolute);
        if (((status >> 8) & 0x41) == 0)
            goto positive_infinity;
        status = compare_one(absolute);
        if (!parity_even(static_cast<uint8_t>(status >> 8) & 5))
            goto positive_zero;
        goto indeterminate;
    }
    if (exponent_high == 0xfff00000u && static_cast<uint32_t>(exponent_words) == 0) {
        status = compare_one(absolute);
        if (((status >> 8) & 0x41) == 0)
            goto positive_zero;
        status = compare_one(absolute);
        if (parity_even(static_cast<uint8_t>(status >> 8) & 5))
            goto indeterminate;
        goto positive_infinity;
    }
    if ((base_words >> 32) == 0x7ff00000u) {
        if (static_cast<uint32_t>(base_words) != 0)
            return 0;
        status = compare_zero_ordered(exponent);
        if (((status >> 8) & 0x41) == 0)
            goto positive_infinity;
        status = compare_zero_ordered(exponent);
        if (parity_even(static_cast<uint8_t>(status >> 8) & 5))
            goto positive_one;
        goto positive_zero;
    }
    if ((base_words >> 32) != 0xfff00000u || static_cast<uint32_t>(base_words) != 0)
        return 0;
    {
        const uint32_t type = FUN_005db687(rounded_store(exponent));
        status = compare_zero_ordered(exponent);
        if (((status >> 8) & 0x41) == 0) {
            result = load_words(dat_0070ec08);
            if (type == 1)
                result = negate(result);
            exponent = store_local(result); // original5db81c/5db81f
            const uint64_t reloaded = words(exponent);
            result = load_words(reloaded);
            goto write_result;
        }
        status = compare_zero_ordered(exponent);
        if (parity_even(static_cast<uint8_t>(status >> 8) & 5))
            goto positive_one;
        result = type == 1 ? load_words(dat_0070ec28) : zero();
        exponent = store_local(result); // original5db843/5db846
        const uint64_t reloaded = words(exponent);
        result = load_words(reloaded);
        goto write_result;
    }
indeterminate:;
    result = load_words(dat_0070ec10);
    fallback = 1;
    goto write_result;
positive_infinity:;
    result = load_words(dat_0070ec08);
    goto write_result;
positive_zero:;
    result = zero();
    goto write_result;
positive_one:;
    result = one();
write_result:;
    store(output, result);
    return static_cast<int32_t>(fallback);
}
