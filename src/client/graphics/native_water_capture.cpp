#include "graphics/native_water_draw.h"
#include "graphics/native_renderer.h"

namespace shaiya::graphics::native {
namespace {
WaterCaptureState captured;
Matrix projective_bias(const Matrix& source) {
    Matrix bias = {{{.5f, 0, 0, 0}, {0, -.5f, 0, 0}, {0, 0, 1, 0}, {.5f, .5f, 0, 1}}}, result = {};
    for (UINT row = 0; row < 4; ++row)
        for (UINT column = 0; column < 4; ++column)
            for (UINT k = 0; k < 4; ++k)
                result.m[row][column] += source.m[row][k] * bias.m[k][column];
    return result;
}
void select_owner(void* value) {
    if (captured.owner != value) {
        captured = {};
        captured.owner = value;
    }
}
} // namespace
WaterCaptureState& water_capture_state() {
    return captured;
}
void capture_water_reflection(void* value) {
    select_owner(value);
    captured.reflection = projective_bias(renderer()->scene.view_projection);
    captured.reflection_valid = true;
}
void capture_water_refraction(void* value) {
    select_owner(value);
    captured.refraction = projective_bias(renderer()->scene.view_projection);
    captured.refraction_valid = true;
}
} // namespace shaiya::graphics::native
