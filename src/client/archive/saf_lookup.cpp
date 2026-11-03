#include "archive/saf.h"

#include "core/byte_utilities.h"
#include "platform/support.hpp"
#include "runtime/file_seek64.h"
#include "runtime/string_ncompare.h"

extern "C" {
OriginalSafDirectory* dat_00719e7c = nullptr;
OriginalSafFile* dat_00719e80 = nullptr;
}

namespace {

/**
 * @brief Load one path byte with the original byte-sized fault boundary.
 * @param pointer Address of the byte or 32-bit field to load.
 * @return The unsigned byte at the supplied address.
 */
uint8_t read_path_byte(const char* pointer) {
    // Preserve byte-sized accesses, including the original fault boundary.
    return *reinterpret_cast<const volatile uint8_t*>(pointer);
}

/**
 * @brief Load the raw byte left by the descriptor read without assigning a new failure value.
 * @param storage Read buffer whose raw byte representation is accessed.
 * @return The zero-extended byte in the original read buffer.
 */
uint8_t read_raw_character(const unsigned char* storage) {
    // A failed read leaves this private byte unwritten. An explicit x86 load
    // preserves its raw representation without promoting an indeterminate
    // C++ value or assigning the original failure case an invented value.
    uint32_t value;
    __asm__ __volatile__("movzbl (%1),%0" : "=r"(value) : "r"(storage) : "memory");
    return uint8_t(value);
}

/**
 * @brief Read one 32-bit archive field through its original volatile access.
 * @param pointer Address of the byte or 32-bit field to load.
 * @return The loaded 32-bit field.
 */
uint32_t read_archive_word(const void* pointer) {
    return *static_cast<const volatile uint32_t*>(pointer);
}

/**
 * @brief Compare a descriptor position with the currently selected SAF entry end.
 *
 * The current entry is required; length and offset fields are read before returning.
 * @param position Current signed descriptor position to compare with the archive entry end.
 * @return True when the position is before offset plus byte length.
 */
bool before_current_file_end(int64_t position) {
    const OriginalSafFile* const entry = dat_00719e80;
    // Keep the original load order; a bad entry can fault before the seek.
    const uint32_t byte_length = read_archive_word(&entry->byte_length);
    const uint32_t offset_low = read_archive_word(&entry->data_offset_low);
    const uint32_t offset_high = read_archive_word(&entry->data_offset_high);
    const uint64_t offset = (uint64_t(offset_high) << 32) | offset_low;
    return position < int64_t(offset + byte_length);
}

} // namespace

/**
 * @brief Find an exact unsigned name hash in an archive directory index.
 *
 * Recovered Ep5.4 entry: 0x00564240.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param output Caller-provided storage for the function result.
 * @param name_hash Address of the unsigned archive name hash to locate.
 * @return The output pointer, containing the matching node or the tree header.
 */
extern "C" OriginalTreeNode24** __attribute__((thiscall))
find_archive_name_hash(OriginalTree12* tree, OriginalTreeNode24** output,
                       const uint32_t* name_hash) {
    OriginalTreeNode24* candidate = tree->header;
    OriginalTreeNode24* node = candidate->parent;
    if (!node->is_header) {
        const uint32_t hash = *name_hash;
        do {
            if (node->payload0c < hash) {
                node = node->right;
            } else {
                candidate = node;
                node = node->left;
            }
        } while (!node->is_header);
    }
    OriginalTreeNode24* const header = tree->header;
    *output = candidate != header && *name_hash >= candidate->payload0c ? candidate : header;
    return output;
}

/**
 * @brief Resolve a data/ path through the loaded SAH index and seek its SAF descriptor.
 *
 * Publishes the current file even if the underlying seek fails. Recovered Ep5.4 entry: 0x0040d0f0.
 * @param descriptor SAF or SAH descriptor, passed indirectly where required by the original ABI.
 * @param path NUL-terminated file path to resolve or open.
 * @return One after finding an entry; zero for a missing prefix, root, directory or file.
 */
