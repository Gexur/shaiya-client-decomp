#include "graphics/native_render_target.h"
#include "graphics/native_scene_ports.h"
#include "config/initialization.hpp"
#include <new>
extern "C" {
extern unsigned char dat_02209408[];
extern float dat_0220aa50[16], dat_0220aa90[16], dat_0220bee8[16];
}
namespace {
using namespace shaiya::graphics::native;
alignas(SceneDrawScope) unsigned char saved_storage[sizeof(SceneDrawScope)];
SceneDrawScope* saved_draw = nullptr;
bool active = false;
Matrix shadow_view_projection;
Matrix identity() {
    Matrix result = {};
    for (UINT i = 0; i < 4; ++i)
        result.m[i][i] = 1;
    return result;
}
Matrix multiply(const Matrix& a, const Matrix& b) {
    Matrix result = {};
    for (UINT r = 0; r < 4; ++r)
        for (UINT c = 0; c < 4; ++c)
            for (UINT k = 0; k < 4; ++k)
                result.m[r][c] += a.m[r][k] * b.m[k][c];
    return result;
}
void normalize(float* value) {
    float squared = value[0] * value[0] + value[1] * value[1] + value[2] * value[2], length;
    __asm__ volatile("flds %1\n\tfsqrt\n\tfstps %0" : "=m"(length) : "m"(squared) : "st");
    if (length > 0)
        for (UINT i = 0; i < 3; ++i)
            value[i] /= length;
}
void prepare_view(float offset) {
    const auto* position = reinterpret_cast<const float*>(dat_02209408 + 0xf0);
    Matrix world = identity();
    for (UINT i = 0; i < 3; ++i)
        world.m[3][i] = position[i];
    float eye[3] = {position[0], position[1] + 50, position[2] + offset};
    float forward[3] = {0, -50, -offset};
    normalize(forward);
    float right[3] = {forward[2], 0, -forward[0]};
    normalize(right);
    float up[3] = {forward[1] * right[2] - forward[2] * right[1],
                   forward[2] * right[0] - forward[0] * right[2],
                   forward[0] * right[1] - forward[1] * right[0]};
    Matrix view = identity();
    for (UINT i = 0; i < 3; ++i) {
        view.m[i][0] = right[i];
        view.m[i][1] = up[i];
        view.m[i][2] = forward[i];
        view.m[3][0] -= right[i] * eye[i];
        view.m[3][1] -= up[i] * eye[i];
        view.m[3][2] -= forward[i] * eye[i];
    }
    *reinterpret_cast<Matrix*>(dat_0220bee8) = world;
    *reinterpret_cast<Matrix*>(dat_0220aa90) = view;
}
HRESULT begin_shadow(void* owner, float width, float height, bool textured) {
    if (active || !(width > 0) || !(height > 0))
        return E_INVALIDARG;
    const float far_plane = __builtin_bit_cast(float, shaiya::config::DAT_00719874);
    const float near_plane = __builtin_bit_cast(float, shaiya::config::DAT_00719878);
    if (!(near_plane > 0) || !(far_plane > near_plane))
        return E_INVALIDARG;
    auto* scope = *reinterpret_cast<TargetScope**>(static_cast<unsigned char*>(owner) + 0x1408);
    auto* image = *reinterpret_cast<Texture2D**>(static_cast<unsigned char*>(owner) + 0x1410);
    if (!scope || !image)
        return E_UNEXPECTED;
    const float transparent[4] = {0, 0, 0, 0};
    HRESULT result = begin_target(*scope, *image, nullptr, transparent);
    if (FAILED(result))
        return result;
    saved_draw = new (saved_storage) SceneDrawScope;
    active = true;
    Matrix projection = {};
    // The CPU skin builder supplies max(abs(viewX/viewZ)) and its Y
    // counterpart, not frustum dimensions. The original0.98 scale leaves
    // a small border around the complete animated silhouette.
    projection.m[0][0] = 0.98f / width;
    projection.m[1][1] = 0.98f / height;
    projection.m[2][2] = far_plane / (far_plane - near_plane);
    projection.m[2][3] = 1;
    projection.m[3][2] = -near_plane * far_plane / (far_plane - near_plane);
    *reinterpret_cast<Matrix*>(dat_0220aa50) = projection;
    auto* current = renderer();
    Scene scene = current->scene;
    scene.view = *reinterpret_cast<Matrix*>(dat_0220aa90);
    scene.view_projection = multiply(scene.view, projection);
    shadow_view_projection = scene.view_projection;
    scene.fog_enabled = false;
    for (float& value : scene.clip_plane)
        value = 0;
    result = begin_scene(*current, scene);
    auto& draw = scene_draw_context();
    draw.world = *reinterpret_cast<Matrix*>(dat_0220bee8);
    draw.lit = false;
    draw.actor_pipeline = ActorPipeline::lit_model;
    draw.actor_reflection = false;
    draw.projected_shadow = false;
    draw.material.style.blend = Blend::opaque;
    draw.material.style.depth = Depth::write;
    draw.material.style.cull = Cull::none;
    draw.material.style.tint = {0, 0, 0, 1};
    draw.material.style.alpha_cutoff = textured ? 7.5f / 255.0f : 0;
    set_scene_diffuse(nullptr);
    return result;
}
} // namespace
extern "C" HRESULT __attribute__((thiscall)) FUN_005484e0(void* owner, float width, float height) {
    return begin_shadow(owner, width, height, false);
}
extern "C" HRESULT __attribute__((thiscall)) FUN_005486a0(void* owner, float width, float height) {
    return begin_shadow(owner, width, height, true);
}
extern "C" HRESULT __attribute__((thiscall)) FUN_00548860(void* owner) {
    using namespace shaiya::graphics::native;
    auto* scope = *reinterpret_cast<TargetScope**>(static_cast<unsigned char*>(owner) + 0x1408);
    if (!active || !scope)
        return E_UNEXPECTED;
    HRESULT result = end_target(*scope);
    saved_draw->~SceneDrawScope();
    saved_draw = nullptr;
    active = false;
    return result;
}
extern "C" void __attribute__((thiscall)) FUN_00548880(void* owner) {
    using namespace shaiya::graphics::native;
    Matrix bias = identity();
    bias.m[0][0] = .5f;
    bias.m[1][1] = -.5f;
    bias.m[3][0] = bias.m[3][1] = .5f;
    auto& draw = scene_draw_context();
    draw.projected_shadow = true;
    draw.shadow_projection = multiply(shadow_view_projection, bias);
    set_scene_shadow_map(
        *reinterpret_cast<Texture2D**>(static_cast<unsigned char*>(owner) + 0x1410));
    draw.material.style.blend = Blend::alpha;
    draw.material.style.depth = Depth::read;
    draw.material.style.cull = Cull::back;
    draw.material.style.alpha_cutoff = 0;
    draw.lit = false;
}
extern "C" void __attribute__((thiscall)) FUN_00548ec0(void*, Matrix* output) {
    prepare_view(20);
    if (output)
        *output = multiply(*reinterpret_cast<Matrix*>(dat_0220bee8),
                           *reinterpret_cast<Matrix*>(dat_0220aa90));
}
extern "C" HRESULT __attribute__((thiscall)) FUN_00548f70(void* owner, float width, float height) {
    prepare_view(.01f);
    return begin_shadow(owner, width, height, true);
}
