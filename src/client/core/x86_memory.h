#pragma once

#include <stdint.h>

namespace client::x86 {

// Recovered x86 procedures sometimes access unaligned raw storage and reread it
// after aliases or callbacks change it. Packed, aliasable, volatile access keeps
// the original access width and order without an inline assembly MOV. This is
// deliberately specific to the client's GNU-compatible x86 compiler target.
template <typename Value> struct __attribute__((packed, may_alias)) MemoryValue {
    static_assert(sizeof(Value) == 1 || sizeof(Value) == 2 || sizeof(Value) == 4,
                  "Recovered scalar memory accesses must retain their x86 width");
    Value value;
};

/**
 * @brief Read one unaligned scalar at the original x86 access width.
 * @tparam Value One-, two-, or four-byte scalar type.
 * @param address Readable client storage; no alignment is required.
 * @return The value observed by one volatile packed access.
 */
template <typename Value> Value load(const void* address) {
    return reinterpret_cast<const volatile MemoryValue<Value>*>(address)->value;
}

/**
 * @brief Write one unaligned scalar at the original x86 access width.
 * @tparam Value One-, two-, or four-byte scalar type.
 * @param address Writable client storage; no alignment is required.
 * @param value Scalar to store through a volatile packed access.
 */
template <typename Value> void store(void* address, Value value) {
    reinterpret_cast<volatile MemoryValue<Value>*>(address)->value = value;
}

/** @brief Read a 32-bit word from the supplied 32-bit client address. */
inline uint32_t load_word(uint32_t address) {
    return load<uint32_t>(reinterpret_cast<const void*>(address));
}

/** @brief Read one byte from the supplied 32-bit client address. */
inline uint8_t load_byte(uint32_t address) {
    return load<uint8_t>(reinterpret_cast<const void*>(address));
}

/** @brief Store a 32-bit word at the supplied 32-bit client address. */
inline void store_word(uint32_t address, uint32_t value) {
    store(reinterpret_cast<void*>(address), value);
}

} // namespace client::x86
