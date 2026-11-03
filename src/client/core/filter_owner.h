#pragma once
#include <stdint.h>
struct OriginalFilterPointerVector {
    uint32_t opaque_prefix;
    uint32_t* begin;
    uint32_t* end;
    uint32_t* capacity_end;
};
struct OriginalFilterOwner12 {
    uint32_t count;
    uint32_t state;
    void* records;
};
static_assert(sizeof(OriginalFilterPointerVector) == 16, "observed vector prefix");
static_assert(sizeof(OriginalFilterOwner12) == 12, "only original owner words0/4/8");
extern "C" {
extern OriginalFilterOwner12 dat_0071cff0;
uint32_t __attribute__((thiscall)) FUN_00437640(OriginalFilterPointerVector*, uint32_t, uint32_t,
                                                uint32_t);
uint32_t __attribute__((thiscall)) FUN_00437820(void*, uint32_t, uint32_t);
void __attribute__((thiscall)) FUN_00437480(void*);
uint32_t __attribute__((thiscall)) FUN_00555f30(void*);
void __attribute__((thiscall)) FUN_004378b0(void*);
OriginalFilterOwner12* __attribute__((thiscall)) FUN_00437910(OriginalFilterOwner12*);
__attribute__((thiscall, noreturn)) void FUN_004375d0(void*);
void fun_006b5bc0();
void fun_006b8210();
}
