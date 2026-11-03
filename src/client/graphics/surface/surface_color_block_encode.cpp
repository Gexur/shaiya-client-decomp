#include "graphics/surface/surface_color_block_encode.h"
#include "graphics/surface/surface_color_endpoints.h"
#include "graphics/surface/surface_block_quantize.h"
#include "graphics/surface/surface_block_codec_helpers.h"
#include "graphics/surface/surface_basic_readers.h"
#include "graphics/surface/surface_block_decode.h"
#include "graphics/surface/surface_write_rgb24.h"
#include "graphics/surface/surface_tenbit_reader.h"
#include "graphics/render_project_unproject.h"
#include "graphics/render_packed_trig_quaternions.h"

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
inline u32 halfword(u32 p) {
    u32 v;
    __asm__ volatile("movzwl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
inline void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
inline void put_half(u32 p, u32 v) {
    __asm__ volatile("movw %w1,(%0)" ::"r"(p), "r"(v) : "memory");
}
inline void increment(u32 p) {
    __asm__ volatile("incl (%0)" ::"r"(p) : "memory", "cc");
}
inline void add_sixteen(u32 p) {
    __asm__ volatile("addl $16,(%0)" ::"r"(p) : "memory", "cc");
}
inline void or_all_half(u32 p) {
    __asm__ volatile("orw $-1,(%0)" ::"r"(p) : "memory", "cc");
}
inline void or_all_word(u32 p) {
    __asm__ volatile("orl $-1,(%0)" ::"r"(p) : "memory", "cc");
}
inline void clear_word(u32 p) {
    __asm__ volatile("andl $0,(%0)" ::"r"(p) : "memory", "cc");
}
inline void copy16(u32 source, u32 destination) {
    __asm__ volatile("movsl\n\tmovsl\n\tmovsl\n\tmovsl"
                     : "+S"(source), "+D"(destination)::"memory");
}
inline void clear_errors(u32 f) {
    u32 destination = f + 256, count = 64;
    __asm__ volatile("rep stosl" : "+D"(destination), "+c"(count) : "a"(0) : "memory");
}
// These helpers are fixed literal x87 operations, with no host floating values.
inline void load(u32 p) {
    __asm__ volatile("flds (%0)" ::"r"(p) : "st", "memory");
}
inline void load_zero() {
    __asm__ volatile("fldz" ::: "st", "memory");
}
inline void load_one() {
    __asm__ volatile("fld1" ::: "st", "memory");
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
inline void subtract(u32 p) {
    __asm__ volatile("fsubs (%0)" ::"r"(p) : "st", "memory");
}
inline void multiply(u32 p) {
    __asm__ volatile("fmuls (%0)" ::"r"(p) : "st", "memory");
}
inline void divide_reverse(u32 p) {
    __asm__ volatile("fdivrs (%0)" ::"r"(p) : "st", "memory");
}
inline void add_store(u32 p) {
    add(p);
    store_pop(p);
}
inline void pop() {
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
}
inline void duplicate0() {
    __asm__ volatile(".byte 0xd9,0xc0" ::: "st", "memory");
}
inline void duplicate1() {
    __asm__ volatile(".byte 0xd9,0xc1" ::: "st", "memory");
}
inline void duplicate2() {
    __asm__ volatile(".byte 0xd9,0xc2" ::: "st", "memory");
}
inline void duplicate3() {
    __asm__ volatile(".byte 0xd9,0xc3" ::: "st", "memory");
}
inline void duplicate4() {
    __asm__ volatile(".byte 0xd9,0xc4" ::: "st", "memory");
}
inline void multiply1() {
    __asm__ volatile(".byte 0xd8,0xc9" ::: "st", "memory");
}
inline void multiply2() {
    __asm__ volatile(".byte 0xd8,0xca" ::: "st", "memory");
}
inline void multiply3() {
    __asm__ volatile(".byte 0xd8,0xcb" ::: "st", "memory");
}
inline void subtract3() {
    __asm__ volatile(".byte 0xd8,0xe3" ::: "st", "memory");
}
inline void add_pop1() {
    __asm__ volatile(".byte 0xde,0xc1" ::: "st", "st(1)", "memory");
}
inline void store_register1() {
    __asm__ volatile(".byte 0xdd,0xd1" ::: "st", "st(1)", "memory");
}
inline void save_control(u32 p) {
    __asm__ volatile("fnstcw (%0)" ::"r"(p) : "memory");
}
inline void load_control(u32 p) {
    __asm__ volatile("fldcw (%0)" ::"r"(p) : "memory");
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
inline bool even05(u32 s) {
    s = (s >> 8) & 5u;
    return s == 0u || s == 5u;
}
inline bool even41(u32 s) {
    s = (s >> 8) & 0x41u;
    return s == 0u || s == 0x41u;
}
struct Gpr {
    u32 eax, ecx, edx;
};
// C++ runs below a separate unwritten gap. Each bridge temporarily uses the
// original caller ESP=f-12, retaining actual outgoing arguments and callee
// private-byte reuse. ESI retains compiler ESP and every real callee saves it.
inline Gpr optimize(u32 f) {
    Gpr r;
    __asm__ volatile(
        "movl %%esp,%%esi\n\tleal -12(%%edi),%%esp\n\tpushl 696(%%edi)\n\tpushl %%edi\n\t"
        "leal 652(%%edi),%%eax\n\tpushl %%eax\n\tleal 708(%%edi),%%eax\n\tpushl %%eax\n\t"
        "calll _FUN_0064fba0@16\n\tmovl %%esi,%%esp"
        : "=a"(r.eax), "=c"(r.ecx), "=d"(r.edx)
        : "D"(f)
        : "esi", "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory",
          "cc");
    return r;
}
inline Gpr quantize(u32 f, Gpr r) {
    __asm__ volatile(
        "movl %%esp,%%esi\n\tleal -12(%%edi),%%esp\n\tcalll _FUN_0064f776\n\tmovl %%esi,%%esp"
        : "+a"(r.eax), "+c"(r.ecx), "+d"(r.edx)
        : "D"(f)
        : "esi", "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory",
          "cc");
    return r;
}
inline Gpr unpack(u32 f, Gpr r) {
    __asm__ volatile(
        "movl %%esp,%%esi\n\tleal -12(%%edi),%%esp\n\tcalll _FUN_0064f674\n\tmovl %%esi,%%esp"
        : "+a"(r.eax), "+c"(r.ecx), "+d"(r.edx)
        : "D"(f)
        : "esi", "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory",
          "cc");
    return r;
}
} // namespace

// Complete00650120..00650a73:711 instructions,2387 bytes, five real calls.
// f=original entrySP-736; the original732B view remains actual inherited memory.
extern "C" u32 recovered_00650120(u32 input, u32 args, u32 f) {
    const u32 half = address(dat_006bc860), weight = address(dat_00716910);
    if (word(args + 4) != 0) {
        u32 transparent = 0;
        for (u32 p = input + 12, n = 16; n; --n, p += 16)
            if (!even05(compare(p, half)))
                ++transparent;
        if (transparent == 16) {
            const u32 out = word(args);
            or_all_half(out + 2);
            or_all_word(out + 4);
            put_half(out, 0);
            return 0;
        }
        put(f + 696, transparent ? 3u : 4u);
    } else
        put(f + 696, 4);
    if (word(args + 8) != 0)
        clear_errors(f);
    save_control(args + 4);
    put(f + 684, word(args + 4) | 0x0c00u);
    load_control(f + 684);
    put(f + 552, f + 256 - input);
    put(f + 636, f + 4 - input);
    put(f + 648, f + 264 - input);
    put(f + 544, f + 268 - input);
    put(f + 556, f + 272 - input);
    put(f + 640, f + 296 - input);
    const u32 saved = word(args + 4);
    put(f + 548, f + 300 - input);
    put(f + 560, f + 304 - input);
    put(f + 692, f + 312 - input);
    put(f + 700, f + 328 - input);
    put(f + 564, f + 332 - input);
    put(f + 684, f + 336 - input);
    put(f + 644, saved);
    put(f + 688, f - input);
    put(args + 4, 0);
    const u32 down_green = f + 316 - input, down_blue = f + 320 - input;
    put(f + 512, down_green);
    put(f + 536, down_blue);
    for (u32 p = input + 8, offset = 0; offset < 256; p += 16) {
        const bool dither_input = word(args + 8) != 0;
        put(f + 708, word(p - 8));
        put(f + 712, word(p - 4));
        put(f + 716, word(p));
        if (dither_input) {
            load(f + 708);
            const u32 delta = word(f + 552);
            add(f + 256 + offset);
            store_pop(f + 708);
            load(f + 712);
            add(f + 260 + offset);
            store_pop(f + 712);
            load(f + 716);
            add(p + delta);
            store_pop(f + 716);
        }
        load(f + 708);
        multiply(address(&dat_006c651c));
        add(half);
        store_pop(f + 728);
        load(f + 728);
        integer_store(f + 532);
        put(f + 728, word(f + 532));
        integer_load(f + 728);
        multiply(address(&dat_006c4be8));
        store(f + 704);
        store_pop(f + offset);
        load(f + 712);
        multiply(address(&dat_006df408));
        add(half);
        store_pop(f + 728);
        load(f + 728);
        integer_store(f + 540);
        put(f + 728, word(f + 540));
        integer_load(f + 728);
        multiply(address(&dat_006df404));
        store(f + 728);
        store_pop(f + offset + 4);
        load(f + 716);
        multiply(address(&dat_006c651c));
        add(half);
        store_pop(f + 724);
        load(f + 724);
        integer_store(f + 632);
        const bool dither_error = word(args + 8) != 0;
        put(f + 724, word(f + 632));
        integer_load(f + 724);
        const u32 normalized_delta = word(f + 688);
        multiply(address(&dat_006c4be8));
        duplicate0();
        store_pop(p + normalized_delta);
        const u32 alpha_delta = word(f + 636);
        load_one();
        store_pop(p + alpha_delta);
        if (dither_error) {
            load(f + 708);
            const u32 column = word(args + 4) & 3u;
            subtract(f + 704);
            load(f + 712);
            subtract(f + 728);
            put(f + 724, column);
            store(f + 672);
            load(f + 716);
            subtract3();
            store(f + 676);
            if (column != 3) {
                load(address(&dat_006f0104));
                u32 target = word(f + 648) + p;
                duplicate3();
                multiply1();
                add_store(target);
                target = word(f + 544) + p;
                duplicate2();
                multiply1();
                add_store(target);
                target = word(f + 556) + p;
                duplicate1();
                multiply1();
                add_store(target);
                pop();
            }
            if (offset >= 192) {
                pop();
                pop();
                pop();
            } else {
                if (word(f + 724) != 0) {
                    load(address(&dat_006df41c));
                    u32 target = word(f + 640) + p;
                    duplicate3();
                    multiply1();
                    add_store(target);
                    target = word(f + 548) + p;
                    duplicate2();
                    multiply1();
                    add_store(target);
                    target = word(f + 560) + p;
                    duplicate1();
                    multiply1();
                    add_store(target);
                    pop();
                }
                load(address(&dat_006df418));
                const u32 target = word(f + 692) + p;
                duplicate3();
                const bool last_column = word(f + 724) == 3;
                multiply1();
                add_store(target);
                duplicate2();
                multiply1();
                add_store(down_green + p);
                duplicate1();
                multiply1();
                add_store(down_blue + p);
                pop();
                pop();
                pop();
                if (last_column)
                    pop();
                else {
                    multiply(address(&dat_006be980));
                    u32 destination = word(f + 700) + p;
                    add_store(destination);
                    destination = word(f + 564) + p;
                    load(f + 672);
                    multiply(address(&dat_006be980));
                    add_store(destination);
                    destination = word(f + 684) + p;
                    load(f + 676);
                    multiply(address(&dat_006be980));
                    add_store(destination);
                }
            }
        }
        load(f + 704);
        const u32 normalized = word(f + 688);
        multiply(weight);
        increment(args + 4);
        offset += 16;
        store_pop(f + offset - 16);
        load(f + 728);
        multiply(weight + 4);
        store_pop(f + offset - 12);
        multiply(weight + 8);
        store_pop(p + normalized);
    }
    load_control(f + 644);
    Gpr gpr = optimize(f);
    const u32 reciprocal = address(dat_00716920);
    load(reciprocal);
    load(f + 708);
    gpr.ecx = f + 516;
    multiply1();
    store_pop(f + 516);
    load(reciprocal + 4);
    load(f + 712);
    multiply1();
    store_pop(f + 520);
    load(f + 716);
    multiply(reciprocal + 8);
    store_pop(f + 524);
    load(f + 652);
    multiply2();
    store_pop(f + 668);
    load(f + 656);
    multiply1();
    store_pop(f + 672);
    pop();
    pop();
    load(f + 660);
    multiply(reciprocal + 8);
    store_pop(f + 676);
    gpr = quantize(f, gpr);
    const u32 first = gpr.eax;
    put(f + 692, first);
    gpr.ecx = f + 668;
    gpr = quantize(f, gpr);
    const u32 second = gpr.eax;
    const bool four_levels = word(f + 696) == 4u;
    put(f + 700, second);
    if (four_levels && static_cast<uint16_t>(first) == static_cast<uint16_t>(second)) {
        const u32 out = word(args);
        clear_word(out + 4);
        put_half(out, first);
        put_half(out + 2, second);
        return 0;
    }
    gpr.ecx = first;
    gpr.eax = f + 516;
    gpr = unpack(f, gpr);
    gpr.ecx = second;
    gpr.eax = f + 668;
    gpr = unpack(f, gpr);
    load(weight);
    load(f + 516);
    const u32 descending = static_cast<uint16_t>(second) < static_cast<uint16_t>(first) ? 0u : 1u;
    multiply1();
    store_pop(f + 708);
    const u32 three_levels = word(f + 696) == 3u ? 1u : 0u;
    load(weight + 4);
    load(f + 520);
    multiply1();
    store_pop(f + 712);
    load(f + 524);
    multiply(weight + 8);
    const u32 output = word(args);
    store_pop(f + 716);
    load(f + 668);
    multiply2();
    store_pop(f + 652);
    load(f + 672);
    multiply1();
    store_pop(f + 656);
    pop();
    pop();
    load(f + 676);
    multiply(weight + 8);
    store_pop(f + 660);
    u32 second_source;
    if (three_levels == descending) {
        put_half(output, first);
        put_half(output + 2, second);
        copy16(f + 708, f + 568);
        second_source = f + 652;
    } else {
        put_half(output + 2, first);
        put_half(output, second);
        copy16(f + 652, f + 568);
        second_source = f + 708;
    }
    const u32 levels = word(f + 696);
    copy16(second_source, f + 584);
    load(f + 584);
    subtract(f + 568);
    if (levels == 3u) {
        load(half);
        put(f + 728, address(dat_006f00f8));
        multiply1();
        add(f + 568);
        store_pop(f + 600);
        load(f + 588);
        subtract(f + 572);
        load(half);
        duplicate1();
        multiply1();
        add(f + 572);
        store_pop(f + 604);
        load(f + 592);
        subtract(f + 576);
        store(args + 4);
        multiply1();
        add(f + 576);
        store_pop(f + 608);
        load(f + 596);
        subtract(f + 580);
        multiply1();
        add(f + 580);
        store_pop(f + 612);
    } else {
        const u32 third = address(&dat_006c2bb4);
        load(third);
        put(f + 728, address(dat_006f00e8));
        multiply1();
        add(f + 568);
        store_pop(f + 600);
        load(f + 588);
        subtract(f + 572);
        load(third);
        multiply1();
        add(f + 572);
        store_pop(f + 604);
        load(f + 592);
        subtract(f + 576);
        store(args + 4);
        load(third);
        multiply1();
        add(f + 576);
        store_pop(f + 608);
        load(f + 596);
        subtract(f + 580);
        load(third);
        multiply1();
        add(f + 580);
        store_pop(f + 612);
        load(address(&dat_006f00e4));
        duplicate4();
        multiply1();
        add(f + 568);
        store_pop(f + 616);
        duplicate3();
        multiply1();
        add(f + 572);
        store_pop(f + 620);
        duplicate2();
        multiply1();
        add(f + 576);
        store_pop(f + 624);
        duplicate1();
        multiply1();
        add(f + 580);
        store_pop(f + 628);
        pop();
        pop();
    }
    pop();
    const u32 last = levels - 1u;
    duplicate1();
    store_pop(f + 652);
    store_register1();
    pop();
    load(args + 4);
    put(args + 4, last);
    integer_load(args + 4);
    if (last & 0x80000000u)
        add(address(dat_006bb60c));
    const u32 second_word = halfword(f + 700);
    store_pop(f + 688);
    const bool unequal = halfword(f + 692) != second_word;
    if (unequal) {
        duplicate0();
        multiply1();
        duplicate2();
        multiply3();
        add_pop1();
        load(f + 652);
        multiply(f + 652);
        add_pop1();
        divide_reverse(f + 688);
    } else
        load_zero();
    load(f + 652);
    const bool dither_indices = word(args + 8) != 0;
    multiply1();
    put(f + 704, 0);
    store_pop(f + 652);
    duplicate0();
    multiply3();
    store_pop(f + 656);
    multiply1();
    store_pop(f + 660);
    pop();
    pop();
    if (dither_indices)
        clear_errors(f);
    save_control(args + 4);
    put(f + 700, word(args + 4) | 0x0c00u);
    load_control(f + 700);
    put(f + 644, word(args + 4));
    put(f + 724, f + 256);
    put(f + 648, f + 276 - input);
    put(args + 4, 0);
    put(f + 636, f + 308 - input);
    const u32 alpha_multiplier = f + 8 - input, following_blue = f + 324 - input;
    u32 error_green = f + 260 - input;
    put(f + 700, error_green);
    put(f + 632, f + 340 - input);
    for (u32 p = input + 4;; p += 16) {
        if (word(f + 696) == 3u && !even05(compare(p + 8, half))) {
            put(f + 704, (word(f + 704) >> 2) | 0xc0000000u);
        } else {
            const bool dither_sample = word(args + 8) != 0;
            load(weight);
            multiply(p - 4);
            store_pop(f + 708);
            load(weight + 4);
            multiply(p);
            store_pop(f + 712);
            load(weight + 8);
            multiply(p + 4);
            store_pop(f + 716);
            if (dither_sample) {
                load(f + 708);
                const u32 error = word(f + 724);
                add(error);
                const u32 delta = word(f + 552);
                store_pop(f + 708);
                load(f + 712);
                add(p + delta);
                store_pop(f + 712);
                load(f + 716);
                add(p + error_green);
                store_pop(f + 716);
            }
            load(f + 716);
            subtract(f + 576);
            multiply(f + 660);
            load(f + 712);
            subtract(f + 572);
            multiply(f + 656);
            add_pop1();
            load(f + 708);
            subtract(f + 568);
            multiply(f + 652);
            add_pop1();
            u32 index;
            if (!even41(compare_live(address(dat_006bb5fc)))) {
                pop();
                index = 0;
            } else if ((compare_live(f + 688) & 0x0100u) == 0) {
                pop();
                index = 1;
            } else {
                add(half);
                store_pop(f + 692);
                load(f + 692);
                integer_store(f + 640);
                index = word(f + 640);
                const u32 table = word(f + 728);
                index = word(table + 4 * index);
            }
            const u32 bits = (index << 30) | (word(f + 704) >> 2);
            const bool dither_error = word(args + 8) != 0;
            put(f + 704, bits);
            if (dither_error) {
                load(f + 708);
                const u32 column = word(args + 4) & 3u;
                subtract(f + 568 + (index << 4));
                multiply(alpha_multiplier + p);
                load(f + 712);
                subtract(f + 572 + (index << 4));
                multiply(alpha_multiplier + p);
                store(f + 672);
                load(f + 716);
                subtract(f + 576 + (index << 4));
                multiply(alpha_multiplier + p);
                store_pop(f + 676);
                if (column != 3) {
                    u32 target = word(f + 544) + p;
                    duplicate1();
                    multiply(address(&dat_006f0104));
                    add_store(target);
                    target = word(f + 556) + p;
                    load(address(&dat_006f0104));
                    multiply1();
                    add_store(target);
                    target = word(f + 648) + p;
                    load(f + 676);
                    multiply(address(&dat_006f0104));
                    add_store(target);
                }
                if (word(args + 4) >= 12u) {
                    pop();
                    pop();
                } else {
                    if (column != 0) {
                        u32 target = word(f + 548) + p;
                        duplicate1();
                        multiply(address(&dat_006df41c));
                        add_store(target);
                        target = word(f + 560) + p;
                        load(address(&dat_006df41c));
                        multiply1();
                        add_store(target);
                        target = word(f + 636) + p;
                        load(f + 676);
                        multiply(address(&dat_006df41c));
                        add_store(target);
                    }
                    u32 target = word(f + 512) + p;
                    duplicate1();
                    multiply(address(&dat_006df418));
                    add_store(target);
                    target = word(f + 536) + p;
                    multiply(address(&dat_006df418));
                    add_store(target);
                    load(f + 676);
                    multiply(address(&dat_006df418));
                    add_store(following_blue + p);
                    if (column == 3)
                        pop();
                    else {
                        multiply(address(&dat_006be980));
                        target = word(f + 564) + p;
                        add_store(target);
                        target = word(f + 684) + p;
                        load(f + 672);
                        multiply(address(&dat_006be980));
                        add_store(target);
                        target = word(f + 632) + p;
                        load(f + 676);
                        multiply(address(&dat_006be980));
                        add_store(target);
                    }
                }
            }
        }
        increment(args + 4);
        add_sixteen(f + 724);
        if (word(args + 4) >= 16u)
            break;
        error_green = word(f + 700);
    }
    load_control(f + 644);
    const u32 bits = word(f + 704), out = word(args);
    put(out + 4, bits);
    return 0;
}
extern "C" __attribute__((naked, stdcall)) u32 FUN_00650120(void*, u32, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $732,%esp\n\tmovl %esp,%edx\n\tsubl $4096,%esp\n\tpushl %edx\n\tleal 8(%ebp),%edx\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_00650120\n\taddl $12,%esp\n\tleave\n\tretl $12");
}
extern "C" {
extern const uint32_t dat_006f00e8[4] = {0, 2, 3, 1};
extern const uint32_t dat_006f00f8[3] = {0, 2, 1};
extern const uint32_t dat_006f0104 = 0x3ee00000u;
uint32_t dat_00716920[3] = {0x4057762eu, 0x3f800000u, 0x411ec1ddu};
}
