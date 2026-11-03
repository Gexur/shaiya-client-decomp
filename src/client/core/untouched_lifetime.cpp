#include "untouched_lifetime.h"

extern "C" __attribute__((noinline)) void* __attribute__((thiscall)) FUN_004441b0(void* self) {
    // Original4441b0 is MOV EAX,ECX;RET. No field initialization is inferred.
    return self;
}
extern "C" __attribute__((noinline)) void __attribute__((thiscall)) FUN_005bfb50(void*) {
    // Existing recovered original5bfb50 is RET; the canonical body moved here.
}
extern "C" void* __attribute__((thiscall)) FUN_005cc4f0(void* self) {
    const uint32_t base = reinterpret_cast<uint32_t>(self);
    for (uint32_t i = 0; i < 6; ++i)
        FUN_004441b0(reinterpret_cast<void*>(base + i * 16u));
    return self;
}
extern "C" void* __attribute__((thiscall)) FUN_005af140(void* self) {
    FUN_005cc4f0(reinterpret_cast<void*>(reinterpret_cast<uint32_t>(self) + 24u));
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_005aeef0(void* self) {
    FUN_005bfb50(reinterpret_cast<void*>(reinterpret_cast<uint32_t>(self) + 24u));
}
