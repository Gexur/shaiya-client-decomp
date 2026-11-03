#include "parent_owner.h"
#include "ordered_stores.h"
#include "resource_owner.h"
#include "nested_owner.h"
#include "core/com_resource.h"

namespace shaiya::ui {
namespace {
struct BaseUnwind {
    Object_004a0fd0* self;
    bool active = true;
    ~BaseUnwind() noexcept(false) {
        if (active)
            FUN_00422c00(self);
    }
};
struct PairUnwind {
    OriginalResourcePair* pair;
    bool active = true;
    ~PairUnwind() noexcept(false) {
        if (active)
            FUN_0041ff00(pair);
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
OriginalResourcePair* pair_at(Object_004a0fd0* self, u32 index) {
    return reinterpret_cast<OriginalResourcePair*>(reinterpret_cast<u8*>(self) + 0x2c + index * 16);
}
__declspec(noinline) void remaining_writes(Object_004a0fd0* self) {
    using namespace ordered_detail;
    FUN_004230b0(&self->subobject_654);
    store32(self, 0x92c, 1);
    store8(&DAT_022012e4, 0, 0);
    const bool zero = load32(self, 0x92c) == 0;
    store8(self, 0x708, 1);
    store8(self, 0x709, 0xff);
    store8(self, 0x70a, 0);
    store32(self, 0x70c, 0);
    store32(self, 0x820, 1);
    store32(self, 0x704, 0);
    store32(self, 0x824, 0);
    store32(self, 0xc, zero ? 0xfb : 0x14d);
    store32(self, 0x10, zero ? 0x152 : 0x17c);
    zero_words(self, 0x82c, 0x20);
    zero_words(self, 0x8ac, 0x20);
}
__declspec(noinline) void complete_parent(Object_004a0fd0* self) {
    using namespace ordered_detail;
    // Actual state0 protects these inline writes: all five pairs become
    // active together only at original4a105d, after their last write.
    for (u32 i = 0; i != 5; ++i) {
        const u32 offset = 0x2c + i * 16;
        store32(self, offset + 4, 0);
        store32(self, offset, 0);
        store32(self, offset + 8, 0);
        store32(self, offset + 12, 0);
    }
    PairUnwind pairs[5] = {{pair_at(self, 0)},
                           {pair_at(self, 1)},
                           {pair_at(self, 2)},
                           {pair_at(self, 3)},
                           {pair_at(self, 4)}};
    FUN_00527000(&self->subobject_07c);
    ResourceUnwind child{&self->subobject_07c};
    // State6 starts before actual4230b0 and stays active for every trailing
    // store. The original adds no cleanup for successful subobject654.
    remaining_writes(self);
    child.active = false;
    for (auto& pair : pairs)
        pair.active = false;
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_00422c00(void* self) {
    ordered_detail::store32(self, 0, reinterpret_cast<u32>(PTR_FUN_006bcc18));
}
extern "C" Object_004a0fd0* __attribute__((thiscall)) FUN_004a0fd0(Object_004a0fd0* self) {
    using namespace ordered_detail;
    for (u32 offset = 4; offset != 0x2c; offset += 4)
        store32(self, offset, offset == 0x20 ? 1 : 0);
    store32(self, 0, reinterpret_cast<u32>(PTR_FUN_006c18d8));
    BaseUnwind base{self};
    complete_parent(self);
    base.active = false;
    return self;
}
} // namespace shaiya::ui
