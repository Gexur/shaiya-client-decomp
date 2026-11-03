#include "com_lifetimes.h"
#include "../runtime/allocations.h"
#include "graphics/native_render_target.h"
extern "C" {
const OriginalComLifetimeDelete dat_006c8624[1] = {FUN_00546d10};
const OriginalComLifetimeDelete dat_006c9780[1] = {FUN_00549680};
const OriginalComLifetimeDelete dat_006c9784[1] = {FUN_005496c0};
}
extern "C" void* __attribute__((thiscall)) FUN_00546d10(void* object, uint32_t flags) {
    auto* self = static_cast<OriginalTripleComOwner20*>(object);
    using namespace shaiya::graphics::native;
    auto* texture = static_cast<Texture2D*>(self->third);
    self->vtable = dat_006c8624;
    if (texture != nullptr) {
        texture->release();
        self->third = nullptr;
    }
    // The native target texture owns this borrowed RTV. It can already have
    // expired after the texture release, so clear it without dereferencing it.
    self->second = nullptr;
    auto* scope = static_cast<TargetScope*>(self->first);
    if (scope != nullptr) {
        release_target_scope(scope);
        self->first = nullptr;
    }
    self->state04 = 0;
    if (flags & 1)
        fun_005cc620(self);
    return self;
}
extern "C" void* __attribute__((thiscall)) FUN_00549680(void* object, uint32_t flags) {
    auto* self = static_cast<OriginalSingleComOwner12*>(object);
    auto* const current = static_cast<shaiya::graphics::native::Texture2D*>(self->resource);
    self->vtable = dat_006c9780;
    if (current != nullptr) {
        current->release();
        self->resource = nullptr;
    }
    if (flags & 1)
        fun_005cc620(self);
    return self;
}
extern "C" void* __attribute__((thiscall)) FUN_005496c0(void* object, uint32_t flags) {
    auto* self = static_cast<OriginalDoubleComOwner12*>(object);
    auto* current = static_cast<shaiya::graphics::native::Texture2D*>(self->first);
    self->vtable = dat_006c9784;
    if (current != nullptr) {
        current->release();
        self->first = nullptr;
    }
    current = static_cast<shaiya::graphics::native::Texture2D*>(self->second);
    if (current != nullptr) {
        current->release();
        self->second = nullptr;
    }
    if (flags & 1)
        fun_005cc620(self);
    return self;
}
