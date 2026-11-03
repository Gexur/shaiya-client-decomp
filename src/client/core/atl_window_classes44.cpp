#include "atl_window_classes44.h"
#include "../startup/global_atl_modules.h"
#include "../runtime/heap.h"
extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) UnregisterClassA(const char*, void*);
__declspec(dllimport) void __attribute__((stdcall)) DeleteCriticalSection(OriginalCriticalSection*);
__declspec(dllimport) void __attribute__((stdcall)) RaiseException(uint32_t, uint32_t, uint32_t,
                                                                   const uint32_t*);
}
extern "C" OriginalAtlWindowClasses44* __attribute__((thiscall))
FUN_0051cd50(OriginalAtlWindowClasses44* self) {
    fun_0051a7a0(&self->critical04);
    self->atoms20 = nullptr;
    self->count24 = 0;
    self->capacity28 = 0;
    self->size = 44;
    self->reserved1c = 0;
    if (fun_0051a7c0(&self->critical04) < 0)
        dat_022033ec = 1;
    return self;
}
extern "C" uint32_t __attribute__((stdcall)) FUN_0051c910(OriginalAtlWindowClasses44* self,
                                                          void* module) {
    if (self == nullptr)
        return 0x80070057u;
    const uint32_t size = self->size;
    if (size == 0)
        return 0;
    if (size != 44)
        return 0x80070057u;
    if (self->count24 > 0) {
        const auto unregister_class = UnregisterClassA;
        uint32_t index = 0;
        do {
            if (static_cast<int32_t>(index) < 0 || static_cast<int32_t>(index) >= self->count24) {
                RaiseException(0xc000008cu, 1, 0, nullptr);
                __asm__ volatile("int3");
                __builtin_unreachable();
            }
            uint16_t atom;
            __asm__ volatile("movw (%1,%2,2),%0"
                             : "=r"(atom)
                             : "r"(self->atoms20), "r"(index)
                             : "memory");
            (void)unregister_class(reinterpret_cast<const char*>(uint32_t(atom)), module);
            ++index;
        } while (static_cast<int32_t>(index) < self->count24);
    }
    auto* atoms = self->atoms20;
    if (atoms != nullptr) {
        fun_005cfaf0(atoms);
        self->atoms20 = nullptr;
    }
    self->count24 = 0;
    self->capacity28 = 0;
    DeleteCriticalSection(&self->critical04);
    self->size = 0;
    return 0;
}
extern "C" void __attribute__((thiscall)) FUN_0051cda0(OriginalAtlWindowClasses44* self) {
    (void)FUN_0051c910(self, dat_0224f310.module);
    auto* atoms = self->atoms20;
    if (atoms != nullptr) {
        fun_005cfaf0(atoms);
        self->atoms20 = nullptr;
    }
    self->count24 = 0;
    self->capacity28 = 0;
}
