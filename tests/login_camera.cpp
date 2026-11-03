#include "graphics/native_login_camera.h"
#include <stdint.h>

extern "C" {
__declspec(dllimport) void __attribute__((stdcall)) ExitProcess(uint32_t);
__declspec(dllimport) void* __attribute__((stdcall)) GetStdHandle(uint32_t);
__declspec(dllimport) int __attribute__((stdcall)) WriteFile(void*, const void*, uint32_t,
                                                             uint32_t*, void*);
float dat_00719a54 = 0;
unsigned char dat_02209408[0x200] = {};
float dat_0220e060[3] = {};
// Exact float constants read by recovered FUN_004b8d60 and 4bd6e7..4bd6f9.
extern const float dat_006bb5fc = 0x0.0p+0f;
extern const float dat_006bc8c4 = 0x1.fe00000000000p+7f;
extern const float dat_006bca34 = 0x1.3333340000000p-1f;
extern const float dat_006be948 = 0x1.1df46a0000000p-6f;
extern const float dat_006bede8 = 0x1.6666660000000p-1f;
extern const float dat_006c21b8 = 0x1.ef5eb80000000p+8f;
extern const float dat_006be7f4 = 0x1.0624de0000000p-10f;
void __attribute__((thiscall)) native_login_camera_tick(void*);
}

// The fixture executes the production recovered tick, including its physical
// x87 instructions and locale getter ABI, rather than a second math model.
__asm__(".text\n.intel_syntax noprefix\n"
#include "graphics/native_login_camera_tick.inc"
        ".att_syntax prefix\n");

