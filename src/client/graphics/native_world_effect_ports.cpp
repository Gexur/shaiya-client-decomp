#include "graphics/native_scene_ports.h"
#include "graphics/native_renderer.h"

using namespace shaiya::graphics::native;
extern "C" {
extern void* dat_00719318;
extern const float dat_006bc85c;
void __attribute__((thiscall)) FUN_0054e490(void*, UINT);
HRESULT __attribute__((thiscall)) FUN_0054f860(void*);
HRESULT __attribute__((stdcall)) FUN_00444060(NativeRenderer*, float, float, float, float, float,
                                              float, float, float, float, float, float,
                                              float) __asm__("_FUN_00444060");
}
namespace {
template <class T> T& field(void* owner, UINT offset) {
    return *reinterpret_cast<T*>(static_cast<unsigned char*>(owner) + offset);
}
} // namespace
extern "C" HRESULT __attribute__((stdcall)) FUN_00444060(NativeRenderer* current, float x0,
                                                         float y0, float z0, float x1, float y1,
                                                         float z1, float x2, float y2, float z2,
                                                         float x3, float y3, float z3) {
    if (!current)
        return E_POINTER;
    WorldVertex corners[4] = {{{x0, y0, z0}, 0x908056b4, {}},
                              {{x1, y1, z1}, 0x900056b4, {}},
                              {{x2, y2, z2}, 0x9000ffb4, {}},
                              {{x3, y3, z3}, 0x90ff56ff, {}}};
    WorldVertex triangles[6];
    const UINT indices[6] = {0, 1, 2, 0, 2, 3};
    for (UINT i = 0; i < 6; ++i)
        triangles[i] = corners[indices[i]];
    set_scene_diffuse(nullptr);
    set_scene_lightmap(nullptr);
    WorldDraw draw;
    draw.vertices = triangles;
    draw.vertex_count = 6;
    draw.world = scene_draw_context().world;
    draw.material = scene_draw_context().material;
    draw.material.diffuse = nullptr;
    draw.material.style.tint = {1, 1, 1, 1};
    return draw_world_triangles(*current, draw);
}
extern "C" HRESULT __attribute__((thiscall)) FUN_0054fa20(void* owner, float,
                                                          NativeRenderer* current) {
    if (!owner || !current)
        return E_POINTER;
    const float fade = field<float>(owner, 4);
    if (fade < dat_006bc85c)
        return S_FALSE;
    if (dat_00719318) {
        UINT prior = field<UINT>(dat_00719318, 0x90);
        FUN_0054e490(dat_00719318, 2);
        FUN_0054f860(dat_00719318);
        FUN_0054e490(dat_00719318, prior);
        auto* captured = field<Texture2D*>(dat_00719318, 0x14);
        if (captured)
            field<Texture2D*>(owner, 0) = captured;
    }
    IndexedWorldDraw draw;
    draw.vertices =
        reinterpret_cast<const WorldVertex*>(static_cast<const unsigned char*>(owner) + 0x10ec);
    draw.vertex_count = 0x21c;
    draw.indices =
        reinterpret_cast<const uint16_t*>(static_cast<const unsigned char*>(owner) + 0x438c);
    draw.index_count = 0x3dc * 3;
    draw.texture_only = true;
    draw.world = scene_draw_context().world;
    draw.material = scene_draw_context().material;
    auto* image = field<Texture2D*>(owner, 0);
    set_scene_diffuse(image);
    draw.material.diffuse = image ? image->view : nullptr;
    const UINT alpha = UINT(INT(fade * 255)) & 255;
    draw.material.style.blend = Blend::alpha;
    draw.material.style.source_blend = D3D11_BLEND(0);
    draw.material.style.destination_blend = D3D11_BLEND(0);
    draw.material.style.tint = {1, 1, 1, float(alpha) / 255};
    draw.material.style.alpha_cutoff = 2.5f / 255;
    return draw_world_indexed_triangles(*current, draw);
}
