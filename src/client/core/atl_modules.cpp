#include "atl_modules.h"
#include "memory.h"
#include "../runtime/security.h"
#include "../runtime/heap.h"
extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) GetVersionExA(void*);
__declspec(dllimport) void __attribute__((stdcall)) DeleteCriticalSection(OriginalCriticalSection*);
OriginalAtlComEntry* dat_00705c48 = nullptr;
const OriginalAtlGuid dat_006dbccc = {
    0x394c3de0u, 0x3c6f, 0x11d2, {0x81, 0x7b, 0, 0xc0, 0x4f, 0x79, 0x7a, 0xb7}};
uint8_t dat_022033ec = 0;
}
extern "C" OriginalCriticalSection* __attribute__((thiscall))
fun_0051a7a0(OriginalCriticalSection* self) {
    self->debug_information = nullptr;
    self->lock_count = 0;
    self->recursion_count = 0;
    self->owning_thread = nullptr;
    self->semaphore = nullptr;
    self->spin_count = 0;
    return self;
}
extern "C" void __attribute__((thiscall)) fun_005e1991(OriginalAtlComModule* self) {
    if (self->size != 0) {
        OriginalAtlComEntry** cursor = self->begin;
        while (reinterpret_cast<uint32_t>(cursor) < reinterpret_cast<uint32_t>(self->end)) {
            OriginalAtlComEntry* const entry = *cursor;
            if (entry != nullptr) {
                void* const factory = entry->factory;
                if (factory != nullptr) {
                    auto* table = *static_cast<void***>(factory);
                    reinterpret_cast<uint32_t(__attribute__((stdcall))*)(void*)>(table[2])(factory);
                }
                entry->factory = nullptr;
            }
            ++cursor;
        }
        DeleteCriticalSection(&self->critical);
        self->size = 0;
    }
}
extern "C" OriginalAtlComModule* __attribute__((thiscall))
fun_005e19d3(OriginalAtlComModule* self) {
    fun_0051a7a0(&self->critical);
    self->size = 40;
    // The supplied PE has IMAGE_FILE_RELOCS_STRIPPED and base00400000; these
    // are actual immediate handle values, not a fabricated Win32 query.
    self->module = reinterpret_cast<void*>(0x400000);
    self->begin = &dat_00705c48;
    self->end = &dat_00705c48;
    if (fun_0051a7c0(&self->critical) < 0)
        dat_022033ec = 1;
    return self;
}
extern "C" void __attribute__((thiscall)) fun_005e1a13(OriginalAtlList* self) {
    void* const allocation = self->allocation;
    if (allocation != nullptr) {
        fun_005cfaf0(allocation);
        self->allocation = nullptr;
    }
    self->count = 0;
    self->capacity = 0;
}
extern "C" OriginalAtlModule* __attribute__((thiscall)) fun_005e1a30(OriginalAtlModule* self) {
    fun_0051a7a0(&self->critical);
    self->list.allocation = nullptr;
    self->list.count = 0;
    self->list.capacity = 0;
    return self;
}
extern "C" void __attribute__((thiscall)) fun_005e1a4a(OriginalAtlModule* self) {
    DeleteCriticalSection(&self->critical);
    fun_005e1a13(&self->list);
}
extern "C" OriginalAtlModule* __attribute__((thiscall)) fun_005e1a60(OriginalAtlModule* self) {
    volatile uint32_t guard = dat_0070e4ec ^ reinterpret_cast<uint32_t>(&guard);
    fun_005e1a30(self);
    self->resource_module = reinterpret_cast<void*>(0x400000);
    self->module = reinterpret_cast<void*>(0x400000);
    self->size = 60;
    self->version_flag = 0;
    uint32_t version[37];
    fun_005dceb0(version, 0, 148);
    version[0] = 148;
    GetVersionExA(version);
    if ((version[4] == 2 && version[1] >= 5) ||
        (version[4] == 1 && (version[1] > 4 || (version[1] == 4 && version[2] > 0))))
        self->version_flag = 1;
    self->version = 0x710;
    self->identifier = &dat_006dbccc;
    if (fun_0051a7c0(&self->critical) < 0)
        dat_022033ec = 1;
    fun_005d0efa(guard ^ reinterpret_cast<uint32_t>(&guard));
    return self;
}
