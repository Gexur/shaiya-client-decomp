#pragma once

#include "archive/entry_layouts.h"

// Preserve the recovered interface names used by existing fixtures and callers.
using OriginalSafFile = shaiya::archive::FileEntry;
using OriginalSafDirectory = shaiya::archive::DirectoryEntry;

extern "C" {
extern OriginalSafDirectory* dat_00719e7c;
extern __attribute__((visibility("hidden"))) OriginalSafFile* dat_00719e80;
/**
 * @brief Find an exact unsigned name hash in an archive directory index.
 *
 * Recovered Ep5.4 entry: 0x00564240.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param name_hash Address of the unsigned archive name hash to locate.
 * @return The output pointer, containing the matching node or the tree header.
 */
OriginalTreeNode24** __attribute__((thiscall)) find_archive_name_hash(OriginalTree12* tree,
                                                                      OriginalTreeNode24** output,
                                                                      const uint32_t* name_hash);
/**
 * @brief Resolve a data/ path through the loaded SAH index and seek its SAF descriptor.
 *
 * Publishes the current file even if the underlying seek fails. Recovered Ep5.4 entry: 0x0040d0f0.
 * @param descriptor SAF or SAH descriptor, passed indirectly where required by the original ABI.
 * @param path NUL-terminated file path to resolve or open.
 * @return One after finding an entry; zero for a missing prefix, root, directory or file.
 */
uint8_t seek_archive_entry(const int32_t* descriptor, const char* path);
/**
 * @brief Read the current archive entry through its next newline.
 *
 * The capacity argument is ignored, and an EOF fragment remains unterminated. Recovered Ep5.4 entry: 0x00437350.
 * @param output Caller-provided storage for the function result.
 * @param unused_capacity Original capacity argument; intentionally ignored by this entry point.
 * @param descriptor SAF or SAH descriptor, passed indirectly where required by the original ABI.
 * @return One when a newline was replaced with NUL; zero at the entry end.
 */
uint8_t read_archive_line(char* output, [[maybe_unused]] uint32_t unused_capacity,
                          int32_t descriptor);
}
