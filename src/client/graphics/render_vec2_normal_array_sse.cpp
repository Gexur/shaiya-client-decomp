#include "graphics/render_vec2_normal_array_sse.h"
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
recovered_sse_vec2_normal_array(const u32* arguments) {
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
extern "C" __attribute__((naked, stdcall)) void* FUN_0068207e(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_vec2_normal_array\n\taddl $4,%esp\n\tretl $24");
}
