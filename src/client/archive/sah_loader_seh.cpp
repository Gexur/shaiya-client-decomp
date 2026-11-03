#include "archive/sah_loader.h"

#include "runtime/allocations.h"
#include "runtime/file_ops.h"
#include "runtime/file_seek64.h"
#include "runtime/string_compare.h"
#include "runtime/string_errors.h"

extern "C" {
uint32_t dat_00719e78 = 0;
OriginalSafDirectory* dat_0224e354 = nullptr;
OriginalSafDirectory* dat_0224e394 = nullptr;
OriginalSafDirectory* dat_0224e364 = nullptr;
}

namespace {

using String = shaiya::startup::String_00405710;
constexpr uint8_t red_node = 0;
constexpr uint8_t black_node = 1;
constexpr uint32_t maximum_tree_count_before_insert = 0x1ffffffd;

/**
 * @brief Initialize only the recovered empty-string fields.
 * @param name Recovered string whose empty representation is initialized.
 */
void initialize_empty_string(String* name) {
    name->capacity_018 = 15;
    name->size_014 = 0;
    name->storage_004[0] = 0;
}

struct StringCleanup {
    String* value;
    bool active = true;
    /**
     * @brief Destroy an active archive name during unwinding.
     */
    ~StringCleanup() noexcept(false) {
        if (active) {
            FUN_00529db0(value);
        }
    }
};

struct TreeCleanup {
    OriginalTree12* tree;
    bool active = true;
    /**
     * @brief Destroy an active archive hash tree during unwinding.
     */
    ~TreeCleanup() noexcept(false) {
        if (active) {
            FUN_0041f2b0(tree);
        }
    }
};

struct AllocationCleanup {
    void* allocation;
    bool active = true;
    /**
     * @brief Free an active archive allocation during unwinding.
     */
    ~AllocationCleanup() noexcept(false) {
        if (active) {
            fun_005cc620(allocation);
        }
    }
};

struct TreeLengthErrorMessage {
    String text;
    /**
     * @brief Construct the recovered map/set length-error message.
     */
    TreeLengthErrorMessage() {
        initialize_empty_string(&text);
        FUN_00405710(&text, "map/set<T> too long", 19);
    }
    /**
     * @brief Destroy the recovered map/set length-error message string.
     */
    ~TreeLengthErrorMessage() {
        FUN_00529db0(&text);
    }
};

/**
 * @brief Throw the original length-error object for an oversized archive hash tree.
 *
 * Does not return; the recovered throw metadata selects the original exception type.
 */
[[noreturn]] void throw_tree_length_error() {
    TreeLengthErrorMessage message;
    OriginalLogicError error;
    FUN_0040ad80(&error, &message.text);
    error.base.vtable = &dat_006dbc80;
    fun_005cce46(&error, const_cast<CxxThrowInfo*>(&dat_006fa52c));
    __builtin_unreachable();
}

// The insertion policy follows 0040dec0/0040dd50/0040d680: unsigned key,
// lower_bound, insertion before the hint, and the original red/black rotations.
/**
 * @brief Allocate and link an archive hash node, then restore red/black balance.
 *
 * Retains the original length limit, insertion policy, rotations and allocation-failure behavior.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param parent Parent tree node, or containing archive directory where applicable.
 * @param insert_left Nonzero inserts as the parent left child; zero selects the right child.
 * @param key_value Two consecutive DWORDs containing the hash and mapped entry address.
 * @return The newly allocated node.
 */
OriginalTreeNode24* insert_tree_node(OriginalTree12* tree, OriginalTreeNode24* parent,
                                     bool insert_left, const uint32_t* key_value) {
    if (tree->count > maximum_tree_count_before_insert) {
        throw_tree_length_error();
    }
    auto* node = static_cast<OriginalTreeNode24*>(fun_005cc96d(sizeof(OriginalTreeNode24)));
    if (node) {
        node->left = tree->header;
        node->right = tree->header;
        node->parent = parent;
        node->payload0c = key_value[0];
        node->payload10 = key_value[1];
        node->color = red_node;
        node->is_header = 0;
    }
    ++tree->count;
    if (parent == tree->header) {
        tree->header->parent = node;
        tree->header->left = node;
        tree->header->right = node;
    } else if (insert_left) {
        parent->left = node;
        if (parent == tree->header->left) {
            tree->header->left = node;
        }
    } else {
        parent->right = node;
        if (parent == tree->header->right) {
            tree->header->right = node;
        }
    }

    auto* current = node;
    while (current->parent->color == red_node) {
        auto* current_parent = current->parent;
        auto* grandparent = current_parent->parent;
        if (current_parent == grandparent->left) {
            auto* uncle = grandparent->right;
            if (uncle->color == red_node) {
                current_parent->color = black_node;
                uncle->color = black_node;
                grandparent->color = red_node;
                current = grandparent;
            } else {
                if (current == current_parent->right) {
                    FUN_00421720(tree, current_parent);
                    current = current_parent;
                }
                current->parent->color = black_node;
                current->parent->parent->color = red_node;
                FUN_00444130(tree, current->parent->parent);
            }
        } else {
            auto* uncle = grandparent->left;
            if (uncle->color == red_node) {
                current_parent->color = black_node;
                uncle->color = black_node;
                grandparent->color = red_node;
                current = grandparent;
            } else {
                if (current == current_parent->left) {
                    FUN_00444130(tree, current_parent);
                    current = current_parent;
                }
                current->parent->color = black_node;
                current->parent->parent->color = red_node;
                FUN_00421720(tree, current->parent->parent);
            }
        }
    }
    tree->header->parent->color = black_node;
    return node;
}

/**
 * @brief Destroy child-directory indexes, file indexes and name in their original order.
 *
 * Does not recursively release indexed entries or free the directory allocation.
 * @param directory Directory whose owned members are accessed.
 */
void destroy_directory_members(OriginalSafDirectory* directory) {
    // 0040df70 destroys the directory map, then the file map, then the key.
    StringCleanup name_cleanup{&directory->name};
    TreeCleanup files_cleanup{&directory->files_by_name_hash};
    FUN_0041f2b0(&directory->directories_by_name_hash);
    FUN_0041f2b0(&directory->files_by_name_hash);
    files_cleanup.active = false;
    FUN_00529db0(&directory->name);
    name_cleanup.active = false;
}

} // namespace

