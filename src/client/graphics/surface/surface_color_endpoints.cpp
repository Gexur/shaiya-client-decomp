#include "graphics/surface/surface_color_endpoints.h"
#include "graphics/render_project_unproject.h"
#include "graphics/render_packed_trig_quaternions.h"
#include "graphics/surface/surface_write_transform.h"
#include "graphics/surface/surface_volume_box_backend.h"

namespace {
using u32 = uint32_t;
// Only integer addresses cross these helpers. Register-register x87 operations
// use their original literal encodings to avoid assembler direction ambiguity.
inline u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
inline void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
inline void clear_rmw(u32 p) {
    __asm__ volatile("andl $0,(%0)" ::"r"(p) : "cc", "memory");
}
inline void increment_rmw(u32 p) {
    __asm__ volatile("incl (%0)" ::"r"(p) : "cc", "memory");
}
inline void load(u32 p) {
    __asm__ volatile("flds (%0)" ::"r"(p) : "st", "memory");
}
inline void load_zero() {
    __asm__ volatile("fldz" ::: "st", "memory");
}
inline void store(u32 p) {
    __asm__ volatile("fsts (%0)" ::"r"(p) : "memory");
}
inline void store_pop(u32 p) {
    __asm__ volatile("fstps (%0)" ::"r"(p) : "st", "memory");
}
inline void pop() {
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
}
inline void zero(u32 p) {
    load_zero();
    store_pop(p);
}
inline bool even05(u32 s) {
    s = (s >> 8) & 5u;
    return s == 0u || s == 5u;
}
inline u32 compare(u32 a, u32 b) {
    uint16_t s;
    __asm__ volatile("flds (%1)\n\tfcomps (%2)\n\tfnstsw %%ax"
                     : "=a"(s)
                     : "r"(a), "r"(b)
                     : "st", "memory");
    return s;
}
inline u32 compare_live(u32 b) {
    uint16_t s;
    __asm__ volatile("fcoms (%1)\n\tfnstsw %%ax" : "=a"(s) : "r"(b) : "memory");
    return s;
}
inline void initial_direction(u32 f) {
    __asm__ volatile("flds 160(%0)\n\tfsubs 176(%0)\n\tfstps 128(%0)\n\t"
                     "flds 180(%0)\n\t.byte 0xd8,0xe9\n\tfstps 132(%0)\n\t"
                     "flds 168(%0)\n\tfsubs 184(%0)\n\t.byte 0xd9,0xc0\n\t.byte 0xd8,0xc9\n\t"
                     "flds 132(%0)\n\tfmuls 132(%0)\n\t.byte 0xde,0xc1\n\t"
                     "flds 128(%0)\n\tfmuls 128(%0)\n\t.byte 0xde,0xc1" ::"r"(f)
                     : "st", "st(1)", "st(2)", "st(3)", "memory");
}
inline u32 initial_length(u32 f) {
    uint16_t s;
    __asm__ volatile("fcoms %2\n\tfsts 108(%1)\n\tfnstsw %%ax"
                     : "=a"(s)
                     : "r"(f), "m"(dat_006de5a4)
                     : "memory");
    return s;
}
inline void initial_projection_center(u32 f) {
    __asm__ volatile(
        "fld1\n\t.byte 0xde,0xf1\n\tflds 128(%0)\n\t.byte 0xd8,0xc9\n\tfstps 76(%0)\n\t"
        "flds 132(%0)\n\t.byte 0xd8,0xc9\n\tfstps 80(%0)\n\t"
        ".byte 0xd8,0xc9\n\tfstps 84(%0)\n\tfstp %%st(0)\n\t"
        "flds %1\n\tflds 160(%0)\n\tfadds 176(%0)\n\t.byte 0xd8,0xc9\n\tfstps 112(%0)\n\t"
        ".byte 0xd9,0xc1\n\tfadds 180(%0)\n\t.byte 0xd8,0xc9\n\tfstps 116(%0)\n\t"
        "flds 168(%0)\n\tfadds 184(%0)\n\t.byte 0xd8,0xc9\n\tfstps 120(%0)\n\tfstp %%st(0)" ::"r"(
            f),
        "m"(dat_006bc860[0])
        : "st", "st(1)", "st(2)", "st(3)", "memory");
}
inline void score_sample(u32 f, u32 p) {
    __asm__ volatile(
        "flds -8(%1)\n\tfsubs 112(%0)\n\tfmuls 76(%0)\n\tfstps 128(%0)\n\t"
        "flds -4(%1)\n\tfsubs 116(%0)\n\tfmuls 80(%0)\n\tfstps 132(%0)\n\t"
        "flds (%1)\n\tfsubs 120(%0)\n\tfmuls 84(%0)\n\t"
        "flds 132(%0)\n\t.byte 0xd8,0xc1\n\tfadds 128(%0)\n\t.byte 0xd9,0xc0\n\t.byte 0xd8,0xc9\n\t.byte 0xde,0xc3\n\tfstp %%st(0)\n\t"
        "flds 132(%0)\n\tfadds 128(%0)\n\t.byte 0xd8,0xe1\n\t.byte 0xd9,0xc0\n\t.byte 0xd8,0xc9\n\tfadds 148(%0)\n\tfstps 148(%0)\n\tfstp %%st(0)\n\t"
        "flds 128(%0)\n\tfsubs 132(%0)\n\t.byte 0xd9,0xc0\n\t.byte 0xd8,0xc2\n\t.byte 0xd9,0xc0\n\t.byte 0xd8,0xc9\n\tfadds 152(%0)\n\tfstps 152(%0)\n\tfstp %%st(0)\n\t"
        ".byte 0xde,0xe1\n\t.byte 0xd9,0xc0\n\t.byte 0xd8,0xc9\n\tfadds 156(%0)\n\tfstps 156(%0)\n\tfstp %%st(0)" ::
            "r"(f),
        "r"(p)
        : "st", "st(1)", "st(2)", "st(3)", "st(4)", "memory");
}
inline void unsigned_count(u32 args, u32 f, u32 value) {
    put(args + 12, value);
    __asm__ volatile("fildl (%0)" ::"r"(args + 12) : "st", "memory");
    if (value & 0x80000000u)
        __asm__ volatile("fadds %0" ::"m"(dat_006bb60c[0]) : "st", "memory");
    store_pop(f + 108);
}
inline void coefficient(u32 f, u32 right, u32 left, u32 dest) {
    __asm__ volatile(
        "flds 176(%0)\n\tfmuls (%1)\n\tflds 160(%0)\n\tfmuls (%2)\n\t.byte 0xde,0xc1\n\tfstps (%3)\n\t"
        "flds 180(%0)\n\tfmuls (%1)\n\tflds 164(%0)\n\tfmuls (%2)\n\t.byte 0xde,0xc1\n\tfstps 4(%3)\n\t"
        "flds 184(%0)\n\tfmuls (%1)\n\tflds 168(%0)\n\tfmuls (%2)\n\t.byte 0xde,0xc1\n\tfstps 8(%3)" ::
            "r"(f),
        "r"(right), "r"(left), "r"(dest)
        : "st", "st(1)", "memory");
}
inline u32 iteration_direction(u32 f) {
    uint16_t s;
    __asm__ volatile(
        "flds 160(%1)\n\tfsubs 176(%1)\n\tflds 164(%1)\n\tfsubs 180(%1)\n\tfstps 132(%1)\n\t"
        "flds 168(%1)\n\tfsubs 184(%1)\n\t.byte 0xd9,0xc0\n\t.byte 0xd8,0xc9\n\t"
        "flds 132(%1)\n\tfmuls 132(%1)\n\t.byte 0xde,0xc1\n\t.byte 0xd9,0xc2\n\t.byte 0xd8,0xcb\n\t.byte 0xde,0xc1\n\t"
        "fcoms %2\n\tfnstsw %%ax"
        : "=a"(s)
        : "r"(f), "m"(dat_006f00a4[1])
        : "st", "st(1)", "st(2)", "st(3)", "memory");
    return s;
}
inline void iteration_projection(u32 f) {
    __asm__ volatile(
        ".byte 0xd9,0xc0\n\t.byte 0xd8,0xcb\n\tfstps 128(%0)\n\t"
        "flds 132(%0)\n\t.byte 0xd8,0xc9\n\tfstps 132(%0)\n\t.byte 0xd8,0xc9\n\tfstps 136(%0)\n\tfstp %%st(0)\n\tfstp %%st(0)" ::
            "r"(f)
        : "st", "st(1)", "st(2)", "st(3)", "memory");
}
inline u32 projected_index(u32 f, u32 p) {
    uint16_t s;
    __asm__ volatile("flds -4(%2)\n\tfsubs 180(%1)\n\tfmuls 132(%1)\n\t"
                     "flds -8(%2)\n\tfsubs 176(%1)\n\tfmuls 128(%1)\n\t.byte 0xde,0xc1\n\t"
                     "flds (%2)\n\tfsubs 184(%1)\n\tfmuls 136(%1)\n\t.byte 0xde,0xc1\n\t"
                     "fsts 100(%1)\n\tfcomps 108(%1)\n\tfnstsw %%ax"
                     : "=a"(s)
                     : "r"(f), "r"(p)
                     : "st", "st(1)", "st(2)", "memory");
    return s;
}
inline void rounded_index(u32 f) {
    __asm__ volatile(
        "fstp %%st(0)\n\tflds 100(%0)\n\tfadds %1\n\tfstps 100(%0)\n\tflds 100(%0)\n\tfistpl 64(%0)" ::
            "r"(f),
        "m"(dat_006bc860[0])
        : "st", "memory");
}
inline void sample_error(u32 f, u32 p, u32 c) {
    __asm__ volatile(
        "flds (%2)\n\tfsubs -8(%1)\n\tflds 4(%2)\n\tfsubs -4(%1)\n\tfstps 80(%0)\n\tflds 8(%2)\n\tfsubs (%1)" ::
            "r"(f),
        "r"(p), "r"(c)
        : "st", "st(1)", "st(2)", "memory");
}
inline void accumulate(u32 f, u32 args, u32 left, u32 right) {
    __asm__ volatile(
        "flds (%2)\n\tfmuls %4\n\tflds (%3)\n\tfmuls %4\n\t"
        ".byte 0xd9,0xc1\n\tfmuls (%2)\n\tfadds 12(%1)\n\tfstps 12(%1)\n\t"
        ".byte 0xd9,0xc1\n\t.byte 0xd8,0xcc\n\tfadds 112(%0)\n\tfstps 112(%0)\n\t"
        ".byte 0xd9,0xc1\n\tfmuls 80(%0)\n\tfadds 116(%0)\n\tfstps 116(%0)\n\t"
        ".byte 0xd9,0xc1\n\t.byte 0xd8,0xcb\n\tfadds 120(%0)\n\tfstps 120(%0)\n\t"
        ".byte 0xd9,0xc0\n\tfmuls (%3)\n\tfadds 8(%1)\n\tfstps 8(%1)\n\t"
        ".byte 0xd9,0xc0\n\t.byte 0xd8,0xcc\n\tfadds 144(%0)\n\tfstps 144(%0)\n\t"
        "flds 80(%0)\n\t.byte 0xd8,0xc9\n\tfadds 148(%0)\n\tfstps 148(%0)\n\t"
        ".byte 0xd8,0xca\n\tfadds 152(%0)\n\tfstps 152(%0)\n\tfstp %%st(0)\n\tfstp %%st(0)\n\tfstp %%st(0)" ::
            "r"(f),
        "r"(args), "r"(left), "r"(right), "m"(dat_006bfde0)
        : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "memory");
}
inline void improve(u32 sum, u32 error, u32 endpoint) {
    __asm__ volatile(
        "flds %3\n\tfdivs (%0)\n\tflds (%1)\n\t.byte 0xd8,0xc9\n\tfadds (%2)\n\tfstps (%2)\n\t"
        "flds 4(%1)\n\t.byte 0xd8,0xc9\n\tfadds 4(%2)\n\tfstps 4(%2)\n\t"
        "fmuls 8(%1)\n\tfadds 8(%2)\n\tfstps 8(%2)" ::"r"(sum),
        "r"(error), "r"(endpoint), "m"(dat_006bb5f8)
        : "st", "st(1)", "memory");
}
inline u32 squared_error(u32 p) {
    uint16_t s;
    __asm__ volatile("flds (%1)\n\tfmuls (%1)\n\t.byte 0xd8,0xd9\n\tfnstsw %%ax"
                     : "=a"(s)
                     : "r"(p)
                     : "st", "memory");
    return s;
}
inline u32 shortcut_output(u32 args, u32 f) {
    const u32 lower = word(args);
    put(lower, word(f + 176));
    put(lower + 4, word(f + 180));
    put(lower + 8, word(f + 184));
    const u32 upper = word(args + 4), red = word(f + 160);
    store_pop(upper + 4);
    put(upper, red);
    put(upper + 8, word(f + 168));
    return upper;
}
} // namespace

