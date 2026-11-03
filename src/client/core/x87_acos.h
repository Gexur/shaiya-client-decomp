#pragma once
#include <stdint.h>
#include "core/x87_pow_private.h"
extern "C" {
extern char s_0070e170[5];
extern const uint64_t dat_006d6b90;
// Only604 has a normal double stack argument. The other entries receive actual
// ST0/EAX/flags or a saved CW on their physical caller stack; calls stay textual.
long double __cdecl FUN_005ce604(double);
void __cdecl FUN_005ce5f0();
void __cdecl FUN_005ce60d();
void __cdecl FUN_005d6a1c();
void __cdecl FUN_005d6a78();
void __cdecl FUN_005d6a9b();
}
