#include "graphics/native_scene_ports.h"
#include "graphics/native_renderer.h"
using namespace shaiya::graphics::native;
extern "C" {
extern unsigned char dat_02209408[];
extern Buffer* dat_02221c30;
}
namespace {
UINT& word(void* object, UINT offset) {
    return *reinterpret_cast<UINT*>(static_cast<unsigned char*>(object) + offset);
}
template <class T> T* pointer(void* object, UINT offset) {
    return reinterpret_cast<T*>(word(object, offset));
}
const float* floats(void* object, UINT offset) {
    return reinterpret_cast<const float*>(static_cast<unsigned char*>(object) + offset);
}
Buffer* scratch(UINT count) {
    auto* buffer = pointer<Buffer>(dat_02209408, 860);
    return buffer && buffer->stride == 24 && count <= buffer->size / 24 ? buffer : nullptr;
}
HRESULT submit(void* owner, Buffer& vertices, UINT count, UINT triangles) {
    auto* indices = pointer<Buffer>(owner, 0x50);
    if (!indices || triangles > indices->size / 6)
        return E_INVALIDARG;
    HRESULT result = update_buffer(*renderer(), vertices, 0, vertices.asset_bytes, count * 24);
    if (FAILED(result))
        return result;
    StaticDraw draw;
    draw.mesh.vertices = vertices.gpu;
    draw.mesh.indices = indices->gpu;
    draw.mesh.index_format = indices->index_format;
    draw.mesh.index_count = triangles * 3;
    auto& state = scene_draw_context();
    draw.world = state.world;
    draw.material = state.material;
    draw.material.diffuse = state.diffuse ? state.diffuse->view : nullptr;
    draw.material.style.cull = Cull::none;
    draw.material.style.blend = Blend::alpha;
    draw.material.style.source_blend = draw.material.style.destination_blend = D3D11_BLEND(0);
    draw.material.style.alpha_cutoff = 7.5f / 255;
    draw.material.style.tint = {1, 1, 1, 1};
    result = draw_world_indexed(*renderer(), draw);
    if (SUCCEEDED(result))
        word(dat_02209408, 1036) += triangles;
    return result;
}
void position(WorldVertex& target, const float* source) {
    for (UINT c = 0; c < 3; ++c)
        target.position[c] = source[c];
}
} // namespace
extern "C" HRESULT __attribute__((thiscall)) FUN_0055a4d0(void* owner) {
    Buffer* buffer = scratch(9);
    if (!buffer || !dat_02221c30 || dat_02221c30->size < 48)
        return E_INVALIDARG;
    auto* vertices = reinterpret_cast<WorldVertex*>(buffer->asset_bytes);
    const UINT offsets[] = {0x14, 0x5c, 0x20, 0x44, 0x74, 0x50, 0x2c, 0x68, 0x38};
    for (UINT i = 0; i < 9; ++i) {
        position(vertices[i], floats(owner, offsets[i]));
        vertices[i].argb = 0xffffffff;
        vertices[i].uv[0] = float(i % 3) * .5f;
        vertices[i].uv[1] = float(i / 3) * .5f;
    }
    HRESULT result = update_buffer(*renderer(), *buffer, 0, vertices, 9 * 24);
    if (FAILED(result))
        return result;
    StaticDraw draw;
    draw.mesh.vertices = buffer->gpu;
    draw.mesh.indices = dat_02221c30->gpu;
    draw.mesh.index_format = dat_02221c30->index_format;
    draw.mesh.index_count = 24;
    draw.world = scene_draw_context().world;
    draw.material = scene_draw_context().material;
    for (UINT layer = 0; layer < 3; ++layer) {
        void* record = pointer<void>(owner, 8 + layer * 4);
        if (!record)
            continue;
        auto* texture = pointer<Texture2D>(record, 4);
        set_scene_diffuse(texture);
        draw.material.diffuse = texture ? texture->view : nullptr;
        const UINT argb = word(owner, 0x80 + layer * 4);
        draw.material.style.tint = {float((argb >> 16) & 255) / 255, float((argb >> 8) & 255) / 255,
                                    float(argb & 255) / 255, float(argb >> 24) / 255};
        result = draw_world_indexed(*renderer(), draw);
        if (FAILED(result))
            return result;
    }
    return result;
}
extern "C" HRESULT __attribute__((thiscall)) FUN_00581b30(void* owner) {
    const int rows = int(word(owner, 8)), columns = int(word(owner, 12));
    const UINT count = word(owner, 0x54);
    Buffer* buffer = scratch(count);
    if (!buffer || !count || rows < 0 || columns < 0 || UINT(rows) >= count ||
        UINT(columns) >= count || UINT(rows + 1) > count / UINT(columns + 1))
        return E_INVALIDARG;
    auto** source = pointer<unsigned char*>(owner, 0x64);
    if (!source)
        return E_INVALIDARG;
    auto* vertices = reinterpret_cast<WorldVertex*>(buffer->asset_bytes);
    UINT cursor = 0;
    for (int row = 0; row <= rows; ++row) {
        if (!source[row])
            return E_INVALIDARG;
        for (int column = 0; column <= columns; ++column) {
            const auto* input = source[row] + column * 80;
            WorldVertex& vertex = vertices[cursor++];
            position(vertex, reinterpret_cast<const float*>(input + 8));
            vertex.argb = 0xffffffff;
            vertex.uv[0] = *reinterpret_cast<const float*>(input + 0x3c);
            vertex.uv[1] = *reinterpret_cast<const float*>(input + 0x40);
        }
    }
    return submit(owner, *buffer, count, word(owner, 0x58));
}
extern "C" HRESULT __attribute__((thiscall)) FUN_00581d70(void* owner, void* samples) {
    const int rows = int(word(owner, 8)), columns = int(word(owner, 12));
    const UINT count = word(owner, 0x54);
    Buffer* buffer = scratch(count);
    if (!buffer || !count || rows < 0 || columns < 0 || UINT(rows) >= count ||
        UINT(columns) >= count || UINT(rows + 1) > count / UINT(columns + 1))
        return E_INVALIDARG;
    auto** authored = pointer<unsigned char*>(owner, 0x68);
    auto* baseline = pointer<float>(owner, 0x70);
    if (!authored || !authored[0] || !baseline)
        return E_INVALIDARG;
    auto* differences = static_cast<float*>(HeapAlloc(GetProcessHeap(), 0, UINT(columns + 1) * 12));
    if (!differences)
        return E_OUTOFMEMORY;
    for (int column = 0; column <= columns; ++column) {
        const auto* source = reinterpret_cast<const float*>(authored[0] + column * 80 + 8);
        for (UINT c = 0; c < 3; ++c)
            differences[column * 3 + c] = source[c] - baseline[column * 10 + c];
    }
    auto* vertices = reinterpret_cast<WorldVertex*>(buffer->asset_bytes);
    UINT cursor = 0;
    for (int row = 0; row <= rows; ++row)
        for (int column = 0; column <= columns; ++column) {
            const auto* source = baseline + cursor * 10;
            WorldVertex& vertex = vertices[cursor++];
            for (UINT c = 0; c < 3; ++c)
                vertex.position[c] = source[c] + differences[column * 3 + c];
            vertex.argb = 0xffffffff;
            vertex.uv[0] = source[8];
            vertex.uv[1] = source[9];
        }
    HeapFree(GetProcessHeap(), 0, differences);
    if (samples) {
        const int center_row = int(word(owner, 0x20)), center_column = int(word(owner, 0x1c)),
                  row_radius = int(word(owner, 0x28)), column_radius = int(word(owner, 0x24));
        const int locations[9][2] = {{-1, -1}, {-1, 1}, {1, -1}, {1, 1}, {0, -1},
                                     {0, 1},   {-1, 0}, {1, 0},  {0, 0}};
        auto* output = reinterpret_cast<float*>(static_cast<unsigned char*>(samples) + 0x14);
        for (UINT sample = 0; sample < 9; ++sample) {
            const int row = center_row + locations[sample][0] * row_radius,
                      column = center_column + locations[sample][1] * column_radius;
            if (row < 0 || row > rows || column < 0 || column > columns)
                return E_INVALIDARG;
            const WorldVertex& vertex = vertices[UINT(row) * (columns + 1) + column];
            for (UINT c = 0; c < 3; ++c)
                output[sample * 3 + c] = vertex.position[c];
        }
    }
    return submit(owner, *buffer, count, word(owner, 0x58));
}
