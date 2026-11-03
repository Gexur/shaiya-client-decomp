#include "stdio_input.h"
#include "stdio_output.h"
#include "file_ops.h"
namespace {
uint8_t read_byte(const char* pointer) {
    uint32_t value;
    // Original MOVZX precedes the cursor store. The memory clobber preserves
    // that fault-visible order instead of C++ postincrement's eager store.
    __asm__ __volatile__("movzbl (%1),%0" : "=r"(value) : "r"(pointer) : "memory");
    return uint8_t(value);
}
} // namespace
extern "C" uint32_t dat_0070e4e0 = 1;
extern "C" int32_t fun_005d3ea0(OriginalFile* file) {
    file->count = int32_t(uint32_t(file->count) - 1);
    if (file->count >= 0) {
        char* const pointer = file->cursor;
        const uint8_t value = read_byte(pointer);
        file->cursor = pointer + 1;
        return value;
    }
    return fun_005d8a13(file);
}
extern "C" int32_t fun_005d8a13(OriginalFile* file) {
    const uint32_t flags = file->flags;
    if (!(flags & 0x83) || (flags & 0x40))
        return -1;
    if (flags & 2) {
        file->flags = flags | 0x20;
        return -1;
    }
    file->flags = flags | 1;
    if (!(flags & 0x10c))
        fun_005dd081(file);
    else
        file->cursor = file->base;
    const int32_t count = fun_005ce53d(file->descriptor, file->base, uint32_t(file->buffer_size));
    file->count = count;
    if (!count || count == -1) {
        file->flags |= count ? 0x20 : 0x10;
        file->count = 0;
        return -1;
    }
    if (!(file->flags & 0x82)) {
        const OriginalIoEntry* entry =
            file->descriptor == -1 ? &dat_0070e968 : file_io_entry(file->descriptor);
        if ((entry->flags & 0x82) == 0x82)
            file->flags |= 0x2000;
    }
    if (file->buffer_size == 0x200 && (file->flags & 8) && !(file->flags & 0x400))
        file->buffer_size = 0x1000;
    file->count = int32_t(uint32_t(count) - 1);
    char* const pointer = file->cursor;
    const uint8_t value = read_byte(pointer);
    file->cursor = pointer + 1;
    return value;
}
extern "C" int32_t fun_005dd176(int32_t character, OriginalFile* file) {
    if (character == -1)
        return -1;
    const uint32_t flags = file->flags;
    if (!(flags & 1) && !((flags & 0x80) && !(flags & 2)))
        return -1;
    if (!file->base)
        fun_005dd081(file);
    if (file->cursor == file->base) {
        if (file->count)
            return -1;
        ++file->cursor;
    }
    --file->cursor;
    if (!(file->flags & 0x40))
        *file->cursor = char(character);
    else if (*file->cursor != char(character)) {
        ++file->cursor;
        return -1;
    }
    file->count = int32_t(uint32_t(file->count) + 1);
    file->flags = (file->flags & ~0x10u) | 1;
    return uint8_t(character);
}
