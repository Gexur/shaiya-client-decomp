#pragma once

#include "../core/string.h"
#include "../core/tree24.h"

namespace shaiya::archive {

// In-memory x86 records used by this Ep5.4 client, not serialized SAH records.
// Directory and file entries share the name/hash prefix used by 0040af40.
struct FileEntry {
    startup::String_00405710 name;
    uint32_t name_hash;
    uint32_t data_offset_low;
    uint32_t data_offset_high;
    uint32_t byte_length;
    uint8_t undecoded_02c[4];
};

struct DirectoryEntry {
    startup::String_00405710 name;
    uint32_t name_hash;
    OriginalTree12 files_by_name_hash;
    OriginalTree12 directories_by_name_hash;
};

static_assert(sizeof(FileEntry) == 0x30);
static_assert(offsetof(FileEntry, name) == 0);
static_assert(offsetof(FileEntry, name_hash) == 0x1c);
static_assert(offsetof(FileEntry, data_offset_low) == 0x20);
static_assert(offsetof(FileEntry, data_offset_high) == 0x24);
static_assert(offsetof(FileEntry, byte_length) == 0x28);
static_assert(offsetof(FileEntry, undecoded_02c) == 0x2c);
static_assert(sizeof(DirectoryEntry) == 0x38);
static_assert(offsetof(DirectoryEntry, name) == 0);
static_assert(offsetof(DirectoryEntry, name_hash) == 0x1c);
static_assert(offsetof(DirectoryEntry, files_by_name_hash) == 0x20);
static_assert(offsetof(DirectoryEntry, directories_by_name_hash) == 0x2c);

} // namespace shaiya::archive
