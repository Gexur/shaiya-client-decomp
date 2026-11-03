#pragma once
#include <stdint.h>
extern "C" {
// Actual custom ABI: EAX=output,ECX=packed color; no stack arguments.
// Explicit assembly calls only. EAX stays output; ECX=blue5,EDX=green6.
void FUN_0064f674();
// ECX=16 consecutive16B records; EAX0,ECX+=256,EDX0 on completion.
uint32_t __attribute__((thiscall)) FUN_0064f6c2(void*);
// Actual custom ABI: EAX=source,ECX=destination; no stack arguments.
// Explicit assembly calls only. EAX0,ECX+=256,EDX0 on completion.
uint32_t FUN_0064f746();
}
