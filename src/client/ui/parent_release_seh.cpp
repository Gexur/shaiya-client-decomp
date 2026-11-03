#include "parent_release.h"
#include "ordered_stores.h"
#include "resource_owner.h"
#include "nested_owner.h"
#include "core/com_resource.h"
#include "runtime/allocations.h"
#include "graphics/native_resources.h"

namespace shaiya::ui {
namespace {
using namespace ordered_detail;
OriginalResourcePair* pair_at(Object_004a0fd0* self, u32 index) {
    return reinterpret_cast<OriginalResourcePair*>(reinterpret_cast<u8*>(self) + 0x2c + 16 * index);
}
struct BaseUnwind {
    Object_004a0fd0* self;
    bool active = true;
    ~BaseUnwind() noexcept(false) {
        if (active)
            FUN_00422c00(self);
    }
};
struct PairsUnwind {
    Object_004a0fd0* self;
    volatile u32 count = 5;
    ~PairsUnwind() noexcept(false) {
        for (u32 i = count; i != 0; --i)
            FUN_0041ff00(pair_at(self, i - 1));
    }
};
struct ResourceUnwind {
    Object_00527000* self;
    bool active = true;
    ~ResourceUnwind() noexcept(false) {
        if (active)
            FUN_00527170(self);
    }
};
struct NestedUnwind {
    Object_004230b0* self;
    bool active = true;
    ~NestedUnwind() noexcept(false) {
        if (active)
            FUN_00423110(self);
    }
};
void release_loaded(Object_004a0fd0* self, u32 offset, u32 pointer) {
    if (pointer != 0) {
        auto* object = reinterpret_cast<void*>(pointer);
        native_release_asset_resource(object);
        store32(self, offset, 0);
    }
}
void delete_member(Object_004a0fd0* self, u32 offset) {
    const u32 pointer = load32(self, offset);
    if (pointer != 0) {
        using Delete = void(__attribute__((thiscall))*)(void*, u32);
        auto* object = reinterpret_cast<void*>(pointer);
        auto* table = *static_cast<void***>(object);
        reinterpret_cast<Delete>(table[0])(object, 1);
        store32(self, offset, 0);
    }
}
__declspec(noinline) u32 first_pair_pointer(Object_004a0fd0* self, u32 offset) {
    return load32(self, offset);
}
__declspec(noinline) void release_pair_loaded(Object_004a0fd0* self, u32 offset, u32 first) {
    release_loaded(self, offset, first);
    release_loaded(self, offset + 4, load32(self, offset + 4));
}
__declspec(noinline) void early_release(Object_004a0fd0* self, u32 first) {
    release_loaded(self, 0x2c, first);
    release_loaded(self, 0x30, load32(self, 0x30));
    delete_member(self, 0x704);
    delete_member(self, 0x824);
    FUN_0041ff00(pair_at(self, 1));
    FUN_0041ff00(pair_at(self, 2));
    FUN_0041ff00(pair_at(self, 3));
}
} // namespace

extern "C" void __attribute__((thiscall)) FUN_004a1120(Object_004a0fd0* self) {
    using namespace ordered_detail;
    store32(self, 0, reinterpret_cast<u32>(PTR_FUN_006c18d8));
    // Actual4a1144 reads this slot before state7 is installed. Do not move
    // that first hardware load into the protected release interval.
    const u32 first = load32(self, 0x2c);
    BaseUnwind base{self};
    PairsUnwind pairs{self};
    ResourceUnwind resource{&self->subobject_07c};
    NestedUnwind nested{&self->subobject_654};
    early_release(self, first);
    // Each original state drops BEFORE calling its ordinary destructor.
    nested.active = false;
    FUN_00423110(&self->subobject_654);
    resource.active = false;
    FUN_00527170(&self->subobject_07c);
    for (u32 index = 5; index != 0; --index) {
        const u32 offset = 0x2c + (index - 1) * 16;
        // Original loads each first pointer while the current pair's state
        // is still active, then drops state before testing/calling it.
        const u32 first = first_pair_pointer(self, offset);
        pairs.count = index - 1;
        release_pair_loaded(self, offset, first);
    }
    FUN_00422c00(self);
    base.active = false;
}
extern "C" Object_004a0fd0* __attribute__((thiscall)) FUN_004a14f0(Object_004a0fd0* self,
                                                                   u32 flags) {
    FUN_004a1120(self);
    if ((flags & 1) != 0)
        fun_005cc620(self);
    return self;
}
extern "C" void* __attribute__((thiscall)) FUN_00422c20(void* self, u32 flags) {
    ordered_detail::store32(self, 0, reinterpret_cast<u32>(PTR_FUN_006bcc18));
    if ((flags & 1) != 0)
        fun_005cc620(self);
    return self;
}
} // namespace shaiya::ui
