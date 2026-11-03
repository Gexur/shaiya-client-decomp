#include "extended96.h"
#include "../runtime/security.h"
#include <stddef.h>
namespace {
uint16_t load16(const void* p) {
    uint32_t x;
    __asm__ volatile("movzwl (%1),%0" : "=r"(x) : "r"(p) : "memory");
    return uint16_t(x);
}
uint32_t load32(const void* p) {
    uint32_t x;
    __asm__ volatile("movl (%1),%0" : "=r"(x) : "r"(p) : "memory");
    return x;
}
void store16(void* p, uint16_t x) {
    __asm__ volatile("movw %w1,(%0)" ::"r"(p), "r"(uint32_t(x)) : "memory");
}
void store32(void* p, uint32_t x) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(x) : "memory");
}
struct ProductStorage {
    uint8_t value[12];
    volatile uint32_t guard;
};
static_assert(offsetof(ProductStorage, guard) == 12);
void clear_value(uint8_t* p) {
    store32(p + 8, 0);
    store32(p + 4, 0);
    store32(p, 0);
}
bool zero_magnitude(const uint8_t* p) {
    return (load32(p + 8) & 0x7fffffffu) == 0 && load32(p + 4) == 0 && load32(p) == 0;
}
} // namespace
extern "C" int32_t fun_005e0491(uint32_t left, uint32_t right, uint32_t* output) {
    const uint32_t sum = left + right;
    const int32_t carry = sum < left || sum < right;
    store32(output, sum);
    return carry;
}
extern "C" int32_t fun_005e04b2(OriginalExtended96* value, const OriginalExtended96* other) {
    auto* p = reinterpret_cast<uint8_t*>(value);
    const auto* q = reinterpret_cast<const uint8_t*>(other);
    if (fun_005e0491(load32(p), load32(q), reinterpret_cast<uint32_t*>(p)) != 0) {
        if (fun_005e0491(load32(p + 4), 1, reinterpret_cast<uint32_t*>(p + 4)) != 0)
            store32(p + 8, load32(p + 8) + 1);
    }
    if (fun_005e0491(load32(p + 4), load32(q + 4), reinterpret_cast<uint32_t*>(p + 4)) != 0)
        store32(p + 8, load32(p + 8) + 1);
    return fun_005e0491(load32(p + 8), load32(q + 8), reinterpret_cast<uint32_t*>(p + 8));
}
extern "C" OriginalExtended96* fun_005e0510(OriginalExtended96* value) {
    auto* p = reinterpret_cast<uint8_t*>(value);
    const uint32_t low = load32(p), middle = load32(p + 4);
    store32(p, low << 1);
    const uint32_t high = load32(p + 8);
    store32(p + 4, (middle << 1) | (low >> 31));
    store32(p + 8, (high << 1) | (middle >> 31));
    return value;
}
extern "C" OriginalExtended96* fun_005e053e(OriginalExtended96* value) {
    auto* p = reinterpret_cast<uint8_t*>(value);
    const uint32_t high = load32(p + 8), middle = load32(p + 4);
    store32(p + 4, (middle >> 1) | (high << 31));
    const uint32_t low = load32(p);
    store32(p + 8, high >> 1);
    store32(p, (low >> 1) | (middle << 31));
    return value;
}
extern "C" void fun_005e0ca4(OriginalExtended96* value, const OriginalExtended96* other) {
    ProductStorage product{};
    product.guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&product.guard);
    auto* temporary = reinterpret_cast<uint8_t*>(&product);
    auto* first = reinterpret_cast<uint8_t*>(value);
    const auto* second = reinterpret_cast<const uint8_t*>(other);
    const uint16_t second_tag = load16(second + 10), first_tag = load16(first + 10);
    const uint16_t first_exponent = first_tag & 0x7fff, second_exponent = second_tag & 0x7fff;
    const uint16_t sign = (first_tag ^ second_tag) & 0x8000;
    uint16_t exponent = uint16_t(first_exponent + second_exponent);
    auto finish = [&]() {
        fun_005d0efa(product.guard ^ reinterpret_cast<uint32_t>(&product.guard));
    };
    auto overflow = [&]() {
        store32(first + 4, 0);
        store32(first, 0);
        store32(first + 8, (sign ? 0x80000000u : 0) + 0x7fff8000u);
    };
    if (first_exponent >= 0x7fff || second_exponent >= 0x7fff || exponent > 0xbffd) {
        overflow();
        finish();
        return;
    }
    if (exponent <= 0x3fbf) {
        clear_value(first);
        finish();
        return;
    }
    if (first_exponent == 0) {
        ++exponent;
        if (zero_magnitude(first)) {
            store16(first + 10, 0);
            finish();
            return;
        }
    }
    if (second_exponent == 0) {
        ++exponent;
        if (zero_magnitude(second)) {
            clear_value(first);
            finish();
            return;
        }
    }
    // Original triangular five-WORD convolution, not a replacement full160-bit
    // multiply: only these actual products/32-bit sums/carry-WORD writes occur.
    for (uint32_t outer = 0; outer < 5; ++outer) {
        for (uint32_t inner = 0; inner < 5 - outer; ++inner) {
            const uint32_t a = load16(first + 2 * (outer + inner));
            const uint32_t b = load16(second + 8 - 2 * inner);
            uint32_t sum;
            const int32_t carry = fun_005e0491(load32(temporary + 2 * outer), a * b, &sum);
            store32(temporary + 2 * outer, sum);
            if (carry)
                store16(temporary + 2 * outer + 4, uint16_t(load16(temporary + 2 * outer + 4) + 1));
        }
    }
    exponent = uint16_t(exponent + 0xc002);
    if (static_cast<int16_t>(exponent) > 0) {
        while ((temporary[11] & 0x80) == 0) {
            (void)fun_005e0510(reinterpret_cast<OriginalExtended96*>(temporary));
            --exponent;
            if (static_cast<int16_t>(exponent) <= 0)
                break;
        }
    }
    if (static_cast<int16_t>(exponent) <= 0) {
        --exponent;
        if (static_cast<int16_t>(exponent) < 0) {
            uint32_t shifts = uint16_t(0u - exponent), sticky = 0;
            exponent = 0;
            do {
                if ((temporary[0] & 1) != 0)
                    ++sticky;
                (void)fun_005e053e(reinterpret_cast<OriginalExtended96*>(temporary));
            } while (--shifts != 0);
            if (sticky)
                temporary[0] |= 1;
        }
    }
    if (load16(temporary) > 0x8000 || (load32(temporary) & 0x1ffffu) == 0x18000) {
        uint32_t lower = load32(temporary + 2), middle = load32(temporary + 6);
        uint16_t top = load16(temporary + 10);
        if (lower == 0xffffffffu) {
            lower = 0;
            if (middle == 0xffffffffu) {
                middle = 0;
                if (top == 0xffff) {
                    ++exponent;
                    top = 0x8000;
                } else
                    ++top;
            } else
                ++middle;
        } else
            ++lower;
        store32(temporary + 2, lower);
        store32(temporary + 6, middle);
        store16(temporary + 10, top);
    }
    if (exponent >= 0x7fff)
        overflow();
    else {
        store16(first, load16(temporary + 2));
        store32(first + 2, load32(temporary + 4));
        store32(first + 6, load32(temporary + 8));
        store16(first + 10, exponent | sign);
    }
    finish();
}
extern "C" void fun_005e0eda(OriginalExtended96* value, int32_t power, int32_t keep_guard) {
    ProductStorage temporary{};
    temporary.guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&temporary.guard);
    auto* scratch = reinterpret_cast<uint8_t*>(&temporary);
    uint32_t remaining = static_cast<uint32_t>(power);
    if (remaining != 0) {
        const OriginalExtended96* table = dat_0070f0b0;
        if (power < 0) {
            remaining = 0u - remaining;
            table = dat_0070f210;
        }
        if (keep_guard == 0)
            store16(value, 0);
        uint32_t row = 0;
        do {
            const uint32_t digit = remaining & 7;
            remaining = (remaining >> 3) | ((remaining & 0x80000000u) ? 0xe0000000u : 0);
            if (digit != 0) {
                const uint32_t address =
                    reinterpret_cast<uint32_t>(table) + (row * 7 + digit - 1) * 12;
                const auto* selected = reinterpret_cast<const uint8_t*>(address);
                if (load16(selected) >= 0x8000) {
                    store32(scratch, load32(selected));
                    store32(scratch + 4, load32(selected + 4));
                    store32(scratch + 8, load32(selected + 8));
                    store32(scratch + 2, load32(scratch + 2) - 1);
                    selected = scratch;
                }
                fun_005e0ca4(value, reinterpret_cast<const OriginalExtended96*>(selected));
            }
            ++row;
        } while (remaining != 0);
    }
    fun_005d0efa(temporary.guard ^ reinterpret_cast<uint32_t>(&temporary.guard));
}
