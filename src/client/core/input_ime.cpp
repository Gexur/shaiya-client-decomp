#include "input_owner15016.h"
#include "input_owner_access.h"
#include "runtime/allocations.h"
using namespace original_input;
extern "C" {
__declspec(dllimport) void* __attribute__((stdcall)) ImmGetContext(void*);
__declspec(dllimport) int32_t __attribute__((stdcall)) ImmNotifyIME(void*, uint32_t, uint32_t,
                                                                    uint32_t);
__declspec(dllimport) int32_t __attribute__((stdcall)) ImmReleaseContext(void*, void*);
extern const OriginalInputDeleting dat_006cf228[1] = {FUN_005aa3d0};
}
extern "C" void __attribute__((thiscall)) FUN_005aa2d0(void* self) {
    void* buffer = reinterpret_cast<void*>(load(self, 0x438));
    store(self, 0, reinterpret_cast<uint32_t>(dat_006cf228));
    if (buffer) {
        fun_005cc620(buffer);
        store(self, 0x438, 0);
    }
}
extern "C" void __attribute__((thiscall)) FUN_005aa300(void* self) {
    for (uint32_t i = 1; i <= 0x100; ++i)
        store(self, i * 4, 0);
    store(self, 0x404, 0);
    store(self, 0x408, 0);
    void* window = reinterpret_cast<void*>(load(self, 0x418));
    store(self, 0x40c, 0);
    store(self, 0x410, 0);
    store(self, 0x414, 0);
    store(self, 0x428, 20);
    store(self, 0x424, 0);
    if (window) {
        void* context = ImmGetContext(window);
        if (context) {
            ImmNotifyIME(context, 0x15, 4, 0);
            ImmReleaseContext(reinterpret_cast<void*>(load(self, 0x418)), context);
        }
    }
    void* buffer = reinterpret_cast<void*>(load(self, 0x438));
    if (buffer) {
        fun_005cc620(buffer);
        store(self, 0x438, 0);
    }
}
extern "C" void* __attribute__((thiscall)) FUN_005aa390(void* self) {
    store(self, 0, reinterpret_cast<uint32_t>(dat_006cf228));
    store(self, 0x42c, 0);
    store(self, 0x430, 1);
    byte(self, 0x41c, 0);
    store(self, 0x420, 10);
    store(self, 0x418, 0);
    store(self, 0x438, 0);
    FUN_005aa300(self);
    return self;
}
extern "C" void* __attribute__((thiscall)) FUN_005aa3d0(void* self, uint32_t flags) {
    FUN_005aa2d0(self);
    if (static_cast<uint8_t>(flags) & 1)
        fun_005cc620(self);
    return self;
}
