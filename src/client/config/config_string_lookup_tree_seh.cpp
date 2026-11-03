#include "config_string_lookup.h"
#include "core/string_internal.h"
#include "core/string_compare.h"
#include "core/resource_tree72_allocate.h"
#include "runtime/allocations.h"
#include "runtime/string_errors.h"
using shaiya::recovered_string::data;
namespace {
/**
 * @brief Initialize the recovered inline representation of an empty configuration string.
 * @param string Recovered string whose existing stored bytes are modified in place.
 */
void initialize_empty_config_string(ConfigString* string) {
    string->capacity_018 = 15;
    string->size_014 = 0;
    string->storage_004[0] = 0;
}
struct StringCleanup {
    ConfigString* string;
    bool active = true;
    /**
     * @brief Destroy an active temporary configuration string on scope exit or unwinding.
     */
    ~StringCleanup() noexcept(false) {
        if (active)
            FUN_00529db0(string);
    }
};
struct AllocationCleanup {
    void* allocation;
    bool active = true;
    /**
     * @brief Free a node allocation until its payload construction succeeds.
     */
    ~AllocationCleanup() noexcept(false) {
        if (active)
            fun_005cc620(allocation);
    }
};
struct TreeCleanup {
    OriginalNestedTree72* tree;
    bool active = true;
    /**
     * @brief Destroy an active temporary or partially constructed value tree.
     */
    ~TreeCleanup() noexcept(false) {
        if (active)
            FUN_004c33e0(tree);
    }
};
struct PayloadCleanup {
    OriginalNestedPayload40* payload;
    bool active = true;
    /**
     * @brief Destroy an active temporary section key and value-tree payload.
     */
    ~PayloadCleanup() noexcept(false) {
        if (active)
            FUN_004c3410(payload);
    }
};
struct SubtreeCleanup {
    OriginalNestedTree72* tree;
    OriginalNestedNode72* subtree;
    bool active = true;
    /**
     * @brief Destroy a partially cloned value subtree if a descendant copy throws.
     */
    ~SubtreeCleanup() noexcept(false) {
        if (active)
            FUN_004c32e0(tree, subtree);
    }
};
/**
 * @brief Throw the recovered map/set length-error object when insertion exceeds its node limit.
 *
 * Does not return; its temporary message retains recovered destruction behavior.
 */
[[noreturn]] void throw_config_tree_length_error() {
    ConfigString message;
    initialize_empty_config_string(&message);
    FUN_00405710(&message, "map/set<T> too long", 19);
    StringCleanup cleanup{&message};
    OriginalLogicError error;
    FUN_0040ad80(&error, &message);
    error.base.vtable = &dat_006dbc80;
    fun_005cce46(&error, const_cast<CxxThrowInfo*>(&dat_006fa52c));
    __builtin_unreachable();
}
struct SectionTreeOperations {
    using Node = OriginalNestedNode56;
    using Tree = OriginalNestedTree56;
    using Payload = OriginalNestedPayload40;
    using Result = ConfigInsert56;
    /**
     * @brief Access the string key in a node or copied payload.
     * @param node Tree node whose key or links are accessed.
     * @return A borrowed pointer to the key owned by the supplied node or payload.
     */
    static const ConfigString* key_of(Node* node) {
        return &node->payload.key;
    }
    /**
     * @brief Access the string key in a node or copied payload.
     * @param payload Copied payload whose key is accessed.
     * @return A borrowed pointer to the key owned by the supplied node or payload.
     */
    static const ConfigString* key_of(const Payload* payload) {
        return &payload->key;
    }
    /**
     * @brief Allocate a red node with sentinel children and copy its payload.
     * @param tree Tree whose recovered sentinel and node links are used.
     * @param parent Parent tree node, or containing archive directory where applicable.
     * @param value Value or payload copied into the destination node or pair.
     * @return The allocated node returned by the corresponding recovered allocation entry.
     */
    static Node* allocate_node(Tree* tree, Node* parent, const Payload* value) {
        return allocate_config_section_node(tree, tree->header, parent, tree->header, value, 0);
    }
    /**
     * @brief Insert a node at the requested parent branch and restore red/black balance.
     * @param tree Tree whose recovered sentinel and node links are used.
     * @param output Caller-provided storage for the function result.
     * @param insert_left Nonzero inserts as the parent left child; zero selects the right child.
     * @param parent Parent tree node, or containing archive directory where applicable.
     * @param value Value or payload copied into the destination node or pair.
     * @return The output pointer, containing the inserted node.
     */
    static Node** insert_and_rebalance(Tree* tree, Node** output, uint8_t insert_left, Node* parent,
                                       const Payload* value) {
        return insert_config_section_node(tree, output, insert_left, parent, value);
    }
    /**
     * @brief Rotate a configuration subtree left through its recovered tree-family entry.
     * @param tree Tree whose recovered sentinel and node links are used.
     * @param pivot Root of the subtree to rotate.
     */
    static void rotate_left(Tree* tree, Node* pivot) {
        FUN_004c1440(tree, pivot);
    }
    /**
     * @brief Rotate a configuration subtree right through its recovered tree-family entry.
     * @param tree Tree whose recovered sentinel and node links are used.
     * @param pivot Root of the subtree to rotate.
     */
    static void rotate_right(Tree* tree, Node* pivot) {
        FUN_004c0900(tree, pivot);
    }
    /**
     * @brief Move a configuration-tree iterator to its predecessor.
     * @param iterator Address of the iterator node pointer to update.
     */
    static void decrement_iterator(Node** iterator) {
        decrement_config_section_iterator(iterator);
    }
    /**
     * @brief Move a configuration-tree iterator to its successor.
     * @param iterator Address of the iterator node pointer to update.
     */
    static void increment_iterator(Node** iterator) {
        FUN_004c0a40(iterator);
    }
    /**
     * @brief Insert a unique payload or report the node already holding its key.
     * @param tree Tree whose recovered sentinel and node links are used.
     * @param output Caller-provided storage for the function result.
     * @param value Value or payload copied into the destination node or pair.
     * @return The insertion result containing the node and inserted flag.
     */
    static Result* insert_unique_payload(Tree* tree, Result* output, const Payload* value) {
        return insert_unique_config_section(tree, output, value);
    }
    static constexpr uint32_t maximum = 0x06666664u;
};
struct ValueTreeOperations {
    using Node = OriginalNestedNode72;
    using Tree = OriginalNestedTree72;
    using Payload = ConfigStringPair;
    using Result = ConfigInsert72;
    /**
     * @brief Access the string key in a node or copied payload.
     * @param node Tree node whose key or links are accessed.
     * @return A borrowed pointer to the key owned by the supplied node or payload.
     */
    static const ConfigString* key_of(Node* node) {
        return &node->key;
    }
    /**
     * @brief Access the string key in a node or copied payload.
     * @param payload Copied payload whose key is accessed.
     * @return A borrowed pointer to the key owned by the supplied node or payload.
     */
    static const ConfigString* key_of(const Payload* payload) {
        return &payload->key;
    }
    /**
     * @brief Allocate a red node with sentinel children and copy its payload.
     * @param tree Tree whose recovered sentinel and node links are used.
     * @param parent Parent tree node, or containing archive directory where applicable.
     * @param value Value or payload copied into the destination node or pair.
     * @return The allocated node returned by the corresponding recovered allocation entry.
     */
    static Node* allocate_node(Tree* tree, Node* parent, const Payload* value) {
        return allocate_config_value_node(tree, tree->header, parent, tree->header, value, 0);
    }
    /**
     * @brief Insert a node at the requested parent branch and restore red/black balance.
     * @param tree Tree whose recovered sentinel and node links are used.
     * @param output Caller-provided storage for the function result.
     * @param insert_left Nonzero inserts as the parent left child; zero selects the right child.
     * @param parent Parent tree node, or containing archive directory where applicable.
     * @param value Value or payload copied into the destination node or pair.
     * @return The output pointer, containing the inserted node.
     */
    static Node** insert_and_rebalance(Tree* tree, Node** output, uint8_t insert_left, Node* parent,
                                       const Payload* value) {
        return insert_config_value_node(tree, output, insert_left, parent, value);
    }
    /**
     * @brief Rotate a configuration subtree left through its recovered tree-family entry.
     * @param tree Tree whose recovered sentinel and node links are used.
     * @param pivot Root of the subtree to rotate.
     */
    static void rotate_left(Tree* tree, Node* pivot) {
        FUN_004c14a0(tree, pivot);
    }
    /**
     * @brief Rotate a configuration subtree right through its recovered tree-family entry.
     * @param tree Tree whose recovered sentinel and node links are used.
     * @param pivot Root of the subtree to rotate.
     */
    static void rotate_right(Tree* tree, Node* pivot) {
        FUN_004c0960(tree, pivot);
    }
    /**
     * @brief Move a configuration-tree iterator to its predecessor.
     * @param iterator Address of the iterator node pointer to update.
     */
    static void decrement_iterator(Node** iterator) {
        decrement_config_value_iterator(iterator);
    }
    /**
     * @brief Move a configuration-tree iterator to its successor.
     * @param iterator Address of the iterator node pointer to update.
     */
    static void increment_iterator(Node** iterator) {
        FUN_004c0aa0(iterator);
    }
    /**
     * @brief Insert a unique payload or report the node already holding its key.
     * @param tree Tree whose recovered sentinel and node links are used.
     * @param output Caller-provided storage for the function result.
     * @param value Value or payload copied into the destination node or pair.
     * @return The insertion result containing the node and inserted flag.
     */
    static Result* insert_unique_payload(Tree* tree, Result* output, const Payload* value) {
        return insert_unique_config_value(tree, output, value);
    }
    static constexpr uint32_t maximum = 0x04924922u;
};
/**
 * @brief Test recovered lexicographic configuration-key ordering.
 * @param left_key Left operand of the ordering comparison.
 * @param right_key Right operand of the ordering comparison.
 * @return True when the left key sorts first.
 */
bool config_string_less(const ConfigString* left_key, const ConfigString* right_key) {
    return config_key_less(nullptr, left_key, right_key);
}
// Matching original tree insertion families. Color0 is red; color1 is black.
/**
 * @brief Insert a node at the requested parent branch and restore red/black balance.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param insert_left Nonzero inserts as the parent left child; zero selects the right child.
 * @param parent Parent tree node, or containing archive directory where applicable.
 * @param value Value or payload copied into the destination node or pair.
 * @return The output pointer, containing the inserted node.
 */
template <class Operations>
typename Operations::Node**
insert_and_rebalance(typename Operations::Tree* tree, typename Operations::Node** output,
                     uint8_t insert_left, typename Operations::Node* parent,
                     const typename Operations::Payload* value) {
    using Node = typename Operations::Node;
    if (tree->count > Operations::maximum)
        throw_config_tree_length_error();
    Node* node = Operations::allocate_node(tree, parent, value);
    ++tree->count;
    if (parent == tree->header) {
        tree->header->parent = node;
        tree->header->left = node;
        tree->header->right = node;
    } else if (insert_left) {
        parent->left = node;
        if (parent == tree->header->left)
            tree->header->left = node;
    } else {
        parent->right = node;
        if (parent == tree->header->right)
            tree->header->right = node;
    }
    Node* current = node;
    while (current->parent->color == 0) {
        Node *current_parent = current->parent, *grandparent = current_parent->parent;
        if (current_parent == grandparent->left) {
            Node* uncle = grandparent->right;
            if (uncle->color == 0) {
                current_parent->color = 1;
                uncle->color = 1;
                grandparent->color = 0;
                current = grandparent;
            } else {
                if (current == current_parent->right) {
                    Operations::rotate_left(tree, current_parent);
                    current = current_parent;
                }
                current->parent->color = 1;
                current->parent->parent->color = 0;
                Operations::rotate_right(tree, current->parent->parent);
            }
        } else {
            Node* uncle = grandparent->left;
            if (uncle->color == 0) {
                current_parent->color = 1;
                uncle->color = 1;
                grandparent->color = 0;
                current = grandparent;
            } else {
                if (current == current_parent->left) {
                    Operations::rotate_right(tree, current_parent);
                    current = current_parent;
                }
                current->parent->color = 1;
                current->parent->parent->color = 0;
                Operations::rotate_left(tree, current->parent->parent);
            }
        }
    }
    tree->header->parent->color = 1;
    *output = node;
    return output;
}
/**
 * @brief Insert a unique payload or report the node already holding its key.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param value Value or payload copied into the destination node or pair.
 * @return The insertion result containing the node and inserted flag.
 */
template <class Operations>
typename Operations::Result* insert_unique_payload(typename Operations::Tree* tree,
                                                   typename Operations::Result* output,
                                                   const typename Operations::Payload* value) {
    using Node = typename Operations::Node;
    Node *parent = tree->header, *node = parent->parent;
    bool insert_left = true;
    while (node->is_header == 0) {
        parent = node;
        insert_left = config_string_less(Operations::key_of(value), Operations::key_of(node));
        node = insert_left ? node->left : node->right;
    }
    Node* before = parent;
    if (insert_left) {
        if (parent == tree->header->left) {
            Node* added;
            Operations::insert_and_rebalance(tree, &added, 1, parent, value);
            output->node = added;
            output->inserted = 1;
            return output;
        }
        Operations::decrement_iterator(&before);
    }
    const ConfigString *preceding_key = Operations::key_of(before),
                       *value_key = Operations::key_of(value);
    if (FUN_0040a670(const_cast<ConfigString*>(preceding_key), 0, preceding_key->size_014,
                     data(value_key), value_key->size_014) < 0) {
        Node* added;
        Operations::insert_and_rebalance(tree, &added, insert_left, parent, value);
        output->node = added;
        output->inserted = 1;
    } else {
        output->node = before;
        output->inserted = 0;
    }
    return output;
}
/**
 * @brief Try a neighboring-node insertion hint before searching the entire tree.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param hint_node Candidate insertion neighbor, or the tree header for an end hint.
 * @param value Value or payload copied into the destination node or pair.
 * @return The output pointer, containing the inserted or existing node.
 */
template <class Operations>
typename Operations::Node** insert_payload_with_hint(typename Operations::Tree* tree,
                                                     typename Operations::Node** output,
                                                     typename Operations::Node* hint_node,
                                                     const typename Operations::Payload* value) {
    using Node = typename Operations::Node;
    if (tree->count == 0)
        return Operations::insert_and_rebalance(tree, output, 1, tree->header, value);
    if (hint_node == tree->header->left) {
        if (config_string_less(Operations::key_of(value), Operations::key_of(hint_node)))
            return Operations::insert_and_rebalance(tree, output, 1, hint_node, value);
    } else if (hint_node == tree->header) {
        if (config_string_less(Operations::key_of(tree->header->right), Operations::key_of(value)))
            return Operations::insert_and_rebalance(tree, output, 0, tree->header->right, value);
    } else {
        if (config_string_less(Operations::key_of(value), Operations::key_of(hint_node))) {
            Node* before = hint_node;
            Operations::decrement_iterator(&before);
            if (config_string_less(Operations::key_of(before), Operations::key_of(value))) {
                if (before->right->is_header)
                    return Operations::insert_and_rebalance(tree, output, 0, before, value);
                return Operations::insert_and_rebalance(tree, output, 1, hint_node, value);
            }
        }
        if (config_string_less(Operations::key_of(hint_node), Operations::key_of(value))) {
            Node* after = hint_node;
            Operations::increment_iterator(&after);
            if (after == tree->header ||
                config_string_less(Operations::key_of(value), Operations::key_of(after))) {
                if (hint_node->right->is_header)
                    return Operations::insert_and_rebalance(tree, output, 0, hint_node, value);
                return Operations::insert_and_rebalance(tree, output, 1, after, value);
            }
        }
    }
    typename Operations::Result result;
    Operations::insert_unique_payload(tree, &result, value);
    *output = result.node;
    return output;
}
} // namespace
/**
 * @brief Copy-construct a configuration key/value pair with cleanup of a partial key.
 *
 * Recovered Ep5.4 entry: 0x005b8e20.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param key Configuration key whose stored bytes and length are used.
 * @param value Value or payload copied into the destination node or pair.
 * @return The initialized pair.
 */
