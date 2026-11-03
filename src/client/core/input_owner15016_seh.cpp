#include "input_owner15016.h"
#include "input_owner_access.h"
#include "runtime/allocations.h"
using namespace original_input;
extern "C" extern const OriginalInputDeleting dat_006c58c8[1] = {FUN_00531660};
namespace {
// Integer LEA and an explicit original MOV retain the saved-null unwind edge
// without C++ pointer-arithmetic/dereference nonnull inference.
void* offset(void* self, uint32_t amount) {
    return reinterpret_cast<void*>(reinterpret_cast<uint32_t>(self) + amount);
}
void table_store(void* self) {
    uint32_t value = reinterpret_cast<uint32_t>(dat_006c58c8);
    __asm__ volatile("movl %1,(%0)" ::"r"(self), "r"(value) : "memory");
}
struct DevicesCleanup {
    void* self;
    bool active = true;
    ~DevicesCleanup() noexcept(false) {
        if (active)
            FUN_005aa540(self);
    }
};
struct ImeCleanup {
    void* self;
    bool active = true;
    ~ImeCleanup() noexcept(false) {
        if (active)
            FUN_005aa2d0(self);
    }
};
// The original state0 is installed BEFORE its owner-vtable store. An outlined
// protected call keeps that interval active on Clang's x86 C++ EH target.
__declspec(noinline) void construct_ime(void* self) {
    table_store(self);
    FUN_005aa390(offset(self, 0x28));
}
} // namespace
extern "C" void* __attribute__((thiscall)) FUN_00531580(void* self) {
    FUN_00557200(offset(self, 4));
    DevicesCleanup devices{offset(self, 4)};
    construct_ime(self);
    ImeCleanup ime{offset(self, 0x28)};
    FUN_00535200(offset(self, 0x464));
    store(self, 0x18, 0);
    store(self, 0x1c, 0);
    ime.active = false;
    devices.active = false;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_005315f0(void* self) {
    table_store(self);
    DevicesCleanup devices{self ? offset(self, 4) : nullptr};
    ImeCleanup ime{offset(self, 0x28)};
    FUN_005340e0(offset(self, 0x464));
    ime.active = false;
    FUN_005aa2d0(offset(self, 0x28));
    devices.active = false;
    FUN_005aa540(offset(self, 4));
}
extern "C" void* __attribute__((thiscall)) FUN_00531660(void* self, uint32_t flags) {
    FUN_005315f0(self);
    if (static_cast<uint8_t>(flags) & 1)
        fun_005cc620(self);
    return self;
}
