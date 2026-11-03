#pragma once
#include <stdint.h>

// Binary-evidenced helpers. Names retain original procedure addresses.
// These APIs keep the original x86 public stack cleanup conventions.
extern "C" {
__declspec(dllexport) uint32_t __attribute__((cdecl)) fun_0040d040(const uint8_t* input,
                                                                   uint32_t length);

// Uses the original 1024-byte temporary. The original has no bounds check;
// differential tests cover inputs whose retained bytes fit with a terminator.
__declspec(dllexport) void __attribute__((stdcall)) fun_0040a6f0(char* text);

// Null pointers and an empty source leave destination untouched, unlike strcpy.
__declspec(dllexport) void __attribute__((cdecl)) fun_0041d3b0(char* destination,
                                                               const char* source);
}
