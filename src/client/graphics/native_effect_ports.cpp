#include "graphics/native_scene_ports.h"
#include "graphics/native_renderer.h"
#include "startup/application.h"
#include "core/x87_runtime.h"

extern "C" {
extern unsigned char dat_02209408[], dat_0220f708[], dat_0220df28[];
extern unsigned char dat_0071d0f9;
extern UINT dat_0085d3a8;
extern void* dat_007191d4;
extern float dat_007085b4, DAT_00719874, DAT_00719878, dat_0070baa0, dat_0070baa4;
void __attribute__((thiscall)) FUN_005426e0(void*, const float*, const float*, const float*);
void __attribute__((thiscall)) FUN_00542670(void*, const float*);
void __attribute__((thiscall)) FUN_00542440(void*, float, float, float);
void __attribute__((thiscall)) FUN_00559890(void*);
void __attribute__((thiscall)) FUN_0053dc20(void*);
void __attribute__((thiscall)) FUN_0055b1f0(void*);
void __attribute__((thiscall)) FUN_0055b650(void*);
HRESULT __attribute__((thiscall)) FUN_00556490(void*);
void __attribute__((thiscall)) FUN_00541bb0(void*, int);
void __attribute__((stdcall)) native_actor_effect_blend(void*);
void __attribute__((stdcall)) native_scene_blending(UINT);
void __attribute__((stdcall)) native_scene_alpha_test(UINT);
void __attribute__((stdcall)) native_scene_lighting(UINT);
void __attribute__((stdcall)) native_scene_tint(UINT);
}

using namespace shaiya::graphics::native;
extern "C" HRESULT __attribute__((stdcall)) native_effect_world_strip(UINT, const WorldVertex*);
namespace {
UINT& word(void* object, UINT offset) {
    return *reinterpret_cast<UINT*>(static_cast<unsigned char*>(object) + offset);
}
template <class T> T* pointer(void* object, UINT offset) {
    return reinterpret_cast<T*>(word(object, offset));
}
float* values(void* object, UINT offset) {
    return reinterpret_cast<float*>(static_cast<unsigned char*>(object) + offset);
}
Material effect_material() {
    auto& state = scene_draw_context();
    Material material = state.material;
    material.diffuse = state.diffuse ? state.diffuse->view : nullptr;
    return material;
}
UINT particle_material = 0;
} // namespace

extern "C" void __attribute__((stdcall)) native_particle_material(void* owner) {
    particle_material = word(owner, 8);
    set_scene_diffuse(pointer<Texture2D>(owner, 0x124));
}

extern "C" HRESULT __attribute__((stdcall)) native_particle_quad(Buffer* buffer) {
    if (buffer == nullptr || buffer->asset_bytes == nullptr ||
        buffer->stride != sizeof(WorldVertex) || buffer->size < 4 * sizeof(WorldVertex))
        return E_INVALIDARG;
    const auto* quad = reinterpret_cast<const WorldVertex*>(buffer->asset_bytes);
    const UINT order[6] = {0, 1, 2, 0, 2, 3};
    WorldVertex vertices[6];
    const bool constant_color = particle_material < 2;
    for (UINT i = 0; i < 6; ++i) {
        vertices[i] = quad[order[i]];
        if (constant_color)
            vertices[i].argb = 0xffffffffu;
    }
    WorldDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = 6;
    draw.world = scene_draw_context().world;
    draw.material = effect_material();
    auto& style = draw.material.style;
    style.blend = particle_material == 0 || particle_material == 3 ? Blend::additive : Blend::alpha;
    style.source_blend = D3D11_BLEND(0);
    style.destination_blend = D3D11_BLEND(0);
    style.depth = style.depth == Depth::disabled ? Depth::disabled : Depth::read;
    style.sampling = Sampling::linear_wrap;
    style.alpha_cutoff = constant_color ? 0 : 79.5f / 255;
    if (!constant_color)
        style.tint = {1, 1, 1, 1};
    return draw_world_triangles(*renderer(), draw);
}

extern "C" void __cdecl native_material_vertex_color() {
    // These authored passes multiply texture alpha by vertex alpha. The
    // previous overlay's constant tint does not participate in that material.
    scene_draw_context().material.style.tint = {1, 1, 1, 1};
}
extern "C" void __cdecl native_effect_mirrored_uv() {
    scene_draw_context().material.style.sampling = Sampling::linear_mirror;
}
extern "C" void __cdecl native_effect_wrapped_uv() {
    scene_draw_context().material.style.sampling = Sampling::linear_wrap;
}

extern "C" void __attribute__((thiscall)) FUN_0055cb10(void* object) {
    FUN_005426e0(dat_02209408, values(object, 0x2c), values(object, 0x38), values(object, 0x44));
    UINT* begin = pointer<UINT>(object, 0xf0);
    if (begin && word(object, 0xf4) != word(object, 0xf0)) {
        const int effect = int(word(object, 0x104));
        if (effect < 250) {
            auto* catalog = dat_0220f708 + effect * 300;
            const int frame = int(begin[word(object, 0x1dac8)]);
            if (!word(catalog, 0xc))
                FUN_00559890(catalog);
            void* texture = frame >= 0 && frame < int(word(catalog, 8))
                                ? pointer<void*>(catalog, 0x1c)[frame]
                                : nullptr;
            if (texture)
                FUN_0053dc20(texture);
            else
                set_scene_diffuse(nullptr);
        }
    } else {
        set_scene_diffuse(nullptr);
    }
    native_actor_effect_blend(object);
    if (word(object, 0x1dad0) && !word(object, 0x17c))
        FUN_0055b1f0(object);
    else
        FUN_0055b650(object);
}

