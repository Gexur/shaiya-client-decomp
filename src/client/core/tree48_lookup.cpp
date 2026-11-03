#include "tree48_lookup.h"
#include "string_compare.h"
namespace {
uint32_t word(const void* p) {
    uint32_t value;
    __asm__ __volatile__("movl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
uint8_t byte(const void* p) {
    uint32_t value;
    __asm__ __volatile__("movzbl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return uint8_t(value);
}
int32_t bytes_compare(const uint8_t* left, const uint8_t* right, uint32_t count) {
    int32_t value;
    __asm__ __volatile__("xorl %0,%0\n\trepe cmpsb\n\tje 1f\n\tsbbl %0,%0\n\tsbbl $-1,%0\n1:"
                         : "=&a"(value), "+S"(left), "+D"(right), "+c"(count)::"cc", "memory");
    return value;
}
} // namespace
extern "C" OriginalTreeNode48* __attribute__((thiscall))
FUN_0054b050(OriginalTree48Owner12* self, const shaiya::startup::String_00405710* key) {
    OriginalTreeNode48* candidate = self->header;
    OriginalTreeNode48* node = candidate->parent;
    if (byte(&node->is_header) != 0)
        return candidate;
    const uint32_t capacity = word(&key->capacity_018), length = word(&key->size_014);
    do {
        const uint8_t* key_data =
            capacity < 16 ? key->storage_004
                          : reinterpret_cast<const uint8_t*>(uintptr_t(word(key->storage_004)));
        const uint32_t node_length = word(&node->key.size_014);
        int32_t comparison = 0;
        if (node_length != 0) {
            const uint32_t common = node_length < length ? node_length : length;
            const uint8_t* node_data =
                word(&node->key.capacity_018) < 16
                    ? node->key.storage_004
                    : reinterpret_cast<const uint8_t*>(uintptr_t(word(node->key.storage_004)));
            comparison = bytes_compare(node_data, key_data, common);
        }
        if (comparison == 0)
            comparison = node_length < length ? -1 : node_length != length ? 1 : 0;
        if (comparison < 0)
            node = node->right;
        else {
            candidate = node;
            node = node->left;
        }
    } while (byte(&node->is_header) == 0);
    return candidate;
}
extern "C" OriginalTreeNode48** __attribute__((thiscall))
FUN_0054b170(OriginalTree48Owner12* self, OriginalTreeNode48** output,
             shaiya::startup::String_00405710* key) {
    OriginalTreeNode48* candidate = FUN_0054b050(self, key);
    if (candidate != self->header) {
        const uint32_t capacity = word(&candidate->key.capacity_018),
                       length = word(&candidate->key.size_014);
        const uint8_t* data =
            capacity < 16
                ? candidate->key.storage_004
                : reinterpret_cast<const uint8_t*>(uintptr_t(word(candidate->key.storage_004)));
        if (FUN_0040a670(key, 0, word(&key->size_014), data, length) >= 0) {
            *output = candidate;
            return output;
        }
    }
    *output = self->header;
    return output;
}
