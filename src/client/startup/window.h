#pragma once
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdint.h>

extern "C" {
extern uint32_t dat_007198d0, dat_007198d4, dat_00719a5c, dat_0085cfbc;
extern void* dat_0071cfb0;
extern HWND dat_0224ea44;

__declspec(dllexport) int32_t __cdecl classify_startup_physical_memory();
__declspec(dllexport) void __cdecl detect_windows_nt_platform();
__declspec(dllexport) int32_t __cdecl ensure_startup_timing_marker();
// ANSI, Unicode and locale-selected window creation, respectively.
// Definitions document recovered behavior and original entry addresses.
__declspec(dllexport) void __cdecl create_game_window_ansi(uint32_t window_style, int32_t left,
                                                           int32_t top, int32_t window_width,
                                                           int32_t window_height);
__declspec(dllexport) void __cdecl create_game_window_unicode(uint32_t window_style, int32_t left,
                                                              int32_t top, int32_t window_width,
                                                              int32_t window_height);
__declspec(dllexport) void __cdecl create_game_window_for_locale(uint32_t window_style,
                                                                 int32_t left, int32_t top,
                                                                 int32_t window_width,
                                                                 int32_t window_height);
__declspec(dllexport) void __cdecl unregister_game_window_class_for_locale();
__declspec(dllexport) void __cdecl unregister_game_window_class_unicode();
__declspec(dllexport) LRESULT __attribute__((stdcall))
game_window_procedure(HWND window, UINT message, WPARAM wparam, LPARAM lparam);
__declspec(dllexport) void __cdecl send_activation_packet_2605();
}
