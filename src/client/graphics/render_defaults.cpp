#include "graphics/render_defaults.h"
#include "graphics/native_renderer.h"
#include "config/initialization.hpp"

extern "C" void __attribute__((thiscall)) FUN_005414f0(void*, float);

namespace {
void store(void* self, uintptr_t offset, uint32_t value) {
    auto* destination = reinterpret_cast<uint32_t*>(static_cast<unsigned char*>(self) + offset);
    *destination = value;
}
} // namespace

extern "C" void __attribute__((thiscall)) FUN_00541fe0(void* self) {
    auto* current = shaiya::graphics::native::renderer();
    current->scene.ambient = {192.0f / 255.0f, 192.0f / 255.0f, 192.0f / 255.0f, 1};
    current->scene.directional = {1, 1, 1, 1};
    current->scene.light_direction[0] = -1;
    current->scene.light_direction[1] = -1;
    current->scene.light_direction[2] = -1;
    current->scene.light_direction[3] = 0;
    // Material colors remain game data; draw passes consume typed material
    // descriptors instead of a mutable device-wide fixed-function state.
    for (uintptr_t offset = 0; offset < 0x44; offset += 4)
        store(self, 0x3c0 + offset, 0);
    for (uintptr_t offset = 0; offset < 0x20; offset += 4)
        store(self, 0x3c0 + offset, 0x3f800000);
    store(self, 0xe4, 0xbf800000);
    store(self, 0xe8, 0xbf800000);
    store(self, 0xec, 0xbf800000);
    store(self, 0x1620, 0);
    const uint32_t setting = shaiya::config::DAT_007198e8 - 2u;
    FUN_005414f0(self, 1.0f + static_cast<float>(static_cast<int32_t>(setting)) * 0.15f);
}

extern "C" int32_t __attribute__((thiscall)) FUN_0054a4e0(void* self) {
    store(self, 0x10, DXGI_FORMAT_B8G8R8A8_UNORM);
    return 1;
}
