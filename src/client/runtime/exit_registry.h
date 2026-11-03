#pragma once
#include <stdint.h>

using OriginalExitCallback = void(__attribute__((cdecl)) *)();
extern "C" {
extern OriginalExitCallback* dat_0225464c;
extern OriginalExitCallback* dat_02254648;
int32_t fun_005ccf00();
// The original private entry receives callback in EDI. This normalized source
// API makes that operand explicit; all recovered callers use this declaration.
OriginalExitCallback fun_005cce80(OriginalExitCallback callback);
OriginalExitCallback fun_005ccf28(OriginalExitCallback callback);
int32_t fun_005ccf60(OriginalExitCallback callback);
void fun_005ccf5a();
void fun_005cdfc9();
void fun_005cdfd2();
int32_t atexit(OriginalExitCallback callback);
uint32_t fun_005d2a5a(void* pointer);
void fun_005d2ac7();
}
