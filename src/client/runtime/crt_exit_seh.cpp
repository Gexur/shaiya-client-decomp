#include "crt_exit.h"
#include "cinit.h"
#include "exit_registry.h"
#include "heap.h"

extern "C" {
__declspec(dllimport) void* __attribute__((stdcall)) GetCurrentProcess();
__declspec(dllimport) int32_t __attribute__((stdcall)) TerminateProcess(void*, uint32_t);
}
namespace {
__declspec(noinline) void run_termination(uint32_t status, int32_t quick, int32_t returning) {
    if (dat_0224ee28 == 1)
        TerminateProcess(GetCurrentProcess(), status);
    dat_0224ee24 = 1;
    dat_0224ee20 = static_cast<uint8_t>(returning);
    if (quick == 0) {
        if (dat_0225464c != nullptr) {
            for (;;) {
                const uint32_t next = reinterpret_cast<uint32_t>(dat_02254648) - 4;
                dat_02254648 = reinterpret_cast<OriginalExitCallback*>(next);
                if (next < reinterpret_cast<uint32_t>(dat_0225464c))
                    break;
                OriginalExitCallback callback = *dat_02254648;
                if (callback != nullptr)
                    callback();
            }
        }
        fun_005cdfdb(dat_00708504, dat_00708504 + 3);
    }
    fun_005cdfdb(dat_00708514, dat_00708514 + 2);
}
} // namespace
extern "C" void fun_005ce10c(int32_t returning) {
    if (returning != 0)
        fun_005d64e6(8);
}
extern "C" void fun_005ce05d(uint32_t status, int32_t quick, int32_t returning) {
    fun_005d659b(8);
    __try {
        run_termination(status, quick, returning);
    } __finally {
        fun_005ce10c(returning);
    }
    if (returning == 0) {
        dat_0224ee28 = 1;
        fun_005cdf99(static_cast<int32_t>(status));
    }
}
