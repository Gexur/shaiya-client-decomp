#include "graphics/render_plane_intersect.h"
#include "core/float_classify.h"
namespace {
using u32 = uint32_t;
u32 word(u32 p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
struct __attribute__((packed, may_alias)) FloatWord {
    float value;
};
volatile float& f32(u32 p) {
    return reinterpret_cast<volatile FloatWord*>(p)->value;
}
bool nonzero_or_unordered(const volatile long double& value) {
    uint16_t status;
    __asm__ volatile("fldz\n\tfldt %1\n\tfucompp\n\tfnstsw %0"
                     : "=a"(status)
                     : "m"(value)
                     : "st", "memory");
    const u32 flags = (status >> 8) & 0x44;
    return flags == 0 || flags == 0x44;
}
} // namespace
extern "C" void* recovered_005e705d(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments);
    volatile double call_t;
    const u32 plane = word(slots + 4); // original005e7062
    const volatile long double extended_000 =
        static_cast<long double>(f32(plane + 0)); // original005e7065
    const u32 start = word(slots + 8);            // original005e7068
    const volatile long double extended_001 =
        extended_000 * static_cast<long double>(f32(start + 0)); // original005e706b
    const volatile long double extended_002 =
        static_cast<long double>(f32(plane + 4)); // original005e706e
    const u32 end = word(slots + 12);             // original005e7071
    const volatile long double extended_003 =
        extended_002 * static_cast<long double>(f32(start + 4)); // original005e7074
    const volatile long double extended_004 =
        static_cast<long double>(f32(start + 8)); // original005e7077
    const volatile long double extended_005 =
        extended_004 * static_cast<long double>(f32(plane + 8));           // original005e707a
    const volatile long double extended_006 = extended_003 + extended_005; // original005e707d
    const volatile long double extended_007 =
        extended_006 + static_cast<long double>(extended_001); // original005e707f
    const volatile long double extended_008 =
        static_cast<long double>(f32(plane + 0)); // original005e7081
    const volatile long double extended_009 =
        extended_008 * static_cast<long double>(f32(end + 0)); // original005e7083
    const volatile long double extended_010 =
        static_cast<long double>(f32(end + 8)); // original005e7085
    const volatile long double extended_011 =
        extended_010 * static_cast<long double>(f32(plane + 8));           // original005e7088
    const volatile long double extended_012 = extended_009 + extended_011; // original005e708b
    const volatile long double extended_013 =
        static_cast<long double>(f32(plane + 4)); // original005e708d
    const volatile long double extended_014 =
        extended_013 * static_cast<long double>(f32(end + 4));             // original005e7090
    const volatile long double extended_015 = extended_012 + extended_014; // original005e7093
    const volatile long double extended_016 = extended_007 - extended_015; // original005e7095
    const bool nonzero = nonzero_or_unordered(extended_016);
    if (!nonzero)
        return nullptr; // original005e7097..70ac
    const volatile long double extended_017 =
        static_cast<long double>(f32(plane + 4)); // original005e70ae
    const volatile long double extended_018 =
        extended_017 * static_cast<long double>(f32(start + 4)); // original005e70b2
    const volatile long double extended_019 =
        static_cast<long double>(f32(start + 8)); // original005e70b6
    const volatile long double extended_020 =
        extended_019 * static_cast<long double>(f32(plane + 8));           // original005e70b9
    const volatile long double extended_021 = extended_018 + extended_020; // original005e70bc
    const volatile long double extended_022 =
        extended_021 + static_cast<long double>(f32(plane + 12)); // original005e70be
    const volatile long double extended_023 =
        extended_022 + static_cast<long double>(extended_001); // original005e70c1
    const volatile long double extended_024 =
        extended_023 / static_cast<long double>(extended_016); // original005e70c3
    f32(slots + 4) = static_cast<float>(extended_024);         // original005e70c5
    const volatile long double extended_025 =
        static_cast<long double>(f32(slots + 4)); // original005e70cc
    call_t = static_cast<double>(extended_025);   // original005e70cf
    const int32_t finite = FUN_005ced05(call_t);  // original005e70d2
    if (!finite)
        return nullptr; // original005e70db
    const volatile long double extended_026 =
        static_cast<long double>(f32(end + 0)); // original005e70e1
    const u32 output = word(slots);             // original005e70e3
    const volatile long double extended_027 =
        extended_026 - static_cast<long double>(f32(start + 0)); // original005e70e6
    const volatile long double extended_028 =
        extended_027 * static_cast<long double>(f32(slots + 4)); // original005e70e8
    const volatile long double extended_029 =
        extended_028 + static_cast<long double>(f32(start + 0)); // original005e70eb
    f32(output + 0) = static_cast<float>(extended_029);          // original005e70ed
    const volatile long double extended_030 =
        static_cast<long double>(f32(end + 4)); // original005e70ef
    const volatile long double extended_031 =
        extended_030 - static_cast<long double>(f32(start + 4)); // original005e70f2
    const volatile long double extended_032 =
        extended_031 * static_cast<long double>(f32(slots + 4)); // original005e70f5
    const volatile long double extended_033 =
        extended_032 + static_cast<long double>(f32(start + 4)); // original005e70f8
    f32(output + 4) = static_cast<float>(extended_033);          // original005e70fb
    const volatile long double extended_034 =
        static_cast<long double>(f32(end + 8)); // original005e70fe
    const volatile long double extended_035 =
        extended_034 - static_cast<long double>(f32(start + 8)); // original005e7101
    const volatile long double extended_036 =
        extended_035 * static_cast<long double>(f32(slots + 4)); // original005e7104
    const volatile long double extended_037 =
        extended_036 + static_cast<long double>(f32(start + 8)); // original005e7107
    f32(output + 8) = static_cast<float>(extended_037);          // original005e710a
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e705d(void*, const void*, const void*,
                                                              const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e705d\n\taddl $4,%esp\n\tretl $16");
}
