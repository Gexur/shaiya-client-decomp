#include "input_owner15016.h"
#include "input_owner_access.h"
#include "core/block_ring20.h"
#include "runtime/allocations.h"
using namespace original_input;
extern "C" __declspec(dllimport) int32_t __attribute__((stdcall)) FreeLibrary(void*);
extern "C" void* __attribute__((thiscall)) FUN_00535200(void* self) {
    store(self, 0x14, 0);
    store(self, 0x18, 0);
    store(self, 0x1c, 0);
    store(self, 0x20, 0);
    store(self, 0x80, 7);
    store(self, 0x7c, 0);
    word(self, 0x6c, 0);
    store(self, 0x9c, 7);
    store(self, 0x98, 0);
    word(self, 0x88, 0);
    store(self, 0xb8, 15);
    store(self, 0xb4, 0);
    byte(self, 0xa4, 0);
    store(self, 0x30f4, 7);
    store(self, 0x30f0, 0);
    word(self, 0x30e0, 0);
    store(self, 0x30fc, 0);
    store(self, 0x3100, 0);
    store(self, 0x3104, 0);
    store(self, 0x3630, 0);
    store(self, 0x3620, 0);
    store(self, 0x28, 0);
    byte(self, 0, 0);
    byte(self, 0x30, 0);
    store(self, 0x34, 0);
    store(self, 0x360c, 0);
    store(self, 0xc, 0);
    store(self, 8, 0);
    byte(self, 0xd0, 0);
    store(self, 0x3634, 0);
    store(self, 0x24, 20);
    store(self, 0x2c, 1);
    store(self, 4, 500);
    store(self, 0x3608, 1);
    store(self, 0xc4, 0xffffffff);
    store(self, 0xc8, 0xffffffff);
    store(self, 0xcc, 1);
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_005340e0(void* self) {
    void* module = reinterpret_cast<void*>(load(self, 0x3630));
    if (module)
        FreeLibrary(module);
    void* buffer = reinterpret_cast<void*>(load(self, 0x30fc));
    if (buffer)
        fun_005cc620(buffer);
    store(self, 0x30fc, 0);
    store(self, 0x3100, 0);
    store(self, 0x3104, 0);
    if (load(self, 0x30f4) >= 8)
        fun_005cc620(reinterpret_cast<void*>(load(self, 0x30e0)));
    store(self, 0x30f4, 7);
    store(self, 0x30f0, 0);
    word(self, 0x30e0, 0);
    if (load(self, 0xb8) >= 16)
        fun_005cc620(reinterpret_cast<void*>(load(self, 0xa4)));
    store(self, 0xb8, 15);
    store(self, 0xb4, 0);
    byte(self, 0xa4, 0);
    if (load(self, 0x9c) >= 8)
        fun_005cc620(reinterpret_cast<void*>(load(self, 0x88)));
    store(self, 0x9c, 7);
    store(self, 0x98, 0);
    word(self, 0x88, 0);
    if (load(self, 0x80) >= 8)
        fun_005cc620(reinterpret_cast<void*>(load(self, 0x6c)));
    store(self, 0x7c, 0);
    store(self, 0x80, 7);
    word(self, 0x6c, 0);
    FUN_00421990(reinterpret_cast<OriginalBlockRing20*>(at(self, 0x10)));
}
