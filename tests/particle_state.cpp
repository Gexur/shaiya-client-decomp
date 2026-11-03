// Offscreen D3D11 regression for the shared SEFF -> EFT material state.
#include "graphics/native_renderer.h"
#include "graphics/native_scene_ports.h"
#include <windows.h>

using namespace shaiya::graphics::native;

namespace {
NativeRenderer fixture_renderer;
ID3D11Texture2D* staging = nullptr;
UINT checks = 0;

void require(bool passed, UINT stage) {
    if (!passed)
        ExitProcess(stage);
    ++checks;
}

Matrix identity() {
    return {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
}

void clear() {
    const float background[] = {64.0f / 255, 0, 0, 1};
    fixture_renderer.context->ClearRenderTargetView(fixture_renderer.color_target, background);
}

void pixel(UINT expected_red, UINT expected_blue, UINT stage) {
    fixture_renderer.context->CopyResource(staging, fixture_renderer.backbuffer);
    D3D11_MAPPED_SUBRESOURCE mapped = {};
    require(SUCCEEDED(fixture_renderer.context->Map(staging, 0, D3D11_MAP_READ, 0, &mapped)), stage);
    const auto* value = static_cast<const unsigned char*>(mapped.pData) + 32 * mapped.RowPitch + 128;
    const int red_error = int(value[2]) - int(expected_red);
    const int blue_error = int(value[0]) - int(expected_blue);
    fixture_renderer.context->Unmap(staging, 0);
    require(red_error >= -2 && red_error <= 2 && blue_error >= -2 && blue_error <= 2, stage);
}

Texture2D* texture(UINT rgba) {
    TextureMip mip = {&rgba, 4, 4};
    Texture2D* output = nullptr;
    require(SUCCEEDED(create_texture(fixture_renderer, 1, 1, DXGI_FORMAT_R8G8B8A8_UNORM, &mip, 1,
                                      D3D11_BIND_SHADER_RESOURCE, &output)), 10);
    return output;
}
} // namespace

namespace shaiya::graphics::native {
NativeRenderer* renderer() {
    return &fixture_renderer;
}
} // namespace shaiya::graphics::native

extern "C" {
NativeRenderer* dat_02209400 = &fixture_renderer;
void __attribute__((stdcall)) native_particle_material(void*);
void __cdecl native_particle_complete();
HRESULT __attribute__((stdcall)) native_particle_quad(Buffer*);
HRESULT __attribute__((stdcall)) native_effect_world_strip(UINT, const WorldVertex*);
void __attribute__((stdcall)) native_actor_effect_blend(void*);
void __attribute__((stdcall)) native_scene_depth_test(UINT);
void __attribute__((stdcall)) native_scene_blending(UINT);
void __attribute__((thiscall)) FUN_00548880(void*);
HRESULT __attribute__((thiscall)) FUN_00581b30(void*);
HRESULT __attribute__((thiscall)) FUN_00581d70(void*, void*);
}

extern "C" void particle_state_test_entry() {
    // WARP exercises the production GPU shaders without opening a window or
    // requiring a particular graphics adapter.
    require(SUCCEEDED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 0,
                                        D3D11_SDK_VERSION, &fixture_renderer.device,
                                        &fixture_renderer.feature_level, &fixture_renderer.context)), 1);
    fixture_renderer.width = fixture_renderer.height = 64;
    D3D11_TEXTURE2D_DESC description = {};
    description.Width = description.Height = 64;
    description.MipLevels = description.ArraySize = description.SampleDesc.Count = 1;
    description.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    description.BindFlags = D3D11_BIND_RENDER_TARGET;
    require(SUCCEEDED(fixture_renderer.device->CreateTexture2D(&description, nullptr,
                                                       &fixture_renderer.backbuffer)), 2);
    require(SUCCEEDED(fixture_renderer.device->CreateRenderTargetView(fixture_renderer.backbuffer, nullptr,
                                                              &fixture_renderer.color_target)), 3);
    fixture_renderer.context->OMSetRenderTargets(1, &fixture_renderer.color_target, nullptr);
    D3D11_VIEWPORT viewport = {0, 0, 64, 64, 0, 1};
    fixture_renderer.context->RSSetViewports(1, &viewport);
    description.Usage = D3D11_USAGE_STAGING;
    description.BindFlags = 0;
    description.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    require(SUCCEEDED(fixture_renderer.device->CreateTexture2D(&description, nullptr, &staging)), 4);
    require(SUCCEEDED(passes_initialize(fixture_renderer)), 5);
    Scene scene;
    scene.view = scene.view_projection = identity();
    require(SUCCEEDED(begin_scene(fixture_renderer, scene)), 6);
    auto& state = scene_draw_context();
    state.world = identity();
    state.material.style = {Blend::opaque, Depth::disabled, Cull::none, Sampling::linear_wrap};
    native_scene_depth_test(0);

    const WorldVertex quad[] = {{{-1, 1, .5f}, 0x80ffffff, {0, 0}},
                                {{1, 1, .5f}, 0x80ffffff, {1, 0}},
                                {{1, -1, .5f}, 0x80ffffff, {1, 1}},
                                {{-1, -1, .5f}, 0x80ffffff, {0, 1}}};
    Buffer* vertices = nullptr;
    require(SUCCEEDED(create_buffer(fixture_renderer, BufferKind::vertices, quad, sizeof(quad),
                                     sizeof(WorldVertex), DXGI_FORMAT_UNKNOWN, &vertices)), 7);
    UINT particle[0x128 / 4] = {};
    for (UINT mode = 0; mode < 4; ++mode) {
        for (UINT opaque = 0; opaque < 2; ++opaque) {
            const UINT alpha = opaque ? mode < 2 ? 0x80000000u : 0xff000000u : 0;
            auto* image = texture(0x00ff0000u | alpha);
            particle[2] = mode;
            particle[0x124 / 4] = reinterpret_cast<UINT>(image);
            native_particle_material(particle);
            state.material.style.tint = {1, 1, 1, 1};
            clear();
            require(SUCCEEDED(native_particle_quad(vertices)), 20);
            const UINT red = opaque && (mode == 1 || mode == 2) ? 32 : 64;
            pixel(red, opaque ? 128 : 0, 30 + mode * 2 + opaque);
            native_particle_complete();
            image->release();
        }
    }

    // Both SEFF completion and the actor shadow receiver leave blending
    // enabled. A following EFT strip changes the factors but relies on that
    // shared enable. Selection draws the shadow receiver before weapon EFT.
    auto* blue = texture(0xffff0000);
    particle[2] = 0;
    particle[0x124 / 4] = reinterpret_cast<UINT>(blue);
    UINT effect[0xd0 / 4] = {};
    effect[0xc8 / 4] = 4; // Authored SRCALPHA catalog choice.
    effect[0xcc / 4] = 1; // Authored ONE catalog choice.
    WorldVertex strip[] = {quad[0], quad[1], quad[3], quad[2]};
    UINT shadow[0x1414 / 4] = {};
    shadow[0x1410 / 4] = reinterpret_cast<UINT>(blue);
    UINT cloth[0x74 / 4] = {};
    for (UINT boundary = 0; boundary < 4; ++boundary) {
        native_scene_blending(0);
        if (boundary == 0) {
            native_particle_material(particle);
            native_particle_complete();
        } else if (boundary == 1) {
            FUN_00548880(shadow);
        } else {
            // Original cape setup changes shared state before checking whether
            // its vertex buffer lock succeeded. Missing geometry retains that
            // state change too; no fabricated mesh or successful lock is used.
            const HRESULT result = boundary == 2 ? FUN_00581b30(cloth)
                                                  : FUN_00581d70(cloth, nullptr);
            require(result == E_INVALIDARG && state.material.style.alpha_cutoff > 0, 56);
        }
        require(state.material.style.source_blend == D3D11_BLEND_SRC_ALPHA &&
                    state.material.style.destination_blend == D3D11_BLEND_INV_SRC_ALPHA, 50);
        native_actor_effect_blend(effect);
        require(state.material.style.source_blend == D3D11_BLEND_SRC_ALPHA &&
                    state.material.style.destination_blend == D3D11_BLEND_ONE, 57);
        for (auto& vertex : strip)
            vertex.argb = 0x000064ff;
        clear();
        require(SUCCEEDED(native_effect_world_strip(2, strip)), 51);
        pixel(64, 0, 52); // Alpha-zero texels must leave the background intact.
        for (auto& vertex : strip)
            vertex.argb = 0x800064ff;
        clear();
        require(SUCCEEDED(native_effect_world_strip(2, strip)), 53);
        pixel(64, 128, 54); // Partial alpha retains the authored additive glow.
        native_scene_depth_test(1);
        require(state.material.style.depth == (boundary == 0 ? Depth::write : Depth::read), 55);
    }
    set_scene_diffuse(nullptr);
    set_scene_shadow_map(nullptr);
    blue->release();
    vertices->release();
    const char message[] = "Effect state: particle, shadow and cape transitions to EFT alpha pixels passed.\n";
    DWORD written;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), message, sizeof(message) - 1, &written, nullptr);
    ExitProcess(0);
}

