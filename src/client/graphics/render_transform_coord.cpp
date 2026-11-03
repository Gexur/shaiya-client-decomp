#include "graphics/render_transform_coord.h"
#include "graphics/render_vector.h"
namespace {
inline uint32_t word(uint32_t p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
struct __attribute__((packed, may_alias)) FloatWord {
    float value;
};
inline volatile float& f32(uint32_t p) {
    return reinterpret_cast<volatile FloatWord*>(p)->value;
}
} // namespace
extern "C" void* recovered_005e77b5(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    const uint32_t input = word(slots + 4);
    const uint32_t matrix = word(slots + 8);
    uint32_t output = word(slots);
    volatile float private_w, call_w, call_one;
    const volatile long double extended_000 =
        static_cast<long double>(f32(input + 0)); // original005e77c4
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(f32(matrix + 0)); // original005e77c6
    const volatile long double extended_002 =
        static_cast<long double>(f32(input + 0)); // original005e77c8
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(f32(matrix + 4)); // original005e77ca
    const volatile long double extended_004 =
        static_cast<long double>(f32(input + 0)); // original005e77cd
    const volatile long double extended_005 =
        extended_004 * static_cast<long double>(f32(matrix + 12)); // original005e77cf
    const volatile long double extended_006 =
        static_cast<long double>(f32(input + 4)); // original005e77d4
    const volatile long double extended_007 =
        extended_006 * static_cast<long double>(f32(matrix + 16)); // original005e77d7
    const volatile long double extended_008 =
        static_cast<long double>(f32(input + 4)); // original005e77da
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(f32(matrix + 20)); // original005e77dd
    const volatile long double extended_010 =
        static_cast<long double>(f32(input + 4)); // original005e77e0
    const volatile long double extended_011 =
        extended_010 * static_cast<long double>(f32(matrix + 28));         // original005e77e3
    const volatile long double extended_012 = extended_001 + extended_007; // original005e77e8
    const volatile long double extended_013 = extended_003 + extended_009; // original005e77ea
    const volatile long double extended_014 = extended_005 + extended_011; // original005e77ec
    const volatile long double extended_015 =
        static_cast<long double>(f32(matrix + 48));                        // original005e77ee
    const volatile long double extended_016 = extended_012 + extended_015; // original005e77f1
    const volatile long double extended_017 =
        static_cast<long double>(f32(matrix + 52));                        // original005e77f3
    const volatile long double extended_018 = extended_013 + extended_017; // original005e77f6
    const volatile long double extended_019 =
        static_cast<long double>(f32(matrix + 60));                        // original005e77f8
    const volatile long double extended_020 = extended_014 + extended_019; // original005e77fb
    f32(output + 0) = static_cast<float>(extended_016);                    // original005e77fd
    f32(output + 4) = static_cast<float>(extended_018);                    // original005e77ff
    private_w = static_cast<float>(extended_020);                          // original005e7802
    const volatile long double extended_021 = 1.0L;                        // original005e7805
    call_one = static_cast<float>(extended_021);                           // original005e7809
    const volatile long double extended_022 =
        static_cast<long double>(private_w);                 // original005e780d
    call_w = static_cast<float>(extended_022);               // original005e7810
    const int32_t near_one = FUN_005e3be9(call_w, call_one); // original005e7813
    output = word(slots);                                    // original005e781a
    if (!near_one) {                                         // original005e781d
        const volatile long double extended_023 = 1.0L;      // original005e781f
        const volatile long double extended_024 =
            extended_023 / static_cast<long double>(private_w); // original005e7821
        const volatile long double extended_025 =
            static_cast<long double>(extended_024); // original005e7824
        const volatile long double extended_026 =
            extended_025 * static_cast<long double>(f32(output + 0)); // original005e7826
        f32(output + 0) = static_cast<float>(extended_026);           // original005e7828
        const volatile long double extended_027 =
            extended_024 * static_cast<long double>(f32(output + 4)); // original005e782a
        f32(output + 4) = static_cast<float>(extended_027);           // original005e782d
    } // original005e7830
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e77b5(void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e77b5\n\taddl $4,%esp\n\tretl $12");
}

extern "C" void* recovered_005e796d(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    const uint32_t input = word(slots + 4);
    const uint32_t matrix = word(slots + 8);
    uint32_t output = word(slots);
    volatile float private_w, call_w, call_one;
    const volatile long double extended_000 =
        static_cast<long double>(f32(input + 0)); // original005e797c
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(f32(matrix + 0)); // original005e797e
    const volatile long double extended_002 =
        static_cast<long double>(f32(input + 0)); // original005e7980
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(f32(matrix + 8)); // original005e7982
    const volatile long double extended_004 =
        static_cast<long double>(f32(input + 0)); // original005e7985
    const volatile long double extended_005 =
        extended_004 * static_cast<long double>(f32(matrix + 4)); // original005e7987
    const volatile long double extended_006 =
        static_cast<long double>(f32(input + 0)); // original005e798a
    const volatile long double extended_007 =
        extended_006 * static_cast<long double>(f32(matrix + 12)); // original005e798c
    const volatile long double extended_008 =
        static_cast<long double>(f32(input + 4)); // original005e7991
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(f32(matrix + 16)); // original005e7994
    const volatile long double extended_010 =
        static_cast<long double>(f32(input + 4)); // original005e7997
    const volatile long double extended_011 =
        extended_010 * static_cast<long double>(f32(matrix + 24)); // original005e799a
    const volatile long double extended_012 =
        static_cast<long double>(f32(input + 4)); // original005e799d
    const volatile long double extended_013 =
        extended_012 * static_cast<long double>(f32(matrix + 20)); // original005e79a0
    const volatile long double extended_014 =
        static_cast<long double>(f32(input + 4)); // original005e79a3
    const volatile long double extended_015 =
        extended_014 * static_cast<long double>(f32(matrix + 28));         // original005e79a6
    const volatile long double extended_016 = extended_001 + extended_009; // original005e79ab
    const volatile long double extended_017 = extended_005 + extended_013; // original005e79ad
    const volatile long double extended_018 = extended_003 + extended_011; // original005e79af
    const volatile long double extended_019 = extended_007 + extended_015; // original005e79b1
    const volatile long double extended_020 =
        static_cast<long double>(f32(input + 8)); // original005e79b3
    const volatile long double extended_021 =
        extended_020 * static_cast<long double>(f32(matrix + 32)); // original005e79b6
    const volatile long double extended_022 =
        static_cast<long double>(f32(input + 8)); // original005e79b9
    const volatile long double extended_023 =
        extended_022 * static_cast<long double>(f32(matrix + 40)); // original005e79bc
    const volatile long double extended_024 =
        static_cast<long double>(f32(input + 8)); // original005e79bf
    const volatile long double extended_025 =
        extended_024 * static_cast<long double>(f32(matrix + 36)); // original005e79c2
    const volatile long double extended_026 =
        static_cast<long double>(f32(input + 8)); // original005e79c5
    const volatile long double extended_027 =
        extended_026 * static_cast<long double>(f32(matrix + 44));         // original005e79c8
    const volatile long double extended_028 = extended_016 + extended_021; // original005e79cd
    const volatile long double extended_029 = extended_017 + extended_025; // original005e79cf
    const volatile long double extended_030 = extended_018 + extended_023; // original005e79d1
    const volatile long double extended_031 = extended_019 + extended_027; // original005e79d3
    const volatile long double extended_032 =
        static_cast<long double>(f32(matrix + 48));                        // original005e79d5
    const volatile long double extended_033 = extended_028 + extended_032; // original005e79d8
    const volatile long double extended_034 =
        static_cast<long double>(f32(matrix + 52));                        // original005e79da
    const volatile long double extended_035 = extended_029 + extended_034; // original005e79dd
    const volatile long double extended_036 =
        static_cast<long double>(f32(matrix + 56));                        // original005e79df
    const volatile long double extended_037 = extended_030 + extended_036; // original005e79e2
    const volatile long double extended_038 =
        static_cast<long double>(f32(matrix + 60));                        // original005e79e4
    const volatile long double extended_039 = extended_031 + extended_038; // original005e79e7
    f32(output + 0) = static_cast<float>(extended_033);                    // original005e79e9
    f32(output + 4) = static_cast<float>(extended_035);                    // original005e79eb
    f32(output + 8) = static_cast<float>(extended_037);                    // original005e79ee
    private_w = static_cast<float>(extended_039);                          // original005e79f1
    const volatile long double extended_040 = 1.0L;                        // original005e79f4
    call_one = static_cast<float>(extended_040);                           // original005e79f8
    const volatile long double extended_041 =
        static_cast<long double>(private_w);                 // original005e79fc
    call_w = static_cast<float>(extended_041);               // original005e79ff
    const int32_t near_one = FUN_005e3be9(call_w, call_one); // original005e7a02
    output = word(slots);                                    // original005e7a09
    if (!near_one) {                                         // original005e7a0c
        const volatile long double extended_042 = 1.0L;      // original005e7a0e
        const volatile long double extended_043 =
            extended_042 / static_cast<long double>(private_w); // original005e7a10
        const volatile long double extended_044 =
            static_cast<long double>(extended_043); // original005e7a13
        const volatile long double extended_045 =
            extended_044 * static_cast<long double>(f32(output + 0)); // original005e7a15
        f32(output + 0) = static_cast<float>(extended_045);           // original005e7a17
        const volatile long double extended_046 =
            static_cast<long double>(extended_043); // original005e7a19
        const volatile long double extended_047 =
            extended_046 * static_cast<long double>(f32(output + 4)); // original005e7a1b
        f32(output + 4) = static_cast<float>(extended_047);           // original005e7a1e
        const volatile long double extended_048 =
            extended_043 * static_cast<long double>(f32(output + 8)); // original005e7a21
        f32(output + 8) = static_cast<float>(extended_048);           // original005e7a24
    } // original005e7a27
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e796d(void*, const void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e796d\n\taddl $4,%esp\n\tretl $12");
}
