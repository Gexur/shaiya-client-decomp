#include "graphics/render_vec2_normal_array.h"
#include "startup/math_dispatch_state.h"
namespace {
using u32 = uint32_t;
u32 word(const void* p) {
    u32 v;
    __asm__ volatile("movl (%1),%0" : "=r"(v) : "r"(p) : "memory");
    return v;
}
u32 word_at(u32 p) {
    return word(reinterpret_cast<const void*>(p));
}
void store(u32 p, u32 value) {
    __asm__ volatile("movl %1,(%0)" ::"r"(p), "r"(value) : "memory");
}
float scalar(u32 p) {
    return *reinterpret_cast<const volatile float*>(p);
}
u32 rounded(long double value) {
    float result = static_cast<float>(value);
    u32 bits;
    __asm__ volatile("movl %1,%0" : "=r"(bits) : "m"(result) : "memory");
    return bits;
}
} // namespace

// Complete original5e4082..5e40d8. Output/count are cached before the zero-count
// decision; input/matrix only afterward. Both y products precede the first store.
extern "C" void* recovered_vec2_normal_array(const uint32_t* arguments) {
    const u32 first_output = word(arguments);
    u32 count = word(arguments + 5);
    if (!count)
        return reinterpret_cast<void*>(first_output);
    const u32 matrix = word(arguments + 4);
    u32 input = word(arguments + 2), output = first_output;
    do {
        const volatile long double a = scalar(matrix + 16);
        const volatile long double ax = a * static_cast<long double>(scalar(input + 4));
        const volatile long double b = scalar(input);
        const volatile long double bx = b * static_cast<long double>(scalar(matrix));
        const u32 x = rounded(ax + bx);
        const volatile long double c = scalar(matrix + 4);
        const volatile long double cy = c * static_cast<long double>(scalar(input));
        const volatile long double d = scalar(matrix + 20);
        const volatile long double dy = d * static_cast<long double>(scalar(input + 4));
        input += word(arguments + 3);
        store(output, x);
        const u32 y = rounded(cy + dy);
        store(output + 4, y);
        output += word(arguments + 1);
    } while (--count);
    return reinterpret_cast<void*>(first_output);
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_005e4082(void*, uint32_t, const void*, uint32_t, const void*, uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_vec2_normal_array\n\taddl $4,%esp\n\tretl $24");
}
extern "C" __attribute__((naked)) void* __attribute__((stdcall))
FUN_005e406f(void*, uint32_t, const void*, uint32_t, const void*, uint32_t) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+248");
}
