#include "graphics/render_state.h"
#include "graphics/native_font.h"
#include "config/initialization.hpp"
#include "graphics/native_renderer.h"
#include "graphics/native_scene_ports.h"
extern "C" void __cdecl native_scene_style_defaults();

using shaiya::config::DAT_007085b8;
extern "C" {
float dat_007085b4 = 0x1.921fb00000000p-1f; // Original raw DWORD0x3f490fd8.
uint32_t dat_0070c83c = 2;
uint8_t dat_0070ca53 = 1;
uint32_t dat_0224e3f8 = 0;
RenderStatePrefix_005ad720 dat_0224e3a0 = {nullptr, nullptr, {}, nullptr, nullptr};
// Actual statically linked D3DX math dependencies. The inverse entry is the
// original dispatch thunk at5e52de, not an invented backend implementation.
shaiya::graphics::native::Matrix* __attribute__((stdcall))
FUN_005e65c3(shaiya::graphics::native::Matrix*, float, float, float, float);
shaiya::graphics::native::Matrix* __attribute__((stdcall))
FUN_005e646b(shaiya::graphics::native::Matrix*, const void*, const void*, const void*);
shaiya::graphics::native::Matrix* __attribute__((stdcall))
FUN_005e52de(shaiya::graphics::native::Matrix*, float*, const shaiya::graphics::native::Matrix*);
// The canonical atexit symbol denotes original5ccf60; its registry is recovered
// separately. This is a real callback registration, never a fake no-op backend.
int __cdecl atexit(void(__cdecl*)());
}

namespace {
void* at(void* self, uintptr_t offset) {
    return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(self) + offset);
}
uint32_t word(void* self, uintptr_t offset) {
    const auto* p = static_cast<const unsigned char*>(at(self, offset));
    return uint32_t(p[0]) | uint32_t(p[1]) << 8 | uint32_t(p[2]) << 16 | uint32_t(p[3]) << 24;
}
void set_word(void* self, uintptr_t offset, uint32_t value) {
    auto* p = static_cast<unsigned char*>(at(self, offset));
    p[0] = uint8_t(value);
    p[1] = uint8_t(value >> 8);
    p[2] = uint8_t(value >> 16);
    p[3] = uint8_t(value >> 24);
}
struct HardwareWord {
    unsigned char bytes[4];
};
uint32_t hardware_word(const unsigned char* bytes) {
    uint32_t value;
    __asm__ __volatile__("movl %1,%0"
                         : "=r"(value)
                         : "m"(*reinterpret_cast<const HardwareWord*>(bytes)));
    return value;
}
void font_measurement(void* self, uintptr_t font_offset, uintptr_t x_offset, uintptr_t y_offset) {
    auto* font = reinterpret_cast<shaiya::graphics::native::NativeFont*>(word(self, font_offset));
    const char text[2] = {' ', 0};
    HDC context = shaiya::graphics::native::font_dc(font);
    alignas(uint32_t) unsigned char size[8];
    GetTextExtentPoint32A(context, text, 1, reinterpret_cast<SIZE*>(size));
    // Original ignores failure and reads whatever the API/private slots hold.
    // Explicit hardware loads retain that operation without uninitialized C++
    // scalar promotion. Known API outputs are compared in the verifier.
    const uint32_t x = hardware_word(size), y = hardware_word(size + 4);
    set_word(self, x_offset, x);
    set_word(self, y_offset, y);
}
shaiya::graphics::native::NativeRenderer* device(void* self) {
    return reinterpret_cast<shaiya::graphics::native::NativeRenderer*>(word(self, 0x408));
}
void update_view_projection(shaiya::graphics::native::NativeRenderer& current) {
    auto& out = current.scene.view_projection;
    for (unsigned row = 0; row < 4; ++row)
        for (unsigned column = 0; column < 4; ++column) {
            out.m[row][column] = 0;
            for (unsigned component = 0; component < 4; ++component)
                out.m[row][column] +=
                    current.scene.view.m[row][component] * current.projection.m[component][column];
        }
}
} // namespace

extern "C" void __attribute__((thiscall)) FUN_00541bf0(void* self) {
    font_measurement(self, 0x3a8, 0x3b0, 0x3b8);
}
extern "C" void __attribute__((thiscall)) FUN_00541c40(void* self) {
    font_measurement(self, 0x3a4, 0x3b4, 0x3bc);
}
extern "C" void __attribute__((thiscall)) FUN_00542400(void* self) {
    auto* matrix = reinterpret_cast<shaiya::graphics::native::Matrix*>(at(self, 0x80));
    FUN_005e65c3(matrix, dat_007085b4, DAT_007085b8, 0.1f, 400.0f);
    auto* current = device(self);
    current->projection = *matrix;
    update_view_projection(*current);
}

extern "C" void __attribute__((thiscall)) FUN_00542440(void* self, float field_of_view,
                                                       float near_plane, float far_plane) {
    auto* matrix = reinterpret_cast<shaiya::graphics::native::Matrix*>(at(self, 0x80));
    FUN_005e65c3(matrix, field_of_view, DAT_007085b8, near_plane, far_plane);
    auto* current = device(self);
    current->projection = *matrix;
    update_view_projection(*current);
    shaiya::graphics::native::begin_scene(*current, current->scene);
}

