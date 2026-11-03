#pragma once
#include "graphics/native_render_passes.h"
namespace shaiya::graphics::native {
struct WaterCaptureState {
    void* owner = nullptr;
    Matrix reflection, refraction;
    bool reflection_valid = false, refraction_valid = false;
};
WaterCaptureState& water_capture_state();
void capture_water_reflection(void* owner);
void capture_water_refraction(void* owner);
} // namespace shaiya::graphics::native