// Unused engine callbacks are explicit traps. This fixture executes production
// particles, controller state, resource ownership and render passes only.
extern "C" {
unsigned char dat_02209408[4096] = {}, dat_0220f708[75000] = {}, dat_0220df28[4096] = {};
unsigned char dat_0071d0f9 = 0;
UINT dat_0085d3a8 = 0;
void* dat_007191d4 = nullptr;
float dat_007085b4 = 0, DAT_00719874 = 0, DAT_00719878 = 0, dat_0070baa0 = 0, dat_0070baa4 = 0;
float dat_0220aa50[16] = {}, dat_0220aa90[16] = {}, dat_0220bee8[16] = {};
Buffer* dat_02221c30 = nullptr;
void __attribute__((thiscall)) FUN_005426e0(void*, const float*, const float*, const float*) { ExitProcess(90); }
void __attribute__((thiscall)) FUN_00542670(void*, const float*) { ExitProcess(90); }
void __attribute__((thiscall)) FUN_00542440(void*, float, float, float) { ExitProcess(90); }
void __attribute__((thiscall)) FUN_00559890(void*) { ExitProcess(90); }
void __attribute__((thiscall)) FUN_0053dc20(void*) { ExitProcess(90); }
void __attribute__((thiscall)) FUN_0055b1f0(void*) { ExitProcess(90); }
void __attribute__((thiscall)) FUN_0055b650(void*) { ExitProcess(90); }
HRESULT __attribute__((thiscall)) FUN_00556490(void*) { ExitProcess(90); }
void __attribute__((thiscall)) FUN_00541bb0(void*, int) { ExitProcess(90); }
unsigned long long __cdecl x87_to_integer_005cd414(long double) { ExitProcess(90); }
}
