#include "graphics/render_matrix_scalar.h"
namespace {
void copy_sixteen_words(void* target, const void* input) {
    auto* destination = target;
    const void* source = input;
    unsigned count = 16;
    __asm__ __volatile__("rep movsl" : "+D"(destination), "+S"(source), "+c"(count)::"memory");
}
// Actual FLD ST(3)/FMUL sequence, followed by FXCH3/FADDP/FXCH2/FADDP/FADDP.
// These names record the original four cached stack operands and product order.
float original_dot(long double loaded_0, long double loaded_1, long double loaded_2,
                   long double loaded_3, const float* factors, unsigned stride) {
    const volatile long double product_0 = loaded_0 * static_cast<long double>(factors[0]);
    const volatile long double product_1 = loaded_1 * static_cast<long double>(factors[stride]);
    const volatile long double product_2 = loaded_2 * static_cast<long double>(factors[2 * stride]);
    const volatile long double product_3 = loaded_3 * static_cast<long double>(factors[3 * stride]);
    const volatile long double sum_20 = product_2 + product_0;
    const volatile long double sum_13 = product_1 + product_3;
    const volatile long double sum_all = sum_20 + sum_13;
    return static_cast<float>(sum_all);
}
} // namespace
extern "C" D3DMATRIX* __attribute__((stdcall))
FUN_0064f4b5(D3DMATRIX* matrix, const D3DMATRIX* first, const D3DMATRIX* second) {
    const auto* left = reinterpret_cast<const float*>(first);
    const auto* right = reinterpret_cast<const float*>(second);
    auto* output = reinterpret_cast<float*>(matrix);
    float scratch[16];
    if (matrix == second && matrix != first) { // Original64f4c5/64f4ca column-cached path.
        for (unsigned column = 0; column < 4; ++column) {
            const volatile long double loaded_0 = right[column];
            const volatile long double loaded_1 = right[column + 4];
            const volatile long double loaded_2 = right[column + 8];
            const volatile long double loaded_3 = right[column + 12];
            for (unsigned row = 0; row < 4; ++row)
                output[row * 4 + column] =
                    original_dot(loaded_0, loaded_1, loaded_2, loaded_3, left + row * 4, 1);
        }
    } else {
        if (matrix == second) {
            copy_sixteen_words(scratch, right);
            right = scratch;
        }
        for (unsigned row = 0; row < 4; ++row) {
            const volatile long double loaded_0 = left[row * 4];
            const volatile long double loaded_1 = left[row * 4 + 1];
            const volatile long double loaded_2 = left[row * 4 + 2];
            const volatile long double loaded_3 = left[row * 4 + 3];
            for (unsigned column = 0; column < 4; ++column)
                output[row * 4 + column] =
                    original_dot(loaded_0, loaded_1, loaded_2, loaded_3, right + column, 4);
        }
    }
    return matrix;
}
extern "C" D3DMATRIX* __attribute__((stdcall))
FUN_0064f59a(D3DMATRIX* matrix, const D3DMATRIX* first, const D3DMATRIX* second) {
    const auto* left = reinterpret_cast<const float*>(first);
    const auto* right = reinterpret_cast<const float*>(second);
    float scratch[16];
    const bool exact_alias = matrix == first || matrix == second;
    auto* output = exact_alias ? scratch : reinterpret_cast<float*>(matrix);
    for (unsigned row = 0; row < 4; ++row) {
        const volatile long double loaded_0 = left[row * 4];
        const volatile long double loaded_1 = left[row * 4 + 1];
        const volatile long double loaded_2 = left[row * 4 + 2];
        const volatile long double loaded_3 = left[row * 4 + 3];
        for (unsigned column = 0; column < 4; ++column)
            output[column * 4 + row] =
                original_dot(loaded_0, loaded_1, loaded_2, loaded_3, right + column, 4);
    }
    if (exact_alias)
        copy_sixteen_words(matrix, scratch);
    return matrix;
}
