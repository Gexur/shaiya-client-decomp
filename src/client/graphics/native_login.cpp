#include "graphics/native_renderer.h"
#include "graphics/native_scene_ports.h"

extern "C" void __cdecl native_material_source_alpha();
extern "C" void __cdecl native_scene_blend_additive();
extern "C" void __cdecl native_scene_blend_alpha();

namespace {
using namespace shaiya::graphics::native;
float flash_intensity = 1;
HRESULT weather_quad(void* owner, UINT buffer_offset, float intensity) {
    auto* buffer = *reinterpret_cast<Buffer**>(static_cast<unsigned char*>(owner) + buffer_offset);
    if (buffer == nullptr || buffer->asset_bytes == nullptr ||
        buffer->size < sizeof(WorldVertex) * 4)
        return E_INVALIDARG;
    const auto* quad = reinterpret_cast<const WorldVertex*>(buffer->asset_bytes);
    const WorldVertex vertices[6] = {quad[0], quad[1], quad[2], quad[0], quad[2], quad[3]};
    WorldDraw draw;
    auto& source = scene_draw_context();
    draw.vertices = vertices;
    draw.vertex_count = 6;
    draw.world = source.world;
    draw.material.diffuse = source.diffuse != nullptr ? source.diffuse->view : nullptr;
    draw.material.style = {Blend::additive, Depth::read, Cull::none, Sampling::linear_wrap};
    draw.material.style.tint.a = intensity;
    draw.material.style.alpha_cutoff = 0;
    return draw_world_triangles(*renderer(), draw);
}
void fog(uint32_t argb, float far_distance) {
    auto* current = renderer();
    current->scene.fog_color = {float((argb >> 16) & 255) / 255, float((argb >> 8) & 255) / 255,
                                float(argb & 255) / 255, float(argb >> 24) / 255};
    current->scene.fog_enabled = true;
    current->scene.fog_start = 20;
    current->scene.fog_end = far_distance;
    begin_scene(*current, current->scene);
}
} // namespace

extern "C" void __attribute__((stdcall)) native_login_world(const Matrix* world) {
    scene_draw_context().world = *world;
}
extern "C" void __attribute__((stdcall)) native_login_dungeon_fog(uint32_t color) {
    fog(color, 500);
}
extern "C" void __attribute__((stdcall)) native_login_backdrop_fog(uint32_t color) {
    fog(color, 1000);
}
extern "C" void __cdecl native_login_fog_off() {
    auto* current = renderer();
    current->scene.fog_enabled = false;
    begin_scene(*current, current->scene);
}
extern "C" void __cdecl native_login_weather_begin() {
    flash_intensity = 1;
}
extern "C" void __cdecl native_login_models_unlit() {
    scene_draw_context().lit = false;
}
extern "C" void __cdecl native_login_models_lit() {
    scene_draw_context().lit = true;
}
extern "C" void __cdecl native_login_models_additive() {
    native_material_source_alpha();
    native_scene_blend_additive();
    auto& style = scene_draw_context().material.style;
    style.blend = Blend::additive;
    style.source_blend = style.destination_blend = D3D11_BLEND(0);
}
extern "C" void __cdecl native_login_models_alpha() {
    native_material_source_alpha();
    native_scene_blend_alpha();
    auto& style = scene_draw_context().material.style;
    style.blend = Blend::alpha;
    style.source_blend = style.destination_blend = D3D11_BLEND(0);
}
extern "C" void __attribute__((stdcall)) native_login_flash_intensity(uint32_t argb) {
    flash_intensity = float(argb >> 24) / 255;
}
extern "C" HRESULT __attribute__((stdcall)) native_login_weather_first(void* owner) {
    return weather_quad(owner, 0x49dc, 1);
}
extern "C" HRESULT __attribute__((stdcall)) native_login_weather_second(void* owner) {
    return weather_quad(owner, 0x49e0, 1);
}
extern "C" HRESULT __attribute__((stdcall)) native_login_weather_third(void* owner) {
    return weather_quad(owner, 0x49e8, 1);
}
extern "C" HRESULT __attribute__((stdcall)) native_login_weather_flash(void* owner) {
    return weather_quad(owner, 0x49e4, flash_intensity);
}
extern "C" HRESULT __attribute__((stdcall)) native_login_weather_snow(void* owner) {
    return weather_quad(owner, 0x49ec, 1);
}
extern "C" void __attribute__((thiscall)) FUN_0053dc50(void* texture, UINT channel) {
    auto* image = *reinterpret_cast<Texture2D**>(static_cast<unsigned char*>(texture) + 4);
    if (channel == 0)
        set_scene_diffuse(image);
    else if (channel == 1)
        set_scene_lightmap(image);
}

// This game entry receives four authored positions and a native texture. It
// submits one explicit World24 pass; no legacy declaration or device state.
extern "C" HRESULT __attribute__((stdcall)) FUN_004b8490(void*, float, float, float, float, float,
                                                         float, float, float, float, float, float,
                                                         float,
                                                         Texture2D*) __asm__("_FUN_004b8490");
extern "C" HRESULT __attribute__((stdcall)) FUN_004b8490(void*, float x0, float y0, float z0,
                                                         float x1, float y1, float z1, float x2,
                                                         float y2, float z2, float x3, float y3,
                                                         float z3, Texture2D* texture) {
    const WorldVertex quad[4] = {{{x0, y0, z0}, 0xffbbbbbb, {0, 1}},
                                 {{x1, y1, z1}, 0xffbbbbbb, {0, 0}},
                                 {{x3, y3, z3}, 0xffbbbbbb, {1, 0}},
                                 {{x2, y2, z2}, 0xffbbbbbb, {1, 1}}};
    const WorldVertex vertices[6] = {quad[0], quad[1], quad[2], quad[0], quad[2], quad[3]};
    WorldDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 6;
    draw.world = scene_draw_context().world;
    draw.material.diffuse = texture != nullptr ? texture->view : nullptr;
    draw.material.style = {Blend::opaque, Depth::disabled, Cull::none, Sampling::linear_wrap};
    draw.material.style.alpha_cutoff = 0;
    return draw_world_triangles(*renderer(), draw);
}
