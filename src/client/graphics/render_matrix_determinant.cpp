#include "graphics/render_matrix_determinant.h"
namespace {
struct __attribute__((packed, may_alias)) FloatWord {
    float value;
};
inline volatile float& float_at(uint32_t p) {
    return reinterpret_cast<volatile FloatWord*>(p)->value;
}
} // namespace
extern "C" long double recovered_005e4cc6(uint32_t slots, uint32_t matrix) {
    const volatile long double extended_000 =
        static_cast<long double>(float_at(matrix + 40)); // original005e4cce
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(float_at(matrix + 60)); // original005e4cd1
    const volatile long double extended_002 =
        static_cast<long double>(float_at(matrix + 56)); // original005e4cd4
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(float_at(matrix + 44));    // original005e4cd7
    const volatile long double extended_004 = extended_001 - extended_003; // original005e4cda
    const volatile long double extended_005 =
        static_cast<long double>(float_at(matrix + 60)); // original005e4cdc
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(float_at(matrix + 36)); // original005e4cdf
    const volatile long double extended_007 =
        static_cast<long double>(float_at(matrix + 52)); // original005e4ce2
    const volatile long double extended_008 =
        extended_007 * static_cast<long double>(float_at(matrix + 44));    // original005e4ce5
    const volatile long double extended_009 = extended_006 - extended_008; // original005e4ce8
    const volatile long double extended_010 =
        static_cast<long double>(float_at(matrix + 56)); // original005e4cea
    const volatile long double extended_011 =
        extended_010 * static_cast<long double>(float_at(matrix + 36)); // original005e4ced
    const volatile long double extended_012 =
        static_cast<long double>(float_at(matrix + 40)); // original005e4cf0
    const volatile long double extended_013 =
        extended_012 * static_cast<long double>(float_at(matrix + 52));    // original005e4cf3
    const volatile long double extended_014 = extended_011 - extended_013; // original005e4cf6
    const volatile long double extended_015 =
        static_cast<long double>(float_at(matrix + 32)); // original005e4cf8
    const volatile long double extended_016 =
        extended_015 * static_cast<long double>(float_at(matrix + 60)); // original005e4cfb
    const volatile long double extended_017 =
        static_cast<long double>(float_at(matrix + 48)); // original005e4cfe
    const volatile long double extended_018 =
        extended_017 * static_cast<long double>(float_at(matrix + 44));    // original005e4d01
    const volatile long double extended_019 = extended_016 - extended_018; // original005e4d04
    const volatile long double extended_020 =
        static_cast<long double>(float_at(matrix + 56)); // original005e4d06
    const volatile long double extended_021 =
        extended_020 * static_cast<long double>(float_at(matrix + 32)); // original005e4d09
    const volatile long double extended_022 =
        static_cast<long double>(float_at(matrix + 48)); // original005e4d0c
    const volatile long double extended_023 =
        extended_022 * static_cast<long double>(float_at(matrix + 40));    // original005e4d0f
    const volatile long double extended_024 = extended_021 - extended_023; // original005e4d12
    const volatile long double extended_025 =
        static_cast<long double>(float_at(matrix + 32)); // original005e4d14
    const volatile long double extended_026 =
        extended_025 * static_cast<long double>(float_at(matrix + 52)); // original005e4d17
    const volatile long double extended_027 =
        static_cast<long double>(float_at(matrix + 48)); // original005e4d1a
    const volatile long double extended_028 =
        extended_027 * static_cast<long double>(float_at(matrix + 36));    // original005e4d1d
    const volatile long double extended_029 = extended_026 - extended_028; // original005e4d20
    float_at(slots) = static_cast<float>(extended_029);                    // original005e4d22
    const volatile long double extended_030 =
        static_cast<long double>(extended_004); // original005e4d25
    const volatile long double extended_031 =
        extended_030 * static_cast<long double>(float_at(matrix + 20)); // original005e4d27
    const volatile long double extended_032 =
        static_cast<long double>(extended_009); // original005e4d2a
    const volatile long double extended_033 =
        extended_032 * static_cast<long double>(float_at(matrix + 24));    // original005e4d2c
    const volatile long double extended_034 = extended_031 - extended_033; // original005e4d2f
    const volatile long double extended_035 =
        static_cast<long double>(extended_014); // original005e4d31
    const volatile long double extended_036 =
        extended_035 * static_cast<long double>(float_at(matrix + 28));    // original005e4d33
    const volatile long double extended_037 = extended_034 + extended_036; // original005e4d36
    const volatile long double extended_038 =
        extended_037 * static_cast<long double>(float_at(matrix + 0)); // original005e4d38
    const volatile long double extended_039 =
        static_cast<long double>(extended_004); // original005e4d3a
    const volatile long double extended_040 =
        extended_039 * static_cast<long double>(float_at(matrix + 16)); // original005e4d3c
    const volatile long double extended_041 =
        static_cast<long double>(extended_019); // original005e4d3f
    const volatile long double extended_042 =
        extended_041 * static_cast<long double>(float_at(matrix + 24));    // original005e4d41
    const volatile long double extended_043 = extended_040 - extended_042; // original005e4d44
    const volatile long double extended_044 =
        static_cast<long double>(extended_024); // original005e4d46
    const volatile long double extended_045 =
        extended_044 * static_cast<long double>(float_at(matrix + 28));    // original005e4d48
    const volatile long double extended_046 = extended_043 + extended_045; // original005e4d4b
    const volatile long double extended_047 =
        extended_046 * static_cast<long double>(float_at(matrix + 4));     // original005e4d4d
    const volatile long double extended_048 = extended_038 - extended_047; // original005e4d50
    const volatile long double extended_049 =
        static_cast<long double>(extended_009); // original005e4d52
    const volatile long double extended_050 =
        extended_049 * static_cast<long double>(float_at(matrix + 16)); // original005e4d54
    const volatile long double extended_051 =
        static_cast<long double>(extended_019); // original005e4d57
    const volatile long double extended_052 =
        extended_051 * static_cast<long double>(float_at(matrix + 20));    // original005e4d59
    const volatile long double extended_053 = extended_050 - extended_052; // original005e4d5c
    const volatile long double extended_054 =
        static_cast<long double>(float_at(slots)); // original005e4d5e
    const volatile long double extended_055 =
        extended_054 * static_cast<long double>(float_at(matrix + 28));    // original005e4d61
    const volatile long double extended_056 = extended_053 + extended_055; // original005e4d64
    const volatile long double extended_057 =
        extended_056 * static_cast<long double>(float_at(matrix + 8));     // original005e4d66
    const volatile long double extended_058 = extended_048 + extended_057; // original005e4d69
    const volatile long double extended_059 =
        static_cast<long double>(extended_014); // original005e4d6b
    const volatile long double extended_060 =
        extended_059 * static_cast<long double>(float_at(matrix + 16)); // original005e4d6d
    const volatile long double extended_061 =
        static_cast<long double>(extended_024); // original005e4d70
    const volatile long double extended_062 =
        extended_061 * static_cast<long double>(float_at(matrix + 20));    // original005e4d72
    const volatile long double extended_063 = extended_060 - extended_062; // original005e4d75
    const volatile long double extended_064 =
        static_cast<long double>(float_at(slots)); // original005e4d77
    const volatile long double extended_065 =
        extended_064 * static_cast<long double>(float_at(matrix + 24));    // original005e4d7a
    const volatile long double extended_066 = extended_063 + extended_065; // original005e4d7d
    const volatile long double extended_067 =
        extended_066 * static_cast<long double>(float_at(matrix + 12));    // original005e4d7f
    const volatile long double extended_068 = extended_058 - extended_067; // original005e4d82
    return extended_068;
}
extern "C" __attribute__((naked, stdcall)) float FUN_005e4cc6(const void*) {
    __asm__ volatile(
        "pushfl\n\tpushl %ecx\n\tpushl %edx\n\tmovl 16(%esp),%eax\n\tleal 16(%esp),%ecx\n\tpushl %eax\n\tpushl %eax\n\tpushl %ecx\n\tcalll _recovered_005e4cc6\n\taddl $8,%esp\n\tpopl %eax\n\tpopl %edx\n\tpopl %ecx\n\tpopfl\n\tretl $4");
}
