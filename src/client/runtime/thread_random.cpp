#include "thread_random.h"
#include "thread_data.h"
extern "C" void fun_005cdac0(uint32_t seed) {
    auto* const data = static_cast<OriginalPerThreadData*>(fun_005d2659());
    data->random_state = seed;
}
extern "C" int32_t fun_005cdacd() {
    auto* const data = static_cast<OriginalPerThreadData*>(fun_005d2659());
    const uint32_t state = data->random_state * 0x343fdu + 0x269ec3u;
    data->random_state = state;
    return int32_t((state >> 16) & 0x7fff);
}
// Original WinMain uses this spelling with the same cdecl DWORD signature.
extern "C" void FUN_005cdac0(uint32_t) __attribute__((alias("fun_005cdac0")));
