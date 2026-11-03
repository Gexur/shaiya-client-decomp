#include "graphics/native_scene_ports.h"
#include "graphics/native_renderer.h"
#include "core/x87_runtime.h"

using namespace shaiya::graphics::native;
extern "C" {
extern unsigned char dat_0224e498[];
extern float dat_0224e644, dat_0224e648, dat_0224e64c;
extern const float dat_006cf0f8;
void __attribute__((thiscall)) FUN_005a3480(void*, float, float);
}

namespace {
float patch_origin(float coordinate) {
    const UINT cell =
        UINT(x87_to_integer_005cd414(static_cast<long double>(coordinate) * dat_006cf0f8));
    return float(__builtin_bit_cast(int32_t, 0xfffffff8u - (cell << 3)));
}
HRESULT terrain_projection(void* terrain, float x, float z, float height_offset, bool effect) {
    auto& state = scene_draw_context();
    if (!terrain || !state.projected_shadow || !state.shadow_map || !state.shadow_map->view)
        return E_UNEXPECTED;

    // The original CPU operation snaps this small receiver to an eight-unit
    // terrain cell, then copies the actual terrain heights into its World24 VB.
    Matrix world = {};
    world.m[0][0] = world.m[2][2] = dat_0224e64c;
    world.m[1][1] = dat_0224e648;
    world.m[3][0] = patch_origin(x);
    world.m[3][1] = dat_0224e644 + height_offset;
    world.m[3][2] = patch_origin(z);
    world.m[3][3] = 1;
    state.world = world;
    FUN_005a3480(terrain, x, z);

    const auto* vertices = *reinterpret_cast<Buffer**>(dat_0224e498 + 0x8c);
    const auto* indices = *reinterpret_cast<Buffer**>(dat_0224e498 + 0x90);
    const UINT triangles = *reinterpret_cast<UINT*>(dat_0224e498 + 0xa0);
    if (!vertices || !indices || vertices->stride != sizeof(WorldVertex) || indices->stride != 2 ||
        triangles > indices->size / 6)
        return E_INVALIDARG;
    ShadowDraw draw;
    draw.mesh.vertices = vertices->gpu;
    draw.mesh.indices = indices->gpu;
    draw.mesh.index_format = indices->index_format;
    draw.mesh.index_count = triangles * 3;
    draw.world = world;
    draw.material = state.material;
    draw.material.style = {effect ? Blend::additive : Blend::alpha, Depth::read, Cull::back,
                           Sampling::linear_clamp};
    draw.material.style.alpha_cutoff = 0;
    draw.shadow = state.shadow_map->view;
    draw.projector = state.shadow_projection;
    return effect ? draw_projected_world_effect(*renderer(), draw)
                  : draw_projected_world_shadow(*renderer(), draw);
}
} // namespace

extern "C" HRESULT __attribute__((thiscall)) FUN_005a3550(void* terrain, float x, float z,
                                                          float height_offset) {
    return terrain_projection(terrain, x, z, height_offset, false);
}
extern "C" HRESULT __attribute__((thiscall))
native_terrain_projected_effect(void* terrain, float x, float z, float height_offset) {
    return terrain_projection(terrain, x, z, height_offset, true);
}
