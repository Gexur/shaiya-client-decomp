#include "graphics/render_plane_helpers.h"
#include "graphics/render_vector.h"
extern "C" float* __attribute__((stdcall)) FUN_005e40eb(float*, const float*);
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
const float threshold_min = 0x1p-126f, one = 1.0f;
uint16_t compare(float value) {
    uint16_t status;
    __asm__ volatile("flds %1\n\tfcomps %2\n\tfnstsw %0"
                     : "=a"(status)
                     : "m"(value), "m"(threshold_min)
                     : "st", "memory");
    return status;
}
long double inverse_sqrt(float value) {
    long double result;
    __asm__ volatile("flds %1\n\tfsqrt\n\tfdivrs %2\n\tfstpt %0"
                     : "=m"(result)
                     : "m"(value), "m"(one)
                     : "st", "memory");
    return result;
}
} // namespace
extern "C" void* recovered_005e6fa7(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments), input = word(slots + 4); //6fad
    const volatile long double z = static_cast<long double>(f32(input + 8));     //6fb0
    const volatile long double y = static_cast<long double>(f32(input + 4));     //6fb4
    const volatile long double x = static_cast<long double>(f32(input));         //6fb8
    const volatile long double xx = x * x;                                       //6fba..6fbc
    const volatile long double yy = y * y;                                       //6fbe..6fc0
    const volatile long double xy = xx + yy;                                     //6fc2
    const volatile long double zz = z * z;                                       //6fc4..6fc6
    const volatile long double squared = xy + zz;                                //6fc8
    f32(slots + 4) = static_cast<float>(squared);                                //6fca
    const int32_t near_one = FUN_005e3be9(f32(slots + 4), one);                  //6fd3..6fdf
    if (near_one) {
        const u32 output = word(slots); //6fe8
        if (output != input)
            for (u32 i = 0; i < 4; ++i)
                put(output + i * 4, word(input + i * 4)); //6fed..6ff5
        return reinterpret_cast<void*>(output);
    }
    const uint16_t status = compare(f32(slots + 4)); //6ff9..7004
    const u32 output = word(slots);                  //7007
    if (!(status & 0x4100)) {
        const volatile long double factor = inverse_sqrt(f32(slots + 4));              //700c..7011
        const volatile long double rx = factor * static_cast<long double>(f32(input)); //7017..7019
        f32(output) = static_cast<float>(rx);                                          //701b
        const volatile long double ry =
            factor * static_cast<long double>(f32(input + 4)); //701d..701f
        f32(output + 4) = static_cast<float>(ry);              //7022
        const volatile long double rz =
            factor * static_cast<long double>(f32(input + 8)); //7025..7027
        f32(output + 8) = static_cast<float>(rz);              //702a
        const volatile long double rw = factor * static_cast<long double>(f32(input + 12)); //702d
        f32(output + 12) = static_cast<float>(rw);                                          //7042
    } else {
        f32(output) = 0.0f;
        f32(output + 4) = 0.0f;
        f32(output + 8) = 0.0f;
        f32(output + 12) = 0.0f;
    } //7032..7042
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6fa7(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e6fa7\n\taddl $4,%esp\n\tretl $8");
}

