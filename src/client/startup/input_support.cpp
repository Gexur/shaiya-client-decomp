#define CINTERFACE
#include "input_support.h"
#include "../ui/constructors.hpp"

using shaiya::startup::InputFormatObjects;
using shaiya::ui::FUN_005cc96d;
static_assert(sizeof(DIDATAFORMAT) == 24 && sizeof(DIOBJECTDATAFORMAT) == 16);
extern "C" {
// Original wrapper531af0 explicitly replaces ECX with this global address.
// Its full object layout/constructor are unresolved, so storage stays external.
extern unsigned char dat_02207124[];
// Typed GUID fields and format rows are original data, not section snapshots.
extern const GUID dat_006f7388 = {
    0x6f1d2b61, 0xd5a0, 0x11cf, {0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0, 0}};
extern const GUID dat_006f7398 = {
    0x6f1d2b60, 0xd5a0, 0x11cf, {0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0, 0}};
extern const GUID dat_006f73a8 = {
    0x55728220, 0xd33c, 0x11cf, {0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0, 0}};
extern const GUID dat_006f73b8 = {
    0xa36d02e2, 0xc9f3, 0x11cf, {0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0, 0}};
extern const GUID dat_006f73c8 = {
    0xa36d02e1, 0xc9f3, 0x11cf, {0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0, 0}};
extern const GUID dat_006f73d8 = {
    0xa36d02e0, 0xc9f3, 0x11cf, {0xbf, 0xc7, 0x44, 0x45, 0x53, 0x54, 0, 0}};
extern const GUID dat_006f73e8 = {
    0xbf798030, 0x483a, 0x4da2, {0xaa, 0x99, 0x5d, 0x64, 0xed, 0x36, 0x97, 0}};
}

namespace {
constexpr InputFormatObjects<256> keyboard_objects() {
    InputFormatObjects<256> result = {};
    // Every original row has GUID6f73a8, byte offset i, flags0 and this type.
    // The verifier compares all256 original rows, not a sample/pattern guess.
    for (uint32_t i = 0; i != 256; ++i)
        result.objects[i] = {&dat_006f73a8, i, 0x8000000cu | (i << 8), 0};
    return result;
}
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
IDirectInputDevice8A* device(void* self) {
    return reinterpret_cast<IDirectInputDevice8A*>(word_at(self, 0));
}
IDirectInput8A* input(void* self) {
    return reinterpret_cast<IDirectInput8A*>(word_at(self, 0));
}
uint32_t with_low_byte(HRESULT result, bool low) {
    return (uint32_t(result) & 0xffffff00u) | uint32_t(low);
}
uint32_t initialize_device(void* self, HWND window, IDirectInput8A* native_input, uint32_t flags,
                           const GUID& guid, const DIDATAFORMAT& format) {
    HRESULT result = native_input->lpVtbl->CreateDevice(
        native_input, guid, reinterpret_cast<IDirectInputDevice8A**>(self), nullptr);
    if (result < 0)
        return with_low_byte(result, false);
    auto* current = device(self);
    result = current->lpVtbl->SetDataFormat(current, &format);
    if (result < 0)
        return with_low_byte(result, false);
    current = device(self);
    result = current->lpVtbl->SetCooperativeLevel(current, window, flags);
    if (result < 0)
        return with_low_byte(result, false);
    current = device(self);
    result = current->lpVtbl->Acquire(current);
    // Original ignores failure of Acquire and writes AL=1 over its HRESULT.
    return with_low_byte(result, true);
}
} // namespace

extern "C" {
extern const InputFormatObjects<256> dat_005b7850 = keyboard_objects();
extern const InputFormatObjects<11> dat_005b8850 = {{{&dat_006f73d8, 0, 0x00ffff03, 0},
                                                     {&dat_006f73c8, 4, 0x00ffff03, 0},
                                                     {&dat_006f73b8, 8, 0x80ffff03, 0},
                                                     {nullptr, 12, 0x00ffff0c, 0},
                                                     {nullptr, 13, 0x00ffff0c, 0},
                                                     {nullptr, 14, 0x80ffff0c, 0},
                                                     {nullptr, 15, 0x80ffff0c, 0},
                                                     {nullptr, 16, 0x80ffff0c, 0},
                                                     {nullptr, 17, 0x80ffff0c, 0},
                                                     {nullptr, 18, 0x80ffff0c, 0},
                                                     {nullptr, 19, 0x80ffff0c, 0}}};
extern const DIDATAFORMAT dat_006cf6b4 = {
    24, 16, 2, 256, 256, const_cast<DIOBJECTDATAFORMAT*>(dat_005b7850.objects)};
extern const DIDATAFORMAT dat_006cf8bc = {
    24, 16, 2, 20, 11, const_cast<DIOBJECTDATAFORMAT*>(dat_005b8850.objects)};
}

