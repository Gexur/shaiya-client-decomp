#include "graphics/native_render_passes.h"
#include "graphics/native_renderer.h"
#include "graphics/native_scene_ports.h"
#include "startup/application.h"
extern "C" void __attribute__((stdcall)) native_scene_depth_test(UINT enabled);

extern "C" HRESULT __attribute__((stdcall))
native_ui_triangle(const shaiya::graphics::native::UiVertex* vertices) {
    using namespace shaiya::graphics::native;
    if (!dat_02209400)
        return E_UNEXPECTED;
    if (!vertices)
        return E_INVALIDARG;
    // Both cooldown fans supply solid vertex colors and leave UVs unset.
    // Use the pass's white fallback without reading those unused coordinates.
    UiVertex solid[3];
    for (UINT i = 0; i < 3; ++i)
        solid[i] = {vertices[i].x, vertices[i].y, vertices[i].z, vertices[i].rhw,
                    vertices[i].argb, 0, 0};
    UiImageScope preserve_image(*dat_02209400);
    UiDraw draw;
    draw.vertices = solid;
    draw.vertex_count = 3;
    // The original stage modulates DIFFUSE with CURRENT, also DIFFUSE at
    // stage zero. Both fans use one uniform color; tint supplies its second
    // factor, including the squared opacity, without quantizing it to a byte.
    const uint32_t color = solid[0].argb;
    draw.style.tint = {float((color >> 16) & 255) / 255, float((color >> 8) & 255) / 255,
                       float(color & 255) / 255, float(color >> 24) / 255};
    return draw_ui(*dat_02209400, draw);
}
extern "C" HRESULT __attribute__((stdcall))
native_ui_quad(const shaiya::graphics::native::UiVertex* vertices) {
    using namespace shaiya::graphics::native;
    if (!dat_02209400)
        return E_UNEXPECTED;
    UiDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 4;
    draw.primitive = UiPrimitive::quad;
    draw.image = dat_02209400->ui_image;
    draw.style.depth = scene_draw_context().ui_depth;
    return draw_ui(*dat_02209400, draw);
}
extern "C" HRESULT __attribute__((stdcall))
native_ui_image(shaiya::graphics::native::Texture2D* image) {
    if (!dat_02209400)
        return E_UNEXPECTED;
    dat_02209400->set_ui_image(image ? image->view : nullptr);
    return S_OK;
}
extern "C" void __attribute__((thiscall)) FUN_00541bb0(void*, int enabled) {
    using namespace shaiya::graphics::native;
    native_scene_depth_test(enabled);
    scene_draw_context().ui_depth = scene_draw_context().material.style.depth;
}
extern "C" HRESULT __attribute__((stdcall))
native_billboard_image(shaiya::graphics::native::Texture2D* image) {
    shaiya::graphics::native::set_scene_diffuse(image);
    return S_OK;
}
extern "C" HRESULT __attribute__((stdcall))
native_billboard_strip(const shaiya::graphics::native::WorldVertex* quad) {
    using namespace shaiya::graphics::native;
    const WorldVertex vertices[6] = {quad[0], quad[1], quad[2], quad[2], quad[1], quad[3]};
    auto& state = scene_draw_context();
    WorldDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 6;
    draw.world = state.world;
    draw.material.diffuse = state.diffuse ? state.diffuse->view : nullptr;
    draw.material.style = {Blend::alpha, Depth::read, Cull::none, Sampling::linear_wrap};
    draw.material.style.alpha_cutoff = 0;
    return draw_world_triangles(*dat_02209400, draw);
}
