#include "font_clipped.h"
#include "font_text.h"
#include "core/character_span.h"
namespace {
using u32 = uint32_t;
u32 word(const void* base, u32 offset) {
    u32 value;
    const auto* at = reinterpret_cast<const unsigned char*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
u32 byte(const void* base, u32 offset) {
    u32 value;
    const auto* at = reinterpret_cast<const unsigned char*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
void put_byte(void* base, u32 offset, u32 value) {
    auto* at = reinterpret_cast<unsigned char*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movb %b1,(%0)" ::"r"(at), "q"(value) : "memory");
}
void clear_copy(unsigned char* target) {
    u32 count = 256;
    __asm__ volatile("rep stosl" : "+D"(target), "+c"(count) : "a"(0) : "memory", "cc");
}
} // namespace
extern "C" u32 recovered_00543d30(void* self, u32* arguments) {
    auto* text = reinterpret_cast<char*>(word(arguments, 28));
    unsigned char copy[1024];
    clear_copy(copy);
    u32 copied = 0, value;
    do {
        value = byte(text, copied);
        put_byte(copy, copied, value);
        ++copied;
    } while (value != 0);
    value = byte(copy, 0);
    const u32 x = word(arguments, 0), y = word(arguments, 4);
    u32 position = 0;
    if (value != 0) {
        for (;;) {
            const u32 character = byte(copy, position), previous = position;
            u32 count, measured[2];
            (void)get_encoded_character_length(character, &count);
            const u32 kind = word(arguments, 20);
            position += count;
            (void)FUN_00542f70(self, reinterpret_cast<const char*>(copy), position, measured, kind);
            const u32 limit = word(arguments, 24);
            if (static_cast<int32_t>(measured[0]) > static_cast<int32_t>(limit)) {
                auto* current = reinterpret_cast<char*>(word(arguments, 28));
                put_byte(current, previous, 0);
                break;
            }
            if (byte(copy, position) == 0)
                break;
        }
        //543dd4 reloads the original eighth argument on both nonempty exits.
        text = reinterpret_cast<char*>(word(arguments, 28));
    }
    const u32 first = word(self, 0x3a4), kind = word(arguments, 20);
    u32 holder;
    if (first != 0 && kind == 1)
        holder = reinterpret_cast<u32>(self) + 0x3a4;
    else if (word(self, 0x3a0) != 0 && kind == 2)
        holder = reinterpret_cast<u32>(self) + 0x3a0;
    else if (word(self, 0x39c) != 0 && kind == 3)
        holder = reinterpret_cast<u32>(self) + 0x39c;
    else
        holder = reinterpret_cast<u32>(self) + 0x3a8;
    const u32 red = byte(arguments, 8), green = byte(arguments, 12), blue = byte(arguments, 16);
    const u32 color = (((red | 0xffffff00u) << 8 | green) << 8) | blue;
    return FUN_0054be30(reinterpret_cast<void*>(holder), text, x, y, 0, 0, color);
}
extern "C" __attribute__((naked)) u32 __attribute__((thiscall))
FUN_00543d30(void*, u32, u32, u32, u32, u32, u32, int32_t, char*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_00543d30\n\taddl $8,%esp\n\tretl $32");
}
