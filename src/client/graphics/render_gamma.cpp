#include "graphics/render_gamma.h"
#include "graphics/native_renderer.h"

extern "C" void __attribute__((thiscall)) FUN_005414f0(void*, float gamma) {
    // Correct the final client frame, including UI, without changing desktop
    // monitor ramps or the appearance of other applications.
    auto* current = shaiya::graphics::native::renderer();
    current->gamma = gamma > 0.0f && gamma <= 16.0f ? gamma : 1.0f;
}
