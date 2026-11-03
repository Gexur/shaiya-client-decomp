#include "bigint.h"

// Partial source recovery of original005861C0. Every unresolved operation names
// its actual original callee; there is no host pow(), replacement bigint, or
// success path for an unimplemented dependency. The ordinary source can compile
// into the recovery archive, but the full dependency closure is not yet linked.
namespace {
#include "bigint_powmod_tables.inc"

uint32_t original_leading_zero_count(uint32_t value) {
    uint32_t shift = value < 0x10000 ? (value < 0x100 ? 1u : 9u) : (value < 0x1000000 ? 17u : 25u);
    // Preserve the table's original value at zero too; do not silently replace
    // this sequence with a compiler builtin having a different zero-input rule.
    return 33u - leading_zero_table[value >> shift] - shift;
}

void copy_limbs(uint32_t* destination, const uint32_t* source, uint32_t count) {
    if (count != 0)
        do {
            *destination++ = *source++;
        } while (--count != 0);
}

void zero_limbs(uint32_t* destination, uint32_t count) {
    if (count != 0)
        do {
            *destination++ = 0;
        } while (--count != 0);
}

uint32_t normalized_size(const uint32_t* limbs, uint32_t count) {
    while (int32_t(count) > 0 && limbs[count - 1] == 0)
        --count;
    return count;
}
} // namespace

