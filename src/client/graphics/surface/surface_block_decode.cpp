#include "graphics/surface/surface_block_decode.h"
#include "graphics/surface/surface_block_codec_helpers.h"
#include "graphics/render_project_unproject.h"
#include "graphics/surface/surface_tenbit_reader.h"
#include "graphics/surface/surface_nibble_readers.h"
#include "graphics/surface/surface_format_palette.h"
#include "graphics/surface/surface_word_packed_readers.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 half(u32 p) {
    u32 v;
    __asm__ volatile("movzwl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 byte(u32 p) {
    u32 v;
    __asm__ volatile("movzbl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
void endpoint(u32 output, u32 color) {
    __asm__ volatile("calll _FUN_0064f674"
                     : "+a"(output), "+c"(color)::"edx", "st", "st(1)", "memory", "cc");
}
void pop() {
    __asm__ volatile("fstp %%st(0)" ::: "st", "memory");
}
void zero(u32 p) {
    __asm__ volatile("fldz\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void one(u32 p) {
    __asm__ volatile("fld1\n\tfstps (%0)" ::"r"(p) : "st", "memory");
}
void load_half() {
    __asm__ volatile("flds %0" ::"m"(dat_006bc860[0]) : "st", "memory");
}
void midpoint(u32 a, u32 b, u32 out) {
    __asm__ volatile(
        "flds (%1)\n\tfsubs (%0)\n\tfmul %%st(1),%%st(0)\n\tfadds (%0)\n\tfstps (%2)" ::"r"(a),
        "r"(b), "r"(out)
        : "st", "memory");
}
void thirds_begin(u32 first, u32 second, u32 output) {
    __asm__ volatile(
        "flds (%1)\n\tfsubs (%0)\n\tflds %3\n\tfld %%st(1)\n\tfmul %%st(1),%%st(0)\n\tfadds (%0)\n\tfstps (%2)" ::
            "r"(first),
        "r"(second), "r"(output), "m"(dat_006c2bb4)
        : "st", "st(1)", "st(2)", "memory");
}
void third_channel(u32 first, u32 second, u32 scratch, u32 output) {
    __asm__ volatile(
        "flds (%1)\n\tfsubs (%0)\n\tfsts (%2)\n\tfmul %%st(1),%%st(0)\n\tfadds (%0)\n\tfstps (%3)" ::
            "r"(first),
        "r"(second), "r"(scratch), "r"(output)
        : "st", "memory");
}
void thirds_second_begin(u32 first, u32 output) {
    __asm__ volatile(
        "flds %2\n\tfld %%st(1)\n\tfmul %%st(1),%%st(0)\n\tfadds (%0)\n\tfstps (%1)" ::"r"(first),
        "r"(output), "m"(dat_006f00e4)
        : "st", "st(1)", "memory");
}
void second_channel(u32 first, u32 delta, u32 output) {
    __asm__ volatile("flds (%1)\n\tfmul %%st(1),%%st(0)\n\tfadds (%0)\n\tfstps (%2)" ::"r"(first),
                     "r"(delta), "r"(output)
                     : "st", "memory");
}
void nibble_scale() {
    __asm__ volatile("flds %0" ::"m"(dat_006c0c2c) : "st", "memory");
}
void scaled_integer(u32 scratch, u32 output) {
    __asm__ volatile("fildl (%0)\n\tfmul %%st(1),%%st(0)\n\tfstps (%1)" ::"r"(scratch), "r"(output)
                     : "st", "memory");
}
void alpha_begin() {
    __asm__ volatile("flds %0" ::"m"(dat_006be1d0) : "st", "memory");
}
void alpha_pair(u32 scratch, u32 second, u32 frame) {
    __asm__ volatile("fildl (%0)" ::"r"(scratch) : "st", "memory");
    put(scratch, second);
    __asm__ volatile(
        "fmul %%st(1),%%st(0)\n\tfstps (%1)\n\tfildl (%0)\n\tfmul %%st(1),%%st(0)\n\tfstps 4(%1)\n\tfstp %%st(0)" ::
            "r"(scratch),
        "r"(frame)
        : "st", "memory");
}
void weighted_alpha(u32 scratch, u32 left, u32 right, u32 first, u32 second, u32 factor,
                    u32 output) {
    put(scratch, left);
    __asm__ volatile("fildl (%0)\n\tfmuls (%1)" ::"r"(scratch), "r"(first) : "st", "memory");
    put(scratch, right);
    __asm__ volatile(
        "fildl (%0)\n\tfmuls (%1)\n\tfaddp %%st,%%st(1)\n\tfmuls (%2)\n\tfstps (%3)" ::"r"(scratch),
        "r"(second), "r"(factor), "r"(output)
        : "st", "st(1)", "memory");
}
void copy_alpha(u32 source, u32 output) {
    __asm__ volatile("flds (%0)\n\tfstps (%1)" ::"r"(source), "r"(output) : "st", "memory");
}
} // namespace
// Complete650a73..650bb5. The88B original private view is reserved by
// the entry adapter before any C++ stack use; actual incomingword1 is
// overwritten by the original first color-difference FST and read back.
extern "C" u32 recovered_00650a73(u32 args, u32 frame) {
    const u32 block = word(args + 4), first = half(block);
    endpoint(frame, first);
    const u32 second = half(block + 2);
    endpoint(frame + 16, second);
    if (first <= second) {
        load_half();
        for (u32 i = 0; i < 4; ++i)
            midpoint(frame + 4 * i, frame + 16 + 4 * i, frame + 32 + 4 * i);
        pop();
        for (u32 i = 0; i < 4; ++i)
            zero(frame + 64 + 4 * i);
        for (u32 i = 0; i < 4; ++i)
            put(frame + 48 + 4 * i, word(frame + 64 + 4 * i));
    } else {
        thirds_begin(frame, frame + 16, frame + 32);
        third_channel(frame + 4, frame + 20, args + 4, frame + 36);
        third_channel(frame + 8, frame + 24, frame + 84, frame + 40);
        third_channel(frame + 12, frame + 28, frame + 80, frame + 44);
        pop();
        thirds_second_begin(frame, frame + 48);
        second_channel(frame + 4, args + 4, frame + 52);
        second_channel(frame + 8, frame + 84, frame + 56);
        second_channel(frame + 12, frame + 80, frame + 60);
        pop();
        pop();
    }
    u32 selectors = word(block + 4), output = word(args), last = 0;
    for (u32 i = 0; i < 16; ++i) {
        last = (selectors & 3u) * 16u;
        for (u32 j = 0; j < 4; ++j)
            put(output + 4 * j, word(frame + last + 4 * j));
        output += 16;
        selectors >>= 2;
    }
    return last;
}
extern "C" __attribute__((naked, stdcall)) u32 FUN_00650a73(void*, const void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $88,%esp\n\tmovl %esp,%eax\n\tpushl %eax\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_00650a73\n\taddl $8,%esp\n\tmovl %eax,%edx\n\tmovl $0,%ecx\n\txorl %eax,%eax\n\tleave\n\tretl $8");
}
// Complete650bb5..650c3a: both alpha DWORDs are loaded separately,
// with the second load delayed until eight actual alpha stores return.
extern "C" u32 recovered_00650bb5(u32 args, u32 result) {
    const u32 block = word(args + 4), output = word(args);
    const u32 value =
        FUN_00650a73(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(block + 8));
    if (static_cast<int32_t>(value) < 0) {
        put(result, value);
        return 0;
    }
    u32 fields = word(block), last = 0;
    nibble_scale();
    for (u32 i = 0; i < 8; ++i) {
        last = fields & 15u;
        put(args + 4, last);
        scaled_integer(args + 4, output + 12 + 16 * i);
        fields >>= 4;
    }
    fields = word(block + 4);
    for (u32 i = 0; i < 8; ++i) {
        last = fields & 15u;
        put(args + 4, last);
        scaled_integer(args + 4, output + 140 + 16 * i);
        fields >>= 4;
    }
    pop();
    put(result, 0);
    return last;
}
extern "C" __attribute__((naked, stdcall)) u32 FUN_00650bb5(void*, const void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $4,%esp\n\tmovl %esp,%eax\n\tpushl %eax\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_00650bb5\n\taddl $8,%esp\n\tmovl %eax,%edx\n\tmovl -4(%ebp),%eax\n\tmovl $0,%ecx\n\ttestl %eax,%eax\n\tjs 1f\n\txorl %eax,%eax\n\t1: leave\n\tretl $8");
}
// Complete650c3a..650d78. ActualBYTE selector order is2,4,3 then5,7,6;
// all eight private table words come from the original weighted sequence.
extern "C" u32 recovered_00650c3a(u32 args, u32 frame) {
    const u32 block = word(args + 4), output = word(args);
    const u32 value =
        FUN_00650a73(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(block + 8));
    if (static_cast<int32_t>(value) < 0)
        return value;
    const u32 first = byte(block);
    alpha_begin();
    put(args + 4, first);
    const u32 second = byte(block + 1);
    alpha_pair(args + 4, second, frame);
    if (first > second) {
        for (u32 i = 1; i < 7; ++i)
            weighted_alpha(args + 4, 7 - i, i, frame, frame + 4,
                           reinterpret_cast<u32>(&dat_006df420), frame + 4 * (i + 1));
    } else {
        for (u32 i = 1; i < 5; ++i)
            weighted_alpha(args + 4, 5 - i, i, frame, frame + 4,
                           reinterpret_cast<u32>(&dat_006be7fc), frame + 4 * (i + 1));
        zero(frame + 24);
        one(frame + 28);
    }
    u32 lo = byte(block + 2), hi = byte(block + 4), mid = byte(block + 3),
        fields = (hi << 16) | (mid << 8) | lo;
    for (u32 i = 0; i < 8; ++i) {
        copy_alpha(frame + 4 * (fields & 7u), output + 12 + 16 * i);
        fields >>= 3;
    }
    lo = byte(block + 5);
    hi = byte(block + 7);
    mid = byte(block + 6);
    fields = (hi << 16) | (mid << 8) | lo;
    for (u32 i = 0; i < 8; ++i) {
        copy_alpha(frame + 4 * (fields & 7u), output + 140 + 16 * i);
        fields >>= 3;
    }
    return 0;
}
extern "C" __attribute__((naked, stdcall)) u32 FUN_00650c3a(void*, const void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tsubl $32,%esp\n\tmovl %esp,%eax\n\tpushl %eax\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _recovered_00650c3a\n\taddl $8,%esp\n\tmovl $0,%ecx\n\tmovl $0,%edx\n\ttestl %eax,%eax\n\tjs 1f\n\txorl %eax,%eax\n\t1: leave\n\tretl $8");
}
extern "C" {
extern const uint32_t dat_006f00e4 = 0x3f2aaaabu;
extern const uint32_t dat_006be7fc = 0x3e4ccccdu;
}
