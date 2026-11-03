#include "graphics/render_transform_baseline.h"
#include "startup/math_dispatch_state.h"
#include <stdint.h>
using Transform = float*(__attribute__((stdcall)) *)(float*, const float*, const float*);
namespace {
struct HardwareWord {
    unsigned char bytes[4];
};
uint32_t load_word(const volatile float* source) {
    uint32_t value;
    __asm__ __volatile__("movl %1,%0"
                         : "=r"(value)
                         : "m"(*reinterpret_cast<const volatile HardwareWord*>(source)));
    return value;
}
void store_word(float* target, uint32_t value) {
    __asm__ __volatile__("movl %1,%0"
                         : "=m"(*reinterpret_cast<HardwareWord*>(target))
                         : "r"(value));
}
void copy_word(void*& target, const volatile void*& source) {
    __asm__ __volatile__("movsl" : "+D"(target), "+S"(source)::"memory");
}
} // namespace
extern "C" float* __attribute__((stdcall)) FUN_005e76c3(float* output, const float* vector,
                                                        const float* matrix) {
    volatile float locals[4];
    const volatile long double extended_000 = matrix[4]; // original005e76d1
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(vector[1]); // original005e76d4
    const volatile long double extended_002 = vector[0];    // original005e76d8
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(matrix[0]);                // original005e76db
    const volatile long double extended_004 = extended_001 + extended_003; // original005e76e0
    const volatile long double extended_005 =
        extended_004 + static_cast<long double>(matrix[12]); // original005e76e2
    locals[0] = static_cast<float>(extended_005);            // original005e76e5
    const volatile long double extended_006 = matrix[1];     // original005e76e8
    const volatile long double extended_007 =
        extended_006 * static_cast<long double>(vector[0]); // original005e76eb
    const volatile long double extended_008 = matrix[5];    // original005e76ed
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(vector[1]);                // original005e76f0
    const volatile long double extended_010 = extended_007 + extended_009; // original005e76f3
    const volatile long double extended_011 =
        extended_010 + static_cast<long double>(matrix[13]); // original005e76f5
    locals[1] = static_cast<float>(extended_011);            // original005e76f8
    const volatile long double extended_012 = matrix[2];     // original005e76fb
    const volatile long double extended_013 =
        extended_012 * static_cast<long double>(vector[0]); // original005e76fe
    const volatile long double extended_014 = matrix[6];    // original005e7700
    const volatile long double extended_015 =
        extended_014 * static_cast<long double>(vector[1]);                // original005e7703
    const volatile long double extended_016 = extended_013 + extended_015; // original005e7706
    const volatile long double extended_017 =
        extended_016 + static_cast<long double>(matrix[14]); // original005e7708
    locals[2] = static_cast<float>(extended_017);            // original005e770b
    const volatile long double extended_018 = matrix[3];     // original005e770e
    const volatile long double extended_019 =
        extended_018 * static_cast<long double>(vector[0]); // original005e7711
    const volatile long double extended_020 = matrix[7];    // original005e7713
    const volatile long double extended_021 =
        extended_020 * static_cast<long double>(vector[1]);                // original005e7716
    const volatile long double extended_022 = extended_019 + extended_021; // original005e7719
    const volatile long double extended_023 =
        extended_022 + static_cast<long double>(matrix[15]); // original005e771b
    locals[3] = static_cast<float>(extended_023);            // original005e7723
    const volatile void* copy_source = locals;
    void* copy_target = output;
    copy_word(copy_target, copy_source); // original005e7726 MOVSD
    copy_word(copy_target, copy_source); // original005e7727 MOVSD
    copy_word(copy_target, copy_source); // original005e7728 MOVSD
    copy_word(copy_target, copy_source); // original005e7729 MOVSD
    return output;
}

