#include "resource_array_owner492.h"
#include "../runtime/array_lifetime.h"
#include "../config/initialization.hpp"
namespace {
struct BaseCleanup {
    OriginalResourcePair* pair;
    bool active = true;
    ~BaseCleanup() noexcept(false) {
        if (active)
            FUN_0041ff00(pair);
    }
};
struct ArrayCleanup {
    OriginalResourcePair* array;
    bool active = true;
    ~ArrayCleanup() noexcept(false) {
        if (active)
            fun_005cdcbc(array, 16, 5, resource_pair_destroy);
    }
};
// Calls remain explicit protected operations so native foreign exceptions
// execute the original FuncInfo actions as well as C++ exceptions.
__declspec(noinline) void construct_array(OriginalResourcePair* array) {
    fun_005ce6bb(array, 16, 5, resource_pair_construct, resource_pair_destroy);
}
__declspec(noinline) void release_resources(OriginalResourceArrayOwner492* self) {
    FUN_0041ff30(self);
}
} // namespace
extern "C" OriginalResourceArrayOwner492* __attribute__((thiscall))
FUN_00420350(OriginalResourceArrayOwner492* self) {
    self->vtable = dat_006bcb94;
    FUN_0041fef0(&self->base04);
    BaseCleanup base{&self->base04};
    construct_array(self->first14);
    ArrayCleanup first{self->first14};
    construct_array(self->second64);
    self->half_width_b4 = shaiya::config::DAT_0070859c / 2;
    self->half_height_b8 = shaiya::config::DAT_007085a0 / 2;
    self->statec0 = 0;
    self->statec1 = 0;
    self->extrae0 = nullptr;
    self->valuebc = 1;
    for (uint32_t i = 0; i < 65; ++i)
        self->zerose8[i] = 0;
    first.active = false;
    base.active = false;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_00420420(OriginalResourceArrayOwner492* self) {
    self->vtable = dat_006bcb94;
    BaseCleanup base{&self->base04};
    ArrayCleanup first{self->first14};
    ArrayCleanup second{self->second64};
    release_resources(self);
}
