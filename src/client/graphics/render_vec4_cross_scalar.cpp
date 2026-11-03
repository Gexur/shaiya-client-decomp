#include "graphics/render_vec4_cross_scalar.h"
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
} // namespace
extern "C" void* recovered_005e474a(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments);
    volatile float private_0, private_1, private_2, private_3, private_4, private_5, private_6;
    const u32 third = word(slots + 12); // original005e4752
    const u32 second = word(slots + 8); // original005e4755
    const volatile long double extended_000 =
        static_cast<long double>(f32(third + 12)); // original005e4758
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(f32(second + 8)); // original005e475b
    const u32 first = word(slots + 4);                            // original005e475e
    const volatile long double extended_002 =
        static_cast<long double>(f32(second + 12)); // original005e4761
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(f32(third + 8)); // original005e4765
    const volatile long double extended_004 =
        static_cast<long double>(f32(third + 12)); // original005e4769
    const volatile long double extended_005 =
        extended_004 * static_cast<long double>(f32(second + 4)); // original005e476c
    const volatile long double extended_006 =
        static_cast<long double>(f32(second + 12)); // original005e476f
    const volatile long double extended_007 =
        extended_006 * static_cast<long double>(f32(third + 4));           // original005e4772
    const volatile long double extended_008 = extended_005 - extended_007; // original005e4775
    f32(slots + 8) = static_cast<float>(extended_008);                     // original005e4777
    const volatile long double extended_009 =
        static_cast<long double>(f32(second + 4)); // original005e477a
    const volatile long double extended_010 =
        extended_009 * static_cast<long double>(f32(third + 8)); // original005e477d
    private_5 = static_cast<float>(extended_010);                // original005e4780
    const volatile long double extended_011 =
        static_cast<long double>(f32(second + 8)); // original005e4783
    const volatile long double extended_012 =
        extended_011 * static_cast<long double>(f32(third + 4)); // original005e4786
    private_6 = static_cast<float>(extended_012);                // original005e4789
    const volatile long double extended_013 =
        static_cast<long double>(extended_001); // original005e478c
    const volatile long double extended_014 =
        extended_013 - static_cast<long double>(extended_003); // original005e478e
    const volatile long double extended_015 =
        extended_014 * static_cast<long double>(f32(first + 4)); // original005e4790
    const volatile long double extended_016 =
        static_cast<long double>(f32(slots + 8)); // original005e4793
    const volatile long double extended_017 =
        extended_016 * static_cast<long double>(f32(first + 8));           // original005e4796
    const volatile long double extended_018 = extended_015 - extended_017; // original005e4799
    const volatile long double extended_019 =
        static_cast<long double>(private_5); // original005e479b
    const volatile long double extended_020 =
        extended_019 - static_cast<long double>(private_6); // original005e479e
    const volatile long double extended_021 =
        extended_020 * static_cast<long double>(f32(first + 12));          // original005e47a1
    const volatile long double extended_022 = extended_018 + extended_021; // original005e47a4
    private_0 = static_cast<float>(extended_022);                          // original005e47a6
    const volatile long double extended_023 =
        static_cast<long double>(f32(second + 12)); // original005e47a9
    const volatile long double extended_024 =
        extended_023 * static_cast<long double>(f32(third + 0)); // original005e47ac
    f32(slots + 4) = static_cast<float>(extended_024);           // original005e47ae
    const volatile long double extended_025 =
        static_cast<long double>(f32(third + 12)); // original005e47b1
    const volatile long double extended_026 =
        extended_025 * static_cast<long double>(f32(second + 0)); // original005e47b4
    f32(slots + 12) = static_cast<float>(extended_026);           // original005e47b6
    const volatile long double extended_027 =
        static_cast<long double>(f32(third + 0)); // original005e47b9
    const volatile long double extended_028 =
        extended_027 * static_cast<long double>(f32(second + 8)); // original005e47bb
    const volatile long double extended_029 =
        static_cast<long double>(f32(second + 0)); // original005e47be
    const volatile long double extended_030 =
        extended_029 * static_cast<long double>(f32(third + 8));           // original005e47c0
    const volatile long double extended_031 = extended_028 - extended_030; // original005e47c3
    private_4 = static_cast<float>(extended_031);                          // original005e47c5
    const volatile long double extended_032 =
        extended_003 - static_cast<long double>(extended_001); // original005e47c8
    const volatile long double extended_033 =
        extended_032 * static_cast<long double>(f32(first + 0)); // original005e47ca
    const volatile long double extended_034 =
        static_cast<long double>(f32(slots + 4)); // original005e47cc
    const volatile long double extended_035 =
        extended_034 - static_cast<long double>(f32(slots + 12)); // original005e47cf
    const volatile long double extended_036 =
        extended_035 * static_cast<long double>(f32(first + 8));           // original005e47d2
    const volatile long double extended_037 = extended_033 - extended_036; // original005e47d5
    const volatile long double extended_038 =
        static_cast<long double>(private_4); // original005e47d7
    const volatile long double extended_039 =
        extended_038 * static_cast<long double>(f32(first + 12));          // original005e47da
    const volatile long double extended_040 = extended_037 + extended_039; // original005e47dd
    private_1 = static_cast<float>(extended_040);                          // original005e47df
    const volatile long double extended_041 =
        static_cast<long double>(f32(second + 0)); // original005e47e4
    const volatile long double extended_042 =
        extended_041 * static_cast<long double>(f32(third + 4)); // original005e47e6
    const volatile long double extended_043 =
        static_cast<long double>(f32(third + 0)); // original005e47e9
    const volatile long double extended_044 =
        extended_043 * static_cast<long double>(f32(second + 4)); // original005e47eb
    const volatile long double extended_045 =
        static_cast<long double>(f32(slots + 8)); // original005e47ee
    const volatile long double extended_046 =
        extended_045 * static_cast<long double>(f32(first + 0)); // original005e47f1
    const volatile long double extended_047 =
        static_cast<long double>(f32(slots + 12)); // original005e47f3
    const volatile long double extended_048 =
        extended_047 - static_cast<long double>(f32(slots + 4)); // original005e47f6
    const volatile long double extended_049 =
        extended_048 * static_cast<long double>(f32(first + 4));           // original005e47f9
    const volatile long double extended_050 = extended_046 - extended_049; // original005e47fc
    const volatile long double extended_051 =
        static_cast<long double>(extended_042); // original005e47fe
    const volatile long double extended_052 =
        extended_051 - static_cast<long double>(extended_044); // original005e4800
    const volatile long double extended_053 =
        extended_052 * static_cast<long double>(f32(first + 12));          // original005e4802
    const volatile long double extended_054 = extended_050 + extended_053; // original005e4805
    private_2 = static_cast<float>(extended_054);                          // original005e4807
    const volatile long double extended_055 =
        static_cast<long double>(private_6); // original005e480a
    const volatile long double extended_056 =
        extended_055 - static_cast<long double>(private_5); // original005e480d
    const volatile long double extended_057 =
        extended_056 * static_cast<long double>(f32(first + 0)); // original005e4810
    const volatile long double extended_058 =
        static_cast<long double>(private_4); // original005e4812
    const volatile long double extended_059 =
        extended_058 * static_cast<long double>(f32(first + 4));           // original005e4815
    const u32 output = word(slots);                                        // original005e4818
    const volatile long double extended_060 = extended_057 - extended_059; // original005e4820
    const volatile long double extended_061 =
        static_cast<long double>(extended_044); // original005e4822
    const volatile long double extended_062 =
        extended_061 - static_cast<long double>(extended_042); // original005e4824
    const volatile long double extended_063 =
        extended_062 * static_cast<long double>(f32(first + 8));           // original005e4826
    const volatile long double extended_064 = extended_060 + extended_063; // original005e4829
    private_3 = static_cast<float>(extended_064);                          // original005e482b
    put(output + 0, word(reinterpret_cast<u32>(&private_0)));              // original005e482e
    put(output + 4, word(reinterpret_cast<u32>(&private_1)));              // original005e482f
    put(output + 8, word(reinterpret_cast<u32>(&private_2)));              // original005e4834
    put(output + 12, word(reinterpret_cast<u32>(&private_3)));             // original005e4835
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e474a(void*, const void*, const void*,
                                                              const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e474a\n\taddl $4,%esp\n\tretl $16");
}
