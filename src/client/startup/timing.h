#pragma once
#include <stdint.h>

extern "C" {
// File-backed zero initial values at these original .data locations. The
// pointer's object type is unresolved; this helper only tests it for null.
extern __declspec(dllexport) void* dat_00719a64;
extern __declspec(dllexport) uint32_t dat_00719a6c;

__declspec(dllexport) void __cdecl initialize_startup_refresh_tick();
__declspec(dllexport) uint32_t __cdecl refresh_startup_tick();
}
