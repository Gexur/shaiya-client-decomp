#include "graphics/render_transform_scalar.h"
#include "startup/math_dispatch_state.h"
using Transform = float*(__attribute__((stdcall)) *)(float*, const float*, const float*);

extern "C" float* __attribute__((stdcall)) FUN_0064f179(float* output, const float* vector,
                                                        const float* matrix) {
    const volatile long double extended_000 = vector[0]; // original0064f187
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(matrix[0]); // original0064f189
    const volatile long double extended_002 = vector[0];    // original0064f18b
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(matrix[2]); // original0064f18d
    const volatile long double extended_004 = vector[0];    // original0064f190
    const volatile long double extended_005 =
        extended_004 * static_cast<long double>(matrix[1]); // original0064f192
    const volatile long double extended_006 = vector[0];    // original0064f195
    const volatile long double extended_007 =
        extended_006 * static_cast<long double>(matrix[3]); // original0064f197
    const volatile long double extended_008 = vector[1];    // original0064f19c
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(matrix[4]); // original0064f19f
    const volatile long double extended_010 = vector[1];    // original0064f1a2
    const volatile long double extended_011 =
        extended_010 * static_cast<long double>(matrix[6]); // original0064f1a5
    const volatile long double extended_012 = vector[1];    // original0064f1a8
    const volatile long double extended_013 =
        extended_012 * static_cast<long double>(matrix[5]); // original0064f1ab
    const volatile long double extended_014 = vector[1];    // original0064f1ae
    const volatile long double extended_015 =
        extended_014 * static_cast<long double>(matrix[7]);                // original0064f1b1
    const volatile long double extended_016 = extended_001 + extended_009; // original0064f1b6
    const volatile long double extended_017 = extended_005 + extended_013; // original0064f1b8
    const volatile long double extended_018 = extended_003 + extended_011; // original0064f1ba
    const volatile long double extended_019 = extended_007 + extended_015; // original0064f1bc
    const volatile long double extended_020 = matrix[12];                  // original0064f1be
    const volatile long double extended_021 = extended_016 + extended_020; // original0064f1c1
    const volatile long double extended_022 = matrix[13];                  // original0064f1c3
    const volatile long double extended_023 = extended_017 + extended_022; // original0064f1c6
    const volatile long double extended_024 = matrix[14];                  // original0064f1c8
    const volatile long double extended_025 = extended_018 + extended_024; // original0064f1cb
    const volatile long double extended_026 = matrix[15];                  // original0064f1cd
    const volatile long double extended_027 = extended_019 + extended_026; // original0064f1d0
    output[0] = static_cast<float>(extended_021);                          // original0064f1d2
    output[1] = static_cast<float>(extended_023);                          // original0064f1d4
    output[2] = static_cast<float>(extended_025);                          // original0064f1d7
    output[3] = static_cast<float>(extended_027);                          // original0064f1da
    return output;
}

extern "C" float* __attribute__((stdcall)) FUN_0064f1e4(float* output, const float* vector,
                                                        const float* matrix) {
    const volatile long double extended_000 = vector[0]; // original0064f1f2
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(matrix[0]); // original0064f1f4
    const volatile long double extended_002 = vector[0];    // original0064f1f6
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(matrix[1]); // original0064f1f8
    const volatile long double extended_004 = vector[1];    // original0064f1fd
    const volatile long double extended_005 =
        extended_004 * static_cast<long double>(matrix[4]); // original0064f200
    const volatile long double extended_006 = vector[1];    // original0064f203
    const volatile long double extended_007 =
        extended_006 * static_cast<long double>(matrix[5]);                // original0064f206
    const volatile long double extended_008 = extended_001 + extended_005; // original0064f20b
    const volatile long double extended_009 = extended_003 + extended_007; // original0064f20d
    output[0] = static_cast<float>(extended_008);                          // original0064f20f
    output[1] = static_cast<float>(extended_009);                          // original0064f211
    return output;
}

