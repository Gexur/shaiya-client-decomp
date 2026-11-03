#pragma once
#include "atl_modules.h"
struct OriginalAtlBase44;
struct OriginalAtlCallback12 {
    void(__attribute__((stdcall)) * callback)(void*);
    void* argument;
    OriginalAtlCallback12* next;
};
struct OriginalAtlBase36 {
    uint32_t size;
    volatile int32_t references;
    OriginalAtlCallback12* volatile callbacks;
    OriginalCriticalSection critical;
};
struct OriginalAtlBase44Table {
    OriginalAtlBase44*(__attribute__((thiscall)) * deleting)(OriginalAtlBase44*, uint32_t);
    int32_t(__attribute__((thiscall)) * increment)(OriginalAtlBase44*);
    int32_t(__attribute__((thiscall)) * decrement)(OriginalAtlBase44*);
    int32_t(__attribute__((thiscall)) * references)(OriginalAtlBase44*);
};
struct OriginalAtlBase44 {
    const OriginalAtlBase44Table* vtable;
    OriginalAtlBase36 base04;
    void* resource28;
};
static_assert(sizeof(OriginalAtlCallback12) == 12 && sizeof(OriginalAtlBase36) == 36 &&
              sizeof(OriginalAtlBase44) == 44);
static_assert(offsetof(OriginalAtlBase44, resource28) == 40);
extern "C" {
extern const OriginalAtlBase44Table dat_006c4db0;
extern OriginalAtlBase44 dat_0220339c;
extern OriginalAtlBase44* volatile dat_022033d4;
extern OriginalAtlBase44* volatile dat_022033e8;
OriginalAtlBase44* __attribute__((thiscall)) FUN_0051cbe0(OriginalAtlBase44*);
void __attribute__((stdcall)) FUN_0051ab00(OriginalAtlBase36*);
void __attribute__((thiscall)) FUN_0051c8b0(OriginalAtlBase44*);
void __attribute__((thiscall)) FUN_0051c900(OriginalAtlBase44*);
OriginalAtlBase44* __attribute__((thiscall)) FUN_0051ccf0(OriginalAtlBase44*, uint32_t);
int32_t __attribute__((thiscall)) FUN_0051cc40(OriginalAtlBase44*);
int32_t __attribute__((thiscall)) FUN_0051cc50(OriginalAtlBase44*);
int32_t __attribute__((thiscall)) FUN_0051cc60(OriginalAtlBase44*);
void fun_006b6ab0();
void fun_006b97a0();
}
