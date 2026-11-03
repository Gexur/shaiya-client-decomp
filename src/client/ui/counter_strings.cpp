#include "counter_strings.h"
#include "profile_access.h"
#include "startup/client_locale.h"
namespace {
using u32 = uint32_t;
using s32 = int32_t;
using Convert = s32(__attribute__((stdcall)) *)(u32, u32, const uint16_t*, s32, char*, s32,
                                                const char*, int32_t*);
extern "C" Convert imported_counter_wide __asm__("__imp__WideCharToMultiByte@32");
u32 word(const void* base, u32 offset) {
    u32 value;
    auto* at = reinterpret_cast<const uint8_t*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
u32 half(const void* base, u32 offset) {
    u32 value;
    auto* at = reinterpret_cast<const uint8_t*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movzwl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
uint8_t byte(u32 address) {
    uint8_t value;
    __asm__ volatile("movb (%1),%0" : "=q"(value) : "r"(address) : "memory");
    return value;
}
void put_byte(u32 address, uint8_t value) {
    __asm__ volatile("movb %1,(%0)" ::"r"(address), "q"(value) : "memory");
}
Convert conversion() {
    u32 value;
    __asm__ volatile("movl %1,%0" : "=r"(value) : "m"(imported_counter_wide) : "memory");
    return reinterpret_cast<Convert>(value);
}
void clear(u32 address) {
    u32 count = 512;
    __asm__ volatile("rep stosl" : "+D"(address), "+c"(count) : "a"(0) : "memory", "cc");
}
void* pointer(u32 value) {
    return reinterpret_cast<void*>(value);
}
} // namespace
// Original531a80..531af0. The nonnull branch captures its IAT target once,
// caches codepage/source/count, and reloads original capacity/output words.
extern "C" s32 recovered_00531a80(const u32* arguments) {
    const u32 output = word(arguments, 12);
    if (output == 0) {
        const s32 count = static_cast<s32>(word(arguments, 8));
        const auto* source = reinterpret_cast<const uint16_t*>(word(arguments, 4));
        const u32 codepage = word(arguments, 0);
        return conversion()(codepage, 0, source, count, nullptr, 0, nullptr, nullptr);
    }
    const u32 codepage = word(arguments, 0);
    const Convert convert = conversion();
    const s32 count = static_cast<s32>(word(arguments, 8));
    const auto* source = reinterpret_cast<const uint16_t*>(word(arguments, 4));
    const s32 required = convert(codepage, 0, source, count, nullptr, 0, nullptr, nullptr);
    if (required >= static_cast<s32>(word(arguments, 16)))
        return 0;
    auto* destination = reinterpret_cast<char*>(word(arguments, 12));
    return convert(codepage, 0, source, count, destination, required, nullptr, nullptr);
}
extern "C" __attribute__((naked)) s32 FUN_00531a80(u32, const uint16_t*, s32, char*, s32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00531a80\n\taddl $4,%esp\n\tretl");
}

// Original532bc0..532c76. Its ordinary narrow-string branch ignores the
// incoming capacity entirely and performs the actual unchecked NUL copy.
extern "C" s32 recovered_00532bc0(void* self, const u32* arguments) {
    if (word(&dat_00708598, 0) != 3) {
        const u32 capacity = word(self, 0xb8);
        u32 source = capacity < 16 ? reinterpret_cast<u32>(self) + 0xa4 : word(self, 0xa4);
        u32 destination = word(arguments, 0);
        uint8_t value;
        do {
            value = byte(source);
            ++source;
            put_byte(destination, value);
            ++destination;
        } while (value != 0);
        return static_cast<s32>(word(self, 0xb4));
    }
    u32 capacity = word(self, 0x9c);
    s32 count = static_cast<s32>(word(self, 0x98));
    u32 source = capacity < 8 ? reinterpret_cast<u32>(self) + 0x88 : word(self, 0x88);
    const Convert convert = conversion();
    const s32 required = convert(65001, 0, reinterpret_cast<const uint16_t*>(source), count,
                                 nullptr, 0, nullptr, nullptr);
    if (required >= static_cast<s32>(word(arguments, 4)))
        return 0;
    capacity = word(self, 0x9c);
    count = static_cast<s32>(word(self, 0x98));
    source = capacity < 8 ? reinterpret_cast<u32>(self) + 0x88 : word(self, 0x88);
    auto* destination = reinterpret_cast<char*>(word(arguments, 0));
    return convert(65001, 0, reinterpret_cast<const uint16_t*>(source), count, destination,
                   required, nullptr, nullptr);
}
extern "C" __attribute__((naked, thiscall)) s32 FUN_00532bc0(void*, char*, s32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_00532bc0\n\taddl $8,%esp\n\tretl $8");
}

extern "C" u32 __attribute__((thiscall)) FUN_00532dc0(void* self) {
    const u32 output = reinterpret_cast<u32>(self) + 0xdc;
    clear(output);
    const s32 result = FUN_00532bc0(self, reinterpret_cast<char*>(output), 2048);
    return result != 0 ? output : reinterpret_cast<u32>(shaiya::ui::dat_006bb5d5);
}
extern "C" u32 __attribute__((thiscall)) FUN_00532eb0(void* self) {
    if (word(&dat_00708598, 0) == 3)
        return reinterpret_cast<u32>(shaiya::ui::dat_006bb5d5);
    const u32 output = reinterpret_cast<u32>(self) + 0x8dc;
    clear(output);
    const u32 capacity = word(self, 0x80), count = word(self, 0x7c);
    const u32 source = capacity < 8 ? reinterpret_cast<u32>(self) + 0x6c : word(self, 0x6c);
    const u32 codepage = half(self, 0x361a);
    const s32 result = FUN_00531a80(codepage, reinterpret_cast<const uint16_t*>(source),
                                    static_cast<s32>(count), reinterpret_cast<char*>(output), 2048);
    return result != 0 ? output : reinterpret_cast<u32>(shaiya::ui::dat_006bb5d5);
}
