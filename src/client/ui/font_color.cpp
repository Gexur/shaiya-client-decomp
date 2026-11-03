#include "font_color.h"
#include "font_text.h"
#include "runtime/stdio_format.h"
namespace {
uint32_t word(const void* base, uint32_t offset) {
    uint32_t value;
    auto* address = reinterpret_cast<const uint8_t*>(reinterpret_cast<uint32_t>(base) + offset);
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
uint32_t byte(const void* base, uint32_t offset) {
    uint32_t value;
    auto* address = reinterpret_cast<const uint8_t*>(reinterpret_cast<uint32_t>(base) + offset);
    __asm__ volatile("movzbl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
void store(void* base, uint32_t offset, uint32_t value) {
    auto* address = reinterpret_cast<uint8_t*>(reinterpret_cast<uint32_t>(base) + offset);
    __asm__ volatile("movl %1,(%0)" ::"r"(address), "r"(value) : "memory");
}
} // namespace
// Original00541820..005418be. The second/third color bytes are read around
// the original y load; later stores/readbacks remain in their original order.
extern "C" uint32_t recovered_00541820(uint32_t* arguments) {
    const auto* format = reinterpret_cast<const char*>(word(arguments, 28));
    char text[256];
    (void)fun_005ceb39(text, format, arguments + 8);
    const uint32_t red = byte(arguments, 12), green = byte(arguments, 16);
    const uint32_t y = word(arguments, 8);
    const uint32_t blue = byte(arguments, 20);
    const uint32_t color = ((red | 0xffffff00u) << 8 | green) << 8 | blue;
    //4187a writes E+20: the actual eighth/format argument now points to
    //the formatted private buffer, even though this pointer later expires.
    store(arguments, 28, reinterpret_cast<uint32_t>(text));
    const uint32_t x = word(arguments, 4);
    auto* holder = reinterpret_cast<void*>(word(arguments, 0) + 0x3a8);
    return FUN_0054be30(holder, text, x, y, 0, 0, color);
}
extern "C" __attribute__((naked)) uint32_t FUN_00541820(void*, uint32_t, uint32_t, uint32_t,
                                                        uint32_t, uint32_t, uint32_t, const char*,
                                                        ...) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00541820\n\taddl $4,%esp\n\tretl");
}
