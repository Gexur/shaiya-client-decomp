#include "graphics/render_matrix_sse.h"
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
SSE_INLINE uint64_t load_word_pair(const float* source) {
    uint64_t value;
    __builtin_memcpy(&value, source, 8);
    return value;
}
SSE_INLINE Vector from_words(const PairWords& words) {
    Vector value;
    __builtin_memcpy(&value, &words, 16);
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
SSE_INLINE Vector unpcklps(Vector a, Vector b) {
    __asm__ __volatile__("unpcklps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
SSE_INLINE Vector unpckhps(Vector a, Vector b) {
    __asm__ __volatile__("unpckhps %1,%0" : "+x"(a) : "x"(b));
    return a;
}
template <unsigned selection> SSE_INLINE Vector shuffle(Vector a, Vector b) {
    __asm__ __volatile__("shufps %2,%1,%0" : "+x"(a) : "x"(b), "i"(selection));
    return a;
}
SSE_INLINE void store_low(float* target, Vector value) {
    __asm__ __volatile__("movlps %1,%0" : "=m"(*reinterpret_cast<PairBytes*>(target)) : "x"(value));
}
SSE_INLINE void store_high(float* target, Vector value) {
    __asm__ __volatile__("movhps %1,%0" : "=m"(*reinterpret_cast<PairBytes*>(target)) : "x"(value));
}
} // namespace
extern "C" __attribute__((target("sse"))) D3DMATRIX* __attribute__((stdcall))
FUN_006804a0(D3DMATRIX* matrix, const D3DMATRIX* first, const D3DMATRIX* second) {
    const auto* left = reinterpret_cast<const float*>(first);
    const auto* right = reinterpret_cast<const float*>(second);
    auto* output = reinterpret_cast<float*>(matrix);
    alignas(16) PairWords xmm0_words;
    xmm0_words.low = load_word_pair(right + 0);       // original006804ae
    xmm0_words.high = load_word_pair(right + 2);      // original006804b1
    const Vector vector_000 = from_words(xmm0_words); // original006804b1
    alignas(16) PairWords xmm1_words;
    xmm1_words.low = load_word_pair(right + 4);       // original006804b5
    xmm1_words.high = load_word_pair(right + 6);      // original006804b9
    const Vector vector_001 = from_words(xmm1_words); // original006804b9
    alignas(16) PairWords xmm2_words;
    xmm2_words.low = load_word_pair(right + 8);       // original006804bd
    xmm2_words.high = load_word_pair(right + 10);     // original006804c1
    const Vector vector_002 = from_words(xmm2_words); // original006804c1
    alignas(16) PairWords xmm3_words;
    xmm3_words.low = load_word_pair(right + 12);                     // original006804c5
    xmm3_words.high = load_word_pair(right + 14);                    // original006804c9
    const Vector vector_003 = from_words(xmm3_words);                // original006804c9
    const Vector vector_004 = load_scalar(left + 0);                 // original006804cd
    const Vector vector_005 = load_scalar(left + 1);                 // original006804d1
    const Vector vector_006 = load_scalar(left + 2);                 // original006804d6
    const Vector vector_007 = load_scalar(left + 3);                 // original006804db
    const Vector vector_008 = shuffle<0x00>(vector_004, vector_004); // original006804e0
    const Vector vector_009 = shuffle<0x00>(vector_005, vector_005); // original006804e4
    const Vector vector_010 = shuffle<0x00>(vector_006, vector_006); // original006804e8
    const Vector vector_011 = shuffle<0x00>(vector_007, vector_007); // original006804ec
    const Vector vector_012 = mulps(vector_008, vector_000);         // original006804f0
    const Vector vector_013 = mulps(vector_009, vector_001);         // original006804f3
    const Vector vector_014 = mulps(vector_010, vector_002);         // original006804f6
    const Vector vector_015 = mulps(vector_011, vector_003);         // original006804f9
    const Vector vector_016 = addps(vector_012, vector_013);         // original006804fc
    const Vector vector_017 = addps(vector_014, vector_015);         // original006804ff
    const Vector vector_018 = addps(vector_016, vector_017);         // original00680502
    const Vector vector_019 = load_scalar(left + 4);                 // original00680505
    const Vector vector_020 = load_scalar(left + 5);                 // original0068050a
    const Vector vector_021 = load_scalar(left + 6);                 // original0068050f
    const Vector vector_022 = shuffle<0x00>(vector_019, vector_019); // original00680514
    const Vector vector_023 = shuffle<0x00>(vector_020, vector_020); // original00680518
    const Vector vector_024 = shuffle<0x00>(vector_021, vector_021); // original0068051c
    const Vector vector_025 = mulps(vector_022, vector_000);         // original00680520
    const Vector vector_026 = mulps(vector_023, vector_001);         // original00680523
    const Vector vector_027 = mulps(vector_024, vector_002);         // original00680526
    const Vector vector_028 = addps(vector_025, vector_026);         // original00680529
    const Vector vector_029 = addps(vector_028, vector_027);         // original0068052c
    const Vector vector_030 = load_scalar(left + 7);                 // original0068052f
    const Vector vector_031 = shuffle<0x00>(vector_030, vector_030); // original00680534
    const Vector vector_032 = mulps(vector_031, vector_003);         // original00680538
    const Vector vector_033 = addps(vector_029, vector_032);         // original0068053b
    const Vector vector_034 = load_scalar(left + 8);                 // original0068053e
    const Vector vector_035 = load_scalar(left + 9);                 // original00680543
    const Vector vector_036 = shuffle<0x00>(vector_034, vector_034); // original00680548
    const Vector vector_037 = shuffle<0x00>(vector_035, vector_035); // original0068054c
    const Vector vector_038 = mulps(vector_036, vector_000);         // original00680550
    const Vector vector_039 = mulps(vector_037, vector_001);         // original00680553
    const Vector vector_040 = addps(vector_038, vector_039);         // original00680556
    const Vector vector_041 = load_scalar(left + 10);                // original00680559
    const Vector vector_042 = shuffle<0x00>(vector_041, vector_041); // original0068055e
    const Vector vector_043 = mulps(vector_042, vector_002);         // original00680562
    const Vector vector_044 = addps(vector_040, vector_043);         // original00680565
    const Vector vector_045 = load_scalar(left + 11);                // original00680568
    const Vector vector_046 = shuffle<0x00>(vector_045, vector_045); // original0068056d
    const Vector vector_047 = mulps(vector_046, vector_003);         // original00680571
    const Vector vector_048 = addps(vector_044, vector_047);         // original00680574
    const Vector vector_049 = load_scalar(left + 12);                // original00680577
    const Vector vector_050 = shuffle<0x00>(vector_049, vector_049); // original0068057c
    const Vector vector_051 = mulps(vector_000, vector_050);         // original00680580
    const Vector vector_052 = load_scalar(left + 13);                // original00680583
    const Vector vector_053 = shuffle<0x00>(vector_052, vector_052); // original00680588
    const Vector vector_054 = mulps(vector_001, vector_053);         // original0068058c
    const Vector vector_055 = load_scalar(left + 14);                // original0068058f
    const Vector vector_056 = shuffle<0x00>(vector_055, vector_055); // original00680594
    const Vector vector_057 = mulps(vector_002, vector_056);         // original00680598
    const Vector vector_058 = load_scalar(left + 15);                // original0068059b
    const Vector vector_059 = shuffle<0x00>(vector_058, vector_058); // original006805a0
    const Vector vector_060 = mulps(vector_003, vector_059);         // original006805a4
    store_low(output + 0, vector_018);                               // original006805a7
    store_high(output + 2, vector_018);                              // original006805aa
    const Vector vector_061 = addps(vector_051, vector_054);         // original006805ae
    store_low(output + 4, vector_033);                               // original006805b1
    store_high(output + 6, vector_033);                              // original006805b5
    const Vector vector_062 = addps(vector_057, vector_060);         // original006805b9
    store_low(output + 8, vector_048);                               // original006805bc
    store_high(output + 10, vector_048);                             // original006805c0
    const Vector vector_063 = addps(vector_061, vector_062);         // original006805c4
    store_low(output + 12, vector_063);                              // original006805c7
    store_high(output + 14, vector_063);                             // original006805cb
    return matrix;
}

extern "C" __attribute__((target("sse"))) D3DMATRIX* __attribute__((stdcall))
FUN_0068387c(D3DMATRIX* matrix, const D3DMATRIX* first, const D3DMATRIX* second) {
    const auto* left = reinterpret_cast<const float*>(first);
    const auto* right = reinterpret_cast<const float*>(second);
    auto* output = reinterpret_cast<float*>(matrix);
    alignas(16) PairWords xmm0_words;
    xmm0_words.low = load_word_pair(right + 0);       // original0068388a
    xmm0_words.high = load_word_pair(right + 2);      // original0068388d
    const Vector vector_000 = from_words(xmm0_words); // original0068388d
    alignas(16) PairWords xmm1_words;
    xmm1_words.low = load_word_pair(right + 4);       // original00683891
    xmm1_words.high = load_word_pair(right + 6);      // original00683895
    const Vector vector_001 = from_words(xmm1_words); // original00683895
    alignas(16) PairWords xmm2_words;
    xmm2_words.low = load_word_pair(right + 8);       // original00683899
    xmm2_words.high = load_word_pair(right + 10);     // original0068389d
    const Vector vector_002 = from_words(xmm2_words); // original0068389d
    alignas(16) PairWords xmm3_words;
    xmm3_words.low = load_word_pair(right + 12);                     // original006838a1
    xmm3_words.high = load_word_pair(right + 14);                    // original006838a5
    const Vector vector_003 = from_words(xmm3_words);                // original006838a5
    const Vector vector_004 = load_scalar(left + 0);                 // original006838a9
    const Vector vector_005 = load_scalar(left + 1);                 // original006838ad
    const Vector vector_006 = load_scalar(left + 2);                 // original006838b2
    const Vector vector_007 = load_scalar(left + 3);                 // original006838b7
    const Vector vector_008 = shuffle<0x00>(vector_004, vector_004); // original006838bc
    const Vector vector_009 = shuffle<0x00>(vector_005, vector_005); // original006838c0
    const Vector vector_010 = shuffle<0x00>(vector_006, vector_006); // original006838c4
    const Vector vector_011 = shuffle<0x00>(vector_007, vector_007); // original006838c8
    const Vector vector_012 = mulps(vector_008, vector_000);         // original006838cc
    const Vector vector_013 = mulps(vector_009, vector_001);         // original006838cf
    const Vector vector_014 = mulps(vector_010, vector_002);         // original006838d2
    const Vector vector_015 = mulps(vector_011, vector_003);         // original006838d5
    const Vector vector_016 = addps(vector_012, vector_013);         // original006838d8
    const Vector vector_017 = addps(vector_014, vector_015);         // original006838db
    const Vector vector_018 = addps(vector_016, vector_017);         // original006838de
    const Vector vector_019 = load_scalar(left + 4);                 // original006838e1
    const Vector vector_020 = load_scalar(left + 5);                 // original006838e6
    const Vector vector_021 = load_scalar(left + 6);                 // original006838eb
    const Vector vector_022 = shuffle<0x00>(vector_019, vector_019); // original006838f0
    const Vector vector_023 = shuffle<0x00>(vector_020, vector_020); // original006838f4
    const Vector vector_024 = shuffle<0x00>(vector_021, vector_021); // original006838f8
    const Vector vector_025 = mulps(vector_022, vector_000);         // original006838fc
    const Vector vector_026 = mulps(vector_023, vector_001);         // original006838ff
    const Vector vector_027 = mulps(vector_024, vector_002);         // original00683902
    const Vector vector_028 = addps(vector_025, vector_026);         // original00683905
    const Vector vector_029 = addps(vector_028, vector_027);         // original00683908
    const Vector vector_030 = load_scalar(left + 7);                 // original0068390b
    const Vector vector_031 = shuffle<0x00>(vector_030, vector_030); // original00683910
    const Vector vector_032 = mulps(vector_031, vector_003);         // original00683914
    const Vector vector_033 = addps(vector_029, vector_032);         // original00683917
    const Vector vector_034 = load_scalar(left + 8);                 // original0068391a
    const Vector vector_035 = load_scalar(left + 9);                 // original0068391f
    const Vector vector_036 = shuffle<0x00>(vector_034, vector_034); // original00683924
    const Vector vector_037 = shuffle<0x00>(vector_035, vector_035); // original00683928
    const Vector vector_038 = mulps(vector_036, vector_000);         // original0068392c
    const Vector vector_039 = mulps(vector_037, vector_001);         // original0068392f
    const Vector vector_040 = addps(vector_038, vector_039);         // original00683932
    const Vector vector_041 = load_scalar(left + 10);                // original00683935
    const Vector vector_042 = shuffle<0x00>(vector_041, vector_041); // original0068393a
    const Vector vector_043 = mulps(vector_042, vector_002);         // original0068393e
    const Vector vector_044 = addps(vector_040, vector_043);         // original00683941
    const Vector vector_045 = load_scalar(left + 11);                // original00683944
    const Vector vector_046 = shuffle<0x00>(vector_045, vector_045); // original00683949
    const Vector vector_047 = mulps(vector_046, vector_003);         // original0068394d
    const Vector vector_048 = addps(vector_044, vector_047);         // original00683950
    const Vector vector_049 = load_scalar(left + 12);                // original00683953
    const Vector vector_050 = shuffle<0x00>(vector_049, vector_049); // original00683958
    const Vector vector_051 = mulps(vector_000, vector_050);         // original0068395c
    const Vector vector_052 = load_scalar(left + 13);                // original0068395f
    const Vector vector_053 = shuffle<0x00>(vector_052, vector_052); // original00683964
    const Vector vector_054 = mulps(vector_001, vector_053);         // original00683968
    const Vector vector_055 = load_scalar(left + 14);                // original0068396b
    const Vector vector_056 = shuffle<0x00>(vector_055, vector_055); // original00683970
    const Vector vector_057 = mulps(vector_002, vector_056);         // original00683974
    const Vector vector_058 = load_scalar(left + 15);                // original00683977
    const Vector vector_059 = shuffle<0x00>(vector_058, vector_058); // original0068397c
    const Vector vector_060 = mulps(vector_003, vector_059);         // original00683980
    const Vector vector_061 = addps(vector_051, vector_054);         // original00683983
    const Vector vector_062 = addps(vector_057, vector_060);         // original00683986
    const Vector vector_063 = addps(vector_061, vector_062);         // original00683989
    const Vector vector_064 = unpcklps(vector_018, vector_033);      // original00683992
    const Vector vector_065 = unpcklps(vector_048, vector_063);      // original00683995
    const Vector vector_066 = unpckhps(vector_018, vector_033);      // original00683998
    const Vector vector_067 = unpckhps(vector_048, vector_063);      // original0068399b
    store_low(output + 0, vector_064);                               // original0068399e
    store_low(output + 2, vector_065);                               // original006839a1
    store_high(output + 4, vector_064);                              // original006839a5
    store_high(output + 6, vector_065);                              // original006839a9
    store_low(output + 8, vector_066);                               // original006839ad
    store_low(output + 10, vector_067);                              // original006839b1
    store_high(output + 12, vector_066);                             // original006839b5
    store_high(output + 14, vector_067);                             // original006839b9
    return matrix;
}