// Complete original5e717a..5e721e per-instruction dataflow.
extern "C" void* recovered_005e717a(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments);
    volatile float difference_x, difference_y, cross_x, cross_y, cross_z;
    const u32 second = word(slots + 8); // original005e7182
    const u32 first = word(slots + 4);  // original005e7186
    const volatile long double extended_000 =
        static_cast<long double>(f32(first + 0)); // original005e7189
    const volatile long double extended_001 =
        extended_000 - static_cast<long double>(f32(second + 0)); // original005e718c
    const volatile long double extended_002 =
        static_cast<long double>(f32(first + 4)); // original005e718f
    const u32 initial_output = word(slots);       // original005e7192
    const volatile long double extended_003 =
        extended_002 - static_cast<long double>(f32(second + 4)); // original005e7195
    const u32 normalized_input = word(slots);                     // original005e7198
    const volatile long double extended_004 =
        static_cast<long double>(f32(first + 8)); // original005e719b
    const volatile long double extended_005 =
        extended_004 - static_cast<long double>(f32(second + 8)); // original005e71a1
    const u32 second_last = word(slots + 12);                     // original005e71a4
    const volatile long double extended_006 =
        static_cast<long double>(f32(first + 0)); // original005e71a7
    const u32 normalized_output = word(slots);    // original005e71a9
    const volatile long double extended_007 =
        extended_006 - static_cast<long double>(f32(second_last + 0)); // original005e71ac
    difference_x = static_cast<float>(extended_007);                   // original005e71ae
    const volatile long double extended_008 =
        static_cast<long double>(f32(first + 4)); // original005e71b1
    const volatile long double extended_009 =
        extended_008 - static_cast<long double>(f32(second_last + 4)); // original005e71b4
    difference_y = static_cast<float>(extended_009);                   // original005e71b7
    const volatile long double extended_010 =
        static_cast<long double>(f32(first + 8)); // original005e71ba
    const volatile long double extended_011 =
        extended_010 - static_cast<long double>(f32(second_last + 8)); // original005e71bd
    const volatile long double extended_012 =
        static_cast<long double>(extended_011); // original005e71c0
    const volatile long double extended_013 =
        extended_012 * static_cast<long double>(extended_003); // original005e71c2
    const volatile long double extended_014 =
        static_cast<long double>(difference_y); // original005e71c4
    const volatile long double extended_015 =
        extended_014 * static_cast<long double>(extended_005);             // original005e71c7
    const volatile long double extended_016 = extended_013 - extended_015; // original005e71c9
    cross_x = static_cast<float>(extended_016);                            // original005e71cb
    const volatile long double extended_017 =
        static_cast<long double>(extended_005); // original005e71ce
    const volatile long double extended_018 =
        extended_017 * static_cast<long double>(difference_x); // original005e71d0
    const volatile long double extended_019 =
        static_cast<long double>(extended_011); // original005e71d3
    const volatile long double extended_020 =
        extended_019 * static_cast<long double>(extended_001);             // original005e71d5
    const volatile long double extended_021 = extended_018 - extended_020; // original005e71d7
    cross_y = static_cast<float>(extended_021);                            // original005e71d9
    const volatile long double extended_022 =
        static_cast<long double>(difference_y); // original005e71e0
    const volatile long double extended_023 =
        extended_022 * static_cast<long double>(extended_001); // original005e71e3
    const volatile long double extended_024 =
        static_cast<long double>(difference_x); // original005e71e5
    const volatile long double extended_025 =
        extended_024 * static_cast<long double>(extended_003);             // original005e71e8
    const volatile long double extended_026 = extended_023 - extended_025; // original005e71ea
    cross_z = static_cast<float>(extended_026);                            // original005e71ec
    put(initial_output + 0, word(reinterpret_cast<u32>(&cross_x)));        // original005e71ef
    put(initial_output + 4, word(reinterpret_cast<u32>(&cross_y)));        // original005e71f0
    put(initial_output + 8, word(reinterpret_cast<u32>(&cross_z)));        // original005e71f5
    FUN_005e40eb(reinterpret_cast<float*>(normalized_output),
                 reinterpret_cast<const float*>(normalized_input)); // original005e71f6
    const u32 output = word(slots);                                 // original005e71fb
    const volatile long double extended_027 =
        static_cast<long double>(f32(output + 4)); // original005e71ff
    const volatile long double extended_028 =
        extended_027 * static_cast<long double>(f32(first + 4)); // original005e7203
    const volatile long double extended_029 =
        static_cast<long double>(f32(output + 8)); // original005e7206
    const volatile long double extended_030 =
        extended_029 * static_cast<long double>(f32(first + 8));           // original005e7209
    const volatile long double extended_031 = extended_028 + extended_030; // original005e720c
    const volatile long double extended_032 =
        static_cast<long double>(f32(output + 0)); // original005e720e
    const volatile long double extended_033 =
        extended_032 * static_cast<long double>(f32(first + 0));           // original005e7210
    const volatile long double extended_034 = extended_031 + extended_033; // original005e7213
    const volatile long double extended_035 = -extended_034;               // original005e7215
    f32(output + 12) = static_cast<float>(extended_035);                   // original005e7217
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e717a(void*, const void*, const void*,
                                                              const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e717a\n\taddl $4,%esp\n\tretl $16");
}
