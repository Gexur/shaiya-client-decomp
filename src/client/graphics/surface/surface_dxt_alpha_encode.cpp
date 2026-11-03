#include "graphics/surface/surface_dxt_alpha_encode.h"
#include "graphics/surface/surface_color_block_encode.h"
#include "graphics/surface/surface_dxt_color_wrappers.h"
#include "graphics/surface/surface_alpha_endpoints.h"
#include "graphics/surface/surface_block_codec_helpers.h"
#include "graphics/surface/surface_write_rgb24.h"
#include "graphics/surface/surface_format_palette.h"
#include "graphics/surface/surface_block_decode.h"
#include "graphics/surface/surface_word_packed_readers.h"
#include "graphics/render_project_unproject.h"
#include "graphics/render_packed_trig_quaternions.h"
extern "C" {
extern const uint32_t dat_006df41c, dat_006df418, dat_006be980;
}
namespace {
using u32 = uint32_t;
inline u32 addr(const void* p) {
    return reinterpret_cast<u32>(p);
}
inline u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
inline u32 octet(u32 p) {
    u32 v;
    __asm__ volatile("movzbl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
inline void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
inline void byte(u32 p, u32 v) {
    __asm__ volatile("movb %b1,(%0)" ::"r"(p), "q"(v) : "memory");
}
inline void add_mem(u32 p, u32 v) {
    __asm__ volatile("addl %1,(%0)" ::"r"(p), "r"(v) : "memory", "cc");
}
inline void clear16(u32 p) {
    u32 n = 16;
    __asm__ volatile("rep stosl" : "+D"(p), "+c"(n) : "a"(0) : "memory");
}
inline void load(u32 p) {
    __asm__ volatile("flds (%0)" ::"r"(p) : "st", "memory");
}
inline void store(u32 p) {
    __asm__ volatile("fsts (%0)" ::"r"(p) : "memory");
}
inline void store_pop(u32 p) {
    __asm__ volatile("fstps (%0)" ::"r"(p) : "st", "memory");
}
inline void integer_load(u32 p) {
    __asm__ volatile("fildl (%0)" ::"r"(p) : "st", "memory");
}
inline void integer_store(u32 p) {
    __asm__ volatile("fistpl (%0)" ::"r"(p) : "st", "memory");
}
inline void add(u32 p) {
    __asm__ volatile("fadds (%0)" ::"r"(p) : "st", "memory");
}
inline void mul(u32 p) {
    __asm__ volatile("fmuls (%0)" ::"r"(p) : "st", "memory");
}
inline void sub(u32 p) {
    __asm__ volatile("fsubs (%0)" ::"r"(p) : "st", "memory");
}
inline void reverse_sub(u32 p) {
    __asm__ volatile("fsubrs (%0)" ::"r"(p) : "st", "memory");
}
inline void pop() {
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
}
inline void mul1() {
    __asm__ volatile(".byte 0xd8,0xc9" ::: "st", "memory");
}
inline void add_pop() {
    __asm__ volatile("faddp %%st,%%st(1)" ::: "st", "st(1)", "memory");
}
inline void zero(u32 p) {
    __asm__ volatile("fldz\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
inline void one(u32 p) {
    __asm__ volatile("fld1\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
inline void save_control(u32 p) {
    __asm__ volatile("fnstcw (%0)" ::"r"(p) : "memory");
}
inline void load_control(u32 p) {
    __asm__ volatile("fldcw (%0)" ::"r"(p) : "memory");
}
inline u32 compare_live(u32 p) {
    uint16_t s;
    __asm__ volatile("fcoms (%1)\n\tfnstsw %%ax" : "=a"(s) : "r"(p) : "memory");
    return s;
}
inline u32 compare_pop(u32 p) {
    uint16_t s;
    __asm__ volatile("fcomps (%1)\n\tfnstsw %%ax" : "=a"(s) : "r"(p) : "st", "memory");
    return s;
}
inline u32 unordered(u32 first, u32 second) {
    uint16_t s;
    __asm__ volatile("flds (%1)\n\tflds (%2)\n\tfucompp\n\tfnstsw %%ax"
                     : "=a"(s)
                     : "r"(first), "r"(second)
                     : "st", "st(1)", "memory");
    return s;
}
inline bool even(u32 s, u32 mask) {
    s = (s >> 8) & mask;
    return s == 0 || s == mask;
}
inline void diffuse(u32 f, u32 i) {
    const u32 column = i & 3u, offset = i * 4;
    if (column != 3u) {
        load(addr(&dat_006f0104));
        mul1();
        add(f + offset + 4);
        store_pop(f + offset + 4);
    }
    if (i >= 12u)
        pop();
    else {
        if (column) {
            load(addr(&dat_006df41c));
            mul1();
            add(f + offset + 12);
            store_pop(f + offset + 12);
        }
        load(addr(&dat_006df418));
        mul1();
        add(f + offset + 16);
        store_pop(f + offset + 16);
        if (column == 3u)
            pop();
        else {
            mul(addr(&dat_006be980));
            add(f + offset + 20);
            store_pop(f + offset + 20);
        }
    }
}
// Only actual original-position child calls switch ESP. Compiler frames live
// below an unwritten8192B gap; no private/caller input is synthesized here.
inline u32 color(u32 f, u32 input, u32& output) {
    u32 result = input;
    __asm__ volatile(
        "movl %%esp,%%esi\n\tleal -12(%%edi),%%esp\n\tpushl 176(%%edi)\n\tmovl 168(%%edi),%%ebx\n\tpushl $0\n\tleal 8(%%ebx),%%edx\n\tpushl %%edx\n\tcalll _FUN_00650120@12\n\tmovl %%esi,%%esp"
        : "+a"(result), "=b"(output)
        : "D"(f)
        : "ecx", "edx", "esi", "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
          "memory", "cc");
    return result;
}
inline void endpoints(u32 f, u32 levels) {
    __asm__ volatile(
        "movl %%esp,%%esi\n\tleal -12(%%edi),%%esp\n\tpushl %%ebx\n\tleal 64(%%edi),%%eax\n\tpushl %%eax\n\tleal 172(%%edi),%%eax\n\tpushl %%eax\n\tleal 148(%%edi),%%eax\n\tpushl %%eax\n\tcalll _FUN_0064f879@16\n\tmovl %%esi,%%esp" ::
            "D"(f),
        "b"(levels)
        : "eax", "ecx", "edx", "esi", "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)",
          "st(7)", "memory", "cc");
}
inline u32 premultiply(u32 f, u32 source) {
    u32 result = source;
    __asm__ volatile(
        "movl %%esp,%%esi\n\tmovl %%edi,%%esp\n\tmovl %%edi,%%ecx\n\tcalll _FUN_0064f746\n\tmovl %%esi,%%esp"
        : "+a"(result)
        : "D"(f)
        : "ecx", "edx", "esi", "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
          "memory", "cc");
    return result;
}
inline u32 nested3(u32 f, u32 args) {
    u32 result;
    __asm__ volatile(
        "movl %%esp,%%esi\n\tmovl %%edi,%%esp\n\tpushl 8(%%ebx)\n\tpushl %%edi\n\tpushl (%%ebx)\n\tcalll _FUN_00650e9c\n\tmovl %%esi,%%esp"
        : "=a"(result)
        : "D"(f), "b"(args)
        : "ecx", "edx", "esi", "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
          "memory", "cc");
    return result;
}
inline u32 nested5(u32 f, u32 args) {
    u32 result;
    __asm__ volatile(
        "movl %%esp,%%esi\n\tmovl %%edi,%%esp\n\tpushl 8(%%ebx)\n\tpushl %%edi\n\tpushl (%%ebx)\n\tcalll _FUN_00650fcb\n\tmovl %%esi,%%esp"
        : "=a"(result)
        : "D"(f), "b"(args)
        : "ecx", "edx", "esi", "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
          "memory", "cc");
    return result;
}
} // namespace

// Complete00650fcb..0065149f. f=entrySP-164,160 original private bytes;
// args=f+168. The actual second argument is CW/float/integer scratch.
extern "C" u32 recovered_00650fcb(u32 args, u32 f) {
    const u32 input = word(args + 4), alpha = input + 12, first = word(alpha);
    const bool initial = word(args + 8) != 0;
    put(f + 136, alpha);
    put(f + 144, first);
    put(f + 156, first);
    if (initial)
        clear16(f);
    save_control(args + 4);
    put(f + 152, word(args + 4) | 0x0c00u);
    load_control(f + 152);
    put(f + 140, word(args + 4));
    for (u32 i = 0, p = alpha; i < 16; ++i, p += 16) {
        const bool dither = word(args + 8) != 0;
        put(args + 4, word(p));
        if (dither) {
            load(args + 4);
            add(f + 4 * i);
            store_pop(args + 4);
        }
        load(args + 4);
        mul(addr(&dat_006bc8c4));
        add(addr(dat_006bc860));
        store_pop(f + 152);
        load(f + 152);
        integer_store(f + 148);
        put(f + 152, word(f + 148));
        integer_load(f + 152);
        mul(addr(&dat_006be1d0));
        const u32 status = compare_live(f + 144);
        store(f + 64 + 4 * i);
        if (!even(status, 5))
            store(f + 144);
        else if ((compare_live(f + 156) & 0x4100u) == 0)
            store(f + 156);
        if (word(args + 8)) {
            reverse_sub(args + 4);
            diffuse(f, i);
        } else
            pop();
    }
    load_control(f + 140);
    u32 output;
    const u32 result = color(f, input, output);
    if (result & 0x80000000u)
        return result;
    if (!even(unordered(f + 144, addr(dat_006bc4dc)), 0x44)) {
        byte(output, 255);
        byte(output + 1, 255);
        put(output + 2, 0);
        __asm__ volatile("movw $0,(%0)" ::"r"(output + 6) : "memory");
        return 0;
    }
    u32 levels;
    if (!even(unordered(f + 144, addr(dat_006bb5fc)), 0x44) ||
        !even(unordered(f + 156, addr(dat_006bc4dc)), 0x44))
        levels = 6;
    else
        levels = 8;
    put(args, levels);
    if (levels == 6)
        levels = word(args);
    endpoints(f, levels);
    save_control(f + 156);
    put(f + 152, word(f + 156) | 0x0c00u);
    load_control(f + 152);
    load(f + 148);
    mul(addr(&dat_006bc8c4));
    put(f + 140, word(f + 156));
    add(addr(dat_006bc860));
    store_pop(f + 152);
    load(f + 152);
    integer_store(f + 148);
    load(args + 4);
    const u32 lower = word(f + 148);
    mul(addr(&dat_006bc8c4));
    add(addr(dat_006bc860));
    store_pop(args + 4);
    load(args + 4);
    integer_store(f + 152);
    const u32 upper = word(f + 152);
    load_control(f + 140);
    put(args + 4, lower & 255u);
    integer_load(args + 4);
    put(args + 4, upper & 255u);
    mul(addr(&dat_006be1d0));
    integer_load(args + 4);
    mul(addr(&dat_006be1d0));
    store(args + 4);
    if (levels == 8 && (lower & 255u) == (upper & 255u)) {
        pop();
        byte(output, lower);
        pop();
        byte(output + 1, upper);
        put(output + 2, 0);
        __asm__ volatile("movw $0,(%0)" ::"r"(output + 6) : "memory");
        return 0;
    }
    const bool six = levels == 6;
    if (six) {
        byte(output, lower);
        pop();
        const u32 u = word(args + 4);
        store_pop(f + 96);
        put(f + 100, u);
        byte(output + 1, upper);
    } else {
        byte(output + 1, lower);
        store_pop(f + 96);
        store_pop(f + 100);
        byte(output, upper);
    }
    const u32 count = six ? 5u : 7u;
    for (u32 i = 1; i < count; ++i) {
        const u32 complement = count - i;
        put(args + 4, complement);
        integer_load(args + 4);
        if (complement & 0x80000000u)
            add(addr(dat_006bb60c));
        mul(f + 96);
        put(args + 4, i);
        integer_load(args + 4);
        if (i & 0x80000000u)
            add(addr(dat_006bb60c));
        mul(f + 100);
        add_pop();
        mul(six ? addr(&dat_006be7fc) : addr(&dat_006df420));
        store_pop(f + 4 * (i + 1) + 96);
    }
    if (six) {
        put(f + 152, addr(dat_006f0128));
        zero(f + 120);
        one(f + 124);
    } else
        put(f + 152, addr(dat_006f0108));
    --levels;
    put(args + 4, levels);
    integer_load(args + 4);
    if (levels & 0x80000000u)
        add(addr(dat_006bb60c));
    store_pop(f + 148);
    if (even(unordered(f + 100, f + 96), 0x44)) {
        load(f + 100);
        sub(f + 96);
        __asm__ volatile("fdivrs (%0)" ::"r"(f + 148) : "st", "memory");
    } else
        __asm__ volatile("fldz" ::: "st", "memory");
    const bool initial_dither = word(args + 8) != 0;
    store_pop(f + 132);
    if (initial_dither)
        clear16(f);
    save_control(args + 4);
    put(f + 156, word(args + 4) | 0x0c00u);
    load_control(f + 156);
    const u32 saved = word(args + 4), pointer = word(f + 136);
    put(f + 140, saved);
    put(f + 144, pointer);
    for (u32 block = 0; block < 2; ++block) {
        u32 packed = 0;
        const u32 begin = block * 8, end = begin + 8;
        put(f + 156, 0);
        put(f + 156, word(f + 144));
        for (u32 i = begin; i < end; ++i) {
            const bool dither = word(args + 8) != 0;
            put(args + 4, word(word(f + 156)));
            if (dither) {
                load(args + 4);
                add(f + 4 * i);
                store_pop(args + 4);
            }
            load(args + 4);
            sub(f + 96);
            mul(f + 132);
            u32 index;
            if (!even(compare_live(addr(dat_006bb5fc)), 0x41)) {
                const bool six_now = word(args) == 6;
                pop();
                if (six_now) {
                    load(f + 96);
                    mul(addr(dat_006bc860));
                    index = (compare_pop(args + 4) & 0x0100u) ? 0u : 6u;
                } else
                    index = 0;
            } else if ((compare_live(f + 148) & 0x0100u) == 0) {
                const bool six_now = word(args) == 6;
                pop();
                if (six_now) {
                    load(f + 100);
                    add(addr(dat_006bc4dc));
                    mul(addr(dat_006bc860));
                    index = even(compare_pop(args + 4), 0x41) ? 1u : 7u;
                } else
                    index = 1;
            } else {
                add(addr(dat_006bc860));
                store_pop(f + 136);
                load(f + 136);
                integer_store(f + 128);
                const u32 ordinal = word(f + 128), map = word(f + 152);
                index = word(map + ordinal * 4);
            }
            packed = (packed >> 3) | (index << 21);
            if (word(args + 8)) {
                load(args + 4);
                sub(f + 96 + 4 * index);
                diffuse(f, i);
            }
            add_mem(f + 156, 16);
        }
        put(f + 156, packed);
        const u32 high = octet(f + 158);
        add_mem(f + 144, 128);
        const u32 destination = output + 3 + 3 * block;
        byte(destination + 1, high);
        byte(destination - 1, packed);
        byte(destination, packed >> 8);
    }
    load_control(f + 140);
    return 0;
}
extern "C" u32 recovered_006514eb(u32 args, u32 f) {
    const u32 r = premultiply(f, word(args + 4));
    if (r & 0x80000000u)
        return r;
    const u32 z = nested3(f, args);
    return z & 0x80000000u ? z : 0u;
}
extern "C" u32 recovered_00651524(u32 args, u32 f) {
    const u32 r = premultiply(f, word(args + 4));
    if (r & 0x80000000u)
        return r;
    const u32 z = nested5(f, args);
    return z & 0x80000000u ? z : 0u;
}
extern "C" __attribute__((naked, stdcall)) u32 FUN_00650fcb(void*, const void*, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $160,%esp\n\tmovl %esp,%eax\n\tsubl $8192,%esp\n\tpushl %eax\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_00650fcb\n\taddl $8,%esp\n\tleave\n\tretl $12");
}
extern "C" __attribute__((naked, stdcall)) u32 FUN_006514eb(void*, const void*, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $256,%esp\n\tmovl %esp,%eax\n\tsubl $32768,%esp\n\tpushl %eax\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_006514eb\n\taddl $8,%esp\n\tleave\n\tretl $12");
}
extern "C" __attribute__((naked, stdcall)) u32 FUN_00651524(void*, const void*, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $256,%esp\n\tmovl %esp,%eax\n\tsubl $32768,%esp\n\tpushl %eax\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_00651524\n\taddl $8,%esp\n\tleave\n\tretl $12");
}
extern "C" {
extern const uint32_t dat_006f0108[8] = {0, 2, 3, 4, 5, 6, 7, 1};
extern const uint32_t dat_006f0128[6] = {0, 2, 3, 4, 5, 1};
}
