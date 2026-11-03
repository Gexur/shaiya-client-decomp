#pragma once
#include "com_resource.h"
struct OriginalResourceArrayOwner492;
using OriginalResourceArrayDeleting = OriginalResourceArrayOwner492*(
    __attribute__((thiscall)) *)(OriginalResourceArrayOwner492*, uint32_t);
struct OriginalResourceLeaf4 {
    OriginalComObject* resource;
};
struct OriginalResourceArrayOwner492 {
    const OriginalResourceArrayDeleting* vtable;
    OriginalResourcePair base04;
    OriginalResourcePair first14[5], second64[5];
    int32_t half_width_b4, half_height_b8;
    uint32_t valuebc;
    uint8_t statec0, statec1, untouchedc2[30];
    OriginalResourceLeaf4* extrae0;
    uint32_t untouchede4, zerose8[65];
};
static_assert(sizeof(OriginalResourceArrayOwner492) == 492);
static_assert(offsetof(OriginalResourceArrayOwner492, first14) == 0x14 &&
              offsetof(OriginalResourceArrayOwner492, second64) == 0x64);
static_assert(offsetof(OriginalResourceArrayOwner492, extrae0) == 0xe0 &&
              offsetof(OriginalResourceArrayOwner492, zerose8) == 0xe8);
extern "C" {
extern const OriginalResourceArrayDeleting dat_006bcb94[1];
extern OriginalResourceArrayOwner492 dat_0071c1f0;
OriginalResourceArrayOwner492* __attribute__((thiscall))
FUN_00420350(OriginalResourceArrayOwner492*);
void __attribute__((thiscall)) FUN_0041ff30(OriginalResourceArrayOwner492*);
void __attribute__((thiscall)) FUN_00420420(OriginalResourceArrayOwner492*);
OriginalResourceArrayOwner492* __attribute__((thiscall))
FUN_004204c0(OriginalResourceArrayOwner492*, uint32_t);
void fun_006b5830();
void fun_006b7d40();
// Typed integration adapters discard the actual pair constructor's return.
void __attribute__((thiscall)) resource_pair_construct(void*);
void __attribute__((thiscall)) resource_pair_destroy(void*);
}
