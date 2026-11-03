#pragma once

namespace shaiya::graphics::native {
// Calibrated against the original uncapped D3D9 client at 1024x768: its camera
// approached Z300 from Z420 in about 1.83 seconds. This reference stabilizes the
// observed tempo; it is not an original frame-rate limit. Rendering is uncapped.
inline constexpr unsigned login_camera_reference_hz = 825;
}

extern "C" void __attribute__((thiscall)) native_login_camera_update(void* self);
extern "C" void __attribute__((thiscall)) native_login_camera_reset(void* self);
