#include "graphics/render_quaternion_axis.h"
#include "graphics/render_dispatch.h"
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
} // namespace
// Complete original5e68e2..5e6940, including both actual incoming-word writes.
// Readonly0.5 at6bc860 is copied as a value, not new pool-storage ownership.
extern "C" void* recovered_005e68e2(u32* arguments) {
    const u32 slots = reinterpret_cast<u32>(arguments), axis = word(slots + 4); //68ea
    float normalized[3];
    FUN_005e40eb(normalized, reinterpret_cast<const float*>(axis));              //68f1
    const volatile long double angle = static_cast<long double>(f32(slots + 8)); //68f6
    const u32 output = word(slots);                                              //68f9
    const volatile long double half_angle = angle * 0.5L;                        //68fc
    f32(slots) = static_cast<float>(half_angle); //690b actual outputword becomes halfangle
    const u32 cosine = output + 12, sine = slots + 4;
    // Original FSINCOS stores F32cosine directly to outputW, then F32sine to
    // the actual incoming axis-pointer word; later products freshly read it.
    __asm__ volatile("flds (%0)\n\tfsincos\n\tfstps (%1)\n\tfstps (%2)" ::"r"(slots), "r"(cosine),
                     "r"(sine)
                     : "st", "st(1)", "memory");
    const volatile long double x = static_cast<long double>(normalized[0]) *
                                   static_cast<long double>(f32(slots + 4)); //6920..23
    f32(output) = static_cast<float>(x);                                     //6928
    const volatile long double y = static_cast<long double>(normalized[1]) *
                                   static_cast<long double>(f32(slots + 4)); //692a..2d
    f32(output + 4) = static_cast<float>(y);                                 //6930
    const volatile long double z = static_cast<long double>(normalized[2]) *
                                   static_cast<long double>(f32(slots + 4)); //6933..36
    f32(output + 8) = static_cast<float>(z);                                 //6939
    return reinterpret_cast<void*>(output);
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e68e2(void*, const void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e68e2\n\taddl $4,%esp\n\tretl $12");
}
// Textual original entry ABI: initialization precedes incoming-word loads;
// copied outgoing angle has its own F32 rounding and actual mutable slot30.
extern "C" __attribute__((naked, stdcall)) void* FUN_005e68bf(void*, const void*, u32) {
    __asm__ volatile(
        "movl %edi,%edi\n\tpushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tflds 16(%ebp)\n\tpushl %ecx\n\tfstps (%esp)\n\tpushl 12(%ebp)\n\tpushl 8(%ebp)\n\tcalll *_dat_0070f370+120\n\tpopl %ebp\n\tretl $12");
}
