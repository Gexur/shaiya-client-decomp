#include "string_append.h"
#include "core/string_internal.h"

using shaiya::startup::String_00405710;
namespace {
inline uint32_t read32(uint32_t address) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
inline void write32(uint32_t address, uint32_t value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(address), "r"(value) : "memory");
}
inline void zero8(uint32_t address) {
    __asm__ volatile("movb $0,(%0)" ::"r"(address) : "memory");
}
} // namespace

// Complete instruction-derived 00533d50..00533e39 control flow. Raw slot loads
// preserve position-before-source, deferred count and late position reload.
extern "C" String_00405710* __attribute__((cdecl)) recovered_00533d50(String_00405710* self,
                                                                      const uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    const uint32_t destination = reinterpret_cast<uint32_t>(self);
    const uint32_t position = read32(slots + 4);
    const uint32_t source = read32(slots);
    if (read32(source + 0x14) < position)
        FUN_005e1911();
    const uint32_t remaining = read32(source + 0x14) - position;
    uint32_t count = read32(slots + 8);
    if (remaining < count)
        count = remaining;
    const uint32_t previous = read32(destination + 0x14);
    if (0xffffffffu - previous <= count)
        FUN_005e1951(self);
    if (!count)
        return self;
    const uint32_t total = read32(destination + 0x14) + count;
    if (total > 0xfffffffeu)
        FUN_005e1951(self);
    const uint32_t capacity = read32(destination + 0x18);
    if (capacity < total) {
        FUN_004054e0(self, total, read32(destination + 0x14));
        if (!total)
            return self;
    } else if (!total) {
        write32(destination + 0x14, 0);
        zero8(capacity < 16 ? destination + 4 : read32(destination + 4));
        return self;
    }
    const uint32_t source_capacity = read32(source + 0x18);
    const uint32_t source_data = source_capacity < 16 ? source + 4 : read32(source + 4);
    const uint32_t destination_capacity = read32(destination + 0x18);
    const uint32_t destination_data =
        destination_capacity < 16 ? destination + 4 : read32(destination + 4);
    const uint32_t late_position = read32(slots + 4);
    const uint32_t old_size = read32(destination + 0x14);
    shaiya::recovered_string::copy(
        reinterpret_cast<unsigned char*>(destination_data + old_size),
        reinterpret_cast<const unsigned char*>(source_data + late_position), count);
    const uint32_t final_capacity = read32(destination + 0x18);
    write32(destination + 0x14, total);
    const uint32_t final_data = final_capacity < 16 ? destination + 4 : read32(destination + 4);
    zero8(final_data + total);
    return self;
}

extern "C" __attribute__((naked)) String_00405710* __attribute__((thiscall))
FUN_00533d50(String_00405710*, const String_00405710*, uint32_t, uint32_t) {
    __asm__ volatile("leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\t"
                     "calll _recovered_00533d50\n\taddl $8,%esp\n\tretl $12");
}
