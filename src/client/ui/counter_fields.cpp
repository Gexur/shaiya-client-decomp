#include "counter_fields.h"
#include "ordered_stores.h"
using namespace shaiya::ui::ordered_detail;
extern "C" uint32_t __attribute__((thiscall)) FUN_00531b30(void* self) {
    uint16_t value;
    auto* at = static_cast<unsigned char*>(self) + 0x3618;
    __asm__ volatile("movw (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return static_cast<uint32_t>(value) & 0x3ffu;
}
extern "C" uint32_t recovered_00532400(void* self, const uint32_t* args) {
    const uint32_t first = load32(args, 0), third = load32(args, 8);
    store32(self, 0x24, first);
    const uint32_t second = load32(args, 4);
    store32(self, 0x3608, third);
    const uint32_t fourth = load32(args, 12);
    store32(self, 4, second);
    store32(self, 8, fourth);
    store8(self, 0xd0, 0);
    // Original53240b leaves its second stack word in fullEAX throughRET16.
    return second;
}
extern "C" __attribute__((naked)) uint32_t __attribute__((thiscall))
FUN_00532400(void*, uint32_t, uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcall _recovered_00532400\n\taddl $8,%esp\n\tretl $16");
}
