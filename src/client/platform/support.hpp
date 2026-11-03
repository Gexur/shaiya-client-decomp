#pragma once

// These are the observed x86 C interfaces. They do not supply WinMain, a game
// loop, or guessed startup state. Windows and CRT dependencies remain real.
extern "C" {
__declspec(dllexport) unsigned int __cdecl FUN_00409ff0();
__declspec(dllexport) unsigned int __cdecl FUN_0040cf40();
__declspec(dllexport) long __cdecl FUN_0040a040(const char* path);
__declspec(dllexport) int __cdecl FUN_0040d020(void* buffer, unsigned int element_size,
                                               unsigned int element_count, int descriptor);
}
