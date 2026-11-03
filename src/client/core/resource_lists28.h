#pragma once
#include "pointer_list16.h"
#include "resource_record.h"

struct OriginalResourceLists28 {
    const OriginalVirtualDelete* vtable;
    int32_t first_count, second_count, third_count;
    OriginalResourceRecord** first;
    void** second;
    void** third;
};
static_assert(sizeof(OriginalResourceLists28) == 28 &&
              offsetof(OriginalResourceLists28, first) == 16);
extern "C" {
extern const OriginalVirtualDelete dat_006ccb18[1];
void __attribute__((thiscall)) FUN_00556890(OriginalResourceRecord*);
OriginalResourceLists28* __attribute__((thiscall)) FUN_00556cd0(OriginalResourceLists28*);
void __attribute__((thiscall)) FUN_00435010(OriginalResourceLists28*);
void __attribute__((thiscall)) FUN_005571c0(OriginalResourceLists28*);
void* __attribute__((thiscall)) FUN_005571d0(void*, uint32_t flags);
}
