#include "runtime/fpmath.h"
extern "C" void recovered_movapd_005d7e4f();

// Original5d7e4f..5d7e83 probes an actual SSE2 instruction under __except(1).
// A fault leaves result zero; a successful MOVAPD sets it to one. The source
// keeps the real fault boundary and does not assume OS/CPU SSE2 support.
extern "C" int32_t __cdecl fun_005d7e4f() {
    volatile int32_t result = 0;
    __try {
        // LLVM treats inline asm as nounwind even under asynchronous EH and
        // disables its SEH scope immediately before that asm. An actual call
        // across a TU boundary keeps this real instruction inside the scope.
        recovered_movapd_005d7e4f();
        result = 1;
    } __except (1) {
    }
    return result;
}
