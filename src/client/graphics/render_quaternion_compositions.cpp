#include "graphics/render_quaternion_compositions.h"
#include "graphics/render_quaternion_interpolation.h"
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
u32 rounded_argument(u32 p) {
    float value;
    __asm__ volatile("flds (%1)\n\tfstps %0" : "=m"(value) : "r"(p) : "memory");
    return word(reinterpret_cast<u32>(&value));
}
u32 rounded(long double value) {
    float result;
    __asm__ volatile("fstps %0" : "=m"(result) : "t"(value) : "st", "memory");
    return word(reinterpret_cast<u32>(&result));
}
} // namespace
// Complete original5e6e67..5e6ec0. Three calls to the real slot36 fast entry;
// the two 16-byte intermediate results are private, not replacement math.
extern "C" void* recovered_005e6e67(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments);
    u32 first[4], second[4];
    const u32 t0 = rounded_argument(slots + 20);
    const u32 fourth = word(slots + 16), left = word(slots + 4);
    FUN_005e6d50(first, reinterpret_cast<const void*>(left), reinterpret_cast<const void*>(fourth),
                 t0);
    const u32 t1 = rounded_argument(slots + 20);
    const u32 third = word(slots + 12), right = word(slots + 8);
    FUN_005e6d50(second, reinterpret_cast<const void*>(right), reinterpret_cast<const void*>(third),
                 t1);
    const volatile long double one_minus_t = 1.0L - static_cast<long double>(f32(slots + 20));
    const volatile long double product = one_minus_t * static_cast<long double>(f32(slots + 20));
    const volatile long double doubled = product + product;
    const u32 coefficient = rounded(doubled);
    const u32 output = word(slots);
    FUN_005e6d50(reinterpret_cast<void*>(output), first, second, coefficient);
    return reinterpret_cast<void*>(word(slots));
}
// Complete original5e6f04..5e6f8e. The rounded sum overwrites actual arg4.
// The near-zero branch is the original four interleaved DWORD moves (DF=0).
extern "C" void* recovered_005e6f04(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments);
    u32 first[4], second[4];
    const volatile long double a = static_cast<long double>(f32(slots + 16));
    const volatile long double sum = a + static_cast<long double>(f32(slots + 20));
    f32(slots + 16) = static_cast<float>(sum);
    const float zero = 0.0f;
    volatile float call_sum;
    __asm__ volatile("flds (%1)\n\tfstps %0" : "=m"(call_sum) : "r"(slots + 16) : "memory");
    if (FUN_005e3be9(call_sum, zero) != 0) {
        const u32 input = word(slots + 4);
        if (word(slots) != input) {
            const u32 output = word(slots);
            put(output, word(input));
            put(output + 4, word(input + 4));
            put(output + 8, word(input + 8));
            put(output + 12, word(input + 12));
        }
    } else {
        const u32 t0 = rounded_argument(slots + 16);
        const u32 right = word(slots + 8), left = word(slots + 4);
        FUN_005e6d50(first, reinterpret_cast<const void*>(left),
                     reinterpret_cast<const void*>(right), t0);
        const u32 t1 = rounded_argument(slots + 16);
        const u32 third = word(slots + 12), fresh_left = word(slots + 4);
        FUN_005e6d50(second, reinterpret_cast<const void*>(fresh_left),
                     reinterpret_cast<const void*>(third), t1);
        const volatile long double numerator = static_cast<long double>(f32(slots + 20));
        const volatile long double ratio = numerator / static_cast<long double>(f32(slots + 16));
        const u32 coefficient = rounded(ratio);
        const u32 output = word(slots);
        FUN_005e6d50(reinterpret_cast<void*>(output), first, second, coefficient);
    }
    return reinterpret_cast<void*>(word(slots));
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6e67(void*, const void*, const void*,
                                                              const void*, const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e6e67\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6f04(void*, const void*, const void*,
                                                              const void*, u32, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e6f04\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6e3b(void*, const void*, const void*,
                                                              const void*, const void*, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tflds 28(%ebp)\n\tpushl %ecx\n\tfstps (%esp)\n\tpushl 24(%ebp)\n\tpushl 20(%ebp)\n\tpushl 16(%ebp)\n\tpushl 12(%ebp)\n\tpushl 8(%ebp)\n\tcalll *_dat_0070f370+176\n\tpopl %ebp\n\tretl $24");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e6ed3(void*, const void*, const void*,
                                                              const void*, u32, u32) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tflds 28(%ebp)\n\tpushl %ecx\n\tpushl %ecx\n\tfstps 4(%esp)\n\tflds 24(%ebp)\n\tfstps (%esp)\n\tpushl 20(%ebp)\n\tpushl 16(%ebp)\n\tpushl 12(%ebp)\n\tpushl 8(%ebp)\n\tcalll *_dat_0070f370+148\n\tpopl %ebp\n\tretl $24");
}
