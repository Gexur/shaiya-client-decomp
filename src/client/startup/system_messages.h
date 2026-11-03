#pragma once
#include "core/tree24.h"
struct OriginalMessageNode {
    OriginalMessageNode *next, *previous;
    void* payload;
};
struct OriginalMessageList {
    uint32_t opaque;
    OriginalMessageNode* header;
    uint32_t count;
};
struct OriginalMessageOwner {
    OriginalMessageList lists[2];
    uint32_t value18, value1c;
    uint32_t enabled[8];
    uint32_t value40, value44, value48;
};
static_assert(sizeof(OriginalMessageOwner) == 0x4c);
extern "C" {
extern OriginalTree12 dat_0071c1e0;
extern OriginalTreeNode24* dat_0071c1ec;
uint8_t FUN_004373e0(wchar_t*, uint32_t, int32_t);
char* FUN_0046e820(char*, const char*);
void FUN_0041f2e0();
void FUN_0041e1b0();
OriginalMessageOwner* __attribute__((thiscall)) FUN_0041f570(OriginalMessageOwner*);
void __attribute__((thiscall)) FUN_0041e420(OriginalMessageOwner*);
uint32_t* __attribute__((thiscall)) FUN_0041f230(OriginalTree12*, const int32_t*);
}