extern "C" ConfigStringPair* __attribute__((thiscall))
construct_config_key_value(ConfigStringPair* self, const ConfigString* key,
                           const ConfigString* value) {
    initialize_empty_config_string(&self->key);
    FUN_00405620(&self->key, key, 0, 0xffffffffu);
    StringCleanup cleanup{&self->key};
    initialize_empty_config_string(&self->value);
    FUN_00405620(&self->value, value, 0, 0xffffffffu);
    cleanup.active = false;
    return self;
}
/**
 * @brief Copy-construct both strings of a configuration key/value pair.
 *
 * Recovered Ep5.4 entry: 0x005b8e90.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param source Source object to copy; it retains ownership of its storage.
 * @return The initialized pair.
 */
extern "C" ConfigStringPair* __attribute__((thiscall))
copy_config_key_value(ConfigStringPair* self, const ConfigStringPair* source) {
    return construct_config_key_value(self, &source->key, &source->value);
}
/**
 * @brief Allocate a 72-byte value-tree node and copy-construct its key/value payload.
 *
 * Recovered Ep5.4 entry: 0x005b9a80.
 * @param unused_tree Unused tree object retained for thiscall compatibility.
 * @param left Initial left-child link for the allocated node.
 * @param parent Parent tree node, or containing archive directory where applicable.
 * @param right Initial right-child link for the allocated node.
 * @param value Value or payload copied into the destination node or pair.
 * @param color Original red/black color byte: zero is red and one is black.
 * @return The allocated node, or null if allocation returns null.
 */
