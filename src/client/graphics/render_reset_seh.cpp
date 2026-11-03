#include "graphics/render_reset.h"
#include "graphics/native_renderer.h"
#include "graphics/render_state.h"
#include "config/initialization.hpp"

extern "C" HWND dat_00719a3c;
// MSVC emits this link marker for floating-point arithmetic in a freestanding unit.
extern "C" int _fltused = 0x9875;

extern "C" int32_t __attribute__((thiscall)) FUN_00543a00(void* self) {
    using namespace shaiya::config;
    auto* current = *reinterpret_cast<shaiya::graphics::native::NativeRenderer**>(
        static_cast<unsigned char*>(self) + 0x408);
    if (current == nullptr || current->device_removed)
        return 0;
    RECT client = {};
    if (!GetClientRect(dat_00719a3c, &client))
        return 0;
    const UINT width =
        current->fullscreen ? static_cast<UINT>(DAT_0070859c) : static_cast<UINT>(client.right);
    const UINT height =
        current->fullscreen ? static_cast<UINT>(DAT_007085a0) : static_cast<UINT>(client.bottom);
    if (FAILED(native_renderer_resize(current, width, height)))
        return 0;
    DAT_0070859c = static_cast<int32_t>(current->width);
    DAT_007085a0 = static_cast<int32_t>(current->height);
    DAT_007085b8 = static_cast<int32_t>(DAT_007198dc) > 2
                       ? static_cast<float>(current->width) / static_cast<float>(current->height)
                       : 1.25f;
    // D3D11 asset buffers, textures, font atlases and immutable pass objects
    // survive swapchain resize. Only camera projection depends on dimensions.
    FUN_00542400(self);
    FUN_005424d0(self);
    return 1;
}
