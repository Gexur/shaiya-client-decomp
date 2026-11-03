#include "memory.h"

// Derived from the original library routines in game.exe, not a replacement
// library implementation. See the corresponding REA exports and differential
// tests. Optimized DWORD/unrolled paths are expressed as byte copies; their
// observable byte and return-value behavior is checked across all alignments.
extern "C" void* fun_005dceb0(void* destination, int32_t value, uint32_t size) {
    auto* cursor = static_cast<uint8_t*>(destination);
    const uint8_t byte = static_cast<uint8_t>(value);
    while (size != 0) {
        *cursor++ = byte;
        --size;
    }
    return destination;
}

extern "C" void* fun_005cc630(void* destination, const void* source, uint32_t size) {
    auto* target = static_cast<uint8_t*>(destination);
    auto* input = static_cast<const uint8_t*>(source);
    const uint32_t target_address = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(target));
    const uint32_t input_address = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(input));
    // Original unsigned comparisons choose backward copying for overlapping
    // higher destination addresses. The additions retain original x86 wrap.
    if (input_address < target_address && target_address < input_address + size) {
        while (size != 0) {
            --size;
            target[size] = input[size];
        }
    } else {
        for (uint32_t index = 0; index < size; ++index)
            target[index] = input[index];
    }
    return destination;
}

extern "C" void* fun_005d8d30(void* destination, const void* source, uint32_t size) {
    // Original 005D8D30 retains the same overlapping-range direction branch
    // despite the provider's memcpy label; preserve that observed behavior.
    return fun_005cc630(destination, source, size);
}

extern "C" void* memset(void* destination, int value, size_t size) {
    return fun_005dceb0(destination, value, static_cast<uint32_t>(size));
}
extern "C" void* memcpy(void* destination, const void* source, size_t size) {
    return fun_005d8d30(destination, source, static_cast<uint32_t>(size));
}
extern "C" void* memmove(void* destination, const void* source, size_t size) {
    return fun_005cc630(destination, source, static_cast<uint32_t>(size));
}
