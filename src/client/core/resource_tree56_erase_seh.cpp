#include "resource_tree56.h"
#include "runtime/string_errors.h"
#include "runtime/allocations.h"
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
struct Outer {
    static void increment(OriginalNestedNode56** p) {
        FUN_004c0a40(p);
    }
    static OriginalNestedNode56* minimum(OriginalNestedNode56* p) {
        return FUN_004c09e0(p);
    }
    static OriginalNestedNode56* maximum(OriginalNestedNode56* p) {
        return FUN_004c09c0(p);
    }
    static void left(OriginalNestedTree56* t, OriginalNestedNode56* p) {
        FUN_004c1440(t, p);
    }
    static void right(OriginalNestedTree56* t, OriginalNestedNode56* p) {
        FUN_004c0900(t, p);
    }
    static void destroy(OriginalNestedNode56* p) {
        FUN_004c3410(&p->payload);
    }
};
struct Inner {
    static void increment(OriginalNestedNode72** p) {
        FUN_004c0aa0(p);
    }
    static OriginalNestedNode72* minimum(OriginalNestedNode72* p) {
        return FUN_004c0a20(p);
    }
    static OriginalNestedNode72* maximum(OriginalNestedNode72* p) {
        return FUN_004c0a00(p);
    }
    static void left(OriginalNestedTree72* t, OriginalNestedNode72* p) {
        FUN_004c14a0(t, p);
    }
    static void right(OriginalNestedTree72* t, OriginalNestedNode72* p) {
        FUN_004c0960(t, p);
    }
    static void destroy(OriginalNestedNode72* p) {
        if (p->value.capacity_018 >= 16)
            fun_005cc620(*reinterpret_cast<void**>(p->value.storage_004));
        p->value.capacity_018 = 15;
        p->value.size_014 = 0;
        p->value.storage_004[0] = 0;
        if (p->key.capacity_018 >= 16)
            fun_005cc620(*reinterpret_cast<void**>(p->key.storage_004));
        p->key.capacity_018 = 15;
        p->key.size_014 = 0;
        p->key.storage_004[0] = 0;
    }
};
// Both actual erasures retain the original two-child transplant and both
// mirrored repair branches, including blocks omitted by Ghidra's export.
template <class Node, class Tree, class Operations>
Node** erase(Tree* self, Node** output, Node* target) {
    if (target->is_header != 0) {
        InvalidIteratorMessage message;
        OriginalLogicError error;
        FUN_0040ad80(&error, &message.text);
        error.base.vtable = &dat_006dbc8c;
        fun_005cce46(&error, const_cast<CxxThrowInfo*>(&dat_006fa6dc));
        __builtin_unreachable();
    }
    Node* next = target;
    Operations::increment(&next);
    Node* child;
    Node* parent;
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
        self->header->left = child->is_header != 0 ? parent : Operations::minimum(child);
    if (self->header->right == target)
        self->header->right = child->is_header != 0 ? parent : Operations::maximum(child);
repair:
    if (target->color == 1) {
        while (child != self->header->parent && child->color == 1) {
            if (child == parent->left) {
                Node* sibling = parent->right;
                if (sibling->color == 0) {
                    sibling->color = 1;
                    parent->color = 0;
                    Operations::left(self, parent);
                    sibling = parent->right;
                }
                if (sibling->is_header == 0) {
                    if (sibling->left->color == 1 && sibling->right->color == 1)
                        sibling->color = 0;
                    else {
                        if (sibling->right->color == 1) {
                            sibling->left->color = 1;
                            sibling->color = 0;
                            Operations::right(self, sibling);
                            sibling = parent->right;
                        }
                        sibling->color = parent->color;
                        parent->color = 1;
                        sibling->right->color = 1;
                        Operations::left(self, parent);
                        break;
                    }
                }
            } else {
                Node* sibling = parent->left;
                if (sibling->color == 0) {
                    sibling->color = 1;
                    parent->color = 0;
                    Operations::right(self, parent);
                    sibling = parent->left;
                }
                if (sibling->is_header == 0) {
                    if (sibling->right->color == 1 && sibling->left->color == 1)
                        sibling->color = 0;
                    else {
                        if (sibling->left->color == 1) {
                            sibling->right->color = 1;
                            sibling->color = 0;
                            Operations::left(self, sibling);
                            sibling = parent->left;
                        }
                        sibling->color = parent->color;
                        parent->color = 1;
                        sibling->left->color = 1;
                        Operations::right(self, parent);
                        break;
                    }
                }
            }
            child = parent;
            parent = parent->parent;
        }
        child->color = 1;
    }
    Operations::destroy(target);
    fun_005cc620(target);
    if (self->count != 0)
        --self->count;
    *output = next;
    return output;
}
} // namespace
extern "C" OriginalNestedNode56** __attribute__((thiscall))
FUN_004c34b0(OriginalNestedTree56* self, OriginalNestedNode56** out, OriginalNestedNode56* target) {
    return erase<OriginalNestedNode56, OriginalNestedTree56, Outer>(self, out, target);
}
extern "C" OriginalNestedNode72** __attribute__((thiscall))
FUN_004c2fe0(OriginalNestedTree72* self, OriginalNestedNode72** out, OriginalNestedNode72* target) {
    return erase<OriginalNestedNode72, OriginalNestedTree72, Inner>(self, out, target);
}
