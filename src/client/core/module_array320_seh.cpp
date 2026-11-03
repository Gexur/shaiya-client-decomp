#include "module_array320.h"
#include "runtime/array_lifetime.h"
namespace {
struct ArrayCleanup {
    void* self;
    bool active = true;
    ~ArrayCleanup() noexcept(false) {
        if (active)
            fun_005cdcbc(static_cast<uint8_t*>(self) + 4, 0x140, 16, FUN_00548c00);
    }
};
} // namespace
extern "C" void __attribute__((thiscall)) FUN_00549710(void* self) {
    *reinterpret_cast<const OriginalModuleArrayDeleting**>(self) = dat_006c977c;
    ArrayCleanup cleanup{self};
    FUN_00434d20(self);
    FUN_00434cc0(self);
    cleanup.active = false;
    fun_005cdcbc(static_cast<uint8_t*>(self) + 4, 0x140, 16, FUN_00548c00);
}
