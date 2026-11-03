#pragma once
#include <stdint.h>
#include <stddef.h>

// Only the first DWORD of each original 52-byte allocation is interpreted here.
// The remaining bytes are uninitialized by this initializer and unowned by its
// destructor. No payload layout is inferred.
struct OriginalLinkedNode52 {
    OriginalLinkedNode52* next;
    uint8_t untouched04[48];
};
struct OriginalLinkedNodes52 {
    OriginalLinkedNode52* volatile head;
    OriginalLinkedNode52* volatile current;
};
static_assert(sizeof(OriginalLinkedNode52) == 52);
static_assert(sizeof(OriginalLinkedNodes52) == 8);
extern "C" {
void __attribute__((thiscall)) FUN_005b4ec0(OriginalLinkedNodes52*);
extern OriginalLinkedNodes52 dat_0224e6ac;
void fun_006b7740();
void fun_006ba890();
}
