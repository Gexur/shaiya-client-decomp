#include "font_selector.h"
#include "font_text.h"
namespace {
uint32_t word(const void* base, uint32_t offset) {
    uint32_t value;
    const auto* at = static_cast<const unsigned char*>(base) + offset;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
} // namespace
// Actual541aa0..541b21. The original reads its first holder even when the
// final selector is not1, and reads selector only if that holder is nonnull.
// A pointer to its real arguments retains those conditional read contracts.
extern "C" uint32_t recovered_00541aa0(void* self, const uint32_t* args) {
    const uint32_t x = word(args, 0), first = word(self, 0x3a4), y = word(args, 4);
    const uint32_t offset = first != 0 && word(args, 16) == 1 ? 0x3a4 : 0x3a8;
    const uint32_t color = word(args, 8), text = word(args, 12);
    return FUN_0054be30(static_cast<unsigned char*>(self) + offset,
                        reinterpret_cast<const char*>(text), x, y, 0, 0, color);
}
extern "C" __attribute__((naked)) uint32_t __attribute__((thiscall))
FUN_00541aa0(void*, uint32_t, uint32_t, uint32_t, const char*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcall _recovered_00541aa0\n\taddl $8,%esp\n\tretl $20");
}
