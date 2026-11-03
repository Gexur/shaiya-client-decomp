#pragma once
#include <stdint.h>
#include <stddef.h>
#include "locks.h"

struct OriginalIoEntry {
    void* handle;
    uint8_t flags;
    uint8_t lookahead;
    uint8_t untouched_06[2];
    uint32_t section_initialized;
    OriginalCriticalSection section;
};
static_assert(sizeof(OriginalIoEntry) == 36);
static_assert(offsetof(OriginalIoEntry, section) == 12);
extern "C" {
extern int32_t dat_022532d4;
extern OriginalIoEntry* dat_022532e0[64];
int32_t fun_005d591f();
}
