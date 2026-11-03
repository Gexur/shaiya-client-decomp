#include "tree48.h"

// Original5b8a00/54afd0/5b8a60/54aff0/54af70 use flag offsets2c/2d.
extern "C" OriginalTreeNode48* FUN_005b8a00(OriginalTreeNode48* node) {
    while (node->left->is_header == 0)
        node = node->left;
    return node;
}
extern "C" OriginalTreeNode48* FUN_0054afd0(OriginalTreeNode48* node) {
    while (node->right->is_header == 0)
        node = node->right;
    return node;
}
extern "C" void __attribute__((thiscall)) FUN_005b8a60(OriginalTreeNode48** iterator) {
    OriginalTreeNode48* node = *iterator;
    if (node->is_header == 0) {
        OriginalTreeNode48* next = node->right;
        if (next->is_header == 0) {
            while (next->left->is_header == 0)
                next = next->left;
            *iterator = next;
        } else {
            OriginalTreeNode48* parent = node->parent;
            while (parent->is_header == 0 && *iterator == parent->right) {
                *iterator = parent;
                parent = parent->parent;
            }
            *iterator = parent;
        }
    }
}
extern "C" void __attribute__((thiscall)) FUN_0054aff0(OriginalTree48Owner12* self,
                                                       OriginalTreeNode48* node) {
    OriginalTreeNode48* right = node->right;
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
extern "C" void __attribute__((thiscall)) FUN_0054af70(OriginalTree48Owner12* self,
                                                       OriginalTreeNode48* node) {
    OriginalTreeNode48* left = node->left;
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
