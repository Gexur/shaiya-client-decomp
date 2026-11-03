#include "graphics/native_scene_ports.h"
#include "graphics/native_renderer.h"

using namespace shaiya::graphics::native;
extern "C" {
int __cdecl fun_005cdacd();
extern float dat_02207ff4, dat_02207ff8;
}
namespace {
template <class T> T& field(void* owner, UINT offset) {
    return *reinterpret_cast<T*>(static_cast<unsigned char*>(owner) + offset);
}
struct BumpGrid {
    Texture2D *normal = nullptr, *environment = nullptr;
    Matrix inverse_view = {};
    float light_position[4] = {};
};
Matrix identity() {
    Matrix value = {};
    for (UINT i = 0; i < 4; ++i)
        value.m[i][i] = 1;
    return value;
}
float phase_offset(float value) {
    float result;
    constexpr float amplitude = 0x1.08421p-6f;
    __asm__ volatile("flds %1\n\tfcos\n\tfmuls %2\n\tfstps %0"
                     : "=m"(result)
                     : "m"(value), "m"(amplitude)
                     : "st");
    return result;
}
void set_texture(Texture2D*& target, Texture2D* value) {
    if (value)
        value->retain();
    if (target)
        target->release();
    target = value;
}
void release_geometry(void* owner) {
    const UINT offsets[] = {0x1e08, 0x1e0c};
    for (UINT offset : offsets) {
        auto*& buffer = field<Buffer*>(owner, offset);
        if (buffer)
            buffer->release();
        buffer = nullptr;
    }
}
} // namespace

extern "C" void __attribute__((thiscall)) FUN_0053d3c0(void* owner) {
    if (!owner)
        return;
    auto*& state = field<BumpGrid*>(owner, 0x1e10);
    if (state) {
        set_texture(state->normal, nullptr);
        set_texture(state->environment, nullptr);
        HeapFree(GetProcessHeap(), 0, state);
        state = nullptr;
    }
    release_geometry(owner);
}

// This authored water material has one light vector and one inverse-view matrix.
extern "C" HRESULT __attribute__((thiscall)) FUN_0053d420(void* owner, const char*,
                                                          const float* light) {
    auto* state = owner ? field<BumpGrid*>(owner, 0x1e10) : nullptr;
    if (!state || !light)
        return E_POINTER;
    for (UINT i = 0; i < 4; ++i)
        state->light_position[i] = light[i];
    return S_OK;
}
extern "C" HRESULT __attribute__((thiscall)) FUN_0053d440(void* owner, const char*,
                                                          const Matrix* inverse_view) {
    auto* state = owner ? field<BumpGrid*>(owner, 0x1e10) : nullptr;
    if (!state || !inverse_view)
        return E_POINTER;
    state->inverse_view = *inverse_view;
    return S_OK;
}
extern "C" HRESULT __attribute__((thiscall)) FUN_0053d460(void* owner, const char* name,
                                                          Texture2D* texture) {
    auto* state = owner ? field<BumpGrid*>(owner, 0x1e10) : nullptr;
    if (!state || !name)
        return E_POINTER;
    if (name[0] == 'n')
        set_texture(state->normal, texture);
    else if (name[0] == 'c')
        set_texture(state->environment, texture);
    else
        return E_INVALIDARG;
    return S_OK;
}

