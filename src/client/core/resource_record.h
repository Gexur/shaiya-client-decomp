#pragma once
#include "com_resource.h"
struct OriginalArrayElement {
    void* first;
    void* second;
    uint32_t unknown08;
};
struct OriginalResourceRecord {
    OriginalComObject* first;
    OriginalComObject* second;
    uint32_t unknown08, unknown0c, unknown10;
    OriginalArrayElement* elements;
    uint32_t unknown18, unknown1c, unknown20;
    uint8_t untouched24[0x104];
    uint16_t state128, untouched12a;
};
static_assert(sizeof(OriginalArrayElement) == 12);
static_assert(sizeof(OriginalResourceRecord) == 0x12c);
static_assert(offsetof(OriginalResourceRecord, elements) == 0x14);
static_assert(offsetof(OriginalResourceRecord, state128) == 0x128);
extern "C" {
void __attribute__((thiscall)) FUN_0040a900(void*);
void __attribute__((thiscall)) FUN_0040efb0(OriginalArrayElement**);
OriginalResourceRecord* __attribute__((thiscall)) FUN_0040efe0(OriginalResourceRecord*);
void __attribute__((thiscall)) FUN_0040f010(OriginalResourceRecord*);
}
