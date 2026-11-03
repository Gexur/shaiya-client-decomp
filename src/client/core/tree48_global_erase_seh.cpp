#include "tree48_global.h"
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

extern "C" OriginalTreeNode48** __attribute__((thiscall))
FUN_005b97a0(OriginalTree48Owner12* self, OriginalTreeNode48** output, OriginalTreeNode48* target) {
    if (target->is_header != 0) {
        InvalidIteratorMessage message;
        OriginalLogicError error;
        FUN_0040ad80(&error, &message.text);
        error.base.vtable = &dat_006dbc8c;
        fun_005cce46(&error, const_cast<CxxThrowInfo*>(&dat_006fa6dc));
        __builtin_unreachable();
    }
    OriginalTreeNode48* next = target;
    FUN_005b8a60(&next);
    OriginalTreeNode48* child;
    OriginalTreeNode48* parent;
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
        self->header->left = child->is_header != 0 ? parent : FUN_005b8a00(child);
    if (self->header->right == target)
        self->header->right = child->is_header != 0 ? parent : FUN_0054afd0(child);
repair:
    if (target->color == 1) {
        while (child != self->header->parent && child->color == 1) {
            if (child == parent->left) {
                OriginalTreeNode48* sibling = parent->right;
                if (sibling->color == 0) {
                    sibling->color = 1;
                    parent->color = 0;
                    FUN_0054aff0(self, parent);
                    sibling = parent->right;
                }
                if (sibling->is_header == 0) {
                    if (sibling->left->color == 1 && sibling->right->color == 1)
                        sibling->color = 0;
                    else {
                        if (sibling->right->color == 1) {
                            sibling->left->color = 1;
                            sibling->color = 0;
                            FUN_0054af70(self, sibling);
                            sibling = parent->right;
                        }
                        sibling->color = parent->color;
                        parent->color = 1;
                        sibling->right->color = 1;
                        FUN_0054aff0(self, parent);
                        break;
                    }
                }
            } else {
                OriginalTreeNode48* sibling = parent->left;
                if (sibling->color == 0) {
                    sibling->color = 1;
                    parent->color = 0;
                    FUN_0054af70(self, parent);
                    sibling = parent->left;
                }
                if (sibling->is_header == 0) {
                    if (sibling->right->color == 1 && sibling->left->color == 1)
                        sibling->color = 0;
                    else {
                        if (sibling->left->color == 1) {
                            sibling->right->color = 1;
                            sibling->color = 0;
                            FUN_0054aff0(self, sibling);
                            sibling = parent->left;
                        }
                        sibling->color = parent->color;
                        parent->color = 1;
                        sibling->left->color = 1;
                        FUN_0054af70(self, parent);
                        break;
                    }
                }
            }
            child = parent;
            parent = parent->parent;
        }
        child->color = 1;
    }
    // Original5b9a25..5b9a4f destroys the embedded string in place before
    // freeing the node; it preserves its unknown leading DWORD.
    if (target->key.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(target->key.storage_004));
    target->key.capacity_018 = 15;
    target->key.size_014 = 0;
    target->key.storage_004[0] = 0;
    fun_005cc620(target);
    if (self->count != 0)
        --self->count;
    *output = next;
    return output;
}
