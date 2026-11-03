#include "graphics/render_matrix_pair.h"
#include "startup/math_dispatch_state.h"
#include "graphics/render_dispatch_config.h"
namespace {
// Actual tail REP MOVSD. Its path is selected by the original saved CMP flags.
void copy_sixteen_words(void* target, const volatile void* input) {
    auto* destination = target;
    const volatile void* source = input;
    unsigned count = 16;
    __asm__ __volatile__("rep movsl" : "+D"(destination), "+S"(source), "+c"(count)::"memory");
}
} // namespace
extern "C" D3DMATRIX* __attribute__((stdcall))
FUN_005e4dbe(D3DMATRIX* matrix, const D3DMATRIX* first, const D3DMATRIX* second) {
    const auto* left = reinterpret_cast<const float*>(first);
    const auto* right = reinterpret_cast<const float*>(second);
    const bool exact_alias = matrix == first || matrix == second;
    volatile float scratch[16];
    volatile float* output = exact_alias ? scratch : reinterpret_cast<volatile float*>(matrix);
    const volatile long double extended_000 = left[3]; // original005e4ddd
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(right[12]); // original005e4de0
    const volatile long double extended_002 = left[0];      // original005e4de3
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(right[0]);                 // original005e4de5
    const volatile long double extended_004 = extended_001 + extended_003; // original005e4de7
    const volatile long double extended_005 = left[2];                     // original005e4de9
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(right[8]);                 // original005e4dec
    const volatile long double extended_007 = extended_004 + extended_006; // original005e4def
    const volatile long double extended_008 = right[4];                    // original005e4df1
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(left[1]);                  // original005e4df4
    const volatile long double extended_010 = extended_007 + extended_009; // original005e4df7
    output[0] = static_cast<float>(extended_010);                          // original005e4df9
    const volatile long double extended_011 = left[1];                     // original005e4dfb
    const volatile long double extended_012 =
        extended_011 * static_cast<long double>(right[5]); // original005e4dfe
    const volatile long double extended_013 = left[3];     // original005e4e01
    const volatile long double extended_014 =
        extended_013 * static_cast<long double>(right[13]);                // original005e4e04
    const volatile long double extended_015 = extended_012 + extended_014; // original005e4e07
    const volatile long double extended_016 = left[2];                     // original005e4e09
    const volatile long double extended_017 =
        extended_016 * static_cast<long double>(right[9]);                 // original005e4e0c
    const volatile long double extended_018 = extended_015 + extended_017; // original005e4e0f
    const volatile long double extended_019 = right[1];                    // original005e4e11
    const volatile long double extended_020 =
        extended_019 * static_cast<long double>(left[0]);                  // original005e4e14
    const volatile long double extended_021 = extended_018 + extended_020; // original005e4e16
    output[1] = static_cast<float>(extended_021);                          // original005e4e18
    const volatile long double extended_022 = left[3];                     // original005e4e1b
    const volatile long double extended_023 =
        extended_022 * static_cast<long double>(right[14]); // original005e4e1e
    const volatile long double extended_024 = right[2];     // original005e4e21
    const volatile long double extended_025 =
        extended_024 * static_cast<long double>(left[0]);                  // original005e4e24
    const volatile long double extended_026 = extended_023 + extended_025; // original005e4e26
    const volatile long double extended_027 = left[2];                     // original005e4e28
    const volatile long double extended_028 =
        extended_027 * static_cast<long double>(right[10]);                // original005e4e2b
    const volatile long double extended_029 = extended_026 + extended_028; // original005e4e2e
    const volatile long double extended_030 = right[6];                    // original005e4e30
    const volatile long double extended_031 =
        extended_030 * static_cast<long double>(left[1]);                  // original005e4e33
    const volatile long double extended_032 = extended_029 + extended_031; // original005e4e36
    output[2] = static_cast<float>(extended_032);                          // original005e4e38
    const volatile long double extended_033 = left[3];                     // original005e4e3b
    const volatile long double extended_034 =
        extended_033 * static_cast<long double>(right[15]); // original005e4e3e
    const volatile long double extended_035 = right[11];    // original005e4e41
    const volatile long double extended_036 =
        extended_035 * static_cast<long double>(left[2]);                  // original005e4e44
    const volatile long double extended_037 = extended_034 + extended_036; // original005e4e47
    const volatile long double extended_038 = left[0];                     // original005e4e49
    const volatile long double extended_039 =
        extended_038 * static_cast<long double>(right[3]);                 // original005e4e4b
    const volatile long double extended_040 = extended_037 + extended_039; // original005e4e4e
    const volatile long double extended_041 = right[7];                    // original005e4e50
    const volatile long double extended_042 =
        extended_041 * static_cast<long double>(left[1]);                  // original005e4e53
    const volatile long double extended_043 = extended_040 + extended_042; // original005e4e56
    output[3] = static_cast<float>(extended_043);                          // original005e4e58
    const volatile long double extended_044 = left[7];                     // original005e4e5b
    const volatile long double extended_045 =
        extended_044 * static_cast<long double>(right[12]); // original005e4e5e
    const volatile long double extended_046 = left[4];      // original005e4e61
    const volatile long double extended_047 =
        extended_046 * static_cast<long double>(right[0]);                 // original005e4e64
    const volatile long double extended_048 = extended_045 + extended_047; // original005e4e66
    const volatile long double extended_049 = right[4];                    // original005e4e68
    const volatile long double extended_050 =
        extended_049 * static_cast<long double>(left[5]);                  // original005e4e6b
    const volatile long double extended_051 = extended_048 + extended_050; // original005e4e6e
    const volatile long double extended_052 = left[6];                     // original005e4e70
    const volatile long double extended_053 =
        extended_052 * static_cast<long double>(right[8]);                 // original005e4e73
    const volatile long double extended_054 = extended_051 + extended_053; // original005e4e76
    output[4] = static_cast<float>(extended_054);                          // original005e4e78
    const volatile long double extended_055 = left[6];                     // original005e4e7b
    const volatile long double extended_056 =
        extended_055 * static_cast<long double>(right[9]); // original005e4e7e
    const volatile long double extended_057 = left[7];     // original005e4e81
    const volatile long double extended_058 =
        extended_057 * static_cast<long double>(right[13]);                // original005e4e84
    const volatile long double extended_059 = extended_056 + extended_058; // original005e4e87
    const volatile long double extended_060 = right[5];                    // original005e4e89
    const volatile long double extended_061 =
        extended_060 * static_cast<long double>(left[5]);                  // original005e4e8c
    const volatile long double extended_062 = extended_059 + extended_061; // original005e4e8f
    const volatile long double extended_063 = right[1];                    // original005e4e91
    const volatile long double extended_064 =
        extended_063 * static_cast<long double>(left[4]);                  // original005e4e94
    const volatile long double extended_065 = extended_062 + extended_064; // original005e4e97
    output[5] = static_cast<float>(extended_065);                          // original005e4e99
    const volatile long double extended_066 = right[6];                    // original005e4e9c
    const volatile long double extended_067 =
        extended_066 * static_cast<long double>(left[5]); // original005e4e9f
    const volatile long double extended_068 = left[7];    // original005e4ea2
    const volatile long double extended_069 =
        extended_068 * static_cast<long double>(right[14]);                // original005e4ea5
    const volatile long double extended_070 = extended_067 + extended_069; // original005e4ea8
    const volatile long double extended_071 = right[2];                    // original005e4eaa
    const volatile long double extended_072 =
        extended_071 * static_cast<long double>(left[4]);                  // original005e4ead
    const volatile long double extended_073 = extended_070 + extended_072; // original005e4eb0
    const volatile long double extended_074 = left[6];                     // original005e4eb2
    const volatile long double extended_075 =
        extended_074 * static_cast<long double>(right[10]);                // original005e4eb5
    const volatile long double extended_076 = extended_073 + extended_075; // original005e4eb8
    output[6] = static_cast<float>(extended_076);                          // original005e4eba
    const volatile long double extended_077 = right[7];                    // original005e4ebd
    const volatile long double extended_078 =
        extended_077 * static_cast<long double>(left[5]); // original005e4ec0
    const volatile long double extended_079 = left[7];    // original005e4ec3
    const volatile long double extended_080 =
        extended_079 * static_cast<long double>(right[15]);                // original005e4ec6
    const volatile long double extended_081 = extended_078 + extended_080; // original005e4ec9
    const volatile long double extended_082 = left[6];                     // original005e4ecb
    const volatile long double extended_083 =
        extended_082 * static_cast<long double>(right[11]);                // original005e4ece
    const volatile long double extended_084 = extended_081 + extended_083; // original005e4ed1
    const volatile long double extended_085 = left[4];                     // original005e4ed3
    const volatile long double extended_086 =
        extended_085 * static_cast<long double>(right[3]);                 // original005e4ed6
    const volatile long double extended_087 = extended_084 + extended_086; // original005e4ed9
    output[7] = static_cast<float>(extended_087);                          // original005e4edb
    const volatile long double extended_088 = left[11];                    // original005e4ede
    const volatile long double extended_089 =
        extended_088 * static_cast<long double>(right[12]); // original005e4ee1
    const volatile long double extended_090 = left[8];      // original005e4ee4
    const volatile long double extended_091 =
        extended_090 * static_cast<long double>(right[0]);                 // original005e4ee7
    const volatile long double extended_092 = extended_089 + extended_091; // original005e4ee9
    const volatile long double extended_093 = right[4];                    // original005e4eeb
    const volatile long double extended_094 =
        extended_093 * static_cast<long double>(left[9]);                  // original005e4eee
    const volatile long double extended_095 = extended_092 + extended_094; // original005e4ef1
    const volatile long double extended_096 = left[10];                    // original005e4ef3
    const volatile long double extended_097 =
        extended_096 * static_cast<long double>(right[8]);                 // original005e4ef6
    const volatile long double extended_098 = extended_095 + extended_097; // original005e4ef9
    output[8] = static_cast<float>(extended_098);                          // original005e4efb
    const volatile long double extended_099 = left[11];                    // original005e4efe
    const volatile long double extended_100 =
        extended_099 * static_cast<long double>(right[13]); // original005e4f01
    const volatile long double extended_101 = left[10];     // original005e4f04
    const volatile long double extended_102 =
        extended_101 * static_cast<long double>(right[9]);                 // original005e4f07
    const volatile long double extended_103 = extended_100 + extended_102; // original005e4f0a
    const volatile long double extended_104 = right[5];                    // original005e4f0c
    const volatile long double extended_105 =
        extended_104 * static_cast<long double>(left[9]);                  // original005e4f0f
    const volatile long double extended_106 = extended_103 + extended_105; // original005e4f12
    const volatile long double extended_107 = right[1];                    // original005e4f14
    const volatile long double extended_108 =
        extended_107 * static_cast<long double>(left[8]);                  // original005e4f17
    const volatile long double extended_109 = extended_106 + extended_108; // original005e4f1a
    output[9] = static_cast<float>(extended_109);                          // original005e4f1c
    const volatile long double extended_110 = right[6];                    // original005e4f1f
    const volatile long double extended_111 =
        extended_110 * static_cast<long double>(left[9]); // original005e4f22
    const volatile long double extended_112 = right[2];   // original005e4f25
    const volatile long double extended_113 =
        extended_112 * static_cast<long double>(left[8]);                  // original005e4f28
    const volatile long double extended_114 = extended_111 + extended_113; // original005e4f2b
    const volatile long double extended_115 = left[11];                    // original005e4f2d
    const volatile long double extended_116 =
        extended_115 * static_cast<long double>(right[14]);                // original005e4f30
    const volatile long double extended_117 = extended_114 + extended_116; // original005e4f33
    const volatile long double extended_118 = left[10];                    // original005e4f35
    const volatile long double extended_119 =
        extended_118 * static_cast<long double>(right[10]);                // original005e4f38
    const volatile long double extended_120 = extended_117 + extended_119; // original005e4f3b
    output[10] = static_cast<float>(extended_120);                         // original005e4f3d
    const volatile long double extended_121 = left[11];                    // original005e4f40
    const volatile long double extended_122 =
        extended_121 * static_cast<long double>(right[15]); // original005e4f43
    const volatile long double extended_123 = left[10];     // original005e4f46
    const volatile long double extended_124 =
        extended_123 * static_cast<long double>(right[11]);                // original005e4f49
    const volatile long double extended_125 = extended_122 + extended_124; // original005e4f4c
    const volatile long double extended_126 = right[7];                    // original005e4f4e
    const volatile long double extended_127 =
        extended_126 * static_cast<long double>(left[9]);                  // original005e4f51
    const volatile long double extended_128 = extended_125 + extended_127; // original005e4f54
    const volatile long double extended_129 = left[8];                     // original005e4f56
    const volatile long double extended_130 =
        extended_129 * static_cast<long double>(right[3]);                 // original005e4f59
    const volatile long double extended_131 = extended_128 + extended_130; // original005e4f5c
    output[11] = static_cast<float>(extended_131);                         // original005e4f5e
    const volatile long double extended_132 = left[15];                    // original005e4f61
    const volatile long double extended_133 =
        extended_132 * static_cast<long double>(right[12]); // original005e4f64
    const volatile long double extended_134 = left[14];     // original005e4f67
    const volatile long double extended_135 =
        extended_134 * static_cast<long double>(right[8]);                 // original005e4f6a
    const volatile long double extended_136 = extended_133 + extended_135; // original005e4f6d
    const volatile long double extended_137 = left[12];                    // original005e4f6f
    const volatile long double extended_138 =
        extended_137 * static_cast<long double>(right[0]);                 // original005e4f72
    const volatile long double extended_139 = extended_136 + extended_138; // original005e4f74
    const volatile long double extended_140 = right[4];                    // original005e4f76
    const volatile long double extended_141 =
        extended_140 * static_cast<long double>(left[13]);                 // original005e4f79
    const volatile long double extended_142 = extended_139 + extended_141; // original005e4f7c
    output[12] = static_cast<float>(extended_142);                         // original005e4f7e
    const volatile long double extended_143 = left[15];                    // original005e4f81
    const volatile long double extended_144 =
        extended_143 * static_cast<long double>(right[13]); // original005e4f84
    const volatile long double extended_145 = right[5];     // original005e4f87
    const volatile long double extended_146 =
        extended_145 * static_cast<long double>(left[13]);                 // original005e4f8a
    const volatile long double extended_147 = extended_144 + extended_146; // original005e4f8d
    const volatile long double extended_148 = left[14];                    // original005e4f8f
    // Original005e4f92 CMP ESI,EAX supplies tail JE: scratch differs from output.
    const volatile long double extended_149 =
        extended_148 * static_cast<long double>(right[9]);                 // original005e4f94
    const volatile long double extended_150 = extended_147 + extended_149; // original005e4f97
    const volatile long double extended_151 = right[1];                    // original005e4f99
    const volatile long double extended_152 =
        extended_151 * static_cast<long double>(left[12]);                 // original005e4f9c
    const volatile long double extended_153 = extended_150 + extended_152; // original005e4f9f
    output[13] = static_cast<float>(extended_153);                         // original005e4fa1
    const volatile long double extended_154 = left[14];                    // original005e4fa4
    const volatile long double extended_155 =
        extended_154 * static_cast<long double>(right[10]); // original005e4fa7
    const volatile long double extended_156 = right[6];     // original005e4faa
    const volatile long double extended_157 =
        extended_156 * static_cast<long double>(left[13]);                 // original005e4fad
    const volatile long double extended_158 = extended_155 + extended_157; // original005e4fb0
    const volatile long double extended_159 = right[2];                    // original005e4fb2
    const volatile long double extended_160 =
        extended_159 * static_cast<long double>(left[12]);                 // original005e4fb5
    const volatile long double extended_161 = extended_158 + extended_160; // original005e4fb8
    const volatile long double extended_162 = left[15];                    // original005e4fba
    const volatile long double extended_163 =
        extended_162 * static_cast<long double>(right[14]);                // original005e4fbd
    const volatile long double extended_164 = extended_161 + extended_163; // original005e4fc0
    output[14] = static_cast<float>(extended_164);                         // original005e4fc2
    const volatile long double extended_165 = left[15];                    // original005e4fc5
    const volatile long double extended_166 =
        extended_165 * static_cast<long double>(right[15]); // original005e4fc8
    const volatile long double extended_167 = right[7];     // original005e4fcb
    const volatile long double extended_168 =
        extended_167 * static_cast<long double>(left[13]);                 // original005e4fce
    const volatile long double extended_169 = extended_166 + extended_168; // original005e4fd1
    const volatile long double extended_170 = left[12];                    // original005e4fd3
    const volatile long double extended_171 =
        extended_170 * static_cast<long double>(right[3]);                 // original005e4fd6
    const volatile long double extended_172 = extended_169 + extended_171; // original005e4fd9
    const volatile long double extended_173 = right[11];                   // original005e4fdb
    const volatile long double extended_174 =
        extended_173 * static_cast<long double>(left[14]);                 // original005e4fde
    const volatile long double extended_175 = extended_172 + extended_174; // original005e4fe1
    output[15] = static_cast<float>(extended_175);                         // original005e4fe3
    if (exact_alias)
        copy_sixteen_words(matrix,
                           output); // Original JE skips only the redundant direct-output copy.
    return matrix;
}

