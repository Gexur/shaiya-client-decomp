#pragma once
#include <stdint.h>

// The destructor accesses only these two DWORDs. The mangled type name follows
// at+8 in each original variable-length TypeDescriptor.
struct OriginalTypeInfo {
    const void* vtable;
    void* allocated_name;
};
static_assert(sizeof(OriginalTypeInfo) == 8);

extern "C" {
using OriginalTypeInfoDeletingDestructor =
    OriginalTypeInfo*(__attribute__((thiscall)) *)(OriginalTypeInfo*, uint32_t);
extern const OriginalTypeInfoDeletingDestructor dat_006d5f18[1];
void __attribute__((thiscall)) fun_005cddbe(OriginalTypeInfo*);
void fun_005cddfb();
OriginalTypeInfo* __attribute__((thiscall)) fun_005cde04(OriginalTypeInfo*,
                                                         uint32_t deletion_flags);
}
