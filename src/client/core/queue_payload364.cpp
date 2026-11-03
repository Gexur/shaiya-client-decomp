#include "queue_payload364.h"
#include "untouched_lifetime.h"
#include "../startup/global_ownership.h"
#include "../runtime/allocations.h"
#include "../runtime/array_lifetime.h"
#include "graphics/native_resources.h"
extern "C" uint8_t dat_0070ca48 = 1;
namespace {
void release(shaiya::graphics::native::Buffer* object) {
    object->release();
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_005ad7d0(void* value) {
    auto* self = static_cast<OriginalQueueElement24*>(value);
    void* object = self->object;
    if (object != nullptr) {
        if (dat_0070ca48 == 0) {
            using Destroy = void*(__attribute__((thiscall))*)(void*, uint32_t);
            (void)reinterpret_cast<Destroy>((*static_cast<void***>(object))[0])(object, 1);
        }
        self->object = nullptr;
    }
    auto* current = self->resource;
    if (current != nullptr) {
        release(current);
        self->resource = nullptr;
    }
    if (self->resources != nullptr) {
        for (int32_t i = 0; i < self->count; ++i) {
            auto* current = self->resources[i];
            if (current != nullptr)
                release(current);
        }
        fun_005cdc59(self->resources);
        self->resources = nullptr;
    }
    self->count = 0;
    self->state08 = 0;
    self->state0c = 0;
}
extern "C" void __attribute__((thiscall)) FUN_005ad850(void* self) {
    FUN_005ad7d0(self);
}
extern "C" OriginalQueuePayload364* __attribute__((thiscall))
FUN_005ada20(OriginalQueuePayload364* self) {
    FUN_004441b0(self->untouched000 + 0x100);
    self->first = nullptr;
    self->second = nullptr;
    self->state160 = 0;
    self->state164 = 0;
    self->state168 = 0;
    self->elements = nullptr;
    self->state140 = 0;
    self->state144 = 0;
    self->state148 = 0;
    self->state14c = 0;
    self->state150 = 0;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_005adad0(OriginalQueuePayload364* self) {
    OriginalQueueElement24* elements = self->elements;
    if (elements != nullptr) {
        void* cookie = reinterpret_cast<void*>(reinterpret_cast<uint32_t>(elements) - 4u);
        uint32_t count;
        __asm__ volatile("movl (%1),%0" : "=r"(count) : "r"(cookie) : "memory");
        fun_005cdcbc(elements, 24, static_cast<int32_t>(count), FUN_005ad850);
        fun_005cdc59(cookie);
        self->elements = nullptr;
    }
    if (self->first != nullptr) {
        fun_005cdc59(self->first);
        self->first = nullptr;
    }
    if (self->second != nullptr) {
        fun_005cdc59(self->second);
        self->second = nullptr;
    }
    self->state160 = 0;
    self->state164 = 0;
    self->state168 = 0;
    self->state140 = 0;
    self->state144 = 0;
    self->state148 = 0;
    self->state14c = 0;
    self->state150 = 0;
}
