#include "font_rgb.h"
#include "font_text.h"
namespace {
using u32 = uint32_t;
u32 word(const void* base, u32 offset) {
    u32 value;
    auto* at = reinterpret_cast<const unsigned char*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
u32 low(const void* base, u32 offset) {
    u32 value;
    auto* at = reinterpret_cast<const unsigned char*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
} // namespace
extern "C" uint32_t recovered_005419e0(void* self, const uint32_t* arguments) {
    const u32 x = word(arguments, 0), selected = word(self, 0x3a4), y = word(arguments, 4);
    u32 holder = 0x3a8;
    if (selected != 0 && word(arguments, 24) == 1)
        holder = 0x3a4;
    const u32 red = low(arguments, 8), green = low(arguments, 12), blue = low(arguments, 16);
    const u32 color = (((red | 0xffffff00u) << 8) | green) << 8 | blue;
    const auto* text = reinterpret_cast<const char*>(word(arguments, 20));
    return FUN_0054be30(reinterpret_cast<void*>(reinterpret_cast<u32>(self) + holder), text, x, y,
                        0, 0, color);
}
extern "C" __attribute__((naked)) uint32_t __attribute__((thiscall))
FUN_005419e0(void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, const char*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005419e0\n\taddl $8,%esp\n\tretl $28");
}
