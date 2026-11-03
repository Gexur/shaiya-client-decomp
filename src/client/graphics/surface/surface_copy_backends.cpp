#include "graphics/surface/surface_copy_backends.h"
#include "graphics/surface/surface_format_configure.h"
#include "runtime/allocations.h"
#include "core/untouched_lifetime.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void copy(u32 destination, u32 source, u32 bytes) {
    u32 count = bytes >> 2;
    __asm__ volatile("rep movsl" : "+D"(destination), "+S"(source), "+c"(count)::"memory");
    count = bytes & 3;
    __asm__ volatile("rep movsb" : "+D"(destination), "+S"(source), "+c"(count)::"memory");
}
bool palettes_equal(u32 destination, u32 source) {
    u32 count = 256;
    unsigned char equal;
    __asm__ volatile("repe cmpsl\n\tsete %0"
                     : "=qm"(equal), "+S"(destination), "+D"(source), "+c"(count)::"memory", "cc");
    return equal != 0;
}
void row_callback(u32 table, u32 code, u32 receiver, u32 row, u32 slice, u32 buffer) {
    const u32 words[3] = {row, slice, buffer};
    // Exact ECX/three-stack-word call. The original EAX still contains the table.
    __asm__ volatile("pushl 8(%3)\n\tpushl 4(%3)\n\tpushl (%3)\n\tcalll *%2"
                     : "+a"(table), "+c"(receiver)
                     : "r"(code), "r"(words)
                     : "edx", "memory", "cc");
}
constexpr int32_t failure = static_cast<int32_t>(0x80004005u);
} // namespace
// Complete5eccc7..5ece1f. Unsigned block offsets/row-step arithmetic is kept
// verbatim; no format dimension validation or rounding rule is added.
extern "C" int32_t __attribute__((thiscall)) FUN_005eccc7(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object), source = word(self);
    u32 source_flags = word(source + 0x48);
    source_flags |= word(source + 0x44);
    const u32 source_y = word(source + 0x40), source_x = word(source + 0x3c);
    if ((source_flags | source_x | source_y) & 3)
        return failure;
    u32 destination = word(self + 4), destination_flags = word(destination + 0x48);
    destination_flags |= word(destination + 0x44);
    destination_flags |= word(destination + 0x40);
    destination_flags |= word(destination + 0x3c);
    if (destination_flags & 3)
        return failure;
    destination = word(self + 4);
    const u32 format = word(destination + 4);
    u32 block_bytes;
    if (format == 0x31545844u)
        block_bytes = 8;
    else if (format == 0x32545844u || format == 0x33545844u || format == 0x34545844u ||
             format == 0x35545844u)
        block_bytes = 16;
    else
        return failure;
    destination = word(self + 4);
    const u32 width = word(destination + 0x68);
    u32 destination_slice = word(destination + 0x64);
    destination_slice *= word(destination + 0x4c);
    const u32 row_bytes = (width >> 2) * block_bytes;
    u32 destination_row = word(destination + 0x40) >> 2;
    destination_row *= word(destination + 0x60);
    destination_row += destination_slice;
    u32 destination_column = word(destination + 0x3c) >> 2;
    destination_column *= block_bytes;
    u32 source_row = (source_y >> 2) * word(source + 0x60);
    u32 destination_base = destination_row + destination_column;
    destination_base += word(destination + 0x20);
    u32 source_slice = word(source + 0x64);
    source_slice *= word(source + 0x4c);
    const u32 source_column = (source_x >> 2) * block_bytes;
    u32 source_base = source_row + source_slice + source_column;
    source_base += word(source + 0x20);
    destination = word(self + 4);
    if (!word(destination + 0x70))
        return 0;
    u32 slice = 0, height = word(destination + 0x6c);
    do {
        u32 from = source_base, to = destination_base, row = 0;
        if (height)
            do {
                row += 4;
                copy(to, from, row_bytes);
                destination = word(self + 4);
                to += word(destination + 0x60);
                const u32 fresh_source = word(self);
                from += word(fresh_source + 0x60);
                height = word(destination + 0x6c);
            } while (row < height);
        const u32 fresh_source = word(self);
        destination = word(self + 4);
        source_base += word(fresh_source + 0x64);
        destination_base += word(destination + 0x64);
        ++slice;
    } while (slice < word(destination + 0x70));
    return 0;
}
// Complete5edcc4..5eddce. REP transfer widths and fresh descriptor reads are
// observable when backing aliases. DF0 is the proved caller precondition.
extern "C" int32_t __attribute__((thiscall)) FUN_005edcc4(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    u32 destination = word(self + 4), source = word(self);
    const u32 destination_format = word(destination + 4);
    if (destination_format != word(source + 4))
        return failure;
    if (word(source + 0x18))
        return failure;
    u32 value = word(destination + 0x68);
    if (value != word(source + 0x68))
        return failure;
    value = word(destination + 0x6c);
    if (value != word(source + 0x6c))
        return failure;
    value = word(destination + 0x70);
    if (value != word(source + 0x70))
        return failure;
    value = word(destination + 0x10);
    if (value != word(source + 0x10))
        return failure;
    if (!word(destination + 0xc))
        return FUN_005eccc7(object);
    if (word(destination + 0x1c)) {
        const u32 destination_palette = word(destination + 0x38),
                  source_palette = word(source + 0x38);
        if (destination_palette != source_palette &&
            !palettes_equal(destination_palette, source_palette))
            return failure;
    }
    put(destination + 0x10, 0);
    source = word(self);
    put(source + 0x10, 0);
    destination = word(self + 4);
    if (!word(destination + 0x70))
        return 0;
    source = word(self);
    u32 height = word(destination + 0x6c), slice = 0;
    do {
        const u32 destination_for_base = word(self + 4);
        u32 to = word(destination_for_base + 0x64) * slice;
        to += word(destination_for_base + 0x20);
        u32 from = word(source + 0x64) * slice;
        from += word(source + 0x20);
        u32 row = 0;
        if (height)
            do {
                const u32 bytes = word(destination + 0x74);
                copy(to, from, bytes);
                destination = word(self + 4);
                source = word(self);
                to += word(destination + 0x60);
                from += word(source + 0x60);
                ++row;
                height = word(destination + 0x6c);
            } while (row < height);
        ++slice;
        destination = word(self + 4);
    } while (slice < word(destination + 0x70));
    return 0;
}
// Complete5eddce..5edea1. Genuine CRT new, constructor iterator and free remain
// ordinary dependencies, not backend allocation fixtures or successful stubs.
extern "C" int32_t __attribute__((thiscall)) FUN_005eddce(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    u32 destination = word(self + 4), source = word(self);
    const u32 width = word(destination + 0x68);
    if (width != word(source + 0x68))
        return failure;
    u32 value = word(destination + 0x6c);
    if (value != word(source + 0x6c))
        return failure;
    value = word(destination + 0x70);
    if (value != word(source + 0x70))
        return failure;
    void* allocated = fun_005cc96d(width << 4);
    if (allocated)
        FUN_00405c90(allocated, 16, width, reinterpret_cast<uintptr_t>(&FUN_004441b0));
    if (!allocated)
        return failure;
    destination = word(self + 4);
    if (word(destination + 0x10)) {
        source = word(self);
        if (word(source + 0x10)) {
            put(destination + 0x10, 0);
            source = word(self);
            put(source + 0x10, 0);
        }
    }
    destination = word(self + 4);
    u32 slice = 0;
    if (word(destination + 0x70)) {
        u32 height = word(destination + 0x6c);
        do {
            u32 row = 0;
            if (height)
                do {
                    source = word(self);
                    u32 table = word(source);
                    u32 code = word(table + 4);
                    row_callback(table, code, source, row, slice,
                                 reinterpret_cast<uintptr_t>(allocated));
                    destination = word(self + 4);
                    table = word(destination);
                    code = word(table + 8);
                    row_callback(table, code, destination, row, slice,
                                 reinterpret_cast<uintptr_t>(allocated));
                    destination = word(self + 4);
                    height = word(destination + 0x6c);
                    ++row;
                } while (row < height);
            destination = word(self + 4);
            ++slice;
        } while (slice < word(destination + 0x70));
    }
    fun_005cc620(allocated);
    return 0;
}
