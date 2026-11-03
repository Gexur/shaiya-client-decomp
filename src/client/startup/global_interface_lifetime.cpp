#include "global_interface_lifetime.h"
#include "../runtime/allocations.h"
#include "../runtime/exit_registry.h"
extern "C" {
const OriginalInterfaceDeleting dat_006cd2a8[1] = {FUN_00584d30};
const OriginalInterfaceDeleting* dat_0070c0ac = dat_006cd2a8;
}
extern "C" void* __attribute__((thiscall)) FUN_00584d30(void* object, uint32_t flags) {
    *static_cast<const OriginalInterfaceDeleting**>(object) = dat_006cd2a8;
    if (flags & 1)
        fun_005cc620(object);
    return object;
}
extern "C" void fun_006b7670() {
    (void)fun_005ccf60(fun_006ba730);
}
extern "C" void fun_006ba730() {
    dat_0070c0ac = dat_006cd2a8;
}
