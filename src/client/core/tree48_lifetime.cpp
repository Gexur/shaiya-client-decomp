#include "tree48_lifetime.h"
#include "../runtime/allocations.h"

extern "C" OriginalTreeNode48* FUN_00558390() {
    auto* node = static_cast<OriginalTreeNode48*>(fun_005cc96d(48));
    using Word = uint32_t __attribute__((may_alias));
    const uint32_t address = reinterpret_cast<uint32_t>(node);
    if (address != 0)
        *reinterpret_cast<volatile Word*>(address) = 0;
    if (address + 4u != 0)
        *reinterpret_cast<volatile Word*>(address + 4u) = 0;
    if (address + 8u != 0)
        *reinterpret_cast<volatile Word*>(address + 8u) = 0;
    *reinterpret_cast<volatile uint8_t*>(address + 44u) = 1;
    *reinterpret_cast<volatile uint8_t*>(address + 45u) = 0;
    return node;
}
extern "C" void __attribute__((thiscall)) FUN_00434ec0(OriginalTreeNode48* self) {
    if (self->key.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(self->key.storage_004));
    self->key.capacity_018 = 15;
    self->key.size_014 = 0;
    self->key.storage_004[0] = 0;
}
extern "C" void __attribute__((thiscall)) FUN_00435140(OriginalTree48Owner12* self,
                                                       OriginalTreeNode48* node) {
    while (node->is_header == 0) {
        FUN_00435140(self, node->right);
        OriginalTreeNode48* current = node;
        node = node->left;
        FUN_00434ec0(current);
        fun_005cc620(current);
    }
}
extern "C" void __attribute__((thiscall)) FUN_00435180(OriginalTree48Owner12* self,
                                                       OriginalTreeNode48* node) {
    while (node->is_header == 0) {
        FUN_00435180(self, node->right);
        OriginalTreeNode48* current = node;
        node = node->left;
        FUN_00434ec0(current);
        fun_005cc620(current);
    }
}
extern "C" OriginalTreeNode48** __attribute__((thiscall)) FUN_005593c0(OriginalTree48Owner12* self,
                                                                       OriginalTreeNode48** out,
                                                                       OriginalTreeNode48* first,
                                                                       OriginalTreeNode48* last) {
    if (first == self->header->left && last == self->header) {
        FUN_00435140(self, self->header->parent);
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
            FUN_0054b270(self, &ignored, current);
        }
        *out = first;
    }
    return out;
}
extern "C" OriginalTreeNode48** __attribute__((thiscall)) FUN_00559480(OriginalTree48Owner12* self,
                                                                       OriginalTreeNode48** out,
                                                                       OriginalTreeNode48* first,
                                                                       OriginalTreeNode48* last) {
    if (first == self->header->left && last == self->header) {
        FUN_00435180(self, self->header->parent);
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
            FUN_0054b270(self, &ignored, current);
        }
        *out = first;
    }
    return out;
}
extern "C" void __attribute__((thiscall)) FUN_0055a1b0(OriginalTree48Owner12* self) {
    OriginalTreeNode48* ignored;
    FUN_005593c0(self, &ignored, self->header->left, self->header);
    fun_005cc620(self->header);
    self->header = nullptr;
    self->count = 0;
}
extern "C" void __attribute__((thiscall)) FUN_0055a1e0(OriginalTree48Owner12* self) {
    OriginalTreeNode48* ignored;
    FUN_00559480(self, &ignored, self->header->left, self->header);
    fun_005cc620(self->header);
    self->header = nullptr;
    self->count = 0;
}
