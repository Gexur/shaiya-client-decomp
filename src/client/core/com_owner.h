#pragma once
#include <stdint.h>
#include <stddef.h>
struct OriginalComObject;
struct OriginalComOwner;
struct OriginalComOwnerVtable {
    OriginalComOwner*(__attribute__((thiscall)) * deleting_destructor)(OriginalComOwner*, uint32_t);
};
struct OriginalComOwner {
    const OriginalComOwnerVtable* vtable;
    OriginalComObject* resource;
};
struct OriginalComBuffer {
    OriginalComOwner owner;
    uint8_t untouched08[0x104];
    uint16_t state10c, untouched10e;
};
static_assert(sizeof(OriginalComOwner) == 8);
static_assert(sizeof(OriginalComBuffer) == 0x110);
static_assert(offsetof(OriginalComBuffer, state10c) == 0x10c);
extern "C" {
extern const OriginalComOwnerVtable dat_006bc858;
void __attribute__((thiscall)) FUN_0040ef00(OriginalComOwner*);
OriginalComOwner* __attribute__((thiscall)) FUN_0040ef20(OriginalComOwner*, uint32_t);
OriginalComBuffer* __attribute__((thiscall)) FUN_0040e590(OriginalComBuffer*);
}