extern "C" HRESULT __attribute__((thiscall)) FUN_0053d490(void* owner, NativeRenderer* device) {
    if (!owner || !device || !device->device || !device->context || !device->pipeline_data)
        return E_POINTER;
    release_geometry(owner);
    auto*& state = field<BumpGrid*>(owner, 0x1e10);
    if (!state) {
        state =
            static_cast<BumpGrid*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(BumpGrid)));
        if (!state)
            return E_OUTOFMEMORY;
        state->inverse_view = identity();
    }
    // Preserve the original two 31x31 random phase tables and edge-pinned UVs.
    for (UINT column = 0; column < 31; ++column)
        for (UINT row = 0; row < 31; ++row) {
            field<float>(owner, (row * 31 + column) * 4) = float(fun_005cdacd() % 10000);
            field<float>(owner, 0xf04 + (row * 31 + column) * 4) = float(fun_005cdacd() % 10000);
        }
    auto* vertices = static_cast<WorldVertex*>(HeapAlloc(GetProcessHeap(), 0, 961 * 24));
    auto* indices = static_cast<uint16_t*>(HeapAlloc(GetProcessHeap(), 0, 5400 * 2));
    if (!vertices || !indices) {
        if (vertices)
            HeapFree(GetProcessHeap(), 0, vertices);
        if (indices)
            HeapFree(GetProcessHeap(), 0, indices);
        return E_OUTOFMEMORY;
    }
    UINT cursor = 0;
    for (UINT row = 0; row < 31; ++row)
        for (UINT column = 0; column < 31; ++column) {
            const bool edge = row == 0 || column == 0 || row == 30 || column == 30;
            const UINT phase = (column * 31 + row) * 4;
            const float u = edge ? 0 : phase_offset(field<float>(owner, phase));
            const float v = edge ? 0 : phase_offset(field<float>(owner, 0xf04 + phase));
            constexpr float unit = 0x1.111112p-5f;
            vertices[row * 31 + column] = {{float(column * 10), 0, float(row * 10)},
                                           0xffffffff,
                                           {float(column) * unit + u, float(row) * unit + v}};
            if (row < 30 && column < 30) {
                const UINT first = row * 31 + column;
                const uint16_t cell[] = {uint16_t(first),      uint16_t(first + 1),
                                         uint16_t(first + 31), uint16_t(first + 32),
                                         uint16_t(first + 31), uint16_t(first + 1)};
                for (UINT i = 0; i < 6; ++i)
                    indices[cursor++] = cell[i];
            }
        }
    HRESULT result = create_buffer(*device, BufferKind::indices, indices, 10800, 2,
                                   DXGI_FORMAT_R16_UINT, &field<Buffer*>(owner, 0x1e0c));
    if (SUCCEEDED(result))
        result = create_buffer(*device, BufferKind::vertices, vertices, 23064, 24,
                               DXGI_FORMAT_UNKNOWN, &field<Buffer*>(owner, 0x1e08));
    HeapFree(GetProcessHeap(), 0, indices);
    HeapFree(GetProcessHeap(), 0, vertices);
    if (FAILED(result))
        release_geometry(owner);
    return result;
}

extern "C" HRESULT __attribute__((thiscall)) FUN_0053d8d0(void* owner, float elapsed,
                                                          NativeRenderer* device) {
    if (!owner || !device)
        return E_POINTER;
    auto* state = field<BumpGrid*>(owner, 0x1e10);
    auto* vertices = field<Buffer*>(owner, 0x1e08);
    auto* indices = field<Buffer*>(owner, 0x1e0c);
    if (!state || !vertices || !indices || vertices->stride != 24 || vertices->size < 23064 ||
        indices->size < 10800)
        return E_INVALIDARG;
    dat_02207ff8 += elapsed * .003f;
    dat_02207ff4 += elapsed * .003f;
    BumpReflectDraw draw;
    draw.mesh.vertices = vertices->gpu;
    draw.mesh.indices = indices->gpu;
    draw.mesh.index_format = indices->index_format;
    draw.mesh.index_count = 5400;
    draw.world = scene_draw_context().world;
    draw.material = scene_draw_context().material;
    draw.material.style = {Blend::alpha, Depth::write, Cull::none, Sampling::linear_wrap};
    draw.material.style.alpha_cutoff = 0;
    draw.normal = state->normal ? state->normal->view : nullptr;
    draw.environment = state->environment ? state->environment->view : nullptr;
    draw.inverse_view = state->inverse_view;
    for (UINT i = 0; i < 4; ++i)
        draw.light_position[i] = state->light_position[i];
    draw.uv_offset[0] = dat_02207ff8;
    draw.uv_offset[1] = dat_02207ff4;
    return draw_bump_reflect_world24(*device, draw);
}

extern "C" HRESULT __attribute__((thiscall)) FUN_0053da10(void* owner, float elapsed,
                                                          NativeRenderer* device) {
    if (!owner || !device)
        return E_POINTER;
    if (!field<BumpGrid*>(owner, 0x1e10) || !field<Buffer*>(owner, 0x1e08) ||
        !field<Buffer*>(owner, 0x1e0c))
        return S_FALSE;
    const Scene previous = device->scene;
    Scene draw_scene = previous;
    draw_scene.fog_enabled = true;
    HRESULT result = begin_scene(*device, draw_scene);
    if (SUCCEEDED(result))
        result = FUN_0053d8d0(owner, elapsed, device);
    const HRESULT restored = begin_scene(*device, previous);
    return FAILED(result) ? result : restored;
}
