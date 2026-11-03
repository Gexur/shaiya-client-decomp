#include "atl_base_module44.h"
#include "../runtime/allocations.h"
extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) InterlockedIncrement(volatile int32_t*);
__declspec(dllimport) int32_t __attribute__((stdcall)) InterlockedDecrement(volatile int32_t*);
__declspec(dllimport) void __attribute__((stdcall)) DeleteCriticalSection(OriginalCriticalSection*);
__declspec(dllimport) void __attribute__((stdcall)) RaiseException(uint32_t, uint32_t, uint32_t,
                                                                   const uint32_t*);
const OriginalAtlBase44Table dat_006c4db0 = {FUN_0051ccf0, FUN_0051cc40, FUN_0051cc50,
                                             FUN_0051cc60};
OriginalAtlBase44* volatile dat_022033d4 = nullptr;
OriginalAtlBase44* volatile dat_022033e8 = nullptr;
}
extern "C" OriginalAtlBase44* __attribute__((thiscall)) FUN_0051cbe0(OriginalAtlBase44* self) {
    fun_0051a7a0(&self->base04.critical);
    self->base04.size = 36;
    self->base04.callbacks = nullptr;
    self->base04.references = 0;
    dat_022033e8 = self;
    if (fun_0051a7c0(&self->base04.critical) < 0)
        dat_022033ec = 1;
    self->resource28 = nullptr;
    self->vtable = &dat_006c4db0;
    dat_022033d4 = self;
    return self;
}
extern "C" void __attribute__((stdcall)) FUN_0051ab00(OriginalAtlBase36* base) {
    if (base == nullptr)
        RaiseException(0xc0000005u, 1, 0, nullptr);
    OriginalAtlCallback12* node = base->callbacks;
    while (node != nullptr) {
        node->callback(node->argument);
        OriginalAtlCallback12* next = node->next;
        fun_005cc620(node);
        node = next;
    }
    base->callbacks = nullptr;
}
extern "C" void __attribute__((thiscall)) FUN_0051c8b0(OriginalAtlBase44* self) {
    if (self->base04.size != 0) {
        if (self->base04.callbacks != nullptr) {
            FUN_0051ab00(&self->base04);
            self->base04.callbacks = nullptr;
        }
        void* resource = self->resource28;
        if (resource != nullptr) {
            auto** table = *static_cast<void***>(resource);
            (void)reinterpret_cast<uint32_t(__attribute__((stdcall))*)(void*)>(table[2])(resource);
        }
        DeleteCriticalSection(&self->base04.critical);
        self->base04.size = 0;
    }
}
extern "C" void __attribute__((thiscall)) FUN_0051c900(OriginalAtlBase44* self) {
    FUN_0051c8b0(self);
}
extern "C" OriginalAtlBase44* __attribute__((thiscall)) FUN_0051ccf0(OriginalAtlBase44* self,
                                                                     uint32_t flags) {
    FUN_0051c900(self);
    if (flags & 1)
        fun_005cc620(self);
    return self;
}
extern "C" int32_t __attribute__((thiscall)) FUN_0051cc40(OriginalAtlBase44* self) {
    return InterlockedIncrement(&self->base04.references);
}
extern "C" int32_t __attribute__((thiscall)) FUN_0051cc50(OriginalAtlBase44* self) {
    return InterlockedDecrement(&self->base04.references);
}
extern "C" int32_t __attribute__((thiscall)) FUN_0051cc60(OriginalAtlBase44* self) {
    return self->base04.references;
}