/**
 * @brief Copy an archive entry name and compute its case-folded signed-byte DJB2 hash.
 *
 * Only the common name/hash prefix is accessed, so directory records share this entry point. Recovered Ep5.4 entry: 0x0040af40.
 * @param entry File or directory record with the shared name/hash prefix.
 * @param name NUL-terminated entry name, or recovered logger name where typed as a string.
 */
extern "C" void __attribute__((thiscall)) assign_archive_entry_name(OriginalSafFile* entry,
                                                                    const char* name) {
    uint32_t name_length = 0;
    while (name[name_length]) {
        ++name_length;
    }
    FUN_00405710(&entry->name, name, name_length);

    uint32_t name_hash = 0x1505;
    for (const char* cursor = name; *cursor; ++cursor) {
        int32_t character = int8_t(*cursor);
        if (character >= 'A' && character <= 'Z') {
            character += 'a' - 'A';
        }
        name_hash = name_hash * 33u + uint32_t(character);
    }
    entry->name_hash = name_hash;
}

/**
 * @brief Construct an empty name and the file and child-directory hash indexes.
 *
 * Partially constructed members are destroyed if construction throws. Recovered Ep5.4 entry: 0x0040e030.
 * @param directory Directory whose owned members are accessed.
 * @return The initialized directory.
 */
extern "C" OriginalSafDirectory* __attribute__((thiscall))
construct_archive_directory(OriginalSafDirectory* directory) {
    initialize_empty_string(&directory->name);
    StringCleanup name_cleanup{&directory->name};
    FUN_0041fcb0(&directory->files_by_name_hash);
    TreeCleanup files_cleanup{&directory->files_by_name_hash};
    FUN_0041fcb0(&directory->directories_by_name_hash);
    files_cleanup.active = false;
    name_cleanup.active = false;
    return directory;
}

/**
 * @brief Find an archive hash value slot, inserting a zero value when the hash is absent.
 *
 * Recovered Ep5.4 entry: 0x0040dec0.
 * @param tree Tree whose recovered sentinel and node links are used.
 * @param name_hash Address of the unsigned archive name hash to locate.
 * @return The existing or newly inserted 32-bit mapped-value slot.
 */