extern "C" float* __attribute__((stdcall)) FUN_005e4375(float* output, const float* vector,
                                                        const float* matrix) {
    volatile float locals[4];
    const volatile long double extended_000 = matrix[8]; // original005e4383
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(vector[2]); // original005e4386
    const volatile long double extended_002 = matrix[4];    // original005e438a
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(vector[1]);                // original005e438e
    const volatile long double extended_004 = extended_001 + extended_003; // original005e4394
    const volatile long double extended_005 = vector[0];                   // original005e4396
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(matrix[0]);                // original005e4398
    const volatile long double extended_007 = extended_004 + extended_006; // original005e439a
    const volatile long double extended_008 =
        extended_007 + static_cast<long double>(matrix[12]); // original005e439c
    locals[0] = static_cast<float>(extended_008);            // original005e439f
    const volatile long double extended_009 = matrix[9];     // original005e43a2
    const volatile long double extended_010 =
        extended_009 * static_cast<long double>(vector[2]); // original005e43a5
    const volatile long double extended_011 = matrix[5];    // original005e43a8
    const volatile long double extended_012 =
        extended_011 * static_cast<long double>(vector[1]);                // original005e43ab
    const volatile long double extended_013 = extended_010 + extended_012; // original005e43ae
    const volatile long double extended_014 = matrix[1];                   // original005e43b0
    const volatile long double extended_015 =
        extended_014 * static_cast<long double>(vector[0]);                // original005e43b3
    const volatile long double extended_016 = extended_013 + extended_015; // original005e43b5
    const volatile long double extended_017 =
        extended_016 + static_cast<long double>(matrix[13]); // original005e43b7
    locals[1] = static_cast<float>(extended_017);            // original005e43ba
    const volatile long double extended_018 = matrix[10];    // original005e43bd
    const volatile long double extended_019 =
        extended_018 * static_cast<long double>(vector[2]); // original005e43c0
    const volatile long double extended_020 = matrix[6];    // original005e43c3
    const volatile long double extended_021 =
        extended_020 * static_cast<long double>(vector[1]);                // original005e43c6
    const volatile long double extended_022 = extended_019 + extended_021; // original005e43c9
    const volatile long double extended_023 = matrix[2];                   // original005e43cb
    const volatile long double extended_024 =
        extended_023 * static_cast<long double>(vector[0]);                // original005e43ce
    const volatile long double extended_025 = extended_022 + extended_024; // original005e43d0
    const volatile long double extended_026 =
        extended_025 + static_cast<long double>(matrix[14]); // original005e43d2
    locals[2] = static_cast<float>(extended_026);            // original005e43d5
    const volatile long double extended_027 = matrix[11];    // original005e43d8
    const volatile long double extended_028 =
        extended_027 * static_cast<long double>(vector[2]); // original005e43db
    const volatile long double extended_029 = matrix[7];    // original005e43de
    const volatile long double extended_030 =
        extended_029 * static_cast<long double>(vector[1]);                // original005e43e1
    const volatile long double extended_031 = extended_028 + extended_030; // original005e43e4
    const volatile long double extended_032 = matrix[3];                   // original005e43e6
    const volatile long double extended_033 =
        extended_032 * static_cast<long double>(vector[0]);                // original005e43e9
    const volatile long double extended_034 = extended_031 + extended_033; // original005e43eb
    const volatile long double extended_035 =
        extended_034 + static_cast<long double>(matrix[15]); // original005e43ed
    locals[3] = static_cast<float>(extended_035);            // original005e43f5
    const volatile void* copy_source = locals;
    void* copy_target = output;
    copy_word(copy_target, copy_source); // original005e43f8 MOVSD
    copy_word(copy_target, copy_source); // original005e43f9 MOVSD
    copy_word(copy_target, copy_source); // original005e43fa MOVSD
    copy_word(copy_target, copy_source); // original005e43fb MOVSD
    return output;
}

