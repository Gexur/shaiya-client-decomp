#include "graphics/render_shaders.h"
#include "graphics/native_renderer.h"

// Concrete shader programs and input layouts belong to the native pass library.
// The engine owner retains availability flags, without legacy shader objects.
extern "C" int32_t __attribute__((thiscall)) FUN_00547cd0(void* self) {
    auto* fields = static_cast<uint32_t*>(self);
    const bool available = shaiya::graphics::native::renderer()->pipeline_data != nullptr;
    fields[1] = fields[2] = available ? 1 : 0;
    for (UINT offset = 0xc; offset <= 0x20; offset += 4)
        fields[offset / 4] = 0;
    return available ? 1 : 0;
}
