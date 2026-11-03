#include "graphics/render_inverse.h"
#include "core/float_classify.h"

// Straight-line arithmetic lifted from the actual original x87 data flow.
// Extended SSA values retain the original operation/float-store boundaries;
// local names record original evidenced EBP offsets, not guessed semantics.
namespace {
uint32_t load_word(const float* source) {
    uint32_t value;
    __builtin_memcpy(&value, source, 4);
    return value;
}
void store_word(volatile float* target, uint32_t value) {
    auto* bytes = reinterpret_cast<volatile unsigned char*>(target);
    for (unsigned i = 0; i < 4; ++i)
        bytes[i] = static_cast<unsigned char>(value >> (8 * i));
}
} // namespace

extern "C" D3DMATRIX* __attribute__((stdcall)) FUN_005e52e4(D3DMATRIX* matrix, float* determinant,
                                                            const D3DMATRIX* source) {
    const auto* input = reinterpret_cast<const float*>(source);
    volatile float local_54, local_50, local_4c, local_48, local_44, local_40, local_3c, local_38,
        local_34, local_30, local_2c, local_28, local_24, local_20, local_1c, local_18, local_14,
        local_10, local_0c, local_08, local_04, local_arg10;
    const uint32_t word_00 = load_word(input + 4);      // original005e52ef
    const volatile long double extended_000 = input[0]; // original005e52f2
    const volatile long double extended_001 = input[1]; // original005e52f4
    store_word(&local_1c, word_00);                     // original005e52f7
    const uint32_t word_01 = load_word(input + 5);      // original005e52fa
    store_word(&local_20, word_01);                     // original005e52fd
    const volatile long double extended_002 = local_20; // original005e5300
    const uint32_t word_02 = load_word(input + 8);      // original005e5303
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(extended_000); // original005e5306
    store_word(&local_18, word_02);                            // original005e5308
    const volatile long double extended_004 = local_1c;        // original005e530b
    const uint32_t word_03 = load_word(input + 9);             // original005e530e
    const volatile long double extended_005 =
        extended_004 * static_cast<long double>(extended_001);             // original005e5311
    store_word(&local_04, word_03);                                        // original005e5313
    const uint32_t word_04 = load_word(input + 12);                        // original005e5316
    store_word(&local_14, word_04);                                        // original005e5319
    const volatile long double extended_006 = extended_003 - extended_005; // original005e531c
    const uint32_t word_05 = load_word(input + 13);                        // original005e531e
    store_word(&local_arg10, word_05);                                     // original005e5321
    const uint32_t word_06 = load_word(input + 14);                        // original005e5324
    local_0c = static_cast<float>(extended_006);                           // original005e5327
    store_word(&local_10, word_06);                                        // original005e532a
    const volatile long double extended_007 = local_04;                    // original005e532d
    const uint32_t word_07 = load_word(input + 15);                        // original005e5330
    const volatile long double extended_008 =
        extended_007 * static_cast<long double>(extended_000); // original005e5333
    const volatile long double extended_009 = local_18;        // original005e5335
    const volatile long double extended_010 =
        extended_009 * static_cast<long double>(extended_001);             // original005e5338
    const volatile long double extended_011 = extended_008 - extended_010; // original005e533a
    local_08 = static_cast<float>(extended_011);                           // original005e533c
    const volatile long double extended_012 = local_arg10;                 // original005e533f
    const volatile long double extended_013 =
        extended_012 * static_cast<long double>(extended_000); // original005e5342
    const volatile long double extended_014 = local_14;        // original005e5344
    const volatile long double extended_015 =
        extended_014 * static_cast<long double>(extended_001);             // original005e5347
    const volatile long double extended_016 = extended_013 - extended_015; // original005e5349
    local_2c = static_cast<float>(extended_016);                           // original005e534b
    const volatile long double extended_017 = local_04;                    // original005e5352
    const volatile long double extended_018 =
        extended_017 * static_cast<long double>(local_1c); // original005e5355
    const volatile long double extended_019 = local_18;    // original005e5358
    const volatile long double extended_020 =
        extended_019 * static_cast<long double>(local_20);                 // original005e535b
    const volatile long double extended_021 = extended_018 - extended_020; // original005e535e
    local_38 = static_cast<float>(extended_021);                           // original005e5360
    const volatile long double extended_022 = local_arg10;                 // original005e5363
    const volatile long double extended_023 =
        extended_022 * static_cast<long double>(local_1c); // original005e5366
    const volatile long double extended_024 = local_14;    // original005e5369
    const volatile long double extended_025 =
        extended_024 * static_cast<long double>(local_20);                 // original005e536c
    const volatile long double extended_026 = extended_023 - extended_025; // original005e536f
    local_34 = static_cast<float>(extended_026);                           // original005e5371
    const volatile long double extended_027 = local_arg10;                 // original005e5374
    store_word(&local_arg10, word_07);                                     // original005e5377
    const volatile long double extended_028 =
        extended_027 * static_cast<long double>(local_18); // original005e537a
    const volatile long double extended_029 = local_14;    // original005e537d
    const volatile long double extended_030 =
        extended_029 * static_cast<long double>(local_04);                 // original005e5380
    const volatile long double extended_031 = extended_028 - extended_030; // original005e5383
    local_30 = static_cast<float>(extended_031);                           // original005e5385
    const volatile long double extended_032 = input[2];                    // original005e5388
    const volatile long double extended_033 = input[3];                    // original005e538b
    const volatile long double extended_034 = input[6];                    // original005e538e
    local_28 = static_cast<float>(extended_034);                           // original005e5391
    const volatile long double extended_035 = input[7];                    // original005e5394
    local_20 = static_cast<float>(extended_035);                           // original005e5397
    const volatile long double extended_036 = input[10];                   // original005e539a
    local_24 = static_cast<float>(extended_036);                           // original005e539d
    const volatile long double extended_037 = input[11];                   // original005e53a0
    local_04 = static_cast<float>(extended_037);                           // original005e53a3
    const volatile long double extended_038 = extended_032;                // original005e53a6
    const volatile long double extended_039 =
        extended_038 * static_cast<long double>(local_38);  // original005e53a8
    const volatile long double extended_040 = extended_034; // original005e53ab
    const volatile long double extended_041 =
        extended_040 * static_cast<long double>(local_08);                 // original005e53ad
    const volatile long double extended_042 = extended_039 - extended_041; // original005e53b0
    const volatile long double extended_043 = extended_036;                // original005e53b2
    const volatile long double extended_044 =
        extended_043 * static_cast<long double>(local_0c);                 // original005e53b4
    const volatile long double extended_045 = extended_042 + extended_044; // original005e53b7
    local_54 = static_cast<float>(extended_045);                           // original005e53b9
    const volatile long double extended_046 = extended_034;                // original005e53bc
    const volatile long double extended_047 =
        extended_046 * static_cast<long double>(local_2c); // original005e53be
    const volatile long double extended_048 = local_10;    // original005e53c1
    const volatile long double extended_049 =
        extended_048 * static_cast<long double>(local_0c);                 // original005e53c4
    const volatile long double extended_050 = extended_047 - extended_049; // original005e53c7
    const volatile long double extended_051 = extended_032;                // original005e53c9
    const volatile long double extended_052 =
        extended_051 * static_cast<long double>(local_34);                 // original005e53cb
    const volatile long double extended_053 = extended_050 - extended_052; // original005e53ce
    local_50 = static_cast<float>(extended_053);                           // original005e53d0
    const volatile long double extended_054 = extended_032;                // original005e53d3
    const volatile long double extended_055 =
        extended_054 * static_cast<long double>(local_30);  // original005e53d5
    const volatile long double extended_056 = extended_036; // original005e53d8
    const volatile long double extended_057 =
        extended_056 * static_cast<long double>(local_2c);                 // original005e53da
    const volatile long double extended_058 = extended_055 - extended_057; // original005e53dd
    const volatile long double extended_059 = local_10;                    // original005e53df
    const volatile long double extended_060 =
        extended_059 * static_cast<long double>(local_08);                 // original005e53e2
    const volatile long double extended_061 = extended_058 + extended_060; // original005e53e5
    local_4c = static_cast<float>(extended_061);                           // original005e53e7
    const volatile long double extended_062 = extended_036;                // original005e53ea
    const volatile long double extended_063 =
        extended_062 * static_cast<long double>(local_34); // original005e53ec
    const volatile long double extended_064 = local_10;    // original005e53ef
    const volatile long double extended_065 =
        extended_064 * static_cast<long double>(local_38);                 // original005e53f2
    const volatile long double extended_066 = extended_063 - extended_065; // original005e53f5
    const volatile long double extended_067 = extended_034;                // original005e53f7
    const volatile long double extended_068 =
        extended_067 * static_cast<long double>(local_30);                 // original005e53f9
    const volatile long double extended_069 = extended_066 - extended_068; // original005e53fc
    local_48 = static_cast<float>(extended_069);                           // original005e53fe
    const volatile long double extended_070 = local_08;                    // original005e5401
    const volatile long double extended_071 =
        extended_070 * static_cast<long double>(extended_035); // original005e5404
    const volatile long double extended_072 = local_0c;        // original005e5406
    const volatile long double extended_073 =
        extended_072 * static_cast<long double>(extended_037);             // original005e5409
    const volatile long double extended_074 = extended_071 - extended_073; // original005e540b
    const volatile long double extended_075 = local_38;                    // original005e540d
    const volatile long double extended_076 =
        extended_075 * static_cast<long double>(extended_033);             // original005e5410
    const volatile long double extended_077 = extended_074 - extended_076; // original005e5412
    local_44 = static_cast<float>(extended_077);                           // original005e5414
    const volatile long double extended_078 = local_34;                    // original005e5417
    const volatile long double extended_079 =
        extended_078 * static_cast<long double>(extended_033); // original005e541a
    const volatile long double extended_080 = local_2c;        // original005e541c
    const volatile long double extended_081 =
        extended_080 * static_cast<long double>(extended_035);             // original005e541f
    const volatile long double extended_082 = extended_079 - extended_081; // original005e5421
    const volatile long double extended_083 = local_0c;                    // original005e5423
    const volatile long double extended_084 =
        extended_083 * static_cast<long double>(local_arg10);              // original005e5426
    const volatile long double extended_085 = extended_082 + extended_084; // original005e5429
    local_40 = static_cast<float>(extended_085);                           // original005e542b
    const volatile long double extended_086 = local_2c;                    // original005e542e
    const volatile long double extended_087 =
        extended_086 * static_cast<long double>(extended_037); // original005e5431
    const volatile long double extended_088 = local_08;        // original005e5433
    const volatile long double extended_089 =
        extended_088 * static_cast<long double>(local_arg10);              // original005e5436
    const volatile long double extended_090 = extended_087 - extended_089; // original005e5439
    const volatile long double extended_091 = local_30;                    // original005e543b
    const volatile long double extended_092 =
        extended_091 * static_cast<long double>(extended_033);             // original005e543e
    const volatile long double extended_093 = extended_090 - extended_092; // original005e5440
    local_3c = static_cast<float>(extended_093);                           // original005e5442
    const volatile long double extended_094 = local_30;                    // original005e5445
    const volatile long double extended_095 =
        extended_094 * static_cast<long double>(extended_035); // original005e5448
    const volatile long double extended_096 = local_34;        // original005e544a
    const volatile long double extended_097 =
        extended_096 * static_cast<long double>(extended_037);             // original005e544d
    const volatile long double extended_098 = extended_095 - extended_097; // original005e544f
    const volatile long double extended_099 = local_38;                    // original005e5451
    const volatile long double extended_100 =
        extended_099 * static_cast<long double>(local_arg10);              // original005e5454
    const volatile long double extended_101 = extended_098 + extended_100; // original005e5457
    local_2c = static_cast<float>(extended_101);                           // original005e5459
    const volatile long double extended_102 = extended_032;                // original005e5460
    const volatile long double extended_103 =
        extended_102 * static_cast<long double>(extended_035); // original005e5462
    const volatile long double extended_104 = extended_034;    // original005e5464
    const volatile long double extended_105 =
        extended_104 * static_cast<long double>(extended_033);             // original005e5466
    const volatile long double extended_106 = extended_103 - extended_105; // original005e5468
    local_0c = static_cast<float>(extended_106);                           // original005e546a
    const volatile long double extended_107 = extended_032;                // original005e5471
    const volatile long double extended_108 =
        extended_107 * static_cast<long double>(local_04); // original005e5473
    const volatile long double extended_109 = local_24;    // original005e5476
    const volatile long double extended_110 =
        extended_109 * static_cast<long double>(extended_033);             // original005e5479
    const volatile long double extended_111 = extended_108 - extended_110; // original005e547b
    local_08 = static_cast<float>(extended_111);                           // original005e547d
    const volatile long double extended_112 = extended_032;                // original005e5480
    const volatile long double extended_113 =
        extended_112 * static_cast<long double>(local_arg10); // original005e5482
    const volatile long double extended_114 = local_10;       // original005e5485
    const volatile long double extended_115 =
        extended_114 * static_cast<long double>(extended_033);             // original005e5488
    const volatile long double extended_116 = extended_113 - extended_115; // original005e548a
    const volatile long double extended_117 = local_28;                    // original005e5490
    const uint32_t word_08 = load_word(input + 0);                         // original005e5493
    const volatile long double extended_118 =
        extended_117 * static_cast<long double>(local_04); // original005e5495
    store_word(&local_38, word_08);                        // original005e5498
    const volatile long double extended_119 = local_24;    // original005e549b
    const uint32_t word_09 = load_word(input + 4);         // original005e549e
    const volatile long double extended_120 =
        extended_119 * static_cast<long double>(local_20);                 // original005e54a1
    store_word(&local_1c, word_09);                                        // original005e54a4
    const uint32_t word_10 = load_word(input + 8);                         // original005e54a7
    store_word(&local_18, word_10);                                        // original005e54aa
    const volatile long double extended_121 = extended_118 - extended_120; // original005e54ad
    const uint32_t word_11 = load_word(input + 9);                         // original005e54af
    const volatile long double extended_122 = local_28;                    // original005e54b2
    const volatile long double extended_123 =
        extended_122 * static_cast<long double>(local_arg10); // original005e54b5
    const volatile long double extended_124 = local_10;       // original005e54b8
    const volatile long double extended_125 =
        extended_124 * static_cast<long double>(local_20);                 // original005e54bb
    const volatile long double extended_126 = extended_123 - extended_125; // original005e54be
    const volatile long double extended_127 = local_24;                    // original005e54c0
    const volatile long double extended_128 =
        extended_127 * static_cast<long double>(local_arg10); // original005e54c3
    const volatile long double extended_129 = local_10;       // original005e54c6
    const volatile long double extended_130 =
        extended_129 * static_cast<long double>(local_04);                 // original005e54c9
    store_word(&local_04, word_11);                                        // original005e54cc
    const uint32_t word_12 = load_word(input + 12);                        // original005e54cf
    store_word(&local_14, word_12);                                        // original005e54d2
    const volatile long double extended_131 = extended_128 - extended_130; // original005e54d5
    const volatile long double extended_132 = input[1];                    // original005e54d7
    const volatile long double extended_133 = input[5];                    // original005e54da
    const uint32_t word_13 = load_word(input + 13);                        // original005e54dd
    const volatile long double extended_134 = local_08;                    // original005e54e0
    store_word(&local_arg10, word_13);                                     // original005e54e3
    const volatile long double extended_135 =
        extended_134 * static_cast<long double>(extended_133); // original005e54e6
    const volatile long double extended_136 = local_0c;        // original005e54e8
    const volatile long double extended_137 =
        extended_136 * static_cast<long double>(local_04);                 // original005e54eb
    const volatile long double extended_138 = extended_135 - extended_137; // original005e54ee
    const volatile long double extended_139 = extended_121;                // original005e54f0
    const volatile long double extended_140 =
        extended_139 * static_cast<long double>(extended_132);             // original005e54f2
    const volatile long double extended_141 = extended_138 - extended_140; // original005e54f4
    local_10 = static_cast<float>(extended_141);                           // original005e54f6
    const volatile long double extended_142 = extended_126;                // original005e54f9
    const volatile long double extended_143 =
        extended_142 * static_cast<long double>(extended_132); // original005e54fb
    const volatile long double extended_144 = extended_116;    // original005e54fd
    const volatile long double extended_145 =
        extended_144 * static_cast<long double>(extended_133);             // original005e54ff
    const volatile long double extended_146 = extended_143 - extended_145; // original005e5501
    const volatile long double extended_147 = local_0c;                    // original005e5503
    const volatile long double extended_148 =
        extended_147 * static_cast<long double>(local_arg10);              // original005e5506
    const volatile long double extended_149 = extended_146 + extended_148; // original005e5509
    local_24 = static_cast<float>(extended_149);                           // original005e550b
    const volatile long double extended_150 = extended_116;                // original005e550e
    const volatile long double extended_151 =
        extended_150 * static_cast<long double>(local_04); // original005e5510
    const volatile long double extended_152 = local_08;    // original005e5513
    const volatile long double extended_153 =
        extended_152 * static_cast<long double>(local_arg10);              // original005e5516
    const volatile long double extended_154 = extended_151 - extended_153; // original005e5519
    const volatile long double extended_155 = extended_131;                // original005e551b
    const volatile long double extended_156 =
        extended_155 * static_cast<long double>(extended_132);             // original005e551d
    const volatile long double extended_157 = extended_154 - extended_156; // original005e551f
    local_28 = static_cast<float>(extended_157);                           // original005e5521
    const volatile long double extended_158 = extended_131;                // original005e5524
    const volatile long double extended_159 =
        extended_158 * static_cast<long double>(extended_133); // original005e5526
    const volatile long double extended_160 = extended_126;    // original005e5528
    const volatile long double extended_161 =
        extended_160 * static_cast<long double>(local_04);                 // original005e552a
    const volatile long double extended_162 = extended_159 - extended_161; // original005e552d
    const volatile long double extended_163 = extended_121;                // original005e552f
    const volatile long double extended_164 =
        extended_163 * static_cast<long double>(local_arg10);              // original005e5531
    const volatile long double extended_165 = extended_162 + extended_164; // original005e5534
    local_34 = static_cast<float>(extended_165);                           // original005e5536
    const volatile long double extended_166 = extended_121;                // original005e553d
    const volatile long double extended_167 =
        extended_166 * static_cast<long double>(local_38); // original005e553f
    const volatile long double extended_168 = local_08;    // original005e5542
    const volatile long double extended_169 =
        extended_168 * static_cast<long double>(local_1c);                 // original005e5545
    const volatile long double extended_170 = extended_167 - extended_169; // original005e5548
    const volatile long double extended_171 = local_0c;                    // original005e554a
    const volatile long double extended_172 =
        extended_171 * static_cast<long double>(local_18);                 // original005e554d
    const volatile long double extended_173 = extended_170 + extended_172; // original005e5550
    local_arg10 = static_cast<float>(extended_173);                        // original005e5552
    const volatile long double extended_174 = extended_116;                // original005e5555
    const volatile long double extended_175 =
        extended_174 * static_cast<long double>(local_1c); // original005e5557
    const volatile long double extended_176 = local_0c;    // original005e555a
    const volatile long double extended_177 =
        extended_176 * static_cast<long double>(local_14);                 // original005e555d
    const volatile long double extended_178 = extended_175 - extended_177; // original005e5560
    const volatile long double extended_179 = extended_126;                // original005e5562
    const volatile long double extended_180 =
        extended_179 * static_cast<long double>(local_38);                 // original005e5569
    const volatile long double extended_181 = extended_178 - extended_180; // original005e556c
    local_04 = static_cast<float>(extended_181);                           // original005e556e
    const volatile long double extended_182 = local_38;                    // original005e5571
    const volatile long double extended_183 =
        extended_182 * static_cast<long double>(extended_131); // original005e5574
    const volatile long double extended_184 = extended_116;    // original005e5576
    const volatile long double extended_185 =
        extended_184 * static_cast<long double>(local_18);                 // original005e5578
    const volatile long double extended_186 = extended_183 - extended_185; // original005e557b
    const volatile long double extended_187 = local_08;                    // original005e557d
    const volatile long double extended_188 =
        extended_187 * static_cast<long double>(local_14);                 // original005e5580
    const volatile long double extended_189 = extended_186 + extended_188; // original005e5583
    local_20 = static_cast<float>(extended_189);                           // original005e5585
    const volatile long double extended_190 = extended_126;                // original005e5588
    const volatile long double extended_191 =
        extended_190 * static_cast<long double>(local_18);  // original005e558a
    const volatile long double extended_192 = extended_121; // original005e558d
    const volatile long double extended_193 =
        extended_192 * static_cast<long double>(local_14);                 // original005e558f
    const volatile long double extended_194 = extended_191 - extended_193; // original005e5592
    const volatile long double extended_195 = extended_131;                // original005e5594
    const volatile long double extended_196 =
        extended_195 * static_cast<long double>(local_1c);                 // original005e5596
    const volatile long double extended_197 = extended_194 - extended_196; // original005e5599
    local_30 = static_cast<float>(extended_197);                           // original005e559b
    const volatile long double extended_198 = local_10;                    // original005e55a6
    const volatile long double extended_199 =
        extended_198 * static_cast<long double>(local_14); // original005e55a9
    const volatile long double extended_200 = local_24;    // original005e55ac
    const volatile long double extended_201 =
        extended_200 * static_cast<long double>(local_18);                 // original005e55af
    const volatile long double extended_202 = extended_199 + extended_201; // original005e55b2
    const volatile long double extended_203 = local_28;                    // original005e55b4
    const volatile long double extended_204 =
        extended_203 * static_cast<long double>(local_1c);                 // original005e55b7
    const volatile long double extended_205 = extended_202 + extended_204; // original005e55ba
    const volatile long double extended_206 = local_34;                    // original005e55bc
    const volatile long double extended_207 =
        extended_206 * static_cast<long double>(local_38);                 // original005e55bf
    const volatile long double extended_208 = extended_205 + extended_207; // original005e55c2
    if (determinant != nullptr)
        *determinant = static_cast<float>(extended_208); // original5e55c4..5e55c6
    if (extended_208 == 0.0L)
        return nullptr; // actual FUCOMPP/AH44 parity branch
    const volatile float reciprocal =
        static_cast<float>(1.0L / extended_208); // original5e55e0..5e55e6
    if (FUN_005ced05(static_cast<double>(reciprocal)) == 0)
        return nullptr;
    auto* output = reinterpret_cast<float*>(matrix);
    output[0] = static_cast<float>(static_cast<long double>(local_34) *
                                   static_cast<long double>(reciprocal));
    output[1] = static_cast<float>(static_cast<long double>(local_28) *
                                   static_cast<long double>(reciprocal));
    output[2] = static_cast<float>(static_cast<long double>(local_24) *
                                   static_cast<long double>(reciprocal));
    output[3] = static_cast<float>(static_cast<long double>(local_10) *
                                   static_cast<long double>(reciprocal));
    output[4] = static_cast<float>(static_cast<long double>(local_30) *
                                   static_cast<long double>(reciprocal));
    output[5] = static_cast<float>(static_cast<long double>(local_20) *
                                   static_cast<long double>(reciprocal));
    output[6] = static_cast<float>(static_cast<long double>(local_04) *
                                   static_cast<long double>(reciprocal));
    output[7] = static_cast<float>(static_cast<long double>(local_arg10) *
                                   static_cast<long double>(reciprocal));
    output[8] = static_cast<float>(static_cast<long double>(local_2c) *
                                   static_cast<long double>(reciprocal));
    output[9] = static_cast<float>(static_cast<long double>(local_3c) *
                                   static_cast<long double>(reciprocal));
    output[10] = static_cast<float>(static_cast<long double>(local_40) *
                                    static_cast<long double>(reciprocal));
    output[11] = static_cast<float>(static_cast<long double>(local_44) *
                                    static_cast<long double>(reciprocal));
    output[12] = static_cast<float>(static_cast<long double>(local_48) *
                                    static_cast<long double>(reciprocal));
    output[13] = static_cast<float>(static_cast<long double>(local_4c) *
                                    static_cast<long double>(reciprocal));
    output[14] = static_cast<float>(static_cast<long double>(local_50) *
                                    static_cast<long double>(reciprocal));
    output[15] = static_cast<float>(static_cast<long double>(local_54) *
                                    static_cast<long double>(reciprocal));
    return matrix;
}
