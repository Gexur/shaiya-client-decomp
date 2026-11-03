#pragma once
#include "pointer_list16.h"

struct OriginalPointerRange20 {
    uint32_t untouched00, untouched04;
    void** begin;
    void** end;
    void** capacity;
};
struct OriginalPointerRanges60 {
    OriginalPointerRange20 first, second, third;
};
struct OriginalPayloadRanges84 {
    const OriginalVirtualDelete* vtable;
    uint32_t state04, state08, state0c;
    int32_t payload_count;
    OriginalPointerRanges60 ranges;
    void** payloads;
};
static_assert(sizeof(OriginalPointerRange20) == 20 && sizeof(OriginalPointerRanges60) == 60 &&
              sizeof(OriginalPayloadRanges84) == 84);
static_assert(offsetof(OriginalPayloadRanges84, ranges) == 20 &&
              offsetof(OriginalPayloadRanges84, payloads) == 80);
extern "C" {
extern const OriginalVirtualDelete dat_006cd3dc[1];
void __attribute__((thiscall)) FUN_00585290(OriginalPointerRanges60*);
uint32_t __attribute__((thiscall)) FUN_005852f0(OriginalPayloadRanges84*);
void __attribute__((thiscall)) FUN_00585440(OriginalPayloadRanges84*);
void* __attribute__((thiscall)) FUN_00585500(void*, uint32_t flags);
OriginalPayloadRanges84* __attribute__((thiscall)) FUN_00585700(OriginalPayloadRanges84*);
}
