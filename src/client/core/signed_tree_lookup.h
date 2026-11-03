#pragma once
#include <stdint.h>
#include "core/tree24.h"
/**
 * @brief Find a node by signed key in the original 24-byte-node tree.
 * @param tree Tree prefix passed in ECX.
 * @param output Receives the matching node or the tree header when absent.
 * @param key Pointer to the signed search key; equality rereads its storage.
 * @return The output pointer in EAX; EDX also retains the selected node.
 * @note The original argument storage is reused for the candidate. A miss also
 *       replaces restored ECX with the header. The thiscall entry removes 8 bytes.
 */
extern "C" OriginalTreeNode24** __attribute__((thiscall))
find_signed_tree_node(OriginalTree12* tree, OriginalTreeNode24** output, const int32_t* key);
