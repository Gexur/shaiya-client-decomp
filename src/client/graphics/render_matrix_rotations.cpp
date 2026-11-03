#include "graphics/render_matrix_rotations.h"
#include "graphics/render_dispatch.h"
#include "graphics/render_quaternion_angles_dispatch.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
void put(u32 p, u32 v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
struct __attribute__((packed, may_alias)) FloatWord {
    float value;
};
volatile float& f32(u32 p) {
    return reinterpret_cast<volatile FloatWord*>(p)->value;
}
void trig(u32 angle, u32 cosine, u32 sine) {
    __asm__ volatile("flds (%0)\n\tfsincos\n\tfstps (%1)\n\tfstps (%2)" ::"r"(angle), "r"(cosine),
                     "r"(sine)
                     : "st", "st(1)", "memory");
}
} // namespace
// Complete original005e59c5..005e5ac6.
extern "C" void* recovered_005e59c5(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments);
    volatile float cosine, sine;
    u32 axis[3];
    trig(slots + 8, reinterpret_cast<u32>(&cosine),
         reinterpret_cast<u32>(&sine));             // original59e1..59e8
    const volatile long double extended_000 = 1.0L; // original005e59ea
    const u32 input = word(slots + 4);              // original005e59ec
    const volatile long double extended_001 =
        extended_000 - static_cast<long double>(cosine);   // original005e59ef
    put(reinterpret_cast<u32>(&axis[0]), word(input + 0)); // original005e59f5
    f32(slots + 8) = static_cast<float>(extended_001);     // original005e59f9
    put(reinterpret_cast<u32>(&axis[1]), word(input + 4)); // original005e59fc
    put(reinterpret_cast<u32>(&axis[2]), word(input + 8)); // original005e59ff
    FUN_005e40eb(reinterpret_cast<float*>(axis),
                 reinterpret_cast<const float*>(axis)); // original005e5a00
    const u32 output = word(slots);                     // original005e5a05
    const volatile long double extended_002 =
        static_cast<long double>(f32(slots + 8)); // original005e5a08
    const volatile long double extended_003 =
        static_cast<long double>(f32(reinterpret_cast<u32>(axis) + 4)); // original005e5a0b
    const volatile long double extended_004 =
        extended_003 *
        static_cast<long double>(f32(reinterpret_cast<u32>(axis) + 0)); // original005e5a0e
    const volatile long double extended_005 =
        extended_004 * static_cast<long double>(extended_002); // original005e5a11
    f32(slots + 8) = static_cast<float>(extended_005);         // original005e5a13
    const volatile long double extended_006 =
        static_cast<long double>(f32(reinterpret_cast<u32>(axis) + 8)); // original005e5a16
    const volatile long double extended_007 =
        static_cast<long double>(f32(reinterpret_cast<u32>(axis) + 4)); // original005e5a19
    const volatile long double extended_008 =
        extended_007 * static_cast<long double>(extended_006); // original005e5a1c
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(extended_002); // original005e5a1e
    const volatile long double extended_010 =
        static_cast<long double>(extended_006); // original005e5a20
    const volatile long double extended_011 =
        extended_010 *
        static_cast<long double>(f32(reinterpret_cast<u32>(axis) + 0)); // original005e5a22
    const volatile long double extended_012 =
        extended_011 * static_cast<long double>(extended_002); // original005e5a25
    const volatile long double extended_013 =
        static_cast<long double>(f32(reinterpret_cast<u32>(axis) + 0)); // original005e5a27
    const volatile long double extended_014 =
        extended_013 *
        static_cast<long double>(f32(reinterpret_cast<u32>(axis) + 0)); // original005e5a2a
    const volatile long double extended_015 =
        extended_014 * static_cast<long double>(extended_002); // original005e5a2d
    const volatile long double extended_016 =
        extended_015 + static_cast<long double>(cosine); // original005e5a2f
    f32(output + 0) = static_cast<float>(extended_016);  // original005e5a32
    const volatile long double extended_017 =
        static_cast<long double>(extended_006); // original005e5a34
    const volatile long double extended_018 =
        extended_017 * static_cast<long double>(sine); // original005e5a36
    const volatile long double extended_019 =
        static_cast<long double>(f32(slots + 8)); // original005e5a39
    const volatile long double extended_020 =
        extended_019 + static_cast<long double>(extended_018); // original005e5a3c
    f32(output + 4) = static_cast<float>(extended_020);        // original005e5a3e
    const volatile long double extended_021 =
        static_cast<long double>(f32(reinterpret_cast<u32>(axis) + 4)); // original005e5a41
    const volatile long double extended_022 =
        extended_021 * static_cast<long double>(sine); // original005e5a44
    f32(slots + 4) = static_cast<float>(extended_022); // original005e5a47
    const volatile long double extended_023 =
        static_cast<long double>(extended_012); // original005e5a4a
    const volatile long double extended_024 =
        extended_023 - static_cast<long double>(extended_022); // original005e5a4c
    f32(output + 8) = static_cast<float>(extended_024);        // original005e5a4e
    const volatile long double extended_025 = 0.0L;            // original005e5a53
    f32(output + 12) = static_cast<float>(extended_025);       // original005e5a55
    const volatile long double extended_026 =
        static_cast<long double>(f32(slots + 8)); // original005e5a58
    const volatile long double extended_027 =
        extended_026 - static_cast<long double>(extended_018); // original005e5a5b
    f32(output + 16) = static_cast<float>(extended_027);       // original005e5a5d
    const volatile long double extended_028 =
        static_cast<long double>(f32(reinterpret_cast<u32>(axis) + 4)); // original005e5a62
    const volatile long double extended_029 =
        extended_028 *
        static_cast<long double>(f32(reinterpret_cast<u32>(axis) + 4)); // original005e5a65
    const volatile long double extended_030 =
        extended_029 * static_cast<long double>(extended_002); // original005e5a68
    const volatile long double extended_031 =
        extended_030 + static_cast<long double>(cosine); // original005e5a6a
    f32(output + 20) = static_cast<float>(extended_031); // original005e5a6d
    const volatile long double extended_032 =
        static_cast<long double>(f32(reinterpret_cast<u32>(axis) + 0)); // original005e5a70
    const volatile long double extended_033 =
        extended_032 * static_cast<long double>(sine); // original005e5a73
    const volatile long double extended_034 =
        static_cast<long double>(extended_033); // original005e5a76
    const volatile long double extended_035 =
        extended_034 + static_cast<long double>(extended_009); // original005e5a78
    f32(output + 24) = static_cast<float>(extended_035);       // original005e5a7a
    const volatile long double extended_036 = 0.0L;            // original005e5a7d
    f32(output + 28) = static_cast<float>(extended_036);       // original005e5a7f
    const volatile long double extended_037 =
        static_cast<long double>(f32(slots + 4)); // original005e5a82
    const volatile long double extended_038 =
        extended_037 + static_cast<long double>(extended_012); // original005e5a85
    f32(output + 32) = static_cast<float>(extended_038);       // original005e5a87
    const volatile long double extended_039 =
        static_cast<long double>(extended_009); // original005e5a8a
    const volatile long double extended_040 =
        extended_039 - static_cast<long double>(extended_033); // original005e5a8c
    f32(output + 36) = static_cast<float>(extended_040);       // original005e5a8e
    const volatile long double extended_041 =
        static_cast<long double>(extended_006); // original005e5a97
    const volatile long double extended_042 =
        extended_041 * static_cast<long double>(extended_006); // original005e5a99
    const volatile long double extended_043 =
        extended_042 * static_cast<long double>(extended_002); // original005e5a9b
    const volatile long double extended_044 =
        extended_043 + static_cast<long double>(cosine); // original005e5a9d
    f32(output + 40) = static_cast<float>(extended_044); // original005e5aa0
    const volatile long double extended_045 = 0.0L;      // original005e5aa9
    f32(output + 44) = static_cast<float>(extended_045); // original005e5aab
    const volatile long double extended_046 = 0.0L;      // original005e5aae
    f32(output + 48) = static_cast<float>(extended_046); // original005e5ab0
    const volatile long double extended_047 = 0.0L;      // original005e5ab3
    f32(output + 52) = static_cast<float>(extended_047); // original005e5ab5
    const volatile long double extended_048 = 0.0L;      // original005e5ab8
    f32(output + 56) = static_cast<float>(extended_048); // original005e5aba
    const volatile long double extended_049 = 1.0L;      // original005e5abd
    f32(output + 60) = static_cast<float>(extended_049); // original005e5abf
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e59c5(void*, const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e59c5\n\taddl $4,%esp\n\tretl $12");
}

