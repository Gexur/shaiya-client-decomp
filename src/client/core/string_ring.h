#pragma once
#include "string.h"
// Actual observed20-byte prefix used by0040ADE0; the first DWORD is untouched.
struct OriginalStringRing20 {
    uint32_t undecoded00;
    shaiya::startup::String_00405710** blocks;
    uint32_t capacity, start, count;
};
static_assert(sizeof(OriginalStringRing20) == 20);
extern "C" void __attribute__((thiscall)) FUN_0040ade0(OriginalStringRing20*);
