#pragma once
#include <stdint.h>

// Original 005a26c0 is a separate entry containing only JMP 005cd564.
// cdecl: one signed descriptor DWORD, full EAX result, caller pops arguments.
extern "C" int32_t FUN_005a26c0(int32_t descriptor);
