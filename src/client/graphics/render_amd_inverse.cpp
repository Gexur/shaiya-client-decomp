#include "graphics/render_amd_inverse.h"
#include <stdint.h>
namespace {
using Packed = long long __attribute__((vector_size(8)));
struct PairBytes {
    unsigned char bytes[8];
};
#define MMX_INLINE __attribute__((target("mmx,3dnowa"), always_inline)) inline
MMX_INLINE Packed load_pair(const float* source) {
    Packed value;
    __asm__ __volatile__("movq %1,%0"
                         : "=y"(value)
                         : "m"(*reinterpret_cast<const PairBytes*>(source)));
    return value;
}
MMX_INLINE void store_pair(float* target, Packed value) {
    __asm__ __volatile__("movq %1,%0" : "=m"(*reinterpret_cast<PairBytes*>(target)) : "y"(value));
}
MMX_INLINE void store_single(float* target, Packed value) {
    __asm__ __volatile__("movd %1,%0" : "=m"(*target) : "y"(value));
}
MMX_INLINE uint32_t low_word(Packed value) {
    uint32_t result;
    __asm__ __volatile__("movd %1,%0" : "=r"(result) : "y"(value));
    return result;
}
MMX_INLINE Packed zero() {
    Packed value;
    __asm__ __volatile__("pxor %0,%0" : "=y"(value));
    return value;
}
MMX_INLINE void media_empty() {
    __asm__ __volatile__("femms" ::
                             : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st",
                               "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                               "memory");
}
MMX_INLINE Packed pfacc(Packed a, Packed b) {
    __asm__ __volatile__("pfacc %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pfadd(Packed a, Packed b) {
    __asm__ __volatile__("pfadd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pfcmpeq(Packed a, Packed b) {
    __asm__ __volatile__("pfcmpeq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pfmul(Packed a, Packed b) {
    __asm__ __volatile__("pfmul %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pfnacc(Packed a, Packed b) {
    __asm__ __volatile__("pfnacc %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pfrcpit1(Packed a, Packed b) {
    __asm__ __volatile__("pfrcpit1 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pfrcpit2(Packed a, Packed b) {
    __asm__ __volatile__("pfrcpit2 %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pfsub(Packed a, Packed b) {
    __asm__ __volatile__("pfsub %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pfsubr(Packed a, Packed b) {
    __asm__ __volatile__("pfsubr %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed punpckhdq(Packed a, Packed b) {
    __asm__ __volatile__("punpckhdq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed punpckldq(Packed a, Packed b) {
    __asm__ __volatile__("punpckldq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pswapd(Packed value) {
    Packed result;
    __asm__ __volatile__("pswapd %1,%0" : "=y"(result) : "y"(value));
    return result;
}
MMX_INLINE Packed pfrcp(Packed value) {
    Packed result;
    __asm__ __volatile__("pfrcp %1,%0" : "=y"(result) : "y"(value));
    return result;
}
} // namespace
extern "C" alignas(8) const float dat_006f0150[2] = {0x1.0000000000000p+0f, -0x1.0000000000000p+0f};

extern "C" __attribute__((target("mmx,3dnowa"))) D3DMATRIX* __attribute__((stdcall))
FUN_00689836(D3DMATRIX* matrix, float* determinant, const D3DMATRIX* source) {
    const auto* input = reinterpret_cast<const float*>(source);
    auto* output = reinterpret_cast<float*>(matrix);
    const Packed packed_000 = load_pair(input + 4);                        // original0068983d
    const Packed packed_001 = load_pair(input + 8);                        // original00689841
    const Packed packed_002 = pswapd(packed_000);                          // original00689845
    const Packed packed_003 = load_pair(input + 12);                       // original00689849
    const Packed packed_004 = pswapd(packed_001);                          // original0068984d
    const Packed packed_005 = load_pair(input + 0);                        // original00689851
    const Packed packed_006 = pswapd(packed_003);                          // original00689854
    const Packed packed_007 = pswapd(packed_001);                          // original00689858
    const Packed packed_008 = pfmul(packed_002, packed_005);               // original0068985c
    const Packed packed_009 = pfmul(packed_004, packed_005);               // original00689860
    const Packed packed_010 = pfmul(packed_006, packed_005);               // original00689864
    const Packed packed_011 = pswapd(packed_003);                          // original00689868
    const Packed packed_012 = pfmul(packed_007, packed_000);               // original0068986c
    const Packed packed_013 = pfnacc(packed_008, packed_009);              // original00689870
    const Packed packed_014 = pfmul(packed_000, packed_011);               // original00689874
    const Packed packed_015 = pfmul(packed_001, packed_011);               // original00689878
    const Packed packed_016 = pfnacc(packed_010, packed_012);              // original0068987c
    const Packed packed_017 = pfnacc(packed_014, packed_015);              // original00689880
    const Packed packed_018 = load_pair(input + 14);                       // original00689884
    const Packed packed_019 = load_pair(input + 10);                       // original0068988e
    const Packed packed_020 = punpckhdq(packed_016, packed_016);           // original00689892
    const Packed packed_021 = punpckhdq(packed_017, packed_017);           // original00689898
    const Packed packed_022 = pfmul(packed_020, packed_018);               // original0068989b
    const Packed packed_023 = punpckldq(packed_017, packed_017);           // original0068989f
    const Packed packed_024 = pfmul(packed_021, load_pair(input + 6));     // original006898a2
    const Packed packed_025 = pfmul(packed_023, packed_019);               // original006898a7
    const Packed packed_026 = pfadd(packed_022, packed_024);               // original006898ab
    const Packed packed_027 = pfsub(packed_026, packed_025);               // original006898b2
    const Packed packed_028 = punpckldq(packed_016, packed_016);           // original006898b9
    const Packed packed_029 = punpckhdq(packed_017, packed_017);           // original006898c4
    const Packed packed_030 = punpckhdq(packed_013, packed_013);           // original006898c7
    const Packed packed_031 = pfmul(packed_029, load_pair(input + 2));     // original006898ca
    const Packed packed_032 = pfmul(packed_030, packed_018);               // original006898cf
    const Packed packed_033 = pfmul(packed_028, packed_019);               // original006898d3
    const Packed packed_034 = pfsub(packed_032, packed_033);               // original006898d7
    const Packed packed_035 = pfadd(packed_034, packed_031);               // original006898db
    const Packed packed_036 = punpckldq(packed_017, packed_017);           // original006898ea
    const Packed packed_037 = punpckldq(packed_013, packed_013);           // original006898ed
    const Packed packed_038 = punpckldq(packed_016, packed_016);           // original006898f0
    const Packed packed_039 = pfmul(packed_036, load_pair(input + 2));     // original006898f3
    const Packed packed_040 = pfmul(packed_018, packed_037);               // original006898f8
    const Packed packed_041 = pfmul(packed_038, load_pair(input + 6));     // original006898fc
    const Packed packed_042 = pfadd(packed_040, packed_039);               // original00689901
    const Packed packed_043 = pfsub(packed_042, packed_041);               // original00689905
    const Packed packed_044 = punpckhdq(packed_013, packed_013);           // original0068990e
    const Packed packed_045 = punpckhdq(packed_016, packed_016);           // original00689911
    const Packed packed_046 = pfmul(packed_037, packed_019);               // original00689914
    const Packed packed_047 = pfmul(packed_044, load_pair(input + 6));     // original00689918
    const Packed packed_048 = load_pair(input + 2);                        // original0068991d
    const Packed packed_049 = pfmul(packed_045, load_pair(input + 2));     // original00689921
    const Packed packed_050 = pfsub(packed_046, packed_047);               // original00689926
    const Packed packed_051 = pfadd(packed_050, packed_049);               // original0068992a
    const Packed packed_052 = load_pair(input + 6);                        // original00689933
    const Packed packed_053 = load_pair(input + 10);                       // original00689937
    const Packed packed_054 = load_pair(input + 14);                       // original0068993b
    const Packed packed_055 = pswapd(packed_052);                          // original0068993f
    const Packed packed_056 = pswapd(packed_053);                          // original00689943
    const Packed packed_057 = pfmul(packed_055, packed_048);               // original00689947
    const Packed packed_058 = pswapd(packed_054);                          // original0068994b
    const Packed packed_059 = pfmul(packed_056, packed_048);               // original0068994f
    const Packed packed_060 = pswapd(packed_053);                          // original00689953
    const Packed packed_061 = pfmul(packed_058, packed_048);               // original00689957
    const Packed packed_062 = pswapd(packed_054);                          // original0068995b
    const Packed packed_063 = pfnacc(packed_057, packed_059);              // original0068995f
    const Packed packed_064 = pfmul(packed_060, packed_052);               // original00689963
    const Packed packed_065 = pfmul(packed_052, packed_062);               // original00689967
    const Packed packed_066 = pfmul(packed_053, packed_062);               // original0068996b
    const Packed packed_067 = pfnacc(packed_061, packed_064);              // original0068996f
    const Packed packed_068 = pfnacc(packed_065, packed_066);              // original00689973
    const Packed packed_069 = load_pair(input + 12);                       // original00689977
    const Packed packed_070 = load_pair(input + 8);                        // original00689981
    const Packed packed_071 = punpckhdq(packed_068, packed_068);           // original00689988
    const Packed packed_072 = punpckldq(packed_068, packed_068);           // original0068998b
    const Packed packed_073 = punpckhdq(packed_067, packed_067);           // original0068998e
    const Packed packed_074 = pfmul(packed_071, load_pair(input + 4));     // original00689991
    const Packed packed_075 = pfmul(packed_073, packed_069);               // original00689996
    const Packed packed_076 = pfmul(packed_072, packed_070);               // original0068999a
    const Packed packed_077 = pfadd(packed_075, packed_074);               // original0068999e
    const Packed packed_078 = pfsub(packed_077, packed_076);               // original006899a2
    const Packed packed_079 = punpckhdq(packed_068, packed_068);           // original006899b3
    const Packed packed_080 = punpckldq(packed_067, packed_067);           // original006899b6
    const Packed packed_081 = punpckhdq(packed_063, packed_063);           // original006899b9
    const Packed packed_082 = pfmul(packed_079, load_pair(input + 0));     // original006899bc
    const Packed packed_083 = pfmul(packed_081, packed_069);               // original006899c0
    const Packed packed_084 = pfmul(packed_080, packed_070);               // original006899c4
    const Packed packed_085 = pfsub(packed_083, packed_084);               // original006899c8
    const Packed packed_086 = pfadd(packed_085, packed_082);               // original006899cc
    const Packed packed_087 = punpckldq(packed_068, packed_068);           // original006899de
    const Packed packed_088 = punpckldq(packed_063, packed_063);           // original006899e1
    const Packed packed_089 = punpckldq(packed_067, packed_067);           // original006899e4
    const Packed packed_090 = pfmul(packed_087, load_pair(input + 0));     // original006899e7
    const Packed packed_091 = pfmul(packed_069, packed_088);               // original006899eb
    const Packed packed_092 = pfmul(packed_089, load_pair(input + 4));     // original006899ef
    const Packed packed_093 = pfadd(packed_091, packed_090);               // original006899f4
    const Packed packed_094 = pfsub(packed_093, packed_092);               // original006899f8
    const Packed packed_095 = punpckhdq(packed_063, packed_063);           // original00689a01
    const Packed packed_096 = punpckhdq(packed_067, packed_067);           // original00689a04
    const Packed packed_097 = pfmul(packed_088, packed_070);               // original00689a07
    const Packed packed_098 = pfmul(packed_095, load_pair(input + 4));     // original00689a0b
    const Packed packed_099 = pfmul(packed_096, load_pair(input + 0));     // original00689a10
    const Packed packed_100 = pfsub(packed_097, packed_098);               // original00689a14
    const Packed packed_101 = pfadd(packed_100, packed_099);               // original00689a18
    const Packed packed_102 = punpckhdq(packed_094, packed_101);           // original00689a21
    const Packed packed_103 = punpckldq(packed_070, packed_069);           // original00689a24
    const Packed packed_104 = load_pair(input + 0);                        // original00689a27
    const Packed packed_105 = punpckldq(packed_104, load_pair(input + 4)); // original00689a2e
    const Packed packed_106 = punpckhdq(packed_078, packed_086);           // original00689a32
    const Packed packed_107 = pfmul(packed_102, packed_103);               // original00689a37
    const Packed packed_108 = pfmul(packed_105, packed_106);               // original00689a3b
    const Packed packed_109 = pfnacc(packed_107, packed_108);              // original00689a3f
    const Packed packed_110 = pfacc(packed_109, packed_109);               // original00689a47
    if (determinant != nullptr)
        store_single(determinant, packed_110);
    const Packed packed_111 = pfrcp(packed_110);                          // original00689a55
    const Packed packed_112 = zero();                                     // original00689a59
    const Packed packed_113 = punpckldq(packed_110, packed_110);          // original00689a5c
    const Packed packed_114 = pfcmpeq(packed_112, packed_110);            // original00689a5f
    const Packed packed_115 = pfrcpit1(packed_113, packed_111);           // original00689a63
    const Packed packed_116 = pfrcpit2(packed_115, packed_111);           // original00689a67
    const uint32_t zero_mask = low_word(packed_114);                      // original00689a6b
    const Packed packed_117 = pfmul(packed_116, load_pair(dat_006f0150)); // original00689a6e
    const Packed packed_118 = pswapd(packed_117);                         // original00689a78
    uint32_t result = zero_mask;
    if (result == 0) {
        result = reinterpret_cast<uint32_t>(matrix);
        const Packed packed_119 = pfmul(packed_078, packed_118);     // original00689a99
        const Packed packed_120 = pfmul(packed_086, packed_117);     // original00689a9d
        const Packed packed_121 = pfmul(packed_027, packed_118);     // original00689aa1
        const Packed packed_122 = pfmul(packed_035, packed_117);     // original00689aa5
        const Packed packed_123 = punpckhdq(packed_119, packed_120); // original00689aaf
        const Packed packed_124 = punpckldq(packed_119, packed_120); // original00689ab2
        const Packed packed_125 = punpckhdq(packed_121, packed_122); // original00689ab5
        const Packed packed_126 = punpckldq(packed_121, packed_122); // original00689ab8
        store_pair(output + 0, packed_123);                          // original00689abb
        store_pair(output + 4, packed_124);                          // original00689abe
        store_pair(output + 8, packed_125);                          // original00689ac2
        store_pair(output + 12, packed_126);                         // original00689ac6
        const Packed packed_127 = pfmul(packed_094, packed_118);     // original00689ade
        const Packed packed_128 = pfmul(packed_101, packed_117);     // original00689ae2
        const Packed packed_129 = pfmul(packed_043, packed_118);     // original00689ae6
        const Packed packed_130 = pfmul(packed_051, packed_117);     // original00689aea
        const Packed packed_131 = punpckhdq(packed_127, packed_128); // original00689af4
        const Packed packed_132 = punpckldq(packed_127, packed_128); // original00689af7
        const Packed packed_133 = punpckhdq(packed_129, packed_130); // original00689afa
        const Packed packed_134 = punpckldq(packed_129, packed_130); // original00689afd
        store_pair(output + 2, packed_131);                          // original00689b00
        store_pair(output + 6, packed_132);                          // original00689b04
        store_pair(output + 10, packed_133);                         // original00689b08
        store_pair(output + 14, packed_134);                         // original00689b0c
    }
    media_empty(); // Original enhanced entry always executes FEMMS at return.
    return reinterpret_cast<D3DMATRIX*>(result);
}

extern "C" __attribute__((target("mmx,3dnowa"))) D3DMATRIX* __attribute__((stdcall))
FUN_00689f10(D3DMATRIX* matrix, float* determinant, const D3DMATRIX* source) {
    const auto* input = reinterpret_cast<const float*>(source);
    auto* output = reinterpret_cast<float*>(matrix);
    const Packed packed_000 = load_pair(input + 0);                        // original00689f1b
    const Packed packed_001 = load_pair(input + 4);                        // original00689f1e
    const Packed packed_002 = load_pair(input + 8);                        // original00689f22
    const Packed packed_003 = punpckhdq(packed_000, packed_000);           // original00689f32
    const Packed packed_004 = punpckldq(packed_001, packed_002);           // original00689f35
    const Packed packed_005 = punpckldq(packed_000, packed_000);           // original00689f38
    const Packed packed_006 = punpckhdq(packed_001, packed_002);           // original00689f3b
    const Packed packed_007 = pfmul(packed_003, packed_004);               // original00689f3e
    const Packed packed_008 = pfmul(packed_005, packed_006);               // original00689f42
    const Packed packed_009 = load_pair(input + 12);                       // original00689f46
    const Packed packed_010 = pfsub(packed_008, packed_007);               // original00689f4d
    const Packed packed_011 = punpckldq(packed_000, packed_001);           // original00689f51
    const Packed packed_012 = punpckhdq(packed_000, packed_001);           // original00689f54
    const Packed packed_013 = punpckhdq(packed_009, packed_009);           // original00689f5d
    const Packed packed_014 = punpckhdq(packed_009, packed_002);           // original00689f60
    const Packed packed_015 = punpckldq(packed_009, packed_002);           // original00689f63
    const Packed packed_016 = punpckhdq(packed_001, packed_002);           // original00689f66
    const Packed packed_017 = pfmul(packed_014, packed_011);               // original00689f69
    const Packed packed_018 = punpckhdq(packed_011, packed_015);           // original00689f6d
    const Packed packed_019 = pfmul(packed_012, packed_015);               // original00689f70
    const Packed packed_020 = punpckldq(packed_015, packed_015);           // original00689f74
    const Packed packed_021 = pfmul(packed_018, packed_013);               // original00689f77
    const Packed packed_022 = pfmul(packed_016, packed_020);               // original00689f7b
    const Packed packed_023 = pfsub(packed_017, packed_019);               // original00689f7f
    const Packed packed_024 = pfsubr(packed_022, packed_021);              // original00689f83
    const Packed packed_025 = load_pair(input + 14);                       // original00689f87
    const Packed packed_026 = load_pair(input + 10);                       // original00689f91
    const Packed packed_027 = punpckhdq(packed_023, packed_023);           // original00689f95
    const Packed packed_028 = punpckhdq(packed_024, packed_024);           // original00689f9b
    const Packed packed_029 = pfmul(packed_027, packed_025);               // original00689f9e
    const Packed packed_030 = punpckldq(packed_024, packed_024);           // original00689fa2
    const Packed packed_031 = pfmul(packed_028, load_pair(input + 6));     // original00689fa5
    const Packed packed_032 = pfmul(packed_030, packed_026);               // original00689faa
    const Packed packed_033 = pfadd(packed_029, packed_031);               // original00689fae
    const Packed packed_034 = pfsub(packed_033, packed_032);               // original00689fb5
    const Packed packed_035 = punpckldq(packed_023, packed_023);           // original00689fbc
    const Packed packed_036 = punpckhdq(packed_024, packed_024);           // original00689fc6
    const Packed packed_037 = punpckhdq(packed_010, packed_010);           // original00689fc9
    const Packed packed_038 = pfmul(packed_036, load_pair(input + 2));     // original00689fcc
    const Packed packed_039 = pfmul(packed_037, packed_025);               // original00689fd1
    const Packed packed_040 = pfmul(packed_035, packed_026);               // original00689fd5
    const Packed packed_041 = pfsub(packed_039, packed_040);               // original00689fd9
    const Packed packed_042 = pfadd(packed_041, packed_038);               // original00689fdd
    const Packed packed_043 = punpckldq(packed_024, packed_024);           // original00689feb
    const Packed packed_044 = punpckldq(packed_010, packed_010);           // original00689fee
    const Packed packed_045 = punpckldq(packed_023, packed_023);           // original00689ff1
    const Packed packed_046 = pfmul(packed_043, load_pair(input + 2));     // original00689ff4
    const Packed packed_047 = pfmul(packed_025, packed_044);               // original00689ff9
    const Packed packed_048 = pfmul(packed_045, load_pair(input + 6));     // original00689ffd
    const Packed packed_049 = pfadd(packed_047, packed_046);               // original0068a002
    const Packed packed_050 = pfsub(packed_049, packed_048);               // original0068a006
    const Packed packed_051 = punpckhdq(packed_010, packed_010);           // original0068a00e
    const Packed packed_052 = punpckhdq(packed_023, packed_023);           // original0068a011
    const Packed packed_053 = pfmul(packed_044, packed_026);               // original0068a014
    const Packed packed_054 = pfmul(packed_051, load_pair(input + 6));     // original0068a018
    const Packed packed_055 = pfmul(packed_052, load_pair(input + 2));     // original0068a01d
    const Packed packed_056 = pfsub(packed_053, packed_054);               // original0068a022
    const Packed packed_057 = pfadd(packed_056, packed_055);               // original0068a026
    const Packed packed_058 = load_pair(input + 2);                        // original0068a02e
    const Packed packed_059 = load_pair(input + 6);                        // original0068a032
    const Packed packed_060 = load_pair(input + 10);                       // original0068a036
    const Packed packed_061 = punpckhdq(packed_058, packed_058);           // original0068a046
    const Packed packed_062 = punpckldq(packed_059, packed_060);           // original0068a049
    const Packed packed_063 = punpckldq(packed_058, packed_058);           // original0068a04c
    const Packed packed_064 = punpckhdq(packed_059, packed_060);           // original0068a04f
    const Packed packed_065 = pfmul(packed_061, packed_062);               // original0068a052
    const Packed packed_066 = pfmul(packed_063, packed_064);               // original0068a056
    const Packed packed_067 = load_pair(input + 14);                       // original0068a05a
    const Packed packed_068 = pfsub(packed_066, packed_065);               // original0068a061
    const Packed packed_069 = punpckldq(packed_058, packed_059);           // original0068a065
    const Packed packed_070 = punpckhdq(packed_058, packed_059);           // original0068a068
    const Packed packed_071 = punpckhdq(packed_067, packed_067);           // original0068a071
    const Packed packed_072 = punpckhdq(packed_067, packed_060);           // original0068a074
    const Packed packed_073 = punpckldq(packed_067, packed_060);           // original0068a077
    const Packed packed_074 = punpckhdq(packed_059, packed_060);           // original0068a07a
    const Packed packed_075 = pfmul(packed_072, packed_069);               // original0068a07d
    const Packed packed_076 = punpckhdq(packed_069, packed_073);           // original0068a081
    const Packed packed_077 = pfmul(packed_070, packed_073);               // original0068a084
    const Packed packed_078 = punpckldq(packed_073, packed_073);           // original0068a088
    const Packed packed_079 = pfmul(packed_076, packed_071);               // original0068a08b
    const Packed packed_080 = pfmul(packed_074, packed_078);               // original0068a08f
    const Packed packed_081 = pfsub(packed_075, packed_077);               // original0068a093
    const Packed packed_082 = pfsubr(packed_080, packed_079);              // original0068a097
    const Packed packed_083 = load_pair(input + 12);                       // original0068a09b
    const Packed packed_084 = load_pair(input + 8);                        // original0068a0a5
    const Packed packed_085 = punpckhdq(packed_082, packed_082);           // original0068a0ac
    const Packed packed_086 = punpckldq(packed_082, packed_082);           // original0068a0af
    const Packed packed_087 = punpckhdq(packed_081, packed_081);           // original0068a0b2
    const Packed packed_088 = pfmul(packed_085, load_pair(input + 4));     // original0068a0b5
    const Packed packed_089 = pfmul(packed_087, packed_083);               // original0068a0ba
    const Packed packed_090 = pfmul(packed_086, packed_084);               // original0068a0be
    const Packed packed_091 = pfadd(packed_089, packed_088);               // original0068a0c2
    const Packed packed_092 = pfsub(packed_091, packed_090);               // original0068a0c6
    const Packed packed_093 = punpckhdq(packed_082, packed_082);           // original0068a0d7
    const Packed packed_094 = punpckldq(packed_081, packed_081);           // original0068a0da
    const Packed packed_095 = punpckhdq(packed_068, packed_068);           // original0068a0dd
    const Packed packed_096 = pfmul(packed_093, load_pair(input + 0));     // original0068a0e0
    const Packed packed_097 = pfmul(packed_095, packed_083);               // original0068a0e4
    const Packed packed_098 = pfmul(packed_094, packed_084);               // original0068a0e8
    const Packed packed_099 = pfsub(packed_097, packed_098);               // original0068a0ec
    const Packed packed_100 = pfadd(packed_099, packed_096);               // original0068a0f0
    const Packed packed_101 = punpckldq(packed_082, packed_082);           // original0068a101
    const Packed packed_102 = punpckldq(packed_068, packed_068);           // original0068a104
    const Packed packed_103 = punpckldq(packed_081, packed_081);           // original0068a107
    const Packed packed_104 = pfmul(packed_101, load_pair(input + 0));     // original0068a10a
    const Packed packed_105 = pfmul(packed_083, packed_102);               // original0068a10e
    const Packed packed_106 = pfmul(packed_103, load_pair(input + 4));     // original0068a112
    const Packed packed_107 = pfadd(packed_105, packed_104);               // original0068a117
    const Packed packed_108 = pfsub(packed_107, packed_106);               // original0068a11b
    const Packed packed_109 = punpckhdq(packed_068, packed_068);           // original0068a123
    const Packed packed_110 = punpckhdq(packed_081, packed_081);           // original0068a126
    const Packed packed_111 = pfmul(packed_102, packed_084);               // original0068a129
    const Packed packed_112 = pfmul(packed_109, load_pair(input + 4));     // original0068a12d
    const Packed packed_113 = pfmul(packed_110, load_pair(input + 0));     // original0068a132
    const Packed packed_114 = pfsub(packed_111, packed_112);               // original0068a136
    const Packed packed_115 = pfadd(packed_114, packed_113);               // original0068a13a
    const Packed packed_116 = punpckldq(packed_084, packed_083);           // original0068a142
    const Packed packed_117 = load_pair(input + 0);                        // original0068a145
    const Packed packed_118 = punpckhdq(packed_108, packed_115);           // original0068a148
    const Packed packed_119 = pfmul(packed_116, load_pair(dat_006f0150));  // original0068a14b
    const Packed packed_120 = punpckldq(packed_117, load_pair(input + 4)); // original0068a157
    const Packed packed_121 = punpckhdq(packed_092, packed_100);           // original0068a15b
    const Packed packed_122 = pfmul(packed_120, load_pair(dat_006f0150));  // original0068a15f
    const Packed packed_123 = pfmul(packed_118, packed_119);               // original0068a167
    const Packed packed_124 = pfmul(packed_122, packed_121);               // original0068a16b
    const Packed packed_125 = pfadd(packed_123, packed_124);               // original0068a16f
    const Packed packed_126 = pfacc(packed_125, packed_125);               // original0068a176
    if (determinant != nullptr)
        store_single(determinant, packed_126);
    const Packed packed_127 = pfrcp(packed_126);                          // original0068a184
    const Packed packed_128 = zero();                                     // original0068a188
    const Packed packed_129 = punpckldq(packed_126, packed_126);          // original0068a18b
    const Packed packed_130 = pfcmpeq(packed_128, packed_126);            // original0068a18e
    const Packed packed_131 = pfrcpit1(packed_129, packed_127);           // original0068a192
    const Packed packed_132 = pfrcpit2(packed_131, packed_127);           // original0068a196
    const uint32_t zero_mask = low_word(packed_130);                      // original0068a19a
    const Packed packed_133 = pfmul(packed_132, load_pair(dat_006f0150)); // original0068a19d
    const Packed packed_134 = punpckldq(packed_115, packed_133);          // original0068a1aa
    const Packed packed_135 = punpckhdq(packed_133, packed_134);          // original0068a1ad
    uint32_t result = zero_mask;
    if (result == 0) {
        result = reinterpret_cast<uint32_t>(matrix);
        const Packed packed_136 = pfmul(packed_092, packed_135);     // original0068a1c9
        const Packed packed_137 = pfmul(packed_100, packed_133);     // original0068a1cd
        const Packed packed_138 = pfmul(packed_034, packed_135);     // original0068a1d1
        const Packed packed_139 = pfmul(packed_042, packed_133);     // original0068a1d5
        const Packed packed_140 = punpckhdq(packed_136, packed_137); // original0068a1df
        const Packed packed_141 = punpckldq(packed_136, packed_137); // original0068a1e2
        const Packed packed_142 = punpckhdq(packed_138, packed_139); // original0068a1e5
        const Packed packed_143 = punpckldq(packed_138, packed_139); // original0068a1e8
        store_pair(output + 0, packed_140);                          // original0068a1eb
        store_pair(output + 4, packed_141);                          // original0068a1ee
        store_pair(output + 8, packed_142);                          // original0068a1f2
        store_pair(output + 12, packed_143);                         // original0068a1f6
        const Packed packed_144 = pfmul(packed_108, packed_135);     // original0068a20a
        const Packed packed_145 = pfmul(packed_115, packed_133);     // original0068a20e
        const Packed packed_146 = pfmul(packed_050, packed_135);     // original0068a212
        const Packed packed_147 = pfmul(packed_057, packed_133);     // original0068a216
        const Packed packed_148 = punpckhdq(packed_144, packed_145); // original0068a220
        const Packed packed_149 = punpckldq(packed_144, packed_145); // original0068a223
        const Packed packed_150 = punpckhdq(packed_146, packed_147); // original0068a226
        const Packed packed_151 = punpckldq(packed_146, packed_147); // original0068a229
        store_pair(output + 2, packed_148);                          // original0068a22c
        store_pair(output + 6, packed_149);                          // original0068a230
        store_pair(output + 10, packed_150);                         // original0068a234
        store_pair(output + 14, packed_151);                         // original0068a238
    }
    return reinterpret_cast<D3DMATRIX*>(result);
}
// Original wrapper ignores its core's zero-determinant return mask.
extern "C" __attribute__((target("mmx,3dnowa"))) D3DMATRIX* __attribute__((stdcall))
FUN_0068a246(D3DMATRIX* matrix, float* determinant, const D3DMATRIX* source) {
    media_empty();
    FUN_00689f10(matrix, determinant, source);
    media_empty();
    return matrix;
}