extern "C" uint32_t* __attribute__((thiscall))
get_or_insert_archive_hash_value(OriginalTree12* tree, const uint32_t* name_hash) {
    auto* hint = tree->header;
    auto* node = hint->parent;
    while (!node->is_header) {
        if (node->payload0c < *name_hash) {
            node = node->right;
        } else {
            hint = node;
            node = node->left;
        }
    }
    if (hint != tree->header && hint->payload0c <= *name_hash) {
        return &hint->payload10;
    }
    uint32_t key_value[2] = {*name_hash, 0};
    if (tree->count == 0) {
        node = insert_tree_node(tree, tree->header, true, key_value);
    } else if (hint == tree->header) {
        node = insert_tree_node(tree, tree->header->right, false, key_value);
    } else if (hint == tree->header->left) {
        node = insert_tree_node(tree, hint, true, key_value);
    } else {
        // 0040dd50 decrements the lower-bound hint, retaining the original
        // choice between its empty right branch and hint's empty left branch.
        auto* previous = hint;
        if (!previous->left->is_header) {
            previous = previous->left;
            while (!previous->right->is_header) {
                previous = previous->right;
            }
        } else {
            auto* parent = previous->parent;
            while (!parent->is_header && previous == parent->left) {
                previous = parent;
                parent = parent->parent;
            }
            previous = parent;
        }
        node = previous->right->is_header ? insert_tree_node(tree, previous, false, key_value)
                                          : insert_tree_node(tree, hint, true, key_value);
    }
    return &node->payload10;
}

/**
 * @brief Recursively read one SAH directory, its files and its child directories.
 *
 * Uses the detected 32-bit or 64-bit SAF offset format and discards serialized file versions. Recovered Ep5.4 entry: 0x0040e0d0.
 * @param descriptor SAF or SAH descriptor, passed indirectly where required by the original ABI.
 * @param directory Directory whose owned members are accessed.
 * @param parent Parent tree node, or containing archive directory where applicable.
 */
extern "C" void read_sah_directory(const int32_t* descriptor, OriginalSafDirectory* directory,
                                   OriginalSafDirectory* parent) {
    uint32_t name_byte_count;
    char name[1024];
    int32_t entry_count;
    fun_005ce53d(*descriptor, &name_byte_count, 4);
    fun_005ce53d(*descriptor, name, name_byte_count);
    assign_archive_entry_name(reinterpret_cast<OriginalSafFile*>(directory), name);
    if (parent) {
        uint32_t name_hash = directory->name_hash;
        *get_or_insert_archive_hash_value(&parent->directories_by_name_hash, &name_hash) =
            reinterpret_cast<uint32_t>(directory);
    }
    fun_005ce53d(*descriptor, &entry_count, 4);
    for (int32_t index = 0; index < entry_count; ++index) {
        auto* file = static_cast<OriginalSafFile*>(fun_005cc96d(sizeof(OriginalSafFile)));
        if (file) {
            initialize_empty_string(&file->name);
        }
        fun_005ce53d(*descriptor, &name_byte_count, 4);
        fun_005ce53d(*descriptor, name, name_byte_count);
        assign_archive_entry_name(file, name);
        if (dat_00719e78 == 0) {
            uint32_t legacy_offset;
            fun_005ce53d(*descriptor, &legacy_offset, 4);
            file->data_offset_low = legacy_offset;
            file->data_offset_high = 0;
        } else {
            fun_005ce53d(*descriptor, &file->data_offset_low, 8);
        }
        fun_005ce53d(*descriptor, &file->byte_length, 4);
        // Parsec calls the final serialized DWORD Version. This client reads
        // and discards it; it does not populate the opaque bytes at file+0x2c.
        unsigned char ignored_file_version[4];
        fun_005ce53d(*descriptor, ignored_file_version, 4);
        uint32_t name_hash = file->name_hash;
        *get_or_insert_archive_hash_value(&directory->files_by_name_hash, &name_hash) =
            reinterpret_cast<uint32_t>(file);
    }
    fun_005ce53d(*descriptor, &entry_count, 4);
    for (int32_t index = 0; index < entry_count; ++index) {
        void* allocation = fun_005cc96d(sizeof(OriginalSafDirectory));
        AllocationCleanup allocation_cleanup{allocation};
        auto* child =
            allocation ? construct_archive_directory(static_cast<OriginalSafDirectory*>(allocation))
                       : nullptr;
        allocation_cleanup.active = false;
        read_sah_directory(descriptor, child, directory);
    }
}

