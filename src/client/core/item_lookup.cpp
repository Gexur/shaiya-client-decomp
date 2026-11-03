#include "item_lookup.h"
#include "core/x86_memory.h"

// Original004607b0..00460800. Bounds and null tests retain their original
// order, including the signed count comparison before testing item zero.
/**
 * @brief Implement the item lookup while retaining original argument reads.
 * @param item_table Table prefix with record-base, count, and maximum-type fields.
 * @param original_argument_words Address of the original two stack arguments.
 * @return The selected record address, or zero if lookup is rejected.
 * @note The second argument byte is read only after the type and base checks;
 *       this preserves aliasing and fault order. No extent or ownership is inferred.
 */
extern "C" uint32_t find_item_record_from_stack(const void* item_table,
                                                const void* original_argument_words) {
    using client::x86::load_byte;
    using client::x86::load_word;
    // EP4.5 server PDB CGameData::GetItemInfo(nType, nTypeID) corroborates
    // parameter names only. The 92-byte EP5.4 client stride comes from this
    // client's instructions; the server's 168-byte stItemInfo is a different layout.
    constexpr uint32_t item_record_size = 0x5c;
    const uint32_t table_address = reinterpret_cast<uint32_t>(item_table);
    const uint32_t argument_address = reinterpret_cast<uint32_t>(original_argument_words);
    const uint32_t item_type = load_byte(argument_address);
    const uint32_t maximum_type = load_byte(table_address + 12);
    if (maximum_type < item_type || item_type == 0)
        return 0;

    const uint32_t record_bases = load_word(table_address + 4);
    const uint32_t type_offset = (item_type - 1) * sizeof(uint32_t);
    const uint32_t first_record = load_word(record_bases + type_offset);
    if (first_record == 0)
        return 0;

    const uint32_t item_type_id = load_byte(argument_address + 4);
    const uint32_t record_counts = load_word(table_address + 8);
    const int32_t record_count = static_cast<int32_t>(load_word(record_counts + type_offset));
    if (record_count <= static_cast<int32_t>(item_type_id) - 1 || item_type_id == 0)
        return 0;
    return first_record + item_type_id * item_record_size - item_record_size;
}
// Textual argument-address adapter only. Reading the second original stack
// byte eagerly would change the original skipped-read/fault behavior.
/**
 * @brief Locate an EP5.4 item record by one-based type and type identifier.
 * @param item_table Table prefix supplied in ECX; ownership is unchanged.
 * @param item_type Only the low byte selects a type.
 * @param item_type_id Only the low byte selects a record within that type.
 * @return The 32-bit record address, or zero for a rejected type or identifier.
 * @note Uses this client's 92-byte record stride. Server PDBs corroborate the
 *       argument roles, not the EP5.4 client layout. The entry removes 8 bytes.
 */
extern "C" uint32_t __attribute__((naked, thiscall))
find_item_record(void* item_table, uint32_t item_type, uint32_t item_type_id) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _find_item_record_from_stack\n\taddl $8,%esp\n\tretl $8");
}
