#include "signed_tree_lookup.h"
#include "core/x86_memory.h"

// Complete original 0x0041d430..0x0041d498. The signed-key search caches the
// first key value for traversal, then writes its candidate over the actual
// second formal word before rereading the original key pointer for equality.
/**
 * @brief Search a signed-key tree using the original writable argument storage.
 * @param tree_address Address of the original tree prefix.
 * @param arguments Stack words containing the output address and key address.
 * @param restored_ecx Saved ECX slot, overwritten with the header on a miss.
 * @return Selected node in the high word and output address in the low word.
 * @note Candidate writes and fresh key reads retain alias-dependent behavior.
 */
extern "C" __attribute__((noinline)) uint64_t find_signed_tree_node_from_stack(
    uint32_t tree_address, const uint32_t* arguments, uint32_t* restored_ecx) {
    using client::x86::load_byte;
    using client::x86::load_word;
    using client::x86::store_word;

    constexpr uint32_t header_offset = offsetof(OriginalTree12, header);
    constexpr uint32_t left_offset = offsetof(OriginalTreeNode24, left);
    constexpr uint32_t root_offset = offsetof(OriginalTreeNode24, parent);
    constexpr uint32_t right_offset = offsetof(OriginalTreeNode24, right);
    constexpr uint32_t key_offset = offsetof(OriginalTreeNode24, payload0c);
    constexpr uint32_t sentinel_offset = offsetof(OriginalTreeNode24, is_header);

    const uint32_t argument_address = reinterpret_cast<uint32_t>(arguments);
    uint32_t candidate = load_word(tree_address + header_offset);
    uint32_t node = load_word(candidate + root_offset);
    const bool at_sentinel = load_byte(node + sentinel_offset) != 0;
    const uint32_t key_address = load_word(argument_address + 4);
    if (!at_sentinel) {
        const int32_t search_key = static_cast<int32_t>(load_word(key_address));
        do {
            const int32_t node_key = static_cast<int32_t>(load_word(node + key_offset));
            if (node_key < search_key) {
                node = load_word(node + right_offset);
            } else {
                candidate = node;
                node = load_word(node + left_offset);
            }
        } while (load_byte(node + sentinel_offset) == 0);
    }

    const uint32_t header = load_word(tree_address + header_offset);
    store_word(argument_address + 4, candidate);
    uint32_t selected = header;
    bool found = false;
    if (candidate != header) {
        const int32_t fresh_key = static_cast<int32_t>(load_word(key_address));
        const int32_t candidate_key = static_cast<int32_t>(load_word(candidate + key_offset));
        if (fresh_key >= candidate_key) {
            selected = load_word(argument_address + 4);
            found = true;
        }
    }
    if (!found)
        store_word(reinterpret_cast<uint32_t>(restored_ecx), header);
    const uint32_t output_address = load_word(argument_address);
    store_word(output_address, selected);
    return (uint64_t(selected) << 32) | output_address;
}
// Captures actual argument storage and the original reused saved-ECX word.
// On failure the original writes its header over that saved word before POP.
// EDX:EAX carry the selected node and output pointer, exactly as the original.
/**
 * @brief Find a node by signed key in the original 24-byte-node tree.
 * @param tree Tree prefix passed in ECX.
 * @param output Receives the matching node or the tree header when absent.
 * @param key Pointer to the signed search key; equality rereads its storage.
 * @return The output pointer in EAX; EDX also retains the selected node.
 * @note The original argument storage is reused for the candidate. A miss also
 *       replaces restored ECX with the header. The thiscall entry removes 8 bytes.
 */
extern "C" __attribute__((naked, thiscall)) OriginalTreeNode24**
find_signed_tree_node(OriginalTree12* tree, OriginalTreeNode24** output, const int32_t* key) {
    __asm__ volatile(
        "pushl %ecx\n\tmovl %esp,%edx\n\tleal 8(%esp),%eax\n\tpushl %edx\n\tpushl %eax\n\tpushl %ecx\n\tcall _find_signed_tree_node_from_stack\n\tleal 12(%esp),%esp\n\tpopl %ecx\n\tretl $8");
}
