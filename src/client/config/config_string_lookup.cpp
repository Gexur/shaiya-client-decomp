#include "config_string_lookup.h"
#include "core/string_internal.h"
#include "core/string_compare.h"
#include "runtime/allocations.h"
#include "runtime/character_case.h"
using shaiya::recovered_string::data;
namespace {
/**
 * @brief Move a recovered tree iterator to the preceding node.
 * @param iterator Address of the iterator node pointer to update.
 */
template <class Node> void decrement_tree_iterator(Node** iterator) {
    Node* node = *iterator;
    if (node->is_header) {
        *iterator = node->right;
        return;
    }
    Node* left_child = node->left;
    if (left_child->is_header == 0) {
        while (left_child->right->is_header == 0)
            left_child = left_child->right;
        *iterator = left_child;
        return;
    }
    Node* parent = node->parent;
    while (parent->is_header == 0 && *iterator == parent->left) {
        *iterator = parent;
        parent = parent->parent;
    }
    if (parent->is_header == 0)
        *iterator = parent;
}
/**
 * @brief Compare configuration-string bytes lexicographically as unsigned bytes.
 * @param left_string Left string whose stored bytes and length are compared.
 * @param right_string Right string whose stored bytes and length are compared.
 * @return Negative, zero or positive according to byte and length ordering.
 */
int compare_config_string_bytes(const ConfigString* left_string, const ConfigString* right_string) {
    const uint8_t *left_bytes = data(left_string), *right_bytes = data(right_string);
    uint32_t common_length = left_string->size_014 < right_string->size_014
                                 ? left_string->size_014
                                 : right_string->size_014;
    for (uint32_t index = 0; index < common_length; ++index) {
        if (left_bytes[index] < right_bytes[index])
            return -1;
        if (left_bytes[index] > right_bytes[index])
            return 1;
    }
    return left_string->size_014 < right_string->size_014
               ? -1
               : left_string->size_014 != right_string->size_014;
}
/**
 * @brief Find the first node with a key at least as large as the requested key.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param key Configuration key whose stored bytes and length are used.
 * @return A candidate node, or the tree header when the key sorts after all nodes.
 */
template <class Tree, class Node> Node* lower_bound_tree_key(Tree* tree, const ConfigString* key) {
    Node *candidate = tree->header, *node = candidate->parent;
    while (node->is_header == 0) {
        const auto* node_key =
            reinterpret_cast<const ConfigString*>(reinterpret_cast<const uint8_t*>(node) + 12);
        if (compare_config_string_bytes(node_key, key) < 0)
            node = node->right;
        else {
            candidate = node;
            node = node->left;
        }
    }
    return candidate;
}
} // namespace
/**
 * @brief Compare two configuration keys using the recovered string ordering.
 *
 * Recovered Ep5.4 entry: 0x0040ac10.
 * @param unused_comparator Unused comparator object retained for thiscall compatibility.
 * @param left_key Left operand of the ordering comparison.
 * @param right_key Right operand of the ordering comparison.
 * @return True when the left key sorts before the right key.
 */
extern "C" bool __attribute__((thiscall)) config_key_less([[maybe_unused]] void* unused_comparator,
                                                          const ConfigString* left_key,
                                                          const ConfigString* right_key) {
    return FUN_0040a670(const_cast<ConfigString*>(left_key), 0, left_key->size_014, data(right_key),
                        right_key->size_014) < 0;
}
/**
 * @brief Move a section-tree iterator to its predecessor, including the end sentinel.
 *
 * Recovered Ep5.4 entry: 0x005b8940.
 * @param iterator Address of the iterator node pointer to update.
 */
extern "C" void __attribute__((thiscall))
decrement_config_section_iterator(OriginalNestedNode56** iterator) {
    decrement_tree_iterator(iterator);
}
/**
 * @brief Move a value-tree iterator to its predecessor, including the end sentinel.
 *
 * Recovered Ep5.4 entry: 0x005b89a0.
 * @param iterator Address of the iterator node pointer to update.
 */
extern "C" void __attribute__((thiscall))
decrement_config_value_iterator(OriginalNestedNode72** iterator) {
    decrement_tree_iterator(iterator);
}
/**
 * @brief Find the first section node whose key does not sort before the requested key.
 *
 * Recovered Ep5.4 entry: 0x005b8c50.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param key Configuration key whose stored bytes and length are used.
 * @return A candidate section node, or the header when no candidate exists.
 */
extern "C" OriginalNestedNode56* __attribute__((thiscall))
lower_bound_config_section(OriginalNestedTree56* tree, const ConfigString* key) {
    return lower_bound_tree_key<OriginalNestedTree56, OriginalNestedNode56>(tree, key);
}
/**
 * @brief Find the first value node whose key does not sort before the requested key.
 *
 * Recovered Ep5.4 entry: 0x005b8d10.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param key Configuration key whose stored bytes and length are used.
 * @return A candidate value node, or the header when no candidate exists.
 */
