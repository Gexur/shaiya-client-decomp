#include "resource_lists28.h"
#include "triple_list32.h"
#include "../startup/game_init.h"
#include "../startup/global_ownership.h"
#include "../runtime/allocations.h"
#include "graphics/native_resources.h"

extern "C" const OriginalVirtualDelete dat_006ccb18[1] = {FUN_005571d0};
extern "C" void __attribute__((thiscall)) FUN_00556890(OriginalResourceRecord* self) {
    const uint16_t count = self->state128;
    if (count != 0) {
        if (count == 1) {
            if (self->first != nullptr) {
                shaiya::graphics::native::release_asset_resource(self->first);
                self->first = nullptr;
            }
            if (self->second != nullptr) {
                shaiya::graphics::native::release_asset_resource(self->second);
                self->second = nullptr;
            }
            self->state128 = 0;
        } else
            self->state128 = static_cast<uint16_t>(count - 1u);
    }
}
extern "C" OriginalResourceLists28* __attribute__((thiscall))
FUN_00556cd0(OriginalResourceLists28* self) {
    self->vtable = dat_006ccb18;
    self->first = nullptr;
    self->second = nullptr;
    self->third = nullptr;
    self->first_count = 0;
    self->second_count = 0;
    self->third_count = 0;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_00435010(OriginalResourceLists28* self) {
    int32_t index = 0;
    while (index < self->first_count) {
        if (dat_007191d4 != nullptr &&
            uint8_t(dat_007191d4->callbacks->callback_004(dat_007191d4, 0x15)) != 0) {
            OriginalResourceRecord* current = self->first[index];
            if (current != nullptr)
                FUN_00556890(current);
        }
        OriginalResourceRecord* current = self->first[index];
        if (current != nullptr) {
            FUN_0040f010(current);
            fun_005cc620(current);
            self->first[index] = nullptr;
        }
        index = static_cast<int32_t>(static_cast<uint32_t>(index) + 1u);
    }
    if (self->first != nullptr) {
        fun_005cdc59(self->first);
        self->first = nullptr;
    }
    index = 0;
    while (index < self->second_count) {
        if (dat_007191d4 != nullptr &&
            uint8_t(dat_007191d4->callbacks->callback_004(dat_007191d4, 0x15)) != 0) {
            void* current = self->second[index];
            if (current != nullptr)
                FUN_0053dd40(current);
        }
        void* current = self->second[index];
        if (current != nullptr) {
            (*static_cast<const OriginalVirtualDelete**>(current))[0](current, 1);
            self->second[index] = nullptr;
        }
        index = static_cast<int32_t>(static_cast<uint32_t>(index) + 1u);
    }
    if (self->second != nullptr) {
        fun_005cdc59(self->second);
        self->second = nullptr;
    }
    index = 0;
    while (index < self->third_count) {
        void* current = self->third[index];
        if (current != nullptr) {
            fun_005cc620(current);
            self->third[index] = nullptr;
        }
        index = static_cast<int32_t>(static_cast<uint32_t>(index) + 1u);
    }
    if (self->third != nullptr) {
        fun_005cdc59(self->third);
        self->third = nullptr;
    }
    self->first_count = 0;
    self->second_count = 0;
    self->third_count = 0;
}
extern "C" void __attribute__((thiscall)) FUN_005571c0(OriginalResourceLists28* self) {
    self->vtable = dat_006ccb18;
    FUN_00435010(self);
}
extern "C" void* __attribute__((thiscall)) FUN_005571d0(void* value, uint32_t flags) {
    auto* self = static_cast<OriginalResourceLists28*>(value);
    self->vtable = dat_006ccb18;
    FUN_00435010(self);
    if ((flags & 1) != 0)
        fun_005cc620(self);
    return self;
}
