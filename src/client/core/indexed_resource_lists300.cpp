#include "indexed_resource_lists300.h"
#include "resource_manager.h"
#include "../runtime/allocations.h"

extern "C" const OriginalVirtualDelete dat_006cca24[1] = {FUN_00554d20};
extern "C" OriginalIndexedResourceLists300* __attribute__((thiscall))
FUN_00554ca0(OriginalIndexedResourceLists300* self) {
    self->first = nullptr;
    self->second = nullptr;
    self->third = nullptr;
    self->fourth = nullptr;
    self->first_count = 0;
    self->second_count = 0;
    self->third_count = 0;
    self->fourth_count = 0;
    self->owned14 = nullptr;
    self->vtable = dat_006cca24;
    for (uint32_t index = 0; index != 65; ++index)
        self->table28[index] = 0;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_005580d0(OriginalIndexedResourceLists300* self) {
    if (self->first != nullptr) {
        int32_t index = 0;
        while (index < self->first_count) {
            void* current = self->first[index];
            if (current != nullptr)
                FUN_0054b6d0(&dat_02221c00, current);
            index = static_cast<int32_t>(static_cast<uint32_t>(index) + 1u);
        }
    }
    if (self->second != nullptr) {
        int32_t index = 0;
        while (index < self->second_count) {
            void* current = self->second[index];
            if (current != nullptr)
                FUN_0054b650(&dat_02221c18, current);
            index = static_cast<int32_t>(static_cast<uint32_t>(index) + 1u);
        }
    }
}
extern "C" void __attribute__((thiscall)) FUN_00421570(OriginalIndexedResourceLists300* self) {
    FUN_005580d0(self);
    if (self->first != nullptr) {
        fun_005cdc59(self->first);
        self->first = nullptr;
    }
    self->first_count = 0;
    if (self->second != nullptr) {
        fun_005cdc59(self->second);
        self->second = nullptr;
    }
    self->second_count = 0;
    int32_t index = 0;
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
    self->third_count = 0;
    index = 0;
    while (index < self->fourth_count) {
        void* current = self->fourth[index];
        if (current != nullptr) {
            fun_005cdc59(current);
            self->fourth[index] = nullptr;
        }
        index = static_cast<int32_t>(static_cast<uint32_t>(index) + 1u);
    }
    if (self->owned14 != nullptr) {
        fun_005cdc59(self->owned14);
        self->owned14 = nullptr;
    }
    if (self->fourth != nullptr) {
        fun_005cdc59(self->fourth);
        self->fourth = nullptr;
    }
    self->fourth_count = 0;
}
extern "C" void __attribute__((thiscall)) FUN_00554d10(OriginalIndexedResourceLists300* self) {
    self->vtable = dat_006cca24;
    FUN_00421570(self);
}
extern "C" void* __attribute__((thiscall)) FUN_00554d20(void* value, uint32_t flags) {
    auto* self = static_cast<OriginalIndexedResourceLists300*>(value);
    self->vtable = dat_006cca24;
    FUN_00421570(self);
    if ((flags & 1) != 0)
        fun_005cc620(self);
    return self;
}
