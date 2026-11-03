#include "graphics/native_renderer.h"
#include "graphics/native_scene_ports.h"
#include "graphics/native_render_target.h"
#include <new>
namespace {
using namespace shaiya::graphics::native;
struct AssetMaterial {
    Color diffuse, ambient, specular, emissive;
    float power;
};
struct SceneLight {
    UINT kind;
    Color diffuse, specular, ambient;
    float position[3], direction[3];
    float range, falloff, attenuation[3], theta, phi;
};
static_assert(sizeof(SceneLight) == 104);
Color directional_color = {1, 1, 1, 1};
bool directional_enabled = true;
bool depth_test = true, depth_write = true, blending = true, alpha_test = true;
Blend blend = Blend::alpha;
D3D11_BLEND authored_source = D3D11_BLEND_SRC_ALPHA,
            authored_destination = D3D11_BLEND_INV_SRC_ALPHA;
float alpha_cutoff = 7.5f / 255;
float clip_plane[4] = {};
bool clip_enabled = false;
struct PortraitState {
    SceneDrawScope draw;
    Color light_color = directional_color;
    bool light_enabled = directional_enabled;
    bool saved_depth_test = depth_test, saved_depth_write = depth_write;
    bool saved_blending = blending, saved_alpha_test = alpha_test;
    Blend saved_blend = blend;
    D3D11_BLEND source = authored_source, destination = authored_destination;
    float saved_alpha_cutoff = alpha_cutoff;
    float plane[4] = {clip_plane[0], clip_plane[1], clip_plane[2], clip_plane[3]};
    bool saved_clip_enabled = clip_enabled;
};
void restore_portrait(void* saved) {
    auto* state = static_cast<PortraitState*>(saved);
    directional_color = state->light_color;
    directional_enabled = state->light_enabled;
    depth_test = state->saved_depth_test;
    depth_write = state->saved_depth_write;
    blending = state->saved_blending;
    alpha_test = state->saved_alpha_test;
    blend = state->saved_blend;
    authored_source = state->source;
    authored_destination = state->destination;
    alpha_cutoff = state->saved_alpha_cutoff;
    for (UINT i = 0; i < 4; ++i)
        clip_plane[i] = state->plane[i];
    clip_enabled = state->saved_clip_enabled;
    state->~PortraitState();
    HeapFree(GetProcessHeap(), 0, state);
}
void depth() {
    scene_draw_context().material.style.depth = !depth_test   ? Depth::disabled
                                                : depth_write ? Depth::write
                                                              : Depth::read;
}
void apply_blend() {
    auto& style = scene_draw_context().material.style;
    style.blend = blending ? blend : Blend::opaque;
    style.source_blend = blending ? authored_source : D3D11_BLEND(0);
    style.destination_blend = blending ? authored_destination : D3D11_BLEND(0);
}
void update_camera() {
    auto* current = renderer();
    for (UINT row = 0; row < 4; ++row)
        for (UINT column = 0; column < 4; ++column) {
            current->scene.view_projection.m[row][column] = 0;
            for (UINT component = 0; component < 4; ++component)
                current->scene.view_projection.m[row][column] +=
                    current->scene.view.m[row][component] *
                    current->projection.m[component][column];
        }
    begin_scene(*current, current->scene);
}
Color color(UINT argb) {
    return {float((argb >> 16) & 255) / 255, float((argb >> 8) & 255) / 255,
            float(argb & 255) / 255, float(argb >> 24) / 255};
}
UINT channel(float value) {
    return value <= 0 ? 0 : value >= 1 ? 255 : static_cast<UINT>(value * 255 + 0.5f);
}
} // namespace
extern "C" HRESULT __attribute__((stdcall)) native_portrait_preserve_state(TargetScope* target) {
    if (target == nullptr || !target->active || target->restore_draw_state != nullptr)
        return E_INVALIDARG;
    void* storage = HeapAlloc(GetProcessHeap(), 0, sizeof(PortraitState));
    if (storage == nullptr)
        return E_OUTOFMEMORY;
    target->saved_draw_state = new (storage) PortraitState();
    target->restore_draw_state = restore_portrait;
    return S_OK;
}
extern "C" void __attribute__((stdcall)) native_scene_capture_view(Matrix* out) {
    *out = renderer()->scene.view;
}
extern "C" void __attribute__((stdcall)) native_scene_capture_projection(Matrix* out) {
    *out = renderer()->projection;
}
extern "C" void __attribute__((stdcall)) native_scene_capture_world(Matrix* out) {
    *out = scene_draw_context().world;
}
extern "C" void __attribute__((stdcall)) native_scene_view(const Matrix* value) {
    renderer()->scene.view = *value;
    update_camera();
}
extern "C" void __attribute__((stdcall)) native_scene_projection(const Matrix* value) {
    renderer()->projection = *value;
    update_camera();
}
extern "C" void __attribute__((stdcall)) native_scene_world(const Matrix* value) {
    scene_draw_context().world = *value;
}
extern "C" void __attribute__((stdcall)) native_scene_texture_projection(const Matrix* value) {
    auto& material = scene_draw_context().material;
    material.texture_projection = *value;
    material.projected_texture = true;
}
extern "C" void __cdecl native_scene_authored_uv() {
    scene_draw_context().material.projected_texture = false;
}
extern "C" UINT __attribute__((stdcall)) native_effect_ready(const NativeRenderer* current) {
    return current != nullptr && current->device != nullptr && current->context != nullptr &&
           current->pipeline_data != nullptr && current->feature_level >= D3D_FEATURE_LEVEL_10_0;
}
extern "C" void __attribute__((stdcall)) native_scene_material(const AssetMaterial* value) {
    auto& material = scene_draw_context().material;
    material.diffuse_color = value->diffuse;
    material.ambient_color = value->ambient;
    material.specular_color = value->specular;
    material.specular_power = value->power;
    material.emissive_color = value->emissive;
}
extern "C" void __attribute__((stdcall)) native_scene_clip_plane(const float* value) {
    auto* current = renderer();
    for (UINT i = 0; i < 4; ++i) {
        clip_plane[i] = value[i];
        current->scene.clip_plane[i] = clip_enabled ? value[i] : 0;
    }
    begin_scene(*current, current->scene);
}

