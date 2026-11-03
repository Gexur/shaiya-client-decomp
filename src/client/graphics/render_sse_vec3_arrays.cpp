#include "graphics/render_sse_vec3_arrays.h"
#include "graphics/render_transform_amd.h"
namespace {
using u32 = uint32_t;
using V = float __attribute__((vector_size(16)));
using M = long long __attribute__((vector_size(8)));
struct B8 {
    unsigned char bytes[8];
};
struct B16 {
    unsigned char bytes[16];
};
#define SSE __attribute__((target("sse"), always_inline)) inline
#define AMD __attribute__((target("mmx,sse"), always_inline)) inline
u32 word(const u32* p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(const u32* p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
SSE V load16(u32 p) {
    V v;
    __asm__ volatile("movups %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SSE V aligned16(const void* p) {
    V v;
    __asm__ volatile("movaps %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SSE V scalar(u32 p) {
    V v;
    __asm__ volatile("movss %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const u32*>(p)) : "memory");
    return v;
}
SSE V low(u32 p) {
    V v{};
    __asm__ volatile("movlps %1,%0" : "+x"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
template <int mask> SSE V shuffle(V a, V b) {
    __asm__ volatile("shufps %2,%1,%0" : "+x"(a) : "x"(b), "i"(mask));
    return a;
}
SSE V mul(V a, V b) {
    __asm__ volatile("mulps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V add(V a, V b) {
    __asm__ volatile("addps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V sub(V a, V b) {
    __asm__ volatile("subps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V unpack_low(V a, V b) {
    __asm__ volatile("unpcklps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V unpack_high(V a, V b) {
    __asm__ volatile("unpckhps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V low_to_high(V a, V b) {
    __asm__ volatile("movlhps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V high_to_low(V a, V b) {
    __asm__ volatile("movhlps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE V reciprocal(V a) {
    V v;
    __asm__ volatile("rcpps %1,%0" : "=x"(v) : "x"(a));
    return v;
}
SSE void store16(u32 p, V a) {
    __asm__ volatile("movups %1,%0" : "=m"(*reinterpret_cast<B16*>(p)) : "x"(a) : "memory");
}
SSE void store_low(u32 p, V a) {
    __asm__ volatile("movlps %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(a) : "memory");
}
AMD void empty() {
    __asm__ volatile("femms" ::
                         : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st", "st(1)",
                           "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)", "memory");
}
AMD M pair(u32 p) {
    M v;
    __asm__ volatile("movq %1,%0" : "=y"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
AMD M unpack_dword_low(M a, M b) {
    __asm__ volatile("punpckldq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD M unpack_dword_high(M a, M b) {
    __asm__ volatile("punpckhdq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD M packed_mul(M a, M b) {
    __asm__ volatile("pfmul %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD M packed_add(M a, M b) {
    __asm__ volatile("pfadd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD M packed_reciprocal(M a) {
    M v;
    __asm__ volatile("pfrcp %1,%0" : "=y"(v) : "y"(a));
    return v;
}
AMD M reciprocal_one(M a, M b) {
    __asm__ volatile("pfrcpit1 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD M reciprocal_two(M a, M b) {
    __asm__ volatile("pfrcpit2 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
AMD void store_pair(u32 p, M a) {
    __asm__ volatile("movq %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "y"(a) : "memory");
}
} // namespace

namespace {
SSE void store_scalar(u32 p, V a) {
    __asm__ volatile("movss %1,%0" : "=m"(*reinterpret_cast<u32*>(p)) : "x"(a) : "memory");
}
AMD M scalar_pair(u32 p) {
    M a;
    __asm__ volatile("movd %1,%0" : "=y"(a) : "m"(*reinterpret_cast<const u32*>(p)) : "memory");
    return a;
}
AMD void store_scalar_pair(u32 p, M a) {
    __asm__ volatile("movd %1,%0" : "=m"(*reinterpret_cast<u32*>(p)) : "y"(a) : "memory");
}
} // namespace
// Complete141B core; the separate11B wrapper below tails to this actual body.
extern "C" __attribute__((target("mmx,sse"))) u32 recovered_0068a5ce(const u32* arguments) {
    empty();
    const u32 input = word(arguments + 1), matrix = word(arguments + 2), output = word(arguments);
    const M xy = pair(input), x = unpack_dword_low(xy, xy), y = unpack_dword_high(xy, xy),
            z0 = scalar_pair(input + 8), z = unpack_dword_low(z0, z0);
    const M xlo = packed_mul(x, pair(matrix)), ylo = packed_mul(y, pair(matrix + 16)),
            zlo = packed_mul(z, pair(matrix + 32));
    const M tx = packed_add(xlo, pair(matrix + 48)), xhi = packed_mul(x, pair(matrix + 8)),
            yz = packed_add(ylo, zlo);
    const M yhi = packed_mul(y, pair(matrix + 24)), zhi = packed_mul(z, pair(matrix + 40)),
            th = packed_add(xhi, pair(matrix + 56));
    const M lo = packed_add(tx, yz), hi_yz = packed_add(yhi, zhi), hi = packed_add(th, hi_yz),
            w = unpack_dword_high(hi, hi);
    const M guess = packed_reciprocal(w), first = reciprocal_one(w, guess),
            factor = reciprocal_two(first, guess);
    const M result_lo = packed_mul(lo, factor), result_hi = packed_mul(hi, factor);
    store_pair(output, result_lo);
    store_scalar_pair(output + 8, result_hi);
    empty();
    return word(arguments);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068a5ce(void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_0068a5ce\n\taddl $4,%esp\n\tretl $12");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068a824(void*, const void*, const void*) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpopl %ebp\n\tjmp _FUN_0068a5ce@12");
}
extern "C" __attribute__((target("sse"))) u32 recovered_006849a0(const u32* arguments) {
    u32 count = word(arguments + 5), output = word(arguments);
    const u32 matrix = word(arguments + 4);
    if (static_cast<int32_t>(count) < 4) {
        u32 input = word(arguments + 2);
        if (count)
            do {
                output = reinterpret_cast<u32>(FUN_0068a824(reinterpret_cast<void*>(output),
                                                            reinterpret_cast<const void*>(input),
                                                            reinterpret_cast<const void*>(matrix)));
                output += word(arguments + 1);
                input = word(arguments + 2);
                input += word(arguments + 3);
                put(arguments + 2, input);
                count = word(arguments + 5) - 1;
                put(arguments + 5, count);
            } while (count);
    } else {
        alignas(16) V cached[16];
        V c0 = scalar(matrix + 0);
        V c1 = scalar(matrix + 4);
        V c2 = scalar(matrix + 8);
        V c3 = scalar(matrix + 12);
        V c4 = scalar(matrix + 16);
        V c5 = scalar(matrix + 20);
        V c6 = scalar(matrix + 24);
        V c7 = scalar(matrix + 28);
        c0 = shuffle<0>(c0, c0);
        c1 = shuffle<0>(c1, c1);
        c2 = shuffle<0>(c2, c2);
        c3 = shuffle<0>(c3, c3);
        c4 = shuffle<0>(c4, c4);
        c5 = shuffle<0>(c5, c5);
        c6 = shuffle<0>(c6, c6);
        c7 = shuffle<0>(c7, c7);
        cached[0] = c0;
        cached[1] = c1;
        cached[2] = c2;
        cached[3] = c3;
        cached[4] = c4;
        cached[5] = c5;
        cached[6] = c6;
        cached[7] = c7;
        V c8 = scalar(matrix + 32);
        V c9 = scalar(matrix + 36);
        V c10 = scalar(matrix + 40);
        V c11 = scalar(matrix + 44);
        V c12 = scalar(matrix + 48);
        V c13 = scalar(matrix + 52);
        V c14 = scalar(matrix + 56);
        V c15 = scalar(matrix + 60);
        c8 = shuffle<0>(c8, c8);
        c9 = shuffle<0>(c9, c9);
        c10 = shuffle<0>(c10, c10);
        c11 = shuffle<0>(c11, c11);
        c12 = shuffle<0>(c12, c12);
        c13 = shuffle<0>(c13, c13);
        c14 = shuffle<0>(c14, c14);
        c15 = shuffle<0>(c15, c15);
        cached[8] = c8;
        cached[9] = c9;
        cached[10] = c10;
        cached[11] = c11;
        cached[12] = c12;
        cached[13] = c13;
        cached[14] = c14;
        cached[15] = c15;
        u32 input = word(arguments + 2), input_stride = word(arguments + 3),
            output_stride = word(arguments + 1);
        for (;;) {
            if (static_cast<int32_t>(count) < 4) {
                if (!count)
                    break;
                count -= 4;
                output += output_stride * count;
                input += input_stride * count;
                count = 4;
                input_stride = word(arguments + 3);
                output_stride = word(arguments + 1);
            }
            V p0 = low(input), p1 = low(input + input_stride), z0 = scalar(input + 8),
              z1 = scalar(input + input_stride + 8);
            input += input_stride * 2;
            p0 = unpack_low(p0, p1);
            z0 = unpack_low(z0, z1);
            V p2 = low(input), p3 = low(input + input_stride), z2 = scalar(input + 8),
              z3 = scalar(input + input_stride + 8);
            p2 = unpack_low(p2, p3);
            z2 = unpack_low(z2, z3);
            const V before = p0;
            const V z = low_to_high(z0, z2), x = low_to_high(p0, p2), y = high_to_low(p2, before);
            input += input_stride * 2;
            const V x0 = mul(x, aligned16(cached + 0));
            const V x1 = mul(x, aligned16(cached + 1));
            const V x2 = mul(x, aligned16(cached + 2));
            const V x3 = mul(x, aligned16(cached + 3));
            const V y0 = mul(y, aligned16(cached + 4));
            const V y1 = mul(y, aligned16(cached + 5));
            const V xy0 = add(x0, y0);
            const V xy1 = add(x1, y1);
            const V y2 = mul(y, aligned16(cached + 6));
            const V y3 = mul(y, aligned16(cached + 7));
            const V xy2 = add(x2, y2);
            const V xy3 = add(x3, y3);
            const V z4 = mul(z, aligned16(cached + 8));
            const V z5 = mul(z, aligned16(cached + 9));
            const V z6 = mul(z, aligned16(cached + 10));
            const V z7 = mul(z, aligned16(cached + 11));
            const V xyz0 = add(xy0, z4);
            const V xyz1 = add(xy1, z5);
            const V xyz2 = add(xy2, z6);
            const V xyz3 = add(xy3, z7);
            const V two = aligned16(dat_00717940);
            const V t0 = add(xyz0, aligned16(cached + 12));
            const V t1 = add(xyz1, aligned16(cached + 13));
            const V t2 = add(xyz2, aligned16(cached + 14));
            const V t3 = add(xyz3, aligned16(cached + 15));
            const V guess = reciprocal(t3), product = mul(t3, guess),
                    correction = sub(two, product), factor = mul(guess, correction);
            const V r0 = mul(t0, factor), r1 = mul(t1, factor);
            V r2 = mul(t2, factor);
            const V lowxy = unpack_low(r0, r1), highxy = unpack_high(r0, r1);
            store_low(output, lowxy);
            store_scalar(output + 8, r2);
            r2 = shuffle<249>(r2, r2);
            store_low(output + output_stride, high_to_low(lowxy, lowxy));
            store_scalar(output + output_stride + 8, r2);
            r2 = shuffle<249>(r2, r2);
            output += output_stride * 2;
            store_low(output, highxy);
            store_scalar(output + 8, r2);
            r2 = shuffle<249>(r2, r2);
            store_low(output + output_stride, high_to_low(highxy, highxy));
            store_scalar(output + output_stride + 8, r2);
            output += output_stride * 2;
            count -= 4;
        }
    }
    return word(arguments);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_006849a0(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_006849a0\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((target("sse"))) u32 recovered_00684cc0(const u32* arguments) {
    u32 count = word(arguments + 5), output = word(arguments);
    const u32 matrix = word(arguments + 4);
    if (static_cast<int32_t>(count) < 4) {
        u32 input = word(arguments + 2);
        if (count)
            do {
                output = reinterpret_cast<u32>(FUN_0068a2d7(
                    reinterpret_cast<float*>(output), reinterpret_cast<const float*>(input),
                    reinterpret_cast<const float*>(matrix)));
                output += word(arguments + 1);
                input = word(arguments + 2);
                input += word(arguments + 3);
                put(arguments + 2, input);
                count = word(arguments + 5) - 1;
                put(arguments + 5, count);
            } while (count);
    } else {
        alignas(16) V cached[16];
        V c0 = scalar(matrix + 0);
        V c1 = scalar(matrix + 4);
        V c2 = scalar(matrix + 8);
        V c3 = scalar(matrix + 12);
        V c4 = scalar(matrix + 16);
        V c5 = scalar(matrix + 20);
        V c6 = scalar(matrix + 24);
        V c7 = scalar(matrix + 28);
        c0 = shuffle<0>(c0, c0);
        c1 = shuffle<0>(c1, c1);
        c2 = shuffle<0>(c2, c2);
        c3 = shuffle<0>(c3, c3);
        c4 = shuffle<0>(c4, c4);
        c5 = shuffle<0>(c5, c5);
        c6 = shuffle<0>(c6, c6);
        c7 = shuffle<0>(c7, c7);
        cached[0] = c0;
        cached[1] = c1;
        cached[2] = c2;
        cached[3] = c3;
        cached[4] = c4;
        cached[5] = c5;
        cached[6] = c6;
        cached[7] = c7;
        V c8 = scalar(matrix + 32);
        V c9 = scalar(matrix + 36);
        V c10 = scalar(matrix + 40);
        V c11 = scalar(matrix + 44);
        c8 = shuffle<0>(c8, c8);
        c9 = shuffle<0>(c9, c9);
        c10 = shuffle<0>(c10, c10);
        c11 = shuffle<0>(c11, c11);
        cached[8] = c8;
        cached[9] = c9;
        cached[10] = c10;
        cached[11] = c11;
        u32 input = word(arguments + 2), input_stride = word(arguments + 3),
            output_stride = word(arguments + 1);
        for (;;) {
            if (static_cast<int32_t>(count) < 4) {
                if (!count)
                    break;
                count -= 4;
                output += output_stride * count;
                input += input_stride * count;
                count = 4;
                input_stride = word(arguments + 3);
                output_stride = word(arguments + 1);
            }
            V p0 = low(input), p1 = low(input + input_stride), z0 = scalar(input + 8),
              z1 = scalar(input + input_stride + 8);
            input += input_stride * 2;
            p0 = unpack_low(p0, p1);
            z0 = unpack_low(z0, z1);
            V p2 = low(input), p3 = low(input + input_stride), z2 = scalar(input + 8),
              z3 = scalar(input + input_stride + 8);
            p2 = unpack_low(p2, p3);
            z2 = unpack_low(z2, z3);
            const V before = p0;
            const V z = low_to_high(z0, z2), x = low_to_high(p0, p2), y = high_to_low(p2, before);
            input += input_stride * 2;
            const V x0 = mul(x, aligned16(cached + 0));
            const V x1 = mul(x, aligned16(cached + 1));
            const V x2 = mul(x, aligned16(cached + 2));
            const V y0 = mul(y, aligned16(cached + 4));
            const V y1 = mul(y, aligned16(cached + 5));
            const V y2 = mul(y, aligned16(cached + 6));
            const V xy0 = add(x0, y0);
            const V xy1 = add(x1, y1);
            const V xy2 = add(x2, y2);
            const V z4 = mul(z, aligned16(cached + 8));
            const V z5 = mul(z, aligned16(cached + 9));
            const V z6 = mul(z, aligned16(cached + 10));
            const V xyz0 = add(xy0, z4);
            const V xyz1 = add(xy1, z5);
            const V xyz2 = add(xy2, z6);
            const V r0 = xyz0, r1 = xyz1;
            V r2 = xyz2;
            const V lowxy = unpack_low(r0, r1), highxy = unpack_high(r0, r1);
            store_low(output, lowxy);
            store_scalar(output + 8, r2);
            r2 = shuffle<249>(r2, r2);
            store_low(output + output_stride, high_to_low(lowxy, lowxy));
            store_scalar(output + output_stride + 8, r2);
            r2 = shuffle<249>(r2, r2);
            output += output_stride * 2;
            store_low(output, highxy);
            store_scalar(output + 8, r2);
            r2 = shuffle<249>(r2, r2);
            store_low(output + output_stride, high_to_low(highxy, highxy));
            store_scalar(output + output_stride + 8, r2);
            output += output_stride * 2;
            count -= 4;
        }
    }
    return word(arguments);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00684cc0(void*, u32, const void*, u32,
                                                              const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_00684cc0\n\taddl $4,%esp\n\tretl $24");
}
extern "C" alignas(16) uint32_t dat_00717940[4] = {0x40000000u, 0x40000000u, 0x40000000u,
                                                   0x40000000u};
