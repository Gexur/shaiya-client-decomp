#include "graphics/render_quaternion_logarithm.h"
#include "core/x87_acos.h"
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
uint16_t comparison(long double value) {
    const float one = 1.0f;
    uint16_t status;
    __asm__ volatile("fcomps %2\n\tfnstsw %%ax"
                     : "=a"(status)
                     : "t"(value), "m"(one)
                     : "st", "memory", "cc");
    return status;
}
long double arccosine(long double value) {
    // Original6c17 invokes actual private ST0 acos; there are no C stack inputs.
    __asm__ volatile("calll _FUN_005ce5f0"
                     : "+t"(value)::"eax", "ecx", "edx", "cc", "memory", "st(1)", "st(2)");
    return value;
}
long double sine(long double value) {
    __asm__ volatile("fsin" : "+t"(value)::"memory");
    return value;
}
} // namespace
// Complete original5e6bfa..5e6c77. The original parity test enters acos only
// for ordered w<1; its genuine domain-error machinery also handles w<-1.
extern "C" void* recovered_005e6bfa(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments), input = word(slots + 4);
    const volatile long double w = static_cast<long double>(f32(input + 12));
    const uint16_t status = comparison(w);
    u32 output;
    bool scaled = false;
    volatile float sine_single = 0.0f;
    if ((status & 0x500) == 0x100) {
        const volatile long double fresh_w = static_cast<long double>(f32(input + 12));
        const volatile long double radians = arccosine(fresh_w);
        f32(slots + 4) = static_cast<float>(radians); // actual6c1c FST retains80-bit angle
        const volatile long double sine_angle = sine(radians);
        sine_single = static_cast<float>(sine_angle);
        const float zero = 0.0f;
        const int32_t near = FUN_005e3be9(sine_single, zero);
        output = word(slots);
        scaled = near == 0;
    } else
        output = word(slots);
    if (scaled) {
        const volatile long double rounded_angle = static_cast<long double>(f32(slots + 4));
        const volatile long double ratio = rounded_angle / static_cast<long double>(sine_single);
        const volatile long double x = ratio * static_cast<long double>(f32(input));
        f32(output) = static_cast<float>(x);
        const volatile long double y = ratio * static_cast<long double>(f32(input + 4));
        f32(output + 4) = static_cast<float>(y);
        const volatile long double z = ratio * static_cast<long double>(f32(input + 8));
        f32(output + 8) = static_cast<float>(z);
    } else {
        // First component is really FLD/FSTP, while the next two are raw MOVs.
        const volatile long double x = static_cast<long double>(f32(input));
        f32(output) = static_cast<float>(x);
        put(output + 4, word(input + 4));
        put(output + 8, word(input + 8));
    }
    f32(output + 12) = 0.0f;
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6bfa(void*, const void*) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e6bfa\n\taddl $4,%esp\n\tretl $8");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6be1(void*, const void*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+224");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6bf4(void*, const void*) {
    __asm__ volatile("jmpl *_dat_0070f370+224");
}
