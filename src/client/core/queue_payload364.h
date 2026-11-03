#pragma once
#include <stdint.h>
#include <stddef.h>
struct OriginalComObject;
namespace shaiya::graphics::native {
struct Buffer;
}
struct OriginalQueueElement24 {
    void* object;
    int32_t count;
    uint32_t state08, state0c;
    shaiya::graphics::native::Buffer* resource;
    shaiya::graphics::native::Buffer** resources;
};
struct OriginalQueuePayload364 {
    uint8_t untouched000[0x140];
    uint32_t state140, state144, state148, state14c, state150;
    OriginalQueueElement24* elements;
    void* first;
    void* second;
    uint32_t state160, state164, state168;
};
static_assert(sizeof(OriginalQueueElement24) == 24 && sizeof(OriginalQueuePayload364) == 0x16c);
static_assert(offsetof(OriginalQueuePayload364, elements) == 0x154 &&
              offsetof(OriginalQueuePayload364, first) == 0x158);
extern "C" {
extern uint8_t dat_0070ca48;
void __attribute__((thiscall)) FUN_005ad7d0(void*);
void __attribute__((thiscall)) FUN_005ad850(void*);
OriginalQueuePayload364* __attribute__((thiscall)) FUN_005ada20(OriginalQueuePayload364*);
void __attribute__((thiscall)) FUN_005adad0(OriginalQueuePayload364*);
void __attribute__((thiscall)) FUN_005ae040(OriginalQueuePayload364*);
}
