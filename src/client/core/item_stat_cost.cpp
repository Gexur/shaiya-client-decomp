#include "item_stat_cost.h"
#include "graphics/render_project_unproject.h"

// Exact original read-only IEEE754 words. No adjacent storage is inferred.
extern "C" const uint32_t dat_006c2bb4 = 0x3eaaaaab;
// Canonical1.0 at006bc4dc is owned by render_project_unproject[1].

namespace {
using u32 = uint32_t;
u32 dword(const void* at) {
    u32 value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
bool store_ratio_and_test(u32 counter, u32* original_argument) {
    uint16_t status;
    __asm__ volatile(
        "fildl %1\n\tfmuls %2\n\tfstps (%3)\n\tflds (%3)\n\tfcomps _dat_006bc4dc\n\tfnstsw %%ax"
        : "=a"(status)
        : "m"(counter), "m"(dat_006c2bb4), "r"(original_argument)
        : "memory", "st");
    // Original TEST AH,41 / JNP skips the inner loop for less/equal.
    const u32 flags = (status >> 8) & 0x41;
    return flags == 0 || flags == 0x41;
}
bool below_ratio(u32 counter, const u32* original_argument) {
    uint16_t status;
    __asm__ volatile("fildl %1\n\tfcomps (%2)\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "m"(counter), "r"(original_argument)
                     : "memory", "st");
    return (status & 0x100) != 0;
}
} // namespace

extern "C" u32 recovered_004cbf50(u32* original_argument) {
    const u32 bound = dword(original_argument);
    u32 step = 1, total = 0;
    if (static_cast<int32_t>(bound) < 1)
        return 0;
    do {
        u32 level = 1;
        if (store_ratio_and_test(step, original_argument)) {
            do {
                ++level;
                if (level >= 50)
                    break;
            } while (below_ratio(level, original_argument));
        }
        ++step;
        total += level * 3 + 4;
    } while (static_cast<int32_t>(step) <= static_cast<int32_t>(bound));
    return total;
}
extern "C" __attribute__((naked, stdcall)) u32 FUN_004cbf50(u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_004cbf50\n\taddl $4,%esp\n\tretl $4");
}
