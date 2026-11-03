#pragma once
#include "resource_manager.h"
#include "tree48_lifetime.h"
// This exact20-byte original base view also occupies bytes4..23 of the
// canonical24-byte manager; alias qualification retains that representation.
struct __attribute__((may_alias)) OriginalResourceManagerBase20 {
    const OriginalVirtualDelete* vtable;
    OriginalTree48Owner12 tree;
    OriginalTreeNode48* cursor;
};
static_assert(sizeof(OriginalResourceManagerBase20) == 20 &&
              offsetof(OriginalResourceManagerBase20, tree) == 4);
extern "C" {
extern const OriginalVirtualDelete dat_006ccb4c[1], dat_006ccb50[1], dat_006ccb54[1],
    dat_006ccb58[1];
void __attribute__((thiscall)) FUN_004351c0(OriginalResourceManagerBase20*);
void __attribute__((thiscall)) FUN_00435220(OriginalResourceManagerBase20*);
void __attribute__((thiscall)) FUN_0055a210(OriginalResourceManagerBase20*);
void __attribute__((thiscall)) FUN_0055a290(OriginalResourceManagerBase20*);
void* __attribute__((thiscall)) FUN_0055a310(void*, uint32_t);
void* __attribute__((thiscall)) FUN_0055a330(void*, uint32_t);
OriginalResourceManager24* __attribute__((thiscall)) FUN_0055a350(OriginalResourceManager24*);
OriginalResourceManager24* __attribute__((thiscall)) FUN_0055a410(OriginalResourceManager24*);
void __attribute__((thiscall)) FUN_0055a390(OriginalResourceManager24*);
void __attribute__((thiscall)) FUN_0055a450(OriginalResourceManager24*);
void* __attribute__((thiscall)) FUN_0055a3f0(void*, uint32_t);
void* __attribute__((thiscall)) FUN_0055a4b0(void*, uint32_t);
}
