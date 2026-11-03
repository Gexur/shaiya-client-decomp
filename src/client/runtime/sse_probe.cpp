// Source integration adapter for the actual instruction at original5d7e63.
// This tiny entry exists because LLVM omits SEH protection around inline asm
// inside the caller. It performs the original MOVAPD, never tests a CPU model
// or supplies an assumed success value. Actual faults cross the caller's SEH.
extern "C" __attribute__((naked, noinline)) void recovered_movapd_005d7e4f() {
    __asm__ __volatile__("movapd %xmm1,%xmm0\n\tretl");
}
