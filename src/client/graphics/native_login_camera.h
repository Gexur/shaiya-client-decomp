#pragma once

// Native policy: the login3 camera follows recovered 60 Hz camera ticks, with
// interpolation for presentation. Rendering itself remains unrestricted.
extern "C" void __attribute__((thiscall)) native_login_camera_update(void* self);
extern "C" void __attribute__((thiscall)) native_login_camera_reset(void* self);
