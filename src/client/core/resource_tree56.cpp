#include "resource_tree56.h"
#include "runtime/allocations.h"
namespace {
template <class Node> Node* minimum(Node* node) {
    while (node->left->is_header == 0)
        node = node->left;
    return node;
}
template <class Node> Node* maximum(Node* node) {
    while (node->right->is_header == 0)
        node = node->right;
    return node;
}
template <class Node> void increment(Node** iterator) {
    Node* node = *iterator;
    if (node->is_header == 0) {
        Node* next = node->right;
        if (next->is_header == 0) {
            while (next->left->is_header == 0)
                next = next->left;
            *iterator = next;
        } else {
            Node* parent = node->parent;
            while (parent->is_header == 0 && *iterator == parent->right) {
                *iterator = parent;
                parent = parent->parent;
            }
            *iterator = parent;
        }
    }
}
template <class Tree, class Node> void rotate_right(Tree* self, Node* node) {
    Node* left = node->left;
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
template <class Tree, class Node> void rotate_left(Tree* self, Node* node) {
    Node* right = node->right;
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
} // namespace
// Each private template expresses the matching original instruction families,
// whose flag offsets differ34/35 versus44/45. They add no original entries.
extern "C" OriginalNestedNode56* FUN_004c09c0(OriginalNestedNode56* node) {
    return maximum(node);
}
extern "C" OriginalNestedNode56* FUN_004c09e0(OriginalNestedNode56* node) {
    return minimum(node);
}
extern "C" void __attribute__((thiscall)) FUN_004c0a40(OriginalNestedNode56** value) {
    increment(value);
}
extern "C" void __attribute__((thiscall)) FUN_004c0900(OriginalNestedTree56* self,
                                                       OriginalNestedNode56* node) {
    rotate_right(self, node);
}
extern "C" void __attribute__((thiscall)) FUN_004c1440(OriginalNestedTree56* self,
                                                       OriginalNestedNode56* node) {
    rotate_left(self, node);
}
extern "C" OriginalNestedNode72* FUN_004c0a00(OriginalNestedNode72* node) {
    return maximum(node);
}
extern "C" OriginalNestedNode72* FUN_004c0a20(OriginalNestedNode72* node) {
    return minimum(node);
}
extern "C" void __attribute__((thiscall)) FUN_004c0aa0(OriginalNestedNode72** value) {
    increment(value);
}
extern "C" void __attribute__((thiscall)) FUN_004c0960(OriginalNestedTree72* self,
                                                       OriginalNestedNode72* node) {
    rotate_right(self, node);
}
extern "C" void __attribute__((thiscall)) FUN_004c14a0(OriginalNestedTree72* self,
                                                       OriginalNestedNode72* node) {
    rotate_left(self, node);
}
extern "C" OriginalNestedNode56* FUN_004c17b0() {
    auto* node = static_cast<OriginalNestedNode56*>(fun_005cc96d(56));
    const uint32_t address = reinterpret_cast<uint32_t>(node);
    if (address != 0)
        *reinterpret_cast<volatile uint32_t*>(address) = 0;
    if (address + 4u != 0)
        *reinterpret_cast<volatile uint32_t*>(address + 4u) = 0;
    if (address + 8u != 0)
        *reinterpret_cast<volatile uint32_t*>(address + 8u) = 0;
    *reinterpret_cast<volatile uint8_t*>(address + 0x34u) = 1;
    *reinterpret_cast<volatile uint8_t*>(address + 0x35u) = 0;
    return node;
}
extern "C" void __attribute__((thiscall)) FUN_004c17f0(OriginalNestedNode72* self) {
    if (self->value.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(self->value.storage_004));
    self->value.capacity_018 = 15;
    self->value.size_014 = 0;
    self->value.storage_004[0] = 0;
    if (self->key.capacity_018 >= 16)
        fun_005cc620(*reinterpret_cast<void**>(self->key.storage_004));
    self->key.size_014 = 0;
    self->key.capacity_018 = 15;
    self->key.storage_004[0] = 0;
}
extern "C" void __attribute__((thiscall)) FUN_004c34a0(OriginalNestedNode56* self) {
    FUN_004c3410(&self->payload);
}
extern "C" void __attribute__((thiscall)) FUN_004c32e0(OriginalNestedTree72* self,
                                                       OriginalNestedNode72* node) {
    while (node->is_header == 0) {
        FUN_004c32e0(self, node->right);
        OriginalNestedNode72* current = node;
        node = node->left;
        FUN_004c17f0(current);
        fun_005cc620(current);
    }
}
extern "C" void __attribute__((thiscall)) FUN_004c3780(OriginalNestedTree56* self,
                                                       OriginalNestedNode56* node) {
    while (node->is_header == 0) {
        FUN_004c3780(self, node->right);
        OriginalNestedNode56* current = node;
        node = node->left;
        FUN_004c34a0(current);
        fun_005cc620(current);
    }
}
extern "C" OriginalNestedNode72** __attribute__((thiscall))
FUN_004c3320(OriginalNestedTree72* self, OriginalNestedNode72** out, OriginalNestedNode72* first,
             OriginalNestedNode72* last) {
    if (first == self->header->left && last == self->header) {
        FUN_004c32e0(self, self->header->parent);
        self->header->parent = self->header;
        self->count = 0;
        self->header->left = self->header;
        self->header->right = self->header;
        *out = self->header->left;
    } else {
        while (first != last) {
            OriginalNestedNode72* current = first;
            FUN_004c0aa0(&first);
            OriginalNestedNode72* ignored;
            FUN_004c2fe0(self, &ignored, current);
        }
        *out = first;
    }
    return out;
}
extern "C" OriginalNestedNode56** __attribute__((thiscall))
FUN_004c37c0(OriginalNestedTree56* self, OriginalNestedNode56** out, OriginalNestedNode56* first,
             OriginalNestedNode56* last) {
    if (first == self->header->left && last == self->header) {
        FUN_004c3780(self, self->header->parent);
        self->header->parent = self->header;
        self->count = 0;
        self->header->left = self->header;
        self->header->right = self->header;
        *out = self->header->left;
    } else {
        while (first != last) {
            OriginalNestedNode56* current = first;
            FUN_004c0a40(&first);
            OriginalNestedNode56* ignored;
            FUN_004c34b0(self, &ignored, current);
        }
        *out = first;
    }
    return out;
}
extern "C" void __attribute__((thiscall)) FUN_004c33e0(OriginalNestedTree72* self) {
    OriginalNestedNode72* ignored;
    FUN_004c3320(self, &ignored, self->header->left, self->header);
    fun_005cc620(self->header);
    self->header = nullptr;
    self->count = 0;
}
extern "C" void __attribute__((thiscall)) FUN_004c3880(OriginalNestedTree56* self) {
    OriginalNestedNode56* ignored;
    FUN_004c37c0(self, &ignored, self->header->left, self->header);
    fun_005cc620(self->header);
    self->header = nullptr;
    self->count = 0;
}
extern "C" const OriginalNestedDeleting dat_006c2690[1] = {FUN_004c3970};
extern "C" void* __attribute__((thiscall)) FUN_004c3930(void* self) {
    auto* bytes = static_cast<uint8_t*>(self);
    auto* tree = reinterpret_cast<OriginalNestedTree56*>(bytes + 4);
    *reinterpret_cast<const OriginalNestedDeleting**>(self) = dat_006c2690;
    tree->header = FUN_004c17b0();
    tree->header->is_header = 1;
    tree->header->parent = tree->header;
    tree->header->left = tree->header;
    tree->header->right = tree->header;
    tree->count = 0;
    bytes[0x10] = 0;
    return self;
}
extern "C" void* __attribute__((thiscall)) FUN_004c3970(void* self, uint32_t flags) {
    FUN_004c38b0(self);
    if (uint8_t(flags) & 1)
        fun_005cc620(self);
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_005c0050(void* self) {
    auto* bytes = static_cast<uint8_t*>(self);
    auto* tree = reinterpret_cast<OriginalNestedTree56*>(bytes + 4);
    FUN_004c3780(tree, tree->header->parent);
    tree->header->parent = tree->header;
    tree->count = 0;
    tree->header->left = tree->header;
    tree->header->right = tree->header;
    bytes[0x10] = 0;
}
