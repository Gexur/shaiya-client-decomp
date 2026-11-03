#include "parent_draw.h"

namespace shaiya::ui {
namespace {
u32 word(const void* base, u32 offset) {
    u32 value;
    auto* address = static_cast<const u8*>(base) + offset;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
u32 byte(const void* base, u32 offset) {
    u32 value;
    auto* address = static_cast<const u8*>(base) + offset;
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
} // namespace

// Exact original004a0720..004a07e2. The original performs no bounds check
// on the byte-selected40-byte records and wraps the DWORD coordinate/index
// arithmetic. Ordered loads retain callbacks' changes to later fields.
extern "C" u32 __attribute__((thiscall)) FUN_004a0720(Object_004a0fd0* self) {
    const u32 enabled = word(self, 0x20);
    if (enabled == 0)
        return enabled;
    const u32 first = word(self, 0x824);
    if (first != 0)
        (void)FUN_00426740(reinterpret_cast<void*>(first));
    const u32 mode = word(self, 0x92c);
    const u32 selected = mode == 0 ? FUN_0049fba0(self) : FUN_004a0390(self);
    const u32 member = word(self, 0x704);
    const u32 index = selected + 0xf0u;
    if (member != 0)
        return FUN_00529040(reinterpret_cast<void*>(member));
    const u32 record = byte(self, 0x709);
    if (record != 0xff) {
        const u32 offset = record * 0x28u;
        const u32 third = byte(dat_021fed65, offset + 2);
        const u32 second = byte(dat_021fed65, offset + 1);
        const u32 first_byte = byte(dat_021fed65, offset);
        const u32 y = word(&dat_0071c2a8, 0) - 0x10u;
        const u32 x = word(&dat_0071c2a4, 0) - 0x10u;
        return FUN_004a3400(&self->subobject_654, 0x7fffffffu, x, y, first_byte, second, third, 0,
                            1);
    }
    if (index != 0xffffffffu)
        return FUN_004a7680(&self->subobject_654, 0, 0, 0, index, 0, 0, 0, 0);
    return index;
}
} // namespace shaiya::ui
