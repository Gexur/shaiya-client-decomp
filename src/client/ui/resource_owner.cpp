#include "resource_owner.h"
#include "core/resource_tree_owner20_release.h"
#include "runtime/allocations.h"

namespace shaiya::ui {
namespace {
u32 load32(const void* base, u32 offset) {
    u32 value;
    const auto* address = static_cast<const u8*>(base) + offset;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
void store32(void* base, u32 offset, u32 value) {
    auto* address = static_cast<u8*>(base) + offset;
    __asm__ volatile("movl %1,(%0)" ::"r"(address), "r"(value) : "memory");
}
void store8(void* base, u32 offset, u8 value) {
    auto* address = static_cast<u8*>(base) + offset;
    __asm__ volatile("movb %1,(%0)" ::"r"(address), "q"(value) : "memory");
}
} // namespace

// Original006c57cc contains exactly this one pointer. Adjacent bytes are
// floating constants and literal data; they are not fabricated table entries.
extern "C" const Deleting_00527760 PTR_FUN_006c57cc[1] = {FUN_00527760};

// Actual005270f0 loads each member immediately before its call and clears
// only after that call returns. This preserves later-slot callback changes.
extern "C" void __attribute__((thiscall)) FUN_005270f0(Object_00527000* self) {
    for (u32 offset = 0xb4; offset != 0xc4; offset += 4) {
        const u32 value = load32(self, offset);
        if (value != 0) {
            FUN_0052a540(&dat_0220364c, reinterpret_cast<void*>(value));
            store32(self, offset, 0);
        }
    }
    store8(self, 5, 0);
}

extern "C" void __attribute__((thiscall)) FUN_00527170(Object_00527000* self) {
    store32(self, 0, reinterpret_cast<u32>(PTR_FUN_006c57cc));
    FUN_005270f0(self);
}

extern "C" Object_00527000* __attribute__((thiscall)) FUN_00527760(Object_00527000* self,
                                                                   u32 flags) {
    store32(self, 0, reinterpret_cast<u32>(PTR_FUN_006c57cc));
    FUN_005270f0(self);
    if ((flags & 1) != 0)
        fun_005cc620(self);
    return self;
}
} // namespace shaiya::ui
