#pragma once
#include <stdint.h>
#include <stddef.h>
// These are the spans directly accessed by the original cleanup. Allocation
// requests and any larger payload layouts are not inferred from those spans.
struct OriginalTenPointers48 {
    uint8_t untouched00[8];
    void* volatile pointers08[10];
};
struct OriginalPointerTable4004 {
    uint32_t untouched00;
    OriginalTenPointers48* volatile blocks04[1000];
};
struct OriginalPointerTableOwner4 {
    OriginalPointerTable4004* volatile resource;
};
static_assert(sizeof(OriginalTenPointers48) == 48);
static_assert(sizeof(OriginalPointerTable4004) == 4004);
static_assert(sizeof(OriginalPointerTableOwner4) == 4);
extern "C" {
OriginalPointerTableOwner4* __attribute__((thiscall)) FUN_00520550(OriginalPointerTableOwner4*);
void __attribute__((thiscall)) FUN_00530c10(OriginalPointerTable4004*);
void __attribute__((thiscall)) FUN_00531550(OriginalPointerTableOwner4*);
extern OriginalPointerTableOwner4 dat_0071d0e0, dat_0071d0e4, dat_0071d0e8, dat_0071d0ec;
void fun_006b5c80();
void fun_006b5ca0();
void fun_006b5cc0();
void fun_006b5ce0();
void fun_006b82a0();
void fun_006b82b0();
void fun_006b82c0();
void fun_006b82d0();
}