extern "C" void __attribute__((stdcall)) native_scene_clip_enabled(UINT enabled) {
    auto* current = renderer();
    clip_enabled = enabled != 0;
    for (UINT i = 0; i < 4; ++i)
        current->scene.clip_plane[i] = clip_enabled ? clip_plane[i] : 0;
    begin_scene(*current, current->scene);
}

extern "C" void __attribute__((stdcall)) native_ui_scissor(const D3D11_RECT* rectangle) {
    renderer()->ui_scissor = *rectangle;
}
extern "C" void __attribute__((stdcall)) native_ui_scissor_enabled(UINT enabled) {
    renderer()->ui_scissor_enabled = enabled != 0;
}

extern "C" void __cdecl native_scene_style_defaults() {
    depth_test = depth_write = blending = alpha_test = true;
    blend = Blend::alpha;
    alpha_cutoff = 7.5f / 255;
    authored_source = D3D11_BLEND_SRC_ALPHA;
    authored_destination = D3D11_BLEND_INV_SRC_ALPHA;
    scene_draw_context().material.projected_texture = false;
}
extern "C" void __attribute__((thiscall)) FUN_00546300(void* self) {
    auto* words = static_cast<UINT*>(self);
    auto* current = renderer();
    // Portrait callers restore their main camera before closing the target.
    // Keep their restored transforms while the target scope restores world
    // lighting, fog and the material/controller state saved before the preview.
    const Matrix view = current->scene.view;
    const Matrix view_projection = current->scene.view_projection;
    const Matrix projection = current->projection;
    const Matrix world = scene_draw_context().world;
    auto* target = reinterpret_cast<TargetScope*>(words[2]);
    if (target != nullptr)
        end_target(*target);
    current->scene.view = view;
    current->scene.view_projection = view_projection;
    current->projection = projection;
    scene_draw_context().world = world;
    begin_scene(*current, current->scene);
    words[1] = 1;
}
extern "C" void __attribute__((stdcall)) native_scene_diffuse(Texture2D* value) {
    set_scene_diffuse(value);
}

