// Exercise the radial-overlay submission boundary through the real D3D11 pass.
#include "graphics/native_renderer.h"
#include "graphics/native_scene_ports.h"
#include <windows.h>

using namespace shaiya::graphics::native;

namespace {
NativeRenderer fixture_renderer;
SceneDrawContext fixture_scene;
ID3D11Texture2D* staging = nullptr;

void require(bool passed, UINT stage) {
    if (!passed)
        ExitProcess(stage);
}

void clear() {
    const float background[] = {64.0f / 255, 128.0f / 255, 192.0f / 255, 1};
    fixture_renderer.context->ClearRenderTargetView(fixture_renderer.color_target, background);
}

void pixel(UINT x, UINT y, UINT red, UINT green, UINT blue, UINT stage) {
    fixture_renderer.context->CopyResource(staging, fixture_renderer.backbuffer);
    D3D11_MAPPED_SUBRESOURCE mapped = {};
    require(SUCCEEDED(fixture_renderer.context->Map(staging, 0, D3D11_MAP_READ, 0, &mapped)), stage);
    const auto* value = static_cast<const unsigned char*>(mapped.pData) +
                        y * mapped.RowPitch + x * 4;
    const int errors[] = {int(value[2]) - int(red), int(value[1]) - int(green),
                          int(value[0]) - int(blue)};
    fixture_renderer.context->Unmap(staging, 0);
    for (int error : errors)
        require(error >= -2 && error <= 2, stage);
}

ID3D11ShaderResourceView* image(UINT rgba) {
    D3D11_TEXTURE2D_DESC description = {};
    description.Width = description.Height = description.MipLevels = description.ArraySize = 1;
    description.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    description.SampleDesc.Count = 1;
    description.Usage = D3D11_USAGE_IMMUTABLE;
    description.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    D3D11_SUBRESOURCE_DATA initial = {&rgba, 4, 4};
    ID3D11Texture2D* texture = nullptr;
    require(SUCCEEDED(fixture_renderer.device->CreateTexture2D(&description, &initial, &texture)), 10);
    ID3D11ShaderResourceView* view = nullptr;
    require(SUCCEEDED(fixture_renderer.device->CreateShaderResourceView(texture, nullptr, &view)), 11);
    texture->Release();
    return view;
}

void uv_payload(UiVertex& vertex, UINT bits) {
    // Original radial vertices do not initialize these fields. Include quiet
    // and signaling NaN bit patterns without evaluating them as host floats.
    const auto* bytes = reinterpret_cast<const unsigned char*>(&bits);
    auto* uv = reinterpret_cast<unsigned char*>(&vertex.u);
    for (UINT byte = 0; byte < sizeof(bits); ++byte)
        uv[byte] = uv[byte + sizeof(bits)] = bytes[byte];
}
} // namespace

namespace shaiya::graphics::native {
SceneDrawContext& scene_draw_context() {
    return fixture_scene;
}
// These callbacks are unrelated to the tested UI routes.
void set_scene_diffuse(Texture2D*) {
    ExitProcess(90);
}
} // namespace shaiya::graphics::native

extern "C" {
NativeRenderer* dat_02209400 = &fixture_renderer;
HRESULT __attribute__((stdcall)) native_ui_triangle(const UiVertex*);
HRESULT __attribute__((stdcall)) native_ui_quad(const UiVertex*);
void __attribute__((stdcall)) native_scene_depth_test(UINT) {
    ExitProcess(90);
}
}

