#include "graphics/surface/surface_linear_weights.h"
#include "runtime/allocations.h"
namespace {
using u32 = uint32_t;
u32 word(const u32* p) {
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
long double integer(u32 value) {
    long double result;
    __asm__ volatile("fildl %1\n\tfstpt %0" : "=m"(result) : "m"(value) : "st", "memory");
    return result;
}
u32 integer_result(const volatile float& value) {
    u32 result;
    __asm__ volatile("flds %1\n\tfistpl %0" : "=m"(result) : "m"(value) : "st", "memory");
    return result;
}
uint16_t control() {
    uint16_t v;
    __asm__ volatile("fnstcw %0" : "=m"(v));
    return v;
}
void control(uint16_t v) {
    __asm__ volatile("fldcw %0" ::"m"(v) : "memory");
}
// Exact numeric readonly operands6bb60c/6bc860/6bc4dc. These are private
// source literals; no second definition of their original shared storage.
constexpr long double unsigned_offset = 4294967296.0L, half = 0.5L, one = 1.0L;
} // namespace
extern "C" void* recovered_005eea1a(const u32* arguments, u32 source_count, u32 destination_count) {
    void* allocated = fun_005cc96d(destination_count << 4);
    if (!allocated)
        return nullptr;
    volatile long double source = integer(source_count);
    if (source_count & 0x80000000u)
        source = source + unsigned_offset;
    volatile long double destination = integer(destination_count);
    if (destination_count & 0x80000000u)
        destination = destination + unsigned_offset;
    const volatile long double extended_ratio = source / destination;
    const volatile float ratio = static_cast<float>(extended_ratio);
    const uint16_t saved = control();
    control(static_cast<uint16_t>(saved | 0x0c00));
    u32 i = 0, output = reinterpret_cast<uintptr_t>(allocated);
    if (destination_count)
        do {
            volatile long double index = integer(i);
            if (i & 0x80000000u)
                index = index + unsigned_offset;
            const volatile long double shifted = index + half;
            const volatile long double scaled = shifted * static_cast<long double>(ratio);
            const volatile long double positioned = scaled + half;
            const volatile float position = static_cast<float>(positioned);
            u32 high = integer_result(position), low = high - 1;
            const volatile long double high_signed = integer(high);
            const volatile long double endpoint = high_signed + one;
            const volatile long double left = endpoint - static_cast<long double>(position);
            if (low & 0x80000000u)
                low = (0u - static_cast<u32>(word(arguments) != 0)) & (source_count - 1);
            if (high >= source_count)
                high = ~(0u - static_cast<u32>(word(arguments) != 0)) & (source_count - 1);
            f32(output + 4) = static_cast<float>(left);
            put(output, low);
            put(output + 8, high);
            const volatile long double right = one - left;
            output += 16;
            ++i;
            f32(output - 4) = static_cast<float>(right);
        } while (i < destination_count);
    control(saved);
    return allocated;
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005eea1a(uint32_t) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %edi\n\tpushl %esi\n\tpushl %eax\n\tcalll _recovered_005eea1a\n\taddl $12,%esp\n\tretl $4");
}
