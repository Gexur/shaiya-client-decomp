#include "time_initializers.h"

extern "C" uint32_t __attribute__((stdcall)) timeGetTime();

// Every listed target is a concrete original DWORD, initially zero in the PE
// image (file storage or the PE zero-fill region). These are not guessed
// objects: the complete original initializer is CALL timeGetTime; MOV [x],EAX;
// RET. None registers a destructor. Table order is retained in the manifest.
extern "C" {
__declspec(dllexport) uint32_t dat_0071cfd8 = 0;
__declspec(dllexport) uint32_t dat_0071cfe0 = 0;
__declspec(dllexport) uint32_t dat_0071cfdc = 0;
__declspec(dllexport) uint32_t dat_0071d07c = 0;
__declspec(dllexport) uint32_t dat_0071d078 = 0;
__declspec(dllexport) uint32_t dat_00864e30 = 0;
__declspec(dllexport) uint32_t dat_00864e80 = 0;
__declspec(dllexport) uint32_t dat_008655bc = 0;
__declspec(dllexport) uint32_t dat_008655b8 = 0;
__declspec(dllexport) uint32_t dat_008655dc = 0;
__declspec(dllexport) uint32_t dat_008655e0 = 0;
__declspec(dllexport) uint32_t dat_02207f74 = 0;
}

/**
 * Capture one multimedia-clock sample in dat_0071cfd8.
 * Writes only this recovered DWORD and registers no destructor. Its consumer's
 * subsystem is unresolved; the original initializer-table order remains required.
 * Original entry: 0x6b5a40.
 */
extern "C" void __cdecl initialize_tick_0071cfd8() {
    dat_0071cfd8 = timeGetTime();
}
/**
 * Capture one multimedia-clock sample in dat_0071cfe0.
 * Writes only this recovered DWORD and registers no destructor. Its consumer's
 * subsystem is unresolved; the original initializer-table order remains required.
 * Original entry: 0x6b5a50.
 */
extern "C" void __cdecl initialize_tick_0071cfe0() {
    dat_0071cfe0 = timeGetTime();
}
/**
 * Capture one multimedia-clock sample in dat_0071cfdc.
 * Writes only this recovered DWORD and registers no destructor. Its consumer's
 * subsystem is unresolved; the original initializer-table order remains required.
 * Original entry: 0x6b5a70.
 */
extern "C" void __cdecl initialize_tick_0071cfdc() {
    dat_0071cfdc = timeGetTime();
}
/**
 * Capture one multimedia-clock sample in dat_0071d07c.
 * Writes only this recovered DWORD and registers no destructor. Its consumer's
 * subsystem is unresolved; the original initializer-table order remains required.
 * Original entry: 0x6b5c20.
 */
extern "C" void __cdecl initialize_tick_0071d07c() {
    dat_0071d07c = timeGetTime();
}
/**
 * Capture one multimedia-clock sample in dat_0071d078.
 * Writes only this recovered DWORD and registers no destructor. Its consumer's
 * subsystem is unresolved; the original initializer-table order remains required.
 * Original entry: 0x6b5c30.
 */
extern "C" void __cdecl initialize_tick_0071d078() {
    dat_0071d078 = timeGetTime();
}
/**
 * Capture one multimedia-clock sample in dat_00864e30.
 * Writes only this recovered DWORD and registers no destructor. Its consumer's
 * subsystem is unresolved; the original initializer-table order remains required.
 * Original entry: 0x6b6000.
 */
extern "C" void __cdecl initialize_tick_00864e30() {
    dat_00864e30 = timeGetTime();
}
/**
 * Capture one multimedia-clock sample in dat_00864e80.
 * Writes only this recovered DWORD and registers no destructor. Its consumer's
 * subsystem is unresolved; the original initializer-table order remains required.
 * Original entry: 0x6b6050.
 */
extern "C" void __cdecl initialize_tick_00864e80() {
    dat_00864e80 = timeGetTime();
}
/**
 * Capture one multimedia-clock sample in dat_008655bc.
 * Writes only this recovered DWORD and registers no destructor. Its consumer's
 * subsystem is unresolved; the original initializer-table order remains required.
 * Original entry: 0x6b6420.
 */
extern "C" void __cdecl initialize_tick_008655bc() {
    dat_008655bc = timeGetTime();
}
/**
 * Capture one multimedia-clock sample in dat_008655b8.
 * Writes only this recovered DWORD and registers no destructor. Its consumer's
 * subsystem is unresolved; the original initializer-table order remains required.
 * Original entry: 0x6b6430.
 */
extern "C" void __cdecl initialize_tick_008655b8() {
    dat_008655b8 = timeGetTime();
}
/**
 * Capture one multimedia-clock sample in dat_008655dc.
 * Writes only this recovered DWORD and registers no destructor. Its consumer's
 * subsystem is unresolved; the original initializer-table order remains required.
 * Original entry: 0x6b6480.
 */
extern "C" void __cdecl initialize_tick_008655dc() {
    dat_008655dc = timeGetTime();
}
/**
 * Capture one multimedia-clock sample in dat_008655e0.
 * Writes only this recovered DWORD and registers no destructor. Its consumer's
 * subsystem is unresolved; the original initializer-table order remains required.
 * Original entry: 0x6b6490.
 */
extern "C" void __cdecl initialize_tick_008655e0() {
    dat_008655e0 = timeGetTime();
}
/**
 * Capture one multimedia-clock sample in dat_02207f74.
 * Writes only this recovered DWORD and registers no destructor. Its consumer's
 * subsystem is unresolved; the original initializer-table order remains required.
 * Original entry: 0x6b6d50.
 */
extern "C" void __cdecl initialize_tick_02207f74() {
    dat_02207f74 = timeGetTime();
}