extern "C" float* __attribute__((stdcall)) FUN_005e4b38(float* output, const float* vector,
                                                        const float* matrix) {
    volatile float locals[4];
    const volatile long double extended_000 = matrix[12]; // original005e4b46
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(vector[3]); // original005e4b49
    const volatile long double extended_002 = matrix[4];    // original005e4b4d
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(vector[1]);                // original005e4b51
    const volatile long double extended_004 = extended_001 + extended_003; // original005e4b57
    const volatile long double extended_005 = matrix[8];                   // original005e4b59
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(vector[2]);                // original005e4b5c
    const volatile long double extended_007 = extended_004 + extended_006; // original005e4b5f
    const volatile long double extended_008 = vector[0];                   // original005e4b61
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(matrix[0]);                // original005e4b63
    const volatile long double extended_010 = extended_007 + extended_009; // original005e4b65
    locals[0] = static_cast<float>(extended_010);                          // original005e4b67
    const volatile long double extended_011 = matrix[13];                  // original005e4b6a
    const volatile long double extended_012 =
        extended_011 * static_cast<long double>(vector[3]); // original005e4b6d
    const volatile long double extended_013 = matrix[5];    // original005e4b70
    const volatile long double extended_014 =
        extended_013 * static_cast<long double>(vector[1]);                // original005e4b73
    const volatile long double extended_015 = extended_012 + extended_014; // original005e4b76
    const volatile long double extended_016 = matrix[1];                   // original005e4b78
    const volatile long double extended_017 =
        extended_016 * static_cast<long double>(vector[0]);                // original005e4b7b
    const volatile long double extended_018 = extended_015 + extended_017; // original005e4b7d
    const volatile long double extended_019 = matrix[9];                   // original005e4b7f
    const volatile long double extended_020 =
        extended_019 * static_cast<long double>(vector[2]);                // original005e4b82
    const volatile long double extended_021 = extended_018 + extended_020; // original005e4b85
    locals[1] = static_cast<float>(extended_021);                          // original005e4b87
    const volatile long double extended_022 = matrix[14];                  // original005e4b8a
    const volatile long double extended_023 =
        extended_022 * static_cast<long double>(vector[3]); // original005e4b8d
    const volatile long double extended_024 = matrix[6];    // original005e4b90
    const volatile long double extended_025 =
        extended_024 * static_cast<long double>(vector[1]);                // original005e4b93
    const volatile long double extended_026 = extended_023 + extended_025; // original005e4b96
    const volatile long double extended_027 = matrix[2];                   // original005e4b98
    const volatile long double extended_028 =
        extended_027 * static_cast<long double>(vector[0]);                // original005e4b9b
    const volatile long double extended_029 = extended_026 + extended_028; // original005e4b9d
    const volatile long double extended_030 = matrix[10];                  // original005e4b9f
    const volatile long double extended_031 =
        extended_030 * static_cast<long double>(vector[2]);                // original005e4ba2
    const volatile long double extended_032 = extended_029 + extended_031; // original005e4ba5
    locals[2] = static_cast<float>(extended_032);                          // original005e4ba7
    const volatile long double extended_033 = matrix[15];                  // original005e4baa
    const volatile long double extended_034 =
        extended_033 * static_cast<long double>(vector[3]); // original005e4bad
    const volatile long double extended_035 = matrix[7];    // original005e4bb0
    const volatile long double extended_036 =
        extended_035 * static_cast<long double>(vector[1]);                // original005e4bb3
    const volatile long double extended_037 = extended_034 + extended_036; // original005e4bb6
    const volatile long double extended_038 = matrix[3];                   // original005e4bb8
    const volatile long double extended_039 =
        extended_038 * static_cast<long double>(vector[0]);                // original005e4bbb
    const volatile long double extended_040 = extended_037 + extended_039; // original005e4bbd
    const volatile long double extended_041 = matrix[11];                  // original005e4bbf
    const volatile long double extended_042 =
        extended_041 * static_cast<long double>(vector[2]);                // original005e4bc2
    const volatile long double extended_043 = extended_040 + extended_042; // original005e4bca
    locals[3] = static_cast<float>(extended_043);                          // original005e4bcc
    const volatile void* copy_source = locals;
    void* copy_target = output;
    copy_word(copy_target, copy_source); // original005e4bcf MOVSD
    copy_word(copy_target, copy_source); // original005e4bd0 MOVSD
    copy_word(copy_target, copy_source); // original005e4bd1 MOVSD
    copy_word(copy_target, copy_source); // original005e4bd2 MOVSD
    return output;
}

extern "C" float* __attribute__((stdcall)) FUN_005e4031(float* output, const float* vector,
                                                        const float* matrix) {
    volatile float locals[2];
    const volatile long double extended_000 = matrix[4]; // original005e403e
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(vector[1]); // original005e4041
    const volatile long double extended_002 = vector[0];    // original005e4044
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(matrix[0]);                // original005e4046
    const volatile long double extended_004 = extended_001 + extended_003; // original005e4048
    locals[0] = static_cast<float>(extended_004);                          // original005e404a
    const volatile long double extended_005 = matrix[1];                   // original005e404d
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(vector[0]); // original005e4050
    const volatile long double extended_007 = matrix[5];    // original005e4052
    const uint32_t word_0 = load_word(&locals[0]);          // original005e4055
    const volatile long double extended_008 =
        extended_007 * static_cast<long double>(vector[1]);                // original005e4058
    store_word(output + 0, word_0);                                        // original005e405e
    const volatile long double extended_009 = extended_006 + extended_008; // original005e4060
    locals[1] = static_cast<float>(extended_009);                          // original005e4062
    const uint32_t word_1 = load_word(&locals[1]);                         // original005e4065
    store_word(output + 1, word_1);                                        // original005e4068
    return output;
}

