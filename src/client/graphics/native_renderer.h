#pragma once

#include <d3d11.h>
#include <dxgi.h>
#include "graphics/native_render_passes.h"

namespace shaiya::graphics::native {

// The game renderer owns the D3D11 device and presentation surface. Scene and UI
// passes bind explicit native shaders, buffers, resources and immutable states.
struct NativeRenderer {
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    IDXGISwapChain* swapchain = nullptr;
    IDXGIAdapter* adapter = nullptr;
    ID3D11Texture2D* backbuffer = nullptr;
    ID3D11Texture2D* depth_texture = nullptr;
    ID3D11RenderTargetView* color_target = nullptr;
    ID3D11DepthStencilView* depth_target = nullptr;
    ID3D11Texture2D* gamma_texture = nullptr;
    ID3D11ShaderResourceView* gamma_view = nullptr;
    ID3D11ShaderResourceView* ui_image = nullptr;
    void* pipeline_data = nullptr;
    HWND window = nullptr;
    UINT width = 0;
    UINT height = 0;
    D3D_FEATURE_LEVEL feature_level = D3D_FEATURE_LEVEL_9_1;
    bool fullscreen = false;
    bool device_removed = false;
    CRITICAL_SECTION render_lock;
    bool render_lock_initialized = false;
    volatile LONG automatic_frame_owner = 0;
    float gamma = 1.0f;
    volatile LONG presented_frames = 0;
    Scene scene;
    D3D11_RECT ui_scissor = {};
    bool ui_scissor_enabled = false;
    Matrix projection;

    HRESULT initialize(HWND target_window, UINT target_width, UINT target_height,
                       bool exclusive_fullscreen = false);
    HRESULT resize(UINT target_width, UINT target_height);
    void begin_frame(const float clear_color[4], float clear_depth = 1.0f);
    HRESULT present();
    void bind_main_target();
    void shutdown();
    bool enter_render_scope();
    void leave_render_scope();
    void finish_frame();
    void set_ui_image(ID3D11ShaderResourceView* image) {
        if (image == ui_image)
            return;
        if (image)
            image->AddRef();
        if (ui_image)
            ui_image->Release();
        ui_image = image;
    }
};

struct FrameRenderScope {
    NativeRenderer& renderer;
    bool locked;
    explicit FrameRenderScope(NativeRenderer& value)
        : renderer(value), locked(value.enter_render_scope()) {}
    ~FrameRenderScope() {
        if (locked)
            renderer.leave_render_scope();
    }
    FrameRenderScope(const FrameRenderScope&) = delete;
    FrameRenderScope& operator=(const FrameRenderScope&) = delete;
};

struct UiImageScope {
    NativeRenderer& renderer;
    ID3D11ShaderResourceView* previous;
    explicit UiImageScope(NativeRenderer& value) : renderer(value), previous(value.ui_image) {
        if (previous)
            previous->AddRef();
    }
    ~UiImageScope() {
        renderer.set_ui_image(previous);
        if (previous)
            previous->Release();
    }
};

NativeRenderer* renderer();

} // namespace shaiya::graphics::native

// These whole-operation entry points also serve recovered MSVC-SEH units;
// explicit C linkage keeps their ABI independent of the C++ object mangler.
extern "C" HRESULT __cdecl native_renderer_resize(shaiya::graphics::native::NativeRenderer*,
                                                  UINT width, UINT height);
