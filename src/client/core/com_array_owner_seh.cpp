#include "com_array_owner.h"
#include "resource_record.h"
namespace {
struct BaseCleanup {
    void* self;
    ~BaseCleanup() noexcept(false) {
        FUN_0040a900(self);
    }
};
struct PairCleanup {
    void* self;
    ~PairCleanup() noexcept(false) {
        FUN_005b00e0(self);
    }
};
} // namespace
extern "C" void __attribute__((thiscall)) FUN_005b2870(void* self) {
    // Actual FuncInfo704830 has five chained unwind states: base40a900 and
    // pair5b00e0 at14,30,4c,8c. A guard reached on the normal path is
    // already inactive if its own pair call throws.
    auto* bytes = static_cast<uint8_t*>(self);
    BaseCleanup base{self};
    PairCleanup first{bytes + 0x14}, second{bytes + 0x30}, third{bytes + 0x4c},
        fourth{bytes + 0x8c};
    FUN_005b15a0(self);
}