extern "C" float* __attribute__((stdcall)) FUN_005e45ea(float* output, const float* vector,
                                                        const float* matrix) {
    volatile float locals[3];
    const volatile long double extended_000 = matrix[8]; // original005e45f8
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(vector[2]); // original005e45fb
    const volatile long double extended_002 = matrix[4];    // original005e45ff
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(vector[1]);                // original005e4603
    const volatile long double extended_004 = extended_001 + extended_003; // original005e4609
    const volatile long double extended_005 = vector[0];                   // original005e460b
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(matrix[0]);                // original005e460d
    const volatile long double extended_007 = extended_004 + extended_006; // original005e460f
    locals[0] = static_cast<float>(extended_007);                          // original005e4611
    const volatile long double extended_008 = matrix[9];                   // original005e4614
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(vector[2]); // original005e4617
    const volatile long double extended_010 = matrix[5];    // original005e461a
    const volatile long double extended_011 =
        extended_010 * static_cast<long double>(vector[1]);                // original005e461d
    const volatile long double extended_012 = extended_009 + extended_011; // original005e4620
    const volatile long double extended_013 = matrix[1];                   // original005e4622
    const volatile long double extended_014 =
        extended_013 * static_cast<long double>(vector[0]);                // original005e4625
    const volatile long double extended_015 = extended_012 + extended_014; // original005e4627
    locals[1] = static_cast<float>(extended_015);                          // original005e4629
    const volatile long double extended_016 = matrix[10];                  // original005e462c
    const volatile long double extended_017 =
        extended_016 * static_cast<long double>(vector[2]); // original005e462f
    const volatile long double extended_018 = matrix[6];    // original005e4632
    const volatile long double extended_019 =
        extended_018 * static_cast<long double>(vector[1]);                // original005e4635
    const volatile long double extended_020 = extended_017 + extended_019; // original005e4638
    const volatile long double extended_021 = matrix[2];                   // original005e463a
    const volatile long double extended_022 =
        extended_021 * static_cast<long double>(vector[0]);                // original005e463d
    const volatile long double extended_023 = extended_020 + extended_022; // original005e4644
    locals[2] = static_cast<float>(extended_023);                          // original005e4646
    const volatile void* copy_source = locals;
    void* copy_target = output;
    copy_word(copy_target, copy_source); // original005e4649 MOVSD
    copy_word(copy_target, copy_source); // original005e464a MOVSD
    copy_word(copy_target, copy_source); // original005e464b MOVSD
    return output;
}