namespace {
uint32_t locale = 15;
uint8_t __attribute__((thiscall)) feature(void*, uint32_t value) {
    return value == locale;
}
void* feature_table[2] = {nullptr, reinterpret_cast<void*>(feature)};
struct Config {
    void** table;
};
Config config = {feature_table};
alignas(16) unsigned char owner[0x4d88] = {};
alignas(16) unsigned char second_owner[0x4d88] = {};
int failure = 0;
uint32_t checks = 0;
constexpr float tick_seconds = 1.0f / 60.0f;

template <typename T> T& field(void* self, uint32_t offset) {
    return *reinterpret_cast<T*>(static_cast<unsigned char*>(self) + offset);
}
float* eye() {
    return reinterpret_cast<float*>(dat_02209408 + 0xc0);
}
float* target() {
    return reinterpret_cast<float*>(dat_02209408 + 0xcc);
}
float distance(float a, float b) {
    return a < b ? b - a : a - b;
}
void require(bool condition, int code) {
    ++checks;
    if (!condition && failure == 0)
        failure = code;
}
struct Snapshot {
    float eye[3];
    float angle;
    uint32_t direction;
};
Snapshot reference[1201] = {};
Snapshot snapshot(void* self) {
    Snapshot result;
    for (uint32_t axis = 0; axis < 3; ++axis)
        result.eye[axis] = eye()[axis];
    result.angle = field<float>(self, 0x49d0);
    result.direction = field<uint32_t>(self, 0x49cc);
    return result;
}
void initialize(void* self = owner, float initial_z = 420, float feedback_z = 420) {
    locale = 15;
    field<uint32_t>(self, 0x49cc) = 0;
    field<float>(self, 0x49d0) = 0;
    field<float>(self, 0x4d78) = 0;
    eye()[0] = target()[0] = 441.21f;
    target()[1] = 305.87f;
    eye()[1] = target()[1] + 60;
    eye()[2] = initial_z;
    target()[2] = 495.37f;
    dat_0220e060[2] = feedback_z;
    dat_00719a54 = 0;
    native_login_camera_reset(self);
}
void retained_progress(void* self, float seconds) {
    float& progress = field<float>(self, 0x4d78);
    progress = static_cast<float>(static_cast<long double>(progress) +
                                  static_cast<long double>(seconds) * dat_006be7f4);
    if (progress > 1)
        progress = 1;
}
void frame(float seconds, void* self = owner) {
    dat_00719a54 = seconds;
    const uint32_t previous_clock_bits = *reinterpret_cast<uint32_t*>(&dat_00719a54);
    const float previous_z = dat_0220e060[2];
    const float previous_progress = field<float>(self, 0x4d78);
    native_login_camera_update(self);
    // Speculative ticks must not leak into the retained effects and clock.
    require(*reinterpret_cast<uint32_t*>(&dat_00719a54) == previous_clock_bits, 1);
    require(dat_0220e060[2] == previous_z, 2);
    require(field<float>(self, 0x4d78) == previous_progress, 3);
    retained_progress(self, seconds);
    // Recovered render 4ba71d feeds the presented eye back to global storage.
    // Changing these samples must not change the native virtual camera path.
    dat_0220e060[2] = eye()[2];
}
void make_reference() {
    initialize();
    reference[0] = snapshot(owner);
    for (uint32_t tick = 1; tick <= 1200; ++tick) {
        dat_00719a54 = tick_seconds;
        native_login_camera_tick(owner);
        retained_progress(owner, tick_seconds);
        dat_0220e060[2] = eye()[2];
        reference[tick] = snapshot(owner);
    }
}
void compare(const Snapshot& expected, int code, float tolerance = .0002f) {
    for (uint32_t axis = 0; axis < 3; ++axis)
        require(distance(eye()[axis], expected.eye[axis]) <= tolerance, code);
    require(distance(field<float>(owner, 0x49d0), expected.angle) <= .000002f, code);
}
void test_reference_and_rates() {
    // Every virtual reference tick follows the recovered 60 Hz trajectory.
    initialize();
    for (uint32_t tick = 1; tick <= 1200; ++tick) {
        frame(tick_seconds);
        compare(reference[tick], 4);
        for (uint32_t axis = 0; axis < 3; ++axis)
            require(*reinterpret_cast<uint32_t*>(eye() + axis) ==
                        *reinterpret_cast<const uint32_t*>(reference[tick].eye + axis),
                    23);
        require(field<uint32_t>(owner, 0x49cc) == reference[tick].direction, 5);
    }
    static const uint32_t rates[] = {30, 60, 144, 1000, 4000};
    for (uint32_t rate : rates) {
        initialize();
        for (uint32_t second = 1; second <= 20; ++second) {
            for (uint32_t update = 0; update < rate; ++update)
                frame(1.0f / static_cast<float>(rate));
            compare(reference[second * 60], 6);
        }
    }
}
void test_cadence_change_and_hitch() {
    initialize();
    // Reproduce the abrupt performance change when eye Z<300 disables the
    // four expensive SEFFs. The virtual reference must retain its velocity.
    bool crossed = false;
    for (uint32_t second = 1; second <= 12; ++second) {
        for (uint32_t millisecond = 0; millisecond < 1000; ++millisecond) {
            if (eye()[2] < 300)
                crossed = true;
            const uint32_t subframes = crossed ? 4 : 1;
            for (uint32_t update = 0; update < subframes; ++update)
                frame(.001f / static_cast<float>(subframes));
        }
        compare(reference[second * 60], 7);
    }
    require(crossed, 8);

    initialize();
    for (uint32_t tick = 0; tick < 60; ++tick)
        frame(tick_seconds);
    frame(.120f);
    frame(.005f);
    frame(.125f);
    frame(0);
    compare(reference[75], 9); // Full 1.25s elapsed, with no hitch clamping.

    initialize();
    frame(.001f);
    require(eye()[0] != reference[0].eye[0], 10);
    require(distance(eye()[0], reference[0].eye[0]) <
                distance(reference[1].eye[0], reference[0].eye[0]),
            11); // Sub-tick presentation interpolates rather than stepping.
}
void test_skip_reset_and_initial_feedback() {
    initialize();
    frame(.1f);
    field<float>(owner, 0x4d78) = 1; // Retained post-camera Escape processing.
    frame(.0001f);
    require(eye()[2] < 256, 12);
    require(field<float>(owner, 0x4d78) == 1, 13);
    frame(0);
    require(eye()[2] < 256, 14);

    initialize();
    field<float>(owner, 0x4d78) = 1;
    frame(0);
    require(eye()[2] < 256, 24); // Already skipped when the scene is initialized.

    initialize(owner, 400, 390);
    dat_00719a54 = tick_seconds;
    native_login_camera_tick(owner);
    const Snapshot distinct_feedback = snapshot(owner);
    initialize(owner, 400, 390);
    frame(tick_seconds);
    compare(distinct_feedback, 15);

    initialize(owner, 410, 405);
    frame(0);
    require(eye()[2] == 410, 16);
    initialize(second_owner, 430, 425);
    frame(0, second_owner);
    require(eye()[2] == 430, 17);
    // Same pointer, explicit login initialization must discard old snapshots.
    initialize(owner, 415, 412);
    frame(0);
    require(eye()[2] == 415, 18);
}
void test_other_locale_modes() {
    static const uint32_t modes[] = {0, 14};
    for (uint32_t mode : modes) {
        initialize();
        locale = mode;
        dat_00719a54 = .037f;
        native_login_camera_tick(owner);
        const Snapshot expected = snapshot(owner);
        initialize();
        locale = mode;
        dat_00719a54 = .037f;
        native_login_camera_update(owner);
        compare(expected, 19, 0);
        require(field<uint32_t>(owner, 0x49cc) == expected.direction, 20);
        require(dat_00719a54 == .037f, 21);
        require(field<float>(owner, 0x4d78) == 0, 22);
    }
}
} // namespace

extern "C" {
void* dat_007191d4 = &config;
}

extern "C" void __cdecl login_camera_test_entry() {
    make_reference();
    test_reference_and_rates();
    test_cadence_change_and_hitch();
    test_skip_reset_and_initial_feedback();
    test_other_locale_modes();
    static const char passed[] =
        "Login camera: recovered ticks, frame rates, cadence changes, hitch, skip and reset passed.\n";
    static const char failed[] = "Login camera regression failed.\n";
    uint32_t written = 0;
    WriteFile(GetStdHandle(uint32_t(-11)), failure ? failed : passed,
              failure ? sizeof(failed) - 1 : sizeof(passed) - 1, &written, nullptr);
    ExitProcess(uint32_t(failure));
}
