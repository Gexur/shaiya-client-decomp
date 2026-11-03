#include "library_owner8.h"
#include "../runtime/allocations.h"
extern "C" {
__declspec(dllimport) int32_t __attribute__((stdcall)) FreeLibrary(void*);
const OriginalLibraryDeleting dat_006c5998[1] = {FUN_00535f90};
}
extern "C" OriginalLibraryOwner8* __attribute__((thiscall))
FUN_00535e70(OriginalLibraryOwner8* self) {
    self->vtable = dat_006c5998;
    self->module = nullptr;
    return self;
}
extern "C" void __attribute__((thiscall)) FUN_00535e80(OriginalLibraryOwner8* self) {
    self->vtable = dat_006c5998;
    void* module = self->module;
    if (module != nullptr)
        (void)FreeLibrary(module);
}
extern "C" OriginalLibraryOwner8* __attribute__((thiscall))
FUN_00535f90(OriginalLibraryOwner8* self, uint32_t flags) {
    // Original deleting entry loads the module before installing the table;
    // the ordinary destructor above performs those accesses in reverse order.
    void* module = self->module;
    self->vtable = dat_006c5998;
    if (module != nullptr)
        (void)FreeLibrary(module);
    if (flags & 1)
        fun_005cc620(self);
    return self;
}
