#include "graphics/native_renderer.h"
#include "graphics/native_scene_ports.h"

using namespace shaiya::graphics::native;

extern "C" HRESULT __attribute__((stdcall))
native_character_shadow_strip(UINT triangles, const WorldVertex* strip) {
    if (triangles != 2 || !strip)
        return E_INVALIDARG;
    const auto& scene = scene_draw_context();
    if (!scene.projected_shadow || !scene.shadow_map || !scene.shadow_map->view)
        return E_UNEXPECTED;

    // The selection controller authors a horizontal four-vertex strip. Its
    // texture coordinates come from the captured actor-shadow projector,
    // independently of the actor's most recently bound equipment texture.
    const WorldVertex vertices[6] = {strip[0], strip[1], strip[2], strip[2], strip[1], strip[3]};
    WorldDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 6;
    draw.world = scene.world;
    draw.material = scene.material;
    draw.material.style.depth = Depth::read;
    draw.material.style.cull = Cull::back;
    return draw_projected_world_triangles(*renderer(), draw, scene.shadow_map->view,
                                          scene.shadow_projection);
}
