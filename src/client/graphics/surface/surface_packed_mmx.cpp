#include "graphics/surface/surface_packed_mmx.h"
#include "graphics/surface/surface_packed_rows.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
uint8_t byte(u32 p) {
    uint8_t v;
    __asm__ volatile("movb (%1),%0" : "=q"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
#define MEDIA __attribute__((target("mmx"), always_inline)) inline
MEDIA void empty() {
    __asm__ volatile("emms" ::
                         : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st", "st(1)",
                           "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory");
}
MEDIA void prepare(u32 bias) {
    __asm__ volatile("movq (%0),%%mm4\n\tpxor %%mm6,%%mm6" ::"r"(bias) : "mm4", "mm6", "memory");
}
// Actual5ed0dd..5ed149: four QWORD loads, original MMX register identities,
// wrapping packed-word adds, signed shifts, saturated pack and one8-byte store.
MEDIA void chunk(u32 top, u32 bottom, u32 output, u32 zero, u32 bias) {
    __asm__ volatile(
        "movq (%0),%%mm0\n\tmovq (%1),%%mm2\n\tmovq 8(%0),%%mm4\n\tmovq 8(%1),%%mm6\n\t"
        "movq %%mm0,%%mm1\n\tmovq %%mm2,%%mm3\n\tmovq %%mm4,%%mm5\n\tmovq %%mm6,%%mm7\n\t"
        "punpcklbw (%3),%%mm0\n\tpunpckhbw (%3),%%mm1\n\tpunpcklbw (%3),%%mm2\n\tpunpckhbw (%3),%%mm3\n\t"
        "punpcklbw (%3),%%mm4\n\tpunpckhbw (%3),%%mm5\n\tpunpcklbw (%3),%%mm6\n\tpunpckhbw (%3),%%mm7\n\t"
        "paddw %%mm1,%%mm0\n\tpaddw %%mm5,%%mm4\n\tpaddw %%mm2,%%mm0\n\tpaddw %%mm6,%%mm4\n\t"
        "paddw %%mm3,%%mm0\n\tpaddw %%mm7,%%mm4\n\tpaddw (%4),%%mm0\n\tpaddw (%4),%%mm4\n\t"
        "psraw $2,%%mm0\n\tpsraw $2,%%mm4\n\tpackuswb %%mm4,%%mm0\n\tmovq %%mm0,(%2)" ::"r"(top),
        "r"(bottom), "r"(output), "r"(zero), "r"(bias)
        : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "memory");
}
} // namespace
extern "C" __attribute__((target("mmx"))) uint32_t recovered_005ed057(uint32_t args) {
    if (byte(args + 8) & 3) {
        const u32 a5 = word(args + 20), a4 = word(args + 16), a3 = word(args + 12),
                  a2 = word(args + 8), a1 = word(args + 4), a0 = word(args);
        return FUN_005ece1f(a0, a1, a2, a3, a4, a5);
    }
    const u32 height = word(args + 12), stride = word(args + 16), first = word(args + 4);
    unsigned char storage[16];
    const u32 zero = reinterpret_cast<uintptr_t>(storage), bias = zero + 8;
    put(zero, 0);
    put(zero + 4, 0);
    put(args + 12, first + height * stride);
    put(bias, 0x00020002);
    put(bias + 4, 0x00020002);
    empty();
    put(args + 8, word(args + 8) << 2);
    u32 source = word(args + 4), destination = word(args);
    prepare(bias);
    while (static_cast<int32_t>(source) < static_cast<int32_t>(word(args + 12))) {
        u32 top = source, bottom = source + word(args + 16);
        const u32 right = source + word(args + 8);
        u32 output = destination;
        while (static_cast<int32_t>(top) < static_cast<int32_t>(right)) {
            chunk(top, bottom, output, zero, bias);
            top += 16;
            bottom += 16;
            output += 8;
        }
        source += word(args + 16);
        source += word(args + 16);
        destination += word(args + 20);
    }
    empty();
    return 0;
}
extern "C" __attribute__((naked, stdcall)) uint32_t FUN_005ed057(uint32_t, uint32_t, uint32_t,
                                                                 uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005ed057\n\taddl $4,%esp\n\tretl $24");
}
