#include "graphics/native_renderer.h"
#include "graphics/native_render_passes.h"
#include "graphics/native_scene_ports.h"
#include <d3d11_4.h>

namespace shaiya::graphics::native {
namespace {
NativeRenderer main_renderer;

template <class T> void release(T*& object) {
    if (object != nullptr) {
        object->Release();
        object = nullptr;
    }
}

void release_targets(NativeRenderer& renderer) {
    release(renderer.gamma_view);
    release(renderer.gamma_texture);
    release(renderer.depth_target);
    release(renderer.depth_texture);
    release(renderer.color_target);
    release(renderer.backbuffer);
}

HRESULT create_targets(NativeRenderer& renderer) {
    HRESULT result = renderer.swapchain->GetBuffer(0, __uuidof(ID3D11Texture2D),
                                                   reinterpret_cast<void**>(&renderer.backbuffer));
    if (FAILED(result))
        return result;
    D3D11_TEXTURE2D_DESC surface = {};
    renderer.backbuffer->GetDesc(&surface);
    result = renderer.device->CreateRenderTargetView(renderer.backbuffer, nullptr,
                                                     &renderer.color_target);
    if (FAILED(result)) {
        release_targets(renderer);
        return result;
    }
    D3D11_TEXTURE2D_DESC depth = {};
    depth.Width = surface.Width;
    depth.Height = surface.Height;
    depth.MipLevels = 1;
    depth.ArraySize = 1;
    depth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depth.SampleDesc = surface.SampleDesc;
    depth.Usage = D3D11_USAGE_DEFAULT;
    depth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    result = renderer.device->CreateTexture2D(&depth, nullptr, &renderer.depth_texture);
    if (SUCCEEDED(result))
        result = renderer.device->CreateDepthStencilView(renderer.depth_texture, nullptr,
                                                         &renderer.depth_target);
    if (FAILED(result)) {
        release_targets(renderer);
        return result;
    }
    renderer.width = surface.Width;
    renderer.height = surface.Height;
    renderer.bind_main_target();
    return S_OK;
}

HRESULT create_device(NativeRenderer& renderer, D3D_DRIVER_TYPE driver) {
    const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_1, D3D_FEATURE_LEVEL_11_0,
                                        D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0};
    HRESULT result = D3D11CreateDevice(nullptr, driver, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                                       levels, 4, D3D11_SDK_VERSION, &renderer.device,
                                       &renderer.feature_level, &renderer.context);
    if (result == E_INVALIDARG)
        result = D3D11CreateDevice(nullptr, driver, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                                   levels + 1, 3, D3D11_SDK_VERSION, &renderer.device,
                                   &renderer.feature_level, &renderer.context);
    return result;
}
} // namespace

NativeRenderer* renderer() {
    return &main_renderer;
}

HRESULT NativeRenderer::initialize(HWND target_window, UINT target_width, UINT target_height,
                                   bool exclusive_fullscreen) {
    if (device != nullptr || target_window == nullptr || !IsWindow(target_window))
        return E_INVALIDARG;
    RECT client = {};
    if (!GetClientRect(target_window, &client))
        return HRESULT_FROM_WIN32(GetLastError());
    if (target_width == 0)
        target_width = client.right > 0 ? static_cast<UINT>(client.right) : 1;
    if (target_height == 0)
        target_height = client.bottom > 0 ? static_cast<UINT>(client.bottom) : 1;
    window = target_window;
    if (!render_lock_initialized) {
        if (!InitializeCriticalSectionAndSpinCount(&render_lock, 4000))
            return E_OUTOFMEMORY;
        render_lock_initialized = true;
    }
    device_removed = false;
    presented_frames = 0;
    HRESULT result = create_device(*this, D3D_DRIVER_TYPE_HARDWARE);
    if (FAILED(result)) {
        release(context);
        release(device);
        result = create_device(*this, D3D_DRIVER_TYPE_WARP);
    }
    if (FAILED(result)) {
        shutdown();
        return result;
    }
    ID3D11Multithread* threading = nullptr;
    if (SUCCEEDED(context->QueryInterface(__uuidof(ID3D11Multithread),
                                          reinterpret_cast<void**>(&threading)))) {
        threading->SetMultithreadProtected(TRUE);
        threading->Release();
    }
    IDXGIDevice* dxgi_device = nullptr;
    IDXGIFactory* factory = nullptr;
    result = device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&dxgi_device));
    if (SUCCEEDED(result))
        result = dxgi_device->GetAdapter(&adapter);
    if (SUCCEEDED(result))
        result = adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&factory));
    release(dxgi_device);
    if (SUCCEEDED(result)) {
        DXGI_SWAP_CHAIN_DESC description = {};
        description.BufferDesc.Width = target_width;
        description.BufferDesc.Height = target_height;
        description.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        description.SampleDesc.Count = 1;
        description.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        description.BufferCount = 2;
        description.OutputWindow = window;
        description.Windowed = TRUE;
        description.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
        description.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
        result = factory->CreateSwapChain(device, &description, &swapchain);
        if (SUCCEEDED(result))
            factory->MakeWindowAssociation(window,
                                           DXGI_MWA_NO_ALT_ENTER | DXGI_MWA_NO_WINDOW_CHANGES);
    }
    release(factory);
    if (SUCCEEDED(result) && exclusive_fullscreen) {
        result = swapchain->SetFullscreenState(TRUE, nullptr);
        fullscreen = SUCCEEDED(result);
    }
    if (SUCCEEDED(result))
        result = create_targets(*this);
    if (SUCCEEDED(result))
        result = passes_initialize(*this);
    if (FAILED(result))
        shutdown();
    return result;
}

