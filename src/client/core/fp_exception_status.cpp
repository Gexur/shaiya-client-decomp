#include "core/fp_exception_support.h"
extern "C" {
extern const X87PowerWords dat_0070ed18 = {UINT64_C(0x8000000000000000), 0x4410};
extern const X87PowerWords dat_0070ed24 = {UINT64_C(0x8000000000000001), 0x3000};
}

// Original005d8961..005d896c returns sign-extended FPU status after WAIT.
extern "C" int32_t __cdecl FUN_005d8961() {
    uint16_t status;
    __asm__ __volatile__("fwait\n\tfnstsw %0" : "=m"(status));
    return static_cast<int16_t>(status);
}
// Original005d896c..005d8978 returns pre-clear status; FNSTSW has no WAIT.
extern "C" int32_t __cdecl FUN_005d896c() {
    uint16_t status;
    __asm__ __volatile__("fnstsw %0\n\tfnclex" : "=m"(status));
    return static_cast<int16_t>(status);
}
// Original005d8978..005d899c. Its uninitialized private upper WORD is never
// consumed: only low16bits reach FLDCW and the sign-extended result.
extern "C" int32_t __cdecl FUN_005d8978(uint32_t value, uint32_t mask) {
    uint16_t previous;
    __asm__ __volatile__("fwait\n\tfnstcw %0" : "=m"(previous));
    const uint16_t next = static_cast<uint16_t>((uint32_t(previous) & ~mask) | (value & mask));
    __asm__ __volatile__("fldcw %0" ::"m"(next));
    return static_cast<int16_t>(previous);
}
// Original005d899c..005d89f2: real x87 operations intentionally raise the
// selected hardware flags/exceptions in this order. No host fenv substitute.
extern "C" __attribute__((naked)) void __cdecl FUN_005d899c(uint32_t) {
    __asm__ __volatile__(
        "pushl %ecx\n\tpushl %ecx\n\tmovb 12(%esp),%cl\n\ttestb $0x1,%cl\n\tje 1f\n\tfldt _dat_0070ed18\n\tfistpl 12(%esp)\n\tfwait\n"
        "1:\n\ttestb $0x8,%cl\n\tje 2f\n\tfwait\n\tfnstsw %ax\n\tfldt _dat_0070ed18\n\tfstpl (%esp)\n\tfwait\n\tfwait\n\tfnstsw %ax\n"
        "2:\n\ttestb $0x10,%cl\n\tje 3f\n\tfldt _dat_0070ed24\n\tfstpl (%esp)\n\tfwait\n"
        // GNU AT&T fdivp emits original DE F1 (Intel FDIVRP ST1,ST0).
        "3:\n\ttestb $0x4,%cl\n\tje 4f\n\tfldz\n\tfld1\n\tfdivp %st(0),%st(1)\n\tfstp %st(0)\n\tfwait\n"
        "4:\n\ttestb $0x20,%cl\n\tje 5f\n\tfldpi\n\tfstpl (%esp)\n\tfwait\n"
        "5:\n\tpopl %ecx\n\tpopl %ecx\n\tretl");
}
