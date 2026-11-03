#include "panel_resource.h"
#include "panel_caption.h"
#include "font_centered.h"
#include "font_text.h"
#include "core/quad_draw.h"
#include "core/x87_runtime.h"
#include "core/untouched_lifetime.h"
#include "startup/application.h"
extern "C" {
extern unsigned char dat_02209408[];
extern float dat_00719a54;
uint32_t recovered_005276d0(void*, uint32_t);
uint32_t recovered_00549ba0(void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                            uint32_t, uint32_t, uint32_t, uint32_t);
}
namespace {
using u32 = uint32_t;
u32 word(const void* base, u32 offset) {
    u32 result;
    const auto* at = reinterpret_cast<const unsigned char*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl (%1),%0" : "=r"(result) : "r"(at) : "memory");
    return result;
}
uint8_t byte(const void* base, u32 offset) {
    uint8_t result;
    const auto* at = reinterpret_cast<const unsigned char*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movb (%1),%0" : "=q"(result) : "r"(at) : "memory");
    return result;
}
void put(void* base, u32 offset, u32 value) {
    auto* at = reinterpret_cast<unsigned char*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl %1,(%0)" ::"r"(at), "r"(value) : "memory");
}
void put_byte(void* base, u32 offset, uint8_t value) {
    auto* at = reinterpret_cast<unsigned char*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movb %1,(%0)" ::"r"(at), "q"(value) : "memory");
}
void multiply_alpha(void* self, u32* frame) {
    __asm__ volatile("flds (%0)\n\tfmuls 0x9c(%1)\n\tfstps (%0)" ::"r"(frame), "r"(self)
                     : "st", "memory");
}
uint16_t compare(u32 bits, const float& limit) {
    uint16_t status;
    __asm__ volatile("flds %1\n\tfcomps %2\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "m"(bits), "m"(limit)
                     : "st", "memory", "cc");
    return status;
}
u32 channel(u32 bits) {
    static const float one = 1.0f, zero = 0.0f, scale = 255.0f, half = 0.5f;
    if ((compare(bits, one) & 0x100) == 0)
        return 255;
    const u32 masked = compare(bits, zero) & 0x4100;
    // Original TEST AH,41h;JP also takes the unordered case. No conventional
    // NaN/clamp replacement is inferred from decompiler floating comparisons.
    if (masked != 0 && masked != 0x4100)
        return 0;
    uint64_t converted;
    __asm__ volatile("flds %1\n\tfmuls %2\n\tfadds %3\n\tcalll _FUN_005cd414"
                     : "=A"(converted)
                     : "m"(bits), "m"(scale), "m"(half)
                     : "ecx", "st", "st(1)", "memory", "cc");
    return static_cast<u32>(converted);
}
void color_words(u32* frame, u32 r, u32 g, u32 b, u32 alpha) {
    put(frame, 4, r);
    put(frame, 8, g);
    put(frame, 12, b);
    put(frame, 16, alpha);
    put(frame, 20, r);
    put(frame, 24, g);
    put(frame, 28, b);
    put(frame, 32, alpha);
}
void animate(void* self) {
    uint16_t status;
    __asm__ volatile("flds %2\n\tfadds 0xa8(%1)\n\tfsts 0xa8(%1)\n\tfcomps 0xac(%1)\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "r"(self), "m"(dat_00719a54)
                     : "st", "memory", "cc");
    if ((status & 0x4100) == 0) {
        const uint8_t current = byte(self, 0xb2), first = byte(self, 0xb0);
        if (current == first)
            put_byte(self, 0xb2, byte(self, 0xb1));
        else if (current == byte(self, 0xb1))
            put_byte(self, 0xb2, first);
        __asm__ volatile("flds 0xa8(%0)\n\tfsubs 0xac(%0)\n\tfstps 0xa8(%0)" ::"r"(self)
                         : "st", "memory");
    }
}
u32 draw(void* self, u32 resource, u32 alpha, u32 uv_start) {
    const u32 color = (channel(alpha) << 24) | 0xffffffu;
    const u32 v1 = word(self, uv_start + 0x3c), v0 = word(self, uv_start + 0x28),
              u1 = word(self, uv_start + 0x14), u0 = word(self, uv_start);
    const u32 height = word(self, 0x24), width = word(self, 0x20), y = word(self, 0x1c),
              x = word(self, 0x18);
    return recovered_00549ba0(reinterpret_cast<void*>(resource + 4), color, x, y, width, height, u0,
                              u1, v0, v1, color);
}
u32 length(const unsigned char* text) {
    u32 count = 0;
    while (byte(text, count) != 0)
        ++count;
    return count;
}
} // namespace
extern "C" u32 recovered_005277a0(void* self, u32* frame) {
    const uint8_t flag = byte(self, 4);
    put(frame, 0, word(self, 0x98));
    if (flag == 0)
        multiply_alpha(self, frame);
    const u32 alpha = word(frame, 0);
    u32 resource;
    if (byte(self, 0xd) == 0) {
        if (byte(self, 0xa3) == 1)
            resource = word(self, 0xbc);
        else if (byte(self, 6) != 0 && byte(self, 0xc) != 0)
            resource = word(self, 0xc0);
        else
            resource = word(self, 0xb8);
        if (resource != 0) {
            const u32 packed = (channel(alpha) << 24) | 0xffffffu;
            const u32 height = word(self, 0x24), width = word(self, 0x20), y = word(self, 0x1c),
                      x = word(self, 0x18);
            (void)recovered_00549ba0(reinterpret_cast<void*>(resource + 4), packed, x, y, width,
                                     height, 0, 0x3f800000u, 0, 0x3f800000u, packed);
        }
    } else {
        const u32 mode = word(self, 8);
        u32 uv = 0;
        if ((mode == 1 || mode == 4) && flag == 0) {
            resource = word(self, 0xb4);
            color_words(frame, 0x3f139394u, 0x3f119192u, 0x3f0c8c8du, alpha);
            uv = mode == 1 ? 0x58 : 0x54;
            if (resource != 0)
                (void)draw(self, resource, alpha, uv);
        } else if (byte(self, 0xa4) != 0) {
            animate(self);
            resource = word(self, 0xb4);
            color_words(frame, 0x3f57d7d8u, 0x3f57d7d8u, 0x3f4dcdceu, alpha);
            if (resource != 0) {
                const u32 packed = (channel(alpha) << 24) | 0xffffffu, index = byte(self, 0xb2);
                const u32 v1 = word(self, 0x84 + index * 4), v0 = word(self, 0x70 + index * 4),
                          u1 = word(self, 0x5c + index * 4), u0 = word(self, 0x48 + index * 4);
                const u32 height = word(self, 0x24), width = word(self, 0x20), y = word(self, 0x1c),
                          x = word(self, 0x18);
                (void)recovered_00549ba0(reinterpret_cast<void*>(resource + 4), packed, x, y, width,
                                         height, u0, u1, v0, v1, packed);
            }
        } else if (byte(self, 0xa3) == 1) {
            resource = word(self, 0xb4);
            color_words(frame, 0x3f26a6a7u, 0x3f25a5a6u, 0x3f1e9e9fu, alpha);
            if (resource != 0)
                (void)draw(self, resource, alpha, 0x50);
        } else if (mode == 1 && byte(self, 5) != 0) {
            resource = word(self, 0xb4);
            color_words(frame, 0x3f7efeffu, 0x3f7efeffu, 0x3f7efeffu, alpha);
            if (resource != 0)
                (void)draw(self, resource, alpha, 0x54);
        } else if (byte(self, 6) != 0 && byte(self, 0xc) != 0) {
            resource = word(self, 0xb4);
            color_words(frame, 0x3f7dfdfeu, 0x3f6eeeefu, 0x3f27a7a8u, alpha);
            u32 incoming = alpha;
            if (resource != 0)
                incoming = draw(self, resource, alpha, 0x4c);
            (void)recovered_005276d0(self, incoming);
        } else {
            resource = word(self, 0xb4);
            color_words(frame, 0x3f57d7d8u, 0x3f57d7d8u, 0x3f4dcdceu, alpha);
            if (resource != 0)
                (void)draw(self, resource, alpha, 0x48);
        }
    }
    auto* text = static_cast<unsigned char*>(self) + 0xc4;
    const u32 first_length = length(text);
    put(frame, 4, first_length);
    if (first_length == 0)
        return 0;
    const u32 second_length = length(text);
    (void)FUN_00542f70(dat_02209408, reinterpret_cast<const char*>(text), second_length, frame + 1,
                       0);
    FUN_005bfb50(dat_02209408);
    const u32 mode = word(self, 8);
    u32 packed;
    if (mode != 1 && mode != 4) {
        packed = (channel(alpha) << 24) | 0xffffffu;
        const u32 width = word(self, 0x28), offset_y = word(self, 0x5cc), y = word(self, 0x1c),
                  x = word(self, 0x18), height = word(self, 0x2c), offset_x = word(self, 0x5c8);
        const u32 result = FUN_00543eb0(dat_02209408, x + offset_x, y + offset_y, width, height,
                                        packed, reinterpret_cast<const char*>(text));
        FUN_005bfb50(dat_02209408);
        return result;
    }
    const u32 red = channel(word(frame, 20)), green = channel(word(frame, 24)),
              blue = channel(word(frame, 28)), opacity = channel(word(frame, 32));
    packed = (((opacity << 8) | red) << 8 | green) << 8 | blue;
    const u32 width = word(self, 0x28), height = word(self, 0x2c), y = word(self, 0x1c),
              x = word(self, 0x18), offset_y = word(self, 0x5cc), offset_x = word(self, 0x5c8);
    const u32 result = FUN_00543eb0(dat_02209408, x + offset_x, y + offset_y, width, height, packed,
                                    reinterpret_cast<const char*>(text));
    FUN_005bfb50(dat_02209408);
    return result;
}
// Reserve the actual original9DWORD region at entryESP-36..-4 BEFORE pushing
// C++ arguments. On the original d==0/mode1-or4 path, four inherited float
// words are genuinely read without prior initialization; no colors are guessed.
extern "C" __attribute__((naked)) u32 __attribute__((thiscall)) FUN_005277a0(void*) {
    __asm__ volatile(
        "subl $36,%esp\n\tmovl %esp,%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005277a0\n\taddl $44,%esp\n\tretl");
}
