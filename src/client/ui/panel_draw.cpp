#include "panel_draw.h"
#include "ordered_stores.h"
#include "startup/application.h"
#include "core/x87_runtime.h"

namespace {
using namespace shaiya::ui::ordered_detail;
using u32 = uint32_t;
using u8 = uint8_t;

u8 byte(void* self, u32 offset) {
    u8 value;
    auto* address = static_cast<u8*>(self) + offset;
    __asm__ volatile("movb (%1),%0" : "=q"(value) : "r"(address) : "memory");
    return value;
}
// Original5290f4..529131: status-word tests deliberately retain unordered
// behavior, followed by the real x87 integer-conversion routine. In particular
// unordered is not silently clamped by a C++ comparison or converted with UB.
u32 alpha(u32 bits) {
    static const float one = 1.0f, zero = 0.0f, scale = 255.0f, half = 0.5f;
    uint16_t status;
    __asm__ volatile("flds %1\n\tfcomps %2\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "m"(bits), "m"(one)
                     : "st", "cc");
    if ((status & 0x100u) == 0)
        return 255;
    __asm__ volatile("flds %1\n\tfcomps %2\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "m"(bits), "m"(zero)
                     : "st", "cc");
    const u32 mask = status & 0x4100u;
    if (mask != 0 && mask != 0x4100u)
        return 0;
    long double value;
    __asm__ volatile("flds %1\n\tfmuls %2\n\tfadds %3\n\tfstpt %0"
                     : "=m"(value)
                     : "m"(bits), "m"(scale), "m"(half)
                     : "st", "cc");
    return static_cast<u32>(x87_to_integer_005cd414(value));
}
void* pointer(u32 value) {
    return reinterpret_cast<void*>(value);
}
} // namespace

extern "C" uint32_t __attribute__((thiscall)) FUN_00529040(void* self) {
    u32 image = load32(self, 0x22c);
    if (image != 0) {
        const u32 color = (alpha(load32(self, 0x14)) << 24) | 0x00ffffffu;
        const u32 y = load32(self, 8), x = load32(self, 4);
        FUN_00549ff0(pointer(image + 4), color, x, y);
    }
    if (byte(self, 0x19) != 0) {
        image = load32(self, 0x230);
        if (image != 0) {
            const u32 color = (alpha(load32(self, 0x14)) << 24) | 0x00ffffffu;
            const u32 y0 = load32(self, 8), dy = load32(self, 0x20);
            const u32 dx = load32(self, 0x1c), x0 = load32(self, 4);
            FUN_00549ff0(pointer(image + 4), color, dx + x0, dy + y0);
        }
    }
    u32 header = load32(self, 0x238), node = load32(pointer(header), 0);
    while (node != header) {
        const u32 value = load32(pointer(node), 8);
        if (value != 0)
            FUN_0052d390(pointer(value));
        node = load32(pointer(node), 0);
        header = load32(self, 0x238);
    }
    // EAX remains the second header until a non-null child call replaces it.
    // This preserves the original observable register result without guessing
    // an application meaning for that result.
    header = load32(self, 0x244);
    node = load32(pointer(header), 0);
    u32 result = header;
    while (node != header) {
        const u32 value = load32(pointer(node), 8);
        if (value != 0)
            result = FUN_005277a0(pointer(value));
        node = load32(pointer(node), 0);
        header = load32(self, 0x244);
    }
    return result;
}

extern "C" uint32_t __attribute__((thiscall)) FUN_0052d390(void* self) {
    const u32 y = load32(self, 0x30), x = load32(self, 0x2c);
    return FUN_0052d030(self, x, y, 0, 0xff2a2a2au);
}

extern "C" uint32_t __attribute__((thiscall)) FUN_00528b00(void* self, u32 x, u32 y) {
    const u32 result_x = load32(self, 0x10) + x;
    store32(self, 0x38, x);
    const u32 result_y = load32(self, 0x14) + y;
    store32(self, 0x3c, y);
    store32(self, 0x18, result_x);
    store32(self, 0x1c, result_y);
    return FUN_005277a0(self);
}
