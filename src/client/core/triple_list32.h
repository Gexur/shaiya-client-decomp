#pragma once
#include "pointer_list16.h"

struct OriginalTripleList32 {
    const OriginalVirtualDelete* vtable;
    int32_t first_count, second_count, third_count;
    uint32_t unknown10;
    void** first;
    void** second;
    void** third;
};
static_assert(sizeof(OriginalTripleList32) == 32 && offsetof(OriginalTripleList32, first) == 20 &&
              offsetof(OriginalTripleList32, third) == 28);
extern "C" {
extern const OriginalVirtualDelete dat_006cc9fc[1];
OriginalTripleList32* __attribute__((thiscall)) FUN_00553640(OriginalTripleList32*);
void __attribute__((thiscall)) FUN_00553660(OriginalTripleList32*);
void* __attribute__((thiscall)) FUN_00553670(void*, uint32_t flags);
void __attribute__((thiscall)) FUN_005536a0(OriginalTripleList32*);
// Actual resource field operations; these signatures intentionally do not
// invent a complete class extent beyond the offsets read by each procedure.
void __attribute__((thiscall)) FUN_00550710(void*);
void __attribute__((thiscall)) FUN_005507c0(void*);
void __attribute__((thiscall)) FUN_0053dd40(void*);
}