extern "C" OriginalNestedNode72* __attribute__((thiscall))
allocate_config_value_node([[maybe_unused]] void* unused_tree, OriginalNestedNode72* left,
                           OriginalNestedNode72* parent, OriginalNestedNode72* right,
                           const ConfigStringPair* value, uint8_t color) {
    auto* node = static_cast<OriginalNestedNode72*>(fun_005cc96d(72));
    AllocationCleanup cleanup{node};
    if (node) {
        node->left = left;
        node->parent = parent;
        node->right = right;
        copy_config_key_value(reinterpret_cast<ConfigStringPair*>(&node->key), value);
        node->color = color;
        node->is_header = 0;
    }
    cleanup.active = false;
    return node;
}
/**
 * @brief Recursively clone a value subtree while retaining node colors and parent links.
 *
 * Recovered Ep5.4 entry: 0x005b9b20.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param source Source object to copy; it retains ownership of its storage.
 * @param parent Parent tree node, or containing archive directory where applicable.
 * @return The cloned subtree root, or the destination header for an empty source.
 */
extern "C" OriginalNestedNode72* __attribute__((thiscall))
clone_config_value_subtree(OriginalNestedTree72* tree, OriginalNestedNode72* source,
                           OriginalNestedNode72* parent) {
    OriginalNestedNode72* result = tree->header;
    if (source->is_header == 0) {
        auto* node = allocate_config_value_node(tree, tree->header, parent, tree->header,
                                                reinterpret_cast<ConfigStringPair*>(&source->key),
                                                source->color);
        if (result->is_header)
            result = node;
        SubtreeCleanup cleanup{tree, node};
        node->left = clone_config_value_subtree(tree, source->left, node);
        node->right = clone_config_value_subtree(tree, source->right, node);
        cleanup.active = false;
    }
    return result;
}
/**
 * @brief Insert a value node at a selected branch and restore red/black balance.
 *
 * Recovered Ep5.4 entry: 0x005ba290.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param insert_left Nonzero inserts as the parent left child; zero selects the right child.
 * @param parent Parent tree node, or containing archive directory where applicable.
 * @param value Value or payload copied into the destination node or pair.
 * @return The output pointer, containing the inserted node.
 */
