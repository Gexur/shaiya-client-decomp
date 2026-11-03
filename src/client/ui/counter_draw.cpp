#include "ui/counter_draw.h"
#include "profile_access.h"
#include "runtime/stdio_format.h"
namespace shaiya::ui {
extern "C" {
extern const char dat_006be170[3] __attribute__((visibility("hidden")));
extern const char dat_006bc494[5] __attribute__((visibility("hidden")));
}
namespace {
u32 word(const void* base, u32 offset) {
    u32 value;
    auto* at = static_cast<const u8*>(base) + offset;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
void* member(void* self, u32 offset) {
    return static_cast<u8*>(self) + offset;
}
} // namespace
// Original00426740..004268a2. Every child receives newly loaded coordinates;
// the type query tests AX only. The two text getters have no stack inputs:
// original pushes the second string before calling the first-string getter.
extern "C" u32 __attribute__((thiscall)) FUN_00426740(void* self) {
    char text[260];
    u32 y = word(self, 8), x = word(self, 4);
    (void)FUN_00549a70(member(self, 12), x, y);
    if (word(self, 0x1d5c) != 0) {
        (void)FUN_00532400(dat_02203adc, 9, 0x96, 1, 0);
        y = word(self, 8);
        x = word(self, 4);
        (void)FUN_00545ed0(dat_02209408, x + 0x1eu, y + 0x25u, 0, 0, 0);
        const u32 type = FUN_00531b30(dat_02203adc);
        if (static_cast<u16>(type) == 0x12) {
            const u32 second = FUN_00532eb0(dat_02203adc);
            const u32 first = FUN_00532dc0(dat_02203adc);
            (void)fun_005cd489(static_cast<char*>(member(self, 0x1d60)), dat_006bc494,
                               reinterpret_cast<const char*>(first),
                               reinterpret_cast<const char*>(second));
        } else {
            const u32 first = FUN_00532dc0(dat_02203adc);
            (void)fun_005cd489(static_cast<char*>(member(self, 0x1d60)), dat_006be170,
                               reinterpret_cast<const char*>(first));
        }
    } else {
        (void)fun_005cd489(text, dat_006bcafc, static_cast<int32_t>(word(self, 0x1d58)));
        y = word(self, 8);
        x = word(self, 4);
        (void)FUN_00543d30(dat_02209408, x + 0x1eu, y + 0x25u, 0xff, 0xff, 0xff, 0, 0xa0, text);
    }
    u32 result;
    const u32 offsets[5] = {0x1cu, 0x5f4u, 0xbccu, 0x11a4u, 0x177cu};
    for (u32 offset : offsets) {
        y = word(self, 8);
        x = word(self, 4);
        result = FUN_00528b00(member(self, offset), x, y);
    }
    return result;
}
} // namespace shaiya::ui
