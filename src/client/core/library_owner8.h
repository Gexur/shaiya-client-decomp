#pragma once
#include <stdint.h>
struct OriginalLibraryOwner8;
using OriginalLibraryDeleting =
    OriginalLibraryOwner8*(__attribute__((thiscall)) *)(OriginalLibraryOwner8*, uint32_t);
struct OriginalLibraryOwner8 {
    const OriginalLibraryDeleting* volatile vtable;
    void* volatile module;
};
static_assert(sizeof(OriginalLibraryOwner8) == 8);
extern "C" {
extern const OriginalLibraryDeleting dat_006c5998[1];
// The global IMM cache extends the genuine8-byte library base with four
// GetProcAddress results written by original535ea0 at+8,+c,+10,+14.
struct OriginalImmLibraryOwner24 : OriginalLibraryOwner8 {
    void* volatile procedures[4];
};
static_assert(sizeof(OriginalImmLibraryOwner24) == 24);
static_assert(__builtin_offsetof(OriginalImmLibraryOwner24, procedures) == 8);
extern OriginalImmLibraryOwner24 dat_02207124;
OriginalLibraryOwner8* __attribute__((thiscall)) FUN_00535e70(OriginalLibraryOwner8*);
void __attribute__((thiscall)) FUN_00535e80(OriginalLibraryOwner8*);
OriginalLibraryOwner8* __attribute__((thiscall)) FUN_00535f90(OriginalLibraryOwner8*, uint32_t);
void fun_006b6c90();
void fun_006b9a20();
}
