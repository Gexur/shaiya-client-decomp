#include "graphics/native_scene_ports.h"
#include "graphics/native_renderer.h"

extern "C" unsigned char dat_02209408[];
namespace {
using namespace shaiya::graphics::native;
Matrix palette_storage[256];
Matrix actor_clip_transform;
bool actor_clip_valid = false;
Matrix actor_model_transform;
bool actor_model_valid = false;
struct ActorClipScope {
    NativeRenderer& current;
    Scene previous;
    bool active;
    ActorClipScope(StaticDraw& draw, bool skinned)
        : current(*renderer()), previous(current.scene), active(false) {
        const auto& actor = scene_draw_context();
        const bool matching = actor.actor_pipeline == (skinned ? ActorPipeline::skinned_model
                                                               : ActorPipeline::reflective_model);
        if (!matching)
            return;
        // Shader c20 describes this actor part. It never changes the world
        // transform inherited by terrain, particles, water or other passes.
        if (!skinned && actor_model_valid)
            draw.world = actor_model_transform;
        const auto& lighting = actor.actor_lighting;
        // Authored actor colors are the final c7/c8 shader inputs. Unlike
        // fixed lighting, those programs do not multiply them by D3DMATERIAL.
        if (lighting.directional_authored)
            draw.material.diffuse_color.r = draw.material.diffuse_color.g =
                draw.material.diffuse_color.b = 1;
        if (lighting.ambient_authored)
            draw.material.ambient_color.r = draw.material.ambient_color.g =
                draw.material.ambient_color.b = 1;
        active = actor_clip_valid || lighting.ambient_authored || lighting.directional_authored ||
                 lighting.direction_authored || lighting.camera_authored;
        if (!active)
            return;
        if (actor_clip_valid) {
            current.scene.view_projection = actor_clip_transform;
            if (skinned) {
                draw.world = {};
                for (UINT axis = 0; axis < 4; ++axis)
                    draw.world.m[axis][axis] = 1;
            }
        }
        if (lighting.ambient_authored)
            current.scene.ambient = lighting.ambient;
        if (lighting.directional_authored)
            current.scene.directional = lighting.directional;
        for (UINT axis = 0; axis < 3; ++axis) {
            if (lighting.direction_authored)
                current.scene.light_direction[axis] = lighting.direction[axis];
            if (lighting.camera_authored)
                current.scene.camera[axis] = lighting.camera[axis];
        }
        begin_scene(current, current.scene);
    }
    ~ActorClipScope() {
        if (active) {
            begin_scene(current, previous);
        }
    }
};
UINT word(const void* object, UINT offset) {
    return *reinterpret_cast<const UINT*>(static_cast<const unsigned char*>(object) + offset);
}
Buffer* buffer(const void* object, UINT offset) {
    return reinterpret_cast<Buffer*>(word(object, offset));
}
StaticDraw actor_draw(Buffer* vertices, Buffer* indices, UINT triangles) {
    const auto& actor = scene_draw_context();
    StaticDraw draw;
    draw.mesh.vertices = vertices ? vertices->gpu : nullptr;
    draw.mesh.indices = indices ? indices->gpu : nullptr;
    draw.mesh.index_format = indices ? indices->index_format : DXGI_FORMAT_R16_UINT;
    draw.mesh.index_count = triangles * 3;
    draw.world = actor.world;
    draw.material = actor.material;
    draw.material.diffuse = actor.diffuse ? actor.diffuse->view : nullptr;
    draw.material.environment = actor.environment ? actor.environment->view : nullptr;
    draw.material.environment_transform = actor.environment_transform;
    draw.material.environment_eye = actor.environment_eye;
    draw.material.explicit_environment_frame = actor.explicit_environment_frame;
    return draw;
}
void count_triangles(UINT count) {
    *reinterpret_cast<UINT*>(dat_02209408 + 1036) += count;
}
} // namespace
namespace shaiya::graphics::native {
void set_actor_clip_transform(const Matrix& matrix) {
    actor_clip_transform = matrix;
    actor_clip_valid = true;
}
void set_actor_model_transform(const Matrix& matrix) {
    actor_model_transform = matrix;
    actor_model_valid = true;
}
HRESULT set_actor_palette(const AffineBone3x4* source, UINT count) {
    auto& actor = scene_draw_context();
    if (!source || !count || count > 256) {
        actor.bones = nullptr;
        actor.bone_count = 0;
        return E_INVALIDARG;
    }
    for (UINT bone = 0; bone < count; ++bone) {
        palette_storage[bone] = {};
        palette_storage[bone].m[3][3] = 1;
        for (UINT row = 0; row < 3; ++row)
            for (UINT column = 0; column < 4; ++column)
                palette_storage[bone].m[column][row] = source[bone].row[row][column];
    }
    actor.bones = palette_storage;
    actor.bone_count = count;
    return S_OK;
}
HRESULT set_actor_bone(UINT bone, const AffineBone3x4& source) {
    if (bone >= 256)
        return E_INVALIDARG;
    auto& actor = scene_draw_context();
    palette_storage[bone] = {};
    palette_storage[bone].m[3][3] = 1;
    for (UINT row = 0; row < 3; ++row)
        for (UINT column = 0; column < 4; ++column)
            palette_storage[bone].m[column][row] = source.row[row][column];
    if (actor.bones != palette_storage || bone == 0)
        actor.bone_count = 0;
    actor.bones = palette_storage;
    if (actor.bone_count <= bone)
        actor.bone_count = bone + 1;
    return S_OK;
}
} // namespace shaiya::graphics::native
extern "C" void __attribute__((thiscall)) FUN_00548090(void*, UINT mode) {
    using namespace shaiya::graphics::native;
    auto& actor = scene_draw_context();
    if (mode == 0) {
        actor.actor_pipeline = ActorPipeline::lit_model;
        actor.actor_reflection = false;
        actor_clip_valid = false;
    } else if (mode == 1)
        actor.actor_pipeline = ActorPipeline::skinned_model;
    else if (mode == 2)
        actor.actor_pipeline = ActorPipeline::reflective_model;
}
extern "C" void __attribute__((thiscall)) FUN_00548160(void*, UINT mode) {
    if (mode <= 2)
        shaiya::graphics::native::scene_draw_context().actor_reflection = mode == 2;
}
extern "C" HRESULT __attribute__((thiscall)) FUN_00551960(void* object) {
    using namespace shaiya::graphics::native;
    const UINT triangles = word(object, 0x20);
    SkinDraw draw;
    static_cast<StaticDraw&>(draw) = actor_draw(buffer(object, 0), buffer(object, 4), triangles);
    const auto& actor = scene_draw_context();
    draw.bones = actor.bones;
    draw.bone_count = actor.bone_count;
    ActorClipScope clip(draw, true);
    HRESULT result = actor.actor_reflection ? draw_reflective_skinned(*renderer(), draw)
                                            : draw_skinned(*renderer(), draw);
    if (SUCCEEDED(result))
        count_triangles(triangles);
    return result;
}
extern "C" HRESULT __attribute__((thiscall)) FUN_005519c0(void* object) {
    using namespace shaiya::graphics::native;
    const UINT triangles = word(object, 0x20);
    StaticDraw draw = actor_draw(buffer(dat_02209408, 0x358), buffer(object, 4), triangles);
    const auto& actor = scene_draw_context();
    ActorClipScope clip(draw, false);
    HRESULT result = !actor.lit               ? draw_unlit_model(*renderer(), draw)
                     : actor.actor_reflection ? draw_reflective_model(*renderer(), draw)
                                              : draw_model(*renderer(), draw);
    if (SUCCEEDED(result))
        count_triangles(triangles);
    return result;
}
extern "C" HRESULT __attribute__((thiscall)) FUN_00556490(void* object) {
    using namespace shaiya::graphics::native;
    if (!buffer(object, 0))
        return S_FALSE;
    const UINT triangles = word(object, 0xc);
    StaticDraw draw = actor_draw(buffer(object, 0), buffer(object, 4), triangles);
    const auto& actor = scene_draw_context();
    ActorClipScope clip(draw, false);
    HRESULT result = !actor.lit               ? draw_unlit_model(*renderer(), draw)
                     : actor.actor_reflection ? draw_reflective_model(*renderer(), draw)
                                              : draw_model(*renderer(), draw);
    if (SUCCEEDED(result))
        count_triangles(triangles);
    return result;
}
extern "C" HRESULT __attribute__((thiscall)) FUN_00557330(void* object) {
    using namespace shaiya::graphics::native;
    const UINT triangles = word(object, 0x28);
    StaticDraw draw = actor_draw(buffer(dat_02209408, 0x35c), buffer(object, 0x1c), triangles);
    draw.material.style.blend = Blend::alpha;
    draw.material.style.depth = Depth::read;
    draw.material.style.cull = Cull::none;
    HRESULT result = draw_world_indexed(*renderer(), draw);
    if (SUCCEEDED(result))
        count_triangles(triangles);
    return result;
}
