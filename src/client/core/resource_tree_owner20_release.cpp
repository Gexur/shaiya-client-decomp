#include "resource_tree_owner20_release.h"
namespace {
uint32_t load(const void* at) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
void store(void* at, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(at), "r"(value) : "memory");
}
} // namespace
// Original0052a540..0052a5c2. Iterator storage belongs to the actual owner,
// and the count decrement wraps exactly like the original DWORD DEC.
extern "C" void __attribute__((thiscall)) FUN_0052a540(OriginalResourceTreeOwner20* self,
                                                       void* value) {
    if (value == nullptr)
        return;
    self->current10 = self->tree04.header->left;
    if (self->current10 == self->tree04.header)
        return;
    while (self->current10->value != value) {
        FUN_005b8a60(&self->current10);
        if (self->current10 == self->tree04.header)
            return;
    }
    auto* found = static_cast<uint8_t*>(self->current10->value);
    store(found + 0x30, load(found + 0x30) - 1u);
    auto* parameter = static_cast<uint8_t*>(value);
    if (static_cast<int32_t>(load(parameter + 0x30)) > 0)
        return;
    store(parameter + 0x30, 0);
    shaiya::startup::String_00405710 temporary;
    temporary.capacity_018 = 15;
    temporary.size_014 = 0;
    temporary.storage_004[0] = 0;
    FUN_00405620(&temporary, reinterpret_cast<shaiya::startup::String_00405710*>(parameter + 0x14),
                 0, 0xffffffffu);
    FUN_0052a360(self, temporary);
}
