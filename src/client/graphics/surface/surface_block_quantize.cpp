#include "graphics/surface/surface_block_quantize.h"
#include "graphics/render_project_unproject.h"
#include "graphics/render_packed_trig_quaternions.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void begin_zero() {
    __asm__ volatile("flds %0" ::"m"(dat_006bb5fc[0]) : "st", "memory");
}
u32 lower_status(u32 p, bool final) {
    uint16_t status;
    if (final)
        __asm__ volatile("fcomps (%1)\n\tfnstsw %%ax" : "=a"(status) : "r"(p) : "st", "memory");
    else
        __asm__ volatile("fcoms (%1)\n\tfnstsw %%ax" : "=a"(status) : "r"(p) : "memory");
    return status;
}
u32 upper_status(u32 p) {
    uint16_t status;
    __asm__ volatile("flds (%1)\n\tfcomps %2\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "r"(p), "m"(dat_006bc4dc[0])
                     : "st", "memory");
    return status;
}
void zero(u32 p) {
    __asm__ volatile("fldz\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void one(u32 p) {
    __asm__ volatile("fld1\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void load(u32 p) {
    __asm__ volatile("flds (%0)" ::"r"(p) : "st", "memory");
}
void multiply31() {
    __asm__ volatile("fmuls %0" ::"m"(dat_006c651c) : "st", "memory");
}
void multiply63() {
    __asm__ volatile("fmuls %0" ::"m"(dat_006df408) : "st", "memory");
}
void round_store(u32 temporary, u32 integer) {
    __asm__ volatile("fadds %2\n\tfstps (%0)\n\tflds (%0)\n\tfistpl (%1)" ::"r"(temporary),
                     "r"(integer), "m"(dat_006bc860[0])
                     : "st", "memory");
}
} // namespace
// Complete0064f776..0064f879. Literal resident-zero comparisons and raw
// copies preserve unordered cases. The actual original28B private span
// remains reserved before C++ pushes. FNSTCW only writes its real lowWORD;
// the highWORD read atframe24 is actual inherited input, never zero-filled.
extern "C" u32 recovered_0064f776(u32 color, u32 frame, u32 result) {
    begin_zero();
    for (u32 i = 0; i < 3; ++i) {
        const u32 p = color + 4 * i;
        if ((lower_status(p, i == 2) & 0x4100u) == 0)
            zero(frame + 4 * i);
        else if ((upper_status(p) & 0x4100u) == 0)
            one(frame + 4 * i);
        else
            put(frame + 4 * i, word(p));
    }
    __asm__ volatile("fnstcw (%0)" ::"r"(frame + 24) : "memory");
    put(frame + 20, word(frame + 24) | 0x0c00u);
    __asm__ volatile("fldcw (%0)" ::"r"(frame + 20) : "memory");
    load(frame);
    multiply31();
    put(frame + 16, word(frame + 24));
    round_store(frame + 20, frame + 24);
    load(frame + 4);
    const u32 red = word(frame + 24);
    multiply63();
    round_store(frame + 20, frame + 24);
    load(frame + 8);
    const u32 green = word(frame + 24);
    multiply31();
    round_store(frame + 20, frame + 24);
    const u32 blue = word(frame + 24);
    __asm__ volatile("fldcw (%0)" ::"r"(frame + 16) : "memory");
    put(result, green);
    put(result + 4, blue);
    return (((red << 6) | green) << 5) | blue;
}
extern "C" __attribute__((naked, thiscall)) u32 FUN_0064f776(const void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $28,%esp\n\tsubl $8,%esp\n\tmovl %esp,%eax\n\tpushl %eax\n\tleal -28(%ebp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_0064f776\n\taddl $12,%esp\n\tmovl (%esp),%ecx\n\tmovl 4(%esp),%edx\n\torl $0,%eax\n\tleave\n\tretl");
}
extern "C" {
extern const uint32_t dat_006c651c = 0x41f80000u;
extern const uint32_t dat_006df408 = 0x427c0000u;
}
