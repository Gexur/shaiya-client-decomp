#pragma once
#include <stdint.h>
#include <stddef.h>

struct OriginalTreeNode24 {
    OriginalTreeNode24* left;
    OriginalTreeNode24* parent;
    OriginalTreeNode24* right;
    uint32_t payload0c, payload10;
    uint8_t color, is_header;
    uint8_t untouched16[2];
};
struct OriginalTree12 {
    uint8_t untouched00[4];
    OriginalTreeNode24* header;
    uint32_t count;
};
static_assert(sizeof(OriginalTreeNode24) == 24 && offsetof(OriginalTreeNode24, color) == 20 &&
              offsetof(OriginalTreeNode24, is_header) == 21);
static_assert(sizeof(OriginalTree12) == 12 && offsetof(OriginalTree12, header) == 4);
extern "C" {
OriginalTreeNode24* FUN_0053a7e0();
OriginalTree12* __attribute__((thiscall)) FUN_0041fcb0(OriginalTree12*);
void __attribute__((thiscall)) FUN_0041f2b0(OriginalTree12*);
void __attribute__((thiscall)) FUN_0041d3f0(OriginalTree12*, OriginalTreeNode24*);
void __attribute__((thiscall)) FUN_00421720(OriginalTree12*, OriginalTreeNode24*);
void __attribute__((thiscall)) FUN_00444130(OriginalTree12*, OriginalTreeNode24*);
OriginalTreeNode24* FUN_00539ea0(OriginalTreeNode24*);
OriginalTreeNode24* FUN_004cc110(OriginalTreeNode24*);
void __attribute__((thiscall)) FUN_00421780(OriginalTreeNode24**);
OriginalTreeNode24** __attribute__((thiscall)) FUN_0041e730(OriginalTree12*, OriginalTreeNode24**,
                                                            OriginalTreeNode24*);
OriginalTreeNode24** __attribute__((thiscall))
FUN_0041ee30(OriginalTree12*, OriginalTreeNode24**, OriginalTreeNode24*, OriginalTreeNode24*);
}
