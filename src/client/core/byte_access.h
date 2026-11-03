#pragma once

#include <stddef.h>
#include <type_traits>

namespace shaiya::byte_access {

/**
 * @brief Read a value's native representation from possibly unaligned storage.
 * @tparam Value A trivially copyable value type, including native pointer types.
 * @param address At least sizeof(Value) readable bytes, not concurrently modified.
 * @return The value represented by those bytes on the current target.
 * @note The width is sizeof(Value); protocol fields must keep their explicit
 *       fixed-width types. Byte copying permits aliasing and unaligned storage.
 *       This operation does not promise atomicity or machine access/fault order.
 */
template <typename Value> Value load(const void* address) {
    static_assert(std::is_trivially_copyable_v<Value>, "Byte access requires a trivially copyable type");
    Value value;
    auto* destination = reinterpret_cast<unsigned char*>(&value);
    const auto* source = static_cast<const unsigned char*>(address);
    for (size_t index = 0; index != sizeof(Value); ++index)
        destination[index] = source[index];
    return value;
}

/**
 * @brief Write a value's native representation to possibly unaligned storage.
 * @tparam Value A trivially copyable value type, including native pointer types.
 * @param address At least sizeof(Value) writable bytes, not concurrently accessed.
 * @param value Value whose complete target representation is copied.
 * @note Only sizeof(Value) bytes are changed. This operation does not promise
 *       atomicity or machine access/fault order.
 */
template <typename Value> void store(void* address, Value value) {
    static_assert(std::is_trivially_copyable_v<Value>, "Byte access requires a trivially copyable type");
    auto* destination = static_cast<unsigned char*>(address);
    const auto* source = reinterpret_cast<const unsigned char*>(&value);
    for (size_t index = 0; index != sizeof(Value); ++index)
        destination[index] = source[index];
}

} // namespace shaiya::byte_access
