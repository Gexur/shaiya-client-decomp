#pragma once
#include "string.h"

namespace shaiya::recovered_string {
inline unsigned char* data(startup::String_00405710* value) {
    return value->capacity_018 < 16 ? value->storage_004
                                    : *reinterpret_cast<unsigned char**>(value->storage_004);
}
inline const unsigned char* data(const startup::String_00405710* value) {
    return value->capacity_018 < 16 ? value->storage_004
                                    : *reinterpret_cast<unsigned char* const*>(value->storage_004);
}
// REP MOVSD followed by REP MOVSB in the original. Aliased accesses keep the
// exact forward DWORD/byte copy order, including the observed unaligned case.
using UnalignedWord = uint32_t __attribute__((aligned(1), may_alias));
inline void copy(unsigned char* destination, const unsigned char* source, uint32_t size) {
    for (uint32_t words = size >> 2; words != 0; --words, source += 4, destination += 4)
        *reinterpret_cast<volatile UnalignedWord*>(destination) =
            *reinterpret_cast<const volatile UnalignedWord*>(source);
    for (uint32_t bytes = size & 3; bytes != 0; --bytes)
        *static_cast<volatile unsigned char*>(destination++) =
            *static_cast<const volatile unsigned char*>(source++);
}
} // namespace shaiya::recovered_string
