void mix_linear(u32 output, u32 lower, u32 upper, u32 x, u32 y) {
    volatile float private_38, private_3c, private_40, private_44, private_48, private_4c,
        private_58, private_5c, private_60, private_68, private_6c, private_70, private_78,
        private_7c, private_80, private_84, private_88, private_8c, private_98, private_9c,
        private_a0, private_a8, private_ac, private_b0, private_b4, private_b8, private_bc,
        private_c0;
    const u32 high = word(x), upper_high = upper + (high << 4), lower_high = lower + (high << 4);
    const volatile long double extended_000 =
        static_cast<long double>(f32(x + (4))); // original005eeca5
    const volatile long double extended_001 =
        static_cast<long double>(extended_000); // original005eeca8
    const volatile long double extended_002 =
        extended_001 * static_cast<long double>(f32(upper_high + (0))); // original005eecb0
    private_70 = static_cast<float>(extended_002);                      // original005eecb2
    const volatile long double extended_003 =
        static_cast<long double>(extended_000); // original005eecb5
    const volatile long double extended_004 =
        extended_003 * static_cast<long double>(f32(upper_high + (4))); // original005eecb7
    private_6c = static_cast<float>(extended_004);                      // original005eecba
    const volatile long double extended_005 =
        static_cast<long double>(extended_000); // original005eecbd
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(f32(upper_high + (8))); // original005eecbf
    private_68 = static_cast<float>(extended_006);                      // original005eecc2
    const volatile long double extended_007 =
        extended_000 * static_cast<long double>(f32(upper_high + (12))); // original005eecc5
    const u32 low = word(x - 8), upper_low = upper + (low << 4), lower_low = lower + (low << 4);
    const volatile long double extended_008 =
        static_cast<long double>(f32(x + (-4))); // original005eeccb
    const volatile long double extended_009 =
        static_cast<long double>(extended_008); // original005eecd1
    const volatile long double extended_010 =
        extended_009 * static_cast<long double>(f32(upper_low + (0))); // original005eecd6
    const volatile long double extended_011 =
        static_cast<long double>(extended_008); // original005eecdb
    const volatile long double extended_012 =
        extended_011 * static_cast<long double>(f32(upper_low + (4))); // original005eecdf
    private_8c = static_cast<float>(extended_012);                     // original005eece4
    const volatile long double extended_013 =
        static_cast<long double>(extended_008); // original005eecea
    const volatile long double extended_014 =
        extended_013 * static_cast<long double>(f32(upper_low + (8))); // original005eecec
    private_88 = static_cast<float>(extended_014);                     // original005eecef
    const volatile long double extended_015 =
        static_cast<long double>(extended_008); // original005eecf5
    const volatile long double extended_016 =
        extended_015 * static_cast<long double>(f32(upper_low + (12))); // original005eecf7
    private_84 = static_cast<float>(extended_016);                      // original005eecfd
    const volatile long double extended_017 =
        extended_010 + static_cast<long double>(private_70); // original005eed03
    private_40 = static_cast<float>(extended_017);           // original005eed06
    const volatile long double extended_018 =
        static_cast<long double>(private_8c); // original005eed0b
    const volatile long double extended_019 =
        extended_018 + static_cast<long double>(private_6c); // original005eed11
    private_3c = static_cast<float>(extended_019);           // original005eed14
    const volatile long double extended_020 =
        static_cast<long double>(private_88); // original005eed17
    const volatile long double extended_021 =
        extended_020 + static_cast<long double>(private_68); // original005eed1d
    private_38 = static_cast<float>(extended_021);           // original005eed20
    const volatile long double extended_022 =
        extended_007 + static_cast<long double>(private_84); // original005eed23
    const volatile long double extended_023 =
        static_cast<long double>(f32(y + (4))); // original005eed29
    const volatile long double extended_024 =
        static_cast<long double>(private_40); // original005eed2c
    const volatile long double extended_025 =
        extended_024 * static_cast<long double>(extended_023); // original005eed2f
    private_a0 = static_cast<float>(extended_025);             // original005eed31
    const volatile long double extended_026 =
        static_cast<long double>(private_3c); // original005eed37
    const volatile long double extended_027 =
        extended_026 * static_cast<long double>(extended_023); // original005eed3a
    private_9c = static_cast<float>(extended_027);             // original005eed3c
    const volatile long double extended_028 =
        static_cast<long double>(private_38); // original005eed42
    const volatile long double extended_029 =
        extended_028 * static_cast<long double>(extended_023); // original005eed45
    private_98 = static_cast<float>(extended_029);             // original005eed47
    const volatile long double extended_030 =
        static_cast<long double>(extended_022); // original005eed4d
    const volatile long double extended_031 =
        extended_030 * static_cast<long double>(extended_023); // original005eed4f
    const volatile long double extended_032 =
        static_cast<long double>(f32(x + (4))); // original005eed55
    const volatile long double extended_033 =
        static_cast<long double>(extended_032); // original005eed58
    const volatile long double extended_034 =
        extended_033 * static_cast<long double>(f32(lower_high + (0))); // original005eed5a
    private_b0 = static_cast<float>(extended_034);                      // original005eed5c
    const volatile long double extended_035 =
        static_cast<long double>(extended_032); // original005eed62
    const volatile long double extended_036 =
        extended_035 * static_cast<long double>(f32(lower_high + (4))); // original005eed64
    private_ac = static_cast<float>(extended_036);                      // original005eed67
    const volatile long double extended_037 =
        static_cast<long double>(extended_032); // original005eed6d
    const volatile long double extended_038 =
        extended_037 * static_cast<long double>(f32(lower_high + (8))); // original005eed6f
    private_a8 = static_cast<float>(extended_038);                      // original005eed72
    const volatile long double extended_039 =
        extended_032 * static_cast<long double>(f32(lower_high + (12))); // original005eed78
    const volatile long double extended_040 =
        static_cast<long double>(f32(x + (-4))); // original005eed7b
    const volatile long double extended_041 =
        static_cast<long double>(extended_040); // original005eed7e
    const volatile long double extended_042 =
        extended_041 * static_cast<long double>(f32(lower_low + (0))); // original005eed80
    const volatile long double extended_043 =
        static_cast<long double>(extended_040); // original005eed82
    const volatile long double extended_044 =
        extended_043 * static_cast<long double>(f32(lower_low + (4))); // original005eed84
    private_4c = static_cast<float>(extended_044);                     // original005eed87
    const volatile long double extended_045 =
        static_cast<long double>(extended_040); // original005eed8a
    const volatile long double extended_046 =
        extended_045 * static_cast<long double>(f32(lower_low + (8))); // original005eed8c
    private_48 = static_cast<float>(extended_046);                     // original005eed8f
    const volatile long double extended_047 =
        static_cast<long double>(extended_040); // original005eed92
    const volatile long double extended_048 =
        extended_047 * static_cast<long double>(f32(lower_low + (12))); // original005eed94
    private_44 = static_cast<float>(extended_048);                      // original005eed97
    const volatile long double extended_049 =
        extended_042 + static_cast<long double>(private_b0); // original005eed9a
    private_60 = static_cast<float>(extended_049);           // original005eeda0
    const volatile long double extended_050 =
        static_cast<long double>(private_4c); // original005eedb2
    const volatile long double extended_051 =
        extended_050 + static_cast<long double>(private_ac); // original005eedb8
    private_5c = static_cast<float>(extended_051);           // original005eedc1
    const volatile long double extended_052 =
        static_cast<long double>(private_48); // original005eedc4
    const volatile long double extended_053 =
        extended_052 + static_cast<long double>(private_a8); // original005eedc7
    private_58 = static_cast<float>(extended_053);           // original005eedcd
    const volatile long double extended_054 =
        extended_039 + static_cast<long double>(private_44); // original005eedd0
    const volatile long double extended_055 =
        static_cast<long double>(f32(y + (-4))); // original005eedd3
    const volatile long double extended_056 =
        static_cast<long double>(private_60); // original005eedd9
    const volatile long double extended_057 =
        extended_056 * static_cast<long double>(extended_055); // original005eeddc
    private_80 = static_cast<float>(extended_057);             // original005eedde
    const volatile long double extended_058 =
        static_cast<long double>(private_5c); // original005eede1
    const volatile long double extended_059 =
        extended_058 * static_cast<long double>(extended_055); // original005eede4
    private_7c = static_cast<float>(extended_059);             // original005eede6
    const volatile long double extended_060 =
        static_cast<long double>(private_58); // original005eede9
    const volatile long double extended_061 =
        extended_060 * static_cast<long double>(extended_055); // original005eedec
    private_78 = static_cast<float>(extended_061);             // original005eedee
    const volatile long double extended_062 =
        static_cast<long double>(extended_054); // original005eedf1
    const volatile long double extended_063 =
        extended_062 * static_cast<long double>(extended_055); // original005eedf3
    const volatile long double extended_064 =
        static_cast<long double>(private_80); // original005eedf9
    const volatile long double extended_065 =
        extended_064 + static_cast<long double>(private_a0); // original005eedfc
    private_c0 = static_cast<float>(extended_065);           // original005eee02
    const volatile long double extended_066 =
        static_cast<long double>(private_7c); // original005eee08
    const volatile long double extended_067 =
        extended_066 + static_cast<long double>(private_9c); // original005eee0b
    private_bc = static_cast<float>(extended_067);           // original005eee11
    const volatile long double extended_068 =
        static_cast<long double>(private_78); // original005eee17
    const volatile long double extended_069 =
        extended_068 + static_cast<long double>(private_98); // original005eee1a
    private_b8 = static_cast<float>(extended_069);           // original005eee20
    const volatile long double extended_070 =
        extended_063 + static_cast<long double>(extended_031);  // original005eee26
    private_b4 = static_cast<float>(extended_070);              // original005eee28
    put(output + 0, word(reinterpret_cast<u32>(&private_c0)));  // original005eee2e
    put(output + 4, word(reinterpret_cast<u32>(&private_bc)));  // original005eee2f
    put(output + 8, word(reinterpret_cast<u32>(&private_b8)));  // original005eee32
    put(output + 12, word(reinterpret_cast<u32>(&private_b4))); // original005eee33
}
