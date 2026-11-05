#pragma once
#include "graphics/native_render_passes.h"
#include "graphics/native_resources.h"
namespace shaiya::graphics::native {
enum class ActorPipeline { lit_model, skinned_model, reflective_model };
struct AffineBone3x4 {
    float row[3][4];
};
HRESULT set_actor_palette(const AffineBone3x4* palette, UINT bone_count);
HRESULT set_actor_bone(UINT bone, const AffineBone3x4& transform);
struct ActorLighting {
    Color ambient = {0, 0, 0, 1};
    Color directional = {0, 0, 0, 1};
    float direction[3] = {}, camera[3] = {};
    bool ambient_authored = false, directional_authored = false;
    bool direction_authored = false, camera_authored = false;
};
struct SceneDrawContext {
    Matrix world = {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
    Material material;
    Texture2D* diffuse = nullptr;
    Texture2D* lightmap = nullptr;
    Texture2D* detail = nullptr;
    bool lit = true;
    bool use_lightmaps = true;
    Depth ui_depth = Depth::disabled;
    ActorPipeline actor_pipeline = ActorPipeline::lit_model;
    ActorLighting actor_lighting;
    const Matrix* bones = nullptr;
    UINT bone_count = 0;
    Texture2D* environment = nullptr;
    bool actor_reflection = false;
    Matrix environment_transform = {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
    Color environment_eye = {0, 0, 0, 1};
    bool explicit_environment_frame = false;
    bool projected_shadow = false;
    Texture2D* shadow_map = nullptr;
    Matrix shadow_projection;
};
SceneDrawContext& scene_draw_context();
void set_scene_diffuse(Texture2D* texture);
void set_scene_lightmap(Texture2D* texture);
void set_scene_detail(Texture2D* texture);
void set_scene_environment(Texture2D* texture);
void set_scene_shadow_map(Texture2D* texture);
void release_scene_textures();
struct SceneDrawScope {
    SceneDrawContext saved;
    ID3D11ShaderResourceView* saved_ui_image;
    SceneDrawScope();
    ~SceneDrawScope();
    SceneDrawScope(const SceneDrawScope&) = delete;
    SceneDrawScope& operator=(const SceneDrawScope&) = delete;
};
// Engine render-state flags (depth, blending, alpha test, clip plane and the
// directional light switch) that later SetRenderState-style calls combine into
// the current draw style. Nested world renders change them; scopes that run one
// restore them together with the draw context.
struct ControllerState {
    Color light_color;
    bool light_enabled;
    bool depth_test, depth_write, blending, alpha_test;
    Blend blend;
    D3D11_BLEND source, destination;
    float alpha_cutoff;
    float plane[4];
    bool clip_enabled;
};
ControllerState capture_controller_state();
void restore_controller_state(const ControllerState& state);
struct ControllerStateScope {
    ControllerState saved = capture_controller_state();
    ControllerStateScope() = default;
    ~ControllerStateScope() {
        restore_controller_state(saved);
    }
    ControllerStateScope(const ControllerStateScope&) = delete;
    ControllerStateScope& operator=(const ControllerStateScope&) = delete;
};
} // namespace shaiya::graphics::native
