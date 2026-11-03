#pragma once
#include "tree48.h"
// Original0054B050 lower-bound and0054B170 exact lookup, both thiscall.
extern "C" {
OriginalTreeNode48* __attribute__((thiscall)) FUN_0054b050(OriginalTree48Owner12*,
                                                           const shaiya::startup::String_00405710*);
OriginalTreeNode48** __attribute__((thiscall))
FUN_0054b170(OriginalTree48Owner12*, OriginalTreeNode48**, shaiya::startup::String_00405710*);
}
