#include "graphics/render_alternate_transform_arrays_sse.h"
#include "graphics/render_matrix_broadcast_sse.h"
#include "graphics/render_transform_baseline.h"
#include "graphics/render_transform_coord_dispatch.h"
#include "graphics/render_transform_sse_aligned.h"
#include "graphics/render_coordinate_sse.h"
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

struct Triple {
    V x, y, z;
};
SIMD Triple gather_three(u32 input, u32 stride) {
    const V zero = low(input), two = low(input + stride * 2), z0 = scalar_word(input + 8),
            pair01 = high(zero, input + stride), pair23 = high(two, input + stride * 3);
    const V x = shuffle<0x88>(pair01, pair23), y = shuffle<0xdd>(pair01, pair23);
    const V z2 = scalar_word(input + stride * 2 + 8), z3 = scalar_word(input + stride * 3 + 8),
            z23 = low_to_high(z2, z3), z1 = scalar_word(input + stride + 8),
            z01 = low_to_high(z0, z1), z = shuffle<0x88>(z01, z23);
    return {x, y, z};
}
SIMD void scalar_store(u32 p, V v) {
    __asm__ volatile("movss %1,%0" : "=m"(*reinterpret_cast<u32*>(p)) : "x"(v) : "memory");
}
SIMD void store_z_first_pair(u32 output, u32 stride, V z) {
    scalar_store(output + 8, z);
    scalar_store(output + stride + 8, shuffle<0x55>(z, z));
}
SIMD void store_z_second_pair(u32 output, u32 stride, V z) {
    scalar_store(output + stride * 2 + 8, shuffle<0xaa>(z, z));
    scalar_store(output + stride * 3 + 8, shuffle<0xff>(z, z));
}
} // namespace
extern "C" __attribute__((target("sse"))) void*
recovered_sse2_vec2_transform_array(const u32* arguments) {
    const u32 count = word(arguments + 5), initial = word(arguments),
              output_stride = word(arguments + 1), grouped = count > 10 ? (count & ~3u) : 0,
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
recovered_sse2_vec2_coordinate_array(const u32* arguments) {
    const u32 count = word(arguments + 5), initial = word(arguments),
              grouped = count > 10 ? (count & ~3u) : 0, tail = count - grouped;
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
extern "C" __attribute__((target("sse"))) void*
recovered_sse2_vec2_normal_array(const u32* arguments) {
    const u32 count = word(arguments + 5), initial = word(arguments),
              grouped = count > 10 ? (count & ~3u) : 0, tail = count - grouped;
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
            const V y = shuffle<0xdd>(pair01, pair23), yx = mul(y, cache(matrix + 4)),
                    yy = mul(y, cache(matrix + 5));
            const V x = shuffle<0x88>(pair01, pair23), xx = mul(x, cache(matrix)),
                    xy = mul(x, cache(matrix + 1));
            const V result_y = add(xy, yy), result_x = add(xx, yx),
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
        input = word(arguments + 2);
    u32 remaining = tail;
    if (remaining)
        do {
            const u32 matrix = word(arguments + 4);
            FUN_005e402b(reinterpret_cast<float*>(output), reinterpret_cast<const float*>(input),
                         reinterpret_cast<const float*>(matrix));
            input += word(arguments + 3);
            output += word(arguments + 1);
        } while (--remaining);
    return reinterpret_cast<void*>(initial);
}

extern "C" __attribute__((target("sse"))) void*
recovered_sse2_vec3_transform_array(const u32* arguments) {
    const u32 count = word(arguments + 5), initial = word(arguments),
              grouped = count > 10 ? (count & ~3u) : 0, tail = count - grouped;
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
recovered_sse2_vec4_transform_array(const u32* arguments) {
    const u32 count = word(arguments + 5), initial = word(arguments),
              grouped = count > 10 ? (count & ~3u) : 0, tail = count - grouped;
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

extern "C" __attribute__((target("sse"))) void*
recovered_sse2_vec3_normal_array(const u32* arguments) {
    const u32 count = word(arguments + 5), initial = word(arguments),
              grouped = count > 10 ? (count & ~3u) : 0, tail = count - grouped;
    u32 output = initial, input;
    if (grouped) {
        alignas(16) V matrix[16];
        const u32 matrix_pointer = word(arguments + 4);
        FUN_00681a69(matrix, reinterpret_cast<const void*>(matrix_pointer));
        u32 groups = grouped >> 2;
        const u32 input_stride = word(arguments + 3), output_stride = word(arguments + 1);
        input = word(arguments + 2);
        do {
            const Triple p = gather_three(input, input_stride);
            const V zx = mul(p.z, cache(matrix + 8)), yx = mul(p.y, cache(matrix + 4)),
                    xx = mul(p.x, cache(matrix)), sumx = add(xx, yx), resultx = add(sumx, zx);
            const V zy = mul(p.z, cache(matrix + 9)), zz = mul(p.z, cache(matrix + 10)),
                    xz = mul(p.x, cache(matrix + 2)), xy = mul(p.x, cache(matrix + 1)),
                    yz = mul(p.y, cache(matrix + 6)), yy = mul(p.y, cache(matrix + 5));
            const V sumz = add(xz, yz), resultz = add(sumz, zz), sumy = add(xy, yy),
                    resulty = add(sumy, zy);
            const V xy01 = unpack_low(resultx, resulty);
            store_low(output, xy01);
            store_high(output + output_stride, xy01);
            store_z_first_pair(output, output_stride, resultz);
            const V xy23 = unpack_high(resultx, resulty);
            store_low(output + output_stride * 2, xy23);
            store_high(output + output_stride * 3, xy23);
            store_z_second_pair(output, output_stride, resultz);
            input += input_stride * 4;
            output += output_stride * 4;
        } while (--groups);
    } else
        input = word(arguments + 2);
    u32 remaining = tail;
    if (remaining)
        do {
            const u32 matrix = word(arguments + 4);
            FUN_006818a9(reinterpret_cast<float*>(output), reinterpret_cast<const float*>(input),
                         reinterpret_cast<const float*>(matrix));
            input += word(arguments + 3);
            output += word(arguments + 1);
        } while (--remaining);
    return reinterpret_cast<void*>(initial);
}

extern "C" __attribute__((target("sse"))) void*
recovered_sse2_vec3_coordinate_array(const u32* arguments) {
    const u32 count = word(arguments + 5), initial = word(arguments),
              grouped = count > 10 ? (count & ~3u) : 0, tail = count - grouped;
    u32 output = initial, input;
    if (grouped) {
        alignas(16) V matrix[16];
        const u32 matrix_pointer = word(arguments + 4);
        FUN_00681a69(matrix, reinterpret_cast<const void*>(matrix_pointer));
        u32 groups = grouped >> 2;
        const u32 input_stride = word(arguments + 3), output_stride = word(arguments + 1);
        input = word(arguments + 2);
        do {
            const Triple p = gather_three(input, input_stride);
            const V xw = mul(p.x, cache(matrix + 3)), yw = mul(p.y, cache(matrix + 7)),
                    sumw = add(xw, yw), zw = mul(p.z, cache(matrix + 11)), xyzw = add(sumw, zw),
                    w = add(xyzw, cache(matrix + 15));
            const V guess = reciprocal(w), product = mul(guess, w),
                    second_product = mul(product, guess), twice_guess = add(guess, guess),
                    factor = sub(twice_guess, second_product);
            const V xx = mul(p.x, cache(matrix)), yx = mul(p.y, cache(matrix + 4)),
                    sumx = add(xx, yx), zx = mul(p.z, cache(matrix + 8)), xyzx = add(sumx, zx);
            const V xz = mul(p.x, cache(matrix + 2)), xy = mul(p.x, cache(matrix + 1)),
                    translatedx = add(xyzx, cache(matrix + 12)), yz = mul(p.y, cache(matrix + 6)),
                    yy = mul(p.y, cache(matrix + 5)), sumz = add(xz, yz);
            const V zy = mul(p.z, cache(matrix + 9)), zz = mul(p.z, cache(matrix + 10)),
                    xyzz = add(sumz, zz), translatedz = add(xyzz, cache(matrix + 14)),
                    sumy = add(xy, yy), xyzy = add(sumy, zy);
            const V resultx = mul(translatedx, factor), translatedy = add(xyzy, cache(matrix + 13)),
                    resulty = mul(translatedy, factor), xy01 = unpack_low(resultx, resulty);
            store_low(output, xy01);
            store_high(output + output_stride, xy01);
            const V resultz = mul(translatedz, factor);
            store_z_first_pair(output, output_stride, resultz);
            const V xy23 = unpack_high(resultx, resulty);
            store_low(output + output_stride * 2, xy23);
            store_high(output + output_stride * 3, xy23);
            store_z_second_pair(output, output_stride, resultz);
            input += input_stride * 4;
            output += output_stride * 4;
        } while (--groups);
    } else
        input = word(arguments + 2);
    u32 remaining = tail;
    if (remaining)
        do {
            const u32 matrix = word(arguments + 4);
            FUN_00681975(reinterpret_cast<void*>(output), reinterpret_cast<const void*>(input),
                         reinterpret_cast<const void*>(matrix));
            input += word(arguments + 3);
            output += word(arguments + 1);
        } while (--remaining);
    return reinterpret_cast<void*>(initial);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00682947(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse2_vec3_transform_array\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00682b1a(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse2_vec2_transform_array\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00682c9a(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse2_vec2_coordinate_array\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00682df6(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse2_vec2_normal_array\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00682f07(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse2_vec4_transform_array\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00683107(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse2_vec3_normal_array\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_006832bb(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse2_vec3_coordinate_array\n\taddl $4,%esp\n\tretl $24");
}