namespace {
void radial(UINT diameter, UINT segments, UINT uv_bits) {
    // Both recovered icon sizes submit independent triangles around a square.
    // Check complete and partially elapsed overlays without reconstructing UI
    // timers or depending on a live game session.
    const float radius = float(diameter) / 2;
    const float edge[][2] = {{0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1},
                             {1, 1}, {1, 0}, {1, -1}, {0, -1}};
    for (UINT segment = 0; segment < segments; ++segment) {
        UiVertex triangle[] = {
            {32, 32, 1, 1, 0xa0ff0000, 0, 0},
            {32 + radius * edge[segment][0], 32 + radius * edge[segment][1],
             1, 1, 0xa0ff0000, 0, 0},
            {32 + radius * edge[segment + 1][0], 32 + radius * edge[segment + 1][1],
             1, 1, 0xa0ff0000, 0, 0}};
        for (auto& vertex : triangle)
            uv_payload(vertex, uv_bits);
        auto* selected = fixture_renderer.ui_image;
        require(SUCCEEDED(native_ui_triangle(triangle)), 20);
        require(fixture_renderer.ui_image == selected, 21);
    }
}

void test_overlay(ID3D11ShaderResourceView* selected, UINT uv_bits) {
    fixture_renderer.set_ui_image(selected);
    const UINT diameters[] = {16, 32};
    for (UINT diameter : diameters) {
        const UINT radius = diameter / 2;
        clear();
        radial(diameter, 8, uv_bits);
        // Original stage 0 modulates DIFFUSE with CURRENT, which initially
        // contains diffuse too: effective alpha is (160/255)^2 before blending.
        pixel(32 - radius + 2, 32 - radius + 3, 139, 78, 116, 30);
        pixel(32 + radius - 3, 32 + radius - 2, 139, 78, 116, 31);
        pixel(32 - radius - 2, 32, 64, 128, 192, 32);
        clear();
        radial(diameter, 4, uv_bits);
        pixel(32 - radius / 2, 30, 139, 78, 116, 33);
        pixel(32 + radius / 2, 30, 64, 128, 192, 34);
    }
}
} // namespace

extern "C" void cooldown_overlay_test_entry() {
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
    require(SUCCEEDED(fixture_renderer.device->CreateRenderTargetView(fixture_renderer.backbuffer,
                                         nullptr, &fixture_renderer.color_target)), 3);
    fixture_renderer.context->OMSetRenderTargets(1, &fixture_renderer.color_target, nullptr);
    D3D11_VIEWPORT viewport = {0, 0, 64, 64, 0, 1};
    fixture_renderer.context->RSSetViewports(1, &viewport);
    description.Usage = D3D11_USAGE_STAGING;
    description.BindFlags = 0;
    description.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    require(SUCCEEDED(fixture_renderer.device->CreateTexture2D(&description, nullptr, &staging)), 4);
    require(SUCCEEDED(passes_initialize(fixture_renderer)), 5);

    auto* transparent = image(0x00000000);
    auto* green = image(0xff00ff00);
    // Stale transparent/colored images must neither hide nor recolor the timer.
    const UINT uv_patterns[] = {0, 0x47800000, 0xc7800000, 0x7fc00000, 0x7f800001};
    for (UINT bits : uv_patterns) {
        test_overlay(transparent, bits);
        test_overlay(green, bits);
        test_overlay(nullptr, bits);
    }

    // A subsequent icon still uses the image selected before the solid timer.
    fixture_renderer.set_ui_image(green);
    clear();
    radial(32, 8, 0x7fc00000);
    const UiVertex quad[] = {{16, 16, 1, 1, 0xffffffff, 0, 0},
                              {48, 16, 1, 1, 0xffffffff, 1, 0},
                              {48, 48, 1, 1, 0xffffffff, 1, 1},
                              {16, 48, 1, 1, 0xffffffff, 0, 1}};
    require(SUCCEEDED(native_ui_quad(quad)), 40);
    pixel(30, 30, 0, 255, 0, 41);
    require(fixture_renderer.ui_image == green, 42);
    require(native_ui_triangle(nullptr) == E_INVALIDARG, 43);
    require(fixture_renderer.ui_image == green, 44);
    dat_02209400 = nullptr;
    require(native_ui_triangle(quad) == E_UNEXPECTED, 45);
    dat_02209400 = &fixture_renderer;

    fixture_renderer.set_ui_image(nullptr);
    transparent->Release();
    green->Release();
    fixture_renderer.context->ClearState();
    passes_shutdown(fixture_renderer);
    staging->Release();
    fixture_renderer.color_target->Release();
    fixture_renderer.backbuffer->Release();
    fixture_renderer.context->Release();
    fixture_renderer.device->Release();
    const char message[] =
        "Cooldown overlay: solid radial triangles, alpha, icon sizes and image selection passed.\n";
    DWORD written;
    WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), message, sizeof(message) - 1, &written, nullptr);
    ExitProcess(0);
}
