#include "tree24.h"
#include "../runtime/allocations.h"

extern "C" OriginalTreeNode24* FUN_0053a7e0() {
    auto* node = static_cast<OriginalTreeNode24*>(fun_005cc96d(24));
    // The original tests each address separately. Its null-new path still
    // attempts the store at base+4; retain that observed hardware-fault path.
    using Word = uint32_t __attribute__((may_alias));
    const uint32_t address = reinterpret_cast<uint32_t>(node);
    if (address != 0)
        *reinterpret_cast<volatile Word*>(address) = 0;
    if (address + 4u != 0)
        *reinterpret_cast<volatile Word*>(address + 4u) = 0;
    if (address + 8u != 0)
        *reinterpret_cast<volatile Word*>(address + 8u) = 0;
    *reinterpret_cast<volatile uint8_t*>(address + 20u) = 1;
    *reinterpret_cast<volatile uint8_t*>(address + 21u) = 0;
    return node;
}
extern "C" OriginalTree12* __attribute__((thiscall)) FUN_0041fcb0(OriginalTree12* self) {
    self->header = FUN_0053a7e0();
    self->header->is_header = 1;
    self->header->parent = self->header;
    self->header->left = self->header;
    self->header->right = self->header;
    self->count = 0;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_0041d3f0(OriginalTree12* self,
                                                       OriginalTreeNode24* node) {
    while (node->is_header == 0) {
        FUN_0041d3f0(self, node->right);
        OriginalTreeNode24* current = node;
        node = node->left;
        fun_005cc620(current);
    }
}
extern "C" OriginalTreeNode24* FUN_00539ea0(OriginalTreeNode24* node) {
    while (node->left->is_header == 0)
        node = node->left;
    return node;
}
extern "C" OriginalTreeNode24* FUN_004cc110(OriginalTreeNode24* node) {
    while (node->right->is_header == 0)
        node = node->right;
    return node;
}
extern "C" void __attribute__((thiscall)) FUN_00421780(OriginalTreeNode24** iterator) {
    OriginalTreeNode24* node = *iterator;
    if (node->is_header == 0) {
        OriginalTreeNode24* next = node->right;
        if (next->is_header == 0) {
            while (next->left->is_header == 0)
                next = next->left;
            *iterator = next;
        } else {
            OriginalTreeNode24* parent = node->parent;
            while (parent->is_header == 0 && *iterator == parent->right) {
                *iterator = parent;
                parent = parent->parent;
            }
            *iterator = parent;
        }
    }
}
extern "C" void __attribute__((thiscall)) FUN_00421720(OriginalTree12* self,
                                                       OriginalTreeNode24* node) {
    OriginalTreeNode24* right = node->right;
    node->right = right->left;
    if (right->left->is_header == 0)
        right->left->parent = node;
    right->parent = node->parent;
    if (node == self->header->parent)
        self->header->parent = right;
    else if (node == node->parent->left)
        node->parent->left = right;
    else
        node->parent->right = right;
    right->left = node;
    node->parent = right;
}
extern "C" void __attribute__((thiscall)) FUN_00444130(OriginalTree12* self,
                                                       OriginalTreeNode24* node) {
    OriginalTreeNode24* left = node->left;
    node->left = left->right;
    if (left->right->is_header == 0)
        left->right->parent = node;
    left->parent = node->parent;
    if (node == self->header->parent)
        self->header->parent = left;
    else if (node == node->parent->right)
        node->parent->right = left;
    else
        node->parent->left = left;
    left->right = node;
    node->parent = left;
}
extern "C" OriginalTreeNode24** __attribute__((thiscall)) FUN_0041ee30(OriginalTree12* self,
                                                                       OriginalTreeNode24** output,
                                                                       OriginalTreeNode24* first,
                                                                       OriginalTreeNode24* last) {
    if (first == self->header->left && last == self->header) {
        FUN_0041d3f0(self, self->header->parent);
        self->header->parent = self->header;
        self->count = 0;
        self->header->left = self->header;
        self->header->right = self->header;
        *output = self->header->left;
    } else {
        while (first != last) {
            OriginalTreeNode24* current = first;
            FUN_00421780(&first);
            OriginalTreeNode24* discarded;
            FUN_0041e730(self, &discarded, current);
        }
        *output = first;
    }
    return output;
}
extern "C" void __attribute__((thiscall)) FUN_0041f2b0(OriginalTree12* self) {
    OriginalTreeNode24* discarded;
    FUN_0041ee30(self, &discarded, self->header->left, self->header);
    fun_005cc620(self->header);
    self->header = nullptr;
    self->count = 0;
}