extern "C" D3DMATRIX* __attribute__((stdcall))
FUN_005e5093(D3DMATRIX* matrix, const D3DMATRIX* first, const D3DMATRIX* second) {
    const auto* left = reinterpret_cast<const float*>(first);
    const auto* right = reinterpret_cast<const float*>(second);
    const bool exact_alias = matrix == first || matrix == second;
    volatile float scratch[16];
    volatile float* output = exact_alias ? scratch : reinterpret_cast<volatile float*>(matrix);
    const volatile long double extended_000 = left[3]; // original005e50b2
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(right[12]); // original005e50b5
    const volatile long double extended_002 = left[0];      // original005e50b8
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(right[0]);                 // original005e50ba
    const volatile long double extended_004 = extended_001 + extended_003; // original005e50bc
    const volatile long double extended_005 = left[2];                     // original005e50be
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(right[8]);                 // original005e50c1
    const volatile long double extended_007 = extended_004 + extended_006; // original005e50c4
    const volatile long double extended_008 = right[4];                    // original005e50c6
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(left[1]);                  // original005e50c9
    const volatile long double extended_010 = extended_007 + extended_009; // original005e50cc
    output[0] = static_cast<float>(extended_010);                          // original005e50ce
    const volatile long double extended_011 = left[4];                     // original005e50d0
    const volatile long double extended_012 =
        extended_011 * static_cast<long double>(right[0]); // original005e50d3
    const volatile long double extended_013 = right[12];   // original005e50d5
    const volatile long double extended_014 =
        extended_013 * static_cast<long double>(left[7]);                  // original005e50d8
    const volatile long double extended_015 = extended_012 + extended_014; // original005e50db
    const volatile long double extended_016 = right[8];                    // original005e50dd
    const volatile long double extended_017 =
        extended_016 * static_cast<long double>(left[6]);                  // original005e50e0
    const volatile long double extended_018 = extended_015 + extended_017; // original005e50e3
    const volatile long double extended_019 = right[4];                    // original005e50e5
    const volatile long double extended_020 =
        extended_019 * static_cast<long double>(left[5]);                  // original005e50e8
    const volatile long double extended_021 = extended_018 + extended_020; // original005e50eb
    output[1] = static_cast<float>(extended_021);                          // original005e50ed
    const volatile long double extended_022 = left[10];                    // original005e50f0
    const volatile long double extended_023 =
        extended_022 * static_cast<long double>(right[8]); // original005e50f3
    const volatile long double extended_024 = left[9];     // original005e50f6
    const volatile long double extended_025 =
        extended_024 * static_cast<long double>(right[4]);                 // original005e50f9
    const volatile long double extended_026 = extended_023 + extended_025; // original005e50fc
    const volatile long double extended_027 = right[12];                   // original005e50fe
    const volatile long double extended_028 =
        extended_027 * static_cast<long double>(left[11]);                 // original005e5101
    const volatile long double extended_029 = extended_026 + extended_028; // original005e5104
    const volatile long double extended_030 = left[8];                     // original005e5106
    const volatile long double extended_031 =
        extended_030 * static_cast<long double>(right[0]);                 // original005e5109
    const volatile long double extended_032 = extended_029 + extended_031; // original005e510b
    output[2] = static_cast<float>(extended_032);                          // original005e510d
    const volatile long double extended_033 = left[13];                    // original005e5110
    const volatile long double extended_034 =
        extended_033 * static_cast<long double>(right[4]); // original005e5113
    const volatile long double extended_035 = left[15];    // original005e5116
    const volatile long double extended_036 =
        extended_035 * static_cast<long double>(right[12]);                // original005e5119
    const volatile long double extended_037 = extended_034 + extended_036; // original005e511c
    const volatile long double extended_038 = right[0];                    // original005e511e
    const volatile long double extended_039 =
        extended_038 * static_cast<long double>(left[12]);                 // original005e5120
    const volatile long double extended_040 = extended_037 + extended_039; // original005e5123
    const volatile long double extended_041 = left[14];                    // original005e5125
    const volatile long double extended_042 =
        extended_041 * static_cast<long double>(right[8]);                 // original005e5128
    const volatile long double extended_043 = extended_040 + extended_042; // original005e512b
    output[3] = static_cast<float>(extended_043);                          // original005e512d
    const volatile long double extended_044 = right[9];                    // original005e5130
    const volatile long double extended_045 =
        extended_044 * static_cast<long double>(left[2]); // original005e5133
    const volatile long double extended_046 = right[1];   // original005e5136
    const volatile long double extended_047 =
        extended_046 * static_cast<long double>(left[0]);                  // original005e5139
    const volatile long double extended_048 = extended_045 + extended_047; // original005e513b
    const volatile long double extended_049 = right[13];                   // original005e513d
    const volatile long double extended_050 =
        extended_049 * static_cast<long double>(left[3]);                  // original005e5140
    const volatile long double extended_051 = extended_048 + extended_050; // original005e5143
    const volatile long double extended_052 = left[1];                     // original005e5145
    const volatile long double extended_053 =
        extended_052 * static_cast<long double>(right[5]);                 // original005e5148
    const volatile long double extended_054 = extended_051 + extended_053; // original005e514b
    output[4] = static_cast<float>(extended_054);                          // original005e514d
    const volatile long double extended_055 = right[13];                   // original005e5150
    const volatile long double extended_056 =
        extended_055 * static_cast<long double>(left[7]); // original005e5153
    const volatile long double extended_057 = right[9];   // original005e5156
    const volatile long double extended_058 =
        extended_057 * static_cast<long double>(left[6]);                  // original005e5159
    const volatile long double extended_059 = extended_056 + extended_058; // original005e515c
    const volatile long double extended_060 = left[5];                     // original005e515e
    const volatile long double extended_061 =
        extended_060 * static_cast<long double>(right[5]);                 // original005e5161
    const volatile long double extended_062 = extended_059 + extended_061; // original005e5164
    const volatile long double extended_063 = left[4];                     // original005e5166
    const volatile long double extended_064 =
        extended_063 * static_cast<long double>(right[1]);                 // original005e5169
    const volatile long double extended_065 = extended_062 + extended_064; // original005e516c
    output[5] = static_cast<float>(extended_065);                          // original005e516e
    const volatile long double extended_066 = left[9];                     // original005e5171
    const volatile long double extended_067 =
        extended_066 * static_cast<long double>(right[5]); // original005e5174
    const volatile long double extended_068 = right[13];   // original005e5177
    const volatile long double extended_069 =
        extended_068 * static_cast<long double>(left[11]);                 // original005e517a
    const volatile long double extended_070 = extended_067 + extended_069; // original005e517d
    const volatile long double extended_071 = right[9];                    // original005e517f
    const volatile long double extended_072 =
        extended_071 * static_cast<long double>(left[10]);                 // original005e5182
    const volatile long double extended_073 = extended_070 + extended_072; // original005e5185
    const volatile long double extended_074 = left[8];                     // original005e5187
    const volatile long double extended_075 =
        extended_074 * static_cast<long double>(right[1]);                 // original005e518a
    const volatile long double extended_076 = extended_073 + extended_075; // original005e518d
    output[6] = static_cast<float>(extended_076);                          // original005e518f
    const volatile long double extended_077 = left[13];                    // original005e5192
    const volatile long double extended_078 =
        extended_077 * static_cast<long double>(right[5]); // original005e5195
    const volatile long double extended_079 = right[13];   // original005e5198
    const volatile long double extended_080 =
        extended_079 * static_cast<long double>(left[15]);                 // original005e519b
    const volatile long double extended_081 = extended_078 + extended_080; // original005e519e
    const volatile long double extended_082 = right[9];                    // original005e51a0
    const volatile long double extended_083 =
        extended_082 * static_cast<long double>(left[14]);                 // original005e51a3
    const volatile long double extended_084 = extended_081 + extended_083; // original005e51a6
    const volatile long double extended_085 = right[1];                    // original005e51a8
    const volatile long double extended_086 =
        extended_085 * static_cast<long double>(left[12]);                 // original005e51ab
    const volatile long double extended_087 = extended_084 + extended_086; // original005e51ae
    output[7] = static_cast<float>(extended_087);                          // original005e51b0
    const volatile long double extended_088 = right[10];                   // original005e51b3
    const volatile long double extended_089 =
        extended_088 * static_cast<long double>(left[2]); // original005e51b6
    const volatile long double extended_090 = right[2];   // original005e51b9
    const volatile long double extended_091 =
        extended_090 * static_cast<long double>(left[0]);                  // original005e51bc
    const volatile long double extended_092 = extended_089 + extended_091; // original005e51be
    const volatile long double extended_093 = left[1];                     // original005e51c0
    const volatile long double extended_094 =
        extended_093 * static_cast<long double>(right[6]);                 // original005e51c3
    const volatile long double extended_095 = extended_092 + extended_094; // original005e51c6
    const volatile long double extended_096 = right[14];                   // original005e51c8
    const volatile long double extended_097 =
        extended_096 * static_cast<long double>(left[3]);                  // original005e51cb
    const volatile long double extended_098 = extended_095 + extended_097; // original005e51ce
    output[8] = static_cast<float>(extended_098);                          // original005e51d0
    const volatile long double extended_099 = right[14];                   // original005e51d3
    const volatile long double extended_100 =
        extended_099 * static_cast<long double>(left[7]); // original005e51d6
    const volatile long double extended_101 = right[10];  // original005e51d9
    const volatile long double extended_102 =
        extended_101 * static_cast<long double>(left[6]);                  // original005e51dc
    const volatile long double extended_103 = extended_100 + extended_102; // original005e51df
    const volatile long double extended_104 = left[5];                     // original005e51e1
    const volatile long double extended_105 =
        extended_104 * static_cast<long double>(right[6]);                 // original005e51e4
    const volatile long double extended_106 = extended_103 + extended_105; // original005e51e7
    const volatile long double extended_107 = left[4];                     // original005e51e9
    const volatile long double extended_108 =
        extended_107 * static_cast<long double>(right[2]);                 // original005e51ec
    const volatile long double extended_109 = extended_106 + extended_108; // original005e51ef
    output[9] = static_cast<float>(extended_109);                          // original005e51f1
    const volatile long double extended_110 = left[9];                     // original005e51f4
    const volatile long double extended_111 =
        extended_110 * static_cast<long double>(right[6]); // original005e51f7
    const volatile long double extended_112 = right[14];   // original005e51fa
    const volatile long double extended_113 =
        extended_112 * static_cast<long double>(left[11]);                 // original005e51fd
    const volatile long double extended_114 = extended_111 + extended_113; // original005e5200
    const volatile long double extended_115 = right[10];                   // original005e5202
    const volatile long double extended_116 =
        extended_115 * static_cast<long double>(left[10]);                 // original005e5205
    const volatile long double extended_117 = extended_114 + extended_116; // original005e5208
    const volatile long double extended_118 = left[8];                     // original005e520a
    const volatile long double extended_119 =
        extended_118 * static_cast<long double>(right[2]);                 // original005e520d
    const volatile long double extended_120 = extended_117 + extended_119; // original005e5210
    output[10] = static_cast<float>(extended_120);                         // original005e5212
    const volatile long double extended_121 = left[13];                    // original005e5215
    const volatile long double extended_122 =
        extended_121 * static_cast<long double>(right[6]); // original005e5218
    const volatile long double extended_123 = right[14];   // original005e521b
    const volatile long double extended_124 =
        extended_123 * static_cast<long double>(left[15]);                 // original005e521e
    const volatile long double extended_125 = extended_122 + extended_124; // original005e5221
    const volatile long double extended_126 = right[10];                   // original005e5223
    const volatile long double extended_127 =
        extended_126 * static_cast<long double>(left[14]);                 // original005e5226
    const volatile long double extended_128 = extended_125 + extended_127; // original005e5229
    const volatile long double extended_129 = right[2];                    // original005e522b
    const volatile long double extended_130 =
        extended_129 * static_cast<long double>(left[12]);                 // original005e522e
    const volatile long double extended_131 = extended_128 + extended_130; // original005e5231
    output[11] = static_cast<float>(extended_131);                         // original005e5233
    const volatile long double extended_132 = right[3];                    // original005e5236
    const volatile long double extended_133 =
        extended_132 * static_cast<long double>(left[0]); // original005e5239
    const volatile long double extended_134 = left[1];    // original005e523b
    const volatile long double extended_135 =
        extended_134 * static_cast<long double>(right[7]);                 // original005e523e
    const volatile long double extended_136 = extended_133 + extended_135; // original005e5241
    const volatile long double extended_137 = right[15];                   // original005e5243
    const volatile long double extended_138 =
        extended_137 * static_cast<long double>(left[3]);                  // original005e5246
    const volatile long double extended_139 = extended_136 + extended_138; // original005e5249
    const volatile long double extended_140 = left[2];                     // original005e524b
    const volatile long double extended_141 =
        extended_140 * static_cast<long double>(right[11]);                // original005e524e
    const volatile long double extended_142 = extended_139 + extended_141; // original005e5251
    output[12] = static_cast<float>(extended_142);                         // original005e5253
    const volatile long double extended_143 = right[15];                   // original005e5256
    const volatile long double extended_144 =
        extended_143 * static_cast<long double>(left[7]); // original005e5259
    const volatile long double extended_145 = right[11];  // original005e525c
    const volatile long double extended_146 =
        extended_145 * static_cast<long double>(left[6]);                  // original005e525f
    const volatile long double extended_147 = extended_144 + extended_146; // original005e5262
    const volatile long double extended_148 = left[5];                     // original005e5264
    // Original005e5267 CMP ESI,EAX supplies tail JE: scratch differs from output.
    const volatile long double extended_149 =
        extended_148 * static_cast<long double>(right[7]);                 // original005e5269
    const volatile long double extended_150 = extended_147 + extended_149; // original005e526c
    const volatile long double extended_151 = left[4];                     // original005e526e
    const volatile long double extended_152 =
        extended_151 * static_cast<long double>(right[3]);                 // original005e5271
    const volatile long double extended_153 = extended_150 + extended_152; // original005e5274
    output[13] = static_cast<float>(extended_153);                         // original005e5276
    const volatile long double extended_154 = left[10];                    // original005e5279
    const volatile long double extended_155 =
        extended_154 * static_cast<long double>(right[11]); // original005e527c
    const volatile long double extended_156 = left[9];      // original005e527f
    const volatile long double extended_157 =
        extended_156 * static_cast<long double>(right[7]);                 // original005e5282
    const volatile long double extended_158 = extended_155 + extended_157; // original005e5285
    const volatile long double extended_159 = right[15];                   // original005e5287
    const volatile long double extended_160 =
        extended_159 * static_cast<long double>(left[11]);                 // original005e528a
    const volatile long double extended_161 = extended_158 + extended_160; // original005e528d
    const volatile long double extended_162 = left[8];                     // original005e528f
    const volatile long double extended_163 =
        extended_162 * static_cast<long double>(right[3]);                 // original005e5292
    const volatile long double extended_164 = extended_161 + extended_163; // original005e5295
    output[14] = static_cast<float>(extended_164);                         // original005e5297
    const volatile long double extended_165 = left[13];                    // original005e529a
    const volatile long double extended_166 =
        extended_165 * static_cast<long double>(right[7]); // original005e529d
    const volatile long double extended_167 = right[15];   // original005e52a0
    const volatile long double extended_168 =
        extended_167 * static_cast<long double>(left[15]);                 // original005e52a3
    const volatile long double extended_169 = extended_166 + extended_168; // original005e52a6
    const volatile long double extended_170 = right[3];                    // original005e52a8
    const volatile long double extended_171 =
        extended_170 * static_cast<long double>(left[12]);                 // original005e52ab
    const volatile long double extended_172 = extended_169 + extended_171; // original005e52ae
    const volatile long double extended_173 = left[14];                    // original005e52b0
    const volatile long double extended_174 =
        extended_173 * static_cast<long double>(right[11]);                // original005e52b3
    const volatile long double extended_175 = extended_172 + extended_174; // original005e52b6
    output[15] = static_cast<float>(extended_175);                         // original005e52b8
    if (exact_alias)
        copy_sixteen_words(matrix,
                           output); // Original JE skips only the redundant direct-output copy.
    return matrix;
}
using MatrixPair = D3DMATRIX*(__attribute__((stdcall)) *)(D3DMATRIX*, const D3DMATRIX*,
                                                          const D3DMATRIX*);
extern "C" D3DMATRIX* __attribute__((stdcall))
FUN_005e4da5(D3DMATRIX* output, const D3DMATRIX* left, const D3DMATRIX* right) {
    FUN_005fd1f8(1);
    return reinterpret_cast<MatrixPair>(dat_0070f370.entries[3])(output, left, right);
}
extern "C" D3DMATRIX* __attribute__((stdcall))
FUN_005e4db8(D3DMATRIX* output, const D3DMATRIX* left, const D3DMATRIX* right) {
    return reinterpret_cast<MatrixPair>(dat_0070f370.entries[3])(output, left, right);
}
extern "C" D3DMATRIX* __attribute__((stdcall))
FUN_005e5080(D3DMATRIX* output, const D3DMATRIX* left, const D3DMATRIX* right) {
    FUN_005fd1f8(1);
    return reinterpret_cast<MatrixPair>(dat_0070f370.entries[4])(output, left, right);
}
