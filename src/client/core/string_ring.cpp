#include "string_ring.h"
#include "../runtime/allocations.h"
namespace {
void* allocation(const unsigned char* bytes) {
    void* value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(bytes) : "memory");
    return value;
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_0040ade0(OriginalStringRing20* self) {
    while (self->count != 0) {
        if (self->count != 0) {
            uint32_t index = self->count + self->start - 1;
            if (self->capacity <= index)
                index -= self->capacity;
            auto* const value = self->blocks[index];
            if (value->capacity_018 >= 16)
                fun_005cc620(allocation(value->storage_004));
            value->capacity_018 = 15;
            value->size_014 = 0;
            value->storage_004[0] = 0;
            --self->count;
            if (self->count == 0)
                self->start = 0;
        }
    }
    uint32_t remaining = self->capacity;
    while (remaining > 0) {
        auto* const value = self->blocks[remaining - 1];
        --remaining;
        if (value != nullptr)
            fun_005cc620(value);
    }
    auto** const blocks = self->blocks;
    if (blocks != nullptr)
        fun_005cc620(blocks);
    self->capacity = 0;
    self->blocks = nullptr;
}
