#include "close_entry.h"
#include "runtime/descriptor_io.h"

// Original bytes E9 9F AE 02 00 tail-enter the canonical close procedure.
// No additional frame, validation, finally, or duplicate close body exists here.
extern "C" __attribute__((naked)) int32_t FUN_005a26c0(int32_t) {
    __asm__ volatile("jmp _fun_005cd564");
}
