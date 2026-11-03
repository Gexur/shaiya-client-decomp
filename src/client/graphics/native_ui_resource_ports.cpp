#include "graphics/native_scene_ports.h"
#include "graphics/native_renderer.h"
using namespace shaiya::graphics::native;
extern "C" Texture2D* dat_0085d3a4;
extern "C" HRESULT __attribute__((thiscall)) FUN_004c58c0(void* owner, UINT argb, int x, int y,
                                                          UINT width, UINT height, float mask_u0,
                                                          float mask_u1, float mask_v0,
                                                          float mask_v1) {
    auto** fields = static_cast<void**>(owner);
    auto* buffer = static_cast<Buffer*>(fields[0]);
    auto* image = static_cast<Texture2D*>(fields[1]);
    if (!buffer || !image || buffer->stride != sizeof(UiDualVertex36) ||
        buffer->size < sizeof(UiDualVertex36) * 4)
        return E_INVALIDARG;
    const float left = float(x) - .5f, top = float(y) - .5f,
                right = float(int(UINT(x) + width)) - .5f,
                bottom = float(int(UINT(y) + height)) - .5f;
    const UiDualVertex36 vertices[] = {{left, top, 1, 1, argb, 0, 0, mask_u0, mask_v0},
                                       {right, top, 1, 1, argb, 1, 0, mask_u1, mask_v0},
                                       {right, bottom, 1, 1, argb, 1, 1, mask_u1, mask_v1},
                                       {left, bottom, 1, 1, argb, 0, 1, mask_u0, mask_v1}};
    HRESULT result = update_buffer(*renderer(), *buffer, 0, vertices, sizeof(vertices));
    if (FAILED(result))
        return result;
    if (!dat_0085d3a4) {
        // The authored missing-map branch selects opaque black RGB while
        // retaining the circular background's alpha and the vertex opacity.
        UiVertex fallback[4];
        for (UINT i = 0; i < 4; ++i)
            fallback[i] = {vertices[i].x, vertices[i].y, 1, 1, argb & 0xff000000,
                           vertices[i].u, vertices[i].v};
        UiDraw draw;
        draw.vertices = fallback;
        draw.vertex_count = 4;
        draw.primitive = UiPrimitive::quad;
        draw.image = image->view;
        draw.style.depth = scene_draw_context().ui_depth;
        return draw_ui(*renderer(), draw);
    }
    UiDualDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 4;
    draw.image = image->view;
    draw.mask = dat_0085d3a4->view;
    // The background supplies the circular alpha; the second UV set selects
    // map RGB. The original combines both alpha channels with vertex opacity.
    draw.use_mask_rgb = true;
    draw.style.depth = scene_draw_context().ui_depth;
    // Authored world-Z coordinates produce negative map V (for example -1..-.5).
    draw.style.sampling = Sampling::linear_wrap;
    return draw_ui_dual36(*renderer(), draw);
}
