#include "purecall.h"
#include "runtime/runtime_error.h"

extern "C" OriginalPureCallHandler dat_0224ee2c = nullptr;

extern "C" uint32_t fun_005ce71d() {
    OriginalPureCallHandler callback = dat_0224ee2c;
    if (callback != nullptr)
        callback();
    uint32_t result;
    // Exact original5ce728..5ce730 call contract. The real reporter is void
    // in C++, but the original forwards its residual EAX on a returning
    // runtime-exit callback. This architectural bridge supplies no reporter
    // body, exit behavior, or invented constant return value.
    __asm__ volatile("pushl $25\n\tcalll _fun_005d098b\n\tpopl %%ecx"
                     : "=a"(result)::"ecx", "edx", "memory", "cc");
    return result;
}
extern "C" uint32_t _purecall() __attribute__((alias("fun_005ce71d")));
