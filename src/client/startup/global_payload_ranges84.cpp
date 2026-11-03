#include "startup/global_payload_ranges84.h"
#include "runtime/array_lifetime.h"
#include "runtime/exit_registry.h"
extern "C" {
OriginalPayloadRanges84 dat_0223f918[128] = {};
void fun_006b7640() {
    fun_005ce6bb(dat_0223f918, 84, 128, reinterpret_cast<OriginalElementCallback>(FUN_00585700),
                 reinterpret_cast<OriginalElementCallback>(FUN_00585440));
    (void)fun_005ccf60(fun_006ba770);
}
void fun_006ba770() {
    fun_005cdcbc(dat_0223f918, 84, 128, reinterpret_cast<OriginalElementCallback>(FUN_00585440));
}
}

__asm__(".globl _dat_0223f91c\n.set _dat_0223f91c, _dat_0223f918+4\n");
