#pragma once
#include <stdint.h>
#include <stddef.h>

using OriginalVirtualDelete = void*(__attribute__((thiscall)) *)(void*, uint32_t);
struct OriginalPointerList16 {
    const OriginalVirtualDelete* vtable;
    int32_t count;
    uint8_t unknown08;
    uint8_t untouched09[3];
    void** elements;
};
static_assert(sizeof(OriginalPointerList16) == 16 &&
              offsetof(OriginalPointerList16, elements) == 12);
extern "C" {
extern const OriginalVirtualDelete dat_006cca28[1];
OriginalPointerList16* __attribute__((thiscall)) FUN_00554cf0(OriginalPointerList16*);
void __attribute__((thiscall)) FUN_00434c60(OriginalPointerList16*);
void __attribute__((thiscall)) FUN_00554ef0(OriginalPointerList16*);
void* __attribute__((thiscall)) FUN_00554f00(void*, uint32_t flags);
}
