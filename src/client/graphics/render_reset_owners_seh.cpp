#include "graphics/render_reset_owners.h"
#include "graphics/native_postfx_ports.h"
#include "graphics/native_water_ports.h"
#include "core/com_array_owner.h"
#include "graphics/render_support.h"

namespace {
struct PairCleanup {
    void* self;
    ~PairCleanup() noexcept(false) {
        FUN_005b00e0(reinterpret_cast<void*>(reinterpret_cast<uintptr_t>(self) + 0x1d4));
    }
};
} // namespace

// Native water resources include the target scope, textures and authored buffers.
extern "C" void __attribute__((thiscall)) FUN_0053dd80(void* self) {
    native_water_release(self);
}

// Original53e610..53e65d has one active unwind state. FuncInfo7030b4's
// cleanup6b3840 calls the real pair owner at self+1d4 if53dd80 unwinds.
// Normal pair cleanup is inactive before its own first callback can throw.
extern "C" void __attribute__((thiscall)) FUN_0053e610(void* self) {
    PairCleanup cleanup{self};
    FUN_0053dd80(self);
}

// Complete original54e3b0..54e48f, including the signed live count at70bb58.
// Each loop iteration releases the +50 series before the +2c series. The
// count is read again after both callbacks, preserving callback mutations.
extern "C" void __attribute__((thiscall)) FUN_0054e3b0(void* self) {
    native_postfx_release(self);
}
