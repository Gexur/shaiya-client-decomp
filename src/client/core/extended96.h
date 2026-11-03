#pragma once
#include <stdint.h>
struct OriginalExtended96 {
    uint32_t words[3];
};
static_assert(sizeof(OriginalExtended96) == 12);
extern "C" {
int32_t fun_005e0491(uint32_t left, uint32_t right, uint32_t* output);
int32_t fun_005e04b2(OriginalExtended96*, const OriginalExtended96*);
OriginalExtended96* fun_005e0510(OriginalExtended96*);
OriginalExtended96* fun_005e053e(OriginalExtended96*);
void fun_005e0ca4(OriginalExtended96*, const OriginalExtended96*);
void fun_005e0eda(OriginalExtended96*, int32_t power, int32_t keep_guard);
extern const OriginalExtended96 dat_0070f0b0[29], dat_0070f210[29];
}
