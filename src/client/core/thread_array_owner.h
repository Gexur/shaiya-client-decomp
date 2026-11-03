#pragma once
#include "pointer_list16.h"

struct OriginalNestedElement280 {
    uint8_t untouched00[0x10c];
    void* first;
    void* second;
    uint32_t untouched114;
};
struct OriginalThreadChild304 {
    uint32_t untouched00, untouched04;
    OriginalNestedElement280* elements;
    uint8_t untouched0c[0x120];
    uint32_t state12c;
};
struct OriginalThreadArrayOwner32 {
    const OriginalVirtualDelete* vtable;
    int32_t count;
    uint32_t unknown08;
    uint8_t flags0c[3], untouched0f;
    void* thread;
    uint32_t state14;
    OriginalThreadChild304** items;
    uint16_t state1c, untouched1e;
};
static_assert(sizeof(OriginalNestedElement280) == 0x118 &&
              offsetof(OriginalNestedElement280, first) == 0x10c);
static_assert(sizeof(OriginalThreadChild304) == 0x130 &&
              offsetof(OriginalThreadChild304, state12c) == 0x12c);
static_assert(sizeof(OriginalThreadArrayOwner32) == 32 &&
              offsetof(OriginalThreadArrayOwner32, thread) == 16 &&
              offsetof(OriginalThreadArrayOwner32, items) == 24);
extern "C" {
extern const OriginalVirtualDelete dat_006cc9f8[1];
void __attribute__((thiscall)) FUN_00551ff0(void*);
OriginalThreadChild304* __attribute__((thiscall)) FUN_00552030(OriginalThreadChild304*,
                                                               uint32_t flags);
void __attribute__((thiscall)) FUN_00552090(OriginalThreadArrayOwner32*);
void __attribute__((thiscall)) FUN_00552560(OriginalThreadArrayOwner32*);
OriginalThreadArrayOwner32* __attribute__((thiscall)) FUN_005535d0(OriginalThreadArrayOwner32*);
void __attribute__((thiscall)) FUN_00553600(OriginalThreadArrayOwner32*);
void* __attribute__((thiscall)) FUN_00553610(void*, uint32_t flags);
}
