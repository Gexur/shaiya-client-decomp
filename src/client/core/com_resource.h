#pragma once
#include <stdint.h>
#include <stddef.h>
struct OriginalComObject;
struct OriginalResourcePair {
    OriginalComObject* first;
    OriginalComObject* second;
    uint32_t unknown08, unknown0c;
};
static_assert(sizeof(OriginalResourcePair) == 16);
static_assert(offsetof(OriginalResourcePair, second) == 4);
extern "C" {
OriginalResourcePair* __attribute__((thiscall)) FUN_0041fef0(OriginalResourcePair*);
void __attribute__((thiscall)) FUN_0041ff00(OriginalResourcePair*);
}
