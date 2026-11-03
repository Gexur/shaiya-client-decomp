#include "tree48_global.h"
#include "tree48_lifetime.h"
#include "../runtime/allocations.h"

extern "C" OriginalTree48Owner12* __attribute__((thiscall))
FUN_005bae30(OriginalTree48Owner12* self) {
    self->header = FUN_00558390();
    self->header->is_header = 1;
    self->header->parent = self->header;
    self->header->left = self->header;
    self->header->right = self->header;
    self->count = 0;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_005b9760(OriginalTree48Owner12* self,
                                                       OriginalTreeNode48* node) {
    while (node->is_header == 0) {
        FUN_005b9760(self, node->right);
        OriginalTreeNode48* current = node;
        node = node->left;
        FUN_00434ec0(current);
        fun_005cc620(current);
    }
}
extern "C" OriginalTreeNode48** __attribute__((thiscall)) FUN_005ba140(OriginalTree48Owner12* self,
                                                                       OriginalTreeNode48** out,
                                                                       OriginalTreeNode48* first,
                                                                       OriginalTreeNode48* last) {
    if (first == self->header->left && last == self->header) {
        FUN_005b9760(self, self->header->parent);
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
            FUN_005b97a0(self, &ignored, current);
        }
        *out = first;
    }
    return out;
}
extern "C" void __attribute__((thiscall)) FUN_005bac90(OriginalTree48Owner12* self) {
    OriginalTreeNode48* ignored;
    FUN_005ba140(self, &ignored, self->header->left, self->header);
    fun_005cc620(self->header);
    self->header = nullptr;
    self->count = 0;
}
