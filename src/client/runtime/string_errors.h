#pragma once
#include "../core/string.h"
#include "cxx_dispatch.h"
#include "cxx_typeinfo.h"

struct OriginalErrorVtable {
    void*(__attribute__((thiscall)) * deleting_destructor)(void*, uint32_t);
    const char*(__attribute__((thiscall)) * what)(const void*);
};
struct OriginalExceptionBase {
    const OriginalErrorVtable* vtable;
    char* message;
    uint32_t owns_message;
};
struct OriginalLogicError {
    OriginalExceptionBase base;
    shaiya::startup::String_00405710 text;
};
struct OriginalRttiHierarchy;
struct OriginalRttiTypePrefix {
    const void* vtable;
    void* allocated_name;
};
template <uint32_t Size> struct OriginalRttiType {
    OriginalRttiTypePrefix prefix;
    char name[Size];
};
struct OriginalRttiBase {
    const OriginalRttiTypePrefix* type;
    uint32_t contained_bases;
    CxxPointerDisplacement displacement;
    uint32_t attributes;
};
struct OriginalRttiHierarchy {
    uint32_t signature, attributes, base_count;
    const OriginalRttiBase* const* bases;
};
struct OriginalRttiLocator {
    uint32_t signature, offset, constructor_displacement;
    const OriginalRttiTypePrefix* type;
    const OriginalRttiHierarchy* hierarchy;
};
struct OriginalErrorVtableWithLocator {
    const OriginalRttiLocator* locator;
    OriginalErrorVtable functions;
};
static_assert(sizeof(OriginalErrorVtable) == 8 && sizeof(OriginalExceptionBase) == 12 &&
              sizeof(OriginalLogicError) == 40);
static_assert(offsetof(OriginalLogicError, text) == 12);
static_assert(sizeof(OriginalRttiBase) == 24 && sizeof(OriginalRttiHierarchy) == 16 &&
              sizeof(OriginalRttiLocator) == 20);

extern "C" {
extern const OriginalErrorVtable dat_006d5ef8, dat_006dbc74, dat_006dbc80, dat_006dbc8c;
extern const OriginalRttiLocator dat_006fa2f8;
extern const CxxThrowInfo dat_006fa52c, dat_006fa6dc;
OriginalExceptionBase* __attribute__((thiscall)) fun_005cdd1c(OriginalExceptionBase*);
OriginalExceptionBase* __attribute__((thiscall)) fun_005cdd2d(OriginalExceptionBase*,
                                                              const OriginalExceptionBase*);
void __attribute__((thiscall)) fun_005cdd7f(void*);
const char* __attribute__((thiscall)) fun_005cdd95(const void*);
void* __attribute__((thiscall)) fun_005cdda2(void*, uint32_t);
OriginalLogicError* __attribute__((thiscall)) FUN_0040ad80(OriginalLogicError*,
                                                           const shaiya::startup::String_00405710*);
OriginalLogicError* __attribute__((thiscall)) FUN_0040b040(OriginalLogicError*,
                                                           const OriginalLogicError*);
OriginalLogicError* __attribute__((thiscall)) FUN_0040b0b0(OriginalLogicError*,
                                                           const OriginalLogicError*);
OriginalLogicError* __attribute__((thiscall)) FUN_0040d830(OriginalLogicError*,
                                                           const OriginalLogicError*);
void __attribute__((thiscall)) FUN_0040ab70(void*);
const char* __attribute__((thiscall)) FUN_0040abb0(const void*);
void* __attribute__((thiscall)) FUN_0040d230(void*, uint32_t);
}
