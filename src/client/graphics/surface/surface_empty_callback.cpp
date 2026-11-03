#include "graphics/surface/surface_empty_callback.h"

// Original 0x0069dae1 is exactly one RET instruction. The next routine starts
// at 0x0069dae2. Five original surface vtables use this shared empty callback.
// A compiler-generated frame would add scratch-stack writes absent originally.
extern "C" __attribute__((naked)) void FUN_0069dae1() {
    __asm__ volatile("retl");
}
