#include "graphics/render_simd_inverse.h"
#include <stdint.h>
namespace {
using Vector = float __attribute__((vector_size(16)));
struct PairWords {
    uint64_t low, high;
};
struct PairBytes {
    unsigned char bytes[8];
};
#define SSE_INLINE __attribute__((target("sse"), always_inline)) inline
SSE_INLINE uint64_t load_word_pair(const float* pointer) {
    uint64_t value;
    __builtin_memcpy(&value, pointer, 8);
    return value;
}
SSE_INLINE Vector from_words(const PairWords& words) {
    Vector value;
    __builtin_memcpy(&value, &words, 16);
    return value;
}
SSE_INLINE Vector zero() {
    Vector value;
    __asm__ __volatile__("xorps %0,%0" : "=x"(value));
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
SSE_INLINE Vector subps(Vector a, Vector b) {
    __asm__ __volatile__("subps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE_INLINE Vector mulss(Vector a, Vector b) {
    __asm__ __volatile__("mulss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE_INLINE Vector addss(Vector a, Vector b) {
    __asm__ __volatile__("addss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE_INLINE Vector subss(Vector a, Vector b) {
    __asm__ __volatile__("subss %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE_INLINE Vector rcpss(Vector value) {
    __asm__ __volatile__("rcpss %0,%0" : "+x"(value));
    return value;
}
template <unsigned selection> SSE_INLINE Vector shuffle(Vector a, Vector b) {
    __asm__ __volatile__("shufps %2,%1,%0" : "+x"(a) : "x"(b), "i"(selection));
    return a;
}
SSE_INLINE bool equal_or_unordered(Vector a, Vector b) {
    bool result;
    __asm__ __volatile__("comiss %2,%1" : "=@cce"(result) : "x"(a), "x"(b) : "cc");
    return result;
}
SSE_INLINE void store_scalar(float* output, Vector value) {
    __asm__ __volatile__("movss %1,%0" : "=m"(*output) : "x"(value));
}
SSE_INLINE void store_low(float* output, Vector value) {
    __asm__ __volatile__("movlps %1,%0" : "=m"(*reinterpret_cast<PairBytes*>(output)) : "x"(value));
}
SSE_INLINE void store_high(float* output, Vector value) {
    __asm__ __volatile__("movhps %1,%0" : "=m"(*reinterpret_cast<PairBytes*>(output)) : "x"(value));
}
} // namespace

// Actual original packed data flow; no generic matrix-inversion replacement.
extern "C" __attribute__((target("sse"))) D3DMATRIX* __attribute__((stdcall))
FUN_0068070c(D3DMATRIX* matrix, float* determinant, const D3DMATRIX* source) {
    const auto* input = reinterpret_cast<const float*>(source);
    const Vector vector_000 = zero(); // original0068072e
    alignas(16) PairWords xmm2_bits;
    xmm2_bits.low = load_word_pair(input + 2); // original00680731
    alignas(16) PairWords xmm4_bits;
    xmm4_bits.low = load_word_pair(input + 10);      // original00680735
    xmm2_bits.high = load_word_pair(input + 6);      // original00680739
    const Vector vector_001 = from_words(xmm2_bits); // original00680739
    xmm4_bits.high = load_word_pair(input + 14);     // original0068073d
    const Vector vector_002 = from_words(xmm4_bits); // original0068073d
    alignas(16) PairWords xmm3_bits;
    xmm3_bits.low = load_word_pair(input + 8); // original00680741
    alignas(16) PairWords xmm1_bits;
    xmm1_bits.low = load_word_pair(input + 0);                       // original00680745
    xmm3_bits.high = load_word_pair(input + 12);                     // original00680748
    const Vector vector_003 = from_words(xmm3_bits);                 // original00680748
    xmm1_bits.high = load_word_pair(input + 4);                      // original0068074c
    const Vector vector_004 = from_words(xmm1_bits);                 // original0068074c
    const Vector vector_005 = shuffle<0x88>(vector_001, vector_002); // original00680753
    const Vector vector_006 = shuffle<0xdd>(vector_002, vector_001); // original00680757
    const Vector vector_007 = mulps(vector_006, vector_005);         // original0068075e
    const Vector vector_008 = shuffle<0xb1>(vector_007, vector_007); // original00680761
    const Vector vector_009 = shuffle<0x4e>(vector_008, vector_008); // original00680768
    const Vector vector_010 = shuffle<0xdd>(vector_003, vector_004); // original0068076f
    const Vector vector_011 = shuffle<0x88>(vector_004, vector_003); // original00680773
    const Vector vector_012 = mulps(vector_010, vector_009);         // original0068077a
    const Vector vector_013 = mulps(vector_009, vector_011);         // original0068077d
    const Vector vector_014 = mulps(vector_010, vector_008);         // original0068078a
    const Vector vector_015 = mulps(vector_008, vector_011);         // original0068078d
    const Vector vector_016 = subps(vector_012, vector_014);         // original00680790
    const Vector vector_017 = mulps(vector_010, vector_005);         // original00680796
    const Vector vector_018 = shuffle<0x4e>(vector_005, vector_005); // original00680799
    const Vector vector_019 = shuffle<0xb1>(vector_017, vector_017); // original0068079d
    const Vector vector_020 = mulps(vector_006, vector_019);         // original006807ab
    const Vector vector_021 = addps(vector_020, vector_016);         // original006807ae
    const Vector vector_022 = shuffle<0x4e>(vector_019, vector_019); // original006807b4
    const Vector vector_023 = mulps(vector_019, vector_011);         // original006807b8
    const Vector vector_024 = mulps(vector_006, vector_022);         // original006807c5
    const Vector vector_025 = mulps(vector_022, vector_011);         // original006807c8
    const Vector vector_026 = subps(vector_021, vector_024);         // original006807cb
    const Vector vector_027 = shuffle<0x4e>(vector_010, vector_010); // original006807d1
    const Vector vector_028 = mulps(vector_027, vector_006);         // original006807d5
    const Vector vector_029 = shuffle<0xb1>(vector_028, vector_028); // original006807d8
    const Vector vector_030 = mulps(vector_018, vector_029);         // original006807e6
    const Vector vector_031 = addps(vector_030, vector_026);         // original006807e9
    const Vector vector_032 = shuffle<0x4e>(vector_029, vector_029); // original006807ef
    const Vector vector_033 = mulps(vector_029, vector_011);         // original006807f3
    const Vector vector_034 = mulps(vector_018, vector_032);         // original00680800
    const Vector vector_035 = mulps(vector_032, vector_011);         // original00680803
    const Vector vector_036 = subps(vector_031, vector_034);         // original00680806
    const Vector vector_037 = subps(vector_035, vector_033);         // original00680809
    const Vector vector_038 = mulps(vector_011, vector_036);         // original0068080f
    const Vector vector_039 = shuffle<0x4e>(vector_037, vector_037); // original00680812
    const Vector vector_040 = shuffle<0x4e>(vector_038, vector_038); // original00680819
    const Vector vector_041 = addps(vector_040, vector_038);         // original00680824
    const Vector vector_042 = shuffle<0xb1>(vector_041, vector_041); // original0068082a
    const Vector vector_043 = addss(vector_042, vector_041);         // original0068082e
    const Vector vector_044 = mulps(vector_010, vector_011);         // original0068083c
    const Vector vector_045 = shuffle<0xb1>(vector_044, vector_044); // original0068083f
    const Vector vector_046 = shuffle<0x4e>(vector_045, vector_045); // original00680846
    const Vector vector_047 = mulps(vector_006, vector_045);         // original0068085c
    const Vector vector_048 = addps(vector_047, vector_039);         // original0068085f
    const Vector vector_049 = mulps(vector_006, vector_046);         // original00680865
    const Vector vector_050 = subps(vector_049, vector_048);         // original00680868
    const Vector vector_051 = mulps(vector_006, vector_011);         // original0068086e
    const Vector vector_052 = shuffle<0xb1>(vector_051, vector_051); // original00680871
    const Vector vector_053 = mulps(vector_052, vector_010);         // original00680884
    const Vector vector_054 = addps(vector_053, vector_050);         // original00680887
    const Vector vector_055 = shuffle<0x4e>(vector_052, vector_052); // original0068088d
    const Vector vector_056 = mulps(vector_010, vector_055);         // original00680898
    const Vector vector_057 = subps(vector_054, vector_056);         // original006808a5
    const Vector vector_058 = subps(vector_013, vector_015);         // original006808b6
    const Vector vector_059 = shuffle<0x4e>(vector_058, vector_058); // original006808b9
    const Vector vector_060 = mulps(vector_052, vector_018);         // original006808c1
    const Vector vector_061 = mulps(vector_055, vector_018);         // original006808c4
    const Vector vector_062 = subps(vector_059, vector_060);         // original006808c7
    const Vector vector_063 = mulps(vector_011, vector_018);         // original006808ca
    const Vector vector_064 = addps(vector_061, vector_062);         // original006808cd
    const Vector vector_065 = shuffle<0xb1>(vector_063, vector_063); // original006808d0
    const Vector vector_066 = shuffle<0x4e>(vector_065, vector_065); // original006808d7
    const Vector vector_067 = mulps(vector_006, vector_065);         // original006808e6
    const Vector vector_068 = mulps(vector_006, vector_066);         // original006808e9
    const Vector vector_069 = addps(vector_067, vector_064);         // original006808ec
    const Vector vector_070 = subps(vector_069, vector_068);         // original006808f5
    const Vector vector_071 = subps(vector_025, vector_023);         // original00680906
    const Vector vector_072 = shuffle<0x4e>(vector_071, vector_071); // original00680909
    const Vector vector_073 = mulps(vector_045, vector_018);         // original00680911
    const Vector vector_074 = subps(vector_073, vector_072);         // original00680914
    const Vector vector_075 = mulps(vector_018, vector_046);         // original0068091b
    const Vector vector_076 = subps(vector_074, vector_075);         // original0068091e
    const Vector vector_077 = mulps(vector_065, vector_010);         // original00680925
    const Vector vector_078 = mulps(vector_010, vector_066);         // original00680928
    const Vector vector_079 = subps(vector_076, vector_077);         // original0068092b
    const Vector vector_080 = addps(vector_078, vector_079);         // original00680931
    const Vector saved_row2 = vector_057;                            // original680937
    if (equal_or_unordered(vector_043, vector_000))
        return nullptr; // original680934/68093b
    if (determinant != nullptr)
        store_scalar(determinant, vector_043);
    const Vector reciprocal = rcpss(vector_043);
    const Vector reciprocal_square = mulss(reciprocal, reciprocal);
    const Vector product = mulss(vector_043, reciprocal_square);
    const Vector twice = addss(reciprocal, reciprocal);
    const Vector difference = subss(twice, product);
    const Vector factor = shuffle<0>(difference, difference);
    auto* output = reinterpret_cast<float*>(matrix);
    const Vector row0 = mulps(vector_036, factor);
    store_low(output, row0);
    store_high(output + 2, row0);
    const Vector row1 = mulps(vector_070, factor);
    store_low(output + 4, row1);
    store_high(output + 6, row1);
    const Vector row2 = mulps(saved_row2, factor);
    store_low(output + 8, row2);
    store_high(output + 10, row2);
    const Vector row3 = mulps(factor, vector_080);
    store_low(output + 12, row3);
    store_high(output + 14, row3);
    return matrix;
}
