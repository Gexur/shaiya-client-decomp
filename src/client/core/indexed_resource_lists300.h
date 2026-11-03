#pragma once
#include "pointer_list16.h"
struct OriginalIndexedResourceLists300 {
    const OriginalVirtualDelete* vtable;
    int32_t first_count, second_count, third_count, fourth_count;
    void* owned14;
    void** first;
    void** second;
    void** third;
    void** fourth;
    uint32_t table28[65];
};
static_assert(sizeof(OriginalIndexedResourceLists300) == 300 &&
              offsetof(OriginalIndexedResourceLists300, table28) == 40);
extern "C" {
extern const OriginalVirtualDelete dat_006cca24[1];
OriginalIndexedResourceLists300* __attribute__((thiscall))
FUN_00554ca0(OriginalIndexedResourceLists300*);
void __attribute__((thiscall)) FUN_005580d0(OriginalIndexedResourceLists300*);
void __attribute__((thiscall)) FUN_00421570(OriginalIndexedResourceLists300*);
void __attribute__((thiscall)) FUN_00554d10(OriginalIndexedResourceLists300*);
void* __attribute__((thiscall)) FUN_00554d20(void*, uint32_t flags);
}
