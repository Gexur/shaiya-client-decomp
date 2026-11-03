#include "nested_owner.h"
#include "core/owner112.h"
namespace shaiya::ui {
namespace {
shaiya::startup::String_00405710* string_at(Object_004230b0* self) {
    // Original6ac1a0 passes exactly self+24 to actual529db0. Its
    // storage/size/capacity offsets28/38/3c match the canonical string.
    return reinterpret_cast<shaiya::startup::String_00405710*>(
        reinterpret_cast<unsigned char*>(self) + 0x24);
}
struct StringUnwind {
    shaiya::startup::String_00405710* value;
    bool active = true;
    ~StringUnwind() noexcept(false) {
        if (active)
            FUN_00529db0(value);
    }
};
__declspec(noinline) void complete_construction(Object_004230b0* self) {
    using namespace owner112_detail;
    FUN_0052d480(&self->subobject_040);
    store32(self, 0, 0);
    store8(self, 4, 0);
    store8(self, 5, 0);
    // Original is one WORD store at+6; use that actual hardware width.
    auto* at = reinterpret_cast<unsigned char*>(self) + 6;
    unsigned short zero = 0;
    __asm__ volatile("movw %1,(%0)" ::"r"(at), "r"(zero) : "memory");
    store8(self, 8, 0);
    store32(self, 0xc, 0);
}
__declspec(noinline) void complete_destruction(Object_004230b0* self) {
    FUN_0052d500(&self->subobject_040);
    // Original state0 stays active across the ordinary string release,
    // including its free and trailing writes. A thrown ordinary release
    // reaches the same actual string destructor again via6ac1a0.
    FUN_00529db0(string_at(self));
}
} // namespace
extern "C" Object_004230b0* __attribute__((thiscall)) FUN_004230b0(Object_004230b0* self) {
    using namespace owner112_detail;
    store32(self, 0x3c, 15);
    store32(self, 0x38, 0);
    store8(self, 0x28, 0);
    StringUnwind cleanup{string_at(self)};
    complete_construction(self);
    cleanup.active = false;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_00423110(Object_004230b0* self) {
    StringUnwind cleanup{string_at(self)};
    complete_destruction(self);
    cleanup.active = false;
}
} // namespace shaiya::ui
