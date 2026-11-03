#include "resource_queue.h"
#include "queue_payload364.h"
#include "com_payload520.h"
#include "../runtime/allocations.h"

extern "C" void __attribute__((thiscall)) FUN_004442c0(OriginalFreeNodes12* self) {
    self->tail = self->head;
    while (self->head != nullptr) {
        self->head = self->head->next;
        fun_005cc620(self->tail);
        self->tail = self->head;
    }
    self->head = nullptr;
    self->tail = nullptr;
}
extern "C" void __attribute__((thiscall)) FUN_00444300(OriginalFreeNodes8* self) {
    self->tail = self->head;
    while (self->head != nullptr) {
        self->head = self->head->next;
        fun_005cc620(self->tail);
        self->tail = self->head;
    }
    self->head = nullptr;
    self->tail = nullptr;
}
extern "C" void __attribute__((thiscall)) FUN_005af1a0(OriginalPayloadPool28* self) {
    self->cursor = self->sentinel.next;
    while (self->cursor != &self->sentinel) {
        OriginalPoolNode12* current = self->cursor;
        self->cursor = current->next;
        self->free.tail->next = current;
        self->free.tail = current;
        current->next = nullptr;
    }
    self->sentinel.previous = &self->sentinel;
    self->sentinel.next = &self->sentinel;
    self->cursor = &self->sentinel;
    self->count = 0;
}
extern "C" void __attribute__((thiscall)) FUN_00446d60(OriginalPayloadPool28* self) {
    FUN_005af1a0(self);
    FUN_004442c0(&self->free);
}

namespace {
// Both original446080/446120 control-flow bodies match instruction-for-
// instruction after normalizing entry/branch offsets and the payload reset
// call target. This private template is not another recovered procedure.
template <class Payload, void(__attribute__((thiscall)) * Reset)(Payload*)>
void reset_owner(void* owner) {
    auto* bytes = static_cast<uint8_t*>(owner);
    auto* pool = reinterpret_cast<OriginalPayloadPool28*>(bytes + 4);
    auto* queue = reinterpret_cast<OriginalPayloadQueue16*>(bytes + 0x20);
    for (;;) {
        pool->cursor = pool->sentinel.next;
        if (pool->cursor == &pool->sentinel)
            break;
        void* payload = pool->cursor->payload;
        if (payload == nullptr)
            break;
        OriginalPoolNode12* current = pool->cursor;
        current->previous->next = current->next;
        pool->cursor->next->previous = pool->cursor->previous;
        current = pool->cursor;
        OriginalPoolNode12* previous = current->previous;
        pool->free.tail->next = current;
        pool->free.tail = current;
        current->next = nullptr;
        --pool->count;
        pool->cursor = previous;
        Reset(static_cast<Payload*>(payload));
        OriginalQueueNode8* node = queue->free.head;
        if (node->next == nullptr)
            node = static_cast<OriginalQueueNode8*>(fun_005cc96d(8));
        else
            queue->free.head = node->next;
        queue->cursor->next = node;
        queue->cursor = queue->cursor->next;
        *reinterpret_cast<void* volatile*>(reinterpret_cast<uint32_t>(queue->cursor)) = payload;
        *reinterpret_cast<OriginalQueueNode8* volatile*>(reinterpret_cast<uint32_t>(queue->cursor) +
                                                         4u) = nullptr;
    }
    *reinterpret_cast<volatile uint32_t*>(owner) = 0;
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_00446080(void* self) {
    reset_owner<OriginalComPayload520, FUN_005afca0>(self);
}
extern "C" void __attribute__((thiscall)) FUN_00446120(void* self) {
    reset_owner<OriginalQueuePayload364, FUN_005adad0>(self);
}
