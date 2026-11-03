#include "cinit.h"
#include "exit_registry.h"

extern "C" {
struct OriginalFileTime {
    uint32_t low, high;
};
__declspec(dllimport) void __attribute__((stdcall)) GetSystemTimeAsFileTime(OriginalFileTime*);
uint64_t dat_0224ee48 = 0;
}

extern "C" int32_t fun_005d15a1() {
    OriginalFileTime time;
    GetSystemTimeAsFileTime(&time);
    dat_0224ee48 = (uint64_t(time.high) << 32) + time.low;
    return 0;
}
extern "C" void fun_005d672e() {
    // Original5d673a initializes the cursor to6fa3f0, and5d6741 compares it
    // against that same6fa3f0. Its unsigned JAE exits before any callback.
}
extern "C" void fun_005d6772() {
    // Original5d677e/5d6785 similarly use identical begin/end6fa3f8, so no
    // termination callback is reachable. This is an observed empty interval.
}
extern "C" int32_t fun_005cdff3(int32_t precision) {
    OriginalFloatingInitializer floating = dat_0070e13c;
    if (floating != nullptr)
        floating(precision);
    int32_t result = 0;
    for (uint32_t index = 0; index < 7; ++index) {
        if (result != 0)
            return result;
        OriginalCInitializer callback = dat_007084e4[index];
        if (callback != nullptr)
            result = callback();
    }
    if (result != 0)
        return result;
    (void)fun_005ccf60(fun_005d6772);
    for (uint32_t index = 0; index < 312; ++index) {
        OriginalCppInitializer callback = dat_00708000[index];
        if (callback != nullptr)
            callback();
    }
    return 0;
}