extern "C" void __attribute__((stdcall)) native_actor_effect_blend(void* actor) {
    // These are authored effect catalog choices. They select D3D11 factors
    // directly; no device state numbers or legacy graphics interface is used.
    static constexpr D3D11_BLEND factors[13] = {
        D3D11_BLEND_ZERO,          D3D11_BLEND_ONE,
        D3D11_BLEND_SRC_COLOR,     D3D11_BLEND_INV_SRC_COLOR,
        D3D11_BLEND_SRC_ALPHA,     D3D11_BLEND_INV_SRC_ALPHA,
        D3D11_BLEND_DEST_ALPHA,    D3D11_BLEND_INV_DEST_ALPHA,
        D3D11_BLEND_DEST_COLOR,    D3D11_BLEND_INV_DEST_COLOR,
        D3D11_BLEND_SRC_ALPHA_SAT, D3D11_BLEND_SRC_ALPHA,
        D3D11_BLEND_INV_SRC_ALPHA};
    const auto* source = static_cast<const unsigned char*>(actor);
    const UINT source_choice = *reinterpret_cast<const UINT*>(source + 0xc8);
    const UINT destination_choice = *reinterpret_cast<const UINT*>(source + 0xcc);
    auto& style = scene_draw_context().material.style;
    if (source_choice >= 13 || destination_choice >= 13)
        return;
    style.source_blend = factors[source_choice];
    style.destination_blend = source_choice == 11   ? D3D11_BLEND_INV_SRC_ALPHA
                              : source_choice == 12 ? D3D11_BLEND_SRC_ALPHA
                                                    : factors[destination_choice];
    authored_source = style.source_blend;
    authored_destination = style.destination_blend;
    if (!blending)
        style.source_blend = style.destination_blend = D3D11_BLEND(0);
}
extern "C" void __attribute__((stdcall)) native_scene_lightmap(Texture2D* value) {
    set_scene_lightmap(value);
}
extern "C" void __attribute__((stdcall)) native_scene_ambient_argb(UINT value) {
    auto* current = renderer();
    current->scene.ambient = color(value);
    begin_scene(*current, current->scene);
}
extern "C" void __attribute__((stdcall)) native_scene_read_ambient(UINT* value) {
    const auto& c = renderer()->scene.ambient;
    *value = (channel(c.a) << 24) | (channel(c.r) << 16) | (channel(c.g) << 8) | channel(c.b);
}
extern "C" void __attribute__((stdcall)) native_scene_directional(const SceneLight* value) {
    auto* current = renderer();
    directional_color = value->diffuse;
    current->scene.directional = directional_enabled ? directional_color : Color{0, 0, 0, 1};
    for (UINT i = 0; i < 3; ++i)
        current->scene.light_direction[i] = value->direction[i];
    begin_scene(*current, current->scene);
}
extern "C" void __attribute__((stdcall)) native_scene_highlight(const SceneLight* value) {
    auto* current = renderer();
    auto& light = current->scene.point_light;
    light.diffuse = value->diffuse;
    for (UINT i = 0; i < 3; ++i) {
        light.position[i] = value->position[i];
        light.attenuation[i] = value->attenuation[i];
    }
    light.range = value->range;
    begin_scene(*current, current->scene);
}
extern "C" void __attribute__((stdcall)) native_scene_directional_enabled(UINT enabled) {
    auto* current = renderer();
    directional_enabled = enabled != 0;
    current->scene.directional = directional_enabled ? directional_color : Color{0, 0, 0, 1};
    begin_scene(*current, current->scene);
}
extern "C" void __attribute__((stdcall)) native_scene_highlight_enabled(UINT enabled) {
    auto* current = renderer();
    current->scene.point_light.enabled = enabled != 0;
    begin_scene(*current, current->scene);
}
extern "C" void __attribute__((stdcall)) native_actor_light_direction(const float* value) {
    auto& light = scene_draw_context().actor_lighting;
    for (UINT i = 0; i < 3; ++i)
        light.direction[i] = value[i];
    light.direction_authored = true;
}
extern "C" void __attribute__((stdcall)) native_actor_camera(const float* value) {
    auto& light = scene_draw_context().actor_lighting;
    for (UINT i = 0; i < 3; ++i)
        light.camera[i] = value[i];
    light.camera_authored = true;
}
extern "C" void __attribute__((stdcall)) native_actor_directional(const Color* value) {
    auto& light = scene_draw_context().actor_lighting;
    light.directional = *value;
    light.directional_authored = true;
}
extern "C" void __attribute__((stdcall)) native_actor_ambient(const Color* value) {
    auto& light = scene_draw_context().actor_lighting;
    light.ambient = *value;
    light.ambient_authored = true;
}
extern "C" void __attribute__((stdcall)) native_actor_specular(const Color* value) {
    auto& material = scene_draw_context().material;
    material.specular_color = *value;
    material.specular_power = value->a;
}

