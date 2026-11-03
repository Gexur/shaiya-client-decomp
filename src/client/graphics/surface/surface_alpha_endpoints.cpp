#include "graphics/surface/surface_alpha_endpoints.h"
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
void clear_rmw(u32 p) {
    __asm__ volatile("andl $0,(%0)" ::"r"(p) : "memory", "cc");
}
void zero(u32 p) {
    __asm__ volatile("fldz\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void one(u32 p) {
    __asm__ volatile("fld1\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void pop() {
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
}
bool even05(u32 s) {
    s = (s >> 8) & 5u;
    return s == 0 || s == 5;
}
bool even41(u32 s) {
    s = (s >> 8) & 0x41u;
    return s == 0 || s == 0x41;
}
bool even44(u32 s) {
    s = (s >> 8) & 0x44u;
    return s == 0 || s == 0x44;
}
u32 compare(u32 a, u32 b) {
    uint16_t s;
    __asm__ volatile("flds (%1)\n\tfcomps (%2)\n\tfnstsw %%ax"
                     : "=a"(s)
                     : "r"(a), "r"(b)
                     : "st", "memory");
    return s;
}
u32 compare_live(u32 b) {
    uint16_t s;
    __asm__ volatile("fcoms (%1)\n\tfnstsw %%ax" : "=a"(s) : "r"(b) : "memory");
    return s;
}
u32 compare_unordered(u32 max, u32 min) {
    uint16_t s;
    __asm__ volatile("flds (%1)\n\tflds (%2)\n\tfucompp\n\tfnstsw %%ax"
                     : "=a"(s)
                     : "r"(max), "r"(min)
                     : "st", "st(1)", "memory");
    return s;
}
void unsigned_count(u32 scratch, u32 output, u32 value) {
    put(scratch, value);
    __asm__ volatile("fildl (%0)" ::"r"(scratch) : "st", "memory");
    if (value & 0x80000000u)
        __asm__ volatile("fadds %0" ::"m"(dat_006bb60c[0]) : "st", "memory");
    __asm__ volatile("fstps (%0)" ::"r"(output) : "st", "memory");
}
void delta(u32 min, u32 max) {
    __asm__ volatile("flds (%1)\n\tfsubs (%0)" ::"r"(min), "r"(max) : "st", "memory");
}
void scale(u32 count, u32 output) {
    __asm__ volatile("flds (%0)\n\tfdiv %%st(1),%%st(0)\n\tfstps (%1)\n\tfstp %%st(0)" ::"r"(count),
                     "r"(output)
                     : "st", "st(1)", "memory");
}
void coefficient(u32 min, u32 max, u32 left, u32 right, u32 output) {
    __asm__ volatile(
        "flds (%1)\n\tfmuls (%3)\n\tflds (%0)\n\tfmuls (%2)\n\tfaddp %%st,%%st(1)\n\tfstps (%4)" ::
            "r"(min),
        "r"(max), "r"(left), "r"(right), "r"(output)
        : "st", "st(1)", "memory");
}
void index_value(u32 input, u32 min, u32 scale) {
    __asm__ volatile("flds (%0)\n\tfsubs (%1)\n\tfmuls (%2)" ::"r"(input), "r"(min), "r"(scale)
                     : "st", "memory");
}
u32 lower_cut(u32 min, u32 input) {
    uint16_t s;
    __asm__ volatile("flds (%1)\n\tfmuls %3\n\tfcomps (%2)\n\tfnstsw %%ax"
                     : "=a"(s)
                     : "r"(min), "r"(input), "m"(dat_006bc860[0])
                     : "st", "memory");
    return s;
}
u32 upper_cut(u32 max, u32 input) {
    uint16_t s;
    __asm__ volatile("flds (%1)\n\tfadds %3\n\tfmuls %4\n\tfcomps (%2)\n\tfnstsw %%ax"
                     : "=a"(s)
                     : "r"(max), "r"(input), "m"(dat_006bc4dc[0]), "m"(dat_006bc860[0])
                     : "st", "memory");
    return s;
}
void rounded_index(u32 temporary, u32 integer) {
    __asm__ volatile("fadds %2\n\tfstps (%0)\n\tflds (%0)\n\tfistpl (%1)" ::"r"(temporary),
                     "r"(integer), "m"(dat_006bc860[0])
                     : "st", "memory");
}
void error_begin(u32 input, u32 coefficient) {
    __asm__ volatile("flds (%0)\n\tfsubs (%1)" ::"r"(input), "r"(coefficient) : "st", "memory");
}
void accumulate(u32 left, u32 right, u32 frame) {
    __asm__ volatile(
        "fld %%st(0)\n\tfmuls (%0)\n\tfadds 72(%2)\n\tfstps 72(%2)\n\tflds (%0)\n\tfld %%st(0)\n\tfmul %%st(1),%%st(0)\n\tfadds 64(%2)\n\tfstps 64(%2)\n\tfstp %%st(0)\n\tfmuls (%1)\n\tfadds 68(%2)\n\tfstps 68(%2)\n\tflds (%1)\n\tfld %%st(0)\n\tfmul %%st(1),%%st(0)\n\tfadds 60(%2)\n\tfstps 60(%2)\n\tfstp %%st(0)" ::
            "r"(left),
        "r"(right), "r"(frame)
        : "st", "st(1)", "st(2)", "memory");
}
void improve(u32 error, u32 squares, u32 endpoint) {
    __asm__ volatile("flds (%0)\n\tfdivs (%1)\n\tfsubrs (%2)\n\tfstps (%2)" ::"r"(error),
                     "r"(squares), "r"(endpoint)
                     : "st", "memory");
}
void swap(u32 min, u32 max) {
    __asm__ volatile("flds (%0)" ::"r"(min) : "st", "memory");
    const u32 old = word(max);
    __asm__ volatile("fstps (%0)" ::"r"(max) : "st", "memory");
    put(min, old);
}
u32 error_square_compare(u32 error) {
    uint16_t s;
    __asm__ volatile("flds (%1)\n\tfmuls (%1)\n\tfcomps %2\n\tfnstsw %%ax"
                     : "=a"(s)
                     : "r"(error), "m"(dat_006dfa1c)
                     : "st", "memory");
    return s;
}
void endpoint_value(u32 value) {
    if (!even05(compare(value, reinterpret_cast<u32>(dat_006bb5fc))))
        __asm__ volatile("fldz" ::: "st", "memory");
    else if ((compare(value, reinterpret_cast<u32>(dat_006bc4dc)) & 0x4100u) == 0)
        __asm__ volatile("fld1" ::: "st", "memory");
    else
        __asm__ volatile("flds (%0)" ::"r"(value) : "st", "memory");
}
} // namespace
// Complete0064f879..0064fba0. The original84B privateview is reserved
// before C++ stack use, including genuine inherited highWORD of FNSTCW.
// Weight storage is an exact contiguous observed112B view, not a formula.
extern "C" u32 recovered_0064f879(u32 args, u32 frame) {
    u32 levels = word(args + 12);
    const u32 pool = reinterpret_cast<u32>(dat_006f0034);
    const u32 left = pool + (levels == 6 ? 88u : 32u);
    put(frame + 56, pool + (levels == 6 ? 64u : 0u));
    one(frame + 80);
    zero(frame + 76);
    for (u32 i = 0; i < 16; ++i) {
        const u32 input = word(args + 8) + 4 * i;
        if (!even05(compare(input, frame + 80)) &&
            (levels == 8 || (compare(input, reinterpret_cast<u32>(dat_006bb5fc)) & 0x4100u) == 0))
            put(frame + 80, word(input));
        if ((compare(input, frame + 76) & 0x4100u) == 0 &&
            (levels == 8 || !even05(compare(input, reinterpret_cast<u32>(dat_006bc4dc)))))
            put(frame + 76, word(input));
    }
    if (levels != 8 && !even44(compare_unordered(frame + 76, frame + 80)))
        one(frame + 76);
    const u32 last = levels - 1u;
    unsigned_count(frame + 32, frame + 48, last);
    __asm__ volatile("fnstcw (%0)" ::"r"(frame + 52) : "memory");
    put(frame + 60, word(frame + 52) | 0x0c00u);
    __asm__ volatile("fldcw (%0)" ::"r"(frame + 60) : "memory");
    const u32 saved = word(frame + 52);
    clear_rmw(frame + 52);
    put(frame + 32, saved);
    for (;;) {
        delta(frame + 80, frame + 76);
        if (!even05(compare_live(reinterpret_cast<u32>(&dat_006c127c)))) {
            pop();
            break;
        }
        scale(frame + 48, frame + 44);
        if (levels) {
            const u32 right = word(frame + 56);
            for (u32 i = 0; i < levels; ++i)
                coefficient(frame + 80, frame + 76, left + 4 * i, right + 4 * i, frame + 4 * i);
            levels = word(args + 12);
        }
        if (levels == 6) {
            zero(frame + 24);
            one(frame + 28);
        }
        zero(frame + 72);
        zero(frame + 68);
        zero(frame + 64);
        zero(frame + 60);
        for (u32 i = 0; i < 16; ++i) {
            const u32 input = word(args + 8) + 4 * i;
            index_value(input, frame + 80, frame + 44);
            u32 index;
            if (!even41(compare_live(reinterpret_cast<u32>(dat_006bb5fc)))) {
                pop();
                if (levels == 6 && (lower_cut(frame + 80, input) & 0x0100u) == 0)
                    continue;
                index = 0;
            } else if ((compare_live(frame + 48) & 0x0100u) == 0) {
                pop();
                if (levels == 6 && !even41(upper_cut(frame + 76, input)))
                    continue;
                index = last;
            } else {
                rounded_index(frame + 40, frame + 36);
                index = word(frame + 36);
            }
            if (index >= levels)
                continue;
            error_begin(input, frame + 4 * index);
            const u32 right = word(frame + 56);
            accumulate(left + 4 * index, right + 4 * index, frame);
        }
        if ((compare(frame + 64, reinterpret_cast<u32>(dat_006bb5fc)) & 0x4100u) == 0)
            improve(frame + 72, frame + 64, frame + 80);
        if ((compare(frame + 60, reinterpret_cast<u32>(dat_006bb5fc)) & 0x4100u) == 0)
            improve(frame + 68, frame + 60, frame + 76);
        if ((compare(frame + 80, frame + 76) & 0x4100u) == 0)
            swap(frame + 80, frame + 76);
        if (!even05(error_square_compare(frame + 72)) && !even05(error_square_compare(frame + 68)))
            break;
        put(frame + 52, word(frame + 52) + 1u);
        if (word(frame + 52) >= 8)
            break;
    }
    __asm__ volatile("fldcw (%0)" ::"r"(frame + 32) : "memory");
    endpoint_value(frame + 80);
    const u32 lower = word(args);
    __asm__ volatile("fstps (%0)" ::"r"(lower) : "st", "memory");
    endpoint_value(frame + 76);
    const u32 upper = word(args + 4);
    __asm__ volatile("fstps (%0)" ::"r"(upper) : "st", "memory");
    return upper;
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0064f879(void*, void*, const void*, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $84,%esp\n\tmovl %esp,%eax\n\tpushl %eax\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_0064f879\n\taddl $8,%esp\n\tleave\n\tretl $16");
}
extern "C" {
extern const uint32_t dat_006f0034[28] = {
    0x00000000u, 0x3e124925u, 0x3e924925u, 0x3edb6db7u, 0x3f124925u, 0x3f36db6eu, 0x3f5b6db7u,
    0x3f924925u, 0x3f800000u, 0x3f5b6db7u, 0x3f36db6eu, 0x3f124925u, 0x3edb6db7u, 0x3e924925u,
    0x3e124925u, 0x00000000u, 0x00000000u, 0x3e4ccccdu, 0x3ecccccdu, 0x3f19999au, 0x3f4ccccdu,
    0x3f800000u, 0x3f800000u, 0x3f4ccccdu, 0x3f19999au, 0x3ecccccdu, 0x3e4ccccdu, 0x00000000u};
extern const uint32_t dat_006c127c = 0x3b800000u;
extern const uint32_t dat_006dfa1c = 0x3c800000u;
}
