#pragma once
#include "../runtime/locks.h"
#include <stddef.h>
struct OriginalAtlComEntry {
    uint8_t undecoded_00[16];
    void* factory;
};
struct OriginalAtlComModule {
    uint32_t size;
    void* module;
    OriginalAtlComEntry** begin;
    OriginalAtlComEntry** end;
    OriginalCriticalSection critical;
};
struct OriginalAtlList {
    void* allocation;
    uint32_t count, capacity;
};
struct OriginalAtlGuid {
    uint32_t first;
    uint16_t second, third;
    uint8_t last[8];
};
struct OriginalAtlModule {
    uint32_t size;
    void* module;
    void* resource_module;
    uint8_t version_flag;
    uint8_t untouched_0d[3];
    uint32_t version;
    const OriginalAtlGuid* identifier;
    OriginalCriticalSection critical;
    OriginalAtlList list;
};
static_assert(sizeof(OriginalAtlComModule) == 40 && sizeof(OriginalAtlModule) == 60);
static_assert(offsetof(OriginalAtlComModule, critical) == 16 &&
              offsetof(OriginalAtlModule, critical) == 24 &&
              offsetof(OriginalAtlModule, list) == 48);
static_assert(sizeof(OriginalAtlGuid) == 16);
extern "C" {
extern OriginalAtlComEntry* dat_00705c48;
extern const OriginalAtlGuid dat_006dbccc;
extern uint8_t dat_022033ec;
OriginalCriticalSection* __attribute__((thiscall)) fun_0051a7a0(OriginalCriticalSection*);
int32_t __attribute__((thiscall)) fun_0051a7c0(OriginalCriticalSection*);
void __attribute__((thiscall)) fun_005e1991(OriginalAtlComModule*);
OriginalAtlComModule* __attribute__((thiscall)) fun_005e19d3(OriginalAtlComModule*);
void __attribute__((thiscall)) fun_005e1a13(OriginalAtlList*);
OriginalAtlModule* __attribute__((thiscall)) fun_005e1a30(OriginalAtlModule*);
void __attribute__((thiscall)) fun_005e1a4a(OriginalAtlModule*);
OriginalAtlModule* __attribute__((thiscall)) fun_005e1a60(OriginalAtlModule*);
}
