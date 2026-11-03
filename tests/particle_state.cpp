// Offscreen D3D11 regressions for shared effect and actor material state.
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

void pixel(UINT expected_red, UINT expected_blue, UINT stage, UINT expected_green = 0) {
    fixture_renderer.context->CopyResource(staging, fixture_renderer.backbuffer);
    D3D11_MAPPED_SUBRESOURCE mapped = {};
    require(SUCCEEDED(fixture_renderer.context->Map(staging, 0, D3D11_MAP_READ, 0, &mapped)), stage);
    const auto* value = static_cast<const unsigned char*>(mapped.pData) + 32 * mapped.RowPitch + 128;
    const int red_error = int(value[2]) - int(expected_red);
    const int green_error = int(value[1]) - int(expected_green);
    const int blue_error = int(value[0]) - int(expected_blue);
    fixture_renderer.context->Unmap(staging, 0);
    require(red_error >= -2 && red_error <= 2 && green_error >= -2 && green_error <= 2 &&
                blue_error >= -2 && blue_error <= 2,
            stage);
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
void __attribute__((stdcall)) native_scene_lighting(UINT);
void __attribute__((stdcall)) native_scene_tint(UINT);
void __attribute__((thiscall)) FUN_00548090(void*, UINT);
HRESULT __attribute__((thiscall)) FUN_00551960(void*);
HRESULT __attribute__((thiscall)) FUN_005519c0(void*);
HRESULT __attribute__((thiscall)) FUN_00556490(void*);
void __attribute__((thiscall)) FUN_00548880(void*);
HRESULT __attribute__((thiscall)) FUN_00581b30(void*);
HRESULT __attribute__((thiscall)) FUN_00581d70(void*, void*);
extern unsigned char dat_02209408[];
void __cdecl particle_test_ground_item_complete();
}

// Execute the exact production completion boundary after each ground-item
// draw. Calling the existing helper directly would miss a removed caller hook.
__asm__(".text\n.intel_syntax noprefix\n"
        ".globl _particle_test_ground_item_complete\n"
        "_particle_test_ground_item_complete:\n"
#include "graphics/native_ground_item_complete.inc"
        "ret\n.att_syntax prefix\n");

namespace {
void test_ground_item_blink_before_actors() {
    const ModelVertex model[] = {{{-1, 1, .5f}, {0, 1, 0}, {0, 0}},
                                 {{1, 1, .5f}, {0, 1, 0}, {1, 0}},
                                 {{1, -1, .5f}, {0, 1, 0}, {1, 1}},
                                 {{-1, -1, .5f}, {0, 1, 0}, {0, 1}}};
    const SkinVertex skin[] = {{{-1, 1, .5f}, 1, {0, 0, 0, 0}, {0, 1, 0}, {0, 0}},
                               {{1, 1, .5f}, 1, {0, 0, 0, 0}, {0, 1, 0}, {1, 0}},
                               {{1, -1, .5f}, 1, {0, 0, 0, 0}, {0, 1, 0}, {1, 1}},
                               {{-1, -1, .5f}, 1, {0, 0, 0, 0}, {0, 1, 0}, {0, 1}}};
    const uint16_t order[] = {0, 1, 2, 0, 2, 3};
    Buffer *model_vertices = nullptr, *skin_vertices = nullptr, *indices = nullptr;
    require(SUCCEEDED(create_buffer(fixture_renderer, BufferKind::vertices, model, sizeof(model),
                                     sizeof(ModelVertex), DXGI_FORMAT_UNKNOWN, &model_vertices)), 60);
    require(SUCCEEDED(create_buffer(fixture_renderer, BufferKind::vertices, skin, sizeof(skin),
                                     sizeof(SkinVertex), DXGI_FORMAT_UNKNOWN, &skin_vertices)), 61);
    require(SUCCEEDED(create_buffer(fixture_renderer, BufferKind::indices, order, sizeof(order),
                                     sizeof(uint16_t), DXGI_FORMAT_R16_UINT, &indices)), 62);
    UINT item[0x10 / 4] = {reinterpret_cast<UINT>(model_vertices), reinterpret_cast<UINT>(indices),
                          0, 2};
    UINT npc[0x24 / 4] = {}, skinned[0x24 / 4] = {};
    npc[1] = skinned[1] = reinterpret_cast<UINT>(indices);
    npc[0x20 / 4] = skinned[0x20 / 4] = 2;
    skinned[0] = reinterpret_cast<UINT>(skin_vertices);
    *reinterpret_cast<Buffer**>(dat_02209408 + 0x358) = model_vertices;

    Scene scene;
    scene.view = scene.view_projection = identity();
    scene.ambient = {.8f, .6f, .4f, 1};
    require(SUCCEEDED(begin_scene(fixture_renderer, scene)), 63);
    auto& state = scene_draw_context();
    state.world = identity();
    state.material = Material();
    state.material.style = {Blend::opaque, Depth::disabled, Cull::none, Sampling::linear_wrap};
    state.projected_shadow = false;
    set_scene_shadow_map(nullptr);
    auto* white = texture(0xffffffff);
    set_scene_diffuse(white);
    native_scene_depth_test(0);
    native_scene_blending(0);
    native_scene_lighting(1);
    FUN_00548090(nullptr, 0);
    clear();
    require(SUCCEEDED(FUN_005519c0(npc)), 64);
    pixel(204, 102, 65, 153); // Baseline lit NPC before any item pulse.

    const AffineBone3x4 bone = {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}}};
    require(SUCCEEDED(set_actor_palette(&bone, 1)), 66);
    static const UINT pulses[] = {77, 166, 255, 77};
    for (UINT pulse : pulses) {
        // Recovered 428470 draws the item unlit using an opaque grayscale
        // texture factor, then restores lighting and stage-0 diffuse color.
        native_scene_lighting(0);
        native_scene_tint(0xff000000 | pulse << 16 | pulse << 8 | pulse);
        clear();
        require(SUCCEEDED(FUN_00556490(item)), 67);
        pixel(pulse, pulse, 68, pulse); // The item must continue blinking.
        particle_test_ground_item_complete();
        require(state.lit, 69);

        FUN_00548090(nullptr, 0);
        clear();
        require(SUCCEEDED(FUN_005519c0(npc)), 70);
        pixel(204, 102, 71, 153);
        clear();
        require(SUCCEEDED(FUN_00556490(item)), 72); // Same static path, now lit.
        pixel(204, 102, 73, 153);
        FUN_00548090(nullptr, 1);
        clear();
        require(SUCCEEDED(FUN_00551960(skinned)), 74);
        pixel(204, 102, 75, 153);
    }
    set_scene_diffuse(nullptr);
    white->release();
    *reinterpret_cast<Buffer**>(dat_02209408 + 0x358) = nullptr;
    model_vertices->release();
    skin_vertices->release();
    indices->release();
}
} // namespace

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
    test_ground_item_blink_before_actors();
    set_scene_diffuse(nullptr);
    set_scene_shadow_map(nullptr);
    blue->release();
    vertices->release();
    const char message[] =
        "Effect state: particle/cape/shadow alpha and ground-item to actor colors passed.\n";
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
void __attribute__((thiscall)) FUN_00541bb0(void*, int) { ExitProcess(90); }
unsigned long long __cdecl x87_to_integer_005cd414(long double) { ExitProcess(90); }
}
