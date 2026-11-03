#include "graphics/surface/surface_dxt_color_wrappers.h"
#include "graphics/surface/surface_color_block_encode.h"
#include "graphics/surface/surface_write_argb16.h"
#include "graphics/surface/surface_nibble_readers.h"
#include "graphics/surface/surface_write_rgb24.h"
#include "graphics/render_project_unproject.h"

namespace {
using u32 = uint32_t;
inline u32 address(const void* p) {
    return reinterpret_cast<u32>(p);
}
inline u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
inline void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
inline void and_three(u32 p) {
    __asm__ volatile("andl $3,(%0)" ::"r"(p) : "memory", "cc");
}
inline void add_sixteen(u32 p) {
    __asm__ volatile("addl $16,(%0)" ::"r"(p) : "memory", "cc");
}
inline void clear_sixteen(u32 p) {
    u32 count = 16;
    __asm__ volatile("rep stosl" : "+D"(p), "+c"(count) : "a"(0) : "memory");
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
inline void multiply(u32 p) {
    __asm__ volatile("fmuls (%0)" ::"r"(p) : "st", "memory");
}
inline void subtract_reverse(u32 p) {
    __asm__ volatile("fsubrs (%0)" ::"r"(p) : "st", "memory");
}
inline void multiply1() {
    __asm__ volatile(".byte 0xd8,0xc9" ::: "st", "memory");
}
inline void pop() {
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
}
inline void add_store(u32 p) {
    add(p);
    store_pop(p);
}
inline void save_control(u32 p) {
    __asm__ volatile("fnstcw (%0)" ::"r"(p) : "memory");
}
inline void load_control(u32 p) {
    __asm__ volatile("fldcw (%0)" ::"r"(p) : "memory");
}
struct Gpr {
    u32 eax, ecx, edx;
};
// Wrapper C++ lives below an unwritten8192B gap. Main's own4096B gap and
// nested genuine callees remain above that compiler backing. Each real call
// reuses its exact original outgoing ESP and captures physical result GPRs.
inline Gpr color_dxt1(u32 f, u32 input) {
    Gpr r;
    r.eax = input;
    __asm__ volatile(
        "movl %%esp,%%esi\n\tmovl %%edi,%%esp\n\tpushl 348(%%edi)\n\tpushl $1\n\tpushl 340(%%edi)\n\t"
        "calll _FUN_00650120@12\n\tmovl %%esi,%%esp"
        : "+a"(r.eax), "=c"(r.ecx), "=d"(r.edx)
        : "D"(f)
        : "esi", "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory",
          "cc");
    return r;
}
inline Gpr color_dxt3(u32 f, u32 output) {
    Gpr r;
    __asm__ volatile(
        "movl %%esp,%%esi\n\tleal -12(%%edi),%%esp\n\tpushl 96(%%edi)\n\tmovl 92(%%edi),%%eax\n\t"
        "pushl $0\n\tleal 8(%%ebx),%%edx\n\tpushl %%edx\n\tcalll _FUN_00650120@12\n\tmovl %%esi,%%esp"
        : "=a"(r.eax), "=c"(r.ecx), "=d"(r.edx)
        : "D"(f), "b"(output)
        : "esi", "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory",
          "cc");
    return r;
}
} // namespace

// Complete00650d78..00650e9c:99 instructions,292 bytes.
// f=entrySP-336, original332B private view; args=f+340.
extern "C" u32 recovered_00650d78(u32 args, u32 f) {
    u32 input;
    if (word(args + 8) != 0) {
        clear_sixteen(f + 256);
        save_control(f + 328);
        put(f + 324, word(f + 328) | 0x0c00u);
        load_control(f + 324);
        const u32 saved = word(f + 328), source = word(args + 4);
        put(f + 320, saved);
        const u32 normalized_delta = f - source, half = address(dat_006bc860);
        for (u32 i = 0, p = source + 12, destination = f + 4; i < 16;
             ++i, p += 16, destination += 16) {
            const u32 red = word(p - 12), offset = i << 2;
            load(f + 256 + offset);
            put(destination - 4, red);
            add(p);
            put(destination, word(p - 8));
            const u32 blue = word(p - 4);
            store(f + 328);
            put(destination + 4, blue);
            add(half);
            store_pop(args + 4);
            load(args + 4);
            integer_store(f + 324);
            put(args + 4, word(f + 324));
            integer_load(args + 4);
            put(args + 4, i);
            and_three(args + 4);
            const bool last_column = word(args + 4) == 3u;
            store(normalized_delta + p);
            subtract_reverse(f + 328);
            if (!last_column) {
                load(address(&dat_006f0104));
                multiply1();
                add_store(f + 260 + offset);
            }
            if (i >= 12u)
                pop();
            else {
                if (word(args + 4) != 0) {
                    load(address(&dat_006df41c));
                    multiply1();
                    add_store(f + 268 + offset);
                }
                const bool last = word(args + 4) == 3u;
                load(address(&dat_006df418));
                multiply1();
                add_store(f + 272 + offset);
                if (last)
                    pop();
                else {
                    multiply(address(&dat_006be980));
                    add_store(f + 276 + offset);
                }
            }
        }
        load_control(f + 320);
        input = f;
    } else
        input = word(args + 4);
    const u32 result = color_dxt1(f, input).eax;
    return result & 0x80000000u ? result : 0u;
}

// Complete00650e9c..00650fcb:108 instructions,303 bytes.
// f=entrySP-84, original80B private view; args=f+88. Actual output argument
// receives FNSTCW lowWORD and later each alpha. Cached output remains live.
extern "C" u32 recovered_00650e9c(u32 args, u32 f) {
    const u32 output = word(args);
    const bool dither = word(args + 8) != 0;
    put(output, 0);
    put(output + 4, 0);
    if (dither)
        clear_sixteen(f);
    save_control(args);
    put(f + 76, word(args) | 0x0c00u);
    load_control(f + 76);
    put(f + 64, word(args));
    put(f + 76, word(args + 4) + 12u);
    const u32 half = address(dat_006bc860);
    for (u32 i = 0; i < 16; ++i) {
        const bool dither_sample = word(args + 8) != 0;
        const u32 p = word(f + 76);
        put(args, word(p));
        if (dither_sample) {
            load(args);
            add(f + 4 * i);
            store_pop(args);
        }
        load(args);
        multiply(address(&dat_006bc894));
        add(half);
        store_pop(f + 72);
        load(f + 72);
        integer_store(f + 68);
        const u32 index = word(f + 68), destination = output + 4 * (i >> 3);
        const u32 packed = (word(destination) >> 4) | (index << 28);
        const bool dither_error = word(args + 8) != 0;
        put(destination, packed);
        if (dither_error) {
            put(f + 72, index);
            integer_load(f + 72);
            if (index & 0x80000000u)
                add(address(dat_006bb60c));
            multiply(address(&dat_006c0c2c));
            const u32 column = i & 3u;
            subtract_reverse(args);
            if (column != 3u) {
                load(address(&dat_006f0104));
                multiply1();
                add_store(f + 4 * i + 4);
            }
            if (i >= 12u)
                pop();
            else {
                if (column != 0u) {
                    load(address(&dat_006df41c));
                    multiply1();
                    add_store(f + 4 * i + 12);
                }
                load(address(&dat_006df418));
                multiply1();
                add_store(f + 4 * i + 16);
                if (column == 3u)
                    pop();
                else {
                    multiply(address(&dat_006be980));
                    add_store(f + 4 * i + 20);
                }
            }
        }
        add_sixteen(f + 76);
    }
    load_control(f + 64);
    return color_dxt3(f, output).eax;
}
extern "C" __attribute__((naked, stdcall)) u32 FUN_00650d78(void*, const void*, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $332,%esp\n\tmovl %esp,%eax\n\tsubl $8192,%esp\n\tpushl %eax\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_00650d78\n\taddl $8,%esp\n\tleave\n\tretl $12");
}
extern "C" __attribute__((naked, stdcall)) u32 FUN_00650e9c(void*, const void*, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $80,%esp\n\tmovl %esp,%eax\n\tsubl $8192,%esp\n\tpushl %eax\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_00650e9c\n\taddl $8,%esp\n\tleave\n\tretl $12");
}
