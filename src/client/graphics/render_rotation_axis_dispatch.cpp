#include "graphics/render_rotation_axis_dispatch.h"
#include "graphics/render_rotation_axis.h"
#include "startup/math_dispatch_state.h"
namespace {
using u32 = uint32_t;
void* dispatch(const u32* words, u32 slot) {
    FUN_005fd1f8(1);
    u32 angle;
    __asm__ volatile("flds %1\n\tfstps %0"
                     : "=m"(angle)
                     : "m"(*reinterpret_cast<const unsigned char (*)[4]>(words + 1))
                     : "st", "memory");
    u32 output;
    __asm__ volatile("movl (%1),%0" : "=r"(output) : "r"(words) : "memory");
    using Target = decltype(&FUN_005e57d9);
    return reinterpret_cast<Target>(dat_0070f370.entries[slot])(reinterpret_cast<void*>(output),
                                                                angle);
}
} // namespace
extern "C" void* recovered_005e57b3(const u32* words) {
    return dispatch(words, 31);
}
extern "C" void* recovered_005e5855(const u32* words) {
    return dispatch(words, 32);
}
extern "C" void* recovered_005e58f8(const u32* words) {
    return dispatch(words, 33);
}
// Three original initializers copy/round the angle into outgoing storage only.
extern "C" __attribute__((naked, stdcall)) void* FUN_005e57b3(void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e57b3\n\taddl $4,%esp\n\tretl $8");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e5855(void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e5855\n\taddl $4,%esp\n\tretl $8");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e58f8(void*, u32) {
    __asm__ volatile(
        "leal 4(%esp),%eax\n\tpushl %eax\n\tcalll _recovered_005e58f8\n\taddl $4,%esp\n\tretl $8");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e57d3(void*, u32) {
    __asm__ volatile("jmpl *_dat_0070f370+124");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e5875(void*, u32) {
    __asm__ volatile("jmpl *_dat_0070f370+128");
}
extern "C" __attribute__((naked, stdcall)) void* FUN_005e5918(void*, u32) {
    __asm__ volatile("jmpl *_dat_0070f370+132");
}
