#pragma once
#include <stdint.h>
struct OriginalSentinelNode12 {
    OriginalSentinelNode12* next;
    OriginalSentinelNode12* previous;
    uint32_t untouched08;
};
struct OriginalSentinelList12 {
    uint32_t untouched00;
    OriginalSentinelNode12* volatile sentinel04;
    volatile uint32_t count08;
};
static_assert(sizeof(OriginalSentinelNode12) == 12 && sizeof(OriginalSentinelList12) == 12);
extern "C" {
extern OriginalSentinelList12 dat_022032b4;
// The original ignores incoming ECX; this cdecl API has no implicit object.
OriginalSentinelNode12* FUN_004ce840();
void fun_006b6800();
void fun_006b92f0();
}
