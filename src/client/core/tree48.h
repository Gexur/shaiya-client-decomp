#pragma once
#include "string.h"
#include <stdint.h>
#include <stddef.h>

struct OriginalTreeNode48 {
    OriginalTreeNode48* left;
    OriginalTreeNode48* parent;
    OriginalTreeNode48* right;
    shaiya::startup::String_00405710 key;
    void* value;
    uint8_t color, is_header, untouched2e, untouched2f;
};
struct OriginalTree48Owner12 {
    uint32_t untouched00;
    OriginalTreeNode48* header;
    uint32_t count;
};
static_assert(sizeof(OriginalTreeNode48) == 48 && offsetof(OriginalTreeNode48, key) == 12 &&
              offsetof(OriginalTreeNode48, value) == 40 &&
              offsetof(OriginalTreeNode48, color) == 44);
static_assert(sizeof(OriginalTree48Owner12) == 12);
extern "C" {
OriginalTreeNode48* FUN_005b8a00(OriginalTreeNode48*);
OriginalTreeNode48* FUN_0054afd0(OriginalTreeNode48*);
void __attribute__((thiscall)) FUN_005b8a60(OriginalTreeNode48**);
void __attribute__((thiscall)) FUN_0054aff0(OriginalTree48Owner12*, OriginalTreeNode48*);
void __attribute__((thiscall)) FUN_0054af70(OriginalTree48Owner12*, OriginalTreeNode48*);
OriginalTreeNode48** __attribute__((thiscall))
FUN_0054b270(OriginalTree48Owner12*, OriginalTreeNode48**, OriginalTreeNode48*);
}
