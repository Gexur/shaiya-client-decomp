#include "resource_tree_owner20.h"
#include "tree48_lifetime.h"
#include "../runtime/allocations.h"

extern "C" const ResourceTreeDeleting dat_006c582c[1] = {FUN_0052ac00};
extern "C" OriginalResourceTreeOwner20* __attribute__((thiscall))
FUN_0052ac20(OriginalResourceTreeOwner20* self) {
    self->vtable = dat_006c582c;
    self->tree04.header = FUN_00558390();
    self->tree04.header->is_header = 1;
    self->tree04.header->parent = self->tree04.header;
    self->tree04.header->left = self->tree04.header;
    self->tree04.header->right = self->tree04.header;
    self->tree04.count = 0;
    self->current10 = nullptr;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_0052a1c0(OriginalTree48Owner12* self,
                                                       OriginalTreeNode48* node) {
    while (node->is_header == 0) {
        FUN_0052a1c0(self, node->right);
        OriginalTreeNode48* current = node;
        node = node->left;
        FUN_00434ec0(current);
        fun_005cc620(current);
    }
}
extern "C" OriginalTreeNode48** __attribute__((thiscall)) FUN_0052a3f0(OriginalTree48Owner12* self,
                                                                       OriginalTreeNode48** out,
                                                                       OriginalTreeNode48* first,
                                                                       OriginalTreeNode48* last) {
    if (first == self->header->left && last == self->header) {
        FUN_0052a1c0(self, self->header->parent);
        self->header->parent = self->header;
        self->count = 0;
        self->header->left = self->header;
        self->header->right = self->header;
        *out = self->header->left;
    } else {
        while (first != last) {
            OriginalTreeNode48* current = first;
            FUN_005b8a60(&first);
            OriginalTreeNode48* ignored;
            FUN_00529ee0(self, &ignored, current);
        }
        *out = first;
    }
    return out;
}
extern "C" void __attribute__((thiscall)) FUN_0052a5d0(OriginalResourceTreeOwner20* self) {
    using DeleteValue = void(__attribute__((thiscall))*)(void*, uint32_t);
    self->current10 = self->tree04.header->left;
    while (self->current10 != self->tree04.header) {
        void* value = self->current10->value;
        if (value != nullptr)
            (*static_cast<const DeleteValue**>(value))[0](value, 1);
        FUN_005b8a60(&self->current10);
    }
    FUN_0052a1c0(&self->tree04, self->tree04.header->parent);
    self->tree04.header->parent = self->tree04.header;
    self->tree04.count = 0;
    self->tree04.header->left = self->tree04.header;
    self->tree04.header->right = self->tree04.header;
}
extern "C" void __attribute__((thiscall)) FUN_0052aa70(OriginalTree48Owner12* self) {
    OriginalTreeNode48* ignored;
    FUN_0052a3f0(self, &ignored, self->header->left, self->header);
    fun_005cc620(self->header);
    self->header = nullptr;
    self->count = 0;
}
extern "C" OriginalResourceTreeOwner20* __attribute__((thiscall))
FUN_0052ac00(OriginalResourceTreeOwner20* self, uint32_t flags) {
    FUN_0052ab80(self);
    if ((flags & 1) != 0)
        fun_005cc620(self);
    return self;
}
