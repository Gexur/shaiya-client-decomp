#include "com_owner.h"
#include "../startup/global_ownership.h"
#include "../runtime/allocations.h"
#include "graphics/native_resources.h"
extern "C" const OriginalComOwnerVtable dat_006bc858 = {FUN_0040ef20};
namespace {
void release_owner(OriginalComOwner* owner) {
    OriginalComObject* resource = owner->resource;
    owner->vtable = &dat_006bc858;
    if (resource != nullptr) {
        shaiya::graphics::native::release_asset_resource(resource);
        owner->resource = nullptr;
    }
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_0040ef00(OriginalComOwner* owner) {
    release_owner(owner);
}
extern "C" OriginalComOwner* __attribute__((thiscall)) FUN_0040ef20(OriginalComOwner* owner,
                                                                    uint32_t flags) {
    release_owner(owner);
    if ((flags & 1) != 0)
        fun_005cc620(owner);
    return owner;
}
extern "C" OriginalComBuffer* __attribute__((thiscall)) FUN_0040e590(OriginalComBuffer* object) {
    object->owner.vtable = &dat_006bc858;
    object->owner.resource = nullptr;
    object->state10c = 0;
    return object;
}
