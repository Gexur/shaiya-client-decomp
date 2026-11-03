#include "resource_manager_lifetime.h"

namespace {
struct FirstTreeCleanup {
    OriginalTree48Owner12* self;
    ~FirstTreeCleanup() noexcept(false) {
        FUN_0055a1b0(self);
    }
};
struct SecondTreeCleanup {
    OriginalTree48Owner12* self;
    ~SecondTreeCleanup() noexcept(false) {
        FUN_0055a1e0(self);
    }
};
struct FirstBaseCleanup {
    OriginalResourceManagerBase20* self;
    ~FirstBaseCleanup() noexcept(false) {
        FUN_0055a210(self);
    }
};
struct SecondBaseCleanup {
    OriginalResourceManagerBase20* self;
    ~SecondBaseCleanup() noexcept(false) {
        FUN_0055a290(self);
    }
};
// Keep protected callback scopes outside the RAII frame so asynchronous Win32
// faults execute the actual original FuncInfo cleanup as well as C++ throws.
__declspec(noinline) void first_cleanup(OriginalResourceManagerBase20* self) {
    FUN_004351c0(self);
}
__declspec(noinline) void second_cleanup(OriginalResourceManagerBase20* self) {
    FUN_00435220(self);
}
} // namespace
extern "C" void __attribute__((thiscall)) FUN_0055a210(OriginalResourceManagerBase20* self) {
    self->vtable = dat_006ccb4c;
    FirstTreeCleanup cleanup{&self->tree};
    first_cleanup(self);
}
extern "C" void __attribute__((thiscall)) FUN_0055a290(OriginalResourceManagerBase20* self) {
    self->vtable = dat_006ccb50;
    SecondTreeCleanup cleanup{&self->tree};
    second_cleanup(self);
}
extern "C" void __attribute__((thiscall)) FUN_0055a390(OriginalResourceManager24* self) {
    self->untouched00 = reinterpret_cast<uint32_t>(dat_006ccb54);
    auto* base =
        reinterpret_cast<OriginalResourceManagerBase20*>(reinterpret_cast<uint8_t*>(self) + 4);
    FirstBaseCleanup cleanup{base};
    first_cleanup(base);
}
extern "C" void __attribute__((thiscall)) FUN_0055a450(OriginalResourceManager24* self) {
    self->untouched00 = reinterpret_cast<uint32_t>(dat_006ccb58);
    auto* base =
        reinterpret_cast<OriginalResourceManagerBase20*>(reinterpret_cast<uint8_t*>(self) + 4);
    SecondBaseCleanup cleanup{base};
    second_cleanup(base);
}