extern "C" OriginalNestedNode72** __attribute__((thiscall))
insert_config_value_node(OriginalNestedTree72* tree, OriginalNestedNode72** output,
                         uint8_t insert_left, OriginalNestedNode72* parent,
                         const ConfigStringPair* value) {
    return insert_and_rebalance<ValueTreeOperations>(tree, output, insert_left, parent, value);
}
/**
 * @brief Insert a section node at a selected branch and restore red/black balance.
 *
 * Recovered Ep5.4 entry: 0x005bb1a0.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param insert_left Nonzero inserts as the parent left child; zero selects the right child.
 * @param parent Parent tree node, or containing archive directory where applicable.
 * @param value Value or payload copied into the destination node or pair.
 * @return The output pointer, containing the inserted node.
 */
extern "C" OriginalNestedNode56** __attribute__((thiscall))
insert_config_section_node(OriginalNestedTree56* tree, OriginalNestedNode56** output,
                           uint8_t insert_left, OriginalNestedNode56* parent,
                           const OriginalNestedPayload40* value) {
    return insert_and_rebalance<SectionTreeOperations>(tree, output, insert_left, parent, value);
}
/**
 * @brief Clone a value tree into an initialized empty tree and update its extrema.
 *
 * Recovered Ep5.4 entry: 0x005ba440.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param source Source object to copy; it retains ownership of its storage.
 */
