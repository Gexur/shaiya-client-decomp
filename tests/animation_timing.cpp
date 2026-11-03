#include "graphics/native_animation_timing.h"
#include <stdint.h>

extern "C" {
__declspec(dllimport) void __attribute__((stdcall)) ExitProcess(uint32_t);
__declspec(dllimport) void* __attribute__((stdcall)) GetStdHandle(uint32_t);
__declspec(dllimport) int __attribute__((stdcall)) WriteFile(void*, const void*, uint32_t,
                                                             uint32_t*, void*);
float dat_00719a50 = 0;
float dat_00719a54 = 0;
float test_clock_seconds = 0;
void __attribute__((thiscall)) animation_test_sample_fade_clock(void*);
}

// Return the controlled clock value in physical ST0, exactly like the recovered
// stdcall clock. The production fade sampling instructions execute below.
__asm__(".text\n.intel_syntax noprefix\n"
        ".globl \"_FUN_00405840@4\"\n"
        "\"_FUN_00405840@4\":\n"
        "fld dword ptr [_test_clock_seconds]\n"
        "ret 4\n"
        ".globl _animation_test_sample_fade_clock\n"
        "_animation_test_sample_fade_clock:\n"
        "sub esp, 0x1c\n"
        "push esi\n"
#include "graphics/native_animation_frame_clock.inc"
        "pop esi\n"
        "add esp, 0x1c\n"
        "ret\n"
        ".att_syntax prefix\n");

namespace {
int failure = 0;
void require(bool condition, int code) {
    if (!condition && failure == 0)
        failure = code;
}
uint32_t fade_frame(float seconds, float speed = 1) {
    test_clock_seconds = seconds;
    animation_test_sample_fade_clock(nullptr);
    require(dat_00719a54 == seconds, 1);
    const uint32_t interval = native_world_animation_elapsed(speed);
    // All four scene animation families and instances share the interval.
    for (int family = 0; family < 4; ++family)
        require(native_world_animation_elapsed(speed) == interval, 2);
    return interval;
}
void test_fade_rates() {
    static const uint32_t rates[] = {30, 60, 144, 1000, 3500, 4000};
    for (uint32_t rate : rates) {
        // A slow outer frame must not become the interval for the entire fade.
        native_world_animation_begin_frame(0.08f);
        require(native_world_animation_elapsed(1) >= 79, 3);
        uint32_t total = 0;
        for (uint32_t frame = 0; frame < rate; ++frame) {
            const uint32_t interval = fade_frame(1.0f / float(rate));
            require(interval <= 1000 / rate + 1, 4);
            total += interval;
        }
        require(total >= 999 && total <= 1001, 5);
    }
}
void test_hitch_and_speed_changes() {
    native_world_animation_begin_frame(0.08f);
    (void)native_world_animation_elapsed(1);
    // Authored elapsed time is retained through a hitch; no clamping or
    // synthetic smoothing is introduced by refreshing the nested interval.
    const uint32_t total =
        fade_frame(.016f) + fade_frame(.016f) + fade_frame(.120f) + fade_frame(.008f);
    require(total >= 159 && total <= 161, 6);
    require(fade_frame(0) == 0, 7);
    // Remainders survive nested frames and scene speed changes.
    uint32_t scaled = 0;
    for (int frame = 0; frame < 4000; ++frame) {
        const float speed = frame < 1000   ? 1.0f
                            : frame < 2000 ? .5f
                            : frame < 3000 ? 1.0f / 3.0f
                                           : 1.0f;
        scaled += fade_frame(.00025f, speed);
    }
    require(scaled >= 707 && scaled <= 709, 8);
}
} // namespace

extern "C" void __cdecl animation_timing_test_entry() {
    test_fade_rates();
    test_hitch_and_speed_changes();
    static const char passed[] =
        "Animation timing: fade clock, shared intervals, hitches and speed changes passed.\n";
    static const char failed[] = "Animation timing regression failed.\n";
    uint32_t written = 0;
    WriteFile(GetStdHandle(uint32_t(-11)), failure ? failed : passed,
              failure ? sizeof(failed) - 1 : sizeof(passed) - 1, &written, nullptr);
    ExitProcess(uint32_t(failure));
}
