#pragma once
#include "tree48.h"
#include "pointer_list16.h"

struct OriginalManagedElement16 {
    void* first;
    void* second;
    void* third;
    uint32_t untouched0c;
};
struct OriginalResourceManager24 {
    uint32_t untouched00, untouched04;
    OriginalTree48Owner12 tree;
    OriginalTreeNode48* cursor;
};
static_assert(sizeof(OriginalManagedElement16) == 16 && sizeof(OriginalResourceManager24) == 24 &&
              offsetof(OriginalResourceManager24, tree) == 8);
extern "C" {
extern OriginalResourceManager24 dat_02221c00, dat_02221c18;
void __attribute__((thiscall)) FUN_0040a8b0(void*);
void __attribute__((thiscall)) FUN_00434df0(OriginalManagedElement16**);
void __attribute__((thiscall)) FUN_00434e20(void*);
int32_t __attribute__((thiscall)) FUN_00557b10(void*);
int32_t __attribute__((thiscall)) FUN_0053dd10(void*);
void __attribute__((thiscall)) FUN_0054b6d0(OriginalResourceManager24*, void*);
void __attribute__((thiscall)) FUN_0054b650(OriginalResourceManager24*, void*);
}