// Complete original005e5adf..005e5bc3.
extern "C" void* recovered_005e5adf(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments);
    volatile float private_0, private_1, private_2, private_3;
    const u32 input = word(slots + 4);                                        // original005e5ae7
    const volatile long double extended_000 = static_cast<long double>(2.0L); // original005e5aea
    const volatile long double extended_001 =
        static_cast<long double>(f32(input + 0)); // original005e5af0
    const volatile long double extended_002 =
        extended_001 * static_cast<long double>(extended_000); // original005e5af2
    private_0 = static_cast<float>(extended_002);              // original005e5af4
    const volatile long double extended_003 =
        static_cast<long double>(f32(input + 4)); // original005e5af7
    const volatile long double extended_004 =
        extended_003 * static_cast<long double>(extended_000); // original005e5afa
    f32(slots + 4) = static_cast<float>(extended_004);         // original005e5afc
    const volatile long double extended_005 =
        extended_000 * static_cast<long double>(f32(input + 8)); // original005e5aff
    const volatile long double extended_006 =
        static_cast<long double>(private_0); // original005e5b02
    const volatile long double extended_007 =
        extended_006 * static_cast<long double>(f32(input + 12)); // original005e5b05
    const volatile long double extended_008 =
        static_cast<long double>(f32(slots + 4)); // original005e5b08
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(f32(input + 12)); // original005e5b0b
    const volatile long double extended_010 =
        static_cast<long double>(extended_005); // original005e5b0e
    const volatile long double extended_011 =
        extended_010 * static_cast<long double>(f32(input + 12)); // original005e5b10
    const volatile long double extended_012 =
        static_cast<long double>(private_0); // original005e5b13
    const volatile long double extended_013 =
        extended_012 * static_cast<long double>(f32(input + 0)); // original005e5b16
    private_3 = static_cast<float>(extended_013);                // original005e5b18
    const volatile long double extended_014 =
        static_cast<long double>(f32(slots + 4)); // original005e5b1b
    const volatile long double extended_015 =
        extended_014 * static_cast<long double>(f32(input + 0)); // original005e5b1e
    private_0 = static_cast<float>(extended_015);                // original005e5b20
    const volatile long double extended_016 =
        static_cast<long double>(extended_005); // original005e5b23
    const volatile long double extended_017 =
        extended_016 * static_cast<long double>(f32(input + 0)); // original005e5b25
    private_1 = static_cast<float>(extended_017);                // original005e5b27
    const volatile long double extended_018 =
        static_cast<long double>(f32(slots + 4)); // original005e5b2a
    const volatile long double extended_019 =
        extended_018 * static_cast<long double>(f32(input + 4)); // original005e5b2d
    private_2 = static_cast<float>(extended_019);                // original005e5b30
    const volatile long double extended_020 =
        static_cast<long double>(extended_005); // original005e5b33
    const volatile long double extended_021 =
        extended_020 * static_cast<long double>(f32(input + 4)); // original005e5b35
    f32(slots + 4) = static_cast<float>(extended_021);           // original005e5b38
    const volatile long double extended_022 =
        static_cast<long double>(extended_005); // original005e5b3b
    const volatile long double extended_023 =
        extended_022 * static_cast<long double>(f32(input + 8)); // original005e5b3d
    const u32 output = word(slots);                              // original005e5b40
    const volatile long double extended_024 = 1.0L;              // original005e5b43
    const volatile long double extended_025 =
        extended_024 - static_cast<long double>(private_2); // original005e5b45
    const volatile long double extended_026 =
        extended_025 - static_cast<long double>(extended_023); // original005e5b48
    f32(output + 0) = static_cast<float>(extended_026);        // original005e5b4a
    const volatile long double extended_027 =
        static_cast<long double>(private_0); // original005e5b4c
    const volatile long double extended_028 =
        extended_027 + static_cast<long double>(extended_011); // original005e5b4f
    f32(output + 4) = static_cast<float>(extended_028);        // original005e5b51
    const volatile long double extended_029 =
        static_cast<long double>(private_1); // original005e5b54
    const volatile long double extended_030 =
        extended_029 - static_cast<long double>(extended_009); // original005e5b57
    f32(output + 8) = static_cast<float>(extended_030);        // original005e5b59
    const volatile long double extended_031 = 0.0L;            // original005e5b5c
    f32(output + 12) = static_cast<float>(extended_031);       // original005e5b5e
    const volatile long double extended_032 =
        static_cast<long double>(private_0); // original005e5b61
    const volatile long double extended_033 =
        extended_032 - static_cast<long double>(extended_011); // original005e5b64
    f32(output + 16) = static_cast<float>(extended_033);       // original005e5b66
    const volatile long double extended_034 = 1.0L;            // original005e5b69
    const volatile long double extended_035 =
        extended_034 - static_cast<long double>(private_3); // original005e5b6b
    f32(slots + 0) = static_cast<float>(extended_035);      // original005e5b6e
    const volatile long double extended_036 =
        extended_035 - static_cast<long double>(extended_023); // original005e5b71
    f32(output + 20) = static_cast<float>(extended_036);       // original005e5b73
    const volatile long double extended_037 =
        static_cast<long double>(f32(slots + 4)); // original005e5b7a
    const volatile long double extended_038 =
        extended_037 + static_cast<long double>(extended_007); // original005e5b7d
    f32(output + 24) = static_cast<float>(extended_038);       // original005e5b7f
    const volatile long double extended_039 = 0.0L;            // original005e5b82
    f32(output + 28) = static_cast<float>(extended_039);       // original005e5b84
    const volatile long double extended_040 =
        static_cast<long double>(private_1); // original005e5b87
    const volatile long double extended_041 =
        extended_040 + static_cast<long double>(extended_009); // original005e5b8a
    f32(output + 32) = static_cast<float>(extended_041);       // original005e5b8c
    const volatile long double extended_042 =
        static_cast<long double>(f32(slots + 4)); // original005e5b91
    const volatile long double extended_043 =
        extended_042 - static_cast<long double>(extended_007); // original005e5b94
    f32(output + 36) = static_cast<float>(extended_043);       // original005e5b96
    const volatile long double extended_044 =
        static_cast<long double>(f32(slots + 0)); // original005e5b9d
    const volatile long double extended_045 =
        extended_044 - static_cast<long double>(private_2); // original005e5ba0
    f32(output + 40) = static_cast<float>(extended_045);    // original005e5ba3
    const volatile long double extended_046 = 0.0L;         // original005e5ba6
    f32(output + 44) = static_cast<float>(extended_046);    // original005e5ba8
    const volatile long double extended_047 = 0.0L;         // original005e5bab
    f32(output + 48) = static_cast<float>(extended_047);    // original005e5bad
    const volatile long double extended_048 = 0.0L;         // original005e5bb0
    f32(output + 52) = static_cast<float>(extended_048);    // original005e5bb2
    const volatile long double extended_049 = 0.0L;         // original005e5bb5
    f32(output + 56) = static_cast<float>(extended_049);    // original005e5bb7
    const volatile long double extended_050 = 1.0L;         // original005e5bba
    f32(output + 60) = static_cast<float>(extended_050);    // original005e5bbc
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e5adf(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e5adf\n\taddl $4,%esp\n\tretl $8");
}

// Complete original5e85a2..5e85dd.
extern "C" void* recovered_005e85a2(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments);
    volatile float angles[3];
    float quaternion[4];
    f32(reinterpret_cast<u32>(angles) + 8) = f32(slots + 12); // 85aa..85b0
    f32(reinterpret_cast<u32>(angles) + 4) = f32(slots + 8);  // 85b7..85ba
    f32(reinterpret_cast<u32>(angles)) = f32(slots + 4);      // 85be..85c1
    FUN_005e6970(quaternion, word(reinterpret_cast<u32>(angles)),
                 word(reinterpret_cast<u32>(angles) + 4), word(reinterpret_cast<u32>(angles) + 8));
    const u32 matrix_output = word(slots); // actual85ce read
    FUN_005e5ad9(reinterpret_cast<void*>(matrix_output), quaternion);
    return reinterpret_cast<void*>(word(slots)); // fresh85d6 return
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e85a2(void*, u32, u32, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e85a2\n\taddl $4,%esp\n\tretl $16");
}
