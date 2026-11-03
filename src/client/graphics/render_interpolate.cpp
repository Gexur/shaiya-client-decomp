#include "graphics/render_interpolate.h"
namespace {
inline uint32_t word_at(uint32_t address) {
    uint32_t value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
inline volatile float& float_at(uint32_t address) {
    return *reinterpret_cast<volatile float*>(address);
}
} // namespace

extern "C" void* __attribute__((cdecl)) recovered_005e3ddd(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    volatile float private_4;
    volatile float private_8;
    const volatile long double extended_000 =
        static_cast<long double>(float_at(slots + 20)); // original005e3de4
    const uint32_t general_000 = word_at(slots + 4);    // original005e3de7
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(float_at(slots + 20)); // original005e3dea
    const uint32_t general_001 = word_at(slots + 8);                   // original005e3ded
    const volatile long double extended_002 =
        static_cast<long double>(float_at(slots + 20)); // original005e3df0
    const uint32_t general_002 = word_at(slots + 0);    // original005e3df3
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(extended_001); // original005e3df7
    const uint32_t general_003 = word_at(slots + 12);          // original005e3df9
    const uint32_t general_004 = word_at(slots + 16);          // original005e3dfd
    const volatile long double extended_004 =
        static_cast<long double>(extended_003); // original005e3e00
    const volatile long double extended_005 =
        extended_004 + static_cast<long double>(extended_003); // original005e3e02
    const volatile long double extended_006 =
        static_cast<long double>(extended_001); // original005e3e04
    const volatile long double extended_007 =
        extended_006 * static_cast<long double>(0x1.8000000000000p+1f); // original005e3e06
    const volatile long double extended_008 =
        static_cast<long double>(extended_005); // original005e3e0c
    const volatile long double extended_009 =
        extended_008 - static_cast<long double>(extended_007); // original005e3e0e
    const volatile long double extended_010 =
        extended_009 + static_cast<long double>(0x1.0000000000000p+0f); // original005e3e10
    private_8 = static_cast<float>(extended_010);                       // original005e3e16
    const volatile long double extended_011 =
        static_cast<long double>(extended_001); // original005e3e19
    const volatile long double extended_012 =
        extended_011 + static_cast<long double>(extended_011); // original005e3e1b
    const volatile long double extended_013 =
        extended_003 - static_cast<long double>(extended_012); // original005e3e1d
    const volatile long double extended_014 =
        extended_013 + static_cast<long double>(float_at(slots + 20)); // original005e3e1f
    private_4 = static_cast<float>(extended_014);                      // original005e3e22
    const volatile long double extended_015 =
        extended_007 - static_cast<long double>(extended_005);             // original005e3e25
    float_at(slots + 20) = static_cast<float>(extended_015);               // original005e3e27
    const volatile long double extended_016 = extended_003 - extended_001; // original005e3e2c
    const volatile long double extended_017 =
        static_cast<long double>(private_8); // original005e3e2e
    const volatile long double extended_018 =
        extended_017 *
        static_cast<long double>(float_at(general_000 + uint32_t(0))); // original005e3e31
    const volatile long double extended_019 =
        static_cast<long double>(private_4); // original005e3e33
    const volatile long double extended_020 =
        extended_019 *
        static_cast<long double>(float_at(general_001 + uint32_t(0)));     // original005e3e36
    const volatile long double extended_021 = extended_018 + extended_020; // original005e3e38
    const volatile long double extended_022 =
        static_cast<long double>(float_at(slots + 20)); // original005e3e3a
    const volatile long double extended_023 =
        extended_022 *
        static_cast<long double>(float_at(general_003 + uint32_t(0)));     // original005e3e3d
    const volatile long double extended_024 = extended_021 + extended_023; // original005e3e3f
    const volatile long double extended_025 =
        static_cast<long double>(extended_016); // original005e3e41
    const volatile long double extended_026 =
        extended_025 *
        static_cast<long double>(float_at(general_004 + uint32_t(0)));      // original005e3e43
    const volatile long double extended_027 = extended_024 + extended_026;  // original005e3e45
    float_at(general_002 + uint32_t(0)) = static_cast<float>(extended_027); // original005e3e47
    const volatile long double extended_028 =
        extended_016 *
        static_cast<long double>(float_at(general_004 + uint32_t(4))); // original005e3e49
    const volatile long double extended_029 =
        static_cast<long double>(float_at(slots + 20)); // original005e3e4d
    const volatile long double extended_030 =
        extended_029 *
        static_cast<long double>(float_at(general_003 + uint32_t(4)));     // original005e3e50
    const volatile long double extended_031 = extended_028 + extended_030; // original005e3e54
    const volatile long double extended_032 =
        static_cast<long double>(private_4); // original005e3e56
    const volatile long double extended_033 =
        extended_032 *
        static_cast<long double>(float_at(general_001 + uint32_t(4)));     // original005e3e59
    const volatile long double extended_034 = extended_031 + extended_033; // original005e3e5c
    const volatile long double extended_035 =
        static_cast<long double>(private_8); // original005e3e5e
    const volatile long double extended_036 =
        extended_035 *
        static_cast<long double>(float_at(general_000 + uint32_t(4)));      // original005e3e61
    const volatile long double extended_037 = extended_034 + extended_036;  // original005e3e64
    float_at(general_002 + uint32_t(4)) = static_cast<float>(extended_037); // original005e3e66
    return reinterpret_cast<void*>(general_002);
}

extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_005e3ddd(void*, const void*, const void*, const void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e3ddd\n\taddl $4,%esp\n\tretl $24");
}

extern "C" void* __attribute__((cdecl)) recovered_005e3e99(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    volatile float private_4;
    volatile float private_8;
    const volatile long double extended_000 =
        static_cast<long double>(float_at(slots + 20)); // original005e3ea0
    const uint32_t general_000 = word_at(slots + 4);    // original005e3ea3
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(float_at(slots + 20)); // original005e3ea6
    const uint32_t general_001 = word_at(slots + 8);                   // original005e3ea9
    const volatile long double extended_002 =
        static_cast<long double>(float_at(slots + 20)); // original005e3eac
    const uint32_t general_002 = word_at(slots + 0);    // original005e3eaf
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(extended_001); // original005e3eb3
    const uint32_t general_003 = word_at(slots + 12);          // original005e3eb5
    const volatile long double extended_004 =
        static_cast<long double>(0x1.0000000000000p+1f); // original005e3eb8
    const volatile long double extended_005 =
        static_cast<long double>(extended_001);       // original005e3ebf
    const uint32_t general_004 = word_at(slots + 16); // original005e3ec1
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(extended_004); // original005e3ec4
    const volatile long double extended_007 =
        extended_006 - static_cast<long double>(extended_003); // original005e3ec6
    const volatile long double extended_008 =
        extended_007 - static_cast<long double>(float_at(slots + 20)); // original005e3ec8
    private_8 = static_cast<float>(extended_008);                      // original005e3ecb
    const volatile long double extended_009 =
        static_cast<long double>(extended_003); // original005e3ece
    const volatile long double extended_010 =
        extended_009 * static_cast<long double>(0x1.8000000000000p+1f); // original005e3ed0
    const volatile long double extended_011 =
        static_cast<long double>(extended_001); // original005e3ed6
    const volatile long double extended_012 =
        extended_011 * static_cast<long double>(0x1.4000000000000p+2f); // original005e3ed8
    const volatile long double extended_013 =
        extended_010 - static_cast<long double>(extended_012); // original005e3ede
    const volatile long double extended_014 =
        extended_013 + static_cast<long double>(extended_004); // original005e3ee0
    private_4 = static_cast<float>(extended_014);              // original005e3ee2
    const volatile long double extended_015 =
        static_cast<long double>(extended_001); // original005e3ee5
    const volatile long double extended_016 =
        extended_015 * static_cast<long double>(0x1.0000000000000p+2f); // original005e3ee7
    const volatile long double extended_017 =
        extended_016 - static_cast<long double>(extended_010); // original005e3eed
    const volatile long double extended_018 =
        extended_017 + static_cast<long double>(float_at(slots + 20));     // original005e3eef
    float_at(slots + 20) = static_cast<float>(extended_018);               // original005e3ef2
    const volatile long double extended_019 = extended_003 - extended_001; // original005e3ef9
    const volatile long double extended_020 =
        static_cast<long double>(0x1.0000000000000p-1f); // original005e3efb
    const volatile long double extended_021 =
        static_cast<long double>(private_8); // original005e3f01
    const volatile long double extended_022 =
        extended_021 *
        static_cast<long double>(float_at(general_000 + uint32_t(0))); // original005e3f04
    const volatile long double extended_023 =
        static_cast<long double>(private_4); // original005e3f06
    const volatile long double extended_024 =
        extended_023 *
        static_cast<long double>(float_at(general_001 + uint32_t(0)));     // original005e3f09
    const volatile long double extended_025 = extended_022 + extended_024; // original005e3f0b
    const volatile long double extended_026 =
        static_cast<long double>(float_at(slots + 20)); // original005e3f0d
    const volatile long double extended_027 =
        extended_026 *
        static_cast<long double>(float_at(general_003 + uint32_t(0)));     // original005e3f10
    const volatile long double extended_028 = extended_025 + extended_027; // original005e3f12
    const volatile long double extended_029 =
        static_cast<long double>(extended_019); // original005e3f14
    const volatile long double extended_030 =
        extended_029 *
        static_cast<long double>(float_at(general_004 + uint32_t(0)));     // original005e3f16
    const volatile long double extended_031 = extended_028 + extended_030; // original005e3f18
    const volatile long double extended_032 =
        extended_031 * static_cast<long double>(extended_020);              // original005e3f1a
    float_at(general_002 + uint32_t(0)) = static_cast<float>(extended_032); // original005e3f1c
    const volatile long double extended_033 =
        static_cast<long double>(extended_019); // original005e3f1e
    const volatile long double extended_034 =
        extended_033 *
        static_cast<long double>(float_at(general_004 + uint32_t(4))); // original005e3f20
    const volatile long double extended_035 =
        static_cast<long double>(float_at(slots + 20)); // original005e3f24
    const volatile long double extended_036 =
        extended_035 *
        static_cast<long double>(float_at(general_003 + uint32_t(4)));     // original005e3f27
    const volatile long double extended_037 = extended_034 + extended_036; // original005e3f2b
    const volatile long double extended_038 =
        static_cast<long double>(private_4); // original005e3f2d
    const volatile long double extended_039 =
        extended_038 *
        static_cast<long double>(float_at(general_001 + uint32_t(4)));     // original005e3f30
    const volatile long double extended_040 = extended_037 + extended_039; // original005e3f33
    const volatile long double extended_041 =
        static_cast<long double>(private_8); // original005e3f35
    const volatile long double extended_042 =
        extended_041 *
        static_cast<long double>(float_at(general_000 + uint32_t(4)));     // original005e3f38
    const volatile long double extended_043 = extended_040 + extended_042; // original005e3f3b
    const volatile long double extended_044 =
        extended_043 * static_cast<long double>(extended_020);              // original005e3f3d
    float_at(general_002 + uint32_t(4)) = static_cast<float>(extended_044); // original005e3f3f
    return reinterpret_cast<void*>(general_002);
}

extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_005e3e99(void*, const void*, const void*, const void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e3e99\n\taddl $4,%esp\n\tretl $24");
}

extern "C" void* __attribute__((cdecl)) recovered_005e411d(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    volatile float private_4;
    volatile float private_8;
    const volatile long double extended_000 =
        static_cast<long double>(float_at(slots + 20)); // original005e4124
    const uint32_t general_000 = word_at(slots + 4);    // original005e4127
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(float_at(slots + 20)); // original005e412a
    const uint32_t general_001 = word_at(slots + 8);                   // original005e412d
    const volatile long double extended_002 =
        static_cast<long double>(float_at(slots + 20)); // original005e4130
    const uint32_t general_002 = word_at(slots + 0);    // original005e4133
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(extended_001); // original005e4137
    const uint32_t general_003 = word_at(slots + 12);          // original005e4139
    const uint32_t general_004 = word_at(slots + 16);          // original005e413d
    const volatile long double extended_004 =
        static_cast<long double>(extended_003); // original005e4140
    const volatile long double extended_005 =
        extended_004 + static_cast<long double>(extended_003); // original005e4142
    const volatile long double extended_006 =
        static_cast<long double>(extended_001); // original005e4144
    const volatile long double extended_007 =
        extended_006 * static_cast<long double>(0x1.8000000000000p+1f); // original005e4146
    const volatile long double extended_008 =
        static_cast<long double>(extended_005); // original005e414c
    const volatile long double extended_009 =
        extended_008 - static_cast<long double>(extended_007); // original005e414e
    const volatile long double extended_010 =
        extended_009 + static_cast<long double>(0x1.0000000000000p+0f); // original005e4150
    private_8 = static_cast<float>(extended_010);                       // original005e4156
    const volatile long double extended_011 =
        static_cast<long double>(extended_001); // original005e4159
    const volatile long double extended_012 =
        extended_011 + static_cast<long double>(extended_011); // original005e415b
    const volatile long double extended_013 =
        extended_003 - static_cast<long double>(extended_012); // original005e415d
    const volatile long double extended_014 =
        extended_013 + static_cast<long double>(float_at(slots + 20)); // original005e415f
    private_4 = static_cast<float>(extended_014);                      // original005e4162
    const volatile long double extended_015 =
        extended_007 - static_cast<long double>(extended_005);             // original005e4165
    float_at(slots + 20) = static_cast<float>(extended_015);               // original005e4167
    const volatile long double extended_016 = extended_003 - extended_001; // original005e416c
    const volatile long double extended_017 =
        static_cast<long double>(private_8); // original005e416e
    const volatile long double extended_018 =
        extended_017 *
        static_cast<long double>(float_at(general_000 + uint32_t(0))); // original005e4171
    const volatile long double extended_019 =
        static_cast<long double>(private_4); // original005e4173
    const volatile long double extended_020 =
        extended_019 *
        static_cast<long double>(float_at(general_001 + uint32_t(0)));     // original005e4176
    const volatile long double extended_021 = extended_018 + extended_020; // original005e4178
    const volatile long double extended_022 =
        static_cast<long double>(float_at(slots + 20)); // original005e417a
    const volatile long double extended_023 =
        extended_022 *
        static_cast<long double>(float_at(general_003 + uint32_t(0)));     // original005e417d
    const volatile long double extended_024 = extended_021 + extended_023; // original005e417f
    const volatile long double extended_025 =
        static_cast<long double>(extended_016); // original005e4181
    const volatile long double extended_026 =
        extended_025 *
        static_cast<long double>(float_at(general_004 + uint32_t(0)));      // original005e4183
    const volatile long double extended_027 = extended_024 + extended_026;  // original005e4185
    float_at(general_002 + uint32_t(0)) = static_cast<float>(extended_027); // original005e4187
    const volatile long double extended_028 =
        static_cast<long double>(extended_016); // original005e4189
    const volatile long double extended_029 =
        extended_028 *
        static_cast<long double>(float_at(general_004 + uint32_t(4))); // original005e418b
    const volatile long double extended_030 =
        static_cast<long double>(float_at(slots + 20)); // original005e418e
    const volatile long double extended_031 =
        extended_030 *
        static_cast<long double>(float_at(general_003 + uint32_t(4)));     // original005e4191
    const volatile long double extended_032 = extended_029 + extended_031; // original005e4194
    const volatile long double extended_033 =
        static_cast<long double>(private_4); // original005e4196
    const volatile long double extended_034 =
        extended_033 *
        static_cast<long double>(float_at(general_001 + uint32_t(4)));     // original005e4199
    const volatile long double extended_035 = extended_032 + extended_034; // original005e419c
    const volatile long double extended_036 =
        static_cast<long double>(private_8); // original005e419e
    const volatile long double extended_037 =
        extended_036 *
        static_cast<long double>(float_at(general_000 + uint32_t(4)));      // original005e41a1
    const volatile long double extended_038 = extended_035 + extended_037;  // original005e41a4
    float_at(general_002 + uint32_t(4)) = static_cast<float>(extended_038); // original005e41a6
    const volatile long double extended_039 =
        extended_016 *
        static_cast<long double>(float_at(general_004 + uint32_t(8))); // original005e41a9
    const volatile long double extended_040 =
        static_cast<long double>(float_at(slots + 20)); // original005e41ad
    const volatile long double extended_041 =
        extended_040 *
        static_cast<long double>(float_at(general_003 + uint32_t(8)));     // original005e41b0
    const volatile long double extended_042 = extended_039 + extended_041; // original005e41b4
    const volatile long double extended_043 =
        static_cast<long double>(private_4); // original005e41b6
    const volatile long double extended_044 =
        extended_043 *
        static_cast<long double>(float_at(general_001 + uint32_t(8)));     // original005e41b9
    const volatile long double extended_045 = extended_042 + extended_044; // original005e41bc
    const volatile long double extended_046 =
        static_cast<long double>(private_8); // original005e41be
    const volatile long double extended_047 =
        extended_046 *
        static_cast<long double>(float_at(general_000 + uint32_t(8)));      // original005e41c1
    const volatile long double extended_048 = extended_045 + extended_047;  // original005e41c4
    float_at(general_002 + uint32_t(8)) = static_cast<float>(extended_048); // original005e41c6
    return reinterpret_cast<void*>(general_002);
}

extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_005e411d(void*, const void*, const void*, const void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e411d\n\taddl $4,%esp\n\tretl $24");
}

extern "C" void* __attribute__((cdecl)) recovered_005e41f9(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    volatile float private_4;
    volatile float private_8;
    const volatile long double extended_000 =
        static_cast<long double>(float_at(slots + 20)); // original005e4200
    const uint32_t general_000 = word_at(slots + 4);    // original005e4203
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(float_at(slots + 20)); // original005e4206
    const uint32_t general_001 = word_at(slots + 8);                   // original005e4209
    const volatile long double extended_002 =
        static_cast<long double>(float_at(slots + 20)); // original005e420c
    const uint32_t general_002 = word_at(slots + 0);    // original005e420f
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(extended_001); // original005e4213
    const uint32_t general_003 = word_at(slots + 12);          // original005e4215
    const volatile long double extended_004 =
        static_cast<long double>(0x1.0000000000000p+1f); // original005e4218
    const volatile long double extended_005 =
        static_cast<long double>(extended_001);       // original005e421f
    const uint32_t general_004 = word_at(slots + 16); // original005e4221
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(extended_004); // original005e4224
    const volatile long double extended_007 =
        extended_006 - static_cast<long double>(extended_003); // original005e4226
    const volatile long double extended_008 =
        extended_007 - static_cast<long double>(float_at(slots + 20)); // original005e4228
    private_8 = static_cast<float>(extended_008);                      // original005e422b
    const volatile long double extended_009 =
        static_cast<long double>(extended_003); // original005e422e
    const volatile long double extended_010 =
        extended_009 * static_cast<long double>(0x1.8000000000000p+1f); // original005e4230
    const volatile long double extended_011 =
        static_cast<long double>(extended_001); // original005e4236
    const volatile long double extended_012 =
        extended_011 * static_cast<long double>(0x1.4000000000000p+2f); // original005e4238
    const volatile long double extended_013 =
        extended_010 - static_cast<long double>(extended_012); // original005e423e
    const volatile long double extended_014 =
        extended_013 + static_cast<long double>(extended_004); // original005e4240
    private_4 = static_cast<float>(extended_014);              // original005e4242
    const volatile long double extended_015 =
        static_cast<long double>(extended_001); // original005e4245
    const volatile long double extended_016 =
        extended_015 * static_cast<long double>(0x1.0000000000000p+2f); // original005e4247
    const volatile long double extended_017 =
        extended_016 - static_cast<long double>(extended_010); // original005e424d
    const volatile long double extended_018 =
        extended_017 + static_cast<long double>(float_at(slots + 20));     // original005e424f
    float_at(slots + 20) = static_cast<float>(extended_018);               // original005e4252
    const volatile long double extended_019 = extended_003 - extended_001; // original005e4259
    const volatile long double extended_020 =
        static_cast<long double>(0x1.0000000000000p-1f); // original005e425b
    const volatile long double extended_021 =
        static_cast<long double>(private_8); // original005e4261
    const volatile long double extended_022 =
        extended_021 *
        static_cast<long double>(float_at(general_000 + uint32_t(0))); // original005e4264
    const volatile long double extended_023 =
        static_cast<long double>(private_4); // original005e4266
    const volatile long double extended_024 =
        extended_023 *
        static_cast<long double>(float_at(general_001 + uint32_t(0)));     // original005e4269
    const volatile long double extended_025 = extended_022 + extended_024; // original005e426b
    const volatile long double extended_026 =
        static_cast<long double>(float_at(slots + 20)); // original005e426d
    const volatile long double extended_027 =
        extended_026 *
        static_cast<long double>(float_at(general_003 + uint32_t(0)));     // original005e4270
    const volatile long double extended_028 = extended_025 + extended_027; // original005e4272
    const volatile long double extended_029 =
        static_cast<long double>(extended_019); // original005e4274
    const volatile long double extended_030 =
        extended_029 *
        static_cast<long double>(float_at(general_004 + uint32_t(0)));     // original005e4276
    const volatile long double extended_031 = extended_028 + extended_030; // original005e4278
    const volatile long double extended_032 =
        extended_031 * static_cast<long double>(extended_020);              // original005e427a
    float_at(general_002 + uint32_t(0)) = static_cast<float>(extended_032); // original005e427c
    const volatile long double extended_033 =
        static_cast<long double>(extended_019); // original005e427e
    const volatile long double extended_034 =
        extended_033 *
        static_cast<long double>(float_at(general_004 + uint32_t(4))); // original005e4280
    const volatile long double extended_035 =
        static_cast<long double>(float_at(slots + 20)); // original005e4283
    const volatile long double extended_036 =
        extended_035 *
        static_cast<long double>(float_at(general_003 + uint32_t(4)));     // original005e4286
    const volatile long double extended_037 = extended_034 + extended_036; // original005e4289
    const volatile long double extended_038 =
        static_cast<long double>(private_4); // original005e428b
    const volatile long double extended_039 =
        extended_038 *
        static_cast<long double>(float_at(general_001 + uint32_t(4)));     // original005e428e
    const volatile long double extended_040 = extended_037 + extended_039; // original005e4291
    const volatile long double extended_041 =
        static_cast<long double>(private_8); // original005e4293
    const volatile long double extended_042 =
        extended_041 *
        static_cast<long double>(float_at(general_000 + uint32_t(4)));     // original005e4296
    const volatile long double extended_043 = extended_040 + extended_042; // original005e4299
    const volatile long double extended_044 =
        extended_043 * static_cast<long double>(extended_020);              // original005e429b
    float_at(general_002 + uint32_t(4)) = static_cast<float>(extended_044); // original005e429d
    const volatile long double extended_045 =
        static_cast<long double>(extended_019); // original005e42a0
    const volatile long double extended_046 =
        extended_045 *
        static_cast<long double>(float_at(general_004 + uint32_t(8))); // original005e42a2
    const volatile long double extended_047 =
        static_cast<long double>(float_at(slots + 20)); // original005e42a6
    const volatile long double extended_048 =
        extended_047 *
        static_cast<long double>(float_at(general_003 + uint32_t(8)));     // original005e42a9
    const volatile long double extended_049 = extended_046 + extended_048; // original005e42ad
    const volatile long double extended_050 =
        static_cast<long double>(private_4); // original005e42af
    const volatile long double extended_051 =
        extended_050 *
        static_cast<long double>(float_at(general_001 + uint32_t(8)));     // original005e42b2
    const volatile long double extended_052 = extended_049 + extended_051; // original005e42b5
    const volatile long double extended_053 =
        static_cast<long double>(private_8); // original005e42b7
    const volatile long double extended_054 =
        extended_053 *
        static_cast<long double>(float_at(general_000 + uint32_t(8)));     // original005e42ba
    const volatile long double extended_055 = extended_052 + extended_054; // original005e42bd
    const volatile long double extended_056 =
        extended_055 * static_cast<long double>(extended_020);              // original005e42bf
    float_at(general_002 + uint32_t(8)) = static_cast<float>(extended_056); // original005e42c1
    return reinterpret_cast<void*>(general_002);
}

extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_005e41f9(void*, const void*, const void*, const void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e41f9\n\taddl $4,%esp\n\tretl $24");
}

extern "C" void* __attribute__((cdecl)) recovered_005e4881(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    volatile float private_4;
    volatile float private_8;
    volatile float private_12;
    const volatile long double extended_000 =
        static_cast<long double>(float_at(slots + 20)); // original005e4889
    const uint32_t general_000 = word_at(slots + 4);    // original005e488c
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(float_at(slots + 20)); // original005e488f
    const uint32_t general_001 = word_at(slots + 8);                   // original005e4892
    const volatile long double extended_002 =
        static_cast<long double>(float_at(slots + 20)); // original005e4895
    const uint32_t general_002 = word_at(slots + 0);    // original005e4898
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(extended_001); // original005e489c
    const uint32_t general_003 = word_at(slots + 12);          // original005e489e
    const uint32_t general_004 = word_at(slots + 16);          // original005e48a2
    private_4 = static_cast<float>(extended_003);              // original005e48a5
    const volatile long double extended_004 =
        extended_003 + static_cast<long double>(extended_003); // original005e48a8
    private_12 = static_cast<float>(extended_004);             // original005e48aa
    const volatile long double extended_005 =
        static_cast<long double>(0x1.8000000000000p+1f); // original005e48ad
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(extended_001); // original005e48b3
    private_8 = static_cast<float>(extended_006);              // original005e48b5
    const volatile long double extended_007 =
        static_cast<long double>(private_12); // original005e48b8
    const volatile long double extended_008 =
        extended_007 - static_cast<long double>(private_8); // original005e48bb
    const volatile long double extended_009 =
        extended_008 + static_cast<long double>(0x1.0000000000000p+0f); // original005e48be
    const volatile long double extended_010 =
        static_cast<long double>(extended_001); // original005e48c4
    const volatile long double extended_011 =
        extended_010 + static_cast<long double>(extended_010); // original005e48c6
    const volatile long double extended_012 =
        private_4 - static_cast<long double>(extended_011); // original005e48c8
    const volatile long double extended_013 =
        extended_012 + static_cast<long double>(float_at(slots + 20)); // original005e48cb
    const volatile long double extended_014 =
        static_cast<long double>(private_8); // original005e48ce
    const volatile long double extended_015 =
        extended_014 - static_cast<long double>(private_12); // original005e48d1
    const volatile long double extended_016 =
        static_cast<long double>(private_4); // original005e48d4
    const volatile long double extended_017 =
        extended_016 - static_cast<long double>(extended_001); // original005e48d7
    const volatile long double extended_018 =
        static_cast<long double>(extended_009); // original005e48d9
    const volatile long double extended_019 =
        extended_018 *
        static_cast<long double>(float_at(general_000 + uint32_t(0))); // original005e48db
    const volatile long double extended_020 =
        static_cast<long double>(extended_013); // original005e48dd
    const volatile long double extended_021 =
        extended_020 *
        static_cast<long double>(float_at(general_001 + uint32_t(0)));     // original005e48df
    const volatile long double extended_022 = extended_019 + extended_021; // original005e48e1
    const volatile long double extended_023 =
        static_cast<long double>(extended_015); // original005e48e3
    const volatile long double extended_024 =
        extended_023 *
        static_cast<long double>(float_at(general_003 + uint32_t(0)));     // original005e48e5
    const volatile long double extended_025 = extended_022 + extended_024; // original005e48e7
    const volatile long double extended_026 =
        static_cast<long double>(extended_017); // original005e48e9
    const volatile long double extended_027 =
        extended_026 *
        static_cast<long double>(float_at(general_004 + uint32_t(0)));      // original005e48eb
    const volatile long double extended_028 = extended_025 + extended_027;  // original005e48ed
    float_at(general_002 + uint32_t(0)) = static_cast<float>(extended_028); // original005e48ef
    const volatile long double extended_029 =
        static_cast<long double>(extended_017); // original005e48f1
    const volatile long double extended_030 =
        extended_029 *
        static_cast<long double>(float_at(general_004 + uint32_t(4))); // original005e48f3
    const volatile long double extended_031 =
        static_cast<long double>(extended_015); // original005e48f6
    const volatile long double extended_032 =
        extended_031 *
        static_cast<long double>(float_at(general_003 + uint32_t(4)));     // original005e48f8
    const volatile long double extended_033 = extended_030 + extended_032; // original005e48fb
    const volatile long double extended_034 =
        static_cast<long double>(extended_013); // original005e48fd
    const volatile long double extended_035 =
        extended_034 *
        static_cast<long double>(float_at(general_001 + uint32_t(4)));     // original005e48ff
    const volatile long double extended_036 = extended_033 + extended_035; // original005e4902
    const volatile long double extended_037 =
        static_cast<long double>(extended_009); // original005e4904
    const volatile long double extended_038 =
        extended_037 *
        static_cast<long double>(float_at(general_000 + uint32_t(4)));      // original005e4906
    const volatile long double extended_039 = extended_036 + extended_038;  // original005e4909
    float_at(general_002 + uint32_t(4)) = static_cast<float>(extended_039); // original005e490b
    const volatile long double extended_040 =
        static_cast<long double>(extended_017); // original005e490e
    const volatile long double extended_041 =
        extended_040 *
        static_cast<long double>(float_at(general_004 + uint32_t(8))); // original005e4910
    const volatile long double extended_042 =
        static_cast<long double>(extended_015); // original005e4913
    const volatile long double extended_043 =
        extended_042 *
        static_cast<long double>(float_at(general_003 + uint32_t(8)));     // original005e4915
    const volatile long double extended_044 = extended_041 + extended_043; // original005e4918
    const volatile long double extended_045 =
        static_cast<long double>(extended_013); // original005e491a
    const volatile long double extended_046 =
        extended_045 *
        static_cast<long double>(float_at(general_001 + uint32_t(8)));     // original005e491c
    const volatile long double extended_047 = extended_044 + extended_046; // original005e491f
    const volatile long double extended_048 =
        static_cast<long double>(extended_009); // original005e4921
    const volatile long double extended_049 =
        extended_048 *
        static_cast<long double>(float_at(general_000 + uint32_t(8)));      // original005e4923
    const volatile long double extended_050 = extended_047 + extended_049;  // original005e4926
    float_at(general_002 + uint32_t(8)) = static_cast<float>(extended_050); // original005e4928
    const volatile long double extended_051 =
        extended_017 *
        static_cast<long double>(float_at(general_004 + uint32_t(12))); // original005e492b
    const volatile long double extended_052 =
        static_cast<long double>(extended_015); // original005e492f
    const volatile long double extended_053 =
        extended_052 *
        static_cast<long double>(float_at(general_003 + uint32_t(12)));    // original005e4931
    const volatile long double extended_054 = extended_051 + extended_053; // original005e4935
    const volatile long double extended_055 =
        static_cast<long double>(extended_013); // original005e4937
    const volatile long double extended_056 =
        extended_055 *
        static_cast<long double>(float_at(general_001 + uint32_t(12)));    // original005e4939
    const volatile long double extended_057 = extended_054 + extended_056; // original005e493c
    const volatile long double extended_058 =
        static_cast<long double>(extended_009); // original005e493e
    const volatile long double extended_059 =
        extended_058 *
        static_cast<long double>(float_at(general_000 + uint32_t(12)));      // original005e4940
    const volatile long double extended_060 = extended_057 + extended_059;   // original005e4943
    float_at(general_002 + uint32_t(12)) = static_cast<float>(extended_060); // original005e4945
    return reinterpret_cast<void*>(general_002);
}

extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_005e4881(void*, const void*, const void*, const void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e4881\n\taddl $4,%esp\n\tretl $24");
}

extern "C" void* __attribute__((cdecl)) recovered_005e4980(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    volatile float private_4;
    volatile float private_8;
    const volatile long double extended_000 =
        static_cast<long double>(float_at(slots + 20)); // original005e4987
    const uint32_t general_000 = word_at(slots + 4);    // original005e498a
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(float_at(slots + 20)); // original005e498d
    const uint32_t general_001 = word_at(slots + 8);                   // original005e4990
    const volatile long double extended_002 =
        static_cast<long double>(float_at(slots + 20)); // original005e4993
    const uint32_t general_002 = word_at(slots + 0);    // original005e4996
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(extended_001); // original005e499a
    const uint32_t general_003 = word_at(slots + 12);          // original005e499c
    const volatile long double extended_004 =
        static_cast<long double>(0x1.0000000000000p+1f); // original005e499f
    const volatile long double extended_005 =
        static_cast<long double>(extended_001);       // original005e49a6
    const uint32_t general_004 = word_at(slots + 16); // original005e49a8
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(extended_004); // original005e49ab
    const volatile long double extended_007 =
        extended_006 - static_cast<long double>(extended_003); // original005e49ad
    const volatile long double extended_008 =
        extended_007 - static_cast<long double>(float_at(slots + 20)); // original005e49af
    private_8 = static_cast<float>(extended_008);                      // original005e49b2
    const volatile long double extended_009 =
        static_cast<long double>(extended_003); // original005e49b5
    const volatile long double extended_010 =
        extended_009 * static_cast<long double>(0x1.8000000000000p+1f); // original005e49b7
    const volatile long double extended_011 =
        static_cast<long double>(extended_001); // original005e49bd
    const volatile long double extended_012 =
        extended_011 * static_cast<long double>(0x1.4000000000000p+2f); // original005e49bf
    const volatile long double extended_013 =
        extended_010 - static_cast<long double>(extended_012); // original005e49c5
    const volatile long double extended_014 =
        extended_013 + static_cast<long double>(extended_004); // original005e49c7
    private_4 = static_cast<float>(extended_014);              // original005e49c9
    const volatile long double extended_015 =
        static_cast<long double>(extended_001); // original005e49cc
    const volatile long double extended_016 =
        extended_015 * static_cast<long double>(0x1.0000000000000p+2f); // original005e49ce
    const volatile long double extended_017 =
        extended_016 - static_cast<long double>(extended_010); // original005e49d4
    const volatile long double extended_018 =
        extended_017 + static_cast<long double>(float_at(slots + 20));     // original005e49d6
    float_at(slots + 20) = static_cast<float>(extended_018);               // original005e49d9
    const volatile long double extended_019 = extended_003 - extended_001; // original005e49e0
    const volatile long double extended_020 =
        static_cast<long double>(0x1.0000000000000p-1f); // original005e49e2
    const volatile long double extended_021 =
        static_cast<long double>(private_8); // original005e49e8
    const volatile long double extended_022 =
        extended_021 *
        static_cast<long double>(float_at(general_000 + uint32_t(0))); // original005e49eb
    const volatile long double extended_023 =
        static_cast<long double>(private_4); // original005e49ed
    const volatile long double extended_024 =
        extended_023 *
        static_cast<long double>(float_at(general_001 + uint32_t(0)));     // original005e49f0
    const volatile long double extended_025 = extended_022 + extended_024; // original005e49f2
    const volatile long double extended_026 =
        static_cast<long double>(float_at(slots + 20)); // original005e49f4
    const volatile long double extended_027 =
        extended_026 *
        static_cast<long double>(float_at(general_003 + uint32_t(0)));     // original005e49f7
    const volatile long double extended_028 = extended_025 + extended_027; // original005e49f9
    const volatile long double extended_029 =
        static_cast<long double>(extended_019); // original005e49fb
    const volatile long double extended_030 =
        extended_029 *
        static_cast<long double>(float_at(general_004 + uint32_t(0)));     // original005e49fd
    const volatile long double extended_031 = extended_028 + extended_030; // original005e49ff
    const volatile long double extended_032 =
        extended_031 * static_cast<long double>(extended_020);              // original005e4a01
    float_at(general_002 + uint32_t(0)) = static_cast<float>(extended_032); // original005e4a03
    const volatile long double extended_033 =
        static_cast<long double>(extended_019); // original005e4a05
    const volatile long double extended_034 =
        extended_033 *
        static_cast<long double>(float_at(general_004 + uint32_t(4))); // original005e4a07
    const volatile long double extended_035 =
        static_cast<long double>(float_at(slots + 20)); // original005e4a0a
    const volatile long double extended_036 =
        extended_035 *
        static_cast<long double>(float_at(general_003 + uint32_t(4)));     // original005e4a0d
    const volatile long double extended_037 = extended_034 + extended_036; // original005e4a10
    const volatile long double extended_038 =
        static_cast<long double>(private_4); // original005e4a12
    const volatile long double extended_039 =
        extended_038 *
        static_cast<long double>(float_at(general_001 + uint32_t(4)));     // original005e4a15
    const volatile long double extended_040 = extended_037 + extended_039; // original005e4a18
    const volatile long double extended_041 =
        static_cast<long double>(private_8); // original005e4a1a
    const volatile long double extended_042 =
        extended_041 *
        static_cast<long double>(float_at(general_000 + uint32_t(4)));     // original005e4a1d
    const volatile long double extended_043 = extended_040 + extended_042; // original005e4a20
    const volatile long double extended_044 =
        extended_043 * static_cast<long double>(extended_020);              // original005e4a22
    float_at(general_002 + uint32_t(4)) = static_cast<float>(extended_044); // original005e4a24
    const volatile long double extended_045 =
        static_cast<long double>(extended_019); // original005e4a27
    const volatile long double extended_046 =
        extended_045 *
        static_cast<long double>(float_at(general_004 + uint32_t(8))); // original005e4a29
    const volatile long double extended_047 =
        static_cast<long double>(float_at(slots + 20)); // original005e4a2c
    const volatile long double extended_048 =
        extended_047 *
        static_cast<long double>(float_at(general_003 + uint32_t(8)));     // original005e4a2f
    const volatile long double extended_049 = extended_046 + extended_048; // original005e4a32
    const volatile long double extended_050 =
        static_cast<long double>(private_4); // original005e4a34
    const volatile long double extended_051 =
        extended_050 *
        static_cast<long double>(float_at(general_001 + uint32_t(8)));     // original005e4a37
    const volatile long double extended_052 = extended_049 + extended_051; // original005e4a3a
    const volatile long double extended_053 =
        static_cast<long double>(private_8); // original005e4a3c
    const volatile long double extended_054 =
        extended_053 *
        static_cast<long double>(float_at(general_000 + uint32_t(8)));     // original005e4a3f
    const volatile long double extended_055 = extended_052 + extended_054; // original005e4a42
    const volatile long double extended_056 =
        extended_055 * static_cast<long double>(extended_020);              // original005e4a44
    float_at(general_002 + uint32_t(8)) = static_cast<float>(extended_056); // original005e4a46
    const volatile long double extended_057 =
        static_cast<long double>(extended_019); // original005e4a49
    const volatile long double extended_058 =
        extended_057 *
        static_cast<long double>(float_at(general_004 + uint32_t(12))); // original005e4a4b
    const volatile long double extended_059 =
        static_cast<long double>(float_at(slots + 20)); // original005e4a4e
    const volatile long double extended_060 =
        extended_059 *
        static_cast<long double>(float_at(general_003 + uint32_t(12)));    // original005e4a51
    const volatile long double extended_061 = extended_058 + extended_060; // original005e4a54
    const volatile long double extended_062 =
        static_cast<long double>(private_4); // original005e4a56
    const volatile long double extended_063 =
        extended_062 *
        static_cast<long double>(float_at(general_001 + uint32_t(12)));    // original005e4a59
    const volatile long double extended_064 = extended_061 + extended_063; // original005e4a5e
    const volatile long double extended_065 =
        static_cast<long double>(private_8); // original005e4a60
    const volatile long double extended_066 =
        extended_065 *
        static_cast<long double>(float_at(general_000 + uint32_t(12)));    // original005e4a63
    const volatile long double extended_067 = extended_064 + extended_066; // original005e4a66
    const volatile long double extended_068 =
        extended_067 * static_cast<long double>(extended_020);               // original005e4a68
    float_at(general_002 + uint32_t(12)) = static_cast<float>(extended_068); // original005e4a6a
    return reinterpret_cast<void*>(general_002);
}

extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_005e4980(void*, const void*, const void*, const void*, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e4980\n\taddl $4,%esp\n\tretl $24");
}
