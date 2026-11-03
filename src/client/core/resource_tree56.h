#pragma once
#include "core/string.h"
struct OriginalNestedNode72 {
    OriginalNestedNode72 *left, *parent, *right;
    shaiya::startup::String_00405710 key, value;
    uint8_t color, is_header, untouched46[2];
};
struct OriginalNestedTree72 {
    uint32_t untouched0;
    OriginalNestedNode72* header;
    uint32_t count;
};
struct OriginalNestedPayload40 {
    shaiya::startup::String_00405710 key;
    OriginalNestedTree72 values;
};
struct OriginalNestedNode56 {
    OriginalNestedNode56 *left, *parent, *right;
    OriginalNestedPayload40 payload;
    uint8_t color, is_header, untouched36[2];
};
struct OriginalNestedTree56 {
    uint32_t untouched0;
    OriginalNestedNode56* header;
    uint32_t count;
};
static_assert(sizeof(OriginalNestedNode72) == 72 && offsetof(OriginalNestedNode72, color) == 0x44);
static_assert(sizeof(OriginalNestedNode56) == 56 && offsetof(OriginalNestedNode56, color) == 0x34);
static_assert(sizeof(OriginalNestedPayload40) == 40 && sizeof(OriginalNestedTree56) == 12 &&
              sizeof(OriginalNestedTree72) == 12);
using OriginalNestedDeleting = void*(__attribute__((thiscall)) *)(void*, uint32_t);
extern "C" {
extern const OriginalNestedDeleting dat_006c2690[1];
OriginalNestedNode56* FUN_004c17b0();
OriginalNestedNode56* FUN_004c09c0(OriginalNestedNode56*);
OriginalNestedNode56* FUN_004c09e0(OriginalNestedNode56*);
void __attribute__((thiscall)) FUN_004c0a40(OriginalNestedNode56**);
void __attribute__((thiscall)) FUN_004c0900(OriginalNestedTree56*, OriginalNestedNode56*);
void __attribute__((thiscall)) FUN_004c1440(OriginalNestedTree56*, OriginalNestedNode56*);
OriginalNestedNode72* FUN_004c0a00(OriginalNestedNode72*);
OriginalNestedNode72* FUN_004c0a20(OriginalNestedNode72*);
void __attribute__((thiscall)) FUN_004c0aa0(OriginalNestedNode72**);
void __attribute__((thiscall)) FUN_004c0960(OriginalNestedTree72*, OriginalNestedNode72*);
void __attribute__((thiscall)) FUN_004c14a0(OriginalNestedTree72*, OriginalNestedNode72*);
void __attribute__((thiscall)) FUN_004c17f0(OriginalNestedNode72*);
OriginalNestedNode72** __attribute__((thiscall))
FUN_004c2fe0(OriginalNestedTree72*, OriginalNestedNode72**, OriginalNestedNode72*);
void __attribute__((thiscall)) FUN_004c32e0(OriginalNestedTree72*, OriginalNestedNode72*);
OriginalNestedNode72** __attribute__((thiscall)) FUN_004c3320(OriginalNestedTree72*,
                                                              OriginalNestedNode72**,
                                                              OriginalNestedNode72*,
                                                              OriginalNestedNode72*);
void __attribute__((thiscall)) FUN_004c33e0(OriginalNestedTree72*);
void __attribute__((thiscall)) FUN_004c3410(OriginalNestedPayload40*);
void __attribute__((thiscall)) FUN_004c34a0(OriginalNestedNode56*);
OriginalNestedNode56** __attribute__((thiscall))
FUN_004c34b0(OriginalNestedTree56*, OriginalNestedNode56**, OriginalNestedNode56*);
void __attribute__((thiscall)) FUN_004c3780(OriginalNestedTree56*, OriginalNestedNode56*);
OriginalNestedNode56** __attribute__((thiscall)) FUN_004c37c0(OriginalNestedTree56*,
                                                              OriginalNestedNode56**,
                                                              OriginalNestedNode56*,
                                                              OriginalNestedNode56*);
void __attribute__((thiscall)) FUN_004c3880(OriginalNestedTree56*);
void __attribute__((thiscall)) FUN_004c38b0(void*);
void* __attribute__((thiscall)) FUN_004c3930(void*);
void* __attribute__((thiscall)) FUN_004c3970(void*, uint32_t);
void __attribute__((thiscall)) FUN_005c0050(void*);
}
