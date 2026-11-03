#include "pointer_list16.h"
#include "../runtime/allocations.h"

extern "C" const OriginalVirtualDelete dat_006cca28[1] = {FUN_00554f00};

extern "C" OriginalPointerList16* __attribute__((thiscall))
FUN_00554cf0(OriginalPointerList16* self) {
    self->vtable = dat_006cca28;
    self->elements = nullptr;
    self->count = 0;
    self->unknown08 = 0;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_00434c60(OriginalPointerList16* self) {
    int32_t index = 0;
    while (index < self->count) {
        void* current = self->elements[index];
        if (current != nullptr) {
            (*static_cast<const OriginalVirtualDelete**>(current))[0](current, 1);
            self->elements[index] = nullptr;
        }
        index = static_cast<int32_t>(static_cast<uint32_t>(index) + 1u);
    }
    if (self->elements != nullptr) {
        fun_005cdc59(self->elements);
        self->elements = nullptr;
    }
    self->count = 0;
}
extern "C" void __attribute__((thiscall)) FUN_00554ef0(OriginalPointerList16* self) {
    self->vtable = dat_006cca28;
    FUN_00434c60(self);
}
extern "C" void* __attribute__((thiscall)) FUN_00554f00(void* object, uint32_t flags) {
    auto* self = static_cast<OriginalPointerList16*>(object);
    self->vtable = dat_006cca28;
    FUN_00434c60(self);
    if ((flags & 1) != 0)
        fun_005cc620(self);
    return self;
}
