#include "graphics/surface/surface_block_codec_helpers.h"
#include "graphics/surface/surface_basic_readers.h"
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
void zero(u32 p) {
    __asm__ volatile("fldz\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void one(u32 p) {
    __asm__ volatile("fld1\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
u32 zero_alpha_status(u32 alpha) {
    uint16_t status;
    __asm__ volatile("flds (%1)\n\tflds %2\n\tfucompp\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "r"(alpha), "m"(dat_006bb5fc[0])
                     : "st", "st(1)", "memory");
    return status;
}
u32 one_alpha_status(u32 alpha) {
    uint16_t status;
    __asm__ volatile("fld1\n\tfcomps (%1)\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "r"(alpha)
                     : "st", "memory");
    return status;
}
u32 component_alpha_status(u32 component, u32 alpha) {
    uint16_t status;
    __asm__ volatile("flds (%1)\n\tfcomps (%2)\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "r"(component), "r"(alpha)
                     : "st", "memory");
    return status;
}
void begin_reciprocal(u32 alpha) {
    __asm__ volatile("fld1\n\tfdivs (%0)" ::"r"(alpha) : "st", "memory");
}
void scaled_component(u32 component) {
    __asm__ volatile("fld %%st(0)\n\tfmuls (%0)\n\tfstps (%0)" ::"r"(component) : "st", "memory");
}
void final_scaled_component(u32 component) {
    __asm__ volatile("fmuls (%0)\n\tfstps (%0)" ::"r"(component) : "st", "memory");
}
void final_one(u32 component) {
    __asm__ volatile("fstp %%st(0)\n\tfld1\n\tfstps (%0)" ::"r"(component) : "st", "memory");
}
void alpha_then_red(u32 alpha, u32 red, u32 output) {
    __asm__ volatile("flds (%0)\n\tfmuls (%1)\n\tfstps (%2)" ::"r"(alpha), "r"(red), "r"(output)
                     : "st", "memory");
}
void channel_then_alpha(u32 channel, u32 alpha, u32 output) {
    __asm__ volatile("flds (%0)\n\tfmuls (%1)\n\tfstps (%2)" ::"r"(channel), "r"(alpha), "r"(output)
                     : "st", "memory");
}
bool parity44(u32 status) {
    const u32 tested = (status >> 8) & 0x44u;
    return tested == 0 || tested == 0x44u;
}
bool parity05(u32 status) {
    const u32 tested = (status >> 8) & 5u;
    return tested == 0 || tested == 5u;
}
} // namespace
// Complete0064f674..0064f6c2. This uses the actual original privateDWORD,
// overwritten with red/green/blue before each FILD. The resident scale is
// loaded before integer extraction; green's memory scale is loaded late.
extern "C" void recovered_0064f674(u32 output, u32 color, u32 scratch, u32 result) {
    __asm__ volatile("flds %0" ::"m"(dat_006c4be8) : "st", "memory");
    const u32 red = (color & 65535u) >> 11;
    put(scratch, red);
    const u32 green = (color >> 5) & 63u;
    __asm__ volatile("fildl (%0)" ::"r"(scratch) : "st", "memory");
    put(scratch, green);
    const u32 blue = color & 31u;
    __asm__ volatile("fmul %%st(1),%%st(0)\n\tfstps (%1)\n\tfildl (%0)" ::"r"(scratch), "r"(output)
                     : "st", "memory");
    put(scratch, blue);
    __asm__ volatile(
        "fmuls %2\n\tfstps 4(%1)\n\tfildl (%0)\n\tfmul %%st(1),%%st(0)\n\tfstps 8(%1)\n\tfstp %%st(0)\n\tfld1\n\tfstps 12(%1)" ::
            "r"(scratch),
        "r"(output), "m"(dat_006df404)
        : "st", "memory");
    put(result + 4, blue);
    put(result + 8, green);
}

extern "C" __attribute__((naked)) void FUN_0064f674() {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl %ecx\n\tsubl $12,%esp\n\tmovl %eax,(%esp)\n\tmovl %esp,%edx\n\tpushl %edx\n\tleal -4(%ebp),%edx\n\tpushl %edx\n\tpushl %ecx\n\tpushl %eax\n\tcalll _recovered_0064f674\n\taddl $16,%esp\n\tmovl (%esp),%eax\n\tmovl 4(%esp),%ecx\n\tmovl 8(%esp),%edx\n\tandl $31,%ecx\n\tleave\n\tretl");
}
// Complete0064f6c2..0064f746. Exact16-record loop, three original status
// masks and resident reciprocal lifetime. Every alpha/component read stays
// fresh, and alpha itself is never overwritten.
extern "C" u32 recovered_0064f6c2(u32 records) {
    for (u32 remaining = 16; remaining; --remaining, records += 16) {
        if (!parity44(zero_alpha_status(records + 12))) {
            zero(records);
            zero(records + 4);
            zero(records + 8);
        } else if ((one_alpha_status(records + 12) & 0x4100u) == 0) {
            begin_reciprocal(records + 12);
            if (parity05(component_alpha_status(records, records + 12)))
                one(records);
            else
                scaled_component(records);
            if (parity05(component_alpha_status(records + 4, records + 12)))
                one(records + 4);
            else
                scaled_component(records + 4);
            if (parity05(component_alpha_status(records + 8, records + 12)))
                final_one(records + 8);
            else
                final_scaled_component(records + 8);
        }
    }
    return records;
}
extern "C" __attribute__((naked, thiscall)) u32 FUN_0064f6c2(void*) {
    __asm__ volatile(
        "pushl %ecx\n\tcalll _recovered_0064f6c2\n\taddl $4,%esp\n\tmovl %eax,%ecx\n\tmovl $0,%edx\n\txorl %eax,%eax\n\tretl");
}
// Complete0064f746..0064f776. Preserve sourcealpha-before-red, but green
// and blue component-before-freshalpha; rawalpha is read again after RGB.
extern "C" u32 recovered_0064f746(u32 source, u32 destination) {
    for (u32 remaining = 16; remaining; --remaining) {
        alpha_then_red(source + 12, source, destination);
        source += 16;
        destination += 16;
        channel_then_alpha(source - 12, source - 4, destination - 12);
        channel_then_alpha(source - 8, source - 4, destination - 8);
        put(destination - 4, word(source - 4));
    }
    return destination;
}
extern "C" __attribute__((naked)) u32 FUN_0064f746() {
    __asm__ volatile(
        "pushl %ecx\n\tpushl %eax\n\tcalll _recovered_0064f746\n\taddl $8,%esp\n\tmovl %eax,%ecx\n\tmovl $0,%edx\n\txorl %eax,%eax\n\tretl");
}
