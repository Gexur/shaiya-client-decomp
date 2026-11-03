#include "graphics/native_scene_ports.h"
#include "graphics/native_renderer.h"
#include <stdint.h>

using namespace shaiya::graphics::native;
extern "C" {
void* __cdecl FUN_005ad720();
void __attribute__((thiscall)) FUN_005afde0(void*, UINT);
void __attribute__((thiscall)) FUN_004ba5f0(void*);
void __attribute__((thiscall)) FUN_005a4c80(void*, void*);
void __attribute__((thiscall)) FUN_005ada80(void*, UINT);
void __attribute__((thiscall)) FUN_005a5670(void*, void*, const Matrix*);
void __attribute__((thiscall)) FUN_005a60d0(void*, Matrix*);
void __attribute__((thiscall)) FUN_005aa980(void*, Matrix*);
void __attribute__((thiscall)) FUN_005363d0(Matrix*, const float*, const float*, const float*);
void __attribute__((thiscall)) FUN_005aca30(Matrix*, const float*, const float*, const float*);
int __attribute__((thiscall)) FUN_005cc4a0(void*, const void*);
void __attribute__((thiscall)) FUN_005a2490(float*, const Matrix*);
Matrix* __stdcall FUN_005e65c3(Matrix*, float, float, float, float);
void __attribute__((thiscall)) FUN_005b0960(void*, void*);
void __attribute__((thiscall)) FUN_005b1f60(void*);
void __attribute__((thiscall)) FUN_005b1710(void*);
extern unsigned char dat_0224e498[];
extern float dat_0224e644, dat_0224e648, dat_0224e64c;
extern unsigned char dat_0070ca53;
}
namespace {
using Word = uint32_t __attribute__((may_alias));
Word& word(void* object, UINT offset) {
    return *reinterpret_cast<Word*>(static_cast<unsigned char*>(object) + offset);
}
template <class T> T* at(void* object, UINT offset) {
    return reinterpret_cast<T*>(static_cast<unsigned char*>(object) + offset);
}
template <class T> T* pointer(void* object, UINT offset) {
    return reinterpret_cast<T*>(word(object, offset));
}
Matrix identity() {
    return {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
}
void camera_changed(NativeRenderer& current) {
    for (UINT row = 0; row < 4; ++row)
        for (UINT column = 0; column < 4; ++column) {
            float value = 0;
            for (UINT component = 0; component < 4; ++component)
                value +=
                    current.scene.view.m[row][component] * current.projection.m[component][column];
            current.scene.view_projection.m[row][column] = value;
        }
    begin_scene(current, current.scene);
}
Material material() {
    auto& context = scene_draw_context();
    Material result = context.material;
    result.diffuse = context.diffuse ? context.diffuse->view : nullptr;
    return result;
}
bool range(StaticDraw& draw, Buffer* vertices, Buffer* indices, UINT stride, UINT first_index,
           UINT triangles) {
    if (!vertices || !indices || vertices->stride != stride || indices->stride != 2 ||
        first_index > indices->size / 2 || triangles > (indices->size / 2 - first_index) / 3)
        return false;
    draw.mesh.vertices = vertices->gpu;
    draw.mesh.indices = indices->gpu;
    draw.mesh.index_format = indices->index_format;
    draw.mesh.first_index = first_index;
    draw.mesh.index_count = triangles * 3;
    draw.world = scene_draw_context().world;
    draw.material = material();
    return true;
}
template <class Vertex> Vertex* expand_strip(Buffer* buffer, UINT primitives) {
    if (!buffer || buffer->stride != sizeof(Vertex) || buffer->size / sizeof(Vertex) < 2 ||
        primitives > buffer->size / sizeof(Vertex) - 2 ||
        primitives > 0x7fffffffu / (3 * sizeof(Vertex)))
        return nullptr;
    auto* result = static_cast<Vertex*>(
        HeapAlloc(GetProcessHeap(), 0, size_t(primitives) * 3 * sizeof(Vertex)));
    if (!result)
        return nullptr;
    const auto* source = reinterpret_cast<const Vertex*>(buffer->asset_bytes);
    for (UINT triangle = 0; triangle < primitives; ++triangle) {
        result[triangle * 3] = source[triangle + (triangle & 1)];
        result[triangle * 3 + 1] = source[triangle + 1 - (triangle & 1)];
        result[triangle * 3 + 2] = source[triangle + 2];
    }
    return result;
}
void select_dungeon_material(void* dungeon, UINT index) {
    auto** textures = pointer<void*>(dungeon, 0x204);
    void* texture = textures ? textures[index] : nullptr;
    if (!texture) {
        set_scene_diffuse(nullptr);
    } else if (word(dungeon, 0x360) != index) {
        FUN_005afde0(texture, 0);
        word(dungeon, 0x360) = index;
    }
}
void draw_node_groups(void* dungeon, void* node) {
    auto* groups = pointer<unsigned char>(node, 0x110);
    for (int i = 0, count = int(word(node, 0x10c)); i < count; ++i) {
        void* group = groups + i * 20;
        select_dungeon_material(dungeon, word(group, 0));
        FUN_005a4c80(group, dungeon);
    }
    word(dungeon, 0x374) += word(node, 0x134);
    word(dungeon, 0x378) += word(node, 0x138);
}
void transformed_box(float* destination, const float* source, const Matrix* matrix) {
    for (UINT i = 0; i < 24; ++i)
        destination[i] = source[i];
    for (UINT i = 0; i < 8; ++i)
        FUN_005a2490(destination + i * 3, matrix);
}
void orient_instance(void* object, Matrix& matrix) {
    const auto* position = at<float>(object, 4);
    const auto* direction = at<float>(object, 0x10);
    const float target[] = {position[0] + direction[0], position[1] + direction[1],
                            position[2] + direction[2]};
    matrix = identity();
    FUN_005363d0(&matrix, position, target, at<float>(object, 0x1c));
}
void normalize(float* values) {
    const float squared = values[0] * values[0] + values[1] * values[1] + values[2] * values[2];
    float length;
    __asm__ volatile("flds %1\n\tfsqrt\n\tfstps %0" : "=m"(length) : "m"(squared) : "st");
    for (UINT component = 0; component < 3; ++component)
        values[component] /= length;
}
} // namespace

extern "C" HRESULT __attribute__((thiscall)) FUN_005ad990(void* object, UINT frame) {
    if (pointer<void>(object, 0))
        FUN_005afde0(pointer<void>(object, 0), 0);
    auto** frames = pointer<Buffer*>(object, 0x14);
    StaticDraw draw;
    if (!frames || frame >= word(object, 4) ||
        !range(draw, frames[frame], pointer<Buffer>(object, 0x10), 36, 0, word(object, 0xc)))
        return E_INVALIDARG;
    return scene_draw_context().lit ? draw_lit(*renderer(), draw) : draw_static(*renderer(), draw);
}
// These two authored builders contain triangle strips, supplied by their sole
// callers. Expansion preserves alternating winding and uses persistent asset data.
extern "C" HRESULT __attribute__((thiscall)) FUN_005b0240(void* object, UINT strip) {
    if (strip != 5)
        return E_INVALIDARG;
    const UINT primitives = word(object, 0x14);
    UiVertex* vertices = expand_strip<UiVertex>(pointer<Buffer>(object, 0), primitives);
    if (!vertices)
        return E_INVALIDARG;
    UiDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = primitives * 3;
    draw.style = scene_draw_context().material.style;
    draw.image = scene_draw_context().diffuse ? scene_draw_context().diffuse->view : nullptr;
    HRESULT result = draw_ui(*renderer(), draw);
    HeapFree(GetProcessHeap(), 0, vertices);
    return result;
}
extern "C" HRESULT __attribute__((thiscall)) FUN_005b05b0(void* object, UINT strip) {
    if (strip != 5)
        return E_INVALIDARG;
    const UINT primitives = word(object, 0x14);
    WorldVertex* vertices = expand_strip<WorldVertex>(pointer<Buffer>(object, 0), primitives);
    if (!vertices)
        return E_INVALIDARG;
    WorldDraw draw;
    draw.vertices = vertices;
    draw.vertex_count = primitives * 3;
    draw.world = scene_draw_context().world;
    draw.material = material();
    HRESULT result = draw_world_triangles(*renderer(), draw);
    HeapFree(GetProcessHeap(), 0, vertices);
    return result;
}
// Basic-water animation has one caller and an authored two-triangle plane.
// Smaller triangles retain its exact surface/UVs while keeping near-plane
// clipping and depth interpolation from amplifying the8192-unit span at shores.
extern "C" HRESULT __attribute__((thiscall)) native_basic_water_strip(void* object, UINT strip) {
    auto* source_buffer = pointer<Buffer>(object, 0);
    if (strip != 5 || word(object, 0x14) != 2 || !source_buffer || !source_buffer->gpu ||
        !source_buffer->asset_bytes || source_buffer->stride != sizeof(WorldVertex) ||
        source_buffer->size < 4 * sizeof(WorldVertex))
        return E_INVALIDARG;
    const auto* source = reinterpret_cast<const WorldVertex*>(source_buffer->asset_bytes);
    for (UINT i = 1; i < 4; ++i)
        if (source[i].argb != source[0].argb)
            return E_INVALIDARG;
    auto& current = *renderer();
    ID3D11Device* owner = nullptr;
    source_buffer->gpu->GetDevice(&owner);
    const bool own_device = owner == current.device;
    if (owner)
        owner->Release();
    if (!own_device)
        return E_INVALIDARG;
    // The SDK retains these interfaces until their source GPU resource dies.
    // Corner/UV/color updates replace them; buffer reloads start with no cache.
    static const GUID
        source_key = {0x6c996320, 0x7aa6, 0x4a7c, {0x91, 0x37, 0x28, 0xbd, 0xb1, 0x8a, 0x26, 0x0b}},
        vertex_key = {0x6c996321, 0x7aa6, 0x4a7c, {0x91, 0x37, 0x28, 0xbd, 0xb1, 0x8a, 0x26, 0x0b}},
        index_key = {0x6c996322, 0x7aa6, 0x4a7c, {0x91, 0x37, 0x28, 0xbd, 0xb1, 0x8a, 0x26, 0x0b}};
    struct CachedBuffers {
        ID3D11Buffer *vertices = nullptr, *indices = nullptr;
        ~CachedBuffers() {
            if (vertices)
                vertices->Release();
            if (indices)
                indices->Release();
        }
    } cached;
    WorldVertex previous[4];
    UINT size = sizeof(previous);
    bool reuse = SUCCEEDED(source_buffer->gpu->GetPrivateData(source_key, &size, previous)) &&
                 size == sizeof(previous);
    for (UINT i = 0; reuse && i < sizeof(previous); ++i)
        reuse = reinterpret_cast<const unsigned char*>(source)[i] ==
                reinterpret_cast<const unsigned char*>(previous)[i];
    if (reuse) {
        size = sizeof(cached.vertices);
        reuse = SUCCEEDED(source_buffer->gpu->GetPrivateData(vertex_key, &size, &cached.vertices));
        size = sizeof(cached.indices);
        reuse = SUCCEEDED(source_buffer->gpu->GetPrivateData(index_key, &size, &cached.indices)) &&
                reuse;
    }
    constexpr UINT divisions = 32, count = divisions * divisions * 6;
    if (reuse && cached.vertices && cached.indices) {
        D3D11_BUFFER_DESC vertices = {}, indices = {};
        cached.vertices->GetDesc(&vertices);
        cached.indices->GetDesc(&indices);
        cached.vertices->GetDevice(&owner);
        reuse = owner == current.device && vertices.ByteWidth == count * sizeof(WorldVertex) &&
                indices.ByteWidth == count * sizeof(uint16_t);
        if (owner)
            owner->Release();
    } else
        reuse = false;
    if (!reuse) {
        if (cached.vertices) {
            cached.vertices->Release();
            cached.vertices = nullptr;
        }
        if (cached.indices) {
            cached.indices->Release();
            cached.indices = nullptr;
        }
        auto* vertices = static_cast<WorldVertex*>(
            HeapAlloc(GetProcessHeap(), 0, count * (sizeof(WorldVertex) + sizeof(uint16_t))));
        if (!vertices)
            return E_OUTOFMEMORY;
        UINT written = 0;
        for (UINT triangle = 0; triangle < 2; ++triangle) {
            const auto &a = source[triangle ? 2 : 0], &b = source[1], &c = source[triangle ? 3 : 2];
            const auto interpolate = [&](UINT row, UINT column) {
                const float u = float(row) / divisions, v = float(column) / divisions;
                WorldVertex result = a;
                for (UINT axis = 0; axis < 3; ++axis)
                    result.position[axis] += u * (b.position[axis] - a.position[axis]) +
                                             v * (c.position[axis] - a.position[axis]);
                for (UINT axis = 0; axis < 2; ++axis)
                    result.uv[axis] +=
                        u * (b.uv[axis] - a.uv[axis]) + v * (c.uv[axis] - a.uv[axis]);
                return result;
            };
            for (UINT row = 0; row < divisions; ++row)
                for (UINT column = 0; column < divisions - row; ++column) {
                    vertices[written++] = interpolate(row, column);
                    vertices[written++] = interpolate(row + 1, column);
                    vertices[written++] = interpolate(row, column + 1);
                    if (row + column + 1 < divisions) {
                        vertices[written++] = interpolate(row + 1, column);
                        vertices[written++] = interpolate(row + 1, column + 1);
                        vertices[written++] = interpolate(row, column + 1);
                    }
                }
        }
        auto* indices = reinterpret_cast<uint16_t*>(vertices + count);
        for (UINT i = 0; i < count; ++i)
            indices[i] = uint16_t(i);
        D3D11_BUFFER_DESC desc = {};
        desc.ByteWidth = count * sizeof(WorldVertex);
        desc.Usage = D3D11_USAGE_IMMUTABLE;
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        D3D11_SUBRESOURCE_DATA data = {vertices, 0, 0};
        HRESULT status = current.device->CreateBuffer(&desc, &data, &cached.vertices);
        if (SUCCEEDED(status)) {
            desc.ByteWidth = count * sizeof(uint16_t);
            desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
            data.pSysMem = indices;
            status = current.device->CreateBuffer(&desc, &data, &cached.indices);
        }
        HeapFree(GetProcessHeap(), 0, vertices);
        if (FAILED(status))
            return status;
        status = source_buffer->gpu->SetPrivateDataInterface(vertex_key, cached.vertices);
        if (SUCCEEDED(status))
            status = source_buffer->gpu->SetPrivateDataInterface(index_key, cached.indices);
        if (SUCCEEDED(status))
            status = source_buffer->gpu->SetPrivateData(source_key, sizeof(previous), source);
        if (FAILED(status)) {
            source_buffer->gpu->SetPrivateDataInterface(vertex_key, nullptr);
            source_buffer->gpu->SetPrivateDataInterface(index_key, nullptr);
            source_buffer->gpu->SetPrivateData(source_key, 0, nullptr);
            return status;
        }
    }
    StaticDraw draw;
    draw.mesh.vertices = cached.vertices;
    draw.mesh.indices = cached.indices;
    draw.mesh.index_count = count;
    draw.mesh.index_format = DXGI_FORMAT_R16_UINT;
    draw.world = scene_draw_context().world;
    draw.material = material();
    return draw_world_indexed(current, draw);
}
extern "C" HRESULT __attribute__((thiscall))
FUN_005b1240(void* object, UINT base_vertex, UINT, UINT first, UINT triangles, UINT triangle_list) {
    StaticDraw draw;
    if (triangle_list != 4 ||
        !range(draw, pointer<Buffer>(object, 0), pointer<Buffer>(object, 4), 20, first, triangles))
        return E_INVALIDARG;
    draw.mesh.base_vertex = static_cast<INT>(base_vertex);
    return draw_textured_world_indexed(*renderer(), draw);
}
extern "C" HRESULT __attribute__((thiscall))
FUN_005b12c0(void* object, UINT base_vertex, UINT, UINT first, UINT triangles, UINT triangle_list) {
    MultiTextureDraw draw;
    if (triangle_list != 4 ||
        !range(draw, pointer<Buffer>(object, 0), pointer<Buffer>(object, 4), 28, first, triangles))
        return E_INVALIDARG;
    draw.mesh.base_vertex = static_cast<INT>(base_vertex);
    draw.secondary = scene_draw_context().lightmap ? scene_draw_context().lightmap->view : nullptr;
    return draw_textured_world_indexed_multi28(*renderer(), draw);
}
extern "C" HRESULT __attribute__((thiscall))
FUN_005b1340(void* object, UINT base_vertex, UINT, UINT first, UINT triangles, UINT triangle_list) {
    MultiTextureDraw draw;
    if (triangle_list != 4 ||
        !range(draw, pointer<Buffer>(object, 0), pointer<Buffer>(object, 4), 36, first, triangles))
        return E_INVALIDARG;
    draw.mesh.base_vertex = static_cast<INT>(base_vertex);
    auto& context = scene_draw_context();
    draw.secondary = context.lightmap ? context.lightmap->view : nullptr;
    draw.detail = context.detail ? context.detail->view : nullptr;
    return draw_textured_world_indexed_multi36(*renderer(), draw);
}
extern "C" HRESULT __attribute__((thiscall)) FUN_005b13c0(void* object, UINT triangle_list) {
    StaticDraw draw;
    if (triangle_list != 4 || !range(draw, pointer<Buffer>(object, 0), pointer<Buffer>(object, 4),
                                     24, 0, word(object, 0x14)))
        return E_INVALIDARG;
    return draw_world_indexed(*renderer(), draw);
}

extern "C" void __attribute__((thiscall)) FUN_005a5200(void* dungeon, void* node,
                                                       int classification, void* frustum) {
    if (classification == 2) {
        classification = FUN_005cc4a0(frustum, at<void>(node, 0x24));
        if (!classification)
            return;
    }
    for (UINT child = 0; child < 8; ++child)
        if (void* next = pointer<void>(node, 0x114 + child * 4))
            FUN_005a5200(dungeon, next, classification, frustum);
    if (FUN_005cc4a0(frustum, at<void>(node, 0x9c)))
        draw_node_groups(dungeon, node);
}
extern "C" void __attribute__((thiscall)) FUN_005a5350(void* dungeon, void* node,
                                                       int classification, void* frustum,
                                                       const Matrix* matrix, UINT depth) {
    float bounds[24];
    if (classification == 2) {
        transformed_box(bounds, at<float>(node, 0x24), matrix);
        classification = FUN_005cc4a0(frustum, bounds);
        if (!classification)
            return;
    }
    for (UINT child = 0; child < 8; ++child)
        if (void* next = pointer<void>(node, 0x114 + child * 4))
            FUN_005a5350(dungeon, next, classification, frustum, matrix, depth + 1);
    transformed_box(bounds, at<float>(node, 0x9c), matrix);
    if (FUN_005cc4a0(frustum, bounds))
        draw_node_groups(dungeon, node);
}

extern "C" void __attribute__((thiscall)) FUN_005a6b10(void* object) {
    Matrix world = identity();
    FUN_005a60d0(object, &world);
    scene_draw_context().world = world;
    FUN_004ba5f0(pointer<void>(object, 0xa0));
}
extern "C" void __attribute__((thiscall)) FUN_005a8f60(void* object, int elapsed) {
    void* model = pointer<void>(object, 0xa8);
    if (!model)
        return;
    word(object, 0xa4) += elapsed;
    if (int(word(object, 0xa4)) >= int(word(model, 0x148))) {
        ++word(object, 0xa0);
        if (int(word(object, 0xa0)) >= int(word(model, 0x144)))
            word(object, 0xa0) = 0;
        word(object, 0xa4) = 0;
    }
    Matrix world;
    orient_instance(object, world);
    scene_draw_context().world = world;
    FUN_005ada80(model, word(object, 0xa0));
}
extern "C" void __attribute__((thiscall)) FUN_005a90a0(void* object) {
    void* model = pointer<void>(object, 0xa8);
    if (!model)
        return;
    Matrix world;
    orient_instance(object, world);
    scene_draw_context().world = world;
    FUN_005ada80(model, word(object, 0xa0));
}
extern "C" void __attribute__((thiscall)) FUN_005a9820(void* object) {
    Matrix world;
    orient_instance(object, world);
    scene_draw_context().world = world;
    void* owner = FUN_005ad720();
    FUN_005a5670(pointer<void>(object, 0xa0), at<void>(pointer<void>(owner, 0x54), 0xdc), &world);
}
extern "C" void __attribute__((thiscall)) FUN_005aad60(void* object) {
    Matrix world = identity();
    FUN_005aa980(object, &world);
    scene_draw_context().world = world;
    FUN_004ba5f0(pointer<void>(object, 0xa0));
}
extern "C" void __attribute__((thiscall)) FUN_005acd00(void* object) {
    auto* values = at<float>(object, 0x88);
    auto* projection = at<Matrix>(object, 0x9c);
    FUN_005e65c3(projection, values[0], values[1], values[2], values[3]);
    renderer()->projection = *projection;
    camera_changed(*renderer());
}
extern "C" void __attribute__((thiscall)) FUN_005ace00(void* object) {
    const auto* eye = at<float>(object, 0);
    const auto* target = at<float>(object, 0xc);
    const auto* up = at<float>(object, 0x18);
    auto* forward = at<float>(object, 0x24);
    for (UINT i = 0; i < 3; ++i)
        forward[i] = target[i] - eye[i];
    auto* direction = at<float>(object, 0x3c);
    for (UINT i = 0; i < 3; ++i)
        direction[i] = forward[i];
    normalize(direction);
    auto* right = at<float>(object, 0x30);
    right[0] = forward[1] * up[2] - forward[2] * up[1];
    right[1] = forward[2] * up[0] - forward[0] * up[2];
    right[2] = forward[0] * up[1] - forward[1] * up[0];
    normalize(right);
    auto* view = at<Matrix>(object, 0x48);
    *view = identity();
    FUN_005aca30(view, eye, target, up);
    auto& current = *renderer();
    current.scene.view = *view;
    for (UINT i = 0; i < 3; ++i)
        current.scene.camera[i] = eye[i];
    camera_changed(current);
}
extern "C" void __attribute__((thiscall)) FUN_005b41b0(void* object) {
    if (!*at<unsigned char>(object, 0x4f25c))
        return;
    Matrix world = {};
    world.m[0][0] = dat_0224e64c;
    world.m[1][1] = dat_0224e648;
    world.m[2][2] = dat_0224e64c;
    world.m[3][0] = *at<float>(object, 0x4f250);
    world.m[3][1] = dat_0224e644;
    world.m[3][2] = *at<float>(object, 0x4f254);
    world.m[3][3] = 1;
    scene_draw_context().world = world;
    FUN_005b0960(dat_0224e498, object);
    if (dat_0070ca53)
        FUN_005b1710(dat_0224e498);
    else
        FUN_005b1f60(dat_0224e498);
}
