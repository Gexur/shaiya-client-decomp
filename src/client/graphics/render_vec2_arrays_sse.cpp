#include "graphics/render_vec2_arrays_sse.h"
#include "graphics/render_matrix_broadcast_sse.h"
#include "graphics/render_transform_baseline.h"
#include "graphics/render_transform_coord_dispatch.h"
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
} // namespace
extern "C" __attribute__((target("sse"))) void*
recovered_sse_vec2_transform_array(const u32* arguments) {
    const u32 count = word(arguments + 5), initial = word(arguments),
              output_stride = word(arguments + 1), grouped = count > 12 ? (count & ~3u) : 0,
              tail = count - grouped;
    u32 output = initial;
    if (grouped) {
        alignas(16) V matrix[16];
        const u32 matrix_pointer = word(arguments + 4);
        FUN_00681a69(matrix, reinterpret_cast<const void*>(matrix_pointer));
        u32 groups = grouped >> 2;
        const u32 input_stride = word(arguments + 3);
        do {
            const u32 input = word(arguments + 2);
            const V input_two = low(input + input_stride * 2), input_zero = low(input);
            const V pair01 = high(input_zero, input + input_stride),
                    pair23 = high(input_two, input + input_stride * 3);
            const V x = shuffle<0x88>(pair01, pair23), y = shuffle<0xdd>(pair01, pair23);
            const V x0 = mul(x, cache(matrix)), y0 = mul(y, cache(matrix + 4)), sum0 = add(x0, y0),
                    result0 = add(sum0, cache(matrix + 12));
            const V x1 = mul(x, cache(matrix + 1)), y1 = mul(y, cache(matrix + 5)),
                    sum1 = add(x1, y1), result1 = add(sum1, cache(matrix + 13));
            const V x2 = mul(x, cache(matrix + 2)), x3 = mul(x, cache(matrix + 3));
            const V y2 = mul(y, cache(matrix + 6)), y3 = mul(y, cache(matrix + 7));
            const V sum2 = add(x2, y2), sum3 = add(x3, y3), result2 = add(sum2, cache(matrix + 14)),
                    result3 = add(sum3, cache(matrix + 15));
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
            put(arguments + 2, input + input_stride * 4);
            output += output_stride * 4;
        } while (--groups);
    }
    u32 remaining = tail;
    if (remaining)
        do {
            const u32 matrix = word(arguments + 4), input = word(arguments + 2);
            FUN_005e3fd3(reinterpret_cast<float*>(output), reinterpret_cast<const float*>(input),
                         reinterpret_cast<const float*>(matrix));
            const u32 stride = word(arguments + 3);
            put(arguments + 2, word(arguments + 2) + stride);
            output += output_stride;
        } while (--remaining);
    return reinterpret_cast<void*>(initial);
}
extern "C" __attribute__((target("sse"))) void*
recovered_sse_vec2_coordinate_array(const u32* arguments) {
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
            const V input_zero = low(input), input_two = low(input + input_stride * 2);
            const V pair01 = high(input_zero, input + input_stride),
                    pair23 = high(input_two, input + input_stride * 3);
            const V x = shuffle<0x88>(pair01, pair23), y = shuffle<0xdd>(pair01, pair23);
            const V yw = mul(y, cache(matrix + 7)), xw = mul(x, cache(matrix + 3)),
                    sumw = add(xw, yw), w = add(sumw, cache(matrix + 15));
            const V guess = reciprocal(w), product = mul(guess, w),
                    second_product = mul(product, guess), twice_guess = add(guess, guess),
                    factor = sub(twice_guess, second_product);
            const V yx = mul(y, cache(matrix + 4)), yy = mul(y, cache(matrix + 5)),
                    xy = mul(x, cache(matrix + 1)), xx = mul(x, cache(matrix));
            const V sumx = add(xx, yx), sumy = add(xy, yy),
                    translated_y = add(sumy, cache(matrix + 13)),
                    translated_x = add(sumx, cache(matrix + 12));
            const V result_x = mul(translated_x, factor), result_y = mul(translated_y, factor),
                    xy01 = unpack_low(result_x, result_y);
            store_low(output, xy01);
            store_high(output + output_stride, xy01);
            const V xy23 = unpack_high(result_x, result_y);
            store_low(output + output_stride * 2, xy23);
            store_high(output + output_stride * 3, xy23);
            input += input_stride * 4;
            output += output_stride * 4;
        } while (--groups);
    } else
        input = word(arguments + 2); // original reads this even when count is zero
    u32 remaining = tail;
    if (remaining)
        do {
            const u32 matrix = word(arguments + 4);
            FUN_005e3fff(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(input),
                         reinterpret_cast<const void*>(matrix));
            input += word(arguments + 3);
            output += word(arguments + 1);
        } while (--remaining);
    return reinterpret_cast<void*>(initial);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00681da2(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_vec2_transform_array\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00681f22(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_vec2_coordinate_array\n\taddl $4,%esp\n\tretl $24");
}
