#include "resource_record.h"
#include "../startup/global_ownership.h"
#include "../runtime/allocations.h"
#include "../runtime/array_lifetime.h"
#include "graphics/native_resources.h"
extern "C" void __attribute__((thiscall)) FUN_0040a900(void* value) {
    auto* object = static_cast<OriginalArrayElement*>(value);
    if (object->first != nullptr) {
        fun_005cdc59(object->first);
        object->first = nullptr;
    }
    if (object->second != nullptr) {
        fun_005cdc59(object->second);
        object->second = nullptr;
    }
}
extern "C" void __attribute__((thiscall)) FUN_0040efb0(OriginalArrayElement** member) {
    OriginalArrayElement* data = *member;
    if (data != nullptr) {
        uint8_t* cookie = reinterpret_cast<uint8_t*>(data) - 4;
        uint32_t count;
        __asm__ volatile("movl (%1),%0" : "=r"(count) : "r"(cookie) : "memory");
        fun_005cdcbc(data, 12, static_cast<int32_t>(count), FUN_0040a900);
        fun_005cdc59(cookie);
        *member = nullptr;
    }
}
extern "C" OriginalResourceRecord* __attribute__((thiscall))
FUN_0040efe0(OriginalResourceRecord* object) {
    object->elements = nullptr;
    object->unknown18 = 0;
    object->unknown1c = 0;
    object->unknown20 = 0;
    object->state128 = 0;
    object->first = nullptr;
    object->second = nullptr;
    object->unknown08 = 0;
    object->unknown0c = 0;
    object->unknown10 = 0;
    return object;
}
namespace {
struct MemberCleanup {
    OriginalResourceRecord* object;
    ~MemberCleanup() noexcept(false) {
        FUN_0040efb0(&object->elements);
    }
};
// The original FuncInfo6fa800 has one unwind action6abda0, which calls40efb0
// on self+14. Keeping the protected operations in this separate noinline call
// preserves that action for actual Windows faults as well as C++ exceptions.
__declspec(noinline) void release_interfaces(OriginalResourceRecord* object) {
    OriginalComObject* current = object->first;
    if (current != nullptr) {
        native_release_asset_resource(current);
        object->first = nullptr;
    }
    current = object->second;
    if (current != nullptr) {
        native_release_asset_resource(current);
        object->second = nullptr;
    }
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_0040f010(OriginalResourceRecord* object) {
    MemberCleanup cleanup{object};
    release_interfaces(object);
}
