#include "resource_manager_lifetime.h"
#include "../runtime/allocations.h"

extern "C" const OriginalVirtualDelete dat_006ccb4c[1] = {FUN_0055a310};
extern "C" const OriginalVirtualDelete dat_006ccb50[1] = {FUN_0055a330};
extern "C" const OriginalVirtualDelete dat_006ccb54[1] = {FUN_0055a3f0};
extern "C" const OriginalVirtualDelete dat_006ccb58[1] = {FUN_0055a4b0};

extern "C" void __attribute__((thiscall)) FUN_004351c0(OriginalResourceManagerBase20* self) {
    self->cursor = self->tree.header->left;
    while (self->cursor != self->tree.header) {
        void* current = self->cursor->value;
        if (current != nullptr)
            (*static_cast<const OriginalVirtualDelete**>(current))[0](current, 1);
        FUN_005b8a60(&self->cursor);
    }
    FUN_00435140(&self->tree, self->tree.header->parent);
    self->tree.header->parent = self->tree.header;
    self->tree.count = 0;
    self->tree.header->left = self->tree.header;
    self->tree.header->right = self->tree.header;
}
extern "C" void __attribute__((thiscall)) FUN_00435220(OriginalResourceManagerBase20* self) {
    self->cursor = self->tree.header->left;
    while (self->cursor != self->tree.header) {
        void* current = self->cursor->value;
        if (current != nullptr) {
            FUN_00434e20(current);
            fun_005cc620(current);
        }
        FUN_005b8a60(&self->cursor);
    }
    FUN_00435180(&self->tree, self->tree.header->parent);
    self->tree.header->parent = self->tree.header;
    self->tree.count = 0;
    self->tree.header->left = self->tree.header;
    self->tree.header->right = self->tree.header;
}
extern "C" OriginalResourceManager24* __attribute__((thiscall))
FUN_0055a350(OriginalResourceManager24* self) {
    self->untouched00 = reinterpret_cast<uint32_t>(dat_006ccb54);
    self->untouched04 = reinterpret_cast<uint32_t>(dat_006ccb4c);
    self->tree.header = FUN_00558390();
    self->tree.header->is_header = 1;
    self->tree.header->parent = self->tree.header;
    self->tree.header->left = self->tree.header;
    self->tree.header->right = self->tree.header;
    self->tree.count = 0;
    self->cursor = nullptr;
    return self;
}
extern "C" OriginalResourceManager24* __attribute__((thiscall))
FUN_0055a410(OriginalResourceManager24* self) {
    self->untouched00 = reinterpret_cast<uint32_t>(dat_006ccb58);
    self->untouched04 = reinterpret_cast<uint32_t>(dat_006ccb50);
    self->tree.header = FUN_00558390();
    self->tree.header->is_header = 1;
    self->tree.header->parent = self->tree.header;
    self->tree.header->left = self->tree.header;
    self->tree.header->right = self->tree.header;
    self->tree.count = 0;
    self->cursor = nullptr;
    return self;
}
extern "C" void* __attribute__((thiscall)) FUN_0055a310(void* value, uint32_t flags) {
    FUN_0055a210(static_cast<OriginalResourceManagerBase20*>(value));
    if ((flags & 1) != 0)
        fun_005cc620(value);
    return value;
}
extern "C" void* __attribute__((thiscall)) FUN_0055a330(void* value, uint32_t flags) {
    FUN_0055a290(static_cast<OriginalResourceManagerBase20*>(value));
    if ((flags & 1) != 0)
        fun_005cc620(value);
    return value;
}
extern "C" void* __attribute__((thiscall)) FUN_0055a3f0(void* value, uint32_t flags) {
    FUN_0055a390(static_cast<OriginalResourceManager24*>(value));
    if ((flags & 1) != 0)
        fun_005cc620(value);
    return value;
}
extern "C" void* __attribute__((thiscall)) FUN_0055a4b0(void* value, uint32_t flags) {
    FUN_0055a450(static_cast<OriginalResourceManager24*>(value));
    if ((flags & 1) != 0)
        fun_005cc620(value);
    return value;
}
