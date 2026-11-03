#pragma once

#include <stdint.h>

// The application starts one animation interval per update. World animation
// consumers share its integer milliseconds without discarding sub-ms time.
extern "C" void __cdecl native_world_animation_begin_frame(float elapsed_seconds);
extern "C" uint32_t __attribute__((stdcall)) native_world_animation_elapsed(float speed_scale);
