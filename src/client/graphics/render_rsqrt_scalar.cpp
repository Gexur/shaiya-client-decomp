#include "graphics/render_rsqrt_scalar.h"
#include "graphics/render_rsqrt.h"

namespace {
using u32 = uint32_t;
u32 word(u32 address) {
    u32 value;
    __asm__ volatile("movl (%1),%0" : "=r"(value) : "r"(address) : "memory");
    return value;
}
void begin(const u32& seed, const float* multiplier) {
    __asm__ volatile("flds %0\n\tfmuls %1" ::"m"(seed), "m"(*multiplier) : "st", "memory");
}
void add(const float* addend) {
    __asm__ volatile("fadds %0" ::"m"(*addend) : "st", "memory");
}
void finish(const u32& exponent) {
    __asm__ volatile("fmuls %0" ::"m"(exponent) : "st", "memory");
}
} // namespace

// Complete original0064f3a4..0064f3e9. Integer dataflow is C++; the four
// floating instructions retain the actual x87 precision and live ST0 result.
extern "C" uint32_t recovered_0064f3a4(uint32_t actual_argument) {
    const u32 bits = word(actual_argument);
    const u32 index = (bits >> 15) & 0x1ffu;
    const u32 seed = (bits & 0x00ffffffu) | 0x3f000000u;
    const RsqrtCoefficients* coefficient = dat_00715908 + index;
    begin(seed, &coefficient->multiplier);
    // Original subtraction rereads the real caller slot after FMUL.
    const u32 exponent = ((0xbeffffffu - word(actual_argument)) >> 1) & 0xff800000u;
    add(&coefficient->addend);
    finish(exponent);
    return exponent;
}

// Capture the actual caller word address, preserve the untouched ECX/EDX,
// and retain both machine return channels: EAX exponent bits and 80-bit ST0.
extern "C" __attribute__((naked, stdcall)) long double FUN_0064f3a4(uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %ecx\n\tpushl %edx\n\tpushl %eax\n\tcalll _recovered_0064f3a4\n\taddl $4,%esp\n\tpopl %edx\n\tpopl %ecx\n\tandl $0xff800000,%eax\n\tretl $4");
}
