#include "com_payload520.h"
#include "../startup/global_ownership.h"
#include "../runtime/allocations.h"
#include "../runtime/array_lifetime.h"
#include "graphics/native_resources.h"
extern "C" const OriginalPayload520Deleting dat_006cf410[1] = {FUN_005a37f0};
namespace {
void release(shaiya::graphics::native::Texture2D* object) {
    object->release();
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_005afc70(void* value) {
    auto* self = static_cast<OriginalComPayload520*>(value);
    auto* current = self->resource;
    self->vtable = dat_006cf410;
    if (current != nullptr) {
        release(current);
        self->resource = nullptr;
    }
}
extern "C" void __attribute__((thiscall)) FUN_005afca0(OriginalComPayload520* self) {
    auto* current = self->resource;
    if (current != nullptr) {
        release(current);
        self->resource = nullptr;
    }
    self->first[0] = 0;
    self->second[0] = 0;
}
extern "C" void* __attribute__((thiscall)) FUN_005a37f0(OriginalComPayload520* self,
                                                        uint32_t flags) {
    const uint8_t bits = static_cast<uint8_t>(flags);
    if ((bits & 2) != 0) {
        void* cookie = reinterpret_cast<void*>(reinterpret_cast<uint32_t>(self) - 4u);
        uint32_t count;
        __asm__ volatile("movl (%1),%0" : "=r"(count) : "r"(cookie) : "memory");
        fun_005cdcbc(self, 0x208, static_cast<int32_t>(count), FUN_005afc70);
        if ((bits & 1) != 0)
            fun_005cdc59(cookie);
        return cookie;
    }
    FUN_005afc70(self);
    if ((bits & 1) != 0)
        fun_005cc620(self);
    return self;
}
