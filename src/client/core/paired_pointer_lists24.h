#pragma once
#include "pointer_list16.h"
struct OriginalPairedPointerLists24 {
    const OriginalVirtualDelete* vtable;
    void** first;
    void** second;
    void** third;
    int32_t paired_count, third_count;
};
static_assert(sizeof(OriginalPairedPointerLists24) == 24 &&
              offsetof(OriginalPairedPointerLists24, paired_count) == 16);
extern "C" {
extern const OriginalVirtualDelete dat_006ccb64[1];
uint32_t __attribute__((thiscall)) FUN_0055ab50(OriginalPairedPointerLists24*);
void* __attribute__((thiscall)) FUN_0055aec0(void*, uint32_t flags);
}
