#pragma once

#include "archive/saf.h"

extern "C" {
// Nonzero selects the SAH format with 64-bit data.saf offsets; zero is legacy.
extern uint32_t dat_00719e78;
extern OriginalSafDirectory* dat_0224e354;
extern OriginalSafDirectory* dat_0224e394;
extern OriginalSafDirectory* dat_0224e364;
/**
 * @brief Construct an empty name and the file and child-directory hash indexes.
 *
 * Partially constructed members are destroyed if construction throws. Recovered Ep5.4 entry: 0x0040e030.
 * @param directory Directory whose owned members are accessed.
 * @return The initialized directory.
 */
OriginalSafDirectory* __attribute__((thiscall))
construct_archive_directory(OriginalSafDirectory* directory);
/**
 * @brief Copy an archive entry name and compute its case-folded signed-byte DJB2 hash.
 *
 * Only the common name/hash prefix is accessed, so directory records share this entry point. Recovered Ep5.4 entry: 0x0040af40.
 * @param entry File or directory record with the shared name/hash prefix.
 * @param name NUL-terminated entry name, or recovered logger name where typed as a string.
 */
void __attribute__((thiscall)) assign_archive_entry_name(OriginalSafFile* entry, const char* name);
/**
 * @brief Find an archive hash value slot, inserting a zero value when the hash is absent.
 *
 * Recovered Ep5.4 entry: 0x0040dec0.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param name_hash Address of the unsigned archive name hash to locate.
 * @return The existing or newly inserted 32-bit mapped-value slot.
 */
uint32_t* __attribute__((thiscall)) get_or_insert_archive_hash_value(OriginalTree12* tree,
                                                                     const uint32_t* name_hash);
/**
 * @brief Recursively read one SAH directory, its files and its child directories.
 *
 * Uses the detected 32-bit or 64-bit SAF offset format and discards serialized file versions. Recovered Ep5.4 entry: 0x0040e0d0.
 * @param descriptor SAF or SAH descriptor, passed indirectly where required by the original ABI.
 * @param directory Directory whose owned members are accessed.
 * @param parent Parent tree node, or containing archive directory where applicable.
 */
void read_sah_directory(const int32_t* descriptor, OriginalSafDirectory* directory,
                        OriginalSafDirectory* parent);
/**
 * @brief Open data.sah, detect its header format and load the complete archive index.
 *
 * Recovered Ep5.4 entry: 0x0040e2c0.
 * @return Zero if data.sah cannot open; one after loading and publishing its root.
 */
uint8_t load_sah_archive_index();
/**
 * @brief Destroy a directory recursively, releasing child entries, indexes and storage.
 *
 * A null directory is accepted; non-null records must own their indexed entries. Recovered Ep5.4 entry: 0x0040e430.
 * @param directory Directory whose owned members are accessed.
 */
void destroy_archive_directory(OriginalSafDirectory* directory);
/**
 * @brief Destroy the loaded archive tree through its global root.
 *
 * Preserves the original behavior of leaving published root pointers unchanged. Recovered Ep5.4 entry: 0x0040e500.
 */
void destroy_archive_index();
/**
 * @brief Publish the archive root in the consumer slot at original address 0x0224e354.
 *
 * The receiving subsystem has not been identified. Recovered Ep5.4 entry: 0x0059fcb0.
 * @param root_directory Loaded archive root published for a consumer.
 */
void set_archive_root_0224e354(OriginalSafDirectory* root_directory);
/**
 * @brief Publish the archive root in the consumer slot at original address 0x0224e394.
 *
 * The receiving subsystem has not been identified. Recovered Ep5.4 entry: 0x005ac1c0.
 * @param root_directory Loaded archive root published for a consumer.
 */
void set_archive_root_0224e394(OriginalSafDirectory* root_directory);
/**
 * @brief Publish the archive root in the consumer slot at original address 0x0224e364.
 *
 * The receiving subsystem has not been identified. Recovered Ep5.4 entry: 0x005a2610.
 * @param root_directory Loaded archive root published for a consumer.
 */
void set_archive_root_0224e364(OriginalSafDirectory* root_directory);
}
