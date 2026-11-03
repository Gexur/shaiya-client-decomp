#include "graphics/render_quaternion_interpolation.h"
#include "startup/math_dispatch_state.h"
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
uint16_t compare(long double value, const float& bound) {
    uint16_t status;
    __asm__ volatile("fcoms %2\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "t"(value), "m"(bound)
                     : "cc", "memory");
    return status;
}
long double root(long double value) {
    __asm__ volatile("fsqrt" : "+t"(value)::"memory");
    return value;
}
long double sine(long double value) {
    __asm__ volatile("fsin" : "+t"(value)::"memory");
    return value;
}
long double angle(long double y, long double x) {
    long double result;
    __asm__ volatile("fpatan" : "=t"(result) : "0"(x), "u"(y) : "st(1)", "memory");
    return result;
}
} // namespace
// Complete original5e6d56..5e6e3b. Every named extended operation, actual F32
// argument write and branch comes from that instruction stream. No host math
// or conventional quaternion formula supplies these weights or their order.
extern "C" void* recovered_005e6d56(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments);
    const u32 first = word(slots + 4); // 6d5c
    const volatile long double one_minus_t =
        1.0L - static_cast<long double>(f32(slots + 12)); // 6d5f/61
    const u32 second = word(slots + 8);                   // 6d64
    const volatile long double x0 = static_cast<long double>(f32(first));
    const volatile long double xx = x0 * static_cast<long double>(f32(second));
    const volatile long double z1 = static_cast<long double>(f32(second + 8));
    const volatile long double zz = z1 * static_cast<long double>(f32(first + 8));
    const volatile long double xz = xx + zz; // 6d71
    const volatile long double y1 = static_cast<long double>(f32(second + 4));
    const volatile long double yy = y1 * static_cast<long double>(f32(first + 4));
    const volatile long double xyz = xz + yy; // 6d79
    const volatile long double w1 = static_cast<long double>(f32(second + 12));
    const volatile long double ww = w1 * static_cast<long double>(f32(first + 12));
    const volatile long double dot = xyz + ww; // 6d81
    const float zero = 0.0f;                   // ordinary6bb5fc value
    if ((compare(dot, zero) & 0x100) == 0)
        f32(slots + 4) = 1.0f; // 6d83..6d95
    else
        put(slots + 4, 0xbf800000u); // actual6d97 integer write
    const volatile long double sign = static_cast<long double>(f32(slots + 4));
    const volatile long double positive_dot = sign * dot; // 6d9e/6da1
    f32(slots + 8) = static_cast<float>(positive_dot);    // FST keeps extended value
    const volatile long double separation = 1.0L - positive_dot;
    const float threshold = 0x1p-23f; // exact6bb604 bits34000000
    long double first_weight, second_weight;
    if ((compare(separation, threshold) & 0x4100) == 0) { // 6dac..6db7
        const volatile long double square = positive_dot * positive_dot;
        const volatile long double remaining = 1.0L - square; // 6dbd FSUBR
        const volatile long double sine_angle = root(remaining);
        const volatile long double stored_cosine = static_cast<long double>(f32(slots + 8));
        const volatile long double radians = angle(sine_angle, stored_cosine); // 6dcc
        f32(slots + 8) = static_cast<float>(radians); // actual6dce F32 write
        const volatile long double reciprocal = 1.0L / sine_angle;
        volatile float inverse = static_cast<float>(reciprocal); // originalprivate-4
        const volatile long double a = static_cast<long double>(f32(slots + 8)) * one_minus_t;
        const volatile long double sa = sine(a);
        const volatile long double scaled_a = sa * static_cast<long double>(inverse);
        first_weight = scaled_a;
        const volatile long double theta = static_cast<long double>(f32(slots + 8));
        const volatile long double b = theta * static_cast<long double>(f32(slots + 12));
        const volatile long double sb = sine(b);
        const volatile long double scaled_b = sb * static_cast<long double>(inverse);
        second_weight = scaled_b;
    } else {
        first_weight = one_minus_t;
        second_weight = static_cast<long double>(f32(slots + 12)); // fresh6df5 t
    }
    const volatile long double signed_second =
        second_weight * static_cast<long double>(f32(slots + 4)); // 6df8
    const u32 output = word(slots);                               // deferred6dfb output cache
    const volatile long double ax = first_weight * static_cast<long double>(f32(first));
    const volatile long double bx = signed_second * static_cast<long double>(f32(second));
    const volatile long double result_x = ax + bx;
    f32(output) = static_cast<float>(result_x);
    const volatile long double by = signed_second * static_cast<long double>(f32(second + 4));
    const volatile long double ay = first_weight * static_cast<long double>(f32(first + 4));
    const volatile long double result_y = by + ay;
    f32(output + 4) = static_cast<float>(result_y);
    const volatile long double bz = signed_second * static_cast<long double>(f32(second + 8));
    const volatile long double az = first_weight * static_cast<long double>(f32(first + 8));
    const volatile long double result_z = bz + az;
    f32(output + 8) = static_cast<float>(result_z);
    const volatile long double bw = signed_second * static_cast<long double>(f32(second + 12));
    const volatile long double aw = first_weight * static_cast<long double>(f32(first + 12));
    const volatile long double result_w = bw + aw;
    f32(output + 12) = static_cast<float>(result_w);
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6d56(void*, const void*, const void*,
                                                              u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e6d56\n\taddl $4,%esp\n\tretl $16");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6d2a(void*, const void*, const void*,
                                                              u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tflds 20(%ebp)\n\tpushl %ecx\n\tfstps (%esp)\n\tpushl 16(%ebp)\n\tpushl 12(%ebp)\n\tpushl 8(%ebp)\n\tcalll *_dat_0070f370+144\n\tpopl %ebp\n\tretl $16");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6d50(void*, const void*, const void*,
                                                              u32) {
    __asm__ volatile("jmp *_dat_0070f370+144");
}