extern "C" void __attribute__((thiscall)) FUN_0054cce0(void* object) {
    if (dat_0071d0f9 && !dat_0085d3a8)
        return;
    FUN_00542440(dat_02209408, dat_007085b4, 0.1f, 1000000.0f);
    values(object, 0xd4)[0] = values(object, 0xd4)[1] = values(object, 0xd4)[2] = 0;
    FUN_00542670(dat_02209408, values(object, 0xd4));
    set_scene_diffuse(pointer<Texture2D>(object, 0x10));
    native_scene_tint(0xffffffffu);
    native_scene_alpha_test(0);
    native_scene_blending(0);
    FUN_00541bb0(dat_02209408, 0);
    FUN_00556490(dat_0220df28);
    native_scene_blending(1);
    native_scene_lighting(0);
    using Feature = bool(__attribute__((thiscall))*)(void*, UINT);
    auto table = *static_cast<Feature**>(dat_007191d4);
    if (table[1](dat_007191d4, 0x25)) {
        const UINT alpha =
            UINT(x87_to_integer_005cd414(static_cast<long double>(*values(object, 0xf4)) * 255)) &
            255;
        native_scene_tint((alpha << 24) | 0xffffff);
        set_scene_diffuse(pointer<Texture2D>(object, 0x14));
        FUN_00556490(dat_0220df28);
    }
    FUN_00541bb0(dat_02209408, 0);
    auto clouds = [&](UINT vertex_offset, UINT texture_offset) {
        auto* vertices = pointer<Buffer>(object, vertex_offset);
        if (!vertices || vertices->stride != sizeof(WorldVertex) ||
            vertices->size < 4 * sizeof(WorldVertex))
            return;
        set_scene_diffuse(pointer<Texture2D>(object, texture_offset));
        const Color previous = scene_draw_context().material.style.tint;
        scene_draw_context().material.style.tint = {1, 1, 1, 1};
        native_effect_world_strip(2, reinterpret_cast<const WorldVertex*>(vertices->asset_bytes));
        scene_draw_context().material.style.tint = previous;
    };
    if (dat_0070baa0 != 0)
        clouds(8, 0x18);
    if (dat_0070baa4 != 0)
        clouds(0xc, 0x1c);
    FUN_00541bb0(dat_02209408, 1);
    FUN_00542440(dat_02209408, dat_007085b4, DAT_00719878, DAT_00719874);
}

extern "C" HRESULT __attribute__((stdcall)) native_effect_world_strip(UINT triangles,
                                                                      const WorldVertex* strip) {
    if (!triangles)
        return S_OK;
    if (!strip || triangles > 0x7fffffffu / (3 * sizeof(WorldVertex)))
        return E_INVALIDARG;
    WorldVertex local[6];
    auto* vertices = triangles <= 2
                         ? local
                         : static_cast<WorldVertex*>(HeapAlloc(
                               GetProcessHeap(), 0, SIZE_T(triangles) * 3 * sizeof(WorldVertex)));
    if (!vertices)
        return E_OUTOFMEMORY;
    for (UINT i = 0; i < triangles; ++i) {
        vertices[i * 3] = strip[i + (i & 1)];
        vertices[i * 3 + 1] = strip[i + 1 - (i & 1)];
        vertices[i * 3 + 2] = strip[i + 2];
    }
    WorldDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = triangles * 3;
    draw.world = scene_draw_context().world;
    draw.material = effect_material();
    HRESULT result = draw_world_triangles(*dat_02209400, draw);
    if (vertices != local)
        HeapFree(GetProcessHeap(), 0, vertices);
    return result;
}

extern "C" HRESULT __attribute__((stdcall)) native_colored_world_strip(UINT triangles,
                                                                       const WorldVertex* strip) {
    SceneDrawScope preserve;
    set_scene_diffuse(nullptr);
    scene_draw_context().material.style.tint = {1, 1, 1, 1};
    return native_effect_world_strip(triangles, strip);
}

extern "C" HRESULT __attribute__((stdcall)) native_inventory_model_strip(void* owner) {
    auto* source = *reinterpret_cast<Buffer**>(static_cast<unsigned char*>(owner) + 0x154);
    if (!source || source->stride != sizeof(ModelVertex) || source->size < 4 * sizeof(ModelVertex))
        return E_INVALIDARG;
    const auto* model = reinterpret_cast<const ModelVertex*>(source->asset_bytes);
    WorldVertex quad[4];
    for (UINT i = 0; i < 4; ++i) {
        for (UINT component = 0; component < 3; ++component)
            quad[i].position[component] = model[i].position[component];
        quad[i].argb = 0xffffffffu;
        quad[i].uv[0] = model[i].uv[0];
        quad[i].uv[1] = model[i].uv[1];
    }
    // Inventory cards use their model positions/UVs with lighting disabled.
    return native_effect_world_strip(2, quad);
}

extern "C" HRESULT __attribute__((stdcall)) native_ui_buffer_fan(Buffer* vertices) {
    if (!vertices || vertices->stride != sizeof(UiVertex) || vertices->size < 4 * sizeof(UiVertex))
        return E_INVALIDARG;
    auto& state = scene_draw_context();
    UiDraw draw;
    draw.vertices = reinterpret_cast<const UiVertex*>(vertices->asset_bytes);
    draw.vertex_count = 4;
    draw.primitive = UiPrimitive::quad;
    draw.image = state.diffuse ? state.diffuse->view : nullptr;
    draw.style = state.material.style;
    draw.style.cull = Cull::none;
    draw.style.sampling = Sampling::linear_clamp;
    return draw_ui(*dat_02209400, draw);
}
