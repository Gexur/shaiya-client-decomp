#include "font_gated.h"
#include "font_gate_storage.h"
#include "font_color.h"
// Original00541930..005419de: its gate precedes every input argument read.
// The post-gate instruction sequence duplicates00541820's formatter/channel
// loads, original format-word overwrite, and actual0054be30 call. Factor
// that already recovered body; private numerical frame addresses differ.
extern "C" uint32_t recovered_00541930(uint32_t* arguments) {
    uint32_t enabled;
    __asm__ volatile("movl (%1),%0" : "=r"(enabled) : "r"(&dat_0070b8f0) : "memory");
    if (enabled == 0)
        return enabled;
    return recovered_00541820(arguments);
}
extern "C" __attribute__((naked)) uint32_t FUN_00541930(void*, uint32_t, uint32_t, uint32_t,
                                                        uint32_t, uint32_t, uint32_t, const char*,
                                                        ...) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00541930\n\taddl $4,%esp\n\tretl");
}
