#include "graphics/render_sse_amd_fallback_norm_transform.h"
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
#define AMD __attribute__((target("mmx,3dnow"), always_inline)) inline
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

// Complete00684740..006848f6: actual signed-small-count AMD tail and SSE
// four-point normal arithmetic, including overlapping last quartet.
extern "C" __attribute__((target("sse"))) u32 recovered_00684740(const u32* arguments) {
    u32 count = word(arguments + 5), output = word(arguments);
    const u32 matrix = word(arguments + 4);
    if (static_cast<int32_t>(count) < 4) {
        u32 input = word(arguments + 2);
        if (count)
            do {
                output = reinterpret_cast<uintptr_t>(FUN_0068b092(
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
        alignas(16) V cached[8];
        V a = scalar(matrix), b = scalar(matrix + 4), c = scalar(matrix + 8),
          d = scalar(matrix + 12);
        a = shuffle<0>(a, a);
        b = shuffle<0>(b, b);
        c = shuffle<0>(c, c);
        d = shuffle<0>(d, d);
        V e = scalar(matrix + 16), f = scalar(matrix + 20), g = scalar(matrix + 24),
          h = scalar(matrix + 28);
        e = shuffle<0>(e, e);
        f = shuffle<0>(f, f);
        g = shuffle<0>(g, g);
        h = shuffle<0>(h, h);
        cached[0] = a;
        cached[1] = b;
        cached[2] = c;
        cached[3] = d;
        cached[4] = e;
        cached[5] = f;
        cached[6] = g;
        cached[7] = h;
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
            V p0 = low(input), p1 = low(input + input_stride);
            input += input_stride * 2;
            p0 = unpack_low(p0, p1);
            V p2 = low(input), p3 = low(input + input_stride);
            p2 = unpack_low(p2, p3);
            const V before = p0, x = low_to_high(p0, p2), y = high_to_low(p2, before);
            input += input_stride * 2;
            const V x0 = mul(x, aligned16(cached)), x1 = mul(x, aligned16(cached + 1));
            const V y0 = mul(y, aligned16(cached + 4)), y1 = mul(y, aligned16(cached + 5));
            const V r0 = add(x0, y0), r1 = add(x1, y1), lowxy = unpack_low(r0, r1),
                    highxy = unpack_high(r0, r1);
            store_low(output, lowxy);
            store_low(output + output_stride, high_to_low(lowxy, lowxy));
            output += output_stride * 2;
            store_low(output, highxy);
            store_low(output + output_stride, high_to_low(highxy, highxy));
            output += output_stride * 2;
            count -= 4;
        }
    }
    return word(arguments);
}

// Complete00684900..00684989: three-component scalar lane broadcasts and
// paired packed sums; all four matrix rows are read on positive counts.
extern "C" __attribute__((target("sse"))) u32 recovered_00684900(const u32* arguments) {
    u32 count = word(arguments + 5), output = word(arguments), input = word(arguments + 2);
    const u32 matrix = word(arguments + 4);
    if (static_cast<int32_t>(count) > 0) {
        const u32 input_stride = word(arguments + 3), output_stride = word(arguments + 1);
        const V row0 = load16(matrix), row1 = load16(matrix + 16), row2 = load16(matrix + 32),
                row3 = load16(matrix + 48);
        do {
            const V x0 = scalar(input), x = shuffle<0>(x0, x0), y0 = scalar(input + 4),
                    y = shuffle<0>(y0, y0);
            const V z0 = scalar(input + 8), z = shuffle<0>(z0, z0);
            input += input_stride;
            const V a = mul(x, row0), b = mul(y, row1), c = mul(z, row2);
            const V ab = add(a, b), cd = add(c, row3), result = add(ab, cd);
            store16(output, result);
            output += output_stride;
            count -= 1;
        } while (static_cast<int32_t>(count) > 0);
    }
    return word(arguments);
}
#define ARRAY_ENTRY(address)                                                                       \
    extern "C" __attribute__((naked, stdcall)) void* FUN_##address(void*, u32, const void*, u32,   \
                                                                   const void*, u32) {             \
        __asm__ volatile("leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_" #address           \
                         "\n\taddl $4,%esp\n\tretl $24");                                          \
    }
ARRAY_ENTRY(00684740)
ARRAY_ENTRY(00684900)
#undef ARRAY_ENTRY
