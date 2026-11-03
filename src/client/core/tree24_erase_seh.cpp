#include "tree24.h"
#include "../runtime/string_errors.h"
#include "../runtime/allocations.h"

namespace {
struct InvalidIteratorMessage {
    shaiya::startup::String_00405710 text;
    InvalidIteratorMessage() {
        text.capacity_018 = 15;
        text.size_014 = 0;
        text.storage_004[0] = 0;
        FUN_00405710(&text, "invalid map/set<T> iterator", 27);
    }
    ~InvalidIteratorMessage() {
        FUN_00529db0(&text);
    }
};
} // namespace

extern "C" OriginalTreeNode24** __attribute__((thiscall))
FUN_0041e730(OriginalTree12* self, OriginalTreeNode24** output, OriginalTreeNode24* target) {
    if (target->is_header != 0) {
        InvalidIteratorMessage message;
        OriginalLogicError error;
        FUN_0040ad80(&error, &message.text);
        error.base.vtable = &dat_006dbc8c;
        fun_005cce46(&error, const_cast<CxxThrowInfo*>(&dat_006fa6dc));
        __builtin_unreachable();
    }
    OriginalTreeNode24* next = target;
    FUN_00421780(&next);
    OriginalTreeNode24* child;
    OriginalTreeNode24* parent;
    if (target->left->is_header != 0)
        child = target->right;
    else if (target->right->is_header != 0)
        child = target->left;
    else {
        child = next->right;
        if (next != target) {
            target->left->parent = next;
            next->left = target->left;
            if (next == target->right)
                parent = next;
            else {
                parent = next->parent;
                if (child->is_header == 0)
                    child->parent = parent;
                parent->left = child;
                next->right = target->right;
                target->right->parent = next;
            }
            if (self->header->parent == target)
                self->header->parent = next;
            else if (target->parent->left == target)
                target->parent->left = next;
            else
                target->parent->right = next;
            next->parent = target->parent;
            const uint8_t color = target->color;
            target->color = next->color;
            next->color = color;
            goto repair;
        }
    }
    parent = target->parent;
    if (child->is_header == 0)
        child->parent = parent;
    if (self->header->parent == target)
        self->header->parent = child;
    else if (parent->left == target)
        parent->left = child;
    else
        parent->right = child;
    if (self->header->left == target)
        self->header->left = child->is_header != 0 ? parent : FUN_00539ea0(child);
    if (self->header->right == target)
        self->header->right = child->is_header != 0 ? parent : FUN_004cc110(child);
repair:
    if (target->color == 1) {
        while (child != self->header->parent && child->color == 1) {
            if (child == parent->left) {
                OriginalTreeNode24* sibling = parent->right;
                if (sibling->color == 0) {
                    sibling->color = 1;
                    parent->color = 0;
                    FUN_00421720(self, parent);
                    sibling = parent->right;
                }
                if (sibling->is_header == 0) {
                    if (sibling->left->color == 1 && sibling->right->color == 1)
                        sibling->color = 0;
                    else {
                        if (sibling->right->color == 1) {
                            sibling->left->color = 1;
                            sibling->color = 0;
                            FUN_00444130(self, sibling);
                            sibling = parent->right;
                        }
                        sibling->color = parent->color;
                        parent->color = 1;
                        sibling->right->color = 1;
                        FUN_00421720(self, parent);
                        break;
                    }
                }
            } else {
                OriginalTreeNode24* sibling = parent->left;
                if (sibling->color == 0) {
                    sibling->color = 1;
                    parent->color = 0;
                    FUN_00444130(self, parent);
                    sibling = parent->left;
                }
                if (sibling->is_header == 0) {
                    if (sibling->right->color == 1 && sibling->left->color == 1)
                        sibling->color = 0;
                    else {
                        if (sibling->left->color == 1) {
                            sibling->right->color = 1;
                            sibling->color = 0;
                            FUN_00421720(self, sibling);
                            sibling = parent->left;
                        }
                        sibling->color = parent->color;
                        parent->color = 1;
                        sibling->left->color = 1;
                        FUN_00444130(self, parent);
                        break;
                    }
                }
            }
            child = parent;
            parent = parent->parent;
        }
        child->color = 1;
    }
    fun_005cc620(target);
    if (self->count != 0)
        --self->count;
    *output = next;
    return output;
}
