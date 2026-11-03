#include "core/owner112.h"
namespace shaiya::ui {
namespace {
struct FirstCleanup {
    OriginalOwner112Fields* member;
    bool active = true;
    ~FirstCleanup() noexcept(false) {
        if (active)
            FUN_00447020(member);
    }
};
// Original FuncInfo702828 stays in state0 after the second allocation and
// until return. Keep every remaining operation inside a real protected call.
__declspec(noinline) void complete_members(OriginalOwner112* self) {
    using namespace owner112_detail;
    store32(self, 0x5c, reinterpret_cast<unsigned>(FUN_0052cf90()));
    store32(self, 0x60, 0);
    store8(self, 4, 0);
    store32(self, 0x64, 0);
    store32(self, 0x20, 0);
    store8(self, 0x48, 0);
    store32(self, 0x68, 0);
    store32(self, 0x6c, 0);
    store32(self, 0x3c, 0x3f800000);
    store32(self, 0x44, 0x12);
}
} // namespace
extern "C" OriginalOwner112* __attribute__((thiscall)) FUN_0052d480(OriginalOwner112* self) {
    using namespace owner112_detail;
    store32(self, 0, reinterpret_cast<unsigned>(PTR_FUN_006c5850));
    store32(self, 0x50, reinterpret_cast<unsigned>(FUN_0052cf70()));
    store32(self, 0x54, 0);
    FirstCleanup cleanup{&self->fields_04c};
    complete_members(self);
    cleanup.active = false;
    return self;
}
} // namespace shaiya::ui
