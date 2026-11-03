#pragma once
#include <stdint.h>
#include <stddef.h>
struct OriginalQueueNode8 {
    void* payload;
    OriginalQueueNode8* next;
};
struct OriginalPoolNode12 {
    void* payload;
    OriginalPoolNode12* previous;
    OriginalPoolNode12* next;
};
struct OriginalFreeNodes8 {
    OriginalQueueNode8* head;
    OriginalQueueNode8* tail;
};
struct OriginalFreeNodes12 {
    OriginalPoolNode12* head;
    OriginalPoolNode12* tail;
};
struct OriginalPayloadQueue16 {
    OriginalFreeNodes8 free;
    OriginalQueueNode8* head;
    OriginalQueueNode8* cursor;
};
struct OriginalPayloadPool28 {
    OriginalPoolNode12 sentinel;
    OriginalPoolNode12* cursor;
    OriginalFreeNodes12 free;
    uint32_t count;
};
static_assert(sizeof(OriginalQueueNode8) == 8 && sizeof(OriginalPoolNode12) == 12 &&
              sizeof(OriginalPayloadQueue16) == 16 && sizeof(OriginalPayloadPool28) == 28);
static_assert(offsetof(OriginalPayloadPool28, free) == 0x10 &&
              offsetof(OriginalPayloadPool28, count) == 0x18);
extern "C" {
void __attribute__((thiscall)) FUN_004442c0(OriginalFreeNodes12*);
void __attribute__((thiscall)) FUN_00444300(OriginalFreeNodes8*);
void __attribute__((thiscall)) FUN_005af1a0(OriginalPayloadPool28*);
void __attribute__((thiscall)) FUN_00446d60(OriginalPayloadPool28*);
void __attribute__((thiscall)) FUN_00446080(void*);
void __attribute__((thiscall)) FUN_00446120(void*);
OriginalPayloadQueue16* __attribute__((thiscall)) FUN_005afcd0(OriginalPayloadQueue16*);
void __attribute__((thiscall)) FUN_005afd60(OriginalPayloadQueue16*);
OriginalPayloadQueue16* __attribute__((thiscall)) FUN_00445560(OriginalPayloadQueue16*);
void __attribute__((thiscall)) FUN_00445600(OriginalPayloadQueue16*);
void* __attribute__((thiscall)) FUN_005afe30(void*);
void __attribute__((thiscall)) FUN_005afea0(void*);
void* __attribute__((thiscall)) FUN_005b0890(void*);
void __attribute__((thiscall)) FUN_005b0900(void*);
}