/**
 * @brief Publish the archive root in the consumer slot at original address 0x0224e354.
 *
 * The receiving subsystem has not been identified. Recovered Ep5.4 entry: 0x0059fcb0.
 * @param root_directory Loaded archive root published for a consumer.
 */
extern "C" void set_archive_root_0224e354(OriginalSafDirectory* root_directory) {
    dat_0224e354 = root_directory;
}

/**
 * @brief Publish the archive root in the consumer slot at original address 0x0224e394.
 *
 * The receiving subsystem has not been identified. Recovered Ep5.4 entry: 0x005ac1c0.
 * @param root_directory Loaded archive root published for a consumer.
 */
extern "C" void set_archive_root_0224e394(OriginalSafDirectory* root_directory) {
    dat_0224e394 = root_directory;
}

/**
 * @brief Publish the archive root in the consumer slot at original address 0x0224e364.
 *
 * The receiving subsystem has not been identified. Recovered Ep5.4 entry: 0x005a2610.
 * @param root_directory Loaded archive root published for a consumer.
 */
extern "C" void set_archive_root_0224e364(OriginalSafDirectory* root_directory) {
    dat_0224e364 = root_directory;
}

/**
 * @brief Open data.sah, detect its header format and load the complete archive index.
 *
 * Recovered Ep5.4 entry: 0x0040e2c0.
 * @return Zero if data.sah cannot open; one after loading and publishing its root.
 */
extern "C" uint8_t load_sah_archive_index() {
    int32_t descriptor = _open("data.sah", 0x8000);
    if (descriptor == -1) {
        return 0;
    }
    char signature[3];
    unsigned char version[4];
    unsigned char total_file_count[4];
    unsigned char padding[40];
    fun_005ce53d(descriptor, signature, 3);
    if (fun_005cdf60(signature, "SAH", 3) == 0) {
        dat_00719e78 = 1;
        fun_005ce53d(descriptor, version, 4);
        fun_005ce53d(descriptor, total_file_count, 4);
        fun_005ce53d(descriptor, padding, 40);
    } else {
        dat_00719e78 = 0;
        fun_005ce2a2(descriptor, 0, 0);
        fun_005ce53d(descriptor, version, 4);
        fun_005ce53d(descriptor, total_file_count, 4);
    }
    void* allocation = fun_005cc96d(sizeof(OriginalSafDirectory));
    AllocationCleanup allocation_cleanup{allocation};
    dat_00719e7c = allocation
                       ? construct_archive_directory(static_cast<OriginalSafDirectory*>(allocation))
                       : nullptr;
    allocation_cleanup.active = false;
    read_sah_directory(&descriptor, dat_00719e7c, nullptr);
    _close(descriptor);
    set_archive_root_0224e354(dat_00719e7c);
    set_archive_root_0224e394(dat_00719e7c);
    set_archive_root_0224e364(dat_00719e7c);
    return 1;
}

/**
 * @brief Destroy a directory recursively, releasing child entries, indexes and storage.
 *
 * A null directory is accepted; non-null records must own their indexed entries. Recovered Ep5.4 entry: 0x0040e430.
 * @param directory Directory whose owned members are accessed.
 */
extern "C" void destroy_archive_directory(OriginalSafDirectory* directory) {
    if (!directory) {
        return;
    }
    auto* node = directory->directories_by_name_hash.header->left;
    while (node != directory->directories_by_name_hash.header) {
        destroy_archive_directory(reinterpret_cast<OriginalSafDirectory*>(node->payload10));
        FUN_00421780(&node);
    }
    node = directory->files_by_name_hash.header->left;
    while (node != directory->files_by_name_hash.header) {
        auto* file = reinterpret_cast<OriginalSafFile*>(node->payload10);
        if (file) {
            FUN_00529db0(&file->name);
            fun_005cc620(file);
        }
        FUN_00421780(&node);
    }
    destroy_directory_members(directory);
    fun_005cc620(directory);
}

/**
 * @brief Destroy the loaded archive tree through its global root.
 *
 * Preserves the original behavior of leaving published root pointers unchanged. Recovered Ep5.4 entry: 0x0040e500.
 */
extern "C" void destroy_archive_index() {
    destroy_archive_directory(dat_00719e7c);
}
