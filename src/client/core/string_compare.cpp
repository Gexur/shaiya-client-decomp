#include "string_compare.h"
namespace {
uint32_t word(const void* p) {
    uint32_t value;
    __asm__ __volatile__("movl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
int32_t bytes_compare(const uint8_t* left, const uint8_t* right, uint32_t count) {
    int32_t value;
    // Retain the original architectural string-read/fault order, including the
    // count-zero ZF inherited from XOR, rather than replace CMPSB with MOVs.
    __asm__ __volatile__("xorl %0,%0\n\trepe cmpsb\n\tje 1f\n\tsbbl %0,%0\n\tsbbl $-1,%0\n1:"
                         : "=&a"(value), "+S"(left), "+D"(right), "+c"(count)::"cc", "memory");
    return value;
}
} // namespace
extern "C" int32_t __attribute__((thiscall)) FUN_0040a670(shaiya::startup::String_00405710* self,
                                                          uint32_t position, uint32_t count,
                                                          const uint8_t* bytes, uint32_t length) {
    if (word(&self->size_014) < position)
        FUN_005e1911();
    const uint32_t remaining = word(&self->size_014) - position;
    if (remaining < count)
        count = remaining;
    if (count != 0) {
        const uint32_t common = count < length ? count : length;
        const uint8_t* data =
            word(&self->capacity_018) < 16
                ? self->storage_004
                : reinterpret_cast<const uint8_t*>(uintptr_t(word(self->storage_004)));
        const int32_t result = bytes_compare(data + position, bytes, common);
        if (result != 0)
            return result;
    }
    return count < length ? -1 : count != length ? 1 : 0;
}
