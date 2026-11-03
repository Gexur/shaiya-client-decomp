#include "graphics/render_matrix_amd.h"
namespace {
using Packed = long long __attribute__((vector_size(8)));
struct PairBytes {
    unsigned char bytes[8];
};
#define MMX_INLINE __attribute__((target("mmx,3dnow"), always_inline)) inline
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
MMX_INLINE void media_empty() {
    __asm__ __volatile__("femms" ::
                             : "mm0", "mm1", "mm2", "mm3", "mm4", "mm5", "mm6", "mm7", "st",
                               "st(1)", "st(2)", "st(3)", "st(4)", "st(5)", "st(6)", "st(7)",
                               "memory");
}
MMX_INLINE Packed punpckldq(Packed a, Packed b) {
    __asm__ __volatile__("punpckldq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed punpckhdq(Packed a, Packed b) {
    __asm__ __volatile__("punpckhdq %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pfmul(Packed a, Packed b) {
    __asm__ __volatile__("pfmul %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pfacc(Packed a, Packed b) {
    __asm__ __volatile__("pfacc %1,%0" : "+y"(a) : "y"(b));
    return a;
}
MMX_INLINE Packed pfadd(Packed a, Packed b) {
    __asm__ __volatile__("pfadd %1,%0" : "+y"(a) : "y"(b));
    return a;
}
} // namespace
extern "C" __attribute__((target("mmx,3dnow"))) D3DMATRIX* __attribute__((stdcall))
FUN_00686419(D3DMATRIX* matrix, const D3DMATRIX* first, const D3DMATRIX* second) {
    media_empty();
    const auto* left = reinterpret_cast<const float*>(first);
    const auto* right = reinterpret_cast<const float*>(second);
    auto* output = reinterpret_cast<float*>(matrix);
    const Packed packed_000 = load_pair(right + 0);              // original0068642b
    const Packed packed_001 = load_pair(right + 4);              // original0068642e
    const Packed packed_002 = load_pair(right + 10);             // original00686432
    const Packed packed_003 = load_pair(right + 14);             // original00686436
    const Packed packed_004 = punpckldq(packed_000, packed_001); // original0068643d
    const Packed packed_005 = punpckhdq(packed_000, packed_001); // original00686440
    const Packed packed_006 = load_pair(right + 2);              // original0068644f
    const Packed packed_007 = punpckldq(packed_002, packed_003); // original00686453
    const Packed packed_008 = load_pair(right + 6);              // original00686456
    const Packed packed_009 = load_pair(right + 8);              // original0068645a
    const Packed packed_010 = punpckhdq(packed_002, packed_003); // original0068645e
    const Packed packed_011 = punpckldq(packed_006, packed_008); // original00686471
    const Packed packed_012 = load_pair(right + 12);             // original00686474
    const Packed packed_013 = punpckhdq(packed_006, packed_008); // original0068647b
    const Packed packed_014 = punpckhdq(packed_009, packed_012); // original00686483
    const Packed packed_015 = punpckldq(packed_009, packed_012); // original00686486
    const Packed packed_016 = load_pair(left + 0);               // original0068649b
    const Packed packed_017 = load_pair(left + 2);               // original0068649e
    const Packed packed_018 = pfmul(packed_016, packed_004);     // original006864ae
    const Packed packed_019 = pfmul(packed_017, packed_015);     // original006864b3
    const Packed packed_020 = pfmul(packed_016, packed_005);     // original006864bf
    const Packed packed_021 = pfmul(packed_017, packed_014);     // original006864c5
    const Packed packed_022 = pfmul(packed_016, packed_011);     // original006864cb
    const Packed packed_023 = pfmul(packed_017, packed_007);     // original006864d1
    const Packed packed_024 = pfmul(packed_016, packed_013);     // original006864d7
    const Packed packed_025 = pfmul(packed_017, packed_010);     // original006864dd
    const Packed packed_026 = pfacc(packed_018, packed_020);     // original006864e3
    const Packed packed_027 = pfacc(packed_019, packed_021);     // original006864e7
    const Packed packed_028 = pfacc(packed_022, packed_024);     // original006864eb
    const Packed packed_029 = pfacc(packed_023, packed_025);     // original006864ef
    const Packed packed_030 = pfadd(packed_026, packed_027);     // original006864f3
    const Packed packed_031 = pfadd(packed_028, packed_029);     // original006864f7
    store_pair(output + 0, packed_030);                          // original006864fb
    store_pair(output + 2, packed_031);                          // original006864fe
    const Packed packed_032 = load_pair(left + 4);               // original00686502
    const Packed packed_033 = load_pair(left + 6);               // original00686506
    const Packed packed_034 = pfmul(packed_032, packed_004);     // original00686516
    const Packed packed_035 = pfmul(packed_033, packed_015);     // original0068651b
    const Packed packed_036 = pfmul(packed_032, packed_005);     // original00686527
    const Packed packed_037 = pfmul(packed_033, packed_014);     // original0068652d
    const Packed packed_038 = pfmul(packed_032, packed_011);     // original00686533
    const Packed packed_039 = pfmul(packed_033, packed_007);     // original00686539
    const Packed packed_040 = pfmul(packed_032, packed_013);     // original0068653f
    const Packed packed_041 = pfmul(packed_033, packed_010);     // original00686545
    const Packed packed_042 = pfacc(packed_034, packed_036);     // original0068654b
    const Packed packed_043 = pfacc(packed_035, packed_037);     // original0068654f
    const Packed packed_044 = pfacc(packed_038, packed_040);     // original00686553
    const Packed packed_045 = pfacc(packed_039, packed_041);     // original00686557
    const Packed packed_046 = pfadd(packed_042, packed_043);     // original0068655b
    const Packed packed_047 = pfadd(packed_044, packed_045);     // original0068655f
    store_pair(output + 4, packed_046);                          // original00686563
    store_pair(output + 6, packed_047);                          // original00686567
    const Packed packed_048 = load_pair(left + 8);               // original0068656b
    const Packed packed_049 = load_pair(left + 10);              // original0068656f
    const Packed packed_050 = pfmul(packed_048, packed_004);     // original0068657f
    const Packed packed_051 = pfmul(packed_049, packed_015);     // original00686584
    const Packed packed_052 = pfmul(packed_048, packed_005);     // original00686590
    const Packed packed_053 = pfmul(packed_049, packed_014);     // original00686596
    const Packed packed_054 = pfmul(packed_048, packed_011);     // original0068659c
    const Packed packed_055 = pfmul(packed_049, packed_007);     // original006865a2
    const Packed packed_056 = pfmul(packed_048, packed_013);     // original006865a8
    const Packed packed_057 = pfmul(packed_049, packed_010);     // original006865ae
    const Packed packed_058 = pfacc(packed_050, packed_052);     // original006865b4
    const Packed packed_059 = pfacc(packed_051, packed_053);     // original006865b8
    const Packed packed_060 = pfacc(packed_054, packed_056);     // original006865bc
    const Packed packed_061 = pfacc(packed_055, packed_057);     // original006865c0
    const Packed packed_062 = pfadd(packed_058, packed_059);     // original006865c4
    const Packed packed_063 = pfadd(packed_060, packed_061);     // original006865c8
    store_pair(output + 8, packed_062);                          // original006865cc
    store_pair(output + 10, packed_063);                         // original006865d0
    const Packed packed_064 = load_pair(left + 12);              // original006865d4
    const Packed packed_065 = load_pair(left + 14);              // original006865d8
    const Packed packed_066 = pfmul(packed_064, packed_004);     // original006865e8
    const Packed packed_067 = pfmul(packed_065, packed_015);     // original006865ed
    const Packed packed_068 = pfmul(packed_064, packed_005);     // original006865f9
    const Packed packed_069 = pfmul(packed_065, packed_014);     // original006865ff
    const Packed packed_070 = pfmul(packed_064, packed_011);     // original00686605
    const Packed packed_071 = pfmul(packed_065, packed_007);     // original0068660b
    const Packed packed_072 = pfmul(packed_064, packed_013);     // original00686611
    const Packed packed_073 = pfmul(packed_065, packed_010);     // original00686617
    const Packed packed_074 = pfacc(packed_066, packed_068);     // original0068661d
    const Packed packed_075 = pfacc(packed_067, packed_069);     // original00686621
    const Packed packed_076 = pfacc(packed_070, packed_072);     // original00686625
    const Packed packed_077 = pfacc(packed_071, packed_073);     // original00686629
    const Packed packed_078 = pfadd(packed_074, packed_075);     // original0068662d
    const Packed packed_079 = pfadd(packed_076, packed_077);     // original00686631
    store_pair(output + 12, packed_078);                         // original00686635
    store_pair(output + 14, packed_079);                         // original00686639
    media_empty();
    return matrix;
}

extern "C" __attribute__((target("mmx,3dnow"))) D3DMATRIX* __attribute__((stdcall))
FUN_00689b18(D3DMATRIX* matrix, const D3DMATRIX* first, const D3DMATRIX* second) {
    media_empty();
    const auto* left = reinterpret_cast<const float*>(first);
    const auto* right = reinterpret_cast<const float*>(second);
    auto* output = reinterpret_cast<float*>(matrix);
    const Packed packed_000 = load_pair(right + 0);              // original00689b2a
    const Packed packed_001 = load_pair(right + 4);              // original00689b2d
    const Packed packed_002 = load_pair(right + 10);             // original00689b31
    const Packed packed_003 = load_pair(right + 14);             // original00689b35
    const Packed packed_004 = punpckldq(packed_000, packed_001); // original00689b3c
    const Packed packed_005 = punpckhdq(packed_000, packed_001); // original00689b3f
    const Packed packed_006 = load_pair(right + 2);              // original00689b4e
    const Packed packed_007 = punpckldq(packed_002, packed_003); // original00689b52
    const Packed packed_008 = load_pair(right + 6);              // original00689b55
    const Packed packed_009 = load_pair(right + 8);              // original00689b59
    const Packed packed_010 = punpckhdq(packed_002, packed_003); // original00689b5d
    const Packed packed_011 = punpckldq(packed_006, packed_008); // original00689b73
    const Packed packed_012 = load_pair(right + 12);             // original00689b76
    const Packed packed_013 = punpckhdq(packed_006, packed_008); // original00689b7d
    const Packed packed_014 = punpckhdq(packed_009, packed_012); // original00689b85
    const Packed packed_015 = punpckldq(packed_009, packed_012); // original00689b88
    if (first != matrix) { // Original689b70 CMP, deferred JE689b9a.
        const Packed packed_016 = pfmul(packed_004, load_pair(left + 0));  // original00689bb8
        const Packed packed_017 = pfmul(packed_015, load_pair(left + 2));  // original00689bbc
        const Packed packed_018 = pfmul(packed_004, load_pair(left + 4));  // original00689bc7
        const Packed packed_019 = pfmul(packed_015, load_pair(left + 6));  // original00689bcc
        const Packed packed_020 = pfmul(packed_004, load_pair(left + 8));  // original00689bd1
        const Packed packed_021 = pfmul(packed_015, load_pair(left + 10)); // original00689bd6
        const Packed packed_022 = pfmul(packed_004, load_pair(left + 12)); // original00689bdb
        const Packed packed_023 = pfmul(packed_015, load_pair(left + 14)); // original00689be0
        const Packed packed_024 = pfacc(packed_016, packed_018);           // original00689be5
        const Packed packed_025 = pfacc(packed_017, packed_019);           // original00689be9
        const Packed packed_026 = pfacc(packed_020, packed_022);           // original00689bed
        const Packed packed_027 = pfacc(packed_021, packed_023);           // original00689bf1
        const Packed packed_028 = pfadd(packed_024, packed_025);           // original00689bf5
        const Packed packed_029 = pfadd(packed_026, packed_027);           // original00689bf9
        store_pair(output + 0, packed_028);                                // original00689bfd
        store_pair(output + 2, packed_029);                                // original00689c00
        const Packed packed_030 = pfmul(packed_005, load_pair(left + 0));  // original00689c1a
        const Packed packed_031 = pfmul(packed_014, load_pair(left + 2));  // original00689c1e
        const Packed packed_032 = pfmul(packed_005, load_pair(left + 4));  // original00689c29
        const Packed packed_033 = pfmul(packed_014, load_pair(left + 6));  // original00689c2e
        const Packed packed_034 = pfmul(packed_005, load_pair(left + 8));  // original00689c33
        const Packed packed_035 = pfmul(packed_014, load_pair(left + 10)); // original00689c38
        const Packed packed_036 = pfmul(packed_005, load_pair(left + 12)); // original00689c3d
        const Packed packed_037 = pfmul(packed_014, load_pair(left + 14)); // original00689c42
        const Packed packed_038 = pfacc(packed_030, packed_032);           // original00689c47
        const Packed packed_039 = pfacc(packed_031, packed_033);           // original00689c4b
        const Packed packed_040 = pfacc(packed_034, packed_036);           // original00689c4f
        const Packed packed_041 = pfacc(packed_035, packed_037);           // original00689c53
        const Packed packed_042 = pfadd(packed_038, packed_039);           // original00689c57
        const Packed packed_043 = pfadd(packed_040, packed_041);           // original00689c5b
        store_pair(output + 4, packed_042);                                // original00689c5f
        store_pair(output + 6, packed_043);                                // original00689c63
        const Packed packed_044 = pfmul(packed_011, load_pair(left + 0));  // original00689c7d
        const Packed packed_045 = pfmul(packed_007, load_pair(left + 2));  // original00689c81
        const Packed packed_046 = pfmul(packed_011, load_pair(left + 4));  // original00689c8c
        const Packed packed_047 = pfmul(packed_007, load_pair(left + 6));  // original00689c91
        const Packed packed_048 = pfmul(packed_011, load_pair(left + 8));  // original00689c96
        const Packed packed_049 = pfmul(packed_007, load_pair(left + 10)); // original00689c9b
        const Packed packed_050 = pfmul(packed_011, load_pair(left + 12)); // original00689ca0
        const Packed packed_051 = pfmul(packed_007, load_pair(left + 14)); // original00689ca5
        const Packed packed_052 = pfacc(packed_044, packed_046);           // original00689caa
        const Packed packed_053 = pfacc(packed_045, packed_047);           // original00689cae
        const Packed packed_054 = pfacc(packed_048, packed_050);           // original00689cb2
        const Packed packed_055 = pfacc(packed_049, packed_051);           // original00689cb6
        const Packed packed_056 = pfadd(packed_052, packed_053);           // original00689cba
        const Packed packed_057 = pfadd(packed_054, packed_055);           // original00689cbe
        store_pair(output + 8, packed_056);                                // original00689cc2
        store_pair(output + 10, packed_057);                               // original00689cc6
        const Packed packed_058 = pfmul(packed_013, load_pair(left + 0));  // original00689ce0
        const Packed packed_059 = pfmul(packed_010, load_pair(left + 2));  // original00689ce4
        const Packed packed_060 = pfmul(packed_013, load_pair(left + 4));  // original00689cef
        const Packed packed_061 = pfmul(packed_010, load_pair(left + 6));  // original00689cf4
        const Packed packed_062 = pfmul(packed_013, load_pair(left + 8));  // original00689cf9
        const Packed packed_063 = pfmul(packed_010, load_pair(left + 10)); // original00689cfe
        const Packed packed_064 = pfmul(packed_013, load_pair(left + 12)); // original00689d03
        const Packed packed_065 = pfmul(packed_010, load_pair(left + 14)); // original00689d08
        const Packed packed_066 = pfacc(packed_058, packed_060);           // original00689d0d
        const Packed packed_067 = pfacc(packed_059, packed_061);           // original00689d11
        const Packed packed_068 = pfacc(packed_062, packed_064);           // original00689d15
        const Packed packed_069 = pfacc(packed_063, packed_065);           // original00689d19
        const Packed packed_070 = pfadd(packed_066, packed_067);           // original00689d1d
        const Packed packed_071 = pfadd(packed_068, packed_069);           // original00689d21
        store_pair(output + 12, packed_070);                               // original00689d25
        store_pair(output + 14, packed_071);                               // original00689d29
    } else {
        const Packed packed_072 = pfmul(packed_004, load_pair(left + 0));  // original00689d53
        const Packed packed_073 = pfmul(packed_015, load_pair(left + 2));  // original00689d57
        const Packed packed_074 = pfmul(packed_004, load_pair(left + 4));  // original00689d62
        const Packed packed_075 = pfmul(packed_015, load_pair(left + 6));  // original00689d67
        const Packed packed_076 = pfmul(packed_004, load_pair(left + 8));  // original00689d6c
        const Packed packed_077 = pfmul(packed_015, load_pair(left + 10)); // original00689d71
        const Packed packed_078 = pfmul(packed_004, load_pair(left + 12)); // original00689d76
        const Packed packed_079 = pfmul(packed_015, load_pair(left + 14)); // original00689d7b
        const Packed packed_080 = pfacc(packed_072, packed_074);           // original00689d80
        const Packed packed_081 = pfacc(packed_073, packed_075);           // original00689d84
        const Packed packed_082 = pfacc(packed_076, packed_078);           // original00689d88
        const Packed packed_083 = pfacc(packed_077, packed_079);           // original00689d8c
        const Packed packed_084 = pfadd(packed_080, packed_081);           // original00689d90
        const Packed packed_085 = pfadd(packed_082, packed_083);           // original00689d94
        const Packed packed_086 = pfmul(packed_005, load_pair(left + 0));  // original00689db7
        const Packed packed_087 = pfmul(packed_014, load_pair(left + 2));  // original00689dbb
        const Packed packed_088 = pfmul(packed_005, load_pair(left + 4));  // original00689dc6
        const Packed packed_089 = pfmul(packed_014, load_pair(left + 6));  // original00689dcb
        const Packed packed_090 = pfmul(packed_005, load_pair(left + 8));  // original00689dd0
        const Packed packed_091 = pfmul(packed_014, load_pair(left + 10)); // original00689dd5
        const Packed packed_092 = pfmul(packed_005, load_pair(left + 12)); // original00689dda
        const Packed packed_093 = pfmul(packed_014, load_pair(left + 14)); // original00689ddf
        const Packed packed_094 = pfacc(packed_086, packed_088);           // original00689de4
        const Packed packed_095 = pfacc(packed_087, packed_089);           // original00689de8
        const Packed packed_096 = pfacc(packed_090, packed_092);           // original00689dec
        const Packed packed_097 = pfacc(packed_091, packed_093);           // original00689df0
        const Packed packed_098 = pfadd(packed_094, packed_095);           // original00689df4
        const Packed packed_099 = pfadd(packed_096, packed_097);           // original00689df8
        const Packed packed_100 = pfmul(packed_011, load_pair(left + 0));  // original00689e1c
        const Packed packed_101 = pfmul(packed_007, load_pair(left + 2));  // original00689e20
        const Packed packed_102 = pfmul(packed_011, load_pair(left + 4));  // original00689e2b
        const Packed packed_103 = pfmul(packed_007, load_pair(left + 6));  // original00689e30
        const Packed packed_104 = pfmul(packed_011, load_pair(left + 8));  // original00689e35
        const Packed packed_105 = pfmul(packed_007, load_pair(left + 10)); // original00689e3a
        const Packed packed_106 = pfmul(packed_011, load_pair(left + 12)); // original00689e3f
        const Packed packed_107 = pfmul(packed_007, load_pair(left + 14)); // original00689e44
        const Packed packed_108 = pfacc(packed_100, packed_102);           // original00689e49
        const Packed packed_109 = pfacc(packed_101, packed_103);           // original00689e4d
        const Packed packed_110 = pfacc(packed_104, packed_106);           // original00689e51
        const Packed packed_111 = pfacc(packed_105, packed_107);           // original00689e55
        const Packed packed_112 = pfadd(packed_108, packed_109);           // original00689e59
        const Packed packed_113 = pfadd(packed_110, packed_111);           // original00689e5d
        const Packed packed_114 = pfmul(packed_013, load_pair(left + 0));  // original00689e81
        const Packed packed_115 = pfmul(packed_010, load_pair(left + 2));  // original00689e85
        const Packed packed_116 = pfmul(packed_013, load_pair(left + 4));  // original00689e90
        const Packed packed_117 = pfmul(packed_010, load_pair(left + 6));  // original00689e95
        const Packed packed_118 = pfmul(packed_013, load_pair(left + 8));  // original00689e9a
        const Packed packed_119 = pfmul(packed_010, load_pair(left + 10)); // original00689e9f
        const Packed packed_120 = pfmul(packed_013, load_pair(left + 12)); // original00689ea4
        const Packed packed_121 = pfmul(packed_010, load_pair(left + 14)); // original00689ea9
        const Packed packed_122 = pfacc(packed_114, packed_116);           // original00689eae
        const Packed packed_123 = pfacc(packed_115, packed_117);           // original00689eb2
        const Packed packed_124 = pfacc(packed_118, packed_120);           // original00689eb6
        const Packed packed_125 = pfacc(packed_119, packed_121);           // original00689eba
        const Packed packed_126 = pfadd(packed_122, packed_123);           // original00689ebe
        const Packed packed_127 = pfadd(packed_124, packed_125);           // original00689ec2
        store_pair(output + 12, packed_126);                               // original00689ec6
        store_pair(output + 14, packed_127);                               // original00689eca
        store_pair(output + 0, packed_084);                                // original00689eeb
        store_pair(output + 2, packed_085);                                // original00689eee
        store_pair(output + 4, packed_098);                                // original00689ef2
        store_pair(output + 6, packed_099);                                // original00689ef6
        store_pair(output + 8, packed_112);                                // original00689efa
        store_pair(output + 10, packed_113);                               // original00689efe
    }
    media_empty();
    return matrix;
}
