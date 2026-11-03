#pragma once
#include "graphics/native_render_target.h"
namespace shaiya::graphics::native {
void water_release(void* owner);
}
extern "C" void __cdecl native_water_release(void* owner);