extern "C" uint8_t seek_archive_entry(const int32_t* descriptor, const char* path) {
    constexpr uint32_t data_prefix_length = 5;
    if (fun_005e0a1f("data/", path, data_prefix_length) != 0 &&
        fun_005e0a1f("data\\", path, data_prefix_length) != 0) {
        return 0;
    }

    OriginalSafDirectory* directory = dat_00719e7c;
    if (directory == nullptr) {
        return 0;
    }
    char relative_path[2048];
    uint32_t path_length = 0;
    do {
        relative_path[path_length] = char(read_path_byte(path + data_prefix_length + path_length));
    } while (relative_path[path_length++] != 0);

    uint32_t component_start = 0;
    uint32_t cursor = 0;
    for (;;) {
        uint32_t component_length = 0;
        for (;;) {
            const uint8_t character = read_path_byte(relative_path + cursor);
            if (character == '/' || character == '\\') {
                break;
            }
            if (character == 0) {
                const uint32_t name_hash =
                    fun_0040d040(reinterpret_cast<const uint8_t*>(relative_path + component_start),
                                 component_length);
                OriginalTreeNode24* found;
                find_archive_name_hash(&directory->files_by_name_hash, &found, &name_hash);
                if (found == directory->files_by_name_hash.header) {
                    return 0;
                }
                auto* const entry = reinterpret_cast<OriginalSafFile*>(uintptr_t(found->payload10));
                const uint32_t offset_high = read_archive_word(&entry->data_offset_high);
                const uint32_t offset_low = read_archive_word(&entry->data_offset_low);
                const uint64_t offset = (uint64_t(offset_high) << 32) | offset_low;
                (void)fun_005ce2a2(int32_t(read_archive_word(descriptor)), int64_t(offset), 0);
                // The original publishes a found entry even if seek fails.
                dat_00719e80 = entry;
                return 1;
            }
            ++cursor;
            ++component_length;
        }

        uint32_t name_hash = 0x1505;
        for (uint32_t index = 0; index < component_length; ++index) {
            int32_t character = int8_t(read_path_byte(relative_path + component_start + index));
            if (character >= 'A' && character <= 'Z') {
                character += 'a' - 'A';
            }
            name_hash = name_hash * 33u + uint32_t(character);
        }
        OriginalTreeNode24* found;
        find_archive_name_hash(&directory->directories_by_name_hash, &found, &name_hash);
        if (found == directory->directories_by_name_hash.header) {
            return 0;
        }
        directory = reinterpret_cast<OriginalSafDirectory*>(uintptr_t(found->payload10));
        ++cursor;
        component_start = cursor;
    }
}

/**
 * @brief Read the current archive entry through its next newline.
 *
 * The capacity argument is ignored, and an EOF fragment remains unterminated. Recovered Ep5.4 entry: 0x00437350.
 * @param output Caller-provided storage for the function result.
 * @param unused_capacity Original capacity argument; intentionally ignored by this entry point.
 * @param descriptor SAF or SAH descriptor, passed indirectly where required by the original ABI.
 * @return One when a newline was replaced with NUL; zero at the entry end.
 */
extern "C" uint8_t read_archive_line(char* output, [[maybe_unused]] uint32_t unused_capacity,
                                     int32_t descriptor) {
    uint32_t characters_written = 0;
    unsigned char character_storage[1];
    while (before_current_file_end(fun_005ce731(descriptor))) {
        (void)FUN_0040d020(character_storage, 1, 1, descriptor);
        const uint8_t character = read_raw_character(character_storage);
        output[characters_written] = char(character);
        if (character == '\n') {
            output[characters_written] = 0;
            return 1;
        }
        ++characters_written;
    }
    // The original ignores capacity and leaves an EOF fragment unterminated.
    return 0;
}
