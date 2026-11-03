#include "graphics/render_coordinate_sse.h"
namespace {
using V = float __attribute__((vector_size(16)));
struct B4 {
    unsigned char b[4];
};
struct B8 {
    unsigned char b[8];
};
struct B16 {
    unsigned char b[16];
};
#define SIMD __attribute__((target("sse"), always_inline)) inline
uint32_t word(const uint32_t* p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
SIMD V block(uint32_t p) {
    V v;
    __asm__ volatile("movups %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SIMD V aligned(uint32_t p) {
    V v;
    __asm__ volatile("movaps %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return v;
}
SIMD V low(uint32_t p) {
    V v{};
    __asm__ volatile("movlps %1,%0" : "+x"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
SIMD V high(V v, uint32_t p) {
    __asm__ volatile("movhps %1,%0" : "+x"(v) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return v;
}
SIMD V halves(uint32_t p) {
    return high(low(p), p + 8);
}
SIMD V scalar(uint32_t p) {
    V v;
    __asm__ volatile("movss %1,%0" : "=x"(v) : "m"(*reinterpret_cast<const B4*>(p)) : "memory");
    return v;
}
SIMD V scalar_word(uint32_t value) {
    V v;
    __asm__ volatile("movss %1,%0" : "=x"(v) : "m"(value) : "memory");
    return v;
}
template <int mask> SIMD V shuffle(V a) {
    __asm__ volatile("shufps %1,%0,%0" : "+x"(a) : "i"(mask));
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
SIMD V reciprocal(V a) {
    V r;
    __asm__ volatile("rcpps %1,%0" : "=x"(r) : "x"(a));
    return r;
}
SIMD V high_to_low(V a) {
    __asm__ volatile("movhlps %0,%0" : "+x"(a));
    return a;
}
SIMD void store_low(uint32_t p, V a) {
    __asm__ volatile("movlps %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(a) : "memory");
}
SIMD void store_scalar(uint32_t p, V a) {
    __asm__ volatile("movss %1,%0" : "=m"(*reinterpret_cast<B4*>(p)) : "x"(a) : "memory");
}
} // namespace
extern "C" __attribute__((target("sse"))) void*
recovered_sse_coordinate2(const uint32_t* arguments) {
    const uint32_t matrix = word(arguments + 2), input = word(arguments + 1);
    const V row_zero = block(matrix), x = shuffle<0>(scalar(input));
    const V row_one = block(matrix + 16), x_product = mul(x, row_zero);
    const V y = shuffle<0>(scalar(input + 4)), row_three = block(matrix + 48);
    const V y_product = mul(y, row_one);
    const uint32_t output = word(arguments);
    const V translated = add(x_product, row_three), coordinates = add(translated, y_product);
    const V guess = reciprocal(coordinates), squared_guess = mul(guess, guess),
            twice_guess = add(guess, guess);
    const V correction = mul(squared_guess, coordinates), refined = sub(twice_guess, correction);
    const V factor = shuffle<0xff>(refined), result = mul(coordinates, factor);
    store_low(output, result);
    return reinterpret_cast<void*>(word(arguments));
}
extern "C" __attribute__((target("sse"))) void*
recovered_sse_coordinate3(const uint32_t* arguments) {
    const uint32_t input = word(arguments + 1), matrix = word(arguments + 2);
    const V xy = low(input);
    const uint32_t zword = word(reinterpret_cast<const uint32_t*>(input + 8));
    V translated, y_product, x, row_zero;
    if ((matrix & 15) == 0) {
        const V row_three = aligned(matrix + 48), row_two = aligned(matrix + 32),
                z = shuffle<0>(scalar_word(zword));
        const V z_product = mul(row_two, z);
        translated = add(z_product, row_three);
        const V row_one = aligned(matrix + 16), y = shuffle<0x55>(xy);
        y_product = mul(row_one, y);
        x = shuffle<0>(xy);
        row_zero = aligned(matrix);
    } else {
        const V row_three = halves(matrix + 48), row_two = halves(matrix + 32),
                z = shuffle<0>(scalar_word(zword));
        const V z_product = mul(row_two, z);
        translated = add(z_product, row_three);
        const V row_one = halves(matrix + 16), y = shuffle<0x55>(xy);
        y_product = mul(row_one, y);
        x = shuffle<0>(xy);
        row_zero = halves(matrix);
    }
    const uint32_t output = word(arguments);
    const V x_product = mul(row_zero, x), xy_product = add(x_product, y_product),
            coordinates = add(xy_product, translated);
    const V guess = reciprocal(coordinates), product = mul(guess, coordinates),
            second_product = mul(product, guess), twice_guess = add(guess, guess);
    const V refined = sub(twice_guess, second_product), factor = shuffle<0xff>(refined),
            result = mul(coordinates, factor), z = high_to_low(result);
    store_low(output, result);
    store_scalar(output + 8, z);
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_0068040e(void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_coordinate2\n\taddl $4,%esp\n\tretl $12");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_00681975(void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_coordinate3\n\taddl $4,%esp\n\tretl $12");
}