extern "C" void __attribute__((thiscall))
clone_config_value_tree(OriginalNestedTree72* tree, const OriginalNestedTree72* source) {
    auto* header = tree->header;
    header->parent = clone_config_value_subtree(tree, source->header->parent, header);
    tree->count = source->count;
    if (header->parent->is_header == 0) {
        auto* node = header->parent;
        while (node->left->is_header == 0)
            node = node->left;
        header->left = node;
        node = header->parent;
        while (node->right->is_header == 0)
            node = node->right;
        header->right = node;
    } else {
        header->left = header;
        header->right = header;
    }
}
/**
 * @brief Insert a unique configuration key/value pair or report its existing node.
 *
 * Recovered Ep5.4 entry: 0x005ba750.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param value Value or payload copied into the destination node or pair.
 * @return The output result, with the node and a one-byte inserted flag.
 */
extern "C" ConfigInsert72* __attribute__((thiscall))
insert_unique_config_value(OriginalNestedTree72* tree, ConfigInsert72* output,
                           const ConfigStringPair* value) {
    return insert_unique_payload<ValueTreeOperations>(tree, output, value);
}
/**
 * @brief Insert a unique configuration section or report its existing node.
 *
 * Recovered Ep5.4 entry: 0x005bb350.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param value Value or payload copied into the destination node or pair.
 * @return The output result, with the node and a one-byte inserted flag.
 */
