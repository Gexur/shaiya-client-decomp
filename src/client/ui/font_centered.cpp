#include "font_centered.h"
#include "font_text.h"
#include "core/x87_runtime.h"
#include "runtime/stdio_format.h"
namespace {
using u32 = uint32_t;
u32 word(const void* base, u32 offset) {
    u32 value;
    const auto* address = reinterpret_cast<const uint8_t*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
u32 byte(const void* base, u32 offset) {
    u32 value;
    const auto* address = reinterpret_cast<const uint8_t*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
void store(void* base, u32 offset, u32 value) {
    auto* address = reinterpret_cast<uint8_t*>(reinterpret_cast<u32>(base) + offset);
    __asm__ volatile("movl %1,(%0)" ::"r"(address), "r"(value) : "memory");
}
long double half_difference(u32 extent, u32 measured) {
    long double result;
    static const float zero = 0.0f, half = 0.5f;
    if (extent == 0xffffffffu)
        __asm__ volatile("flds %1\n\tfstpt %0" : "=m"(result) : "m"(zero) : "st", "memory");
    else {
        const u32 difference = extent - measured;
        __asm__ volatile("fildl %1\n\tfmuls %2\n\tfstpt %0"
                         : "=m"(result)
                         : "m"(difference), "m"(half)
                         : "st", "memory");
    }
    return result;
}
} // namespace
// Original543eb0..543fbb. Preserve the original format-word write and
// delayed argument loads, rather than passing a guessed fixed signature.
extern "C" u32 recovered_00543eb0(u32* arguments) {
    const u32 enabled = word(&dat_0070b8f0, 0);
    if (enabled == 0)
        return enabled;
    const auto* format = reinterpret_cast<const char*>(word(arguments, 24));
    char text[256];
    (void)fun_005ceb39(text, format, arguments + 7);
    store(arguments, 24, reinterpret_cast<u32>(text));
    u32 count = 0;
    while (byte(text, count) != 0)
        ++count;
    auto* self = reinterpret_cast<void*>(word(arguments, 0));
    u32 measured[2];
    (void)FUN_00542f70(self, text, count, measured, 0);
    const u32 width = word(arguments, 12);
    const u32 horizontal = static_cast<u32>(x87_to_integer_005cd414(
        half_difference(width, width == 0xffffffffu ? 0 : word(measured, 0))));
    const u32 height = word(arguments, 16);
    const long double vertical_value =
        half_difference(height, height == 0xffffffffu ? 0 : word(measured, 4));
    const u32 x = word(arguments, 4) + horizontal;
    const u32 vertical = static_cast<u32>(x87_to_integer_005cd414(vertical_value));
    const u32 color = word(arguments, 20), y = word(arguments, 8) + vertical;
    const auto* current_text = reinterpret_cast<const char*>(word(arguments, 24));
    return FUN_0054be30(reinterpret_cast<void*>(reinterpret_cast<u32>(self) + 0x3a8), current_text,
                        x, y, 0, 0, color);
}
extern "C" __attribute__((naked)) u32 FUN_00543eb0(void*, u32, u32, u32, u32, u32, const char*,
                                                   ...) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00543eb0\n\taddl $4,%esp\n\tretl");
}
