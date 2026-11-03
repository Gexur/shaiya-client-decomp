#include "graphics/native_login_camera.h"
#include <stdint.h>

extern "C" {
extern void* dat_007191d4;
extern float dat_00719a54;
extern const float dat_006be7f4;
extern unsigned char dat_02209408[];
extern float dat_0220e060[];
void __attribute__((thiscall)) native_login_camera_tick(void* self);
}

namespace {
constexpr float tick_seconds = 1.0f / 60.0f;
constexpr double tick_interval = static_cast<double>(tick_seconds);

struct CameraTick {
    uint32_t direction;
    float angle;
    float progress;
    float eye[3];
    float last_z;
};
struct CameraTimeline {
    void* owner;
    double remainder;
    CameraTick current;
    CameraTick next;
};
CameraTimeline timeline = {};

template <typename T> T& field(void* self, uint32_t offset) {
    return *reinterpret_cast<T*>(static_cast<unsigned char*>(self) + offset);
}
float* camera_eye() {
    return reinterpret_cast<float*>(dat_02209408 + 0xc0);
}
bool login3() {
    using Feature = uint8_t(__attribute__((thiscall)) *)(void*, uint32_t);
    auto* table = *static_cast<void***>(dat_007191d4);
    return reinterpret_cast<Feature>(table[1])(dat_007191d4, 15) != 0;
}
void read_tick(void* self, CameraTick& state) {
    state.direction = field<uint32_t>(self, 0x49cc);
    state.angle = field<float>(self, 0x49d0);
    state.progress = field<float>(self, 0x4d78);
    for (uint32_t axis = 0; axis < 3; ++axis)
        state.eye[axis] = camera_eye()[axis];
    state.last_z = dat_0220e060[2];
}
void step(void* self, const CameraTick& from, CameraTick& to, float seconds) {
    field<uint32_t>(self, 0x49cc) = from.direction;
    field<float>(self, 0x49d0) = from.angle;
    field<float>(self, 0x4d78) = from.progress;
    // The recovered camera reads the last rendered eye Z. The native timeline
    // instead feeds back its own previous tick, never an interpolated render.
    dat_0220e060[2] = from.last_z;
    dat_00719a54 = seconds;
    native_login_camera_tick(self);
    read_tick(self, to);
    to.last_z = to.eye[2];
    // Original 4bd6e7..4bd6f9 advances progress AFTER computing the camera.
    to.progress = static_cast<float>(static_cast<long double>(from.progress) +
                                    static_cast<long double>(seconds) * dat_006be7f4);
    if (to.progress > 1.0f)
        to.progress = 1.0f;
}
} // namespace

extern "C" void __attribute__((thiscall)) native_login_camera_reset(void*) {
    timeline.owner = nullptr;
    timeline.remainder = 0;
}

extern "C" void __attribute__((thiscall)) native_login_camera_update(void* self) {
    // The other two locale cameras retain their recovered operation and clock.
    if (!login3()) {
        native_login_camera_reset(self);
        native_login_camera_tick(self);
        return;
    }

    const float elapsed = dat_00719a54;
    const float progress = field<float>(self, 0x4d78);
    const float last_rendered_z = dat_0220e060[2];
    const bool initialized = timeline.owner != self;
    if (initialized) {
        timeline.owner = self;
        timeline.remainder = 0;
        read_tick(self, timeline.current);
        step(self, timeline.current, timeline.next, tick_seconds);
    }

    // Retained input processing sets progress to one after the camera update
    // when Escape is pressed. Honor that skip on the next update even when
    // less than a virtual tick has elapsed.
    if (progress >= 1.0f && (initialized || timeline.current.progress < 1.0f)) {
        timeline.current.progress = 1.0f;
        CameraTick skipped;
        step(self, timeline.current, skipped, 0);
        for (uint32_t axis = 0; axis < 3; ++axis)
            timeline.current.eye[axis] = skipped.eye[axis];
        timeline.current.last_z = skipped.last_z;
        step(self, timeline.current, timeline.next, tick_seconds);
    }

    if (elapsed > 0 && __builtin_isfinite(elapsed))
        timeline.remainder += static_cast<double>(elapsed);
    while (timeline.remainder >= tick_interval) {
        timeline.current = timeline.next;
        step(self, timeline.current, timeline.next, tick_seconds);
        timeline.remainder -= tick_interval;
    }
    const double fraction = timeline.remainder / tick_interval;
    for (uint32_t axis = 0; axis < 3; ++axis)
        camera_eye()[axis] = static_cast<float>(
            timeline.current.eye[axis] +
            (timeline.next.eye[axis] - timeline.current.eye[axis]) * fraction);
    field<float>(self, 0x49d0) = static_cast<float>(
        timeline.current.angle + (timeline.next.angle - timeline.current.angle) * fraction);
    field<uint32_t>(self, 0x49cc) = timeline.current.direction;

    // The retained caller still owns progress, effect updates and threshold
    // checks. Its clock and previous rendered camera must survive look-ahead.
    field<float>(self, 0x4d78) = progress;
    dat_00719a54 = elapsed;
    dat_0220e060[2] = last_rendered_z;
}
