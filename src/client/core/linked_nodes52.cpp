#include "linked_nodes52.h"
#include "../runtime/allocations.h"

extern "C" void __attribute__((thiscall)) FUN_005b4ec0(OriginalLinkedNodes52* owner) {
    OriginalLinkedNode52* node = owner->head;
    owner->current = node;
    while (node != nullptr) {
        OriginalLinkedNode52* current = owner->current;
        OriginalLinkedNode52* next;
        // Preserve the original raw load even when a damaged list faults.
        __asm__ volatile("movl (%1), %0" : "=r"(next) : "r"(node) : "memory");
        owner->head = next;
        fun_005cc620(current);
        node = owner->head;
        owner->current = node;
    }
    owner->head = nullptr;
    owner->current = nullptr;
}
