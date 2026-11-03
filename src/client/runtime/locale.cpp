#include "locale.h"
#include "heap.h"

namespace {
void* pointer_at(void* storage, uint32_t offset) {
    return *reinterpret_cast<void**>(static_cast<uint8_t*>(storage) + offset);
}
uint32_t word_at(void* storage, uint32_t offset) {
    return *reinterpret_cast<uint32_t*>(static_cast<uint8_t*>(storage) + offset);
}
} // namespace

extern "C" void fun_005dd634(void* category) {
    if (category == nullptr)
        return;
    // The original frees the six abbreviated weekdays, then Sunday, the six
    // remaining full weekdays, then Sunday, followed by the remaining fields.
    const uint32_t first_offsets[] = {4, 8, 12, 16, 20, 24, 0, 32, 36, 40, 44, 48, 52, 28};
    for (uint32_t offset : first_offsets)
        fun_005cfaf0(pointer_at(category, offset));
    for (uint32_t offset = 0x38; offset <= 0xa8; offset += 4)
        fun_005cfaf0(pointer_at(category, offset));
}

extern "C" void fun_005dd823(void* conversions) {
    if (conversions == nullptr)
        return;
    for (uint32_t index = 0; index < 3; ++index) {
        void* pointer = pointer_at(conversions, index * 4);
        if (pointer != dat_0070ef38->strings[index] && pointer != dat_0070ef08.strings[index])
            fun_005cfaf0(pointer);
    }
}

extern "C" void fun_005dda4f(void* conversions) {
    if (conversions == nullptr)
        return;
    for (uint32_t index = 3; index < 10; ++index) {
        void* pointer = pointer_at(conversions, index * 4);
        if (pointer != dat_0070ef38->strings[index] && pointer != dat_0070ef08.strings[index])
            fun_005cfaf0(pointer);
    }
}

extern "C" void fun_005d4d7b(void* locale) {
    void* allocation = pointer_at(locale, 0x3c);
    if (allocation != dat_0224f268 && allocation != nullptr &&
        word_at(pointer_at(locale, 0x2c), 0) == 0) {
        void* reference = pointer_at(locale, 0x34);
        if (reference != nullptr && word_at(reference, 0) == 0 && reference != dat_0225329c) {
            fun_005cfaf0(reference);
            fun_005dda4f(pointer_at(locale, 0x3c));
        }
        reference = pointer_at(locale, 0x30);
        if (reference != nullptr && word_at(reference, 0) == 0 && reference != dat_022532a4) {
            fun_005cfaf0(reference);
            fun_005dd823(pointer_at(locale, 0x3c));
        }
        fun_005cfaf0(pointer_at(locale, 0x2c));
        fun_005cfaf0(pointer_at(locale, 0x3c));
    }
    void* reference = pointer_at(locale, 0x40);
    if (reference != dat_02253298 && reference != nullptr && word_at(reference, 0) == 0) {
        fun_005cfaf0(reference);
        const uint32_t table = reinterpret_cast<uint32_t>(pointer_at(locale, 0x44));
        fun_005cfaf0(reinterpret_cast<void*>(table - 0xfe));
    }
    allocation = pointer_at(locale, 0x50);
    if (allocation != dat_0224f264 && allocation != nullptr && word_at(allocation, 0xb4) == 0) {
        fun_005dd634(allocation);
        fun_005cfaf0(pointer_at(locale, 0x50));
    }
    fun_005cfaf0(locale);
}
