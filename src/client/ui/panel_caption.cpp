#include "panel_caption.h"
#include "panel_frame.h"
#include "font_text.h"
#include "font_color.h"
extern "C" {
extern uint32_t dat_0071c2a4, dat_0071c2a8;
extern unsigned char dat_02209408[];
}
namespace {
using u32 = uint32_t;
u32 word(const void* at) {
    u32 value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
uint8_t byte(const void* at) {
    uint8_t value;
    __asm__ volatile("movb (%1),%0" : "=q"(value) : "r"(at) : "memory");
    return value;
}
} // namespace
extern "C" u32 recovered_005276d0(void* self, u32 incoming) {
    auto* object = static_cast<unsigned char*>(self);
    const uint8_t enabled = byte(object + 0x4c4);
    if (enabled == 0)
        return incoming & 0xffffff00u;
    auto* text = reinterpret_cast<const char*>(object + 0x4c5);
    u32 count = 0;
    while (byte(text + count) != 0)
        ++count;
    const u32 width = FUN_005430a0(dat_02209408, text, count, 0);
    u32 x = word(&dat_0071c2a4) - width;
    if (static_cast<int32_t>(x) < 0)
        x = 0;
    const u32 frame_y = word(&dat_0071c2a8) - 18;
    (void)FUN_0050ff10(x, frame_y, width + 3, 13, 0xcd1d1f24u, 0);
    const u32 text_y = word(&dat_0071c2a8) - 11;
    return FUN_00541820(dat_02209408, x + 5, text_y, 255, 255, 255, 0, text);
}
extern "C" __attribute__((naked)) u32 __attribute__((thiscall)) FUN_005276d0(void*) {
    __asm__ volatile(
        "pushl %eax\n\tpushl %ecx\n\tcalll _recovered_005276d0\n\taddl $8,%esp\n\tretl");
}