extern "C" OriginalNestedNode72* __attribute__((thiscall))
lower_bound_config_value(OriginalNestedTree72* tree, const ConfigString* key) {
    return lower_bound_tree_key<OriginalNestedTree72, OriginalNestedNode72>(tree, key);
}
/**
 * @brief Apply a character operation to each signed input byte and copy the low result byte.
 *
 * The source range is half-open; output_end receives the destination past its last write. Recovered Ep5.4 entry: 0x005bee80.
 * @param output_end Receives the destination pointer after the final transformed byte.
 * @param first First signed source byte in the half-open input range.
 * @param last Source pointer immediately past the input range.
 * @param destination Writable transformed-byte range; may alias the source range.
 * @param operation Character operation called once for each sign-extended input byte.
 */
extern "C" void transform_config_bytes(uint8_t** output_end, const int8_t* first,
                                       const int8_t* last, uint8_t* destination,
                                       int32_t (*operation)(int32_t character)) {
    while (first != last) {
        const uint8_t value = static_cast<uint8_t>(operation(*first));
        ++first;
        *destination = value;
        ++destination;
    }
    *output_end = destination;
}
/**
 * @brief Convert every stored key byte in place through the recovered lowercase routine.
 *
 * Does not change the string length or its trailing terminator. Recovered Ep5.4 entry: 0x005beed0.
 * @param string Recovered string whose existing stored bytes are modified in place.
 */
extern "C" void lowercase_config_key(ConfigString* string) {
    auto* first = reinterpret_cast<int8_t*>(data(string));
    uint8_t* output_end;
    transform_config_bytes(&output_end, first, first + string->size_014,
                           reinterpret_cast<uint8_t*>(first), fun_005d0969);
}
/**
 * @brief Find an exact section key without inserting a node.
 *
 * Recovered Ep5.4 entry: 0x005bfd60.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param key Configuration key whose stored bytes and length are used.
 * @return The output pointer, containing a matching node or the section-tree header.
 */
extern "C" OriginalNestedNode56** __attribute__((thiscall))
find_config_section(OriginalNestedTree56* tree, OriginalNestedNode56** output,
                    const ConfigString* key) {
    auto* node = lower_bound_config_section(tree, key);
    *output = node != tree->header &&
                      FUN_0040a670(const_cast<ConfigString*>(key), 0, key->size_014,
                                   data(&node->payload.key), node->payload.key.size_014) >= 0
                  ? node
                  : tree->header;
    return output;
}
/**
 * @brief Find an exact value key without inserting a node.
 *
 * Recovered Ep5.4 entry: 0x005bfdd0.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param key Configuration key whose stored bytes and length are used.
 * @return The output pointer, containing a matching node or the value-tree header.
 */
extern "C" OriginalNestedNode72** __attribute__((thiscall))
find_config_value(OriginalNestedTree72* tree, OriginalNestedNode72** output,
                  const ConfigString* key) {
    auto* node = lower_bound_config_value(tree, key);
    *output = node != tree->header && FUN_0040a670(const_cast<ConfigString*>(key), 0, key->size_014,
                                                   data(&node->key), node->key.size_014) >= 0
                  ? node
                  : tree->header;
    return output;
}
/**
 * @brief Copy-construct a string from the mapped value referenced by a value proxy.
 *
 * Recovered Ep5.4 entry: 0x005bffa0.
 * @param proxy Proxy referencing a mapped string or section tree as required by its type.
 * @param output Caller-provided storage for the function result.
 * @return The newly initialized output string.
 */
extern "C" ConfigString* __attribute__((thiscall))
copy_config_proxy_string(ConfigStringProxy* proxy, ConfigString* output) {
    output->capacity_018 = 15;
    output->size_014 = 0;
    output->storage_004[0] = 0;
    FUN_00405620(output, static_cast<ConfigString*>(proxy->value), 0, 0xffffffffu);
    return output;
}
/**
 * @brief Restore the value-proxy deleting table and optionally free the proxy storage.
 *
 * Only bit zero of the low flags byte controls deallocation. Recovered Ep5.4 entry: 0x005b8a20.
 * @param proxy Proxy referencing a mapped string or section tree as required by its type.
 * @param flags Recovered flags word, with only the documented bits interpreted here.
 * @return The original proxy address.
 */
extern "C" void* __attribute__((thiscall)) destroy_config_value_proxy(void* proxy, uint32_t flags) {
    static_cast<ConfigStringProxy*>(proxy)->table = dat_006cf8e4;
    if (static_cast<uint8_t>(flags) & 1)
        fun_005cc620(proxy);
    return proxy;
}
/**
 * @brief Restore the section-proxy deleting table and optionally free the proxy storage.
 *
 * Only bit zero of the low flags byte controls deallocation. Recovered Ep5.4 entry: 0x005b8a40.
 * @param proxy Proxy referencing a mapped string or section tree as required by its type.
 * @param flags Recovered flags word, with only the documented bits interpreted here.
 * @return The original proxy address.
 */
extern "C" void* __attribute__((thiscall)) destroy_config_section_proxy(void* proxy,
                                                                        uint32_t flags) {
    static_cast<ConfigStringProxy*>(proxy)->table = dat_006cf8e8;
    if (static_cast<uint8_t>(flags) & 1)
        fun_005cc620(proxy);
    return proxy;
}
extern "C" const OriginalNestedDeleting dat_006cf8e4[1] = {destroy_config_value_proxy},
                                        dat_006cf8e8[1] = {destroy_config_section_proxy};
