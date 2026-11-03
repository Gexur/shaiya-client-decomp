#include "native_render_passes.h"
#include "native_renderer.h"
#include "native_render_shaders.h"
#include <d3dcompiler.h>
#include <windows.h>
#include "native_draw_probe.h"

namespace shaiya::graphics::native {
namespace {
template <class T> void release(T*& value) {
    if (value)
        value->Release();
    value = nullptr;
}
void copy(void* destination, const void* source, UINT size) {
    auto* out = static_cast<unsigned char*>(destination);
    const auto* in = static_cast<const unsigned char*>(source);
    for (UINT i = 0; i < size; ++i)
        out[i] = in[i];
}
bool equal(const void* first, const void* second, UINT size) {
    const auto* a = static_cast<const unsigned char*>(first);
    const auto* b = static_cast<const unsigned char*>(second);
    for (UINT i = 0; i < size; ++i)
        if (a[i] != b[i])
            return false;
    return true;
}
Matrix identity() {
    Matrix value = {};
    for (UINT i = 0; i < 4; ++i)
        value.m[i][i] = 1;
    return value;
}
struct SceneData {
    Matrix view_projection, view;
    Color ambient, directional;
    float light_direction[4], camera[4], fog[4];
    Color fog_color;
    float clip_plane[4], viewport[4];
    Color point_color;
    float point_position_range[4], point_attenuation[4];
};
struct ObjectData {
    Matrix world, reflection;
    Color tint, diffuse, ambient;
    float parameters[4], uv[4];
    Color specular;
    float surface[4];
    Color emissive;
    Matrix environment;
    Color environment_eye;
    Matrix texture_projection;
    float projection_flags[4];
};
struct WaterData {
    Matrix refraction;
    Color color;
    float parameters[4], offsets[4];
};
static_assert(sizeof(WaterData) == 112);
static_assert(sizeof(SceneData) == 304);
static_assert(sizeof(ObjectData) == 416);
enum VertexProgram : UINT {
    ui_vertex,
    mesh_vertex,
    lit_vertex,
    lightmap_vertex,
    model_vertex,
    skin_vertex,
    world_vertex,
    reflective_model_vertex,
    reflective_skin_vertex,
    textured_world_vertex,
    multi28_vertex,
    multi36_vertex,
    ui_dual_vertex,
    unlit_model_vertex,
    water32_vertex,
    water56_vertex,
    bump_reflect_vertex,
    fullscreen_vertex,
    vertex_count
};
enum PixelProgram : UINT {
    ui_pixel,
    mask_pixel,
    surface_pixel,
    lightmap_pixel,
    water_pixel,
    copy_pixel,
    eight_tap_pixel,
    gaussian_x_pixel,
    gaussian_y_pixel,
    gamma_pixel,
    reflection_pixel,
    projected_shadow_pixel,
    projected_effect_pixel,
    multi36_pixel,
    multi28_pixel,
    replace28_pixel,
    signed28_pixel,
    replace36_pixel,
    signed36_pixel,
    ui_dual_pixel,
    water56_pixel,
    bump_reflect_pixel,
    pixel_count
};
enum VertexLayout : UINT {
    ui_layout,
    mesh_layout,
    lightmap_layout,
    model_layout,
    skin_layout,
    world_layout,
    textured_world_layout,
    multi28_layout,
    multi36_layout,
    ui_dual_layout,
    water32_layout,
    water56_layout,
    layout_count
};
struct Passes {
    ID3D11VertexShader* vertices[vertex_count];
    ID3D11PixelShader* pixels[pixel_count];
    ID3D11InputLayout* layouts[layout_count];
    ID3D11BlendState* blends[6];
    ID3D11BlendState* custom_blends[20][20];
    ID3D11DepthStencilState* depths[3];
    ID3D11RasterizerState* rasters[3][2];
    ID3D11SamplerState* samplers[5];
    ID3D11Buffer *scene_buffer, *object_buffer, *bone_buffer, *ui_buffer, *quad_indices,
        *world_buffer, *water_buffer, *world_index_buffer;
    ID3D11ShaderResourceView* white;
    UINT ui_capacity, world_capacity, world_index_capacity;
    bool scene_valid, object_valid;
    SceneData scene;
    ObjectData object;
    ID3D11VertexShader* bound_vertex;
    ID3D11PixelShader* bound_pixel;
    ID3D11InputLayout* bound_layout;
    ID3D11BlendState* bound_blend;
    Color bound_blend_factor;
    ID3D11DepthStencilState* bound_depth;
    ID3D11RasterizerState* bound_raster;
    ID3D11SamplerState* bound_sampler;
};
Passes* passes(NativeRenderer& renderer) {
    return static_cast<Passes*>(renderer.pipeline_data);
}
using Compile = HRESULT(WINAPI*)(LPCVOID, SIZE_T, LPCSTR, const D3D_SHADER_MACRO*, ID3DInclude*,
                                 LPCSTR, LPCSTR, UINT, UINT, ID3DBlob**, ID3DBlob**);
HRESULT compile(Compile function, const char* entry, const char* profile, ID3DBlob** output) {
    ID3DBlob* errors = nullptr;
    HRESULT status =
        function(render_shader_source, sizeof(render_shader_source) - 1, "native_render_shaders.h",
                 nullptr, nullptr, entry, profile,
                 D3DCOMPILE_OPTIMIZATION_LEVEL3 | D3DCOMPILE_ENABLE_STRICTNESS, 0, output, &errors);
    if (FAILED(status) && errors) {
        HANDLE log = CreateFileA("native-render-shader-failure.log", GENERIC_WRITE, FILE_SHARE_READ,
                                 nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
        if (log != INVALID_HANDLE_VALUE) {
            DWORD written;
            WriteFile(log, errors->GetBufferPointer(), DWORD(errors->GetBufferSize()), &written,
                      nullptr);
            CloseHandle(log);
        }
    }
    release(errors);
    return status;
}
HRESULT buffer(NativeRenderer& renderer, UINT size, UINT bind, bool dynamic, const void* contents,
               ID3D11Buffer** output) {
    D3D11_BUFFER_DESC description = {};
    description.ByteWidth = size;
    description.Usage = dynamic    ? D3D11_USAGE_DYNAMIC
                        : contents ? D3D11_USAGE_IMMUTABLE
                                   : D3D11_USAGE_DEFAULT;
    description.BindFlags = bind;
    description.CPUAccessFlags = dynamic ? D3D11_CPU_ACCESS_WRITE : 0;
    D3D11_SUBRESOURCE_DATA initial = {};
    initial.pSysMem = contents;
    return renderer.device->CreateBuffer(&description, contents ? &initial : nullptr, output);
}
HRESULT create_programs(NativeRenderer& renderer, Passes& value, Compile function) {
    const char* vertex_names[vertex_count] = {"ui_vs",
                                              "mesh_vs",
                                              "lit_vs",
                                              "lightmap_vs",
                                              "model_vs",
                                              "skin_vs",
                                              "world_vs",
                                              "reflective_model_vs",
                                              "reflective_skin_vs",
                                              "textured_world_vs",
                                              "multi28_vs",
                                              "multi36_vs",
                                              "ui_dual_vs",
                                              "unlit_model_vs",
                                              "water32_vs",
                                              "water56_vs",
                                              "bump_reflect_vs",
                                              "fullscreen_vs"};
    const char* pixel_names[pixel_count] = {"ui_ps",
                                            "mask_ps",
                                            "surface_ps",
                                            "lightmap_ps",
                                            "water_ps",
                                            "copy_ps",
                                            "eight_tap_ps",
                                            "gaussian_x_ps",
                                            "gaussian_y_ps",
                                            "gamma_ps",
                                            "reflection_ps",
                                            "projected_shadow_ps",
                                            "projected_effect_ps",
                                            "multi36_ps",
                                            "multi28_ps",
                                            "replace28_ps",
                                            "signed28_ps",
                                            "replace36_ps",
                                            "signed36_ps",
                                            "ui_dual_ps",
                                            "water56_ps",
                                            "bump_reflect_ps"};
    D3D11_INPUT_ELEMENT_DESC ui[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0}};
    D3D11_INPUT_ELEMENT_DESC dual[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0}};
    D3D11_INPUT_ELEMENT_DESC mesh[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0}};
    D3D11_INPUT_ELEMENT_DESC model[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}};
    D3D11_INPUT_ELEMENT_DESC water32[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0}};
    D3D11_INPUT_ELEMENT_DESC skin[] = {
        // Packed indices are authored bone IDs, not float-register offsets.
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"BLENDWEIGHT", 0, DXGI_FORMAT_R32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"BLENDINDICES", 0, DXGI_FORMAT_R8G8B8A8_UINT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0}};
    D3D11_INPUT_ELEMENT_DESC water56[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 2, DXGI_FORMAT_R32G32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 3, DXGI_FORMAT_R32G32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0}};
    D3D11_INPUT_ELEMENT_DESC world[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 16, D3D11_INPUT_PER_VERTEX_DATA, 0}};
    D3D11_INPUT_ELEMENT_DESC textured_world[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0}};
    D3D11_INPUT_ELEMENT_DESC multi[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, 20, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"TEXCOORD", 2, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0}};
    for (UINT i = 0; i < vertex_count; ++i) {
        ID3DBlob* code = nullptr;
        HRESULT status = compile(function, vertex_names[i], "vs_4_0", &code);
        if (FAILED(status))
            return status;
        status = renderer.device->CreateVertexShader(
            code->GetBufferPointer(), code->GetBufferSize(), nullptr, &value.vertices[i]);
        const D3D11_INPUT_ELEMENT_DESC* elements = nullptr;
        UINT count = 0, layout = 0;
        switch (i) {
        case ui_vertex:
            elements = ui;
            count = 3;
            layout = ui_layout;
            break;
        case mesh_vertex:
            elements = mesh;
            count = 4;
            layout = mesh_layout;
            break;
        case lightmap_vertex:
            elements = mesh;
            count = 5;
            layout = lightmap_layout;
            break;
        case model_vertex:
            elements = model;
            count = 3;
            layout = model_layout;
            break;
        case skin_vertex:
            elements = skin;
            count = 5;
            layout = skin_layout;
            break;
        case world_vertex:
        case bump_reflect_vertex:
            elements = world;
            count = 3;
            layout = world_layout;
            break;
        case textured_world_vertex:
            elements = textured_world;
            count = 2;
            layout = textured_world_layout;
            break;
        case multi28_vertex:
            elements = multi;
            count = 3;
            layout = multi28_layout;
            break;
        case multi36_vertex:
            elements = multi;
            count = 4;
            layout = multi36_layout;
            break;
        case ui_dual_vertex:
            elements = dual;
            count = 4;
            layout = ui_dual_layout;
            break;
        case water32_vertex:
            elements = water32;
            count = 4;
            layout = water32_layout;
            break;
        case water56_vertex:
            elements = water56;
            count = 6;
            layout = water56_layout;
            break;
        default:
            break;
        }
        if (SUCCEEDED(status) && elements)
            status =
                renderer.device->CreateInputLayout(elements, count, code->GetBufferPointer(),
                                                   code->GetBufferSize(), &value.layouts[layout]);
        release(code);
        if (FAILED(status))
            return status;
    }
    for (UINT i = 0; i < pixel_count; ++i) {
        ID3DBlob* code = nullptr;
        HRESULT status = compile(function, pixel_names[i], "ps_4_0", &code);
        if (FAILED(status))
            return status;
        status = renderer.device->CreatePixelShader(code->GetBufferPointer(), code->GetBufferSize(),
                                                    nullptr, &value.pixels[i]);
        release(code);
        if (FAILED(status))
            return status;
    }
    return S_OK;
}
HRESULT create_states(NativeRenderer& renderer, Passes& value) {
    for (UINT i = 0; i < 6; ++i) {
        D3D11_BLEND_DESC description = {};
        auto& target = description.RenderTarget[0];
        target.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        target.BlendEnable = i != UINT(Blend::opaque);
        target.BlendOp = target.BlendOpAlpha = D3D11_BLEND_OP_ADD;
        target.SrcBlend = D3D11_BLEND_SRC_ALPHA;
        target.DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
        target.SrcBlendAlpha = D3D11_BLEND_ONE;
        target.DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
        switch (Blend(i)) {
        case Blend::opaque:
            target.SrcBlend = D3D11_BLEND_ONE;
            target.DestBlend = D3D11_BLEND_ZERO;
            break;
        case Blend::additive:
            target.DestBlend = D3D11_BLEND_ONE;
            break;
        case Blend::color_add:
            target.SrcBlend = D3D11_BLEND_ONE;
            target.DestBlend = D3D11_BLEND_ONE;
            break;
        case Blend::multiply:
            target.SrcBlend = D3D11_BLEND_DEST_COLOR;
            target.DestBlend = D3D11_BLEND_ZERO;
            break;
        case Blend::inverse_alpha:
            target.SrcBlend = D3D11_BLEND_ONE;
            break;
        default:
            break;
        }
        HRESULT status = renderer.device->CreateBlendState(&description, &value.blends[i]);
        if (FAILED(status))
            return status;
    }
    for (UINT i = 0; i < 3; ++i) {
        D3D11_DEPTH_STENCIL_DESC description = {};
        description.DepthEnable = i != UINT(Depth::disabled);
        description.DepthWriteMask =
            i == UINT(Depth::write) ? D3D11_DEPTH_WRITE_MASK_ALL : D3D11_DEPTH_WRITE_MASK_ZERO;
        description.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
        HRESULT status = renderer.device->CreateDepthStencilState(&description, &value.depths[i]);
        if (FAILED(status))
            return status;
        for (UINT scissor = 0; scissor < 2; ++scissor) {
            D3D11_RASTERIZER_DESC raster = {};
            raster.FillMode = D3D11_FILL_SOLID;
            raster.CullMode = i == UINT(Cull::none)    ? D3D11_CULL_NONE
                              : i == UINT(Cull::front) ? D3D11_CULL_FRONT
                                                       : D3D11_CULL_BACK;
            raster.DepthClipEnable = TRUE;
            raster.ScissorEnable = scissor;
            status = renderer.device->CreateRasterizerState(&raster, &value.rasters[i][scissor]);
            if (FAILED(status))
                return status;
        }
    }
    for (UINT i = 0; i < 5; ++i) {
        D3D11_SAMPLER_DESC description = {};
        description.Filter = i == UINT(Sampling::point_clamp) ? D3D11_FILTER_MIN_MAG_MIP_POINT
                             : i == UINT(Sampling::anisotropic_wrap)
                                 ? D3D11_FILTER_ANISOTROPIC
                                 : D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        description.AddressU = description.AddressV = description.AddressW =
            i == UINT(Sampling::linear_mirror) ? D3D11_TEXTURE_ADDRESS_MIRROR
            : i < UINT(Sampling::linear_wrap)  ? D3D11_TEXTURE_ADDRESS_CLAMP
                                               : D3D11_TEXTURE_ADDRESS_WRAP;
        description.MaxAnisotropy = 8;
        description.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
        description.MaxLOD = D3D11_FLOAT32_MAX;
        HRESULT status = renderer.device->CreateSamplerState(&description, &value.samplers[i]);
        if (FAILED(status))
            return status;
    }
    return S_OK;
}
ObjectData object_data(const StaticDraw& draw) {
    ObjectData value = {};
    value.world = draw.world;
    value.reflection = identity();
    value.tint = draw.material.style.tint;
    value.diffuse = draw.material.diffuse_color;
    value.ambient = draw.material.ambient_color;
    value.specular = draw.material.specular_color;
    value.surface[0] = draw.material.specular_power;
    value.emissive = draw.material.emissive_color;
    value.environment = draw.material.environment_transform;
    value.environment_eye = draw.material.environment_eye;
    value.surface[3] = draw.material.explicit_environment_frame ? 1 : 0;
    value.texture_projection = draw.material.texture_projection;
    value.projection_flags[0] = draw.material.projected_texture ? 1 : 0;
    value.parameters[0] = draw.material.style.alpha_cutoff;
    value.parameters[3] = 1;
    return value;
}
D3D11_BLEND alpha_factor(D3D11_BLEND factor) {
    switch (factor) {
    case D3D11_BLEND_SRC_COLOR:
        return D3D11_BLEND_SRC_ALPHA;
    case D3D11_BLEND_INV_SRC_COLOR:
        return D3D11_BLEND_INV_SRC_ALPHA;
    case D3D11_BLEND_DEST_COLOR:
        return D3D11_BLEND_DEST_ALPHA;
    case D3D11_BLEND_INV_DEST_COLOR:
        return D3D11_BLEND_INV_DEST_ALPHA;
    case D3D11_BLEND_SRC_ALPHA_SAT:
        return D3D11_BLEND_ONE;
    case D3D11_BLEND_SRC1_COLOR:
        return D3D11_BLEND_SRC1_ALPHA;
    case D3D11_BLEND_INV_SRC1_COLOR:
        return D3D11_BLEND_INV_SRC1_ALPHA;
    default:
        return factor;
    }
}
HRESULT blend_state(NativeRenderer& renderer, Passes& value, const DrawStyle& style,
                    ID3D11BlendState*& result) {
    if (!UINT(style.source_blend) && !UINT(style.destination_blend)) {
        result = value.blends[UINT(style.blend)];
        return S_OK;
    }
    UINT source = UINT(style.source_blend), destination = UINT(style.destination_blend);
    if (!source || source >= 20 || !destination || destination >= 20)
        return E_INVALIDARG;
    auto*& cached = value.custom_blends[source][destination];
    if (!cached) {
        D3D11_BLEND_DESC description = {};
        auto& target = description.RenderTarget[0];
        target.BlendEnable = TRUE;
        target.RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        target.BlendOp = target.BlendOpAlpha = D3D11_BLEND_OP_ADD;
        target.SrcBlend = style.source_blend;
        target.DestBlend = style.destination_blend;
        target.SrcBlendAlpha = alpha_factor(style.source_blend);
        target.DestBlendAlpha = alpha_factor(style.destination_blend);
        HRESULT status = renderer.device->CreateBlendState(&description, &cached);
        if (FAILED(status))
            return status;
    }
    result = cached;
    return S_OK;
}
HRESULT bind(NativeRenderer& renderer, VertexProgram vertex, PixelProgram pixel,
             VertexLayout layout, const DrawStyle& style, const ObjectData& object,
             ID3D11ShaderResourceView* image, ID3D11ShaderResourceView* secondary,
             const D3D11_RECT* scissor = nullptr, ID3D11ShaderResourceView* detail = nullptr) {
    auto* value = passes(renderer);
    if (!value || UINT(style.blend) >= 6 || UINT(style.depth) >= 3 || UINT(style.cull) >= 3 ||
        UINT(style.sampling) >= 5)
        return E_INVALIDARG;
    auto* context = renderer.context;
    probe_prepare(renderer, UINT(vertex), UINT(pixel), UINT(layout), object.world, style, image,
                  secondary);
    if (!value->object_valid || !equal(&value->object, &object, sizeof(object))) {
        context->UpdateSubresource(value->object_buffer, 0, nullptr, &object, 0, 0);
        value->object = object;
        value->object_valid = true;
    }
    if (value->bound_vertex != value->vertices[vertex]) {
        context->VSSetShader(value->vertices[vertex], nullptr, 0);
        value->bound_vertex = value->vertices[vertex];
    }
    if (value->bound_pixel != value->pixels[pixel]) {
        context->PSSetShader(value->pixels[pixel], nullptr, 0);
        value->bound_pixel = value->pixels[pixel];
    }
    ID3D11InputLayout* input = vertex == fullscreen_vertex ? nullptr : value->layouts[layout];
    if (value->bound_layout != input) {
        context->IASetInputLayout(input);
        value->bound_layout = input;
    }
    ID3D11BlendState* blend = nullptr;
    HRESULT blend_result = blend_state(renderer, *value, style, blend);
    if (FAILED(blend_result))
        return blend_result;
    if (value->bound_blend != blend ||
        !equal(&value->bound_blend_factor, &style.blend_factor, sizeof(Color))) {
        const float factors[4] = {style.blend_factor.r, style.blend_factor.g, style.blend_factor.b,
                                  style.blend_factor.a};
        context->OMSetBlendState(blend, factors, 0xffffffff);
        value->bound_blend = blend;
        value->bound_blend_factor = style.blend_factor;
    }
    auto* depth = value->depths[UINT(style.depth)];
    if (value->bound_depth != depth) {
        context->OMSetDepthStencilState(depth, 0);
        value->bound_depth = depth;
    }
    auto* raster = value->rasters[UINT(style.cull)][scissor != nullptr];
    if (value->bound_raster != raster) {
        context->RSSetState(raster);
        value->bound_raster = raster;
    }
    if (scissor)
        context->RSSetScissorRects(1, scissor);
    auto* sampler = value->samplers[UINT(style.sampling)];
    if (value->bound_sampler != sampler) {
        ID3D11SamplerState* samplers[3] = {sampler, value->samplers[UINT(Sampling::linear_clamp)],
                                           value->samplers[UINT(Sampling::linear_wrap)]};
        context->PSSetSamplers(0, 3, samplers);
        value->bound_sampler = sampler;
    }
    ID3D11ShaderResourceView* views[3] = {image ? image : value->white,
                                          secondary ? secondary : value->white,
                                          detail ? detail : value->white};
    context->PSSetShaderResources(0, 3, views);
    ID3D11Buffer* buffers[3] = {value->scene_buffer, value->object_buffer, value->bone_buffer};
    context->VSSetConstantBuffers(0, 3, buffers);
    context->PSSetConstantBuffers(0, 2, buffers);
    context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    return S_OK;
}
HRESULT indexed(NativeRenderer& renderer, const MeshRange& mesh, UINT stride) {
    if (!mesh.vertices || !mesh.indices || !mesh.index_count ||
        (mesh.index_format != DXGI_FORMAT_R16_UINT && mesh.index_format != DXGI_FORMAT_R32_UINT))
        return E_INVALIDARG;
    renderer.context->IASetVertexBuffers(0, 1, &mesh.vertices, &stride, &mesh.vertex_byte_offset);
    renderer.context->IASetIndexBuffer(mesh.indices, mesh.index_format, 0);
    renderer.context->DrawIndexed(mesh.index_count, mesh.first_index, mesh.base_vertex);
    probe_after_draw(renderer);
    return S_OK;
}
HRESULT mesh_draw(NativeRenderer& renderer, const StaticDraw& draw, VertexProgram vertex,
                  PixelProgram pixel, VertexLayout layout, UINT stride,
                  ID3D11ShaderResourceView* secondary, const ObjectData* custom = nullptr) {
    ObjectData object = custom ? *custom : object_data(draw);
    HRESULT status = bind(renderer, vertex, pixel, layout, draw.material.style, object,
                          draw.material.diffuse, secondary);
    return FAILED(status) ? status : indexed(renderer, draw.mesh, stride);
}
} // namespace