extern "C" ConfigInsert56* __attribute__((thiscall))
insert_unique_config_section(OriginalNestedTree56* tree, ConfigInsert56* output,
                             const OriginalNestedPayload40* value) {
    return insert_unique_payload<SectionTreeOperations>(tree, output, value);
}
/**
 * @brief Insert a unique configuration value using a neighboring node as a hint.
 *
 * Recovered Ep5.4 entry: 0x005baa50.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param hint Candidate insertion neighbor, or the tree header for an end hint.
 * @param value Value or payload copied into the destination node or pair.
 * @return The output pointer, containing the inserted or existing node.
 */
extern "C" OriginalNestedNode72** __attribute__((thiscall))
insert_config_value_with_hint(OriginalNestedTree72* tree, OriginalNestedNode72** output,
                              OriginalNestedNode72* hint, const ConfigStringPair* value) {
    return insert_payload_with_hint<ValueTreeOperations>(tree, output, hint, value);
}
/**
 * @brief Insert a unique configuration section using a neighboring node as a hint.
 *
 * Recovered Ep5.4 entry: 0x005bb4d0.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param hint Candidate insertion neighbor, or the tree header for an end hint.
 * @param value Value or payload copied into the destination node or pair.
 * @return The output pointer, containing the inserted or existing node.
 */
extern "C" OriginalNestedNode56** __attribute__((thiscall))
insert_config_section_with_hint(OriginalNestedTree56* tree, OriginalNestedNode56** output,
                                OriginalNestedNode56* hint, const OriginalNestedPayload40* value) {
    return insert_payload_with_hint<SectionTreeOperations>(tree, output, hint, value);
}
/**
 * @brief Construct a value-tree sentinel and clone the source tree.
 *
 * Recovered Ep5.4 entry: 0x005bac00.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param source Source object to copy; it retains ownership of its storage.
 * @return The initialized destination tree.
 */
extern "C" OriginalNestedTree72* __attribute__((thiscall))
copy_construct_config_value_tree(OriginalNestedTree72* tree, const OriginalNestedTree72* source) {
    tree->header = FUN_005b8ac0();
    auto* header = tree->header;
    header->is_header = 1;
    header->parent = header;
    header->left = header;
    header->right = header;
    tree->count = 0;
    TreeCleanup cleanup{tree};
    clone_config_value_tree(tree, source);
    cleanup.active = false;
    return tree;
}
/**
 * @brief Copy-construct a section key and an explicitly supplied value tree.
 *
 * Recovered Ep5.4 entry: 0x005bb090.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param key Configuration key whose stored bytes and length are used.
 * @param values Source tree of key/value strings copied into the section.
 * @return The initialized section payload.
 */
