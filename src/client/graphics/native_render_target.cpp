#include "graphics/native_render_target.h"
#include <new>

namespace shaiya::graphics::native {
namespace {
template <class T> void release(T*& object) {
    if (object != nullptr) {
        object->Release();
        object = nullptr;
    }
}
void release_saved_targets(TargetScope& scope) {
    for (auto*& target : scope.previous_color)
        release(target);
    release(scope.previous_depth);
}
void restore_draw_state(TargetScope& scope) {
    auto restore = scope.restore_draw_state;
    void* saved = scope.saved_draw_state;
    scope.restore_draw_state = nullptr;
    scope.saved_draw_state = nullptr;
    if (restore != nullptr)
        restore(saved);
}
} // namespace

HRESULT create_target_scope(NativeRenderer& renderer, UINT width, UINT height, bool with_depth,
                            TargetScope** output) {
    if (output == nullptr)
        return E_POINTER;
    *output = nullptr;
    if (renderer.device == nullptr || width == 0 || height == 0)
        return E_INVALIDARG;
    void* storage = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(TargetScope));
    if (storage == nullptr)
        return E_OUTOFMEMORY;
    auto* scope = new (storage) TargetScope();
    scope->renderer = &renderer;
    scope->width = width;
    scope->height = height;
    if (with_depth) {
        const HRESULT result = create_depth_texture(renderer, width, height, &scope->depth);
        if (FAILED(result)) {
            release_target_scope(scope);
            return result;
        }
    }
    *output = scope;
    return S_OK;
}

void release_target_scope(TargetScope* scope) {
    if (scope == nullptr)
        return;
    if (scope->active)
        end_target(*scope);
    restore_draw_state(*scope);
    release_saved_targets(*scope);
    if (scope->depth != nullptr)
        scope->depth->release();
    scope->~TargetScope();
    HeapFree(GetProcessHeap(), 0, scope);
}

HRESULT begin_target(TargetScope& scope, Texture2D& destination, const D3D11_VIEWPORT* requested,
                     const float clear_color[4]) {
    if (scope.active || scope.renderer == nullptr || scope.renderer->context == nullptr ||
        destination.target == nullptr || destination.width != scope.width ||
        destination.height != scope.height)
        return E_INVALIDARG;
    D3D11_VIEWPORT viewport = {
        0, 0, static_cast<float>(scope.width), static_cast<float>(scope.height), 0, 1};
    if (requested != nullptr)
        viewport = *requested;
    if (viewport.TopLeftX < 0 || viewport.TopLeftY < 0 || viewport.Width <= 0 ||
        viewport.Height <= 0 || viewport.TopLeftX + viewport.Width > scope.width ||
        viewport.TopLeftY + viewport.Height > scope.height || viewport.MinDepth < 0 ||
        viewport.MaxDepth > 1 || viewport.MinDepth > viewport.MaxDepth)
        return E_INVALIDARG;
    auto& renderer = *scope.renderer;
    auto* context = renderer.context;
    context->OMGetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT, scope.previous_color,
                                &scope.previous_depth);
    scope.previous_viewport_count = D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
    context->RSGetViewports(&scope.previous_viewport_count, scope.previous_viewports);
    scope.previous_width = renderer.width;
    scope.previous_height = renderer.height;
    scope.previous_scene = renderer.scene;
    renderer.width = destination.width;
    renderer.height = destination.height;
    destination.retain();
    scope.destination = &destination;
    ID3D11ShaderResourceView* empty[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = {};
    context->PSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, empty);
    context->VSSetShaderResources(0, D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, empty);
    context->OMSetRenderTargets(1, &destination.target,
                                scope.depth != nullptr ? scope.depth->depth : nullptr);
    context->RSSetViewports(1, &viewport);
    if (clear_color != nullptr)
        context->ClearRenderTargetView(destination.target, clear_color);
    if (scope.depth != nullptr)
        context->ClearDepthStencilView(scope.depth->depth, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
                                       1, 0);
    passes_reset_bindings(renderer);
    scope.active = true;
    const HRESULT result = begin_scene(renderer, renderer.scene);
    if (FAILED(result))
        end_target(scope);
    return result;
}

HRESULT end_target(TargetScope& scope) {
    if (!scope.active || scope.renderer == nullptr || scope.renderer->context == nullptr)
        return E_INVALIDARG;
    auto& renderer = *scope.renderer;
    renderer.context->OMSetRenderTargets(D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT,
                                         scope.previous_color, scope.previous_depth);
    renderer.context->RSSetViewports(scope.previous_viewport_count, scope.previous_viewports);
    renderer.width = scope.previous_width;
    renderer.height = scope.previous_height;
    release_saved_targets(scope);
    scope.destination->release();
    scope.destination = nullptr;
    scope.active = false;
    passes_reset_bindings(renderer);
    const HRESULT result = begin_scene(renderer, scope.previous_scene);
    restore_draw_state(scope);
    return result;
}
} // namespace shaiya::graphics::native
