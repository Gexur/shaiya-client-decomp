#include "global_com_array_owner.h"
#include "core/com_array_owner.h"
#include "runtime/exit_registry.h"
extern "C" {
alignas(4) uint8_t dat_0224e498[173] = {};
void fun_006b76a0() {
    FUN_005b0c30(dat_0224e498);
    (void)fun_005ccf60(fun_006ba820);
}
void fun_006ba820() {
    FUN_005b2870(dat_0224e498);
}
}

__asm__(".globl _dat_0224e541\n.set _dat_0224e541, _dat_0224e498+169\n");
