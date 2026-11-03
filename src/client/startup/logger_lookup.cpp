#include "logger.h"
#include "../core/string_compare.h"
#include "../core/tree48_lookup.h"
namespace {
uint32_t read32(const void* pointer) {
    uint32_t value;
    __asm__ __volatile__("movl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return value;
}
} // namespace
extern "C" OriginalSafLogger* fun_0040ae80(const shaiya::startup::String_00405710* name) {
    const uint32_t capacity = read32(&name->capacity_018), length = read32(&name->size_014);
    const uint8_t* data =
        capacity < 16 ? name->storage_004
                      : reinterpret_cast<const uint8_t*>(uintptr_t(read32(name->storage_004)));
    if (FUN_0040a670(&dat_0224e6c0.name, 0, read32(&dat_0224e6c0.name.size_014), data, length) == 0)
        return &dat_0224e6c0;
    OriginalTreeNode48* found;
    FUN_0054b170(&dat_0224e700, &found, const_cast<shaiya::startup::String_00405710*>(name));
    if (found != dat_0224e700.header)
        return static_cast<OriginalSafLogger*>(found->value);
    return fun_005bacc0(name, 0x3ff);
}
