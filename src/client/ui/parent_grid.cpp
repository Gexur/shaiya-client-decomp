#include "parent_grid.h"

namespace shaiya::ui {
namespace {
using s32 = int;
const u8* at(const void* base, u32 offset) {
    return reinterpret_cast<const u8*>(reinterpret_cast<u32>(base) + offset);
}
u32 word(const void* base, u32 offset) {
    u32 value;
    const auto* p = at(base, offset);
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
u32 byte(const void* base, u32 offset) {
    u32 value;
    const auto* p = at(base, offset);
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
void put_word(void* base, u32 offset, u32 value) {
    const auto* p = at(base, offset);
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(value) : "memory");
}
void put_byte(void* base, u32 offset, u8 value) {
    const auto* p = at(base, offset);
    __asm__ volatile("movb %1,(%0)" ::"r"(p), "q"(value) : "memory");
}
void* member(void* base, u32 offset) {
    return const_cast<u8*>(at(base, offset));
}
bool less(u32 left, u32 right) {
    return static_cast<s32>(left) < static_cast<s32>(right);
}
bool greater(u32 left, u32 right) {
    return static_cast<s32>(left) > static_cast<s32>(right);
}
u32 length(const u8* text) {
    u32 n = 0;
    while (byte(text, n) != 0)
        ++n;
    return n;
}
u32 eighth(u32 value) {
    const float f = static_cast<float>(static_cast<s32>(value)) * 0.125f;
    u32 bits;
    __builtin_memcpy(&bits, &f, 4);
    return bits;
}

void header(Object_004a0fd0* self, u32 center) {
    u32 y = word(self, 8), x = word(self, 4);
    put_word(self, 0x654, 0);
    (void)FUN_00549a70(member(self, 0x2c), x, y);
    y = word(self, 8) + 7;
    x = word(self, 4) + 7;
    (void)FUN_00549a70(member(self, 0x6c), x, y);
    y = word(self, 8);
    x = word(self, 4);
    (void)FUN_00528b00(member(self, 0x7c), x, y);
    for (u32 which = 0; which < 2; ++which) {
        const auto* text = at(self, 0x82c + which * 0x80);
        if (length(text) == 0)
            continue;
        const u32 count = length(text);
        const u32 width = FUN_005430a0(dat_02209408, reinterpret_cast<const char*>(text), count, 0);
        const u32 half = static_cast<u32>(static_cast<s32>(155u - width) / 2);
        x = word(self, 4);
        y = word(self, 8) + (which == 0 ? 0x16 : 0x2e);
        (void)FUN_005418c0(dat_02209408, x + half + center, y, 0xffffffffu, 0,
                           reinterpret_cast<const char*>(text));
    }
}

u32 grid(Object_004a0fd0* self, u32 columns, u32 rows) {
    u32 x = word(self, 4) + 15;
    u32 y = word(self, 8) + 0x92, bottom = y + 32, selected = 0xffffffffu;
    for (u32 row = 0; row < rows; ++row) {
        u32 right = x + 32;
        for (u32 column = 0; column < columns; ++column) {
            const u32 mode = word(self, 0x820);
            const u32 index = columns == 6 ? (row + mode * 4 - 4) * 6 + column
                                           : (row + mode * 5) * 8 + column - 40;
            if (!less(index, 240)) {
                row = rows;
                break;
            }
            const u32 offset = index * 40;
            const u32 first = byte(dat_021fed65, offset);
            if (first != 0) {
                const u32 third = byte(dat_021fed65, offset + 2);
                const u32 second = byte(dat_021fed65, offset + 1);
                (void)FUN_004a3400(&self->subobject_654, 0xffffffffu, x, y, first, second, third, 0,
                                   1);
                if (byte(self, 0x709) == 0xff) {
                    const u32 mouse_x = word(&dat_0071c2a4, 0);
                    if (!less(mouse_x, x) && !greater(mouse_x, right)) {
                        const u32 mouse_y = word(&dat_0071c2a8, 0);
                        if (!less(mouse_y, y) && !greater(mouse_y, bottom)) {
                            put_word(self, 0x654, 1);
                            const u32 current_first = byte(dat_021fed65, offset);
                            put_byte(self, 0x658, static_cast<u8>(current_first));
                            const u32 current_second = byte(dat_021fed65, offset + 1);
                            selected = index;
                            put_byte(self, 0x659, static_cast<u8>(current_second));
                        }
                    }
                }
            }
            right += 39;
            x += 39;
        }
        x = word(self, 4) + 15;
        y += 39;
        bottom += 39;
    }
    return selected;
}

void five_tabs(Object_004a0fd0* self) {
    for (u32 page = 1, offset = 0; page <= 5; ++page, offset += 47) {
        u32 x = word(self, 4) + offset + 11;
        const u32 mouse_x = word(&dat_0071c2a4, 0);
        bool hover = false;
        u32 y = 0;
        if (!less(mouse_x, x) && !greater(mouse_x, x + 46)) {
            y = word(self, 8);
            const u32 first_mouse_y = word(&dat_0071c2a8, 0);
            if (!less(first_mouse_y, y + 0x72)) {
                const u32 second_mouse_y = word(&dat_0071c2a8, 0);
                hover = !greater(second_mouse_y, y + 0x8e);
            }
        }
        const u32 mode = word(self, 0x820);
        if (!hover)
            y = word(self, 8);
        const bool selected = mode == page;
        const u32 upper = eighth(page), lower = eighth(page - 1);
        const u32 first_u = hover ? 0x3f000000u : 0, second_u = hover ? 0x3f800000u : 0x3f000000u;
        (void)FUN_00549ba0(member(self, selected ? 0x4c : 0x3c), 0xffffffffu, x,
                           y + (selected ? 0x72 : 0x78), 64, 32, first_u, second_u, lower, upper);
        y = word(self, 8) + (selected ? 0x72 : 0x78);
        x += selected ? 14 : 16;
        (void)FUN_00549ba0(member(self, 0x5c), 0xffffffffu, x, y, 32, 32,
                           selected ? 0 : 0x3f000000u, selected ? 0x3f000000u : 0x3f800000u, 0,
                           0x3f800000u);
    }
}
} // namespace

// Original0049fba0..0049ffc2 and004a0390..004a05ef. Shared helpers above
// retain the original two byte scans, mutable mode per record and callbacks'
// changes to later positions, record bytes and hover globals.
extern "C" u32 __attribute__((thiscall)) FUN_0049fba0(Object_004a0fd0* self) {
    header(self, 0x41);
    const u32 selected = grid(self, 6, 4);
    five_tabs(self);
    return selected;
}
extern "C" u32 __attribute__((thiscall)) FUN_004a0390(Object_004a0fd0* self) {
    header(self, 0x5a);
    const u32 selected = grid(self, 8, 5);
    (void)FUN_0049ffd0(self);
    return selected;
}

// Original0049ffd0..004a01ae. Off-hover unselected tabs deliberately skip
// the larger draw. That asymmetry is present in the original instructions.
extern "C" u32 __attribute__((thiscall)) FUN_0049ffd0(Object_004a0fd0* self) {
    for (u32 page = 0, offset = 0; offset < 312; ++page, offset += 52) {
        u32 color = 0xffffffffu;
        if (word(&shaiya::config::dat_00708598, 0) == 2 && byte(&dat_021fed20, 0) == 0 &&
            offset != 0)
            color = 0xffff0000u;
        u32 x = word(self, 4) + offset + 9;
        const u32 mouse_x = word(&dat_0071c2a4, 0);
        bool hover = false;
        u32 y = 0;
        if (!less(mouse_x, x) && !greater(mouse_x, x + 51)) {
            y = word(self, 8);
            const u32 mouse_y = word(&dat_0071c2a8, 0);
            hover = !less(mouse_y, y + 0x72) && !greater(mouse_y, y + 0x8e);
        }
        const u32 mode = word(self, 0x820);
        const bool selected = mode == page + 1;
        if (!hover)
            y = word(self, 8);
        if (hover || selected) {
            const u32 upper = eighth(page + 1), lower = eighth(page);
            const u32 first_u = hover ? 0x3f000000u : 0,
                      second_u = hover ? 0x3f800000u : 0x3f000000u;
            (void)FUN_00549ba0(member(self, selected ? 0x4c : 0x3c), color, x + (selected ? 2 : 0),
                               y + (selected ? 0x72 : 0x78), 64, 32, first_u, second_u, lower,
                               upper);
            y = word(self, 8);
        }
        y += selected ? 0x72 : 0x78;
        x += selected ? 14 : 16;
        (void)FUN_00549ba0(member(self, 0x5c), color, x, y, 32, 32, selected ? 0 : 0x3f000000u,
                           selected ? 0x3f000000u : 0x3f800000u, 0, 0x3f800000u);
    }
    return 312;
}
} // namespace shaiya::ui
