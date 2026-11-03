void mix_volume_linear(u32 output, u32 a, u32 b, u32 c, u32 d, u32 x, u32 y, u32 z) {
    volatile float private_100, private_104, private_10c, private_110, private_114, private_11c,
        private_120, private_124, private_12c, private_130, private_134, private_13c, private_140,
        private_144, private_14c, private_150, private_154, private_15c, private_160, private_164,
        private_16c, private_170, private_174, private_17c, private_180, private_184, private_188,
        private_18c, private_190, private_194, private_48, private_4c, private_50, private_58,
        private_5c, private_60, private_6c, private_70, private_74, private_7c, private_80,
        private_84, private_8c, private_90, private_94, private_98, private_9c, private_a0,
        private_a8, private_ac, private_b0, private_bc, private_c0, private_c4, private_cc,
        private_d0, private_d4, private_dc, private_e0, private_e4, private_ec, private_f0,
        private_f4, private_fc;
    const u32 high = word(x), d_high = d + (high << 4), c_high = c + (high << 4);
    const volatile long double extended_000 =
        static_cast<long double>(f32(x + (4))); // original005ef0cc
    const volatile long double extended_001 =
        static_cast<long double>(extended_000); // original005ef0cf
    const volatile long double extended_002 =
        extended_001 * static_cast<long double>(f32(d_high + (0))); // original005ef0da
    private_104 = static_cast<float>(extended_002);                 // original005ef0dc
    const volatile long double extended_003 =
        static_cast<long double>(extended_000); // original005ef0e2
    const volatile long double extended_004 =
        extended_003 * static_cast<long double>(f32(d_high + (4))); // original005ef0e4
    private_100 = static_cast<float>(extended_004);                 // original005ef0e7
    const volatile long double extended_005 =
        static_cast<long double>(extended_000); // original005ef0ed
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(f32(d_high + (8))); // original005ef0ef
    private_fc = static_cast<float>(extended_006);                  // original005ef0f2
    const volatile long double extended_007 =
        extended_000 * static_cast<long double>(f32(d_high + (12))); // original005ef0f8
    const u32 low = word(x - 8), d_low = d + (low << 4), c_low = c + (low << 4),
              b_low = b + (low << 4), a_low = a + (low << 4);
    const volatile long double extended_008 =
        static_cast<long double>(f32(x + (-4))); // original005ef0fe
    const volatile long double extended_009 =
        static_cast<long double>(extended_008); // original005ef104
    const volatile long double extended_010 =
        extended_009 * static_cast<long double>(f32(d_low + (0))); // original005ef108
    const volatile long double extended_011 =
        static_cast<long double>(extended_008); // original005ef10a
    const volatile long double extended_012 =
        extended_011 * static_cast<long double>(f32(d_low + (4))); // original005ef10c
    private_50 = static_cast<float>(extended_012);                 // original005ef10f
    const volatile long double extended_013 =
        static_cast<long double>(extended_008); // original005ef112
    const volatile long double extended_014 =
        extended_013 * static_cast<long double>(f32(d_low + (8))); // original005ef114
    private_4c = static_cast<float>(extended_014);                 // original005ef117
    const volatile long double extended_015 =
        static_cast<long double>(extended_008); // original005ef11a
    const volatile long double extended_016 =
        extended_015 * static_cast<long double>(f32(d_low + (12))); // original005ef11c
    private_48 = static_cast<float>(extended_016);                  // original005ef126
    const volatile long double extended_017 =
        extended_010 + static_cast<long double>(private_104); // original005ef129
    private_84 = static_cast<float>(extended_017);            // original005ef12f
    const volatile long double extended_018 =
        static_cast<long double>(private_50); // original005ef137
    const volatile long double extended_019 =
        extended_018 + static_cast<long double>(private_100); // original005ef13a
    private_80 = static_cast<float>(extended_019);            // original005ef140
    const volatile long double extended_020 =
        static_cast<long double>(private_4c); // original005ef143
    const volatile long double extended_021 =
        extended_020 + static_cast<long double>(private_fc); // original005ef146
    private_7c = static_cast<float>(extended_021);           // original005ef14c
    const volatile long double extended_022 =
        extended_007 + static_cast<long double>(private_48); // original005ef14f
    const volatile long double extended_023 =
        static_cast<long double>(f32(y + (4))); // original005ef152
    const volatile long double extended_024 =
        static_cast<long double>(private_84); // original005ef155
    const volatile long double extended_025 =
        extended_024 * static_cast<long double>(extended_023); // original005ef15b
    private_164 = static_cast<float>(extended_025);            // original005ef15d
    const volatile long double extended_026 =
        static_cast<long double>(private_80); // original005ef163
    const volatile long double extended_027 =
        extended_026 * static_cast<long double>(extended_023); // original005ef166
    private_160 = static_cast<float>(extended_027);            // original005ef168
    const volatile long double extended_028 =
        static_cast<long double>(private_7c); // original005ef16e
    const volatile long double extended_029 =
        extended_028 * static_cast<long double>(extended_023); // original005ef171
    private_15c = static_cast<float>(extended_029);            // original005ef173
    const volatile long double extended_030 =
        static_cast<long double>(extended_022); // original005ef179
    const volatile long double extended_031 =
        extended_030 * static_cast<long double>(extended_023); // original005ef17b
    const volatile long double extended_032 =
        static_cast<long double>(f32(x + (4))); // original005ef181
    const volatile long double extended_033 =
        static_cast<long double>(extended_032); // original005ef184
    const volatile long double extended_034 =
        extended_033 * static_cast<long double>(f32(c_high + (0))); // original005ef186
    private_184 = static_cast<float>(extended_034);                 // original005ef188
    const volatile long double extended_035 =
        static_cast<long double>(extended_032); // original005ef18e
    const volatile long double extended_036 =
        extended_035 * static_cast<long double>(f32(c_high + (4))); // original005ef190
    private_180 = static_cast<float>(extended_036);                 // original005ef193
    const volatile long double extended_037 =
        static_cast<long double>(extended_032); // original005ef199
    const volatile long double extended_038 =
        extended_037 * static_cast<long double>(f32(c_high + (8))); // original005ef19b
    private_17c = static_cast<float>(extended_038);                 // original005ef19e
    const volatile long double extended_039 =
        extended_032 * static_cast<long double>(f32(c_high + (12))); // original005ef1a4
    const volatile long double extended_040 =
        static_cast<long double>(f32(x + (-4))); // original005ef1a7
    const volatile long double extended_041 =
        static_cast<long double>(extended_040); // original005ef1aa
    const volatile long double extended_042 =
        extended_041 * static_cast<long double>(f32(c_low + (0))); // original005ef1ac
    const volatile long double extended_043 =
        static_cast<long double>(extended_040); // original005ef1ae
    const volatile long double extended_044 =
        extended_043 * static_cast<long double>(f32(c_low + (4))); // original005ef1b0
    private_a0 = static_cast<float>(extended_044);                 // original005ef1b3
    const volatile long double extended_045 =
        static_cast<long double>(extended_040); // original005ef1b9
    const volatile long double extended_046 =
        extended_045 * static_cast<long double>(f32(c_low + (8))); // original005ef1bb
    private_9c = static_cast<float>(extended_046);                 // original005ef1be
    const volatile long double extended_047 =
        static_cast<long double>(extended_040); // original005ef1c4
    const volatile long double extended_048 =
        extended_047 * static_cast<long double>(f32(c_low + (12))); // original005ef1c6
    private_98 = static_cast<float>(extended_048);                  // original005ef1c9
    const volatile long double extended_049 =
        extended_042 + static_cast<long double>(private_184); // original005ef1cf
    private_124 = static_cast<float>(extended_049);           // original005ef1d5
    const volatile long double extended_050 =
        static_cast<long double>(private_a0); // original005ef1e3
    const volatile long double extended_051 =
        extended_050 + static_cast<long double>(private_180); // original005ef1e9
    private_120 = static_cast<float>(extended_051);           // original005ef1ef
    const volatile long double extended_052 =
        static_cast<long double>(private_9c); // original005ef1f5
    const volatile long double extended_053 =
        extended_052 + static_cast<long double>(private_17c); // original005ef1fb
    private_11c = static_cast<float>(extended_053);           // original005ef201
    const volatile long double extended_054 =
        extended_039 + static_cast<long double>(private_98); // original005ef207
    const volatile long double extended_055 =
        static_cast<long double>(f32(y + (-4))); // original005ef20d
    const volatile long double extended_056 =
        static_cast<long double>(private_124); // original005ef210
    const volatile long double extended_057 =
        extended_056 * static_cast<long double>(extended_055); // original005ef216
    private_c4 = static_cast<float>(extended_057);             // original005ef218
    const volatile long double extended_058 =
        static_cast<long double>(private_120); // original005ef21e
    const volatile long double extended_059 =
        extended_058 * static_cast<long double>(extended_055); // original005ef224
    private_c0 = static_cast<float>(extended_059);             // original005ef226
    const volatile long double extended_060 =
        static_cast<long double>(private_11c); // original005ef22c
    const volatile long double extended_061 =
        extended_060 * static_cast<long double>(extended_055); // original005ef232
    private_bc = static_cast<float>(extended_061);             // original005ef234
    const volatile long double extended_062 =
        static_cast<long double>(extended_054); // original005ef23a
    const volatile long double extended_063 =
        extended_062 * static_cast<long double>(extended_055); // original005ef23c
    const volatile long double extended_064 =
        static_cast<long double>(private_c4); // original005ef242
    const volatile long double extended_065 =
        extended_064 + static_cast<long double>(private_164); // original005ef248
    private_e4 = static_cast<float>(extended_065);            // original005ef24e
    const volatile long double extended_066 =
        static_cast<long double>(private_c0); // original005ef254
    const volatile long double extended_067 =
        extended_066 + static_cast<long double>(private_160); // original005ef25a
    private_e0 = static_cast<float>(extended_067);            // original005ef260
    const volatile long double extended_068 =
        static_cast<long double>(private_bc); // original005ef266
    const volatile long double extended_069 =
        extended_068 + static_cast<long double>(private_15c);              // original005ef26c
    private_dc = static_cast<float>(extended_069);                         // original005ef272
    const volatile long double extended_070 = extended_031 + extended_063; // original005ef278
    const volatile long double extended_071 =
        static_cast<long double>(f32(z + (4))); // original005ef27a
    const u32 high_again = word(x), b_high = b + (high_again << 4), a_high = a + (high_again << 4);
    const volatile long double extended_072 =
        static_cast<long double>(private_e4); // original005ef27f
    const volatile long double extended_073 =
        extended_072 * static_cast<long double>(extended_071); // original005ef288
    private_174 = static_cast<float>(extended_073);            // original005ef28c
    const volatile long double extended_074 =
        static_cast<long double>(private_e0); // original005ef292
    const volatile long double extended_075 =
        extended_074 * static_cast<long double>(extended_071); // original005ef298
    private_170 = static_cast<float>(extended_075);            // original005ef29a
    const volatile long double extended_076 =
        static_cast<long double>(private_dc); // original005ef2a0
    const volatile long double extended_077 =
        extended_076 * static_cast<long double>(extended_071); // original005ef2a6
    private_16c = static_cast<float>(extended_077);            // original005ef2a8
    const volatile long double extended_078 =
        static_cast<long double>(extended_070); // original005ef2ae
    const volatile long double extended_079 =
        extended_078 * static_cast<long double>(extended_071); // original005ef2b0
    const volatile long double extended_080 =
        static_cast<long double>(f32(x + (4))); // original005ef2b6
    const volatile long double extended_081 =
        static_cast<long double>(extended_080); // original005ef2b9
    const volatile long double extended_082 =
        extended_081 * static_cast<long double>(f32(b_high + (0))); // original005ef2bb
    private_144 = static_cast<float>(extended_082);                 // original005ef2bd
    const volatile long double extended_083 =
        static_cast<long double>(extended_080); // original005ef2c3
    const volatile long double extended_084 =
        extended_083 * static_cast<long double>(f32(b_high + (4))); // original005ef2c5
    private_140 = static_cast<float>(extended_084);                 // original005ef2c8
    const volatile long double extended_085 =
        static_cast<long double>(extended_080); // original005ef2ce
    const volatile long double extended_086 =
        extended_085 * static_cast<long double>(f32(b_high + (8))); // original005ef2d0
    private_13c = static_cast<float>(extended_086);                 // original005ef2d3
    const volatile long double extended_087 =
        extended_080 * static_cast<long double>(f32(b_high + (12))); // original005ef2d9
    const volatile long double extended_088 =
        static_cast<long double>(f32(x + (-4))); // original005ef2df
    const volatile long double extended_089 =
        static_cast<long double>(extended_088); // original005ef2e4
    const volatile long double extended_090 =
        extended_089 * static_cast<long double>(f32(b_low + (0))); // original005ef2e6
    const volatile long double extended_091 =
        static_cast<long double>(extended_088); // original005ef2e8
    const volatile long double extended_092 =
        extended_091 * static_cast<long double>(f32(b_low + (4))); // original005ef2ea
    private_60 = static_cast<float>(extended_092);                 // original005ef2ed
    const volatile long double extended_093 =
        static_cast<long double>(extended_088); // original005ef2f0
    const volatile long double extended_094 =
        extended_093 * static_cast<long double>(f32(b_low + (8))); // original005ef2f2
    private_5c = static_cast<float>(extended_094);                 // original005ef2f5
    const volatile long double extended_095 =
        static_cast<long double>(extended_088); // original005ef2f8
    const volatile long double extended_096 =
        extended_095 * static_cast<long double>(f32(b_low + (12))); // original005ef2fa
    private_58 = static_cast<float>(extended_096);                  // original005ef2fd
    const volatile long double extended_097 =
        extended_090 + static_cast<long double>(private_144); // original005ef300
    private_74 = static_cast<float>(extended_097);            // original005ef306
    const volatile long double extended_098 =
        static_cast<long double>(private_60); // original005ef30b
    const volatile long double extended_099 =
        extended_098 + static_cast<long double>(private_140); // original005ef30e
    private_70 = static_cast<float>(extended_099);            // original005ef31b
    const volatile long double extended_100 =
        static_cast<long double>(private_5c); // original005ef31e
    const volatile long double extended_101 =
        extended_100 + static_cast<long double>(private_13c); // original005ef321
    private_6c = static_cast<float>(extended_101);            // original005ef327
    const volatile long double extended_102 =
        extended_087 + static_cast<long double>(private_58); // original005ef32a
    const volatile long double extended_103 =
        static_cast<long double>(f32(y + (4))); // original005ef32d
    const volatile long double extended_104 =
        static_cast<long double>(private_74); // original005ef330
    const volatile long double extended_105 =
        extended_104 * static_cast<long double>(extended_103); // original005ef333
    private_114 = static_cast<float>(extended_105);            // original005ef335
    const volatile long double extended_106 =
        static_cast<long double>(private_70); // original005ef33b
    const volatile long double extended_107 =
        extended_106 * static_cast<long double>(extended_103); // original005ef33e
    private_110 = static_cast<float>(extended_107);            // original005ef340
    const volatile long double extended_108 =
        static_cast<long double>(private_6c); // original005ef346
    const volatile long double extended_109 =
        extended_108 * static_cast<long double>(extended_103); // original005ef349
    private_10c = static_cast<float>(extended_109);            // original005ef34b
    const volatile long double extended_110 =
        static_cast<long double>(extended_102); // original005ef351
    const volatile long double extended_111 =
        extended_110 * static_cast<long double>(extended_103); // original005ef353
    const volatile long double extended_112 =
        static_cast<long double>(f32(x + (4))); // original005ef359
    const volatile long double extended_113 =
        static_cast<long double>(extended_112); // original005ef35c
    const volatile long double extended_114 =
        extended_113 * static_cast<long double>(f32(a_high + (0))); // original005ef35e
    private_94 = static_cast<float>(extended_114);                  // original005ef360
    const volatile long double extended_115 =
        static_cast<long double>(extended_112); // original005ef366
    const volatile long double extended_116 =
        extended_115 * static_cast<long double>(f32(a_high + (4))); // original005ef368
    private_90 = static_cast<float>(extended_116);                  // original005ef36b
    const volatile long double extended_117 =
        static_cast<long double>(extended_112); // original005ef371
    const volatile long double extended_118 =
        extended_117 * static_cast<long double>(f32(a_high + (8))); // original005ef373
    private_8c = static_cast<float>(extended_118);                  // original005ef376
    const volatile long double extended_119 =
        extended_112 * static_cast<long double>(f32(a_high + (12))); // original005ef37c
    const volatile long double extended_120 =
        static_cast<long double>(f32(x + (-4))); // original005ef37f
    const volatile long double extended_121 =
        static_cast<long double>(extended_120); // original005ef382
    const volatile long double extended_122 =
        extended_121 * static_cast<long double>(f32(a_low + (0))); // original005ef384
    const volatile long double extended_123 =
        static_cast<long double>(extended_120); // original005ef386
    const volatile long double extended_124 =
        extended_123 * static_cast<long double>(f32(a_low + (4))); // original005ef388
    private_b0 = static_cast<float>(extended_124);                 // original005ef38b
    const volatile long double extended_125 =
        static_cast<long double>(extended_120); // original005ef391
    const volatile long double extended_126 =
        extended_125 * static_cast<long double>(f32(a_low + (8))); // original005ef393
    private_ac = static_cast<float>(extended_126);                 // original005ef396
    const volatile long double extended_127 =
        static_cast<long double>(extended_120); // original005ef39c
    const volatile long double extended_128 =
        extended_127 * static_cast<long double>(f32(a_low + (12))); // original005ef39e
    private_a8 = static_cast<float>(extended_128);                  // original005ef3a4
    const volatile long double extended_129 =
        extended_122 + static_cast<long double>(private_94); // original005ef3aa
    private_d4 = static_cast<float>(extended_129);           // original005ef3b0
    const volatile long double extended_130 =
        static_cast<long double>(private_b0); // original005ef3b8
    const volatile long double extended_131 =
        extended_130 + static_cast<long double>(private_90); // original005ef3be
    private_d0 = static_cast<float>(extended_131);           // original005ef3c4
    const volatile long double extended_132 =
        static_cast<long double>(private_ac); // original005ef3ca
    const volatile long double extended_133 =
        extended_132 + static_cast<long double>(private_8c); // original005ef3d0
    private_cc = static_cast<float>(extended_133);           // original005ef3d6
    const volatile long double extended_134 =
        extended_119 + static_cast<long double>(private_a8); // original005ef3dc
    const volatile long double extended_135 =
        static_cast<long double>(f32(y + (-4))); // original005ef3e2
    const volatile long double extended_136 =
        static_cast<long double>(private_d4); // original005ef3e5
    const volatile long double extended_137 =
        extended_136 * static_cast<long double>(extended_135); // original005ef3eb
    private_f4 = static_cast<float>(extended_137);             // original005ef3ed
    const volatile long double extended_138 =
        static_cast<long double>(private_d0); // original005ef3f3
    const volatile long double extended_139 =
        extended_138 * static_cast<long double>(extended_135); // original005ef3f9
    private_f0 = static_cast<float>(extended_139);             // original005ef3fb
    const volatile long double extended_140 =
        static_cast<long double>(private_cc); // original005ef401
    const volatile long double extended_141 =
        extended_140 * static_cast<long double>(extended_135); // original005ef407
    private_ec = static_cast<float>(extended_141);             // original005ef409
    const volatile long double extended_142 =
        static_cast<long double>(extended_134); // original005ef40f
    const volatile long double extended_143 =
        extended_142 * static_cast<long double>(extended_135); // original005ef411
    const volatile long double extended_144 =
        static_cast<long double>(private_f4); // original005ef417
    const volatile long double extended_145 =
        extended_144 + static_cast<long double>(private_114); // original005ef41d
    private_134 = static_cast<float>(extended_145);           // original005ef423
    const volatile long double extended_146 =
        static_cast<long double>(private_f0); // original005ef429
    const volatile long double extended_147 =
        extended_146 + static_cast<long double>(private_110); // original005ef42f
    private_130 = static_cast<float>(extended_147);           // original005ef435
    const volatile long double extended_148 =
        static_cast<long double>(private_ec); // original005ef43b
    const volatile long double extended_149 =
        extended_148 + static_cast<long double>(private_10c);              // original005ef441
    private_12c = static_cast<float>(extended_149);                        // original005ef447
    const volatile long double extended_150 = extended_111 + extended_143; // original005ef44d
    const volatile long double extended_151 =
        static_cast<long double>(f32(z + (-4))); // original005ef44f
    const volatile long double extended_152 =
        static_cast<long double>(private_134); // original005ef455
    const volatile long double extended_153 =
        extended_152 * static_cast<long double>(extended_151); // original005ef45f
    private_154 = static_cast<float>(extended_153);            // original005ef46d
    const volatile long double extended_154 =
        static_cast<long double>(private_130); // original005ef476
    const volatile long double extended_155 =
        extended_154 * static_cast<long double>(extended_151); // original005ef47c
    private_150 = static_cast<float>(extended_155);            // original005ef47e
    const volatile long double extended_156 =
        static_cast<long double>(private_12c); // original005ef484
    const volatile long double extended_157 =
        extended_156 * static_cast<long double>(extended_151); // original005ef48a
    private_14c = static_cast<float>(extended_157);            // original005ef48c
    const volatile long double extended_158 =
        static_cast<long double>(extended_150); // original005ef492
    const volatile long double extended_159 =
        extended_158 * static_cast<long double>(extended_151); // original005ef494
    const volatile long double extended_160 =
        static_cast<long double>(private_154); // original005ef49a
    const volatile long double extended_161 =
        extended_160 + static_cast<long double>(private_174); // original005ef4a0
    private_194 = static_cast<float>(extended_161);           // original005ef4a6
    const volatile long double extended_162 =
        static_cast<long double>(private_150); // original005ef4ac
    const volatile long double extended_163 =
        extended_162 + static_cast<long double>(private_170); // original005ef4b2
    private_190 = static_cast<float>(extended_163);           // original005ef4b8
    const volatile long double extended_164 =
        static_cast<long double>(private_14c); // original005ef4be
    const volatile long double extended_165 =
        extended_164 + static_cast<long double>(private_16c); // original005ef4c4
    private_18c = static_cast<float>(extended_165);           // original005ef4ca
    const volatile long double extended_166 =
        extended_159 + static_cast<long double>(extended_079);   // original005ef4d0
    private_188 = static_cast<float>(extended_166);              // original005ef4d2
    put(output + 0, word(reinterpret_cast<u32>(&private_194)));  // original005ef4d8
    put(output + 4, word(reinterpret_cast<u32>(&private_190)));  // original005ef4d9
    put(output + 8, word(reinterpret_cast<u32>(&private_18c)));  // original005ef4dc
    put(output + 12, word(reinterpret_cast<u32>(&private_188))); // original005ef4dd
}
