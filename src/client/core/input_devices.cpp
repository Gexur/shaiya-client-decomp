#include "input_owner15016.h"
#include "input_owner_access.h"
#include "runtime/allocations.h"
using namespace original_input;
extern "C" void* __attribute__((thiscall)) FUN_00557200(void* self) {
    store(self, 0, 0);
    store(self, 4, 0);
    store(self, 8, 0);
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_005aa030(void* self) {
    void* device = reinterpret_cast<void*>(load(self, 0));
    if (device) {
        com(device, 0x20);
        device = reinterpret_cast<void*>(load(self, 0));
        com(device, 8);
    }
}
extern "C" void __attribute__((thiscall)) FUN_005aa190(void* self) {
    void* device = reinterpret_cast<void*>(load(self, 0));
    if (device) {
        com(device, 0x20);
        device = reinterpret_cast<void*>(load(self, 0));
        if (device)
            com(device, 8);
    }
}
extern "C" void __attribute__((thiscall)) FUN_005aa540(void* self) {
    if (load(self, 0)) {
        void* child = reinterpret_cast<void*>(load(self, 4));
        if (child) {
            FUN_005aa030(child);
            fun_005cc620(child);
        }
        child = reinterpret_cast<void*>(load(self, 8));
        if (child) {
            FUN_005aa190(child);
            fun_005cc620(child);
        }
        com(reinterpret_cast<void*>(load(self, 0)), 8);
    }
}
