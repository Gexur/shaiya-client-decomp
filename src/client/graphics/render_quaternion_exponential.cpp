#include "graphics/render_quaternion_exponential.h"
#include "startup/math_dispatch_state.h"
#include "graphics/render_vector.h"
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
long double root(long double value) {
    __asm__ volatile("fsqrt" : "+t"(value)::"memory");
    return value;
}
void sine_cosine(const volatile float* angle, u32 cosine, u32 sine) {
    __asm__ volatile("flds %0\n\tfsincos\n\tfstps (%1)\n\tfstps (%2)" ::"m"(*angle), "r"(cosine),
                     "r"(sine)
                     : "memory", "st", "st(1)");
}
} // namespace
// Complete original5e6c90..5e6d2a: exact Z/Y/output/X load order, rounded
// private length, actual arg0=out+12 and actual arg1=sine stores are retained.
extern "C" void* recovered_005e6c90(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments);
    const u32 input = word(slots + 4);
    const volatile long double z = static_cast<long double>(f32(input + 8));
    const volatile long double y = static_cast<long double>(f32(input + 4));
    const u32 output = word(slots);
    const volatile long double x = static_cast<long double>(f32(input));
    const u32 cosine_output = output + 12;
    put(slots, cosine_output);
    const volatile long double xx = x * x;
    const volatile long double yy = y * y;
    const volatile long double xy = xx + yy;
    const volatile long double zz = z * z;
    const volatile long double xyz = xy + zz;
    const volatile long double norm = root(xyz);
    volatile float length = static_cast<float>(norm);
    sine_cosine(&length, word(slots), slots + 4); // original6cd0 freshly reloads actual arg0
    const float zero = 0.0f;
    const float sine = f32(slots + 4);
    if (FUN_005e3be9(sine, zero) != 0) {
        if (output != input) {
            put(output, word(input));
            put(output + 4, word(input + 4));
            put(output + 8, word(input + 8));
        }
    } else {
        const volatile long double numerator = static_cast<long double>(f32(slots + 4));
        const volatile long double ratio = numerator / static_cast<long double>(length);
        const volatile long double vx = ratio * static_cast<long double>(f32(input));
        f32(output) = static_cast<float>(vx);
        const volatile long double vy = ratio * static_cast<long double>(f32(input + 4));
        f32(output + 4) = static_cast<float>(vy);
        const volatile long double vz = ratio * static_cast<long double>(f32(input + 8));
        f32(output + 8) = static_cast<float>(vz);
    }
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6c90(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e6c90\n\taddl $4,%esp\n\tretl $8");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6c77(void*, const void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+228");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6c8a(void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+228");
}
