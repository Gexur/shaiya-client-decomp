#pragma once
#include <stdint.h>

using OriginalCInitializer = int32_t(__attribute__((cdecl)) *)();
using OriginalCppInitializer = void(__attribute__((cdecl)) *)();
using OriginalFloatingInitializer = void(__attribute__((cdecl)) *)(int32_t);

extern "C" {
extern OriginalCppInitializer dat_00708000[312];
extern OriginalCInitializer dat_007084e4[7];
extern OriginalCppInitializer dat_00708504[3], dat_00708514[2];
extern OriginalFloatingInitializer dat_0070e13c;
extern uint64_t dat_0224ee48;

int32_t fun_005cdff3(int32_t floating_precision);
// Original first=EAX, last=stack[4]. All recovered callers use this normalized
// two-argument source interface, retaining the original unsigned range check.
void fun_005cdfdb(OriginalCppInitializer* first, OriginalCppInitializer* last);
int32_t fun_005d15a1();
void fun_005d672e();
void fun_005d6772();

// Type adapters discard the actual return values at these three original
// terminator-table callsites. They are not additional original procedures.
void terminate_stdio_005d0152();
void terminate_temporary_files_006abadc();
void restore_exception_filter_005d2a4d();
}
