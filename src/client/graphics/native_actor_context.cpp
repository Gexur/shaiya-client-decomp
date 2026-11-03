#include "graphics/native_scene_ports.h"
#include "graphics/native_renderer.h"
namespace shaiya::graphics::native {
void set_actor_clip_transform(const Matrix& matrix);
void set_actor_model_transform(const Matrix& matrix);
} // namespace shaiya::graphics::native
namespace {
using namespace shaiya::graphics::native;
float water_height = 0;
Matrix transpose(const Matrix& source) {
    Matrix result;
    for (UINT r = 0; r < 4; ++r)
        for (UINT c = 0; c < 4; ++c)
            result.m[r][c] = source.m[c][r];
    return result;
}
} // namespace
extern "C" void __attribute__((stdcall)) native_actor_view_projection_rows(const Matrix* source) {
    set_actor_clip_transform(transpose(*source));
}
extern "C" void __attribute__((stdcall)) native_actor_environment_rows(const Matrix* source) {
    auto& actor = scene_draw_context();
    actor.environment_transform = transpose(*source);
    actor.explicit_environment_frame = true;
}
extern "C" void __attribute__((stdcall)) native_actor_environment_eye(const Color* source) {
    auto& actor = scene_draw_context();
    actor.environment_eye = *source;
    actor.explicit_environment_frame = true;
}
extern "C" void __attribute__((stdcall)) native_actor_model_rows(const AffineBone3x4* source) {
    Matrix matrix = {};
    matrix.m[3][3] = 1;
    for (UINT r = 0; r < 3; ++r)
        for (UINT c = 0; c < 4; ++c)
            matrix.m[c][r] = source->row[r][c];
    set_actor_model_transform(matrix);
}
extern "C" HRESULT __attribute__((stdcall)) native_actor_pose_bone(UINT bone,
                                                                   const AffineBone3x4* source) {
    return source ? set_actor_bone(bone, *source) : E_POINTER;
}
extern "C" UINT native_actor_is_skinned() {
    return scene_draw_context().actor_pipeline == ActorPipeline::skinned_model ? 1 : 0;
}
extern "C" void __attribute__((stdcall)) native_actor_water_height(const float* value) {
    water_height = value[1];
}
extern "C" void __attribute__((stdcall)) native_actor_water_clip(const float* value) {
    auto* current = renderer();
    current->scene.clip_plane[0] = current->scene.clip_plane[2] = 0;
    current->scene.clip_plane[1] = value[1];
    current->scene.clip_plane[3] = (water_height + value[2]) * value[1];
    begin_scene(*current, current->scene);
}
