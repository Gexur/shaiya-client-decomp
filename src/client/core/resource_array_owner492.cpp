#include "resource_array_owner492.h"
#include "../startup/global_ownership.h"
#include "../runtime/allocations.h"
#include "graphics/native_resources.h"
extern "C" const OriginalResourceArrayDeleting dat_006bcb94[1] = {FUN_004204c0};
extern "C" void __attribute__((thiscall)) resource_pair_construct(void* object) {
    (void)FUN_0041fef0(static_cast<OriginalResourcePair*>(object));
}
extern "C" void __attribute__((thiscall)) resource_pair_destroy(void* object) {
    FUN_0041ff00(static_cast<OriginalResourcePair*>(object));
}
namespace {
void release(OriginalComObject*& slot) {
    OriginalComObject* current = slot;
    if (current != nullptr) {
        shaiya::graphics::native::release_asset_resource(current);
        slot = nullptr;
    }
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_0041ff30(OriginalResourceArrayOwner492* self) {
    release(self->base04.first);
    release(self->base04.second);
    for (uint32_t i = 0; i < 5; ++i) {
        release(self->first14[i].first);
        release(self->first14[i].second);
        release(self->second64[i].first);
        release(self->second64[i].second);
    }
    OriginalResourceLeaf4* leaf = self->extrae0;
    if (leaf != nullptr) {
        release(leaf->resource);
        fun_005cc620(leaf);
        self->extrae0 = nullptr;
    }
}
extern "C" OriginalResourceArrayOwner492* __attribute__((thiscall))
FUN_004204c0(OriginalResourceArrayOwner492* self, uint32_t flags) {
    FUN_00420420(self);
    if (flags & 1)
        fun_005cc620(self);
    return self;
}
