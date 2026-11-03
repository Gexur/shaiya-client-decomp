#include "graphics/surface/surface_extend_backend.h"
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
unsigned char byte(u32 p) {
    unsigned char v;
    __asm__ volatile("movb (%1),%0" : "=q"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void clear(u32 destination, u32 bytes) {
    u32 count = bytes >> 2;
    __asm__ volatile("rep stosl" : "+D"(destination), "+c"(count) : "a"(0) : "memory");
    count = bytes & 3;
    __asm__ volatile("rep stosb" : "+D"(destination), "+c"(count) : "a"(0) : "memory");
}
void row_call(u32 receiver, u32 row, u32 slice, u32 buffer, u32 offset) {
    const u32 table = word(receiver), code = word(table + offset), words[3] = {row, slice, buffer};
    u32 incoming_eax = table;
    __asm__ volatile("pushl 8(%3)\n\tpushl 4(%3)\n\tpushl (%3)\n\tcalll *%2"
                     : "+a"(incoming_eax), "+c"(receiver)
                     : "r"(code), "r"(words)
                     : "edx", "memory", "cc");
}
constexpr int32_t failure = static_cast<int32_t>(0x80004005u);
} // namespace
// Complete5edea1..5ee074. The first scratch length is MAX(widths), whereas
// copied rows/slices are MIN(height/depth). Fresh destination dimensions are
// deliberately reloaded only at the original sites; no general resize model.
extern "C" int32_t __attribute__((thiscall)) FUN_005edea1(void* object) {
    const u32 self = reinterpret_cast<uintptr_t>(object);
    if (byte(self + 8) != 1)
        return failure;
    u32 destination = word(self + 4), source = word(self);
    const u32 destination_width = word(destination + 0x68), source_width = word(source + 0x68);
    const u32 max_width = destination_width > source_width ? destination_width : source_width;
    const u32 destination_height = word(destination + 0x6c), source_height = word(source + 0x6c);
    const u32 copied_height =
        destination_height < source_height ? destination_height : source_height;
    const u32 destination_depth = word(destination + 0x70), source_depth = word(source + 0x70);
    const u32 copied_depth = destination_depth < source_depth ? destination_depth : source_depth;
    const u32 first_bytes = max_width << 4;
    void* first = fun_005cc96d(first_bytes);
    if (first)
        FUN_00405c90(first, 16, max_width, reinterpret_cast<uintptr_t>(&FUN_004441b0));
    if (!first)
        return failure;
    destination = word(self + 4);
    const u32 second_width = word(destination + 0x68);
    void* second = fun_005cc96d(second_width << 4);
    if (second)
        FUN_00405c90(second, 16, second_width, reinterpret_cast<uintptr_t>(&FUN_004441b0));
    if (!second) {
        fun_005cc620(first);
        return failure;
    }
    clear(reinterpret_cast<uintptr_t>(first), first_bytes);
    destination = word(self + 4);
    const u32 zero_width = word(destination + 0x68);
    clear(reinterpret_cast<uintptr_t>(second), zero_width << 4);
    destination = word(self + 4);
    if (word(destination + 0x10)) {
        source = word(self);
        if (word(source + 0x10)) {
            put(destination + 0x10, 0);
            source = word(self);
            put(source + 0x10, 0);
        }
    }
    u32 slice = 0;
    if (copied_depth)
        do {
            u32 row = 0;
            if (copied_height)
                do {
                    source = word(self);
                    row_call(source, row, slice, reinterpret_cast<uintptr_t>(first), 4);
                    destination = word(self + 4);
                    row_call(destination, row, slice, reinterpret_cast<uintptr_t>(first), 8);
                    ++row;
                } while (row < copied_height);
            destination = word(self + 4);
            row = copied_height;
            if (row < word(destination + 0x6c))
                do {
                    destination = word(self + 4);
                    row_call(destination, row, slice, reinterpret_cast<uintptr_t>(second), 8);
                    destination = word(self + 4);
                    ++row;
                } while (row < word(destination + 0x6c));
            ++slice;
        } while (slice < copied_depth);
    // The next slice reuses the last height value (original EAX); it does not
    // reload height at the top merely because the device/descriptor changed.
    u32 extra_slice = copied_depth;
    destination = word(self + 4);
    if (extra_slice < word(destination + 0x70)) {
        u32 height = word(destination + 0x6c);
        do {
            u32 row = 0;
            if (height)
                do {
                    destination = word(self + 4);
                    row_call(destination, row, extra_slice, reinterpret_cast<uintptr_t>(second), 8);
                    destination = word(self + 4);
                    height = word(destination + 0x6c);
                    ++row;
                } while (row < height);
            destination = word(self + 4);
            ++extra_slice;
        } while (extra_slice < word(destination + 0x70));
    }
    fun_005cc620(first);
    fun_005cc620(second);
    return 0;
}
