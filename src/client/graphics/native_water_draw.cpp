#include "graphics/native_water_draw.h"
#include "graphics/native_render_target.h"
#include "graphics/native_scene_ports.h"

extern "C" {
extern unsigned char dat_02209408[];
extern float dat_0220e060[], dat_0085d138;
void __attribute__((thiscall)) FUN_0053ded0(void*);
unsigned char __attribute__((thiscall)) FUN_0053fa40(void*);
unsigned char __attribute__((thiscall)) FUN_0053ff10(void*);
void __attribute__((thiscall)) FUN_00542bf0(void*);
void __cdecl FUN_005afc00(const float*);
}
using namespace shaiya::graphics::native;
namespace {
template <class T> T& field(void* owner, UINT offset) {
    return *reinterpret_cast<T*>(static_cast<unsigned char*>(owner) + offset);
}
Matrix identity() {
    Matrix result = {};
    for (UINT i = 0; i < 4; ++i)
        result.m[i][i] = 1;
    return result;
}
void copy_bytes(void* to, const void* from, UINT size) {
    auto* out = static_cast<unsigned char*>(to);
    const auto* in = static_cast<const unsigned char*>(from);
    for (UINT i = 0; i < size; ++i)
        out[i] = in[i];
}
struct SceneRestore {
    NativeRenderer& renderer;
    Scene scene;
    Matrix projection;
    explicit SceneRestore(NativeRenderer& value)
        : renderer(value), scene(value.scene), projection(value.projection) {}
    void restore() {
        renderer.projection = projection;
        begin_scene(renderer, scene);
    }
    ~SceneRestore() {
        restore();
    }
};
struct ScreenVertex {
    float x, y, z, rhw;
    UINT color;
};
} // namespace

// Underwater attenuation is an explicit screen-color pass with constant blending.
extern "C" HRESULT __attribute__((thiscall)) FUN_0053f470(void* owner) {
    if (!owner)
        return E_POINTER;
    auto* source = field<Buffer*>(owner, 0x2e4);
    if (!source || !source->asset_bytes || source->size < sizeof(ScreenVertex) * 4)
        return E_INVALIDARG;
    const auto* input = reinterpret_cast<const ScreenVertex*>(source->asset_bytes);
    UiVertex vertices[4];
    const UINT order[4] = {1, 3, 2, 0};
    for (UINT i = 0; i < 4; ++i) {
        const auto& v = input[order[i]];
        vertices[i] = {v.x, v.y, v.z, v.rhw, v.color, 0, 0};
    }
    UINT factor = UINT(INT((1 - dat_0085d138) * .7f * 255)) & 255;
    const float amount = float(factor) / 255;
    UiDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 4;
    draw.primitive = UiPrimitive::quad;
    draw.style.alpha_cutoff = 0;
    draw.style.source_blend = D3D11_BLEND_BLEND_FACTOR;
    draw.style.destination_blend = D3D11_BLEND_INV_BLEND_FACTOR;
    draw.style.blend_factor = {amount, amount, amount, amount};
    SceneDrawScope material_scope;
    return draw_ui(*renderer(), draw);
}

// Capture callbacks retain the authored world recursion and camera ordering.
extern "C" HRESULT __attribute__((thiscall)) FUN_005403b0(void* owner) {
    if (!owner)
        return E_POINTER;
    const UINT mode = field<UINT>(owner, 0);
    if (mode > 1 || !field<unsigned char>(owner, 4) || field<unsigned char>(owner, 0x1d0))
        return S_FALSE;
    auto* scope = field<TargetScope*>(owner, 0x10);
    if (scope && scope->active)
        return S_FALSE;
    auto* geometry = field<Buffer*>(owner, 0x2e0);
    auto* reflected = field<Texture2D*>(owner, 0xf4);
    if (!geometry || !reflected)
        return E_POINTER;
    auto& current = *renderer();
    SceneDrawScope material_scope;
    SceneRestore scene_scope(current);
    FUN_0053ded0(owner);
    FUN_00542bf0(dat_02209408);
    if (mode == 1 && !FUN_0053fa40(owner))
        return S_FALSE;
    copy_bytes(static_cast<unsigned char*>(owner) + 0x30, dat_02209408 + 0xfc, 192);
    const bool reflection_ok = FUN_0053ff10(owner) != 0;
    FUN_005afc00(dat_0220e060);
    copy_bytes(dat_02209408 + 0xfc, static_cast<unsigned char*>(owner) + 0x30, 192);
    scene_scope.restore();
    if (!reflection_ok)
        return S_FALSE;
    const auto& captured = water_capture_state();
    if (captured.owner != owner || !captured.reflection_valid ||
        (mode == 1 && !captured.refraction_valid))
        return E_FAIL;
    WaterDraw draw;
    draw.mesh.vertices = geometry->gpu;
    draw.world = identity();
    draw.material.style = {Blend::alpha, Depth::read, Cull::none, Sampling::linear_wrap};
    draw.material.style.alpha_cutoff = 0;
    draw.reflection = reflected->view;
    draw.reflection_projection = captured.reflection;
    if (mode == 0) {
        auto* normal = field<Texture2D*>(owner, 0x2dc);
        if (!normal)
            return E_POINTER;
        draw.material.diffuse = normal->view;
        draw.normal_signed = true;
        return draw_water32(current, draw);
    }
    auto* normal = field<Texture2D*>(owner, 0x2f0);
    auto* second = field<Texture2D*>(owner, 0x2f4);
    auto* refracted = field<Texture2D*>(owner, 0xf8);
    if (!normal || !second || !refracted)
        return E_POINTER;
    draw.material.diffuse = normal->view;
    draw.normal_second = second->view;
    draw.refraction = refracted->view;
    draw.refraction_projection = captured.refraction;
    const float phase = field<float>(owner, 0x300);
    draw.uv_offset[0] = phase;
    draw.uv_offset[1] = phase;
    draw.second_uv_offset[0] = -phase;
    draw.second_uv_offset[1] = phase;
    draw.reflectivity = .1f;
    return draw_water56(current, draw);
}
