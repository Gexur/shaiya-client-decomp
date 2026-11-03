#pragma once
#include <stdint.h>
#include <stddef.h>

namespace shaiya::startup {
// Actual x86 representation already shared by application/render recovery.
// The first four bytes remain opaque; storage holds inline bytes or a pointer.
struct String_00405710 {
    unsigned char unknown_000[4];
    unsigned char storage_004[16];
    uint32_t size_014;
    uint32_t capacity_018;
};
static_assert(sizeof(String_00405710) == 0x1c);
static_assert(offsetof(String_00405710, storage_004) == 4);
static_assert(offsetof(String_00405710, size_014) == 0x14);
static_assert(offsetof(String_00405710, capacity_018) == 0x18);
} // namespace shaiya::startup

extern "C" {
shaiya::startup::String_00405710* __attribute__((thiscall))
FUN_00405460(shaiya::startup::String_00405710*, uint32_t position, uint32_t count);
unsigned char* __attribute__((thiscall)) FUN_004054e0(shaiya::startup::String_00405710*,
                                                      uint32_t requested, uint32_t old_size);
// Original shared tail0040557C consumes ESI=self, EDX=new_storage, EBX=capacity
// and old_size from its enclosing EBP+0xc; the normalized inputs are explicit.
unsigned char* FUN_0040557c(shaiya::startup::String_00405710*, unsigned char* new_storage,
                            uint32_t capacity, uint32_t old_size);
shaiya::startup::String_00405710* __attribute__((thiscall))
FUN_00405620(shaiya::startup::String_00405710*, const shaiya::startup::String_00405710*,
             uint32_t position, uint32_t count);
shaiya::startup::String_00405710* __attribute__((thiscall))
FUN_00405710(shaiya::startup::String_00405710*, const char*, uint32_t count);
shaiya::startup::String_00405710* __attribute__((thiscall))
FUN_00405800(shaiya::startup::String_00405710*, const char*);
uint32_t __attribute__((thiscall)) FUN_00529db0(shaiya::startup::String_00405710*);

// Actual length/range-error construction helpers remain explicit dependencies
// until their exception-object/vtable closures have also been recovered.
[[noreturn]] void FUN_005e1911();
[[noreturn]] void __attribute__((thiscall)) FUN_005e1951(shaiya::startup::String_00405710*);
}
