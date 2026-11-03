#include "graphics/render_transform_arrays.h"
#include "graphics/render_vector.h"
namespace {
inline uint32_t word_at(uint32_t p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
inline void put_word(uint32_t p, uint32_t v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
struct __attribute__((packed, may_alias)) FloatWord {
    float value;
};
inline volatile float& float_at(uint32_t p) {
    return reinterpret_cast<volatile FloatWord*>(p)->value;
}
} // namespace
extern "C" void* recovered_005e4415(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    uint32_t remaining = word_at(slots + 20);
    uint32_t output = word_at(slots);
    put_word(slots, output);
    if (remaining) {
        const uint32_t matrix = word_at(slots + 16);
        uint32_t input = word_at(slots + 8);
        do {
            volatile float private_0;
            volatile float private_1;
            volatile float private_2;
            volatile float private_3;
            const volatile long double extended_000 =
                static_cast<long double>(float_at(matrix + 16)); // original005e4437
            const uint32_t saved_output = output;                // original005e443a
            const volatile long double extended_001 =
                extended_000 * static_cast<long double>(float_at(input + 4)); // original005e443c
            output += word_at(slots + 4);                                     // original005e443f
            const volatile long double extended_002 =
                static_cast<long double>(float_at(matrix + 32)); // original005e4442
            const volatile long double extended_003 =
                extended_002 * static_cast<long double>(float_at(input + 8)); // original005e4448
            const volatile long double extended_004 =
                extended_001 + extended_003; // original005e444b
            const volatile long double extended_005 =
                static_cast<long double>(float_at(input + 0)); // original005e444d
            const volatile long double extended_006 =
                extended_005 * static_cast<long double>(float_at(matrix + 0)); // original005e444f
            const volatile long double extended_007 =
                extended_004 + extended_006; // original005e4451
            const volatile long double extended_008 =
                extended_007 + static_cast<long double>(float_at(matrix + 48)); // original005e4453
            private_0 = static_cast<float>(extended_008);                       // original005e4456
            const volatile long double extended_009 =
                static_cast<long double>(float_at(matrix + 4)); // original005e4459
            const volatile long double extended_010 =
                extended_009 * static_cast<long double>(float_at(input + 0)); // original005e445c
            const volatile long double extended_011 =
                static_cast<long double>(float_at(matrix + 20)); // original005e445e
            const volatile long double extended_012 =
                extended_011 * static_cast<long double>(float_at(input + 4)); // original005e4461
            const volatile long double extended_013 =
                extended_010 + extended_012; // original005e4464
            const volatile long double extended_014 =
                static_cast<long double>(float_at(matrix + 36)); // original005e4466
            const volatile long double extended_015 =
                extended_014 * static_cast<long double>(float_at(input + 8)); // original005e4469
            const volatile long double extended_016 =
                extended_013 + extended_015; // original005e446c
            const volatile long double extended_017 =
                extended_016 + static_cast<long double>(float_at(matrix + 52)); // original005e446e
            private_1 = static_cast<float>(extended_017);                       // original005e4471
            const volatile long double extended_018 =
                static_cast<long double>(float_at(input + 8)); // original005e4474
            const volatile long double extended_019 =
                extended_018 * static_cast<long double>(float_at(matrix + 40)); // original005e4477
            const volatile long double extended_020 =
                static_cast<long double>(float_at(input + 0)); // original005e447a
            const volatile long double extended_021 =
                extended_020 * static_cast<long double>(float_at(matrix + 8)); // original005e447c
            const volatile long double extended_022 =
                extended_019 + extended_021; // original005e447f
            const volatile long double extended_023 =
                static_cast<long double>(float_at(input + 4)); // original005e4481
            const volatile long double extended_024 =
                extended_023 * static_cast<long double>(float_at(matrix + 24)); // original005e4484
            const volatile long double extended_025 =
                extended_022 + extended_024; // original005e4487
            const volatile long double extended_026 =
                extended_025 + static_cast<long double>(float_at(matrix + 56)); // original005e4489
            private_2 = static_cast<float>(extended_026);                       // original005e448c
            const volatile long double extended_027 =
                static_cast<long double>(float_at(matrix + 12)); // original005e448f
            const volatile long double extended_028 =
                extended_027 * static_cast<long double>(float_at(input + 0)); // original005e4492
            const volatile long double extended_029 =
                static_cast<long double>(float_at(matrix + 28)); // original005e4494
            const volatile long double extended_030 =
                extended_029 * static_cast<long double>(float_at(input + 4)); // original005e4497
            const volatile long double extended_031 =
                extended_028 + extended_030; // original005e449a
            const volatile long double extended_032 =
                static_cast<long double>(float_at(matrix + 44)); // original005e449c
            const volatile long double extended_033 =
                extended_032 * static_cast<long double>(float_at(input + 8)); // original005e449f
            input += word_at(slots + 12);                                     // original005e44a2
            --remaining;                                                      // original005e44a5
            const volatile long double extended_034 =
                extended_031 + extended_033; // original005e44a6
            const volatile long double extended_035 =
                extended_034 + static_cast<long double>(float_at(matrix + 60)); // original005e44a8
            private_3 = static_cast<float>(extended_035);                       // original005e44ab
            put_word(saved_output + 0,
                     word_at(reinterpret_cast<uint32_t>(&private_0))); // original005e44ae
            put_word(saved_output + 4,
                     word_at(reinterpret_cast<uint32_t>(&private_1))); // original005e44af
            put_word(saved_output + 8,
                     word_at(reinterpret_cast<uint32_t>(&private_2))); // original005e44b0
            put_word(saved_output + 12,
                     word_at(reinterpret_cast<uint32_t>(&private_3))); // original005e44b1
        } while (remaining);
    }
    return reinterpret_cast<void*>(word_at(slots));
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e4415(void*, uint32_t, const void*,
                                                              uint32_t, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e4415\n\taddl $4,%esp\n\tretl $24");
}

extern "C" void* recovered_005e44f0(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    uint32_t remaining = word_at(slots + 20);
    uint32_t output = word_at(slots);
    const uint32_t initial_output = output;
    if (remaining) {
        const uint32_t matrix = word_at(slots + 16);
        uint32_t input = word_at(slots + 8);
        put_word(slots + 20, remaining);
        do {
            volatile float private_0;
            volatile float private_1;
            volatile float private_2;
            volatile float call_w, call_one;
            const volatile long double extended_000 =
                static_cast<long double>(float_at(matrix + 16)); // original005e4515
            const volatile long double extended_001 =
                extended_000 * static_cast<long double>(float_at(input + 4)); // original005e451b
            const uint32_t saved_output = output;                             // original005e451e
            const volatile long double extended_002 =
                static_cast<long double>(float_at(matrix + 32)); // original005e4520
            const volatile long double extended_003 =
                extended_002 * static_cast<long double>(float_at(input + 8)); // original005e4524
            const volatile long double extended_004 =
                extended_001 + extended_003; // original005e4528
            const volatile long double extended_005 =
                static_cast<long double>(float_at(input + 0)); // original005e452a
            const volatile long double extended_006 =
                extended_005 * static_cast<long double>(float_at(matrix + 0)); // original005e452c
            const volatile long double extended_007 =
                extended_004 + extended_006; // original005e452e
            const volatile long double extended_008 =
                extended_007 + static_cast<long double>(float_at(matrix + 48)); // original005e4530
            private_0 = static_cast<float>(extended_008);                       // original005e4533
            const volatile long double extended_009 =
                static_cast<long double>(float_at(matrix + 4)); // original005e4536
            const volatile long double extended_010 =
                extended_009 * static_cast<long double>(float_at(input + 0)); // original005e4539
            const volatile long double extended_011 =
                static_cast<long double>(float_at(matrix + 20)); // original005e453b
            const volatile long double extended_012 =
                extended_011 * static_cast<long double>(float_at(input + 4)); // original005e453e
            const volatile long double extended_013 =
                extended_010 + extended_012; // original005e4541
            const volatile long double extended_014 =
                static_cast<long double>(float_at(matrix + 36)); // original005e4543
            const volatile long double extended_015 =
                extended_014 * static_cast<long double>(float_at(input + 8)); // original005e4546
            const volatile long double extended_016 =
                extended_013 + extended_015; // original005e4549
            const volatile long double extended_017 =
                extended_016 + static_cast<long double>(float_at(matrix + 52)); // original005e454b
            private_1 = static_cast<float>(extended_017);                       // original005e454e
            const volatile long double extended_018 =
                static_cast<long double>(float_at(input + 8)); // original005e4551
            const volatile long double extended_019 =
                extended_018 * static_cast<long double>(float_at(matrix + 40)); // original005e4554
            const volatile long double extended_020 =
                static_cast<long double>(float_at(input + 0)); // original005e4557
            const volatile long double extended_021 =
                extended_020 * static_cast<long double>(float_at(matrix + 8)); // original005e4559
            const volatile long double extended_022 =
                extended_019 + extended_021; // original005e455c
            const volatile long double extended_023 =
                static_cast<long double>(float_at(input + 4)); // original005e455e
            const volatile long double extended_024 =
                extended_023 * static_cast<long double>(float_at(matrix + 24)); // original005e4561
            const volatile long double extended_025 =
                extended_022 + extended_024; // original005e4564
            const volatile long double extended_026 =
                extended_025 + static_cast<long double>(float_at(matrix + 56)); // original005e4566
            private_2 = static_cast<float>(extended_026);                       // original005e4569
            const volatile long double extended_027 =
                static_cast<long double>(float_at(matrix + 12)); // original005e456c
            const volatile long double extended_028 =
                extended_027 * static_cast<long double>(float_at(input + 0)); // original005e456f
            const volatile long double extended_029 =
                static_cast<long double>(float_at(matrix + 28)); // original005e4571
            const volatile long double extended_030 =
                extended_029 * static_cast<long double>(float_at(input + 4)); // original005e4574
            const volatile long double extended_031 =
                extended_028 + extended_030; // original005e4577
            const volatile long double extended_032 =
                static_cast<long double>(float_at(matrix + 44)); // original005e4579
            const volatile long double extended_033 =
                extended_032 * static_cast<long double>(float_at(input + 8)); // original005e457c
            const volatile long double extended_034 =
                extended_031 + extended_033; // original005e457f
            const volatile long double extended_035 =
                extended_034 + static_cast<long double>(float_at(matrix + 60)); // original005e4581
            put_word(saved_output + 0,
                     word_at(reinterpret_cast<uint32_t>(&private_0))); // original005e4584
            put_word(saved_output + 4,
                     word_at(reinterpret_cast<uint32_t>(&private_1))); // original005e4585
            float_at(slots) = static_cast<float>(extended_035);        // original005e4586
            const volatile long double extended_036 = 1.0L;            // original005e4589
            call_one = static_cast<float>(extended_036);               // original005e458b
            const volatile long double extended_037 =
                static_cast<long double>(float_at(slots)); // original005e458f
            put_word(saved_output + 8,
                     word_at(reinterpret_cast<uint32_t>(&private_2))); // original005e4592
            call_w = static_cast<float>(extended_037);                 // original005e4593
            const int32_t near_one = FUN_005e3be9(call_w, call_one);   // original005e4596
            if (!near_one) {                                           // original005e459d
                const volatile long double extended_038 = 1.0L;        // original005e459f
                const volatile long double extended_039 =
                    extended_038 / static_cast<long double>(float_at(slots)); // original005e45a1
                const volatile long double extended_040 =
                    static_cast<long double>(extended_039); // original005e45a4
                const volatile long double extended_041 =
                    extended_040 *
                    static_cast<long double>(float_at(output + 0));      // original005e45a6
                float_at(output + 0) = static_cast<float>(extended_041); // original005e45a8
                const volatile long double extended_042 =
                    static_cast<long double>(extended_039); // original005e45aa
                const volatile long double extended_043 =
                    extended_042 *
                    static_cast<long double>(float_at(output + 4));      // original005e45ac
                float_at(output + 4) = static_cast<float>(extended_043); // original005e45af
                const volatile long double extended_044 =
                    extended_039 *
                    static_cast<long double>(float_at(output + 8));      // original005e45b2
                float_at(output + 8) = static_cast<float>(extended_044); // original005e45b5
            }
            input += word_at(slots + 12); // original005e45b8
            output += word_at(slots + 4); // original005e45bb
            remaining = word_at(slots + 20) - 1;
            put_word(slots + 20, remaining); // original005e45be
        } while (remaining);
    }
    return reinterpret_cast<void*>(initial_output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e44f0(void*, uint32_t, const void*,
                                                              uint32_t, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e44f0\n\taddl $4,%esp\n\tretl $24");
}

extern "C" void* recovered_005e4665(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    uint32_t remaining = word_at(slots + 20);
    uint32_t output = word_at(slots);
    put_word(slots, output);
    if (remaining) {
        const uint32_t matrix = word_at(slots + 16);
        uint32_t input = word_at(slots + 8);
        do {
            volatile float private_0;
            volatile float private_1;
            volatile float private_2;
            const volatile long double extended_000 =
                static_cast<long double>(float_at(matrix + 16)); // original005e4683
            const uint32_t saved_output = output;                // original005e4686
            const volatile long double extended_001 =
                extended_000 * static_cast<long double>(float_at(input + 4)); // original005e4688
            output += word_at(slots + 4);                                     // original005e468b
            const volatile long double extended_002 =
                static_cast<long double>(float_at(matrix + 32)); // original005e468e
            const volatile long double extended_003 =
                extended_002 * static_cast<long double>(float_at(input + 8)); // original005e4694
            const volatile long double extended_004 =
                extended_001 + extended_003; // original005e4697
            const volatile long double extended_005 =
                static_cast<long double>(float_at(input + 0)); // original005e4699
            const volatile long double extended_006 =
                extended_005 * static_cast<long double>(float_at(matrix + 0)); // original005e469b
            const volatile long double extended_007 =
                extended_004 + extended_006;              // original005e469d
            private_0 = static_cast<float>(extended_007); // original005e469f
            const volatile long double extended_008 =
                static_cast<long double>(float_at(matrix + 4)); // original005e46a2
            const volatile long double extended_009 =
                extended_008 * static_cast<long double>(float_at(input + 0)); // original005e46a5
            const volatile long double extended_010 =
                static_cast<long double>(float_at(matrix + 20)); // original005e46a7
            const volatile long double extended_011 =
                extended_010 * static_cast<long double>(float_at(input + 4)); // original005e46aa
            const volatile long double extended_012 =
                extended_009 + extended_011; // original005e46ad
            const volatile long double extended_013 =
                static_cast<long double>(float_at(matrix + 36)); // original005e46af
            const volatile long double extended_014 =
                extended_013 * static_cast<long double>(float_at(input + 8)); // original005e46b2
            const volatile long double extended_015 =
                extended_012 + extended_014;              // original005e46b5
            private_1 = static_cast<float>(extended_015); // original005e46b7
            const volatile long double extended_016 =
                static_cast<long double>(float_at(input + 8)); // original005e46ba
            const volatile long double extended_017 =
                extended_016 * static_cast<long double>(float_at(matrix + 40)); // original005e46bd
            const volatile long double extended_018 =
                static_cast<long double>(float_at(input + 0)); // original005e46c0
            const volatile long double extended_019 =
                extended_018 * static_cast<long double>(float_at(matrix + 8)); // original005e46c2
            const volatile long double extended_020 =
                extended_017 + extended_019; // original005e46c5
            const volatile long double extended_021 =
                static_cast<long double>(float_at(input + 4)); // original005e46c7
            input += word_at(slots + 12);                      // original005e46ca
            --remaining;                                       // original005e46cd
            const volatile long double extended_022 =
                extended_021 * static_cast<long double>(float_at(matrix + 24)); // original005e46ce
            const volatile long double extended_023 =
                extended_020 + extended_022;              // original005e46d1
            private_2 = static_cast<float>(extended_023); // original005e46d3
            put_word(saved_output + 0,
                     word_at(reinterpret_cast<uint32_t>(&private_0))); // original005e46d6
            put_word(saved_output + 4,
                     word_at(reinterpret_cast<uint32_t>(&private_1))); // original005e46d7
            put_word(saved_output + 8,
                     word_at(reinterpret_cast<uint32_t>(&private_2))); // original005e46d8
        } while (remaining);
    }
    return reinterpret_cast<void*>(word_at(slots));
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e4665(void*, uint32_t, const void*,
                                                              uint32_t, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e4665\n\taddl $4,%esp\n\tretl $24");
}

extern "C" void* recovered_005e4bec(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    uint32_t remaining = word_at(slots + 20);
    uint32_t output = word_at(slots);
    put_word(slots, output);
    if (remaining) {
        const uint32_t matrix = word_at(slots + 16);
        uint32_t input = word_at(slots + 8);
        do {
            volatile float private_0;
            volatile float private_1;
            volatile float private_2;
            volatile float private_3;
            const volatile long double extended_000 =
                static_cast<long double>(float_at(matrix + 16)); // original005e4c0e
            const uint32_t saved_output = output;                // original005e4c11
            const volatile long double extended_001 =
                extended_000 * static_cast<long double>(float_at(input + 4)); // original005e4c13
            output += word_at(slots + 4);                                     // original005e4c16
            const volatile long double extended_002 =
                static_cast<long double>(float_at(matrix + 32)); // original005e4c19
            const volatile long double extended_003 =
                extended_002 * static_cast<long double>(float_at(input + 8)); // original005e4c1f
            const volatile long double extended_004 =
                extended_001 + extended_003; // original005e4c22
            const volatile long double extended_005 =
                static_cast<long double>(float_at(input + 12)); // original005e4c24
            const volatile long double extended_006 =
                extended_005 * static_cast<long double>(float_at(matrix + 48)); // original005e4c27
            const volatile long double extended_007 =
                extended_004 + extended_006; // original005e4c2a
            const volatile long double extended_008 =
                static_cast<long double>(float_at(input + 0)); // original005e4c2c
            const volatile long double extended_009 =
                extended_008 * static_cast<long double>(float_at(matrix + 0)); // original005e4c2e
            const volatile long double extended_010 =
                extended_007 + extended_009;              // original005e4c30
            private_0 = static_cast<float>(extended_010); // original005e4c32
            const volatile long double extended_011 =
                static_cast<long double>(float_at(matrix + 20)); // original005e4c35
            const volatile long double extended_012 =
                extended_011 * static_cast<long double>(float_at(input + 4)); // original005e4c38
            const volatile long double extended_013 =
                static_cast<long double>(float_at(matrix + 52)); // original005e4c3b
            const volatile long double extended_014 =
                extended_013 * static_cast<long double>(float_at(input + 12)); // original005e4c3e
            const volatile long double extended_015 =
                extended_012 + extended_014; // original005e4c41
            const volatile long double extended_016 =
                static_cast<long double>(float_at(matrix + 36)); // original005e4c43
            const volatile long double extended_017 =
                extended_016 * static_cast<long double>(float_at(input + 8)); // original005e4c46
            const volatile long double extended_018 =
                extended_015 + extended_017; // original005e4c49
            const volatile long double extended_019 =
                static_cast<long double>(float_at(input + 0)); // original005e4c4b
            const volatile long double extended_020 =
                extended_019 * static_cast<long double>(float_at(matrix + 4)); // original005e4c4d
            const volatile long double extended_021 =
                extended_018 + extended_020;              // original005e4c50
            private_1 = static_cast<float>(extended_021); // original005e4c52
            const volatile long double extended_022 =
                static_cast<long double>(float_at(matrix + 8)); // original005e4c55
            const volatile long double extended_023 =
                extended_022 * static_cast<long double>(float_at(input + 0)); // original005e4c58
            const volatile long double extended_024 =
                static_cast<long double>(float_at(matrix + 24)); // original005e4c5a
            const volatile long double extended_025 =
                extended_024 * static_cast<long double>(float_at(input + 4)); // original005e4c5d
            const volatile long double extended_026 =
                extended_023 + extended_025; // original005e4c60
            const volatile long double extended_027 =
                static_cast<long double>(float_at(matrix + 40)); // original005e4c62
            const volatile long double extended_028 =
                extended_027 * static_cast<long double>(float_at(input + 8)); // original005e4c65
            const volatile long double extended_029 =
                extended_026 + extended_028; // original005e4c68
            const volatile long double extended_030 =
                static_cast<long double>(float_at(input + 12)); // original005e4c6a
            const volatile long double extended_031 =
                extended_030 * static_cast<long double>(float_at(matrix + 56)); // original005e4c6d
            const volatile long double extended_032 =
                extended_029 + extended_031;              // original005e4c70
            private_2 = static_cast<float>(extended_032); // original005e4c72
            const volatile long double extended_033 =
                static_cast<long double>(float_at(input + 12)); // original005e4c75
            const volatile long double extended_034 =
                extended_033 * static_cast<long double>(float_at(matrix + 60)); // original005e4c78
            const volatile long double extended_035 =
                static_cast<long double>(float_at(matrix + 12)); // original005e4c7b
            const volatile long double extended_036 =
                extended_035 * static_cast<long double>(float_at(input + 0)); // original005e4c7e
            const volatile long double extended_037 =
                extended_034 + extended_036; // original005e4c80
            const volatile long double extended_038 =
                static_cast<long double>(float_at(matrix + 28)); // original005e4c82
            const volatile long double extended_039 =
                extended_038 * static_cast<long double>(float_at(input + 4)); // original005e4c85
            const volatile long double extended_040 =
                extended_037 + extended_039; // original005e4c88
            const volatile long double extended_041 =
                static_cast<long double>(float_at(matrix + 44)); // original005e4c8a
            const volatile long double extended_042 =
                extended_041 * static_cast<long double>(float_at(input + 8)); // original005e4c8d
            input += word_at(slots + 12);                                     // original005e4c90
            --remaining;                                                      // original005e4c93
            const volatile long double extended_043 =
                extended_040 + extended_042;              // original005e4c94
            private_3 = static_cast<float>(extended_043); // original005e4c96
            put_word(saved_output + 0,
                     word_at(reinterpret_cast<uint32_t>(&private_0))); // original005e4c99
            put_word(saved_output + 4,
                     word_at(reinterpret_cast<uint32_t>(&private_1))); // original005e4c9a
            put_word(saved_output + 8,
                     word_at(reinterpret_cast<uint32_t>(&private_2))); // original005e4c9b
            put_word(saved_output + 12,
                     word_at(reinterpret_cast<uint32_t>(&private_3))); // original005e4c9c
        } while (remaining);
    }
    return reinterpret_cast<void*>(word_at(slots));
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e4bec(void*, uint32_t, const void*,
                                                              uint32_t, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e4bec\n\taddl $4,%esp\n\tretl $24");
}