HRESULT NativeRenderer::resize(UINT target_width, UINT target_height) {
    FrameRenderScope serialization(*this);
    if (swapchain == nullptr || context == nullptr)
        return E_UNEXPECTED;
    // A minimized HWND reports zero client dimensions. Keep the render surface
    // alive so background scene and camera updates continue at their normal pace.
    if (target_width == 0 || target_height == 0 ||
        (target_width == width && target_height == height))
        return S_OK;
    context->ClearState();
    passes_reset_bindings(*this);
    context->Flush();
    release_targets(*this);
    const HRESULT result =
        swapchain->ResizeBuffers(2, target_width, target_height, DXGI_FORMAT_B8G8R8A8_UNORM,
                                 DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
    const HRESULT targets = create_targets(*this);
    if (FAILED(result))
        return result;
    return FAILED(targets) ? targets : begin_scene(*this, scene);
}

void NativeRenderer::bind_main_target() {
    if (context == nullptr || color_target == nullptr)
        return;
    context->OMSetRenderTargets(1, &color_target, depth_target);
    const D3D11_VIEWPORT viewport = {0, 0, static_cast<float>(width), static_cast<float>(height),
                                     0, 1};
    context->RSSetViewports(1, &viewport);
}

void NativeRenderer::begin_frame(const float clear_color[4], float clear_depth) {
    if (context == nullptr || color_target == nullptr)
        return;
    const DWORD thread = GetCurrentThreadId();
    if (render_lock_initialized &&
        DWORD(InterlockedCompareExchange(&automatic_frame_owner, 0, 0)) != thread) {
        EnterCriticalSection(&render_lock);
        InterlockedExchange(&automatic_frame_owner, LONG(thread));
    }
    bind_main_target();
    if (context == nullptr || color_target == nullptr)
        return;
    if (clear_color != nullptr)
        context->ClearRenderTargetView(color_target, clear_color);
    if (depth_target != nullptr)
        context->ClearDepthStencilView(depth_target, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
                                       clear_depth, 0);
}

HRESULT NativeRenderer::present() {
    FrameRenderScope serialization(*this);
    struct Finish {
        NativeRenderer& renderer;
        ~Finish() {
            renderer.finish_frame();
        }
    } finish{*this};
    if (swapchain == nullptr)
        return E_UNEXPECTED;
    if (gamma != 1.0f) {
        if (gamma_texture == nullptr) {
            D3D11_TEXTURE2D_DESC description = {};
            backbuffer->GetDesc(&description);
            description.Usage = D3D11_USAGE_DEFAULT;
            description.BindFlags = D3D11_BIND_SHADER_RESOURCE;
            description.CPUAccessFlags = 0;
            description.MiscFlags = 0;
            HRESULT result = device->CreateTexture2D(&description, nullptr, &gamma_texture);
            if (SUCCEEDED(result))
                result = device->CreateShaderResourceView(gamma_texture, nullptr, &gamma_view);
            if (FAILED(result)) {
                release(gamma_view);
                release(gamma_texture);
                return result;
            }
        }
        context->OMSetRenderTargets(0, nullptr, nullptr);
        context->CopyResource(gamma_texture, backbuffer);
        const HRESULT result = draw_gamma(*this, gamma_view, color_target, gamma);
        ID3D11ShaderResourceView* empty = nullptr;
        context->PSSetShaderResources(0, 1, &empty);
        if (FAILED(result))
            return result;
    }
    const HRESULT result = swapchain->Present(0, 0);
    if (result == DXGI_ERROR_DEVICE_REMOVED || result == DXGI_ERROR_DEVICE_RESET ||
        result == DXGI_ERROR_DEVICE_HUNG)
        device_removed = true;
    if (SUCCEEDED(result))
        InterlockedIncrement(&presented_frames);
    return result;
}

void NativeRenderer::shutdown() {
    const bool serialization = enter_render_scope();
    finish_frame();
    release_scene_textures();
    set_ui_image(nullptr);
    if (context != nullptr)
        context->ClearState();
    passes_shutdown(*this);
    release_targets(*this);
    if (swapchain != nullptr)
        swapchain->SetFullscreenState(FALSE, nullptr);
    release(swapchain);
    release(adapter);
    if (context != nullptr)
        context->Flush();
    release(context);
    release(device);
    window = nullptr;
    width = height = 0;
    fullscreen = false;
    device_removed = false;
    if (serialization)
        leave_render_scope();
    if (render_lock_initialized) {
        DeleteCriticalSection(&render_lock);
        render_lock_initialized = false;
    }
}

bool NativeRenderer::enter_render_scope() {
    if (!render_lock_initialized)
        return false;
    EnterCriticalSection(&render_lock);
    return true;
}
void NativeRenderer::leave_render_scope() {
    LeaveCriticalSection(&render_lock);
}
void NativeRenderer::finish_frame() {
    if (render_lock_initialized &&
        DWORD(InterlockedCompareExchange(&automatic_frame_owner, 0, 0)) == GetCurrentThreadId()) {
        InterlockedExchange(&automatic_frame_owner, 0);
        LeaveCriticalSection(&render_lock);
    }
}
} // namespace shaiya::graphics::native

extern "C" HRESULT __cdecl native_renderer_resize(shaiya::graphics::native::NativeRenderer* current,
                                                  UINT width, UINT height) {
    return current != nullptr ? current->resize(width, height) : E_POINTER;
}