extern "C" void fun_005861c0(BigInt* output, const BigInt* base, const BigInt* exponent,
                             const BigInt* modulus) {
    int32_t count = modulus->signed_size;
    const uint32_t* divisor = modulus->limbs;
    if (count < 0)
        count = int32_t(0u - uint32_t(count));
    if (count == 0)
        fun_00589580();
    uint32_t exponent_count = uint32_t(exponent->signed_size);
    if (int32_t(exponent_count) < 1) {
        if (exponent_count == 0) {
            output->signed_size = count == 1 && divisor[0] == 1 ? 0 : 1;
            output->limbs[0] = 1;
            return;
        }
    }
    BigInt inverse;
    if (int32_t(exponent_count) < 0) {
        inverse.capacity = count + 1;
        inverse.limbs = static_cast<uint32_t*>(__builtin_alloca(uint32_t(count + 1) * 4));
        if (fun_00586d80(&inverse, base, modulus) == 0)
            fun_00589580();
        base = &inverse;
        exponent_count = 0u - exponent_count;
    }
    bool montgomery = count < 125 && (divisor[0] & 1) != 0;
    uint32_t reduction_parameter;
    if (montgomery) {
        uint32_t word = divisor[0];
        uint32_t approximation = odd_inverse_table[(word >> 1) & 127];
        approximation = (2u - approximation * word) * approximation;
        reduction_parameter = 0u - (2u - approximation * word) * approximation;
    } else {
        reduction_parameter = original_leading_zero_count(divisor[count - 1]);
        if (reduction_parameter != 0) {
            uint32_t* normalized = static_cast<uint32_t*>(__builtin_alloca(uint32_t(count) * 4));
            fun_00587480(normalized, divisor, uint32_t(count), reduction_parameter);
            divisor = normalized;
        }
    }
    uint32_t leading = original_leading_zero_count(exponent->limbs[exponent_count - 1]);
    uint32_t target_bits = (exponent_count * 32 - leading) * 2;
    uint32_t window = 1, power = 2;
    if (target_bits > 12) {
        do {
            ++window;
            power *= 2;
        } while (((window + 3) * window + 2) * power < target_bits);
    }
    uint32_t* product = static_cast<uint32_t*>(__builtin_alloca(uint32_t(count) * 8 + 4));
    uint32_t* quotient = static_cast<uint32_t*>(__builtin_alloca(uint32_t(count) * 4 + 4));
    uint32_t entries = power / 2;
    uint32_t table_bytes = entries * uint32_t(count) * 4;
    uint32_t* odd_powers = static_cast<uint32_t*>(dat_0070c0d0(table_bytes));
    int32_t base_count_signed = base->signed_size;
    uint32_t base_count = uint32_t(base_count_signed < 0 ? int32_t(0u - uint32_t(base_count_signed))
                                                         : base_count_signed);
    const uint32_t* base_limbs = base->limbs;
    bool reduce_base =
        int32_t(base_count) > count ||
        (base_count == uint32_t(count) && fun_00587660(base_limbs, divisor, count) >= 0);
    if (reduce_base) {
        if (montgomery) {
            fun_00586b90(product + count, base_limbs, int32_t(base_count), divisor, count);
            zero_limbs(product, uint32_t(count));
            fun_00588c30(quotient, odd_powers, 0, product, count * 2, divisor, count);
        } else {
            fun_00586b90(odd_powers, base_limbs, int32_t(base_count), divisor, count);
        }
    } else if (montgomery) {
        zero_limbs(product, uint32_t(count));
        copy_limbs(product + count, base_limbs, base_count);
        zero_limbs(product + count + base_count, uint32_t(count) - base_count);
        fun_00588c30(quotient, odd_powers, 0, product, count * 2, divisor, count);
    } else {
        copy_limbs(odd_powers, base_limbs, base_count);
        zero_limbs(odd_powers + base_count, uint32_t(count) - base_count);
    }
    uint32_t* result = static_cast<uint32_t*>(__builtin_alloca(uint32_t(count) * 4));
    // Repeated original reduce calls share the exact scratch and quotient arrays.
    auto reduce_product = [&](uint32_t* destination) {
        if (montgomery)
            fun_00586ae0(destination, divisor, count, reduction_parameter, product);
        else
            fun_00588c30(quotient, destination, 0, product, count * 2, divisor, count);
    };
    auto square_result = [&]() {
        fun_00586f70(product, result, count);
        reduce_product(result);
    };
    fun_00586f70(product, odd_powers, count);
    reduce_product(result);
    for (uint32_t i = 1; i < entries; ++i) {
        fun_00588b40(product, odd_powers + (i - 1) * uint32_t(count), result, count);
        reduce_product(odd_powers + i * uint32_t(count));
    }
    uint32_t exponent_index = exponent_count - 1;
    const uint32_t* exponent_limbs = exponent->limbs;
    uint32_t value = exponent_limbs[exponent_index];
    int32_t position = int32_t(32u - window - leading);
    if (position < 0) {
        if (int32_t(exponent_index) > 0) {
            uint32_t left_shift = uint32_t(0u - uint32_t(position)) & 31;
            --exponent_index;
            position += 32;
            value = (value << left_shift) |
                    (exponent_limbs[exponent_index] >> (uint32_t(position) & 31));
        }
    } else
        value >>= uint32_t(position) & 31;
    uint32_t trailing = 0;
    while ((value & 1) == 0) {
        value >>= 1;
        ++trailing;
    }
    copy_limbs(result, odd_powers + (value >> 1) * uint32_t(count), uint32_t(count));
    for (uint32_t i = 0; i < trailing; ++i)
        square_result();
    while (int32_t(exponent_index) > 0 || position > 0) {
        position -= int32_t(window);
        const uint32_t* current_word = exponent_limbs + exponent_index;
        value = *current_word;
        uint32_t used_bits = window;
        if (position < 0) {
            if (int32_t(exponent_index) < 1)
                used_bits = uint32_t(position) + window;
            else {
                uint32_t left_shift = uint32_t(0u - uint32_t(position)) & 31;
                --exponent_index;
                position += 32;
                current_word = exponent_limbs + exponent_index;
                value = (value << left_shift) | (*current_word >> (uint32_t(position) & 31));
            }
        } else
            value >>= uint32_t(position) & 31;
        value &= (1u << (used_bits & 31)) - 1;
        if ((value >> ((used_bits - 1) & 31)) == 0) {
            do {
                if (int32_t(exponent_index) < 1 && position < 1)
                    break;
                square_result();
                uint32_t next_bit;
                if (position == 0) {
                    position = 31;
                    --exponent_index;
                    --current_word;
                    next_bit = *current_word >> 31;
                } else {
                    --position;
                    next_bit = (*current_word >> (uint32_t(position) & 31)) & 1;
                }
                value = next_bit + value * 2;
            } while ((value >> ((used_bits - 1) & 31)) == 0);
        }
        trailing = used_bits;
        if (value != 0) {
            trailing = 0;
            while ((value & 1) == 0) {
                value >>= 1;
                ++trailing;
            }
            for (uint32_t i = 0; i < used_bits - trailing; ++i)
                square_result();
            fun_00588b40(product, result, odd_powers + (value >> 1) * uint32_t(count), count);
            reduce_product(result);
        }
        for (uint32_t i = 0; i < trailing; ++i)
            square_result();
    }
    if (montgomery) {
        copy_limbs(product, result, uint32_t(count));
        zero_limbs(product + count, uint32_t(count));
        fun_00586ae0(result, divisor, count, reduction_parameter, product);
        if (fun_00587660(result, divisor, count) >= 0)
            fun_00587610(result, result, divisor, uint32_t(count));
    } else if (reduction_parameter != 0) {
        uint32_t carry = fun_00587480(product, result, uint32_t(count), reduction_parameter);
        product[count] = carry;
        fun_00588c30(quotient, result, 0, product, count + int32_t(carry != 0), divisor, count);
        fun_00587510(result, result, uint32_t(count), reduction_parameter);
    }
    uint32_t result_count = normalized_size(result, uint32_t(count));
    if ((exponent_limbs[0] & 1) != 0 && base->signed_size < 0 && result_count != 0) {
        fun_005876a0(result, modulus->limbs, count, result, int32_t(result_count));
        result_count = normalized_size(result, uint32_t(count));
    }
    if (output->capacity < int32_t(result_count))
        fun_00587300(output, int32_t(result_count));
    output->signed_size = int32_t(result_count);
    copy_limbs(output->limbs, result, result_count);
    dat_0070c0d8(odd_powers, table_bytes);
}
