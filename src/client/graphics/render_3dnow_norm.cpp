#include "graphics/render_3dnow_norm.h"
extern "C" alignas(8) const float dat_006f01d0[2] = {0x1p-126f, 0x1p-126f};

namespace {
using Packed = long long __attribute__((vector_size(8)));
struct PairBytes {
    unsigned char bytes[8];
};
#define MMX_INLINE __attribute__((target("mmx,3dnow"), always_inline)) inline
MMX_INLINE void media_empty() {
    __asm__ __volatile__("femms" ::
                             : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st",
                               "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                               "memory");
}
MMX_INLINE Packed load_pair(const float* source) {
    Packed value;
    __asm__ __volatile__("movq %1,%0"
                         : "=y"(value)
                         : "m"(*reinterpret_cast<const PairBytes*>(source)));
    return value;
}
MMX_INLINE Packed load_single(const float* source) {
    Packed value;
    __asm__ __volatile__("movd %1,%0" : "=y"(value) : "m"(*source));
    return value;
}
MMX_INLINE void store_pair(float* output, Packed value) {
    __asm__ __volatile__("movq %1,%0" : "=m"(*reinterpret_cast<PairBytes*>(output)) : "y"(value));
}
MMX_INLINE void store_single(float* output, Packed value) {
    __asm__ __volatile__("movd %1,%0" : "=m"(*output) : "y"(value));
}
MMX_INLINE Packed mul(Packed left, Packed right) {
    __asm__ __volatile__("pfmul %1,%0" : "+y"(left) : "y"(right));
    return left;
}
MMX_INLINE Packed add(Packed left, Packed right) {
    __asm__ __volatile__("pfadd %1,%0" : "+y"(left) : "y"(right));
    return left;
}
MMX_INLINE Packed accumulate(Packed value) {
    __asm__ __volatile__("pfacc %0,%0" : "+y"(value));
    return value;
}
MMX_INLINE Packed root_guess(Packed value) {
    Packed result;
    __asm__ __volatile__("pfrsqrt %1,%0" : "=y"(result) : "y"(value));
    return result;
}
MMX_INLINE Packed greater(Packed left) {
    __asm__ __volatile__("pfcmpgt %1,%0"
                         : "+y"(left)
                         : "m"(*reinterpret_cast<const PairBytes*>(dat_006f01d0)));
    return left;
}
MMX_INLINE Packed mask(Packed left, Packed right) {
    __asm__ __volatile__("pand %1,%0" : "+y"(left) : "y"(right));
    return left;
}
MMX_INLINE Packed iterate_one(Packed left, Packed right) {
    __asm__ __volatile__("pfrsqit1 %1,%0" : "+y"(left) : "y"(right));
    return left;
}
MMX_INLINE Packed iterate_two(Packed left, Packed right) {
    __asm__ __volatile__("pfrcpit2 %1,%0" : "+y"(left) : "y"(right));
    return left;
}
} // namespace

extern "C" __attribute__((target("mmx,3dnow"))) float* __attribute__((stdcall))
FUN_0068a340(float* output, const float* input) {
    media_empty();
    const Packed xy = load_pair(input), z = load_single(input + 2);
    const Packed square_xy = mul(xy, xy), square_z = mul(z, z);
    const Packed squared = accumulate(add(square_xy, square_z));
    const Packed guess = root_guess(squared);
    const Packed valid = greater(squared);
    const Packed square_guess = mul(guess, guess);
    const Packed first = iterate_one(squared, square_guess);
    const Packed masked_xy = mask(xy, valid), masked_z = mask(z, valid);
    const Packed factor = iterate_two(first, guess);
    const Packed normalized_xy = mul(masked_xy, factor), normalized_z = mul(masked_z, factor);
    store_pair(output, normalized_xy);
    store_single(output + 2, normalized_z);
    media_empty();
    return output;
}