extern "C" void __attribute__((stdcall)) native_scene_depth_test(UINT enabled) {
    depth_test = enabled != 0;
    depth();
}
extern "C" void __attribute__((stdcall)) native_scene_depth_write(UINT enabled) {
    depth_write = enabled != 0;
    depth();
}
extern "C" void __attribute__((stdcall)) native_scene_blending(UINT enabled) {
    blending = enabled != 0;
    scene_draw_context().material.style.blend = blending ? blend : Blend::opaque;
    auto& style = scene_draw_context().material.style;
    style.source_blend = blending ? authored_source : D3D11_BLEND(0);
    style.destination_blend = blending ? authored_destination : D3D11_BLEND(0);
}
extern "C" void __cdecl native_scene_blend_alpha() {
    authored_destination = D3D11_BLEND_INV_SRC_ALPHA;
    apply_blend();
}
extern "C" void __cdecl native_scene_blend_additive() {
    authored_destination = D3D11_BLEND_ONE;
    apply_blend();
}
extern "C" void __cdecl native_scene_blend_color_add() {
    authored_source = D3D11_BLEND_ONE;
    apply_blend();
}
extern "C" void __cdecl native_scene_blend_multiply() {
    authored_destination = D3D11_BLEND_SRC_COLOR;
    apply_blend();
}
extern "C" void __cdecl native_material_source_alpha() {
    authored_source = D3D11_BLEND_SRC_ALPHA;
    apply_blend();
}
extern "C" void __cdecl native_material_source_zero() {
    authored_source = D3D11_BLEND_ZERO;
    apply_blend();
}
extern "C" void __cdecl native_material_source_inverse_alpha() {
    authored_source = D3D11_BLEND_INV_SRC_ALPHA;
    apply_blend();
}
extern "C" void __cdecl native_material_source_color() {
    authored_source = D3D11_BLEND_SRC_COLOR;
    apply_blend();
}
extern "C" void __cdecl native_material_source_inverse_color() {
    authored_source = D3D11_BLEND_INV_SRC_COLOR;
    apply_blend();
}
extern "C" void __attribute__((stdcall)) native_scene_alpha_test(UINT enabled) {
    alpha_test = enabled != 0;
    scene_draw_context().material.style.alpha_cutoff = alpha_test ? alpha_cutoff : 0;
}
extern "C" void __attribute__((stdcall)) native_scene_alpha_reference(UINT reference) {
    alpha_cutoff = (float(reference) - 0.5f) / 255;
    scene_draw_context().material.style.alpha_cutoff = alpha_test ? alpha_cutoff : 0;
}
extern "C" void __cdecl native_scene_cull_none() {
    scene_draw_context().material.style.cull = Cull::none;
}
extern "C" void __cdecl native_scene_cull_front() {
    scene_draw_context().material.style.cull = Cull::front;
}
extern "C" void __cdecl native_scene_cull_back() {
    scene_draw_context().material.style.cull = Cull::back;
}
extern "C" void __attribute__((stdcall)) native_scene_lighting(UINT enabled) {
    scene_draw_context().lit = enabled != 0;
}
extern "C" void __attribute__((stdcall)) native_scene_tint(UINT argb) {
    scene_draw_context().material.style.tint = color(argb);
}
extern "C" void __attribute__((stdcall)) native_scene_fog_enabled(UINT enabled) {
    auto* r = renderer();
    r->scene.fog_enabled = enabled != 0;
    begin_scene(*r, r->scene);
}
extern "C" void __attribute__((stdcall)) native_scene_fog_color(UINT argb) {
    auto* r = renderer();
    r->scene.fog_color = color(argb);
    begin_scene(*r, r->scene);
}
extern "C" void __attribute__((stdcall)) native_scene_fog_start(float value) {
    auto* r = renderer();
    r->scene.fog_start = value;
    begin_scene(*r, r->scene);
}
extern "C" void __attribute__((stdcall)) native_scene_fog_end(float value) {
    auto* r = renderer();
    r->scene.fog_end = value;
    begin_scene(*r, r->scene);
}