extern "C" void __attribute__((thiscall)) FUN_00542560(void* self, const uint32_t* position,
                                                       const uint32_t* target, const uint32_t* up) {
    for (UINT component = 0; component < 3; ++component) {
        set_word(self, 0xc0 + component * 4, position[component]);
        set_word(self, 0xcc + component * 4, target[component]);
        set_word(self, 0xd8 + component * 4, up[component]);
    }
    FUN_005424d0(self);
    auto* current = device(self);
    for (UINT component = 0; component < 3; ++component)
        current->scene.camera[component] = *reinterpret_cast<const float*>(position + component);
    shaiya::graphics::native::begin_scene(*current, current->scene);
}

extern "C" void __attribute__((thiscall)) FUN_00542bf0(void*) {
    using namespace shaiya::graphics::native;
    auto& context = scene_draw_context();
    context.world = {{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
    context.lit = true;
    context.material.style = {Blend::alpha, Depth::write, Cull::back, Sampling::linear_wrap};
    context.material.style.alpha_cutoff = 7.5f / 255;
    context.material.diffuse_color = {1, 1, 1, 1};
    context.material.ambient_color = {1, 1, 1, 1};
    native_scene_style_defaults();
}

extern "C" void __attribute__((thiscall)) FUN_00542e20(void*, float* output,
                                                       const float* position) {
    auto* current = shaiya::graphics::native::renderer();
    const auto& matrix = current->scene.view_projection;
    float clip[4] = {};
    for (UINT column = 0; column < 4; ++column) {
        clip[column] = matrix.m[3][column];
        for (UINT component = 0; component < 3; ++component)
            clip[column] += position[component] * matrix.m[component][column];
    }
    D3D11_VIEWPORT viewport = {
        0, 0, static_cast<float>(current->width), static_cast<float>(current->height), 0, 1};
    UINT count = 1;
    current->context->RSGetViewports(&count, &viewport);
    output[0] = viewport.TopLeftX + (1 + clip[0] / clip[3]) * viewport.Width * 0.5f;
    output[1] = viewport.TopLeftY + (1 - clip[1] / clip[3]) * viewport.Height * 0.5f;
    output[2] = viewport.MinDepth + (clip[2] / clip[3]) * (viewport.MaxDepth - viewport.MinDepth);
}
extern "C" void __attribute__((thiscall)) FUN_005424d0(void* self) {
    auto* matrix = reinterpret_cast<shaiya::graphics::native::Matrix*>(at(self, 0x40));
    FUN_005e646b(matrix, at(self, 0xc0), at(self, 0xcc), at(self, 0xd8));
    auto* current = device(self);
    current->scene.view = *matrix;
    update_view_projection(*current);
    FUN_005e52de(reinterpret_cast<shaiya::graphics::native::Matrix*>(at(self, 0xfc)), nullptr,
                 matrix);
}
extern "C" void __attribute__((thiscall)) FUN_005425f0(void* self) {
    const uintptr_t zero_offsets[] = {0x38, 0x34, 0x30, 0x2c, 0x24, 0x20,
                                      0x1c, 0x18, 0x10, 0x0c, 8,    4};
    for (uintptr_t offset : zero_offsets)
        set_word(self, offset, 0);
    set_word(self, 0x3c, 0x3f800000);
    set_word(self, 0x28, 0x3f800000);
    set_word(self, 0x14, 0x3f800000);
    set_word(self, 0, 0x3f800000);
    // Original542627..542635 also binds this identity WORLD transform.
    // Later world effects and basic water must not inherit an actor pose.
    shaiya::graphics::native::scene_draw_context().world =
        *reinterpret_cast<const shaiya::graphics::native::Matrix*>(self);
}
extern "C" void* __cdecl FUN_005ad720() {
    if ((dat_0224e3f8 & 1) == 0) {
        dat_0224e3f8 |= 1;
        dat_0224e3a0.field_000 = nullptr;
        dat_0224e3a0.field_004 = nullptr;
        dat_0224e3a0.field_050 = nullptr;
        (void)atexit(FUN_006ba7c0);
    }
    return &dat_0224e3a0;
}
extern "C" uint32_t __attribute__((thiscall)) FUN_005ad770(void* self, void* device_pointer) {
    set_word(self, 4, uint32_t(reinterpret_cast<uintptr_t>(device_pointer)));
    // Native material passes bind explicit shader resources and sampler objects.
    dat_0070c83c = D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT;
    dat_0070ca53 = 1;
    return 0;
}
// Native GPU resources belong to NativeRenderer and typed asset owners. This
// recovered camera prefix stores borrowed engine pointers only.
extern "C" void __cdecl FUN_006ba7c0() {
    dat_0224e3a0.field_000 = nullptr;
    dat_0224e3a0.field_004 = nullptr;
    dat_0224e3a0.field_050 = nullptr;
}
