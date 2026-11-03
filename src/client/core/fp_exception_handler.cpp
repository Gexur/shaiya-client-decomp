#include "core/fp_exception_handler.h"
#include "core/fp_exception_support.h"
#include "core/fp_normalize.h"
#include "runtime/floating_text.h"
extern "C" {
extern const uint64_t dat_0070ec08; // Canonical original definition in x87_pow_special.cpp.
extern const uint64_t dat_0070ec18 = UINT64_C(0x7fefffffffffffff);
}
namespace {
inline uint64_t words(const double& value) {
    uint64_t result;
    __builtin_memcpy(&result, &value, 8);
    return result;
}
inline double value(uint64_t raw) {
    double result;
    __builtin_memcpy(&result, &raw, 8);
    return result;
}
inline uint16_t compare_zero(const double* input, bool ordered) {
    uint16_t status;
    if (ordered)
        __asm__ __volatile__("fldl %1\n\tfcompl %2\n\tfnstsw %%ax"
                             : "=a"(status)
                             : "m"(*input), "m"(dat_006bb5f0)
                             : "st", "cc");
    else
        __asm__ __volatile__("fldl %1\n\tfldl %2\n\tfucompp\n\tfnstsw %%ax"
                             : "=a"(status)
                             : "m"(dat_006bb5f0), "m"(*input)
                             : "st", "st(1)", "cc");
    return status;
}
inline long double load(const uint64_t& raw) {
    long double result;
    __asm__ __volatile__("fldl %1" : "=t"(result) : "m"(raw));
    return result;
}
inline long double negate(long double number) {
    __asm__ __volatile__("fchs" : "+t"(number));
    return number;
}
inline double rounded(long double number) {
    double result;
    __asm__ __volatile__("fstpl %0" : "=m"(result) : "t"(number) : "st");
    return result;
}
inline void copy_to(double* output, const double& input) {
    __asm__ __volatile__("fldl %1\n\tfstpl %0" : "=m"(*output) : "m"(input) : "st", "memory");
}
inline bool parity_even(uint8_t bits) {
    return __builtin_parity(static_cast<unsigned>(bits)) == 0;
}
} // namespace

// Original005d840f..005d8633: exact exception priority, result adjustment,
// underflow shift/sticky-bit behavior and the real flag-raising callee.
extern "C" int32_t __cdecl FUN_005d840f(uint32_t flags, double* result, uint32_t control) {
    uint32_t remaining = flags & 0x1fu;
    if ((flags & 8u) != 0 && (control & 1u) != 0) {
        FUN_005d899c(1);
        remaining &= ~8u;
    } else if ((flags & 4u) != 0 && (control & 4u) != 0) {
        FUN_005d899c(4);
        remaining &= ~4u;
    } else if ((flags & 1u) != 0 && (control & 8u) != 0) {
        FUN_005d899c(8);
        const uint32_t mode = control & 0xc00;
        const uint16_t status = compare_zero(result, true);
        const bool positive = ((status >> 8) & 0x41) == 0;
        const uint64_t* bound;
        bool negative = false;
        if (mode == 0) {
            bound = &dat_0070ec08;
            negative = !positive;
        } else if (mode == 0x400) {
            bound = positive ? &dat_0070ec18 : &dat_0070ec08;
            negative = !positive;
        } else if (mode == 0x800) {
            bound = positive ? &dat_0070ec08 : &dat_0070ec18;
            negative = !positive;
        } else {
            bound = &dat_0070ec18;
            negative = !positive;
        }
        long double replacement = load(*bound);
        if (negative)
            replacement = negate(replacement);
        const double stored = rounded(replacement);
        copy_to(result, stored);
        remaining &= ~1u;
    } else if ((flags & 2u) != 0 && (control & 0x10u) != 0) {
        bool sticky = (flags & 0x10u) != 0;
        const uint16_t status = compare_zero(result, false);
        if (parity_even(static_cast<uint8_t>(status >> 8) & 0x44)) {
            int32_t exponent;
            double argument;
            copy_to(&argument, *result); // original FLD/FSTP outgoing argument
            const double component = rounded(FUN_005d80ae(argument, &exponent));
            exponent = static_cast<int32_t>(static_cast<uint32_t>(exponent) - 0x600u);
            double replacement;
            if (exponent < -1074) {
                long double zero_product;
                __asm__ __volatile__("fldl %1\n\tfmull %2"
                                     : "=t"(zero_product)
                                     : "m"(component), "m"(dat_006bb5f0));
                replacement = rounded(zero_product);
                sticky = true;
            } else {
                const bool negative =
                    !parity_even(static_cast<uint8_t>(compare_zero(&component, true) >> 8) & 5);
                uint64_t encoded = (words(component) & UINT64_C(0x000fffffffffffff)) |
                                   UINT64_C(0x0010000000000000);
                if (exponent < -1021) {
                    uint32_t count = static_cast<uint32_t>(-1021 - exponent);
                    do {
                        if ((encoded & 1) != 0 && !sticky)
                            sticky = true;
                        encoded >>= 1;
                    } while (--count != 0);
                }
                if (negative)
                    replacement = rounded(negate(load(encoded)));
                else
                    replacement = value(encoded);
            }
            copy_to(result, replacement);
        } else
            sticky = true; // original zero result takes this path unconditionally.
        if (sticky)
            FUN_005d899c(0x10);
        remaining &= ~2u;
    }
    if ((flags & 0x10u) != 0 && (control & 0x20u) != 0) {
        FUN_005d899c(0x20);
        remaining &= ~0x10u;
    }
    return remaining == 0 ? 1 : 0;
}
