#pragma once
#include <stdint.h>
#include <stddef.h>
using OriginalComLifetimeDelete = void*(__attribute__((thiscall)) *)(void*, uint32_t);
struct OriginalTripleComOwner20 {
    const OriginalComLifetimeDelete* vtable;
    uint32_t state04;
    void* first;
    void* second;
    void* third;
};
struct OriginalSingleComOwner12 {
    const OriginalComLifetimeDelete* vtable;
    uint32_t untouched04;
    void* resource;
};
struct OriginalDoubleComOwner12 {
    const OriginalComLifetimeDelete* vtable;
    void* first;
    void* second;
};
static_assert(sizeof(OriginalTripleComOwner20) == 20 &&
              offsetof(OriginalTripleComOwner20, third) == 16);
static_assert(sizeof(OriginalSingleComOwner12) == 12 && sizeof(OriginalDoubleComOwner12) == 12);
extern "C" {
extern const OriginalComLifetimeDelete dat_006c8624[1], dat_006c9780[1], dat_006c9784[1];
void* __attribute__((thiscall)) FUN_00546d10(void*, uint32_t flags);
void* __attribute__((thiscall)) FUN_00549680(void*, uint32_t flags);
void* __attribute__((thiscall)) FUN_005496c0(void*, uint32_t flags);
}
