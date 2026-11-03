#include "graphics/render_transform2_arrays.h"
#include "graphics/render_vector.h"
namespace {
inline uint32_t word(uint32_t p) {
    uint32_t v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
inline void put(uint32_t p, uint32_t v) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(v) : "memory");
}
struct __attribute__((packed, may_alias)) FloatWord {
    float value;
};
inline volatile float& f32(uint32_t p) {
    return reinterpret_cast<volatile FloatWord*>(p)->value;
}
} // namespace
extern "C" void* recovered_005e7730(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    uint32_t remaining = word(slots + 20);
    uint32_t output = word(slots);
    put(slots, output);
    if (remaining) {
        const uint32_t matrix = word(slots + 16);
        uint32_t input = word(slots + 8);
        do {
            volatile float private_0;
            volatile float private_1;
            volatile float private_2;
            volatile float private_3;
            const volatile long double extended_000 =
                static_cast<long double>(f32(matrix + 16)); // original005e774e
            const uint32_t saved_output = output;           // original005e7751
            const volatile long double extended_001 =
                extended_000 * static_cast<long double>(f32(input + 4)); // original005e7753
            output += word(slots + 4);                                   // original005e7756
            const volatile long double extended_002 =
                static_cast<long double>(f32(input + 0)); // original005e7759
            const volatile long double extended_003 =
                extended_002 * static_cast<long double>(f32(matrix + 0)); // original005e775e
            const volatile long double extended_004 =
                extended_001 + extended_003; // original005e7760
            const volatile long double extended_005 =
                extended_004 + static_cast<long double>(f32(matrix + 48)); // original005e7762
            private_0 = static_cast<float>(extended_005);                  // original005e7765
            const volatile long double extended_006 =
                static_cast<long double>(f32(matrix + 4)); // original005e7768
            const volatile long double extended_007 =
                extended_006 * static_cast<long double>(f32(input + 0)); // original005e776b
            const volatile long double extended_008 =
                static_cast<long double>(f32(matrix + 20)); // original005e776d
            const volatile long double extended_009 =
                extended_008 * static_cast<long double>(f32(input + 4)); // original005e7770
            const volatile long double extended_010 =
                extended_007 + extended_009; // original005e7773
            const volatile long double extended_011 =
                extended_010 + static_cast<long double>(f32(matrix + 52)); // original005e7775
            private_1 = static_cast<float>(extended_011);                  // original005e7778
            const volatile long double extended_012 =
                static_cast<long double>(f32(matrix + 8)); // original005e777b
            const volatile long double extended_013 =
                extended_012 * static_cast<long double>(f32(input + 0)); // original005e777e
            const volatile long double extended_014 =
                static_cast<long double>(f32(matrix + 24)); // original005e7780
            const volatile long double extended_015 =
                extended_014 * static_cast<long double>(f32(input + 4)); // original005e7783
            const volatile long double extended_016 =
                extended_013 + extended_015; // original005e7786
            const volatile long double extended_017 =
                extended_016 + static_cast<long double>(f32(matrix + 56)); // original005e7788
            private_2 = static_cast<float>(extended_017);                  // original005e778b
            const volatile long double extended_018 =
                static_cast<long double>(f32(input + 0)); // original005e778e
            const volatile long double extended_019 =
                extended_018 * static_cast<long double>(f32(matrix + 12)); // original005e7790
            const volatile long double extended_020 =
                static_cast<long double>(f32(input + 4)); // original005e7793
            input += word(slots + 12);                    // original005e7796
            --remaining;                                  // original005e7799
            const volatile long double extended_021 =
                extended_020 * static_cast<long double>(f32(matrix + 28)); // original005e779a
            const volatile long double extended_022 =
                extended_019 + extended_021; // original005e779d
            const volatile long double extended_023 =
                extended_022 + static_cast<long double>(f32(matrix + 60));       // original005e779f
            private_3 = static_cast<float>(extended_023);                        // original005e77a2
            put(saved_output + 0, word(reinterpret_cast<uint32_t>(&private_0))); // original005e77a5
            put(saved_output + 4, word(reinterpret_cast<uint32_t>(&private_1))); // original005e77a6
            put(saved_output + 8, word(reinterpret_cast<uint32_t>(&private_2))); // original005e77a7
            put(saved_output + 12,
                word(reinterpret_cast<uint32_t>(&private_3))); // original005e77a8
        } while (remaining);
    }
    return reinterpret_cast<void*>(word(slots));
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e7730(void*, uint32_t, const void*,
                                                              uint32_t, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e7730\n\taddl $4,%esp\n\tretl $24");
}

extern "C" void* recovered_005e7834(uint32_t* arguments) {
    const uint32_t slots = reinterpret_cast<uint32_t>(arguments);
    uint32_t output = word(slots);
    uint32_t remaining = word(slots + 20);
    const uint32_t initial_output = output;
    if (remaining) {
        const uint32_t matrix = word(slots + 16);
        uint32_t input = word(slots + 8);
        do {
            volatile float private_0;
            volatile float private_1;
            volatile float call_w, call_one;
            const volatile long double extended_000 =
                static_cast<long double>(f32(matrix + 16)); // original005e7851
            const volatile long double extended_001 =
                extended_000 * static_cast<long double>(f32(input + 4)); // original005e7855
            const volatile long double extended_002 =
                static_cast<long double>(f32(input + 0)); // original005e7859
            const volatile long double extended_003 =
                extended_002 * static_cast<long double>(f32(matrix + 0)); // original005e785b
            const volatile long double extended_004 =
                extended_001 + extended_003; // original005e785d
            const volatile long double extended_005 =
                extended_004 + static_cast<long double>(f32(matrix + 48));       // original005e785f
            private_0 = static_cast<float>(extended_005);                        // original005e7862
            const uint32_t raw_x = word(reinterpret_cast<uint32_t>(&private_0)); // original005e7865
            const volatile long double extended_006 =
                static_cast<long double>(f32(matrix + 4)); // original005e7868
            const volatile long double extended_007 =
                extended_006 * static_cast<long double>(f32(input + 0)); // original005e786b
            const volatile long double extended_008 =
                static_cast<long double>(f32(matrix + 20)); // original005e786d
            const volatile long double extended_009 =
                extended_008 * static_cast<long double>(f32(input + 4)); // original005e7870
            const volatile long double extended_010 =
                extended_007 + extended_009; // original005e7873
            const volatile long double extended_011 =
                extended_010 + static_cast<long double>(f32(matrix + 52)); // original005e7875
            private_1 = static_cast<float>(extended_011);                  // original005e7878
            const volatile long double extended_012 =
                static_cast<long double>(f32(matrix + 12)); // original005e787b
            const volatile long double extended_013 =
                extended_012 * static_cast<long double>(f32(input + 0)); // original005e787e
            const volatile long double extended_014 =
                static_cast<long double>(f32(matrix + 28)); // original005e7880
            const volatile long double extended_015 =
                extended_014 * static_cast<long double>(f32(input + 4)); // original005e7883
            const volatile long double extended_016 =
                extended_013 + extended_015; // original005e7886
            const volatile long double extended_017 =
                extended_016 + static_cast<long double>(f32(matrix + 60));       // original005e7888
            put(output, raw_x);                                                  // original005e788b
            const uint32_t raw_y = word(reinterpret_cast<uint32_t>(&private_1)); // original005e788d
            put(output + 4, raw_y);                                              // original005e7890
            f32(slots) = static_cast<float>(extended_017);                       // original005e7893
            const volatile long double extended_018 = 1.0L;                      // original005e7896
            call_one = static_cast<float>(extended_018);                         // original005e7898
            const volatile long double extended_019 =
                static_cast<long double>(f32(slots));                // original005e789c
            call_w = static_cast<float>(extended_019);               // original005e789f
            const int32_t near_one = FUN_005e3be9(call_w, call_one); // original005e78a2
            if (!near_one) {                                         // original005e78a9
                const volatile long double extended_020 = 1.0L;      // original005e78ab
                const volatile long double extended_021 =
                    extended_020 / static_cast<long double>(f32(slots)); // original005e78ad
                const volatile long double extended_022 =
                    static_cast<long double>(extended_021); // original005e78b0
                const volatile long double extended_023 =
                    extended_022 * static_cast<long double>(f32(output + 0)); // original005e78b2
                f32(output + 0) = static_cast<float>(extended_023);           // original005e78b4
                const volatile long double extended_024 =
                    extended_021 * static_cast<long double>(f32(output + 4)); // original005e78b6
                f32(output + 4) = static_cast<float>(extended_024);           // original005e78b9
            }
            input += word(slots + 12); // original005e78bc
            output += word(slots + 4); // original005e78bf
            --remaining;               // original005e78c2
        } while (remaining);
    }
    return reinterpret_cast<void*>(initial_output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e7834(void*, uint32_t, const void*,
                                                              uint32_t, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e7834\n\taddl $4,%esp\n\tretl $24");
}
