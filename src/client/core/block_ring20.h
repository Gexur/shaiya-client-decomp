#pragma once
#include <stdint.h>
#include <stddef.h>
struct OriginalBlockRing20 {
    uint32_t untouched00;
    void** volatile blocks;
    volatile uint32_t capacity, start, count;
};
static_assert(sizeof(OriginalBlockRing20) == 20);
static_assert(offsetof(OriginalBlockRing20, count) == 16);
extern "C" {
OriginalBlockRing20* __attribute__((thiscall)) FUN_00421f70(OriginalBlockRing20*);
void __attribute__((thiscall)) FUN_00421990(OriginalBlockRing20*);
void __attribute__((thiscall)) FUN_00421a30(OriginalBlockRing20*);
extern OriginalBlockRing20 dat_0071c548;
void fun_006b58d0();
void fun_006b7e40();
}
