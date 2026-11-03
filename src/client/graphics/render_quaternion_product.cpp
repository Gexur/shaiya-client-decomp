#include "graphics/render_quaternion_product.h"
namespace {
inline uint32_t word_at(uint32_t p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
inline volatile float& float_at(uint32_t p) {
    return *reinterpret_cast<volatile float*>(p);
}
} // namespace
extern "C" void* recovered_005e6a6a(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    const uint32_t general_000 = word_at(slots + 8); // original005e6a6f
    const uint32_t general_001 = word_at(slots + 4); // original005e6a72
    const uint32_t general_002 = word_at(slots + 0); // original005e6a75
    const volatile long double extended_000 =
        static_cast<long double>(float_at(general_000 + 12)); // original005e6a78
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(float_at(general_001 + 0)); // original005e6a7b
    const volatile long double extended_002 =
        static_cast<long double>(float_at(general_000 + 12)); // original005e6a7d
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(float_at(general_001 + 8)); // original005e6a80
    const volatile long double extended_004 =
        static_cast<long double>(float_at(general_000 + 12)); // original005e6a83
    const volatile long double extended_005 =
        extended_004 * static_cast<long double>(float_at(general_001 + 4)); // original005e6a86
    const volatile long double extended_006 =
        static_cast<long double>(float_at(general_000 + 12)); // original005e6a89
    const volatile long double extended_007 =
        extended_006 * static_cast<long double>(float_at(general_001 + 12)); // original005e6a8c
    const volatile long double extended_008 =
        static_cast<long double>(float_at(general_000 + 0)); // original005e6a91
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(float_at(general_001 + 12)); // original005e6a93
    const volatile long double extended_010 =
        static_cast<long double>(float_at(general_000 + 0)); // original005e6a96
    const volatile long double extended_011 =
        extended_010 * static_cast<long double>(float_at(general_001 + 4)); // original005e6a98
    const volatile long double extended_012 =
        static_cast<long double>(float_at(general_000 + 0)); // original005e6a9b
    const volatile long double extended_013 =
        extended_012 * static_cast<long double>(float_at(general_001 + 8)); // original005e6a9d
    const volatile long double extended_014 =
        static_cast<long double>(float_at(general_000 + 0)); // original005e6aa0
    const volatile long double extended_015 =
        extended_014 * static_cast<long double>(float_at(general_001 + 0)); // original005e6aa2
    const volatile long double extended_016 = extended_001 + extended_009;  // original005e6aa6
    const volatile long double extended_017 = extended_005 - extended_013;  // original005e6aa8
    const volatile long double extended_018 = extended_003 + extended_011;  // original005e6aaa
    const volatile long double extended_019 = extended_007 - extended_015;  // original005e6aac
    const volatile long double extended_020 =
        static_cast<long double>(float_at(general_000 + 4)); // original005e6aae
    const volatile long double extended_021 =
        extended_020 * static_cast<long double>(float_at(general_001 + 8)); // original005e6ab1
    const volatile long double extended_022 =
        static_cast<long double>(float_at(general_000 + 4)); // original005e6ab4
    const volatile long double extended_023 =
        extended_022 * static_cast<long double>(float_at(general_001 + 0)); // original005e6ab7
    const volatile long double extended_024 =
        static_cast<long double>(float_at(general_000 + 4)); // original005e6ab9
    const volatile long double extended_025 =
        extended_024 * static_cast<long double>(float_at(general_001 + 12)); // original005e6abc
    const volatile long double extended_026 =
        static_cast<long double>(float_at(general_000 + 4)); // original005e6abf
    const volatile long double extended_027 =
        extended_026 * static_cast<long double>(float_at(general_001 + 4)); // original005e6ac2
    const volatile long double extended_028 = extended_016 + extended_021;  // original005e6ac7
    const volatile long double extended_029 = extended_017 + extended_025;  // original005e6ac9
    const volatile long double extended_030 = extended_018 - extended_023;  // original005e6acb
    const volatile long double extended_031 = extended_019 - extended_027;  // original005e6acd
    const volatile long double extended_032 =
        static_cast<long double>(float_at(general_000 + 8)); // original005e6acf
    const volatile long double extended_033 =
        extended_032 * static_cast<long double>(float_at(general_001 + 4)); // original005e6ad2
    const volatile long double extended_034 =
        static_cast<long double>(float_at(general_000 + 8)); // original005e6ad5
    const volatile long double extended_035 =
        extended_034 * static_cast<long double>(float_at(general_001 + 12)); // original005e6ad8
    const volatile long double extended_036 =
        static_cast<long double>(float_at(general_000 + 8)); // original005e6adb
    const volatile long double extended_037 =
        extended_036 * static_cast<long double>(float_at(general_001 + 0)); // original005e6ade
    const volatile long double extended_038 =
        static_cast<long double>(float_at(general_000 + 8)); // original005e6ae0
    const volatile long double extended_039 =
        extended_038 * static_cast<long double>(float_at(general_001 + 8)); // original005e6ae3
    const volatile long double extended_040 = extended_028 - extended_033;  // original005e6ae8
    const volatile long double extended_041 = extended_029 + extended_037;  // original005e6aea
    const volatile long double extended_042 = extended_030 + extended_035;  // original005e6aec
    const volatile long double extended_043 = extended_031 - extended_039;  // original005e6aee
    float_at(general_002 + 0) = static_cast<float>(extended_040);           // original005e6af0
    float_at(general_002 + 4) = static_cast<float>(extended_041);           // original005e6af2
    float_at(general_002 + 8) = static_cast<float>(extended_042);           // original005e6af5
    float_at(general_002 + 12) = static_cast<float>(extended_043);          // original005e6af8
    const uint32_t general_003 = word_at(slots + 0);                        // original005e6afb
    return reinterpret_cast<void*>(general_003);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6a6a(void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e6a6a\n\taddl $4,%esp\n\tretl $12");
}
