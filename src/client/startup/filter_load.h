#pragma once
#include "core/filter_owner.h"
#include "core/string.h"
struct OriginalFilterText {
    shaiya::startup::String_00405710 string;
    uint32_t hash;
    uint32_t flags;
};
struct OriginalFilterNode {
    OriginalFilterNode *next, *previous;
    OriginalFilterText* value;
};
struct OriginalFilterList {
    uint32_t opaque;
    OriginalFilterNode* header;
    uint32_t count;
};
struct OriginalFilterRecord {
    uint32_t buckets_count, opaque;
    OriginalFilterList** buckets;
    uint32_t end, capacity_end;
    OriginalFilterList* current_list;
    OriginalFilterNode* current_node;
    OriginalFilterText* current_entry;
};
static_assert(sizeof(OriginalFilterText) == 0x24 && sizeof(OriginalFilterRecord) == 0x20);
extern "C" {
uint8_t __attribute__((thiscall)) FUN_0040bb10(OriginalFilterOwner12*, const char*);
uint8_t __attribute__((thiscall)) FUN_0040ba20(OriginalFilterOwner12*, const char*,
                                               OriginalFilterText*);
uint8_t __attribute__((thiscall)) FUN_0040ac50(OriginalFilterRecord*, const char*,
                                               OriginalFilterText**);
void __attribute__((thiscall)) FUN_0040b8e0(OriginalFilterRecord*, const char*,
                                            OriginalFilterText*);
OriginalFilterText* __attribute__((thiscall)) FUN_0040b250(OriginalFilterText*, const char*,
                                                           uint32_t);
}