HRESULT passes_initialize(NativeRenderer& renderer) {
    if (!renderer.device || !renderer.context || renderer.pipeline_data)
        return E_INVALIDARG;
    auto* value =
        static_cast<Passes*>(HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(Passes)));
    if (!value)
        return E_OUTOFMEMORY;
    renderer.pipeline_data = value;
    HMODULE module = LoadLibraryA("d3dcompiler_47.dll");
    auto function =
        module ? reinterpret_cast<Compile>(GetProcAddress(module, "D3DCompile")) : nullptr;
    HRESULT status = function ? create_programs(renderer, *value, function)
                              : HRESULT_FROM_WIN32(ERROR_MOD_NOT_FOUND);
    if (module)
        FreeLibrary(module);
    if (SUCCEEDED(status))
        status = create_states(renderer, *value);
    if (SUCCEEDED(status))
        status = buffer(renderer, sizeof(SceneData), D3D11_BIND_CONSTANT_BUFFER, false, nullptr,
                        &value->scene_buffer);
    if (SUCCEEDED(status))
        status = buffer(renderer, sizeof(ObjectData), D3D11_BIND_CONSTANT_BUFFER, false, nullptr,
                        &value->object_buffer);
    if (SUCCEEDED(status))
        status = buffer(renderer, sizeof(WaterData), D3D11_BIND_CONSTANT_BUFFER, false, nullptr,
                        &value->water_buffer);
    if (SUCCEEDED(status))
        status = buffer(renderer, sizeof(Matrix) * 256, D3D11_BIND_CONSTANT_BUFFER, true, nullptr,
                        &value->bone_buffer);
    value->ui_capacity = sizeof(UiVertex) * 4096;
    if (SUCCEEDED(status))
        status = buffer(renderer, value->ui_capacity, D3D11_BIND_VERTEX_BUFFER, true, nullptr,
                        &value->ui_buffer);
    const uint16_t indices[6] = {0, 1, 2, 0, 2, 3};
    if (SUCCEEDED(status))
        status = buffer(renderer, sizeof(indices), D3D11_BIND_INDEX_BUFFER, false, indices,
                        &value->quad_indices);
    ID3D11Texture2D* white = nullptr;
    if (SUCCEEDED(status)) {
        D3D11_TEXTURE2D_DESC description = {};
        description.Width = description.Height = description.MipLevels = description.ArraySize = 1;
        description.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
        description.SampleDesc.Count = 1;
        description.Usage = D3D11_USAGE_IMMUTABLE;
        description.BindFlags = D3D11_BIND_SHADER_RESOURCE;
        const UINT pixel = 0xffffffff;
        D3D11_SUBRESOURCE_DATA initial = {&pixel, 4, 4};
        status = renderer.device->CreateTexture2D(&description, &initial, &white);
        if (SUCCEEDED(status))
            status = renderer.device->CreateShaderResourceView(white, nullptr, &value->white);
    }
    release(white);
    if (FAILED(status)) {
        passes_shutdown(renderer);
        return status;
    }
    Scene scene;
    scene.view = scene.view_projection = identity();
    return begin_scene(renderer, scene);
}
void passes_shutdown(NativeRenderer& renderer) {
    auto* value = passes(renderer);
    if (!value)
        return;
    for (auto*& item : value->vertices)
        release(item);
    for (auto*& item : value->pixels)
        release(item);
    for (auto*& item : value->layouts)
        release(item);
    for (auto*& item : value->blends)
        release(item);
    for (auto& row : value->custom_blends)
        for (auto*& item : row)
            release(item);
    for (auto*& item : value->depths)
        release(item);
    for (auto& row : value->rasters)
        for (auto*& item : row)
            release(item);
    for (auto*& item : value->samplers)
        release(item);
    release(value->scene_buffer);
    release(value->object_buffer);
    release(value->bone_buffer);
    release(value->ui_buffer);
    release(value->world_buffer);
    release(value->world_index_buffer);
    release(value->water_buffer);
    release(value->quad_indices);
    release(value->white);
    HeapFree(GetProcessHeap(), 0, value);
    renderer.pipeline_data = nullptr;
}
void passes_reset_bindings(NativeRenderer& renderer) {
    auto* value = passes(renderer);
    if (!value)
        return;
    value->bound_vertex = nullptr;
    value->bound_pixel = nullptr;
    value->bound_layout = nullptr;
    value->bound_blend = nullptr;
    value->bound_depth = nullptr;
    value->bound_raster = nullptr;
    value->bound_sampler = nullptr;
}
HRESULT begin_scene(NativeRenderer& renderer, const Scene& scene) {
    auto* value = passes(renderer);
    if (!value || !renderer.width || !renderer.height)
        return E_INVALIDARG;
    renderer.scene = scene;
    SceneData data = {};
    data.view_projection = scene.view_projection;
    data.view = scene.view;
    data.ambient = scene.ambient;
    data.directional = scene.directional;
    copy(data.light_direction, scene.light_direction, sizeof(data.light_direction));
    copy(data.camera, scene.camera, sizeof(data.camera));
    data.fog[0] = scene.fog_start;
    data.fog[1] = scene.fog_end;
    data.fog[2] = scene.fog_enabled ? 1 : 0;
    data.fog_color = scene.fog_color;
    copy(data.clip_plane, scene.clip_plane, sizeof(data.clip_plane));
    data.viewport[0] = float(renderer.width);
    data.viewport[1] = float(renderer.height);
    data.point_color = scene.point_light.diffuse;
    for (UINT i = 0; i < 3; ++i) {
        data.point_position_range[i] = scene.point_light.position[i];
        data.point_attenuation[i] = scene.point_light.attenuation[i];
    }
    data.point_position_range[3] = scene.point_light.range;
    data.point_attenuation[3] = scene.point_light.enabled ? 1 : 0;
    if (!value->scene_valid || !equal(&value->scene, &data, sizeof(data))) {
        renderer.context->UpdateSubresource(value->scene_buffer, 0, nullptr, &data, 0, 0);
        value->scene = data;
        value->scene_valid = true;
    }
    return S_OK;
}
HRESULT draw_ui(NativeRenderer& renderer, const UiDraw& draw) {
    auto* value = passes(renderer);
    if (!value || !draw.vertices || !draw.vertex_count || draw.vertex_count > 0x07ffffff ||
        (draw.primitive == UiPrimitive::quad    ? draw.vertex_count != 4
         : draw.primitive == UiPrimitive::lines ? draw.vertex_count % 2 != 0
                                                : draw.vertex_count % 3 != 0))
        return E_INVALIDARG;
    if (draw.vertex_count * sizeof(UiVertex) > value->ui_capacity) {
        ID3D11Buffer* next = nullptr;
        HRESULT status = buffer(renderer, draw.vertex_count * sizeof(UiVertex),
                                D3D11_BIND_VERTEX_BUFFER, true, nullptr, &next);
        if (FAILED(status))
            return status;
        release(value->ui_buffer);
        value->ui_buffer = next;
        value->ui_capacity = draw.vertex_count * sizeof(UiVertex);
    }
    D3D11_MAPPED_SUBRESOURCE mapping = {};
    HRESULT status =
        renderer.context->Map(value->ui_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapping);
    if (FAILED(status))
        return status;
    copy(mapping.pData, draw.vertices, draw.vertex_count * sizeof(UiVertex));
    renderer.context->Unmap(value->ui_buffer, 0);
    ObjectData object = {};
    object.tint = draw.style.tint;
    object.parameters[0] = draw.style.alpha_cutoff;
    const D3D11_RECT* scissor = draw.scissor;
    if (!scissor && renderer.ui_scissor_enabled)
        scissor = &renderer.ui_scissor;
    status = bind(renderer, ui_vertex, draw.mask ? mask_pixel : ui_pixel, ui_layout, draw.style,
                  object, draw.image, draw.mask, scissor);
    if (FAILED(status))
        return status;
    UINT stride = sizeof(UiVertex), offset = 0;
    renderer.context->IASetVertexBuffers(0, 1, &value->ui_buffer, &stride, &offset);
    if (draw.primitive == UiPrimitive::lines)
        renderer.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
    if (draw.primitive == UiPrimitive::quad) {
        renderer.context->IASetIndexBuffer(value->quad_indices, DXGI_FORMAT_R16_UINT, 0);
        renderer.context->DrawIndexed(6, 0, 0);
    } else
        renderer.context->Draw(draw.vertex_count, 0);
    probe_after_draw(renderer, draw.vertices, draw.vertex_count * sizeof(UiVertex));
    renderer.set_ui_image(draw.image);
    return S_OK;
}
HRESULT draw_ui_dual36(NativeRenderer& renderer, const UiDualDraw& draw) {
    auto* value = passes(renderer);
    if (!value || !draw.vertices || !draw.vertex_count ||
        draw.vertex_count > 0x7fffffff / sizeof(UiDualVertex36))
        return E_INVALIDARG;
    if (draw.primitive == UiPrimitive::quad    ? draw.vertex_count != 4
        : draw.primitive == UiPrimitive::lines ? draw.vertex_count % 2
                                               : draw.vertex_count % 3)
        return E_INVALIDARG;
    UINT bytes = draw.vertex_count * sizeof(UiDualVertex36);
    if (bytes > value->ui_capacity) {
        ID3D11Buffer* next = nullptr;
        HRESULT result = buffer(renderer, bytes, D3D11_BIND_VERTEX_BUFFER, true, nullptr, &next);
        if (FAILED(result))
            return result;
        release(value->ui_buffer);
        value->ui_buffer = next;
        value->ui_capacity = bytes;
    }
    D3D11_MAPPED_SUBRESOURCE mapped = {};
    HRESULT result =
        renderer.context->Map(value->ui_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
    if (FAILED(result))
        return result;
    copy(mapped.pData, draw.vertices, bytes);
    renderer.context->Unmap(value->ui_buffer, 0);
    ObjectData object = {};
    object.tint = draw.style.tint;
    object.parameters[0] = draw.style.alpha_cutoff;
    object.surface[2] = draw.use_mask_rgb ? 1 : 0;
    const D3D11_RECT* scissor = draw.scissor;
    if (!scissor && renderer.ui_scissor_enabled)
        scissor = &renderer.ui_scissor;
    result = bind(renderer, ui_dual_vertex, ui_dual_pixel, ui_dual_layout, draw.style, object,
                  draw.image, draw.mask, scissor);
    if (FAILED(result))
        return result;
    UINT stride = sizeof(UiDualVertex36), offset = 0;
    renderer.context->IASetVertexBuffers(0, 1, &value->ui_buffer, &stride, &offset);
    if (draw.primitive == UiPrimitive::quad) {
        renderer.context->IASetIndexBuffer(value->quad_indices, DXGI_FORMAT_R16_UINT, 0);
        renderer.context->DrawIndexed(6, 0, 0);
    } else {
        if (draw.primitive == UiPrimitive::lines)
            renderer.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);
        renderer.context->Draw(draw.vertex_count, 0);
    }
    probe_after_draw(renderer, draw.vertices, draw.vertex_count * sizeof(UiDualVertex36));
    renderer.set_ui_image(draw.image);
    return S_OK;
}
HRESULT draw_static(NativeRenderer& renderer, const StaticDraw& draw) {
    return mesh_draw(renderer, draw, mesh_vertex, surface_pixel, mesh_layout, sizeof(MeshVertex),
                     nullptr);
}
HRESULT draw_lit(NativeRenderer& renderer, const StaticDraw& draw) {
    return mesh_draw(renderer, draw, lit_vertex, surface_pixel, mesh_layout, sizeof(MeshVertex),
                     nullptr);
}
HRESULT draw_model(NativeRenderer& renderer, const StaticDraw& draw) {
    return mesh_draw(renderer, draw, model_vertex, surface_pixel, model_layout, sizeof(ModelVertex),
                     nullptr);
}
HRESULT draw_unlit_model(NativeRenderer& renderer, const StaticDraw& draw) {
    return mesh_draw(renderer, draw, unlit_model_vertex, surface_pixel, model_layout,
                     sizeof(ModelVertex), nullptr);
}
HRESULT draw_reflective_model(NativeRenderer& renderer, const StaticDraw& draw) {
    return mesh_draw(renderer, draw, reflective_model_vertex, reflection_pixel, model_layout,
                     sizeof(ModelVertex), draw.material.environment);
}
HRESULT draw_lightmap(NativeRenderer& renderer, const LightmapDraw& draw) {
    return mesh_draw(renderer, draw, lightmap_vertex, lightmap_pixel, lightmap_layout,
                     sizeof(LightmapVertex), draw.lightmap);
}
HRESULT draw_skinned(NativeRenderer& renderer, const SkinDraw& draw) {
    auto* value = passes(renderer);
    if (!value || !draw.bones || !draw.bone_count || draw.bone_count > 256)
        return E_INVALIDARG;
    D3D11_MAPPED_SUBRESOURCE mapping = {};
    HRESULT status =
        renderer.context->Map(value->bone_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapping);
    if (FAILED(status))
        return status;
    copy(mapping.pData, draw.bones, draw.bone_count * sizeof(Matrix));
    renderer.context->Unmap(value->bone_buffer, 0);
    return mesh_draw(renderer, draw, skin_vertex, surface_pixel, skin_layout, sizeof(SkinVertex),
                     nullptr);
}
HRESULT draw_reflective_skinned(NativeRenderer& renderer, const SkinDraw& draw) {
    auto* value = passes(renderer);
    if (!value || !draw.bones || !draw.bone_count || draw.bone_count > 256)
        return E_INVALIDARG;
    D3D11_MAPPED_SUBRESOURCE mapping = {};
    HRESULT status =
        renderer.context->Map(value->bone_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapping);
    if (FAILED(status))
        return status;
    copy(mapping.pData, draw.bones, draw.bone_count * sizeof(Matrix));
    renderer.context->Unmap(value->bone_buffer, 0);
    return mesh_draw(renderer, draw, reflective_skin_vertex, reflection_pixel, skin_layout,
                     sizeof(SkinVertex), draw.material.environment);
}
HRESULT draw_water(NativeRenderer& renderer, const WaterDraw& draw) {
    ObjectData object = object_data(draw);
    object.reflection = draw.reflection_projection;
    object.parameters[1] = draw.distortion;
    object.parameters[2] = draw.reflectivity;
    object.uv[0] = draw.uv_offset[0];
    object.uv[1] = draw.uv_offset[1];
    return mesh_draw(renderer, draw, mesh_vertex, water_pixel, mesh_layout, sizeof(MeshVertex),
                     draw.reflection, &object);
}
namespace {
HRESULT water_quad(NativeRenderer& renderer, const WaterDraw& draw, VertexProgram vertex,
                   PixelProgram pixel, VertexLayout layout, UINT stride) {
    if (!draw.mesh.vertices)
        return E_INVALIDARG;
    ObjectData object = object_data(draw);
    object.reflection = draw.reflection_projection;
    object.parameters[1] = draw.distortion;
    object.parameters[2] = draw.reflectivity;
    object.uv[0] = draw.uv_offset[0];
    object.uv[1] = draw.uv_offset[1];
    HRESULT result = bind(renderer, vertex, pixel, layout, draw.material.style, object,
                          draw.material.diffuse, draw.reflection, nullptr, draw.refraction);
    if (FAILED(result))
        return result;
    if (draw.mesh.indices)
        return indexed(renderer, draw.mesh, stride);
    renderer.context->IASetVertexBuffers(0, 1, &draw.mesh.vertices, &stride,
                                         &draw.mesh.vertex_byte_offset);
    renderer.context->IASetIndexBuffer(nullptr, DXGI_FORMAT_R16_UINT, 0);
    renderer.context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
    renderer.context->Draw(4, 0);
    probe_after_draw(renderer);
    return S_OK;
}
} // namespace
HRESULT draw_water32(NativeRenderer& renderer, const WaterDraw& draw) {
    return water_quad(renderer, draw, water32_vertex, water_pixel, water32_layout,
                      sizeof(WaterVertex32));
}
HRESULT draw_water56(NativeRenderer& renderer, const WaterDraw& draw) {
    auto* value = passes(renderer);
    if (!value)
        return E_UNEXPECTED;
    WaterData data = {};
    data.refraction = draw.refraction_projection;
    data.color = draw.water_color;
    data.parameters[0] = draw.distortion;
    data.parameters[1] = draw.reflectivity;
    data.parameters[2] = draw.opacity;
    data.parameters[3] = draw.normal_signed ? 1 : 0;
    for (UINT i = 0; i < 2; ++i) {
        data.offsets[i] = draw.uv_offset[i];
        data.offsets[i + 2] = draw.second_uv_offset[i];
    }
    renderer.context->UpdateSubresource(value->water_buffer, 0, nullptr, &data, 0, 0);
    renderer.context->VSSetConstantBuffers(3, 1, &value->water_buffer);
    renderer.context->PSSetConstantBuffers(3, 1, &value->water_buffer);
    ID3D11ShaderResourceView* normal = draw.normal_second      ? draw.normal_second
                                       : draw.material.diffuse ? draw.material.diffuse
                                                               : value->white;
    renderer.context->PSSetShaderResources(3, 1, &normal);
    return water_quad(renderer, draw, water56_vertex, water56_pixel, water56_layout,
                      sizeof(WaterVertex56));
}
HRESULT draw_bump_reflect_world24(NativeRenderer& renderer, const BumpReflectDraw& draw) {
    ObjectData object = object_data(draw);
    object.environment = draw.inverse_view;
    object.environment_eye = {draw.light_position[0], draw.light_position[1],
                              draw.light_position[2], draw.light_position[3]};
    object.uv[0] = draw.uv_offset[0];
    object.uv[1] = draw.uv_offset[1];
    StaticDraw surface = draw;
    surface.material.diffuse = draw.normal;
    return mesh_draw(renderer, surface, bump_reflect_vertex, bump_reflect_pixel, world_layout,
                     sizeof(WorldVertex), draw.environment, &object);
}
namespace {
HRESULT world_triangles(NativeRenderer& renderer, const WorldDraw& draw, PixelProgram pixel,
                        const ObjectData* custom = nullptr) {
    auto* value = passes(renderer);
    if (!value || !draw.vertices || !draw.vertex_count || draw.vertex_count % 3 ||
        draw.vertex_count > 0x07ffffff)
        return E_INVALIDARG;
    if (draw.vertex_count > value->world_capacity) {
        ID3D11Buffer* next = nullptr;
        UINT capacity = draw.vertex_count < 4096 ? 4096 : draw.vertex_count;
        HRESULT status = buffer(renderer, capacity * sizeof(WorldVertex), D3D11_BIND_VERTEX_BUFFER,
                                true, nullptr, &next);
        if (FAILED(status))
            return status;
        release(value->world_buffer);
        value->world_buffer = next;
        value->world_capacity = capacity;
    }
    D3D11_MAPPED_SUBRESOURCE mapping = {};
    HRESULT status =
        renderer.context->Map(value->world_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapping);
    if (FAILED(status))
        return status;
    copy(mapping.pData, draw.vertices, draw.vertex_count * sizeof(WorldVertex));
    renderer.context->Unmap(value->world_buffer, 0);
    StaticDraw material;
    material.world = draw.world;
    material.material = draw.material;
    ObjectData object = custom ? *custom : object_data(material);
    status = bind(renderer, world_vertex, pixel, world_layout, draw.material.style, object,
                  draw.material.diffuse, nullptr);
    if (FAILED(status))
        return status;
    UINT stride = sizeof(WorldVertex), offset = 0;
    renderer.context->IASetVertexBuffers(0, 1, &value->world_buffer, &stride, &offset);
    renderer.context->Draw(draw.vertex_count, 0);
    probe_after_draw(renderer, draw.vertices, draw.vertex_count * sizeof(WorldVertex));
    return S_OK;
}
} // namespace
HRESULT draw_world_triangles(NativeRenderer& renderer, const WorldDraw& draw) {
    return world_triangles(renderer, draw, surface_pixel);
}
HRESULT draw_projected_world_triangles(NativeRenderer& renderer, const WorldDraw& draw,
                                       ID3D11ShaderResourceView* shadow, const Matrix& projector,
                                       float opacity) {
    if (!shadow || opacity < 0 || opacity > 1)
        return E_INVALIDARG;
    WorldDraw surface = draw;
    surface.material.diffuse = shadow;
    surface.material.style.blend = Blend::alpha;
    surface.material.style.source_blend = surface.material.style.destination_blend = D3D11_BLEND(0);
    surface.material.style.sampling = Sampling::linear_clamp;
    surface.material.style.alpha_cutoff = 0;
    StaticDraw parameters;
    parameters.world = surface.world;
    parameters.material = surface.material;
    ObjectData object = object_data(parameters);
    object.reflection = projector;
    object.parameters[2] = opacity;
    return world_triangles(renderer, surface, projected_shadow_pixel, &object);
}
HRESULT draw_world_indexed(NativeRenderer& renderer, const StaticDraw& draw) {
    return mesh_draw(renderer, draw, world_vertex, surface_pixel, world_layout, sizeof(WorldVertex),
                     nullptr);
}
HRESULT draw_world_indexed_triangles(NativeRenderer& renderer, const IndexedWorldDraw& draw) {
    auto* value = passes(renderer);
    if (!value || !draw.vertices || !draw.vertex_count || draw.vertex_count > 65536 ||
        !draw.indices || !draw.index_count || draw.index_count % 3 || draw.index_count > 0x07ffffff)
        return E_INVALIDARG;
    for (UINT i = 0; i < draw.index_count; ++i)
        if (draw.indices[i] >= draw.vertex_count)
            return E_INVALIDARG;
    if (draw.vertex_count > value->world_capacity) {
        ID3D11Buffer* next = nullptr;
        UINT capacity = draw.vertex_count < 4096 ? 4096 : draw.vertex_count;
        HRESULT status = buffer(renderer, capacity * sizeof(WorldVertex), D3D11_BIND_VERTEX_BUFFER,
                                true, nullptr, &next);
        if (FAILED(status))
            return status;
        release(value->world_buffer);
        value->world_buffer = next;
        value->world_capacity = capacity;
    }
    if (draw.index_count > value->world_index_capacity) {
        ID3D11Buffer* next = nullptr;
        UINT capacity = draw.index_count < 4096 ? 4096 : draw.index_count;
        HRESULT status = buffer(renderer, capacity * sizeof(uint16_t), D3D11_BIND_INDEX_BUFFER,
                                true, nullptr, &next);
        if (FAILED(status))
            return status;
        release(value->world_index_buffer);
        value->world_index_buffer = next;
        value->world_index_capacity = capacity;
    }
    D3D11_MAPPED_SUBRESOURCE mapping = {};
    HRESULT status =
        renderer.context->Map(value->world_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapping);
    if (FAILED(status))
        return status;
    copy(mapping.pData, draw.vertices, draw.vertex_count * sizeof(WorldVertex));
    if (draw.texture_only)
        for (UINT i = 0; i < draw.vertex_count; ++i)
            static_cast<WorldVertex*>(mapping.pData)[i].argb = 0xffffffff;
    renderer.context->Unmap(value->world_buffer, 0);
    status =
        renderer.context->Map(value->world_index_buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapping);
    if (FAILED(status))
        return status;
    copy(mapping.pData, draw.indices, draw.index_count * sizeof(uint16_t));
    renderer.context->Unmap(value->world_index_buffer, 0);
    StaticDraw surface;
    surface.world = draw.world;
    surface.material = draw.material;
    surface.mesh.vertices = value->world_buffer;
    surface.mesh.indices = value->world_index_buffer;
    surface.mesh.index_count = draw.index_count;
    return mesh_draw(renderer, surface, world_vertex, surface_pixel, world_layout,
                     sizeof(WorldVertex), nullptr);
}
HRESULT draw_textured_world_indexed(NativeRenderer& renderer, const StaticDraw& draw) {
    return mesh_draw(renderer, draw, textured_world_vertex, surface_pixel, textured_world_layout,
                     sizeof(TexturedWorldVertex), nullptr);
}
HRESULT draw_textured_world_indexed_multi28(NativeRenderer& renderer,
                                            const MultiTextureDraw& draw) {
    static const PixelProgram programs[] = {multi28_pixel, replace28_pixel, signed28_pixel};
    if (UINT(draw.secondary_blend) >= 3)
        return E_INVALIDARG;
    ObjectData object = object_data(draw);
    object.surface[1] = draw.use_diffuse_rgb ? 1 : 0;
    return mesh_draw(renderer, draw, multi28_vertex, programs[UINT(draw.secondary_blend)],
                     multi28_layout, sizeof(TexturedWorldMulti28), draw.secondary, &object);
}
HRESULT draw_textured_world_indexed_multi36(NativeRenderer& renderer,
                                            const MultiTextureDraw& draw) {
    static const PixelProgram programs[] = {multi36_pixel, replace36_pixel, signed36_pixel};
    if (UINT(draw.secondary_blend) >= 3)
        return E_INVALIDARG;
    ObjectData object = object_data(draw);
    object.surface[1] = draw.use_diffuse_rgb ? 1 : 0;
    HRESULT status = bind(renderer, multi36_vertex, programs[UINT(draw.secondary_blend)],
                          multi36_layout, draw.material.style, object, draw.material.diffuse,
                          draw.secondary, nullptr, draw.detail);
    return FAILED(status) ? status : indexed(renderer, draw.mesh, sizeof(TexturedWorldMulti36));
}
namespace {
HRESULT projected_shadow(NativeRenderer& renderer, const ShadowDraw& draw, VertexProgram program,
                         VertexLayout layout, UINT stride) {
    ObjectData object = object_data(draw);
    object.reflection = draw.projector;
    object.parameters[2] = draw.opacity;
    StaticDraw surface = draw;
    surface.material.diffuse = draw.shadow;
    return mesh_draw(renderer, surface, program, projected_shadow_pixel, layout, stride, nullptr,
                     &object);
}
} // namespace
HRESULT draw_projected_mesh_shadow(NativeRenderer& renderer, const ShadowDraw& draw) {
    return projected_shadow(renderer, draw, mesh_vertex, mesh_layout, sizeof(MeshVertex));
}
HRESULT draw_projected_world_shadow(NativeRenderer& renderer, const ShadowDraw& draw) {
    return projected_shadow(renderer, draw, world_vertex, world_layout, sizeof(WorldVertex));
}
HRESULT draw_projected_world_effect(NativeRenderer& renderer, const ShadowDraw& draw) {
    ObjectData object = object_data(draw);
    object.reflection = draw.projector;
    StaticDraw surface = draw;
    surface.material.diffuse = draw.shadow;
    return mesh_draw(renderer, surface, world_vertex, projected_effect_pixel, world_layout,
                     sizeof(WorldVertex), nullptr, &object);
}
HRESULT draw_projected_model_shadow(NativeRenderer& renderer, const ShadowDraw& draw) {
    return projected_shadow(renderer, draw, model_vertex, model_layout, sizeof(ModelVertex));
}
namespace {
HRESULT post(NativeRenderer& renderer, const GlowDraw& draw, PixelProgram pixel, float exponent) {
    if (!passes(renderer) || !draw.source || !draw.target || !draw.width || !draw.height)
        return E_INVALIDARG;
    ID3D11Resource *source_resource = nullptr, *target_resource = nullptr;
    draw.source->GetResource(&source_resource);
    draw.target->GetResource(&target_resource);
    bool conflict = source_resource == target_resource;
    release(source_resource);
    release(target_resource);
    if (conflict)
        return E_INVALIDARG;
    ID3D11RenderTargetView* previous = nullptr;
    ID3D11DepthStencilView* depth = nullptr;
    renderer.context->OMGetRenderTargets(1, &previous, &depth);
    D3D11_VIEWPORT viewport = {};
    UINT count = 1;
    renderer.context->RSGetViewports(&count, &viewport);
    ID3D11ShaderResourceView* empty[2] = {};
    renderer.context->PSSetShaderResources(0, 2, empty);
    renderer.context->OMSetRenderTargets(1, &draw.target, nullptr);
    D3D11_VIEWPORT target = {0, 0, float(draw.width), float(draw.height), 0, 1};
    renderer.context->RSSetViewports(1, &target);
    DrawStyle style;
    style.blend = draw.blend;
    style.depth = Depth::disabled;
    style.cull = Cull::none;
    style.sampling = Sampling::linear_clamp;
    ObjectData object = {};
    object.parameters[1] = exponent;
    object.parameters[3] = draw.alpha;
    object.uv[2] = draw.source_texel_size[0];
    object.uv[3] = draw.source_texel_size[1];
    HRESULT status =
        bind(renderer, fullscreen_vertex, pixel, ui_layout, style, object, draw.source, nullptr);
    if (SUCCEEDED(status)) {
        renderer.context->Draw(3, 0);
        probe_after_draw(renderer);
    }
    renderer.context->PSSetShaderResources(0, 2, empty);
    renderer.context->OMSetRenderTargets(1, &previous, depth);
    if (count)
        renderer.context->RSSetViewports(1, &viewport);
    release(previous);
    release(depth);
    return status;
}
} // namespace
HRESULT draw_glow(NativeRenderer& renderer, const GlowDraw& draw) {
    static const PixelProgram programs[] = {copy_pixel, eight_tap_pixel, gaussian_x_pixel,
                                            gaussian_y_pixel};
    if (UINT(draw.filter) >= 4)
        return E_INVALIDARG;
    return post(renderer, draw, programs[UINT(draw.filter)], 1);
}
HRESULT draw_gamma(NativeRenderer& renderer, ID3D11ShaderResourceView* source,
                   ID3D11RenderTargetView* target, float gamma) {
    if (!(gamma > 0) || gamma > 16)
        return E_INVALIDARG;
    GlowDraw draw;
    draw.source = source;
    draw.target = target;
    draw.width = renderer.width;
    draw.height = renderer.height;
    return post(renderer, draw, gamma_pixel, 1 / gamma);
}
} // namespace shaiya::graphics::native
