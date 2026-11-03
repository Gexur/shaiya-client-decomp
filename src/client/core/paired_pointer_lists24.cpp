#include "paired_pointer_lists24.h"
#include "../runtime/allocations.h"
extern "C" const OriginalVirtualDelete dat_006ccb64[1] = {FUN_0055aec0};
extern "C" uint32_t __attribute__((thiscall)) FUN_0055ab50(OriginalPairedPointerLists24* self) {
    int32_t index = 0;
    while (index < self->paired_count) {
        void* current = self->first[index];
        if (current != nullptr) {
            (*static_cast<const OriginalVirtualDelete**>(current))[0](current, 1);
            self->first[index] = nullptr;
        }
        current = self->second[index];
        if (current != nullptr) {
            (*static_cast<const OriginalVirtualDelete**>(current))[0](current, 1);
            self->second[index] = nullptr;
        }
        index = static_cast<int32_t>(static_cast<uint32_t>(index) + 1u);
    }
    if (self->first != nullptr) {
        fun_005cdc59(self->first);
        self->first = nullptr;
    }
    if (self->second != nullptr) {
        fun_005cdc59(self->second);
        self->second = nullptr;
    }
    index = 0;
    while (index < self->third_count) {
        void* current = self->third[index];
        if (current != nullptr) {
            (*static_cast<const OriginalVirtualDelete**>(current))[0](current, 1);
            self->third[index] = nullptr;
        }
        index = static_cast<int32_t>(static_cast<uint32_t>(index) + 1u);
    }
    if (self->third != nullptr) {
        fun_005cdc59(self->third);
        self->third = nullptr;
    }
    self->paired_count = 0;
    self->third_count = 0;
    return 1;
}
extern "C" void* __attribute__((thiscall)) FUN_0055aec0(void* value, uint32_t flags) {
    auto* self = static_cast<OriginalPairedPointerLists24*>(value);
    self->vtable = dat_006ccb64;
    (void)FUN_0055ab50(self);
    if ((flags & 1) != 0)
        fun_005cc620(self);
    return self;
}
