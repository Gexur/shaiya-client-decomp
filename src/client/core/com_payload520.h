#pragma once
#include <stdint.h>
#include <stddef.h>
struct OriginalComObject;
namespace shaiya::graphics::native {
struct Texture2D;
}
struct OriginalComPayload520;
using OriginalPayload520Deleting = void*(__attribute__((thiscall)) *)(OriginalComPayload520*,
                                                                      uint32_t);
struct OriginalComPayload520 {
    const OriginalPayload520Deleting* vtable;
    uint8_t first[256], second[256];
    shaiya::graphics::native::Texture2D* resource;
};
static_assert(sizeof(OriginalComPayload520) == 0x208 &&
              offsetof(OriginalComPayload520, resource) == 0x204);
extern "C" {
extern const OriginalPayload520Deleting dat_006cf410[1];
void __attribute__((thiscall)) FUN_005afc70(void*);
void __attribute__((thiscall)) FUN_005afca0(OriginalComPayload520*);
void* __attribute__((thiscall)) FUN_005a37f0(OriginalComPayload520*, uint32_t);
}
