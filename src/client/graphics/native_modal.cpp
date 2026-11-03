#include "graphics/native_modal.h"
namespace {
UINT depth = 0;
bool restore_exclusive = false;
} // namespace
extern "C" HRESULT __cdecl native_modal_begin() {
    auto* current = shaiya::graphics::native::renderer();
    shaiya::graphics::native::FrameRenderScope serialization(*current);
    if (!current->swapchain)
        return E_UNEXPECTED;
    if (depth) {
        ++depth;
        return S_OK;
    }
    BOOL exclusive = FALSE;
    HRESULT result = current->swapchain->GetFullscreenState(&exclusive, nullptr);
    if (FAILED(result))
        return result;
    if (exclusive) {
        result = current->swapchain->SetFullscreenState(FALSE, nullptr);
        if (FAILED(result))
            return result;
        current->fullscreen = false;
    }
    restore_exclusive = exclusive != FALSE;
    depth = 1;
    return S_OK;
}
extern "C" HRESULT __cdecl native_modal_end() {
    auto* current = shaiya::graphics::native::renderer();
    shaiya::graphics::native::FrameRenderScope serialization(*current);
    if (!depth)
        return S_FALSE;
    if (depth > 1) {
        --depth;
        return S_OK;
    }
    if (!current->swapchain) {
        restore_exclusive = false;
        depth = 0;
        return S_FALSE;
    }
    HRESULT result =
        restore_exclusive ? current->swapchain->SetFullscreenState(TRUE, nullptr) : S_OK;
    if (SUCCEEDED(result)) {
        current->fullscreen = restore_exclusive;
        restore_exclusive = false;
        depth = 0;
    }
    return result;
}
