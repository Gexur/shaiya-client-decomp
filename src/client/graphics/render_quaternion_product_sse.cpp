#include "graphics/render_quaternion_product_sse.h"
#include "graphics/render_quaternion_product_sse_data.inc"
namespace {
using V = float __attribute__((vector_size(16)));
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
SIMD V zero() {
    V v;
    __asm__ volatile("xorps %0,%0" : "=x"(v));
    return v;
}
SIMD V low(V a, uint32_t p) {
    __asm__ volatile("movlps %1,%0" : "+x"(a) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return a;
}
SIMD V high(V a, uint32_t p) {
    __asm__ volatile("movhps %1,%0" : "+x"(a) : "m"(*reinterpret_cast<const B8*>(p)) : "memory");
    return a;
}
template <unsigned k> SIMD V shuffle(V a) {
    __asm__ volatile("shufps %1,%0,%0" : "+x"(a) : "i"(k));
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
SIMD V mask(V a, const uint32_t* p) {
    __asm__ volatile("xorps %1,%0" : "+x"(a) : "m"(*reinterpret_cast<const B16*>(p)) : "memory");
    return a;
}
SIMD void put_low(uint32_t p, V a) {
    __asm__ volatile("movlps %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(a) : "memory");
}
SIMD void put_high(uint32_t p, V a) {
    __asm__ volatile("movhps %1,%0" : "=m"(*reinterpret_cast<B8*>(p)) : "x"(a) : "memory");
}
} // namespace
// Complete original680048..6800c3; distinct named values follow its actual
// MOVLPS/MOVHPS/shuffle/multiply/XOR/add order, including late output reload.
extern "C" __attribute__((target("sse"))) void*
recovered_sse_quaternion_product(const uint32_t* arguments) {
    const uint32_t right = word(arguments + 2);         // 68004e
    const uint32_t left = word(arguments + 1);          // 680051
    const uint32_t output = word(arguments);            // 680054
    const V right_low = low(zero(), right);             // 680057; high lanes overwritten next
    const V right_all = high(right_low, right + 8);     // 68005a
    const V left_low = low(zero(), left);               // 68005e; high lanes overwritten next
    const V left_all = high(left_low, left + 8);        // 680061
    const V right_w = shuffle<0xff>(right_all);         // 680068
    const V product_w = mul(right_w, left_all);         // 68006c
    const V right_x = shuffle<0x00>(right_all);         // 680072
    const V left_reverse = shuffle<0x1b>(left_all);     // 680076
    const V signed_x = mask(right_x, dat_006f38c0 + 8); // 68007a
    const V product_x = mul(signed_x, left_reverse);    // 680081
    const V sum_wx = add(product_w, product_x);         // 680084
    const V right_y = shuffle<0x55>(right_all);         // 68008a
    const V left_y = shuffle<0xb1>(left_reverse);       // 68008e
    const V signed_y = mask(right_y, dat_006f38c0 + 4); // 680092
    const V product_y = mul(signed_y, left_y);          // 680099
    const V sum_wxy = add(sum_wx, product_y);           // 68009c
    const V right_z = shuffle<0xaa>(right_all);         // 68009f
    const V left_z = shuffle<0x1b>(left_y);             // 6800a3
    const V signed_z = mask(right_z, dat_006f38c0);     // 6800a7
    const V product_z = mul(signed_z, left_z);          // 6800ae
    const V sum = add(sum_wxy, product_z);              // 6800b1
    put_low(output, sum);                               // 6800b4
    put_high(output + 8, sum);                          // 6800b7
    return reinterpret_cast<void*>(word(arguments));    // 6800bb
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall)) FUN_00680048(void*, const void*,
                                                                              const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_sse_quaternion_product\n\taddl $4,%esp\n\tretl $12");
}
