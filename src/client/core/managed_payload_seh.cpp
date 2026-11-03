#include "resource_manager.h"
#include "../runtime/allocations.h"
#include "../runtime/array_lifetime.h"
#include "../startup/global_ownership.h"
#include "graphics/native_resources.h"

extern "C" void __attribute__((thiscall)) FUN_0040a8b0(void* value) {
    auto* self = static_cast<OriginalManagedElement16*>(value);
    if (self->second != nullptr) {
        fun_005cdc59(self->second);
        self->second = nullptr;
    }
    if (self->third != nullptr) {
        fun_005cdc59(self->third);
        self->third = nullptr;
    }
    if (self->first != nullptr) {
        fun_005cdc59(self->first);
        self->first = nullptr;
    }
}
extern "C" void __attribute__((thiscall)) FUN_00434df0(OriginalManagedElement16** member) {
    if (*member != nullptr) {
        auto* cookie = reinterpret_cast<uint32_t*>(reinterpret_cast<uint8_t*>(*member) - 4);
        fun_005cdcbc(*member, 16, static_cast<int32_t>(*cookie), FUN_0040a8b0);
        fun_005cdc59(cookie);
        *member = nullptr;
    }
}
namespace {
using Word = uint32_t __attribute__((may_alias));
struct MemberCleanup {
    OriginalManagedElement16** member;
    ~MemberCleanup() noexcept(false) {
        FUN_00434df0(member);
    }
};
// Original434e20 protects its owned20 deallocation and COM1c release with
// FuncInfo6fb338's action6ac6b0 ->434df0(parent self atEBP-10).
__declspec(noinline) void release_owned_fields(void* value) {
    auto* bytes = static_cast<uint8_t*>(value);
    auto* owned = reinterpret_cast<Word*>(bytes + 0x20);
    if (*owned != 0) {
        fun_005cdc59(reinterpret_cast<void*>(*owned));
        *owned = 0;
    }
    auto* field = reinterpret_cast<Word*>(bytes + 0x1c);
    if (*field != 0) {
        auto* object = reinterpret_cast<OriginalComObject*>(*field);
        native_release_asset_resource(object);
        *field = 0;
    }
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_00434e20(void* self) {
    MemberCleanup cleanup{static_cast<OriginalManagedElement16**>(self)};
    release_owned_fields(self);
}
