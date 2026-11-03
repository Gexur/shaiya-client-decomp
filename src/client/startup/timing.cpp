#include "timing.h"

namespace {
constexpr uint32_t kRefreshIntervalMilliseconds = 5000;
}

// Genuine WINMM API dependency. Production linking requires its import
// library; test-only clock fixtures are kept outside the recovered source.
extern "C" uint32_t __attribute__((stdcall)) timeGetTime();

extern "C" {
__declspec(dllexport) void* dat_00719a64 = nullptr;
__declspec(dllexport) uint32_t dat_00719a6c = 0;
}

/**
 * Capture the initial multimedia-clock tick for the startup refresh marker.
 * Writes dat_00719a6c once and registers no destructor. The recovered startup table
 * invokes this entry in its original order: slot 0x70801c -> 0x6b5710.
 */
extern "C" void __cdecl initialize_startup_refresh_tick() {
    dat_00719a6c = timeGetTime();
}

/**
 * Refresh the stored multimedia-clock tick when its allocated marker is active.
 * Reads the clock only when dat_00719a64 is non-null and writes dat_00719a6c only
 * after strictly more than 5000 milliseconds have elapsed. Unsigned subtraction
 * preserves the original 32-bit clock wraparound.
 * @return One on every path, including when the marker is absent.
 * Original entry: 0x40a7a0.
 */
extern "C" uint32_t __cdecl refresh_startup_tick() {
    if (dat_00719a64 != nullptr) {
        const uint32_t current_tick = timeGetTime();
        if (current_tick - dat_00719a6c > kRefreshIntervalMilliseconds)
            dat_00719a6c = current_tick;
    }
    return 1;
}
