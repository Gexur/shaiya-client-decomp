#include "graphics/render_vec34_transform_arrays_sse.h"
#include "graphics/render_matrix_broadcast_sse.h"
#include "graphics/render_transform_baseline.h"
#include "graphics/render_transform_coord_dispatch.h"
#include "graphics/render_transform_sse_aligned.h"
namespace {
using u32 = uint32_t;
using V = float __attribute__((vector_size(16)));
struct B8 {
    unsigned char bytes[8];
};
struct B16 {
    unsigned char bytes[16];
};
#define SIMD __attribute__((target("sse"), always_inline)) inline
u32 word(const u32* p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(const u32* p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
SIMD V low(u32 p) {
    V v{};
    __asm__ volatile("movlps %1,%0" : "+x"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
SIMD V high(V v, u32 p) {
    __asm__ volatile("movhps %1,%0" : "+x"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
SIMD V cache(const V* p) {
    V v;
    __asm__ volatile("movaps %1,%0" : "=x"(v) : "m"(*p) : "memory");
    return v;
}
template <int mask> SIMD V shuffle(V a, V b) {
    __asm__ volatile("shufps %2,%1,%0" : "+x"(a) : "x"(b), "i"(mask));
    return a;
}
SIMD V mul(V a, V b) {
    __asm__ volatile("mulps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V add(V a, V b) {
    __asm__ volatile("addps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V sub(V a, V b) {
    __asm__ volatile("subps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V unpack_low(V a, V b) {
    __asm__ volatile("unpcklps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V unpack_high(V a, V b) {
    __asm__ volatile("unpckhps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SIMD V reciprocal(V a) {
    V r;
    __asm__ volatile("rcpps %1,%0" : "=x"(r) : "x"(a));
    return r;
}
SIMD void store_low(u32 p, V a) {
    __asm__ volatile("movlps %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(a) : "memory");
}
SIMD void store_high(u32 p, V a) {
    __asm__ volatile("movhps %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(a) : "memory");
}

SIMD V scalar_word(u32 p) {
    V v;
    __asm__ volatile("movss %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const u32*>(p)) : "memory");
    return v;
}
SIMD V low_to_high(V a, V b) {
    __asm__ volatile("movlhps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
} // namespace

extern "C" __attribute__((target("sse"))) void*
recovered_sse_vec3_transform_array(const u32* arguments) {
    const u32 count = word(arguments + 5), initial = word(arguments),
              grouped = count > 12 ? (count & ~3u) : 0, tail = count - grouped;
    u32 output = initial, input;
    if (grouped) {
        alignas(16) V matrix[16];
        const u32 matrix_pointer = word(arguments + 4);
        FUN_00681a69(matrix, reinterpret_cast<const void*>(matrix_pointer));
        u32 groups = grouped >> 2;
        const u32 input_stride = word(arguments + 3), output_stride = word(arguments + 1);
        input = word(arguments + 2);
        do {
            const V input_two = low(input + input_stride * 2), input_zero = low(input),
                    pair01 = high(input_zero, input + input_stride);
            const V z0 = scalar_word(input + 8), pair23 = high(input_two, input + input_stride * 3);
            const V y = shuffle<0xdd>(pair01, pair23), x = shuffle<0x88>(pair01, pair23);
            const V z2 = scalar_word(input + input_stride * 2 + 8),
                    z3 = scalar_word(input + input_stride * 3 + 8), z23 = low_to_high(z2, z3);
            const V z1 = scalar_word(input + input_stride + 8), z01 = low_to_high(z0, z1),
                    z = shuffle<0x88>(z01, z23);
            const V y0 = mul(y, cache(matrix + 4)), x0 = mul(x, cache(matrix)), xy0 = add(x0, y0),
                    zprod0 = mul(z, cache(matrix + 8)), xyz0 = add(xy0, zprod0),
                    result0 = add(xyz0, cache(matrix + 12));
            const V y1 = mul(y, cache(matrix + 5)), x1 = mul(x, cache(matrix + 1)),
                    xy1 = add(x1, y1), zprod1 = mul(z, cache(matrix + 9)), xyz1 = add(xy1, zprod1),
                    result1 = add(xyz1, cache(matrix + 13));
            const V y2 = mul(y, cache(matrix + 6)), y3 = mul(y, cache(matrix + 7)),
                    x2 = mul(x, cache(matrix + 2)), x3 = mul(x, cache(matrix + 3));
            const V zprod2 = mul(z, cache(matrix + 10)), zprod3 = mul(z, cache(matrix + 11)),
                    xy3 = add(x3, y3), xy2 = add(x2, y2), xyz2 = add(xy2, zprod2),
                    xyz3 = add(xy3, zprod3);
            const V result3 = add(xyz3, cache(matrix + 15)),
                    result2 = add(xyz2, cache(matrix + 14));
            const V xy01 = unpack_low(result0, result1);
            store_low(output, xy01);
            const V zw01 = unpack_low(result2, result3);
            store_low(output + 8, zw01);
            store_high(output + output_stride, xy01);
            store_high(output + output_stride + 8, zw01);
            const V xy23 = unpack_high(result0, result1);
            store_low(output + output_stride * 2, xy23);
            const V zw23 = unpack_high(result2, result3);
            store_low(output + output_stride * 2 + 8, zw23);
            store_high(output + output_stride * 3, xy23);
            store_high(output + output_stride * 3 + 8, zw23);
            input += input_stride * 4;
            output += output_stride * 4;
        } while (--groups);
    } else
        input = word(arguments + 2);
    u32 remaining = tail;
    if (remaining)
        do {
            const u32 matrix = word(arguments + 4);
            FUN_00683e19(reinterpret_cast<float*>(output), reinterpret_cast<const float*>(input),
                         reinterpret_cast<const float*>(matrix));
            input += word(arguments + 3);
            output += word(arguments + 1);
        } while (--remaining);
    return reinterpret_cast<void*>(initial);
}

extern "C" __attribute__((target("sse"))) void*
recovered_sse_vec4_transform_array(const u32* arguments) {
    const u32 count = word(arguments + 5), initial = word(arguments),
              grouped = count > 12 ? (count & ~3u) : 0, tail = count - grouped;
    u32 output = initial, input;
    if (grouped) {
        alignas(16) V matrix[16];
        const u32 matrix_pointer = word(arguments + 4);
        FUN_00681a69(matrix, reinterpret_cast<const void*>(matrix_pointer));
        u32 groups = grouped >> 2;
        const u32 input_stride = word(arguments + 3), output_stride = word(arguments + 1);
        input = word(arguments + 2);
        do {
            const V input_two = low(input + input_stride * 2), input_zero = low(input),
                    pair01 = high(input_zero, input + input_stride);
            const V zw_zero = low(input + 8), zw01 = high(zw_zero, input + input_stride + 8),
                    pair23 = high(input_two, input + input_stride * 3);
            const V x = shuffle<0x88>(pair01, pair23), y = shuffle<0xdd>(pair01, pair23);
            const V zw_two = low(input + input_stride * 2 + 8),
                    zw23 = high(zw_two, input + input_stride * 3 + 8),
                    w = shuffle<0xdd>(zw01, zw23), z = shuffle<0x88>(zw01, zw23);
            const V w0 = mul(w, cache(matrix + 12)), w1 = mul(w, cache(matrix + 13));
            const V x0 = mul(x, cache(matrix)), y0 = mul(y, cache(matrix + 4)), xy0 = add(x0, y0),
                    z0 = mul(z, cache(matrix + 8)), xyz0 = add(xy0, z0), result0 = add(xyz0, w0);
            const V x1 = mul(x, cache(matrix + 1)), y1 = mul(y, cache(matrix + 5)),
                    xy1 = add(x1, y1), z1 = mul(z, cache(matrix + 9)), xyz1 = add(xy1, z1),
                    result1 = add(xyz1, w1);
            const V w2 = mul(w, cache(matrix + 14)), x2 = mul(x, cache(matrix + 2)),
                    x3 = mul(x, cache(matrix + 3)), y2 = mul(y, cache(matrix + 6)),
                    y3 = mul(y, cache(matrix + 7)), z2 = mul(z, cache(matrix + 10)),
                    z3 = mul(z, cache(matrix + 11));
            const V xy2 = add(x2, y2), xy3 = add(x3, y3), xyz2 = add(xy2, z2), xyz3 = add(xy3, z3),
                    result2 = add(xyz2, w2), w3 = mul(w, cache(matrix + 15));
            const V pair_xy01 = unpack_low(result0, result1),
                    pair_xy23 = unpack_high(result0, result1), result3 = add(xyz3, w3);
            const V pair_zw01 = unpack_low(result2, result3);
            store_low(output, pair_xy01);
            store_low(output + 8, pair_zw01);
            store_high(output + output_stride, pair_xy01);
            store_high(output + output_stride + 8, pair_zw01);
            const V pair_zw23 = unpack_high(result2, result3);
            store_low(output + output_stride * 2, pair_xy23);
            store_low(output + output_stride * 2 + 8, pair_zw23);
            store_high(output + output_stride * 3, pair_xy23);
            store_high(output + output_stride * 3 + 8, pair_zw23);
            input += input_stride * 4;
            output += output_stride * 4;
        } while (--groups);
    } else
        input = word(arguments + 2);
    u32 remaining = tail;
    if (remaining)
        do {
            const u32 matrix = word(arguments + 4);
            FUN_00683686(reinterpret_cast<float*>(output), reinterpret_cast<const float*>(input),
                         reinterpret_cast<const float*>(matrix));
            input += word(arguments + 3);
            output += word(arguments + 1);
        } while (--remaining);
    return reinterpret_cast<void*>(initial);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00681bcf(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_vec3_transform_array\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068218f(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_vec4_transform_array\n\taddl $4,%esp\n\tretl $24");
}