extern "C" float* __attribute__((stdcall)) FUN_0064f21b(float* output, const float* vector,
                                                        const float* matrix) {
    const volatile long double extended_000 = vector[0]; // original0064f229
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(matrix[0]); // original0064f22b
    const volatile long double extended_002 = vector[0];    // original0064f22d
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(matrix[2]); // original0064f22f
    const volatile long double extended_004 = vector[0];    // original0064f232
    const volatile long double extended_005 =
        extended_004 * static_cast<long double>(matrix[1]); // original0064f234
    const volatile long double extended_006 = vector[0];    // original0064f237
    const volatile long double extended_007 =
        extended_006 * static_cast<long double>(matrix[3]); // original0064f239
    const volatile long double extended_008 = vector[1];    // original0064f23e
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(matrix[4]); // original0064f241
    const volatile long double extended_010 = vector[1];    // original0064f244
    const volatile long double extended_011 =
        extended_010 * static_cast<long double>(matrix[6]); // original0064f247
    const volatile long double extended_012 = vector[1];    // original0064f24a
    const volatile long double extended_013 =
        extended_012 * static_cast<long double>(matrix[5]); // original0064f24d
    const volatile long double extended_014 = vector[1];    // original0064f250
    const volatile long double extended_015 =
        extended_014 * static_cast<long double>(matrix[7]);                // original0064f253
    const volatile long double extended_016 = extended_001 + extended_009; // original0064f258
    const volatile long double extended_017 = extended_005 + extended_013; // original0064f25a
    const volatile long double extended_018 = extended_003 + extended_011; // original0064f25c
    const volatile long double extended_019 = extended_007 + extended_015; // original0064f25e
    const volatile long double extended_020 = vector[2];                   // original0064f260
    const volatile long double extended_021 =
        extended_020 * static_cast<long double>(matrix[8]); // original0064f263
    const volatile long double extended_022 = vector[2];    // original0064f266
    const volatile long double extended_023 =
        extended_022 * static_cast<long double>(matrix[10]); // original0064f269
    const volatile long double extended_024 = vector[2];     // original0064f26c
    const volatile long double extended_025 =
        extended_024 * static_cast<long double>(matrix[9]); // original0064f26f
    const volatile long double extended_026 = vector[2];    // original0064f272
    const volatile long double extended_027 =
        extended_026 * static_cast<long double>(matrix[11]);               // original0064f275
    const volatile long double extended_028 = extended_016 + extended_021; // original0064f27a
    const volatile long double extended_029 = extended_017 + extended_025; // original0064f27c
    const volatile long double extended_030 = extended_018 + extended_023; // original0064f27e
    const volatile long double extended_031 = extended_019 + extended_027; // original0064f280
    const volatile long double extended_032 = matrix[12];                  // original0064f282
    const volatile long double extended_033 = extended_028 + extended_032; // original0064f285
    const volatile long double extended_034 = matrix[13];                  // original0064f287
    const volatile long double extended_035 = extended_029 + extended_034; // original0064f28a
    const volatile long double extended_036 = matrix[14];                  // original0064f28c
    const volatile long double extended_037 = extended_030 + extended_036; // original0064f28f
    const volatile long double extended_038 = matrix[15];                  // original0064f291
    const volatile long double extended_039 = extended_031 + extended_038; // original0064f294
    output[0] = static_cast<float>(extended_033);                          // original0064f296
    output[1] = static_cast<float>(extended_035);                          // original0064f298
    output[2] = static_cast<float>(extended_037);                          // original0064f29b
    output[3] = static_cast<float>(extended_039);                          // original0064f29e
    return output;
}