extern "C" float* __attribute__((stdcall)) FUN_005e7231(float* output, const float* vector,
                                                        const float* matrix) {
    volatile float locals[4];
    const volatile long double extended_000 = matrix[8]; // original005e723f
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(vector[2]); // original005e7242
    const volatile long double extended_002 = matrix[12];   // original005e7246
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(vector[3]);                // original005e724a
    const volatile long double extended_004 = extended_001 + extended_003; // original005e7250
    const volatile long double extended_005 = matrix[4];                   // original005e7252
    const volatile long double extended_006 =
        extended_005 * static_cast<long double>(vector[1]);                // original005e7255
    const volatile long double extended_007 = extended_004 + extended_006; // original005e7258
    const volatile long double extended_008 = vector[0];                   // original005e725a
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(matrix[0]);                // original005e725c
    const volatile long double extended_010 = extended_007 + extended_009; // original005e725e
    locals[0] = static_cast<float>(extended_010);                          // original005e7260
    const volatile long double extended_011 = matrix[9];                   // original005e7263
    const volatile long double extended_012 =
        extended_011 * static_cast<long double>(vector[2]); // original005e7266
    const volatile long double extended_013 = matrix[1];    // original005e7269
    const volatile long double extended_014 =
        extended_013 * static_cast<long double>(vector[0]);                // original005e726c
    const volatile long double extended_015 = extended_012 + extended_014; // original005e726e
    const volatile long double extended_016 = matrix[13];                  // original005e7270
    const volatile long double extended_017 =
        extended_016 * static_cast<long double>(vector[3]);                // original005e7273
    const volatile long double extended_018 = extended_015 + extended_017; // original005e7276
    const volatile long double extended_019 = matrix[5];                   // original005e7278
    const volatile long double extended_020 =
        extended_019 * static_cast<long double>(vector[1]);                // original005e727b
    const volatile long double extended_021 = extended_018 + extended_020; // original005e727e
    locals[1] = static_cast<float>(extended_021);                          // original005e7280
    const volatile long double extended_022 = matrix[10];                  // original005e7283
    const volatile long double extended_023 =
        extended_022 * static_cast<long double>(vector[2]); // original005e7286
    const volatile long double extended_024 = matrix[2];    // original005e7289
    const volatile long double extended_025 =
        extended_024 * static_cast<long double>(vector[0]);                // original005e728c
    const volatile long double extended_026 = extended_023 + extended_025; // original005e728e
    const volatile long double extended_027 = matrix[14];                  // original005e7290
    const volatile long double extended_028 =
        extended_027 * static_cast<long double>(vector[3]);                // original005e7293
    const volatile long double extended_029 = extended_026 + extended_028; // original005e7296
    const volatile long double extended_030 = matrix[6];                   // original005e7298
    const volatile long double extended_031 =
        extended_030 * static_cast<long double>(vector[1]);                // original005e729b
    const volatile long double extended_032 = extended_029 + extended_031; // original005e729e
    locals[2] = static_cast<float>(extended_032);                          // original005e72a0
    const volatile long double extended_033 = matrix[11];                  // original005e72a3
    const volatile long double extended_034 =
        extended_033 * static_cast<long double>(vector[2]); // original005e72a6
    const volatile long double extended_035 = matrix[3];    // original005e72a9
    const volatile long double extended_036 =
        extended_035 * static_cast<long double>(vector[0]);                // original005e72ac
    const volatile long double extended_037 = extended_034 + extended_036; // original005e72ae
    const volatile long double extended_038 = matrix[15];                  // original005e72b0
    const volatile long double extended_039 =
        extended_038 * static_cast<long double>(vector[3]);                // original005e72b3
    const volatile long double extended_040 = extended_037 + extended_039; // original005e72b6
    const volatile long double extended_041 = matrix[7];                   // original005e72b8
    const volatile long double extended_042 =
        extended_041 * static_cast<long double>(vector[1]);                // original005e72bb
    const volatile long double extended_043 = extended_040 + extended_042; // original005e72c3
    locals[3] = static_cast<float>(extended_043);                          // original005e72c5
    const volatile void* copy_source = locals;
    void* copy_target = output;
    copy_word(copy_target, copy_source); // original005e72c8 MOVSD
    copy_word(copy_target, copy_source); // original005e72c9 MOVSD
    copy_word(copy_target, copy_source); // original005e72ca MOVSD
    copy_word(copy_target, copy_source); // original005e72cb MOVSD
    return output;
}

extern "C" float* __attribute__((stdcall)) FUN_005e3fd3(float* output, const float* vector,
                                                        const float* matrix) {
    return reinterpret_cast<Transform>(dat_0070f370.entries[0])(output, vector, matrix);
}

extern "C" float* __attribute__((stdcall)) FUN_005e436f(float* output, const float* vector,
                                                        const float* matrix) {
    return reinterpret_cast<Transform>(dat_0070f370.entries[1])(output, vector, matrix);
}

extern "C" float* __attribute__((stdcall)) FUN_005e4b32(float* output, const float* vector,
                                                        const float* matrix) {
    return reinterpret_cast<Transform>(dat_0070f370.entries[2])(output, vector, matrix);
}

extern "C" float* __attribute__((stdcall)) FUN_005e402b(float* output, const float* vector,
                                                        const float* matrix) {
    return reinterpret_cast<Transform>(dat_0070f370.entries[5])(output, vector, matrix);
}

extern "C" float* __attribute__((stdcall)) FUN_005e45e4(float* output, const float* vector,
                                                        const float* matrix) {
    return reinterpret_cast<Transform>(dat_0070f370.entries[6])(output, vector, matrix);
}
