#include "font_text.h"
#include "core/wide_copy.h"
#include "runtime/stdio_format.h"
#include "startup/client_locale.h"
#include "graphics/native_font.h"

extern "C" {
uint16_t dat_02208400[1024] = {}, dat_02208c00[1024] = {};
using Convert = int32_t(__attribute__((stdcall)) *)(uint32_t, uint32_t, const char*, int32_t,
                                                    uint16_t*, int32_t);
extern Convert imported_font_multibyte __asm__("__imp__MultiByteToWideChar@24");
}
namespace {
using u32 = uint32_t;
using s32 = int32_t;
u32 word(const void* base, u32 offset) {
    u32 value;
    const auto* p = reinterpret_cast<const uint8_t*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
uint16_t half(const void* base, u32 offset) {
    uint16_t value;
    const auto* p = reinterpret_cast<const uint8_t*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movw (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
void put_word(void* base, u32 offset, u32 value) {
    auto* p = reinterpret_cast<uint8_t*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(value) : "memory");
}
void put_half(void* base, u32 offset, uint16_t value) {
    auto* p = reinterpret_cast<uint8_t*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movw %1,(%0)" ::"r"(p), "r"(value) : "memory");
}
void clear(uint16_t* target) {
    u32 count = 512;
    __asm__ volatile("rep stosl" : "+D"(target), "+c"(count) : "a"(0) : "memory", "cc");
}
Convert conversion() {
    u32 value;
    __asm__ volatile("movl %1,%0" : "=r"(value) : "m"(imported_font_multibyte) : "memory");
    return reinterpret_cast<Convert>(value);
}
} // namespace

// Actual541cb0 clears/copies exactly the observed2048-byte shared prefix,
// selects a real font receiver and reads back RECT.right/RECT.bottom.
extern "C" u32 __attribute__((thiscall)) FUN_00541cb0(void* self, const uint16_t* input, u32 count,
                                                      u32* output, u32 kind) {
    clear(dat_02208400);
    (void)copy_utf16_string_forward(dat_02208400, input);
    put_half(dat_02208400, count * 2, 0);
    const u32 first = word(self, 0x3a4);
    u32 font;
    if (first != 0 && kind == 1)
        font = word(self, 0x3a4);
    else {
        const u32 second = word(self, 0x3a0);
        if (second != 0 && kind == 2)
            font = second;
        else {
            const u32 third = word(self, 0x39c);
            font = third != 0 && kind == 3 ? third : word(self, 0x3a8);
        }
    }
    const SIZE extent = shaiya::graphics::native::measure_text(
        reinterpret_cast<shaiya::graphics::native::NativeFont*>(font),
        reinterpret_cast<const WCHAR*>(dat_02208400));
    put_word(output, 0, u32(extent.cx));
    put_word(output, 4, u32(extent.cy));
    return reinterpret_cast<u32>(output);
}

extern "C" u32 recovered_00542f70(void* self, u32* arguments) {
    const u32 locale = word(&dat_00708598, 0);
    if (locale < 3 || locale > 17) {
        const u32 count = word(arguments, 4);
        auto* output = reinterpret_cast<u32*>(word(arguments, 8));
        put_word(output, 0, count * 6);
        put_word(output, 4, 12);
        return reinterpret_cast<u32>(output);
    }
    const u32 codepage = fun_0040a550();
    const u32 count = word(arguments, 4);
    const auto* text = reinterpret_cast<const char*>(word(arguments, 0));
    const u32 converted =
        static_cast<u32>(conversion()(codepage, 0, text, static_cast<s32>(count), nullptr, 0));
    clear(dat_02208c00);
    const auto* second_text = reinterpret_cast<const char*>(word(arguments, 0));
    (void)conversion()(codepage, 0, second_text, static_cast<s32>(count), dat_02208c00,
                       static_cast<s32>(converted));
    const u32 kind = word(arguments, 12);
    auto* output = reinterpret_cast<u32*>(word(arguments, 8));
    (void)FUN_00541cb0(self, dat_02208c00, converted, output, kind);
    u32 index = converted - 1, spaces = 0;
    while (static_cast<s32>(index) >= 0 && half(dat_02208c00, index * 2) == 0x20) {
        ++spaces;
        --index;
    }
    const u32 enabled = word(self, 0x3a4);
    if (enabled != 0 && kind == 1) {
        const u32 padding = word(self, 0x3b4);
        const u32 original = word(output, 0);
        const u32 result = original + padding * spaces;
        put_word(output, 0, result);
        return result;
    }
    const u32 amount = word(self, 0x3b0) * spaces;
    const u32 original = word(output, 0);
    put_word(output, 0, original + amount);
    return amount;
}
extern "C" __attribute__((naked)) u32 __attribute__((thiscall)) FUN_00542f70(void*, const char*,
                                                                             u32, u32*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_00542f70\n\taddl $8,%esp\n\tretl $16");
}
extern "C" u32 __attribute__((thiscall)) FUN_005430a0(void* self, const char* text, u32 count,
                                                      u32 kind) {
    u32 output[2];
    (void)FUN_00542f70(self, text, count, output, kind);
    return word(output, 0);
}

// Raw-argument normalized helpers preserve the original timing/backing of
// variadic reads and the rectangle passed by value in incoming stack slots.
extern "C" u32 recovered_0054be30(u32* arguments) {
    const u32 color = word(arguments, 24);
    auto* holder = reinterpret_cast<void*>(word(arguments, 0));
    auto* font = reinterpret_cast<shaiya::graphics::native::NativeFont*>(word(holder, 0));
    const auto* text = reinterpret_cast<const char*>(word(arguments, 4));
    auto* current = shaiya::graphics::native::renderer();
    return u32(shaiya::graphics::native::draw_text_ansi(
        *current, font, text, -1, *reinterpret_cast<RECT*>(arguments + 2), DT_NOCLIP, color));
}
extern "C" u32 recovered_005418c0(u32* arguments) {
    const auto* format = reinterpret_cast<const char*>(word(arguments, 20));
    char buffer[256];
    (void)fun_005ceb39(buffer, format, arguments + 6);
    const u32 color = word(arguments, 12), x = word(arguments, 4), y = word(arguments, 8);
    auto* holder = reinterpret_cast<void*>(word(arguments, 0) + 0x3a8);
    return FUN_0054be30(holder, buffer, x, y, 0, 0, color);
}
extern "C" __attribute__((naked)) u32 FUN_0054be30(void*, const char*, u32, u32, u32, u32, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0054be30\n\taddl $4,%esp\n\tretl");
}
extern "C" __attribute__((naked)) u32 FUN_005418c0(void*, u32, u32, u32, u32, const char*, ...) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005418c0\n\taddl $4,%esp\n\tretl");
}
