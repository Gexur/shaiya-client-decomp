#pragma once
#include "graphics/native_resources.h"

namespace shaiya::graphics::native {
struct TargetScope {
    NativeRenderer* renderer = nullptr;
    Texture2D* depth = nullptr;
    Texture2D* destination = nullptr;
    ID3D11RenderTargetView* previous_color[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = {};
    ID3D11DepthStencilView* previous_depth = nullptr;
    D3D11_VIEWPORT previous_viewports[D3D11_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE] =
        {};
    UINT previous_viewport_count = 0;
    UINT previous_width = 0, previous_height = 0;
    Scene previous_scene;
    // Optional operation-owned state follows the same lifetime as this target.
    void* saved_draw_state = nullptr;
    void (*restore_draw_state)(void*) = nullptr;
    UINT width = 0, height = 0;
    bool active = false;
};
HRESULT create_target_scope(NativeRenderer&, UINT width, UINT height, bool with_depth,
                            TargetScope** scope);
void release_target_scope(TargetScope* scope);
HRESULT begin_target(TargetScope&, Texture2D& destination, const D3D11_VIEWPORT* viewport = nullptr,
                     const float clear_color[4] = nullptr);
HRESULT end_target(TargetScope&);
} // namespace shaiya::graphics::native
