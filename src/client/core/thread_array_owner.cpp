#include "thread_array_owner.h"
#include "../runtime/allocations.h"
#include "../runtime/array_lifetime.h"
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

extern "C" const OriginalVirtualDelete dat_006cc9f8[1] = {FUN_00553610};

extern "C" void __attribute__((thiscall)) FUN_00551ff0(void* value) {
    auto* self = static_cast<OriginalNestedElement280*>(value);
    if (self->first != nullptr) {
        fun_005cdc59(self->first);
        self->first = nullptr;
    }
    if (self->second != nullptr) {
        fun_005cdc59(self->second);
        self->second = nullptr;
    }
}
extern "C" OriginalThreadChild304* __attribute__((thiscall))
FUN_00552030(OriginalThreadChild304* self, uint32_t flags) {
    if (self->elements != nullptr) {
        auto* cookie = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(self->elements) - 4);
        fun_005cdcbc(self->elements, 0x118, static_cast<int32_t>(*cookie), FUN_00551ff0);
        fun_005cdc59(cookie);
        self->elements = nullptr;
    }
    self->state12c = 0;
    if ((flags & 1) != 0)
        fun_005cc620(self);
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_00552090(OriginalThreadArrayOwner32* self) {
    int32_t index = 0;
    while (index < self->count) {
        OriginalThreadChild304* current = self->items[index];
        if (current != nullptr) {
            FUN_00552030(current, 1);
            self->items[index] = nullptr;
        }
        self->items[index] = nullptr;
        index = static_cast<int32_t>(static_cast<uint32_t>(index) + 1u);
    }
    if (self->items != nullptr) {
        fun_005cdc59(self->items);
        self->items = nullptr;
    }
    self->items = nullptr;
    self->count = 0;
    self->state14 = 0;
}
extern "C" void __attribute__((thiscall)) FUN_00552560(OriginalThreadArrayOwner32* self) {
    (void)WaitForSingleObjectEx(self->thread, 0xffffffffu, FALSE);
    (void)CloseHandle(self->thread);
    self->thread = nullptr;
    FUN_00552090(self);
}
extern "C" OriginalThreadArrayOwner32* __attribute__((thiscall))
FUN_005535d0(OriginalThreadArrayOwner32* self) {
    self->vtable = dat_006cc9f8;
    self->items = nullptr;
    self->count = 0;
    self->state1c = 0;
    self->unknown08 = 0;
    self->flags0c[0] = 0;
    self->flags0c[1] = 0;
    self->flags0c[2] = 0;
    self->state14 = 0;
    self->thread = nullptr;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_00553600(OriginalThreadArrayOwner32* self) {
    self->vtable = dat_006cc9f8;
    FUN_00552560(self);
}
extern "C" void* __attribute__((thiscall)) FUN_00553610(void* value, uint32_t flags) {
    auto* self = static_cast<OriginalThreadArrayOwner32*>(value);
    self->vtable = dat_006cc9f8;
    FUN_00552560(self);
    if ((flags & 1) != 0)
        fun_005cc620(self);
    return self;
}
