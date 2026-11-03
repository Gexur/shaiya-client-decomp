#include "graphics/surface/surface_color_match.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
uint16_t compare(u32 color, u32 pixel) {
    uint16_t status;
    __asm__ volatile("flds (%1)\n\tflds (%2)\n\tfucompp\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "r"(color), "r"(pixel)
                     : "st", "st(1)", "memory");
    return status;
}
void zero(u32 p) {
    __asm__ volatile("fldz\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
} // namespace
// Complete5f225c..5f22d6. Each FNSTSW changes only EAX's low16bits; the
// surviving high16bits come from the actual rounded-up loop count.
extern "C" u32 recovered_005f225c(u32 self, u32 argument) {
    const u32 width = word(self + 0x68), buffer = word(argument);
    const u32 end = buffer + (width << 4);
    u32 result = end;
    if (buffer < end) {
        u32 count = ((end - buffer - 1) >> 4) + 1, pixel = buffer + 8;
        result = count;
        do {
            bool equal = true;
            for (u32 channel = 0; channel != 4; ++channel) {
                const uint16_t status = compare(self + 0x24 + channel * 4, pixel - 8 + channel * 4);
                result = (result & 0xffff0000u) | status;
                const u32 masked = status & 0x4400u;
                if (masked == 0 || masked == 0x4400u) {
                    equal = false;
                    break;
                }
            }
            if (equal) {
                zero(pixel + 4);
                zero(pixel);
                zero(pixel - 4);
                zero(pixel - 8);
            }
            pixel += 16;
        } while (--count);
    }
    return result;
}
// Original ECX is preserved and read by genuine row callers after this call.
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f225c(void*, void*) {
    __asm__ volatile(
        "pushl %ecx\n\tleal 8(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f225c\n\taddl $8,%esp\n\tpopl %ecx\n\tretl $4");
}
