#include "graphics/render_transform_sse_aligned.h"
#include <stdint.h>
namespace {
using Vector = float __attribute__((vector_size(16)));
struct BlockBytes {
    unsigned char bytes[16];
};
struct PairBytes {
    unsigned char bytes[8];
};
#define SSE_INLINE __attribute__((target("sse"), always_inline)) inline
SSE_INLINE Vector load_private(const unsigned char* source) {
    Vector value;
    __asm__ __volatile__("movaps %1,%0"
                         : "=x"(value)
                         : "m"(*reinterpret_cast<const BlockBytes*>(source)));
    return value;
}
SSE_INLINE Vector load_aligned(const float* source) {
    Vector value;
    __asm__ __volatile__("movaps %1,%0"
                         : "=x"(value)
                         : "m"(*reinterpret_cast<const BlockBytes*>(source)));
    return value;
}
SSE_INLINE Vector load_unaligned(const float* source) {
    Vector value;
    __asm__ __volatile__("movups %1,%0"
                         : "=x"(value)
                         : "m"(*reinterpret_cast<const BlockBytes*>(source)));
    return value;
}
SSE_INLINE Vector load_partial(const float* source, const unsigned char* original_private) {
    Vector value = load_private(original_private);
    __asm__ __volatile__("movlps %1,%0"
                         : "+x"(value)
                         : "m"(*reinterpret_cast<const PairBytes*>(source)));
    return value;
}
SSE_INLINE Vector load_pair_row(const float* source, const unsigned char* original_private) {
    Vector value = load_partial(source, original_private);
    __asm__ __volatile__("movhps %1,%0"
                         : "+x"(value)
                         : "m"(*reinterpret_cast<const PairBytes*>(source + 2)));
    return value;
}
SSE_INLINE uint32_t raw_word(const float* source) {
    uint32_t word;
    __builtin_memcpy(&word, source, 4);
    return word;
}
SSE_INLINE Vector scalar_from_word(const uint32_t& word) {
    Vector value;
    __asm__ __volatile__("movss %1,%0" : "=x"(value) : "m"(word));
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
template <unsigned selection> SSE_INLINE Vector broadcast(Vector a) {
    __asm__ __volatile__("shufps %1,%0,%0" : "+x"(a) : "i"(selection));
    return a;
}
SSE_INLINE Vector high_to_low(Vector value) {
    __asm__ __volatile__("movhlps %0,%0" : "+x"(value));
    return value;
}
SSE_INLINE void store_scalar(float* target, Vector value) {
    __asm__ __volatile__("movss %1,%0" : "=m"(*target) : "x"(value));
}
SSE_INLINE void store_pair(float* target, Vector value) {
    __asm__ __volatile__("movlps %1,%0" : "=m"(*reinterpret_cast<PairBytes*>(target)) : "x"(value));
}
SSE_INLINE void store_block(float* target, Vector value) {
    __asm__ __volatile__("movups %1,%0"
                         : "=m"(*reinterpret_cast<BlockBytes*>(target))
                         : "x"(value));
}
} // namespace

// Actual private MOVAPS reads remain explicit hardware operations. Partial
// input upper lanes carry those private bytes until SHUFPS0/55 selects only the
// defined low pair. Every row partial load is completed by MOVHPS before use.
extern "C" __attribute__((target("sse"))) float* __attribute__((stdcall))
FUN_006818a9(float* output, const float* vector, const float* matrix) {
    alignas(16) unsigned char original_private[16];
    Vector x_product, y_product, z_product;
    if ((reinterpret_cast<uintptr_t>(matrix) & 15) == 0) {        // Original6818c1 TEST/JNE.
        const Vector xy = load_partial(vector, original_private); // Original6818c5/6818c9.
        const uint32_t z_word = raw_word(vector + 2);
        const Vector matrix_2 = load_aligned(matrix + 8);
        const Vector z = broadcast<0>(scalar_from_word(z_word));
        z_product = mulps(z, matrix_2); // Original6818df preserves operand order.
        const Vector matrix_1 = load_aligned(matrix + 4);
        const Vector y = broadcast<0x55>(xy);
        y_product = mulps(y, matrix_1);
        const Vector matrix_0 = load_aligned(matrix);
        const Vector x = broadcast<0>(xy);
        x_product = mulps(x, matrix_0);
    } else {
        const Vector xy = load_partial(vector, original_private); // Original681905/681909.
        const uint32_t z_word = raw_word(vector + 2);
        const Vector matrix_2 = load_pair_row(matrix + 8, original_private);
        const Vector matrix_1 = load_pair_row(matrix + 4, original_private);
        const Vector z = broadcast<0>(scalar_from_word(z_word));
        z_product = mulps(matrix_2, z); // Original681933 reverses these operands.
        const Vector y = broadcast<0x55>(xy);
        const Vector x = broadcast<0>(xy);
        const Vector matrix_0 = load_pair_row(matrix, original_private);
        y_product = mulps(matrix_1, y);
        x_product = mulps(x, matrix_0);
    }
    const Vector sum_xy = addps(x_product, y_product); // Original681958.
    const Vector sum_all = addps(sum_xy, z_product);   // Original68195b.
    const Vector high = high_to_low(sum_all);          // Original681961.
    store_pair(output, sum_all);
    store_scalar(output + 2, high);
    return output;
}

extern "C" __attribute__((target("sse"))) float* __attribute__((stdcall))
FUN_00683686(float* output, const float* vector, const float* matrix) {
    alignas(16) unsigned char original_private[16];
    const Vector input = load_unaligned(vector); // Original68369b.
    const Vector w = broadcast<0xff>(input);
    Vector matrix_0, x, y_product, sum_zw;
    if ((reinterpret_cast<uintptr_t>(matrix) & 15) == 0) {
        const Vector matrix_3 = load_aligned(matrix + 12);
        const Vector matrix_2 = load_aligned(matrix + 8);
        const Vector w_product = mulps(matrix_3, w);
        const Vector z = broadcast<0xaa>(input);
        const Vector z_product = mulps(matrix_2, z);
        sum_zw = addps(z_product, w_product);
        const Vector matrix_1 = load_aligned(matrix + 4);
        const Vector y = broadcast<0x55>(input);
        y_product = mulps(matrix_1, y);
        x = broadcast<0>(input);
        matrix_0 = load_aligned(matrix);
    } else {
        const Vector matrix_3 = load_pair_row(matrix + 12, original_private);
        const Vector matrix_2 = load_pair_row(matrix + 8, original_private);
        const Vector w_product = mulps(matrix_3, w);
        const Vector z = broadcast<0xaa>(input);
        const Vector z_product = mulps(matrix_2, z);
        sum_zw = addps(z_product, w_product);
        const Vector matrix_1 = load_pair_row(matrix + 4, original_private);
        const Vector y = broadcast<0x55>(input);
        y_product = mulps(matrix_1, y);
        x = broadcast<0>(input);
        matrix_0 = load_pair_row(matrix, original_private);
    }
    const Vector x_product = mulps(matrix_0, x);
    const Vector sum_xy = addps(x_product, y_product);
    const Vector sum_all = addps(sum_xy, sum_zw);
    store_block(output, sum_all);
    return output;
}

extern "C" __attribute__((target("sse"))) float* __attribute__((stdcall))
FUN_00683e19(float* output, const float* vector, const float* matrix) {
    alignas(16) unsigned char original_private[16];
    const Vector xy = load_partial(vector, original_private); // Original683e2e/683e32.
    const uint32_t z_word = raw_word(vector + 2);             // Original683e35 raw GPR snapshot.
    Vector matrix_0, x, y_product, sum_zw;
    if ((reinterpret_cast<uintptr_t>(matrix) & 15) == 0) {
        const Vector matrix_3 = load_aligned(matrix + 12);
        const Vector matrix_2 = load_aligned(matrix + 8);
        const Vector z = broadcast<0>(scalar_from_word(z_word));
        const Vector z_product = mulps(matrix_2, z);
        sum_zw = addps(z_product, matrix_3);
        const Vector matrix_1 = load_aligned(matrix + 4);
        const Vector y = broadcast<0x55>(xy);
        y_product = mulps(matrix_1, y);
        x = broadcast<0>(xy);
        matrix_0 = load_aligned(matrix);
    } else {
        const Vector matrix_3 = load_pair_row(matrix + 12, original_private);
        const Vector matrix_2 = load_pair_row(matrix + 8, original_private);
        const Vector z = broadcast<0>(scalar_from_word(z_word));
        const Vector z_product = mulps(matrix_2, z);
        sum_zw = addps(z_product, matrix_3);
        const Vector matrix_1 = load_pair_row(matrix + 4, original_private);
        const Vector y = broadcast<0x55>(xy);
        y_product = mulps(matrix_1, y);
        x = broadcast<0>(xy);
        matrix_0 = load_pair_row(matrix, original_private);
    }
    const Vector x_product = mulps(matrix_0, x);
    const Vector sum_xy = addps(x_product, y_product);
    const Vector sum_all = addps(sum_xy, sum_zw);
    store_block(output, sum_all);
    return output;
}
