#include "block_ring20.h"
#include "../runtime/allocations.h"
extern "C" OriginalBlockRing20* __attribute__((thiscall)) FUN_00421f70(OriginalBlockRing20* owner) {
    owner->blocks = nullptr;
    owner->capacity = 0;
    owner->start = 0;
    owner->count = 0;
    return owner;
}
extern "C" void __attribute__((thiscall)) FUN_00421990(OriginalBlockRing20* owner) {
    // Retain the original live count loop, including its second load/test.
    // An initially empty ring leaves start untouched.
    if (owner->count != 0) {
        do {
            const uint32_t count = owner->count;
            if (count != 0) {
                const uint32_t next = count - 1;
                owner->count = next;
                if (next == 0)
                    owner->start = 0;
            }
        } while (owner->count != 0);
    }
    uint32_t remaining = owner->capacity;
    while (remaining > 0) {
        void** blocks = owner->blocks;
        void* block;
        __asm__ volatile("movl (%1,%2,4),%0"
                         : "=r"(block)
                         : "r"(blocks), "r"(remaining - 1)
                         : "memory");
        --remaining;
        if (block != nullptr)
            fun_005cc620(block);
    }
    void** blocks = owner->blocks;
    if (blocks != nullptr)
        fun_005cc620(blocks);
    owner->capacity = 0;
    owner->blocks = nullptr;
}
extern "C" void __attribute__((thiscall)) FUN_00421a30(OriginalBlockRing20* owner) {
    FUN_00421990(owner);
}
