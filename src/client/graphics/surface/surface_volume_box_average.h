void average8(u32 output, u32 a, u32 b, u32 c, u32 d, u32 e, u32 f, u32 g, u32 h,
              const volatile long double& q) {
    volatile float private_3c, private_40, private_44, private_48, private_4c, private_50,
        private_58, private_5c, private_60, private_64, private_70, private_74, private_78,
        private_7c, private_88, private_8c, private_98, private_a4, private_a8, private_b4;
    const volatile long double extended_000 =
        static_cast<long double>(f32(b + 0)); // original005ee87e
    const volatile long double extended_001 =
        extended_000 + static_cast<long double>(f32(a + 0)); // original005ee882
    const volatile long double extended_002 =
        static_cast<long double>(f32(b + 4)); // original005ee884
    const volatile long double extended_003 =
        extended_002 + static_cast<long double>(f32(a + 4)); // original005ee887
    const volatile long double extended_004 =
        static_cast<long double>(f32(b + 8)); // original005ee88a
    const volatile long double extended_005 =
        extended_004 + static_cast<long double>(f32(a + 8)); // original005ee88d
    private_7c = static_cast<float>(extended_005);           // original005ee890
    const volatile long double extended_006 =
        static_cast<long double>(f32(b + 12)); // original005ee893
    const volatile long double extended_007 =
        extended_006 + static_cast<long double>(f32(a + 12)); // original005ee899
    private_78 = static_cast<float>(extended_007);            // original005ee89c
    const volatile long double extended_008 =
        static_cast<long double>(extended_001); // original005ee89f
    const volatile long double extended_009 =
        extended_008 + static_cast<long double>(f32(c + 0)); // original005ee8a1
    private_a4 = static_cast<float>(extended_009);           // original005ee8a3
    const volatile long double extended_010 =
        extended_003 + static_cast<long double>(f32(c + 4)); // original005ee8a9
    const volatile long double extended_011 =
        static_cast<long double>(private_7c); // original005ee8ae
    const volatile long double extended_012 =
        extended_011 + static_cast<long double>(f32(c + 8)); // original005ee8b1
    const volatile long double extended_013 =
        static_cast<long double>(private_78); // original005ee8b4
    const volatile long double extended_014 =
        extended_013 + static_cast<long double>(f32(c + 12)); // original005ee8b7
    private_98 = static_cast<float>(extended_014);            // original005ee8bf
    const volatile long double extended_015 =
        static_cast<long double>(private_a4); // original005ee8c5
    const volatile long double extended_016 =
        extended_015 + static_cast<long double>(f32(d + 0)); // original005ee8cb
    private_74 = static_cast<float>(extended_016);           // original005ee8cd
    const volatile long double extended_017 =
        static_cast<long double>(extended_010); // original005ee8d0
    const volatile long double extended_018 =
        extended_017 + static_cast<long double>(f32(d + 4)); // original005ee8d2
    private_70 = static_cast<float>(extended_018);           // original005ee8d5
    const volatile long double extended_019 =
        extended_012 + static_cast<long double>(f32(d + 8)); // original005ee8d8
    const volatile long double extended_020 =
        static_cast<long double>(private_98); // original005ee8dd
    const volatile long double extended_021 =
        extended_020 + static_cast<long double>(f32(d + 12)); // original005ee8e3
    const volatile long double extended_022 =
        static_cast<long double>(private_74); // original005ee8e9
    const volatile long double extended_023 =
        extended_022 + static_cast<long double>(f32(e + 0)); // original005ee8ee
    private_44 = static_cast<float>(extended_023);           // original005ee8f0
    const volatile long double extended_024 =
        static_cast<long double>(private_70); // original005ee8f3
    const volatile long double extended_025 =
        extended_024 + static_cast<long double>(f32(e + 4)); // original005ee8f6
    private_40 = static_cast<float>(extended_025);           // original005ee8f9
    const volatile long double extended_026 =
        static_cast<long double>(extended_019); // original005ee8fc
    const volatile long double extended_027 =
        extended_026 + static_cast<long double>(f32(e + 8)); // original005ee8fe
    private_3c = static_cast<float>(extended_027);           // original005ee901
    const volatile long double extended_028 =
        extended_021 + static_cast<long double>(f32(e + 12)); // original005ee904
    const volatile long double extended_029 =
        static_cast<long double>(private_44); // original005ee90e
    const volatile long double extended_030 =
        extended_029 + static_cast<long double>(f32(f + 0)); // original005ee911
    const volatile long double extended_031 =
        static_cast<long double>(private_40); // original005ee913
    const volatile long double extended_032 =
        extended_031 + static_cast<long double>(f32(f + 4)); // original005ee916
    private_50 = static_cast<float>(extended_032);           // original005ee919
    const volatile long double extended_033 =
        static_cast<long double>(private_3c); // original005ee91c
    const volatile long double extended_034 =
        extended_033 + static_cast<long double>(f32(f + 8)); // original005ee91f
    private_4c = static_cast<float>(extended_034);           // original005ee922
    const volatile long double extended_035 =
        static_cast<long double>(extended_028); // original005ee925
    const volatile long double extended_036 =
        extended_035 + static_cast<long double>(f32(f + 12)); // original005ee927
    private_48 = static_cast<float>(extended_036);            // original005ee92f
    const volatile long double extended_037 =
        extended_030 + static_cast<long double>(f32(g + 0)); // original005ee932
    const volatile long double extended_038 =
        static_cast<long double>(private_50); // original005ee936
    const volatile long double extended_039 =
        extended_038 + static_cast<long double>(f32(g + 4)); // original005ee939
    const volatile long double extended_040 =
        static_cast<long double>(private_4c); // original005ee93c
    const volatile long double extended_041 =
        extended_040 + static_cast<long double>(f32(g + 8)); // original005ee93f
    private_8c = static_cast<float>(extended_041);           // original005ee942
    const volatile long double extended_042 =
        static_cast<long double>(private_48); // original005ee948
    const volatile long double extended_043 =
        extended_042 + static_cast<long double>(f32(g + 12)); // original005ee94b
    private_88 = static_cast<float>(extended_043);            // original005ee953
    const volatile long double extended_044 =
        static_cast<long double>(extended_037); // original005ee959
    const volatile long double extended_045 =
        extended_044 + static_cast<long double>(f32(h + 0)); // original005ee95b
    private_b4 = static_cast<float>(extended_045);           // original005ee966
    const volatile long double extended_046 =
        extended_039 + static_cast<long double>(f32(h + 4)); // original005ee973
    const volatile long double extended_047 =
        static_cast<long double>(private_8c); // original005ee978
    const volatile long double extended_048 =
        extended_047 + static_cast<long double>(f32(h + 8)); // original005ee97e
    const volatile long double extended_049 =
        static_cast<long double>(private_88); // original005ee981
    const volatile long double extended_050 =
        extended_049 + static_cast<long double>(f32(h + 12)); // original005ee987
    private_a8 = static_cast<float>(extended_050);            // original005ee98a
    const volatile long double extended_051 =
        static_cast<long double>(private_b4); // original005ee990
    const volatile long double extended_052 =
        extended_051 * static_cast<long double>(q); // original005ee996
    private_64 = static_cast<float>(extended_052);  // original005ee998
    const volatile long double extended_053 =
        static_cast<long double>(extended_046); // original005ee99b
    const volatile long double extended_054 =
        extended_053 * static_cast<long double>(q); // original005ee99d
    private_60 = static_cast<float>(extended_054);  // original005ee99f
    const volatile long double extended_055 =
        extended_048 * static_cast<long double>(q); // original005ee9a2
    private_5c = static_cast<float>(extended_055);  // original005ee9a4
    const volatile long double extended_056 =
        static_cast<long double>(private_a8); // original005ee9a9
    const volatile long double extended_057 =
        extended_056 * static_cast<long double>(q); // original005ee9af
    private_58 = static_cast<float>(extended_057);  // original005ee9b1
    put(output + 0, word(reinterpret_cast<u32>(&private_64)));
    put(output + 4, word(reinterpret_cast<u32>(&private_60)));
    put(output + 8, word(reinterpret_cast<u32>(&private_5c)));
    put(output + 12, word(reinterpret_cast<u32>(&private_58)));
}
