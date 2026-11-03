#pragma once
#include "core/resource_tree56.h"
using ConfigString = shaiya::startup::String_00405710;
struct ConfigStringPair {
    ConfigString key, value;
};
struct ConfigStringProxy {
    const OriginalNestedDeleting* table;
    void* value;
};
struct ConfigInsert56 {
    OriginalNestedNode56* node;
    uint8_t inserted;
    uint8_t untouched[3];
};
struct ConfigInsert72 {
    OriginalNestedNode72* node;
    uint8_t inserted;
    uint8_t untouched[3];
};
extern "C" {
extern const OriginalNestedDeleting dat_006cf8e4[1], dat_006cf8e8[1];
/**
 * @brief Restore the value-proxy deleting table and optionally free the proxy storage.
 *
 * Only bit zero of the low flags byte controls deallocation. Recovered Ep5.4 entry: 0x005b8a20.
 * @param proxy Proxy referencing a mapped string or section tree as required by its type.
 * @param flags Recovered flags word, with only the documented bits interpreted here.
 * @return The original proxy address.
 */
void* __attribute__((thiscall)) destroy_config_value_proxy(void* proxy, uint32_t flags);
/**
 * @brief Restore the section-proxy deleting table and optionally free the proxy storage.
 *
 * Only bit zero of the low flags byte controls deallocation. Recovered Ep5.4 entry: 0x005b8a40.
 * @param proxy Proxy referencing a mapped string or section tree as required by its type.
 * @param flags Recovered flags word, with only the documented bits interpreted here.
 * @return The original proxy address.
 */
void* __attribute__((thiscall)) destroy_config_section_proxy(void* proxy, uint32_t flags);
/**
 * @brief Compare two configuration keys using the recovered string ordering.
 *
 * Recovered Ep5.4 entry: 0x0040ac10.
 * @param unused_comparator Unused comparator object retained for thiscall compatibility.
 * @param left_key Left operand of the ordering comparison.
 * @param right_key Right operand of the ordering comparison.
 * @return True when the left key sorts before the right key.
 */
bool __attribute__((thiscall)) config_key_less([[maybe_unused]] void* unused_comparator,
                                               const ConfigString* left_key,
                                               const ConfigString* right_key);
/**
 * @brief Move a section-tree iterator to its predecessor, including the end sentinel.
 *
 * Recovered Ep5.4 entry: 0x005b8940.
 * @param iterator Address of the iterator node pointer to update.
 */
void __attribute__((thiscall)) decrement_config_section_iterator(OriginalNestedNode56** iterator);
/**
 * @brief Move a value-tree iterator to its predecessor, including the end sentinel.
 *
 * Recovered Ep5.4 entry: 0x005b89a0.
 * @param iterator Address of the iterator node pointer to update.
 */
void __attribute__((thiscall)) decrement_config_value_iterator(OriginalNestedNode72** iterator);
/**
 * @brief Find the first section node whose key does not sort before the requested key.
 *
 * Recovered Ep5.4 entry: 0x005b8c50.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param key Configuration key whose stored bytes and length are used.
 * @return A candidate section node, or the header when no candidate exists.
 */
OriginalNestedNode56* __attribute__((thiscall))
lower_bound_config_section(OriginalNestedTree56* tree, const ConfigString* key);
/**
 * @brief Find the first value node whose key does not sort before the requested key.
 *
 * Recovered Ep5.4 entry: 0x005b8d10.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param key Configuration key whose stored bytes and length are used.
 * @return A candidate value node, or the header when no candidate exists.
 */
OriginalNestedNode72* __attribute__((thiscall)) lower_bound_config_value(OriginalNestedTree72* tree,
                                                                         const ConfigString* key);
/**
 * @brief Copy-construct a configuration key/value pair with cleanup of a partial key.
 *
 * Recovered Ep5.4 entry: 0x005b8e20.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param key Configuration key whose stored bytes and length are used.
 * @param value Value or payload copied into the destination node or pair.
 * @return The initialized pair.
 */
ConfigStringPair* __attribute__((thiscall)) construct_config_key_value(ConfigStringPair* self,
                                                                       const ConfigString* key,
                                                                       const ConfigString* value);
/**
 * @brief Copy-construct both strings of a configuration key/value pair.
 *
 * Recovered Ep5.4 entry: 0x005b8e90.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param source Source object to copy; it retains ownership of its storage.
 * @return The initialized pair.
 */
ConfigStringPair* __attribute__((thiscall)) copy_config_key_value(ConfigStringPair* self,
                                                                  const ConfigStringPair* source);
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
OriginalNestedNode72* __attribute__((thiscall))
allocate_config_value_node([[maybe_unused]] void* unused_tree, OriginalNestedNode72* left,
                           OriginalNestedNode72* parent, OriginalNestedNode72* right,
                           const ConfigStringPair* value, uint8_t color);
/**
 * @brief Recursively clone a value subtree while retaining node colors and parent links.
 *
 * Recovered Ep5.4 entry: 0x005b9b20.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param source Source object to copy; it retains ownership of its storage.
 * @param parent Parent tree node, or containing archive directory where applicable.
 * @return The cloned subtree root, or the destination header for an empty source.
 */
OriginalNestedNode72* __attribute__((thiscall))
clone_config_value_subtree(OriginalNestedTree72* tree, OriginalNestedNode72* source,
                           OriginalNestedNode72* parent);
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
OriginalNestedNode72** __attribute__((thiscall))
insert_config_value_node(OriginalNestedTree72* tree, OriginalNestedNode72** output,
                         uint8_t insert_left, OriginalNestedNode72* parent,
                         const ConfigStringPair* value);
/**
 * @brief Clone a value tree into an initialized empty tree and update its extrema.
 *
 * Recovered Ep5.4 entry: 0x005ba440.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param source Source object to copy; it retains ownership of its storage.
 */
void __attribute__((thiscall)) clone_config_value_tree(OriginalNestedTree72* tree,
                                                       const OriginalNestedTree72* source);
/**
 * @brief Insert a unique configuration key/value pair or report its existing node.
 *
 * Recovered Ep5.4 entry: 0x005ba750.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param value Value or payload copied into the destination node or pair.
 * @return The output result, with the node and a one-byte inserted flag.
 */
ConfigInsert72* __attribute__((thiscall)) insert_unique_config_value(OriginalNestedTree72* tree,
                                                                     ConfigInsert72* output,
                                                                     const ConfigStringPair* value);
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
OriginalNestedNode72** __attribute__((thiscall))
insert_config_value_with_hint(OriginalNestedTree72* tree, OriginalNestedNode72** output,
                              OriginalNestedNode72* hint, const ConfigStringPair* value);
/**
 * @brief Construct a value-tree sentinel and clone the source tree.
 *
 * Recovered Ep5.4 entry: 0x005bac00.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param source Source object to copy; it retains ownership of its storage.
 * @return The initialized destination tree.
 */
OriginalNestedTree72* __attribute__((thiscall))
copy_construct_config_value_tree(OriginalNestedTree72* tree, const OriginalNestedTree72* source);
/**
 * @brief Return a mapped configuration string, inserting an empty value when absent.
 *
 * Recovered Ep5.4 entry: 0x005bae60.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param key Configuration key whose stored bytes and length are used.
 * @return The mapped string owned by the value tree.
 */
ConfigString* __attribute__((thiscall)) get_or_insert_config_value(OriginalNestedTree72* tree,
                                                                   const ConfigString* key);
/**
 * @brief Copy-construct a section key and its nested value tree.
 *
 * Recovered Ep5.4 entry: 0x005baf70.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param source Source object to copy; it retains ownership of its storage.
 * @return The initialized section payload.
 */
OriginalNestedPayload40* __attribute__((thiscall))
copy_config_section_payload(OriginalNestedPayload40* self, const OriginalNestedPayload40* source);
/**
 * @brief Fold a key to lowercase and obtain a proxy to its mapped string.
 *
 * Inserts an empty string when the key is absent. Recovered Ep5.4 entry: 0x005bafe0.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param output Caller-provided storage for the function result.
 * @param key Configuration key whose stored bytes and length are used.
 * @return The output value proxy.
 */
ConfigStringProxy* __attribute__((thiscall))
get_config_value_proxy(ConfigStringProxy* self, ConfigStringProxy* output, const ConfigString* key);
/**
 * @brief Copy-construct a section key and an explicitly supplied value tree.
 *
 * Recovered Ep5.4 entry: 0x005bb090.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param key Configuration key whose stored bytes and length are used.
 * @param values Source tree of key/value strings copied into the section.
 * @return The initialized section payload.
 */
OriginalNestedPayload40* __attribute__((thiscall))
construct_config_section_payload(OriginalNestedPayload40* self, const ConfigString* key,
                                 const OriginalNestedTree72* values);
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
OriginalNestedNode56* __attribute__((thiscall))
allocate_config_section_node([[maybe_unused]] void* unused_tree, OriginalNestedNode56* left,
                             OriginalNestedNode56* parent, OriginalNestedNode56* right,
                             const OriginalNestedPayload40* value, uint8_t color);
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
OriginalNestedNode56** __attribute__((thiscall))
insert_config_section_node(OriginalNestedTree56* tree, OriginalNestedNode56** output,
                           uint8_t insert_left, OriginalNestedNode56* parent,
                           const OriginalNestedPayload40* value);
/**
 * @brief Insert a unique configuration section or report its existing node.
 *
 * Recovered Ep5.4 entry: 0x005bb350.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param value Value or payload copied into the destination node or pair.
 * @return The output result, with the node and a one-byte inserted flag.
 */
ConfigInsert56* __attribute__((thiscall))
insert_unique_config_section(OriginalNestedTree56* tree, ConfigInsert56* output,
                             const OriginalNestedPayload40* value);
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
OriginalNestedNode56** __attribute__((thiscall))
insert_config_section_with_hint(OriginalNestedTree56* tree, OriginalNestedNode56** output,
                                OriginalNestedNode56* hint, const OriginalNestedPayload40* value);
/**
 * @brief Return a section value tree, inserting an empty tree when the key is absent.
 *
 * Recovered Ep5.4 entry: 0x005bb680.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param key Configuration key whose stored bytes and length are used.
 * @return The value tree owned by the section node.
 */
OriginalNestedTree72* __attribute__((thiscall))
get_or_insert_config_section(OriginalNestedTree56* tree, const ConfigString* key);
/**
 * @brief Fold a section name to lowercase and obtain a proxy to its value tree.
 *
 * Inserts an empty section when the name is absent. Recovered Ep5.4 entry: 0x005bb790.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param output Caller-provided storage for the function result.
 * @param section Configuration section name, folded to lowercase by proxy lookups.
 * @return The output section proxy.
 */
ConfigStringProxy* __attribute__((thiscall))
get_config_section_proxy(void* self, ConfigStringProxy* output, const ConfigString* section);
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
void transform_config_bytes(uint8_t** output_end, const int8_t* first, const int8_t* last,
                            uint8_t* destination, int32_t (*operation)(int32_t character));
/**
 * @brief Convert every stored key byte in place through the recovered lowercase routine.
 *
 * Does not change the string length or its trailing terminator. Recovered Ep5.4 entry: 0x005beed0.
 * @param string Recovered string whose existing stored bytes are modified in place.
 */
void lowercase_config_key(ConfigString* string);
/**
 * @brief Find an exact section key without inserting a node.
 *
 * Recovered Ep5.4 entry: 0x005bfd60.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param key Configuration key whose stored bytes and length are used.
 * @return The output pointer, containing a matching node or the section-tree header.
 */
OriginalNestedNode56** __attribute__((thiscall)) find_config_section(OriginalNestedTree56* tree,
                                                                     OriginalNestedNode56** output,
                                                                     const ConfigString* key);
/**
 * @brief Find an exact value key without inserting a node.
 *
 * Recovered Ep5.4 entry: 0x005bfdd0.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param key Configuration key whose stored bytes and length are used.
 * @return The output pointer, containing a matching node or the value-tree header.
 */
OriginalNestedNode72** __attribute__((thiscall)) find_config_value(OriginalNestedTree72* tree,
                                                                   OriginalNestedNode72** output,
                                                                   const ConfigString* key);
/**
 * @brief Check whether a lowercased section and key already exist without insertion.
 *
 * Recovered Ep5.4 entry: 0x005bfe40.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param section Configuration section name, folded to lowercase by proxy lookups.
 * @param key Configuration key whose stored bytes and length are used.
 * @return One when both lookups succeed; otherwise zero.
 */
uint8_t __attribute__((thiscall)) contains_config_value(void* self, const ConfigString* section,
                                                        const ConfigString* key);
/**
 * @brief Copy-construct a string from the mapped value referenced by a value proxy.
 *
 * Recovered Ep5.4 entry: 0x005bffa0.
 * @param proxy Proxy referencing a mapped string or section tree as required by its type.
 * @param output Caller-provided storage for the function result.
 * @return The newly initialized output string.
 */
ConfigString* __attribute__((thiscall)) copy_config_proxy_string(ConfigStringProxy* proxy,
                                                                 ConfigString* output);
/**
 * @brief Copy a configuration value, inserting the fallback when its section/key is absent.
 *
 * Missing entries are created in the configuration tree as part of this read. Recovered Ep5.4 entry: 0x005c0630.
 * @param self Destination or owning object required by the recovered thiscall interface.
 * @param output Caller-provided storage for the function result.
 * @param section Configuration section name, folded to lowercase by proxy lookups.
 * @param key Configuration key whose stored bytes and length are used.
 * @param fallback Default string copied into missing entries and into the output.
 * @return The newly initialized output string.
 */
ConfigString* __attribute__((thiscall))
get_config_string_or_insert_default(void* self, ConfigString* output, const ConfigString* section,
                                    const ConfigString* key, const ConfigString* fallback);
}
