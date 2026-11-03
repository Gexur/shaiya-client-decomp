#pragma once
#include "atl_modules.h"
struct OriginalAtlWindowClasses44 {
    uint32_t size;
    OriginalCriticalSection critical04;
    uint32_t reserved1c;
    uint16_t* volatile atoms20;
    volatile int32_t count24, capacity28;
};
static_assert(sizeof(OriginalAtlWindowClasses44) == 44);
static_assert(offsetof(OriginalAtlWindowClasses44, atoms20) == 32);
extern "C" {
OriginalAtlWindowClasses44* __attribute__((thiscall)) FUN_0051cd50(OriginalAtlWindowClasses44*);
uint32_t __attribute__((stdcall)) FUN_0051c910(OriginalAtlWindowClasses44*, void* module);
void __attribute__((thiscall)) FUN_0051cda0(OriginalAtlWindowClasses44*);
extern OriginalAtlWindowClasses44 dat_02203414;
void fun_006b6a70();
void fun_006b97b0();
}
