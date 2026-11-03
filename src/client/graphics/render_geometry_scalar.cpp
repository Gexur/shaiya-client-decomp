#include "graphics/render_geometry_scalar.h"
#include "graphics/render_transform_coord_dispatch.h"
#include "graphics/render_transform_baseline.h"
#include "runtime/x87_convert64.h"
extern "C" {
extern const uint32_t dat_006bb5fc[], dat_006bb60c[], dat_006c2bb4;
extern const float dat_006bfe14;
extern const uint32_t dat_006df780 = 0x3e2aaa7eu;
extern const uint32_t dat_006bca1c = 0x40400000u;
extern const uint32_t dat_006bc9b8 = 0x40c00000u;
}
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
uint8_t byte(u32 p) {
    uint8_t v;
    __asm__ volatile("movb (%1),%0" : "=q"(v) : "r"(p) : "memory");
    return v;
}
void put_byte(u32 p, uint8_t v) {
    __asm__ volatile("movb %1,(%0)" ::"r"(p), "q"(v) : "memory");
}
void copy(u32 output, u32 input, u32 bytes) {
    for (u32 n = bytes >> 2; n; --n, input += 4, output += 4)
        put(output, word(input));
    for (u32 n = bytes & 3; n; --n, ++input, ++output)
        put_byte(output, byte(input));
}
void clear(u32 output, u32 bytes) {
    for (u32 n = bytes >> 2; n; --n, output += 4)
        put(output, 0);
    for (u32 n = bytes & 3; n; --n, ++output)
        put_byte(output, 0);
}
void zero(u32 output) {
    __asm__ volatile("fldz\n\tfstps (%0)" ::"r"(output) : "st", "memory");
}
bool weight_present(u32 input) {
    uint16_t status;
    __asm__ volatile("flds (%1)\n\tfcomps %2\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "r"(input), "m"(dat_006bb5fc[0])
                     : "st", "memory");
    return (status & 0x100u) == 0;
}
u32 fraction(u32 input, u32 output) {
    u32 low, high;
    __asm__ volatile("flds (%2)\n\tcalll _FUN_005d0bc4"
                     : "=a"(low), "=d"(high)
                     : "r"(input)
                     : "ecx", "st", "memory", "cc");
    const u32 index = low >> 1;
    put(output, index * 2);
    __asm__ volatile("fildl (%0)" ::"r"(output) : "st", "memory");
    if (static_cast<int32_t>(index * 2) < 0)
        __asm__ volatile("fadds %0" ::"m"(dat_006bb60c[0]) : "st", "memory");
    __asm__ volatile("fsubrs (%0)\n\tfstps (%1)" ::"r"(input), "r"(output) : "st", "memory");
    return index;
}
void transform(u32 output, u32 input, u32 matrix, bool position) {
    if (position)
        FUN_005e44d1(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(input),
                     reinterpret_cast<const void*>(matrix));
    else
        FUN_005e45e4(reinterpret_cast<float*>(output), reinterpret_cast<const float*>(input),
                     reinterpret_cast<const float*>(matrix));
}
u32 third() {
    u32 value;
    __asm__ volatile("flds %1\n\tfstps %0" : "=m"(value) : "m"(dat_006c2bb4) : "st", "memory");
    return value;
}
__attribute__((always_inline)) inline void fp_control_point(u32 frame, u32 slots, u32 output,
                                                            u32 second, u32 normal) {
    __asm__ volatile(
        "flds 0(%[output])\n\t"
        "fsubs 0(%[second])\n\t"
        "fstps 0(%[output])\n\t"
        "flds 4(%[output])\n\t"
        "fsubs 4(%[second])\n\t"
        "fstps 4(%[output])\n\t"
        "flds 8(%[output])\n\t"
        "fsubs 8(%[second])\n\t"
        "fsts 8(%[output])\n\t"
        "fld %%st(0)\n\t"
        "fmuls 8(%[normal])\n\t"
        "flds 0(%[normal])\n\t"
        "fmuls 0(%[output])\n\t"
        "faddp %%st,%%st(1)\n\t"
        "flds 4(%[output])\n\t"
        "fmuls 4(%[normal])\n\t"
        "faddp %%st,%%st(1)\n\t"
        "fld %%st(0)\n\t"
        "fmuls 0(%[normal])\n\t"
        "fstps -12(%[frame])\n\t"
        "fld %%st(0)\n\t"
        "fmuls 4(%[normal])\n\t"
        "fstps -8(%[frame])\n\t"
        "fmuls 8(%[normal])\n\t"
        "fld %%st(1)\n\t"
        "fsub %%st(1),%%st\n\t"
        "fstps 8(%[output])\n\t"
        "fstp %%st(0)\n\t"
        "fstp %%st(0)\n\t"
        "flds 0(%[output])\n\t"
        "fsubs -12(%[frame])\n\t"
        "fmuls 12(%[slots])\n\t"
        "fsts 0(%[output])\n\t"
        "flds 4(%[output])\n\t"
        "fsubs -8(%[frame])\n\t"
        "fmuls 12(%[slots])\n\t"
        "fsts 4(%[output])\n\t"
        "flds 12(%[slots])\n\t"
        "fmuls 8(%[output])\n\t"
        "fstps 8(%[output])\n\t"
        "fld %%st(1)\n\t"
        "fadds 0(%[second])\n\t"
        "fstps 0(%[output])\n\t"
        "fadds 4(%[second])\n\t"
        "fstps 4(%[output])\n\t"
        "fstp %%st(0)\n\t"
        "flds 8(%[second])\n\t"
        "fadds 8(%[output])\n\t"
        "fstps 8(%[output])\n\t" ::[frame] "r"(frame),
        [slots] "r"(slots), [output] "r"(output), [second] "r"(second), [normal] "r"(normal)
        : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory");
}

__attribute__((always_inline)) inline void fp_fast_accumulate(u32 frame, u32 slots, u32 output,
                                                              u32 other_output) {
    __asm__ volatile("flds 40(%[slots])\n\t"
                     "flds -20(%[frame])\n\t"
                     "fmul %%st(1),%%st\n\t"
                     "fstps -20(%[frame])\n\t"
                     "flds -16(%[frame])\n\t"
                     "fmul %%st(1),%%st\n\t"
                     "fstps -16(%[frame])\n\t"
                     "flds -12(%[frame])\n\t"
                     "fmul %%st(1),%%st\n\t"
                     "fstps -12(%[frame])\n\t"
                     "flds -36(%[frame])\n\t"
                     "fmul %%st(1),%%st\n\t"
                     "fstps -36(%[frame])\n\t"
                     "flds -32(%[frame])\n\t"
                     "fmul %%st(1),%%st\n\t"
                     "fstps -32(%[frame])\n\t"
                     "flds -28(%[frame])\n\t"
                     "fmul %%st(1),%%st\n\t"
                     "fstps -28(%[frame])\n\t"
                     "fstp %%st(0)\n\t"
                     "flds -20(%[frame])\n\t"
                     "fadds 0(%[output])\n\t"
                     "fstps 0(%[output])\n\t"
                     "flds -16(%[frame])\n\t"
                     "fadds 4(%[output])\n\t"
                     "fstps 4(%[output])\n\t"
                     "flds -12(%[frame])\n\t"
                     "fadds 8(%[output])\n\t"
                     "fstps 8(%[output])\n\t"
                     "flds -36(%[frame])\n\t"
                     "fadds 0(%[other_output])\n\t"
                     "fstps 0(%[other_output])\n\t"
                     "flds -32(%[frame])\n\t"
                     "fadds 4(%[other_output])\n\t"
                     "fstps 4(%[other_output])\n\t"
                     "flds -28(%[frame])\n\t"
                     "fadds 8(%[other_output])\n\t"
                     "fstps 8(%[other_output])\n\t" ::[frame] "r"(frame),
                     [slots] "r"(slots), [output] "r"(output), [other_output] "r"(other_output)
                     : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                       "memory");
}

__attribute__((always_inline)) inline void fp_generic_accumulate(u32 frame, u32 accumulation) {
    __asm__ volatile("flds -20(%[frame])\n\t"
                     "fmuls -4(%[frame])\n\t"
                     "fstps -20(%[frame])\n\t"
                     "flds -16(%[frame])\n\t"
                     "fmuls -4(%[frame])\n\t"
                     "fstps -16(%[frame])\n\t"
                     "flds -12(%[frame])\n\t"
                     "fmuls -4(%[frame])\n\t"
                     "fstps -12(%[frame])\n\t"
                     "flds -20(%[frame])\n\t"
                     "fadds -8(%[accumulation])\n\t"
                     "fstps -8(%[accumulation])\n\t"
                     "flds -16(%[frame])\n\t"
                     "fadds -4(%[accumulation])\n\t"
                     "fstps -4(%[accumulation])\n\t"
                     "flds -12(%[frame])\n\t"
                     "fadds 0(%[accumulation])\n\t"
                     "fstps 0(%[accumulation])\n\t" ::[frame] "r"(frame),
                     [accumulation] "r"(accumulation)
                     : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                       "memory");
}

__attribute__((always_inline)) inline void fp_patch_initial_a(u32 frame) {
    __asm__ volatile("flds -96(%[frame])\n\t"
                     "fadds -72(%[frame])\n\t"
                     "flds -92(%[frame])\n\t"
                     "fadds -68(%[frame])\n\t"
                     "flds -88(%[frame])\n\t"
                     "fadds -64(%[frame])\n\t"
                     "fstps -64(%[frame])\n\t"
                     "flds -84(%[frame])\n\t"
                     "fadd %%st(2),%%st\n\t"
                     "fstps -72(%[frame])\n\t"
                     "flds -80(%[frame])\n\t"
                     "fadd %%st(1),%%st\n\t"
                     "fstp %%st(2)\n\t"
                     "fstp %%st(0)\n\t"
                     "flds -76(%[frame])\n\t"
                     "fadds -64(%[frame])\n\t"
                     "flds -60(%[frame])\n\t"
                     "fadds -72(%[frame])\n\t"
                     "fstps -72(%[frame])\n\t"
                     "flds -56(%[frame])\n\t"
                     "fadd %%st(2),%%st\n\t"
                     "fstps -68(%[frame])\n\t"
                     "flds -52(%[frame])\n\t"
                     "fadd %%st(1),%%st\n\t"
                     "fstp %%st(2)\n\t"
                     "fstp %%st(0)\n\t"
                     "flds -36(%[frame])\n\t"
                     "fadds -72(%[frame])\n\t"
                     "flds -32(%[frame])\n\t"
                     "fadds -68(%[frame])\n\t"
                     "fstps -68(%[frame])\n\t"
                     "flds -28(%[frame])\n\t"
                     "fadd %%st(2),%%st\n\t"
                     "fstps -64(%[frame])\n\t"
                     "flds -24(%[frame])\n\t"
                     "fadd %%st(1),%%st\n\t"
                     "fstps -72(%[frame])\n\t"
                     "fstp %%st(0)\n\t"
                     "fstp %%st(0)\n\t"
                     "flds -20(%[frame])\n\t"
                     "fadds -68(%[frame])\n\t"
                     "fstps -68(%[frame])\n\t"
                     "flds -16(%[frame])\n\t"
                     "fadds -64(%[frame])\n\t"
                     "flds %[dat_006bfe14]\n\t"
                     "flds -72(%[frame])\n\t"
                     "fmul %%st(1),%%st\n\t"
                     "fstps -72(%[frame])\n\t"
                     "flds -68(%[frame])\n\t"
                     "fmul %%st(1),%%st\n\t"
                     "fstps -68(%[frame])\n\t"
                     "fld %%st(1)\n\t"
                     "fmul %%st(1),%%st\n\t"
                     "fstp %%st(2)\n\t"
                     "fstp %%st(0)\n\t"
                     "flds -48(%[frame])\n\t"
                     "fadds -120(%[frame])\n\t"
                     "flds -44(%[frame])\n\t"
                     "fadds -116(%[frame])\n\t"
                     "flds -40(%[frame])\n\t"
                     "fadds -112(%[frame])\n\t"
                     "fstps -124(%[frame])\n\t"
                     "flds -12(%[frame])\n\t"
                     "fadd %%st(2),%%st\n\t"
                     "fstps -144(%[frame])\n\t"
                     "flds -8(%[frame])\n\t"
                     "fadd %%st(1),%%st\n\t"
                     "fstp %%st(2)\n\t"
                     "fstp %%st(0)\n\t"
                     "flds -4(%[frame])\n\t"
                     "fadds -124(%[frame])\n\t" ::[frame] "r"(frame),
                     [dat_006bfe14] "m"(dat_006bfe14)
                     : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                       "memory");
}

__attribute__((always_inline)) inline void fp_patch_initial_b(u32 frame) {
    __asm__ volatile("fstps -136(%[frame])\n\t"
                     "flds %[dat_006df780]\n\t"
                     "flds -144(%[frame])\n\t"
                     "fmul %%st(1),%%st\n\t"
                     "fld %%st(2)\n\t"
                     "fmul %%st(2),%%st\n\t"
                     "fstps -128(%[frame])\n\t"
                     "flds -136(%[frame])\n\t"
                     "fmul %%st(2),%%st\n\t"
                     "fstps -124(%[frame])\n\t"
                     "flds -72(%[frame])\n\t"
                     "fsub %%st(1),%%st\n\t"
                     "fstps -72(%[frame])\n\t"
                     "fstp %%st(0)\n\t"
                     "fstp %%st(0)\n\t"
                     "fstp %%st(0)\n\t"
                     "flds -68(%[frame])\n\t"
                     "fsubs -128(%[frame])\n\t"
                     "fstps -68(%[frame])\n\t"
                     "fsubs -124(%[frame])\n\t"
                     "fstps -64(%[frame])\n\t" ::[frame] "r"(frame),
                     [dat_006df780] "m"(dat_006df780)
                     : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                       "memory");
}

__attribute__((always_inline)) inline void fp_three() {
    __asm__ volatile("flds %[dat_006bca1c]\n\t" ::[dat_006bca1c] "m"(dat_006bca1c)
                     : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                       "memory");
}

__attribute__((always_inline)) inline void fp_patch_weights(u32 frame, u32 slots, u32 coordinates) {
    __asm__ volatile(
        "flds 0(%[coordinates])\n\t"
        "flds 4(%[coordinates])\n\t"
        "fld1\n\t"
        "fsub %%st(2),%%st\n\t"
        "fsub %%st(1),%%st\n\t"
        "fld %%st(1)\n\t"
        "fmul %%st(2),%%st\n\t"
        "fld %%st(0)\n\t"
        "fmul %%st(3),%%st\n\t"
        "fstps -184(%[frame])\n\t"
        "fld %%st(1)\n\t"
        "fmul %%st(3),%%st\n\t"
        "fsts 20(%[slots])\n\t"
        "fmul %%st(3),%%st\n\t"
        "fmul %%st(5),%%st\n\t"
        "fstps -180(%[frame])\n\t"
        "fmul %%st(3),%%st\n\t"
        "fmul %%st(4),%%st\n\t"
        "fstps -176(%[frame])\n\t"
        "fld %%st(0)\n\t"
        "fmul %%st(1),%%st\n\t"
        "fld %%st(0)\n\t"
        "fmul %%st(3),%%st\n\t"
        "fmul %%st(5),%%st\n\t"
        "fstps -172(%[frame])\n\t"
        "flds 20(%[slots])\n\t"
        "fmul %%st(4),%%st\n\t"
        "fmuls %[dat_006bc9b8]\n\t"
        "fstps -168(%[frame])\n\t"
        "fld %%st(2)\n\t"
        "fmul %%st(4),%%st\n\t"
        "fmul %%st(4),%%st\n\t"
        "fmul %%st(5),%%st\n\t"
        "fstps -164(%[frame])\n\t"
        "fld %%st(0)\n\t"
        "fmul %%st(2),%%st\n\t"
        "fstps -160(%[frame])\n\t"
        "fmul %%st(3),%%st\n\t"
        "fmul %%st(4),%%st\n\t"
        "fstps -156(%[frame])\n\t"
        "fld %%st(0)\n\t"
        "fmul %%st(3),%%st\n\t"
        "fmul %%st(3),%%st\n\t"
        "fmul %%st(4),%%st\n\t"
        "fstps -152(%[frame])\n\t"
        "fld %%st(2)\n\t"
        "fmul %%st(3),%%st\n\t"
        "fmul %%st(3),%%st\n\t"
        "fstps -148(%[frame])\n\t" ::[frame] "r"(frame),
        [slots] "r"(slots), [coordinates] "r"(coordinates), [dat_006bc9b8] "m"(dat_006bc9b8)
        : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory");
}

__attribute__((always_inline)) inline void fp_zero_three() {
    __asm__ volatile("fldz\n\t"
                     "fldz\n\t"
                     "fldz\n\t" ::
                         : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                           "memory");
}

__attribute__((always_inline)) inline void fp_patch_accumulate(u32 point, u32 weight) {
    __asm__ volatile("flds -4(%[point])\n\t"
                     "fmuls 0(%[weight])\n\t"
                     "faddp %%st,%%st(3)\n\t"
                     "flds 0(%[weight])\n\t"
                     "fmuls 0(%[point])\n\t"
                     "faddp %%st,%%st(2)\n\t"
                     "flds 4(%[point])\n\t"
                     "fmuls 0(%[weight])\n\t"
                     "faddp %%st,%%st(1)\n\t" ::[point] "r"(point),
                     [weight] "r"(weight)
                     : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                       "memory");
}

__attribute__((always_inline)) inline void fp_patch_store(u32 frame) {
    __asm__ volatile("fstps -448(%[frame])\n\t"
                     "fstps -452(%[frame])\n\t"
                     "fstps -456(%[frame])\n\t" ::[frame] "r"(frame)
                     : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                       "memory");
}

__attribute__((always_inline)) inline void fp_patch_extra(u32 output, u32 first, u32 second,
                                                          u32 third) {
    __asm__ volatile("fld %%st(2)\n\t"
                     "fmuls 0(%[third])\n\t"
                     "fld %%st(2)\n\t"
                     "fmuls 0(%[first])\n\t"
                     "faddp %%st,%%st(1)\n\t"
                     "fld %%st(1)\n\t"
                     "fmuls 0(%[second])\n\t"
                     "faddp %%st,%%st(1)\n\t"
                     "fstps 0(%[output])\n\t" ::[output] "r"(output),
                     [first] "r"(first), [second] "r"(second), [third] "r"(third)
                     : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                       "memory");
}

__attribute__((always_inline)) inline void fp_pop_three() {
    __asm__ volatile("fstp %%st(0)\n\t"
                     "fstp %%st(0)\n\t"
                     "fstp %%st(0)\n\t" ::
                         : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                           "memory");
}

__attribute__((always_inline)) inline void fp_pop_one() {
    __asm__ volatile("fstp %%st(0)\n\t" ::
                         : "st", "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                           "memory");
}

} // namespace

extern "C" u32 recovered_geometry_005fcc26(u32 slots) {
    alignas(4) unsigned char private_storage[12];
    const u32 frame = reinterpret_cast<u32>(private_storage) + 12;
    const u32 output = word(slots + 16), first = word(slots), second = word(slots + 4),
              normal = word(slots + 8);
    copy(output, first, 12);
    fp_control_point(frame, slots, output, second, normal);
    return output;
}
namespace {
void control_point(u32 output, u32 first, u32 second, u32 normal) {
    const u32 arguments[5] = {first, second, normal, third(), output};
    recovered_geometry_005fcc26(reinterpret_cast<u32>(arguments));
}
void copy_stream(u32 slots) {
    const u32 stride = word(slots + 20), source = word(slots + 8), output = word(slots + 12);
    put(slots + 12, output + stride);
    copy(output, source, stride & ~3u);
    put(slots + 8, source + stride);
    copy(output + (stride & ~3u), source + (stride & ~3u), stride & 3u);
}
} // namespace

// Complete005fc8ac..005fcc26: original two-stream fast path and generic path.
// The actual incoming words are mutable and remain shared with the caller.
extern "C" void recovered_geometry_005fc8ac(u32 slots) {
    alignas(4) unsigned char private_storage[0x338];
    const u32 frame = reinterpret_cast<u32>(private_storage) + 0x338;
    const u32 packed_bytes = word(slots + 36) * 12;
    const bool copy_other = packed_bytes != word(slots + 20);
    if (!word(slots + 4))
        put(slots + 4, word(slots));
    if (word(slots + 36) == 2) {
        const u32 types = word(slots + 32);
        const uint8_t first_type = byte(types);
        u32 first = 0, second = 0, output = 0, other_output = 0;
        if (first_type == 0 && byte(types + 1) == 3) {
            const u32 inputs = word(slots + 24);
            first = word(inputs);
            second = word(inputs + 4);
            const u32 outputs = word(slots + 28);
            other_output = word(outputs + 4);
            output = word(outputs);
        } else if (byte(types + 1) == 0 && first_type == 3) {
            const u32 inputs = word(slots + 24);
            first = word(inputs + 4);
            second = word(inputs);
            const u32 outputs = word(slots + 28);
            output = word(outputs + 4);
            other_output = word(outputs);
        }
        if (first) {
            const u32 count = word(slots + 16);
            if (!count)
                return;
            put(slots + 24, count);
            do {
                if (copy_other)
                    copy_stream(slots);
                u32 weights = word(slots + 40);
                zero(output);
                zero(output + 4);
                zero(output + 8);
                zero(other_output);
                zero(other_output + 4);
                zero(other_output + 8);
                while (weight_present(weights)) {
                    const u32 index = fraction(weights, slots + 40), matrix_offset = index << 6;
                    transform(frame - 20, first, word(slots) + matrix_offset, true);
                    transform(frame - 36, second, word(slots + 4) + matrix_offset, false);
                    weights += 4;
                    fp_fast_accumulate(frame, slots, output, other_output);
                }
                const u32 stride = word(slots + 20);
                first += stride;
                second += stride;
                other_output += stride;
                weights += 4;
                output += stride;
                put(slots + 24, word(slots + 24) - 1);
                put(slots + 40, weights);
            } while (word(slots + 24));
            return;
        }
    }
    u32 outer = 0;
    if (!word(slots + 16))
        return;
    do {
        clear(frame - 0x338, packed_bytes);
        u32 weights = word(slots + 40);
        while (weight_present(weights)) {
            const u32 index = fraction(weights, frame - 4);
            u32 channel = 0;
            while (channel < word(slots + 36)) {
                const uint8_t type = byte(word(slots + 32) + channel);
                u32 matrix;
                if (type == 0)
                    matrix = word(slots);
                else if (type == 3)
                    matrix = word(slots + 4);
                else if (type == 6 || type == 7)
                    matrix = word(slots);
                else
                    return;
                transform(frame - 20, word(word(slots + 24) + channel * 4), matrix + (index << 6),
                          type == 0);
                fp_generic_accumulate(frame, frame - 0x330 + channel * 12);
                ++channel;
            }
            weights = word(slots + 40) + 4;
            put(slots + 40, weights);
        }
        if (copy_other)
            copy_stream(slots);
        const u32 channels = word(slots + 36);
        if (channels) {
            u32 output_entry = word(slots + 28);
            const u32 input_delta = word(slots + 24) - output_entry;
            for (u32 n = channels, index = 0; n; --n, ++index, output_entry += 4) {
                const u32 target = word(output_entry), stride = word(slots + 20);
                copy(target, frame - 0x338 + index * 12, 12);
                put(output_entry, word(output_entry) + stride);
                put(output_entry + input_delta, word(output_entry + input_delta) + stride);
            }
        }
        put(slots + 40, word(slots + 40) + 4);
        ++outer;
    } while (outer < word(slots + 16));
}

// Complete005fccc5..005fd01e: six original control-point calls and ordered
// polynomial accumulation, followed by linear interpolation of extra fields.
extern "C" void recovered_geometry_005fccc5(u32 slots) {
    alignas(4) unsigned char private_storage[0x1c8];
    const u32 frame = reinterpret_cast<u32>(private_storage) + 0x1c8;
    const u32 original_second = word(slots + 20);
    copy(frame - 120, word(slots + 16), 12);
    copy(frame - 48, original_second, 12);
    copy(frame - 12, word(slots + 24), 12);
    const u32 normals = word(slots);
    control_point(frame - 108, frame - 48, frame - 120, normals);
    control_point(frame - 96, frame - 12, frame - 120, normals);
    control_point(frame - 84, frame - 120, frame - 48, normals + 12);
    control_point(frame - 60, frame - 120, frame - 12, normals + 24);
    control_point(frame - 36, frame - 12, frame - 48, normals + 12);
    control_point(frame - 24, frame - 48, frame - 12, normals + 24);
    copy(frame - 72, frame - 108, 12);
    fp_patch_initial_a(frame);
    put(slots, 0);
    fp_patch_initial_b(frame);
    if (!word(slots + 8))
        return;
    fp_three();
    do {
        const u32 coordinates = word(slots + 4) + (word(slots) << 3);
        fp_patch_weights(frame, slots, coordinates);
        fp_zero_three();
        for (u32 n = 0; n < 10; ++n)
            fp_patch_accumulate(frame - 116 + n * 12, frame - 184 + n * 4);
        fp_patch_store(frame);
        const u32 components = word(slots + 28);
        if (components > 3) {
            const u32 first = word(slots + 16), third = word(slots + 24);
            for (u32 n = 3; n < components; ++n)
                fp_patch_extra(frame - 456 + n * 4, first + n * 4, original_second + n * 4,
                               third + n * 4);
        }
        const u32 output = word(slots + 12);
        fp_pop_three();
        const u32 bytes = components << 2;
        put(slots + 12, output + bytes);
        copy(output, frame - 456, bytes);
        put(slots, word(slots) + 1);
    } while (word(slots) < word(slots + 8));
    fp_pop_one();
}

extern "C" __attribute__((naked, stdcall)) void FUN_005fc8ac(uint32_t, uint32_t, uint32_t, uint32_t,
                                                             uint32_t, uint32_t, uint32_t, uint32_t,
                                                             uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_geometry_005fc8ac\n\taddl $4,%esp\n\tretl $44");
}
extern "C" __attribute__((naked, stdcall)) void
FUN_005fccc5(uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_geometry_005fccc5\n\taddl $4,%esp\n\tretl $32");
}
extern "C" __attribute__((naked, stdcall)) uint32_t FUN_005fcc26(uint32_t, uint32_t, uint32_t,
                                                                 uint32_t, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_geometry_005fcc26\n\taddl $4,%esp\n\tretl $20");
}