extern "C" float* __attribute__((stdcall)) FUN_0064f2a8(float* output, const float* vector,
                                                        const float* matrix) {
    const volatile long double extended_000 = vector[0]; // original0064f2b6
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(matrix[0]); // original0064f2b8
    const volatile long double extended_002 = vector[0];    // original0064f2ba
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(matrix[1]); // original0064f2bc
    const volatile long double extended_004 = vector[0];    // original0064f2bf
    const volatile long double extended_005 =
        extended_004 * static_cast<long double>(matrix[2]); // original0064f2c1
    const volatile long double extended_006 = vector[1];    // original0064f2c6
    const volatile long double extended_007 =
        extended_006 * static_cast<long double>(matrix[4]); // original0064f2c9
    const volatile long double extended_008 = vector[1];    // original0064f2cc
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(matrix[5]); // original0064f2cf
    const volatile long double extended_010 = vector[1];    // original0064f2d2
    const volatile long double extended_011 =
        extended_010 * static_cast<long double>(matrix[6]);                // original0064f2d5
    const volatile long double extended_012 = extended_001 + extended_007; // original0064f2da
    const volatile long double extended_013 = extended_003 + extended_009; // original0064f2dc
    const volatile long double extended_014 = extended_005 + extended_011; // original0064f2de
    const volatile long double extended_015 = vector[2];                   // original0064f2e0
    const volatile long double extended_016 =
        extended_015 * static_cast<long double>(matrix[8]); // original0064f2e3
    const volatile long double extended_017 = vector[2];    // original0064f2e6
    const volatile long double extended_018 =
        extended_017 * static_cast<long double>(matrix[9]); // original0064f2e9
    const volatile long double extended_019 = vector[2];    // original0064f2ec
    const volatile long double extended_020 =
        extended_019 * static_cast<long double>(matrix[10]);               // original0064f2ef
    const volatile long double extended_021 = extended_012 + extended_016; // original0064f2f4
    const volatile long double extended_022 = extended_013 + extended_018; // original0064f2f6
    const volatile long double extended_023 = extended_014 + extended_020; // original0064f2f8
    output[0] = static_cast<float>(extended_021);                          // original0064f2fa
    output[1] = static_cast<float>(extended_022);                          // original0064f2fc
    output[2] = static_cast<float>(extended_023);                          // original0064f2ff
    return output;
}

