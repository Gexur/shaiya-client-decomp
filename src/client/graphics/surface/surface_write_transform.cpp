#include "graphics/surface/surface_write_transform.h"
#include "graphics/render_project_unproject.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void load(u32 p) {
    __asm__ volatile("flds (%0)" ::"r"(p) : "st", "memory");
}
void store(u32 p) {
    __asm__ volatile("fstps (%0)" ::"r"(p) : "st", "memory");
}
void pop() {
    __asm__ volatile("fstp %%st(0)" ::: "st");
}
void signed_bounds() {
    __asm__ volatile("flds %0\n\tflds %1" ::"m"(dat_006bb5f8), "m"(dat_006bc4dc)
                     : "st", "st(1)", "memory");
}
void unsigned_bound() {
    __asm__ volatile("flds %0" ::"m"(dat_006bc4dc) : "st", "memory");
}
void scale_bounds(bool half) {
    if (half)
        __asm__ volatile("flds %0\n\tflds %1" ::"m"(dat_006bc4dc), "m"(dat_006bc860)
                         : "st", "st(1)", "memory");
    else
        __asm__ volatile("flds %0\n\tflds %1" ::"m"(dat_006bc4dc), "m"(dat_006bc9d4)
                         : "st", "st(1)", "memory");
}
void clamp(u32 p, bool signed_lower) {
    uint16_t status;
    if (signed_lower)
        __asm__ volatile("fld %%st(1)\n\tfcomps (%1)\n\tfnstsw %0"
                         : "=a"(status)
                         : "r"(p)
                         : "st", "memory");
    else
        __asm__ volatile("fldz\n\tfcomps (%1)\n\tfnstsw %0"
                         : "=a"(status)
                         : "r"(p)
                         : "st", "memory");
    if (!(status & 0x4100u)) {
        if (signed_lower)
            __asm__ volatile("fld %%st(1)" ::: "st");
        else
            __asm__ volatile("fldz" ::: "st");
    } else {
        __asm__ volatile("fcoms (%1)\n\tfnstsw %0" : "=a"(status) : "r"(p) : "st", "memory");
        if (!(status & 0x4100u))
            load(p);
        else
            __asm__ volatile("fld1" ::: "st");
    }
}
void scale(bool half) {
    if (half)
        __asm__ volatile("fadd %%st(2),%%st\n\tfmul %%st(1),%%st" ::: "st");
    else
        __asm__ volatile("fmul %%st(1),%%st\n\tfsub %%st(2),%%st" ::: "st");
}
void alpha_scale(bool half) {
    if (half)
        __asm__ volatile("fadds %0\n\tfmuls %1" ::"m"(dat_006bc4dc), "m"(dat_006bc860)
                         : "st", "memory");
    else
        __asm__ volatile("fadd %%st,%%st\n\tfsubs %0" ::"m"(dat_006bc4dc) : "st", "memory");
}
} // namespace
// Complete original005f0da1..005f12b9. Literal branch modes and x87
// operations follow the original, including unordered comparisons.
extern "C" uint32_t recovered_005f0da1(uint32_t self, uint32_t argument) {
    const u32 kind = word(self + 8);
    if (kind != 1 && kind != 2 && kind != 3)
        return word(self + 0x58);
    const u32 format = word(self + 0x54);
    const bool clamped = format == 4;
    const bool all_scaled = (kind == 3 && format == 1) || (kind == 1 && format == 3);
    const bool rgb_scaled = (kind == 2 && format == 1) || (kind == 1 && format == 2);
    const bool alpha_scaled = (kind == 3 && format == 2) || (kind == 2 && format == 3);
    if (!clamped && !all_scaled && !rgb_scaled && !alpha_scaled)
        return word(self + 0x58);
    if (word(self + 0x68) == 0)
        return word(self + 0x58);
    const u32 base = word(argument);
    u32 p = base + 8, count = 0, offset = 0;
    if (clamped) {
        if (kind == 1)
            unsigned_bound();
        else
            signed_bounds();
        const u32 relative = 0xfffffff8u - base;
        do {
            clamp(p - 8, kind != 1);
            u32 output = word(self + 0x58);
            offset = relative + p;
            store(output + offset);
            clamp(p - 4, kind != 1);
            output = word(self + 0x58);
            store(output + offset + 4);
            clamp(p, kind != 1);
            output = word(self + 0x58);
            store(output + offset + 8);
            clamp(p + 4, kind == 3);
            output = word(self + 0x58);
            ++count;
            store(output + offset + 12);
            p += 16;
        } while (count < word(self + 0x68));
        if (kind != 1)
            pop();
        pop();
    } else if (all_scaled || rgb_scaled) {
        const bool half = kind == 1;
        scale_bounds(half);
        do {
            load(p - 8);
            u32 output = word(self + 0x58);
            scale(half);
            ++count;
            store(output + offset);
            output = word(self + 0x58);
            load(p - 4);
            offset += 16;
            scale(half);
            store(output + offset - 12);
            output = word(self + 0x58);
            load(p);
            p += 16;
            scale(half);
            store(output + offset - 8);
            output = word(self + 0x58);
            load(p - 12);
            if (all_scaled)
                scale(half);
            store(output + offset - 4);
        } while (count < word(self + 0x68));
        pop();
        pop();
    } else {
        do {
            u32 output = word(self + 0x58);
            load(p - 8);
            store(output + offset);
            output = word(self + 0x58);
            load(p - 4);
            ++count;
            store(output + offset + 4);
            output = word(self + 0x58);
            load(p);
            offset += 16;
            store(output + offset - 8);
            output = word(self + 0x58);
            load(p + 4);
            p += 16;
            alpha_scale(kind == 2);
            store(output + offset - 4);
        } while (count < word(self + 0x68));
    }
    return word(self + 0x58);
}
extern "C" __attribute__((naked, thiscall)) uint32_t FUN_005f0da1(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005f0da1\n\taddl $8,%esp\n\tretl $4");
}
extern "C" {
extern const uint32_t dat_006bb5f8 = 0xbf800000u;
}
