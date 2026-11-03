#include "graphics/render_transform_sse.h"
namespace {
using Vector = float __attribute__((vector_size(16)));
struct BlockBytes {
    unsigned char bytes[16];
};
struct PairBytes {
    unsigned char bytes[8];
};
#define SSE_INLINE __attribute__((target("sse"), always_inline)) inline
SSE_INLINE Vector load_block(const float* source) {
    Vector value;
    __asm__ __volatile__("movups %1,%0"
                         : "=x"(value)
                         : "m"(*reinterpret_cast<const BlockBytes*>(source)));
    return value;
}
SSE_INLINE Vector load_scalar(const float* source) {
    Vector value;
    __asm__ __volatile__("movss %1,%0" : "=x"(value) : "m"(*source));
    return value;
}
SSE_INLINE Vector mulps(Vector a, Vector b) {
    __asm__ __volatile__("mulps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE_INLINE Vector addps(Vector a, Vector b) {
    __asm__ __volatile__("addps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE_INLINE Vector broadcast(Vector a) {
    __asm__ __volatile__("shufps $0,%0,%0" : "+x"(a));
    return a;
}
SSE_INLINE void store_block(float* target, Vector value) {
    __asm__ __volatile__("movups %1,%0"
                         : "=m"(*reinterpret_cast<BlockBytes*>(target))
                         : "x"(value));
}
SSE_INLINE void store_pair(float* target, Vector value) {
    __asm__ __volatile__("movlps %1,%0" : "=m"(*reinterpret_cast<PairBytes*>(target)) : "x"(value));
}
} // namespace
extern "C" __attribute__((target("sse"))) float* __attribute__((stdcall))
FUN_006803ce(float* output, const float* vector, const float* matrix) {
    const Vector matrix_0 = load_block(matrix);                 // Original6803d9.
    const Vector vector_0 = broadcast(load_scalar(vector));     // Original6803dc/6803e0.
    const Vector matrix_1 = load_block(matrix + 4);             // Original6803e4.
    const Vector product_0 = mulps(vector_0, matrix_0);         // Original6803e8.
    const Vector vector_1 = broadcast(load_scalar(vector + 1)); // Original6803eb/6803f0.
    const Vector matrix_3 = load_block(matrix + 12);            // Original6803f4.
    const Vector product_1 = mulps(vector_1, matrix_1);         // Original6803f8.
    const Vector sum_03 = addps(product_0, matrix_3);           // Original6803fe.
    const Vector sum_all = addps(sum_03, product_1);            // Original680401.
    store_block(output, sum_all);
    return output; // Original680404/68040b RET12.
}
extern "C" __attribute__((target("sse"))) float* __attribute__((stdcall))
FUN_00680467(float* output, const float* vector, const float* matrix) {
    const Vector scalar_0 = load_scalar(vector);        // Original680472.
    const Vector matrix_0 = load_block(matrix);         // Original680476.
    const Vector vector_0 = broadcast(scalar_0);        // Original680479.
    const Vector matrix_1 = load_block(matrix + 4);     // Original68047d.
    const Vector scalar_1 = load_scalar(vector + 1);    // Original680481.
    const Vector product_0 = mulps(vector_0, matrix_0); // Original680486.
    const Vector vector_1 = broadcast(scalar_1);        // Original680489.
    const Vector product_1 = mulps(vector_1, matrix_1); // Original68048d.
    const Vector sum_all = addps(product_0, product_1); // Original680493.
    store_pair(output, sum_all);
    return output; // Original680496/68049d RET12.
}
