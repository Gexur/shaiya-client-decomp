#include "stdio_output.h"
#include "heap.h"
#include "file_ops.h"
#include "../core/memory.h"

extern "C" {
uint32_t dat_0224ee34 = 0;
char* dat_0224ee78[2] = {nullptr, nullptr};
OriginalIoEntry dat_0070e968 = {reinterpret_cast<void*>(0xffffffffu), 0x80, 0x0a, {0, 0}, 0, {}};
}
extern "C" void fun_005dd081(OriginalFile* file) {
    ++dat_0224ee34;
    file->base = static_cast<char*>(fun_005cfade(4096));
    if (file->base) {
        file->flags |= 8;
        file->buffer_size = 4096;
    } else {
        file->flags |= 4;
        file->base = reinterpret_cast<char*>(&file->character_buffer);
        file->buffer_size = 2;
    }
    file->count = 0;
    file->cursor = file->base;
}
extern "C" int32_t fun_005dd0c5(int32_t descriptor) {
    if (uint32_t(descriptor) >= dat_022532d4)
        return 0;
    return file_io_entry(descriptor)->flags & 0x40;
}
extern "C" int32_t fun_005d353d(int32_t character, OriginalFile* file) {
    uint32_t flags = file->flags;
    const int32_t descriptor = file->descriptor;
    if (!(flags & 0x82) || flags & 0x40) {
        file->flags = flags | 0x20;
        return -1;
    }
    if (flags & 1) {
        file->count = 0;
        if (!(flags & 0x10)) {
            file->flags = flags | 0x20;
            return -1;
        }
        file->cursor = file->base;
        file->flags = flags & ~1u;
    }
    flags = file->flags;
    file->count = 0;
    file->flags = (flags & ~0x10u) | 2;
    int32_t written = 0;
    if (!(file->flags & 0x10c) &&
        ((file != &dat_0070e240[1] && file != &dat_0070e240[2]) || !fun_005dd0c5(descriptor)))
        fun_005dd081(file);
    uint32_t requested;
    if (file->flags & 0x108) {
        char* const base = file->base;
        requested = reinterpret_cast<uint32_t>(file->cursor) - reinterpret_cast<uint32_t>(base);
        file->cursor = reinterpret_cast<char*>(reinterpret_cast<uint32_t>(base) + 1);
        file->count = int32_t(uint32_t(file->buffer_size) - 1);
        if (int32_t(requested) > 0)
            written = fun_005d0e1e(descriptor, base, requested);
        else {
            auto* entry = descriptor == -1 ? &dat_0070e968 : file_io_entry(descriptor);
            if (entry->flags & 0x20)
                fun_005cd684(descriptor, 0, 2);
        }
        *file->base = static_cast<char>(character);
    } else {
        requested = 1;
        written = fun_005d0e1e(descriptor, &character, 1);
    }
    if (uint32_t(written) == requested)
        return uint32_t(character) & 0xff;
    file->flags |= 0x20;
    return -1;
}
extern "C" void fun_005d3656(uint8_t character, OriginalFile* file, int32_t* count) {
    if (!(file->flags & 0x40) || file->base) {
        file->count = int32_t(uint32_t(file->count) - 1);
        int32_t result;
        if (file->count < 0)
            result = fun_005d353d(static_cast<int8_t>(character), file);
        else {
            *file->cursor = static_cast<char>(character);
            ++file->cursor;
            result = character;
        }
        if (result == -1) {
            *count = -1;
            return;
        }
    }
    *count = int32_t(uint32_t(*count) + 1);
}
extern "C" void fun_005d3689(uint32_t character, int32_t repeat, OriginalFile* file,
                             int32_t* count) {
    while (repeat > 0) {
        --repeat;
        fun_005d3656(uint8_t(character), file, count);
        if (*count == -1)
            break;
    }
}
extern "C" void fun_005d36ad(const char* text, int32_t length, OriginalFile* file, int32_t* count) {
    if ((file->flags & 0x40) && !file->base) {
        *count = int32_t(uint32_t(*count) + uint32_t(length));
        return;
    }
    while (length > 0) {
        --length;
        fun_005d3656(uint8_t(*text), file, count);
        ++text;
        if (*count == -1)
            break;
    }
}
extern "C" int32_t fun_005d6007(OriginalFile* file) {
    if (!fun_005dd0c5(file->descriptor))
        return 0;
    uint32_t index;
    if (file == &dat_0070e240[1])
        index = 0;
    else if (file == &dat_0070e240[2])
        index = 1;
    else
        return 0;
    ++dat_0224ee34;
    if (file->flags & 0x10c)
        return 0;
    if (!dat_0224ee78[index])
        dat_0224ee78[index] = static_cast<char*>(fun_005cfade(4096));
    if (!dat_0224ee78[index]) {
        file->base = reinterpret_cast<char*>(&file->character_buffer);
        file->cursor = file->base;
        file->buffer_size = 2;
        file->count = 2;
    } else {
        file->base = dat_0224ee78[index];
        file->cursor = file->base;
        file->buffer_size = 4096;
        file->count = 4096;
    }
    file->flags |= 0x1102;
    return 1;
}
extern "C" void fun_005d608f(int32_t active, OriginalFile* file) {
    if (active && (file->flags & 0x1000)) {
        fun_005cfef0(file);
        file->flags &= ~0x1100u;
        file->buffer_size = 0;
        file->cursor = nullptr;
        file->base = nullptr;
    }
}
extern "C" uint32_t fun_005d049a(const void* buffer, uint32_t size, uint32_t count,
                                 OriginalFile* file) {
    const uint32_t total = size * count;
    if (!total)
        return 0;
    const char* cursor = static_cast<const char*>(buffer);
    uint32_t remaining = total;
    uint32_t block = file->flags & 0x10c ? uint32_t(file->buffer_size) : 4096;
    do {
        if ((file->flags & 0x108) && file->count) {
            const uint32_t copied =
                uint32_t(file->count) < remaining ? uint32_t(file->count) : remaining;
            fun_005d8d30(file->cursor, cursor, copied);
            file->count = int32_t(uint32_t(file->count) - copied);
            file->cursor += copied;
            remaining -= copied;
            cursor += copied;
        } else if (remaining >= block) {
            if ((file->flags & 0x108) && fun_005cfef0(file))
                return (total - remaining) / size;
            const uint32_t requested = block ? remaining - remaining % block : remaining;
            const int32_t written = fun_005d0e1e(file->descriptor, cursor, requested);
            if (written == -1) {
                file->flags |= 0x20;
                return (total - remaining) / size;
            }
            cursor += uint32_t(written);
            remaining -= uint32_t(written);
            if (uint32_t(written) < requested) {
                file->flags |= 0x20;
                return (total - remaining) / size;
            }
        } else {
            if (fun_005d353d(static_cast<int8_t>(*cursor), file) == -1)
                return (total - remaining) / size;
            ++cursor;
            --remaining;
            block = uint32_t(file->buffer_size);
            if (int32_t(block) < 1)
                block = 1;
        }
    } while (remaining);
    return count;
}
extern "C" void fun_005d05e3(OriginalFile* file) {
    fun_005d01b8(file);
}
