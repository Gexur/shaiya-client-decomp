#include "graphics/render_texture_create.h"
namespace {
using u32 = uint32_t;
u32 word(const void* p) {
    u32 value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(p) : "memory");
    return value;
}
} // namespace
// Original5e2298..5e22bf is only a forwarding ABI bridge: EDX carries device,
// eight words carry the exact dimension/mips/format pointers and type3.
// The stack addresses/order stay original; no incompatible C++ call is used.
extern "C" __attribute__((naked, stdcall)) int32_t FUN_005e2298(void*, uint32_t*, uint32_t*,
                                                                uint32_t*, uint32_t, int32_t*,
                                                                uint32_t) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tmovl 8(%ebp),%edx\n\tpushl $3\n\tpushl 32(%ebp)\n\tpushl 28(%ebp)\n\tpushl 24(%ebp)\n\tpushl 20(%ebp)\n\tpushl $0\n\tpushl 16(%ebp)\n\tpushl 12(%ebp)\n\tcalll _normalize_texture_requirements@32\n\tpopl %ebp\n\tretl $28");
}
// Complete original5e22bf..5e232f control; checker receives addresses of the
// actual incoming width/height/mips/format words, not synthetic local copies.
extern "C" int32_t recovered_005e22bf(uint32_t* args) {
    const u32 device = word(args);
    if (!device || !word(args + 7))
        return static_cast<int32_t>(0x8876086c);
    u32 usage = word(args + 4);
    if (usage == 0xffffffff)
        usage = 0;
    const u32 pool = word(args + 6);
    const int32_t checked =
        FUN_005e2298(reinterpret_cast<void*>(device), args + 1, args + 2, args + 3, usage,
                     reinterpret_cast<int32_t*>(args + 5), pool);
    if (checked < 0)
        return checked;
    const u32 table = word(reinterpret_cast<void*>(device));
    const u32 output = word(args + 7), current_pool = word(args + 6), format = word(args + 5);
    usage &= 0xffe07fff;
    const u32 levels = word(args + 3), height = word(args + 2), width = word(args + 1);
    using Create =
        int32_t(__attribute__((stdcall))*)(void*, u32, u32, u32, u32, u32, u32, void**, void*);
    const auto create =
        reinterpret_cast<Create>(word(reinterpret_cast<const unsigned char*>(table) + 0x5c));
    const int32_t result = create(reinterpret_cast<void*>(device), width, height, levels, usage,
                                  format, current_pool, reinterpret_cast<void**>(output), nullptr);
    return result < 0 ? result : 0;
}
extern "C" __attribute__((naked, stdcall)) int32_t FUN_005e22bf(void*, uint32_t, uint32_t, uint32_t,
                                                                uint32_t, uint32_t, uint32_t,
                                                                void**) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e22bf\n\taddl $4,%esp\n\tretl $32");
}
