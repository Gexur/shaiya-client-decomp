#pragma once
#define WIN32_LEAN_AND_MEAN
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION 0x0800
#endif
#include <windows.h>
#include <dinput.h>
#include <stdint.h>

namespace shaiya::startup {
template <unsigned int N> struct InputFormatObjects {
    DIOBJECTDATAFORMAT objects[N];
};
} // namespace shaiya::startup
extern "C" {
extern const GUID dat_006f7388, dat_006f7398, dat_006f73a8, dat_006f73b8, dat_006f73c8,
    dat_006f73d8, dat_006f73e8;
extern const shaiya::startup::InputFormatObjects<256> dat_005b7850;
extern const shaiya::startup::InputFormatObjects<11> dat_005b8850;
extern const DIDATAFORMAT dat_006cf6b4, dat_006cf8bc;

// Original EAX results retain their high24 HRESULT bits while replacing AL.
__declspec(dllexport) uint32_t __attribute__((thiscall)) FUN_005aa410(void*, HINSTANCE);
__declspec(dllexport) uint32_t __attribute__((thiscall)) FUN_005aa050(void*, HWND, IDirectInput8A*,
                                                                      uint32_t);
__declspec(dllexport) uint32_t __attribute__((thiscall)) FUN_005aa1b0(void*, HWND, IDirectInput8A*,
                                                                      uint32_t);
__declspec(dllexport) uint32_t __attribute__((thiscall)) FUN_005aa430(void*, HWND, uint32_t,
                                                                      uint32_t);
__declspec(dllexport) uint32_t __attribute__((thiscall)) FUN_005aa4b0(void*, HWND, uint32_t,
                                                                      uint32_t);
__declspec(dllexport) void* __attribute__((thiscall)) FUN_005aa150(void*);
__declspec(dllexport) void* __attribute__((thiscall)) FUN_005aa2a0(void*);
__declspec(dllexport) void __attribute__((thiscall)) FUN_00531af0(void*);
__declspec(dllexport) void __attribute__((thiscall)) FUN_00535ea0(void*);
}
