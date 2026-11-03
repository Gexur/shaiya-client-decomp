#include "graphics/native_scene_ports.h"
#include "graphics/native_renderer.h"
#include <stdint.h>
using namespace shaiya::graphics::native;
extern "C" {
extern unsigned char dat_0070ca50, dat_0070ca51, dat_0070ca52;
}
namespace {
using Word = uint32_t __attribute__((may_alias));
Word& word(void* object, UINT offset) {
    return *reinterpret_cast<Word*>(static_cast<unsigned char*>(object) + offset);
}
void* address(void* object, UINT offset) {
    return static_cast<unsigned char*>(object) + offset;
}
template <class T> T* pointer(void* object, UINT offset) {
    return reinterpret_cast<T*>(word(object, offset));
}
Texture2D* texture(void* record) {
    return record ? pointer<Texture2D>(record, 0x204) : nullptr;
}
bool geometry(StaticDraw& draw, void* part, const UINT* range, UINT stride) {
    auto* vertices = pointer<Buffer>(part, 0);
    auto* indices = pointer<Buffer>(part, 4);
    if (!vertices || !indices || vertices->stride != stride || indices->stride != 2 ||
        range[1] > indices->size / 2 || range[3] > (indices->size / 2 - range[1]) / 3)
        return false;
    draw.mesh.vertices = vertices->gpu;
    draw.mesh.indices = indices->gpu;
    draw.mesh.index_format = indices->index_format;
    draw.mesh.first_index = range[1];
    draw.mesh.index_count = range[3] * 3;
    draw.mesh.base_vertex = static_cast<INT>(range[0]);
    draw.world = scene_draw_context().world;
    draw.material = scene_draw_context().material;
    return true;
}
void terrain_layers(void* object, bool detail_in_layer) {
    void* terrain = pointer<void>(object, 0x88);
    auto* layers = pointer<unsigned char>(object, 0x68);
    if (!terrain || !layers)
        return;
    int count = int(word(object, 0x70));
    if (count > 8)
        count = 8;
    Texture2D* detail = dat_0070ca52 ? texture(address(terrain, 0x4e008)) : nullptr;
    bool rendered = false;
    for (int layer = 0; layer < count; ++layer) {
        const auto* values = static_cast<const UINT*>(address(terrain, 0x4f278 + layer * 16));
        void* properties = layers + layer * 0x438;
        if (int(values[3]) <= 0 || !word(properties, 0x304))
            continue;
        MultiTextureDraw draw;
        if (!geometry(draw, address(object, detail_in_layer ? 0x4c : 0x30), values,
                      detail_in_layer ? 36 : 28))
            continue;
        Texture2D* base = texture(address(terrain, 0x4e210 + layer * 0x208));
        Texture2D* secondary = dat_0070ca51 ? texture(address(properties, 0x100)) : nullptr;
        draw.material.diffuse = base ? base->view : nullptr;
        draw.material.style = {rendered ? Blend::alpha : Blend::opaque, Depth::write, Cull::none,
                               Sampling::linear_clamp};
        draw.material.projected_texture = false;
        draw.material.style.alpha_cutoff = rendered ? 7.5f / 255 : 0;
        draw.secondary = secondary ? secondary->view : nullptr;
        draw.detail = detail_in_layer && detail ? detail->view : nullptr;
        draw.use_diffuse_rgb = dat_0070ca50 != 0;
        draw.secondary_blend = !secondary     ? SecondaryBlend::multiply
                               : dat_0070ca50 ? SecondaryBlend::add_signed
                                              : SecondaryBlend::replace;
        if (detail_in_layer)
            draw_textured_world_indexed_multi36(*renderer(), draw);
        else
            draw_textured_world_indexed_multi28(*renderer(), draw);
        rendered = true;
        word(object, 0x80) += values[3];
        word(object, 0x84) += values[2];
    }
    if (!detail_in_layer && detail) {
        const auto* values = static_cast<const UINT*>(address(terrain, 0x4f2f8));
        StaticDraw draw;
        if (geometry(draw, address(object, 0x14), values, 20)) {
            draw.material.diffuse = detail->view;
            draw.material.style = {Blend::multiply, Depth::write, Cull::none,
                                   Sampling::linear_clamp};
            draw.material.style.alpha_cutoff = 7.5f / 255;
            draw_textured_world_indexed(*renderer(), draw);
            word(object, 0x80) += values[3];
            word(object, 0x84) += values[2];
        }
    }
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_005b1710(void* object) {
    terrain_layers(object, true);
}
extern "C" void __attribute__((thiscall)) FUN_005b1f60(void* object) {
    terrain_layers(object, false);
}