extern "C" float* __attribute__((stdcall)) FUN_0064f309(float* output, const float* vector,
                                                        const float* matrix) {
    const volatile long double extended_000 = vector[0]; // original0064f317
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(matrix[0]); // original0064f319
    const volatile long double extended_002 = vector[0];    // original0064f31b
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(matrix[2]); // original0064f31d
    const volatile long double extended_004 = vector[0];    // original0064f320
    const volatile long double extended_005 =
        extended_004 * static_cast<long double>(matrix[1]); // original0064f322
    const volatile long double extended_006 = vector[0];    // original0064f325
    const volatile long double extended_007 =
        extended_006 * static_cast<long double>(matrix[3]); // original0064f327
    const volatile long double extended_008 = vector[1];    // original0064f32c
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(matrix[4]); // original0064f32f
    const volatile long double extended_010 = vector[1];    // original0064f332
    const volatile long double extended_011 =
        extended_010 * static_cast<long double>(matrix[6]); // original0064f335
    const volatile long double extended_012 = vector[1];    // original0064f338
    const volatile long double extended_013 =
        extended_012 * static_cast<long double>(matrix[5]); // original0064f33b
    const volatile long double extended_014 = vector[1];    // original0064f33e
    const volatile long double extended_015 =
        extended_014 * static_cast<long double>(matrix[7]);                // original0064f341
    const volatile long double extended_016 = extended_001 + extended_009; // original0064f346
    const volatile long double extended_017 = extended_005 + extended_013; // original0064f348
    const volatile long double extended_018 = extended_003 + extended_011; // original0064f34a
    const volatile long double extended_019 = extended_007 + extended_015; // original0064f34c
    const volatile long double extended_020 = vector[2];                   // original0064f34e
    const volatile long double extended_021 =
        extended_020 * static_cast<long double>(matrix[8]); // original0064f351
    const volatile long double extended_022 = vector[2];    // original0064f354
    const volatile long double extended_023 =
        extended_022 * static_cast<long double>(matrix[10]); // original0064f357
    const volatile long double extended_024 = vector[2];     // original0064f35a
    const volatile long double extended_025 =
        extended_024 * static_cast<long double>(matrix[9]); // original0064f35d
    const volatile long double extended_026 = vector[2];    // original0064f360
    const volatile long double extended_027 =
        extended_026 * static_cast<long double>(matrix[11]);               // original0064f363
    const volatile long double extended_028 = extended_016 + extended_021; // original0064f368
    const volatile long double extended_029 = extended_017 + extended_025; // original0064f36a
    const volatile long double extended_030 = extended_018 + extended_023; // original0064f36c
    const volatile long double extended_031 = extended_019 + extended_027; // original0064f36e
    const volatile long double extended_032 = vector[3];                   // original0064f370
    const volatile long double extended_033 =
        extended_032 * static_cast<long double>(matrix[12]); // original0064f373
    const volatile long double extended_034 = vector[3];     // original0064f376
    const volatile long double extended_035 =
        extended_034 * static_cast<long double>(matrix[14]); // original0064f379
    const volatile long double extended_036 = vector[3];     // original0064f37c
    const volatile long double extended_037 =
        extended_036 * static_cast<long double>(matrix[13]); // original0064f37f
    const volatile long double extended_038 = vector[3];     // original0064f382
    const volatile long double extended_039 =
        extended_038 * static_cast<long double>(matrix[15]);               // original0064f385
    const volatile long double extended_040 = extended_028 + extended_033; // original0064f38a
    const volatile long double extended_041 = extended_029 + extended_037; // original0064f38c
    const volatile long double extended_042 = extended_030 + extended_035; // original0064f38e
    const volatile long double extended_043 = extended_031 + extended_039; // original0064f390
    output[0] = static_cast<float>(extended_040);                          // original0064f392
    output[1] = static_cast<float>(extended_041);                          // original0064f394
    output[2] = static_cast<float>(extended_042);                          // original0064f397
    output[3] = static_cast<float>(extended_043);                          // original0064f39a
    return output;
}

extern "C" float* __attribute__((stdcall)) FUN_005e3fc0(float* output, const float* vector,
                                                        const float* matrix) {
    FUN_005fd1f8(1);
    return reinterpret_cast<Transform>(dat_0070f370.entries[0])(output, vector, matrix);
}

extern "C" float* __attribute__((stdcall)) FUN_005e435c(float* output, const float* vector,
                                                        const float* matrix) {
    FUN_005fd1f8(1);
    return reinterpret_cast<Transform>(dat_0070f370.entries[1])(output, vector, matrix);
}

extern "C" float* __attribute__((stdcall)) FUN_005e4b1f(float* output, const float* vector,
                                                        const float* matrix) {
    FUN_005fd1f8(1);
    return reinterpret_cast<Transform>(dat_0070f370.entries[2])(output, vector, matrix);
}

extern "C" float* __attribute__((stdcall)) FUN_005e4018(float* output, const float* vector,
                                                        const float* matrix) {
    FUN_005fd1f8(1);
    return reinterpret_cast<Transform>(dat_0070f370.entries[5])(output, vector, matrix);
}

extern "C" float* __attribute__((stdcall)) FUN_005e45d1(float* output, const float* vector,
                                                        const float* matrix) {
    FUN_005fd1f8(1);
    return reinterpret_cast<Transform>(dat_0070f370.entries[6])(output, vector, matrix);
}

extern "C" float* __attribute__((stdcall)) FUN_005e721e(float* output, const float* vector,
                                                        const float* matrix) {
    FUN_005fd1f8(1);
    return reinterpret_cast<Transform>(dat_0070f370.entries[35])(output, vector, matrix);
}
