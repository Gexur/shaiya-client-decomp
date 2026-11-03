#pragma once
#include "exception.h"

using OriginalUnhandledFilter = int32_t(__attribute__((stdcall)) *)(OriginalExceptionPointers*);

extern "C" {
// Original loader-zero DWORD0224EE60; initialization captures the actual OS
// filter pointer and cleanup returns SetUnhandledExceptionFilter's result.
extern OriginalUnhandledFilter dat_0224ee60;
int32_t __attribute__((stdcall)) fun_005d29ec(OriginalExceptionPointers*);
int32_t fun_005d2a3a();
OriginalUnhandledFilter fun_005d2a4d();
}
