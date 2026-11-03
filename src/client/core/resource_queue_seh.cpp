#include "resource_queue.h"
#include "queue_payload364.h"
#include "com_payload520.h"
#include "../runtime/allocations.h"
namespace {
void store(void* base, uint32_t offset, uint32_t value) {
    *reinterpret_cast<volatile uint32_t*>(reinterpret_cast<uint32_t>(base) + offset) = value;
}
struct Free8Failure {
    OriginalFreeNodes8* self;
    bool complete = false;
    ~Free8Failure() noexcept(false) {
        if (!complete)
            FUN_00444300(self);
    }
};
struct Free8Cleanup {
    OriginalFreeNodes8* self;
    ~Free8Cleanup() noexcept(false) {
        FUN_00444300(self);
    }
};
struct PoolFailure {
    OriginalPayloadPool28* self;
    bool complete = false;
    ~PoolFailure() noexcept(false) {
        if (!complete)
            FUN_00446d60(self);
    }
};
struct PoolCleanup {
    OriginalPayloadPool28* self;
    ~PoolCleanup() noexcept(false) {
        FUN_00446d60(self);
    }
};
struct Queue520Cleanup {
    OriginalPayloadQueue16* self;
    ~Queue520Cleanup() noexcept(false) {
        FUN_005afd60(self);
    }
};
struct Queue364Cleanup {
    OriginalPayloadQueue16* self;
    ~Queue364Cleanup() noexcept(false) {
        FUN_00445600(self);
    }
};
struct AllocatedPayload {
    void* pointer;
    bool complete = false;
    ~AllocatedPayload() noexcept(false) {
        if (!complete)
            fun_005cc620(pointer);
    }
};

__declspec(noinline) void finish520(OriginalPayloadQueue16* self) {
    self->head = static_cast<OriginalQueueNode8*>(fun_005cc96d(8));
    auto* payload = static_cast<OriginalComPayload520*>(fun_005cc96d(0x208));
    if (payload != nullptr) {
        payload->vtable = dat_006cf410;
        payload->resource = nullptr;
        payload->first[0] = 0;
        payload->second[0] = 0;
    }
    store(self->head, 0, reinterpret_cast<uint32_t>(payload));
    store(self->head, 4, 0);
    self->cursor = self->head;
}
__declspec(noinline) void finish364(OriginalPayloadQueue16* self) {
    self->head = static_cast<OriginalQueueNode8*>(fun_005cc96d(8));
    auto* payload = static_cast<OriginalQueuePayload364*>(fun_005cc96d(0x16c));
    AllocatedPayload cleanup{payload};
    if (payload != nullptr)
        FUN_005ada20(payload);
    store(self->head, 0, reinterpret_cast<uint32_t>(payload));
    store(self->head, 4, 0);
    self->cursor = self->head;
    cleanup.complete = true;
}
void initialize_pool(OriginalPayloadPool28* self) {
    self->free.head = static_cast<OriginalPoolNode12*>(fun_005cc96d(12));
    store(self->free.head, 8, 0);
    self->free.tail = self->free.head;
    self->count = 0;
    self->sentinel.previous = &self->sentinel;
    self->sentinel.next = &self->sentinel;
    self->cursor = &self->sentinel;
}
void owner_stores(void* self) {
    *reinterpret_cast<volatile uint32_t*>(self) = 0;
    *reinterpret_cast<volatile uint8_t*>(reinterpret_cast<uint32_t>(self) + 0x31u) = 0;
    *reinterpret_cast<volatile uint8_t*>(reinterpret_cast<uint32_t>(self) + 0x30u) = 0;
}
} // namespace
extern "C" OriginalPayloadQueue16* __attribute__((thiscall))
FUN_005afcd0(OriginalPayloadQueue16* self) {
    self->free.head = static_cast<OriginalQueueNode8*>(fun_005cc96d(8));
    store(self->free.head, 4, 0);
    self->free.tail = self->free.head;
    Free8Failure cleanup{&self->free};
    finish520(self);
    cleanup.complete = true;
    return self;
}
extern "C" OriginalPayloadQueue16* __attribute__((thiscall))
FUN_00445560(OriginalPayloadQueue16* self) {
    self->free.head = static_cast<OriginalQueueNode8*>(fun_005cc96d(8));
    store(self->free.head, 4, 0);
    self->free.tail = self->free.head;
    Free8Failure cleanup{&self->free};
    finish364(self);
    cleanup.complete = true;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_005afd60(OriginalPayloadQueue16* self) {
    Free8Cleanup cleanup{&self->free};
    self->cursor = self->head;
    while (self->head != nullptr) {
        self->head = self->head->next;
        void* payload = self->cursor->payload;
        if (payload != nullptr) {
            using Destroy = void*(__attribute__((thiscall))*)(void*, uint32_t);
            (void)reinterpret_cast<Destroy>((*static_cast<void***>(payload))[0])(payload, 1);
        }
        fun_005cc620(self->cursor);
        self->cursor = self->head;
    }
}
extern "C" void __attribute__((thiscall)) FUN_00445600(OriginalPayloadQueue16* self) {
    Free8Cleanup cleanup{&self->free};
    self->cursor = self->head;
    while (self->head != nullptr) {
        self->head = self->head->next;
        auto* payload = static_cast<OriginalQueuePayload364*>(self->cursor->payload);
        if (payload != nullptr) {
            FUN_005ae040(payload);
            fun_005cc620(payload);
        }
        fun_005cc620(self->cursor);
        self->cursor = self->head;
    }
}
extern "C" void* __attribute__((thiscall)) FUN_005afe30(void* self) {
    auto* bytes = static_cast<uint8_t*>(self);
    auto* pool = reinterpret_cast<OriginalPayloadPool28*>(bytes + 4);
    initialize_pool(pool);
    PoolFailure cleanup{pool};
    FUN_005afcd0(reinterpret_cast<OriginalPayloadQueue16*>(bytes + 0x20));
    owner_stores(self);
    cleanup.complete = true;
    return self;
}
extern "C" void* __attribute__((thiscall)) FUN_005b0890(void* self) {
    auto* bytes = static_cast<uint8_t*>(self);
    auto* pool = reinterpret_cast<OriginalPayloadPool28*>(bytes + 4);
    initialize_pool(pool);
    PoolFailure cleanup{pool};
    FUN_00445560(reinterpret_cast<OriginalPayloadQueue16*>(bytes + 0x20));
    owner_stores(self);
    cleanup.complete = true;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_005afea0(void* self) {
    auto* bytes = static_cast<uint8_t*>(self);
    PoolCleanup pool{reinterpret_cast<OriginalPayloadPool28*>(bytes + 4)};
    Queue520Cleanup queue{reinterpret_cast<OriginalPayloadQueue16*>(bytes + 0x20)};
    FUN_00446080(self);
}
extern "C" void __attribute__((thiscall)) FUN_005b0900(void* self) {
    auto* bytes = static_cast<uint8_t*>(self);
    PoolCleanup pool{reinterpret_cast<OriginalPayloadPool28*>(bytes + 4)};
    Queue364Cleanup queue{reinterpret_cast<OriginalPayloadQueue16*>(bytes + 0x20)};
    FUN_00446120(self);
}
