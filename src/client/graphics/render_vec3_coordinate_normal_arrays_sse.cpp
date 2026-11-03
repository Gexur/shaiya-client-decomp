#include "graphics/render_vec3_coordinate_normal_arrays_sse.h"
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
recovered_sse_vec3_normal_array(const u32* arguments) {
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
recovered_sse_vec3_coordinate_array(const u32* arguments) {
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
extern "C" __attribute__((naked, stdcall)) void* FUN_0068238f(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_vec3_normal_array\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00682543(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_vec3_coordinate_array\n\taddl $4,%esp\n\tretl $24");
}
