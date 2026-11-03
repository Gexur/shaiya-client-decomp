#include "security.h"
extern "C" {
void fun_005dc223(int32_t failure_kind, const void* context);
__declspec(dllimport) void __attribute__((stdcall)) ExitProcess(uint32_t status);
}
// The original catches exceptions from the real reporting dependency, then
// terminates. No replacement reporter or successful failure result is supplied.
extern "C" [[noreturn]] void fun_005d0ec9() {
    __try {
        fun_005dc223(1, nullptr);
    } __except (1) {
    }
    ExitProcess(3);
    __asm__ volatile("int3");
    __builtin_unreachable();
}