extern "C" uint32_t __attribute__((thiscall)) FUN_005aa410(void* self, HINSTANCE instance) {
    const HRESULT result =
        DirectInput8Create(instance, 0x800, dat_006f73e8, reinterpret_cast<void**>(self), nullptr);
    return with_low_byte(result, result >= 0);
}
extern "C" uint32_t __attribute__((thiscall))
FUN_005aa050(void* self, HWND window, IDirectInput8A* native_input, uint32_t flags) {
    return initialize_device(self, window, native_input, flags, dat_006f7388, dat_006cf6b4);
}
extern "C" uint32_t __attribute__((thiscall))
FUN_005aa1b0(void* self, HWND window, IDirectInput8A* native_input, uint32_t flags) {
    return initialize_device(self, window, native_input, flags, dat_006f7398, dat_006cf8bc);
}
extern "C" void* __attribute__((thiscall)) FUN_005aa150(void* self) {
    set_word(self, 0, 0);
    for (uint32_t offset = 4; offset != 0x204; offset += 4)
        set_word(self, offset, 0);
    set_word(self, 0x404, 0);
    set_word(self, 0x408, 1);
    for (uint32_t offset = 0x204; offset != 0x404; offset += 4)
        set_word(self, offset, 0);
    return self;
}
extern "C" void* __attribute__((thiscall)) FUN_005aa2a0(void* self) {
    set_word(self, 0, 0);
    for (uint32_t offset = 0x0c; offset != 0x2c; offset += 4)
        set_word(self, offset, 0);
    set_word(self, 4, 0);
    set_word(self, 8, 1);
    return self;
}

// Original wrappers register FS:[0] cleanup frames for constructor exceptions.
// This C++ recovery currently preserves their real normal-return paths only.
extern "C" uint32_t __attribute__((thiscall)) FUN_005aa430(void* self, HWND window, uint32_t,
                                                           uint32_t) {
    void* allocated = FUN_005cc96d(0x40c);
    void* child = allocated != nullptr ? FUN_005aa150(allocated) : nullptr;
    IDirectInput8A* native_input = input(self);
    set_word(self, 4, uint32_t(reinterpret_cast<uintptr_t>(child)));
    const uint32_t result = FUN_005aa050(child, window, native_input, 6);
    return (result & 0xffffff00u) | uint32_t(uint8_t(result) != 0);
}
extern "C" uint32_t __attribute__((thiscall))
FUN_005aa4b0(void* self, HWND window, uint32_t parameter2, uint32_t parameter3) {
    const uint32_t flags = uint8_t(parameter3) == 0 ? 10 : 6 - uint32_t(uint8_t(parameter2) != 0);
    void* allocated = FUN_005cc96d(0x34);
    void* child = allocated != nullptr ? FUN_005aa2a0(allocated) : nullptr;
    IDirectInput8A* native_input = input(self);
    set_word(self, 8, uint32_t(reinterpret_cast<uintptr_t>(child)));
    const uint32_t result = FUN_005aa1b0(child, window, native_input, flags);
    return (result & 0xffffff00u) | uint32_t(uint8_t(result) != 0);
}

extern "C" void __attribute__((thiscall)) FUN_00531af0(void*) {
    FUN_00535ea0(dat_02207124);
}
extern "C" void __attribute__((thiscall)) FUN_00535ea0(void* self) {
    char path[0x108];
    if (GetSystemDirectoryA(path, 0x105) == 0)
        return;
    uint32_t length = 0;
    while (path[length] != 0)
        ++length;
    const char suffix[] = "\\imm32.dll";
    for (uint32_t i = 0; i != 11; ++i)
        path[length + i] = suffix[i];
    HMODULE module = LoadLibraryA(path);
    set_word(self, 4, uint32_t(reinterpret_cast<uintptr_t>(module)));
    if (module == nullptr)
        return;
    const auto get_proc = &GetProcAddress;
    FARPROC procedure = get_proc(module, "ImmLockIMC");
    set_word(self, 8, uint32_t(reinterpret_cast<uintptr_t>(procedure)));
    procedure = get_proc(reinterpret_cast<HMODULE>(word_at(self, 4)), "ImmUnlockIMC");
    set_word(self, 0x0c, uint32_t(reinterpret_cast<uintptr_t>(procedure)));
    procedure = get_proc(reinterpret_cast<HMODULE>(word_at(self, 4)), "ImmLockIMCC");
    set_word(self, 0x10, uint32_t(reinterpret_cast<uintptr_t>(procedure)));
    procedure = get_proc(reinterpret_cast<HMODULE>(word_at(self, 4)), "ImmUnlockIMCC");
    set_word(self, 0x14, uint32_t(reinterpret_cast<uintptr_t>(procedure)));
}