// Complete original0064fba0..00650120,516 instructions/1408 bytes.
// The192B private view is reserved before C++ pushes. Alpha slots in the four
// 16B coefficients and all other unproduced bytes retain their actual input.
extern "C" u32 recovered_0064fba0(u32 args, u32 f) {
    const u32 pool = reinterpret_cast<u32>(dat_006f00a4);
    if (word(args + 12) == 3u) {
        put(f + 104, pool + 52);
        put(f + 92, pool + 40);
    } else {
        put(f + 104, pool + 24);
        put(f + 92, pool + 8);
    }
    zero(f + 160);
    load_zero();
    store(f + 164);
    const u32 initial = reinterpret_cast<u32>(dat_00716910);
    put(f + 176, word(initial));
    load_zero();
    put(f + 180, word(initial + 4));
    store_pop(f + 168);
    put(f + 184, word(initial + 8));
    put(f + 188, word(initial + 12));
    const u32 input = word(args + 8) + 8u;
    put(f + 68, input);
    for (u32 p = input, n = 16; n; --n, p += 16) {
        if (!even05(compare(p - 8, f + 176)))
            put(f + 176, word(p - 8));
        if (!even05(compare(p - 4, f + 180)))
            put(f + 180, word(p - 4));
        if (!even05(compare(p, f + 184)))
            put(f + 184, word(p));
        if ((compare(p - 8, f + 160) & 0x4100u) == 0)
            put(f + 160, word(p - 8));
        if (!even05(compare_live(p - 4))) {
            pop();
            load(p - 4);
        }
        if ((compare(p, f + 168) & 0x4100u) == 0)
            put(f + 168, word(p));
    }
    store(f + 164);
    initial_direction(f);
    if (!even05(initial_length(f))) {
        pop();
        pop();
        return shortcut_output(args, f);
    }
    initial_projection_center(f);
    zero(f + 156);
    zero(f + 152);
    zero(f + 148);
    load_zero();
    for (u32 p = input, n = 16; n; --n, p += 16)
        score_sample(f, p);
    store(f + 144);
    u32 selected = 0;
    for (u32 i = 1; i < 4; ++i) {
        if (!even05(compare_live(f + 144 + 4 * i))) {
            pop();
            selected = i;
            load(f + 144 + 4 * i);
        }
    }
    pop();
    if (selected & 2u) {
        const u32 old = word(f + 180);
        store_pop(f + 180);
        put(args + 8, old);
        load(args + 8);
        store(f + 164);
    }
    if (selected & 1u) {
        load(f + 184);
        const u32 old = word(f + 168);
        store_pop(f + 168);
        put(f + 184, old);
    }
    if (!even05(compare(f + 108, pool + 4)))
        return shortcut_output(args, f);
    const u32 levels = word(args + 12);
    pop();
    unsigned_count(args, f, levels - 1u);
    __asm__ volatile("fnstcw (%0)" ::"r"(args + 12) : "memory");
    put(args + 8, word(args + 12) | 0x0c00u);
    __asm__ volatile("fldcw (%0)" ::"r"(args + 8) : "memory");
    const u32 saved = word(args + 12);
    load(pool);
    clear_rmw(f + 96);
    put(f + 72, saved);
    for (;;) {
        if (levels) {
            u32 right = word(f + 104), left = word(f + 92), dest = f;
            for (u32 n = levels; n; --n, right += 4, left += 4, dest += 16)
                coefficient(f, right, left, dest);
        }
        if (!even05(iteration_direction(f))) {
            pop();
            pop();
            pop();
            break;
        }
        __asm__ volatile("fdivrs 108(%0)" ::"r"(f) : "st", "memory");
        const u32 iteration_input = word(f + 68);
        iteration_projection(f);
        zero(f + 152);
        zero(f + 148);
        zero(f + 144);
        zero(f + 120);
        zero(f + 116);
        zero(f + 112);
        zero(args + 8);
        zero(args + 12);
        for (u32 p = iteration_input, n = 16; n; --n, p += 16) {
            u32 index;
            if ((projected_index(f, p) & 0x0100u) == 0)
                index = levels - 1u;
            else {
                rounded_index(f);
                index = word(f + 64);
                load(pool);
            }
            const u32 upper_weights = word(f + 92);
            sample_error(f, p, f + (index << 4));
            const u32 lower_weights = word(f + 104);
            accumulate(f, args, lower_weights + (index << 2), upper_weights + (index << 2));
        }
        const u32 origin = reinterpret_cast<u32>(dat_006bb5fc);
        if ((compare(args + 12, origin) & 0x4100u) == 0)
            improve(args + 12, f + 112, f + 176);
        if ((compare(args + 8, origin) & 0x4100u) == 0)
            improve(args + 8, f + 144, f + 160);
        if (!even05(squared_error(f + 112)) && !even05(squared_error(f + 116)) &&
            !even05(squared_error(f + 120)) && !even05(squared_error(f + 144)) &&
            !even05(squared_error(f + 148)) && !even05(squared_error(f + 152)))
            break;
        increment_rmw(f + 96);
        if (word(f + 96) >= 8u)
            break;
    }
    pop();
    __asm__ volatile("fldcw (%0)" ::"r"(f + 72) : "memory");
    const u32 lower = word(args);
    put(lower, word(f + 176));
    put(lower + 4, word(f + 180));
    put(lower + 8, word(f + 184));
    const u32 red = word(f + 160), upper = word(args + 4);
    put(upper, red);
    put(upper + 4, word(f + 164));
    put(upper + 8, word(f + 168));
    return upper;
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0064fba0(void*, void*, const void*, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $192,%esp\n\tmovl %esp,%eax\n\tpushl %eax\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_0064fba0\n\taddl $8,%esp\n\tleave\n\tretl $16");
}
extern "C" {
uint32_t dat_00716910[4] = {0x3e981530u, 0x3f800000u, 0x3dce6734u, 0x3f800000u};
extern const uint32_t dat_006de5a4 = 0x00800000u;
extern const uint32_t dat_006f00a4[16] = {0x37800000u, 0x39800000u, 0x00000000u, 0x3eaaaaabu,
                                          0x3f2aaaabu, 0x3f800000u, 0x3f800000u, 0x3f2aaaabu,
                                          0x3eaaaaabu, 0x00000000u, 0x00000000u, 0x3f000000u,
                                          0x3f800000u, 0x3f800000u, 0x3f000000u, 0x00000000u};
}
