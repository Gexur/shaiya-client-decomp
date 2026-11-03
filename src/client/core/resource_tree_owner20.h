#pragma once
#include "tree48.h"

struct OriginalResourceTreeOwner20;
using ResourceTreeDeleting = OriginalResourceTreeOwner20*(
    __attribute__((thiscall)) *)(OriginalResourceTreeOwner20*, uint32_t);
struct OriginalResourceTreeOwner20 {
    const ResourceTreeDeleting* vtable;
    OriginalTree48Owner12 tree04;
    OriginalTreeNode48* current10;
};
static_assert(sizeof(OriginalResourceTreeOwner20) == 20 &&
              offsetof(OriginalResourceTreeOwner20, current10) == 16);
extern "C" {
extern OriginalResourceTreeOwner20 dat_0220364c;
extern const ResourceTreeDeleting dat_006c582c[1];
void __attribute__((thiscall)) FUN_0052a1c0(OriginalTree48Owner12*, OriginalTreeNode48*);
OriginalTreeNode48** __attribute__((thiscall)) FUN_0052a3f0(OriginalTree48Owner12*,
                                                            OriginalTreeNode48**,
                                                            OriginalTreeNode48*,
                                                            OriginalTreeNode48*);
OriginalTreeNode48** __attribute__((thiscall))
FUN_00529ee0(OriginalTree48Owner12*, OriginalTreeNode48**, OriginalTreeNode48*);
void __attribute__((thiscall)) FUN_0052a5d0(OriginalResourceTreeOwner20*);
void __attribute__((thiscall)) FUN_0052aa70(OriginalTree48Owner12*);
void __attribute__((thiscall)) FUN_0052ab80(OriginalResourceTreeOwner20*);
OriginalResourceTreeOwner20* __attribute__((thiscall)) FUN_0052ac00(OriginalResourceTreeOwner20*,
                                                                    uint32_t);
OriginalResourceTreeOwner20* __attribute__((thiscall)) FUN_0052ac20(OriginalResourceTreeOwner20*);
void __attribute__((thiscall)) FUN_0052ac60(OriginalResourceTreeOwner20*);
void fun_006b6b50();
void fun_006b98b0();
}
