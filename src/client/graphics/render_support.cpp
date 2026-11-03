#include "graphics/render_support.h"
#include "startup/application.h"
#include "network/packets.h"
#include "config/initialization.hpp"
#include "graphics/native_renderer.h"

using shaiya::config::DAT_0070859c;
using shaiya::config::DAT_007085a0;
using shaiya::config::DAT_0071987c;
using shaiya::config::DAT_00719a40;
extern "C" {
int32_t dat_0070bb58 = 5; // Actual little-endian file DWORD at0x70bb58.
int32_t __cdecl FUN_00546fb0(uint32_t*, uint32_t*, char*);
int32_t __cdecl FUN_005472c0(uint32_t*, uint32_t*, char*);
int32_t __cdecl FUN_005d0969(int32_t); // Original _tolower entry, see disassembly.
uint32_t __attribute__((thiscall)) FUN_005aa410(void*, HINSTANCE);
uint32_t __attribute__((thiscall)) FUN_005aa4b0(void*, HWND, uint32_t, uint32_t);
// The original RET12 consumes all three pushed words, despite Ghidra exposing
// only its first used argument. Do not turn this into a one-argument method.
uint32_t __attribute__((thiscall)) FUN_005aa430(void*, HWND, uint32_t, uint32_t);
void __attribute__((thiscall)) FUN_00531af0(void*);
}

namespace {
uint32_t word_at(void* object, uintptr_t offset) {
    const auto* p =
        reinterpret_cast<const unsigned char*>(reinterpret_cast<uintptr_t>(object) + offset);
    return uint32_t(p[0]) | uint32_t(p[1]) << 8 | uint32_t(p[2]) << 16 | uint32_t(p[3]) << 24;
}
void set_word(void* object, uintptr_t offset, uint32_t value) {
    auto* p = reinterpret_cast<unsigned char*>(reinterpret_cast<uintptr_t>(object) + offset);
    p[0] = uint8_t(value);
    p[1] = uint8_t(value >> 8);
    p[2] = uint8_t(value >> 16);
    p[3] = uint8_t(value >> 24);
}
void set_byte(void* object, uintptr_t offset, unsigned char value) {
    *reinterpret_cast<unsigned char*>(reinterpret_cast<uintptr_t>(object) + offset) = value;
}
void* offset_pointer(void* object, uintptr_t offset) {
    return reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(object) + offset);
}
} // namespace

// Validate the native renderer requirements instead of legacy DirectX version
// strings. Hardware and WARP use the same explicit D3D11 pass implementation.
extern "C" int32_t __cdecl FUN_00547c30() {
    const D3D_FEATURE_LEVEL levels[] = {D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1,
                                        D3D_FEATURE_LEVEL_10_0};
    ID3D11Device* device = nullptr;
    ID3D11DeviceContext* context = nullptr;
    HRESULT result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                                       D3D11_CREATE_DEVICE_BGRA_SUPPORT, levels, 3,
                                       D3D11_SDK_VERSION, &device, nullptr, &context);
    if (FAILED(result))
        result = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr,
                                   D3D11_CREATE_DEVICE_BGRA_SUPPORT, levels, 3, D3D11_SDK_VERSION,
                                   &device, nullptr, &context);
    if (context != nullptr)
        context->Release();
    if (device != nullptr)
        device->Release();
    return SUCCEEDED(result);
}
extern "C" int32_t __attribute__((thiscall)) FUN_00541400(void*) {
    return FUN_00547c30();
}

extern "C" int32_t __attribute__((thiscall)) FUN_00541410(void*) {
    // DXGI applies exclusive mode as part of NativeRenderer initialization;
    // windowed clients never change the desktop's display mode.
    return DAT_0070859c > 0 && DAT_007085a0 > 0;
}

extern "C" int32_t __attribute__((thiscall)) FUN_00531680(void* self) {
    void* input = offset_pointer(self, 4);
    FUN_005aa410(input, static_cast<HINSTANCE>(DAT_00719a40));
    FUN_005aa4b0(input, dat_00719a3c, 0, 1);
    set_word(self, 0x14, word_at(self, 0x0c));
    FUN_005aa430(input, dat_00719a3c, 0, 0);
    set_word(self, 0x10, word_at(self, 8));
    FUN_00531af0(offset_pointer(self, 0x464));
    set_word(self, 0x3aa4, 3);
    return 1;
}

extern "C" void* __attribute__((thiscall)) FUN_005a3c10(void* self) {
    set_word(self, 0, 0);
    set_word(self, 4, 0);
    set_word(self, 0x10, 0);
    set_word(self, 0x14, 0);
    set_word(self, 0x18, 0);
    return self;
}
extern "C" void* __attribute__((thiscall)) FUN_0053e530(void* self) {
    FUN_005a3c10(offset_pointer(self, 0x1d4));
    set_word(self, 0x13c, 0);
    set_word(self, 0x140, 0);
    set_word(self, 0x144, 0);
    set_word(self, 0x148, 0x3f800000);
    set_word(self, 0x14c, 0);
    set_word(self, 0x150, 0);
    set_word(self, 0x154, 0);
    set_word(self, 0x158, 0x3f800000);
    set_word(self, 0, 0);
    set_word(self, 0xf4, 0);
    set_word(self, 0xf8, 0);
    set_word(self, 0xf0, 0);
    set_word(self, 0x2d8, 0);
    set_byte(self, 0x1d0, 0);
    set_word(self, 0x10, 0);
    set_word(self, 0x14, 0);
    set_word(self, 0x2dc, 0);
    set_word(self, 0x2e0, 0);
    set_word(self, 0x2e4, 0);
    set_word(self, 0x2f0, 0);
    set_word(self, 0x2f4, 0);
    set_word(self, 0x2e8, 0);
    set_word(self, 0x2ec, 0);
    set_word(self, 0x2f8, 0);
    set_word(self, 0x2fc, 0);
    set_byte(self, 4, 0);
    set_word(self, 0x15c, 0);
    return self;
}
extern "C" void* __attribute__((thiscall)) FUN_0054e330(void* self) {
    const int32_t count = dat_0070bb58;
    set_byte(self, 8, 1);
    set_byte(self, 9, 1);
    set_byte(self, 0x86, 1);
    set_byte(self, 0x85, 0);
    set_byte(self, 0, 0);
    set_word(self, 4, 0);
    set_word(self, 0x90, 2);
    set_word(self, 0x0c, 2);
    set_word(self, 0x10, 0x3f800000);
    set_word(self, 0x74, 0);
    set_word(self, 0x78, 0);
    set_word(self, 0x1c, 0);
    set_word(self, 0x18, 0);
    set_word(self, 0x14, 0);
    set_word(self, 0x28, 0);
    set_word(self, 0x24, 0);
    set_word(self, 0x20, 0);
    for (uint32_t i = 0; i < uint32_t(count > 0 ? count : 0); ++i) {
        set_word(self, 0x2c + 4 * i, 0);
        set_word(self, 0x50 + 4 * i, 0);
    }
    set_word(self, 0x7c, 0);
    set_word(self, 0x80, 0);
    set_byte(self, 0x84, 0);
    set_word(self, 0x88, 0);
    set_word(self, 0x8c, 0);
    return self;
}
