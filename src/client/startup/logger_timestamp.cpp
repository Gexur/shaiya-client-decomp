#include "runtime/calendar.h"
#include "startup/time_seed.h"
#include "runtime/runtime_error.h"
extern "C" const char* fun_005c3a00(const char* format) {
    (void)read_unix_time32(&dat_0224eca4);
    const auto* const time = fun_005ce980(reinterpret_cast<const int32_t*>(&dat_0224eca4));
    for (uint32_t index = 0; index < 32; ++index) {
        auto* word = reinterpret_cast<uint32_t*>(dat_0224eca8) + index;
        __asm__ __volatile__("movl $0,(%0)" ::"r"(word) : "memory");
    }
    if (time == nullptr) {
        fun_005cd0f0(dat_0224eca8, "No Time", 7);
        dat_0224eca8[7] = 0;
    } else
        (void)fun_005cf877(dat_0224eca8, 128, format, time);
    return dat_0224eca8;
}
