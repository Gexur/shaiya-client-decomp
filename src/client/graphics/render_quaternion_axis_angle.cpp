#include "graphics/render_quaternion_axis_angle.h"
#include "startup/math_dispatch_state.h"
#include "core/x87_acos.h"
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
} // namespace
// Complete original5e6738..5e6770 copy/selection logic. The temporary state is
// discarded before actual acos, restoring its original parent ESP and the
// original EAX/ECX/EDX/ESI inputs. It does not provide a client math result.
extern "C" void prepare_005e6738(const u32* arguments, u32* state) {
    const u32 slots = reinterpret_cast<u32>(arguments), temporary = reinterpret_cast<u32>(state);
    const u32 axis = word(slots + 4), input = word(slots);
    u32 copied = word(temporary + 20);
    if (axis) {
        put(axis, word(input));
        put(axis + 4, word(input + 4));
        copied = word(input + 8);
        put(axis + 8, copied);
    }
    const u32 angle = word(slots + 8);
    put(temporary, input);
    put(temporary + 4, axis);
    put(temporary + 8, angle);
    put(temporary + 12, copied);
    if (angle)
        put(temporary + 16, word(input + 12));
}
extern "C" __attribute__((naked, stdcall)) u32 FUN_005e6738(const void*, void*, float*) {
    // Only the private ST0 call stage stays at original ESP. FADD ST0,ST0 is
    // literal hardware addition, retaining original precision and residual EAX.
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl %esi\n\tsubl $24,%esp\n\tmovl %edx,20(%esp)\n\t"
        "movl %esp,%eax\n\tpushl %eax\n\tleal 8(%ebp),%eax\n\tpushl %eax\n\tcalll _prepare_005e6738\n\taddl $8,%esp\n\t"
        "movl (%esp),%eax\n\tmovl 4(%esp),%ecx\n\tmovl 8(%esp),%esi\n\tmovl 12(%esp),%edx\n\ttestl %esi,%esi\n\tjz 1f\n\t"
        "flds 16(%esp)\n\tleal 24(%esp),%esp\n\tcalll _FUN_005ce5f0\n\tfadd %st(0),%st(0)\n\tfstps (%esi)\n\tjmp 2f\n\t"
        "1: leal 24(%esp),%esp\n\t2: popl %esi\n\tpopl %ebp\n\tretl $12");
}
extern "C" __attribute__((naked, stdcall)) u32 FUN_005e6725(const void*, void*, float*) {
    __asm__ volatile(
        "pushl %ebp\n\tmovl %esp,%ebp\n\tpushl $1\n\tcalll _FUN_005fd1f8@4\n\tpopl %ebp\n\tjmpl *_dat_0070f370+96");
}
