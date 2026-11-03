#include "filter_owner.h"
#include "runtime/allocations.h"
#include "runtime/array_lifetime.h"
namespace {
using u32 = uint32_t;
void put(u32 p, u32 v) {
    *reinterpret_cast<volatile u32*>(p) = v;
}
struct VectorCleanup {
    u32 vector;
    bool active = true;
    ~VectorCleanup() noexcept(false) {
        if (active)
            (void)FUN_00555f30(reinterpret_cast<void*>(vector));
    }
};
struct AllocationCleanup {
    void* allocation;
    bool active = true;
    ~AllocationCleanup() noexcept(false) {
        if (active)
            fun_005cdc59(allocation);
    }
};
} // namespace
// Complete4378b0..437905, cleanup action6ac7c0 ->555f30(self+4).
extern "C" void* __attribute__((thiscall)) recovered_filter_record_initialize(void* object) {
    const u32 self = reinterpret_cast<u32>(object);
    put(self + 8, 0);
    put(self + 12, 0);
    put(self + 16, 0);
    put(self + 24, 0);
    VectorCleanup cleanup{self + 4};
    put(self, 0x400);
    FUN_00437820(reinterpret_cast<void*>(self + 4), 0x400, 0);
    cleanup.active = false;
    return object;
}
// Exact void element-callback type. The real EAX self result is retained
// through this literal ABI tail bridge, without an incompatible C++ call.
extern "C" __attribute__((naked, thiscall)) void FUN_004378b0(void*) {
    __asm__ volatile("jmp _recovered_filter_record_initialize");
}
// Complete437910..437999, cleanup action6ac7e0 ->delete[](raw allocation).
extern "C" OriginalFilterOwner12* __attribute__((thiscall))
FUN_00437910(OriginalFilterOwner12* self) {
    self->count = 0x50;
    self->state = 0;
    void* allocation = fun_005cde20(0xa04);
    AllocationCleanup cleanup{allocation};
    if (allocation) {
        *reinterpret_cast<volatile u32*>(allocation) = 0x50;
        void* first = reinterpret_cast<unsigned char*>(allocation) + 4;
        fun_005ce6bb(first, 0x20, 0x50, FUN_004378b0, FUN_00437480);
        self->records = first;
    } else
        self->records = nullptr;
    cleanup.active = false;
    return self;
}
