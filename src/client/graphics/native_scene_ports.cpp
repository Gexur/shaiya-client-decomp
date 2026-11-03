#include "graphics/native_scene_ports.h"
#include "graphics/native_renderer.h"
#include <stdint.h>
namespace {
using namespace shaiya::graphics::native;
struct Part {
    Buffer* vertices;
    Buffer* indices;
    uint32_t vertex_capacity, index_capacity, vertex_count, triangles, reserved, texture;
};
static_assert(sizeof(Part) == 32);
struct Model {
    int count;
    Part* parts;
};
struct DungeonGroup {
    int texture;
    int count;
    Part* parts;
};
SceneDrawContext current_draw;
void bind(Texture2D*& destination, Texture2D* texture) {
    if (destination == texture)
        return;
    if (texture != nullptr)
        texture->retain();
    auto* previous = destination;
    destination = texture;
    if (previous != nullptr)
        previous->release();
}
void retain_textures(const SceneDrawContext& value) {
    for (auto* texture : (Texture2D* const[]){value.diffuse, value.lightmap, value.detail,
                                              value.environment, value.shadow_map})
        if (texture != nullptr)
            texture->retain();
}
void release_textures(const SceneDrawContext& value) {
    for (auto* texture : (Texture2D* const[]){value.diffuse, value.lightmap, value.detail,
                                              value.environment, value.shadow_map})
        if (texture != nullptr)
            texture->release();
}
uint32_t word(const void* object, UINT offset) {
    return *reinterpret_cast<const uint32_t*>(static_cast<const unsigned char*>(object) + offset);
}
Texture2D* image(const void* object) {
    return object ? reinterpret_cast<Texture2D*>(word(object, 0x204)) : nullptr;
}
StaticDraw static_draw(const Part& part) {
    StaticDraw draw;
    draw.mesh.vertices = part.vertices ? part.vertices->gpu : nullptr;
    draw.mesh.indices = part.indices ? part.indices->gpu : nullptr;
    draw.mesh.index_format = part.indices ? part.indices->index_format : DXGI_FORMAT_R16_UINT;
    draw.mesh.index_count = part.triangles * 3;
    draw.world = current_draw.world;
    draw.material = current_draw.material;
    draw.material.diffuse = current_draw.diffuse ? current_draw.diffuse->view : nullptr;
    return draw;
}
} // namespace
namespace shaiya::graphics::native {
SceneDrawContext& scene_draw_context() {
    return current_draw;
}
void set_scene_diffuse(Texture2D* texture) {
    bind(current_draw.diffuse, texture);
    renderer()->set_ui_image(texture != nullptr ? texture->view : nullptr);
}
void set_scene_lightmap(Texture2D* texture) {
    bind(current_draw.lightmap, texture);
}
void set_scene_detail(Texture2D* texture) {
    bind(current_draw.detail, texture);
}
void set_scene_environment(Texture2D* texture) {
    bind(current_draw.environment, texture);
}
void set_scene_shadow_map(Texture2D* texture) {
    bind(current_draw.shadow_map, texture);
}
void release_scene_textures() {
    set_scene_diffuse(nullptr);
    set_scene_lightmap(nullptr);
    set_scene_detail(nullptr);
    set_scene_environment(nullptr);
    set_scene_shadow_map(nullptr);
}
SceneDrawScope::SceneDrawScope() : saved(current_draw), saved_ui_image(renderer()->ui_image) {
    retain_textures(saved);
    if (saved_ui_image != nullptr)
        saved_ui_image->AddRef();
}
SceneDrawScope::~SceneDrawScope() {
    set_scene_diffuse(saved.diffuse);
    set_scene_lightmap(saved.lightmap);
    set_scene_detail(saved.detail);
    set_scene_environment(saved.environment);
    set_scene_shadow_map(saved.shadow_map);
    current_draw = saved;
    release_textures(saved);
    renderer()->set_ui_image(saved_ui_image);
    if (saved_ui_image != nullptr)
        saved_ui_image->Release();
}
} // namespace shaiya::graphics::native
extern "C" void __attribute__((thiscall)) FUN_005afde0(void* texture, UINT channel) {
    if (channel == 0)
        set_scene_diffuse(image(texture));
    else if (channel == 1)
        set_scene_lightmap(image(texture));
}
extern "C" void __attribute__((thiscall)) FUN_005a4090(void* dungeon) {
    current_draw.use_lightmaps = *(static_cast<const unsigned char*>(dungeon) + 0x368) != 0;
    current_draw.material.style = {Blend::opaque, Depth::write, Cull::none, Sampling::linear_wrap};
}
extern "C" HRESULT __attribute__((thiscall)) FUN_004b8f80(void* object, UINT) {
    StaticDraw draw = static_draw(*static_cast<Part*>(object));
    return current_draw.lit ? draw_lit(*renderer(), draw) : draw_static(*renderer(), draw);
}
extern "C" HRESULT __attribute__((thiscall)) FUN_005a4c10(void* object, UINT) {
    LightmapDraw draw;
    static_cast<StaticDraw&>(draw) = static_draw(*static_cast<Part*>(object));
    draw.lightmap =
        current_draw.use_lightmaps && current_draw.lightmap ? current_draw.lightmap->view : nullptr;
    return draw_lightmap(*renderer(), draw);
}
extern "C" void __attribute__((thiscall)) FUN_004ba5f0(void* object) {
    auto& model = *static_cast<Model*>(object);
    for (int i = 0; i < model.count; ++i) {
        Part& part = model.parts[i];
        set_scene_diffuse(image(reinterpret_cast<void*>(part.texture)));
        FUN_004b8f80(&part, 4);
    }
}
extern "C" void __attribute__((thiscall)) FUN_005a4c80(void* object, void* dungeon) {
    auto& group = *static_cast<DungeonGroup*>(object);
    auto* lightmaps = reinterpret_cast<unsigned char*>(word(dungeon, 0x20c));
    for (int i = 0; i < group.count; ++i) {
        Part& part = group.parts[i];
        set_scene_lightmap(current_draw.use_lightmaps && lightmaps
                               ? image(lightmaps + part.texture * 0x208)
                               : nullptr);
        FUN_005a4c10(&part, 4);
    }
}
extern "C" void __attribute__((thiscall)) FUN_005a85e0(void* object) {
    const auto* values = static_cast<const float*>(object);
    float forward[3] = {values[4], values[5], values[6]};
    auto normalize = [](float* vector) {
        const float squared = vector[0] * vector[0] + vector[1] * vector[1] + vector[2] * vector[2];
        float length;
        __asm__ volatile("flds %1\n\tfsqrt\n\tfstps %0" : "=m"(length) : "m"(squared) : "st");
        const float inverse = 1.0f / length;
        for (UINT i = 0; i < 3; ++i)
            vector[i] *= inverse;
    };
    normalize(forward);
    float right[3] = {forward[2] * values[8] - forward[1] * values[9],
                      forward[0] * values[9] - forward[2] * values[7],
                      forward[1] * values[7] - forward[0] * values[8]};
    normalize(right);
    float up[3] = {forward[1] * right[2] - forward[2] * right[1],
                   forward[2] * right[0] - forward[0] * right[2],
                   forward[0] * right[1] - forward[1] * right[0]};
    normalize(up);
    current_draw.world = {{{right[0], right[1], right[2], 0},
                           {up[0], up[1], up[2], 0},
                           {forward[0], forward[1], forward[2], 0},
                           {values[1], values[2], values[3], 1}}};
    FUN_004ba5f0(reinterpret_cast<void*>(word(object, 0xa0)));
}
