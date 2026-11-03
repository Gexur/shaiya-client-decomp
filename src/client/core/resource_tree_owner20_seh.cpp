#include "resource_tree_owner20.h"

namespace {
struct TreeCleanup {
    OriginalTree48Owner12* tree;
    bool active = true;
    ~TreeCleanup() noexcept(false) {
        if (active)
            FUN_0052aa70(tree);
    }
};
struct OwnerCleanup {
    OriginalResourceTreeOwner20* owner;
    bool active = true;
    ~OwnerCleanup() noexcept(false) {
        if (active)
            FUN_0052ab80(owner);
    }
};
__declspec(noinline) void release_values(OriginalResourceTreeOwner20* self) {
    FUN_0052a5d0(self);
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_0052ab80(OriginalResourceTreeOwner20* self) {
    self->vtable = dat_006c582c;
    TreeCleanup tree{&self->tree04};
    release_values(self);
    tree.active = false;
    FUN_0052aa70(&self->tree04);
}
extern "C" void __attribute__((thiscall)) FUN_0052ac60(OriginalResourceTreeOwner20* self) {
    OwnerCleanup owner{self};
    release_values(self);
    owner.active = false;
    FUN_0052ab80(self);
}
