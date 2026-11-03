#include "frame_corner.h"
#include "startup/global_ownership.h"
extern "C" uint32_t recovered_00549ba0(void*, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t,
                                       uint32_t, uint32_t, uint32_t, uint32_t, uint32_t);
namespace {
uint32_t word(const void* base, uint32_t offset) {
    uint32_t value;
    const auto* at =
        reinterpret_cast<const unsigned char*>(reinterpret_cast<uint32_t>(base) + offset);
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(at) : "memory");
    return value;
}
} // namespace
extern "C" uint32_t recovered_005101f0(const uint32_t* arguments) {
    const uint32_t kind = word(arguments, 0);
    const uint32_t y = word(arguments, 8), x = word(arguments, 4);
    if (kind != 0)
        return recovered_00549ba0(&dat_022032fc, 0xffffffffu, x, y, 4, 4, 0, 0x3e800000u,
                                  0x3f000000u, 0x3f400000u, y);
    return recovered_00549ba0(&dat_022032fc, 0xffffffffu, x, y, 4, 4, 0x3e800000u, 0x3f000000u,
                              0x3f000000u, 0x3f400000u, x);
}
extern "C" __attribute__((naked)) uint32_t FUN_005101f0(uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005101f0\n\taddl $4,%esp\n\tretl");
}
