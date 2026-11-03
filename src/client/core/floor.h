#pragma once
#include "core/x87_runtime.h"
extern "C" {
// Each original entry is cdecl(double stack argument),RET0 and actual80bitST0.
// SIMD kernel may overwrite the caller's actual8argumentbytes; fallback's
// classification MOV reads4bytes at argument+6, including2adjacentbytes.
long double __cdecl FUN_006aa710(double);
long double __cdecl FUN_006aa750(double);
long double __cdecl FUN_006ab0bf(double);
}
