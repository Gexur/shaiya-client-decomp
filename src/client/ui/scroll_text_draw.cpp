#include "scroll_text_draw.h"
#include "font_selector.h"
#include "core/x87_runtime.h"
namespace {
using u32 = uint32_t;
using s32 = int32_t;
u32 word(const void* base, u32 offset) {
    u32 value;
    const auto* at = reinterpret_cast<const uint8_t*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
void put(void* base, u32 offset, u32 value) {
    auto* at = reinterpret_cast<uint8_t*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl %1,(%0)" ::"r"(at), "r"(value) : "memory");
}
void* pointer(u32 value) {
    return reinterpret_cast<void*>(value);
}
u32 callback(u32 target, u32 top, u32 x, u32 y) {
    u32 result = x, context = top;
    // Original52d2d6 also supplies EAX=x,ECX=top,EDX=target. The observed
    // callback is cdecl and caller-pops the two actual stack arguments.
    __asm__ volatile("pushl %3\n\tpushl %%eax\n\tcalll *%%edx\n\taddl $8,%%esp"
                     : "+a"(result), "+c"(context), "+d"(target)
                     : "r"(y)
                     : "memory", "cc");
    return result;
}
void font(u32 x, u32 y, u32 color, u32 text) {
    (void)FUN_00541aa0(dat_02209408, x, y, color, reinterpret_cast<const char*>(text), 0);
}
u32 final_font(u32 x, u32 y, u32 color, u32 text) {
    return FUN_00541aa0(dat_02209408, x, y, color, reinterpret_cast<const char*>(text), 0);
}
} // namespace
// Original0052d030..0052d2ec. The source preserves observable residual EAX
// without assigning an application meaning to pointer/row/register returns.
extern "C" u32 recovered_0052d030(void* self, const u32* arguments) {
    const u32 x = word(arguments, 0), base_x = word(self, 8), y = word(arguments, 4);
    put(self, 0x2c, x);
    const u32 base_y = word(self, 12);
    put(self, 0x30, y);
    put(self, 0x10, base_x + x);
    put(self, 0x14, base_y + y);
    // Opacity is carried by each row's packed ARGB below. The native font pass
    // supplies its own alpha blend and texture modulation for each submission.
    const u32 first_header = word(self, 0x50);
    u32 result = first_header, node = word(pointer(first_header), 0);
    if (node != first_header) {
        const u32 minimum = word(self, 0x20);
        do {
            (void)word(pointer(node), 8);
            (void)word(pointer(node), 12);
            const u32 row = word(pointer(node), 16);
            (void)word(pointer(node), 20);
            if (static_cast<s32>(row) >= static_cast<s32>(minimum))
                break;
            node = word(pointer(node), 0);
        } while (node != word(self, 0x50));
        if (node != first_header) {
            do {
                static const float scale = 255.0f;
                // Original FLD precedes the first node word; FMUL follows
                // that word and precedes the remaining three node words.
                __asm__ volatile("flds 0x3c(%0)" ::"r"(self) : "st", "memory");
                const u32 color = word(pointer(node), 8);
                __asm__ volatile("fmuls %0" ::"m"(scale) : "st", "memory");
                const u32 offset_x = word(pointer(node), 12), row = word(pointer(node), 16),
                          text = word(pointer(node), 20);
                uint64_t alpha;
                __asm__ volatile("calll _FUN_005cd414"
                                 : "=A"(alpha)::"ecx", "st", "st(1)", "memory", "cc");
                const u32 packed =
                    ((static_cast<u32>(alpha) << 8 | (color & 255)) << 8 | ((color >> 8) & 255))
                        << 8 |
                    ((color >> 16) & 255);
                result = word(self, 0x28);
                if (result != 0xffffffffu) {
                    const u32 top = word(self, 0x20);
                    if (static_cast<s32>(row - top + 1) > static_cast<s32>(result))
                        break;
                }
                if (word(arguments, 8) == 1) {
                    u32 shadow = word(arguments, 12), top = word(self, 0x20),
                        height = word(self, 0x44), origin_y = word(self, 0x14),
                        origin_x = word(self, 0x10);
                    font(origin_x + offset_x, (row - top) * height + origin_y - 1, shadow, text);
                    shadow = word(arguments, 12);
                    top = word(self, 0x20);
                    height = word(self, 0x44);
                    origin_y = word(self, 0x14);
                    origin_x = word(self, 0x10);
                    font(origin_x + offset_x, (row - top) * height + origin_y + 1, shadow, text);
                    shadow = word(arguments, 12);
                    origin_y = word(self, 0x14);
                    top = word(self, 0x20);
                    height = word(self, 0x44);
                    origin_x = word(self, 0x10);
                    font(origin_x + offset_x - 1, (row - top) * height + origin_y, shadow, text);
                    shadow = word(arguments, 12);
                    top = word(self, 0x20);
                    height = word(self, 0x44);
                    origin_x = word(self, 0x10);
                    origin_y = word(self, 0x14);
                    font(origin_x + offset_x + 1, (row - top) * height + origin_y, shadow, text);
                }
                const u32 top = word(self, 0x20), origin_y = word(self, 0x14),
                          height = word(self, 0x44), origin_x = word(self, 0x10);
                result =
                    final_font(origin_x + offset_x, (row - top) * height + origin_y, packed, text);
                node = word(pointer(node), 0);
            } while (node != word(self, 0x50));
        }
    }
    const u32 second_header = word(self, 0x5c);
    node = word(pointer(second_header), 0);
    if (node != second_header) {
        const u32 minimum = word(self, 0x20);
        do {
            (void)word(pointer(node), 8);
            result = word(pointer(node), 12);
            (void)word(pointer(node), 16);
            if (static_cast<s32>(result) >= static_cast<s32>(minimum))
                break;
            node = word(pointer(node), 0);
        } while (node != word(self, 0x5c));
        if (node != second_header) {
            do {
                const u32 offset_x = word(pointer(node), 8), row = word(pointer(node), 12),
                          kind = word(pointer(node), 16), limit = word(self, 0x28);
                result = row;
                if (limit != 0xffffffffu) {
                    const u32 top = word(self, 0x20);
                    if (static_cast<s32>(row - top + 1) > static_cast<s32>(limit))
                        break;
                }
                if (static_cast<s32>(kind) < 5) {
                    const u32 target = word(dat_02203660, kind * 4);
                    if (target != 0) {
                        const u32 top = word(self, 0x20), origin_y = word(self, 0x14),
                                  height = word(self, 0x44), origin_x = word(self, 0x10);
                        result = callback(target, top, origin_x + offset_x,
                                          (row - top) * height + origin_y);
                    }
                }
                node = word(pointer(node), 0);
            } while (node != word(self, 0x5c));
        }
    }
    return result;
}
extern "C" u32 __attribute__((naked, thiscall)) FUN_0052d030(void*, u32, u32, u32, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_0052d030\n\taddl $8,%esp\n\tretl $16");
}
