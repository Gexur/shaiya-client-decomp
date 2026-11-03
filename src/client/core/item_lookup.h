#pragma once
#include <stdint.h>
extern "C" {
/**
 * @brief Locate an EP5.4 item record by one-based type and type identifier.
 * @param item_table Table prefix supplied in ECX; ownership is unchanged.
 * @param item_type Only the low byte selects a type.
 * @param item_type_id Only the low byte selects a record within that type.
 * @return The 32-bit record address, or zero for a rejected type or identifier.
 * @note Uses this client's 92-byte record stride. Server PDBs corroborate the
 *       argument roles, not the EP5.4 client layout. The entry removes 8 bytes.
 */
uint32_t __attribute__((thiscall)) find_item_record(void* item_table, uint32_t item_type,
                                                    uint32_t item_type_id);
/**
 * @brief Implement the item lookup while retaining original argument reads.
 * @param item_table Table prefix with record-base, count, and maximum-type fields.
 * @param original_argument_words Address of the original two stack arguments.
 * @return The selected record address, or zero if lookup is rejected.
 * @note The second argument byte is read only after the type and base checks;
 *       this preserves aliasing and fault order. No extent or ownership is inferred.
 */
uint32_t find_item_record_from_stack(const void* item_table, const void* original_argument_words);
}