extern "C" OriginalNestedPayload40* __attribute__((thiscall))
construct_config_section_payload(OriginalNestedPayload40* self, const ConfigString* key,
                                 const OriginalNestedTree72* values) {
    initialize_empty_config_string(&self->key);
    FUN_00405620(&self->key, key, 0, 0xffffffffu);
    StringCleanup cleanup{&self->key};
    copy_construct_config_value_tree(&self->values, values);
    cleanup.active = false;
    return self;
}
/**
 * @brief Copy-construct a section key and its nested value tree.
 *
 * Recovered Ep5.4 entry: 0x005baf70.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param source Source object to copy; it retains ownership of its storage.
 * @return The initialized section payload.
 */
extern "C" OriginalNestedPayload40* __attribute__((thiscall))
copy_config_section_payload(OriginalNestedPayload40* self, const OriginalNestedPayload40* source) {
    return construct_config_section_payload(self, &source->key, &source->values);
}
/**
 * @brief Allocate a 56-byte section node and copy-construct its nested tree payload.
 *
 * Recovered Ep5.4 entry: 0x005bb100.
 * @param unused_tree Unused tree object retained for thiscall compatibility.
 * @param left Initial left-child link for the allocated node.
 * @param parent Parent tree node, or containing archive directory where applicable.
 * @param right Initial right-child link for the allocated node.
 * @param value Value or payload copied into the destination node or pair.
 * @param color Original red/black color byte: zero is red and one is black.
 * @return The allocated node, or null if allocation returns null.
 */
extern "C" OriginalNestedNode56* __attribute__((thiscall))
allocate_config_section_node([[maybe_unused]] void* unused_tree, OriginalNestedNode56* left,
                             OriginalNestedNode56* parent, OriginalNestedNode56* right,
                             const OriginalNestedPayload40* value, uint8_t color) {
    auto* node = static_cast<OriginalNestedNode56*>(fun_005cc96d(56));
    AllocationCleanup cleanup{node};
    if (node) {
        node->left = left;
        node->parent = parent;
        node->right = right;
        copy_config_section_payload(&node->payload, value);
        node->color = color;
        node->is_header = 0;
    }
    cleanup.active = false;
    return node;
}
/**
 * @brief Return a mapped configuration string, inserting an empty value when absent.
 *
 * Recovered Ep5.4 entry: 0x005bae60.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param key Configuration key whose stored bytes and length are used.
 * @return The mapped string owned by the value tree.
 */
extern "C" ConfigString* __attribute__((thiscall))
get_or_insert_config_value(OriginalNestedTree72* tree, const ConfigString* key) {
    auto* node = lower_bound_config_value(tree, key);
    if (node != tree->header && FUN_0040a670(const_cast<ConfigString*>(key), 0, key->size_014,
                                             data(&node->key), node->key.size_014) >= 0)
        return &node->value;
    ConfigString fallback;
    initialize_empty_config_string(&fallback);
    StringCleanup fallback_cleanup{&fallback};
    ConfigStringPair pair;
    construct_config_key_value(&pair, key, &fallback);
    StringCleanup key_cleanup{&pair.key};
    StringCleanup value_cleanup{&pair.value};
    OriginalNestedNode72* added;
    insert_config_value_with_hint(tree, &added, node, &pair);
    return &added->value;
}
/**
 * @brief Return a section value tree, inserting an empty tree when the key is absent.
 *
 * Recovered Ep5.4 entry: 0x005bb680.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param key Configuration key whose stored bytes and length are used.
 * @return The value tree owned by the section node.
 */
extern "C" OriginalNestedTree72* __attribute__((thiscall))
get_or_insert_config_section(OriginalNestedTree56* tree, const ConfigString* key) {
    auto* node = lower_bound_config_section(tree, key);
    if (node != tree->header &&
        FUN_0040a670(const_cast<ConfigString*>(key), 0, key->size_014, data(&node->payload.key),
                     node->payload.key.size_014) >= 0)
        return &node->payload.values;
    OriginalNestedTree72 empty;
    empty.header = FUN_005b8ac0();
    auto* header = empty.header;
    header->is_header = 1;
    header->left = header;
    header->parent = header;
    header->right = header;
    empty.count = 0;
    TreeCleanup empty_cleanup{&empty};
    OriginalNestedPayload40 payload;
    construct_config_section_payload(&payload, key, &empty);
    PayloadCleanup payload_cleanup{&payload};
    OriginalNestedNode56* added;
    insert_config_section_with_hint(tree, &added, node, &payload);
    return &added->payload.values;
}
