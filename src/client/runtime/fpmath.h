#pragma once
#include <stdint.h>

// These six slots store original routine addresses. Their individual formatter
// call signatures are still unresolved; they are never called through this
// opaque address type. No successful formatter implementation is substituted.
using FloatingRoutineAddress = void(__cdecl*)();
extern "C" {
// Canonical definition remains core/x87_runtime.cpp; this header also serves
// MSVC-target SEH units, whose long-double C type is only eight bytes.
extern uint32_t dat_022532cc;
extern FloatingRoutineAddress dat_0070e500, dat_0070e504, dat_0070e508;
extern FloatingRoutineAddress dat_0070e50c, dat_0070e510, dat_0070e514;
extern uint32_t dat_0224ede0, dat_022532d0;
void __cdecl fun_005ccf72();
void __cdecl fun_005ccfaa(int32_t);
int32_t __cdecl fun_005d7e84();
int32_t __cdecl fun_005d7e4f();
void __cdecl fun_005d2f29();
int32_t __cdecl fun_005d2f3b();
int32_t __cdecl fun_005d2f7b();
uint32_t __cdecl fun_005dd039(uint32_t, uint32_t);
uint32_t __cdecl fun_005dd06b(uint32_t, uint32_t);
void __cdecl fun_005dcf10();
// Public spellings retain original EBX/BX entry contracts.
uint32_t __cdecl fun_005dcf19();
uint32_t __cdecl fun_005dcfab();
}
